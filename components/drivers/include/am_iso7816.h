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
 * \brief ISO7816Э�����ͷ�ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-05-17  htf, first implementation.
 * \endinternal
 */

#ifndef __AM_ISO7816_H
#define __AM_ISO7816_H

#include "ametal.h"
#include "am_pwm.h"
#include "am_uart.h"
#include "am_gpio.h"
#include "am_timer.h"
#include "am_delay.h"
#include "am_softimer.h"

#define AM_ISO7816_TOUCH_CARD_TYPE_T0    0       /**< \brief T=0 �Ӵ�ʽ��*/
#define AM_ISO7816_TOUCH_CARD_TYPE_T1    1       /**< \brief T=1 �Ӵ�ʽ��*/

/**
 * \brief ISO7816-3 �豸��Ϣ�ṹ��
 */
typedef struct am_iso7816_devinfo {
    uint8_t          vicc_pin;          /**< \brief �Ӵ�ʽ���ĵ�Դ���� */
    uint8_t          rst_pin;           /**< \brief �Ӵ�ʽ���ĸ�λ���� */
    uint8_t          pwm_pin;           /**< \brief �Ӵ�ʽ����ʱ���ź����� */
    uint32_t         pwm_mode;          /**< \brief ʱ���ź�����PWMģʽ */
    uint8_t          pwm_chan;          /**< \brief PWMͨ���ţ����ڽӴ�ʽ������ʱ��Ƶ��*/
    uint8_t          io_pin;            /**< \brief �Ӵ�ʽ��������/������� */
    uint32_t         rx_mode;           /**< \brief ����/�����������ģʽ */
    am_bool_t        is_high;           /**< \brief �Ӵ�ʽ����Դ�������Ÿ���Ч */
    uint32_t         clk;               /**< \brief �Ӵ�ʽ���ʱ��ѡ�� */
} am_iso7816_devinfo_t;

/**
 * \brief ISO7816-3 ���������ṹ��
 */
struct am_iso7816_drv_funcs {

    /** ISO7816-3 �Ӵ�ʽIC���临λ */
    int (*pfn_ic_cold_reset)(void        *p_drv,
                             uint8_t     *p_atr,
                             uint32_t    *p_nbytes,
                             am_bool_t    pps);

    /** ISO7816-3 �Ӵ�ʽIC���ȸ�λ */
    int (*pfn_ic_warm_reset)(void     *p_drv,
                             uint8_t  *p_atr,
                             uint32_t *p_nbytes);

    /** \brief IOS7816-3 �Ӵ�ʽIC������ */
    int (*pfn_ic_transfer)(void       *p_drv,
                           uint8_t     type,
                           const void *p_tx_buf,
                           uint32_t    tx_nbytes,
                           void       *p_rx_buf,
                           uint32_t   *p_rx_nbytes);

    /** \brief IOS7816-3 �Ӵ�ʽIC��ͣ�� */
    int (*pfn_ic_deactivate)(void *p_drv);
};

/**
 * \brief ISO7816-3 ����ṹ��
 */
typedef struct am_iso7816_serv {

    /** \brief ISO7816-3 ���������ṹ��ָ�� */
    struct am_iso7816_drv_funcs *p_funcs;

    /** \brief �������������ĵ�һ������ */
    void                        *p_drv;
} am_iso7816_serv_t;

/** \brief ����ISO7816-3����������� */
typedef am_iso7816_serv_t *am_iso7816_handle_t;

/**
 * \brief ISO7816-3 �豸�ṹ��
 */
typedef struct am_iso7816_dev{
    am_iso7816_serv_t           serv;               /**< \brief ISO7816����ṹ�� */
    uint8_t                     status;             /**< \brief ��ǰ�豸״̬ */

    /* ע�����²����ڽ��ո�λ��Ϣ֮�����ݸ�λ��Ϣ���ݽ��иı� */
    volatile uint32_t           etu;                /**< \brief ����λ���ֱ�׼ʱ�� */
    volatile uint8_t            msb_first;          /**< \brief ��/����Լ�� */
    volatile uint8_t            t_type;             /**< \brief Э������(T = 0 �� T = 1) */
    volatile uint8_t            fd;                 /**< \brief ʱ��Ƶ�ʱ任���Ӻͱ����ʵ������� */
    volatile uint8_t            extra_time;         /**< \brief �ֽڼ���Ᵽ��ʱ�� */
    volatile uint8_t            wi;                 /**< \brief �ַ���ʱ���� 960 * F / f * WI(T = 0) */
    volatile uint8_t            ifsc;               /**< \brief ��������Ϣ����(T = 1) */
    volatile uint8_t            b_cwi;              /**< \brief �ַ��ȴ�ʱ�����ȴ�ʱ��(T = 1) */
    volatile uint8_t            tc3;                /**< \brief ֡βУ��ģʽ */
    volatile am_bool_t          auto_pps;           /**< \brief �Ƿ��Զ�����Э�� */
    volatile uint32_t           clkout;             /**< \brief ���Ƶ�� */

    am_bool_t                   is_timeout;         /**< \brief ���ճ�ʱ��־ */
    am_softimer_t               timeout_timer;      /**< \brief ���ճ�ʱ�����ʱ�� */

    am_pwm_handle_t             pwm_handle;         /**< \brief ʱ�������� */
    am_uart_handle_t            uart_handle;        /**< \brief ���ھ��(�첽��˫��ģʽ) */
    const am_iso7816_devinfo_t *p_info;             /**< \brief �����豸��Ϣ */
} am_iso7816_dev_t;

