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
 * - 1.00 20-03-25  cds, first implementation
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include "am_hc32f460_spi_int.h"
#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "hw/amhw_hc32f460_spi.h"
#include "hc32f460_irq_handle.h"
#include "hc32f460_intctrl.h"

/*******************************************************************************
  SPI ״̬���¼�����
*******************************************************************************/

/**
 * SPI ������״̬
 */

#define __SPI_ST_IDLE               0                   /**< \brief ����״̬ */
#define __SPI_ST_MSG_START          1                   /**< \brief ��Ϣ��ʼ */
#define __SPI_ST_TRANS_START        2                   /**< \brief ���俪ʼ */
#define __SPI_ST_M_SEND_DATA        3                   /**< \brief �������� */
#define __SPI_ST_M_RECV_DATA        4                   /**< \brief �������� */

/**
 * SPI �������¼�
 *
 * ��32λ����16λ���¼���ţ���16λ���¼�����
 */

#define __SPI_EVT_NUM_GET(event)    ((event) & 0xFFFF)
#define __SPI_EVT_PAR_GET(event)    ((event >> 16) & 0xFFFF)
#define __SPI_EVT(evt_num, evt_par) (((evt_num) & 0xFFFF) | ((evt_par) << 16))

#define __SPI_EVT_NONE              __SPI_EVT(0, 0)     /**< \brief ���¼� */
#define __SPI_EVT_TRANS_LAUNCH      __SPI_EVT(1, 0)     /**< \brief ������� */
#define __SPI_EVT_M_SEND_DATA       __SPI_EVT(2, 0)     /**< \brief �������� */
#define __SPI_EVT_M_RECV_DATA       __SPI_EVT(3, 0)     /**< \brief �������� */

/*******************************************************************************
  ģ���ں�������
*******************************************************************************/
am_local void __spi_default_cs_ha    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_la    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state);

am_local void __spi_cs_on  (am_hc32f460_spi_int_dev_t *p_this, am_spi_device_t *p_dev);
am_local void __spi_cs_off (am_hc32f460_spi_int_dev_t *p_this, am_spi_device_t *p_dev);

am_local void __spi_write_data (am_hc32f460_spi_int_dev_t *p_dev);
am_local void __spi_read_data (am_hc32f460_spi_int_dev_t *p_dev);

void __spi_irq_handler (void *p_arg);
am_local int  __spi_hard_init (am_hc32f460_spi_int_dev_t *p_this);
am_local int  __spi_config (am_hc32f460_spi_int_dev_t *p_this);

am_local uint32_t __spi_speed_cfg (am_hc32f460_spi_int_dev_t *p_dev,
                                   uint32_t                 target_baud);

am_local int  __spi_mst_sm_event (am_hc32f460_spi_int_dev_t *p_dev, uint32_t event);
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

/** \brief ��ȡSPI������Ƶ�� */
#define __SPI_FRQIIN_GET(p_hw_spi)    am_clk_rate_get(p_this->p_devinfo->clk_id)

/** \brief ��ȡSPI֧�ֵ�����ٶ� */
#define __SPI_MAXSPEED_GET(p_hw_spi) (__SPI_FRQIIN_GET(p_hw_spi) / 2)

