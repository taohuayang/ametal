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
 *   1. ����16���ⲿ����
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4�������� PC���ڵ�RXD��
 *       PIOE_5�������� PC���ڵ�TXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_multichan_adc.c src_hc32f460_hw_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-22  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_multichan_adc
 * \copydoc demo_hc32f460_hw_multichan_adc.c
 */

/** [src_hc32f460_hw_multichan_adc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_hc32f460_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_multichan_seq_adc_entry (void)
{
	uint8_t i = 0;

    /* 16��ͨ��ADC�ɼ� */
    amhw_adc_chmux_t adc_chan[] = {
                                      {0,  PIOA_0 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN0},
                                      {1,  PIOA_1 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN1},
                                      {2,  PIOA_2 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN2},
                                      {3,  PIOA_3 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN3},
                                      {4,  PIOA_4 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN4},
                                      {5,  PIOA_5 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN5},
                                      {6,  PIOA_6 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN6},
                                      {7,  PIOA_7 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN7},
                                      {8,  PIOB_0 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN8},
                                      {9,  PIOB_1 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN9},
                                      {10, PIOC_0 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN10},
                                      {11, PIOC_1 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN11},
                                      {12, PIOC_2 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN12},
                                      {13, PIOC_3 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN13},
                                      {14, PIOC_4 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN14},
                                      {15, PIOC_5 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN15}
                                  };
    
    AM_DBG_INFO("demo hc32f460_core hw multichan seq adc int !\r\n");

    /* �������� */
    for(i = 0; i < sizeof(adc_chan) / sizeof(adc_chan[0]); i++) {
        am_gpio_pin_cfg(adc_chan[i].pin, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN));
    }

    /* ʱ��ʹ��  */
    am_clk_enable(CLK_ADC1);

    demo_hc32f460_hw_multichan_seq_adc_entry(HC32F460_ADC1,
                                             INT_VECTOR_16,
                                             3300,
                                             adc_chan,
                                             sizeof(adc_chan) / sizeof(adc_chan[0]));
}
/** [src_hc32f460_hw_multichan_seq_adc] */

/* end of file */
