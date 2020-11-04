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
 * \brief TIM2 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 5Hz ��Ƶ�ʷ�ת��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *
 * \note
 *   1. ���� TIM2 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *      am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SOFTIMER_ENABLE
 *      �� AM_CFG_SYSTEM_TICK_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_zlg118_std_tim2_timing.c src_zlg118_std_tim2_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_std_tim2_timing
 * \copydoc demo_zlg118_std_tim2_timing.c
 */

/** [src_zlg118_std_tim2_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zlg118_inst_init.h"
#include "demo_am118_core_entries.h"

/**
 * \brief �������
 */
void demo_zlg118_core_std_tim2_timing_entry (void)
{
    AM_DBG_INFO("demo am118_core std tim2 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg118_tim2_timing_inst_init(), 0);
}
/** [src_zlg118_std_tim2_timing] */

/* end of file */
