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
 * \brief RTC interfaces for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-16  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG118_RTC_H
#define __AMHW_ZLG118_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"

/**
 * \addtogroup amhw_zlg118_if_rtc
 * \copydoc amhw_zlg118_rtc.h
 * @{
 */

/**
 * \brief RTC �Ĵ����ṹ�嶨��
 */
typedef struct amhw_zlg118_rtc {
    __IO uint32_t cr0;       /**< \brief ���ƼĴ���0 */
    __IO uint32_t cr1;       /**< \brief ���ƼĴ���1 */
    __IO uint32_t sec;       /**< \brief ������Ĵ��� */
    __IO uint32_t min;       /**< \brief �ּ����Ĵ��� */
    __IO uint32_t hour;      /**< \brief ʱ�����Ĵ��� */
    __IO uint32_t week;      /**< \brief �ܼ����Ĵ��� */
    __IO uint32_t day;       /**< \brief �ռ����Ĵ��� */
    __IO uint32_t mon;       /**< \brief �¼����Ĵ��� */
    __IO uint32_t year;      /**< \brief ������Ĵ��� */
    __IO uint32_t almmin;    /**< \brief �����ӼĴ��� */
    __IO uint32_t almhour;   /**< \brief ʱ���ӼĴ��� */
    __IO uint32_t almweek;   /**< \brief �����ӼĴ��� */
    __IO uint32_t compen;    /**< \brief ʱ�������Ĵ��� */
    __IO uint32_t almsec;    /**< \brief �����ӼĴ��� */
} amhw_zlg118_rtc_t;

/**
 * \brief RTC�����ж�ѡ��
 */
typedef enum {
    AMHW_ZLG118_RTC_PERIOD_INT_TYPE_CUSTOM  = 0,    /* �û��Զ���ʱ�� */
    AMHW_ZLG118_RTC_PERIOD_INT_TYPE_SYSTEAM = 1,    /* ����涨����ѡ�� */
} amhw_zlg118_rtc_period_int_type_t;

/**
 * \brief RTC�����ж�ʱ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_RTC_PERIOD_INT_TIME_NO      = 0ul,    /* �����������ж� */
    AMHW_ZLG118_RTC_PERIOD_INT_TIME_0_5_SEC = 1ul,    /* 0.5�� */
    AMHW_ZLG118_RTC_PERIOD_INT_TIME_1_SEC   = 2ul,    /* 1�� */
    AMHW_ZLG118_RTC_PERIOD_INT_TIME_1_MIN   = 3ul,    /* 1���� */
    AMHW_ZLG118_RTC_PERIOD_INT_TIME_1_HOUR  = 4ul,    /* 1Сʱ */
    AMHW_ZLG118_RTC_PERIOD_INT_TIME_1_DAY   = 5ul,    /* 1�� */
    AMHW_ZLG118_RTC_PERIOD_INT_TIME_1_MON   = 6ul,    /* 1�� */
} amhw_zlg118_rtc_period_int_time_t;

/**
 * \brief PRDS RTC�����ж�ѡ��
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    amhw_zlg118_rtc_period_int_time_tö��ѡ��
 *
 * \note ����Ҫ�� START=1ʱд����������жϵ�ʱ���������������£�
 *          step1���� NVIC �йر� RTC �жϣ�
 *          step2�����������жϵ�ʱ������
 *          step3����� RTC �жϱ�־��
 *          step4��ʹ�� RTC �жϡ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_period_int_time_sel (
         amhw_zlg118_rtc_t                *p_hw_rtc,
         amhw_zlg118_rtc_period_int_time_t choice)
{
    p_hw_rtc->cr0 = (p_hw_rtc->cr0 & (~(0x7ul << 0))) |
                    (choice << 0);
}

/**
 * \brief PRDX �����ж�ʱ��ֵ����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] time     �����ж�ʱ��ֵ���ã�0.5 ~ 32s��
 *
 * \return AM_FALSE ��ʱ��������ô���
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_period_int_time_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                               float              time)
{
    uint8_t setvalue = 0;

    if(time > 32.0 || time < 0.5) {
        return AM_FALSE;
    }

    setvalue = (uint8_t)(time / 0.5 - 1.0);

    p_hw_rtc->cr0 = (p_hw_rtc->cr0 & (~(0x3f << 8))) |
                    (setvalue << 8);

    return AM_TRUE;
}

/**
 * \brief PRDX �����ж�ʱ��ֵ��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ��ȡ�������ж�ʱ��ֵ
 */
