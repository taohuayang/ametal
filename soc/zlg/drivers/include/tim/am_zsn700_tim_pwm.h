/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
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
 * - 1.00 20-03-12  yrz, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_TIM_PWM_H
#define __AM_ZSN700_TIM_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "hw/amhw_zsn700_tim.h"

/**
 * \addtogroup am_zsn700_if_tim_pwm
 * \copydoc am_zsn700_tim_pwm.h
 * @{
 */

/**
 * \brief ͨ����ʶ��
 *
 * \note CHxA �� CHxB�����ڵ���PWM�����Ҳ�����ڻ���PWM�����
 *       ���ڶ�ʱ��012��ֻ��CH0A��CH0B����ͨ����
 *       ���ڶ�ʱ��3����6��ͨ�����ֱ�ΪCH0A��CH0B��������1��
 *                            CH1A��CH1B��������2��
 *                            CH2A��CH2B��������3��
 */
#define  AM_ZSN700_TIM_PWM_CH0A        0x00   /**< \brief PWMͨ��0��ʶ��*/
#define  AM_ZSN700_TIM_PWM_CH0B        0x01   /**< \brief PWMͨ��1��ʶ��*/
#define  AM_ZSN700_TIM_PWM_CH1A        0x02   /**< \brief PWMͨ��2��ʶ��*/
#define  AM_ZSN700_TIM_PWM_CH1B        0x03   /**< \brief PWMͨ��3��ʶ��*/
#define  AM_ZSN700_TIM_PWM_CH2A        0x04   /**< \brief PWMͨ��4��ʶ��*/
#define  AM_ZSN700_TIM_PWM_CH2B        0x05   /**< \brief PWMͨ��5��ʶ��*/

/* PWM������� */
#define  AM_ZSN700_TIM_PWM_OCPOLARITY_HIGH 6  /**< \brief �ߵ�ƽ��Ч */
#define  AM_ZSN700_TIM_PWM_OCPOLARITY_LOW  7  /**< \brief �͵�ƽ��Ч */

/**
 * \brief TIMPWM���������ص�GPIO��Ϣ
 */
typedef struct am_zsn700_tim_pwm_chaninfo {
    int8_t   channel;                  /**< \brief PWM��ʹ�õ�ͨ����ʶ�� */
    int8_t   gpio;                     /**< \brief PWM������õ�GPIO���� */
    uint32_t func;                     /**< \brief PWM���ܵ�GPIO��������ֵ */
    uint32_t dfunc;                    /**< \brief ����PWMģʽ��Ĭ��GPIO��������ֵ */
} am_zsn700_tim_pwm_chaninfo_t;

/**
 * \brief TIMPWM���������ص��豸��Ϣ
 */
typedef struct am_zsn700_tim_pwm_devinfo {
    uint32_t                    tim_regbase;    /**< \brief TIM�Ĵ������ַ */

    uint8_t                     channels_num;   /**< \brief ʹ�õ�ͨ���������Ϊ6 */

    /** \brief ����PWMѡ��  1������PWM   0������PWM */
    uint8_t                     comp;

    /** \brief PWM�������,AM_ZSN700_TIM_PWM_OCPOLARITY_HIGH��AM_ZSN700_TIM_PWM_OCPOLARITY_LOW */
    uint8_t                     ocpolarity;

    am_zsn700_tim_pwm_chaninfo_t  *p_chaninfo;     /**< \brief ָ��PWM���ͨ����Ϣ�ṹ�� */

    amhw_zsn700_tim_type_t         tim_type;       /**< \brief ��ʱ������ */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                      (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                      (*pfn_plfm_deinit)(void);

} am_zsn700_tim_pwm_devinfo_t;

/**
 * \brief TIMPWM��������豸�ṹ��
 */
typedef struct am_zsn700_tim_pwm_dev {

    am_pwm_serv_t                      pwm_serv;   /**< \brief ��׼PWM���� */

    /** \brief ָ��TIM(PWM�������)�豸��Ϣ������ָ�� */
    const am_zsn700_tim_pwm_devinfo_t *p_devinfo;

    uint8_t                            chan_max;   /**< \brief ��Ч�����ͨ����  */

} am_zsn700_tim_pwm_dev_t;

/**
 * \brief ��ʼ��TIMΪPWM�������
 *
 * \param[in] p_dev     : ָ��TIM(PWM�������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(PWM�������)�豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t am_zsn700_tim_pwm_init(am_zsn700_tim_pwm_dev_t              *p_dev,
                                    const am_zsn700_tim_pwm_devinfo_t    *p_devinfo);

/**
 * \brief ��ʹ��TIMPWM�������ʱ�����ʼ��TIMPWM������ܣ��ͷ������Դ
 *
 * \param[in] handle : am_zsn700_tim_pwm_init() ��ʼ��������õ�PWM������
 *
 * \return ��
 */
void am_zsn700_tim_pwm_deinit (am_pwm_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_TIM_PWM_H */

/* end of file */
