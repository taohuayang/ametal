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
 * \brief ZLG118 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-03  zp, first implementation
 * \endinternal
 */

#ifndef __ZLG118_REGBASE_H
#define __ZLG118_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zlg118_if_regbase
 * \copydoc zlg118_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

#define ZLG118_UART0_BASE              (0x40000000UL)  /** \brief UART0����ַ */
#define ZLG118_UART1_BASE              (0x40000100UL)  /** \brief UART1����ַ */
#define ZLG118_UART2_BASE              (0x40006000UL)  /** \brief UART2����ַ */
#define ZLG118_UART3_BASE              (0x40006400UL)  /** \brief UART3����ַ */
#define ZLG118_LPUART0_BASE            (0x40000200UL)  /** \brief LPUART0����ַ */
#define ZLG118_LPUART1_BASE            (0x40004000UL)  /** \brief LPUART1����ַ */
#define ZLG118_I2C0_BASE               (0x40000400UL)  /** \brief I2C0����ַ */
#define ZLG118_I2C1_BASE               (0x40004400UL)  /** \brief I2C1����ַ */
#define ZLG118_SPI0_BASE               (0x40000800UL)  /** \brief SPI0����ַ */
#define ZLG118_SPI1_BASE               (0x40004800UL)  /** \brief SPI1����ַ */
#define ZLG118_TIM0_BASE               (0x40000C00UL)  /** \brief TIM0����ַ */
#define ZLG118_TIM1_BASE               (0x40000D00UL)  /** \brief TIM1����ַ */
#define ZLG118_TIM2_BASE               (0x40000E00UL)  /** \brief TIM2����ַ */
#define ZLG118_TIM3_BASE               (0x40005800UL)  /** \brief TIM3����ַ */
#define ZLG118_TIM4_BASE               (0x40003000UL)  /** \brief TIM4����ַ */
#define ZLG118_TIM5_BASE               (0x40003400UL)  /** \brief TIM5����ַ */
#define ZLG118_TIM6_BASE               (0x40003800UL)  /** \brief TIM6����ַ */
#define ZLG118_LPTIM0_BASE             (0x40000F00UL)  /** \brief LPTIM0����ַ */
#define ZLG118_LPTIM1_BASE             (0x40000F40UL)  /** \brief LPTIM1����ַ */
#define ZLG118_AES_BASE                (0x40021400UL)  /** \brief AES����ַ */
#define ZLG118_ADC_BASE                (0x40002400UL)  /** \brief ADC����ַ */
#define ZLG118_CLKTRIM_BASE            (0x40001800UL)  /** \brief CLKTRIM����ַ */
#define ZLG118_CRC_BASE                (0x40020900UL)  /** \brief CRC����ַ */
#define ZLG118_DAC_BASE                (0x40002500UL)  /** \brief DAC����ַ */
#define ZLG118_DMA_BASE                (0x40021000UL)  /** \brief DMA����ַ */
#define ZLG118_FLASH_BASE              (0x40020000UL)  /** \brief FLASH����ַ */
#define ZLG118_PORT0_BASE              (0x40020C00UL)  /** \brief PORT0����ַ */
#define ZLG118_PORT1_BASE              (0x40022000UL)  /** \brief PORT1����ַ */
#define ZLG118_LCD_BASE                (0x40005C00UL)  /** \brief LCDCTRL����ַ */
#define ZLG118_LVD_BASE                (0x40002400UL)  /** \brief LVD����ַ */
#define ZLG118_RCC_BASE                (0x40002000UL)  /** \brief RCC����ַ */
#define ZLG118_OPA_BASE                (0x40002400UL)  /** \brief OPA����ַ */
#define ZLG118_PCNT_BASE               (0x40005400UL)  /** \brief PCNT����ַ */
#define ZLG118_RAM_BASE                (0x40020400UL)  /** \brief RAM����ַ */
#define ZLG118_PCA_BASE                (0x40001000UL)  /** \brief PCA����ַ */
#define ZLG118_RTC_BASE                (0x40001400UL)  /** \brief RTC����ַ */
#define ZLG118_TRNG_BASE               (0x40004C00UL)  /** \brief TRNG����ַ */
#define ZLG118_VC_BASE                 (0x40002410UL)  /** \brief VC����ַ */
#define ZLG118_WDT_BASE                (0x40000F80UL)  /** \brief WDT����ַ */
#define ZLG118_BGR_BASE                (0x40002400UL)  /** \brief BGR����ַ */
#define ZLG118_SYSTICK                 (0xE000E010UL)  /** \brief SYSTICK����ַ */
/** @} */

/**
 * @} zlg118_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZLG118_REGBASE_H */

/* end of file */
