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
 * \brief �͹���ģʽ�����˯�ߣ��͹��Ĵ��ڻ������̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1.���ڷ���������ʾ�������˯��ģʽ��
 *   2.PC��ͨ�����ڷ������ݣ�MCU�յ����ݻ��ѣ��˳��жϺ�����������˯��ģʽ��
 *
 * \note
 *   1.�� PIOB_11 �������� PC ���ڵ� TXD��PIOB_12 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l19x_lpuart_wake_up.c src_hc32l19x_lpuart_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 20-07-15  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l19x_lpuart_wake_up
 * \copydoc demo_hc32l19x_lpuart_wake_up.c
 */

/** [src_hc32l19x_lpuart_wake_up] */
#include "ametal.h"
#include "am_board.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hc32_pin.h"
#include "am_hc32l19x_inst_init.h"
#include "demo_aml19x_core_entries.h"
#include "am_hc32_lpmode.h"

/* �͹������� */
static void lowerpower_cfg (void)
{
    int i = 0;

    amhw_hc32_rcc_set_start(0x5A5A);
    amhw_hc32_rcc_set_start(0xA5A5);
    amhw_hc32_rcc_swdio_gpio(); 

    /* ����û���õ������� */
    for (i = PIOA_0; i < PIN_NUM; i++) {

        am_gpio_pin_cfg(i, AM_GPIO_INPUT | AM_GPIO_PULLDOWN);
    }

    /* �͹���ģʽ��ʼ�� */
    am_hc32_lpmode_init();
}

/* �͹��Ĵ��ڽ��պ��� */
static void lpuart_recv_handler (void *p_arg, char  ch)
{
    am_uart_handle_t handle = (am_uart_handle_t)(p_arg);

    am_uart_poll_send(handle, (const uint8_t*)&ch, 1);
}

/**
 * \brief �������
 */
void demo_hc32l19x_lpuart_wake_up_entry (void)
{
    const uint8_t tx_string[] = "deepsleep mode lpuart wake up test!\r\n";

    am_uart_handle_t handle;

    /* ��ֹ����͹����޷���¼ */
    am_mdelay(3000);

    lowerpower_cfg();

    handle = am_hc32_lpuart0_inst_init();
    
    am_uart_ioctl(handle, AM_UART_MODE_SET, (void*)AM_UART_MODE_INT);
    am_uart_callback_set(handle,
                         AM_UART_CALLBACK_RXCHAR_PUT,
                         lpuart_recv_handler,
                         handle);

    am_uart_poll_send(handle, tx_string, sizeof(tx_string) - 1);
    am_mdelay(100);

    /* �������˯��ģʽ */
    am_hc32_lpmode_deepsleep(AM_TRUE);

    while (1) {

    }
}
/** [src_hc32l19x_lpuart_wake_up] */

/* end of file */
