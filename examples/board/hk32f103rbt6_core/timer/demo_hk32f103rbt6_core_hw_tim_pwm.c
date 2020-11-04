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
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOB_11(TIM2_CH4) ���  5HZ �� PWM��ռ�ձ�Ϊ 50%��
 *   2. LED0 �� 200ms ������з�ת��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ơ�
 *
 * \par Դ����
 * \snippet demo_hk32f103rbt6_hw_tim_pwm.c src_hk32f103rbt6_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-04  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_hw_tim_pwm
 * \copydoc demo_hk32f103rbt6_hw_tim_pwm.c
 */

/** [src_hk32f103rbt6_hw_tim_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hk32f103rbt6.h"
#include "am_hk32f103rbt6_clk.h"
#include "am_hk32f103rbt6_tim_pwm.h"
#include "am_hk32f103rbt6_inst_init.h"
#include "demo_hk32f103rbt6_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

/**
 * \brief ��ʱ��PWM���HW���������
 */
void demo_hk32f103rbt6_core_hw_tim_pwm_entry (void)
{

    AM_DBG_INFO("demo hk32f103rbt6_core hw tim cmp toggle!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOB_11, PIOB_11_TIM2_CH4_REMAP2 | PIOB_11_AF_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λ��ʱ�� */
    am_hk32f103rbt6_clk_reset(CLK_TIM2);

    demo_hk32f103rbt6_hw_tim_pwm_entry(HK32F103RBT6_TIM2,
                              AMHW_HK32F103RBT6_TIM_TYPE1,
                              AM_HK32F103RBT6_TIM_PWM_CH4,
                              am_clk_rate_get(CLK_TIM2),
                              INUM_TIM2);
}
/** [src_hk32f103rbt6_hw_tim_pwm] */

/* end of file */
