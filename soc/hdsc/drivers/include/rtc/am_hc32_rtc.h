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
 * - 1.11 20-04-23 zcb, Add RTC interrupt management interface
 * - 1.10 20-04-17 zcb, Adapt standard drive and delete interfaces that
 *                      are not related to standards
 * - 1.00 19-10-16  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_RTC_H
#define __AM_HC32_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_rtc.h"
#include "hw/amhw_hc32_rtc.h"
#include "hw/amhw_hc32_rcc.h"

/**
 * \addtogroup am_hc32_if_rtc
 * \copydoc am_hc32_rtc.h
 * @{
 */

/**
 * \name HC32 RTC �ж�����
 * @{
 */

/** \brief RTC �����ж� */
#define  AM_HC32_RTC_INT_PERIOD  (0x0)

/** \brief RTC �����ж� */
#define  AM_HC32_RTC_INT_ALARM   (0x1)

/** \brief RTC �ж��������� */
#define  AM_HC32_RTC_INT_CNT     (AM_HC32_RTC_INT_ALARM + 1)

/** @} */

/**
 * \brief HC32 RTC �豸��Ϣ
 */
typedef struct am_hc32_rtc_devinfo {

    /** \brief RTC �Ĵ�������ַ */
    uint32_t                     regbase;

    /** \brief RTC �жϺ� */
    int                          inum;

    /** \brief RTC �����ʼ����Ϊ HC32 RTC ��ݱ�ʾ��ΧΪ 0-99����˱���ָ�������ʼʱ�䣬����1900 */
    uint32_t                     year_epoch;

    /** \brief ƽ̨��ʼ������ */
    void                       (*pfn_plfm_init) (void);
    /** \brief ƽ̨���ʼ������ */
    void                       (*pfn_plfm_deinit) (void);
} am_hc32_rtc_devinfo_t;

/**
 * \brief HC32 RTC �豸
 */
typedef struct am_hc32_rtc_dev {

    /** \brief RTC ��׼���� */
    am_rtc_serv_t                rtc_serv;

    /** \brief RTC�豸��Ϣ */
    const am_hc32_rtc_devinfo_t *p_devinfo;

    /** \brief �ص����� */
    am_pfnvoid_t                 pfn_callback[AM_HC32_RTC_INT_CNT];

    /** \brief �ص��������� */
    void                        *p_arg[AM_HC32_RTC_INT_CNT];
}am_hc32_rtc_dev_t;

/**
 * \brief ��ʼ�� RTC
 *
 * \param[in] p_dev        : ָ�� RTC �豸��ָ��
 * \param[in] p_devinfo    : ָ�� RTC �豸��Ϣ��ָ��
 *
 * \return RTC ��׼���������������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_hc32_rtc_init (am_hc32_rtc_dev_t           *p_dev,
                                  const am_hc32_rtc_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ�� RTC
 *
 * \param[in] handle       : ʹ�� am_hc32_rtc_init() ��ȡ���� RTC ��׼����������
 *
 * \return ��
 */
void am_hc32_rtc_deinit (am_rtc_handle_t            handle);

/******************************************************************************/

/**
 * \brief ���� RTC �ж��������ûص�����
 *
 * \param[in] handle       : ��������RTC ���ж϶�Ӧ RTC ��������� RTC �������
 * \param[in] type         : �ж����ͣ�AM_HC32_RTC_INT_xxxx
 * \param[in] pfn_callback : �ص�����
 * \param[in] p_arg        : �ص���������
 *
 * \note  ��Ϊ RTC ֻ��һ���ж�Դ��������Ҫ�����׼���������������жϿ����������׼��ʱ��������
 *        ���� RTC �����ڳ������׼ RTC �ӿ��������Ӷ� RTC �жϵĹ���
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_hc32_rtc_int_connect (am_rtc_handle_t   handle,
                                  uint8_t           type,
                                  am_pfnvoid_t      pfn_callback,
                                  void             *p_arg);

/**
 * \brief RTC �ж�ʹ��
 *
 * \param[in] handle       : RTC ��׼����������
 * \param[in] type         : �ж����ͣ�AM_HC32_RTC_INT_xxxx
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_hc32_rtc_int_disable (am_rtc_handle_t   handle,
                                  uint8_t           type);

/**
 * \brief RTC �жϽ���
 *
 * \param[in] handle       : RTC ��׼����������
 * \param[in] type         : �ж����ͣ�AM_HC32_RTC_INT_xxxx
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_hc32_rtc_int_enable  (am_rtc_handle_t   handle,
                                  uint8_t           type);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif/* __HC32_RTC_H */

/* end of file */
