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
  \brief HC32F460 TIM ��ʱ�����û������ļ�
  \sa am_hwconf_hc32f460_tim_timing.c
 *
 *
  \internal
  \par Modification history
  - 1.00 
  \endinternal
 */

#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32f460_clk.h"
#include "am_hc32f460_tim4_timing.h"
#include "hc32f460_inum.h"

/**
  \addtogroup am_if_src_hwconf_hc32f460_tim_timing
  \copydoc am_hwconf_hc32f460_tim_timing.c
  @{
 */
 
/*******************************************************************************
  TIM41 ����
*******************************************************************************/

/** \brief TIM41 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim41_timing_init (void)
{
    am_clk_enable(CLK_TIMER4_1);
}

/** \brief ��� TIM41 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim41_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER4_1);
}

/** \brief TIM41 �豸��Ϣ */
const am_hc32f460_tim4_timing_devinfo_t  __g_tim41_timing_devinfo = {
    HC32F460_TMR41_BASE,                   /**< \brief TIMA�Ĵ�����Ļ���ַ */
    INUM_TIMER4_1,                         /**< \brief TIM0�жϱ�� */
    TIM4_COUNT_MODE_SAWTOOTH_WAVE,
    __hc32f460_plfm_tim41_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_tim41_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM41 �豸���� */
am_hc32f460_tim4_timing_dev_t __g_tim41_timing_dev;

/** \brief ��ʱ��TIM41 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim41_timing_inst_init (void)
{
    return am_hc32f460_tim4_timing_init(&__g_tim41_timing_dev,
                                        &__g_tim41_timing_devinfo);
}

/** \brief TIM41 Timingʵ�����ʼ�� */
void am_hc32f460_tim41_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_tim4_timing_deinit(handle);
}

/*******************************************************************************
  TIM42 ����
*******************************************************************************/

/** \brief TIM42 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim42_timing_init (void)
{
    am_clk_enable(CLK_TIMER4_2);
}

/** \brief ��� TIM42 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim42_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER4_2);
}

/** \brief TIM42 �豸��Ϣ */
const am_hc32f460_tim4_timing_devinfo_t  __g_tim42_timing_devinfo = {
    HC32F460_TMR42_BASE,                   /**< \brief TIMA�Ĵ�����Ļ���ַ */
    INUM_TIMER4_2,                         /**< \brief TIM0�жϱ�� */
    TIM4_COUNT_MODE_SAWTOOTH_WAVE,
    __hc32f460_plfm_tim42_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_tim42_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM42 �豸���� */
am_hc32f460_tim4_timing_dev_t __g_tim42_timing_dev;

/** \brief ��ʱ��TIM42 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim42_timing_inst_init (void)
{
    return am_hc32f460_tim4_timing_init(&__g_tim42_timing_dev,
                                        &__g_tim42_timing_devinfo);
}

/** \brief TIM42 Timingʵ�����ʼ�� */
void am_hc32f460_tim42_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_tim4_timing_deinit(handle);
}

/*******************************************************************************
  TIM43 ����
*******************************************************************************/

/** \brief TIM43 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim43_timing_init (void)
{
    am_clk_enable(CLK_TIMER4_3);
}

/** \brief ��� TIM43 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim43_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER4_3);
}

/** \brief TIM43 �豸��Ϣ */
const am_hc32f460_tim4_timing_devinfo_t  __g_tim43_timing_devinfo = {
    HC32F460_TMR43_BASE,                   /**< \brief TIMA�Ĵ�����Ļ���ַ */
    INUM_TIMER4_3,                         /**< \brief TIM0�жϱ�� */
    TIM4_COUNT_MODE_SAWTOOTH_WAVE,
    __hc32f460_plfm_tim43_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_tim43_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM43 �豸���� */
am_hc32f460_tim4_timing_dev_t __g_tim43_timing_dev;

/** \brief ��ʱ��TIM43 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim43_timing_inst_init (void)
{
    return am_hc32f460_tim4_timing_init(&__g_tim43_timing_dev,
                                     &__g_tim43_timing_devinfo);
}

/** \brief TIM43 Timingʵ�����ʼ�� */
void am_hc32f460_tim43_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_tim4_timing_deinit(handle);
}

/**
  @}
 */

/* end of file */
