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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOC_13 �������� PC ���ڵ� TXD��
 *       PIOH_2 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *    3. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_uart_tx_dma.c src_hc32f460_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-10  cds, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_uart_tx_dma
 * \copydoc demo_hc32f460_hw_uart_tx_dma.c
 */

/** [src_hc32f460_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_entries.h"
#include "am_hc32f460_dma.h"

extern am_hc32f460_dma_dev_t __g_dma1_dev;

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_uart_tx_dma_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core hw uart tx dma!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOC_13, GPIO_AFIO(AMHW_HC32F460_AFIO_USART4_RX));
    am_gpio_pin_cfg(PIOH_2, GPIO_AFIO(AMHW_HC32F460_AFIO_USART4_TX));

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_USART4);
    am_clk_enable(CLK_PTDIS);

    /* �ȴ������������ */
    am_mdelay(100);

    demo_hc32f460_hw_uart_tx_dma_entry(HC32F460_UART4,
                                       am_clk_rate_get(CLK_USART4),
                                       &__g_dma1_dev,
                                       DMA_CHAN_2);
}

/** [src_hc32f460_hw_uart_tx_dma] */

/* end of file */
