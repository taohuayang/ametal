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
 * \snippet demo_zlg237_hw_adc_int.c src_zlg237_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-28  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg237_hw_adc_int
 * \copydoc demo_zlg237_hw_adc_int.c
 */

/** [src_zlg237_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg237.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_zlg_entries.h"
#include "demo_am237_core_entries.h"

/**
 * \brief �������
 */
void demo_zlg237_core_hw_adc_injected_int_entry (void)
{
    AM_DBG_INFO("demo am237_core hw adc int!\r\n");

    int adc_chan[] = {0, 1, 2, 3};

    /* ����Ӳ��������ǰ�Ļ������� ���������ţ�ʹ��ʱ�ӵ� */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_AIN | PIOA_0_ADC12_IN0); /* ADC1ͨ��0 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_AIN | PIOA_1_ADC12_IN1); /* ADC1ͨ��1 */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_AIN | PIOA_2_ADC12_IN2); /* ADC1ͨ��2 */
    am_gpio_pin_cfg(PIOA_3, PIOA_3_AIN | PIOA_3_ADC12_IN3); /* ADC1ͨ��3 */

    am_clk_enable(CLK_ADC1);

    demo_zlg237_hw_adc_injected_int_entry((void *)ZLG237_ADC1,
                                          INUM_ADC1_2,
                                          3300,
                                          adc_chan,
                                          sizeof(adc_chan)/sizeof(adc_chan[0]));
}
/** [src_zlg237_hw_adc_int] */

/* end of file */
