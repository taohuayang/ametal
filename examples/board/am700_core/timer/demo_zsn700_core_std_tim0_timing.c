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
 * \brief TIM0 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 5Hz ��Ƶ����˸��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *
 * \par Դ����
 * \snippet demo_zsn700_std_tim0_timing.c src_zsn700_std_tim0_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_std_tim0_timing
 * \copydoc demo_zsn700_std_tim0_timing.c
 */

/** [src_zsn700_std_tim0_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zsn700_inst_init.h"
#include "demo_am700_core_entries.h"

/**
 * \brief �������
 */
void demo_zsn700_core_std_tim0_timing_entry (void)
{
    AM_DBG_INFO("demo am700_core std tim0 timing!\r\n");

    demo_std_timer_timing_entry(am_zsn700_tim0_timing_inst_init(), 0);
}
/** [src_zsn700_std_tim0_timing] */

/* end of file */
