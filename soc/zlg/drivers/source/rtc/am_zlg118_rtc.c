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
 * \brief Real-Time Clock(RTC) drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-16  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_time.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zlg118.h"
#include "am_zlg118_clk.h"
#include "am_zlg118_rtc.h"
#include "hw/amhw_zlg118_rtc.h"
#include "hw/amhw_zlg118_rcc.h"
#include "zlg118_periph_map.h"
#include <time.h>
#include <string.h>

/*******************************************************************************
  ���غ�������
*******************************************************************************/

/**
 * \brief ���õ�ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_set (void *p_drv, am_tm_t *p_tm);

/**
 * \brief ��ȡ��ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_get (void *p_drv, am_tm_t *p_tm);

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief ���� RTC ��׼�ӿ���Ҫ�ĺ��� */
am_local am_const struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __rtc_time_set,  /* ���õ�ǰ��ϸ��ʱ�� */
    __rtc_time_get,  /* ��ȡ��ǰ��ϸ��ʱ�� */
};

/*******************************************************************************
  ���غ�������
*******************************************************************************/
/**
 * \brief ��ȡ��ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_get (void *p_drv, am_tm_t *p_tm)
{
    am_zlg118_rtc_dev_t *p_dev    = (am_zlg118_rtc_dev_t *)p_drv;
    amhw_zlg118_rtc_t   *p_hw_rtc = (amhw_zlg118_rtc_t  *)p_dev->p_devinfo->rtc_regbase;

    if ((NULL == p_tm) || (NULL == p_tm)) {
        return -AM_EINVAL;
    }

    /* ��дģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_WRITEREAD);

    /* �ȴ�����д��/����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_FALSE);

    p_tm->tm_sec  = amhw_zlg118_rtc_sec_get(p_hw_rtc);
    p_tm->tm_min  = amhw_zlg118_rtc_min_get(p_hw_rtc);
    p_tm->tm_hour = amhw_zlg118_rtc_hour_get(p_hw_rtc);
    p_tm->tm_mday = amhw_zlg118_rtc_day_get(p_hw_rtc);
    p_tm->tm_wday = amhw_zlg118_rtc_week_get(p_hw_rtc);
    p_tm->tm_mon  = amhw_zlg118_rtc_mon_get(p_hw_rtc);
    p_tm->tm_year = amhw_zlg118_rtc_year_get(p_hw_rtc);

    /* ����ֵģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_COUNTER);

    /* �ȴ����ڼ�����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_TRUE);

    return AM_OK;
}

/**
 * \brief ���õ�ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_set (void *p_drv, am_tm_t *p_tm)
{
    am_zlg118_rtc_dev_t *p_dev = (am_zlg118_rtc_dev_t *)p_drv;
    amhw_zlg118_rtc_t   *p_hw_rtc = (amhw_zlg118_rtc_t  *)p_dev->p_devinfo->rtc_regbase;

    if ((NULL == p_tm) || (NULL == p_tm)) {
        return -AM_EINVAL;
    }

    /* ��дģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_WRITEREAD);

    /* �ȴ�����д��/����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_FALSE);

    amhw_zlg118_rtc_sec_set(p_hw_rtc, p_tm->tm_sec);
    amhw_zlg118_rtc_min_set(p_hw_rtc, p_tm->tm_min);
    amhw_zlg118_rtc_hour_set(p_hw_rtc, p_tm->tm_hour);
    amhw_zlg118_rtc_day_set(p_hw_rtc, p_tm->tm_mday);
    amhw_zlg118_rtc_week_set(p_hw_rtc, p_tm->tm_wday);
    amhw_zlg118_rtc_mon_set(p_hw_rtc, p_tm->tm_mon);
    amhw_zlg118_rtc_year_set(p_hw_rtc, p_tm->tm_year);

    /* ����ֵģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_COUNTER);

    /* �ȴ����ڼ�����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_TRUE);

    return AM_OK;
}

/**
 * \brief RTC �жϷ�����
 */
