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
 * \brief ADC����A �¼��������� ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_7 �ӵز����½��ء�
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��������Ϊ32��ת����ƽ��ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *       PIOE_5 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_adc_int.c src_hc32f460_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-17  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_adc_int
 * \copydoc demo_hc32f460_hw_adc_int.c
 */

/** [src_hc32f460_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_hc32f460_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_adc_seq_a_event_trigger_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core hw adc seq a event trigger!\r\n");

    /* ����ģ���������� */
    am_gpio_pin_cfg(PIOA_0, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN));

    /* �����ⲿ�������� */
    am_gpio_pin_cfg(PIOB_7,GPIO_AFIO(AMHW_HC32F460_AFIO_ADTRG));

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_ADC1);

    demo_hc32f460_hw_adc_seq_a_event_trigger_entry(HC32F460_ADC1,
                                                   INT_VECTOR_16,
                                                   0,
                                                   3300);
}
/** [src_hc32f460_hw_adc_seqa_event_trigger] */

/* end of file */
