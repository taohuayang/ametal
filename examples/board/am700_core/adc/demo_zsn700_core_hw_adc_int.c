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
 * \snippet demo_zsn700_hw_adc_int.c src_zsn700_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_adc_int
 * \copydoc demo_zsn700_hw_adc_int.c
 */

/** [src_zsn700_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zsn700.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_zlg_entries.h"
#include "demo_am700_core_entries.h"

/**
 * \brief �������
 */
void demo_zsn700_core_hw_adc_int_entry (void)
{
    AM_DBG_INFO("demo am700_core hw adc int!\r\n");

    /* �������� */
    am_gpio_pin_cfg(PIOA_3, PIOA_3_GPIO | PIOA_3_AIN);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_ADC_BGR);

    demo_zsn700_hw_adc_int_entry(ZSN700_ADC,
                                 INUM_ADC_DAC,
                                 AMHW_ZSN700_CHAN_AIN3_PA3,
                                 3300);
}
/** [src_zsn700_hw_adc_int] */

/* end of file */
