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
 * \snippet demo_hc32_hw_wdt.c src_hc32_hw_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_wdt
 * \copydoc demo_hc32_hw_wdt.c
 */

/** [src_hc32_hw_wdt] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_hc32.h"
#include "am_hc32_wdt.h"

#define HC32_WDT_RST_COUNT1   (0x1e)
#define HC32_WDT_RST_COUNT2   (0xe1)

/**
 * \brief ���Ź�ʹ��
 *
 * \param[in] timeout_ms : ��ʱʱ��ֵ����λ��ms
 *
 * \return ��
 *
 */
static int __hc32_wdt_enable (amhw_hc32_wdt_t *p_hw_wdt,
                                uint32_t           timeout_ms)
{
    if (timeout_ms > HC32_WDT_52_4S) {
        return AM_ERROR;
    }

    /* �������ʱ�� */
    amhw_hc32_wdt_wov_set(p_hw_wdt, (uint8_t)timeout_ms);

    /* ���������λ */
    amhw_hc32_wdt_en_set(p_hw_wdt, 0);

    /* �������Ź� */
    amhw_hc32_wdt_rst_set(p_hw_wdt, HC32_WDT_RST_COUNT1);
    amhw_hc32_wdt_rst_set(p_hw_wdt, HC32_WDT_RST_COUNT2);

    return AM_OK;
}

/**
 * \brief ���Ź�ι��
 *
 * \return ��
 *
 */
static void __zlg_sdt_feed (amhw_hc32_wdt_t *p_hw_wdt)
{
    amhw_hc32_wdt_rst_set(p_hw_wdt, HC32_WDT_RST_COUNT1);
    amhw_hc32_wdt_rst_set(p_hw_wdt, HC32_WDT_RST_COUNT2);
}

/**
 * \brief HC32 WDT ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32_hw_wdt_entry (void     *p_hw_wdt,
                             uint32_t  time_out_ms,
                             uint32_t  feed_time_ms)
{
    __hc32_wdt_enable((amhw_hc32_wdt_t *)p_hw_wdt, time_out_ms);

    while (1) {

        /* ι������ */
        __zlg_sdt_feed(p_hw_wdt);

        /* ��ʱ������ʱ����ι��ʱ��ʱ,��������Ź��¼���MCU��λ */
        am_mdelay(feed_time_ms);
    }
}
/** [src_hc32_hw_wdt] */

/* end of file */
