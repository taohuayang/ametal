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
  \file
  \brief HC32 TIM ��ʱ�����û������ļ�
  \sa am_hwconf_hc32f03x_tim_timing.c
 *
 *
  \internal
  \par Modification history
  - 1.00 19-09-11  zp, first implementation
  \endinternal
 */

#include "ametal.h"
#include "am_clk.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "am_hc32_clk.h"
#include "am_hc32_tim_timing.h"
#include "am_hc32_adtim_timing.h"

/**
  \addtogroup am_if_src_hwconf_hc32f03x_tim_timing
  \copydoc am_hwconf_hc32f03x_tim_timing.c
  @{
 */

/*******************************************************************************
  TIM0 ����
*******************************************************************************/

/** \brief TIM0 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim0_timing_init (void)
{
//    /* ����GATE���ţ���ʵ���ſع��� */
//    am_gpio_pin_cfg(PIOB_8, PIOB_8_INPUT_PD | PIOB_8_TIM0_GATE);
//
//    /* ����ETR���ţ����ⲿʱ����Ϊ����ʱ�ӹ��� */
//    am_gpio_pin_cfg(PIOA_0, PIOA_0_INPUT_PD | PIOA_0_TIM0_ETR);

    am_clk_enable(CLK_TIM012);
}

/** \brief ��� TIM0 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim0_timing_deinit (void)
{
//    am_gpio_pin_cfg(PIOB_8, PIOB_8_INPUT_PU | PIOB_8_GPIO);
//
//    am_gpio_pin_cfg(PIOA_0, PIOA_0_INPUT_PU | PIOA_0_GPIO);

    am_clk_disable(CLK_TIM012);
}

/** \brief TIM0 �豸��Ϣ */
const am_hc32_tim_timing_devinfo_t  __g_tim0_timing_devinfo = {
    HC32_TIM0_BASE,                  /**< \brief TIM0�Ĵ�����Ļ���ַ */
    INUM_TIM0,                         /**< \brief TIM0�жϱ�� */
    AMHW_HC32_TIM_TYPE_TIM0,         /**< \brief ��ʱ������ */
    AMHW_HC32_TIM_MODE0_COUNTER_16,  /**< \brief 16λ���ؼ��� */
    AMHW_HC32_TIM_GATE_DISABLE,      /**< \brief �ſ�״̬��Ĭ�Ϲرգ� */
    AM_TRUE,                           /**< \brief �ſ��ź�Ϊ�棨1����Ч */
    AMHW_HC32_TIM_CLK_SRC_TCLK,      /**< \brief ����ʱ��ѡ��Ĭ���ڲ��� */
    __hc32f03x_plfm_tim0_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim0_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM0 �豸���� */
am_hc32_tim_timing_dev_t __g_tim0_timing_dev;

/** \brief ��ʱ��TIM0 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_tim0_timing_inst_init (void)
{
    return am_hc32_tim_timing_init(&__g_tim0_timing_dev,
                                     &__g_tim0_timing_devinfo);
}

/** \brief TIM0 Timingʵ�����ʼ�� */
void am_hc32_tim0_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_tim_timing_deinit(handle);
}

/*******************************************************************************
  TIM1 ����
*******************************************************************************/

/** \brief TIM1 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim1_timing_init (void)
{
//    /* ����GATE���ţ���ʵ���ſع��� */
//    am_gpio_pin_cfg(PIOB_13, PIOB_13_INPUT_PD | PIOB_13_TIM1_GATE);
//
//    /* ����ETR���ţ����ⲿʱ����Ϊ����ʱ�ӹ��� */
//    am_gpio_pin_cfg(PIOC_9, PIOC_9_INPUT_PD | PIOC_9_TIM1_ETR);

    am_clk_enable(CLK_TIM012);
}

