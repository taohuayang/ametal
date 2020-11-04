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
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG118_RCC_H
#define __AMHW_ZLG118_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "zlg118_regbase.h"

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
 * \addtogroup amhw_zlg118_if_rcc
 * \copydoc amhw_zlg118_rcc.h
 * @{
 */

/**
 * \brief CRC�Ĵ�����ṹ��
 */
typedef struct amhw_zlg118_rcc {
  __IO uint32_t sysctrl[3];       /**< \brief ϵͳ���ƼĴ���0��1��2 */
  __IO uint32_t rch_cr;           /**< \brief �ڲ�����ʱ�ӿ��ƼĴ��� */
  __IO uint32_t xth_cr;           /**< \brief �ⲿ����ʱ�ӿ��ƼĴ��� */
  __IO uint32_t rcl_cr;           /**< \brief �ڲ�����ʱ�ӿ��ƼĴ��� */
  __IO uint32_t xtl_cr;            /**< \brief �ⲿ����ʱ�ӿ��ƼĴ��� */
  __IO uint32_t reserve0;         /**< \brief ����λ */
  __IO uint32_t peri_clken[2];    /**< \brief ����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t reserve1[5];         /**< \brief ����λ */
  __IO uint32_t pll_cr;           /**< \brief PLLʱ�ӿ��ƼĴ��� */
} amhw_zlg118_rcc_t;

#define ZLG118_RCCCTRL            ((amhw_zlg118_rcc_t *)ZLG118_RCC_BASE)

/**
 * \brief ����ö��
 */
typedef enum {

    /* peri_clken[0]�Ĵ������Ƶ�����ʹ��λ  */
    AMHW_ZLG118_RCC_FLASH   = 31,
    AMHW_ZLG118_RCC_DMA     = 29,
    AMHW_ZLG118_RCC_GPIO    = 28,
    AMHW_ZLG118_RCC_AES     = 27,
    AMHW_ZLG118_RCC_CRC     = 26,
    AMHW_ZLG118_RCC_SWD     = 25,
    AMHW_ZLG118_RCC_TICK    = 24,
    AMHW_ZLG118_RCC_LCD     = 22,
    AMHW_ZLG118_RCC_TRIM    = 21,
    AMHW_ZLG118_RCC_RTC     = 20,
    AMHW_ZLG118_RCC_PCNT    = 19,
    AMHW_ZLG118_RCC_RNG     = 18,
    AMHW_ZLG118_RCC_VC      = 17,
    AMHW_ZLG118_RCC_ADC     = 16,
    AMHW_ZLG118_RCC_WDT     = 15,
    AMHW_ZLG118_RCC_PCA     = 14,
    AMHW_ZLG118_RCC_OPA     = 13,
    AMHW_ZLG118_RCC_TIM3    = 11,
    AMHW_ZLG118_RCC_ADVTIM  = 10,
    AMHW_ZLG118_RCC_LPTIM0  = 9,
    AMHW_ZLG118_RCC_BASETIM = 8,
    AMHW_ZLG118_RCC_SPI1    = 7,
    AMHW_ZLG118_RCC_SPI0    = 6,
    AMHW_ZLG118_RCC_I2C1    = 5,
    AMHW_ZLG118_RCC_I2C0    = 4,
    AMHW_ZLG118_RCC_LPUART1 = 3,
    AMHW_ZLG118_RCC_LPUART0 = 2,
    AMHW_ZLG118_RCC_UART1   = 1,
    AMHW_ZLG118_RCC_UART0   = 0,

    /* peri_clken[1]�Ĵ������Ƶ�����ʹ��λ  */
    AMHW_ZLG118_RCC_UART3   = 9 + 31,
    AMHW_ZLG118_RCC_UART2   = 8 + 31,
    AMHW_ZLG118_RCC_LPTIM1  = 4 + 31,
    AMHW_ZLG118_RCC_DAC     = 3 + 31,
}amhw_zlg118_peripheral;

/**
 * \brief ϵͳʱ��Դ
 */
typedef enum {
    AMHW_ZLG118_SYSCLK_RCH = 0,   /**< \brief �ڲ�����ʱ����Ϊϵͳʱ�� */
    AMHW_ZLG118_SYSCLK_XTH,       /**< \brief �ⲿ����ʱ����Ϊϵͳʱ�� */
    AMHW_ZLG118_SYSCLK_RCL,       /**< \brief �ڲ�����ʱ����Ϊϵͳʱ�� */
    AMHW_ZLG118_SYSCLK_XTL,       /**< \brief �ⲿ����ʱ����Ϊϵͳʱ�� */
    AMHW_ZLG118_SYSCLK_PLL = 4,   /**< \brief �ڲ�PLL��Ϊϵͳʱ�� */
}amhw_zlg118_sys_clk_src;

/**
 * \brief HCLKʱ��Դ
 */
typedef enum {
    AMHW_ZLG118_HCLK_SYSCLK = 0,        /**< \brief ϵͳʱ��/1  ��ΪHCLKԴ */
    AMHW_ZLG118_HCLK_SYSCLK_DIV2,       /**< \brief ϵͳʱ��/2  ��ΪHCLKԴ */
    AMHW_ZLG118_HCLK_SYSCLK_DIV4,       /**< \brief ϵͳʱ��/4  ��ΪHCLKԴ */
    AMHW_ZLG118_HCLK_SYSCLK_DIV8,       /**< \brief ϵͳʱ��/8  ��ΪHCLKԴ */
    AMHW_ZLG118_HCLK_SYSCLK_DIV16,      /**< \brief ϵͳʱ��/16 ��ΪHCLKԴ */
    AMHW_ZLG118_HCLK_SYSCLK_DIV32,      /**< \brief ϵͳʱ��/32 ��ΪHCLKԴ */
    AMHW_ZLG118_HCLK_SYSCLK_DIV64,      /**< \brief ϵͳʱ��/64 ��ΪHCLKԴ */
    AMHW_ZLG118_HCLK_SYSCLK_DIV128,     /**< \brief ϵͳʱ��/128��ΪHCLKԴ */
}amhw_zlg118_hclk_src;

/**
 * \brief PCLKʱ��Դ
 */
typedef enum {
    AMHW_ZLG118_PCLK_HCLK = 0,        /**< \brief HCLKʱ��/1  ��ΪPCLKԴ */
    AMHW_ZLG118_PCLK_HCLK_DIV2,       /**< \brief HCLKʱ��/2  ��ΪPCLKԴ */
    AMHW_ZLG118_PCLK_HCLK_DIV4,       /**< \brief HCLKʱ��/4  ��ΪPCLKԴ */
    AMHW_ZLG118_PCLK_HCLK_DIV8,       /**< \brief HCLKʱ��/8  ��ΪPCLKԴ */
}amhw_zlg118_pclk_src;

/**
 * \brief SYSCTRL2 �Ĵ��� SYSCTL0��SYSCTRL1����ϵ�п��ƼĴ�����
 *
 * \param[in]  data ��д������
 *
 * \note �Ĵ��� SYSCTL0��SYSCTRL1����ϵ�п��ƼĴ�����
 *       �� SYSCTRL2��д0x5A5A����д 0xA5A5���������ڼĴ��� SYSCTL0��SYSCTRL1��д������
 *       ֻҪ�ԼĴ��� SYSCTL0�� SYSCTRL1д�����ˣ��������λ�Զ��ظ�����״̬����Ҫ����д��ϵ�д򿪱�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_set_start (uint16_t data)
{
    ZLG118_RCCCTRL->sysctrl[2] = data;
}

/**
 * \brief  wakeup_byRCH  ��deepsleep���Ѻ�ϵͳʱ��Դ����ΪRCH��ԭʱ�Ӽ���ʹ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zlg118_rcc_wakeup_sysclk_rch (void)
{
    ZLG118_RCCCTRL->sysctrl[0] |= (1ul << 15);
}

/**
 * \brief wakeup_byRCH  ��deepsleep���Ѻ󣬲��ı�ϵͳʱ��Դ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zlg118_rcc_wakeup_sysclk_nochange (void)
{
    ZLG118_RCCCTRL->sysctrl[0] &= ~(1ul << 15);
}

/**
 * \brief PCLK_PRS PCLKʱ��Դ�л�
 *
 * \param[in]  src ��PCLKʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pclk_set (amhw_zlg118_pclk_src src)
{

    ZLG118_RCCCTRL->sysctrl[0] = (ZLG118_RCCCTRL->sysctrl[0] & ~(0x3ul << 11)) |
                                 ((src & 0x3ul) << 11);
}

/**
 * \brief HCLK_PRS HCLKʱ��Դ�л�
 *
 * \param[in]  src ��HCLKʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_hclk_set (amhw_zlg118_hclk_src src)
{

    ZLG118_RCCCTRL->sysctrl[0] = (ZLG118_RCCCTRL->sysctrl[0] & ~(0x7ul << 8)) |
                                 ((src & 0x7ul) << 8);
}

/**
 * \brief CLKSW ϵͳʱ��Դ�л�
 *
 * \param[in]  src ��ϵͳʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_sys_clk_set (amhw_zlg118_sys_clk_src src)
{

    ZLG118_RCCCTRL->sysctrl[0] &= ~(0x7ul << 5);

    amhw_zlg118_rcc_set_start(0x5A5A);
    amhw_zlg118_rcc_set_start(0xA5A5);
    ZLG118_RCCCTRL->sysctrl[0] |= (src  << 5);
}

/**
 * \brief PLL_EN PLL����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pll_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] &= ~(1ul << 4);
}

/**
 * \brief PLL_EN PLLʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pll_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] |= (1ul << 4);
}

/**
 * \brief XTL_EN �ⲿ���پ���XTL����
 *
 * \note ��Ҫ��PC14�� PC15���ó�ģ��˿�.
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] &= ~(1ul << 3);
}

/**
 * \brief XTL_EN �ⲿ���پ���XTLʹ��
 *
 * \note ��Ҫ��PC14�� PC15���ó�ģ��˿�.
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] |= (1ul << 3);
}

/**
 * \brief RCL_EN �ڲ�����ʱ��RCL����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rcl_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] &= ~(1ul << 2);
}

/**
 * \brief RCL_EN �ڲ�����ʱ��RCLʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rcl_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] |= (1ul << 2);
}

/**
 * \brief ��ȡ�ڲ�����ʱ��RCL�Ƿ�ʹ��
 *
 * \return ��
 */
am_static_inline
am_bool_t amhw_zlg118_rcc_rcl_enable_get (void)
{
    return (ZLG118_RCCCTRL->sysctrl[0] & (1ul << 2)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief XTH_EN �ⲿ���پ���XTH����
 *
 * \note ��ϵͳ����DeepSleep���˸���ʱ�ӻ��Զ��رա�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xth_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] &= ~(1ul << 1);
}

/**
 * \brief XTH_EN �ⲿ���پ���XTHʹ��
 *
 * \note ��ϵͳ����DeepSleep���˸���ʱ�ӻ��Զ��رա�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xth_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] |= (1ul << 1);
}

/**
 * \brief RCH_EN �ڲ�����ʱ��RCH����
 *
c
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rch_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] &= ~(1ul << 0);
}

/**
 * \brief RCH_EN �ڲ�����ʱ��RCHʹ��
 *
 * \note ��ϵͳ����DeepSleep���˸���ʱ�ӻ��Զ��رա�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rch_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[0] |= (1ul << 0);
}

/**
 * \brief ��ȡ�ڲ�����ʱ��RCH�Ƿ�ʹ��
 *
 * \return ��
 */
am_static_inline
am_bool_t amhw_zlg118_rcc_rch_enable_get (void)
{
    return (ZLG118_RCCCTRL->sysctrl[0] & (1ul << 0)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief RTC����ʱ�Ӳ���ʱ��Ƶ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_RTCCLK_ADJUST_4M = 0,    /**< \brief 4  MHz����ʱ��Ƶ�� */
    AMHW_ZLG118_RTCCLK_ADJUST_6M,        /**< \brief 6  MHz����ʱ��Ƶ�� */
    AMHW_ZLG118_RTCCLK_ADJUST_8M,        /**< \brief 8  MHz����ʱ��Ƶ�� */
    AMHW_ZLG118_RTCCLK_ADJUST_10M,       /**< \brief 10 MHz����ʱ��Ƶ�� */
    AMHW_ZLG118_RTCCLK_ADJUST_16M,       /**< \brief 16 MHz����ʱ��Ƶ�� */
    AMHW_ZLG118_RTCCLK_ADJUST_20M,       /**< \brief 20 MHz����ʱ��Ƶ�� */
    AMHW_ZLG118_RTCCLK_ADJUST_24M,       /**< \brief 24 MHz����ʱ��Ƶ�� */
    AMHW_ZLG118_RTCCLK_ADJUST_32M,       /**< \brief 32 MHz����ʱ��Ƶ�� */
}amhw_zlg118_rtcclk_adjust;

/**
 * \brief RTC_FREQ_ADJUST RTC����ʱ�Ӳ���ʱ��Ƶ��ѡ��
 *
 * \param[in]  choice ������ʱ��Ƶ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rtcclk_adjust_set (amhw_zlg118_rtcclk_adjust choice)
{
    ZLG118_RCCCTRL->sysctrl[1] = (ZLG118_RCCCTRL->sysctrl[1] & (~(0x7ul << 9))) |
                                 ((choice & 0x7ul) << 9);
}


/**
 * \brief SWD_USE_IO SWD�˿ڹ������ã�SWD��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_swdio_debug (void)
{
    ZLG118_RCCCTRL->sysctrl[1] &= ~(1ul << 8);
}

/**
 * \brief SWD_USE_IO SWD�˿ڹ������ã�GPIO��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_swdio_gpio (void)
{
    ZLG118_RCCCTRL->sysctrl[1] |= (1ul << 8);
}

/**
 * \brief LOCKUP_EN Cortex-M0+ LockUp����
 *
 * \note ʹ�ܺ�CPU������Чָ��ʱ�ḴλMCU������ǿϵͳ�ɿ��ԡ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_lockup_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[1] &= ~(1ul << 6);
}

/**
 * \brief LOCKUP_EN Cortex-M0+ LockUpʹ��
 *
 * \note ʹ�ܺ�CPU������Чָ��ʱ�ḴλMCU������ǿϵͳ�ɿ��ԡ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_lockup_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[1] |= (1ul << 6);
}

/**
 * \brief RTC_LPW RTCģ��͹��Ľ���
 *
 * \note ʹ�ܺ� RTCģ����͹���״̬����Ĵ��������Զ�д��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rtc_lowpower_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[1] &= ~(1ul << 5);
}

/**
 * \brief RTC_LPW RTCģ��͹���ʹ��
 *
 * \note ʹ�ܺ� RTCģ����͹���״̬����Ĵ��������Զ�д��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rtc_lowpower_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[1] |= (1ul << 5);
}

/**
 * \brief XTL_ALWAYS_ON XTL�߼�ʹ�ܿ��ƽ���
 *
 * \note ʹ�ܺ� sysctrl[0].XTL_ENֻ����λ��
 *       ���ܺ� sysctrl[0].XTL_EN����λ�����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_alwayson_disable (void)
{
    ZLG118_RCCCTRL->sysctrl[1] &= ~(1ul << 3);
}

/**
 * \brief XTL_ALWAYS_ON XTL�߼�ʹ�ܿ���ʹ��
 *
 * \note ʹ�ܺ� sysctrl[0].XTL_ENֻ����λ��
 *       ���ܺ� sysctrl[0].XTL_EN����λ�����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_alwayson_enable (void)
{
    ZLG118_RCCCTRL->sysctrl[1] |= (1ul << 3);
}


/**
 * \brief �ⲿ XTLʱ���������
 */
typedef enum {
    AMHW_ZLG118_XTL_INPUT_XTAL = 0,    /**< \brief XTL�����ɾ������ */
    AMHW_ZLG118_XTL_INPUT_PC14,        /**< \brief XTL������ PC14���� */
}amhw_zlg118_xtl_input;

/**
 * \brief EXTL_EN XTLʱ���������
 *
 * \param[in]  choice ��XTLʱ������ѡ��
 *
 * \note ʹ��PC14����ʱ��ʱ��������sysctrl[0].XTL_ENΪ1��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_input_set (amhw_zlg118_xtl_input choice)
{
    ZLG118_RCCCTRL->sysctrl[1] = (ZLG118_RCCCTRL->sysctrl[1] & (~(0x1ul << 2))) |
                                 ((choice & 0x1ul) << 2);
}

/**
 * \brief �ⲿ XTHʱ���������
 */
typedef enum {
    AMHW_ZLG118_XTH_INPUT_XTAL = 0,    /**< \brief XTH�����ɾ������ */
    AMHW_ZLG118_XTH_INPUT_PF00,        /**< \brief XTH������PF00���� */
}amhw_zlg118_xth_input;

/**
 * \brief EXTH_EN XTHʱ���������
 *
 * \param[in]  choice ��XTHʱ������ѡ��
 *
 * \note ʹ��PC14����ʱ��ʱ��������sysctrl[0].XTH_ENΪ1��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xth_input_set (amhw_zlg118_xth_input choice)
{
    ZLG118_RCCCTRL->sysctrl[1] = (ZLG118_RCCCTRL->sysctrl[1] & (~(0x1ul << 1))) |
                                 ((choice & 0x1ul) << 1);
}


/**
 * \brief stable RCHʱ���ȶ���־λ
 *
 * \retval TRUE  : �Ѿ��ȶ������Ա��ڲ���·ʹ�á�
 * \retval FALSE : δ�ȶ��������Ա��ڲ���·ʹ�á�
 */
am_static_inline
am_bool_t amhw_zlg118_rcc_rch_state_get (void)
{
    return (am_bool_t)((ZLG118_RCCCTRL->rch_cr & (0x1ul << 11)) ?
                       AM_TRUE :
                       AM_FALSE);
}

typedef enum {
    AMHW_ZLG118_RCH_FRE_24MHz = 0x00100C00,
    AMHW_ZLG118_RCH_FRE_22MHz = 0x00100C02,   // 22.12MHz
    AMHW_ZLG118_RCH_FRE_16MHz = 0x00100C04,
    AMHW_ZLG118_RCH_FRE_8MHz = 0x00100C06,
    AMHW_ZLG118_RCH_FRE_4MHz = 0x00100C08,
}amhw_zlg118_rch_fre_t;
/**
 * \brief TRIM ʱ��Ƶ�ʵ���
 *
 * \param[in]  data ��д������
 *
 * \note ʱ��Ƶ�ʵ����� Flash�б�����5��Ƶ�ʵ�У׼ֵ��
 *       ��Flash�ڵ�У׼ֵ������д��RCH_CR.TRIM���ɻ�þ�׼��Ƶ�ʡ�
 *
 *       24MУ׼ֵ��ַ         �� 0x00100C00 - 0x00100C01
 *       22.12MУ׼ֵ��ַ�� 0x00100C02 - 0x00100C03
 *       16MУ׼ֵ��ַ         �� 0x00100C04 - 0x00100C05
 *       8MУ׼ֵ��ַ            �� 0x00100C06 - 0x00100C07
 *       4MУ׼ֵ��ַ            �� 0x00100C08 - 0x00100C09
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rch_trim_set (uint16_t data)
{
    ZLG118_RCCCTRL->rch_cr = (ZLG118_RCCCTRL->rch_cr & (~0x07FFul)) |
                         (data & 0x07FFul);
}

/**
 * \brief TRIM ʱ��Ƶ�ʻ�ȡ
 *
 * \return �Ĵ����ڲ���ʱ��Ƶ��У׼ֵ
 */
am_static_inline
uint16_t amhw_zlg118_rcc_rch_trim_get (void)
{
    return (ZLG118_RCCCTRL->rch_cr & 0x07FFul);
}

/**
 * \brief stable XTHʱ���ȶ���־λ
 *
 * \retval TRUE  : �Ѿ��ȶ������Ա��ڲ���·ʹ�á�
 * \retval FALSE : δ�ȶ��������Ա��ڲ���·ʹ�á�
 */
am_static_inline
am_bool_t amhw_zlg118_rcc_xth_state_get (void)
{
    return (am_bool_t)((ZLG118_RCCCTRL->xth_cr & (0x1ul << 6)) ?
                       AM_TRUE :
                       AM_FALSE);
}


/**
 * \brief �ⲿ����ʱ��XTH�ȶ�ʱ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_XTH_WAITTIME_256 = 0,       /**< \brief �ȶ�ʱ��Ϊ256������ */
    AMHW_ZLG118_XTH_WAITTIME_1024,          /**< \brief �ȶ�ʱ��Ϊ1024������ */
    AMHW_ZLG118_XTH_WAITTIME_4096,          /**< \brief �ȶ�ʱ��Ϊ4096������ */
    AMHW_ZLG118_XTH_WAITTIME_16384,         /**< \brief �ȶ�ʱ��Ϊ16384������ */
}amhw_zlg118_xth_waittime;

/**
 * \brief Startup �ⲿ����ʱ��XTH�ȶ�ʱ��ѡ��
 *
 * \param[in]  data ��д������
 *
 * \note ǿ�ҽ��齫 XTH ���ȶ�ʱ������Ϊ 11��AMHW_ZLG118_XTH_WAITTIME_16384����
 *       ���XTH�ȶ�ʱ�䲻�㣬�ڽ���ʱ���л�ʱ���������߻���ʱ��ϵͳ�����ȶ�������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xth_waittime_set (amhw_zlg118_xth_waittime time_set)
{
    ZLG118_RCCCTRL->xth_cr = (ZLG118_RCCCTRL->xth_cr & (~(0x3ul << 4))) |
                         ((time_set & 0x3ul) << 4);
}

/**
 * \brief �ⲿ������Ƶ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_XTH_XTAL_FRE_4_6 = 0,       /**< \brief 4M~6M */
    AMHW_ZLG118_XTH_XTAL_FRE_6_12,          /**< \brief 6M~12M */
    AMHW_ZLG118_XTH_XTAL_FRE_12_20,         /**< \brief 12M~20M */
    AMHW_ZLG118_XTH_XTAL_FRE_20_32,         /**< \brief 20M~32M */
}amhw_zlg118_xth_xtal_fre;

