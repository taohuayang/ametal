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
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ�󴮿ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      uart tx dma test running
 *      uart tx dma test done
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *    3. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_hc32l13x_hw_uart_tx_dma.c src_hc32l13x_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l13x_hw_uart_tx_dma
 * \copydoc demo_hc32l13x_hw_uart_tx_dma.c
 */

/** [src_hc32l13x_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_hc32.h"
#include "demo_hc32_entries.h"
#include "am_hc32l13x_inst_init.h"
#include "demo_aml13x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l13x_core_hw_uart_tx_dma_entry (void)
{
    AM_DBG_INFO("demo aml13x_core hw uart tx dma!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART1_TXD | PIOA_2_OUT_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_UART1_RXD | PIOA_10_INPUT_FLOAT);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    /* �ȴ������������ */
    am_mdelay(100);

    demo_hc32_hw_uart_tx_dma_entry(HC32_UART1,
                                     am_clk_rate_get(CLK_UART1),
                                     DMA_CHAN_1,
                                     HC32_DMA_SRC_TYPE_UART1_TX);
}

/** [src_hc32l13x_hw_uart_tx_dma] */

/* end of file */
