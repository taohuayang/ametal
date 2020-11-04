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
 * \brief TIM3 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ�ʷ�ת��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. 16 λ��ʱ����ʱ����ֵ��Ϊ 65536 �ı�������ʱ����һЩƫ�
 *    3. ���� TIM3 Ĭ�ϳ�ʼ������Ϊ������ PWM ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *       am_prj_config.h �ڽ� AM_CFG_BUZZER_ENABLE ����Ϊ 0��
 *
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_std_tim3_timing.c src_stm32f103rbt6_std_tim3_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-25  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_std_tim3_timing
 * \copydoc demo_stm32f103rbt6_std_tim3_timing.c
 */

/** [src_stm32f103rbt6_std_tim3_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_std_tim3_timing_entry (void)
{
    AM_DBG_INFO("demo stm32f103rbt6_core std tim3 timing!\r\n");

    demo_std_timer_timing_entry(am_stm32f103rbt6_tim3_timing_inst_init(), 0);
}
/** [src_stm32f103rbt6_std_tim3_timing] */

/* end of file */