/**
 * \brief xth_fsel �ⲿ������Ƶ��ѡ��
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xth_xtal_fre_set (amhw_zlg118_xth_xtal_fre fre)
{
    ZLG118_RCCCTRL->xth_cr = (ZLG118_RCCCTRL->xth_cr & (~(0x3ul << 2))) |
                         ((fre & 0x3ul) << 2);
}

/**
 * \brief �ⲿ������������ѡ��
 */
typedef enum {
    AMHW_ZLG118_XTH_XTAL_DRIVER_MIN = 0,       /**< \brief ������������ */
    AMHW_ZLG118_XTH_XTAL_DRIVER_SMALL,         /**< \brief ���������� */
    AMHW_ZLG118_XTH_XTAL_DRIVER_DEFAULT,       /**< \brief Ĭ���������� (�Ƽ�ֵ) */
    AMHW_ZLG118_XTH_XTAL_DRIVER_MAX,           /**< \brief ��ǿ�������� */
}amhw_zlg118_xth_xtal_driver;

/**
 * \brief Driver �ⲿ������������ѡ��
 *
 * \param[in]  data ��д������
 *
 * \note ��Ҫ���ݾ������ԡ����ص����Լ���·��ļ�������ѡ���ʵ�������������
 *       ��������Խ���򹦺�Խ����������Խ���򹦺�ԽС��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xth_xtal_driver_set (amhw_zlg118_xth_xtal_driver driver_set)
{
    ZLG118_RCCCTRL->xth_cr = (ZLG118_RCCCTRL->xth_cr & (~(0x3ul << 0))) |
                             ((driver_set & 0x3ul) << 0);
}

/**
 * \brief stable RCLʱ���ȶ���־λ
 *
 * \retval TRUE  : �Ѿ��ȶ������Ա��ڲ���·ʹ�á�
 * \retval FALSE : δ�ȶ��������Ա��ڲ���·ʹ�á�
 */
