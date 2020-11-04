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
 * \brief STM32F103RBT6 ����ӳ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-26  yrh, first implementation
 * \endinternal
 */

#ifndef __AMHW_STM32F103RBT6_PERIPH_MAP_H
#define __AMHW_STM32F103RBT6_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f103rbt6_regbase.h"
#include "hw/amhw_stm32f103rbt6_adc.h"
#include "hw/amhw_stm32f103rbt6_bkp.h"
#include "hw/amhw_stm32f103rbt6_cmp.h"
#include "hw/amhw_stm32f103rbt6_crc.h"
#include "hw/amhw_stm32f103rbt6_flash.h"
#include "hw/amhw_stm32f103rbt6_i2c.h"
#include "hw/amhw_stm32f103rbt6_rtc.h"
#include "hw/amhw_stm32f103rbt6_spi.h"
#include "hw/amhw_stm32f103rbt6_tim.h"
#include "hw/amhw_stm32f103rbt6_usart.h"
#include "hw/amhw_stm32f103rbt6_iwdg.h"
#include "hw/amhw_stm32f103rbt6_wwdg.h"
#include "hw/amhw_stm32f103rbt6_pwr.h"
#include "hw/amhw_stm32f103rbt6_exti.h"
#include "hw/amhw_stm32f103rbt6_gpio.h"
#include "hw/amhw_stm32f103rbt6_dma.h"
//#include "hw/amhw_stm32f103rbt6_usbd.h"

/**
 * \addtogroup amhw_stm32f103rbt6_if_periph_map
 * \copydoc amhw_stm32f103rbt6_periph_map.h
 * @{
 */

/**
 * \name ���趨��
 * @{
 */

/** \brief GPIO�˿�A�Ĵ�����ָ�� */
#define STM32F103RBT6_GPIOA   ((amhw_stm32f103rbt6_gpio_reg_t  *)STM32F103RBT6_GPIOA_BASE)

/** \brief GPIO�˿�B�Ĵ�����ָ�� */
#define STM32F103RBT6_GPIOB   ((amhw_stm32f103rbt6_gpio_reg_t  *)STM32F103RBT6_GPIOB_BASE)

/** \brief GPIO�˿�C�Ĵ�����ָ�� */
#define STM32F103RBT6_GPIOC   ((amhw_stm32f103rbt6_gpio_reg_t  *)STM32F103RBT6_GPIOC_BASE)

/** \brief GPIO�˿�D�Ĵ�����ָ�� */
#define STM32F103RBT6_GPIOD   ((amhw_stm32f103rbt6_gpio_reg_t  *)STM32F103RBT6_GPIOD_BASE)

/** \brief GPIO�Ĵ�����ָ�� */
#define STM32F103RBT6_GPIO    ((amhw_stm32f103rbt6_gpio_t      *)STM32F103RBT6_GPIO_BASE)

/** \brief AFIO�Ĵ�����ָ�� */
#define STM32F103RBT6_AFIO    ((amhw_stm32f103rbt6_afio_t      *)STM32F103RBT6_AFIO_BASE)

/** \brief TIM1�Ĵ�����ָ�� */
#define STM32F103RBT6_TIM1    ((amhw_stm32f103rbt6_tim_t          *)STM32F103RBT6_TIM1_BASE)

/** \brief ͨ�ö�ʱ��2�Ĵ�����ָ�� */
#define STM32F103RBT6_TIM2    ((amhw_stm32f103rbt6_tim_t          *)STM32F103RBT6_TIM2_BASE)

/** \brief ͨ�ö�ʱ��3�Ĵ�����ָ�� */
#define STM32F103RBT6_TIM3    ((amhw_stm32f103rbt6_tim_t          *)STM32F103RBT6_TIM3_BASE)

/** \brief ͨ�ö�ʱ��4�Ĵ�����ָ�� */
#define STM32F103RBT6_TIM4    ((amhw_stm32f103rbt6_tim_t          *)STM32F103RBT6_TIM4_BASE)

/** \brief RTC�Ĵ�����ָ�� */
#define STM32F103RBT6_RTC     ((amhw_stm32f103rbt6_rtc_t       *)STM32F103RBT6_RTC_BASE)

/** \brief ��Դ����PWR�Ĵ�����ָ�� */
#define STM32F103RBT6_PWR     ((amhw_stm32f103rbt6_pwr_t       *)STM32F103RBT6_PWR_BASE)

