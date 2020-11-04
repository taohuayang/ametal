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
 * \brief ZLG116 TIM���ڲ����ܵ��û������ļ�
 * \sa am_hwconf_zlg116_tim_cap.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg116.h"
#include "am_zlg_tim_cap.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg116_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_tim_cap
 * \copydoc am_hwconf_zlg116_tim_cap.c
 * @{
 */
 
/*******************************************************************************
 * TIM1 ����
 ******************************************************************************/

/** \brief TIM1���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim1_cap_init (void)
{

    /* ʹ�ܸ߼���ʱ��1ʱ�� */
    am_clk_enable(CLK_TIM1);

    /* ��λ�߼���ʱ��1 */
    am_zlg116_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
void __zlg_plfm_tim1_cap_deinit (void)
{

    /* ��λ�߼���ʱ��1 */
    am_zlg116_clk_reset(CLK_TIM1);

    /* ���ܸ߼���ʱ��1ʱ�� */
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim1_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_8,  PIOA_8_TIM1_CH1  | PIOA_8_INPUT_FLOAT,  PIOA_8_GPIO  | PIOA_8_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_9,  PIOA_9_TIM1_CH2  | PIOA_9_INPUT_FLOAT,  PIOA_9_GPIO  | PIOA_9_INPUT_FLOAT},

    /** \brief ͨ��3 */
    {PIOA_10, PIOA_10_TIM1_CH3 | PIOA_10_INPUT_FLOAT, PIOA_10_GPIO | PIOA_10_INPUT_FLOAT},

    /** \brief ͨ��4 */
    {PIOA_11, PIOA_11_TIM1_CH4 | PIOA_11_INPUT_FLOAT, PIOA_11_GPIO | PIOA_11_INPUT_FLOAT}
};

/** \brief TIM1���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim1_cap_devinfo = {
    ZLG116_TIM1_BASE,               /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1_CC,                   /**< \brief TIM1�жϱ�� */
    CLK_TIM1,                       /**< \brief TIM1ʱ��ID */
    4,                              /**< \brief 4������ͨ�� */
    &__g_tim1_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE0,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim1_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim1_cap_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM1���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim1_cap_dev;

/** \brief tim1 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg116_tim1_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim1_cap_dev,
                                  &__g_tim1_cap_devinfo);
}

/** \brief tim1 capʵ�����ʼ�� */
void am_zlg116_tim1_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM2 ����
 ******************************************************************************/

/** \brief TIM2���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim2_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��2ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λͨ�ö�ʱ��2 */
    am_zlg116_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
void __zlg_plfm_tim2_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��2 */
    am_zlg116_clk_reset(CLK_TIM2);

    /* ����ͨ�ö�ʱ��2ʱ�� */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim2_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_INPUT_FLOAT, PIOA_0_GPIO | PIOA_0_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_1, PIOA_1_TIM2_CH2     | PIOA_1_INPUT_FLOAT, PIOA_1_GPIO | PIOA_1_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_2, PIOA_2_TIM2_CH3     | PIOA_2_INPUT_FLOAT, PIOA_2_GPIO | PIOA_2_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_3, PIOA_3_TIM2_CH4     | PIOA_3_INPUT_FLOAT, PIOA_3_GPIO | PIOA_3_INPUT_FLOAT},
};

/** \brief TIM2���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim2_cap_devinfo = {
    ZLG116_TIM2_BASE,               /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                      /**< \brief TIM2�жϱ�� */
    CLK_TIM2,                       /**< \brief TIM2ʱ��ID */
    4,                              /**< \brief 4������ͨ�� */
    &__g_tim2_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE1,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim2_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim2_cap_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM2���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim2_cap_dev;

/** \brief tim2 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg116_tim2_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim2_cap_dev,
                                  &__g_tim2_cap_devinfo);
}

/** \brief tim2 capʵ�����ʼ�� */
void am_zlg116_tim2_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM3 ����
 ******************************************************************************/

/** \brief TIM3���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim3_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��3ʱ�� */
    am_clk_enable(CLK_TIM3);

    /* ��λͨ�ö�ʱ��3 */
    am_zlg116_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __zlg_plfm_tim3_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��3 */
    am_zlg116_clk_reset(CLK_TIM3);

    /* ����ͨ�ö�ʱ��3ʱ�� */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim3_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOB_4,  PIOB_4_TIM3_CH1 | PIOB_4_INPUT_FLOAT, PIOB_4_GPIO | PIOB_4_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOB_5,  PIOB_5_TIM3_CH2 | PIOB_5_INPUT_FLOAT, PIOB_5_GPIO | PIOB_5_INPUT_FLOAT},

    /** \brief ͨ��3 */
    {PIOB_0,  PIOB_0_TIM3_CH3 | PIOB_0_INPUT_FLOAT, PIOB_0_GPIO | PIOB_0_INPUT_FLOAT},

    /** \brief ͨ��4 */
    {PIOB_1,  PIOB_1_TIM3_CH4 | PIOB_1_INPUT_FLOAT, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},
};

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim3_cap_devinfo = {
    ZLG116_TIM3_BASE,               /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                      /**< \brief TIM3�жϱ�� */
    CLK_TIM3,                       /**< \brief TIM3ʱ��ID */
    4,                              /**< \brief 4������ͨ�� */
    &__g_tim3_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE1,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim3_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim3_cap_deinit      /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM3���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim3_cap_dev;

/** \brief tim3 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg116_tim3_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim3_cap_dev,
                                  &__g_tim3_cap_devinfo);
}

/** \brief tim3 capʵ�����ʼ�� */
void am_zlg116_tim3_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM14 ����
 ******************************************************************************/

/** \brief TIM14���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim14_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��14ʱ�� */
    am_clk_enable(CLK_TIM14);

    /* ��λͨ�ö�ʱ��14 */
    am_zlg116_clk_reset(CLK_TIM14);
}

