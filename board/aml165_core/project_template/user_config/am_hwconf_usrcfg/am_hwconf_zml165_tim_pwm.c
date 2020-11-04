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
 * \sa am_hwconf_zml165_tim_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-24  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zml165.h"
#include "am_gpio.h"
#include "am_zlg_tim_pwm.h"
#include "am_clk.h"
#include "am_zml165_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zml165_tim_pwm
 * \copydoc am_hwconf_zml165_tim_pwm.c
 * @{
 */

/*******************************************************************************
 * TIM1 ����
 ******************************************************************************/

/** \brief TIM1����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim1_pwm_init (void)
{
    /* ʹ�ܸ߼���ʱ��1ʱ�� */
    am_clk_enable(CLK_TIM1);

    /* ��λ�߼���ʱ��1 */
    am_zml165_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
static void __zlg_plfm_tim1_pwm_deinit (void)
{
    /* ��λ�߼���ʱ��1 */
    am_zml165_clk_reset(CLK_TIM1);

    /* ���ܸ߼���ʱ��1ʱ�� */
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim1_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOB_3, PIOB_3_TIM1_CH1 | PIOB_3_AF_PP, PIOB_3_GPIO | PIOB_3_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_ZLG_TIM_PWM_CH2, PIOB_4, PIOB_4_TIM1_CH2  | PIOB_4_AF_PP,  PIOB_4_GPIO  | PIOB_4_INPUT_FLOAT},
    /** \brief ͨ��3�������� */
    {AM_ZLG_TIM_PWM_CH3, PIOB_5, PIOB_5_TIM1_CH3 | PIOB_5_AF_PP, PIOB_5_GPIO | PIOB_5_INPUT_FLOAT},
    /** \brief ͨ��3������������ */
    {AM_ZLG_TIM_PWM_CH3N, PIOA_5, PIOA_5_TIM1_CH3N | PIOA_5_AF_PP, PIOA_5_GPIO | PIOA_5_INPUT_FLOAT},
};

/** \brief TIM1����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim1_pwm_devinfo = {
    ZML165_TIM1_BASE,                          /**< \brief TIM1�Ĵ�����Ļ���ַ    */
    CLK_TIM1,                                  /**< \brief TIM1ʱ��ID              */
    AM_NELEMENTS(__g_tim1_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2            */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim1_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE0,                        /**< \brief ��ʱ������              */
    __zlg_plfm_tim1_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim1_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM1����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim1_pwm_dev;
static am_pwm_handle_t       __g_tim1_pwm_handle = NULL;

/** \brief tim1 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_zml165_tim1_pwm_inst_init (void)
{
    if (__g_tim1_pwm_handle == NULL) {
        __g_tim1_pwm_handle = am_zlg_tim_pwm_init(&__g_tim1_pwm_dev,
                                                  &__g_tim1_pwm_devinfo);
    }
    
    return __g_tim1_pwm_handle;
}

/** \brief tim1 pwm ʵ�����ʼ�� */
void am_zml165_tim1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim1_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim1_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM2 ����
 ******************************************************************************/

/** \brief TIM2����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim2_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��2ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λͨ�ö�ʱ��2 */
    am_zml165_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
static void __zlg_plfm_tim2_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��2 */
    am_zml165_clk_reset(CLK_TIM2);

    /* ����ͨ�ö�ʱ��2ʱ�� */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim2_pwm_chaninfo_list[] = {
        /** \brief ͨ��1�������� */
        {AM_ZLG_TIM_PWM_CH1, PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_AF_PP, PIOA_0_GPIO | PIOA_0_INPUT_FLOAT},
        /** \brief ͨ��2�������� */
        {AM_ZLG_TIM_PWM_CH2, PIOB_4, PIOB_4_TIM2_CH2 | PIOB_4_AF_PP, PIOB_4_GPIO | PIOB_4_INPUT_FLOAT},
        /** \brief ͨ��3�������� */
        {AM_ZLG_TIM_PWM_CH3, PIOB_5, PIOB_5_TIM2_CH3 | PIOB_5_AF_PP, PIOB_5_GPIO | PIOB_5_INPUT_FLOAT},
};

/** \brief TIM2����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim2_pwm_devinfo = {
    ZML165_TIM2_BASE,                          /**< \brief TIM2�Ĵ�����Ļ���ַ    */
    CLK_TIM2,                                  /**< \brief TIM2ʱ��ID              */
    AM_NELEMENTS(__g_tim2_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2            */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim2_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE1,                        /**< \brief ��ʱ������              */
    __zlg_plfm_tim2_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim2_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM2 ����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim2_pwm_dev;
static am_pwm_handle_t       __g_tim2_pwm_handle = NULL;

/** \brief tim2 pwmʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_zml165_tim2_pwm_inst_init (void)
{
    if (__g_tim2_pwm_handle == NULL) {
        __g_tim2_pwm_handle = am_zlg_tim_pwm_init(&__g_tim2_pwm_dev,
                                                  &__g_tim2_pwm_devinfo);
    }
    
    return __g_tim2_pwm_handle;
}

/** \brief tim2 pwmʵ�����ʼ�� */
void am_zml165_tim2_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim2_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim2_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM3 ����
 ******************************************************************************/

/** \brief TIM3����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim3_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��3ʱ�� */
    am_clk_enable(CLK_TIM3);

    /* ��λͨ�ö�ʱ��3 */
    am_zml165_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim3_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��3 */
    am_zml165_clk_reset(CLK_TIM3);

    /* ����ͨ�ö�ʱ��3ʱ�� */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim3_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOB_4,  PIOB_4_TIM3_CH1 | PIOB_4_AF_PP, PIOB_4_GPIO | PIOB_4_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_ZLG_TIM_PWM_CH2, PIOB_5,  PIOB_5_TIM3_CH2 | PIOB_5_AF_PP, PIOB_5_GPIO | PIOB_5_INPUT_FLOAT},
};

