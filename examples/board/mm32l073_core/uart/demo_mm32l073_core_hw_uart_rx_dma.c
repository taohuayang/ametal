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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_hw_uart_rx_dma.c src_mm32l073_core_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 17-03-10  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_hw_uart_rx_dma
 * \copydoc demo_mm32l073_core_hw_uart_rx_dma.c
 */

/** [src_mm32l073_core_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_hw_uart_rx_dma_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core hw uart rx dma!\r\n");

    demo_mm32_hw_uart_rx_dma_entry(MM32L073_UART1,
                                  am_clk_rate_get(CLK_UART1),
                                  DMA_CHAN_UART1_RX);
}
/** [src_mm32l073_core_hw_uart_rx_dma] */

/* end of file */
