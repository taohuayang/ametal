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
 * \snippet demo_zlg237_hw_tim_pwm.c src_zlg237_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-04  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg237_hw_tim_pwm
 * \copydoc demo_zlg237_hw_tim_pwm.c
 */

/** [src_zlg237_hw_tim_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg237.h"
#include "am_zlg237_clk.h"
#include "am_zlg_tim_pwm.h"
#include "am_zlg237_inst_init.h"
#include "demo_zlg_entries.h"
#include "demo_am237_core_entries.h"

/**
 * \brief ��ʱ��PWM���HW���������
 */
void demo_zlg237_core_hw_tim_pwm_entry (void)
{

    AM_DBG_INFO("demo am237_core hw tim cmp toggle!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOB_11, PIOB_11_TIM2_CH4_REMAP2 | PIOB_11_AF_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λ��ʱ�� */
    am_zlg237_clk_reset(CLK_TIM2);

    demo_zlg_hw_tim_pwm_entry(ZLG237_TIM2,
                              AMHW_ZLG_TIM_TYPE1,
                              AM_ZLG_TIM_PWM_CH4,
                              am_clk_rate_get(CLK_TIM2),
                              INUM_TIM2);
}
/** [src_zlg237_hw_tim_pwm] */

/* end of file */