/** \brief ��ȡSPI֧�ֵ���С�ٶ� */
#define __SPI_MINSPEED_GET(p_hw_spi) (__SPI_FRQIIN_GET(p_hw_spi) / 128)

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
void __spi_cs_on (am_hc32f460_spi_int_dev_t *p_this, am_spi_device_t *p_dev)
{
    /** \brief if last device toggled after message */
    if (p_this->p_tgl_dev != NULL) {

        /** \brief last message on defferent device */
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
void __spi_cs_off (am_hc32f460_spi_int_dev_t *p_this,
                   am_spi_device_t      *p_dev)
{

    if (p_this->p_tgl_dev == p_dev) {
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 0);
}

/******************************************************************************/

am_local
void __spi_write_data (am_hc32f460_spi_int_dev_t *p_dev)
{
    amhw_hc32f460_spi_t *p_hw_spi = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);
    am_spi_transfer_t *p_trans  = p_dev->p_cur_trans;

    if (p_dev == NULL) {
        return ;
    }

    while(amhw_hc32f460_spi_flag_check (
            p_hw_spi, AMHW_HC32F460_SPI_STATUS_TXBUFFER_EMPTY) == AM_FALSE);
    /* tx_buf ��Ч */
    if (p_trans->p_txbuf != NULL) {

        /** \brief ���������ݵĻ�ַ+ƫ�� */
        uint8_t *ptr = (uint8_t *)(p_trans->p_txbuf) + p_dev->data_ptr;
        amhw_hc32f460_spi_tx_data8_put(p_hw_spi, *ptr);

    /* tx_buf ��Ч */
    } else {
        amhw_hc32f460_spi_tx_data8_put(p_hw_spi, 0x00);
    }

    /** \brief ��������ݵ�byte�� */
    p_dev->nbytes_to_recv = __bits_to_bytes(p_dev->p_cur_spi_dev->bits_per_word);
    p_dev->p_cur_msg->actual_length += p_dev->nbytes_to_recv;
}

am_local
void __spi_read_data (am_hc32f460_spi_int_dev_t *p_dev)
{
    amhw_hc32f460_spi_t *p_hw_spi = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    am_spi_transfer_t   *p_trans  = p_dev->p_cur_trans;
    uint8_t  *p_buf8;

    p_buf8  = (uint8_t *)p_trans->p_rxbuf + p_dev->data_ptr;

    if (p_dev == NULL) {
        return ;
    }

    if (amhw_hc32f460_spi_flag_check (
            p_hw_spi, AMHW_HC32F460_SPI_STATUS_RXBUFFER_FULL) == AM_TRUE) {

        /* rx_buf ��Ч */
        if (p_trans->p_rxbuf != NULL && p_dev->nbytes_to_recv) {
            *p_buf8 = amhw_hc32f460_spi_rx_data8_get(p_hw_spi);
        /* rx_buf ��Ч���߲���Ҫ�������� */
        } else {
            (void)amhw_hc32f460_spi_rx_data8_get(p_hw_spi);
        }

        /* �Ѿ����ͻ���յ�����byte�� */
        p_dev->data_ptr += p_dev->nbytes_to_recv;
        p_dev->nbytes_to_recv = 0;
    }
}

/******************************************************************************/

/**
 * \brief ���һ�� message �������������б�ĩβ
 * \attention ���ô˺�����������������
 */
am_static_inline
void __spi_msg_in (am_hc32f460_spi_int_dev_t *p_dev,
                   struct am_spi_message   *p_msg)
{
    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                                             &(p_dev->msg_list));
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_spi_message *__spi_msg_out (am_hc32f460_spi_int_dev_t *p_dev)
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
    am_hc32f460_spi_int_dev_t *p_this = (am_hc32f460_spi_int_dev_t *)p_arg;

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
    am_hc32f460_spi_int_dev_t  *p_this   = (am_hc32f460_spi_int_dev_t *)p_arg;

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
int __spi_hard_init (am_hc32f460_spi_int_dev_t *p_this)
{
    amhw_hc32f460_spi_t *p_hw_spi = (amhw_hc32f460_spi_t *)(p_this->p_devinfo->spi_reg_base);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* ����Ϊ����ģʽ */
    amhw_hc32f460_spi_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_MODE_MASTER);

    /* SPIʹ�� */
    amhw_hc32f460_spi_enable(p_hw_spi, AM_TRUE);

    /* ��ʼ������SPI */
    return AM_OK;
}


/**
 * \brief SPI �жϾ������
 */
void __spi_irq_handler (void *p_arg)
{
    am_hc32f460_spi_int_dev_t  *p_dev    = (am_hc32f460_spi_int_dev_t *)p_arg;
    amhw_hc32f460_spi_t        *p_hw_spi = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);


    /* �������� */
    if (amhw_hc32f460_spi_flag_check(
        p_hw_spi, AMHW_HC32F460_SPI_STATUS_TXBUFFER_EMPTY) == AM_TRUE) {

        __spi_mst_sm_event(p_dev, __SPI_EVT_M_SEND_DATA);
    }

    /* �������� */
    if (amhw_hc32f460_spi_flag_check(
        p_hw_spi, AMHW_HC32F460_SPI_STATUS_RXBUFFER_FULL) == AM_TRUE) {

        __spi_mst_sm_event(p_dev, __SPI_EVT_M_RECV_DATA);
    }
}

