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
 * \brief WWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 * 
 * - ʵ������
 *   1. �޸ĺ궨�� __WWDG_FEED_TIME_MS ��ֵ������ __WWDG_TIMEOUT_MS��оƬ��λ��
 *   2. �޸ĺ궨�� __WWDG_FEED_TIME_MS ��ֵ��С�� __WWDG_TIMEOUT_MS�������������С�
 *
 * \par Դ����
 * \snippet demo_aml165_core_hw_wwdg.c src_aml165_core_hw_wwdg
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_aml165_core_hw_wwdg
 * \copydoc demo_aml165_core_hw_wwdg.c
 */
 
/** [src_aml165_core_hw_wwdg] */
#include "ametal.h"
#include "am_clk.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "demo_zlg_entries.h"
#include "am_zml165_clk.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief ���Ź���ʱʱ�� 
 */
#define __WWDG_TIMEOUT_MS       50

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��WWDG_TIMEOUT_MS��ֵ
 */
#define __WWDG_FEED_TIME_MS     25

/**
 * \brief �������
 */
void demo_aml165_core_hw_wwdg_entry (void)
{
    AM_DBG_INFO("demo aml165_core hw wwdg!\r\n");

    am_clk_enable(CLK_WWDG);
    am_zml165_clk_reset(CLK_WWDG);

    demo_zlg_hw_wwdg_entry(ZML165_WWDG,
                           am_clk_rate_get(CLK_WWDG),
                           __WWDG_TIMEOUT_MS,
                           __WWDG_FEED_TIME_MS);
}
/** [src_aml165_core_hw_wwdg] */

/* end of file */
