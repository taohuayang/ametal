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
 * \brief
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-27  yrh, first implementation
 * \endinternal
 */

#ifndef __AMHW_HK32F103RBT6_RCC_H
#define __AMHW_HK32F103RBT6_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hk32f103rbt6_periph_map.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_hk32f103rbt6_if_rcc
 * \copydoc amhw_hk32f103rbt6_rcc.h
 * @{
 */

/**
 * \brief CRC�Ĵ�����ṹ��
 */
typedef struct amhw_hk32f103rbt6_rcc {
  __IO uint32_t cr;        /**< \brief ʱ�ӿ��ƼĴ��� */
  __IO uint32_t cfgr;      /**< \brief ʱ�����üĴ��� */
  __IO uint32_t cir;       /**< \brief ʱ���жϼĴ��� */
  __IO uint32_t apb2rstr;  /**< \brief APB2���踴λ�Ĵ��� */
  __IO uint32_t apb1rstr;  /**< \brief APB1���踴λ�Ĵ��� */
  __IO uint32_t ahbenr;    /**< \brief AHB����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t apb2enr;   /**< \brief APB2����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t apb1enr;   /**< \brief APB1����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t bdcr;      /**< \brief ���ݿ��ƼĴ��� */
  __IO uint32_t csr;       /**< \brief ����״̬�Ĵ��� */
  __IO uint32_t wts;       /**< \brief hseʱ��Դ���ƼĴ��� */
  __I  uint32_t reserve;   /**< \brief ���� */
  __IO uint32_t lpclk_ctl; /**< \brief �͹���ʱ�����üĴ��� */

} amhw_hk32f103rbt6_rcc_t;

/**
 * \brief ϵͳʱ��Դ
 */
typedef enum {
    AMHW_HK32F103RBT6_SYSCLK_HSI,       /**< \brief HSI ��Ϊϵͳʱ�� */
    AMHW_HK32F103RBT6_SYSCLK_HSE,       /**< \brief HSE ��Ϊϵͳʱ�� */
    AMHW_HK32F103RBT6_SYSCLK_PLL,       /**< \brief PLL �����Ϊϵͳʱ�� */
    AMHW_HK32F103RBT6_SYSCLK_LSI_OR_LSE /**< \brief LSI ��  LSE �����Ϊϵͳʱ�� */
}amhw_hk32f103rbt6_sys_clk_src;

/**
 * \brief ����ϵͳʱ��
 */
typedef enum {
    AMHW_HK32F103RBT6_LCLK_LSI,  /**< \brief �����ڲ�ʱ�� */
    AMHW_HK32F103RBT6_LCLK_LSE,  /**< \brief �����ⲿʱ�� */
}amhw_hk32f103rbt6_lclk;


/**
 * \brief RTCʱ��Դ
 */
typedef enum {
    AMHW_HK32F103RBT6_RTCCLK_LSE = 1,       /**< \brief PLL �����Ϊϵͳʱ�� */
    AMHW_HK32F103RBT6_RTCCLK_LSI = 2,       /**< \brief HSI ����  6 ��Ƶ��Ϊϵͳʱ�� */
    AMHW_HK32F103RBT6_RTCCLK_HSE_DIV128 =3, /**< \brief HSE ��Ϊϵͳʱ�� */
}amhw_hk32f103rbt6_rtc_clk_src;

/**
 * \brief PLLʱ��Դ
 */
typedef enum {
    AMHW_HK32F103RBT6_PLLCLK_HSI = 0,  /**< \brief HSI ��ΪPLL����ʱ�� */
    AMHW_HK32F103RBT6_PLLCLK_HSE = 1,  /**< \brief HSE ��ΪPLL����ʱ�� */
}amhw_hk32f103rbt6_pll_clk_src;

/**
 * \brief usb ��Ƶϵ��
 */
typedef enum {
    AMHW_HK32F103RBT6_PLL_USB_DIV1P5 = 0, /**< \brief PLL 1.5 ��Ƶ��Ϊusb����ʱ�� */
    AMHW_HK32F103RBT6_PLL_USB_DIV1   = 1, /**< \brief PLL 1 ��Ƶ��Ϊusb����ʱ�� */
}amhw_hk32f103rbt6_pll_usb_clk_div;

/**
 * \brief ʱ���жϱ�־
 */
typedef enum {
    AMHW_HK32F103RBT6_CLKINT_INDEX_LSI = 0,  /**< \brief LSI��־ */
    AMHW_HK32F103RBT6_CLKINT_INDEX_LSE = 1,  /**< \brief LSE��־ */
    AMHW_HK32F103RBT6_CLKINT_INDEX_HSI,      /**< \brief HSI��־ */
    AMHW_HK32F103RBT6_CLKINT_INDEX_HSE,      /**< \brief HSE��־ */
    AMHW_HK32F103RBT6_CLKINT_INDEX_PLL,      /**< \brief PLL��־ */
    AMHW_HK32F103RBT6_CLKINT_INDEX_CSSF = 7, /**< \brief CSSF(ʱ�Ӱ�ȫϵͳ�ж�)��־ */
}amhw_hk32f103rbt6_clk_int_index;

/**
 * \brief APB2����ö��
 */
typedef enum {
    AMHW_HK32F103RBT6_RCC_APB2_AFIO   = 0,  /**< \brief AFIO */
    AMHW_HK32F103RBT6_RCC_APB2_IOPA   = 2,  /**< \brief IOPA */
    AMHW_HK32F103RBT6_RCC_APB2_IOPB   = 3,  /**< \brief IOPB */
    AMHW_HK32F103RBT6_RCC_APB2_IOPC   = 4,  /**< \brief IOPC */
    AMHW_HK32F103RBT6_RCC_APB2_IOPD   = 5,  /**< \brief IOPD */
    AMHW_HK32F103RBT6_RCC_APB2_ADC1   = 9,  /**< \brief ADC1 */
    AMHW_HK32F103RBT6_RCC_APB2_ADC2   = 10, /**< \brief ADC2 */
    AMHW_HK32F103RBT6_RCC_APB2_TIM1   = 11, /**< \brief TIM1 */
    AMHW_HK32F103RBT6_RCC_APB2_SPI1   = 12, /**< \brief SPI1 */
    AMHW_HK32F103RBT6_RCC_APB2_UART1  = 14, /**< \brief UART1 */
}amhw_hk32f103rbt6_apb2_peripheral;

/**
 * \brief APB1����ö��
 */
typedef enum {
    AMHW_HK32F103RBT6_RCC_APB1_TIM2   = 0,    /**< \brief TIM2��ʱ�� */
    AMHW_HK32F103RBT6_RCC_APB1_TIM3   = 1,    /**< \brief TIM3��ʱ�� */
    AMHW_HK32F103RBT6_RCC_APB1_TIM4   = 2,    /**< \brief TIM4��ʱ�� */
    AMHW_HK32F103RBT6_RCC_APB1_WWDG   = 11,   /**< \brief WWDG���ڿ��Ź� */
    AMHW_HK32F103RBT6_RCC_APB1_SPI2   = 14,   /**< \brief SPI2 */
    AMHW_HK32F103RBT6_RCC_APB1_USART2  = 17,  /**< \brief USART2 */
    AMHW_HK32F103RBT6_RCC_APB1_USART3  = 18,  /**< \brief USART3 */
    AMHW_HK32F103RBT6_RCC_APB1_I2C1   = 21,   /**< \brief I2C1 */
    AMHW_HK32F103RBT6_RCC_APB1_I2C2   = 22,   /**< \brief I2C2 */
    AMHW_HK32F103RBT6_RCC_APB1_USB    = 23,   /**< \brief USB */
    AMHW_HK32F103RBT6_RCC_APB1_CAN    = 25,   /**< \brief CAN */
    AMHW_HK32F103RBT6_RCC_APB1_BKP    = 27,   /**< \brief BKP */
    AMHW_HK32F103RBT6_RCC_APB1_PWR    = 28,   /**< \brief ��Դ�ӿ� */
}amhw_hk32f103rbt6_apb1_peripheral;

/**
 * \brief AHB����ö��
 */
typedef enum {
    AMHW_HK32F103RBT6_RCC_AHB_DMA   = 0,   /**< \brief DMA */
    AMHW_HK32F103RBT6_RCC_AHB_SRAM  = 2,   /**< \brief SRAM */
    AMHW_HK32F103RBT6_RCC_AHB_FLITF = 4,   /**< \brief FLITF */
    AMHW_HK32F103RBT6_RCC_AHB_CRC   = 6,   /**< \brief CRC */
}amhw_hk32f103rbt6_ahb_peripheral;

/**
 * \brief ��λ��־ö��
 */
typedef enum {
    AMHW_HK32F103RBT6_RCC_CSR_PINRSTF   = (1ul << 26),      /**< \brief NRST�ܽŸ�λ��־ */
    AMHW_HK32F103RBT6_RCC_CSR_PORRSTF   = (1ul << 27),      /**< \brief �ϵ�/���縴λ��־ */
    AMHW_HK32F103RBT6_RCC_CSR_SFTRSTF   = (1ul << 28),      /**< \brief �����λ��־ */
    AMHW_HK32F103RBT6_RCC_CSR_IWDGRSTF  = (1ul << 29),      /**< \brief �������Ź���λ��־ */
    AMHW_HK32F103RBT6_RCC_CSR_WWDGRSTF  = (1ul << 30),      /**< \brief ���ڿ��Ź���λ��־ */
    AMHW_HK32F103RBT6_RCC_CSR_LPWRRSTF  = (int)(1ul << 31), /**< \brief �͹��Ĺ���λ��־ */
}amhw_hk32f103rbt6_reset_flag_t;

/**
 * \brief �ڲ�����ʱ��ʹ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_hsion_enable (void)
{
    HK32F103RBT6_RCC->cr |= 1ul;
}

/**
 * \brief �ڲ�����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ڲ� 8MHzʱ��û�о���
 * \retval FALSE : �ڲ� 8MHzʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_hk32f103rbt6_rcc_hsirdy_read (void)
{
    return (am_bool_t)((HK32F103RBT6_RCC->cr & 0x2ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ��(HSE ����)ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_hseon_enable (void)
{
    HK32F103RBT6_RCC->cr |= (1ul << 16);
}

/**
 * \brief �ⲿ����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ⲿʱ��û�о���
 * \retval FALSE : �ⲿʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_hk32f103rbt6_rcc_hserdy_read (void)
{
    return (am_bool_t)((HK32F103RBT6_RCC->cr & (1ul << 17)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ����·ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_hsebyp_enable (void)
{
    HK32F103RBT6_RCC->cr |= (1ul << 18);
}

/**
 * \brief ʱ�Ӱ�ȫϵͳʹ��
 *
 * \details ����ⲿ 8-24MHz����������ʱ�Ӽ����������
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_ccson_enable (void)
{
    HK32F103RBT6_RCC->cr |= (1ul << 19);
}


/**
 * \brief PLL ʹ��
 *
 * \details �����������ֹͣģʽʱ����λ��Ӳ�����㡣
 *          �� PLL ʱ�ӱ�������ѡ��Ҫ��Ϊϵͳʱ��ʱ,
 *          ��λ���ܱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_pll_enable (void)
{
    HK32F103RBT6_RCC->cr |= (1ul << 24);
}

/**
 * \brief PLL ����
 *
 * \details �����������ֹͣģʽʱ����λ��Ӳ�����㡣
 *          �� PLL ʱ�ӱ�������ѡ��Ҫ��Ϊϵͳʱ��ʱ,
 *          ��λ���ܱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_pll_disable (void)
{
    HK32F103RBT6_RCC->cr &= ~(1ul << 24);
}

/**
 * \brief PLL ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : PLL δ����
 * \retval FALSE : PLL ����
 */
am_static_inline
am_bool_t amhw_hk32f103rbt6_rcc_pllrdy_read (void)
{
    return (am_bool_t)((HK32F103RBT6_RCC->cr & (1ul << 25)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ϵͳʱ���л�
 *
 * \param[in]  src ��ϵͳʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_sys_clk_set (amhw_hk32f103rbt6_sys_clk_src src)
{

    HK32F103RBT6_RCC->cfgr = ((src & 0x3ul) << 0) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x3ul << 0));
}

/**
 * \brief ��ǰϵͳʱ�ӻ�ȡ
 *
 * \return ��ǰϵͳʱ��Դ
 */
am_static_inline
amhw_hk32f103rbt6_sys_clk_src amhw_hk32f103rbt6_rcc_sys_clk_get (void)
{

    return (amhw_hk32f103rbt6_sys_clk_src)((HK32F103RBT6_RCC->cfgr >> 2ul) & 0x3ul);
}

/**
 * \brief ����AHB Ԥ��Ƶ
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-7 �� ����Ƶ
 *       - 8   �� 2��Ƶ
 *       - 9   �� 4��Ƶ
 *       - 10  �� 8��Ƶ
 *       - 11  �� 16��Ƶ
 *       - 12  �� 64��Ƶ
 *       - 13  �� 128��Ƶ
 *       - 14  �� 256��Ƶ
 *       - 15  �� 512��Ƶ
 *
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_ahb_div_set (uint8_t div)
{

    HK32F103RBT6_RCC->cfgr = ((div & 0xful) << 4) |
                              (HK32F103RBT6_RCC->cfgr & ~(0xful << 4));
}

/**
 * \brief ���� ���� APB Ԥ��Ƶ��APB1��
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb1_div_set (uint8_t div)
{

    HK32F103RBT6_RCC->cfgr = ((div & 0x7ul) << 8) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x7ul << 8));
}

/**
 * \brief ��ȡ ���� APB Ԥ��Ƶ��APB1��
 *
 * \return Ԥ��Ƶֵ
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 */
am_static_inline
uint8_t amhw_hk32f103rbt6_rcc_apb1_div_get (void)
{

    return (uint8_t)((HK32F103RBT6_RCC->cfgr >> 8) & 0x7ul);
}

/**
 * \brief ���� ���� APB Ԥ��Ƶ��APB2��
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb2_div_set (uint8_t div)
{

    HK32F103RBT6_RCC->cfgr = ((div & 0x7ul) << 11) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x7ul << 11));
}

/**
 * \brief ��ȡ ���� APB Ԥ��Ƶ��APB2��
 *
 * \return Ԥ��Ƶֵ
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 */
am_static_inline
uint8_t amhw_hk32f103rbt6_rcc_apb2_div_get (void)
{

    return (uint8_t)((HK32F103RBT6_RCC->cfgr >> 11) & 0x7ul);
}


/**
 * \brief ���� ADC Ԥ��Ƶ
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0   �� 2 ��Ƶ
 *       - 1   �� 4 ��Ƶ
 *       - 2   �� 8 ��Ƶ
 *       - 3   �� 16��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_adc_div_set (uint8_t div)
{

    HK32F103RBT6_RCC->cfgr = ((div & 0x3ul) << 14) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x3ul << 14));
}

/**
 * \brief ��ȡ ADC Ԥ��Ƶ
 *
 * \return Ԥ��Ƶֵ
 *       - 0   �� 2 ��Ƶ
 *       - 1   �� 4 ��Ƶ
 *       - 2   �� 8 ��Ƶ
 *       - 3   �� 16��Ƶ
 */
am_static_inline
uint8_t amhw_hk32f103rbt6_rcc_adc_div_get (void)
{

    return (uint8_t)((HK32F103RBT6_RCC->cfgr >> 14) & 0x3ul);
}


/**
 * \brief PLL����ʱ��ѡ��
 *
 * \param[in]  src ��PLL����ʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_pll_clk_set (amhw_hk32f103rbt6_pll_clk_src src)
{

    HK32F103RBT6_RCC->cfgr = ((src & 0x3ul) << 16) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x3ul << 16));
}

/**
 * \brief ��ǰPLL����ʱ�ӻ�ȡ
 *
 * \return ��ǰPLL����ʱ��Դ
 */
am_static_inline
amhw_hk32f103rbt6_pll_clk_src amhw_hk32f103rbt6_rcc_pll_clk_get (void)
{

    return (amhw_hk32f103rbt6_pll_clk_src)((HK32F103RBT6_RCC->cfgr >> 16ul) & 0x3ul);
}

/**
 * \brief ѡ�� HSE ��Ƶ����Ϊ PLL ����
 *
 * \param[in]  div ����Ƶֵ
 *
 *      - 0  �� ����Ƶ
 *      - 1  �� 2��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_hseforpll_set (uint8_t div)
{

    HK32F103RBT6_RCC->cfgr = ((div & 0x1ul) << 17) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x1ul << 17));
}


///**
// * \brief PLL��Ƶϵ������
// *
// * \param[in]  div ����Ƶֵ
// *
// * \return ��
// */
//am_static_inline
//void amhw_hk32f103rbt6_rcc_plldm_set (uint8_t div)
//{
//    HK32F103RBT6_RCC->cr = ((div & 0x7ul) << 20) |
//                            (HK32F103RBT6_RCC->cr & ~(0x7ul << 20));
//}

/**
 * \brief PLL��Ƶϵ������
 *
 * \param[in]  mul ����Ƶֵ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_plldn_set (uint8_t mul)
{

    HK32F103RBT6_RCC->cfgr = ((mul & 0xful) << 18) |
                            (HK32F103RBT6_RCC->cfgr & ~(0xful << 18));
}


/**
 * \brief ѡ�� USB Ԥ��Ƶ
 *
 * \param[in]  div ����Ƶֵ
 *
 *      - AMHW_HK32F103RBT6_PLL_USB_DIV1P5 ��PLL ʱ��1.5��Ƶ��Ϊ USB ʱ��
 *      - AMHW_HK32F103RBT6_PLL_USB_DIV1   �� PLL ʱ��ֱ����Ϊ USBʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_pllforusb_set (amhw_hk32f103rbt6_pll_usb_clk_div index)
{

    HK32F103RBT6_RCC->cfgr = ((index & 0x1ul) << 22) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x1ul << 22));
}

/**
 * \brief USB Ԥ��Ƶ��ȡ
 *
 * \retval  0  �� PLL ʱ��ֱ����Ϊ USB ʱ��
 * \retval  1  �� PLL ʱ��2 ��Ƶ��Ϊ USBʱ��
 * \retval  2  �� PLL ʱ��3 ��Ƶ��Ϊ USBʱ��
 * \retval  3  �� PLL ʱ��4 ��Ƶ��Ϊ USBʱ��
 */
am_static_inline
uint8_t amhw_hk32f103rbt6_rcc_pllforusb_get (void)
{

    return (uint8_t)((HK32F103RBT6_RCC->cfgr >> 22ul) & 0x1ul);
}

/**
 * \brief ΢������ʱ�����ѡ��
 *
 * \details 1.��ʱ��������������л� MCO ʱ��Դʱ���ܻᱻ�ض�,
 *          2.��ϵͳʱ����Ϊ����� MCO �ܽ�ʱ���뱣֤���ʱ��Ƶ
 *            �ʲ����� 50MHz��IO�����Ƶ�ʣ�
 *
 * \param[in]  src ��ʱ��Դ
 *
 *      - 0-3 �� û��ʱ�����
 *      - 4   �� ϵͳʱ�ӣ�SYSCLK�����
 *      - 5   �� HSI ʱ�����
 *      - 6   �� HSE ʱ�����
 *      - 7   �� PLL ʱ��2 ��Ƶ�����
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_mco_src_set (uint8_t src)
{

    HK32F103RBT6_RCC->cfgr = ((src & 0x7ul) << 24ul) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x7ul << 24ul));
}

/**
 * \brief ѡ�� HSI ��Ƶ����Ϊ PLL ����ο�ʱ��
 *
 * \param[in]  div ����Ƶֵ
 *
 *      - 0  �� 2��Ƶ
 *      - 1  �� ����Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_pllcrpre_set (uint8_t div)
{

    HK32F103RBT6_RCC->cfgr = ((div & 0x1ul) << 31ul) |
                              (HK32F103RBT6_RCC->cfgr & ~(0x1ul << 31ul));
}


/**
 * \brief �����ж�ʹ��
 *
 * \param[in]  index ��������־
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_clkint_enable (amhw_hk32f103rbt6_clk_int_index index)
{

    HK32F103RBT6_RCC->cir |= ((index & 0x1ful) << 8);
}

/**
 * \brief �����жϽ���
 *
 * \param[in]  index ��������־
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_clkint_disable (amhw_hk32f103rbt6_clk_int_index index)
{

    HK32F103RBT6_RCC->cir &= ~((index & 0x1ful) << 8);
}

/**
 * \brief ��ȡ�жϱ�־
 *
 * \return �жϱ�־
 */
am_static_inline
amhw_hk32f103rbt6_clk_int_index amhw_hk32f103rbt6_rcc_clkint_flag_read (void)
{

    return (amhw_hk32f103rbt6_clk_int_index)(HK32F103RBT6_RCC->cir & 0x9ful);
}

/**
 * \brief ����жϱ�־
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_clkint_flag_clear (amhw_hk32f103rbt6_clk_int_index index)
{

    HK32F103RBT6_RCC->cir |= ((index & 0x9ful) << 16);
}

/**
 * \brief ��λAPB2����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb2_reset (amhw_hk32f103rbt6_apb2_peripheral reset)
{

    HK32F103RBT6_RCC->apb2rstr |= (1ul << reset);
}

/**
 * \brief ֹͣ��λAPB2����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb2_reset_stop (amhw_hk32f103rbt6_apb2_peripheral reset)
{

    HK32F103RBT6_RCC->apb2rstr &= ~(1ul << reset);
}

/**
 * \brief ��λAPB1����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb1_reset (amhw_hk32f103rbt6_apb1_peripheral reset)
{

    HK32F103RBT6_RCC->apb1rstr |= (1ul << reset);
}

/**
 * \brief ֹͣ��λAPB1����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb1_reset_stop (amhw_hk32f103rbt6_apb1_peripheral reset)
{

    HK32F103RBT6_RCC->apb1rstr &= ~(1ul << reset);
}

/**
 * \brief ʹ��APB1����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb1_enable (amhw_hk32f103rbt6_apb1_peripheral peri)
{

    HK32F103RBT6_RCC->apb1enr |= (1ul << peri);
}

/**
 * \brief ����APB1����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb1_disable (amhw_hk32f103rbt6_apb1_peripheral peri)
{

    HK32F103RBT6_RCC->apb1enr &= ~(1ul << peri);
}

/**
 * \brief ʹ��APB2����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb2_enable (amhw_hk32f103rbt6_apb2_peripheral peri)
{

    HK32F103RBT6_RCC->apb2enr |= (1ul << peri);
}

/**
 * \brief ����APB2����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_apb2_disable (amhw_hk32f103rbt6_apb2_peripheral peri)
{

    HK32F103RBT6_RCC->apb2enr &= ~(1ul << peri);
}

/**
 * \brief ʹ��AHB����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
void amhw_hk32f103rbt6_rcc_ahb_enable (amhw_hk32f103rbt6_ahb_peripheral peri);

/**
 * \brief ����AHB����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_hk32f103rbt6_rcc_ahb_disable (amhw_hk32f103rbt6_ahb_peripheral peri);

/**
 * \brief ʹ��LSI
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_lsi_enable (void)
{

    HK32F103RBT6_RCC->csr |= (1ul << 0);
}

/**
 * \brief ����LSI
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_lsi_disable (void)
{

    HK32F103RBT6_RCC->csr &= ~(1ul << 0);
}

/**
 * \brief �ڲ�����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ڲ� 40kHz ����ʱ�Ӿ���
 * \retval FALSE : �ڲ� 40kHz ����ʱ��δ����
 */
am_static_inline
am_bool_t amhw_hk32f103rbt6_rcc_lsirdy_read (void)
{
    return (am_bool_t)((HK32F103RBT6_RCC->csr & (1ul << 1)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ��ȡ��λ��־
 *
 * \return ��λ��־
 */
am_static_inline
amhw_hk32f103rbt6_reset_flag_t amhw_hk32f103rbt6_rcc_reset_flag (void)
{

    return (amhw_hk32f103rbt6_reset_flag_t)(HK32F103RBT6_RCC->csr & 0xfc000000);
}

/**
 * \brief �����λ��־
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_reset_flag_clear (void)
{

    HK32F103RBT6_RCC->csr |= (1ul << 24);
}

/**
 * \brief �ⲿ��������ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_lse_enable (void)
{

    HK32F103RBT6_RCC->bdcr |= (1ul << 0);
}
/**
 * \brief �ⲿ������������
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_lse_disable (void)
{
    HK32F103RBT6_RCC->bdcr &= ~(1ul << 0);
}

/**
 * \brief �ⲿ����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ⲿ 32kHz ����ʱ�Ӿ���
 * \retval FALSE : �ⲿ 32kHz ����ʱ��δ����
 */
am_static_inline
am_bool_t amhw_hk32f103rbt6_rcc_lserdy_read (void)
{
    return (am_bool_t)((HK32F103RBT6_RCC->bdcr & (1ul << 1)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ����·״̬
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_bdcr_lsebyp_set (uint32_t lsebyp)
{
    HK32F103RBT6_RCC->bdcr |= (lsebyp << 2);
}
/**
 * \brief �ⲿ����ʱ����·״̬
 *
 * \retval TRUE  : LSE ʱ�ӱ���·
 * \retval FALSE : LSE ʱ��δ����·
 */
am_static_inline
am_bool_t amhw_hk32f103rbt6_rcc_bdcr_lsebyp_get (void)
{
    return (am_bool_t)((HK32F103RBT6_RCC->bdcr & 0x4ul) ? AM_TRUE : AM_FALSE);
}
/**
 * \brief RTC����ʱ��ѡ��
 *
 * \param[in]  src ��RTC����ʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_bdcr_rtc_clk_set (amhw_hk32f103rbt6_rtc_clk_src src)
{

    HK32F103RBT6_RCC->bdcr = ((src & 0x3ul) << 8) |
                              (HK32F103RBT6_RCC->bdcr & ~(0x3ul << 8));
}

/**
 * \brief RTC����ʱ�ӻ�ȡ
 *
 * \retval  rtcʱ��Դ��ȡ
 */
am_static_inline
amhw_hk32f103rbt6_rtc_clk_src amhw_hk32f103rbt6_rcc_bdcr_rtc_clk_get (void)
{
    return (amhw_hk32f103rbt6_rtc_clk_src)((HK32F103RBT6_RCC->bdcr >> 8) & 0x3ul);
}

/**
 * \brief RTCʱ��ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_bdcr_rtc_enable (void)
{

    HK32F103RBT6_RCC->bdcr |= (1ul << 15);
}
/**
 * \brief RTCʱ�ӽ���
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_bdcr_rtc_disable (void)
{

    HK32F103RBT6_RCC->bdcr &= ~(1ul << 15);
}

/**
 * \brief �����������λ
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_bdcr_bdrst_reset (void)
{

    HK32F103RBT6_RCC->bdcr |= (1ul << 16);
}
/**
 * \brief �����������λ����
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_bdcr_bdrst_reset_end (void)
{

    HK32F103RBT6_RCC->bdcr &= ~(1ul << 16);
}

/**
 * \brief HSE ���������ȴ�ʱ������
 *
 * \param[in]  value ������ֵ
 *
 * �ȴ�ʱ�� = value * 8 * hseʱ������
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_hse_wt_set(uint16_t value)
{
    HK32F103RBT6_RCC->wts = ((value & 0x1ffful) << 0) |
                                 (HK32F103RBT6_RCC->wts & ~(0x1ffful << 0));
}

/**
 * \brief XCH_IOp[2:0]  HSE����������������
 */
typedef enum amhw_hk32f103rbt6_rcc_hse_iop_set {
    AMHW_HK32F103RBT6_RCC_HSE_IOP_20 = 0,/**< \brief ����������ԼΪ20uA���Ƽ�ʹ��0.5~3MHz���� */
    AMHW_HK32F103RBT6_RCC_HSE_IOP_30,    /**< \brief ����������ԼΪ30uA���Ƽ�ʹ��0.5~4MHz���� */
    AMHW_HK32F103RBT6_RCC_HSE_IOP_40,    /**< \brief ����������ԼΪ40uA���Ƽ�ʹ��0.5~5MHz���� */
    AMHW_HK32F103RBT6_RCC_HSE_IOP_50,    /**< \brief ����������ԼΪ50uA���Ƽ�ʹ��1~6MHz���� */
    AMHW_HK32F103RBT6_RCC_HSE_IOP_60,    /**< \brief ����������ԼΪ60uA���Ƽ�ʹ��2~12MHz���� */
    AMHW_HK32F103RBT6_RCC_HSE_IOP_80,    /**< \brief ����������ԼΪ80uA���Ƽ�ʹ��2~15MHz���� */
    AMHW_HK32F103RBT6_RCC_HSE_IOP_100,   /**< \brief ����������ԼΪ100uA���Ƽ�ʹ��3~20MHz���� */
    AMHW_HK32F103RBT6_RCC_HSE_IOP_200,   /**< \brief ����������ԼΪ200uA���Ƽ�ʹ��5~30MHz���� */
} amhw_hk32f103rbt6_rcc_hse_iop_set_t;
/**
 * \brief XCH_IOp[2:0]  HSE����������������
 *
 * \param[in] status_flag��HSE���������������ã�
 *                        ֵΪ amhw_hk32f103rbt6_rcc_hse_iop_set_t ��һö������
 *
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_hse_iop_set (amhw_hk32f103rbt6_rcc_hse_iop_set_t hse_iop_set)
{
    HK32F103RBT6_RCC->wts = (HK32F103RBT6_RCC->wts & ~(0x7ul << 16)) |
                      ((hse_iop_set & 0x7ul) << 16) ;

}

/**
 * \brief HSE Ƭ��ģ���������bypass����
 *
 *
 *  0 ��HSE ʱ���źž���Ƭ��ģ����������ʹ�á�
 *  1 ��bypass Ƭ��HSE ģ����������
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_hsenf_byp_cfg(uint8_t index)
{
    HK32F103RBT6_RCC->wts = ((index & 0x1ul) << 24) |
                                       (HK32F103RBT6_RCC->wts & ~(0x1ul << 24));
}

/**
 * \brief ����ϵͳʱ��ѡ��
 *
 * \param[in]  index : ����ʱ��
 *
 *      - AMHW_HK32F103RBT6_LCLK_LSI  �� �����ڲ�LSIʱ��
 *      - AMHW_HK32F103RBT6_LCLK_LSE  �� �����ⲿLSEʱ��
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_lclk_sel(amhw_hk32f103rbt6_lclk index)
{
    HK32F103RBT6_RCC->lpclk_ctl = ((index & 0x1ul) << 0) |
                                       (HK32F103RBT6_RCC->lpclk_ctl & ~(0x1ul << 0));
}

/**
 * \brief USB1.1ʱ��ʹ��
 *
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_usbclk_enable(void)
{
    HK32F103RBT6_RCC->lpclk_ctl |= ( 0x1ul << 8);
}

/**
 * \brief USB1.1ʱ�ӽ���
 *
 */
am_static_inline
void amhw_hk32f103rbt6_rcc_usbclk_disable(void)
{
    HK32F103RBT6_RCC->lpclk_ctl &= ~( 0x1ul << 8);
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __HK32F103RBT6_RCC_H */

#endif

/* end of file */
