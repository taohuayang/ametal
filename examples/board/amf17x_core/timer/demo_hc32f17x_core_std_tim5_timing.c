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
 * \brief ADTIM5 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 5Hz ��Ƶ����˸��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *
 *
 * \par Դ����
 * \snippet demo_hc32f17x_std_tim5_timing.c src_hc32f17x_std_tim5_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-09  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f17x_std_tim5_timing
 * \copydoc demo_hc32f17x_std_tim5_timing.c
 */

/** [src_hc32f17x_std_tim5_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_hc32f17x_inst_init.h"
#include "demo_amf17x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f17x_core_std_tim5_timing_entry (void)
{
    AM_DBG_INFO("demo amf17x_core std tim5 timing!\r\n");

    demo_std_timer_timing_entry(am_hc32_tim5_timing_inst_init(), 0);
}
/** [src_hc32f17x_std_tim5_timing] */

/* end of file */
