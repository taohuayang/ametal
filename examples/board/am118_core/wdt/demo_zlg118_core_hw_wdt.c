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
 * \brief WDT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __WDT_FEED_TIME_MS ��ֵ������ __WDT_TIMEOUT_MS��оƬ��λ��
 *   2. �޸ĺ궨�� __WDT_FEED_TIME_MS ��ֵ��С�� __WDT_TIMEOUT_MS�������������С�
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_wdt.c src_zlg118_hw_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_wdt
 * \copydoc demo_zlg118_hw_wdt.c
 */

/** [src_zlg118_hw_wdt] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg118.h"
#include "am_zlg118_clk.h"
#include "am_zlg118_wdt.h"
#include "demo_zlg_entries.h"
#include "demo_am118_core_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 */
#define __WDT_TIMEOUT_MS       ZLG118_WDT_500MS

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��WDT_TIMEOUT_MS��ֵоƬ�������λ
 */
#define __WDT_FEED_TIME_MS     600


/**
 * \brief �������
 */
void demo_zlg118_core_hw_wdt_entry (void)
{
    AM_DBG_INFO("demo am118_core hw wdt!\r\n");

    am_clk_enable(CLK_WDT);

    demo_zlg118_hw_wdt_entry(ZLG118_WDT,
                             __WDT_TIMEOUT_MS,
                             __WDT_FEED_TIME_MS);
}
/** [src_zlg118_hw_wdt] */

/* end of file */
