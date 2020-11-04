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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f03x_hw_uart_int.c src_hc32f03x_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hc32f03x_hw_uart_int
 * \copydoc demo_hc32f03x_hw_uart_int.c
 */

/** [src_hc32f03x_hw_uart_int] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_hc32_entries.h"
#include "demo_amf03x_core_entries.h"

static void __hc32f03x_uart_pins_intit (void)
{
    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART1_TXD | PIOA_2_OUT_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_UART1_RXD | PIOA_10_INPUT_FLOAT);

}

/**
 * \brief �������
 */
void demo_hc32f03x_core_hw_uart_int_entry (void)
{
    AM_DBG_INFO("demo amf03x_core hw uart int!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    demo_hc32_hw_uart_int_entry(HC32_UART1,
                                  __hc32f03x_uart_pins_intit,
                                  am_clk_rate_get(CLK_UART1),
                                  HC32_UART1_BASE,
                                  INUM_UART1_3);
}
/** [src_hc32f03x_hw_uart_int] */

/* end of file */
