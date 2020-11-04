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
 * \brief bootloader �������ݴ����׼�豸ʵ�֣�uart������
 *
 * \internal
 * \par modification history:
 * - 1.00 18-12-11  yrh, first implementation.
 * \endinternal
 */

#ifndef __AM_BOOT_SERIAL_UART_H
#define __AM_BOOT_SERIAL_UART_H

#include "am_boot_serial_byte.h"
#include "am_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief serial���ݲ������豸��uart���� ��
 */
typedef struct am_boot_serial_uart_dev {
    am_boot_serial_byte_serv_t    serial_serv;      /**< \brief ��׼�� �������ݲ��� ����    */
    am_uart_handle_t              uart_handle;      /**< \brief ��׼��uart�������  */
} am_boot_serial_uart_dev_t;

/**
 * \brief serial���ݲ������豸��ʼ����uart���� ��
 */
am_boot_serial_handle_t am_boot_serial_uart_init(am_uart_handle_t uart_handle,
                                                 uint32_t         baund);
/**
 * \brief serial���ݲ������豸���ʼ����uart���� ��
 */
void am_boot_serial_uart_deinit(void);


#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_SERIAL_UART_H */

/* end of file */
