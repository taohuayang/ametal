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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_3 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_aml165_core_hw_uart_int.c src_aml165_core_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-01-20  ari, first implementation
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_aml165_core_hw_uart_int
 * \copydoc demo_aml165_core_hw_uart_int.c
 */ 

/** [src_aml165_core_hw_uart_int] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "demo_zlg_entries.h"
#include "demo_aml165_core_entries.h"

static void __zlg165_uart_pins_intit (void)
{
    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOB_3, PIOB_3_UART1_TX | PIOB_3_AF_PP);
    am_gpio_pin_cfg(PIOB_4, PIOB_4_UART1_RX | PIOB_4_INPUT_FLOAT);
}

/**
 * \brief �������
 */
void demo_aml165_core_hw_uart_int_entry (void)
{
    AM_DBG_INFO("demo aml165_core hw uart int!\r\n");

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    demo_zlg_hw_uart_int_entry(ZML165_UART1, 
                               __zlg165_uart_pins_intit, 
                               am_clk_rate_get(CLK_UART1), 
                               ZML165_UART1_BASE, 
                               INUM_UART1);
}
/** [src_aml165_core_hw_uart_int] */

/* end of file */
