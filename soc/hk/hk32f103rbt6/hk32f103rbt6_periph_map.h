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
 * \brief HK32F103RBT6 ����ӳ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-26  yrh, first implementation
 * \endinternal
 */

#ifndef __AMHW_HK32F103RBT6_PERIPH_MAP_H
#define __AMHW_HK32F103RBT6_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hk32f103rbt6_regbase.h"
#include "hw/amhw_hk32f103rbt6_adc.h"
#include "hw/amhw_hk32f103rbt6_bkp.h"
#include "hw/amhw_hk32f103rbt6_crc.h"
#include "hw/amhw_hk32f103rbt6_flash.h"
#include "hw/amhw_hk32f103rbt6_i2c.h"
#include "hw/amhw_hk32f103rbt6_rtc.h"
#include "hw/amhw_hk32f103rbt6_spi.h"
#include "hw/amhw_hk32f103rbt6_tim.h"
#include "hw/amhw_hk32f103rbt6_usart.h"
#include "hw/amhw_hk32f103rbt6_iwdg.h"
#include "hw/amhw_hk32f103rbt6_wwdg.h"
#include "hw/amhw_hk32f103rbt6_pwr.h"
#include "hw/amhw_hk32f103rbt6_exti.h"
#include "hw/amhw_hk32f103rbt6_gpio.h"
#include "hw/amhw_hk32f103rbt6_dma.h"

/**
 * \addtogroup amhw_hk32f103rbt6_if_periph_map
 * \copydoc amhw_hk32f103rbt6_periph_map.h
 * @{
 */

/**
 * \name ���趨��
 * @{
 */

/** \brief GPIO�˿�A�Ĵ�����ָ�� */
#define HK32F103RBT6_GPIOA   ((amhw_hk32f103rbt6_gpio_reg_t  *)HK32F103RBT6_GPIOA_BASE)

/** \brief GPIO�˿�B�Ĵ�����ָ�� */
#define HK32F103RBT6_GPIOB   ((amhw_hk32f103rbt6_gpio_reg_t  *)HK32F103RBT6_GPIOB_BASE)

/** \brief GPIO�˿�C�Ĵ�����ָ�� */
#define HK32F103RBT6_GPIOC   ((amhw_hk32f103rbt6_gpio_reg_t  *)HK32F103RBT6_GPIOC_BASE)

/** \brief GPIO�˿�D�Ĵ�����ָ�� */
#define HK32F103RBT6_GPIOD   ((amhw_hk32f103rbt6_gpio_reg_t  *)HK32F103RBT6_GPIOD_BASE)

/** \brief GPIO�Ĵ�����ָ�� */
#define HK32F103RBT6_GPIO    ((amhw_hk32f103rbt6_gpio_t      *)HK32F103RBT6_GPIO_BASE)

/** \brief AFIO�Ĵ�����ָ�� */
#define HK32F103RBT6_AFIO    ((amhw_hk32f103rbt6_afio_t      *)HK32F103RBT6_AFIO_BASE)

/** \brief TIM1�Ĵ�����ָ�� */
#define HK32F103RBT6_TIM1    ((amhw_hk32f103rbt6_tim_t          *)HK32F103RBT6_TIM1_BASE)

/** \brief ͨ�ö�ʱ��2�Ĵ�����ָ�� */
#define HK32F103RBT6_TIM2    ((amhw_hk32f103rbt6_tim_t          *)HK32F103RBT6_TIM2_BASE)

/** \brief ͨ�ö�ʱ��3�Ĵ�����ָ�� */
#define HK32F103RBT6_TIM3    ((amhw_hk32f103rbt6_tim_t          *)HK32F103RBT6_TIM3_BASE)

/** \brief ͨ�ö�ʱ��4�Ĵ�����ָ�� */
#define HK32F103RBT6_TIM4    ((amhw_hk32f103rbt6_tim_t          *)HK32F103RBT6_TIM4_BASE)

/** \brief RTC�Ĵ�����ָ�� */
#define HK32F103RBT6_RTC     ((amhw_hk32f103rbt6_rtc_t       *)HK32F103RBT6_RTC_BASE)

/** \brief ��Դ����PWR�Ĵ�����ָ�� */
#define HK32F103RBT6_PWR     ((amhw_hk32f103rbt6_pwr_t       *)HK32F103RBT6_PWR_BASE)

