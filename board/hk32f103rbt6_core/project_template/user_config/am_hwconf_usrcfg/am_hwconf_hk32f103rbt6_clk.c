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
 * \brief HK32F103RBT6 CLK �û������ļ�
 * \sa am_hwconf_hk32f103rbt6_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */
#include "hk32f103rbt6_pin.h"
#include "am_gpio.h"
#include "am_hk32f103rbt6_clk.h"
#include "amhw_hk32f103rbt6_rcc.h"
/**
 * \addtogroup am_if_src_hwconf_hk32f103rbt6_clk
 * \copydoc am_hwconf_hk32f103rbt6_clk.c
 * @{
 */
/** \brief CLK ƽ̨��ʼ�� */
static void __hk32f103rbt6_clk_plfm_init (void)
{
}

/** \brief CLK�豸��Ϣ */
static const am_hk32f103rbt6_clk_devinfo_t __g_clk_devinfo =
{
    /**
     * \brief ϵͳʱ��Դѡ��
     *
     * AM_HK32F103RBT6_SYSCLK_HSI : HSI ��Ϊϵͳʱ��
     * AM_HK32F103RBT6_SYSCLK_HSE : HSE ��Ϊϵͳʱ��
     * AM_HK32F103RBT6_SYSCLK_PLL : PLL �����Ϊϵͳʱ��
     * AM_HK32F103RBT6_SYSCLK_LSI : LSI �����Ϊϵͳʱ��
     * AM_HK32F103RBT6_SYSCLK_LSE : LSE �����Ϊϵͳʱ��
     */
    AM_HK32F103RBT6_SYSCLK_PLL,

    /**
     * \brief HSEOSC�ⲿ����Ƶ��
     *
     *  ���pllin_srcѡ�� AMHW_HK32F103RBT6_PLLCLK_HSE �� PLLIN = hse_osc��
     */
    12000000,

    /**
     * \brief LSEOSC�ⲿ����Ƶ��
     *
     *  ���rtc_srcѡ�� AMHW_HK32F103RBT6_RTCCLK_LSE �� rtcclk = lse_osc��
     */
    0,

    /** \brief
     *    PLL ʱ��Դѡ��
     *    -# AMHW_HK32F103RBT6_PLLCLK_HSI : HSI ��ΪPLL����ʱ��
     *    -# AMHW_HK32F103RBT6_PLLCLK_HSE : HSE ��ΪPLL����ʱ��
     */
    AMHW_HK32F103RBT6_PLLCLK_HSE,

    /**
     * \brief PLL ��Ƶϵ������ѡ2-17
     *        PLLOUT = PLLIN * pll_mul
     */
     6,

    /** \brief USB��Ƶϵ����
     *
     *  AMHW_HK32F103RBT6_PLL_USB_DIV1P5 : PLL 1.5 ��Ƶ��Ϊusb����ʱ�� ,USBCLK = PLLOUT / 1.5;
     *  AMHW_HK32F103RBT6_PLL_USB_DIV1   : PLL 1 ��Ƶ��Ϊusb����ʱ�� ,  USBCLK = PLLOUT / 1��
     *
     *  �������ó�48Mhz
     */
    AMHW_HK32F103RBT6_PLL_USB_DIV1,

    /**
     * \brief AHB��Ƶϵ����AHBCLK = PLLOUT / DIV,AHB���Ƶ��Ϊ80Mhz
     *
     *    ahb_div |  DIV
     *   ---------------------
     *        0-7 |   1
     *        8   |   2
     *        9   |   4
     *        10  |   8
     *        11  |   16
     *        12  |   64
     *        13  |  128
     *        14  |  256
     *        15  |  512
     */
    0,

    /**
     * \brief APB1��Ƶϵ����APB1CLK = AHBCLK / (2 ^ apb1_div)
     *        APB1���Ƶ��Ϊ36Mhz
     */
    1,

    /**
     * \brief APB2��Ƶϵ����APB2CLK = AHBCLK / (2 ^ apb2_div)
     *        APB2���Ƶ��Ϊ72Mhz
     */
    0,

    /**
     * \brief ADC��Ƶϵ����ADCCLK = APB2 / DIV
     *    adc_div |  DIV
     *   -----------------
     *          0 | 2 ��Ƶ
     *          1 | 4 ��Ƶ
     *          2 | 8 ��Ƶ
     *          3 | 16��Ƶ
     *
     *        ADC���Ƶ��Ϊ14Mhz
     */
    0,

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    __hk32f103rbt6_clk_plfm_init,

    /** \brief ƽ̨���ʼ������ */
    NULL,
};

/** \brief ʱ���豸ʵ�� */
static am_hk32f103rbt6_clk_dev_t __g_clk_dev;

/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 */
int am_hk32f103rbt6_clk_inst_init (void)
{
    return am_hk32f103rbt6_clk_init(&__g_clk_dev, &__g_clk_devinfo);
}

/**
 * @}
 */

/* end of file */
