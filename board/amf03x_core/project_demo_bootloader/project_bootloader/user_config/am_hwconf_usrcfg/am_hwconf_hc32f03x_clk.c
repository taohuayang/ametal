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
 * \brief HC32 CLK �û������ļ�
 * \sa am_hwconf_hc32_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */
#include "am_gpio.h"

#include "am_hc32_clk.h"
#include "hw/amhw_hc32_rcc.h"
#include "hc32x3x_pin.h"
/**
 * \addtogroup am_if_src_hwconf_hc32_clk
 * \copydoc am_hwconf_hc32_clk.c
 * @{
 */
/** \brief CLK ƽ̨��ʼ�� */
static void __hc32_clk_plfm_init (void)
{
}

/** \brief CLK ��ƽ̨��ʼ�� */
static void __hc32_clk_plfm_deinit (void)
{
}

/*
 * PLL����ѡ��XTH�������ɵ�ʱ�ӡ�XTH�ӹܽ�PF00�����ʱ�ӡ�RCHʱ����ΪPLLʱ��Դ
 * ����������PLL�ı�Ƶϵ��������õ�һ��Ƶ�ʣ��Ӷ���������ϵͳʱ�ӡ�
 *
 * ϵͳʱ��Դ��ѡ����Ҫ�����֣�  RCH  ---  �ڲ�����ʱ��
 *                       XTH  ---  �ⲿ����ʱ��
 *                       RCL  ---  �ڲ�����ʱ��
 *                       XTL  ---  �ⲿ����ʱ��
 *                       PLL  ---  �ڲ�PLL���ʱ��  = PLL����ʱ�� * PLL��Ƶϵ��
 *
 * ϵͳʱ��Դѡ������õ����¹�ϵ
 *
 * SYSCLK = ��ѡ���ϵͳʱ��Դ
 * HCLK   = SYSCLK / (2 ^ hclk_div)
 * PCLK   = HCLK   / (2 ^ pclk_div)
 *
 * \note ϵͳ����DeepSleepģʽ������ʱ�ӣ�RCH��XTH���Զ��رգ�
 *       ���ֶ��л�������ʱ�ӣ�RCL��XTL����Ϊϵͳʱ��Դ��
 */
/** \brief CLK�豸��Ϣ */
static const am_hc32_clk_devinfo_t __g_clk_devinfo =
{
    /**
     * \brief XTH�ⲿ����ʱ�Ӿ���Ƶ�ʣ�Hz��
     */
    32000000,

    /**
     * \brief XTL�ⲿ����ʱ�Ӿ���Ƶ�ʣ�Hz��
     */
    32768,

    /**
     * \brief RCH�ڲ�����ʱ�Ӿ���Ƶ�ʣ�Hz��
     *
     * \note Ƶ��ѡ��    24M�� 22.12M��16M�� 8M��4M
     *       ��������Ƶ�ʣ���Ĭ��ʹ��4M
     */
    AMHW_HC32_RCH_FRE_4MHz,

    /**
     * \brief RCL�ڲ�����ʱ�Ӿ���Ƶ�ʣ�Hz��
     *
     * \note Ƶ��ѡ��    38.4k  ��      32.768K
     *       ��������Ƶ�ʣ���Ĭ��ʹ��38.4k
     */
    AMHW_HC32_RCl_FRE_38400Hz,

    /** \brief
     *    PLLʱ��Դѡ��
     *    -# AMHW_HC32_PLL_INPUT_FRE_SRC_XTH_XTAL : XTH�������ɵ�ʱ��
     *    -# AMHW_HC32_PLL_INPUT_FRE_SRC_XTH_PF00 : XTH�ӹܽ�PF00�����ʱ��
     *    -# AMHW_HC32_PLL_INPUT_FRE_SRC_RCH      : RCHʱ��
     */
    AMHW_HC32_PLL_INPUT_FRE_SRC_RCH,

    /**
     * \brief PLL ��Ƶϵ��������Χ 2 ~ 12
     *        PLLOUT = PLLIN * pll_mul
     */
    12,

    /** \brief
     *    ϵͳ ʱ��Դѡ��
     *    -# AMHW_HC32_SYSCLK_RCH : �ڲ�����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32_SYSCLK_XTH : �ⲿ����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32_SYSCLK_RCL : �ڲ�����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32_SYSCLK_XTL ��  �ⲿ����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32_SYSCLK_PLL �� �ڲ�PLL��Ϊϵͳʱ��
     */
    AMHW_HC32_SYSCLK_PLL,

    /**
     * \brief HCLK��Ƶϵ����HCLK = SYSCLK / (2 ^ hclk_div)
     */
    0,

    /**
     * \brief PCLK��Ƶϵ����PCLK = HCLK / (2 ^ pclk_div)
     */
    1,

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    __hc32_clk_plfm_init,

    /** \brief ƽ̨���ʼ������ */
    __hc32_clk_plfm_deinit,
};

/** \brief ʱ���豸ʵ�� */
static am_hc32_clk_dev_t __g_clk_dev;

/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 */
int am_hc32_clk_inst_init (void)
{
    return am_hc32_clk_init(&__g_clk_dev, &__g_clk_devinfo);
}

/**
 * @}
 */

/* end of file */
