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
 * \brief MK100 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-20  mxy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_uart_rngbuf.h"
#include "am_zlg116_inst_init.h"
#include "am_hwconf_mk100_uart.h"
#define UART_RX_BUF_SIZE  128  /**< \brief ���ջ��λ�������С��Ӧ��Ϊ2^n  */
#define UART_TX_BUF_SIZE  128  /**< \brief ���ͻ��λ�������С��Ӧ��Ϊ2^n  */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief UART ���ջ��λ�����  */
static uint8_t __uart_rxbuf[UART_RX_BUF_SIZE];

/** \brief UART ���ͻ��λ�����  */
static uint8_t __uart_txbuf[UART_TX_BUF_SIZE];

/** \brief MK100 �豸ʵ�� */
static am_mk100_dev_t __g_mk100_uart_dev ;

/** \brief MK100 �豸��Ϣʵ�� */
static am_mk100_devinfo_t __g_mk100_uart_dev_info = {
    __uart_rxbuf,
    __uart_txbuf,
    UART_RX_BUF_SIZE,
    UART_TX_BUF_SIZE,
};

/** \brief MK100 �豸��ʼ�� */
am_mk100_handle_t am_mk100_uart2_inst_init (void)
{
    uint32_t pam = AM_MK100_DEFAULT_BAUDRATE;
    __g_mk100_uart_dev.uart_handle = am_zlg116_uart2_inst_init();
    am_uart_ioctl(__g_mk100_uart_dev.uart_handle, AM_UART_BAUD_SET, (void *)pam);
    return am_mk100_init(&__g_mk100_uart_dev, &__g_mk100_uart_dev_info, __g_mk100_uart_dev.uart_handle);
}

/** \brief MK100 �豸���ʼ�� */
void am_mk100_uart2_inst_deinit(am_mk100_handle_t handle)
{
    am_zlg116_uart2_inst_deinit(handle->uart_handle);
}
/* end of file */
