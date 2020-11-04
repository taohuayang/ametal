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
 * \brief ZSN700 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */

#ifndef __ZSN700_REGBASE_H
#define __ZSN700_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zsn700_if_regbase
 * \copydoc zsn700_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

#define ZSN700_UART0_BASE              (0x40000000UL)  /** \brief UART0����ַ */
#define ZSN700_UART1_BASE              (0x40000100UL)  /** \brief UART1����ַ */
#define ZSN700_UART2_BASE              (0x40006000UL)  /** \brief UART2����ַ */
#define ZSN700_UART3_BASE              (0x40006400UL)  /** \brief UART3����ַ */
#define ZSN700_LPUART0_BASE            (0x40000200UL)  /** \brief LPUART0����ַ */
#define ZSN700_LPUART1_BASE            (0x40004000UL)  /** \brief LPUART1����ַ */
#define ZSN700_I2C0_BASE               (0x40000400UL)  /** \brief I2C0����ַ */
#define ZSN700_I2C1_BASE               (0x40004400UL)  /** \brief I2C1����ַ */
#define ZSN700_SPI0_BASE               (0x40000800UL)  /** \brief SPI0����ַ */
#define ZSN700_SPI1_BASE               (0x40004800UL)  /** \brief SPI1����ַ */
#define ZSN700_TIM0_BASE               (0x40000C00UL)  /** \brief TIM0����ַ */
#define ZSN700_TIM1_BASE               (0x40000D00UL)  /** \brief TIM1����ַ */
#define ZSN700_TIM2_BASE               (0x40000E00UL)  /** \brief TIM2����ַ */
#define ZSN700_TIM3_BASE               (0x40005800UL)  /** \brief TIM3����ַ */
#define ZSN700_TIM4_BASE               (0x40003000UL)  /** \brief TIM4����ַ */
#define ZSN700_TIM5_BASE               (0x40003400UL)  /** \brief TIM5����ַ */
#define ZSN700_TIM6_BASE               (0x40003800UL)  /** \brief TIM6����ַ */
#define ZSN700_LPTIM0_BASE             (0x40000F00UL)  /** \brief LPTIM0����ַ */
#define ZSN700_LPTIM1_BASE             (0x40000F40UL)  /** \brief LPTIM1����ַ */
#define ZSN700_AES_BASE                (0x40021400UL)  /** \brief AES����ַ */
#define ZSN700_ADC_BASE                (0x40002400UL)  /** \brief ADC����ַ */
#define ZSN700_CLKTRIM_BASE            (0x40001800UL)  /** \brief CLKTRIM����ַ */
#define ZSN700_CRC_BASE                (0x40020900UL)  /** \brief CRC����ַ */
#define ZSN700_DAC_BASE                (0x40002500UL)  /** \brief DAC����ַ */
#define ZSN700_DMA_BASE                (0x40021000UL)  /** \brief DMA����ַ */
#define ZSN700_FLASH_BASE              (0x40020000UL)  /** \brief FLASH����ַ */
#define ZSN700_PORT0_BASE              (0x40020C00UL)  /** \brief PORT0����ַ */
#define ZSN700_PORT1_BASE              (0x40022000UL)  /** \brief PORT1����ַ */
#define ZSN700_LCD_BASE                (0x40005C00UL)  /** \brief LCDCTRL����ַ */
#define ZSN700_LVD_BASE                (0x40002400UL)  /** \brief LVD����ַ */
#define ZSN700_RCC_BASE                (0x40002000UL)  /** \brief RCC����ַ */
#define ZSN700_OPA_BASE                (0x40002400UL)  /** \brief OPA����ַ */
#define ZSN700_PCNT_BASE               (0x40005400UL)  /** \brief PCNT����ַ */
#define ZSN700_RAM_BASE                (0x40020400UL)  /** \brief RAM����ַ */
#define ZSN700_PCA_BASE                (0x40001000UL)  /** \brief PCA����ַ */
#define ZSN700_RTC_BASE                (0x40001400UL)  /** \brief RTC����ַ */
#define ZSN700_TRNG_BASE               (0x40004C00UL)  /** \brief TRNG����ַ */
#define ZSN700_VC_BASE                 (0x40002410UL)  /** \brief VC����ַ */
#define ZSN700_WDT_BASE                (0x40000F80UL)  /** \brief WDT����ַ */
#define ZSN700_BGR_BASE                (0x40002400UL)  /** \brief BGR����ַ */
#define ZSN700_SYSTICK                 (0xE000E010UL)  /** \brief SYSTICK����ַ */
/** @} */

/**
 * @} zsn700_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZSN700_REGBASE_H */

/* end of file */
