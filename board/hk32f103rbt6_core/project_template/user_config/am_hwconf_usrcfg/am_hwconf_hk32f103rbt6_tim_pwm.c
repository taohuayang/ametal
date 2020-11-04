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
 * \brief TIM����PWM��� �û������ļ�
 * \sa am_hwconf_hk32f103rbt6_tim_pwm.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-28  zcb, first implementation
 * \endinternal
 */

#include "am_hk32f103rbt6.h"
#include "ametal.h"
#include "am_gpio.h"
#include "am_hk32f103rbt6_tim_pwm.h"
#include "am_clk.h"
#include "am_hk32f103rbt6_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hk32f103rbt6_tim_pwm
 * \copydoc am_hwconf_hk32f103rbt6_tim_pwm.c
 * @{
 */

/*******************************************************************************
  TIM1 ����
*******************************************************************************/

/** \brief TIM1����PWM��� ƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim1_pwm_init (void)
{
    am_clk_enable(CLK_TIM1);
    am_hk32f103rbt6_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim1_pwm_deinit (void)
{
    am_hk32f103rbt6_clk_reset(CLK_TIM1);
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1����PWM���ܵ�����������Ϣ�б� */
am_hk32f103rbt6_tim_pwm_chaninfo_t __g_tim1_pwm_chaninfo_list[] = {

    /** \brief ͨ��1�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH1, PIOA_8,  PIOA_8_TIM1_CH1_REMAP0 | PIOA_8_AF_PP, PIOA_8_GPIO  | PIOA_8_INPUT_FLOAT},
    /** \brief ͨ��1������������ */
    {AM_HK32F103RBT6_TIM_PWM_CH1N, PIOB_13, PIOB_13_TIM1_CH1N_REMAP0 | PIOB_13_AF_PP, PIOB_13_GPIO  | PIOB_13_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH2, PIOA_9,  PIOA_9_TIM1_CH2_REMAP0  | PIOA_9_AF_PP,  PIOA_9_GPIO  | PIOA_9_INPUT_FLOAT},
    /** \brief ͨ��2������������ */
    {AM_HK32F103RBT6_TIM_PWM_CH2N, PIOB_14, PIOB_14_TIM1_CH2N_REMAP0 | PIOB_14_AF_PP, PIOB_14_GPIO  | PIOB_14_INPUT_FLOAT},
    /** \brief ͨ��3�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH3, PIOA_10, PIOA_10_TIM1_CH3_REMAP0 | PIOA_10_AF_PP, PIOA_10_GPIO | PIOA_10_INPUT_FLOAT},
    /** \brief ͨ��3������������ */
    {AM_HK32F103RBT6_TIM_PWM_CH3N, PIOB_15, PIOB_15_TIM1_CH3N_REMAP0 | PIOB_15_AF_PP, PIOB_15_GPIO  | PIOB_15_INPUT_FLOAT},
    /** \brief ͨ��4�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH4, PIOA_11, PIOA_11_TIM1_CH4_REMAP0 | PIOA_11_AF_PP, PIOA_11_GPIO | PIOA_11_INPUT_FLOAT}
};

/** \brief TIM1����PWM�豸��Ϣ */
const am_hk32f103rbt6_tim_pwm_devinfo_t  __g_tim1_pwm_devinfo = {
    HK32F103RBT6_TIM1_BASE,                         /**< \brief TIM1�Ĵ�����Ļ���ַ */
    CLK_TIM1,                                 /**< \brief TIM1ʱ��ID */
    AM_NELEMENTS(__g_tim1_pwm_chaninfo_list), /**< \brief �������ͨ������ */
    AMHW_HK32F103RBT6_TIM_PWM_MODE2,                   /**< \brief PWM���ģʽ2 */
    0,                                        /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim1_pwm_chaninfo_list[0],           /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HK32F103RBT6_TIM_TYPE0,                       /**< \brief ��ʱ������ */
    __hk32f103rbt6_plfm_tim1_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hk32f103rbt6_plfm_tim1_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM1����PWM�豸���� */
am_hk32f103rbt6_tim_pwm_dev_t __g_tim1_pwm_dev;

/** \brief tim1 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hk32f103rbt6_tim1_pwm_inst_init (void)
{
    return am_hk32f103rbt6_tim_pwm_init(&__g_tim1_pwm_dev,
                               &__g_tim1_pwm_devinfo);
}

/** \brief tim1 pwm ʵ�����ʼ�� */
void am_hk32f103rbt6_tim1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hk32f103rbt6_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM2 ����
*******************************************************************************/

/** \brief TIM2����PWM��� ƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim2_pwm_init (void)
{
    am_clk_enable(CLK_TIM2);
    am_hk32f103rbt6_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim2_pwm_deinit (void)
{
    am_hk32f103rbt6_clk_reset(CLK_TIM2);
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2����PWM���ܵ�����������Ϣ�б� */
am_hk32f103rbt6_tim_pwm_chaninfo_t __g_tim2_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH1, PIOA_15, PIOA_15_TIM2_CH1_ETR_REMAP3 | PIOA_15_AF_PP, PIOA_15_GPIO | PIOA_15_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH2, PIOB_3, PIOB_3_TIM2_CH2_REMAP3 | PIOB_3_AF_PP, PIOB_3_GPIO | PIOB_3_INPUT_FLOAT},
    /** \brief ͨ��3�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH3, PIOB_10, PIOB_10_TIM2_CH3_REMAP3 | PIOB_10_AF_PP, PIOB_10_GPIO | PIOB_10_INPUT_FLOAT},
    /** \brief ͨ��4�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH4, PIOB_11, PIOB_11_TIM2_CH4_REMAP3 | PIOB_11_AF_PP, PIOB_11_GPIO | PIOB_11_INPUT_FLOAT},
};

/** \brief TIM2����PWM�豸��Ϣ */
const am_hk32f103rbt6_tim_pwm_devinfo_t  __g_tim2_pwm_devinfo = {
    HK32F103RBT6_TIM2_BASE,                         /**< \brief TIM2�Ĵ�����Ļ���ַ */
    CLK_TIM2,                                 /**< \brief TIM2ʱ��ID */
    AM_NELEMENTS(__g_tim2_pwm_chaninfo_list), /**< \brief �������ͨ������ */
    AMHW_HK32F103RBT6_TIM_PWM_MODE2,                   /**< \brief PWM���ģʽ2 */
    0,                                        /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim2_pwm_chaninfo_list[0],           /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HK32F103RBT6_TIM_TYPE1,                       /**< \brief ��ʱ������ */
    __hk32f103rbt6_plfm_tim2_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hk32f103rbt6_plfm_tim2_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM2 ����PWM�豸���� */
am_hk32f103rbt6_tim_pwm_dev_t  __g_tim2_pwm_dev;

/** \brief tim2 pwmʵ����ʼ�������pwm��׼������ */
    am_pwm_handle_t am_hk32f103rbt6_tim2_pwm_inst_init (void)
{
    return am_hk32f103rbt6_tim_pwm_init(&__g_tim2_pwm_dev,
                               &__g_tim2_pwm_devinfo);
}

/** \brief tim2 pwmʵ�����ʼ�� */
void am_hk32f103rbt6_tim2_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hk32f103rbt6_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM3 ����
*******************************************************************************/

/** \brief TIM3����PWM��� ƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim3_pwm_init (void)
{
    am_clk_enable(CLK_TIM3);
    am_hk32f103rbt6_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3 PWMƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim3_pwm_deinit (void)
{
    am_hk32f103rbt6_clk_reset(CLK_TIM3);
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3����PWM���ܵ�����������Ϣ�б� */
am_hk32f103rbt6_tim_pwm_chaninfo_t __g_tim3_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH1, PIOA_6, PIOA_6_TIM3_CH1_REMAP0 | PIOA_6_AF_PP, PIOA_6_GPIO | PIOA_6_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH2, PIOA_7, PIOA_7_TIM3_CH2_REMAP0 | PIOA_7_AF_PP, PIOA_7_GPIO | PIOA_7_INPUT_FLOAT},
    /** \brief ͨ��3�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH3, PIOC_8, PIOC_8_TIM3_CH3_REMAP3 | PIOC_8_AF_PP, PIOC_8_GPIO | PIOC_8_INPUT_FLOAT},
    /** \brief ͨ��4�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH4, PIOB_1, PIOB_1_TIM3_CH4_REMAP0 | PIOB_1_AF_PP, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},
};

/** \brief TIM3����PWM�豸��Ϣ */
const am_hk32f103rbt6_tim_pwm_devinfo_t  __g_tim3_pwm_devinfo = {
    HK32F103RBT6_TIM3_BASE,                          /**< \brief TIM3�Ĵ�����Ļ���ַ */
    CLK_TIM3,                                  /**< \brief TIM3ʱ��ID */
    AM_NELEMENTS(__g_tim1_pwm_chaninfo_list),  /**< \brief �������ͨ������ */
    AMHW_HK32F103RBT6_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2 */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim3_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HK32F103RBT6_TIM_TYPE1,                        /**< \brief ��ʱ������ */
    __hk32f103rbt6_plfm_tim3_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hk32f103rbt6_plfm_tim3_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM3����PWM�豸���� */
am_hk32f103rbt6_tim_pwm_dev_t __g_tim3_pwm_dev;

/** \brief tim3 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_hk32f103rbt6_tim3_pwm_inst_init (void)
{
    return am_hk32f103rbt6_tim_pwm_init(&__g_tim3_pwm_dev,
                                  &__g_tim3_pwm_devinfo);
}

/** \brief tim3 pwm ʵ�����ʼ�� */
void am_hk32f103rbt6_tim3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hk32f103rbt6_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM4����
*******************************************************************************/

/** \brief TIM4����PWM��� ƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim4_pwm_init (void)
{
    am_clk_enable(CLK_TIM4);
    am_hk32f103rbt6_clk_reset(CLK_TIM4);
}

/** \brief ���TIM4 PWMƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_tim4_pwm_deinit (void)
{
    am_hk32f103rbt6_clk_reset(CLK_TIM4);
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4����PWM���ܵ�����������Ϣ�б� */
am_hk32f103rbt6_tim_pwm_chaninfo_t __g_tim4_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH1, PIOB_6, PIOB_6_TIM4_CH1 | PIOB_6_AF_PP, PIOB_6_GPIO | PIOB_6_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH2, PIOB_7, PIOB_7_TIM4_CH2 | PIOB_7_AF_PP, PIOB_7_GPIO | PIOB_7_INPUT_FLOAT},
    /** \brief ͨ��3�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH3, PIOB_8, PIOB_8_TIM4_CH3 | PIOB_8_AF_PP, PIOB_8_GPIO | PIOB_8_INPUT_FLOAT},
    /** \brief ͨ��4�������� */
    {AM_HK32F103RBT6_TIM_PWM_CH4, PIOB_9, PIOB_9_TIM4_CH4 | PIOB_9_AF_PP, PIOB_9_GPIO | PIOB_9_INPUT_FLOAT},
};

/** \brief TIM4����PWM�豸��Ϣ */
const am_hk32f103rbt6_tim_pwm_devinfo_t  __g_tim4_pwm_devinfo = {
    HK32F103RBT6_TIM4_BASE,                          /**< \brief TIM4�Ĵ�����Ļ���ַ */
    CLK_TIM4,                                  /**< \brief TIM4ʱ��ID */
    AM_NELEMENTS(__g_tim1_pwm_chaninfo_list),  /**< \brief �������ͨ������ */
    AMHW_HK32F103RBT6_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2 */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim4_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HK32F103RBT6_TIM_TYPE1,                        /**< \brief ��ʱ������ */
    __hk32f103rbt6_plfm_tim4_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hk32f103rbt6_plfm_tim4_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM4����PWM�豸���� */
am_hk32f103rbt6_tim_pwm_dev_t  __g_tim4_pwm_dev;

/** \brief tim4 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_hk32f103rbt6_tim4_pwm_inst_init (void)
{
    return am_hk32f103rbt6_tim_pwm_init(&__g_tim4_pwm_dev,
                                  &__g_tim4_pwm_devinfo);
}

/** \brief tim4 pwmʵ�����ʼ�� */
void am_hk32f103rbt6_tim4_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hk32f103rbt6_tim_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */
