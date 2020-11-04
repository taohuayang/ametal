/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
*******************************************************************************/

/**
 * \file
 * \brief SPI ������ʵ�ֺ���
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zsn700_dma.h"
#include "zsn700_dma_chan.h"
#include "zsn700_regbase.h"
#include "hw/amhw_zsn700_spi.h"
#include "am_zsn700_spi_dma.h"

/*******************************************************************************
  SPI ״̬���¼�����
*******************************************************************************/

/** \brief ��ȡSPI������Ƶ�� */
#define __SPI_FRQIIN_GET(p_hw_spi)    am_clk_rate_get(p_this->p_devinfo->clk_id)

/** \brief ��ȡSPI��֧�ֵ�����ٶ� */
#define __SPI_MAXSPEED_GET(p_hw_spi) (__SPI_FRQIIN_GET(p_hw_spi) / 2)

/** \brief ��ȡSPI֧�ֵ���С�ٶ� */
#define __SPI_MINSPEED_GET(p_hw_spi) (__SPI_FRQIIN_GET(p_hw_spi) / 128)

/**
 * \brief SPI ������״̬
 */

#define __SPI_ST_IDLE               0                   /**< \brief����״̬ */
#define __SPI_ST_MSG_START          1                   /**< \brief��Ϣ��ʼ */
#define __SPI_ST_TRANS_START        2                   /**< \brief���俪ʼ */
#define __SPI_ST_DMA_TRANS_DATA     3                   /**< \briefDMA ���� */

/**
 * \briefSPI �������¼�
 *
 */

#define __SPI_EVT_NUM_GET(event)    ((event) & 0xFFFF)
#define __SPI_EVT_PAR_GET(event)    ((event >> 16) & 0xFFFF)
#define __SPI_EVT(evt_num, evt_par) (((evt_num) & 0xFFFF) | ((evt_par) << 16))

#define __SPI_EVT_NONE              __SPI_EVT(0, 0)     /**< \brief ���¼� */
#define __SPI_EVT_TRANS_LAUNCH      __SPI_EVT(1, 0)     /**< \brief ������� */
#define __SPI_EVT_DMA_TRANS_DATA    __SPI_EVT(2, 0)     /**< \brief DMA�������� */

/*******************************************************************************
  ģ���ں�������
*******************************************************************************/
am_local void __spi_default_cs_ha    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_la    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state);

am_local void __spi_cs_on  (am_zsn700_spi_dma_dev_t *p_this, am_spi_device_t *p_dev);
am_local void __spi_cs_off (am_zsn700_spi_dma_dev_t *p_this, am_spi_device_t *p_dev);

am_local int  __spi_hard_init (am_zsn700_spi_dma_dev_t *p_this);
am_local int  __spi_config (am_zsn700_spi_dma_dev_t *p_this);

am_local uint32_t __spi_speed_cfg (am_zsn700_spi_dma_dev_t *p_dev,
                                   uint32_t                 target_baud);

am_local int  __spi_mst_sm_event (am_zsn700_spi_dma_dev_t *p_dev, uint32_t event);

/*******************************************************************************
  SPI������������
*******************************************************************************/
am_local int __spi_info_get  (void *p_arg, am_spi_info_t   *p_info);
am_local int __spi_setup     (void *p_arg, am_spi_device_t *p_dev );
am_local int __spi_msg_start (void              *p_drv,
                              am_spi_device_t   *p_dev,
                              am_spi_message_t  *p_msg);

/**
 * \brief SPI ��������
 */
am_local am_const struct am_spi_drv_funcs __g_spi_drv_funcs = {
    __spi_info_get,
    __spi_setup,
    __spi_msg_start,
};

/******************************************************************************/

/**
 * \brief Ĭ��CS�ſ��ƺ������ߵ�ƽ��Ч
 */
am_local
void __spi_default_cs_ha (am_spi_device_t *p_dev, int state)
{
    am_gpio_set(p_dev->cs_pin, state ? 1 : 0);
}

