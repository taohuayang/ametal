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
 * \brief ADC1 �� ADC2ͬʱ�ɼ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 *        ADC1 ʹ�� ������ DMAͨ��, ADC2 ʹ�� ע���� �ж�ͨ��
 *
 * - �������裺
 *   1. PIOA_2 (ADC ͨ�� 2) ����ģ�����롣
 *   2. PIOA_3 (ADC ͨ�� 3) ����ģ�����롣
 *   3. PIOA_4 (ADC ͨ�� 4) ����ģ�����롣
 *   4. PIOA_5 (ADC ͨ�� 5) ����ģ�����롣
 *   5. PIOA_6 (ADC ͨ�� 6) ����ģ�����롣
 *   6. PIOA_7 (ADC ͨ�� 7) ����ģ�����롣
 *   7. PIOC_1 (ADC ͨ�� 11) ����ģ�����롣
 *   8. PIOC_2 (ADC ͨ�� 12) ����ģ�����롣
 *   9. PIOC_3 (ADC ͨ�� 13) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ʹ�� ADCģ�鹦�ܣ����뱣֤ ADCģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9�������� PC���ڵ�RXD��
 *       PIOA_10�������� PC���ڵ�TXD��
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_core_hw_adc_dma_int.c src_stm32f103rbt6_core_hw_adc_dma_int
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-28  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_core_hw_adc_dma_int
 * \copydoc demo_stm32f103rbt6_core_hw_adc_dma_int.c
 */

/** [src_stm32f103rbt6_core_hw_adc_dma_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_stm32f103rbt6.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_stm32f103rbt6_entries.h"
#include "demo_stm32f103rbt6_core_entries.h"

#define  __ADC1_DMA_CHAN1         DMA_CHAN_1 /* ADC1��ӦDMAͨ��1 */
                                             /* ��ADC1�ܷ���DMA���� */

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_hw_adc_dma_double_entry (void)
{
    AM_DBG_INFO("demo stm32f103rbt6_core hw adc dma!\r\n");

    int adc1_chan[] = {2, 3, 4, 5, 6, 7};
    int adc2_chan[] = {11, 12, 13};

    /* ����Ӳ��������ǰ�Ļ������� ���������ţ�ʹ��ʱ�ӵ� */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_AIN | PIOA_2_ADC12_IN2); /* ADC1ͨ��2 */
    am_gpio_pin_cfg(PIOA_3, PIOA_3_AIN | PIOA_3_ADC12_IN3); /* ADC1ͨ��3 */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AIN | PIOA_4_ADC12_IN4); /* ADC1ͨ��0 */
    am_gpio_pin_cfg(PIOA_5, PIOA_5_AIN | PIOA_5_ADC12_IN5); /* ADC1ͨ��1 */
    am_gpio_pin_cfg(PIOA_6, PIOA_6_AIN | PIOA_6_ADC12_IN6); /* ADC1ͨ��2 */
    am_gpio_pin_cfg(PIOA_7, PIOA_7_AIN | PIOA_7_ADC12_IN7); /* ADC1ͨ��3 */


    am_gpio_pin_cfg(PIOC_1, PIOC_1_AIN | PIOC_1_ADC12_IN11); /* ADC2ͨ��11 */
    am_gpio_pin_cfg(PIOC_2, PIOC_2_AIN | PIOC_2_ADC12_IN12); /* ADC2ͨ��12 */
    am_gpio_pin_cfg(PIOC_3, PIOC_3_AIN | PIOC_3_ADC12_IN13); /* ADC2ͨ��13 */

    am_clk_enable(CLK_ADC1);
    am_clk_enable(CLK_ADC2);

    demo_stm32f103rbt6_hw_adc_dma_double_entry((void *)STM32F103RBT6_ADC1,
                                        adc1_chan,
                                        sizeof(adc1_chan)/sizeof(adc1_chan[0]),
                                        __ADC1_DMA_CHAN1,
                                        (void *)STM32F103RBT6_ADC2,
                                        adc2_chan,
                                        sizeof(adc2_chan)/sizeof(adc2_chan[0]));
}
/** [src_stm32f103rbt6_core_hw_adc_dma_int] */

/* end of file */
