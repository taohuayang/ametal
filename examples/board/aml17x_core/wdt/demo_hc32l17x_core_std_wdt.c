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
 * \brief WDT��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __WDT_FEED_TIME_MS ��ֵ������ __WDT_TIMEOUT_MS��оƬ��λ��
 *   2. �޸ĺ궨�� __WDT_FEED_TIME_MS ��ֵ��С�� __WDT_TIMEOUT_MS�������������С�
 *
 * \par Դ����
 * \snippet demo_hc32l17x_std_wdt.c src_hc32l17x_std_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l17x_std_wdt
 * \copydoc demo_hc32l17x_std_wdt.c
 */

/** [src_hc32l17x_std_wdt] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32_wdt.h"
#include "am_hc32l17x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_aml17x_core_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 */
#define __WDT_TIMEOUT_MS       HC32_WDT_51MS     /* ���52.4s */

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��WDT_TIMEOUT_MS��ֵ,
 *        ��������Ź��¼���
 */
#define __WDT_FEED_TIME_MS     10

/**
 * \brief �������
 */
void demo_hc32l17x_core_std_wdt_entry (void)
{
    AM_DBG_INFO("demo aml17x_core std wdt!\r\n");

    demo_std_wdt_entry(am_hc32_wdt_inst_init(),
                       __WDT_TIMEOUT_MS,
                       __WDT_FEED_TIME_MS);
}
/** [src_hc32l17x_std_wdt] */

/* end of file */