/** \brief ���ݿ���BKP�Ĵ�����ָ�� */
#define HK32F103RBT6_BKP     ((amhw_hk32f103rbt6_bkp_t       *)HK32F103RBT6_BKP_BASE)

/** \brief UART1 �Ĵ�����ָ�� */
#define HK32F103RBT6_USART1  ((amhw_hk32f103rbt6_usart_t     *)HK32F103RBT6_USART1_BASE)

/** \brief UART2 �Ĵ�����ָ�� */
#define HK32F103RBT6_USART2  ((amhw_hk32f103rbt6_usart_t     *)HK32F103RBT6_USART2_BASE)

/** \brief UART3 �Ĵ�����ָ�� */
#define HK32F103RBT6_USART3  ((amhw_hk32f103rbt6_usart_t     *)HK32F103RBT6_USART3_BASE)

/** \brief ADC1 �Ĵ�����ָ�� */
#define HK32F103RBT6_ADC1    ((amhw_hk32f103rbt6_adc_t       *)HK32F103RBT6_ADC1_BASE)

/** \brief ADC2 �Ĵ�����ָ�� */
#define HK32F103RBT6_ADC2    ((amhw_hk32f103rbt6_adc_t       *)HK32F103RBT6_ADC2_BASE)

/** \brief DMA �Ĵ�����ָ�� */
#define HK32F103RBT6_DMA     ((amhw_hk32f103rbt6_dma_t       *)HK32F103RBT6_DMA_BASE)

/** \brief RCC�������Ĵ�����ָ�� */
#define HK32F103RBT6_RCC     ((amhw_hk32f103rbt6_rcc_t       *)HK32F103RBT6_RCC_BASE)

/** \brief SPI1�������Ĵ�����ָ�� */
#define HK32F103RBT6_SPI1    ((amhw_hk32f103rbt6_spi_t       *)HK32F103RBT6_SPI1_BASE)

/** \brief SPI2�������Ĵ�����ָ�� */
#define HK32F103RBT6_SPI2    ((amhw_hk32f103rbt6_spi_t       *)HK32F103RBT6_SPI2_BASE)

/** \brief I2C1�Ĵ�����ָ�� */
#define HK32F103RBT6_I2C1    ((amhw_hk32f103rbt6_i2c_t       *)HK32F103RBT6_I2C1_BASE)

/** \brief I2C2�Ĵ�����ָ�� */
#define HK32F103RBT6_I2C2    ((amhw_hk32f103rbt6_i2c_t       *)HK32F103RBT6_I2C2_BASE)

/** \brief IWDG�������Ĵ�����ָ�� */
#define HK32F103RBT6_IWDG    ((amhw_hk32f103rbt6_iwdg_t         *)HK32F103RBT6_IWDG_BASE)

/** \brief WWDG�������Ĵ�����ָ�� */
#define HK32F103RBT6_WWDG    ((amhw_hk32f103rbt6_wwdg_t         *)HK32F103RBT6_WWDG_BASE)

/** \brief CAN�������Ĵ�����ָ�� */
#define HK32F103RBT6_CAN     ((amhw_hk32f103rbt6_can_t       *)HK32F103RBT6_CAN_BASE)

/** \brief USB�������Ĵ�����ָ�� */
#define HK32F103RBT6_USB     ((amhw_hk32f103rbt6_usb_t       *)HK32F103RBT6_USB_BASE)

/** \brief �ⲿ�ж�(�¼�)������EXTI�Ĵ�����ָ�� */
#define HK32F103RBT6_EXTI    ((amhw_hk32f103rbt6_exti_t      *)HK32F103RBT6_EXTI_BASE)

/** \brief FLASH�Ĵ�����ָ�� */
#define HK32F103RBT6_FLASH   ((amhw_hk32f103rbt6_flash_t     *)HK32F103RBT6_FLASH_BASE)

/** \brief CRC�Ĵ�����ָ�� */
#define HK32F103RBT6_CRC     (amhw_hk32f103rbt6_crc_t           *)(HK32F103RBT6_CRC_BASE)

/** \brief CMP �Ĵ�����ָ�� */
#define HK32F103RBT6_CMP     ((amhw_hk32f103rbt6_cmp_t           *)HK32F103RBT6_CMP_BASE)
/** @} */

/**
 * @} amhw_hk32f103rbt6_if_periph_map
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HK32F103RBT6_REG_BASE_H */

/* end of file */
