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
 * \snippet demo_hc32f460_hw_wdt.c src_hc32f460_hw_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-12
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_wdt
 * \copydoc demo_hc32f460_hw_wdt.c
 */

/** [src_hc32f460_hw_wdt] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "am_hc32f460_clk.h"
#include "am_hc32f460_wdt.h"
#include "demo_hc32f460_entries.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 */
#define __WDT_TIMEOUT_MS       5000

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��WDT_TIMEOUT_MS��ֵоƬ�������λ
 */
#define __WDT_FEED_TIME_MS     1000


/**
 * \brief �������
 */
void demo_hc32f460_core_hw_wdt_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core hw wdt!\r\n");

    uint32_t clk_rate = am_clk_rate_get(CLK_PCLK3);

    demo_hc32f460_hw_wdt_entry((void *)HC32F460_WDT_BASE,
                               __WDT_TIMEOUT_MS,
                               __WDT_FEED_TIME_MS,
                               clk_rate);
}
/** [src_hc32f460_hw_wdt] */

/* end of file */
