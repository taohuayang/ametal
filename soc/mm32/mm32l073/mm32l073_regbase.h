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
 * \brief MM32L073 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __MM32L073_REGBASE_H
#define __MM32L073_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup mm32l073_if_regbase
 * \copydoc mm32l073_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

/** \brief GPIO����ַ */
#define MM32L073_GPIO_BASE              (0x48000000UL)

/** \brief GPIOA����ַ */
#define MM32L073_GPIOA_BASE             (0x48000000UL)

/** \brief GPIOB����ַ */
#define MM32L073_GPIOB_BASE             (0x48000400UL)

/** \brief GPIOC����ַ */
#define MM32L073_GPIOC_BASE             (0x48000800UL)

/** \brief GPIOD����ַ */
#define MM32L073_GPIOD_BASE             (0x48000C00UL)

/** \brief �߼����ƶ�ʱ��1����ַ */
#define MM32L073_TIM1_BASE              (0x40012C00UL)

/** \brief ͨ�ö�ʱ��2����ַ */
#define MM32L073_TIM2_BASE              (0x40000000UL)

/** \brief ͨ�ö�ʱ��3����ַ */
#define MM32L073_TIM3_BASE              (0x40000400UL)

/** \brief 16λͨ�ö�ʱ��14����ַ */
#define MM32L073_TIM14_BASE             (0x40014000UL)

/** \brief 16λͨ�ö�ʱ��16����ַ */
#define MM32L073_TIM16_BASE             (0x40014400UL)

/** \brief 16λͨ�ö�ʱ��17����ַ */
#define MM32L073_TIM17_BASE             (0x40014800UL)

/** \brief SYSCFG����ַ */
#define MM32L073_SYSCFG_BASE            (0x40010000UL)

/** \brief ��Դ����PWR����ַ */
#define MM32L073_PWR_BASE               (0x40007000UL)

/** \brief ���ݿ���BKP����ַ */
#define MM32L073_BKP_BASE               (0x40002800UL)

/** \brief UART1 ����ַ */
#define MM32L073_UART1_BASE             (0x40013800UL)

/** \brief UART2 ����ַ */
#define MM32L073_UART2_BASE             (0x40004400UL)

/** \brief ADC ����ַ */
#define MM32L073_ADC_BASE               (0x40012400UL)

/** \brief CMP ����ַ */
#define MM32L073_CMP_BASE               (0x40013C00UL)

/** \brief DMA ����ַ */
#define MM32L073_DMA_BASE               (0x40020000UL)

/** \brief FLASH����������ַ */
#define MM32L073_FLASHCTR_BASE          (0x40022000UL)

/** \brief RCC����������ַ */
#define MM32L073_RCC_BASE               (0x40021000UL)

/** \brief CRS����������ַ */
#define MM32L073_CRS_BASE               (0x40006C00UL)

/** \brief SPI1����������ַ */
#define MM32L073_SPI1_BASE              (0x40013000UL)

/** \brief SPI2����������ַ */
#define MM32L073_SPI2_BASE              (0x40003800UL)

/** \brief I2C1����ַ */
#define MM32L073_I2C1_BASE              (0x40005400UL)

/** \brief IWDG����������ַ */
#define MM32L073_IWDG_BASE              (0x40003000UL)

/** \brief WWDG����������ַ */
#define MM32L073_WWDG_BASE              (0x40002C00UL)

/** \brief DBGMCU ����ַ */
#define MM32L073_DBGMCU_BASE            (0x40005400UL)

/** \brief CAN����������ַ */
#define MM32L073_CAN_BASE               (0x40006400UL)

/** \brief USB����������ַ */
#define MM32L073_USB_BASE               (0x40005C00UL)

/** \brief �ⲿ�ж�(�¼�)������EXTI����ַ */
#define MM32L073_EXTI_BASE              (0x40010400UL)

/** \brief NVIC����ַ */
#define MM32L073_NVIC_BASE              (0xE000E100UL)

/** \brief SYSTICK����ַ */
#define MM32L073_SYSTICK_BASE           (0xE000E010UL)

/** \brief FLASH����ַ */
#define MM32L073_FLASH_BASE             (0x40022000UL)

/** \brief SRAM����ַ */
#define MM32L073_SRAM_BASE              (0x20000000UL)

/** @} */

/**
 * @} mm32l073_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif /* __MM32L073_REGBASE_H */

/* end of file */
