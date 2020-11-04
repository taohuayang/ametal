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
 *   1. 16��˳��ͨ��  + 4������ͨ�� ɨ��ת���ɼ���ѹ
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9�������� PC���ڵ�RXD��
 *       PIOA_10�������� PC���ڵ�TXD��
 *
 * \par Դ����
 * \snippet demo_hc32l13x_hw_multichan_adc.c src_hc32l13x_hw_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l13x_hw_multichan_adc
 * \copydoc demo_hc32l13x_hw_multichan_adc.c
 */

/** [src_hc32l13x_hw_multichan_adc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_hc32_entries.h"
#include "demo_aml13x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l13x_core_hw_multichan_adc_entry (void)
{
    /* 16��˳��ͨ��ADC�ɼ� */ 
    /* 4������ͨ��ADC�ɼ� */
    int adc_chan[20] = {AMHW_HC32_CHAN_AIN0_PA0,
                        AMHW_HC32_CHAN_AIN1_PA1,
                        AMHW_HC32_CHAN_AIN2_PA2,
                        AMHW_HC32_CHAN_AIN3_PA3,
                        AMHW_HC32_CHAN_AIN4_PA4,
                        AMHW_HC32_CHAN_AIN5_PA5,
                        AMHW_HC32_CHAN_AIN6_PA6,
                        AMHW_HC32_CHAN_AIN7_PA7,
                        AMHW_HC32_CHAN_AIN8_PB0,
                        AMHW_HC32_CHAN_AIN9_PB1,
                        AMHW_HC32_CHAN_AIN10_PC0,
                        AMHW_HC32_CHAN_AIN11_PC1,
                        AMHW_HC32_CHAN_AIN12_PC2,
                        AMHW_HC32_CHAN_AIN13_PC3,
                        AMHW_HC32_CHAN_AIN14_PC4,
                        AMHW_HC32_CHAN_AIN15_PC5,
                        AMHW_HC32_CHAN_AIN16_PB2,
                        AMHW_HC32_CHAN_AIN17_PB10,
                        AMHW_HC32_CHAN_AIN18_PB11,
                        AMHW_HC32_CHAN_AIN19_PB12};
    
    AM_DBG_INFO("demo aml13x_core hw multichan adc int!\r\n");

    /* �������� */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_GPIO | PIOA_0_AIN);
    am_gpio_pin_cfg(PIOA_1, PIOA_1_GPIO | PIOA_1_AIN);
    am_gpio_pin_cfg(PIOA_2, PIOA_2_GPIO | PIOA_2_AIN);
    am_gpio_pin_cfg(PIOA_3, PIOA_3_GPIO | PIOA_3_AIN);
    am_gpio_pin_cfg(PIOA_4, PIOA_4_GPIO | PIOA_4_AIN);
    am_gpio_pin_cfg(PIOA_5, PIOA_5_GPIO | PIOA_5_AIN);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_GPIO | PIOA_6_AIN);
    am_gpio_pin_cfg(PIOA_7, PIOA_7_GPIO | PIOA_7_AIN);
    am_gpio_pin_cfg(PIOB_0, PIOB_0_GPIO | PIOB_0_AIN);
    am_gpio_pin_cfg(PIOB_1, PIOB_1_GPIO | PIOB_1_AIN);
    am_gpio_pin_cfg(PIOC_0, PIOC_0_GPIO | PIOC_0_AIN);
    am_gpio_pin_cfg(PIOC_1, PIOC_1_GPIO | PIOC_1_AIN);
    am_gpio_pin_cfg(PIOC_2, PIOC_2_GPIO | PIOC_2_AIN);
    am_gpio_pin_cfg(PIOC_3, PIOC_3_GPIO | PIOC_3_AIN);
    am_gpio_pin_cfg(PIOC_4, PIOC_4_GPIO | PIOC_4_AIN);
    am_gpio_pin_cfg(PIOC_5, PIOC_5_GPIO | PIOC_5_AIN);
    am_gpio_pin_cfg(PIOB_2, PIOB_2_GPIO | PIOB_2_AIN);
    am_gpio_pin_cfg(PIOB_10, PIOB_10_GPIO | PIOB_10_AIN);
    am_gpio_pin_cfg(PIOB_11, PIOB_11_GPIO | PIOB_11_AIN);
    am_gpio_pin_cfg(PIOB_12, PIOB_12_GPIO | PIOB_12_AIN);

    /* ʱ��ʹ��  */
    am_clk_enable(CLK_ADC_BGR);

    demo_hc32_hw_multichan_adc_entry(HC32_ADC,
                                     INUM_ADC_DAC,
                                     2500,
                                     adc_chan,
                                     16,
                                     4);
}
/** [src_hc32l13x_hw_multichan_adc] */

/* end of file */
