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
 * \brief TIMA2 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 5Hz ��Ƶ����˸��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *   2. Channel_num��Ҫ��Ӳ�������ļ�am_hwconf_hc32f460_tim_timing.cһ��
 * \par Դ����
 * \snippet demo_hc32f460_std_tim0_timing.c src_hc32f460_std_tim0_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_tim0_timing
 * \copydoc demo_hc32f460_std_tim0_timing.c
 */

/** [src_hc32f460_std_tim0_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_timea2_timing_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core std timea2 timing!\r\n");

    demo_std_timer_timing_entry(am_hc32f460_timea2_timing_inst_init(), 0);
}
/** [src_hc32f460_std_tim0_timing] */

/* end of file */
