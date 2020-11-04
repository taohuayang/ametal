/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief SPI ������ʵ�ֺ���
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-14  htf, first implementation
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include "am_zlg_spi_poll.h"
#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "hw/amhw_zlg_spi.h"

/*******************************************************************************
  SPI ״̬���¼�����
*******************************************************************************/

/**
 * SPI ������״̬
 */

#define __SPI_ST_IDLE               0                   /* ����״̬ */
#define __SPI_ST_MSG_START          1                   /* ��Ϣ��ʼ */
#define __SPI_ST_TRANS_START        2                   /* ���俪ʼ */
#define __SPI_ST_M_SEND_DATA        3                   /* �������� */
#define __SPI_ST_M_RECV_DATA        4                   /* �������� */

/**
 * SPI �������¼�
 *
 * ��32λ����16λ���¼���ţ���16λ���¼�����
 */

#define __SPI_EVT_NUM_GET(event)    ((event) & 0xFFFF)
#define __SPI_EVT_PAR_GET(event)    ((event >> 16) & 0xFFFF)
#define __SPI_EVT(evt_num, evt_par) (((evt_num) & 0xFFFF) | ((evt_par) << 16))

#define __SPI_EVT_NONE              __SPI_EVT(0, 0)     /* ���¼� */
#define __SPI_EVT_TRANS_LAUNCH      __SPI_EVT(1, 0)     /* ������� */
#define __SPI_EVT_M_SEND_DATA       __SPI_EVT(2, 0)     /* �������� */
#define __SPI_EVT_M_RECV_DATA       __SPI_EVT(3, 0)     /* �������� */

/*******************************************************************************
  ģ���ں�������
*******************************************************************************/
am_local void __spi_default_cs_ha    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_la    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state);

am_local void __spi_cs_on  (am_zlg_spi_poll_dev_t *p_this, am_spi_device_t *p_dev);
am_local void __spi_cs_off (am_zlg_spi_poll_dev_t *p_this, am_spi_device_t *p_dev);

am_local void __spi_write_data (am_zlg_spi_poll_dev_t *p_dev);
am_local void __spi_read_data (am_zlg_spi_poll_dev_t *p_dev);

am_local int  __spi_hard_init (am_zlg_spi_poll_dev_t *p_this);
am_local int  __spi_config (am_zlg_spi_poll_dev_t *p_this);

am_local uint32_t __spi_speed_cfg (am_zlg_spi_poll_dev_t *p_dev, uint32_t target_baud);

am_local int  __spi_mst_sm_event (am_zlg_spi_poll_dev_t *p_dev);
/*******************************************************************************
  SPI������������
*******************************************************************************/
am_local int __spi_info_get (void *p_arg, am_spi_info_t   *p_info);
am_local int __spi_setup    (void *p_arg, am_spi_device_t *p_dev );
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

/* ��ȡSPI������Ƶ�� */
#define __SPI_FRQIIN_GET(p_hw_spi)    am_clk_rate_get(p_this->p_devinfo->clk_id)

/* ��ȡSPI֧�ֵ�����ٶ� */
#define __SPI_MAXSPEED_GET(p_hw_spi) (__SPI_FRQIIN_GET(p_hw_spi) / 2)

/* ��ȡSPI֧�ֵ���С�ٶ� */
#define __SPI_MINSPEED_GET(p_hw_spi) (__SPI_FRQIIN_GET(p_hw_spi) / 65535)

/**
 * \brief λ��ת�ֽ�
 */
am_local
uint8_t __bits_to_bytes (uint8_t bits)
{
       uint8_t bytes = 0;
       bytes = (bits >> 3) + ((bits & 0x7) ? 1 : 0);
       return bytes;
}
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
void __spi_cs_on (am_zlg_spi_poll_dev_t *p_this, am_spi_device_t *p_dev)
{
    /* if last device toggled after message */
    if (p_this->p_tgl_dev != NULL) {

        /* last message on defferent device */
        if (p_this->p_tgl_dev != p_dev) {
            p_this->p_tgl_dev->pfunc_cs(p_this->p_tgl_dev, 0);
        }
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 1);
}

/**
 * \brief CS����ȥ��
 */
am_local
void __spi_cs_off (am_zlg_spi_poll_dev_t *p_this,
                   am_spi_device_t      *p_dev)
{
    if (p_this->p_tgl_dev == p_dev) {
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 0);
}

/******************************************************************************/