/**
 * \brief Ĭ��CS�ſ��ƺ������͵�ƽ��Ч
 */
am_local
void __spi_default_cs_la (am_spi_device_t *p_dev, int state)
{
    am_gpio_set(p_dev->cs_pin, state ? 0 : 1);
}

/**
 * \brief Ĭ��CS�ſ��ƺ�������Ӳ�����п���
 */
am_local
void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state)
{
    return;
}

/**
 * \brief CS���ż���
 */
am_local
void __spi_cs_on (am_zsn700_spi_dma_dev_t *p_this, am_spi_device_t *p_dev)
{
    amhw_zsn700_spi_t     *p_hw_spi = (amhw_zsn700_spi_t *)(p_this->p_devinfo->spi_reg_base);

    /* if last device toggled after message */
    if (p_this->p_tgl_dev != NULL) {

        /* last message on defferent device */
        if (p_this->p_tgl_dev != p_dev) {
            p_this->p_tgl_dev->pfunc_cs(p_this->p_tgl_dev, 0);
        }
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 1);

    /* SPI�ײ�Ĵ����ڲ�CS���ƣ���ЧSPI����Ź�������һ������������� */
    amhw_zsn700_spi_cs_sel(p_hw_spi, AM_TRUE);
}

/**
 * \brief CS����ȥ��
 */
am_local
void __spi_cs_off (am_zsn700_spi_dma_dev_t   *p_this,
                   am_spi_device_t           *p_dev)
{
    amhw_zsn700_spi_t     *p_hw_spi = (amhw_zsn700_spi_t *)(p_this->p_devinfo->spi_reg_base);

    if (p_this->p_tgl_dev == p_dev) {
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 0);

    /* SPI�ײ�Ĵ����ڲ�CS���ƣ���ЧSPI����Ź�������һ������������� */
    amhw_zsn700_spi_cs_sel(p_hw_spi, AM_FALSE);
}

/******************************************************************************/

/**
 * \brief ���һ�� message �������������б�ĩβ
 * \note���ô˺�����������������
 */
am_static_inline
void __spi_msg_in (am_zsn700_spi_dma_dev_t *p_dev, struct am_spi_message *p_msg)
{
    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                                             &(p_dev->msg_list));
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \note���ô˺�����������������
 */
am_static_inline
struct am_spi_message *__spi_msg_out (am_zsn700_spi_dma_dev_t *p_dev)
{
    if (am_list_empty_careful(&(p_dev->msg_list))) {
        return NULL;
    } else {
        struct am_list_head *p_node = p_dev->msg_list.next;
        am_list_del(p_node);
        return am_list_entry(p_node, struct am_spi_message, ctlrdata);
    }
}

/**
 * \brief ��message�б��ͷȡ��һ�� transfer
 * \note ���ô˺�����������������
 */
am_static_inline
struct am_spi_transfer *__spi_trans_out (am_spi_message_t *msg)
{
    if (am_list_empty_careful(&(msg->transfers))) {
        return NULL;
    } else {
        struct am_list_head *p_node = msg->transfers.next;
        am_list_del(p_node);
        return am_list_entry(p_node, struct am_spi_transfer, trans_node);
    }
}

/******************************************************************************/

