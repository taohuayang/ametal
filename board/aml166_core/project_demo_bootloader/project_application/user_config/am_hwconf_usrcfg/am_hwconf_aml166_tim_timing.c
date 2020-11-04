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
 * \brief ZLG116 TIM ��ʱ�����û������ļ�
 * \sa am_hwconf_zlg116_tim_timing.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_clk.h"
#include "am_zlg116.h"
#include "am_zlg116_clk.h"
#include "am_zlg_tim_timing.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_tim_timing
 * \copydoc am_hwconf_zlg116_tim_timing.c
 * @{
 */

/*******************************************************************************
 * TIM1 ����
 ******************************************************************************/

/** \brief TIM1 ƽ̨��ʼ�� */
void __zlg_plfm_tim1_timing_init (void)
{

    /* ʹ�ܸ߼���ʱ��1ʱ�� */
    am_clk_enable(CLK_TIM1);

    /* ��λ�߼���ʱ��1 */
    am_zlg116_clk_reset(CLK_TIM1);
}

/** \brief ��� TIM1 ƽ̨��ʼ�� */
void __zlg_plfm_tim1_timing_deinit (void)
{

    /* ��λ�߼���ʱ��1 */
    am_zlg116_clk_reset(CLK_TIM1);

    /* ���ܸ߼���ʱ��1ʱ�� */
    am_clk_disable(CLK_TIM1);
}


/** \brief TIM1 �豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim1_timing_devinfo = {
    ZLG116_TIM1_BASE,                /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1_BRK_UP_TRG_COM,        /**< \brief TIM1�жϱ�� */
    CLK_TIM1,                        /**< \brief TIM1ʱ��ID */
    AMHW_ZLG_TIM_TYPE0,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim1_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim1_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM1 �豸���� */
am_zlg_tim_timing_dev_t  __g_tim1_timing_dev;

/** \brief ��ʱ��TIM1 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zlg116_tim1_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim1_timing_dev,
                                  &__g_tim1_timing_devinfo);
}

/** \brief TIM1 Timingʵ�����ʼ�� */
void am_zlg116_tim1_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM2 ����
 ******************************************************************************/

/** \brief TIM2 ƽ̨��ʼ�� */
void __zlg_plfm_tim2_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��2ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λͨ�ö�ʱ��2 */
    am_zlg116_clk_reset(CLK_TIM2);
}

/** \brief ��� TIM2 ƽ̨��ʼ�� */
void __zlg_plfm_tim2_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��2 */
    am_zlg116_clk_reset(CLK_TIM2);

    /* ����ͨ�ö�ʱ��2ʱ�� */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2 �豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim2_timing_devinfo = {
    ZLG116_TIM2_BASE,                /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                       /**< \brief TIM2�жϱ�� */
    CLK_TIM2,                        /**< \brief TIM2ʱ��ID */
    AMHW_ZLG_TIM_TYPE1,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim2_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim2_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM2 �豸���� */
am_zlg_tim_timing_dev_t  __g_tim2_timing_dev;

/** \brief TIM2 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zlg116_tim2_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim2_timing_dev,
                                  &__g_tim2_timing_devinfo);
}

/** \brief TIM2 Timingʵ�����ʼ�� */
void am_zlg116_tim2_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}


/*******************************************************************************
 * TIM3����
 ******************************************************************************/
/** \brief TIM3ƽ̨��ʼ�� */
void __zlg_plfm_tim3_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��3ʱ�� */
    am_clk_enable(CLK_TIM3);

    /* ��λͨ�ö�ʱ��3 */
    am_zlg116_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __zlg_plfm_tim3_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��3 */
    am_zlg116_clk_reset(CLK_TIM3);

    /* ����ͨ�ö�ʱ��3ʱ�� */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3 �豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim3_timing_devinfo = {
    ZLG116_TIM3_BASE,                /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                       /**< \brief TIM3�жϱ�� */
    CLK_TIM3,                        /**< \brief TIM3ʱ��ID */
    AMHW_ZLG_TIM_TYPE2,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim3_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim3_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM3�豸���� */
am_zlg_tim_timing_dev_t  __g_tim3_timing_dev;

/** \brief TIM3 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zlg116_tim3_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim3_timing_dev,
                                  &__g_tim3_timing_devinfo);
}

/** \brief TIM3 Timingʵ�����ʼ�� */
void am_zlg116_tim3_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM14����
 ******************************************************************************/
/** \brief TIM14ƽ̨��ʼ�� */
void __zlg_plfm_tim14_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��14ʱ�� */
    am_clk_enable(CLK_TIM14);

    /* ��λͨ�ö�ʱ��14 */
    am_zlg116_clk_reset(CLK_TIM14);
}

