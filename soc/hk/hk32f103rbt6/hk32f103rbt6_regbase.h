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
 * \brief HK32F103RBT6 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-26  yrh, first implementation
 * \endinternal
 */

#ifndef __HK32F103RBT6_REGBASE_H
#define __HK32F103RBT6_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup hk32f103rbt6_if_regbase
 * \copydoc hk32f103rbt6_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

/** \brief GPIO����ַ */
#define HK32F103RBT6_GPIO_BASE              (0x40010800UL)

/** \brief GPIOA����ַ */
#define HK32F103RBT6_GPIOA_BASE             (0x40010800UL)

/** \brief GPIOB����ַ */
#define HK32F103RBT6_GPIOB_BASE             (0x40010C00UL)

/** \brief GPIOC����ַ */
#define HK32F103RBT6_GPIOC_BASE             (0x40011000UL)

/** \brief GPIOD����ַ */
#define HK32F103RBT6_GPIOD_BASE             (0x40011400UL)

/** \brief AFIOA����ַ */
#define HK32F103RBT6_AFIO_BASE              (0x40010000UL)

/** \brief �߼����ƶ�ʱ��1����ַ */
#define HK32F103RBT6_TIM1_BASE              (0x40012C00UL)

/** \brief ͨ�ö�ʱ��2����ַ */
#define HK32F103RBT6_TIM2_BASE              (0x40000000UL)

/** \brief ͨ�ö�ʱ��3����ַ */
#define HK32F103RBT6_TIM3_BASE              (0x40000400UL)

/** \brief ͨ�ö�ʱ��4����ַ */
#define HK32F103RBT6_TIM4_BASE              (0x40000800UL)

/** \brief RTC����ַ */
#define HK32F103RBT6_RTC_BASE               (0x40002800UL)

/** \brief ��Դ����PWR����ַ */
#define HK32F103RBT6_PWR_BASE               (0x40007000UL)

/** \brief ���ݿ���BKP����ַ */
#define HK32F103RBT6_BKP_BASE               (0x40006C00UL)

/** \brief �Ƚ�������ַ */
#define HK32F103RBT6_CMP_BASE               (0x40013C00UL)

/** \brief UART1 ����ַ */
#define HK32F103RBT6_USART1_BASE            (0x40013800UL)

/** \brief UART2 ����ַ */
#define HK32F103RBT6_USART2_BASE            (0x40004400UL)

/** \brief UART3 ����ַ */
#define HK32F103RBT6_USART3_BASE            (0x40004800UL)

/** \brief ADC1 ����ַ */
#define HK32F103RBT6_ADC1_BASE              (0x40012400UL)

/** \brief ADC2 ����ַ */
#define HK32F103RBT6_ADC2_BASE              (0x40012800UL)

/** \brief DAC ����ַ */
#define HK32F103RBT6_DAC_BASE               (0x40007400UL)

/** \brief DMA ����ַ */
#define HK32F103RBT6_DMA_BASE               (0x40020000UL)

/** \brief RCC����������ַ */
#define HK32F103RBT6_RCC_BASE               (0x40021000UL)

/** \brief SPI1����������ַ */
#define HK32F103RBT6_SPI1_BASE              (0x40013000UL)

/** \brief SPI2����������ַ */
#define HK32F103RBT6_SPI2_BASE              (0x40003800UL)

/** \brief I2C1����ַ */
#define HK32F103RBT6_I2C1_BASE              (0x40005400UL)

/** \brief I2C2����ַ */
#define HK32F103RBT6_I2C2_BASE              (0x40005800UL)

/** \brief IWDG����������ַ */
#define HK32F103RBT6_IWDG_BASE              (0x40003000UL)

/** \brief WWDG����������ַ */
#define HK32F103RBT6_WWDG_BASE              (0x40002C00UL)

/** \brief CAN����������ַ */
#define HK32F103RBT6_CAN_BASE               (0x40006400UL)

/** \brief USB����������ַ */
#define HK32F103RBT6_USB_BASE               (0x40005C00UL)

/** \brief �ⲿ�ж�(�¼�)������EXTI����ַ */
#define HK32F103RBT6_EXTI_BASE              (0x40010400UL)

/** \brief FLASH����ַ */
#define HK32F103RBT6_FLASH_BASE             (0x40022000UL)

/** \brief SRAM����ַ */
#define HK32F103RBT6_SRAM_BASE              (0x20000000UL)

/** \brief FLASH����ַ */
#define HK32F103RBT6_FLASH_UID_BASE         (0x1FFFF7E8UL)

/** \brief CRC����ַ */
#define HK32F103RBT6_CRC_BASE               (0x40023000UL)

/** \brief SYSTICK����ַ */
#define HK32F103RBT6_SYSTICK                (0xE000E010UL)

/** @} */

/**
 * @} hk32f103rbt6_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __HK32F103RBT6_REGBASE_H */

/* end of file */
