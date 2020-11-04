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
 * \brief WDT �ж���ʾ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. feed_time_ms ���� time_out_ms�������жϣ���ӡ" wdt counter underflow !"��
 *   2. feed_time_ms С�� time_out_ms�����򲻲���wdt�жϣ���ӡ"normal feed dog !"��
 *
 * \par Դ����
 * \snippet demo_std_wdt.c src_std_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 20-06-03  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_drv_wdt
 * \copydoc demo_drv_wdt.c
 */

/** [src_drv_wdt] */
#include "ametal.h"
#include "am_wdt.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_hc32f460_wdt.h"

static uint8_t g_wdt_status_flag = 0xFF;

/**
 * \brief WDT �жϷ������
 */
static void wdt_isr (void *p_arg , uint32_t flag)
{
    if (flag == AM_HC32F460_WDT_STATUS_REFRESH_ERROR) {
        g_wdt_status_flag = AM_HC32F460_WDT_STATUS_REFRESH_ERROR;
    } else if (flag == AM_HC32F460_WDT_STATUS_COUNT_UNDERFLOW) {
        g_wdt_status_flag = AM_HC32F460_WDT_STATUS_COUNT_UNDERFLOW;
    }
}

/**
 * \brief �������
 */
void demo_hc32f460_drv_wdt_int_entry (am_wdt_handle_t         handle,
                                      am_hc32f460_wdt_dev_t  *p_dev,
                                      uint32_t                time_out_ms,
                                      uint32_t                feed_time_ms)
{
    am_wdt_info_t info;

    AM_DBG_INFO("The chip Reset by External Reset Pin or WDT \r\n");

    am_wdt_info_get(handle, &info);

    AM_DBG_INFO("The WDT support min time is %d ms\r\n", info.min_timeout_ms);
    AM_DBG_INFO("The WDT support max time is %d ms\r\n", info.max_timeout_ms);

    am_hc32f460_wdt_isr_connect(p_dev, wdt_isr, (void *)0);

    am_wdt_enable(handle, time_out_ms);

    while (1) {

        /* ι������ */
        am_wdt_feed(handle);

        /* ��ʱ������ʱ����ι��ʱ��ʱ,��������Ź��¼���MCU ��λ */
        am_mdelay(feed_time_ms);

        if (g_wdt_status_flag == AM_HC32F460_WDT_STATUS_COUNT_UNDERFLOW) {
            AM_DBG_INFO("wdt counter underflow !\r\n");
        } else if (g_wdt_status_flag == AM_HC32F460_WDT_STATUS_REFRESH_ERROR) {
            AM_DBG_INFO("wdt counter refresh error !\r\n");
        } else {
            AM_DBG_INFO("normal feed dog !\r\n");
        }

    }
}
/** [src_drv_wdt] */

/* end of file */
