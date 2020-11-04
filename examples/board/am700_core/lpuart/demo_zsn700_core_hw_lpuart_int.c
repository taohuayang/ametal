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
 * \brief LPUART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "HW example---LPUART test in interrupt mode:"��
 *   2. ����������յ����ַ���
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *       PIOB_12 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_lpuart_int.c src_zsn700_hw_lpuart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-26  zp, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zsn700_hw_lpuart_int
 * \copydoc demo_zsn700_hw_lpuart_int.c
 */

/** [src_zsn700_hw_lpuart_int] */
#include "ametal.h"
#include "am_zsn700.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_zlg_entries.h"
#include "demo_am700_core_entries.h"

static void __zsn700_lpuart_pins_intit (void)
{
    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOB_11, PIOB_11_LPUART0_RXD | PIOB_11_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_12, PIOB_12_LPUART0_TXD | PIOB_12_OUT_PP );
}

/**
 * \brief �������
 */
void demo_zsn700_core_hw_lpuart_int_entry (void)
{
    AM_DBG_INFO("demo am700_core hw lpuart int!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_LPUART0);

    demo_zsn700_hw_lpuart_int_entry(ZSN700_LPUART0,
                                    __zsn700_lpuart_pins_intit,
                                    AMHW_ZSN700_LPUART_SCLK_SRC_PCLK,
                                    16000000,
                                    115200,
                                    ZSN700_LPUART0_BASE,
                                    INUM_LPUART0);
}
/** [src_zsn700_hw_lpuart_int] */

/* end of file */