am_local void __rtc_sec_isr (void *p_arg)
{
    am_zlg118_rtc_dev_t *p_dev = (am_zlg118_rtc_dev_t *)p_arg;
    amhw_zlg118_rtc_t   *p_hw_rtc = NULL;

    p_hw_rtc =(amhw_zlg118_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    /* �����ж� */
    if (amhw_zlg118_rtc_period_int_flag_get(p_hw_rtc) == AM_TRUE) {
        amhw_zlg118_rtc_period_int_flag_clr(p_hw_rtc);
        if (p_dev->pfn_callback[0]) {
            p_dev->pfn_callback[0](p_dev->p_arg[0]);
        }
    }

    /* �����ж� */
    if (amhw_zlg118_rtc_alarm_clock_int_flag_get(p_hw_rtc) == AM_TRUE) {
        amhw_zlg118_rtc_alarm_clock_int_flag_clr(p_hw_rtc);
        if (p_dev->pfn_callback[1]) {
            p_dev->pfn_callback[1](p_dev->p_arg[1]);
        }
    }
}

/*******************************************************************************
  �ⲿ��������
*******************************************************************************/

/**
 * \brief ��ȡ RTC ������ֵ
 */
am_err_t am_zlg118_rtc_cnt_get (am_rtc_handle_t handle,
                                uint8_t        *sec,
                                uint8_t        *min,
                                uint8_t        *hour,
                                uint8_t        *mday,
                                uint8_t        *wday,
                                uint8_t        *mon,
                                uint8_t        *year)
{
    am_zlg118_rtc_dev_t *p_dev    = NULL;
    amhw_zlg118_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg118_rtc_dev_t *)handle->p_drv;
    p_hw_rtc =(amhw_zlg118_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    /* ��дģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_WRITEREAD);

    /* �ȴ�����д��/����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_FALSE);

    *sec  = amhw_zlg118_rtc_sec_get(p_hw_rtc);
    *min  = amhw_zlg118_rtc_min_get(p_hw_rtc);
    *hour = amhw_zlg118_rtc_hour_get(p_hw_rtc);
    *mday = amhw_zlg118_rtc_day_get(p_hw_rtc);
    *wday = amhw_zlg118_rtc_week_get(p_hw_rtc);
    *mon  = amhw_zlg118_rtc_mon_get(p_hw_rtc);
    *year = amhw_zlg118_rtc_year_get(p_hw_rtc);

    /* ����ֵģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_COUNTER);

    /* �ȴ����ڼ�����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_TRUE);

    return AM_OK;
}

/**
 * \brief ���� RTC ������ֵ
 */
am_err_t am_zlg118_rtc_cnt_set (am_rtc_handle_t handle,
                                uint8_t         sec,
                                uint8_t         min,
                                uint8_t         hour,
                                uint8_t         mday,
                                uint8_t         wday,
                                uint8_t         mon,
                                uint8_t         year)
{
    am_zlg118_rtc_dev_t *p_dev    = NULL;
    amhw_zlg118_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }
		
    p_dev    = (am_zlg118_rtc_dev_t *)handle->p_drv;
    p_hw_rtc = (amhw_zlg118_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    /* ��дģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_WRITEREAD);

    /* �ȴ�����д��/����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_FALSE);

    amhw_zlg118_rtc_sec_set(p_hw_rtc, sec);
    amhw_zlg118_rtc_min_set(p_hw_rtc, min);
    amhw_zlg118_rtc_hour_set(p_hw_rtc, hour);
    amhw_zlg118_rtc_day_set(p_hw_rtc, mday);
    amhw_zlg118_rtc_week_set(p_hw_rtc, wday);
    amhw_zlg118_rtc_mon_set(p_hw_rtc, mon);
    amhw_zlg118_rtc_year_set(p_hw_rtc, year);

    /* ����ֵģʽ */
    amhw_zlg118_rtc_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_MODE_COUNTER);

    /* �ȴ����ڼ�����״̬ */
    while(amhw_zlg118_rtc_writeread_flag_get(p_hw_rtc) == AM_TRUE);

    return AM_OK;
}

/**
 * \brief ���� RTC �жϻص�
 */
am_err_t am_zlg118_rtc_callback_set (am_rtc_handle_t handle,
                                     uint8_t         type,
                                     am_pfnvoid_t    pfn_callback,
                                     void           *p_arg)
{
    am_zlg118_rtc_dev_t *p_dev = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg118_rtc_dev_t *)handle->p_drv;

    if (AM_ZLG118_RTC_CALLBACK_PERIOD == type) {
        p_dev->pfn_callback[0] = pfn_callback;
        p_dev->p_arg[0] = p_arg;
    } else if (AM_ZLG118_RTC_CALLBACK_ALARM == type) {
        p_dev->pfn_callback[1] = pfn_callback;
        p_dev->p_arg[1] = p_arg;
    } else {
        return -AM_EINVAL;
    }

    return AM_OK;
}