am_local
int __spi_setup (void *p_arg, am_spi_device_t *p_dev)
{
    am_zsn700_spi_dma_dev_t *p_this = (am_zsn700_spi_dma_dev_t *)p_arg;

    uint32_t max_speed, min_speed;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* Ĭ������Ϊ8λ */
    if (p_dev->bits_per_word != 8) {
        p_dev->bits_per_word = 8;
    }

    /* ���SPI���ʲ��ܳ�����ʱ�ӣ���С����С����ʱ��65536��Ƶ */
    max_speed = __SPI_MAXSPEED_GET(p_hw_spi);
    min_speed = __SPI_MINSPEED_GET(p_hw_spi);

    if (p_dev->max_speed_hz > max_speed) {
        p_dev->max_speed_hz = max_speed;
    } else if (p_dev->max_speed_hz < min_speed) {
        return -AM_ENOTSUP;
    }

    /* ��Ƭѡ���� */
    if (p_dev->mode & AM_SPI_NO_CS) {
        p_dev->pfunc_cs = __spi_default_cs_dummy;

    /* ��Ƭѡ���� */
    }  else {

        /* ���ṩ��Ĭ��Ƭѡ���� */
        if (p_dev->pfunc_cs == NULL) {

            /* Ƭѡ�ߵ�ƽ��Ч */
            if (p_dev->mode & AM_SPI_CS_HIGH) {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_LOW);
                p_dev->pfunc_cs = __spi_default_cs_ha;

            /* Ƭѡ�͵�ƽ��Ч */
            } else {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_HIGH);
                p_dev->pfunc_cs = __spi_default_cs_la;
            }
        }
    }

    /* ���Ƭѡ�ź� */
    __spi_cs_off(p_this, p_dev);

    return AM_OK;
}

am_local
int __spi_info_get (void *p_arg, am_spi_info_t *p_info)
{
    am_zsn700_spi_dma_dev_t *p_this   = (am_zsn700_spi_dma_dev_t *)p_arg;

    if (p_info == NULL) {
        return -AM_EINVAL;
    }

    /* ������ʵ��� PCLK */
    p_info->max_speed = __SPI_MAXSPEED_GET(p_hw_spi);
    p_info->min_speed = __SPI_MINSPEED_GET(p_hw_spi);
    p_info->features  = AM_SPI_CS_HIGH   |
                        AM_SPI_MODE_0    |
                        AM_SPI_MODE_1    |
                        AM_SPI_MODE_2    |
                        AM_SPI_MODE_3;   /* features */
    return AM_OK;
}

/**
 * \brief SPI Ӳ����ʼ��
 */
am_local
int __spi_hard_init (am_zsn700_spi_dma_dev_t *p_this)
{
    amhw_zsn700_spi_t *p_hw_spi = (amhw_zsn700_spi_t *)(p_this->p_devinfo->spi_reg_base);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* ����Ϊ����ģʽ */
    amhw_zsn700_spi_mode_sel(p_hw_spi, AMHW_ZSN700_SPI_MODE_TYPE_MASTER);

    /* SPIʹ�� */
    amhw_zsn700_spi_enable(p_hw_spi, AM_TRUE);

    /* ��ʼ������SPI */
    return AM_OK;
}



am_local
void __dma_isr (void *p_arg, uint32_t stat)
{
    am_zsn700_spi_dma_dev_t *p_this   = (am_zsn700_spi_dma_dev_t *)p_arg;
    amhw_zsn700_spi_t       *p_hw_spi = (amhw_zsn700_spi_t *)(p_this->p_devinfo->spi_reg_base);


    /* �жϷ��� */
    if (stat == AM_ZSN700_DMA_INT_COMPLETE)
    {
        /* ��¼�ɹ������ֽ��� */
        if (p_this->p_cur_trans->p_txbuf != NULL) {
            p_this->p_cur_msg->actual_length += (p_this->p_cur_trans->nbytes)
                            *(p_this->p_cur_spi_dev->bits_per_word < 9 ? 1 : 2);
        }

        if ((p_this != NULL) &&
            (p_this->p_isr_msg != NULL) &&
            (p_this->p_isr_msg->pfn_complete != NULL)) {
            p_this->p_isr_msg->pfn_complete(p_this->p_isr_msg->p_arg);
        }

        /* ������� */
        __spi_mst_sm_event(p_this, __SPI_EVT_TRANS_LAUNCH);

        /* ���� */
        amhw_zsn700_spi_dma_tx_disable(p_hw_spi);
        amhw_zsn700_spi_dma_rx_disable(p_hw_spi);

        /* Ƭѡ�ر� */
        __spi_cs_off(p_this, p_this->p_cur_spi_dev);

        p_this->busy = AM_FALSE;

    } else {
        /* �ж�Դ��ƥ�� */
    }
}