am_static_inline
float amhw_zlg118_rtc_period_int_time_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t setvalue = 0;
    float   getvalue = 0.0;

    setvalue = (p_hw_rtc->cr0 >> 8) & 0x3f;

    getvalue = (float)(setvalue + 1) * 0.5;

    return getvalue;
}

/**
 * \brief PRDSEL �Ƿ�ʹ�����õ������ж�ʱ��ֵ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata  AM_FALSE ��ʹ��amhw_zlg118_rtc_period_int_time_sel���õ��ж�ʱ��
 *                   AM_TRUE  ��ʹ��amhw_zlg118_rtc_period_int_time_set���õ��ж�ʱ��
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_period_int_time_set_enable (amhw_zlg118_rtc_t *p_hw_rtc,
                                                 am_bool_t          stata)
{
    if(stata == AM_TRUE) {
        p_hw_rtc->cr0 |= (1ul << 14);
    } else {
        p_hw_rtc->cr0 &= ~(1ul << 14);
    }
}

/**
 * \brief START RTC������ֹͣ/����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    AM_FALSE ��ֹͣ RTC������
 *                     AM_TRUE  ��ʹ�� RTC������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_enable (amhw_zlg118_rtc_t *p_hw_rtc,
                             am_bool_t          stata)
{
    if(stata == AM_TRUE) {
        p_hw_rtc->cr0 |= (1ul << 7);
    } else {
        p_hw_rtc->cr0 &= ~(1ul << 7);
    }
}

/**
 * \brief HZ1SEL �߾���1Hzʹ��/����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    AM_FALSE ����ͨ����1Hz
 *                     AM_TRUE  ���߾���1Hz
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_1hz_high_enable (amhw_zlg118_rtc_t *p_hw_rtc,
                                      am_bool_t          stata)
{
    if(stata == AM_TRUE) {
        p_hw_rtc->cr0 |= (1ul << 6);
    } else {
        p_hw_rtc->cr0 &= ~(1ul << 6);
    }
}

/**
 * \brief HZ1OE 1Hz���ʹ��/����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    AM_FALSE ��1Hz�������
 *                     AM_TRUE  ��1Hz���ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_1hz_out_enable (amhw_zlg118_rtc_t *p_hw_rtc,
                                     am_bool_t          stata)
{
    if(stata == AM_TRUE) {
        p_hw_rtc->cr0 |= (1ul << 5);
    } else {
        p_hw_rtc->cr0 &= ~(1ul << 5);
    }
}

/**
 * \brief RTCСʱ��ѡ��ö��
 */
typedef enum {
    AMHW_ZLG118_RTC_TIME_MODE_12h = 0ul,    /* 12Сʱ�� */
    AMHW_ZLG118_RTC_TIME_MODE_24H = 1ul,    /* 24Сʱ�� */
} amhw_zlg118_rtc_time_mode_t;

/**
 * \brief AMPM Сʱ��ѡ��
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    amhw_zlg118_rtc_time_mode_tö��ѡ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_time_mode_sel (amhw_zlg118_rtc_t          *p_hw_rtc,
                                    amhw_zlg118_rtc_time_mode_t stata)
{
    p_hw_rtc->cr0 = (p_hw_rtc->cr0 & (~(0x1ul << 3))) |
                    (stata << 3);
}

/**
 * \brief AMPM Сʱ�ƻ�ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return amhw_zlg118_rtc_time_mode_tö��
 */
am_static_inline
amhw_zlg118_rtc_time_mode_t
amhw_zlg118_rtc_time_mode_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    return (amhw_zlg118_rtc_time_mode_t)((p_hw_rtc->cr0 >> 3) & 1ul);
}

/**
 * \brief RTCʱ��ѡ��ö��
 */
typedef enum {
    AMHW_ZLG118_RTC_CLK_SRC_XTL_32768Hz       = 0,  /* XTL 32.768k */
    AMHW_ZLG118_RTC_CLK_SRC_RCL_32KHz         = 2,  /* RCL 32k */
    AMHW_ZLG118_RTC_CLK_SRC_XTH_4MHz_DIV128   = 4,  /* XTH 4M */
    AMHW_ZLG118_RTC_CLK_SRC_XTH_8MHz_DIV256   = 5,  /* XTH 4M */
    AMHW_ZLG118_RTC_CLK_SRC_XTH_16MHz_DIV512  = 6,  /* XTH 4M */
    AMHW_ZLG118_RTC_CLK_SRC_XTH_32MHz_DIV1024 = 7,  /* XTH 4M */
} amhw_zlg118_rtc_clk_src_t;

