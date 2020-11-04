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
 * \brief MM32L373 CLK �û������ļ�
 * \sa am_hwconf_mm32l373_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */
#include "am_gpio.h"

#include "am_mm32l373_clk.h"
#include "amhw_mm32l373_rcc.h"
#include "mm32l373_pin.h"
/**
 * \addtogroup am_if_src_hwconf_mm32l373_clk
 * \copydoc am_hwconf_mm32l373_clk.c
 * @{
 */
/** \brief CLK ƽ̨��ʼ�� */
static void __mm32l373_clk_plfm_init (void)
{
}

/** \brief CLK�豸��Ϣ */
static const am_mm32l373_clk_devinfo_t __g_clk_devinfo =
{
    /**
     * \brief HSEOSC�ⲿ����Ƶ��
     *
     *  ���pllin_srcѡ�� AMHW_MM32L373_PLLCLK_HSE �� PLLIN = hse_osc��
     */
    12000000,

    /**
     * \brief LSEOSC�ⲿ����Ƶ��
     *
     *  ���rtc_srcѡ�� AMHW_MM32L373_RTCCLK_LSE �� rtcclk = lse_osc��
     */
    0,

    /** \brief
     *    PLL ʱ��Դѡ��
     *    -# AMHW_MM32L373_PLLCLK_HSI_DIV4 : HSI ���� 4 ��Ƶ��ΪPLL����ʱ��
     *    -# AMHW_MM32L373_PLLCLK_HSE      : HSE ��ΪPLL����ʱ��
     */
    AMHW_MM32L373_PLLCLK_HSE,

    /**
     * \brief PLL ��Ƶϵ������ѡ1-64
     *        PLLOUT = PLLIN * pll_mul / pll_div
     */
    8,

    /**
     * \brief PLL ��Ƶϵ������ѡ1-8
     *        PLLOUT = PLLIN * pll_mul / pll_div
     */
    1,

    /** \brief USB��Ƶϵ����USBCLK = PLLOUT / (usb_div + 1),�������ó�48Mhz */
    1,

    /**
     * \brief AHB��Ƶϵ����AHBCLK = PLLOUT / DIV,AHB���Ƶ��Ϊ96Mhz
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
     *        APB1���Ƶ��Ϊ96Mhz
     */
    1,

    /**
     * \brief APB2��Ƶϵ����APB2CLK = AHBCLK / (2 ^ apb2_div)
     *        APB2���Ƶ��Ϊ96Mhz
     */
    0,

    /**
     * \brief ADC��Ƶϵ����ADCCLK = APB2 / (2 ^ adc_div)
     *        ADC���Ƶ��Ϊ48Mhz
     */
    1,

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    __mm32l373_clk_plfm_init,

    /** \brief ƽ̨���ʼ������ */
    NULL,
};

/** \brief ʱ���豸ʵ�� */
static am_mm32l373_clk_dev_t __g_clk_dev;

/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 */
int am_mm32l373_clk_inst_init (void)
{
    return am_mm32l373_clk_init(&__g_clk_dev, &__g_clk_devinfo);
}

/**
 * @}
 */

/* end of file */