/**
 * \brief SPI ʹ��DMA����
 */
am_local
int __spi_dma_trans (am_zsn700_spi_dma_dev_t *p_dev)
{
    am_zsn700_spi_dma_dev_t           *p_this      = (am_zsn700_spi_dma_dev_t *)p_dev;
    const am_zsn700_spi_dma_devinfo_t *p_devinfo   = p_this->p_devinfo;
    amhw_zsn700_spi_t                 *p_hw_spi    = (amhw_zsn700_spi_t *)(p_devinfo->spi_reg_base);
    am_spi_transfer_t                 *p_cur_trans = p_dev->p_cur_trans;

    static uint16_t tx_rx_trans = 0; 
    uint32_t   dma_flags[2]     = {0};  /* DMA����ͨ�������� */

    /* ����DMA�жϷ����� */
    am_zsn700_dma_isr_connect(p_this->p_devinfo->dma_chan_tx,
                           __dma_isr, 
                           (void *)p_this);

    /* DMA����ͨ������ */
    dma_flags[0] = AMHW_ZSN700_DMA_CHAN_TRANSFER_MODE_BLOCK    | /* SPIֻ�п鴫��ģʽ */
                   AMHW_ZSN700_DMA_CHAN_SIZE_8BIT              | /* ����λ�� 8bit */

                   AMHW_ZSN700_DMA_CHAN_RELOAD_SRC_ADD_DISABLE | /* Դ��ַ������*/

                   AMHW_ZSN700_DMA_CHAN_DST_ADD_INC_DISABLE    | /* Ŀ���ַ������ */
                   AMHW_ZSN700_DMA_CHAN_RELOAD_DST_ADD_ENABLE  | /* Ŀ���ַ���� */

                   AMHW_ZSN700_DMA_CHAN_RELOAD_COUNTER_ENABLE  | /* �������������� */
                   AMHW_ZSN700_DMA_CHAN_INT_ERR_DISABLE        | /* ��������жϽ��� */
                   AMHW_ZSN700_DMA_CHAN_INT_TX_CMP_ENABLE      | /* ��������ж�ʹ�� */
                   AMHW_ZSN700_DMA_CHAN_CIRCULAR_MODE_DISABLE ;  /* �ر�ѭ��ģʽ */

    /* DMA����ͨ������ */
    dma_flags[1] = AMHW_ZSN700_DMA_CHAN_TRANSFER_MODE_BLOCK    | /* SPIֻ�п鴫��ģʽ */
                   AMHW_ZSN700_DMA_CHAN_SIZE_8BIT              | /* ����λ�� 8bit */

                   AMHW_ZSN700_DMA_CHAN_SRC_ADD_INC_DISABLE    | /* Դ��ַ������ */
                   AMHW_ZSN700_DMA_CHAN_RELOAD_SRC_ADD_ENABLE  | /* Դ��ַ����*/

                   AMHW_ZSN700_DMA_CHAN_RELOAD_DST_ADD_DISABLE | /* Ŀ���ַ������ */

                   AMHW_ZSN700_DMA_CHAN_RELOAD_COUNTER_ENABLE  | /* �������������� */
                   AMHW_ZSN700_DMA_CHAN_INT_ERR_DISABLE        | /* ��������жϽ��� */
                   AMHW_ZSN700_DMA_CHAN_INT_TX_CMP_ENABLE      | /* ��������ж�ʹ�� */
                   AMHW_ZSN700_DMA_CHAN_CIRCULAR_MODE_DISABLE ;  /* �ر�ѭ��ģʽ */

    /* ֻ���Ͳ��������� */
    if (p_cur_trans->p_rxbuf == NULL) {

        /* Ŀ���ַ������ (��������buff��ַ������)*/;
        dma_flags[1] |= AMHW_ZSN700_DMA_CHAN_DST_ADD_INC_DISABLE;

        /* ��������ͨ�������� */
        am_zsn700_dma_xfer_desc_build(&(p_this->g_desc[1]),       /* ͨ�������� */
                                    (uint32_t)(&(p_hw_spi->data)),/* Դ�������׵�ַ */
                                    (uint32_t)(&tx_rx_trans),     /* Ŀ�Ļ������׵�ַ */
                                     p_cur_trans->nbytes,         /* �����ֽ��� */
                                     dma_flags[1]);               /* �������� */

    /* ���ڽ������� */
    } else {

        /* Ŀ���ַ����(��������buff��ַ����) */
        dma_flags[1] |= AMHW_ZSN700_DMA_CHAN_DST_ADD_INC_ENABLE;

        /* ��������ͨ�������� */ 
        am_zsn700_dma_xfer_desc_build(&(p_this->g_desc[1]),          /* ͨ�������� */
                                    (uint32_t)(&(p_hw_spi->data)),   /* Դ�������׵�ַ */
                                    (uint32_t)(p_cur_trans->p_rxbuf),/* Ŀ�Ļ������׵�ַ */
                                     p_cur_trans->nbytes,            /* �����ֽ��� */
                                     dma_flags[1]);                  /* �������� */
    }

    if (p_cur_trans->p_txbuf == NULL) {

        /* Դ��ַ������(��������buff��ַ������) */
        dma_flags[0] |= AMHW_ZSN700_DMA_CHAN_SRC_ADD_INC_DISABLE;

        /* ��������ͨ�������� */
        am_zsn700_dma_xfer_desc_build(&(p_this->g_desc[0]),       /* ͨ�������� */
                                    (uint32_t)(&tx_rx_trans),          /* Դ�������׵�ַ */
                                    (uint32_t)(&(p_hw_spi->data)),/* Ŀ�Ļ������׵�ַ */
                                    p_cur_trans->nbytes,          /* �����ֽ��� */
                                    dma_flags[0]);                /* �������� */
    } else {

        /* Դ��ַ����(��������buff��ַ����) */
        dma_flags[0] |= AMHW_ZSN700_DMA_CHAN_SRC_ADD_INC_ENABLE;

        /* ��������ͨ�������� */
        am_zsn700_dma_xfer_desc_build(&(p_this->g_desc[0]),          /* ͨ�������� */
                                    (uint32_t)(p_cur_trans->p_txbuf),/* Դ�������׵�ַ */
                                    (uint32_t)(&(p_hw_spi->data)),   /* Ŀ�Ļ������׵�ַ */
                                    p_cur_trans->nbytes,             /* �����ֽ��� */
                                    dma_flags[0]);                   /* �������� */
    }

    if (am_zsn700_dma_xfer_desc_chan_cfg(&(p_this->g_desc[0]),
                                        AMHW_ZSN700_DMA_MER_TO_PER,  /* �ڴ浽���� */
                                        p_this->p_devinfo->dma_chan_tx) == AM_ERROR) {
        return AM_ERROR;
    }

    if (am_zsn700_dma_xfer_desc_chan_cfg(&(p_this->g_desc[1]),
                                        AMHW_ZSN700_DMA_PER_TO_MER,  /* ���赽�ڴ� */
                                        p_this->p_devinfo->dma_chan_rx) == AM_ERROR) {
        return AM_ERROR;
    }

    am_zsn700_dma_priority_same();

    /* ����ÿ��DMA������СΪ�ѿ�����ͨ��������1�� */
    am_zsn700_dma_block_data_size(p_this->p_devinfo->dma_chan_rx, 1);
    am_zsn700_dma_block_data_size(p_this->p_devinfo->dma_chan_tx, 1);

    /* ����DMA����Դ*/
    if((p_devinfo->spi_reg_base) == ZSN700_SPI0_BASE) {
        am_zsn700_dma_chan_src_set(p_this->p_devinfo->dma_chan_rx,
                                   ZSN700_DMA_SRC_TYPE_SPI0_RX);
        am_zsn700_dma_chan_src_set(p_this->p_devinfo->dma_chan_tx,
                                   ZSN700_DMA_SRC_TYPE_SPI0_TX);

    } else if((p_devinfo->spi_reg_base) == ZSN700_SPI1_BASE) {

        am_zsn700_dma_chan_src_set(p_this->p_devinfo->dma_chan_rx,
                                   ZSN700_DMA_SRC_TYPE_SPI1_RX);

        am_zsn700_dma_chan_src_set(p_this->p_devinfo->dma_chan_tx,
                                   ZSN700_DMA_SRC_TYPE_SPI1_TX);
    }

    am_zsn700_dma_chan_start(p_this->p_devinfo->dma_chan_rx);
    am_zsn700_dma_chan_start(p_this->p_devinfo->dma_chan_tx);

    return AM_OK;
}

