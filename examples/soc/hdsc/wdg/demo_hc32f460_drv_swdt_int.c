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
 * \brief SWDT �ж���ʾ���̣�ͨ��������ӿ�ʵ��
 *
 *  SWDTֻ֧��Ӳ��������MCU����ʱ�������������ȡ���Ź����������趨��Ϣ��ICG0�Ĵ�������
 *  �������Զ���ʼ������
 *
 * - �������裺
 *   1. ����hc32f460_icg.h�� �ĺ�HC32F460_ICG0_SWDT_HARDWARE_START��ֵΪ
 *      ICG_FUNCTION_ON��ʹ��SWDT��Ӳ��������
 *   2. ����hc32f460_icg.h�� �ĺ� HC32F460_ICG0_SWDT_REG_CONFIG������SWDT�������Ŀ��Ʋ�����
 *      ���궨��HC32F460_ICG0_SWDT_ITS����ΪHC32F460_ICG_SWDT_INTERRUPT_REQUEST������
 *      SWDT�����¼�����Ϊ�жϡ�
 *
 * - ʵ������
 *   1. ���ݿ��Ź���ι��ʱ���Ƿ񳬹����õĿ��Ź���ʱʱ�䣬��ӡ"wdt counter underflow !"��
 *   "normal feed dog !"����ʾ��Ϣ��
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
#include "am_hc32f460_swdt.h"

static uint8_t g_swdt_status_flag = 0xFF;

/**
 * \brief SWDT �жϷ������
 */
static void swdt_isr (void *p_arg , uint32_t flag)
{
    if (flag == AM_HC32F460_SWDT_STATUS_REFRESH_ERROR) {
        g_swdt_status_flag = AM_HC32F460_SWDT_STATUS_REFRESH_ERROR;
    } else if (flag == AM_HC32F460_SWDT_STATUS_COUNT_UNDERFLOW) {
        g_swdt_status_flag = AM_HC32F460_SWDT_STATUS_COUNT_UNDERFLOW;
    }
}

/**
 * \brief �������
 */
void demo_hc32f460_drv_swdt_int_entry (am_wdt_handle_t         handle,
                                       am_hc32f460_swdt_dev_t *p_dev,
                                       uint32_t                feed_time_ms)
{
    am_wdt_info_t info;

    AM_DBG_INFO("The chip Reset by External Reset Pin or SWDT \r\n");

    am_wdt_info_get(handle, &info);

    AM_DBG_INFO("The SWDT support min time is %d ms\r\n", info.min_timeout_ms);
    AM_DBG_INFO("The SWDT support max time is %d ms\r\n", info.max_timeout_ms);

    am_hc32f460_swdt_isr_connect(p_dev, swdt_isr, (void *)0);

    while (1) {

        /* ι������ */
        am_wdt_feed(handle);

        /* ��ʱ������ʱ����ι��ʱ��ʱ,��������Ź��¼���MCU ��λ */
        am_mdelay(feed_time_ms);

        if (g_swdt_status_flag == AM_HC32F460_SWDT_STATUS_COUNT_UNDERFLOW) {
            AM_DBG_INFO("wdt counter underflow !\r\n");
        } else if (g_swdt_status_flag == AM_HC32F460_SWDT_STATUS_REFRESH_ERROR) {
            AM_DBG_INFO("wdt counter refresh error !\r\n");
        } else {
            AM_DBG_INFO("normal feed dog !\r\n");
        }

    }
}
/** [src_drv_swdt] */

/* end of file */
