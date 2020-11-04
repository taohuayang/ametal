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
 * \brief ��ʱ�� TIMING ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ�ʽ��з�ת��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. 16 λ��ʱ����ʱ����ֵ��Ϊ 65536 �ı�������ʱ����һЩƫ�
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_hw_tim_timing.c src_stm32f103rbt6_hw_tim_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-25  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_hw_tim_timing
 * \copydoc demo_stm32f103rbt6_hw_tim_timing.c
 */

/** [src_stm32f103rbt6_hw_tim_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_stm32f103rbt6.h"
#include "am_stm32f103rbt6_clk.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_stm32f103rbt6_entries.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief ��ʱ��timing HW���������
 */
void demo_stm32f103rbt6_core_hw_tim_timing_entry (void)
{
    AM_DBG_INFO("demo stm32f103rbt6_core hw tim timing!\r\n");

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λ��ʱ�� */
    am_stm32f103rbt6_clk_reset(CLK_TIM2);

    demo_stm32f103rbt6_hw_tim_timing_entry(STM32F103RBT6_TIM2,
                                 AMHW_STM32F103RBT6_TIM_TYPE0,
                                 am_clk_rate_get(CLK_TIM2),
                                 INUM_TIM2);
}
/** [src_stm32f103rbt6_hw_tim_timing] */

/* end of file */