/** \brief ���TIM14ƽ̨��ʼ�� */
void __zlg_plfm_tim14_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��14 */
    am_zlg116_clk_reset(CLK_TIM14);

    /* ����ͨ�ö�ʱ��14ʱ�� */
    am_clk_disable(CLK_TIM14);
}

/** \brief TIM14���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim14_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_4,  PIOA_4_TIM14_CH1 | PIOA_4_INPUT_FLOAT, PIOA_4_GPIO | PIOA_4_INPUT_FLOAT},
};

/** \brief TIM14���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim14_cap_devinfo = {
    ZLG116_TIM14_BASE,               /**< \brief TIM14�Ĵ�����Ļ���ַ */
    INUM_TIM14,                      /**< \brief TIM14�жϱ�� */
    CLK_TIM14,                       /**< \brief TIM14ʱ��ID */
    1,                               /**< \brief 1������ͨ�� */
    &__g_tim14_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE2,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim14_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim14_cap_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM14���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim14_cap_dev;

/** \brief tim14 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg116_tim14_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim14_cap_dev,
                                  &__g_tim14_cap_devinfo);
}

/** \brief tim14 capʵ�����ʼ�� */
void am_zlg116_tim14_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}


/*******************************************************************************
 * TIM16 ����
 ******************************************************************************/

/** \brief TIM16���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim16_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��16ʱ�� */
    am_clk_enable(CLK_TIM16);

    /* ��λͨ�ö�ʱ��16 */
    am_zlg116_clk_reset(CLK_TIM16);
}

/** \brief ���TIM16ƽ̨��ʼ�� */
void __zlg_plfm_tim16_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��16 */
    am_zlg116_clk_reset(CLK_TIM16);

    /* ����ͨ�ö�ʱ��16ʱ�� */
    am_clk_disable(CLK_TIM16);
}

/** \brief TIM16���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim16_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_6,  PIOA_6_TIM16_CH1 | PIOA_6_INPUT_FLOAT, PIOA_6_GPIO | PIOA_6_INPUT_FLOAT},
};

/** \brief TIM16���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim16_cap_devinfo = {
    ZLG116_TIM16_BASE,               /**< \brief TIM16�Ĵ�����Ļ���ַ */
    INUM_TIM16,                      /**< \brief TIM16�жϱ�� */
    CLK_TIM16,                       /**< \brief TIM16ʱ��ID */
    1,                               /**< \brief 1������ͨ�� */
    &__g_tim16_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE3,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim16_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim16_cap_deinit      /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM16���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim16_cap_dev;

/** \brief tim16 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg116_tim16_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim16_cap_dev,
                                  &__g_tim16_cap_devinfo);
}

/** \brief tim16 capʵ�����ʼ�� */
void am_zlg116_tim16_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM17 ����
 ******************************************************************************/

/** \brief TIM17���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim17_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��17ʱ�� */
    am_clk_enable(CLK_TIM17);

    /* ��λͨ�ö�ʱ��17 */
    am_zlg116_clk_reset(CLK_TIM17);
}

/** \brief ���TIM17ƽ̨��ʼ�� */
void __zlg_plfm_tim17_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��17 */
    am_zlg116_clk_reset(CLK_TIM17);

    /* ����ͨ�ö�ʱ��17ʱ�� */
    am_clk_disable(CLK_TIM17);
}

/** \brief TIM17���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim17_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_7, PIOA_7_TIM17_CH1 | PIOA_7_INPUT_FLOAT, PIOA_7_GPIO | PIOA_7_INPUT_FLOAT},
};

/** \brief TIM17���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim17_cap_devinfo = {
    ZLG116_TIM17_BASE,               /**< \brief TIM17�Ĵ�����Ļ���ַ */
    INUM_TIM17,                      /**< \brief TIM17�жϱ�� */
    CLK_TIM17,                       /**< \brief TIM17ʱ��ID */
    1,                               /**< \brief 1������ͨ�� */
    &__g_tim17_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE3,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim17_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim17_cap_deinit      /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM17���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim17_cap_dev;

/** \brief tim17 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg116_tim17_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim17_cap_dev,
                                  &__g_tim17_cap_devinfo);
}

/** \brief tim17 capʵ�����ʼ�� */
void am_zlg116_tim17_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/**
 * @}
 */

/* end of file */