/**
 * \brief RTC�����ж�ʹ��
 */
am_err_t am_zlg118_rtc_period_int_enable(
              am_rtc_handle_t                   handle,
              amhw_zlg118_rtc_period_int_type_t type,
              amhw_zlg118_rtc_period_int_time_t set_s,
              float                             set_c)
{
    am_zlg118_rtc_dev_t *p_dev    = NULL;
    amhw_zlg118_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg118_rtc_dev_t *)handle->p_drv;
    p_hw_rtc = (amhw_zlg118_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    /* RTC���� */
    amhw_zlg118_rtc_enable(p_hw_rtc, AM_FALSE);

    /* ���������ж� */
    if (AMHW_ZLG118_RTC_PERIOD_INT_TYPE_CUSTOM == type) {

        /* �����Զ�������ʱ���趨*/
        amhw_zlg118_rtc_period_int_time_set_enable(p_hw_rtc, AM_TRUE);

        /* �趨ʱ�� */
        amhw_zlg118_rtc_period_int_time_set(p_hw_rtc, set_c);
    } else {

        /* �����Զ�������ʱ���趨,����ϵͳ��ʱ��ѡ�� */
        amhw_zlg118_rtc_period_int_time_set_enable(p_hw_rtc, AM_TRUE);

        /* �趨ʱ�� */
        amhw_zlg118_rtc_period_int_time_sel(p_hw_rtc, set_s);
    }

    /* NVIC�ж� */
    am_int_enable(p_dev->p_devinfo->rtc_inum);

    /* RTCʹ�� */
    amhw_zlg118_rtc_enable(p_hw_rtc, AM_TRUE);

    p_dev->int_state |= AM_ZLG118_RTC_CALLBACK_PERIOD;

    return AM_OK;
}

/**
 * \brief RTC�����ж�ʹ��
 */
am_err_t am_zlg118_rtc_alarm_clock_int_enable(am_rtc_handle_t handle,
                                              uint8_t         sec,
                                              uint8_t         min,
                                              uint8_t         hour,
                                              uint8_t         wday)
{
    am_zlg118_rtc_dev_t *p_dev    = NULL;
    amhw_zlg118_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg118_rtc_dev_t *)handle->p_drv;
    p_hw_rtc =(amhw_zlg118_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    /* RTC���� */
    amhw_zlg118_rtc_enable(p_hw_rtc, AM_FALSE);

    /* ���ӽ��� */
    amhw_zlg118_rtc_alarm_clock_enable(p_hw_rtc, AM_FALSE);

    /* �����ж�ʹ�� */
    amhw_zlg118_rtc_alarm_clock_int_enable(p_hw_rtc, AM_TRUE);

    /* ���������롢ʱ���֡�ʱ���ܼ� */
    amhw_zlg118_rtc_sec_alarm_clock_set(p_hw_rtc, sec);
    amhw_zlg118_rtc_min_alarm_clock_set(p_hw_rtc, min);
    amhw_zlg118_rtc_hour_alarm_clock_set(p_hw_rtc, hour);
    amhw_zlg118_rtc_week_alarm_clock_set(p_hw_rtc, wday);

    /* �������жϱ�־ */
    amhw_zlg118_rtc_alarm_clock_int_flag_clr(p_hw_rtc);

    /* ����ʹ�� */
    amhw_zlg118_rtc_alarm_clock_enable(p_hw_rtc, AM_TRUE);

    /* NVIC�ж�ʹ�� */
    am_int_enable(p_dev->p_devinfo->rtc_inum);

    /* RTCʹ�� */
    amhw_zlg118_rtc_enable(p_hw_rtc, AM_TRUE);

    p_dev->int_state |= AM_ZLG118_RTC_CALLBACK_PERIOD;

    return AM_OK;
}