/** \brief ��� TIM1 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim1_timing_deinit (void)
{
//    am_gpio_pin_cfg(PIOB_13, PIOB_13_INPUT_PU | PIOB_13_GPIO);
//
//    am_gpio_pin_cfg(PIOC_9, PIOC_9_INPUT_PU | PIOC_9_GPIO);

    am_clk_disable(CLK_TIM012);
}

/** \brief TIM1 �豸��Ϣ */
const am_hc32_tim_timing_devinfo_t  __g_tim1_timing_devinfo = {
    HC32_TIM1_BASE,                  /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1,                         /**< \brief TIM1�жϱ�� */
    AMHW_HC32_TIM_TYPE_TIM1,         /**< \brief ��ʱ������ */
    AMHW_HC32_TIM_MODE0_COUNTER_16,  /**< \brief 16λ���ؼ��� */
    AMHW_HC32_TIM_GATE_DISABLE,      /**< \brief �ſ�״̬��Ĭ�Ϲرգ� */
    AM_TRUE,                           /**< \brief �ſ��ź�Ϊ�棨1����Ч */
    AMHW_HC32_TIM_CLK_SRC_TCLK,      /**< \brief ����ʱ��ѡ��Ĭ���ڲ��� */
    __hc32f03x_plfm_tim1_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim1_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM1 �豸���� */
am_hc32_tim_timing_dev_t __g_tim1_timing_dev;

/** \brief ��ʱ��TIM1 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_tim1_timing_inst_init (void)
{
    return am_hc32_tim_timing_init(&__g_tim1_timing_dev,
                                     &__g_tim1_timing_devinfo);
}

/** \brief TIM1 Timingʵ�����ʼ�� */
void am_hc32_tim1_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_tim_timing_deinit(handle);
}

/*******************************************************************************
  TIM2 ����
*******************************************************************************/

/** \brief TIM2 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim2_timing_init (void)
{
//    /* ����GATE���ţ���ʵ���ſع��� */
//    am_gpio_pin_cfg(PIOA_10, PIOA_10_INPUT_PD | PIOA_10_TIM2_GATE);
//
//    /* ����ETR���ţ����ⲿʱ����Ϊ����ʱ�ӹ��� */
//    am_gpio_pin_cfg(PIOC_4, PIOC_4_INPUT_PD | PIOC_4_TIM2_ETR);

    am_clk_enable(CLK_TIM012);
}

/** \brief ��� TIM2 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim2_timing_deinit (void)
{
//    am_gpio_pin_cfg(PIOA_10, PIOA_10_INPUT_PU | PIOA_10_GPIO);
//
//    am_gpio_pin_cfg(PIOC_4, PIOC_4_INPUT_PU | PIOC_4_GPIO);

    am_clk_disable(CLK_TIM012);
}

/** \brief TIM2 �豸��Ϣ */
const am_hc32_tim_timing_devinfo_t  __g_tim2_timing_devinfo = {
    HC32_TIM2_BASE,                  /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                         /**< \brief TIM2�жϱ�� */
    AMHW_HC32_TIM_TYPE_TIM2,         /**< \brief ��ʱ������ */
    AMHW_HC32_TIM_MODE0_COUNTER_16,  /**< \brief 16λ���ؼ��� */
    AMHW_HC32_TIM_GATE_DISABLE,      /**< \brief �ſ�״̬��Ĭ�Ϲرգ� */
    AM_TRUE,                           /**< \brief �ſ��ź�Ϊ�棨1����Ч */
    AMHW_HC32_TIM_CLK_SRC_TCLK,      /**< \brief ����ʱ��ѡ��Ĭ���ڲ��� */
    __hc32f03x_plfm_tim2_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim2_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM2 �豸���� */
am_hc32_tim_timing_dev_t __g_tim2_timing_dev;

/** \brief ��ʱ��TIM2 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_tim2_timing_inst_init (void)
{
    return am_hc32_tim_timing_init(&__g_tim2_timing_dev,
                                     &__g_tim2_timing_devinfo);
}

/** \brief TIM2 Timingʵ�����ʼ�� */
void am_hc32_tim2_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_tim_timing_deinit(handle);
}

/*******************************************************************************
  TIM3 ����
*******************************************************************************/

/** \brief TIM3 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim3_timing_init (void)
{
    /* ����GATE���ţ���ʵ���ſع��� */
    am_gpio_pin_cfg(PIOA_6, PIOA_6_INPUT_PD | PIOA_6_TIM3_GATE);

    /* ����ETR���ţ����ⲿʱ����Ϊ����ʱ�ӹ��� */
    am_gpio_pin_cfg(PIOA_11, PIOA_11_INPUT_PD | PIOA_11_TIM3_GATE);

    am_clk_enable(CLK_TIM3);
}

/** \brief ��� TIM3 ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim3_timing_deinit (void)
{
    am_gpio_pin_cfg(PIOA_6, PIOA_6_INPUT_PU | PIOA_6_GPIO);

    am_gpio_pin_cfg(PIOA_11, PIOA_11_INPUT_PU | PIOA_11_GPIO);

    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3 �豸��Ϣ */
