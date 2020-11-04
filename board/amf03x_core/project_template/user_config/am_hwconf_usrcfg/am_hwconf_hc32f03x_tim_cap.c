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
 * \brief TIM ���ڲ����ܵ��û������ļ�
 * \sa am_hwconf_hc32f03x_tim_cap.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-12  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32.h"
#include "am_hc32_tim_cap.h"
#include "am_hc32_adtim_cap.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f03x_tim_cap
 * \copydoc am_hwconf_hc32f03x_tim_cap.c
 * @{
 */
/*******************************************************************************
  TIM0 ����
*******************************************************************************/

/** \brief TIM0���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim0_cap_init (void)
{
    am_clk_enable(CLK_TIM012);
}

/** \brief ���TIM0ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim0_cap_deinit (void)
{
    am_clk_disable(CLK_TIM012);
}

/** \brief TIM0���ڲ����ܵ�����������Ϣ�б� */
am_hc32_tim_cap_ioinfo_t __g_tim0_cap_ioinfo_list[] = {
    /**< \brief ͨ��0 */
    {
        AM_HC32_TIM_CAP_CH0A,
        PIOA_0,
        PIOA_0_TIM0_CHA  | PIOA_0_INPUT_FLOAT,
        PIOA_0_GPIO  | PIOA_0_INPUT_PU
    },

    /**< \brief ͨ��1 */
    {
        AM_HC32_TIM_CAP_CH0B,
        PIOA_1,
        PIOA_1_TIM0_CHB  | PIOA_1_INPUT_FLOAT,
        PIOA_1_GPIO  | PIOA_1_INPUT_PU
    },
};

/** \brief TIM0���ڲ����ܵ��豸��Ϣ */
const am_hc32_tim_cap_devinfo_t  __g_tim0_cap_devinfo = {
    HC32_TIM0_BASE,                   /**< \brief TIM0�Ĵ�����Ļ���ַ */
    INUM_TIM0,                          /**< \brief TIM0�жϱ�� */
    AMHW_HC32_TIM_CLK_DIV1,           /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                  /**< \brief 2������ͨ�� */
    AMHW_HC32_TIM_TYPE_TIM0,          /**< \brief ��ʱ��ѡ�� */

    &__g_tim0_cap_ioinfo_list[0],
    __hc32f03x_plfm_tim0_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim0_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM0���ڲ����ܵ��豸���� */
am_hc32_tim_cap_dev_t  __g_tim0_cap_dev;

/** \brief tim0 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32_tim0_cap_inst_init (void)
{
    return am_hc32_tim_cap_init(&__g_tim0_cap_dev,
                                  &__g_tim0_cap_devinfo);
}

/** \brief tim0 capʵ�����ʼ�� */
void am_hc32_tim0_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32_tim_cap_deinit(handle);
}

/*******************************************************************************
  TIM1 ����
*******************************************************************************/

/** \brief TIM1���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim1_cap_init (void)
{
    am_clk_enable(CLK_TIM012);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim1_cap_deinit (void)
{
    am_clk_disable(CLK_TIM012);
}

/** \brief TIM1���ڲ����ܵ�����������Ϣ�б� */
am_hc32_tim_cap_ioinfo_t __g_tim1_cap_ioinfo_list[] = {
    /**< \brief ͨ��0 */
    {
        AM_HC32_TIM_CAP_CH0A,
        PIOA_0,
        PIOA_0_TIM1_CHA  | PIOA_0_INPUT_FLOAT,
        PIOA_0_GPIO  | PIOA_0_INPUT_PU
    },

    /**< \brief ͨ��1 */
    {
        AM_HC32_TIM_CAP_CH0B,
        PIOA_1,
        PIOA_1_TIM1_CHB  | PIOA_1_INPUT_FLOAT,
        PIOA_1_GPIO  | PIOA_1_INPUT_PU
    },
};

/** \brief TIM1���ڲ����ܵ��豸��Ϣ */
const am_hc32_tim_cap_devinfo_t  __g_tim1_cap_devinfo = {
    HC32_TIM1_BASE,                   /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1,                          /**< \brief TIM1�жϱ�� */
    AMHW_HC32_TIM_CLK_DIV1,           /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                  /**< \brief 2������ͨ�� */
    AMHW_HC32_TIM_TYPE_TIM1,          /**< \brief ��ʱ��ѡ�� */

    &__g_tim1_cap_ioinfo_list[0],
    __hc32f03x_plfm_tim1_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim1_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM1���ڲ����ܵ��豸���� */
am_hc32_tim_cap_dev_t  __g_tim1_cap_dev;

/** \brief tim1 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32_tim1_cap_inst_init (void)
{
    return am_hc32_tim_cap_init(&__g_tim1_cap_dev,
                                  &__g_tim1_cap_devinfo);
}

/** \brief tim1 capʵ�����ʼ�� */
void am_hc32_tim1_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32_tim_cap_deinit(handle);
}

/*******************************************************************************
  TIM2 ����
*******************************************************************************/

/** \brief TIM2���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim2_cap_init (void)
{
    am_clk_enable(CLK_TIM012);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim2_cap_deinit (void)
{
    am_clk_disable(CLK_TIM012);
}

/** \brief TIM2���ڲ����ܵ�����������Ϣ�б� */
am_hc32_tim_cap_ioinfo_t __g_tim2_cap_ioinfo_list[] = {
    /**< \brief ͨ��0 */
    {
        AM_HC32_TIM_CAP_CH0A,
        PIOA_2,
        PIOA_2_TIM2_CHA  | PIOA_2_INPUT_FLOAT,
        PIOA_2_GPIO  | PIOA_2_INPUT_PU
    },

    /**< \brief ͨ��1 */
    {
        AM_HC32_TIM_CAP_CH0B,
        PIOA_3,
        PIOA_3_TIM2_CHB  | PIOA_3_INPUT_FLOAT,
        PIOA_3_GPIO  | PIOA_3_INPUT_PU
    },
};

/** \brief TIM2���ڲ����ܵ��豸��Ϣ */
const am_hc32_tim_cap_devinfo_t  __g_tim2_cap_devinfo = {
    HC32_TIM2_BASE,                   /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                          /**< \brief TIM2�жϱ�� */
    AMHW_HC32_TIM_CLK_DIV1,           /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                  /**< \brief 2������ͨ�� */
    AMHW_HC32_TIM_TYPE_TIM2,          /**< \brief ��ʱ��ѡ�� */

    &__g_tim2_cap_ioinfo_list[0],
    __hc32f03x_plfm_tim2_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim2_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM2���ڲ����ܵ��豸���� */
am_hc32_tim_cap_dev_t  __g_tim2_cap_dev;

/** \brief tim2 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32_tim2_cap_inst_init (void)
{
    return am_hc32_tim_cap_init(&__g_tim2_cap_dev,
                                  &__g_tim2_cap_devinfo);
}

/** \brief tim2 capʵ�����ʼ�� */
void am_hc32_tim2_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32_tim_cap_deinit(handle);
}

/*******************************************************************************
  TIM3 ����
*******************************************************************************/

/** \brief TIM3���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim3_cap_init (void)
{
    am_clk_enable(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __hc32f03x_plfm_tim3_cap_deinit (void)
{
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3���ڲ����ܵ�����������Ϣ�б� */
am_hc32_tim_cap_ioinfo_t __g_tim3_cap_ioinfo_list[] = {

    /**< \brief ͨ��0 */
    {
        AM_HC32_TIM_CAP_CH0A,
        PIOB_3,
        PIOB_3_TIM3_CH0A  | PIOB_3_INPUT_FLOAT ,
        PIOB_3_GPIO  | PIOB_3_INPUT_PU
    },
    /**< \brief ͨ��1 */
    {
        AM_HC32_TIM_CAP_CH0B,
        PIOB_4,
        PIOB_4_TIM3_CH0B  | PIOB_4_INPUT_FLOAT ,
        PIOB_4_GPIO  | PIOB_4_INPUT_PU
    },
    /**< \brief ͨ��2 */
    {
        AM_HC32_TIM_CAP_CH1A,
        PIOB_10,
        PIOB_10_TIM3_CH1A | PIOB_10_INPUT_FLOAT,
        PIOB_10_GPIO | PIOB_10_INPUT_PU
    },
    /**< \brief ͨ��3 */
    {
        AM_HC32_TIM_CAP_CH1B,
        PIOB_14,
        PIOB_14_TIM3_CH1B | PIOB_14_INPUT_FLOAT,
        PIOB_14_GPIO | PIOB_14_INPUT_PU
    },
    /**< \brief ͨ��4 */
    {
        AM_HC32_TIM_CAP_CH2A,
        PIOB_8,
        PIOB_8_TIM3_CH2A | PIOB_8_INPUT_FLOAT,
        PIOB_8_GPIO | PIOB_8_INPUT_PU
    },
    /**< \brief ͨ��5 */
    {
        AM_HC32_TIM_CAP_CH2B,
        PIOB_15,
        PIOB_15_TIM3_CH2B | PIOB_15_INPUT_FLOAT,
        PIOB_15_GPIO | PIOB_15_INPUT_PU
    },
};

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_hc32_tim_cap_devinfo_t  __g_tim3_cap_devinfo = {
    HC32_TIM3_BASE,                   /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                          /**< \brief TIM3�жϱ�� */
    AMHW_HC32_TIM_CLK_DIV1,           /**< \brief ʱ�ӷ�Ƶϵ�� */
    6,                                  /**< \brief 6������ͨ�� */
    AMHW_HC32_TIM_TYPE_TIM3,          /**< \brief ��ʱ��ѡ�� */

    &__g_tim3_cap_ioinfo_list[0],
    __hc32f03x_plfm_tim3_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_tim3_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM3���ڲ����ܵ��豸���� */
am_hc32_tim_cap_dev_t  __g_tim3_cap_dev;

/** \brief tim3 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32_tim3_cap_inst_init (void)
{
    return am_hc32_tim_cap_init(&__g_tim3_cap_dev,
                                  &__g_tim3_cap_devinfo);
}

/** \brief tim3 capʵ�����ʼ�� */
void am_hc32_tim3_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32_tim_cap_deinit(handle);
}

/*******************************************************************************
  ADTIM4 ����
*******************************************************************************/
/** \brief ADTIM4���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim4_cap_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ���ADTIM4ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim4_cap_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM4���ڲ����ܵ�����������Ϣ�б� */
am_hc32_adtim_cap_ioinfo_t __g_adtim4_cap_ioinfo_list[] = {
    {
        AM_HC32_ADTIM_CAP_CHA,
        PIOB_2,
        PIOB_2_TIM4_CHA  | PIOB_2_INPUT_FLOAT ,
        PIOB_2_GPIO  | PIOB_2_INPUT_PU
    },

    {
        AM_HC32_ADTIM_CAP_CHB,
        PIOA_7,
        PIOA_7_TIM4_CHB  | PIOA_7_INPUT_FLOAT ,
        PIOA_7_GPIO  | PIOA_7_INPUT_PU
    },
};

/** \brief ADTIM4���ڲ����ܵ��豸��Ϣ */
const am_hc32_adtim_cap_devinfo_t  __g_adtim4_cap_devinfo = {
    HC32_TIM4_BASE,                   /**< \brief ADTIM4�Ĵ�����Ļ���ַ */
    INUM_TIM4,                          /**< \brief ADTIM4�жϱ�� */
    AMHW_HC32_ADTIM_PCLK_DIV16,       /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                  /**< \brief 2������ͨ�� */

    &__g_adtim4_cap_ioinfo_list[0],     /**< \brief ����������Ϣ�б� */
    __hc32f03x_plfm_adtim4_cap_init,      /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim4_cap_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM4���ڲ����ܵ��豸���� */
am_hc32_adtim_cap_dev_t  __g_adtim4_cap_dev;

/** \brief adtim4 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32_tim4_cap_inst_init (void)
{
    return am_hc32_adtim_cap_init(&__g_adtim4_cap_dev,
                                    &__g_adtim4_cap_devinfo);
}

/** \brief adtim4 capʵ�����ʼ�� */
void am_hc32_tim4_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32_adtim_cap_deinit(handle);
}

/*******************************************************************************
  ADTIM5 ����
*******************************************************************************/
/** \brief ADTIM5���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim5_cap_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ���ADTIM5ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim5_cap_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM5���ڲ����ܵ�����������Ϣ�б� */
am_hc32_adtim_cap_ioinfo_t __g_adtim5_cap_ioinfo_list[] = {
    {
        AM_HC32_ADTIM_CAP_CHA,
        PIOA_3,
        PIOA_3_TIM5_CHA  | PIOA_3_INPUT_FLOAT ,
        PIOA_3_GPIO  | PIOA_3_INPUT_PU
    },

    {
        AM_HC32_ADTIM_CAP_CHB,
        PIOA_5,
        PIOA_5_TIM5_CHB  | PIOA_5_INPUT_FLOAT ,
        PIOA_5_GPIO  | PIOA_5_INPUT_PU
    },
};

/** \brief ADTIM5���ڲ����ܵ��豸��Ϣ */
const am_hc32_adtim_cap_devinfo_t  __g_adtim5_cap_devinfo = {
    HC32_TIM5_BASE,                   /**< \brief ADTIM5�Ĵ�����Ļ���ַ */
    INUM_TIM5,                          /**< \brief ADTIM5�жϱ�� */
    AMHW_HC32_ADTIM_PCLK_DIV16,        /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                  /**< \brief 2������ͨ�� */

    &__g_adtim5_cap_ioinfo_list[0],     /**< \brief ����������Ϣ�б� */
    __hc32f03x_plfm_adtim5_cap_init,      /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim5_cap_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM5���ڲ����ܵ��豸���� */
am_hc32_adtim_cap_dev_t  __g_adtim5_cap_dev;

/** \brief adtim5 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32_tim5_cap_inst_init (void)
{
    return am_hc32_adtim_cap_init(&__g_adtim5_cap_dev,
                                    &__g_adtim5_cap_devinfo);
}

/** \brief adtim5 capʵ�����ʼ�� */
void am_hc32_tim5_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32_adtim_cap_deinit(handle);
}

/*******************************************************************************
  ADTIM6 ����
*******************************************************************************/
/** \brief ADTIM6���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim6_cap_init (void)
{
    am_clk_enable(CLK_TIM456);
}

/** \brief ���ADTIM6ƽ̨��ʼ�� */
void __hc32f03x_plfm_adtim6_cap_deinit (void)
{
    am_clk_disable(CLK_TIM456);
}

/** \brief ADTIM6���ڲ����ܵ�����������Ϣ�б� */
am_hc32_adtim_cap_ioinfo_t __g_adtim6_cap_ioinfo_list[] = {
    {
        AM_HC32_ADTIM_CAP_CHA,
        PIOB_11,
        PIOB_11_TIM6_CHA | PIOB_11_INPUT_FLOAT ,
        PIOB_11_GPIO | PIOB_11_INPUT_PU
    },
    {
        AM_HC32_ADTIM_CAP_CHB,
        PIOB_1,
        PIOB_1_TIM6_CHB  | PIOB_1_INPUT_FLOAT ,
        PIOB_1_GPIO  | PIOB_1_INPUT_PU
    },
};

/** \brief ADTIM6���ڲ����ܵ��豸��Ϣ */
const am_hc32_adtim_cap_devinfo_t  __g_adtim6_cap_devinfo = {
    HC32_TIM6_BASE,                   /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIM6,                          /**< \brief ADTIM6�жϱ�� */
    AMHW_HC32_ADTIM_PCLK_DIV16,       /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                  /**< \brief 2������ͨ�� */

    &__g_adtim6_cap_ioinfo_list[0],     /**< \brief ����������Ϣ�б� */
    __hc32f03x_plfm_adtim6_cap_init,      /**< \brief ƽ̨��ʼ������ */
    __hc32f03x_plfm_adtim6_cap_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM6���ڲ����ܵ��豸���� */
am_hc32_adtim_cap_dev_t  __g_adtim6_cap_dev;

/** \brief adtim6 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32_tim6_cap_inst_init (void)
{
    return am_hc32_adtim_cap_init(&__g_adtim6_cap_dev,
                                    &__g_adtim6_cap_devinfo);
}

/** \brief adtim6 capʵ�����ʼ�� */
void am_hc32_tim6_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32_adtim_cap_deinit(handle);
}

/**
 * @}
 */

/* end of file */
