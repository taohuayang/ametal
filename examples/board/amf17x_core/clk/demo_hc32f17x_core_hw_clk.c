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
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ƶ��(HCLK:48MHz, PCLK:24MHz,)
 *   2. PIOA_1�������HCLK��8��Ƶ��Ƶ���źţ���6MHz
 *      PIOA_2�������PCLK��8��Ƶ��Ƶ���źţ���3MHz
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f17x_hw_clk.c src_hc32f17x_hw_clk
 *
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f17x_hw_clk
 * \copydoc demo_hc32f17x_hw_clk.c
 */

/** [src_hc32f17x_hw_clk] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "hw/amhw_hc32_rcc.h"
#include "am_hc32f17x_inst_init.h"
#include "demo_hc32_entries.h"
#include "demo_amf17x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f17x_core_hw_clk_entry (void)
{
    am_clk_id_t clk_id[] = {CLK_HCLK, CLK_PCLK};

    AM_DBG_INFO("demo amf17x_core hw clk!\r\n");

    amhw_hc32_gpio_sup_hclk_div_set(HC32_GPIO0,
                                    AMHW_HC32_GPIO_SUP_CLK_DIV_8);
    amhw_hc32_gpio_sup_hclk_output(HC32_GPIO0);
    am_gpio_pin_cfg(PIOA_1, PIOA_1_HCLK_OUT | PIOA_1_OUT_PP);

    amhw_hc32_gpio_sup_pclk_div_set(HC32_GPIO0,
                                    AMHW_HC32_GPIO_SUP_CLK_DIV_8);
    amhw_hc32_gpio_sup_pclk_output(HC32_GPIO0);
    am_gpio_pin_cfg(PIOA_2, PIOA_2_PCLK_OUT | PIOA_2_OUT_PP);

    demo_hc32_hw_clk_entry(&clk_id[0], AM_NELEMENTS(clk_id));
}
/** [src_hc32f17x_hw_clk] */

/* end of file */
