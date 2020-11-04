
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
 * \brief CLK������ʱ�ӱ�׼����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-27  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG237_CLK_H
#define __AM_ZLG237_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_clk.h"
#include "amhw_zlg237_rcc.h"

/**
 * \addtogroup am_zlg237_if_clk
 * \copydoc am_zlg237_clk.h
 * @{
 */
/**
 * \brief ϵͳʱ��Դ
 */
typedef enum {
    AM_ZLG237_SYSCLK_HSI, /**< \brief HSI ��Ϊϵͳʱ�� */
    AM_ZLG237_SYSCLK_HSE, /**< \brief HSE ��Ϊϵͳʱ�� */
    AM_ZLG237_SYSCLK_PLL, /**< \brief PLL �����Ϊϵͳʱ�� */
    AM_ZLG237_SYSCLK_LSI, /**< \brief LSI �����Ϊϵͳʱ�� */
    AM_ZLG237_SYSCLK_LSE  /**< \brief LSE �����Ϊϵͳʱ�� */
}am_zlg237_sys_clk_src;

/**
 * \brief CLK �豸��Ϣ�����ṹ��
 */
typedef struct am_zlg237_clk_devinfo {
    /**
     * \brief ϵͳʱ��Դѡ��
     *
     * AM_ZLG237_SYSCLK_HSI : HSI ��Ϊϵͳʱ��
     * AM_ZLG237_SYSCLK_HSE : HSE ��Ϊϵͳʱ��
     * AM_ZLG237_SYSCLK_PLL : PLL �����Ϊϵͳʱ��
     * AM_ZLG237_SYSCLK_LSI : LSI �����Ϊϵͳʱ��
     * AM_ZLG237_SYSCLK_LSE : LSE �����Ϊϵͳʱ��
     */

    uint32_t sysclk_src;
    /**
     * \brief HSEOSC�ⲿ����Ƶ��
     *
     *  ���pllin_srcѡ�� AMHW_ZLG237_PLLCLK_HSE �� PLLIN = hse_osc��
     */
    uint32_t hse_osc;

    /**
     * \brief LSEOSC�ⲿ����Ƶ��
     *
     *  ���rtc_srcѡ�� AMHW_ZLG237_RTCCLK_LSE �� rtcclk = lse_osc��
     */
    uint32_t lse_osc;

    /** \brief
     *    PLL ʱ��Դѡ��
     *    -# AMHW_ZLG237_PLLCLK_HSI : HSI ��ΪPLL����ʱ��
     *    -# AMHW_ZLG237_PLLCLK_HSE : HSE ��ΪPLL����ʱ��
     */
    amhw_zlg237_pll_clk_src pllin_src;

    /**
     * \brief PLL ��Ƶϵ������ѡ2-17
     *        PLLOUT = PLLIN * pll_mul
     */
    uint8_t pll_mul;

    /** \brief USB��Ƶϵ����
     *
     *  AMHW_ZLG237_PLL_USB_DIV1P5 : PLL 1.5 ��Ƶ��Ϊusb����ʱ�� ,USBCLK = PLLOUT / 1.5;
     *  AMHW_ZLG237_PLL_USB_DIV1   : PLL 1 ��Ƶ��Ϊusb����ʱ�� ,  USBCLK = PLLOUT / 1��
     *
     *  �������ó�48Mhz
     */
    amhw_zlg237_pll_usb_clk_div usb_div;

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
     *        13  |   128
     *        14  |   256
     *        15  |   512
     */
    uint8_t ahb_div;

    /**
     * \brief APB1��Ƶϵ����APB1CLK = AHBCLK / (2 ^ apb1_div)
     *        APB1���Ƶ��Ϊ80Mhz
     */
    uint8_t apb1_div;

    /**
     * \brief APB2��Ƶϵ����APB2CLK = AHBCLK / (2 ^ apb2_div)
     *        APB2���Ƶ��Ϊ36Mhz
     */
    uint8_t apb2_div;

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
    uint8_t adc_div;

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    void  (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void  (*pfn_plfm_deinit)(void);

} am_zlg237_clk_devinfo_t;

/**
 * \brief CLK �豸�ṹ��
 */
typedef struct am_zlg237_clk_dev {

    /** \brief ָ��CLK �豸��Ϣ��ָ�� */
    const am_zlg237_clk_devinfo_t *p_devinfo;

    /** \brief PLL����Ƶ�� */
    uint32_t sys_clk;

    /** \brief PLL����Ƶ�� */
    uint32_t pllin_clk;

    /** \brief PLL���Ƶ�� */
    uint32_t pllout_clk;

    /** \brief AHBʱ��Ƶ�� */
    uint32_t ahb_clk;

    /** \brief APB1ʱ��Ƶ�� */
    uint32_t apb1_clk;

    /** \brief APB2ʱ��Ƶ�� */
    uint32_t apb2_clk;

    /** \brief USBʱ��Ƶ�� */
    uint32_t usb_clk;

    /** \brief RTCʱ��Ƶ�� */
    uint32_t rtc_clk;

} am_zlg237_clk_dev_t;

/**
 * \brief ��ȡʱ��Ƶ��
 */
int am_clk_rate_get (am_clk_id_t clk_id);

/**
 * \brief CLK ��ʼ��
 *
 * \param[in] p_dev     : ָ��CLK�豸��ָ��
 * \param[in] p_devinfo : ָ��CLK�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zlg237_clk_init (am_zlg237_clk_dev_t           *p_dev,
                        const am_zlg237_clk_devinfo_t *p_devinfo);

/**
 * \brief CLK ���踴λ
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zlg237_clk_reset (am_clk_id_t clk_id);

/**
 * \brief ��������Ƶ��ֵ
 *
 *  ������Ƶ�ʱ���������ʱ����Ҫ���ô˺������������ڲ��洢��Ƶ��ֵ
 *  ����CLK_AHB��CLK_APB1��CLK_APB2��Ч
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 * \param[in] clk     ���µ�Ƶ��ֵ
 *
 * \retval AM_OK : �����ɹ�
 *
 * \note ע���˺�������
 */
int am_zlg237_clk_update (am_clk_id_t clk_id, int clk);

/**
 * \brief ��ȡPLL������ʱ��Դ
 *  ����CLK_AHB��CLK_APB1��CLK_APB2��Ч
 *
 * \return clk��ʱ��������Ϣ
 */
const am_zlg237_clk_dev_t *am_zlg237_clk_devinfo_get (void);

/**
 * \brief �������߻������CLK��Ƶֵ
 *
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \return: ���ض�Ӧ���߻�����ķ�Ƶֵ
 *
 */
int am_zlg237_div_get (am_clk_id_t clk_id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG237_CLK_H */

/* end of file */