/**
 * \brief CKSEL RTCʱ��Դ����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    amhw_zlg118_rtc_clk_src_tö��ѡ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_clk_src_sel (amhw_zlg118_rtc_t        *p_hw_rtc,
                                  amhw_zlg118_rtc_clk_src_t src)
{
    p_hw_rtc->cr1 = (p_hw_rtc->cr1 & (~(0x7ul << 8))) |
                    (src << 8);
}

/**
 * \brief CKSEL RTCʱ��Դ��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return amhw_zlg118_rtc_clk_src_tö��
 */
am_static_inline
amhw_zlg118_rtc_clk_src_t
amhw_zlg118_rtc_clk_src_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    return (amhw_zlg118_rtc_clk_src_t)((p_hw_rtc->cr1 >> 8) & 0x7ul);
}

/**
 * \brief ALMEN ����ʹ��/����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    AM_FALSE �����ӽ���
 *                     AM_TRUE  ������ʹ��
 *
 * \note �� START=1�������������в��� ALMIE=1�ж���ɵ������ʹ��ALMEN ʱ��Ϊ��ֹ����
 *       �뽫ϵͳ�жϹرա�ʹ�ܺ��뽫 ALMF��־λ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_alarm_clock_enable (amhw_zlg118_rtc_t *p_hw_rtc,
                                         am_bool_t          stata)
{
    if(stata == AM_TRUE) {
        p_hw_rtc->cr1 |= (1ul << 7);
    } else {
        p_hw_rtc->cr1 &= ~(1ul << 7);
    }
}

/**
 * \brief ALMIE �����ж�ʹ��/����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    AM_FALSE �������жϽ���
 *                     AM_TRUE  �������ж�ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_alarm_clock_int_enable (amhw_zlg118_rtc_t *p_hw_rtc,
                                             am_bool_t          stata)
{
    if(stata == AM_TRUE) {
        p_hw_rtc->cr1 |= (1ul << 6);
    } else {
        p_hw_rtc->cr1 &= ~(1ul << 6);
    }
}

/**
 * \brief ALMF �����жϱ�־��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return AM_FALSE ����־��Ч
 *         AM_TRUE  ����־��Ч
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_alarm_clock_int_flag_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    return (am_bool_t)((p_hw_rtc->cr1 >> 4) & 1ul);
}

/**
 * \brief ALMF �����жϱ�־���
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_alarm_clock_int_flag_clr (amhw_zlg118_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr1 &= (~(1ul << 4));
}

/**
 * \brief PRDF �����жϱ�־��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return AM_FALSE ����־��Ч
 *         AM_TRUE  ����־��Ч
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_period_int_flag_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    return (am_bool_t)((p_hw_rtc->cr1 >> 3) & 1ul);
}

/**
 * \brief PRDF �����жϱ�־���
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_period_int_flag_clr (amhw_zlg118_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr1 &= (~(1ul << 3));
}

/**
 * \brief WAITF д��/����״̬״̬��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \note WAITλ�趨�Ƿ���Ч��־����д��/����ǰ��ȷ�ϸ�λ�Ƿ�Ϊ��1�������������У�
 *       �� WAIT λ�塱0����ȴ�д����ɺ��λ���塱0��
 *
 * \return AM_FALSE ����д��/����״̬
 *         AM_TRUE  ��д��/����״̬
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_writeread_flag_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    return ((p_hw_rtc->cr1 >> 1) & 1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief RTC����ģʽѡ��
 */
typedef enum {
    AMHW_ZLG118_RTC_MODE_COUNTER   = 0ul,    /* ����ֵģʽ */
    AMHW_ZLG118_RTC_MODE_WRITEREAD = 1ul,    /* ��дģʽ */
} amhw_zlg118_rtc_mode_t;