/**
 * \brief ISO7816 �Ӵ�ʽ��Э���ʼ��
 *
 * \param[in] p_dev         : �Ӵ�ʽIC�������ṹ��ָ��
 * \param[in] uart_handle   : ���ڷ�����
 * \param[in] p_info        : �豸��Ϣ�ṹ��ָ��
 *
 * \retval ISO7816 ���
 */
am_iso7816_handle_t am_iso7816_init (am_iso7816_dev_t              *p_dev,
                                     am_uart_handle_t               uart_handle,
                                     am_pwm_handle_t                pwm_handle,
                                     const am_iso7816_devinfo_t    *p_info);

/**
 * \brief  ISO7816 �Ӵ�ʽ���临λ
 *
 * \param[in] handle    : ISO7816  ���
 * \param[in] fd        : ��ʼ����ʱ��Ƶ�ʱ任���Ӻͱ����ʵ�������  Ĭ��0x01
 * \param[in] p_atr     : ��λ��Ϣ����(��SW1 SW2)
 * \param[in] p_nbytes  : ��λ��Ϣ���ݳ���
 *
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_iso7816_cold_reset (am_iso7816_handle_t  handle,
                           uint8_t             *p_atr,
                           uint32_t            *p_nbytes,
                           am_bool_t            pps)
{
    return handle->p_funcs->pfn_ic_cold_reset(handle->p_drv,
                                              p_atr,
                                              p_nbytes,
                                              pps);
}

/**
 * \brief  ISO7816 �Ӵ�ʽ���ȸ�λ
 *
 * \param[in] handle    : ISO7816  ���
 * \param[in] fd        : ��ʼ����ʱ��Ƶ�ʱ任���Ӻͱ����ʵ�������  Ĭ��0x01
 * \param[in] p_atr     : ��λ��Ϣ����(��SW1 SW2)
 * \param[in] p_nbytes  : ��λ��Ϣ���ݳ���
 *
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_iso7816_warm_reset (am_iso7816_handle_t  handle,
                           uint8_t             *p_atr,
                           uint32_t            *p_nbytes)
{
    return handle->p_funcs->pfn_ic_warm_reset(handle->p_drv,
                                              p_atr,
                                              p_nbytes);
}

/**
 * \brief  ISO7816 �Ӵ�ʽ�������
 *
 * \param[in] handle      : ISO7816  ���
 * \param[in] type        : ISO7816  Э�鿨����  ��ѡ����    AM_ISO7816_TOUCH_CARD_TYPE_T0
 *                                                 AM_ISO7816_TOUCH_CARD_TYPE_T1
 *                          Ŀǰֻ���Թ�T=0�ĽӴ�ʽ��Ƭ
 * \param[in] p_tx_buf    : �������������
 * \param[in] tx_nbytes   : �����������ֽ���
 * \param[in] p_rx_buf    : �������ݻ�����
 * \param[in] p_rx_nbytes : ���յ������ݳ���
 *
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_iso7816_transfer (am_iso7816_handle_t    handle,
                         uint8_t                type,
                         uint8_t               *p_tx_buf,
                         uint32_t               tx_nbytes,
                         uint8_t               *p_rx_buf,
                         uint32_t              *p_rx_nbytes)
{
    return handle->p_funcs->pfn_ic_transfer(handle,
                                            type,
                                            p_tx_buf,
                                            tx_nbytes,
                                            p_rx_buf,
                                            p_rx_nbytes);
}

/**
 * \brief  ISO7816 �Ӵ�ʽ��ͣ��
 *
 * \param[in] handle : ISO7816  ���
 *
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_iso7816_ic_deactivate (am_iso7816_handle_t handle)
{
    return handle->p_funcs->pfn_ic_deactivate(handle);
}

#endif  /* __AM_ISO7816_H */

/* end of file */

