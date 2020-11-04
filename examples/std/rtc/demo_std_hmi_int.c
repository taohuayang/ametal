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
 * \brief HMI�ж� ����
 *
 * - �������裺
 *   1. ������ں���
 *
 * - ʵ������
 *   1. ���ڽ�ÿ30���ӡʱ����Ϣ��
 *   2. LED0ÿ30�뷭תһ��״̬��
 *
 * \par Դ����
 * \snippet demo_std_hmi_int.c src_std_hmi_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-16  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_hmi_int
 * \copydoc demo_std_hmi_int.c
 */

/** [src_std_hmi_int] */
#include "ametal.h"
#include "am_board.h"
#include "am_rtc.h"
#include "am_pcf85063.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_led.h"

/** \brief �豸���� */
am_local am_rtc_serv_t __g_microport_rtc;

/** \brief �豸���� */
am_local am_alarm_clk_serv_t __g_microport_rtc_alarm_clk;

/** \brief HMI��ʱ��־ */
am_local uint8_t __g_hmi_flag = 0;

/** \brief Ҫ���õ�ʱ����Ϣ */
am_local am_tm_t __g_current_time = {
    55,          /**< \brief �� */
    59,          /**< \brief �� */
    11,          /**< \brief ʱ */
    5,           /**< \brief �� */
    8-1,         /**< \brief �� */
    2017-1900,   /**< \brief �� */
    6,           /**< \brief �� */
};

am_alarm_clk_tm_t alarm_tm = {
    59,
    23,
    AM_ALARM_CLK_EVERYDAY,
};

/**
 * \brief HMI�ص�����
 */
void am_pcf85063_hmi_cb(void *p_arg)
{
    uint8_t *p_hmi_flag = (uint8_t *)p_arg;

    *p_hmi_flag = 1;
}

/**
 * \brief �������
 */
void demo_std_hmi_int_entry (am_pcf85063_handle_t pcf85063_handle)
{
    int     ret = AM_OK;
    am_tm_t time;

    /* MicroPort PCF85063��ʼ�� ��ʹ��ͨ�õ� RTC ���ܣ� */
    am_rtc_handle_t rtc_handle = am_pcf85063_rtc_init(pcf85063_handle, &__g_microport_rtc);
    /* ��ȡPCF85063 ALARM_CLK��׼������ */
    am_alarm_clk_handle_t alarm_handle = am_pcf85063_alarm_clk_init(pcf85063_handle, &__g_microport_rtc_alarm_clk);

    /* ����ʱ�� */
    ret= am_rtc_time_set(rtc_handle, &__g_current_time);
    if(ret == AM_OK){
        AM_DBG_INFO("set time success \r\n");
        AM_DBG_INFO("%02d-%02d-%02d %02d:%02d:%02d %02d\n",
                    __g_current_time.tm_year +1900,
                    __g_current_time.tm_mon + 1,
                    __g_current_time.tm_mday,
                    __g_current_time.tm_hour,
                    __g_current_time.tm_min,
                    __g_current_time.tm_sec,
                    __g_current_time.tm_wday);
    } else {
        AM_DBG_INFO("set time fail \r\n");
    }

    /* ����û����õ��ǷǱ�׼�����ӽӿ� ��Ҫ����alarm_modeΪ__PCF85063_ALARM_MODE_NONSTANDARD */
    am_alarm_clk_time_set(alarm_handle, &alarm_tm);

    /* PCF85063 HMI�ص��������� */
    am_pcf85063_minute_timer_cb_set(pcf85063_handle, am_pcf85063_hmi_cb, &__g_hmi_flag);

    /* ʹ��PCF85063 HMI�ж� */
    am_pcf85063_minute_timer_int_enable(pcf85063_handle, AM_PCF85063_INT_HMINUTE);

    while(1) {
        if (__g_hmi_flag == 1) {
            __g_hmi_flag = 0;
            ret = am_rtc_time_get(rtc_handle, &time);
            AM_DBG_INFO("%02d-%02d-%02d %02d:%02d:%02d %02d\n",
                        time.tm_year +1900,
                        time.tm_mon + 1,
                        time.tm_mday,
                        time.tm_hour,
                        time.tm_min,
                        time.tm_sec,
                        time.tm_wday);

            am_led_toggle(LED0);
        }
    }
}
/** [src_std_rtc] */

/* end of file */