/**
 * \brief WAIT RTC����ģʽѡ��
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata    amhw_zlg118_rtc_mode_tö��ѡ��
 *
 * \note ��д��/����ʱ�뽫��λ�á�1�������ڼ���������������������1���ʱ�������д��/��������������λ�塰0����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_mode_sel (amhw_zlg118_rtc_t     *p_hw_rtc,
                               amhw_zlg118_rtc_mode_t mode)
{
    p_hw_rtc->cr1 = ((p_hw_rtc->cr1) & (~(0x1ul << 0))) |
                    (mode << 0);
}

/**
 * \brief SECH��SECL �����������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    �����ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_sec_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                   uint8_t            value)
{
    if(value > 59) {
        return AM_FALSE;
    }

    p_hw_rtc->sec = (p_hw_rtc->sec & (~0x7ful)) | ((value / 10) << 4);
    p_hw_rtc->sec = p_hw_rtc->sec | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief SECH��SECL ���������ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_sec_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->sec >> 4) & 0x7ul);

    value = value * 10 + ((p_hw_rtc->sec >> 0) & 0xful);

    return value;
}

/**
 * \brief MINH��MINL �ּ���������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    �ּ���ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_min_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                   uint8_t            value)
{
    if(value > 59) {
        return AM_FALSE;
    }

    p_hw_rtc->min = (p_hw_rtc->min & (~0x7ful)) | ((value / 10) << 4);
    p_hw_rtc->min = p_hw_rtc->min | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief MINH��MINL �ּ�������ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_min_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->min >> 4) & 0x7ul);

    value = value * 10 + ((p_hw_rtc->min >> 0) & 0xful);

    return value;
}

/**
 * \brief HOURH��HOURL ʱ����������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    ʱ����ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_hour_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                    uint8_t            value)
{
    if(value > 32) {
        return AM_FALSE;
    }

    p_hw_rtc->hour = (p_hw_rtc->hour & (~0x3ful)) | ((value / 10) << 4);
    p_hw_rtc->hour = p_hw_rtc->hour | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief HOURH��HOURL ʱ��������ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ʱ��ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_hour_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->hour >> 4) & 0x3ul);

    value = value * 10 + ((p_hw_rtc->hour >> 0) & 0xful);

    return value;
}

/**
 * \brief DAYH��DAYL �ռ���������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    �ռ���ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_day_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                   uint8_t            value)
{
    if(value > 31) {
        return AM_FALSE;
    }

    p_hw_rtc->day = (p_hw_rtc->day & (~0x3ful)) | ((value / 10) << 4);
    p_hw_rtc->day = p_hw_rtc->day | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief DAYH��DAYL �ռ�������ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_day_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->day >> 4) & 0x3ul);

    value = value * 10 + ((p_hw_rtc->day >> 0) & 0xful);

    return value;
}

/**
 * \brief WEEK �ܼ���������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    �ܼ���ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_week_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                    uint8_t            value)
{
    if(value > 6) {
        return AM_FALSE;
    }

    p_hw_rtc->week = (p_hw_rtc->week & (~(0x7ul << 0))) |
                     (value << 0);

    return AM_TRUE;
}

/**
 * \brief WEEK �ܼ�������ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_week_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    return ((p_hw_rtc->week >> 0) & 0x7ul);
}

/**
 * \brief MON �¼���������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    �¼���ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_mon_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                   uint8_t            value)
{
    if(value > 12) {
        return AM_FALSE;
    }

    p_hw_rtc->mon = (p_hw_rtc->mon & (~0x1eul)) | ((value / 10) << 4);
    p_hw_rtc->mon = (p_hw_rtc->mon & (~(0xful << 0))) | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief MON �¼�������ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_mon_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->mon >> 4) & 0x1ul);

    value = value * 10 + ((p_hw_rtc->mon >> 0) & 0xful);

    return value;
}

/**
 * \brief YEARH��YEARL �����������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    �����ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_year_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                    uint8_t            value)
{
    if(value > 99) {
        return AM_FALSE;
    }

    p_hw_rtc->year = (p_hw_rtc->year & (~0xfful)) | ((value / 10) << 4);
    p_hw_rtc->year = p_hw_rtc->year | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief YEARH��YEARL ���������ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_year_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->year >> 4) & 0xful);

    value = value * 10 + ((p_hw_rtc->year >> 0) & 0xful);

    return value;
}

/**
 * \brief ALMSECH��ALMSECL ��������ֵ����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    ��������ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_sec_alarm_clock_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                               uint8_t            value)
{
    if(value > 59) {
        return AM_FALSE;
    }

    p_hw_rtc->almsec = (p_hw_rtc->almsec & (~0x7ful)) | ((value / 10) << 4);
    p_hw_rtc->almsec = p_hw_rtc->almsec | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief ALMSECH��ALMSECL ��������ֵ��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ��������ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_sec_alarm_clock_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->almsec >> 4) & 0x7ul);

    value = value * 10 + ((p_hw_rtc->almsec >> 0) & 0xful);

    return value;
}

/**
 * \brief ALMMINH��ALMMINL ��������ֵ����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    ��������ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_min_alarm_clock_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                               uint8_t            value)
{
    if(value > 59) {
        return AM_FALSE;
    }

    p_hw_rtc->almmin = (p_hw_rtc->almmin & (~0x7ful)) | ((value / 10) << 4);
    p_hw_rtc->almmin = p_hw_rtc->almmin | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief ALMMINH��ALMMINL ��������ֵ��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ��������ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_min_alarm_clock_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->almmin >> 4) & 0x7ul);

    value = value * 10 + ((p_hw_rtc->almmin >> 0) & 0xful);

    return value;
}

/**
 * \brief ALMHOURH��ALMHOURL ʱ������ֵ����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    ʱ������ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_hour_alarm_clock_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                                uint8_t            value)
{
    if(value > 32) {
        return AM_FALSE;
    }

    p_hw_rtc->almhour = (p_hw_rtc->almhour & (~0x3ful)) | ((value / 10) << 4);

    p_hw_rtc->almhour = p_hw_rtc->almhour | ((value % 10) << 0);

    return AM_TRUE;
}

/**
 * \brief ALMHOURH��ALMHOURL ʱ������ֵ��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ʱ������ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_hour_alarm_clock_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;

    value = ((p_hw_rtc->almhour >> 4) & 0x3ul);

    value = value * 10 + ((p_hw_rtc->almhour >> 0) & 0xful);

    return value;
}


/**
 * \brief ALMWEEK ��������ֵ����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    ��������ֵ
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_week_alarm_clock_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                                uint8_t            value)
{
    if(value > 6) {
        return AM_FALSE;
    }

    p_hw_rtc->almweek = (p_hw_rtc->almweek & (~(0x7ful << 0))) |
                        (1ul << value);

    return AM_TRUE;
}

/**
 * \brief ALMWEEK ��������ֵ��ȡ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 *
 * \return ��������ֵ
 */
