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
 * \brief �߼���ʱ��tim6 CAP ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOB_3 �� PIOB_11 ���ӡ�
 *
 * - ʵ������
 *   1. TIM3 ͨ�� PIOB_3 ������� 2KHz �� PWM��
 *   2. TIM6 ��������ͨ�� 0 ʹ�� PIOB_11 ���Ų���
 *   3. ���ڴ�ӡ�����ò����ܵõ��� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f17x_std_tim6_cap.c src_hc32f17x_std_tim6_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-09  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f17x_std_tim6_cap
 * \copydoc demo_hc32f17x_std_tim6_cap.c
 */

/** [src_hc32f17x_std_tim6_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f17x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_amf17x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f17x_core_std_tim6_cap_entry (void)
{

    am_pwm_handle_t tim3_pwm_handle = am_hc32_tim3_pwm_inst_init();
    am_cap_handle_t tim6_cap_handle = am_hc32_tim6_cap_inst_init();
    
	  AM_DBG_INFO("demo amf17x_core std tim6 cap!\r\n");

    /* TIM3 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(tim3_pwm_handle, 0, 500000 / 2, 500000);
    am_pwm_enable(tim3_pwm_handle, 0);

    demo_std_timer_cap_entry(tim6_cap_handle, 0);
}
/** [src_hc32f17x_std_tim6_cap] */

/* end of file */
