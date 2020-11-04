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
 * \brief ADTIMER61 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOE_2 �� PIOE_9 ���ӡ�
 *
 * - ʵ������
 *   1. TIMEA1 ͨ�� PIOE_2 ������� 2KHz �� PWM��
 *   2. ADTIM61 ��������ͨ�� 1 ʹ�� PIOE_9 ���Ų���
 *   3. ���ڴ�ӡ�����ò����ܵõ��� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \note
 *    
 *      
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_tim0_cap.c src_hc32f460_std_adtim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_adtim_cap
 * \copydoc demo_hc32f460_std_tim_cap.c
 */

/** [src_hc32f460_std_tim0_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460_adtim_cap.h"
#include "am_hc32f460_timea_pwm.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hc32f460_core_entries.h"


/**
 * \brief �������
 */
void demo_hc32f460_core_std_adtim61_cap_entry (void)
{
    am_pwm_handle_t timea3_pwm_handle = am_hc32f460_timea3_pwm_inst_init();
    am_cap_handle_t adtim61_cap_handle = am_hc32f460_adtim61_cap_inst_init();
    
    AM_DBG_INFO("demo hc32f460_core std adtim61 cap!\r\n");

    /* TIM0 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(timea3_pwm_handle, TIMERA_CH5, 500000 / 2, 500000);
    am_pwm_enable(timea3_pwm_handle, TIMERA_CH5);

    demo_std_timer_cap_entry(adtim61_cap_handle, AMHW_HC32F460_ADTIM_CHX_A);
}
/** [src_hc32f460_std_tim0_cap] */

/* end of file */