am_local
void __spi_write_data (am_zlg_spi_poll_dev_t *p_dev)
{
    amhw_zlg_spi_t    *p_hw_spi = (amhw_zlg_spi_t *)(p_dev->p_devinfo->spi_reg_base);
    am_spi_transfer_t *p_trans  = p_dev->p_cur_trans;

    while(!(amhw_zlg_spi_reg_cstat_get (p_hw_spi) & AMHW_ZLG_SPI_CSTAT_TX_EMPTY));

    /* tx_buf ��Ч */
    if (p_trans->p_txbuf != NULL) {
        /** \brief ���������ݵĻ�ַ+ƫ�� */
        uint8_t *ptr = (uint8_t *)(p_trans->p_txbuf) + p_dev->data_ptr;
        amhw_zlg_spi_tx_data8_put(p_hw_spi, *ptr);
    /* tx_buf ��Ч */
    } else {
        /* ������������Ч ֱ�ӷ�0 */
            amhw_zlg_spi_tx_data8_put(p_hw_spi, 0x00);
    }
    /** \brief ��������ݵ�byte�� */
    p_dev->nbytes_to_recv = __bits_to_bytes(p_dev->p_cur_spi_dev->bits_per_word); //todo
    p_dev->p_cur_msg->actual_length += p_dev->nbytes_to_recv;
}