am_local
int __spi_config (am_zsn700_spi_dma_dev_t *p_this)
{
    const am_zsn700_spi_dma_devinfo_t *p_devinfo = p_this->p_devinfo;
    amhw_zsn700_spi_t                 *p_hw_spi  = (amhw_zsn700_spi_t *)(p_devinfo->spi_reg_base);
    am_spi_transfer_t                 *p_trans   = p_this->p_cur_trans;

    /* ���Ϊ0��ʹ��Ĭ�ϲ���ֵ */
    if (p_trans->bits_per_word == 0) {
        p_trans->bits_per_word = p_this->p_cur_spi_dev->bits_per_word;
    }

    if (p_trans->speed_hz == 0) {
        p_trans->speed_hz = p_this->p_cur_spi_dev->max_speed_hz;
    }

    /* �����ֽ�����Ч�Լ�� */
    if (p_trans->bits_per_word != 8) {
        return -AM_EINVAL;
    }

    /* ���÷�Ƶֵ��Ч�Լ�� */
    if (p_trans->speed_hz > __SPI_MAXSPEED_GET(p_hw_spi) ||
        p_trans->speed_hz < __SPI_MINSPEED_GET(p_hw_spi)) {
        return -AM_EINVAL;
    }

    /* ���ͺͽ��ջ�������Ч�Լ�� */
    if ((p_trans->p_txbuf == NULL) && (p_trans->p_rxbuf == NULL)) {
        return -AM_EINVAL;
    }

    /* �����ֽ������ */
    if (p_trans->nbytes == 0) {
        return -AM_ELOW;
    }

    /* ����SPIģʽ */
    amhw_zsn700_spi_clk_mode_set(p_hw_spi, p_this->p_cur_spi_dev->mode);

    /* ����Ϊ����ģʽ */
    amhw_zsn700_spi_mode_sel(p_hw_spi, AMHW_ZSN700_SPI_MODE_TYPE_MASTER);

    /* ����SPI���� */
    __spi_speed_cfg(p_this, p_trans->speed_hz);

    return AM_OK;
}

