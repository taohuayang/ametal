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
 * \brief LPUART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 *
 * - ʵ������
 *   1. ������� "HW example---LPUART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *       PIOB_12 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32l19x_hw_lpuart_polling.c src_hc32l19x_hw_lpuart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-26  zp, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hc32l19x_hw_lpuart_polling
 * \copydoc demo_hc32l19x_hw_lpuart_polling.c
 */

/** [src_hc32l19x_hw_lpuart_polling] */
#include "ametal.h"
#include "am_board.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "demo_hc32_entries.h"
#include "demo_aml19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l19x_core_hw_lpuart_polling_entry (void)
{
    AM_DBG_INFO("demo aml19x_core hw lpuart polling!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOB_11, PIOB_11_LPUART0_RXD | PIOB_11_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_12, PIOB_12_LPUART0_TXD | PIOB_12_OUT_PP );

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_LPUART0);

    demo_hc32_hw_lpuart_polling_entry(HC32_LPUART0,
                                      AMHW_HC32_LPUART_SCLK_SRC_PCLK,
                                      am_clk_rate_get(CLK_LPUART0),
                                      115200);
}
/** [src_hc32l19x_hw_lpuart_polling] */

/* end of file */