/** \brief ���ݿ���BKP�Ĵ�����ָ�� */
#define STM32F103RBT6_BKP     ((amhw_stm32f103rbt6_bkp_t       *)STM32F103RBT6_BKP_BASE)

/** \brief UART1 �Ĵ�����ָ�� */
#define STM32F103RBT6_USART1  ((amhw_stm32f103rbt6_usart_t     *)STM32F103RBT6_USART1_BASE)

/** \brief UART2 �Ĵ�����ָ�� */
#define STM32F103RBT6_USART2  ((amhw_stm32f103rbt6_usart_t     *)STM32F103RBT6_USART2_BASE)

/** \brief UART3 �Ĵ�����ָ�� */
#define STM32F103RBT6_USART3  ((amhw_stm32f103rbt6_usart_t     *)STM32F103RBT6_USART3_BASE)

/** \brief ADC1 �Ĵ�����ָ�� */
#define STM32F103RBT6_ADC1    ((amhw_stm32f103rbt6_adc_t       *)STM32F103RBT6_ADC1_BASE)

/** \brief ADC2 �Ĵ�����ָ�� */
#define STM32F103RBT6_ADC2    ((amhw_stm32f103rbt6_adc_t       *)STM32F103RBT6_ADC2_BASE)

/** \brief DMA �Ĵ�����ָ�� */
#define STM32F103RBT6_DMA     ((amhw_stm32f103rbt6_dma_t       *)STM32F103RBT6_DMA_BASE)

/** \brief RCC�������Ĵ�����ָ�� */
#define STM32F103RBT6_RCC     ((amhw_stm32f103rbt6_rcc_t       *)STM32F103RBT6_RCC_BASE)

/** \brief SPI1�������Ĵ�����ָ�� */
#define STM32F103RBT6_SPI1    ((amhw_stm32f103rbt6_spi_t       *)STM32F103RBT6_SPI1_BASE)

/** \brief SPI2�������Ĵ�����ָ�� */
#define STM32F103RBT6_SPI2    ((amhw_stm32f103rbt6_spi_t       *)STM32F103RBT6_SPI2_BASE)

/** \brief I2C1�Ĵ�����ָ�� */
#define STM32F103RBT6_I2C1    ((amhw_stm32f103rbt6_i2c_t       *)STM32F103RBT6_I2C1_BASE)

/** \brief I2C2�Ĵ�����ָ�� */
#define STM32F103RBT6_I2C2    ((amhw_stm32f103rbt6_i2c_t       *)STM32F103RBT6_I2C2_BASE)

/** \brief IWDG�������Ĵ�����ָ�� */
#define STM32F103RBT6_IWDG    ((amhw_stm32f103rbt6_iwdg_t         *)STM32F103RBT6_IWDG_BASE)

/** \brief WWDG�������Ĵ�����ָ�� */
#define STM32F103RBT6_WWDG    ((amhw_stm32f103rbt6_wwdg_t         *)STM32F103RBT6_WWDG_BASE)

/** \brief CAN�������Ĵ�����ָ�� */
#define STM32F103RBT6_CAN     ((amhw_stm32f103rbt6_can_t       *)STM32F103RBT6_CAN_BASE)

/** \brief USB�������Ĵ�����ָ�� */
#define STM32F103RBT6_USB     ((amhw_stm32f103rbt6_usb_t       *)STM32F103RBT6_USB_BASE)

/** \brief �ⲿ�ж�(�¼�)������EXTI�Ĵ�����ָ�� */
#define STM32F103RBT6_EXTI    ((amhw_stm32f103rbt6_exti_t      *)STM32F103RBT6_EXTI_BASE)

/** \brief FLASH�Ĵ�����ָ�� */
#define STM32F103RBT6_FLASH   ((amhw_stm32f103rbt6_flash_t     *)STM32F103RBT6_FLASH_BASE)

/** \brief CRC�Ĵ�����ָ�� */
#define STM32F103RBT6_CRC     (amhw_stm32f103rbt6_crc_t           *)(STM32F103RBT6_CRC_BASE)

/** \brief CMP �Ĵ�����ָ�� */
#define STM32F103RBT6_CMP     ((amhw_stm32f103rbt6_cmp_t           *)STM32F103RBT6_CMP_BASE)
/** @} */

/**
 * @} amhw_stm32f103rbt6_if_periph_map
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_STM32F103RBT6_REG_BASE_H */

/* end of file */
