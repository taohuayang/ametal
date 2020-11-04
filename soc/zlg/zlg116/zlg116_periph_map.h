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
 * \brief ZLG116 ����ӳ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __ZLG116_PERIPH_MAP_H
#define __ZLG116_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zlg116_regbase.h"

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

#include "amhw_zlg116_device.h"
#include "hw/amhw_zlg116_rcc.h"


/**
 * \addtogroup zlg116_if_periph_map
 * \copydoc zlg116_periph_map.h
 * @{
 */

/**
 * \name ���趨��
 * @{
 */

/** \brief ��Դ����Ԫ(PWR)�Ĵ�����ָ�� */
#define ZLG116_PWR     ((amhw_zlg_pwr_t           *)ZLG116_PWR_BASE)

/** \brief ��������(BKP)�Ĵ�����ָ�� */
#define ZLG116_BKP     ((amhw_zlg_bkp_t           *)ZLG116_BKP_BASE)

/** \brief ϵͳ����(SYSCFG)�Ĵ�����ָ�� */
#define ZLG116_SYSCFG  ((amhw_zlg_syscfg_t        *)ZLG116_SYSCFG_BASE)

/** \brief GPIO�˿�A�Ĵ�����ָ�� */
#define ZLG116_GPIOA   ((amhw_zlg_gpio_t          *)ZLG116_GPIOA_BASE)

/** \brief GPIO�˿�B�Ĵ�����ָ�� */
#define ZLG116_GPIOB   ((amhw_zlg_gpio_t          *)ZLG116_GPIOB_BASE)

/** \brief GPIO�˿�C�Ĵ�����ָ�� */
#define ZLG116_GPIOC   ((amhw_zlg_gpio_t          *)ZLG116_GPIOC_BASE)

/** \brief GPIO�˿�D�Ĵ�����ָ�� */
#define ZLG116_GPIOD   ((amhw_zlg_gpio_t          *)ZLG116_GPIOD_BASE)

/** \brief GPIO�Ĵ�����ָ�� */
#define ZLG116_GPIO    ((amhw_zlg_gpio_t          *)ZLG116_GPIO_BASE)

/** \brief 16λ�߼���ʱ��1�Ĵ���ָ�� */
#define ZLG116_TIM1    ((amhw_zlg_tim_t           *)ZLG116_TIM1_BASE)

/** \brief 16λͨ�ö�ʱ��14�Ĵ���ָ�� */
#define ZLG116_TIM14   ((amhw_zlg_tim_t           *)ZLG116_TIM14_BASE)

/** \brief 16λͨ�ö�ʱ��16�Ĵ���ָ�� */
#define ZLG116_TIM16   ((amhw_zlg_tim_t           *)ZLG116_TIM16_BASE)

/** \brief 16λͨ�ö�ʱ��17�Ĵ���ָ�� */
#define ZLG116_TIM17   ((amhw_zlg_tim_t           *)ZLG116_TIM17_BASE)

/** \brief 16λͨ�ö�ʱ��2�Ĵ���ָ�� */
#define ZLG116_TIM2    ((amhw_zlg_tim_t           *)ZLG116_TIM2_BASE)

/** \brief 16λͨ�ö�ʱ��3�Ĵ���ָ�� */
#define ZLG116_TIM3    ((amhw_zlg_tim_t           *)ZLG116_TIM3_BASE)

/** \brief I2C���߿�����(I2C0)�Ĵ�����ָ�� */
#define ZLG116_I2C     ((amhw_zlg_i2c_t           *)ZLG116_I2C1_BASE )

/** \brief �������Ź�(IWDG)�Ĵ�����ָ�� */
#define ZLG116_IWDG    ((amhw_zlg_iwdg_t          *)ZLG116_IWDG_BASE)

/** \brief ���ڿ��Ź�(WWDG)�Ĵ�����ָ�� */
#define ZLG116_WWDG    ((amhw_zlg_wwdg_t          *)ZLG116_WWDG_BASE)

/** \brief ����(UART2)�Ĵ�����ָ�� */
#define ZLG116_UART2   ((amhw_zlg_uart_t          *)ZLG116_UART2_BASE)

/** \brief ����(UART1)�Ĵ�����ָ�� */
#define ZLG116_UART1   ((amhw_zlg_uart_t          *)ZLG116_UART1_BASE)

/** \brief ģ��ת��(ADC)�Ĵ�����ָ�� */
#define ZLG116_ADC     ((amhw_zlg_adc_t           *)ZLG116_ADC_BASE)

/** \brief SPI1 �Ĵ�����ָ�� */
#define ZLG116_SPI1    ((amhw_zlg_spi_t           *)ZLG116_SPI1_BASE)

/** \brief SPI2 �Ĵ�����ָ�� */
#define ZLG116_SPI2    ((amhw_zlg_spi_t           *)ZLG116_SPI2_BASE)

/** \brief DMA ������(DMA)�Ĵ�����ָ�� */
#define ZLG116_DMA     ((amhw_zlg_dma_t           *)ZLG116_DMA_BASE)

/** \brief CMP �Ĵ�����ָ�� */
#define ZLG116_CMP     ((amhw_zlg_cmp_t           *)ZLG116_CMP_BASE)

/** \brief NVIC �Ĵ�����ָ�� */
#define ZLG116_INT     ((amhw_arm_nvic_t          *)ZLG116_NVIC_BASE)

/** \brief SYSTICK �Ĵ�����ָ�� */
#define ZLG116_SYSTICK ((amhw_arm_systick_t       *)ZLG116_SYSTICK_BASE)

/** \brief FLASH �Ĵ�����ָ�� */
#define ZLG116_FLASH   ((amhw_zlg_flash_t         *)ZLG116_FLASHCTR_BASE)

/** \brief RCC �Ĵ�����ָ�� */
#define ZLG116_RCC     ((amhw_zlg116_rcc_t        *)ZLG116_RCC_BASE)

/** \brief EXTI �Ĵ�����ָ�� */
#define ZLG116_EXTI    ((amhw_zlg_exti_t          *)ZLG116_EXTI_BASE)

/** \brief EXTI �Ĵ�����ָ�� */
#define ZLG116_DEVICE    ((amhw_zlg116_device_t          *)ZLG116_DEVICE_BASE)
/** @} */

/**
 * @} zlg116_if_periph_map
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG116_PERIPH_MAP_H */

/* end of file */
