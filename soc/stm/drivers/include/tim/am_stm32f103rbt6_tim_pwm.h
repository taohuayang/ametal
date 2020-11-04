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
 * - 1.00 17-04-21  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_STM32F103RBT6_TIM_PWM_H
#define __AM_STM32F103RBT6_TIM_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "hw/amhw_stm32f103rbt6_tim.h"

/**
 * \addtogroup am_stm32f103rbt6_if_tim_pwm
 * \copydoc am_stm32f103rbt6_tim_pwm.h
 * @{
 */

/**
 * \brief ͨ����ʶ�������λΪ��1��������ͨ������7λ�����Ӧͨ���ţ�
 */
#define  AM_STM32F103RBT6_TIM_PWM_CH1         0x00   /**< \brief PWMͨ��1��ʶ��*/
#define  AM_STM32F103RBT6_TIM_PWM_CH2         0x01   /**< \brief PWMͨ��2��ʶ��*/
#define  AM_STM32F103RBT6_TIM_PWM_CH3         0x02   /**< \brief PWMͨ��3��ʶ��*/
#define  AM_STM32F103RBT6_TIM_PWM_CH4         0x03   /**< \brief PWMͨ��4��ʶ��*/

#define  AM_STM32F103RBT6_TIM_PWM_CH1N        0x80   /**< \brief PWMͨ��1������ʶ��*/
#define  AM_STM32F103RBT6_TIM_PWM_CH2N        0x81   /**< \brief PWMͨ��2������ʶ��*/
#define  AM_STM32F103RBT6_TIM_PWM_CH3N        0x82   /**< \brief PWMͨ��3������ʶ��*/
#define  AM_STM32F103RBT6_TIM_PWM_CH4N        0x83   /**< \brief PWMͨ��4������ʶ��*/


/**
 * \brief TIMPWM���������ص�GPIO��Ϣ
 */
typedef struct am_stm32f103rbt6_tim_pwm_chaninfo {
    int8_t   channel;                  /**< \brief PWM��ʹ�õ�ͨ����ʶ�� */
    int8_t   gpio;                     /**< \brief PWM������õ�GPIO���� */
    uint32_t func;                     /**< \brief PWM���ܵ�GPIO��������ֵ */
    uint32_t dfunc;                    /**< \brief ����PWMģʽ��Ĭ��GPIO��������ֵ */
} am_stm32f103rbt6_tim_pwm_chaninfo_t;

/**
 * \brief TIMPWM���������ص��豸��Ϣ
 */
typedef struct am_stm32f103rbt6_tim_pwm_devinfo {
    uint32_t                    tim_regbase;    /**< \brief TIM�Ĵ������ַ */

    int                         clk_num;        /**< \brief ʱ��ID */

    uint8_t                     channels_num;   /**< \brief ʹ�õ�ͨ���������Ϊ4 */

    /** \brief PWM��ģʽ�� AMHW_STM32F103RBT6_TIM_PWM_MODE2 �� AMHW_STM32F103RBT6_TIM_PWM_MODE1 */
    uint8_t                     pwm_mode;

    /** \brief PWM�������,0Ϊ�ߵ�ƽ��Ч, 1Ϊ�͵�ƽ��Ч */
    uint8_t                     ocpolarity;

    am_stm32f103rbt6_tim_pwm_chaninfo_t  *p_chaninfo;     /**< \brief ָ��PWM���ͨ����Ϣ�ṹ�� */

    amhw_stm32f103rbt6_tim_type_t         tim_type;       /**< \brief ��ʱ������ */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                      (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                      (*pfn_plfm_deinit)(void);

} am_stm32f103rbt6_tim_pwm_devinfo_t;

/**
 * \brief TIMPWM��������豸�ṹ��
 */
typedef struct am_stm32f103rbt6_tim_pwm_dev {

    am_pwm_serv_t                      pwm_serv; /**< \brief ��׼PWM���� */

    /** \brief ָ��TIM(PWM�������)�豸��Ϣ������ָ�� */
    const am_stm32f103rbt6_tim_pwm_devinfo_t    *p_devinfo;

} am_stm32f103rbt6_tim_pwm_dev_t;

/**
 * \brief ��ʼ��TIMΪPWM�������
 *
 * \param[in] p_dev     : ָ��TIM(PWM�������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(PWM�������)�豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t am_stm32f103rbt6_tim_pwm_init(am_stm32f103rbt6_tim_pwm_dev_t              *p_dev,
                                    const am_stm32f103rbt6_tim_pwm_devinfo_t    *p_devinfo);

/**
 * \brief ��ʹ��TIMPWM�������ʱ�����ʼ��TIMPWM������ܣ��ͷ������Դ
 *
 * \param[in] handle : am_stm32f103rbt6_tim_pwm_init() ��ʼ��������õ�PWM������
 *
 * \return ��
 */
void am_stm32f103rbt6_tim_pwm_deinit (am_pwm_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_STM32F103RBT6_TIM_PWM_H */

/* end of file */