const am_hc32_tim_timing_devinfo_t  __g_tim3_timing_devinfo = {
    HC32_TIM3_BASE,                  /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                         /**< \brief TIM3�жϱ�� */
    AMHW_HC32_TIM_TYPE_TIM3,         /**< \brief ��ʱ������ */
    AMHW_HC32_TIM_MODE0_COUNTER_16,  /**< \brief 16λ���ؼ��� */
    AMHW_HC32_TIM_GATE_DISABLE,      /**< \brief �ſ�״̬��Ĭ�Ϲرգ� */
    AM_TRUE,                           /**< \brief �ſ��ź�Ϊ�棨1����Ч */
    AMHW_HC32_TIM_CLK_SRC_TCLK,      /**< \brief ����ʱ��ѡ��Ĭ���ڲ��� */
    __hc32f03x_plfm_tim3_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim3_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM3 �豸���� */
am_hc32_tim_timing_dev_t __g_tim3_timing_dev;

/** \brief ��ʱ��TIM3 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_tim3_timing_inst_init (void)
{
    return am_hc32_tim_timing_init(&__g_tim3_timing_dev,
                                     &__g_tim3_timing_devinfo);
}

/** \brief TIM3 Timingʵ�����ʼ�� */
void am_hc32_tim3_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_tim_timing_deinit(handle);
}

/*******************************************************************************
  ADTIM4 ����
*******************************************************************************/

/** \brief ADTIM4 ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim4_timing_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ��� ADTIM4 ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim4_timing_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM4 �豸��Ϣ */
const am_hc32_adtim_timing_devinfo_t  __g_adtim4_timing_devinfo = {
    HC32_TIM4_BASE,                    /**< \brief ADTIM4�Ĵ�����Ļ���ַ */
    INUM_TIM4,                           /**< \brief ADTIM4�жϱ�� */
    __hc32f03x_plfm_adtim4_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim4_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief ADTIM4 �豸���� */
am_hc32_adtim_timing_dev_t __g_adtim4_timing_dev;

/** \brief ��ʱ��ADTIM4 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_tim4_timing_inst_init (void)
{
    return am_hc32_adtim_timing_init(&__g_adtim4_timing_dev,
                                       &__g_adtim4_timing_devinfo);
}

/** \brief ADTIM4 Timingʵ�����ʼ�� */
void am_hc32_tim4_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_adtim_timing_deinit(handle);
}

/*******************************************************************************
  ADTIM5 ����
*******************************************************************************/
/** \brief ADTIM5 ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim5_timing_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ��� ADTIM5 ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim5_timing_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM5 �豸��Ϣ */
const am_hc32_adtim_timing_devinfo_t  __g_adtim5_timing_devinfo = {
    HC32_TIM5_BASE,                    /**< \brief ADTIM5�Ĵ�����Ļ���ַ */
    INUM_TIM5,                           /**< \brief ADTIM5�жϱ�� */
    __hc32f03x_plfm_adtim5_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim5_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief ADTIM5 �豸���� */
am_hc32_adtim_timing_dev_t __g_adtim5_timing_dev;

/** \brief ��ʱ��ADTIM5 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_tim5_timing_inst_init (void)
{
    return am_hc32_adtim_timing_init(&__g_adtim5_timing_dev,
                                       &__g_adtim5_timing_devinfo);
}

/** \brief ADTIM5 Timingʵ�����ʼ�� */
void am_hc32_tim5_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_adtim_timing_deinit(handle);
}

/*******************************************************************************
  ADTIM6 ����
*******************************************************************************/

/** \brief ADTIM6 ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim6_timing_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ��� ADTIM6 ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim6_timing_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM6 �豸��Ϣ */
const am_hc32_adtim_timing_devinfo_t  __g_adtim6_timing_devinfo = {
    HC32_TIM6_BASE,                    /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIM6,                           /**< \brief ADTIM6�жϱ�� */
    __hc32f03x_plfm_adtim6_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim6_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief ADTIM6 �豸���� */
am_hc32_adtim_timing_dev_t __g_adtim6_timing_dev;

/** \brief ��ʱ��ADTIM6 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_tim6_timing_inst_init (void)
{
    return am_hc32_adtim_timing_init(&__g_adtim6_timing_dev,
                                       &__g_adtim6_timing_devinfo);
}

/** \brief ADTIM6 Timingʵ�����ʼ�� */
void am_hc32_tim6_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_adtim_timing_deinit(handle);
}

/**
  @}
 */

/* end of file */
