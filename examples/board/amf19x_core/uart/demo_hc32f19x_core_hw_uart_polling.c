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
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 *
 * - ʵ������
 *   1. ������� "HW example---UART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f19x_hw_uart_polling.c src_hc32f19x_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hc32f19x_hw_uart_polling
 * \copydoc demo_hc32f19x_hw_uart_polling.c
 */

/** [src_hc32f19x_hw_uart_polling] */
#include "ametal.h"
#include "am_board.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "demo_hc32_entries.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_hw_uart_polling_entry (void)
{
    AM_DBG_INFO("demo amf19x_core hw uart polling!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART1_TXD | PIOA_2_OUT_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_UART1_RXD | PIOA_10_INPUT_FLOAT);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    demo_hc32_hw_uart_polling_entry(HC32_UART1, am_clk_rate_get(CLK_UART1));
}
/** [src_hc32f19x_hw_uart_polling] */

/* end of file */
