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
 * \brief ZLG116 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __ZLG116_REGBASE_H
#define __ZLG116_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zlg116_if_regbase
 * \copydoc zlg116_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

/** \brief GPIO����ַ */
#define ZLG116_GPIO_BASE              (0x48000000UL)

/** \brief GPIOA����ַ */
#define ZLG116_GPIOA_BASE             (0x48000000UL)

/** \brief GPIOB����ַ */
#define ZLG116_GPIOB_BASE             (0x48000400UL)

/** \brief GPIOC����ַ */
#define ZLG116_GPIOC_BASE             (0x48000800UL)

/** \brief GPIOD����ַ */
#define ZLG116_GPIOD_BASE             (0x48000C00UL)

/** \brief �߼����ƶ�ʱ��1����ַ */
#define ZLG116_TIM1_BASE              (0x40012C00UL)

/** \brief ͨ�ö�ʱ��2����ַ */
#define ZLG116_TIM2_BASE              (0x40000000UL)

/** \brief ͨ�ö�ʱ��3����ַ */
#define ZLG116_TIM3_BASE              (0x40000400UL)

/** \brief 16λͨ�ö�ʱ��14����ַ */
#define ZLG116_TIM14_BASE             (0x40014000UL)

/** \brief 16λͨ�ö�ʱ��16����ַ */
#define ZLG116_TIM16_BASE             (0x40014400UL)

/** \brief 16λͨ�ö�ʱ��17����ַ */
#define ZLG116_TIM17_BASE             (0x40014800UL)

/** \brief SYSCFG����ַ */
#define ZLG116_SYSCFG_BASE            (0x40010000UL)

/** \brief ��Դ����PWR����ַ */
#define ZLG116_PWR_BASE               (0x40007000UL)

/** \brief ���ݿ���BKP����ַ */
#define ZLG116_BKP_BASE               (0x40002800UL)

/** \brief UART1 ����ַ */
#define ZLG116_UART1_BASE             (0x40013800UL)

/** \brief UART2 ����ַ */
#define ZLG116_UART2_BASE             (0x40004400UL)

/** \brief ADC ����ַ */
#define ZLG116_ADC_BASE               (0x40012400UL)

/** \brief CMP ����ַ */
#define ZLG116_CMP_BASE               (0x40013C00UL)

/** \brief DMA ����ַ */
#define ZLG116_DMA_BASE               (0x40020000UL)

/** \brief FLASH����������ַ */
#define ZLG116_FLASHCTR_BASE          (0x40022000UL)

/** \brief RCC����������ַ */
#define ZLG116_RCC_BASE               (0x40021000UL)

/** \brief CRS����������ַ */
#define ZLG116_CRS_BASE               (0x40006C00UL)

/** \brief SPI1����������ַ */
#define ZLG116_SPI1_BASE              (0x40013000UL)

/** \brief SPI2����������ַ */
#define ZLG116_SPI2_BASE              (0x40003800UL)

/** \brief I2C1����ַ */
#define ZLG116_I2C1_BASE              (0x40005400UL)

/** \brief IWDG����������ַ */
#define ZLG116_IWDG_BASE              (0x40003000UL)

/** \brief WWDG����������ַ */
#define ZLG116_WWDG_BASE              (0x40002C00UL)

/** \brief DBGMCU ����ַ */
#define ZLG116_DBGMCU_BASE            (0x40005400UL)

/** \brief CAN����������ַ */
#define ZLG116_CAN_BASE               (0x40006400UL)

/** \brief USB����������ַ */
#define ZLG116_USB_BASE               (0x40005C00UL)

/** \brief �ⲿ�ж�(�¼�)������EXTI����ַ */
#define ZLG116_EXTI_BASE              (0x40010400UL)

/** \brief NVIC����ַ */
#define ZLG116_NVIC_BASE              (0xE000E100UL)

/** \brief SYSTICK����ַ */
#define ZLG116_SYSTICK_BASE           (0xE000E010UL)

/** \brief FLASH����ַ */
#define ZLG116_FLASH_BASE             (0x40022000UL)

/** \brief SRAM����ַ */
#define ZLG116_SRAM_BASE              (0x20000000UL)

/** \brief DEVICE����ַ */
#define ZLG116_DEVICE_BASE            (0x1FFFF7E0UL)
/** @} */

/**
 * @} zlg116_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG116_REGBASE_H */

/* end of file */
