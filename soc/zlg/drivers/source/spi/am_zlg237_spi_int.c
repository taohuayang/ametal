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
 * - 1.00 19-07-19  ari, first implementation
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include "am_zlg237_spi_int.h"
#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_clk.h"
#include "hw/amhw_zlg237_spi.h"

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

am_local void __spi_cs_on  (am_zlg237_spi_int_dev_t *p_this,
                            am_spi_device_t         *p_dev);
am_local void __spi_cs_off (am_zlg237_spi_int_dev_t *p_this,
                            am_spi_device_t         *p_dev);

am_local void __spi_write_data (am_zlg237_spi_int_dev_t *p_dev);
am_local void __spi_read_data (am_zlg237_spi_int_dev_t *p_dev);

am_local void __spi_irq_handler (void *p_arg);
am_local int  __spi_hard_init (am_zlg237_spi_int_dev_t *p_this);
am_local int  __spi_config (am_zlg237_spi_int_dev_t *p_this);

am_local int  __spi_mst_sm_event (am_zlg237_spi_int_dev_t *p_dev,
                                  uint32_t                 event);
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
#define __SPI_MINSPEED_GET(p_hw_spi) (__SPI_FRQIIN_GET(p_hw_spi) / 256)

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
void __spi_cs_on (am_zlg237_spi_int_dev_t *p_this, am_spi_device_t *p_dev)
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
void __spi_cs_off (am_zlg237_spi_int_dev_t *p_this,
                   am_spi_device_t      *p_dev)
{
    if (p_this->p_tgl_dev == p_dev) {
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 0);
}

/******************************************************************************/

am_local
void __spi_write_data (am_zlg237_spi_int_dev_t *p_dev)
{
    amhw_zlg237_spi_t *p_hw_spi = (amhw_zlg237_spi_t *)(p_dev->p_devinfo->spi_reg_base);
    am_spi_transfer_t *p_trans  = p_dev->p_cur_trans;

    if (p_dev == NULL) {
        return ;
    }

    while(amhw_zlg237_spi_status_flag_check (p_hw_spi, AMHW_ZLG237_SPI_TX_EMPTY_FLAG) == AM_FALSE);

    /* tx_buf ��Ч */
    if (p_trans->p_txbuf != NULL) {
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {

            /** \brief ���������ݵĻ�ַ+ƫ�� */
            uint8_t *ptr = (uint8_t *)(p_trans->p_txbuf) + p_dev->data_ptr;
            amhw_zlg237_spi_tx_put(p_hw_spi, *ptr);

        } else {
            uint32_t *ptr = (uint32_t *)(p_trans->p_txbuf) + p_dev->data_ptr;
            amhw_zlg237_spi_tx_put(p_hw_spi, *ptr);
        }

    /* tx_buf ��Ч */
    } else {

        /* ������������Ч ֱ�ӷ�0 */
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
            amhw_zlg237_spi_tx_put(p_hw_spi, 0x00);
        } else {
            amhw_zlg237_spi_tx_put(p_hw_spi, 0x0000);
        }
    }

    /** \brief ��������ݵ�byte�� */
    p_dev->nbytes_to_recv = __bits_to_bytes(p_dev->p_cur_spi_dev->bits_per_word); //todo
    p_dev->p_cur_msg->actual_length += p_dev->nbytes_to_recv;
}