am_static_inline
am_bool_t amhw_zlg118_rcc_rcl_state_get (void)
{
    return (am_bool_t)((ZLG118_RCCCTRL->rcl_cr & (0x1ul << 12)) ?
                       AM_TRUE :
                       AM_FALSE);
}

/**
 * \brief �ڲ�����ʱ��RCL�ȶ�ʱ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_RCL_WAITTIME_4 = 0,       /**< \brief �ȶ�ʱ��Ϊ4������ */
    AMHW_ZLG118_RCL_WAITTIME_16,          /**< \brief �ȶ�ʱ��Ϊ16������ */
    AMHW_ZLG118_RCL_WAITTIME_64,          /**< \brief �ȶ�ʱ��Ϊ64������ */
    AMHW_ZLG118_RCL_WAITTIME_256,         /**< \brief �ȶ�ʱ��Ϊ256������ */
}amhw_zlg118_rcl_waittime;

/**
 * \brief Startup �ڲ�����ʱ��RCL�ȶ�ʱ��ѡ��
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rcl_waittime_set (amhw_zlg118_rcl_waittime time_set)
{
    ZLG118_RCCCTRL->rcl_cr = (ZLG118_RCCCTRL->rcl_cr & (~(0x3ul << 10))) |
                             ((time_set & 0x3ul) << 10);
}

typedef enum {
    AMHW_ZLG118_RCl_FRE_38400Hz = 0x00100C20,
    AMHW_ZLG118_RCl_FRE_32768Hz = 0x00100C22,
}amhw_zlg118_rcl_fre_t;

/**
 * \brief TRIM ʱ��Ƶ�ʵ���
 *
 * \param[in]  data ��д������
 *
 * \note �ڲ�����ʱ��Ƶ�ʵ����� Flash�б�����2��Ƶ�ʵ�У׼ֵ��
 *       ��Flash�ڵ�У׼ֵ������д��RCL_CR.TRIM���ɻ�þ�׼��Ƶ�ʡ�
 *
 *       38.4KУ׼ֵ��ַ      �� 0x00100C20 - 0x00100C21
 *       32.768KУ׼ֵ��ַ�� 0x00100C22 - 0x00100C23
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_rcl_trim_set (uint16_t data)
{
    ZLG118_RCCCTRL->rcl_cr = (ZLG118_RCCCTRL->rcl_cr & (~0x03FFul)) |
                         (data & 0x03FFul);
}

/**
 * \brief TRIM ʱ��Ƶ�ʻ�ȡ
 *
 * \return �Ĵ����ڲ���ʱ��Ƶ��У׼ֵ
 */
