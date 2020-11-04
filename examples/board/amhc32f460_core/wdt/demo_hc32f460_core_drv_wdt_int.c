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
 * \brief WDT �ж���ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __WDT_FEED_TIME_MS ��ֵ������ __WDT_TIMEOUT_MS�������жϣ���ӡ" wdt counter underflow !"��
 *   2. �޸ĺ궨�� __WDT_FEED_TIME_MS ��ֵ��С�� __WDT_TIMEOUT_MS�����򲻲���wdt�жϣ���ӡ"normal feed dog !"��
 *
 * \par Դ����
 * \snippet demo_hc32f460_drv_wdt.c src_hc32f460_drv_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-12
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_drv_wdt
 * \copydoc demo_hc32f460_drv_wdt.c
 */

/** [src_hc32f460_drv_wdt] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460_wdt.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hc32f460_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 */
#define __WDT_TIMEOUT_MS       1000

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��WDT_TIMEOUT_MS��ֵ,
 *        ��������Ź��¼���
 */
#define __WDT_FEED_TIME_MS     1200
extern am_hc32f460_wdt_dev_t __g_wdt_dev;
/**
 * \brief �������
 */
void demo_hc32f460_core_drv_wdt_int_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core drv wdt int !\r\n");

    demo_hc32f460_drv_wdt_int_entry(am_hc32f460_wdt_inst_init(),
                                    &__g_wdt_dev,
                                    __WDT_TIMEOUT_MS,
                                    __WDT_FEED_TIME_MS);
}
/** [src_hc32f460_drv_wdt] */

/* end of file */
