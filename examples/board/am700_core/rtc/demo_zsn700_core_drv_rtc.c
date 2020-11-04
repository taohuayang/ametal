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
 * \brief RTC ���̣�ͨ����׼�ӿں��м������㺯��ʵ��
 *
 * - ʵ������
 *   1. ÿ10�뷢��һ�������жϣ����ڲ���ӡ����ǰʱ����Ϣ��
 *   2. ���ĵ�11��21��0����������жϣ���ӡ����"alarm clock int!"��ʾ��Ϣ��
 *   3. ����am_hwconf_zsn700_rtc.c�ļ�������1Hz������ƣ���ʹ�ܣ�PIOB_14�����1Hz�ķ�����
 *   4. �ر�ʱ�Ӳ���������£����1Hz������ʵ��Ƶ�ʣ��������м���ʽ���㣺
 *           ppm = ��1Hz������ʵ��Ƶ�� - 1Hz��* 10^6
 *      ��������Ľ������am_hwconf_zsn700_rtc.c���豸��Ϣ��Ӧλ�ã������о����Ƿ�ʹ�ܸ��ٲ���ʱ�ӡ�
 *      ���롢���أ�����˿ڽ�������Ƚϸߵ�1Hz����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsn700_std_rtc.c src_zsn700_std_rtc
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_std_rtc
 * \copydoc demo_zsn700_std_rtc.c
 */

/** [src_zsn700_std_rtc] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_rtc.h"
#include "am_zsn700_rtc.h"
#include "am_zsn700_inst_init.h"
#include "demo_am700_core_entries.h"

am_tm_t   __time;
am_bool_t __get_flag =  AM_FALSE;


am_local am_tm_t __g_current_time = {
    0,           /**< \brief �� */
    20,          /**< \brief �� */
    11,          /**< \brief ʱ */
    17,          /**< \brief �� */
    10,          /**< \brief �� */
    19,          /**< \brief �� */
    4,           /**< \brief �� */
};

void period_int_callback(void *drv)
{

    am_rtc_handle_t rtc_handle = (am_rtc_handle_t )drv;

    if(am_rtc_time_get(rtc_handle, &__time) == AM_OK) {
        __get_flag = AM_TRUE;
    }
}

void alarm_clock_int_callback(void *drv)
{
    AM_DBG_INFO("\r\n\r\n");
    AM_DBG_INFO("alarm clock int!\r\n");
    AM_DBG_INFO("alarm clock int!\r\n");
    AM_DBG_INFO("alarm clock int!\r\n");
    AM_DBG_INFO("alarm clock int!\r\n");
    AM_DBG_INFO("\r\n\r\n");
}

/**
 * \brief �������
 */
void demo_zsn700_core_drv_rtc_entry (void)
{
    int             ret          = AM_OK;
    am_rtc_handle_t p_rtc_handle = am_zsn700_rtc_inst_init();

    AM_DBG_INFO("demo am700_core rtc entry!\r\n");

    /* ����ʱ�� */
    ret= am_rtc_time_set(p_rtc_handle, &__g_current_time);


    if(ret == AM_OK){
        AM_DBG_INFO("set time success \r\n");
    } else {
        AM_DBG_INFO("set time fail \r\n");
    }

    /* ���������жϻص����� */
    am_zsn700_rtc_callback_set(p_rtc_handle,
                               AM_ZSN700_RTC_CALLBACK_PERIOD,
                               period_int_callback,
                               (void *)p_rtc_handle);

    /* ʹ���Զ��������ж�ʱ��ѡ��20s����һ�������ж� */
    am_zsn700_rtc_period_int_enable(p_rtc_handle,
                                    AMHW_ZSN700_RTC_PERIOD_INT_TYPE_CUSTOM,
                                    AMHW_ZSN700_RTC_PERIOD_INT_TIME_1_MIN,
                                    10.0);

    /* ���������жϻص����� */
    am_zsn700_rtc_callback_set(p_rtc_handle,
                               AM_ZSN700_RTC_CALLBACK_ALARM,
                               alarm_clock_int_callback,
                               (void *)p_rtc_handle);

    /* �����ж����ã������ĵ�11��21��0����������ж� */
    am_zsn700_rtc_alarm_clock_int_enable(p_rtc_handle,
                                         0,
                                         21,
                                         11,
                                         4);

    while(1) {

        if(__get_flag == AM_TRUE) {
            AM_DBG_INFO("%02d-%02d-%02d %02d:%02d:%02d %02d\n",
                        __time.tm_year,
                        __time.tm_mon,
                        __time.tm_mday,
                        __time.tm_hour,
                        __time.tm_min,
                        __time.tm_sec,
                        __time.tm_wday);

            __get_flag =  AM_FALSE;
        }
        am_mdelay(20);
    }
}
/** [src_zsn700_std_rtc] */

/* end of file */
