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
 * \brief tim0 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOB_3 �� PIOA_0 ���ӡ�
 *
 * - ʵ������
 *   1. TIM3 ͨ�� PIOB_3 ������� 2KHz �� PWM��
 *   2. TIM0 ��������ͨ�� 0 ʹ�� PIOA_0 ���Ų���
 *   3. ���ڴ�ӡ�����ò����ܵõ��� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l17x_std_tim0_cap.c src_hc32l17x_std_tim0_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l17x_std_tim0_cap
 * \copydoc demo_hc32l17x_std_tim0_cap.c
 */

/** [src_hc32l17x_std_tim0_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32l17x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_aml17x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l17x_core_std_tim0_cap_entry (void)
{

    am_pwm_handle_t tim3_pwm_handle = am_hc32_tim3_pwm_inst_init();
    am_cap_handle_t tim0_cap_handle = am_hc32_tim0_cap_inst_init();
    
	  AM_DBG_INFO("demo aml17x_core std tim0 cap!\r\n");

    /* TIM3 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(tim3_pwm_handle, 0, 500000 / 2, 500000);
    am_pwm_enable(tim3_pwm_handle, 0);

    demo_std_timer_cap_entry(tim0_cap_handle, 0);
}
/** [src_hc32l17x_std_tim0_cap] */

/* end of file */
