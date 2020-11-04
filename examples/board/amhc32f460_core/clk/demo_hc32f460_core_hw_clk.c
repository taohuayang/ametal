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
 *   1. ���ڴ�ӡ������Ƶ��
 *   2. PIOA_8�������ϵͳʱ�ӵ�8��Ƶ��Ƶ���źţ���21MHz
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *       PIOE_5 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_clk.c src_hc32f460_hw_clk
 *
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_clk
 * \copydoc demo_hc32f460_hw_clk.c
 */

/** [src_hc32f460_hw_clk] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "hw/amhw_hc32f460_rcc.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_entries.h"

#define __CLK_ID_NAME_LENGTH   20

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_clk_entry (void)
{
    am_clk_id_t clk_id[] = {CLK_HCLK, CLK_PCLK0, CLK_PCLK1, CLK_PCLK2, CLK_PCLK3, CLK_PCLK4,CLK_SYSCLK_DIV1};

    char clk_name[7][__CLK_ID_NAME_LENGTH] = {"CLK_HCLK", "CLK_PCLK0","CLK_PCLK1","CLK_PCLK2", "CLK_PCLK3","CLK_PCLK4", "CLK_SYSCLK_DIV1"};

    AM_DBG_INFO("demo amhc32f460_core hw clk!\r\n");

    /* ����MCO1ʱ��ԴΪϵͳʱ�� */
    amhw_hc32f460_rcc_mco1_src_set(AMHW_HC32F460_RCC_MCO_SRC_SYSCLK);

    /* ����MCO1�����ƵΪ8��Ƶ */
    amhw_hc32f460_rcc_mco1_div_set(AMHW_HC32F460_RCC_MCO_DIV_8);

    /* ʹ��MCO1��� */
    amhw_hc32f460_rcc_mco1_enable();

    /* ��ʼ������ΪMCO1������� */
    am_gpio_pin_cfg(PIOA_8, GPIO_AFIO(AMHW_HC32F460_AFIO_MCLKOUT));

    /* ��ӡʱ��Ƶ�� */
    demo_hc32f460_hw_clk_entry(&clk_id[0], AM_NELEMENTS(clk_id), &clk_name[0][0], __CLK_ID_NAME_LENGTH);
}
/** [src_hc32f460_hw_clk] */

/* end of file */