am_static_inline
uint16_t amhw_zlg118_rcc_rcl_trim_get (void)
{
    return (ZLG118_RCCCTRL->rcl_cr & 0x07FFul);
}

/**
 * \brief stable XTLʱ���ȶ���־λ
 *
 * \retval TRUE  : �Ѿ��ȶ������Ա��ڲ���·ʹ�á�
 * \retval FALSE : δ�ȶ��������Ա��ڲ���·ʹ�á�
 */
am_static_inline
am_bool_t amhw_zlg118_rcc_xtl_state_get (void)
{
    return (am_bool_t)((ZLG118_RCCCTRL->xtl_cr & (0x1ul << 6)) ?
                       AM_TRUE :
                       AM_FALSE);
}

/**
 * \brief �ڲ�����ʱ��RCL�ȶ�ʱ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_XTL_WAITTIME_256 = 0,       /**< \brief �ȶ�ʱ��Ϊ256������ */
    AMHW_ZLG118_XTL_WAITTIME_1024,          /**< \brief �ȶ�ʱ��Ϊ1024������ */
    AMHW_ZLG118_XTL_WAITTIME_4096,          /**< \brief �ȶ�ʱ��Ϊ4096������ */
    AMHW_ZLG118_XTL_WAITTIME_16384,         /**< \brief �ȶ�ʱ��Ϊ16384������ */
}amhw_zlg118_xtl_waittime;

