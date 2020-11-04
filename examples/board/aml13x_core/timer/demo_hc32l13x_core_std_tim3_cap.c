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
 * \brief TIM1 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOA_2 �� PIOB_3 ���ӡ�
 *
 * - ʵ������
 *   1. TIM0 ͨ�� PIOA_2 ������� 2KHz �� PWM��
 *   2. TIM3 ��������ͨ�� 0 ʹ�� PIOB_3 ���Ų���
 *   3. ���ڴ�ӡ�����ò����ܵõ��� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l13x_std_tim0_cap.c src_hc32l13x_std_tim0_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l13x_std_tim0_cap
 * \copydoc demo_hc32l13x_std_tim0_cap.c
 */

/** [src_hc32l13x_std_tim0_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32l13x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_aml13x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l13x_core_std_tim3_cap_entry (void)
{

    am_pwm_handle_t tim0_pwm_handle = am_hc32_tim0_pwm_inst_init();
    am_cap_handle_t tim3_cap_handle = am_hc32_tim3_cap_inst_init();
    
	  AM_DBG_INFO("demo aml13x_core std tim1 cap!\r\n");

    /* TIM0 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(tim0_pwm_handle, 0, 50000 / 2, 100000);
    am_pwm_enable(tim0_pwm_handle, 0);

    demo_std_timer_cap_entry(tim3_cap_handle, 0);
}
/** [src_hc32l13x_std_tim0_cap] */

/* end of file */
