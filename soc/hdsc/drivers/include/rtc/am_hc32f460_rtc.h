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
 * - 1.00 19-10-16  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_RTC_H
#define __AM_HC32_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_rtc.h"
#include "hw/amhw_hc32f460_rtc.h"

/**
 * \addtogroup am_hc32f460_if_rtc
 * \copydoc am_hc32f460_rtc.h
 * @{
 */

/**
 * \brief HC32 RTC �豸��Ϣ
 */
typedef struct am_hc32f460_rtc_devinfo {
    uint32_t                  rtc_regbase;           /**< \brief RTC �Ĵ�������ַ */
    int                       inum;                  /**< \brief RTC �жϺ� */
    void                    (*pfn_plfm_init)(void);  /**< \brief ƽ̨��ʼ������ */
    void                    (*pfn_plfm_deinit)(void);/**< \brief ƽ̨���ʼ������ */
} am_hc32f460_rtc_devinfo_t;

/**
 * \brief HC32 RTC �豸
 */
typedef struct am_hc32f460_rtc_dev {
    am_rtc_serv_t                  rtc_serv;        /**< \brief RTC ��׼���� */
    uint8_t                        int_state;       /**< \brief �ж�ʹ�ܱ�־ */
    am_bool_t                      rtc_continue;    /**< \brief RTC�Ƿ�������� */
    am_pfnvoid_t                   pfn_callback[2]; /**< \brief �ص����� */
    void                          *p_arg[2];        /**< \brief �ص��������� */
    const am_hc32f460_rtc_devinfo_t *p_devinfo;     /**< \brief RTC�豸��Ϣ */
}am_hc32f460_rtc_dev_t;

/**
 * \brief ��ʼ�� RTC
 *
 * \param[in] p_dev     ָ�� RTC �豸��ָ��
 * \param[in] p_devinfo ָ�� RTC �豸��Ϣ��ָ��
 *
 * \return RTC ��׼���������������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_hc32f460_rtc_init (am_hc32f460_rtc_dev_t           *p_dev,
                                      const am_hc32f460_rtc_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ�� RTC
 *
 * \param[in] handle ʹ�� am_hc32f460_rtc_init() ��ȡ���� RTC ��׼����������
 *
 * \return ��
 */
void am_hc32f460_rtc_deinit (am_rtc_handle_t handle);

void RTC_ALM_IrqHandler(void *p_arg);

void RTC_PRD_IrqHandler(void *p_arg);

/** @} */

/**
 * @} hc32f460_if_rtc
 */

#ifdef __cplusplus
}
#endif

#endif/* __HC32F460_RTC_H */

/* end of file */
