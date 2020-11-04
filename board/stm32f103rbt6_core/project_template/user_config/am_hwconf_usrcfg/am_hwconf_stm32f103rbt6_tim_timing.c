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
  \brief STM32F103RBT6 TIM ��ʱ�����û������ļ�
  \sa am_hwconf_stm32f103rbt6_tim_timing.c
 *
 *
  \internal
  \par Modification history
  - 1.00 17-08-25  zcb, first implementation
  \endinternal
 */

#include "am_stm32f103rbt6.h"
#include "ametal.h"
#include "am_clk.h"
#include "am_stm32f103rbt6_clk.h"
#include "am_stm32f103rbt6_tim_timing.h"

/**
  \addtogroup am_if_src_hwconf_stm32f103rbt6_tim_timing
  \copydoc am_hwconf_stm32f103rbt6_tim_timing.c
  @{
 */

/*******************************************************************************
  TIM1 ����
*******************************************************************************/

/** \brief TIM1 ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim1_timing_init (void)
{
    am_clk_enable(CLK_TIM1);
    am_stm32f103rbt6_clk_reset(CLK_TIM1);
}

/** \brief ��� TIM1 ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim1_timing_deinit (void)
{
    am_stm32f103rbt6_clk_reset(CLK_TIM1);
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1 �豸��Ϣ */
const am_stm32f103rbt6_tim_timing_devinfo_t  __g_tim1_timing_devinfo = {
    STM32F103RBT6_TIM1_BASE,                  /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1_UP,                      /**< \brief TIM1�жϱ�� */
    CLK_TIM1,                          /**< \brief TIM1ʱ��ID */
    AMHW_STM32F103RBT6_TIM_TYPE0,             /**< \brief ��ʱ������ */
    __stm32f103rbt6_plfm_tim1_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __stm32f103rbt6_plfm_tim1_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM1 �豸���� */
am_stm32f103rbt6_tim_timing_dev_t __g_tim1_timing_dev;

/** \brief ��ʱ��TIM1 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_stm32f103rbt6_tim1_timing_inst_init (void)
{
    return am_stm32f103rbt6_tim_timing_init(&__g_tim1_timing_dev,
                                     &__g_tim1_timing_devinfo);
}

/** \brief TIM1 Timingʵ�����ʼ�� */
void am_stm32f103rbt6_tim1_timing_inst_deinit (am_timer_handle_t handle)
{
    am_stm32f103rbt6_tim_timing_deinit(handle);
}

/*******************************************************************************
  TIM2 ����
*******************************************************************************/

/** \brief TIM2 ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim2_timing_init (void)
{
    am_clk_enable(CLK_TIM2);
    am_stm32f103rbt6_clk_reset(CLK_TIM2);
}

/** \brief ��� TIM2 ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim2_timing_deinit (void)
{
    am_stm32f103rbt6_clk_reset(CLK_TIM2);
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2 �豸��Ϣ */
const am_stm32f103rbt6_tim_timing_devinfo_t  __g_tim2_timing_devinfo = {
    STM32F103RBT6_TIM2_BASE,                  /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                         /**< \brief TIM2�жϱ�� */
    CLK_TIM2,                          /**< \brief TIM2ʱ��ID */
    AMHW_STM32F103RBT6_TIM_TYPE1,             /**< \brief ��ʱ������ */
    __stm32f103rbt6_plfm_tim2_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __stm32f103rbt6_plfm_tim2_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM2 �豸���� */
am_stm32f103rbt6_tim_timing_dev_t  __g_tim2_timing_dev;

/** \brief TIM2 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_stm32f103rbt6_tim2_timing_inst_init (void)
{
    return am_stm32f103rbt6_tim_timing_init(&__g_tim2_timing_dev,
                                     &__g_tim2_timing_devinfo);
}

/** \brief TIM2 Timingʵ�����ʼ�� */
void am_stm32f103rbt6_tim2_timing_inst_deinit (am_timer_handle_t handle)
{
    am_stm32f103rbt6_tim_timing_deinit(handle);
}

/*******************************************************************************
  TIM3����
*******************************************************************************/

/** \brief TIM3ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim3_timing_init (void)
{
    am_clk_enable(CLK_TIM3);
    am_stm32f103rbt6_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim3_timing_deinit (void)
{
    am_stm32f103rbt6_clk_reset(CLK_TIM3);
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3 �豸��Ϣ */
const am_stm32f103rbt6_tim_timing_devinfo_t  __g_tim3_timing_devinfo = {
    STM32F103RBT6_TIM3_BASE,                  /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                         /**< \brief TIM3�жϱ�� */
    CLK_TIM3,                          /**< \brief TIM3ʱ��ID */
    AMHW_STM32F103RBT6_TIM_TYPE1,             /**< \brief ��ʱ������ */
    __stm32f103rbt6_plfm_tim3_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __stm32f103rbt6_plfm_tim3_timing_deinit   /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM3�豸���� */
am_stm32f103rbt6_tim_timing_dev_t  __g_tim3_timing_dev;

/** \brief TIM3 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_stm32f103rbt6_tim3_timing_inst_init (void)
{
    return am_stm32f103rbt6_tim_timing_init(&__g_tim3_timing_dev,
                                     &__g_tim3_timing_devinfo);
}

/** \brief TIM3 Timingʵ�����ʼ�� */
void am_stm32f103rbt6_tim3_timing_inst_deinit (am_timer_handle_t handle)
{
    am_stm32f103rbt6_tim_timing_deinit(handle);
}

/*******************************************************************************
  TIM4����
*******************************************************************************/

/** \brief TIM4ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim4_timing_init (void)
{
    am_clk_enable(CLK_TIM4);
    am_stm32f103rbt6_clk_reset(CLK_TIM4);
}

/** \brief ���TIM4ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_tim4_timing_deinit (void)
{
    am_stm32f103rbt6_clk_reset(CLK_TIM4);
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4�豸��Ϣ */
const am_stm32f103rbt6_tim_timing_devinfo_t  __g_tim4_timing_devinfo = {
    STM32F103RBT6_TIM4_BASE,                  /**< \brief TIM4�Ĵ�����Ļ���ַ */
    INUM_TIM4,                         /**< \brief TIM4�жϱ�� */
    CLK_TIM4,                          /**< \brief TIM4ʱ��ID */
    AMHW_STM32F103RBT6_TIM_TYPE1,             /**< \brief ��ʱ������ */
    __stm32f103rbt6_plfm_tim4_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __stm32f103rbt6_plfm_tim4_timing_deinit   /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM4�豸���� */
am_stm32f103rbt6_tim_timing_dev_t  __g_tim4_timing_dev;

/** \brief TIM4 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_stm32f103rbt6_tim4_timing_inst_init (void)
{
    return am_stm32f103rbt6_tim_timing_init(&__g_tim4_timing_dev,
                                     &__g_tim4_timing_devinfo);
}

/** \brief TIM4 Timingʵ�����ʼ�� */
void am_stm32f103rbt6_tim4_timing_inst_deinit (am_timer_handle_t handle)
{
    am_stm32f103rbt6_tim_timing_deinit(handle);
}

/**
  @}
 */

/* end of file */