/**
 * \brief Startup �ڲ�����ʱ��XTL�ȶ�ʱ��ѡ��
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_waittime_set (amhw_zlg118_xtl_waittime time_set)
{
    ZLG118_RCCCTRL->xtl_cr = (ZLG118_RCCCTRL->xtl_cr & (~(0x3ul << 4))) |
                             ((time_set & 0x3ul) << 4);
}

/**
 * \brief XTL�����񵴷��ȵĵ���
 */
typedef enum {
    AMHW_ZLG118_XTL_XTAL_AMPLITUDE_MIN = 0,       /**< \brief ��С��� */
    AMHW_ZLG118_XTL_XTAL_AMPLITUDE_NORMAL,        /**< \brief ������� */
    AMHW_ZLG118_XTL_XTAL_AMPLITUDE_BIG_DEFAULT,   /**< \brief �ϴ�������Ƽ�ֵ�� */
    AMHW_ZLG118_XTL_XTAL_AMPLITUDE_MAX,           /**< \brief ������ */
}amhw_zlg118_xtl_xtal_amplitude;

/**
 * \brief Driver XTL�����񵴷��ȵĵ���
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_xtal_amplitude_set (amhw_zlg118_xtl_xtal_amplitude driver_set)
{
    ZLG118_RCCCTRL->xtl_cr = (ZLG118_RCCCTRL->xtl_cr & (~(0x3ul << 2))) |
                             ((driver_set & 0x3ul) << 2);
}

/**
 * \brief �ⲿ������������ѡ��
 */
