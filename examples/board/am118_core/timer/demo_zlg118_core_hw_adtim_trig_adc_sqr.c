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
 * \brief �߼���ʱ����������ADC˳��ɨ��ת�����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1.ADC��10Hz��Ƶ�ʽ���˳��ɨ��ת������ʱ����ʱ100ms����ÿת��һ��LED��תһ�Σ���˸Ƶ��10/2=5Hz��
 *   2.�������ݴ�ӡ��Ƶ����ADCת����ʱ������ͬ�����ڴ�ӡ���Ϊ500ms��
 *
 * \note
 *   1.����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *     PIOA_9 �������� PC ���ڵ� RXD��
 *   2.adcͨ��������sqr_num�����趨��ΧΪ1~16
 *   3.��PCLK16MHz�£���ʱ������ʱ�䣨period_us�����趨��ΧΪ0~262140us��0~262ms֮�䣩���������
 *     ������ʱ��ֵ������Ҫ����demo_zlg118_hw_adtim_trig_adc_sqr.c�ж�ʱ����Ƶϵ�����趨��
 *   4.��ͬ����£�ADC��ת���ٶ����ޣ���Ҫ���Ƕ�ʱ��������ʱ���Ƿ����ADCת��ʱ�䣨���ͨ������Ҫ�ۼ�ת��ʱ�䣩
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_adtim_trig_adc_sqr.c src_zlg118_hw_adtim_trig_adc_sqr
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-11  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_adtim_trig_adc_sqr
 * \copydoc demo_zlg118_hw_adtim_trig_adc_sqr.c
 */

/** [src_zlg118_hw_adtim_trig_adc_sqr] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg118.h"
#include "hw/amhw_zlg118_adtim.h"
#include "hw/amhw_zlg118_adc.h"
#include "am_zlg118_inst_init.h"
#include "demo_zlg_entries.h"
#include "demo_am118_core_entries.h"

/**
 * \brief �������
 */
void demo_zlg118_core_hw_adtim_trig_adc_sqr_entry (void)
{
    /* 16��˳��ͨ��ADC�ɼ� */
    int adc_chan[] = {AMHW_ZLG118_CHAN_AIN0_PA0,
                      AMHW_ZLG118_CHAN_AIN1_PA1,
                      AMHW_ZLG118_CHAN_AIN2_PA2,
                      AMHW_ZLG118_CHAN_AIN3_PA3,
                      AMHW_ZLG118_CHAN_AIN4_PA4,
                      AMHW_ZLG118_CHAN_AIN5_PA5,
                      AMHW_ZLG118_CHAN_AIN6_PA6,
                      AMHW_ZLG118_CHAN_AIN7_PA7,
                      AMHW_ZLG118_CHAN_AIN8_PB0,
                      AMHW_ZLG118_CHAN_AIN9_PB1,
                      AMHW_ZLG118_CHAN_AIN10_PC0,
                      AMHW_ZLG118_CHAN_AIN11_PC1,
                      AMHW_ZLG118_CHAN_AIN12_PC2,
                      AMHW_ZLG118_CHAN_AIN13_PC3,
                      AMHW_ZLG118_CHAN_AIN14_PC4,
                      AMHW_ZLG118_CHAN_AIN15_PC5};
    
    AM_DBG_INFO("demo am118_core hw adtim trig adc sqr!\r\n");

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

    /* ʱ��ʹ��  */
    am_clk_enable(CLK_ADC_BGR);
    am_clk_enable(CLK_TIM456);

    demo_zlg118_hw_adtim_trig_adc_sqr_entry(ZLG118_TIM4,     //�߼���ʱ��4
                                            100000,          //100000us = 100ms
                                            ZLG118_ADC,      //ADC
                                            INUM_ADC_DAC,    //�жϺ�
                                            adc_chan,        //ADCͨ�����
                                            6);              //ʹ�õ�ADCͨ������
}
/** [src_zlg118_hw_adtim_trig_adc_sqr] */

/* end of file */