/** \brief TIM3����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim3_pwm_devinfo = {
    ZML165_TIM3_BASE,                          /**< \brief TIM3�Ĵ�����Ļ���ַ    */
    CLK_TIM3,                                  /**< \brief TIM3ʱ��ID              */
    AM_NELEMENTS(__g_tim3_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2            */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim3_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE1,                        /**< \brief ��ʱ������              */
    __zlg_plfm_tim3_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim3_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM3����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim3_pwm_dev;
static am_pwm_handle_t       __g_tim3_pwm_handle = NULL;

/** \brief tim3 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zml165_tim3_pwm_inst_init (void)
{
    if (__g_tim3_pwm_handle == NULL) {
        __g_tim3_pwm_handle = am_zlg_tim_pwm_init(&__g_tim3_pwm_dev,
                                                  &__g_tim3_pwm_devinfo);
    }
    return __g_tim3_pwm_handle;
}

/** \brief tim3 pwm ʵ�����ʼ�� */
void am_zml165_tim3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim3_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim3_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM14����
 ******************************************************************************/

/** \brief TIM14����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim14_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��14ʱ�� */
    am_clk_enable(CLK_TIM14);

    /* ��λͨ�ö�ʱ��14 */
    am_zml165_clk_reset(CLK_TIM14);
}

/** \brief ���TIM14 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim14_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��14 */
    am_zml165_clk_reset(CLK_TIM14);

    /* ����ͨ�ö�ʱ��14ʱ�� */
    am_clk_disable(CLK_TIM14);
}

/** \brief TIM14����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim14_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOA_4,  PIOA_4_TIM14_CH1 | PIOA_4_AF_PP, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM14����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim14_pwm_devinfo = {
    ZML165_TIM14_BASE,                          /**< \brief TIM14�Ĵ�����Ļ���ַ   */
    CLK_TIM14,                                  /**< \brief TIM14ʱ��ID             */
    AM_NELEMENTS(__g_tim14_pwm_chaninfo_list) , /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM���ģʽ2            */
    0,                                          /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim14_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE2,                         /**< \brief ��ʱ������              */
    __zlg_plfm_tim14_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim14_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM14����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim14_pwm_dev;
static am_pwm_handle_t       __g_tim14_pwm_handle = NULL;

/** \brief tim14 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zml165_tim14_pwm_inst_init (void)
{
    if (__g_tim14_pwm_handle == NULL) {
        __g_tim14_pwm_handle = am_zlg_tim_pwm_init(&__g_tim14_pwm_dev,
                                                   &__g_tim14_pwm_devinfo);
    }
    return __g_tim14_pwm_handle;
}

/** \brief tim14 pwmʵ�����ʼ�� */
void am_zml165_tim14_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim14_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim14_pwm_handle = NULL;
    }
}

/**
 * @}
 */

/* end of file */
