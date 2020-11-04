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
 *   1. PIOA_0 (ADC ͨ�� 0) ����ģ�����롣
 *   2. PIOA_1 (ADC ͨ�� 1) ����ģ�����롣
 *   3. PIOA_2 (ADC ͨ�� 2) ����ģ�����롣
 *   4. PIOA_3 (ADC ͨ�� 3) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_mm32l373_hw_adc_dma.c src_mm32l373_hw_adc_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-28  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l373_hw_adc_dma
 * \copydoc demo_mm32l373_hw_adc_dma.c
 */

/** [src_mm32l373_hw_adc_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l373.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l373_core_entries.h"

#define  __ADC1_DMA_CHAN1         DMA_CHAN_1 /* ADC1��ӦDMAͨ��1 */
#define  __ADC2_DMA_CHAN2         DMA_CHAN_2 /* ADC2��ӦDMAͨ��2 */

/**
 * \brief �������
 */
void demo_mm32l373_core_hw_adc_dma_entry (void)
{
    AM_DBG_INFO("demo mm32l373_core hw adc dma!\r\n");

    int adc_chan[] = {0, 1, 2, 3};

    /* ����Ӳ��������ǰ�Ļ������� ���������ţ�ʹ��ʱ�ӵ� */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_AIN | PIOA_0_ADC1_IN0); /* ADC1ͨ��0 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_AIN | PIOA_1_ADC1_IN1); /* ADC1ͨ��1 */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_AIN | PIOA_2_ADC1_IN2); /* ADC1ͨ��2 */
    am_gpio_pin_cfg(PIOA_3, PIOA_3_AIN | PIOA_3_ADC1_IN3); /* ADC1ͨ��3 */

    am_clk_enable(CLK_ADC1);

    demo_mm32_hw_adc_dma_entry(MM32L373_ADC1,
                              adc_chan,
                              sizeof(adc_chan)/sizeof(adc_chan[0]),
                              __ADC1_DMA_CHAN1);
}
/** [src_mm32l373_hw_adc_dma] */

/* end of file */
