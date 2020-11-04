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
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_hc32f460_clk.h"
#include "am_hc32f460_adtim_timing.h"

/**
  \addtogroup am_if_src_hwconf_hc32f460_tim_timing
  \copydoc am_hwconf_hc32f460_tim_timing.c
  @{
 */
/*******************************************************************************
  ADTIM61 ����
*******************************************************************************/

/** \brief ADTIM6 ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim61_timing_init (void)
{
    am_clk_enable(CLK_TIMER6_1);
}

/** \brief ��� ADTIM6 ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim61_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER6_1);
}

/** \brief ADTIM6 �豸��Ϣ */
const am_hc32f460_adtim_timing_devinfo_t  __g_adtim61_timing_devinfo = {
    HC32F460_TMR61_BASE,                    /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIMER6_1,                          /**< \brief ADTIM6�жϱ�� */
    __hc32f460_plfm_adtim61_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim61_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief ADTIM6 �豸���� */
am_hc32f460_adtim_timing_dev_t __g_adtim61_timing_dev;

/** \brief ��ʱ��ADTIM6 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim61_timing_inst_init (void)
{
    return am_hc32f460_adtim_timing_init(&__g_adtim61_timing_dev,
                                         &__g_adtim61_timing_devinfo);
}

/** \brief ADTIM6 Timingʵ�����ʼ�� */
void am_hc32f460_tim61_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_adtim_timing_deinit(handle);
}

/*******************************************************************************
  ADTIM62 ����
*******************************************************************************/
/** \brief ADTIM6 ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim62_timing_init (void)
{
    am_clk_enable(CLK_TIMER6_2);
}

/** \brief ��� ADTIM6 ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim62_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER6_2);
}

/** \brief ADTIM6 �豸��Ϣ */
const am_hc32f460_adtim_timing_devinfo_t  __g_adtim62_timing_devinfo = {
    HC32F460_TMR62_BASE,                    /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIMER6_2,                          /**< \brief ADTIM6�жϱ�� */
    __hc32f460_plfm_adtim62_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim62_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief ADTIM6 �豸���� */
am_hc32f460_adtim_timing_dev_t __g_adtim62_timing_dev;

/** \brief ��ʱ��ADTIM6 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim62_timing_inst_init (void)
{
    return am_hc32f460_adtim_timing_init(&__g_adtim62_timing_dev,
                                         &__g_adtim62_timing_devinfo);
}

/** \brief ADTIM6 Timingʵ�����ʼ�� */
void am_hc32f460_tim62_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_adtim_timing_deinit(handle);
}

/*******************************************************************************
  ADTIM63 ����
*******************************************************************************/
/** \brief ADTIM6 ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim63_timing_init (void)
{
    am_clk_enable(CLK_TIMER6_3);
}

/** \brief ��� ADTIM6 ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim63_timing_deinit (void)
{
    am_clk_disable(CLK_TIMER6_3);
}

/** \brief ADTIM6 �豸��Ϣ */
const am_hc32f460_adtim_timing_devinfo_t  __g_adtim63_timing_devinfo = {
    HC32F460_TMR63_BASE,                    /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIMER6_3,                          /**< \brief ADTIM6�жϱ�� */
    __hc32f460_plfm_adtim63_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim63_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief ADTIM6 �豸���� */
am_hc32f460_adtim_timing_dev_t __g_adtim63_timing_dev;

/** \brief ��ʱ��ADTIM6 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_tim63_timing_inst_init (void)
{
    return am_hc32f460_adtim_timing_init(&__g_adtim63_timing_dev,
                                         &__g_adtim63_timing_devinfo);
}

/** \brief ADTIM6 Timingʵ�����ʼ�� */
void am_hc32f460_tim63_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_adtim_timing_deinit(handle);
}

/**
  @}
 */

/* end of file */
