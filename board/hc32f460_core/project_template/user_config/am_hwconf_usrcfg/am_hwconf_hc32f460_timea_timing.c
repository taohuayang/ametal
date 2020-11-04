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
#include "am_hc32f460_timea_timing.h"
#include "hc32f460_inum.h"

/**
  \addtogroup am_if_src_hwconf_hc32f460_tim_timing
  \copydoc am_hwconf_hc32f460_tim_timing.c
  @{
 */
 
/*******************************************************************************
  TIMA1 ����
*******************************************************************************/

/** \brief TIMA1 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea1_timing_init (void)
{
    am_clk_enable(CLK_TIMERA_1);
}

/** \brief ��� TIMA1 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea1_timing_deinit (void)
{
    am_clk_disable(CLK_TIMERA_1);
}

/** \brief TIMA1 �豸��Ϣ */
const am_hc32f460_timea_timing_devinfo_t  __g_timea1_timing_devinfo = {
    HC32F460_TMRA1_BASE,                    /**< \brief TIMA1�Ĵ�����Ļ���ַ */
    INUM_TIMERA_1,                          /**< \brief TIMA1�жϱ�� */
    timea_count_mode_sawtooth_wave,
    timea_count_dir_up,
    0,                                      /**< \brief �Ƿ���ͬ��ģʽ(ʹ��ͬ��ģʽ����Ҫ����TMR1)*/
    __hc32f460_plfm_timea1_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea1_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIMA1 �豸���� */
am_hc32f460_timea_timing_dev_t __g_timea1_timing_dev;

/** \brief ��ʱ��TIMA1 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_timea1_timing_inst_init (void)
{
    return am_hc32f460_timea_timing_init(&__g_timea1_timing_dev,
                                         &__g_timea1_timing_devinfo);
}

/** \brief TIMA1 Timingʵ�����ʼ�� */
void am_hc32f460_timea1_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_timea_timing_deinit(handle);
}


/*******************************************************************************
  TIMA2 ����
*******************************************************************************/

/** \brief TIMA2 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea2_timing_init (void)
{
    am_clk_enable(CLK_TIMERA_2);
}

/** \brief ��� TIMA2 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea2_timing_deinit (void)
{
    am_clk_disable(CLK_TIMERA_2);
}

/** \brief TIMA2 �豸��Ϣ */
const am_hc32f460_timea_timing_devinfo_t  __g_timea2_timing_devinfo = {
    HC32F460_TMRA2_BASE,                   /**< \brief TIMA2�Ĵ�����Ļ���ַ */
    INUM_TIMERA_2,                         /**< \brief TIMA2�жϱ�� */
    timea_count_mode_sawtooth_wave,
    timea_count_dir_up,
    1,                                     /**< \brief �Ƿ���ͬ��ģʽ(ʹ��ͬ��ģʽ����Ҫ����TMR1)*/
    __hc32f460_plfm_timea2_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea2_timing_deinit   /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIMA2 �豸���� */
am_hc32f460_timea_timing_dev_t __g_timea2_timing_dev;

/** \brief ��ʱ��TIMA2 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_timea2_timing_inst_init (void)
{
    return am_hc32f460_timea_timing_init(&__g_timea2_timing_dev,
                                         &__g_timea2_timing_devinfo);
}

/** \brief TIMA2 Timingʵ�����ʼ�� */
void am_hc32f460_timea2_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_timea_timing_deinit(handle);
}

/*******************************************************************************
  TIMA3 ����
*******************************************************************************/

/** \brief TIMA3 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea3_timing_init (void)
{
    am_clk_enable(CLK_TIMERA_3);
}

/** \brief ��� TIMA3 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea3_timing_deinit (void)
{
    am_clk_disable(CLK_TIMERA_3);
}

/** \brief TIMA3 �豸��Ϣ */
const am_hc32f460_timea_timing_devinfo_t  __g_timea3_timing_devinfo = {
    HC32F460_TMRA3_BASE,                    /**< \brief TIMA3�Ĵ�����Ļ���ַ */
    INUM_TIMERA_3,                          /**< \brief TIMA3�жϱ�� */
    timea_count_mode_sawtooth_wave,
    timea_count_dir_up,
    1,                                      /**< \brief �Ƿ���ͬ��ģʽ(ʹ��ͬ��ģʽ����Ҫ����TMR1)*/
    __hc32f460_plfm_timea3_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea3_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIMA3 �豸���� */
am_hc32f460_timea_timing_dev_t __g_timea3_timing_dev;

/** \brief ��ʱ��TIMA3 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_timea3_timing_inst_init (void)
{
    return am_hc32f460_timea_timing_init(&__g_timea3_timing_dev,
                                         &__g_timea3_timing_devinfo);
}

/** \brief TIMA3 Timingʵ�����ʼ�� */
void am_hc32f460_timea3_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_timea_timing_deinit(handle);
}

