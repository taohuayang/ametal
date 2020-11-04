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
 * \brief TIM4 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   0. ���ļ�������TIMER4_PWM_U��Ҫ��hwconf_hc32f460_tim4_pwm�������Ӧ
 *   1. PIOC_10(TIMER4_PWM_U)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 *   2. PIOD_8 (TIMER4_PWM_U)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 * \par Դ����
 * \snippet demo_hc32f460_std_tim43_pwm.c src__hc32f460_std_tim4_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_tim43_pwm
 * \copydoc demo_hc32f460_std_tim43_pwm.c
 */

/** [src_hc32f460_std_tim3_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460_tim4_pwm.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_tim43_pwm_entry (void)
{

    AM_DBG_INFO("demo hc32f460_core std tim43 pwm!\r\n");

    demo_std_timer_pwm_entry(am_hc32f460_tim43_pwm_inst_init(), TIMER4_PWM_U);
}
/** [src_hc32f460_std_tim3_pwm] */

/* end of file */
