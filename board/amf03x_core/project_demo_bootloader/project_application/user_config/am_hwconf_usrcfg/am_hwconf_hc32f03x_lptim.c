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
  \brief HC32 LPTIM ��ʱ�����û������ļ�
  \sa am_hwconf_hc32f03x_lptim_timing.c
 *
 *
  \internal
  \par Modification history
  - 1.00 19-09-27  zp, first implementation
  \endinternal
 */

#include "ametal.h"
#include "am_clk.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "am_hc32_clk.h"
#include "am_hc32_lptim_timing.h"

/**
  \addtogroup am_if_src_hwconf_hc32f03x_lptim_timing
  \copydoc am_hwconf_hc32f03x_lptim_timing.c
  @{
 */

/*******************************************************************************
  lptim1 ����
*******************************************************************************/

/** \brief LPTIM0 ƽ̨��ʼ�� */
void __hc32f03x_plfm_lptim0_timing_init (void)
{
    /* ����GATE���ţ���ʵ���ſع��� */
    am_gpio_pin_cfg(PIOB_3, PIOB_3_INPUT_FLOAT | PIOB_3_LPTIM0_GATE);

    /* ����ETR���ţ����ⲿʱ����Ϊ����ʱ�ӹ��� */
    am_gpio_pin_cfg(PIOB_4, PIOB_4_INPUT_FLOAT | PIOB_4_LPTIM0_ETR);

    /* ����TOG��TOGN���ţ������ص�ƽ */
    am_gpio_pin_cfg(PIOC_1, PIOC_1_OUT_PP | PIOC_1_LPTIM0_TOG);
    am_gpio_pin_cfg(PIOC_2, PIOC_2_OUT_PP | PIOC_2_LPTIM0_TOGN);

    am_clk_enable(CLK_LPTIM0);
}

/** \brief ��� LPTIM0 ƽ̨��ʼ�� */
void __hc32f03x_plfm_lptim0_timing_deinit (void)
{
    am_gpio_pin_cfg(PIOB_3, PIOB_3_INPUT_PU | PIOB_3_GPIO);
    am_gpio_pin_cfg(PIOB_4, PIOB_4_INPUT_PU | PIOB_4_GPIO);
    am_gpio_pin_cfg(PIOC_1, PIOC_1_INPUT_PU | PIOC_1_GPIO);
    am_gpio_pin_cfg(PIOC_2, PIOC_2_INPUT_PU | PIOC_2_GPIO);

    am_clk_disable(CLK_LPTIM0);
}

/** \brief LPTIM0 �豸��Ϣ */
const am_hc32_lptim_timing_devinfo_t  __g_lptim0_timing_devinfo = {
    HC32_LPTIM0_BASE,                  /**< \brief LPTIM0�Ĵ�����Ļ���ַ */
    INUM_LPTIM0_1,                       /**< \brief LPTIM0�жϱ�� */
    AMHW_HC32_LPTIM_CLK_SRC_PCLK,      /**< \brief ʱ��Դѡ�� */
    AMHW_HC32_LPTIM_FUNCTION_TIMER,    /**< \brief ��ʱ��/����������ѡ��
                                          *
                                          *��������������Ҫ��ʼ�����ETR���ţ�
                                          *
                                          */
    AMHW_HC32_LPTIM_MODE_RELOAD,       /**< \brief �Զ�����ģʽ */
    AM_FALSE,                            /**< \brief �ſ�״̬��Ĭ�Ϲرգ� */
    AM_TRUE,                             /**< \brief �ſ��ź�Ϊ�棨1����Ч */
    AM_TRUE,                             /**< \brief TOG��TOGN���ʹ��
                                          *
                                          *    AM_FALSE �� TOG,TOGNͬʱ���0
                                          *    AM_TRUE  �� TOG,TOGN�����λ�෴���ź�
                                          *
                                          */

    __hc32f03x_plfm_lptim0_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_lptim0_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief LPTIM0 �豸���� */
am_hc32_lptim_timing_dev_t __g_lptim0_timing_dev;

/** \brief ��ʱ��LPTIM0 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32_lptim0_timing_inst_init (void)
{
    return am_hc32_lptim_timing_init(&__g_lptim0_timing_dev,
                                       &__g_lptim0_timing_devinfo);
}

/** \brief LPTIM0 Timingʵ�����ʼ�� */
void am_hc32_lptim0_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32_lptim_timing_deinit(handle);
}

/**
  @}
 */

/* end of file */
