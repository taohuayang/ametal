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
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ͨ����λ������һ������ MCU ���� 5 ���ַ���
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����յ������ݣ�
 *   2. Ȼ�󴮿ڴ�ӡ�� "DMA transfer done!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32l19x_hw_uart_rx_dma.c src_hc32l19x_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l19x_hw_uart_rx_dma
 * \copydoc demo_hc32l19x_hw_uart_rx_dma.c
 */

/** [src_hc32l19x_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_hc32.h"
#include "demo_hc32_entries.h"
#include "am_hc32l19x_inst_init.h"
#include "demo_aml19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l19x_core_hw_uart_rx_dma_entry (void)
{
    AM_DBG_INFO("demo aml19x_core hw uart rx dma!\r\n");

    /* �ȴ������������ */
    am_mdelay(100);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART1_TXD | PIOA_2_OUT_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_UART1_RXD | PIOA_10_INPUT_FLOAT);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    demo_hc32_hw_uart_rx_dma_entry(HC32_UART1,
                                     am_clk_rate_get(CLK_UART1),
                                     DMA_CHAN_1,
                                     HC32_DMA_SRC_TYPE_UART1_RX);
}

/** [src_hc32l19x_hw_uart_rx_dma] */

/* end of file */
