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
 * \brief ��ʱ��TIM����������CAP��׼�ӿ�
 *
 * 1. TIM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ��񡰲��񡱱�׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. TIM1��TIM2��TIM3������4������ͨ����TIM14��TIM16��TIM17������1������ͨ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-4-21  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_TIMEA_CAP_H
#define __AM_HC32F460_TIMEA_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "hw/amhw_hc32f460_timea.h"

/**
 * \addtogroup am_hc32f460_if_tim_cap
 * \copydoc am_hc32f460_timea_cap.h
 * @{
 */

/**
 * \brief TIM��������ص�GPIO��Ϣ
 */
typedef struct am_hc32f460_timea_cap_ioinfo {
    int8_t   channel;        /**< \brief CAP��ʹ�õ�ͨ����ʶ�� */
    uint32_t gpio;           /**< \brief ��Ӧ��GPIO�ܽ� */
    uint32_t func;           /**< \brief Ϊ������ʱ��GPIO�������� */
    uint32_t dfunc;          /**< \brief ���ܹܽŲ�����ʱ��Ĭ��GPIO�������� */
} am_hc32f460_timea_cap_ioinfo_t;

/**
 * \brief TIM��������ص��豸��Ϣ
 */
typedef struct am_hc32f460_timea_cap_devinfo {
    uint32_t                     tim_regbase;   /**< \brief TIM�Ĵ������ַ */
    uint8_t                      inum;          /**< \brief TIM��Ӧ���жϺ� */
    amhw_hc32f460_timea_clkdiv_t clk_div;       /**< \brief ʱ�ӷ�Ƶϵ�� */
    uint8_t                      chan_max_num;  /**< \brief ʹ�õ�ͨ���������Ϊ8 */    
    uint8_t                      sync_startup_en;
    am_hc32f460_timea_cap_ioinfo_t *p_ioinfo;   /**< \brief ָ�򲶻�ܽ���Ϣ�ṹ�� */
    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                      (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                      (*pfn_plfm_deinit)(void);
} am_hc32f460_timea_cap_devinfo_t;

/**
 * \brief TIM�������豸
 */
typedef struct am_hc32f460_timea_cap_dev {
    am_cap_serv_t          cap_serv;      /**< \brief ��׼CAP���� */

    struct {
        am_cap_callback_t  callback_func; /**< \brief �ص����� */
        void              *p_arg;         /**< \brief �ص��������û����� */
    } callback_info[8];                   /**< \brief �洢���8ͨ���Ļص�������Ϣ */

    /** \brief ָ��TIM(������)�豸��Ϣ������ָ�� */
    const am_hc32f460_timea_cap_devinfo_t *p_devinfo;

    uint8_t                chan_max;      /**< \brief ��Ч�����ͨ����  */

} am_hc32f460_timea_cap_dev_t;

/**
 * \brief ��ʼ��TIMΪ������
 *
 * \param[in] p_dev     : ָ��TIM(������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(������)�豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_timea_cap_init (am_hc32f460_timea_cap_dev_t           *p_dev,
                                            const am_hc32f460_timea_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TIM������ʱ�����ʼ��TIM�����ܣ��ͷ������Դ
 *
 * \param[in] handle : am_hc32f460_timea_cap_init() ��ʼ��������õ�cap������
 *
 * \return ��
 */
void am_hc32f460_timea_cap_deinit (am_cap_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_TIMEA_CAP_H */

/* end of file */
