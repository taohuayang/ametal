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
 *    1. �� PIOC_13 �������� PC ���ڵ� TXD��PIOH_2 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_uart_polling.c src_hc32f460_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-11  cds, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hc32f460_hw_uart_polling
 * \copydoc demo_hc32f460_hw_uart_polling.c
 */

/** [src_hc32f460_hw_uart_polling] */
#include "ametal.h"
#include "am_board.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "demo_hc32f460_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_uart_polling_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core hw uart polling!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOC_13, GPIO_AFIO(AMHW_HC32F460_AFIO_USART4_RX));
    am_gpio_pin_cfg(PIOH_2, GPIO_AFIO(AMHW_HC32F460_AFIO_USART4_TX));

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_USART4);

    demo_hc32f460_hw_uart_polling_entry(HC32F460_UART4, am_clk_rate_get(CLK_USART4));
}
/** [src_hc32f460_hw_uart_polling] */

/* end of file */
