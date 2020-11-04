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
 *   1. PIOA_3����ģ�����롣
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
 * \snippet demo_hc32f07x_hw_adc_int.c src_hc32f07x_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f07x_hw_adc_int
 * \copydoc demo_hc32f07x_hw_adc_int.c
 */

/** [src_hc32f07x_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_hc32_entries.h"
#include "demo_amf07x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f07x_core_hw_adc_int_entry (void)
{
    AM_DBG_INFO("demo amf07x_core hw adc int!\r\n");

    /* �������� */
    am_gpio_pin_cfg(PIOC_5, PIOC_5_GPIO | PIOC_5_AIN);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_ADC_BGR);

    demo_hc32_hw_adc_int_entry(HC32_ADC,
                                 INUM_ADC_DAC,
                                 AMHW_HC32_CHAN_AIN15_PC5,
                                 3300);
}
/** [src_hc32f07x_hw_adc_int] */

/* end of file */
