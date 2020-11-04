/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.hc32f03x.cn/
*******************************************************************************/

/**
 * \file
 * \brief TIM����PWM��� �û������ļ�
 * \sa am_hwconf_hc32f03x_tim_pwm.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-16  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "am_hc32_tim_pwm.h"
#include "am_hc32_adtim_pwm.h"
#include "am_clk.h"
#include "am_hc32_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f03x_tim_pwm
 * \copydoc am_hwconf_hc32f03x_tim_pwm.c
 * @{
 */
/*******************************************************************************
  TIM0 ����
*******************************************************************************/

/** \brief TIM0����PWM��� ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim0_pwm_init (void)
{
    am_clk_enable(CLK_TIM012);
}

/** \brief ���TIM0ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim0_pwm_deinit (void)
{
    am_clk_disable(CLK_TIM012);
}

/** \brief TIM0����PWM���ܵ�����������Ϣ�б� */
am_hc32_tim_pwm_chaninfo_t __g_tim0_pwm_chaninfo_list[] = {

    /** \brief ͨ��0�������� */
    {
        AM_HC32_TIM_PWM_CH0A,
        PIOA_2,
        PIOA_2_TIM0_CHA | PIOA_2_OUT_PP,
        PIOA_2_GPIO  | PIOA_2_INPUT_PU
    },

    /** \brief ͨ��1�������� */
    {
        AM_HC32_TIM_PWM_CH0B,
        PIOB_3,
        PIOB_3_TIM0_CHB | PIOB_3_OUT_PP,
        PIOB_3_GPIO  | PIOB_3_INPUT_PU
    },
};

