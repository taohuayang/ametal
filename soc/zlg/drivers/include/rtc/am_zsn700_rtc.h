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
 * \brief RTC drivers for standard interface
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-13  yrz, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_RTC_H
#define __AM_ZSN700_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_rtc.h"
#include "hw/amhw_zsn700_rtc.h"
#include "hw/amhw_zsn700_rcc.h"

/**
 * \addtogroup am_zsn700_if_rtc
 * \copydoc am_zsn700_rtc.h
 * @{
 */

#define  AM_ZSN700_RTC_CALLBACK_PERIOD  (1 << 0) /**< \brief RTC�����жϻص�������� */
#define  AM_ZSN700_RTC_CALLBACK_ALARM   (1 << 1) /**< \brief RTC�����жϻص�������� */

/**
 * \brief ZSN700 1Hz������ƽṹ��
 */
typedef struct {
    am_bool_t enable;                 /* �Ƿ�ʹ��1Hz�������
                                       * AM_TRUE �� ʹ�� �����Ķ������������õ�ע�ͣ�
                                       * AM_FALSE�� ���ܣ���������������Ч��
                                       */
    float     ppm;                    /* ����ֵ��-274.6 ~ 212.6��ppm����Χ�����ر�*/
    am_bool_t adjust_enable;          /* ��ppm���ڷ�Χ��ʱ������������������£���
                                       * ѡ���Ƿ�������ʱ����Ϊ����ʱ��
                                       *
                                       * AM_TRUE �� ��������ʱ����Ϊ����ʱ��
                                       * AM_FALSE�� �رո���ʱ����Ϊ����ʱ��
                                       */
    amhw_zsn700_rtcclk_adjust adjust_clk; /* ����ʱ�Ӳ���ʱ��ѡ�� �������PCLKƵ����ͬ  */
} am_zsn700_rtc_1hz_out_t;


/**
 * \brief ZSN700 RTC �豸��Ϣ
 */
typedef struct am_zsn700_rtc_devinfo {
    uint32_t                  rtc_regbase;           /**< \brief RTC �Ĵ�������ַ */
    amhw_zsn700_rtc_clk_src_t rtc_clk_sour;          /**< \brief RTC ʱ��Դ */
    int                       rtc_inum;              /**< \brief RTC �жϺ� */
    am_zsn700_rtc_1hz_out_t   ctrl_1hz_out;
    void                    (*pfn_plfm_init)(void);  /**< \brief ƽ̨��ʼ������ */
    void                    (*pfn_plfm_deinit)(void);/**< \brief ƽ̨���ʼ������ */
} am_zsn700_rtc_devinfo_t;

/**
 * \brief ZSN700 RTC �豸
 */
typedef struct am_zsn700_rtc_dev {
    am_rtc_serv_t                  rtc_serv;        /**< \brief RTC ��׼���� */
    uint8_t                        int_state;       /**< \brief �ж�ʹ�ܱ�־ */
    am_bool_t                      rtc_continue;    /**< \brief RTC�Ƿ�������� */
    am_pfnvoid_t                   pfn_callback[2]; /**< \brief �ص����� */
    void                          *p_arg[2];        /**< \brief �ص��������� */
    const am_zsn700_rtc_devinfo_t *p_devinfo;       /**< \brief RTC�豸��Ϣ */
}am_zsn700_rtc_dev_t;

/**
 * \brief ��ȡ RTC ������ֵ
 *
 * \param[in]  handle RTC ��׼����������
 * \param[in]  handle RTC ��׼����������
 * \param[in] *sec    �루0-59��
 * \param[in] *min    �֣�0-59��
 * \param[in] *hour   ʱ��0-23��
 * \param[in] *mday   ÿ�µĵڼ��죨0-29,0-28,0-30,0-31��
 * \param[in] *wday   һ�ܵĵڼ��죨0-6����Ӧ����-������
 * \param[in] *mon    �£�1-12��
 * \param[in] *year   �꣨0-99��
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zsn700_rtc_cnt_get (am_rtc_handle_t handle,
                                uint8_t        *sec,
                                uint8_t        *min,
                                uint8_t        *hour,
                                uint8_t        *mday,
                                uint8_t        *wday,
                                uint8_t        *mon,
                                uint8_t        *year);

/**
 * \brief ���� RTC ������ֵ
 *
 * \param[in] handle RTC ��׼����������
 * \param[in] sec    �루0-59��
 * \param[in] min    �֣�0-59��
 * \param[in] hour   ʱ��0-23��
 * \param[in] mday   ÿ�µĵڼ��죨0-29,0-28,0-30,0-31��
 * \param[in] wday   һ�ܵĵڼ��죨0-6����Ӧ����-������
 * \param[in] mon    �£�1-12��
 * \param[in] year   �꣨0-99��
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zsn700_rtc_cnt_set (am_rtc_handle_t handle,
                                uint8_t         sec,
                                uint8_t         min,
                                uint8_t         hour,
                                uint8_t         mday,
                                uint8_t         wday,
                                uint8_t         mon,
                                uint8_t         year);

/**
 * \brief ���� RTC �жϻص�
 *
 * \param[in] handle       RTC ��׼����������
 * \param[in] type         �ж����ͣ���ѡ AM_ZSN700_RTC_CALLBACK_SECOND
 *                                   AM_ZSN700_RTC_CALLBACK_PERIOD
 * \param[in] pfn_callback �ص�����
 * \param[in] p_arg        �ص���������
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zsn700_rtc_callback_set (am_rtc_handle_t handle,
                                     uint8_t         type,
                                     am_pfnvoid_t    pfn_callback,
                                     void           *p_arg);

/**
 * \brief RTC�����ж�ʹ��
 *
 * \param[in] handle RTC��׼����������
 * \param[in] type   �����ж����ͣ���ö�ٶ���amhw_zsn700_rtc_period_int_type_t
 * \param[in] set_s  ��������Ϊϵͳ����ʱ�������������жϲ���ʱ��amhw_zsn700_rtc_period_int_time_t
 * \param[in] set_c  ��������Ϊ�Զ���ʱ�������������жϲ���ʱ�䣨0.5 ~ 32s��
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zsn700_rtc_period_int_enable(
              am_rtc_handle_t                   handle,
              amhw_zsn700_rtc_period_int_type_t type,
              amhw_zsn700_rtc_period_int_time_t set_s,
              float                             set_c);

/**
 * \brief RTC�����ж�ʹ��
 *
 * \param[in] handle RTC��׼����������
 * \param[in] sec    ����ʱ��-�루0-59��
 * \param[in] min    ����ʱ��-�֣�0-59��
 * \param[in] hour   ����ʱ��-ʱ��0-59��
 * \param[in] wday   ����ʱ��-�ܼ���0-6����Ӧ����-������
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zsn700_rtc_alarm_clock_int_enable(am_rtc_handle_t handle,
                                              uint8_t         sec,
                                              uint8_t         min,
                                              uint8_t         hour,
                                              uint8_t         wday);

/**
 * \brief RTC �ж�ʧ��
 *
 * \param[in] handle RTC ��׼����������
 * \param[in] type   �ж����ͣ���ѡ AM_ZSN700_RTC_CALLBACK_PERIOD
 *                             AM_ZSN700_RTC_CALLBACK_ALARM
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zsn700_rtc_int_disable (am_rtc_handle_t handle,
                                    uint8_t         type);

/**
 * \brief ��ʼ�� RTC
 *
 * \param[in] p_dev     ָ�� RTC �豸��ָ��
 * \param[in] p_devinfo ָ�� RTC �豸��Ϣ��ָ��
 *
 * \return RTC ��׼���������������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_zsn700_rtc_init (am_zsn700_rtc_dev_t           *p_dev,
                                    const am_zsn700_rtc_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ�� RTC
 *
 * \param[in] handle ʹ�� am_zsn700_rtc_init() ��ȡ���� RTC ��׼����������
 *
 * \return ��
 */
void am_zsn700_rtc_deinit (am_rtc_handle_t handle);

/** @} */

/**
 * @} zlg_if_rtc
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZSN700_RTC_H */

/* end of file */
