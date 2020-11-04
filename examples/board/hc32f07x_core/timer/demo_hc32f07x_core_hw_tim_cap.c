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
 * \brief ��ʱ�� CAP �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOB_3 �� PIOA_0 ���ӡ�
 *
 * - ʵ������
 *   1. TIM3 ͨ�� PIOB_3 ������� 2KHz �� PWM��
 *   2. TIM1 ��������ͨ�� 0 ʹ�� PIOA_0 ���Ų���
 *   3. ���ڴ�ӡ�����ò����ܵõ��� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ���� TIM2 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *       am_prj_config.h �ڽ� AM_CFG_DELAY_ENABLE��AM_CFG_SOFTIMER_ENABLE
 *       �� AM_CFG_SYSTEM_TICK_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_hc32f19x_hw_tim_cap.c src_hc32f19x_hw_tim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f19x_hw_tim_cap
 * \copydoc demo_hc32f19x_hw_tim_cap.c
 */

/** [src_hc32f19x_hw_tim_cap] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_hc32.h"
#include "am_hc32_clk.h"
#include "am_hc32f07x_inst_init.h"
#include "demo_hc32_entries.h"
#include "demo_amf07x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f07x_core_hw_tim_cap_entry (void)
{
    am_pwm_handle_t tim3_pwm_handle = am_hc32_tim3_pwm_inst_init();

    AM_DBG_INFO("demo amf19x_core hw tim cap!\r\n");

    /* TIM3 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(tim3_pwm_handle, 0, 500000 / 2, 500000);

    am_pwm_enable(tim3_pwm_handle, 0);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_0,  PIOA_0_TIM1_CHA  | PIOA_0_INPUT_FLOAT);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM012);

    demo_hc32_hw_tim_cap_entry(HC32_TIM1,
                               HC32_TIM_CH0A,
                               am_clk_rate_get(CLK_TIM012),
                               INUM_TIM1);
}
/** [src_hc32f19x_hw_tim_cap] */

/* end of file */