am_static_inline
uint8_t amhw_zlg118_rtc_week_alarm_clock_get (amhw_zlg118_rtc_t *p_hw_rtc)
{
    uint8_t value = 0;
    uint8_t i     = 0;

    value = (p_hw_rtc->almweek >> 0) & 0x7ful;

    for(i = 0; i < 7; i++) {
        value = value >> i;
        if((value & 1) == 1) {
            return i;
        }
    }

    return 255;
}

/**
 * \brief CR ʱ����������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] value    ����ֵ��-274.6 ~ 212.6��ppm
 *
 * \return AM_FALSE : ����ʧ�ܣ���������
 *         AM_TRUE  �� ���óɹ�
 */
am_static_inline
am_bool_t amhw_zlg118_rtc_compensate_set (amhw_zlg118_rtc_t *p_hw_rtc,
                                          float              value)
{
    uint8_t  temp_int;
    float    temp = 0.0;
    char     i    = 0;
    uint16_t data = 0;

    if(value < (-274.6) || value > (212.6)) {
        return AM_FALSE;
    }

    /* ���㲹��Ŀ��ֵ[ppm]*(2^15)/(10^6) */
    temp = ((value * (1ul << 15)) / 1000000.0);

    if(temp < 0.0) {
        temp = -temp;
    }

    /* �õ��������� */
    temp_int = (uint8_t)temp;

    /* �õ�С������ */
    temp = temp - temp_int;

    /* �õ��趨ֵ���������֣���Ԥ����5λ��С������*/
    data = (temp_int << 5);

    /* ��С������ת���ɶ����ƣ�ͬʱǶ�뵽�趨ֵ�ĵ�5λ */
    for(i = 4; i > 0; i--) {
        temp = temp * 2;
        data = data | ((uint8_t)temp << i);
    }

    /* ����Ǹ�����ȡ2�Ĳ��� */
    if(value < 0.0) {
        data = ~data;
        data = data + 1;
    }

    /* �õ����յ��趨���� */
    data = data + (1ul << 5);

    p_hw_rtc->compen = (p_hw_rtc->compen & (~(0x1fful << 0))) |
                       ((data & 0x1fful) << 0);

    return AM_TRUE;
}

/**
 * \brief EN ʱ������ʹ��
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg118_rtc_t�ṹ��ָ��
 * \param[in] stata  AM_FALSE ����ֹʱ������
 *                   AM_TRUE  ��ʹ��ʱ������
 * \return ��
 */
am_static_inline
void amhw_zlg118_rtc_compensate_enable (amhw_zlg118_rtc_t *p_hw_rtc,
                                        am_bool_t          stata)
{
    if(stata == AM_TRUE) {
        p_hw_rtc->compen |= (1ul << 15);
    } else {
        p_hw_rtc->compen &= ~(1ul << 15);
    }
}
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZLG118_RTC_H */

/* end of file */
