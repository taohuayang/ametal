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
 * \brief ADTIM6 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOB_12(TIM6_CHA)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_hc32f19x_std_tim6_pwm.c src_hc32f19x_std_tim6_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f19x_std_tim6_pwm
 * \copydoc demo_hc32f19x_std_tim6_pwm.c
 */

/** [src_hc32f19x_std_tim6_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f19x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_std_tim6_pwm_entry (void)
{

    AM_DBG_INFO("demo amf19x_core std tim6 pwm!\r\n");

    demo_std_timer_pwm_entry(am_hc32_tim6_pwm_inst_init(), 0);
}
/** [src_hc32f19x_std_tim6_pwm] */

/* end of file */
