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
 *   1. PIOA_7(TIM2_CH0)��� 2KHz �� PWM��ռ�ձ�Ϊ 50%��
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ���� TIM2 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *       am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SOFTIMER_ENABLE
 *       �� AM_CFG_SYSTEM_TICK_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_hc32l13x_std_tim2_pwm.c src_hc32l13x_std_tim2_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l13x_std_tim2_pwm
 * \copydoc demo_hc32l13x_std_tim2_pwm.c
 */

/** [src_hc32l13x_std_tim2_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32_tim_pwm.h"
#include "am_hc32l13x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_aml13x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l13x_core_std_tim2_pwm_entry (void)
{

    AM_DBG_INFO("demo aml13x_core std tim2 pwm!\r\n");

    demo_std_timer_pwm_entry(am_hc32_tim2_pwm_inst_init(), AM_HC32_TIM_PWM_CH0A);
}
/** [src_hc32l13x_std_tim2_pwm] */

/* end of file */