/*******************************************************************************
  TIMA4 ����
*******************************************************************************/

/** \brief TIMA4 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea4_timing_init (void)
{
    am_clk_enable(CLK_TIMERA_4);
}

/** \brief ��� TIMA4 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea4_timing_deinit (void)
{
    am_clk_disable(CLK_TIMERA_4);
}

/** \brief TIMA4 �豸��Ϣ */
const am_hc32f460_timea_timing_devinfo_t  __g_timea4_timing_devinfo = {
    HC32F460_TMRA4_BASE,                    /**< \brief TIMA4�Ĵ�����Ļ���ַ */
    INUM_TIMERA_4,                          /**< \brief TIMA4�жϱ�� */
    timea_count_mode_sawtooth_wave,
    timea_count_dir_up,
    1,                                      /**< \brief �Ƿ���ͬ��ģʽ(ʹ��ͬ��ģʽ����Ҫ����TMR1)*/
    __hc32f460_plfm_timea4_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea4_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIMA4 �豸���� */
am_hc32f460_timea_timing_dev_t __g_timea4_timing_dev;

/** \brief ��ʱ��TIMA4 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_timea4_timing_inst_init (void)
{
    return am_hc32f460_timea_timing_init(&__g_timea4_timing_dev,
                                         &__g_timea4_timing_devinfo);
}

/** \brief TIMA4 Timingʵ�����ʼ�� */
void am_hc32f460_timea4_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_timea_timing_deinit(handle);
}

/*******************************************************************************
  TIMA5 ����
*******************************************************************************/

/** \brief TIMA5 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea5_timing_init (void)
{
    am_clk_enable(CLK_TIMERA_5);
}

/** \brief ��� TIMA5 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea5_timing_deinit (void)
{
    am_clk_disable(CLK_TIMERA_5);
}

/** \brief TIMA5 �豸��Ϣ */
const am_hc32f460_timea_timing_devinfo_t  __g_timea5_timing_devinfo = {
    HC32F460_TMRA5_BASE,                    /**< \brief TIMA�Ĵ�����Ļ���ַ */
    INUM_TIMERA_5,                          /**< \brief TIMA5�жϱ�� */
    timea_count_mode_sawtooth_wave,
    timea_count_dir_up,
    1,                                      /**< \brief �Ƿ���ͬ��ģʽ(ʹ��ͬ��ģʽ����Ҫ����TMR1)*/
    __hc32f460_plfm_timea5_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea5_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIMA5 �豸���� */
am_hc32f460_timea_timing_dev_t __g_timea5_timing_dev;

/** \brief ��ʱ��TIMA5 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_timea5_timing_inst_init (void)
{
    return am_hc32f460_timea_timing_init(&__g_timea5_timing_dev,
                                         &__g_timea5_timing_devinfo);
}

/** \brief TIMA5 Timingʵ�����ʼ�� */
void am_hc32f460_timea5_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_timea_timing_deinit(handle);
}

/*******************************************************************************
  TIMA6 ����
*******************************************************************************/

/** \brief TIMA6 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea6_timing_init (void)
{
    am_clk_enable(CLK_TIMERA_6);
}

/** \brief ��� TIMA6 ƽ̨��ʼ�� */
void __hc32f460_plfm_timea6_timing_deinit (void)
{
    am_clk_disable(CLK_TIMERA_6);
}

/** \brief TIMA6 �豸��Ϣ */
const am_hc32f460_timea_timing_devinfo_t  __g_timea6_timing_devinfo = {
    HC32F460_TMRA6_BASE,                    /**< \brief TIMA�Ĵ�����Ļ���ַ */
    INUM_TIMERA_6,                          /**< \brief TIM0�жϱ�� */
    timea_count_mode_sawtooth_wave,
    timea_count_dir_up,
    1,                                      /**< \brief �Ƿ���ͬ��ģʽ(ʹ��ͬ��ģʽ����Ҫ����TMR1)*/
    __hc32f460_plfm_timea6_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea6_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIMA6 �豸���� */
am_hc32f460_timea_timing_dev_t __g_timea6_timing_dev;

/** \brief ��ʱ��TIMA6 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_hc32f460_timea6_timing_inst_init (void)
{
    return am_hc32f460_timea_timing_init(&__g_timea6_timing_dev,
                                         &__g_timea6_timing_devinfo);
}

/** \brief TIMA6 Timingʵ�����ʼ�� */
void am_hc32f460_timea6_timing_inst_deinit (am_timer_handle_t handle)
{
    am_hc32f460_timea_timing_deinit(handle);
}

/**
  @}
 */

/* end of file */
