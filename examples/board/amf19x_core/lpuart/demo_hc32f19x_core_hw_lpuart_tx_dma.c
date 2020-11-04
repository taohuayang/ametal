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
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ�󴮿ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      lpuart tx dma test running
 *      lpuart tx dma test done
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *       PIOB_12 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *    3. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_hc32f19x_hw_lpuart_tx_dma.c src_hc32f19x_hw_lpuart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-26  zp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f19x_hw_lpuart_tx_dma
 * \copydoc demo_hc32f19x_hw_lpuart_tx_dma.c
 */

/** [src_hc32f19x_hw_lpuart_tx_dma] */
#include "ametal.h"
#include "am_hc32.h"
#include "demo_hc32_entries.h"
#include "am_hc32f19x_inst_init.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_hw_lpuart_tx_dma_entry (void)
{
    AM_DBG_INFO("demo amf19x_core hw lpuart tx dma!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOB_11, PIOB_11_LPUART0_RXD | PIOB_11_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_12, PIOB_12_LPUART0_TXD | PIOB_12_OUT_PP );

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_LPUART0);

    /* �ȴ������������ */
    am_mdelay(100);

    demo_hc32_hw_lpuart_tx_dma_entry(HC32_LPUART0,
                                     AMHW_HC32_LPUART_SCLK_SRC_PCLK,
                                     am_clk_rate_get(CLK_LPUART0),
                                     115200,
                                     DMA_CHAN_1,
                                     HC32_DMA_SRC_TYPE_LPUART0_TX);
}

/** [src_hc32f19x_hw_lpuart_tx_dma] */

/* end of file */