am_local
void __spi_read_data (am_zlg237_spi_int_dev_t *p_dev)
{
    amhw_zlg237_spi_t *p_hw_spi = (amhw_zlg237_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    am_spi_transfer_t   *p_trans  = p_dev->p_cur_trans;
    uint32_t *p_buf32;
    uint8_t  *p_buf8;

    if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
        p_buf8  = (uint8_t *)p_trans->p_rxbuf + p_dev->data_ptr;
    } else {
        p_buf32 = (uint32_t *)p_trans->p_rxbuf + p_dev->data_ptr;
    }
    if (p_dev == NULL) {
        return ;
    }

    if (amhw_zlg237_spi_status_flag_check (p_hw_spi, AMHW_ZLG237_SPI_RX_NOT_EMPTY_FLAG) == AM_TRUE) {

        /* rx_buf ��Ч */
        if (p_trans->p_rxbuf != NULL && p_dev->nbytes_to_recv) {
            if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
                 *p_buf8 = amhw_zlg237_spi_rx_get(p_hw_spi);
            } else {
                 *p_buf32 = amhw_zlg237_spi_rx_get(p_hw_spi);
            }

        /* rx_buf ��Ч���߲���Ҫ�������� */
        } else {
            if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
                (void)amhw_zlg237_spi_rx_get(p_hw_spi);

            } else {
                (void)amhw_zlg237_spi_rx_get(p_hw_spi);
            }
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
void __spi_msg_in (am_zlg237_spi_int_dev_t *p_dev,
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
struct am_spi_message *__spi_msg_out (am_zlg237_spi_int_dev_t *p_dev)
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
    am_zlg237_spi_int_dev_t *p_this = (am_zlg237_spi_int_dev_t *)p_arg;

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

    /* ���SPI���ʲ��ܳ�����ʱ�ӣ���С����С����ʱ��256��Ƶ */
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
    am_zlg237_spi_int_dev_t  *p_this   = (am_zlg237_spi_int_dev_t *)p_arg;

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
int __spi_hard_init (am_zlg237_spi_int_dev_t *p_this)
{
    amhw_zlg237_spi_t *p_hw_spi = (amhw_zlg237_spi_t *)
                                  (p_this->p_devinfo->spi_reg_base);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* NSS�����������*/
    amhw_zlg237_spi_ssm_enable(p_hw_spi);

    /* �ر�Ӳ��SPI��NSS�������*/
    amhw_zlg237_spi_ssout_disable(p_hw_spi);

    /* ��������£�NSS�ڲ�Ϊ�ߣ��������޹ء��ر�ע�⣬����Ӳ��������������ó�����ģʽ��NSS����Ϊ��*/
    amhw_zlg237_spi_ssi_set(p_hw_spi,AMHW_ZLG237_SPI_SSI_TO_NSS_ENABLE);

    /* ����Ϊ����ģʽ */
    amhw_zlg237_spi_master_salver_set(p_hw_spi, AMHW_ZLG237_SPI_MASTER);

    /* SPIʹ�� */
    amhw_zlg237_spi_enable(p_hw_spi);

    return AM_OK;
}

/**
 * \brief SPI �жϾ������
 */
am_local
void __spi_irq_handler (void *p_arg)
{
    am_zlg237_spi_int_dev_t  *p_dev    = (am_zlg237_spi_int_dev_t *)p_arg;
    amhw_zlg237_spi_t     *p_hw_spi    = (amhw_zlg237_spi_t *)
                                         (p_dev->p_devinfo->spi_reg_base);

    /* �������� */
    if(amhw_zlg237_spi_status_flag_check(
        p_hw_spi, AMHW_ZLG237_SPI_TX_EMPTY_FLAG) == AM_TRUE) {

        __spi_mst_sm_event(p_dev, __SPI_EVT_M_SEND_DATA);
    }

    /* �������� */
    if(amhw_zlg237_spi_status_flag_check(
        p_hw_spi, AMHW_ZLG237_SPI_RX_NOT_EMPTY_FLAG) == AM_TRUE) {

        __spi_mst_sm_event(p_dev, __SPI_EVT_M_RECV_DATA);
    }
}

am_local
int __spi_config (am_zlg237_spi_int_dev_t *p_this)
{
    const am_zlg237_spi_int_devinfo_t *p_devinfo = p_this->p_devinfo;
    amhw_zlg237_spi_t              *p_hw_spi     = (amhw_zlg237_spi_t *)
                                                   (p_devinfo->spi_reg_base);
    am_spi_transfer_t              *p_trans      = p_this->p_cur_trans;

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
         mode_flag |= AMHW_ZLG237_SPI_LSB_FIRST_SEND_LSB;
    }

    amhw_zlg237_spi_disable(p_hw_spi);

    /* �ر�spi����*/
    amhw_zlg237_spi_disable(p_hw_spi);

    /* NSS�����������*/
    amhw_zlg237_spi_ssm_enable(p_hw_spi);

    /* �ر�Ӳ��SPI��NSS�������*/
    amhw_zlg237_spi_ssout_disable(p_hw_spi);

    /* ��������£�NSS�ڲ�Ϊ�ߣ��������޹ء��ر�ע�⣬����Ӳ��������������ó�����ģʽ��NSS����Ϊ��*/
    amhw_zlg237_spi_ssi_set(p_hw_spi,AMHW_ZLG237_SPI_SSI_TO_NSS_ENABLE);

    /* ����Ϊ����ģʽ*/
    amhw_zlg237_spi_master_salver_set(p_hw_spi, AMHW_ZLG237_SPI_MASTER);

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_zlg237_spi_clk_mode_set(p_hw_spi, 0x3 & p_this->p_cur_spi_dev->mode);

    /* ����SPI�������� */
    amhw_zlg237_spi_lsbfirst_set(p_hw_spi, mode_flag);

    /* ����SPI���ݳ��� */
    amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_8BIT);

    /* ����SPI���ݳ��Ⱥ�֡��ʽ */
    if (p_this->p_cur_spi_dev->bits_per_word == 8) {
        amhw_zlg237_spi_lsbfirst_set(p_hw_spi, mode_flag);
        amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_8BIT);
    }
    else if (p_this->p_cur_spi_dev->bits_per_word == 16) {
        amhw_zlg237_spi_lsbfirst_set(p_hw_spi, mode_flag);
        amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_16BIT);
    }
    else if ((p_this->p_cur_spi_dev->bits_per_word >= 1) ||
             (p_this->p_cur_spi_dev->bits_per_word <= 32)) {
        amhw_zlg237_spi_lsbfirst_set(p_hw_spi, mode_flag);
        amhw_zlg237_spi_flex_length_set(p_hw_spi,
                                        p_this->p_cur_spi_dev->bits_per_word);
        amhw_zlg237_spi_flexlength_enable(p_hw_spi);
    }
    else {
        amhw_zlg237_spi_lsbfirst_set(p_hw_spi, mode_flag);
        amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_8BIT);
    }

    /* ����SPI���� */
    amhw_zlg237_spi_baudratefre_set(p_hw_spi, p_this->p_devinfo->baud_div);

    amhw_zlg237_spi_enable(p_hw_spi);

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
    am_zlg237_spi_int_dev_t *p_this = (am_zlg237_spi_int_dev_t *)p_drv;

    int key;

    /* �豸��Ч�Լ�� */
    if ((p_drv              == NULL) ||
        (p_dev              == NULL) ||
        (p_msg              == NULL) ){
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
int __spi_mst_sm_event (am_zlg237_spi_int_dev_t *p_dev, uint32_t event)
{
    amhw_zlg237_spi_t *p_hw_spi = (amhw_zlg237_spi_t *)
                                  (p_dev->p_devinfo->spi_reg_base);

    volatile uint32_t new_event = __SPI_EVT_NONE;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    while (1) {

        if (new_event != __SPI_EVT_NONE) {     /* ������¼��Ƿ������ڲ� */
            event      = new_event;
            new_event  = __SPI_EVT_NONE;
        }

        switch (p_dev->state) {

        case __SPI_ST_IDLE:         /* ���������ڿ���״̬ */
        {
            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;     /* ����״̬�ȴ�����Ϣ�������������� */
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

                /* ���������ж� */
                amhw_zlg237_spi_int_disable(p_hw_spi, AMHW_ZLG237_SPI_INT_ALL);

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
            am_spi_message_t  *p_cur_msg   = p_dev->p_cur_msg;

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
                    am_gpio_pin_cfg(p_dev->p_devinfo->mosi_pin,
                                    AM_GPIO_INPUT | AM_GPIO_FLOAT);
                }

                /* CSѡͨ */
                __spi_cs_on(p_dev, p_dev->p_cur_spi_dev);


                /* CSѡͨ��������Ҫ�ȴ�100ms���ȴ��ӻ�(��Ƭ��)����������
                 * ������ȷ�������ݣ����򲿷����ݻᶪʧ�����ҡ�
                 * �����������ӻ���λ����Ӧ�Ͽ죬�ɿ���ȡ���˴���ʱ��
                 */
                if(p_dev->p_devinfo->cs_mdelay != 0) {
                    am_mdelay(p_dev->p_devinfo->cs_mdelay);
                }

                /* ��һ״̬��ʹ���жϷ�ʽ�������� */
                __SPI_NEXT_STATE(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);
            }
            break;
        }

        case __SPI_ST_M_SEND_DATA:    /* �������� */
        {
            am_spi_transfer_t *p_cur_trans = p_dev->p_cur_trans;

            if (event != __SPI_EVT_M_SEND_DATA) {
                return -AM_EINVAL;  /* ��������״̬�ȴ�����Ϣ�����Ƿ������� */
            }

            /* û�и�����Ҫ���͵������� */
            if (p_dev->data_ptr >= p_cur_trans->nbytes) {

                 /* �ر��жϵȴ����;��� */
                 amhw_zlg237_spi_int_disable(p_hw_spi, AMHW_ZLG237_SPI_INT_ALL);

                 /* �ص����俪ʼ״̬ */
                 __SPI_NEXT_STATE(__SPI_ST_TRANS_START, __SPI_EVT_TRANS_LAUNCH);

                 break;
            } else {
                if (amhw_zlg237_spi_status_flag_check (
                    p_hw_spi, AMHW_ZLG237_SPI_TX_EMPTY_FLAG) == AM_TRUE) {

                    /* ��ӻ�д���� */
                    __spi_write_data(p_dev);

                    __SPI_NEXT_STATE(__SPI_ST_M_RECV_DATA, __SPI_EVT_NONE);

                    /* Enable RX interrupt */
                    amhw_zlg237_spi_int_enable(
                        p_hw_spi,AMHW_ZLG237_SPI_INT_RX_NOT_EMPTY);


                } else {

                    /* ���жϵȴ����;��� */
                    amhw_zlg237_spi_int_enable(p_hw_spi,
                                               AMHW_ZLG237_SPI_INT_TX_EMPTY);
                }
            }
            break;
        }

        case __SPI_ST_M_RECV_DATA:   /* �������� */
        {
            if (event != __SPI_EVT_M_RECV_DATA) {
                return -AM_EINVAL;      /* ��������״̬�ȴ�����Ϣ�����ǽ������� */
            }

            /* ��ȡ���� */
            __spi_read_data(p_dev);

            /* û�и����������Ҫ������ */
            if (p_dev->nbytes_to_recv == 0) {

                /* ��Ϊ����ģʽ�ҽ��ջ���rx_buf��Ϊ�յ�ʱ�� */
                if ((p_dev->p_cur_spi_dev->mode & AM_SPI_3WIRE) &&
                    (p_dev->p_cur_trans->p_rxbuf)) {

                    /* �����û�MOSIģʽ */
                    am_gpio_pin_cfg(p_dev->p_devinfo->mosi_pin,
                                    p_dev->p_devinfo->flags);
                }

                /* ����ʣ������ */
                __SPI_NEXT_STATE(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);

                /* ���ܷ��ͼ������ж� */
                amhw_zlg237_spi_int_disable(p_hw_spi,
                                            AMHW_ZLG237_SPI_INT_TX_EMPTY);
                amhw_zlg237_spi_int_disable(p_hw_spi,
                                            AMHW_ZLG237_SPI_INT_RX_NOT_EMPTY);

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
am_spi_handle_t am_zlg237_spi_int_init (
    am_zlg237_spi_int_dev_t           *p_dev,
    const am_zlg237_spi_int_devinfo_t *p_devinfo)
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

    am_int_connect(p_dev->p_devinfo->inum,
                   __spi_irq_handler,
                   (void *)p_dev);

    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->spi_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_zlg237_spi_int_deinit (am_spi_handle_t handle)
{
    am_zlg237_spi_int_dev_t *p_dev    = (am_zlg237_spi_int_dev_t *)handle;
    amhw_zlg237_spi_t       *p_hw_spi = (amhw_zlg237_spi_t *)
                                        (p_dev->p_devinfo->spi_reg_base);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_serve.p_funcs = NULL;
    p_dev->spi_serve.p_drv   = NULL;

    /* ����SPI */
    amhw_zlg237_spi_disable(p_hw_spi);

    /* �ر�SPI�жϺŲ��Ͽ����� */
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum,
                      __spi_irq_handler,
                      (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}