/**
 * \brief RTC �ж�ʧ��
 */
am_err_t am_zlg118_rtc_int_disable (am_rtc_handle_t handle,
                                    uint8_t         type)
{
    am_zlg118_rtc_dev_t *p_dev    = NULL;
    amhw_zlg118_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg118_rtc_dev_t *)handle->p_drv;
    p_hw_rtc =(amhw_zlg118_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    if(type == AM_ZLG118_RTC_CALLBACK_ALARM) {
        /* ���ӽ��� */
        amhw_zlg118_rtc_alarm_clock_enable(p_hw_rtc, AM_FALSE);

        /* �����жϽ���*/
        amhw_zlg118_rtc_alarm_clock_int_enable(p_hw_rtc, AM_FALSE);

        p_dev->int_state &= ~AM_ZLG118_RTC_CALLBACK_ALARM;

    } else if(type == AM_ZLG118_RTC_CALLBACK_PERIOD) {
        /* �����Զ�������ʱ���趨,����ϵͳ��ʱ��ѡ�� */
        amhw_zlg118_rtc_period_int_time_set_enable(p_hw_rtc, AM_FALSE);

        /* �趨ʱ�� */
        amhw_zlg118_rtc_period_int_time_sel(p_hw_rtc,
                                            AMHW_ZLG118_RTC_PERIOD_INT_TIME_NO);

        p_dev->int_state &= ~AM_ZLG118_RTC_CALLBACK_PERIOD;
    } else {
        return -AM_EINVAL;
    }

    return AM_OK;
}

/**
 * \brief ��ʼ�� RTC
 */
