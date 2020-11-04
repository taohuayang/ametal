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
 * \brief TIM1 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOA_2(TIM0_CH0)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_hc32f19x_std_tim0_pwm.c src_hc32f19x_std_tim0_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f19x_std_tim0_pwm
 * \copydoc demo_hc32f19x_std_tim0_pwm.c
 */

/** [src_hc32f19x_std_tim0_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32_tim_pwm.h"
#include "am_hc32f19x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_std_tim0_pwm_entry (void)
{

    AM_DBG_INFO("demo amf19x_core std tim0 pwm!\r\n");

    demo_std_timer_pwm_entry(am_hc32_tim0_pwm_inst_init(), AM_HC32_TIM_PWM_CH0A);
}
/** [src_hc32f19x_std_tim0_pwm] */

/* end of file */