am_local
void __spi_read_data (am_zlg_spi_poll_dev_t *p_dev)
{
    amhw_zlg_spi_t     *p_hw_spi = (amhw_zlg_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    am_spi_transfer_t  *p_trans  = p_dev->p_cur_trans;

    uint8_t  *p_buf8;

    p_buf8  = (uint8_t *)p_trans->p_rxbuf + p_dev->data_ptr;

    if (amhw_zlg_spi_reg_cstat_get (p_hw_spi) & AMHW_ZLG_SPI_CSTAT_RXVAL) {

        /* rx_buf ��Ч */
        if (p_trans->p_rxbuf != NULL && p_dev->nbytes_to_recv) {
             *p_buf8 = amhw_zlg_spi_rx_data8_get(p_hw_spi);
        /* rx_buf ��Ч���߲���Ҫ�������� */
        } else {
               (void)amhw_zlg_spi_rx_data8_get(p_hw_spi);
        }

        /* �Ѿ����ͻ���յ�����byte�� */
        p_dev->data_ptr += p_dev->nbytes_to_recv;
        p_dev->nbytes_to_recv = 0;

    }
}

/******************************************************************************/
/**
 * \brief ��message�б��ͷȡ��һ�� transfer
 * \attention ���ô˺�����������������
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
    am_zlg_spi_poll_dev_t *p_this = (am_zlg_spi_poll_dev_t *)p_arg;

    uint32_t max_speed, min_speed;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* Ĭ������Ϊ8λ����󲻳���16λ */
    if (p_dev->bits_per_word == 0) {
        p_dev->bits_per_word = 8;
    } else if (p_dev->bits_per_word > 32) {
        return -AM_ENOTSUP;
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
    am_zlg_spi_poll_dev_t  *p_this   = (am_zlg_spi_poll_dev_t *)p_arg;

    if (p_info == NULL) {
        return -AM_EINVAL;
    }

    /* ������ʵ��� PCLK */
    p_info->max_speed = __SPI_MAXSPEED_GET(p_hw_spi);
    p_info->min_speed = __SPI_MINSPEED_GET(p_hw_spi);
    p_info->features  = AM_SPI_CS_HIGH   |
                        AM_SPI_LSB_FIRST |
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
int __spi_hard_init (am_zlg_spi_poll_dev_t *p_this)
{
    amhw_zlg_spi_t *p_hw_spi = (amhw_zlg_spi_t *)(p_this->p_devinfo->spi_reg_base);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* ����Ϊ����ģʽ */
    amhw_zlg_spi_mode_sel(p_hw_spi, AMHW_ZLG_SPI_MODE_MASTER);
    amhw_zlg_spi_tx_enable(p_hw_spi, AM_TRUE);
    amhw_zlg_spi_rx_enable(p_hw_spi, AM_TRUE);
    amhw_zlg_spi_module_enable(p_hw_spi, AM_TRUE);

    /* ��ʼ������SPI */
    return AM_OK;
}

am_local
int __spi_config (am_zlg_spi_poll_dev_t *p_this)
{
    const am_zlg_spi_poll_devinfo_t *p_devinfo = p_this->p_devinfo;
    amhw_zlg_spi_t                  *p_hw_spi  = (amhw_zlg_spi_t *)(p_devinfo->spi_reg_base);
    am_spi_transfer_t               *p_trans   = p_this->p_cur_trans;

    uint32_t mode_flag = 0;

    /* ���Ϊ0��ʹ��Ĭ�ϲ���ֵ */
    if (p_trans->bits_per_word == 0) {
        p_trans->bits_per_word = p_this->p_cur_spi_dev->bits_per_word;
    }

    if (p_trans->speed_hz == 0) {
        p_trans->speed_hz = p_this->p_cur_spi_dev->max_speed_hz;
    }

    /* �����ֽ�����Ч�Լ�� */
    if (p_trans->bits_per_word > 32 || p_trans->bits_per_word < 1) {
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

    /**
     * ���õ�ǰ�豸ģʽ
     */
    mode_flag = 0;

    if (p_this->p_cur_spi_dev->mode & AM_SPI_LSB_FIRST) {
        mode_flag |= AMHW_ZLG_SPI_DATA_LSB;
    }

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_zlg_spi_clk_mode_set(p_hw_spi, (0x3 & p_this->p_cur_spi_dev->mode) ^ 0x01);

    /* ����SPI�������� */
    amhw_zlg_spi_first_bit_sel(p_hw_spi, (1u << 2) & mode_flag);

    amhw_zlg_spi_data_len_sel(p_hw_spi, AMHW_ZLG_SPI_DATA_LEN_8BIT);

    /* ����Ϊ����ģʽ */
    amhw_zlg_spi_mode_sel(p_hw_spi, AMHW_ZLG_SPI_MODE_MASTER);

    if (p_this->p_cur_spi_dev->bits_per_word > 8) {
            amhw_zlg_spi_valid_data_sel(p_hw_spi, AMHW_ZLG_SPI_VALID_DATA_32BIT);
            amhw_zlg_spi_first_bit_sel(p_hw_spi, AMHW_ZLG_SPI_DATA_LSB);
        if (p_this->p_cur_spi_dev->bits_per_word == 32) {
            amhw_zlg_spi_extlen_set(p_hw_spi, 0);
        } else {
            amhw_zlg_spi_extlen_set(p_hw_spi, p_this->p_cur_spi_dev->bits_per_word);
        }
    }

    if (p_trans->speed_hz > (72000000 / 5)) {

        /* ���� */
        amhw_zlg_spi_tx_data_edge_sel(p_hw_spi, AMHW_ZLG_SPI_TX_DATA_IMMEDIATELY);
        amhw_zlg_spi_rx_data_edge_sel(p_hw_spi, AMHW_ZLG_SPI_RX_DATA_LAST_CLOCK);

    } else {

        /* ���� */
        amhw_zlg_spi_tx_data_edge_sel(p_hw_spi, AMHW_ZLG_SPI_TX_DATA_ONE_CLOCK);
        amhw_zlg_spi_rx_data_edge_sel(p_hw_spi, AMHW_ZLG_SPI_RX_DATA_MID_CLOCK);

    }

    /* ����SPI���� */
    __spi_speed_cfg(p_this, p_trans->speed_hz);

    return AM_OK;
}

/**
 * \brief SPI�������ݺ���
 */
am_local
int __spi_msg_start (void              *p_drv,
                     am_spi_device_t   *p_dev,
                     am_spi_message_t  *p_msg)
{
    am_zlg_spi_poll_dev_t *p_this = (am_zlg_spi_poll_dev_t *)p_drv;

    p_this->p_cur_spi_dev  = p_dev;                         /* ����ǰ�豸������Ϣ���� */
    p_this->p_cur_msg      = p_msg;                         /* ����ǰ�豸������Ϣ���� */
    p_this->nbytes_to_recv = 0;                             /* �������ַ�����0 */
    p_this->data_ptr       = 0;                             /* �ѽ����ַ�����0 */

    p_this->busy = AM_TRUE;

    __spi_mst_sm_event(p_this);

    return AM_OK;
}

/******************************************************************************/


/**
 * \brief SPI ʹ��״̬������
 */
am_local
int __spi_mst_sm_event (am_zlg_spi_poll_dev_t *p_dev)
{
    am_spi_message_t  *p_cur_msg   = NULL;

    p_cur_msg = p_dev->p_cur_msg;

    while (!am_list_empty(&(p_cur_msg->transfers))) {
        /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */
        am_spi_transfer_t *p_cur_trans = __spi_trans_out(p_cur_msg);
        p_dev->p_cur_trans             = p_cur_trans;

        /* reset current data pointer */
        p_dev->data_ptr       = 0;
        p_dev->nbytes_to_recv = 0;

        /* ����ô���ָ��SPI�ֽ�������  �������ж� �û��Զ�������  */
        if(p_dev->p_cur_trans->bits_per_word != 0 || p_dev->p_cur_trans->speed_hz != 0){
           __spi_config(p_dev);
           p_dev->bef_bits_per_word = p_dev->p_cur_spi_dev->bits_per_word;
           p_dev->bef_speed_hz = p_dev->p_cur_trans->speed_hz;
        /* ����ô���Ĭ��SPI�ֽ�������  ���ϴδ��䱣���SPI�ֽ����� SPI �豸��ͬ  �������������  */
        }else if(p_dev->p_cur_trans->bits_per_word == 0 &&
               p_dev->bef_bits_per_word != p_dev->p_cur_spi_dev->bits_per_word){
            /* �ж�ʹ�ú��ִ��䷽ʽ   �ı�ʱ������������ */
            __spi_config(p_dev);
            p_dev->bef_bits_per_word = p_dev->p_cur_spi_dev->bits_per_word;
        }
       if(p_dev->p_cur_trans->speed_hz == 0 &&
            p_dev->bef_speed_hz != p_dev->p_cur_spi_dev->max_speed_hz ){
            /* ����SPI�������    �ı�ʱ������������     */
            __spi_config(p_dev);
            p_dev->bef_speed_hz = p_dev->p_cur_spi_dev->max_speed_hz;
        }
        /* CSѡͨ */
        __spi_cs_on(p_dev, p_dev->p_cur_spi_dev);
        while(p_dev->data_ptr < p_cur_trans->nbytes){
            __spi_write_data(p_dev);
            while(p_dev->nbytes_to_recv != 0){
                __spi_read_data(p_dev);
            }
        }
    }
    /* notify the caller */
    p_cur_msg->pfn_complete(p_cur_msg->p_arg);

    /* Ƭѡ�ر� */
    __spi_cs_off(p_dev, p_dev->p_cur_spi_dev);

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief SPI��ʼ��
 */
am_spi_handle_t am_zlg_spi_poll_init (am_zlg_spi_poll_dev_t           *p_dev,
                                     const am_zlg_spi_poll_devinfo_t *p_devinfo)
{
    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->spi_serve.p_funcs = (struct am_spi_drv_funcs *)&__g_spi_drv_funcs;
    p_dev->spi_serve.p_drv   = p_dev;

    p_dev->p_devinfo         = p_devinfo;

    p_dev->p_cur_spi_dev     = NULL;
    p_dev->p_tgl_dev         = NULL;
    p_dev->busy              = AM_FALSE;
    p_dev->p_cur_msg         = NULL;
    p_dev->p_cur_trans       = NULL;
    p_dev->data_ptr          = 0;
    p_dev->nbytes_to_recv    = 0;
    p_dev->state             = __SPI_ST_IDLE;     /* ��ʼ��Ϊ����״̬ */

    if (__spi_hard_init(p_dev) != AM_OK) {
        return NULL;
    }

    return &(p_dev->spi_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_zlg_spi_poll_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_poll_dev_t *p_dev    = (am_zlg_spi_poll_dev_t *)handle;
    amhw_zlg_spi_t        *p_hw_spi = (amhw_zlg_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_serve.p_funcs = NULL;
    p_dev->spi_serve.p_drv   = NULL;

    /* ����SPI */
    amhw_zlg_spi_module_enable(p_hw_spi, AM_FALSE);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/**
 * \brief SPI�����ٶ�����
 *
 */
am_local
uint32_t __spi_speed_cfg (am_zlg_spi_poll_dev_t *p_dev, uint32_t target_speed)
{

    uint32_t baud_div, best_speed;  /* ��������ٶ� */

    amhw_zlg_spi_t *p_hw_spi = (amhw_zlg_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    baud_div = am_clk_rate_get(p_dev->p_devinfo->clk_id) / target_speed;

    amhw_zlg_spi_baud_rate_set(p_hw_spi, baud_div);

    best_speed = target_speed;
   return best_speed;
}