/** \brief TIM0����PWM�豸��Ϣ */
const am_hc32_tim_pwm_devinfo_t  __g_tim0_pwm_devinfo = {
    HC32_TIM0_BASE,                           /**< \brief TIM0�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_tim0_pwm_chaninfo_list),   /**< \brief �������ͨ������ */
    0,                                          /**< \brief ����PWMѡ��
                                                 *          1������PWM
                                                 *          0������PWM
                                                 */
    AM_HC32_TIM_PWM_OCPOLARITY_HIGH,          /**< \brief ������ */
    &__g_tim0_pwm_chaninfo_list[0],             /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32_TIM_TYPE_TIM0,                  /**< \brief ��ʱ������ */
    __hc32f03x_plfm_tim0_pwm_init,                /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim0_pwm_deinit               /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM0����PWM�豸���� */
am_hc32_tim_pwm_dev_t __g_tim0_pwm_dev;

/** \brief tim0 PWM ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32_tim0_pwm_inst_init (void)
{
    return am_hc32_tim_pwm_init(&__g_tim0_pwm_dev,
                               &__g_tim0_pwm_devinfo);
}

/** \brief tim0 PWM ʵ�����ʼ�� */
void am_hc32_tim0_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM1 ����
*******************************************************************************/

/** \brief TIM1����PWM��� ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim1_pwm_init (void)
{
    am_clk_enable(CLK_TIM012);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim1_pwm_deinit (void)
{
    am_clk_disable(CLK_TIM012);
}

/** \brief TIM1����PWM���ܵ�����������Ϣ�б� */
am_hc32_tim_pwm_chaninfo_t __g_tim1_pwm_chaninfo_list[] = {

    /** \brief ͨ��0�������� */
    {
        AM_HC32_TIM_PWM_CH0A,
        PIOA_0,
        PIOA_0_TIM1_CHA | PIOA_0_OUT_PP,
        PIOA_0_GPIO  | PIOA_0_INPUT_PU
    },

    /** \brief ͨ��1�������� */
    {
        AM_HC32_TIM_PWM_CH0B,
        PIOA_1,
        PIOA_1_TIM1_CHB | PIOA_1_OUT_PP,
        PIOA_1_GPIO  | PIOA_1_INPUT_PU
    },
};

/** \brief TIM1����PWM�豸��Ϣ */
const am_hc32_tim_pwm_devinfo_t  __g_tim1_pwm_devinfo = {
    HC32_TIM1_BASE,                           /**< \brief TIM1�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_tim1_pwm_chaninfo_list),   /**< \brief �������ͨ������ */
    0,                                          /**< \brief ����PWMѡ��
                                                 *          1������PWM
                                                 *          0������PWM
                                                 */
    AM_HC32_TIM_PWM_OCPOLARITY_HIGH,          /**< \brief ������ */
    &__g_tim1_pwm_chaninfo_list[0],             /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32_TIM_TYPE_TIM1,                  /**< \brief ��ʱ������ */
    __hc32f03x_plfm_tim1_pwm_init,                /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim1_pwm_deinit               /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM1����PWM�豸���� */
am_hc32_tim_pwm_dev_t __g_tim1_pwm_dev;

/** \brief tim1 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32_tim1_pwm_inst_init (void)
{
    return am_hc32_tim_pwm_init(&__g_tim1_pwm_dev,
                               &__g_tim1_pwm_devinfo);
}

/** \brief tim1 pwm ʵ�����ʼ�� */
void am_hc32_tim1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32_tim_pwm_deinit(handle);
}

/*******************************************************************************
  tim2 ����
*******************************************************************************/

/** \brief TIM2����PWM��� ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim2_pwm_init (void)
{
    am_clk_enable(CLK_TIM012);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim2_pwm_deinit (void)
{
    am_clk_disable(CLK_TIM012);
}

/** \brief TIM2����PWM���ܵ�����������Ϣ�б� */
am_hc32_tim_pwm_chaninfo_t __g_tim2_pwm_chaninfo_list[] = {

    /** \brief ͨ��0�������� */
    {
        AM_HC32_TIM_PWM_CH0A,
        PIOA_7,
        PIOA_7_TIM2_CHA | PIOA_7_OUT_PP,
        PIOA_7_GPIO | PIOA_7_INPUT_PU
    },

    /** \brief ͨ��1�������� */
    {
        AM_HC32_TIM_PWM_CH0B,
        PIOB_7,
        PIOB_7_TIM2_CHB | PIOB_7_OUT_PP,
        PIOB_7_GPIO | PIOB_7_INPUT_PU
    },
};

/** \brief TIM2����PWM�豸��Ϣ */
const am_hc32_tim_pwm_devinfo_t  __g_tim2_pwm_devinfo = {
    HC32_TIM2_BASE,                           /**< \brief TIM2�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_tim2_pwm_chaninfo_list),   /**< \brief �������ͨ������ */
    0,                                          /**< \brief ����PWMѡ��
                                                 *          1������PWM
                                                 *          0������PWM
                                                 */
    AM_HC32_TIM_PWM_OCPOLARITY_HIGH,          /**< \brief ������ */
    &__g_tim2_pwm_chaninfo_list[0],             /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32_TIM_TYPE_TIM2,                  /**< \brief ��ʱ������ */
    __hc32f03x_plfm_tim2_pwm_init,                /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim2_pwm_deinit               /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM2����PWM�豸���� */
am_hc32_tim_pwm_dev_t __g_tim2_pwm_dev;

/** \brief tim2 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32_tim2_pwm_inst_init (void)
{
    return am_hc32_tim_pwm_init(&__g_tim2_pwm_dev,
                               &__g_tim2_pwm_devinfo);
}

/** \brief tim2 pwm ʵ�����ʼ�� */
void am_hc32_tim2_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM3 ����
*******************************************************************************/

/** \brief TIM3����PWM��� ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim3_pwm_init (void)
{
    am_clk_enable(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim3_pwm_deinit (void)
{
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3����PWM���ܵ�����������Ϣ�б� */
am_hc32_tim_pwm_chaninfo_t __g_tim3_pwm_chaninfo_list[] = {

    /** \brief ͨ��0�������� */
    {
        AM_HC32_TIM_PWM_CH0A,
        PIOB_3,
        PIOB_3_TIM3_CH0A | PIOB_3_OUT_PP,
        PIOB_3_GPIO | PIOB_3_INPUT_PU
    },

    /** \brief ͨ��1�������� */
    {
        AM_HC32_TIM_PWM_CH0B,
        PIOA_7,
        PIOA_7_TIM3_CH0B | PIOA_7_OUT_PP,
        PIOA_7_GPIO | PIOA_7_INPUT_PU
    },

    /** \brief ͨ��2�������� */
    {
        AM_HC32_TIM_PWM_CH1A,
        PIOA_3,
        PIOA_3_TIM3_CH1A | PIOA_3_OUT_PP,
        PIOA_3_GPIO | PIOA_3_INPUT_PU
    },

    /** \brief ͨ��3�������� */
    {
        AM_HC32_TIM_PWM_CH1B,
        PIOB_0,
        PIOB_0_TIM3_CH1B | PIOB_0_OUT_PP,
        PIOB_0_GPIO | PIOB_0_INPUT_PU
    },

    /** \brief ͨ��4�������� */
    {
        AM_HC32_TIM_PWM_CH2A,
        PIOA_10,
        PIOA_10_TIM3_CH2A | PIOA_10_OUT_PP,
        PIOA_10_GPIO | PIOA_10_INPUT_PU
    },

    /** \brief ͨ��5�������� */
    {
        AM_HC32_TIM_PWM_CH2B,
        PIOA_4,
        PIOA_4_TIM3_CH2B | PIOA_4_OUT_PP,
        PIOA_4_GPIO | PIOA_4_INPUT_PU
    },

};

/** \brief TIM3����PWM�豸��Ϣ */
const am_hc32_tim_pwm_devinfo_t  __g_tim3_pwm_devinfo = {
    HC32_TIM3_BASE,                           /**< \brief TIM3�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_tim3_pwm_chaninfo_list),   /**< \brief �������ͨ������ */
    0,                                          /**< \brief ����PWMѡ��
                                                 *          1������PWM
                                                 *          0������PWM
                                                 */
    AM_HC32_TIM_PWM_OCPOLARITY_HIGH,          /**< \brief ������ */
    &__g_tim3_pwm_chaninfo_list[0],             /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32_TIM_TYPE_TIM3,                  /**< \brief ��ʱ������ */
    __hc32f03x_plfm_tim3_pwm_init,                /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim3_pwm_deinit               /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM3����PWM�豸���� */
am_hc32_tim_pwm_dev_t __g_tim3_pwm_dev;

/** \brief tim3 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32_tim3_pwm_inst_init (void)
{
    return am_hc32_tim_pwm_init(&__g_tim3_pwm_dev,
                               &__g_tim3_pwm_devinfo);
}

/** \brief tim3 pwm ʵ�����ʼ�� */
void am_hc32_tim3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32_tim_pwm_deinit(handle);
}

/*******************************************************************************
  ADTIM4 ����
*******************************************************************************/
/** \brief ADTIM4����PWM��� ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim4_pwm_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ���ADTIM4ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim4_pwm_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM4����PWM���ܵ�����������Ϣ�б� */
am_hc32_adtim_pwm_chaninfo_t __g_adtim4_pwm_chaninfo_list[] = {

    {
        AM_HC32_ADTIM_PWM_CHA,
        PIOA_8,
        PIOA_8_TIM4_CHA  | PIOA_8_OUT_PP ,
        PIOA_8_GPIO  | PIOA_8_INPUT_PU
    },

    {
        AM_HC32_ADTIM_PWM_CHB,
        PIOA_11,
        PIOA_11_TIM4_CHB | PIOA_11_OUT_PP ,
        PIOA_11_GPIO | PIOA_11_INPUT_PU
    },

};

/** \brief ADTIM4����PWM�豸��Ϣ */
const am_hc32_adtim_pwm_devinfo_t  __g_adtim4_pwm_devinfo = {
    HC32_TIM4_BASE,                           /**< \brief ADTIM4�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_adtim4_pwm_chaninfo_list), /**< \brief �������ͨ������ */
    0,                                          /**< \brief ����PWMѡ��
                                                 *          1������PWM
                                                 *          0������PWM
                                                 */
    AM_HC32_ADTIM_PWM_OCPOLARITY_HIGH,        /**< \brief ������ */
    &__g_adtim4_pwm_chaninfo_list[0],           /**< \brief ͨ��������Ϣ�б�        */
    __hc32f03x_plfm_adtim4_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim4_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM4����PWM�豸���� */
am_hc32_adtim_pwm_dev_t __g_adtim4_pwm_dev;

/** \brief adtim4 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32_tim4_pwm_inst_init (void)
{
    return am_hc32_adtim_pwm_init(&__g_adtim4_pwm_dev,
                                    &__g_adtim4_pwm_devinfo);
}

/** \brief adtim4 pwm ʵ�����ʼ�� */
void am_hc32_tim4_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32_adtim_pwm_deinit(handle);
}

/*******************************************************************************
  ADTIM5 ����
*******************************************************************************/

/** \brief ADTIM5����PWM��� ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim5_pwm_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ���ADTIM5ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim5_pwm_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM5����PWM���ܵ�����������Ϣ�б� */
am_hc32_adtim_pwm_chaninfo_t __g_adtim5_pwm_chaninfo_list[] = {

    {
        AM_HC32_ADTIM_PWM_CHA,
        PIOA_3,
        PIOA_3_TIM5_CHA | PIOA_3_OUT_PP ,
        PIOA_3_GPIO | PIOA_3_INPUT_PU
    },

    {
        AM_HC32_ADTIM_PWM_CHB,
        PIOA_5,
        PIOA_5_TIM5_CHB | PIOA_5_OUT_PP ,
        PIOA_5_GPIO | PIOA_5_INPUT_PU
    },
};

/** \brief ADTIM5����PWM�豸��Ϣ */
const am_hc32_adtim_pwm_devinfo_t  __g_adtim5_pwm_devinfo = {
    HC32_TIM5_BASE,                           /**< \brief ADTIM5�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_adtim5_pwm_chaninfo_list), /**< \brief �������ͨ������ */
    0,                                          /**< \brief ����PWMѡ��
                                                 *          1������PWM
                                                 *          0������PWM
                                                 */
    AM_HC32_ADTIM_PWM_OCPOLARITY_HIGH,        /**< \brief ������ */
    &__g_adtim5_pwm_chaninfo_list[0],           /**< \brief ͨ��������Ϣ�б�        */
    __hc32f03x_plfm_adtim5_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim5_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM5����PWM�豸���� */
am_hc32_adtim_pwm_dev_t __g_adtim5_pwm_dev;

/** \brief adtim5 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32_tim5_pwm_inst_init (void)
{
    return am_hc32_adtim_pwm_init(&__g_adtim5_pwm_dev,
                                    &__g_adtim5_pwm_devinfo);
}

/** \brief adtim5 pwm ʵ�����ʼ�� */
void am_hc32_tim5_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32_adtim_pwm_deinit(handle);
}

/*******************************************************************************
  ADTIM6 ����
*******************************************************************************/

/** \brief ADTIM6����PWM��� ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim6_pwm_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ���ADTIM6ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim6_pwm_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM6����PWM���ܵ�����������Ϣ�б� */
am_hc32_adtim_pwm_chaninfo_t __g_adtim6_pwm_chaninfo_list[] = {

    {
        AM_HC32_ADTIM_PWM_CHA,
        PIOB_12,
        PIOB_12_TIM6_CHA | PIOB_12_OUT_PP ,
        PIOB_12_GPIO | PIOB_12_INPUT_PU
    },

    {
        AM_HC32_ADTIM_PWM_CHB,
        PIOC_5,
        PIOC_5_TIM6_CHB  | PIOC_5_OUT_PP ,
        PIOC_5_GPIO  | PIOC_5_INPUT_PU
    },
};

/** \brief ADTIM6����PWM�豸��Ϣ */
const am_hc32_adtim_pwm_devinfo_t  __g_adtim6_pwm_devinfo = {
    HC32_TIM6_BASE,                           /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_adtim6_pwm_chaninfo_list), /**< \brief �������ͨ������ */
    0,                                          /**< \brief ����PWMѡ��
                                                 *          1������PWM
                                                 *          0������PWM
                                                 */
    AM_HC32_ADTIM_PWM_OCPOLARITY_HIGH,        /**< \brief ������ */
    &__g_adtim6_pwm_chaninfo_list[0],           /**< \brief ͨ��������Ϣ�б�        */
    __hc32f03x_plfm_adtim6_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim6_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM6����PWM�豸���� */
am_hc32_adtim_pwm_dev_t __g_adtim6_pwm_dev;

/** \brief adtim6 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32_tim6_pwm_inst_init (void)
{
    return am_hc32_adtim_pwm_init(&__g_adtim6_pwm_dev,
                                    &__g_adtim6_pwm_devinfo);
}

/** \brief adtim6 pwm ʵ�����ʼ�� */
void am_hc32_tim6_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32_adtim_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */
