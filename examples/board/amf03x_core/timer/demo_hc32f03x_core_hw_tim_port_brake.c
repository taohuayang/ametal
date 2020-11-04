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
 * \brief ��ʱ���˿�ɲ���ж�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_5��͵�ƽ���ӣ�TIM1_CHA��PIOA_0�����ռ�ձ�Ϊ25%��2Hz��PWM����
 *   2. PIOB_5��ߵ�ƽ���ӣ�����ɲ���жϣ����ڴ�ӡ"brake int!"��TIM1_CHA��PIOA_0����PWM
 *      ���ֹͣ���ٴν�PIOB_5��͵�ƽ���ӣ��ָ����������
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f03x_hw_tim_port_brake.c src_hc32f03x_hw_tim_port_brake
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f03x_hw_tim_port_brake
 * \copydoc demo_hc32f03x_hw_tim_port_brake.c
 */

/** [src_hc32f03x_hw_tim_port_brake] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_hc32.h"
#include "hw/amhw_hc32_adtim.h"
#include "am_hc32f03x_inst_init.h"
#include "demo_hc32_entries.h"
#include "demo_amf03x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f03x_core_hw_tim_port_brake_entry (void)
{

    AM_DBG_INFO("demo amf03x_core hw adtim port brake!\r\n");

    /* ɲ��������ų�ʼ�� */
    am_gpio_pin_cfg(PIOB_5, PIOB_5_TIM1_BK | PIOB_5_INPUT_FLOAT);

    /* TIM1_CHAͨ���������� */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_TIM1_CHA | PIOA_0_OUT_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM012);

    demo_hc32_hw_tim_port_brake_entry(HC32_TIM1,
                                        AMHW_HC32_TIM_TYPE_TIM1,
                                        HC32_TIM_CH0A,
                                        INUM_TIM1,
                                        500000 / 4,
                                        500000);
}
/** [src_hc32f03x_hw_tim_port_brake] */

/* end of file */
