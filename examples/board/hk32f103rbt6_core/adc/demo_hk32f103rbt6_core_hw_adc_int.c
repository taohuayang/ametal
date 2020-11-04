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
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_4 (ADC ͨ�� 4) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9�������� PC���ڵ�RXD��
 *       PIOA_10�������� PC���ڵ�TXD��
 *
 * \par Դ����
 * \snippet demo_hk32f103rbt6_hw_adc_int.c src_hk32f103rbt6_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-28  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_hw_adc_int
 * \copydoc demo_hk32f103rbt6_hw_adc_int.c
 */

/** [src_hk32f103rbt6_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hk32f103rbt6.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_hk32f103rbt6_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_hk32f103rbt6_core_hw_adc_int_entry (void)
{
    AM_DBG_INFO("demo hk32f103rbt6_core hw adc int!\r\n");

    /* ����Ӳ��������ǰ�Ļ������� ���������ţ�ʹ��ʱ�ӵ� */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_AIN);
    am_clk_enable(CLK_ADC1);

    demo_hk32f103rbt6_hw_adc_int_entry((void *)HK32F103RBT6_ADC1,
                                 INUM_ADC1_2,
                                 AMHW_HK32F103RBT6_ADC_CHAN_0,
                                 3300);
}
/** [src_hk32f103rbt6_hw_adc_int] */

/* end of file */