am_rtc_handle_t am_zlg118_rtc_init (am_zlg118_rtc_dev_t           *p_dev,
                                    const am_zlg118_rtc_devinfo_t *p_devinfo)
{
    amhw_zlg118_rtc_t   *p_hw_rtc  = NULL;
    am_zlg118_clk_dev_t *p_clk_dev = NULL;

    if ((NULL == p_dev) || (NULL == p_devinfo)) {
        return NULL;
    }

    p_hw_rtc                = (amhw_zlg118_rtc_t *)p_devinfo->rtc_regbase;
    p_dev->rtc_serv.p_funcs = (struct am_rtc_drv_funcs *)&__g_rtc_drv_funcs;
    p_dev->rtc_serv.p_drv   = p_dev;
    p_dev->int_state        = 0;
    p_dev->rtc_continue     = AM_FALSE;
    p_dev->pfn_callback[0]  = NULL;
    p_dev->pfn_callback[1]  = NULL;
    p_dev->p_devinfo        = p_devinfo;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* RTC���� */
    amhw_zlg118_rtc_enable(p_hw_rtc, AM_FALSE);

    /* ��ȡ RTC ʱ��Դ��ʹ��ʱ�Ӳ�����Ԥ��Ƶֵ */
    switch (p_dev->p_devinfo->rtc_clk_sour){

    case AMHW_ZLG118_RTC_CLK_SRC_XTL_32768Hz:
        /* �ⲿ������������ѡ�� */
        amhw_zlg118_rcc_xtl_xtal_driver_set(AMHW_ZLG118_XTL_XTAL_DRIVER_DEFAULT);

        /* XTL�����񵴷��ȵĵ��� */
        amhw_zlg118_rcc_xtl_xtal_amplitude_set(
        AMHW_ZLG118_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

        /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
        amhw_zlg118_rcc_xtl_waittime_set(AMHW_ZLG118_XTL_WAITTIME_16384);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_xtl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_xtl_state_get() == AM_FALSE);
        break;

    case AMHW_ZLG118_RTC_CLK_SRC_RCL_32KHz:

        /* ����RCLʱ��Ƶ��У׼ֵ ��38.4KHz��*/
        amhw_zlg118_rcc_rcl_trim_set(*((uint16_t*)AMHW_ZLG118_RCl_FRE_32768Hz));

        amhw_zlg118_rcc_rcl_waittime_set(AMHW_ZLG118_RCL_WAITTIME_256);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_rcl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_rcl_state_get() == AM_FALSE);

        break;

    case AMHW_ZLG118_RTC_CLK_SRC_XTH_4MHz_DIV128:
        p_clk_dev = (am_zlg118_clk_dev_t *)am_zlg118_clk_devinfo_get();
        if(p_clk_dev->p_devinfo->xth_osc != 4000000) {
            return NULL;
        }

        /* �ⲿ������������ѡ�� */
        amhw_zlg118_rcc_xth_xtal_driver_set(AMHW_ZLG118_XTH_XTAL_DRIVER_DEFAULT);

        /* �ⲿ������Ƶ��ѡ�� */
        amhw_zlg118_rcc_xth_xtal_fre_set(AMHW_ZLG118_XTH_XTAL_FRE_4_6);

        /* �ⲿ����ʱ��XTH�ȶ�ʱ��ѡ�� */
        amhw_zlg118_rcc_xth_waittime_set(AMHW_ZLG118_XTH_WAITTIME_16384);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_xth_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_xth_state_get() == AM_FALSE);

        break;

    case AMHW_ZLG118_RTC_CLK_SRC_XTH_8MHz_DIV256:
        p_clk_dev = (am_zlg118_clk_dev_t *)am_zlg118_clk_devinfo_get();
        if(p_clk_dev->p_devinfo->xth_osc != 4000000) {
            return NULL;
        }

        /* �ⲿ������������ѡ�� */
        amhw_zlg118_rcc_xth_xtal_driver_set(AMHW_ZLG118_XTH_XTAL_DRIVER_DEFAULT);

        /* �ⲿ������Ƶ��ѡ�� */
        amhw_zlg118_rcc_xth_xtal_fre_set(AMHW_ZLG118_XTH_XTAL_FRE_6_12);

        /* �ⲿ����ʱ��XTH�ȶ�ʱ��ѡ�� */
        amhw_zlg118_rcc_xth_waittime_set(AMHW_ZLG118_XTH_WAITTIME_16384);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_xth_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_xth_state_get() == AM_FALSE);

        break;

    case AMHW_ZLG118_RTC_CLK_SRC_XTH_16MHz_DIV512:
        p_clk_dev = (am_zlg118_clk_dev_t *)am_zlg118_clk_devinfo_get();
        if(p_clk_dev->p_devinfo->xth_osc != 4000000) {
            return NULL;
        }

        /* �ⲿ������������ѡ�� */
        amhw_zlg118_rcc_xth_xtal_driver_set(AMHW_ZLG118_XTH_XTAL_DRIVER_DEFAULT);

        /* �ⲿ������Ƶ��ѡ�� */
        amhw_zlg118_rcc_xth_xtal_fre_set(AMHW_ZLG118_XTH_XTAL_FRE_12_20);

        /* �ⲿ����ʱ��XTH�ȶ�ʱ��ѡ�� */
        amhw_zlg118_rcc_xth_waittime_set(AMHW_ZLG118_XTH_WAITTIME_16384);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_xth_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_xth_state_get() == AM_FALSE);

        break;

    case AMHW_ZLG118_RTC_CLK_SRC_XTH_32MHz_DIV1024:

        break;

    default:
       break;
    }

    /* RTC ʱ��Դѡ�� */
    amhw_zlg118_rtc_clk_src_sel(p_hw_rtc, p_devinfo->rtc_clk_sour);

    /* �����Զ�������ʱ���趨,����ϵͳ��ʱ��ѡ�� */
    amhw_zlg118_rtc_period_int_time_set_enable(p_hw_rtc, AM_FALSE);

    /* �趨����ʱ�� */
    amhw_zlg118_rtc_period_int_time_sel(p_hw_rtc,
                                        AMHW_ZLG118_RTC_PERIOD_INT_TIME_NO);

    amhw_zlg118_rtc_time_mode_sel(p_hw_rtc, AMHW_ZLG118_RTC_TIME_MODE_24H);

    /* 1Hz���ʹ�� */
    if(p_devinfo->ctrl_1hz_out.enable == AM_TRUE) {

        amhw_zlg118_rtc_1hz_out_enable(p_hw_rtc, AM_TRUE);

        /* �����ڷ�Χ�ڣ�ֱ�ӹرղ������� */
        if(p_devinfo->ctrl_1hz_out.ppm < (-274.6) ||
           p_devinfo->ctrl_1hz_out.ppm > (212.6)) {
            amhw_zlg118_rtc_compensate_enable(p_hw_rtc, AM_FALSE);

        /* ���ڲ�����Χ�� */
        } else {

            /* ���ٲ���ʱ������ */
            if(p_devinfo->ctrl_1hz_out.adjust_enable == AM_TRUE) {
                amhw_zlg118_rtc_1hz_high_enable(p_hw_rtc, AM_TRUE);
                amhw_zlg118_rcc_rtcclk_adjust_set(
                    p_devinfo->ctrl_1hz_out.adjust_clk);
            } else {
                amhw_zlg118_rtc_1hz_high_enable(p_hw_rtc, AM_FALSE);
            }

            /* ʹ�ܲ������趨����ֵ */
            amhw_zlg118_rtc_compensate_set(p_hw_rtc,
                                           p_devinfo->ctrl_1hz_out.ppm);
            amhw_zlg118_rtc_compensate_enable(p_hw_rtc, AM_TRUE);
        }

    /* 1Hz������� */
    } else {
        amhw_zlg118_rtc_1hz_out_enable(p_hw_rtc, AM_FALSE);
    }

    /* �����ж� */
    am_int_connect(p_devinfo->rtc_inum, __rtc_sec_isr, p_dev);
    am_int_disable(p_devinfo->rtc_inum);

    /* RTCʹ�� */
    amhw_zlg118_rtc_enable(p_hw_rtc, AM_TRUE);

    p_dev->rtc_continue = AM_TRUE;

    return &p_dev->rtc_serv;
}

/**
 * \brief ���ʼ�� RTC
 */
void am_zlg118_rtc_deinit (am_rtc_handle_t handle)
{
    am_zlg118_rtc_dev_t *p_dev    = (am_zlg118_rtc_dev_t *)handle;
    amhw_zlg118_rtc_t   *p_hw_rtc = NULL;

    if ((NULL == p_dev) || (NULL == p_dev->p_devinfo)) {
        return;
    }

    p_hw_rtc = (amhw_zlg118_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    p_dev->pfn_callback[0]  = NULL;
    p_dev->pfn_callback[1]  = NULL;
    p_dev->p_devinfo        = NULL;
    p_dev->rtc_serv.p_funcs = NULL;
    p_dev->rtc_serv.p_drv   = NULL;
    p_dev                   = NULL;

    /* RTC���� */
    amhw_zlg118_rtc_enable(p_hw_rtc, AM_FALSE);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/** end of file */