typedef enum {
    AMHW_ZLG118_XTL_XTAL_DRIVER_MIN = 0,       /**< \brief ������������ */
    AMHW_ZLG118_XTL_XTAL_DRIVER_DEFAULT,       /**< \brief һ���������� ���Ƽ�ֵ�� */
    AMHW_ZLG118_XTL_XTAL_DRIVER_BIG,           /**< \brief ��ǿ�������� */
    AMHW_ZLG118_XTL_XTAL_DRIVER_MAX,           /**< \brief ��ǿ�������� */
}amhw_zlg118_xtl_xtal_driver;

/**
 * \brief Driver �ⲿ���پ�����������ѡ��
 *
 * \param[in]  data ��д������
 *
 * \note ��Ҫ���ݾ������ԡ����ص����Լ���·��ļ�������ѡ���ʵ�������������
 *       ��������Խ���򹦺�Խ����������Խ���򹦺�ԽС��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_xtl_xtal_driver_set (amhw_zlg118_xtl_xtal_driver driver_set)
{
    ZLG118_RCCCTRL->xtl_cr = (ZLG118_RCCCTRL->xtl_cr & (~(0x3ul << 0))) |
                             ((driver_set & 0x3ul) << 0);
}

/**
 * \brief stable PLL�ȶ���־
 *
 * \retval TRUE  : �Ѿ��ȶ������Ա��ڲ���·ʹ�á�
 * \retval FALSE : δ�ȶ��������Ա��ڲ���·ʹ�á�
 */
