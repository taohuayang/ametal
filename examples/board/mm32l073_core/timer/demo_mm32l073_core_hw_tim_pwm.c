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
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOA_0(TIM2_CH1) ��� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_hw_tim_pwm.c src_mm32l073_core_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_mm32l073_core_hw_tim_pwm
 * \copydoc demo_mm32l073_core_hw_tim_pwm.c
 */

/** [src_mm32l073_core_hw_tim_pwm] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "am_mm32l073_clk.h"
#include "am_mm32_tim_pwm.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_hw_tim_pwm_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core hw tim pwm!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_AF_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λ��ʱ�� */
    am_mm32l073_clk_reset(CLK_TIM2);

    demo_mm32_hw_tim_pwm_entry(MM32L073_TIM2,
                                 AMHW_MM32_TIM_TYPE1,
                                 AM_MM32_TIM_PWM_CH1,
                                 am_clk_rate_get(CLK_TIM2),
                                 INUM_TIM2);
}
/** [src_mm32l073_core_hw_tim_pwm] */

/* end of file */
