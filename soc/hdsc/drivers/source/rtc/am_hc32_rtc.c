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
 * - 1.11 20-04-23 zcb, Add RTC interrupt management interface
 * - 1.10 20-04-17 zcb, Adapt standard drive and delete interfaces that
 *                      are not related to standards
 * - 1.00 19-10-16  zp, first implementation
 * \endinternal
 */

#include "am_int.h"
#include "am_time.h"
#include "am_hc32.h"
#include "am_hc32_rtc.h"
#include "hw/amhw_hc32_rtc.h"

/** \brief RTC ���жϴ��� */
am_local void __rtc_irq_proc (void *p_arg);

/** \brief ���õ�ǰ��ϸ��ʱ�� */
am_local int  __rtc_time_set (void *p_drv, am_tm_t *p_tm);

/** \brief ��ȡ��ǰ��ϸ��ʱ�� */
am_local int  __rtc_time_get (void *p_drv, am_tm_t *p_tm);

/******************************************************************************/

/** \brief ���� RTC ��׼�ӿ���Ҫ�ĺ��� */
am_local am_const struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __rtc_time_set,
    __rtc_time_get,
};

/******************************************************************************/

/**
 * \brief ��ȡ��ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_get (void *p_drv, am_tm_t *p_tm)
{
    am_hc32_rtc_dev_t *p_dev = (am_hc32_rtc_dev_t *)p_drv;
    amhw_hc32_rtc_t   *p_rtc = (amhw_hc32_rtc_t  *)p_dev->p_devinfo->regbase;

    if ((NULL == p_tm) || (NULL == p_tm)) {
        return -AM_EINVAL;
    }

    /* ��дģʽ */
    amhw_hc32_rtc_mode_sel(p_rtc, AMHW_HC32_RTC_MODE_WRITEREAD);
    while(amhw_hc32_rtc_writeread_flag_get(p_rtc) == AM_FALSE);

    p_tm->tm_sec  = amhw_hc32_rtc_sec_get(p_rtc);
    p_tm->tm_min  = amhw_hc32_rtc_min_get(p_rtc);
    p_tm->tm_hour = amhw_hc32_rtc_hour_get(p_rtc);
    p_tm->tm_mday = amhw_hc32_rtc_day_get(p_rtc);
    p_tm->tm_wday = amhw_hc32_rtc_week_get(p_rtc);
    p_tm->tm_mon  = amhw_hc32_rtc_mon_get(p_rtc) - 1;
    p_tm->tm_year = amhw_hc32_rtc_year_get(p_rtc) +
        (p_dev->p_devinfo->year_epoch - 1900);

    /* ����ֵģʽ */
    amhw_hc32_rtc_mode_sel(p_rtc, AMHW_HC32_RTC_MODE_COUNTER);
    while(amhw_hc32_rtc_writeread_flag_get(p_rtc) == AM_TRUE);

    return AM_OK;
}

/**
 * \brief ���õ�ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_set (void *p_drv, am_tm_t *p_tm)
{
    am_hc32_rtc_dev_t *p_dev = (am_hc32_rtc_dev_t *)p_drv;
    amhw_hc32_rtc_t   *p_rtc = (amhw_hc32_rtc_t  *)p_dev->p_devinfo->regbase;

    if ((NULL == p_tm) || (NULL == p_tm)) {
        return -AM_EINVAL;
    }

    /* ��дģʽ */
    amhw_hc32_rtc_mode_sel(p_rtc, AMHW_HC32_RTC_MODE_WRITEREAD);
    while(amhw_hc32_rtc_writeread_flag_get(p_rtc) == AM_FALSE);

    amhw_hc32_rtc_sec_set(p_rtc, p_tm->tm_sec);
    amhw_hc32_rtc_min_set(p_rtc, p_tm->tm_min);
    amhw_hc32_rtc_hour_set(p_rtc, p_tm->tm_hour);
    amhw_hc32_rtc_day_set(p_rtc, p_tm->tm_mday);
    amhw_hc32_rtc_week_set(p_rtc, p_tm->tm_wday);
    amhw_hc32_rtc_mon_set(p_rtc, p_tm->tm_mon + 1);
    amhw_hc32_rtc_year_set(
        p_rtc,
        p_tm->tm_year - (p_dev->p_devinfo->year_epoch - 1900));

    /* ����ֵģʽ */
    amhw_hc32_rtc_mode_sel(p_rtc, AMHW_HC32_RTC_MODE_COUNTER);
    while(amhw_hc32_rtc_writeread_flag_get(p_rtc) == AM_TRUE);

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief ��ʼ�� RTC
 */