/** \brief ���TIM14ƽ̨��ʼ�� */
void __zlg_plfm_tim14_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��14 */
    am_zlg116_clk_reset(CLK_TIM14);

    /* ����ͨ�ö�ʱ��14ʱ�� */
    am_clk_disable(CLK_TIM14);
}

/** \brief TIM14�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim14_timing_devinfo = {
    ZLG116_TIM14_BASE,                /**< \brief TIM14�Ĵ�����Ļ���ַ */
    INUM_TIM14,                       /**< \brief TIM14�жϱ�� */
    CLK_TIM14,                        /**< \brief TIM14ʱ��ID */
    AMHW_ZLG_TIM_TYPE3,               /**< \brief ��ʱ������ */
    __zlg_plfm_tim14_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim14_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM14�豸���� */
am_zlg_tim_timing_dev_t  __g_tim14_timing_dev;

/** \brief TIM14 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zlg116_tim14_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim14_timing_dev,
                                  &__g_tim14_timing_devinfo);
}

/** \brief TIM14 Timingʵ�����ʼ�� */
void am_zlg116_tim14_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM16����
 ******************************************************************************/

/** \brief TIM16ƽ̨��ʼ�� */
void __zlg_plfm_tim16_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��16ʱ�� */
    am_clk_enable(CLK_TIM16);

    /* ��λͨ�ö�ʱ��16 */
    am_zlg116_clk_reset(CLK_TIM16);
}

/** \brief ���TIM16ƽ̨��ʼ�� */
void __zlg_plfm_tim16_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��16 */
    am_zlg116_clk_reset(CLK_TIM16);

    /* ����ͨ�ö�ʱ��16ʱ�� */
    am_clk_disable(CLK_TIM16);
}

/** \brief TIM16�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim16_timing_devinfo = {
    ZLG116_TIM16_BASE,                /**< \brief TIM16�Ĵ�����Ļ���ַ */
    INUM_TIM16,                       /**< \brief TIM16�жϱ�� */
    CLK_TIM16,                        /**< \brief TIM16ʱ��ID */
    AMHW_ZLG_TIM_TYPE3,               /**< \brief ��ʱ������ */
    __zlg_plfm_tim16_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim16_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM16�豸���� */
am_zlg_tim_timing_dev_t  __g_tim16_timing_dev;

/** \brief ��ʱ��TIM16 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zlg116_tim16_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim16_timing_dev,
                                  &__g_tim16_timing_devinfo);
}

/** \brief TIM16 Timingʵ�����ʼ�� */
void am_zlg116_tim16_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM17����
 ******************************************************************************/

/** \brief TIM17ƽ̨��ʼ�� */
void __zlg_plfm_tim17_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��17ʱ�� */
    am_clk_enable(CLK_TIM17);

    /* ��λͨ�ö�ʱ��17 */
    am_zlg116_clk_reset(CLK_TIM17);
}

/** \brief ���TIM17ƽ̨��ʼ�� */
void __zlg_plfm_tim17_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��17 */
    am_zlg116_clk_reset(CLK_TIM17);

    /* ����ͨ�ö�ʱ��17ʱ�� */
    am_clk_disable(CLK_TIM17);
}

/** \brief TIM17�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim17_timing_devinfo = {
    ZLG116_TIM17_BASE,                /**< \brief TIM17�Ĵ�����Ļ���ַ */
    INUM_TIM17,                       /**< \brief TIM17�жϱ�� */
    CLK_TIM17,                        /**< \brief TIM17ʱ��ID */
    AMHW_ZLG_TIM_TYPE3,               /**< \brief ��ʱ������ */
    __zlg_plfm_tim17_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim17_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM17�豸���� */
am_zlg_tim_timing_dev_t  __g_tim17_timing_dev;

/** \brief ��ʱ��TIM17 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zlg116_tim17_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim17_timing_dev,
                                     &__g_tim17_timing_devinfo);
}

/** \brief TIM17 Timingʵ�����ʼ�� */
void am_zlg116_tim17_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/**
 * @}
 */

/* end of file */
