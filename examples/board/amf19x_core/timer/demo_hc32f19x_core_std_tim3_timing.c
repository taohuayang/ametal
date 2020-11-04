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
 *   1. LED0 �� 5Hz ��Ƶ�ʷ�ת��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *
 * \par Դ����
 * \snippet demo_hc32f19x_std_tim3_timing.c src_hc32f19x_std_tim3_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f19x_std_tim3_timing
 * \copydoc demo_hc32f19x_std_tim3_timing.c
 */

/** [src_hc32f19x_std_tim3_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_hc32f19x_inst_init.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_std_tim3_timing_entry (void)
{
    AM_DBG_INFO("demo amf19x_core std tim3 timing!\r\n");

    demo_std_timer_timing_entry(am_hc32_tim3_timing_inst_init(), 0);
}
/** [src_hc32f19x_std_tim3_timing] */

/* end of file */
