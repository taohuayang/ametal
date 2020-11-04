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
 * \brief 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-11-12  win, first implementation.
 * \endinternal
 */
 
#ifndef __AM_UARTCMD_SERIAL_UART_H
#define __AM_UARTCMD_SERIAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "am_softimer.h"
#include "am_uart.h"
#include "am_uartcmd_serial.h"
#include "am_uartcmd_flash_define.h"

/**
 * \brief ���ڳ�ʱ��ʱ���ṹ��
 */
typedef struct uartcmd_serial_uart_timer {
    
    /** \brief ��ʱ����ʱ��� */
    am_softimer_t *p_softtimer;
    
    /** \brief ��ʱ������ֵ */
    uint32_t       timeout_ms;
    
} uartcmd_serial_uart_timer_t;

/**
 * \brief UARTCMD �����豸 UART �豸�ڵ����ɺ���
 *
 * \param[in] p_serial      : �����豸�ṹ��ָ��
 * \param[in] p_uart_timer  : ���ڳ�ʱ��ʱ���ṹ��ָ��
 * \param[in] uart_handle   : ���ھ��
 * \param[in] am_softimer_t : �����ʱ���ṹ��ָ��
 * \param[in] timer_ms      : ��ʱ����ʱʱ��,��λ��ms��
 * \param[in] serial_id     : �����豸��ʾ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int uartcmd_serial_uart_mkdev (uartcmd_serial_t            *p_serial,
                               uartcmd_serial_uart_timer_t *p_uart_timer,
                               am_uart_handle_t             uart_handle,
                               am_softimer_t               *p_softtimer,
                               uint32_t                     timeout_ms,
                               uint8_t                      serial_id)
{
    if (p_serial == NULL || p_uart_timer == NULL) {
        return -AM_EINVAL;
    }

    p_uart_timer->p_softtimer = p_softtimer;
    p_uart_timer->timeout_ms  = timeout_ms;

    p_serial->p_serial_handle = uart_handle;
    p_serial->serial_id       = serial_id & UARTCMD_FLASH_COMM_MODE_MASK;
    p_serial->p_arg           = (void *)p_uart_timer;

    return AM_OK;
}

/**
 * \brief �����豸 UART ��ʼ������
 *
 * \param[in] handle   : UARTCMD������
 * \param[in] p_serial : �����豸�ṹ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_serial_uart_init (am_uartcmd_handle_t  handle,
                              uartcmd_serial_t    *p_serial);

/**
 * \brief �����豸 UART �����ʼ������
 *
 * \param[in] p_serial     : �����豸�ṹ��
 * \param[in] uart_handle  : ���ھ��
 * \param[in] timer_handle : ��ʱ�����
 * \param[in] serial_id    : �����豸ID���������ֲ�ͬ���豸
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_serial_uart_deinit (am_uartcmd_handle_t  handle,
                                uartcmd_serial_t    *p_serial);

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_SERIAL_UART_H */

/* end of file */
