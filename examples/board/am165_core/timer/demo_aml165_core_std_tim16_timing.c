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
 * \brief TIM16 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Դ��������ʱ���������Ϣ
 *   2. ��ʱ���ڵ���(Ĭ��Ϊ 2Hz)�����Դ��ڻ���� The timing frq is 2Hz;
 *
 * \note
 *    1. ���� TIM16 Ĭ�ϳ�ʼ������Ϊ������ PWM ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *       am_prj_config.h �ڽ� AM_CFG_BUZZER_ENABLE ����Ϊ 0��
 *    3. 16 λ��ʱ����ʱ����ֵ��Ϊ 65536 �ı�������ʱ����һЩƫ�
 *
 * \par Դ����
 * \snippet demo_aml165_core_std_tim16_timing.c src_aml165_core_std_tim16_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_aml165_core_std_tim16_timing
 * \copydoc demo_aml165_core_std_tim16_timing.c
 */

/** [src_aml165_core_std_tim16_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_aml165_inst_init.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_std_tim16_timing_entry (void)
{
    AM_DBG_INFO("demo aml165_core std tim16 timing!\r\n");

    demo_std_timer_timing_entry(am_zml165_tim16_timing_inst_init(), 0);
}
/** [src_aml165_core_std_tim16_timing] */

/* end of file */