/**
 * \brief SPI �������ݺ���
 */
am_local
int __spi_msg_start (void              *p_drv,
                     am_spi_device_t   *p_dev,
                     am_spi_message_t  *p_msg)
{
    am_zsn700_spi_dma_dev_t *p_this = (am_zsn700_spi_dma_dev_t *)p_drv;

    int key;

    /* �豸��Ч�Լ�� */
    if ((p_drv == NULL) || (p_dev == NULL) || (p_msg == NULL) ){
        return -AM_EINVAL;
    }

    p_msg->p_spi_dev       = p_dev; /* �豸������Ϣ���뵽��Ϣ�� */
    p_this->p_cur_msg      = p_msg; /* ����ǰ�豸������Ϣ���� */
    p_this->nbytes_to_recv = 0;     /* �������ַ�����0 */
    p_this->data_ptr       = 0;     /* �ѽ����ַ�����0 */

    key = am_int_cpu_lock();

    /* ��ǰ���ڴ�����Ϣ��ֻ��Ҫ���µ���Ϣ���������� */
    if (p_this->busy == AM_TRUE) {
        __spi_msg_in(p_this, p_msg);
        am_int_cpu_unlock(key);
        return AM_OK;
    } else {
        p_this->busy = AM_TRUE;
        __spi_msg_in(p_this, p_msg);
        p_msg->status = -AM_EISCONN; /* �����Ŷ��� */
        am_int_cpu_unlock(key);

        /* ����״̬�� */
        return __spi_mst_sm_event(p_this, __SPI_EVT_TRANS_LAUNCH);
    }
}

