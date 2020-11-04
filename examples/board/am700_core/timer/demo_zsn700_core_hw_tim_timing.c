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
 *   1. LED0 �� 10Hz ��Ƶ�ʽ��з�ת��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_tim_timing.c src_zsn700_hw_tim_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_tim_timing
 * \copydoc demo_zsn700_hw_tim_timing.c
 */

/** [src_zsn700_hw_tim_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zsn700.h"
#include "am_zsn700_clk.h"
#include "am_zsn700_inst_init.h"
#include "demo_zlg_entries.h"
#include "demo_am700_core_entries.h"

/**
 * \brief ��ʱ��timing HW���������
 */
void demo_zsn700_core_hw_tim_timing_entry (void)
{
    AM_DBG_INFO("demo am700_core hw tim timing!\r\n");

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM012);

    demo_zsn700_hw_tim_timing_entry(ZSN700_TIM0,
    		                        AMHW_ZSN700_TIM_TYPE_TIM0,
                                    am_clk_rate_get(CLK_TIM012),
                                    INUM_TIM0);
}
/** [src_zsn700_hw_tim_timing] */

/* end of file */
