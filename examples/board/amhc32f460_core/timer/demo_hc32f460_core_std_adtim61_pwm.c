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
 * \brief ADTIMER61 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOE_8(TIMERA_CH1)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 *   2. PIOE_9(TIMERA_CH1)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 * \par Դ����
 * \snippet demo_hc32f460_std_timea1_pwm.c src_hc32f460_std_tim3_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32lf460_std_timea1_pwm
 * \copydoc demo_hc32f460_std_timea1_pwm.c
 */

/** [src_hc32f460_std_tim3_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460_adtim_pwm.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_adtim61_pwm_entry (void)
{

    AM_DBG_INFO("demo hc32f460_core std adtim61 pwm!\r\n");

    demo_std_timer_pwm_entry(am_hc32f460_adtim61_pwm_inst_init(), 0);
}
/** [src_hc32f460_std_tim3_pwm] */

/* end of file */