/******************************************************************************/

/*  ״̬���ڲ�״̬�л� */
#define __SPI_NEXT_STATE(s, e) \
    do { \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

/**
 * \brief SPI ʹ��״̬������
 */
am_local
int __spi_mst_sm_event (am_zsn700_spi_dma_dev_t *p_dev, uint32_t event)
{
    volatile uint32_t new_event = __SPI_EVT_NONE;
    amhw_zsn700_spi_t *p_hw_spi = (amhw_zsn700_spi_t *)(p_dev->p_devinfo->spi_reg_base);


    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    while (1) {

        if (new_event != __SPI_EVT_NONE) {  /* ������¼��Ƿ������ڲ� */
            event     = new_event;
            new_event  = __SPI_EVT_NONE;
        }

        switch (p_dev->state) {

        case __SPI_ST_IDLE:         /* ���������ڿ���״̬ */
        {
            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ����״̬�ȴ�����Ϣ�������������� */
            }

            /* �л�����Ϣ��ʼ״̬������break */
        }
        /* no break */

        case __SPI_ST_MSG_START:    /* ��Ϣ��ʼ */
        {
            am_spi_message_t  *p_cur_msg   = NULL;

            int key;

            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ��Ϣ��ʼ״̬�ȴ�����Ϣ�������������� */
            }

            key = am_int_cpu_lock();
            p_cur_msg          = __spi_msg_out(p_dev);
            p_dev->p_cur_msg   = p_cur_msg;

            if (p_cur_msg) {
                p_cur_msg->status = -AM_EINPROGRESS;
            } else {

                p_dev->busy = AM_FALSE;
            }
            am_int_cpu_unlock(key);

            /* ����Ҫ�������Ϣ */
            if (p_cur_msg == NULL) {
                __SPI_NEXT_STATE(__SPI_ST_IDLE, __SPI_EVT_NONE);
                break;
            } else {

                p_dev->p_cur_spi_dev = p_cur_msg->p_spi_dev;

                /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
                __SPI_NEXT_STATE(__SPI_ST_TRANS_START, __SPI_EVT_TRANS_LAUNCH);

                event     = new_event;
                new_event = __SPI_EVT_NONE;
            }
        }
        /* no break */

        case __SPI_ST_TRANS_START:  /* ���俪ʼ */
        {
            am_spi_message_t *p_cur_msg = p_dev->p_cur_msg;

            p_dev->p_isr_msg = p_cur_msg;

            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /* ���俪ʼ״̬�ȴ�����Ϣ�������������� */
            }

            /* ��ǰ��Ϣ������� */
            if (am_list_empty(&(p_cur_msg->transfers))) {

                p_cur_msg->actual_length = 0;

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                __SPI_NEXT_STATE(__SPI_ST_MSG_START, __SPI_EVT_TRANS_LAUNCH);

            } else {

                /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */
                am_spi_transfer_t *p_cur_trans = __spi_trans_out(p_cur_msg);
                p_dev->p_cur_trans             = p_cur_trans;

                /* reset current data pointer */
                p_dev->data_ptr       = 0;
                p_dev->nbytes_to_recv = 0;

                /* ����SPI������� */
                __spi_config(p_dev);

                /* CSѡͨ */
                __spi_cs_on(p_dev, p_dev->p_cur_spi_dev);

                __SPI_NEXT_STATE(__SPI_ST_DMA_TRANS_DATA, __SPI_EVT_DMA_TRANS_DATA);

            }
            break;
        }

        case __SPI_ST_DMA_TRANS_DATA:    /* DMA�������� */
        {
            if (event != __SPI_EVT_DMA_TRANS_DATA) {
                return -AM_EINVAL;  /* ��������״̬�ȴ�����Ϣ�����Ƿ������� */
            }

            /* ��һ״̬���Ƿ���״̬ */
            __SPI_NEXT_STATE(__SPI_ST_TRANS_START, __SPI_EVT_NONE);

            amhw_zsn700_spi_dma_tx_enable(p_hw_spi);
            amhw_zsn700_spi_dma_rx_enable(p_hw_spi);

            /* ʹ��DMA���� */
            __spi_dma_trans(p_dev);

            break;
        }

        /*
         * ��ԶҲ�������е����
         */
        default:
            break;
        }

        /* û�������ڲ�����Ϣ, ���� */
        if (new_event == __SPI_EVT_NONE) {
            break;
        }
    }
    return AM_OK;
}

