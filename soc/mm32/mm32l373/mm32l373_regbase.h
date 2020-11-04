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
 * \brief MM32L373 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __MM32L373_REGBASE_H
#define __MM32L373_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup mm32l373_if_regbase
 * \copydoc mm32l373_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

/** \brief GPIO����ַ */
#define MM32L373_GPIO_BASE              (0x40010800UL)

/** \brief GPIOA����ַ */
#define MM32L373_GPIOA_BASE             (0x40010800UL)

/** \brief GPIOB����ַ */
#define MM32L373_GPIOB_BASE             (0x40010C00UL)

/** \brief GPIOC����ַ */
#define MM32L373_GPIOC_BASE             (0x40011000UL)

/** \brief GPIOD����ַ */
#define MM32L373_GPIOD_BASE             (0x40011400UL)

/** \brief GPIOE����ַ */
#define MM32L373_GPIOE_BASE             (0x40011800UL)

/** \brief AFIOA����ַ */
#define MM32L373_AFIO_BASE              (0x40010000UL)

/** \brief �߼����ƶ�ʱ��1����ַ */
#define MM32L373_TIM1_BASE              (0x40012C00UL)

/** \brief ͨ�ö�ʱ��2����ַ */
#define MM32L373_TIM2_BASE              (0x40000000UL)

/** \brief ͨ�ö�ʱ��3����ַ */
#define MM32L373_TIM3_BASE              (0x40000400UL)

/** \brief ͨ�ö�ʱ��4����ַ */
#define MM32L373_TIM4_BASE              (0x40000800UL)

/** \brief RTC����ַ */
#define MM32L373_RTC_BASE               (0x40002800UL)

/** \brief ��Դ����PWR����ַ */
#define MM32L373_PWR_BASE               (0x40007000UL)

/** \brief ���ݿ���BKP����ַ */
#define MM32L373_BKP_BASE               (0x40006C00UL)

/** \brief UART1 ����ַ */
#define MM32L373_UART1_BASE             (0x40013800UL)

/** \brief UART2 ����ַ */
#define MM32L373_UART2_BASE             (0x40004400UL)

/** \brief UART3 ����ַ */
#define MM32L373_UART3_BASE             (0x40004800UL)

/** \brief ADC1 ����ַ */
#define MM32L373_ADC1_BASE              (0x40012400UL)

/** \brief ADC2 ����ַ */
#define MM32L373_ADC2_BASE              (0x40012800UL)

/** \brief DAC ����ַ */
#define MM32L373_DAC_BASE               (0x40007400UL)

/** \brief DMA ����ַ */
#define MM32L373_DMA_BASE               (0x40020000UL)

/** \brief RCC����������ַ */
#define MM32L373_RCC_BASE               (0x40021000UL)

/** \brief SPI1����������ַ */
#define MM32L373_SPI1_BASE              (0x40013000UL)

/** \brief SPI2����������ַ */
#define MM32L373_SPI2_BASE              (0x40003800UL)

/** \brief I2C1����ַ */
#define MM32L373_I2C1_BASE              (0x40005400UL)

/** \brief I2C2����ַ */
#define MM32L373_I2C2_BASE              (0x40005800UL)

/** \brief IWDG����������ַ */
#define MM32L373_IWDG_BASE              (0x40003000UL)

/** \brief WWDG����������ַ */
#define MM32L373_WWDG_BASE              (0x40002C00UL)

/** \brief CAN����������ַ */
#define MM32L373_CAN_BASE               (0x40006400UL)

/** \brief USB����������ַ */
#define MM32L373_USB_BASE               (0x40005C00UL)

/** \brief �ⲿ�ж�(�¼�)������EXTI����ַ */
#define MM32L373_EXTI_BASE              (0x40010400UL)

/** \brief FLASH����ַ */
#define MM32L373_FLASH_BASE             (0x40022000UL)

/** \brief SRAM����ַ */
#define MM32L373_SRAM_BASE              (0x20000000UL)

/** \brief FLASH����ַ */
#define MM32L373_FLASH_UID_BASE         (0x1FFFF7E8UL)

/** \brief CRC����ַ */
#define MM32L373_CRC_BASE               (0x40023000UL)

/** \brief SYSTICK����ַ */
#define MM32L373_SYSTICK                (0xE000E010UL)

/** @} */

/**
 * @} mm32l373_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __MM32L373_REGBASE_H */

/* end of file */
