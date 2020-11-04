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
 * \snippet demo_hk32f103rbt6_hw_wwdg.c src_hk32f103rbt6_hw_wwdg
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_hw_wwdg
 * \copydoc demo_hk32f103rbt6_hw_wwdg.c
 */

/** [src_hk32f103rbt6_hw_wwdg] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hk32f103rbt6.h"
#include "am_hk32f103rbt6_clk.h"
#include "demo_hk32f103rbt6_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 */
#define __WWDG_TIMEOUT_MS       30          /* ���58ms */

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��WWDG_TIMEOUT_MS��ֵоƬ�������λ
 */
#define __WWDG_FEED_TIME_MS     50


/**
 * \brief �������
 */
void demo_hk32f103rbt6_core_hw_wwdg_entry (void)
{
    AM_DBG_INFO("demo hk32f103rbt6_core hw wwdg!\r\n");

    amhw_hk32f103rbt6_rcc_lsi_enable();

    am_clk_enable(CLK_WWDG);

    am_hk32f103rbt6_clk_reset(CLK_WWDG);

    demo_hk32f103rbt6_hw_wwdg_entry(HK32F103RBT6_WWDG,
                           am_clk_rate_get(CLK_WWDG),
                           __WWDG_TIMEOUT_MS,
                           __WWDG_FEED_TIME_MS);
}
/** [src_hk32f103rbt6_hw_wwdg] */

/* end of file */