/******************************************************************************/

/**
 * \brief SPI ��ʼ��
 */
am_spi_handle_t am_zsn700_spi_dma_init (am_zsn700_spi_dma_dev_t           *p_dev,
                                        const am_zsn700_spi_dma_devinfo_t *p_devinfo)
{
    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->spi_serve.p_funcs = (struct am_spi_drv_funcs *)&__g_spi_drv_funcs;
    p_dev->spi_serve.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    p_dev->p_cur_spi_dev    = NULL;
    p_dev->p_tgl_dev        = NULL;
    p_dev->busy             = AM_FALSE;
    p_dev->p_cur_msg        = NULL;
    p_dev->p_cur_trans      = NULL;
    p_dev->data_ptr         = 0;
    p_dev->nbytes_to_recv   = 0;
    p_dev->state            = __SPI_ST_IDLE;     /* ��ʼ��Ϊ����״̬ */

    am_list_head_init(&(p_dev->msg_list));

    if (__spi_hard_init(p_dev) != AM_OK) {
        return NULL;
    }

    return &(p_dev->spi_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_zsn700_spi_dma_deinit (am_spi_handle_t handle)
{
    am_zsn700_spi_dma_dev_t *p_dev    = (am_zsn700_spi_dma_dev_t *)handle;
    amhw_zsn700_spi_t       *p_hw_spi = (amhw_zsn700_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_serve.p_funcs = NULL;
    p_dev->spi_serve.p_drv   = NULL;

    /* ���� SPI */
    amhw_zsn700_spi_dma_tx_disable(p_hw_spi);
    amhw_zsn700_spi_dma_rx_disable(p_hw_spi);
    amhw_zsn700_spi_enable(p_hw_spi, AM_FALSE);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/**
 * \brief SPI�����ٶ�����
 *
 */
am_local
uint32_t __spi_speed_cfg (am_zsn700_spi_dma_dev_t *p_dev,
                          uint32_t                 target_speed)
{

    uint32_t clk, best_speed;  /* ��������ٶ� */
    uint8_t  i = 0;
    amhw_zsn700_spi_baud_rate_t baud_div = AMHW_ZSN700_SPI_BAUD_RATE_PCLK_0;

    amhw_zsn700_spi_t *p_hw_spi = (amhw_zsn700_spi_t *)
                                  (p_dev->p_devinfo->spi_reg_base);

    if(target_speed == 0) {
        baud_div = AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV2;
    } else {

        clk = am_clk_rate_get(p_dev->p_devinfo->clk_id);

        for(i = 1; i < 8; i++) {

            best_speed = clk >> i;
            if(best_speed <= target_speed) {
                break;
            }
        }
    }

    baud_div = (amhw_zsn700_spi_baud_rate_t)(i - 1);

    amhw_zsn700_spi_baud_rate_set(p_hw_spi, baud_div);

    best_speed = am_clk_rate_get(p_dev->p_devinfo->clk_id) /
                 (0x1ul << (baud_div + 1));

   return best_speed;
}

