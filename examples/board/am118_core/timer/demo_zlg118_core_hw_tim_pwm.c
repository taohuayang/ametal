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
 *   1. PIOA_2(TIM0_CHA) ���  10HZ �� PWM��ռ�ձ�Ϊ 50%��
 *   2. LED0 �� 100ms ������з�ת��
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_tim_pwm.c src_zlg118_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_tim_pwm
 * \copydoc demo_zlg118_hw_tim_pwm.c
 */

/** [src_zlg118_hw_tim_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg118.h"
#include "am_zlg118_clk.h"
#include "am_zlg118_tim_pwm.h"
#include "am_zlg118_inst_init.h"
#include "demo_zlg_entries.h"
#include "demo_am118_core_entries.h"

/**
 * \brief ��ʱ��PWM���HW���������
 */
void demo_zlg118_core_hw_tim_pwm_entry (void)
{

    AM_DBG_INFO("demo am217_core hw tim cmp toggle!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_TIM0_CHA | PIOA_2_OUT_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM012);

    demo_zlg118_hw_tim_pwm_entry((void *)ZLG118_TIM0,
                                 AMHW_ZLG118_TIM_TYPE_TIM0,
                                 ZLG118_TIM_CH0A,
                                 am_clk_rate_get(CLK_TIM012),
                                 AMHW_ZLG118_TIM_CLK_DIV64,
                                 INUM_TIM0);
}
/** [src_zlg118_hw_tim_pwm] */

/* end of file */
