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
 *   16��˳��ɨ��ת��ͨ����ʹ��DMA�鴫�䣨16�����ݣ�
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *       PIOE_5 �������� PC ���ڵ� RXD��
 *    2. ADC1֧��16ͨ����ADC2֧��8ͨ�����ڲ�ģ��ͨ�����ƣ���
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_adc_dma.c src_hc32f460_hw_adc_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-22  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_adc_dma
 * \copydoc demo_hc32f460_hw_adc_dma.c
 */

/** [src_hc32f460_hw_adc_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32f460_dma.h"
#include "demo_hc32f460_entries.h"

extern am_hc32f460_dma_dev_t __g_dma1_dev;

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_adc_dma_entry (void)
{     
	uint8_t i = 0;

    /* 16��ͨ��ADC�ɼ� */
    amhw_adc_chmux_t adc_chan[16] = {{0,  PIOA_0 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN0},
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
                                     {15, PIOC_5 , AMHW_HC32F460_ADC_CH_MUX_ADC1_IN15}};
    
    AM_DBG_INFO("demo hc32f460_core hw adc dma!\r\n");

    /* �������� */
    for(i = 0; i < 16; i++) {
        am_gpio_pin_cfg(adc_chan[i].pin, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN));
    }

    /* ʱ��ʹ��  */
    am_clk_enable(CLK_ADC1);
    am_clk_enable(CLK_PTDIS);

    demo_hc32f460_hw_adc_dma_entry(HC32F460_ADC1,
                                   adc_chan,
                                   &__g_dma1_dev,
                                   INT_VECTOR_16,
                                   3300,
                                   DMA_CHAN_1);
}
/** [src_hc32f460_hw_adc_dma] */

/* end of file */