am_rtc_handle_t am_hc32_rtc_init (am_hc32_rtc_dev_t           *p_dev,
                                    const am_hc32_rtc_devinfo_t *p_devinfo)
{
    amhw_hc32_rtc_t   *p_hw_rtc  = NULL;

    if ((NULL == p_dev) || (NULL == p_devinfo)) {
        return NULL;
    }

    p_hw_rtc                = (amhw_hc32_rtc_t *)p_devinfo->regbase;
    p_dev->p_devinfo        = p_devinfo;

    p_dev->rtc_serv.p_funcs = (struct am_rtc_drv_funcs *)&__g_rtc_drv_funcs;
    p_dev->rtc_serv.p_drv   = p_dev;

    p_dev->pfn_callback[0]  = NULL;
    p_dev->pfn_callback[1]  = NULL;

    /* ƽ̨��ʼ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* RTC���� */
    amhw_hc32_rtc_enable(p_hw_rtc, AM_FALSE);

    /* �����Զ�������ʱ���趨,����ϵͳ��ʱ��ѡ�� */
    amhw_hc32_rtc_period_int_time_set_enable(p_hw_rtc, AM_FALSE);

    /* ���������ж� */
    amhw_hc32_rtc_period_int_time_sel(
        p_hw_rtc,
        AMHW_HC32_RTC_PERIOD_INT_TIME_NO);

    /* ����Ϊ24Сʱ�� */
    amhw_hc32_rtc_time_mode_sel(p_hw_rtc, AMHW_HC32_RTC_TIME_MODE_24H);

    /* 1Hz������� */
    amhw_hc32_rtc_1hz_out_enable(p_hw_rtc, AM_FALSE);

    /* RTCʹ�� */
    amhw_hc32_rtc_enable(p_hw_rtc, AM_TRUE);

    /* �����ж� */
    am_int_connect(p_devinfo->inum, __rtc_irq_proc, p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &p_dev->rtc_serv;
}

/**
 * \brief ���ʼ�� RTC
 */
void am_hc32_rtc_deinit (am_rtc_handle_t handle)
{
    am_hc32_rtc_dev_t *p_dev    = (am_hc32_rtc_dev_t *)handle;
    amhw_hc32_rtc_t   *p_hw_rtc = NULL;

    if ((NULL == p_dev) || (NULL == p_dev->p_devinfo)) {
        return;
    }

    p_hw_rtc = (amhw_hc32_rtc_t *)p_dev->p_devinfo->regbase;

    p_dev->pfn_callback[0]  = NULL;
    p_dev->pfn_callback[1]  = NULL;
    p_dev->p_devinfo        = NULL;
    p_dev->rtc_serv.p_funcs = NULL;
    p_dev->rtc_serv.p_drv   = NULL;
    p_dev                   = NULL;

    /* RTC���� */
    amhw_hc32_rtc_enable(p_hw_rtc, AM_FALSE);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/******************************************************************************/

/**
 * \brief RTC ���жϴ���
 */
am_local void __rtc_irq_proc (void *p_arg)
{
    am_hc32_rtc_dev_t *p_dev = (am_hc32_rtc_dev_t *)p_arg;
    amhw_hc32_rtc_t   *p_rtc = (amhw_hc32_rtc_t *)p_dev->p_devinfo->regbase;

    /* �����ж� */
    if (amhw_hc32_rtc_period_int_flag_get(p_rtc) == AM_TRUE) {
        amhw_hc32_rtc_period_int_flag_clr(p_rtc);
        if (p_dev->pfn_callback[AM_HC32_RTC_INT_PERIOD]) {
            p_dev->pfn_callback[AM_HC32_RTC_INT_PERIOD](
                p_dev->p_arg[AM_HC32_RTC_INT_PERIOD]);
        }
    }

    /* �����ж� */
    if (amhw_hc32_rtc_alarm_clock_int_flag_get(p_rtc) == AM_TRUE) {
        amhw_hc32_rtc_alarm_clock_int_flag_clr(p_rtc);
        if (p_dev->pfn_callback[AM_HC32_RTC_INT_ALARM]) {
            p_dev->pfn_callback[AM_HC32_RTC_INT_ALARM](
                p_dev->p_arg[AM_HC32_RTC_INT_ALARM]);
        }
    }
}

/**
 * \brief ���� RTC �ж��������ûص�����
 */
am_err_t am_hc32_rtc_int_connect (am_rtc_handle_t   handle,
                                  uint8_t           type,
                                  am_pfnvoid_t      pfn_callback,
                                  void             *p_arg)
{
    am_hc32_rtc_dev_t *p_dev = (am_hc32_rtc_dev_t *)handle;
    int                key;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    if (type >= AM_HC32_RTC_INT_CNT) {
        return -AM_EINVAL;
    }

    key = am_int_cpu_lock();

    p_dev->pfn_callback[type] = pfn_callback;
    p_dev->p_arg[type]        = p_arg;

    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief RTC �жϽ���
 */
am_err_t am_hc32_rtc_int_enable  (am_rtc_handle_t   handle,
                                  uint8_t           type)
{
    am_hc32_rtc_dev_t *p_dev = (am_hc32_rtc_dev_t *)handle;
    amhw_hc32_rtc_t   *p_rtc = (amhw_hc32_rtc_t *)p_dev->p_devinfo->regbase;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    if (type >= AM_HC32_RTC_INT_CNT) {
        return -AM_EINVAL;
    }

    /* �����ж�ʹ�� */
    if (type == AM_HC32_RTC_INT_ALARM) {
        amhw_hc32_rtc_alarm_clock_int_enable(p_rtc, AM_TRUE);
    }

    /* �趨ʱ����൱������ */
    return AM_OK;
}

/**
 * \brief RTC �ж�ʹ��
 */
am_err_t am_hc32_rtc_int_disable (am_rtc_handle_t   handle,
                                  uint8_t           type)
{
    am_hc32_rtc_dev_t *p_dev = (am_hc32_rtc_dev_t *)handle;
    amhw_hc32_rtc_t   *p_rtc = (amhw_hc32_rtc_t *)p_dev->p_devinfo->regbase;
    int                key;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    if (type >= AM_HC32_RTC_INT_CNT) {
        return -AM_EINVAL;
    }

    key = am_int_cpu_lock();

    /* �����жϽ��� */
    if (type == AM_HC32_RTC_INT_ALARM) {
        amhw_hc32_rtc_alarm_clock_int_enable(p_rtc, AM_FALSE);
        amhw_hc32_rtc_alarm_clock_int_flag_clr(p_rtc);
    }

    /* �����жϽ��� */
    if (type == AM_HC32_RTC_INT_PERIOD) {

        /* �����Զ�������ʱ���趨,����ϵͳ��ʱ��ѡ�� */
        amhw_hc32_rtc_period_int_time_set_enable(p_rtc, AM_FALSE);

        /* ���������ж� */
        amhw_hc32_rtc_period_int_time_sel(
            p_rtc,
            AMHW_HC32_RTC_PERIOD_INT_TIME_NO);

        amhw_hc32_rtc_period_int_flag_clr(p_rtc);
    }

    am_int_cpu_unlock(key);

    return AM_OK;
}

/** end of file */
