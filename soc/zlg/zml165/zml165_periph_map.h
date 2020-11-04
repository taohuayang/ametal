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
 * \brief ZML165 ����ӳ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __ZML165_PERIPH_MAP_H
#define __ZML165_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zml165_regbase.h"

#include "hw/amhw_zlg_adc.h"
#include "hw/amhw_zlg_bkp.h"
#include "hw/amhw_zlg_cmp.h"
#include "hw/amhw_zlg_crc.h"
#include "hw/amhw_zlg_dac.h"
#include "hw/amhw_zlg_flash.h"
#include "hw/amhw_zlg_i2c.h"
#include "hw/amhw_zlg_spi.h"
#include "hw/amhw_zlg_tim.h"
#include "hw/amhw_zlg_uart.h"
#include "hw/amhw_zlg_iwdg.h"
#include "hw/amhw_zlg_wwdg.h"
#include "hw/amhw_zlg_pwr.h"
#include "hw/amhw_zlg_exti.h"
#include "hw/amhw_zlg_syscfg.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zlg_dma.h"

#include "hw/amhw_zml165_rcc.h"


/**
 * \addtogroup zml165_if_periph_map
 * \copydoc zml165_periph_map.h
 * @{
 */

/**
 * \name ���趨��
 * @{
 */

/** \brief ��Դ����Ԫ(PWR)�Ĵ�����ָ�� */
#define ZML165_PWR     ((amhw_zlg_pwr_t           *)ZML165_PWR_BASE)

/** \brief ��������(BKP)�Ĵ�����ָ�� */
#define ZML165_BKP     ((amhw_zlg_bkp_t           *)ZML165_BKP_BASE)

/** \brief ϵͳ����(SYSCFG)�Ĵ�����ָ�� */
#define ZML165_SYSCFG  ((amhw_zlg_syscfg_t        *)ZML165_SYSCFG_BASE)

/** \brief GPIO�˿�A�Ĵ�����ָ�� */
#define ZML165_GPIOA   ((amhw_zlg_gpio_t          *)ZML165_GPIOA_BASE)

/** \brief GPIO�˿�B�Ĵ�����ָ�� */
#define ZML165_GPIOB   ((amhw_zlg_gpio_t          *)ZML165_GPIOB_BASE)

/** \brief GPIO�˿�C�Ĵ�����ָ�� */
#define ZML165_GPIOC   ((amhw_zlg_gpio_t          *)ZML165_GPIOC_BASE)

/** \brief GPIO�˿�D�Ĵ�����ָ�� */
#define ZML165_GPIOD   ((amhw_zlg_gpio_t          *)ZML165_GPIOD_BASE)

/** \brief GPIO�Ĵ�����ָ�� */
#define ZML165_GPIO    ((amhw_zlg_gpio_t          *)ZML165_GPIO_BASE)

/** \brief 16λ�߼���ʱ��1�Ĵ���ָ�� */
#define ZML165_TIM1    ((amhw_zlg_tim_t           *)ZML165_TIM1_BASE)

/** \brief 16λͨ�ö�ʱ��14�Ĵ���ָ�� */
#define ZML165_TIM14   ((amhw_zlg_tim_t           *)ZML165_TIM14_BASE)

/** \brief 16λͨ�ö�ʱ��16�Ĵ���ָ�� */
#define ZML165_TIM16   ((amhw_zlg_tim_t           *)ZML165_TIM16_BASE)

/** \brief 16λͨ�ö�ʱ��17�Ĵ���ָ�� */
#define ZML165_TIM17   ((amhw_zlg_tim_t           *)ZML165_TIM17_BASE)

/** \brief 16λͨ�ö�ʱ��2�Ĵ���ָ�� */
#define ZML165_TIM2    ((amhw_zlg_tim_t           *)ZML165_TIM2_BASE)

/** \brief 16λͨ�ö�ʱ��3�Ĵ���ָ�� */
#define ZML165_TIM3    ((amhw_zlg_tim_t           *)ZML165_TIM3_BASE)

/** \brief I2C���߿�����(I2C0)�Ĵ�����ָ�� */
#define ZML165_I2C     ((amhw_zlg_i2c_t           *)ZML165_I2C1_BASE )

/** \brief �������Ź�(IWDG)�Ĵ�����ָ�� */
#define ZML165_IWDG    ((amhw_zlg_iwdg_t          *)ZML165_IWDG_BASE)

/** \brief ���ڿ��Ź�(WWDG)�Ĵ�����ָ�� */
#define ZML165_WWDG    ((amhw_zlg_wwdg_t          *)ZML165_WWDG_BASE)

/** \brief ����(UART2)�Ĵ�����ָ�� */
#define ZML165_UART2   ((amhw_zlg_uart_t          *)ZML165_UART2_BASE)

/** \brief ����(UART1)�Ĵ�����ָ�� */
#define ZML165_UART1   ((amhw_zlg_uart_t          *)ZML165_UART1_BASE)

/** \brief ģ��ת��(ADC)�Ĵ�����ָ�� */
#define ZML165_ADC     ((amhw_zlg_adc_t           *)ZML165_ADC_BASE)

/** \brief SPI1 �Ĵ�����ָ�� */
#define ZML165_SPI1    ((amhw_zlg_spi_t           *)ZML165_SPI1_BASE)

/** \brief SPI2 �Ĵ�����ָ�� */
#define ZML165_SPI2    ((amhw_zlg_spi_t           *)ZML165_SPI2_BASE)

/** \brief DMA ������(DMA)�Ĵ�����ָ�� */
#define ZML165_DMA     ((amhw_zlg_dma_t           *)ZML165_DMA_BASE)

/** \brief CMP �Ĵ�����ָ�� */
#define ZML165_CMP     ((amhw_zlg_cmp_t           *)ZML165_CMP_BASE)

/** \brief NVIC �Ĵ�����ָ�� */
#define ZML165_INT     ((amhw_arm_nvic_t          *)ZML165_NVIC_BASE)

/** \brief SYSTICK �Ĵ�����ָ�� */
#define ZML165_SYSTICK ((amhw_arm_systick_t       *)ZML165_SYSTICK_BASE)

/** \brief FLASH �Ĵ�����ָ�� */
#define ZML165_FLASH   ((amhw_zlg_flash_t         *)ZML165_FLASHCTR_BASE)

/** \brief RCC �Ĵ�����ָ�� */
#define ZML165_RCC     ((amhw_zml165_rcc_t        *)ZML165_RCC_BASE)

/** \brief EXTI �Ĵ�����ָ�� */
#define ZML165_EXTI    ((amhw_zlg_exti_t          *)ZML165_EXTI_BASE)

/** @} */

/**
 * @} zml165_if_periph_map
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZML165_PERIPH_MAP_H */

/* end of file */
