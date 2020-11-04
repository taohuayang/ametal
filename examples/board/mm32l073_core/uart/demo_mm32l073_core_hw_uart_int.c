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
 * \brief UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "HW example---UART test in interrupt mode:"��
 *   2. ����������յ����ַ���
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_hw_uart_int.c src_mm32l073_core_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-01-20  ari, first implementation
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_mm32l073_core_hw_uart_int
 * \copydoc demo_mm32l073_core_hw_uart_int.c
 */ 

/** [src_mm32l073_core_hw_uart_int] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l073_core_entries.h"

static void __mm32l073_uart_pins_intit (void)
{
    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_9, PIOA_9_UART1_TX | PIOA_9_AF_PP);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX| PIOA_10_INPUT_FLOAT);
}

/**
 * \brief �������
 */
void demo_mm32l073_core_hw_uart_int_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core hw uart int!\r\n");

    am_mdelay(100);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    demo_mm32_hw_uart_int_entry(MM32L073_UART1,
                               __mm32l073_uart_pins_intit,
                               am_clk_rate_get(CLK_UART1),
                               MM32L073_UART1_BASE,
                               INUM_UART1);
}
/** [src_mm32l073_core_hw_uart_int] */

/* end of file */
