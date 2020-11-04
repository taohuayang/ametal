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
 * \brief ͨ�ö�ʱ��VCɲ�����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - �������裺
 *   1.VC0_P("+"�����PA1)����һ��ģ���ѹ�����鲻����3.3V��
 *   2.VC0_N("-"�����PA0)����һ��ģ���ѹ�����鲻����3.3V��
 *   3.����VC0_P��VC0_N֮��Ĵ�С��ϵ������������ʵ������
 *
 * - ʵ������
 *   1.VC0_P("+"�����PA1)�ĵ�ѹ����VC0_N("-"�����PA0)�ĵ�ѹ��VC0_OUT(PA6)����ߵ�ƽ��
 *     ����VC0�ж�(�ߵ�ƽһֱ�����ж�)����ʱ��1ɲ��������Ч��TIM1_CHB(PIOB_6)��PWM���ֹͣ��
 *   2.VC0_P("+"�����PA1)�ĵ�ѹС��VC0_N("-"�����PA0)�ĵ�ѹ��VC0_OUT(PA6)����͵�ƽ��
 *     VC0���жϲ�����TIM1_CHB(PIOB_6)��PWM���������
 *
 * \note
 *    1. ��ʵ����������ͨ�ö�ʱ����TIM0��1��2����
 *    2. VCĬ��ʹ��VC0�˿���Ϊ��ʾʵ����
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_tim_vc_brake.c src_zsn700_hw_tim_vc_brake
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_tim_vc_brake
 * \copydoc demo_zsn700_hw_tim_vc_brake.c
 */

/** [src_zsn700_hw_tim_vc_brake] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_tim.h"
#include "hw/amhw_zsn700_vc.h"
#include "am_zsn700_inst_init.h"
#include "demo_zlg_entries.h"
#include "demo_am700_core_entries.h"

/**
 * \brief �������
 */void demo_zsn700_core_hw_tim_vc_brake_entry (void)

{

    AM_DBG_INFO("demo am700_core hw tim vc_brake!\r\n");

    /* ����PIOA_0ΪVC_OUT���� */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_VC0_OUT | PIOA_0_OUT_PP);

    /* VC0_N��VC0_P��������ų�ʼ�� */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_AIN);
    am_gpio_pin_cfg(PIOA_1, PIOA_1_AIN);

    /* TIM1_CHBͨ���������� */
    am_gpio_pin_cfg(PIOB_6, PIOB_6_TIM1_CHB | PIOB_6_OUT_PP);

    /* ����TIM1��VC��BGRʱ�� */
    am_clk_enable(CLK_TIM012);
    am_clk_enable(CLK_VC_LVD);
    am_clk_enable(CLK_ADC_BGR);

    demo_zsn700_hw_tim_vc_brake_entry(ZSN700_TIM1,
                                      ZSN700_TIM_CH0B,
                                      500000 / 4,
                                      500000,
                                      ZSN700_VC,
                                      AMHW_ZSN700_VC0_N_INPUT_PA0,
                                      AMHW_ZSN700_VC0_P_INPUT_PA1);
}
/** [src_zsn700_hw_tim_vc_brake] */

/* end of file */