am_static_inline
am_bool_t amhw_zlg118_rcc_pll_state_get (void)
{
    return (am_bool_t)((ZLG118_RCCCTRL->pll_cr & (0x1ul << 18)) ?
                       AM_TRUE :
                       AM_FALSE);
}

/**
 * \brief PLL�ȶ�ʱ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_PLL_WAITTIME_128 = 0,      /**< \brief �ȶ�ʱ��Ϊ128������ */
    AMHW_ZLG118_PLL_WAITTIME_256,          /**< \brief �ȶ�ʱ��Ϊ256������ */
    AMHW_ZLG118_PLL_WAITTIME_512,          /**< \brief �ȶ�ʱ��Ϊ512������ */
    AMHW_ZLG118_PLL_WAITTIME_1024,         /**< \brief �ȶ�ʱ��Ϊ1024������ */
    AMHW_ZLG118_PLL_WAITTIME_2048,         /**< \brief �ȶ�ʱ��Ϊ2048������ */
    AMHW_ZLG118_PLL_WAITTIME_4096,         /**< \brief �ȶ�ʱ��Ϊ4096������ */
    AMHW_ZLG118_PLL_WAITTIME_8192,         /**< \brief �ȶ�ʱ��Ϊ8192������ */
    AMHW_ZLG118_PLL_WAITTIME_16384,        /**< \brief �ȶ�ʱ��Ϊ16384������ */
}amhw_zlg118_pll_waittime;

