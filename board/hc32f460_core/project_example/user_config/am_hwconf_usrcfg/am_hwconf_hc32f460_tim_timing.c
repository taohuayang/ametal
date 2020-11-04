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
#include "am_hc32f460_tim_timing.h"
#include "hc32f460_inum.h"

/**
  \addtogroup am_if_src_hwconf_hc32f460_tim_timing
  \copydoc am_hwconf_hc32f460_tim_timing.c
  @{
 */

/*******************************************************************************
  TIM01 ����
*******************************************************************************/

/** \brief TIM01 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim01_timing_init (void)
{
    am_clk_enable(CLK_TIMER0_1);
}

/** \brief ��� TIM01 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim01_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER0_1);
}

/** \brief TIM01 �豸��Ϣ */
const am_hc32f460_tim_timing_devinfo_t  __g_tim01_timing_devinfo = {
    HC32F460_TIMER0_1_BASE,                /**< \brief TIM0�Ĵ�����Ļ���ַ */
    INUM_TIMER0_1,                         /**< \brief TIM0�жϱ�� */
    tim0_pclk1,                            /**< \brief Tim0_syncClockSource */
    tim0_XTAL32,                           /**< \brief Tim0_AsyncClockSource */
    tim0_sync,
    TIM0_CHANNEL_B,                        /**< \brief demo �е�Channel_num��Ҫ��Ӳ�������ļ�am_hwconf_hc32f460_tim_timing.cһ�� */
    __hc32f460_plfm_tim01_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_tim01_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM01 �豸���� */
am_hc32f460_tim_timing_dev_t __g_tim01_timing_dev;

/** \brief ��ʱ��TIM01 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim01_timing_inst_init (void)
{
    return am_hc32f460_tim_timing_init(&__g_tim01_timing_dev,
                                       &__g_tim01_timing_devinfo);
}

/** \brief TIM01 Timingʵ�����ʼ�� */
void am_hc32f460_tim01_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_tim_timing_deinit(handle);
}

/*******************************************************************************
  TIM02 ����
*******************************************************************************/

/** \brief TIM02 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim02_timing_init (void)
{
    am_clk_enable(CLK_TIMER0_2);
}

/** \brief ��� TIM02 ƽ̨��ʼ�� */
void __hc32f460_plfm_tim02_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER0_2);
}

/** \brief TIM02 �豸��Ϣ */
const am_hc32f460_tim_timing_devinfo_t  __g_tim02_timing_devinfo = {
    HC32F460_TIMER0_2_BASE,                /**< \brief TIM0�Ĵ�����Ļ���ַ */
    INUM_TIMER0_2,                         /**< \brief TIM0�жϱ�� */
    tim0_pclk1,                            /**< \brief Tim0_syncClockSource */
    tim0_XTAL32,                           /**< \brief Tim0_AsyncClockSource */
    tim0_sync,
    TIM0_CHANNEL_B,                        /**< \brief demo �е�Channel_num��Ҫ��Ӳ�������ļ�am_hwconf_hc32f460_tim_timing.cһ�� */
    __hc32f460_plfm_tim02_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_tim02_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM02 �豸���� */
am_hc32f460_tim_timing_dev_t __g_tim02_timing_dev;

/** \brief ��ʱ��TIM02 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim02_timing_inst_init (void)
{
    return am_hc32f460_tim_timing_init(&__g_tim02_timing_dev,
                                     &__g_tim02_timing_devinfo);
}

/** \brief TIM02 Timingʵ�����ʼ�� */
void am_hc32f460_tim02_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_tim_timing_deinit(handle);
}


/**
  @}
 */

/* end of file */
