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
 * \brief MM32L373 ����ӳ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AMHW_MM32L373_PERIPH_MAP_H
#define __AMHW_MM32L373_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mm32l373_regbase.h"

#include "hw/amhw_mm32_adc.h"
#include "hw/amhw_mm32_bkp.h"
#include "hw/amhw_mm32_flash.h"
#include "hw/amhw_mm32_i2c.h"
#include "hw/amhw_mm32_spi.h"
#include "hw/amhw_mm32_tim.h"
#include "hw/amhw_mm32_iwdg.h"
#include "hw/amhw_mm32_wwdg.h"
#include "hw/amhw_mm32_pwr.h"
#include "hw/amhw_mm32_exti.h"
#include "hw/amhw_mm32_syscfg.h"
#include "hw/amhw_mm32_gpio.h"
#include "hw/amhw_mm32_dma.h"
#include "hw/amhw_mm32_crc.h"
#include "hw/amhw_mm32_dac.h"
#include "hw/amhw_mm32_uart.h"
#include "hw/amhw_mm32_cmp.h"

/**
 * \addtogroup amhw_mm32l373_if_periph_map
 * \copydoc amhw_mm32l373_periph_map.h
 * @{
 */

/**
 * \name ���趨��
 * @{
 */

/** \brief GPIO�˿�A�Ĵ�����ָ�� */
#define MM32L373_GPIOA   ((amhw_mm32l373_gpio_reg_t  *)MM32L373_GPIOA_BASE)

/** \brief GPIO�˿�B�Ĵ�����ָ�� */
#define MM32L373_GPIOB   ((amhw_mm32l373_gpio_reg_t  *)MM32L373_GPIOB_BASE)

/** \brief GPIO�˿�C�Ĵ�����ָ�� */
#define MM32L373_GPIOC   ((amhw_mm32l373_gpio_reg_t  *)MM32L373_GPIOC_BASE)

/** \brief GPIO�˿�D�Ĵ�����ָ�� */
#define MM32L373_GPIOD   ((amhw_mm32l373_gpio_reg_t  *)MM32L373_GPIOD_BASE)

/** \brief GPIO�˿�E�Ĵ�����ָ�� */
#define MM32L373_GPIOE   ((amhw_mm32l373_gpio_reg_t  *)MM32L373_GPIOE_BASE)

/** \brief GPIO�Ĵ�����ָ�� */
#define MM32L373_GPIO    ((amhw_mm32l373_gpio_t      *)MM32L373_GPIO_BASE)

/** \brief AFIO�Ĵ�����ָ�� */
#define MM32L373_AFIO    ((amhw_mm32l373_afio_t      *)MM32L373_AFIO_BASE)

/** \brief TIM1�Ĵ�����ָ�� */
#define MM32L373_TIM1    ((amhw_mm32_tim_t          *)MM32L373_TIM1_BASE)

/** \brief ͨ�ö�ʱ��2�Ĵ�����ָ�� */
#define MM32L373_TIM2    ((amhw_mm32_tim_t          *)MM32L373_TIM2_BASE)

/** \brief ͨ�ö�ʱ��3�Ĵ�����ָ�� */
#define MM32L373_TIM3    ((amhw_mm32_tim_t          *)MM32L373_TIM3_BASE)

/** \brief ͨ�ö�ʱ��4�Ĵ�����ָ�� */
#define MM32L373_TIM4    ((amhw_mm32_tim_t          *)MM32L373_TIM4_BASE)

/** \brief RTC�Ĵ�����ָ�� */
#define MM32L373_RTC     ((amhw_mm32l373_rtc_t       *)MM32L373_RTC_BASE)

/** \brief ��Դ����PWR�Ĵ�����ָ�� */
#define MM32L373_PWR     ((amhw_mm32_pwr_t          *)MM32L373_PWR_BASE)

/** \brief ���ݿ���BKP�Ĵ�����ָ�� */
#define MM32L373_BKP     ((amhw_mm32l373_bkp_t       *)MM32L373_BKP_BASE)

/** \brief UART1 �Ĵ�����ָ�� */
#define MM32L373_UART1   ((amhw_mm32_uart_t         *)MM32L373_UART1_BASE)

/** \brief UART2 �Ĵ�����ָ�� */
#define MM32L373_UART2   ((amhw_mm32_uart_t         *)MM32L373_UART2_BASE)

/** \brief UART3 �Ĵ�����ָ�� */
#define MM32L373_UART3   ((amhw_mm32_uart_t         *)MM32L373_UART3_BASE)

/** \brief ADC1 �Ĵ�����ָ�� */
#define MM32L373_ADC1    ((amhw_mm32_adc_t          *)MM32L373_ADC1_BASE)

/** \brief ADC2 �Ĵ�����ָ�� */
#define MM32L373_ADC2    ((amhw_mm32_adc_t          *)MM32L373_ADC2_BASE)

/** \brief DAC �Ĵ�����ָ�� */
#define MM32L373_DAC     ((amhw_mm32_dac_t          *)MM32L373_DAC_BASE)

/** \brief DMA �Ĵ�����ָ�� */
#define MM32L373_DMA     ((amhw_mm32l373_dma_t       *)MM32L373_DMA_BASE)

/** \brief RCC�������Ĵ�����ָ�� */
#define MM32L373_RCC     ((amhw_mm32l373_rcc_t       *)MM32L373_RCC_BASE)

/** \brief SPI1�������Ĵ�����ָ�� */
#define MM32L373_SPI1    ((amhw_mm32_spi_t          *)MM32L373_SPI1_BASE)

/** \brief SPI2�������Ĵ�����ָ�� */
#define MM32L373_SPI2    ((amhw_mm32_spi_t          *)MM32L373_SPI2_BASE)

/** \brief I2C1�Ĵ�����ָ�� */
#define MM32L373_I2C1    ((amhw_mm32_i2c_t          *)MM32L373_I2C1_BASE)

/** \brief I2C2�Ĵ�����ָ�� */
#define MM32L373_I2C2    ((amhw_mm32_i2c_t          *)MM32L373_I2C2_BASE)

/** \brief IWDG�������Ĵ�����ָ�� */
#define MM32L373_IWDG    ((amhw_mm32_iwdg_t         *)MM32L373_IWDG_BASE)

/** \brief WWDG�������Ĵ�����ָ�� */
#define MM32L373_WWDG    ((amhw_mm32_wwdg_t         *)MM32L373_WWDG_BASE)

/** \brief CAN�������Ĵ�����ָ�� */
#define MM32L373_CAN     ((amhw_mm32l373_can_t       *)MM32L373_CAN_BASE)

/** \brief USB�������Ĵ�����ָ�� */
#define MM32L373_USB     ((amhw_mm32l373_usb_t       *)MM32L373_USB_BASE)

/** \brief �ⲿ�ж�(�¼�)������EXTI�Ĵ�����ָ�� */
#define MM32L373_EXTI    ((amhw_mm32l373_exti_t      *)MM32L373_EXTI_BASE)

/** \brief FLASH�Ĵ�����ָ�� */
#define MM32L373_FLASH   ((amhw_mm32_flash_t        *)MM32L373_FLASH_BASE)

/** \brief CRC�Ĵ�����ָ�� */
#define MM32L373_CRC     (amhw_mm32_crc_t           *)(MM32L373_CRC_BASE)

/** @} */

/**
 * @} amhw_mm32l373_if_periph_map
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MM32L373_REG_BASE_H */

/* end of file */