/**
 * \brief Startup PLL�ȶ�ʱ��ѡ��
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pll_waittime_set (amhw_zlg118_pll_waittime time_set)
{
    ZLG118_RCCCTRL->pll_cr = (ZLG118_RCCCTRL->pll_cr & (~(0x7ul << 15))) |
                         ((time_set & 0x7ul) << 15);
}

/**
 * \brief PLL����Ƶ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_PLL_INPUT_FRE_4_6 = 0,       /**< \brief 4M~6M */
    AMHW_ZLG118_PLL_INPUT_FRE_6_12,          /**< \brief 6M~12M */
    AMHW_ZLG118_PLL_INPUT_FRE_12_20,         /**< \brief 12M~20M */
    AMHW_ZLG118_PLL_INPUT_FRE_20_24,         /**< \brief 20M~32M */
}amhw_zlg118_pll_input_fre;

/**
 * \brief FRSEL PLL����Ƶ��ѡ��
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pll_input_fre_set (amhw_zlg118_pll_input_fre fre)
{
    ZLG118_RCCCTRL->pll_cr = (ZLG118_RCCCTRL->pll_cr & (~(0x3ul << 13))) |
                             ((fre & 0x3ul) << 13);
}

/**
 * \brief DIVN PLL���ʱ�ӵı�Ƶϵ��
 *
 * \param[in]  data ��д������, ����Χ0X2~0XC
 *
 * \note ���Ƶ�� = DIVN*����Ƶ�ʣ�
 *       data ����Χ0X2~0XC
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pll_divn_set (uint8_t data)
{
    ZLG118_RCCCTRL->pll_cr = (ZLG118_RCCCTRL->pll_cr & (~(0xful << 5))) |
                             ((data & 0xful) << 5);
}

/**
 * \brief PLL���Ƶ�ʷ�Χѡ��
 */
typedef enum {
    AMHW_ZLG118_PLL_OUTPUT_FRE_8_12 = 0,      /**< \brief 8M~12M  */
    AMHW_ZLG118_PLL_OUTPUT_FRE_12_18,         /**< \brief 12M~18M */
    AMHW_ZLG118_PLL_OUTPUT_FRE_18_24,         /**< \brief 18M~24M */
    AMHW_ZLG118_PLL_OUTPUT_FRE_24_36,         /**< \brief 24M~36M */
    AMHW_ZLG118_PLL_OUTPUT_FRE_36_48,         /**< \brief 36M~48M */
}amhw_zlg118_pll_output_fre;

/**
 * \brief FOSC PLL���Ƶ�ʷ�Χѡ��
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pll_output_fre_set (amhw_zlg118_pll_output_fre fre)
{
    ZLG118_RCCCTRL->pll_cr = (ZLG118_RCCCTRL->pll_cr & (~(0x7ul << 2))) |
                             ((fre & 0x7ul) << 2);
}

/**
 * \brief PLL����ʱ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_PLL_INPUT_FRE_SRC_XTH_XTAL = 0,   /**< \brief XTH�������ɵ�ʱ��  */
    AMHW_ZLG118_PLL_INPUT_FRE_SRC_XTH_PF00 = 1,   /**< \brief XTH�ӹܽ�PF00�����ʱ�� */
    AMHW_ZLG118_PLL_INPUT_FRE_SRC_RCH      = 3,   /**< \brief RCHʱ�� */
}amhw_zlg118_pll_input_fre_src;

/**
 * \brief FRSEL PLL����ʱ��ѡ��
 *
 * \param[in]  data ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_rcc_pll_input_fre_src_set (amhw_zlg118_pll_input_fre_src fre)
{
    ZLG118_RCCCTRL->pll_cr = (ZLG118_RCCCTRL->pll_cr & (~0x3ul)) |
                             (fre & 0x3ul);
}

/**
 * \brief ʹ������
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 *
 */
void amhw_zlg118_rcc_peripheral_enable (amhw_zlg118_peripheral peri);

/**
 * \brief ���ĳ����ʱ���Ƿ�ʹ��
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return 1: ��ǰ����ʱ����ʹ�ܣ������ٴ�ʹ��
 *         0: ��ǰ����ʱ��δʹ��
 *
 */
int amhw_zlg118_rcc_peripheral_enable_check (amhw_zlg118_peripheral peri);

/**
 * \brief ��������
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_zlg118_rcc_peripheral_disable (amhw_zlg118_peripheral peri);

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
#endif /* __ZLG118_RCC_H */

#endif

/* end of file */
