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

#ifndef __AM_HK32F103RBT6_TIM_CAP_H
#define __AM_HK32F103RBT6_TIM_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "hw/amhw_hk32f103rbt6_tim.h"

/**
 * \addtogroup am_hk32f103rbt6_if_tim_cap
 * \copydoc am_hk32f103rbt6_tim_cap.h
 * @{
 */

/**
 * \brief TIM��������ص�GPIO��Ϣ
 */
typedef struct am_hk32f103rbt6_tim_cap_ioinfo {
    uint32_t gpio;           /**< \brief ��Ӧ��GPIO�ܽ� */
    uint32_t func;           /**< \brief Ϊ������ʱ��GPIO�������� */
    uint32_t dfunc;          /**< \brief ���ܹܽŲ�����ʱ��Ĭ��GPIO�������� */
} am_hk32f103rbt6_tim_cap_ioinfo_t;

/**
 * \brief TIM��������ص��豸��Ϣ
 */
typedef struct am_hk32f103rbt6_tim_cap_devinfo {
    uint32_t                    tim_regbase;   /**< \brief TIM�Ĵ������ַ */
    uint8_t                     inum;          /**< \brief TIM��Ӧ���жϺ� */
    int                         clk_num;       /**< \brief ʱ��ID */
    uint8_t                     channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ6 */
    am_hk32f103rbt6_tim_cap_ioinfo_t    *p_ioinfo;      /**< \brief ָ�򲶻�ܽ���Ϣ�ṹ�� */
    amhw_hk32f103rbt6_tim_type_t         tim_type;      /**< \brief ��ʱ������ */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                      (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                      (*pfn_plfm_deinit)(void);
} am_hk32f103rbt6_tim_cap_devinfo_t;

/**
 * \brief TIM�������豸
 */
typedef struct am_hk32f103rbt6_tim_cap_dev {
    am_cap_serv_t          cap_serv;      /**< \brief ��׼CAP���� */

    struct {
        am_cap_callback_t  callback_func; /**< \brief �ص����� */
        void              *p_arg;         /**< \brief �ص��������û����� */
    } callback_info[4];                   /**< \brief �洢���6ͨ���Ļص�������Ϣ */

    /** \brief ָ��TIM(������)�豸��Ϣ������ָ�� */
    const am_hk32f103rbt6_tim_cap_devinfo_t *p_devinfo;

} am_hk32f103rbt6_tim_cap_dev_t;

/**
 * \brief ��ʼ��TIMΪ������
 *
 * \param[in] p_dev     : ָ��TIM(������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(������)�豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t am_hk32f103rbt6_tim_cap_init (am_hk32f103rbt6_tim_cap_dev_t              *p_dev,
                                        const am_hk32f103rbt6_tim_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TIM������ʱ�����ʼ��TIM�����ܣ��ͷ������Դ
 *
 * \param[in] handle : am_hk32f103rbt6_tim_cap_init() ��ʼ��������õ�cap������
 *
 * \return ��
 */
void am_hk32f103rbt6_tim_cap_deinit (am_cap_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HK32F103RBT6_TIM_CAP_H */

/* end of file */
