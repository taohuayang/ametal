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
 *   1. PIOA_8(TIM1_CH1)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_std_tim1_pwm.c src_stm32f103rbt6_std_tim1_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-28  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_std_tim1_pwm
 * \copydoc demo_stm32f103rbt6_std_tim1_pwm.c
 */

/** [src_stm32f103rbt6_std_tim1_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_stm32f103rbt6_tim_pwm.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_std_entries.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_std_tim1_pwm_entry (void)
{

    AM_DBG_INFO("demo stm32f103rbt6_core std tim1 pwm!\r\n");

    demo_std_timer_pwm_entry(am_stm32f103rbt6_tim1_pwm_inst_init(), AM_STM32F103RBT6_TIM_PWM_CH1);
}
/** [src_stm32f103rbt6_std_tim1_pwm] */

/* end of file */