am_local
int __spi_config (am_hc32f460_spi_int_dev_t *p_this)
{
    const am_hc32f460_spi_int_devinfo_t *p_devinfo = p_this->p_devinfo;
    amhw_hc32f460_spi_t                 *p_hw_spi  = (amhw_hc32f460_spi_t *)(p_devinfo->spi_reg_base);
    am_spi_transfer_t                   *p_trans   = p_this->p_cur_trans;

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

    /**
     * ���õ�ǰ�豸ģʽ
     */
    if (p_this->p_cur_spi_dev->mode & AM_SPI_LSB_FIRST) {
        p_this->lsbfirst = AM_TRUE;
        amhw_hc32f460_spi_first_bit_position_set(p_hw_spi, AMHW_HC32F460_SPI_LSB_FIRST);
    } else {
        p_this->lsbfirst = AM_FALSE;
        amhw_hc32f460_spi_first_bit_position_set(p_hw_spi, AMHW_HC32F460_SPI_MSB_FIRST);
    }

    /* ����SPIͨ��ģʽ */
    amhw_hc32f460_spi_trans_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_TRANS_MODE_FULL_DUPLEX);

    /* ����SPI����ģʽ */
    if (p_this->p_cur_spi_dev->mode & AM_SPI_3WIRE) {
        amhw_hc32f460_spi_work_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_WORK_MODE_3LINE);
    } else {
        amhw_hc32f460_spi_work_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_WORK_MODE_4LINE);
    }

    /* �������ݳ��� */
    switch (p_this->p_cur_spi_dev->bits_per_word) {

    case 4:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT4);
        break;
    case 5:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT5);
        break;
    case 6:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT6);
        break;
    case 7:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT7);
        break;
    case 8:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT8);
        break;
    case 9:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT9);
        break;
    case 10:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT10);
        break;
    case 11:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT11);
        break;
    case 12:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT12);
        break;
    case 13:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT13);
        break;
    case 14:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT14);
        break;
    case 15:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT15);
        break;
    case 16:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT16);
        break;
    case 20:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT20);
        break;
    case 24:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT24);
        break;
    case 32:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT32);
        break;
    }


    /* ����Ϊ����ģʽ */
    amhw_hc32f460_spi_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_MODE_MASTER);

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_hc32f460_spi_clk_mode_set(p_hw_spi, 0x3 & p_this->p_cur_spi_dev->mode);

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
    am_hc32f460_spi_int_dev_t *p_this = (am_hc32f460_spi_int_dev_t *)p_drv;

    int key;

    /* �豸��Ч�Լ�� */
    if ((p_drv == NULL) || (p_dev == NULL) || (p_msg == NULL) ){
        return -AM_EINVAL;
    }

    p_msg->p_spi_dev       = p_dev; /**< \brief �豸������Ϣ���뵽��Ϣ�� */
    p_this->p_cur_msg      = p_msg; /**< \brief ����ǰ�豸������Ϣ���� */
    p_this->nbytes_to_recv = 0;     /**< \brief �������ַ�����0 */
    p_this->data_ptr       = 0;     /**< \brief �ѽ����ַ�����0 */

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
int __spi_mst_sm_event (am_hc32f460_spi_int_dev_t *p_dev, uint32_t event)
{
    amhw_hc32f460_spi_t *p_hw_spi = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    volatile uint32_t new_event = __SPI_EVT_NONE;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    while (1) {

        if (new_event != __SPI_EVT_NONE) {     /**< \brief ������¼��Ƿ������ڲ� */
            event     = new_event;
            new_event  = __SPI_EVT_NONE;
        }

        switch (p_dev->state) {

        case __SPI_ST_IDLE:         /**< \brief ���������ڿ���״̬ */
        {
            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;     /**< \brief ����״̬�ȴ�����Ϣ�������������� */
            }

            /* �л�����Ϣ��ʼ״̬������break */
        }
        /* no break */

        case __SPI_ST_MSG_START:    /**< \brief ��Ϣ��ʼ */
        {
            am_spi_message_t  *p_cur_msg   = NULL;

            int key;

            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /**< \brief ��Ϣ��ʼ״̬�ȴ�����Ϣ�������������� */
            }

            key = am_int_cpu_lock();
            p_cur_msg          = __spi_msg_out(p_dev);
            p_dev->p_cur_msg   = p_cur_msg;

            if (p_cur_msg) {
                p_cur_msg->status = -AM_EINPROGRESS;
            } else {

                /* �����ж� */
                amhw_hc32f460_spi_all_int_enable(p_hw_spi, AM_FALSE);
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

        case __SPI_ST_TRANS_START:  /**< \brief ���俪ʼ */
        {
            am_spi_message_t  *p_cur_msg   = p_dev->p_cur_msg;

            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;  /**< \brief ���俪ʼ״̬�ȴ�����Ϣ�������������� */
            }

            /* ��ǰ��Ϣ������� */
            if (am_list_empty(&(p_cur_msg->transfers))) {

                p_cur_msg->actual_length = 0;

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                /* notify the caller */
                if (p_cur_msg->pfn_complete != NULL) {
                    p_cur_msg->pfn_complete(p_cur_msg->p_arg);
                }

                /* Ƭѡ�ر� */
                __spi_cs_off(p_dev, p_dev->p_cur_spi_dev);

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

                /* ��Ϊ����ģʽ�ҽ��ջ���rx_buf��Ϊ�յ�ʱ�� */
                if ((p_dev->p_cur_spi_dev->mode & AM_SPI_3WIRE) &&
                    (p_dev->p_cur_trans->p_rxbuf)) {

                    /* ��MOSI��Ϊ���븡�� */
                    am_gpio_pin_cfg(p_dev->p_devinfo->mosi_pin, AM_GPIO_INPUT | AM_GPIO_FLOAT);
                }

                /* CSѡͨ */
                __spi_cs_on(p_dev, p_dev->p_cur_spi_dev);

                /* ��һ״̬��ʹ���жϷ�ʽ�������� */
                __SPI_NEXT_STATE(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);
            }
            break;
        }

        case __SPI_ST_M_SEND_DATA:    /**< \brief �������� */
        {
            am_spi_transfer_t *p_cur_trans = p_dev->p_cur_trans;

            if (event != __SPI_EVT_M_SEND_DATA) {
                return -AM_EINVAL;  /**< \brief ��������״̬�ȴ�����Ϣ�����Ƿ������� */
            }

            /* û�и�����Ҫ���͵������� */
            if (p_dev->data_ptr >= p_cur_trans->nbytes) {

                 /* �ر��жϵȴ����;��� */
                 amhw_hc32f460_spi_all_int_enable(p_hw_spi, AM_FALSE);

                 /* �ص����俪ʼ״̬ */
                 __SPI_NEXT_STATE(__SPI_ST_TRANS_START, __SPI_EVT_TRANS_LAUNCH);

                 break;
            } else {
                if (amhw_hc32f460_spi_flag_check (
                    p_hw_spi,
                    AMHW_HC32F460_SPI_STATUS_TXBUFFER_EMPTY) ==
                    AM_TRUE) {

                    /* ��ӻ�д���� */
                    __spi_write_data(p_dev);

                    __SPI_NEXT_STATE(__SPI_ST_M_RECV_DATA, __SPI_EVT_NONE);

                    /* �򿪽����ж� */
                    amhw_hc32f460_spi_rx_int_enable(p_hw_spi, AM_TRUE);
                } else {

                    /* ���жϵȴ����;��� */
                    amhw_hc32f460_spi_tx_int_enable(p_hw_spi, AM_TRUE);
                }
            }
            break;
        }

        case __SPI_ST_M_RECV_DATA:   /**< \brief �������� */
        {
            if (event != __SPI_EVT_M_RECV_DATA) {
                return -AM_EINVAL;   /**< \brief ��������״̬�ȴ�����Ϣ�����ǽ������� */
            }

            /* ��ȡ���� */
            __spi_read_data(p_dev);

            /* û�и����������Ҫ������ */
            if (p_dev->nbytes_to_recv == 0) {

                /* ��Ϊ����ģʽ�ҽ��ջ���rx_buf��Ϊ�յ�ʱ�� */
                if ((p_dev->p_cur_spi_dev->mode & AM_SPI_3WIRE) &&
                    (p_dev->p_cur_trans->p_rxbuf)) {

                    /* �����û�MOSIģʽ */
                    am_gpio_pin_cfg(p_dev->p_devinfo->mosi_pin, p_dev->p_devinfo->flags);
                }

                /* ����ʣ������ */
                __SPI_NEXT_STATE(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);

                /* ���ܷ��ͼ������ж� */
                amhw_hc32f460_spi_tx_int_enable(p_hw_spi, AM_FALSE);
                amhw_hc32f460_spi_rx_int_enable(p_hw_spi, AM_FALSE);

            /* ��Ҫ���ո������� */
            } else {

                /* ���ʲôҲ��Ҫ�� */
            }
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
 * \brief SPI��ʼ��
 */
am_spi_handle_t am_hc32f460_spi_int_init (am_hc32f460_spi_int_dev_t           *p_dev,
                                          const am_hc32f460_spi_int_devinfo_t *p_devinfo)
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
    p_dev->lsbfirst         = AM_FALSE;
    p_dev->busy             = AM_FALSE;
    p_dev->p_cur_msg        = NULL;
    p_dev->p_cur_trans      = NULL;
    p_dev->data_ptr         = 0;
    p_dev->nbytes_to_recv   = 0;
    p_dev->state            = __SPI_ST_IDLE;/* ��ʼ��Ϊ����״̬ */

    am_list_head_init(&(p_dev->msg_list));

    if (__spi_hard_init(p_dev) != AM_OK) {
        return NULL;
    }

    am_int_connect(p_dev->p_devinfo->inum,
                   IRQ137_Handler,
                   (void *)p_dev);

    amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum,
                                         (0x1f << (11 + (p_dev->p_devinfo->dev_id - 1) * 5)));

#if 0
        uint8_t spi_id = p_dev->p_devinfo->dev_id;

        uint32_t enIRQ_rx  = 20;
        uint32_t enIRQ_tx  = 21;
        uint32_t enIRQ_idle  = 22;
        uint32_t enIRQ_error = 23;

        uint32_t INT_SPI_RX    = 299u + 5 * (spi_id - 1);
        uint32_t INT_SPI_TX    = 300u + 5 * (spi_id - 1);
        uint32_t INT_SPI_IDLE    = 301u + 5 * (spi_id - 1);
        uint32_t INT_SPI_ERROR   = 302u + 5 * (spi_id - 1);


    	stc_intc_sel_field_t *stcIntSel;

        stcIntSel = (stc_intc_sel_field_t *)((uint32_t)(0x40051000UL + 0x5c) + (4u * enIRQ_rx));
        stcIntSel->INTSEL = INT_SPI_RX;
        am_int_connect(enIRQ_rx, __spi_irq_handler, p_dev);
        am_int_enable(enIRQ_rx);

        stcIntSel = (stc_intc_sel_field_t *)((uint32_t)(0x40051000UL + 0x5c) + (4u * enIRQ_tx));
        stcIntSel->INTSEL = INT_SPI_TX;
        am_int_connect(enIRQ_tx, __spi_irq_handler, p_dev);
        am_int_enable(enIRQ_tx);

        stcIntSel = (stc_intc_sel_field_t *)((uint32_t)(0x40051000UL + 0x5c) + (4u * enIRQ_idle));
        stcIntSel->INTSEL = INT_SPI_IDLE;
        am_int_connect(enIRQ_idle, NULL, NULL);
        am_int_enable(enIRQ_idle);

        stcIntSel = (stc_intc_sel_field_t *)((uint32_t)(0x40051000UL + 0x5c) + (4u * enIRQ_error));
        stcIntSel->INTSEL = INT_SPI_ERROR;
        am_int_connect(enIRQ_error, NULL, NULL);
        am_int_enable(enIRQ_error);
#endif




    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->spi_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_hc32f460_spi_int_deinit (am_spi_handle_t handle)
{
    am_hc32f460_spi_int_dev_t *p_dev    = (am_hc32f460_spi_int_dev_t *)handle;
    amhw_hc32f460_spi_t       *p_hw_spi = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_serve.p_funcs = NULL;
    p_dev->spi_serve.p_drv   = NULL;

    /* ����SPI */
    amhw_hc32f460_spi_enable(p_hw_spi, AM_FALSE);

    /* �ر�SPI�жϺŲ��Ͽ����� */
    amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum,
                                         (0x1f << (11 + (p_dev->p_devinfo->dev_id - 1) * 5)));

    if (amhw_hc32f460_intc_int_vssel_get(p_dev->p_devinfo->inum) == 0){
        am_int_disable(p_dev->p_devinfo->inum);
    }

    am_int_disconnect(p_dev->p_devinfo->inum,
                      IRQ137_Handler,
                      (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/**
 * \brief SPI�����ٶ�����
 *
 */
am_local
uint32_t __spi_speed_cfg (am_hc32f460_spi_int_dev_t *p_dev,
                          uint32_t                target_speed)
{

    uint32_t clk, best_speed;  /**< \brief ��������ٶ� */
    uint8_t  i = 0;
    amhw_hc32f460_spi_clk_div_t baud_div = AMHW_HC32F460_SPI_CLK_DIV_2;

    amhw_hc32f460_spi_t *p_hw_spi = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    if(target_speed == 0) {
        baud_div = AMHW_HC32F460_SPI_CLK_DIV_2;
    } else {

        clk = am_clk_rate_get(p_dev->p_devinfo->clk_id);

        for(i = 1; i < 8; i++) {

            best_speed = clk >> i;
            if(best_speed <= target_speed) {
                break;
            }
        }
    }

    baud_div = (amhw_hc32f460_spi_clk_div_t)(i - 1);

    amhw_hc32f460_spi_clk_div_set(p_hw_spi, baud_div);

    best_speed = am_clk_rate_get(p_dev->p_devinfo->clk_id) /
                 (0x1ul << (baud_div + 1));

   return best_speed;
}

/* end of file */

