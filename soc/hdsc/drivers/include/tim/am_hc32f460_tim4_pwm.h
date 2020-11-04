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
 * \brief ��ʱ��TIM����������PWM��׼�ӿ�
 *
 * 1. TIM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���PWM��׼���������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. TIM1��TIM2��TIM3������4·PWMͨ������Ե���м����ģʽ����
 *    TIM14��TIM16��TIM17������1·PWMͨ������Ե����ģʽ��
 *
 * \note һ��TIM���������PWM��������ֵ��Ҳ����˵����TIM�����
 * ����PWM������ͬ��Ƶ����ͬ
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-16  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_TIM4_PWM_H
#define __AM_HC32F460_TIM4_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "hw/amhw_hc32f460_tim4.h"

/**
 * \addtogroup am_hc32f460_if_tim_pwm
 * \copydoc am_hc32f460_tim_pwm.h
 * @{
 */

/**
 * \brief TIMPWM���������ص�GPIO��Ϣ
 */
typedef struct am_hc32f460_tim4_pwm_chaninfo {
    int8_t   channel;                  /**< \brief PWM��ʹ�õ�ͨ����ʶ�� */
    int8_t   gpio;                     /**< \brief PWM������õ�GPIO���� */
    uint32_t func;                     /**< \brief PWM���ܵ�GPIO��������ֵ */
    uint32_t dfunc;                    /**< \brief ����PWMģʽ��Ĭ��GPIO��������ֵ */
} am_hc32f460_tim4_pwm_chaninfo_t;

/**
 * \brief TIMPWM���������ص��豸��Ϣ
 */
typedef struct am_hc32f460_tim4_pwm_devinfo {

    /** \brief TIM�Ĵ������ַ */
    uint32_t                          tim_regbase;

    /** \brief ʹ�õ�ͨ���������Ϊ6 */
    uint8_t                           channels_num;

    en_timer4_pwm_ch_t                pwm_ch;

    /** \brief ָ��PWM���ͨ����Ϣ�ṹ�� */
    am_hc32f460_tim4_pwm_chaninfo_t  *p_chaninfo;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                            (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                            (*pfn_plfm_deinit)(void);

} am_hc32f460_tim4_pwm_devinfo_t;

/**
 * \brief TIMPWM��������豸�ṹ��
 */
typedef struct am_hc32f460_tim4_pwm_dev {

    am_pwm_serv_t                      pwm_serv;   /**< \brief ��׼PWM���� */

    /** \brief ָ��TIM(PWM�������)�豸��Ϣ������ָ�� */
    const am_hc32f460_tim4_pwm_devinfo_t *p_devinfo;

    uint8_t                            chan_max;   /**< \brief ��Ч�����ͨ����  */

} am_hc32f460_tim4_pwm_dev_t;

/**
 * \brief ��ʼ��TIMΪPWM�������
 *
 * \param[in] p_dev     : ָ��TIM(PWM�������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(PWM�������)�豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_tim4_pwm_init(am_hc32f460_tim4_pwm_dev_t              *p_dev,
                                          const am_hc32f460_tim4_pwm_devinfo_t    *p_devinfo);

/**
 * \brief ��ʹ��TIMPWM�������ʱ�����ʼ��TIMPWM������ܣ��ͷ������Դ
 *
 * \param[in] handle : am_hc32f460_tim4_pwm_init() ��ʼ��������õ�PWM������
 *
 * \return ��
 */
void am_hc32f460_tim4_pwm_deinit (am_pwm_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_TIM4_PWM_H */

/* end of file */
