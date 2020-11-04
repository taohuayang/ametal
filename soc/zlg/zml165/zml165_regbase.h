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
 * \brief ZML165 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __ZML165_REGBASE_H
#define __ZML165_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zml165_if_regbase
 * \copydoc zml165_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

/** \brief GPIO����ַ */
#define ZML165_GPIO_BASE              (0x48000000UL)

/** \brief GPIOA����ַ */
#define ZML165_GPIOA_BASE             (0x48000000UL)

/** \brief GPIOB����ַ */
#define ZML165_GPIOB_BASE             (0x48000400UL)

/** \brief GPIOC����ַ */
#define ZML165_GPIOC_BASE             (0x48000800UL)

/** \brief GPIOD����ַ */
#define ZML165_GPIOD_BASE             (0x48000C00UL)

/** \brief �߼����ƶ�ʱ��1����ַ */
#define ZML165_TIM1_BASE              (0x40012C00UL)

/** \brief ͨ�ö�ʱ��2����ַ */
#define ZML165_TIM2_BASE              (0x40000000UL)

/** \brief ͨ�ö�ʱ��3����ַ */
#define ZML165_TIM3_BASE              (0x40000400UL)

/** \brief 16λͨ�ö�ʱ��14����ַ */
#define ZML165_TIM14_BASE             (0x40014000UL)

/** \brief 16λͨ�ö�ʱ��16����ַ */
#define ZML165_TIM16_BASE             (0x40014400UL)

/** \brief 16λͨ�ö�ʱ��17����ַ */
#define ZML165_TIM17_BASE             (0x40014800UL)

/** \brief SYSCFG����ַ */
#define ZML165_SYSCFG_BASE            (0x40010000UL)

/** \brief ��Դ����PWR����ַ */
#define ZML165_PWR_BASE               (0x40007000UL)

/** \brief ���ݿ���BKP����ַ */
#define ZML165_BKP_BASE               (0x40002800UL)

/** \brief UART1 ����ַ */
#define ZML165_UART1_BASE             (0x40013800UL)

/** \brief UART2 ����ַ */
#define ZML165_UART2_BASE             (0x40004400UL)

/** \brief ADC ����ַ */
#define ZML165_ADC_BASE               (0x40012400UL)

/** \brief CMP ����ַ */
#define ZML165_CMP_BASE               (0x40013C00UL)

/** \brief DMA ����ַ */
#define ZML165_DMA_BASE               (0x40020000UL)

/** \brief FLASH����������ַ */
#define ZML165_FLASHCTR_BASE          (0x40022000UL)

/** \brief RCC����������ַ */
#define ZML165_RCC_BASE               (0x40021000UL)

/** \brief CRS����������ַ */
#define ZML165_CRS_BASE               (0x40006C00UL)

/** \brief SPI1����������ַ */
#define ZML165_SPI1_BASE              (0x40013000UL)

/** \brief SPI2����������ַ */
#define ZML165_SPI2_BASE              (0x40003800UL)

/** \brief I2C1����ַ */
#define ZML165_I2C1_BASE              (0x40005400UL)

/** \brief IWDG����������ַ */
#define ZML165_IWDG_BASE              (0x40003000UL)

/** \brief WWDG����������ַ */
#define ZML165_WWDG_BASE              (0x40002C00UL)

/** \brief DBGMCU ����ַ */
#define ZML165_DBGMCU_BASE            (0x40005400UL)

/** \brief CAN����������ַ */
#define ZML165_CAN_BASE               (0x40006400UL)

/** \brief USB����������ַ */
#define ZML165_USB_BASE               (0x40005C00UL)

/** \brief �ⲿ�ж�(�¼�)������EXTI����ַ */
#define ZML165_EXTI_BASE              (0x40010400UL)

/** \brief NVIC����ַ */
#define ZML165_NVIC_BASE              (0xE000E100UL)

/** \brief SYSTICK����ַ */
#define ZML165_SYSTICK_BASE           (0xE000E010UL)

/** \brief FLASH����ַ */
#define ZML165_FLASH_BASE             (0x40022000UL)

/** \brief SRAM����ַ */
#define ZML165_SRAM_BASE              (0x20000000UL)

/** @} */

/**
 * @} zml165_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZML165_REGBASE_H */

/* end of file */
