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
 * \brief ϵͳ���ƽӿ�
 *
 * 1. ��ӳ�䲿�ִ� TIM16 �� TIM17��UART1 �� ADC �� DMA ����Դ��������ͬ�� DMAͨ���ϣ�
 * 2. �������ӵ� GPIO�ڵ��ⲿ�жϣ�
 * 3. ��ӳ��洢����������ʼ����
 * 4. �ⲿ�ж��������ã�
 *
 * \internal
 * \par History
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_STM32F103RBT6_SYSCFG_H
#define __AMHW_STM32F103RBT6_SYSCFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_stm32f103rbt6_if_syscfg
 * \copydoc amhw_stm32f103rbt6_syscfg.h
 * @{
 */

/**
 * \name �ⲿ�ж϶˿�Դ
 * @{
 */

#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOA       ((uint8_t)0x00)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOB       ((uint8_t)0x01)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOC       ((uint8_t)0x02)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOD       ((uint8_t)0x03)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOE       ((uint8_t)0x04)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOF       ((uint8_t)0x05)

#define AMHW_STM32F103RBT6_SYSCFG_IS_EXTI_PORTSOURCE(portsource) \
           (((portsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOA) || \
            ((portsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOB) || \
            ((portsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOC) || \
            ((portsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOD) || \
            ((portsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOE) || \
            ((portsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOF))

/** @} */

/**
 * \name �ⲿ�жϵ�����Դ
 * @{
 */
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_0            ((uint8_t)0x00)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_1            ((uint8_t)0x01)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_2            ((uint8_t)0x02)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_3            ((uint8_t)0x03)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_4            ((uint8_t)0x04)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_5            ((uint8_t)0x05)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_6            ((uint8_t)0x06)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_7            ((uint8_t)0x07)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_8            ((uint8_t)0x08)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_9            ((uint8_t)0x09)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_10           ((uint8_t)0x0A)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_11           ((uint8_t)0x0B)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_12           ((uint8_t)0x0C)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_13           ((uint8_t)0x0D)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_14           ((uint8_t)0x0E)
#define AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_15           ((uint8_t)0x0F)

#define AMHW_STM32F103RBT6_SYSCFG_IS_EXTI_PIN_SOURCE(pinsource) \
           (((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_0)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_1)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_2)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_3)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_4)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_5)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_6)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_7)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_8)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_9)  || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_10) || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_11) || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_12) || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_13) || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_14) || \
            ((pinsource) == AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_15))

/** @} */

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_stm32f103rbt6_syscfg {
    __IO uint32_t cfgr;        /**< \brief ϵͳ���üĴ��� */
    __I  uint32_t reserve;     /**< \brief ���� */
    __IO uint32_t exticr[4];   /**< \brief �ⲿ�ж����üĴ��� */
} amhw_stm32f103rbt6_syscfg_t;

/**
 * \brief ϵͳ�ڴ���ӳ�䣬������ӳ��洢����������ʼ����
 */
typedef enum amhw_stm32f103rbt6_syscfg_bootmode_remap {
    AMHW_STM32F103RBT6_SYSCFG_REMAP_BOOT_MAIN_FLASH = 0,  /**< \brief ������洢��ӳ�䵽 0x00000000 */
    AMHW_STM32F103RBT6_SYSCFG_REMAP_BOOT_SYS_FLASH  = 1,  /**< \brief ϵͳ����ӳ�䵽 0x00000000 */
    AMHW_STM32F103RBT6_SYSCFG_REMAP_BOOT_SRAM       = 3,  /**< \brief Ƕ��ʽ RAM ӳ�䵽 0x00000000 */
} amhw_stm32f103rbt6_syscfg_bootmode_remap_t;

/**
 * \brief ĳЩ����(UART1, TIM16��TIM17)DMAͨ����ӳ��
 */
typedef enum amhw_stm32f103rbt6_syscfg_dma_chan_remap {
    AMHW_STM32F103RBT6_SYSCFG_REMAP_TIM17_DMA    = (1 << 12), /**< \brief ��ʱ��17DMAͨ����ӳ�� */
    AMHW_STM32F103RBT6_SYSCFG_REMAP_TIM16_DMA    = (1 << 11), /**< \brief ��ʱ��16DMAͨ����ӳ�� */
    AMHW_STM32F103RBT6_SYSCFG_REMAP_UART1_RX_DMA = (1 << 10), /**< \brief UART1_RX_DMAͨ����ӳ�� */
    AMHW_STM32F103RBT6_SYSCFG_REMAP_UART1_TX_DMA = (1 << 9),  /**< \brief UART1_TX_DMAͨ����ӳ�� */
    AMHW_STM32F103RBT6_SYSCFG_REMAP_ADC_DMA      = (1 << 8),  /**< \brief ADC_DMͨ����ӳ�� */
} amhw_stm32f103rbt6_syscfg_dma_chan_remap_t;

/**
 * \brief ��ӳ��洢����������ʼ����
 *
 * \param[in] remap       ��ӳ�������ʼ���Ĵ洢λ��
 * \param[in] p_hw_syscfg ��ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_syscfg_mem_mode_remap_set (
                                amhw_stm32f103rbt6_syscfg_t               *p_hw_syscfg,
                                amhw_stm32f103rbt6_syscfg_bootmode_remap_t remap)
{
    AM_BITS_SET(p_hw_syscfg->cfgr, 0, 2, remap);
}

/**
 * \brief ��ȡ�洢����������ʼ�������ӳ��ֵ
 *
 * \param[in] p_hw_syscfg ��ָ��ϵͳ���üĴ������ָ��
 *
 * \return ������������ʼ�������ӳ��ֵ
 */
am_static_inline
int amhw_stm32f103rbt6_syscfg_mem_mode_remap_get (amhw_stm32f103rbt6_syscfg_t *p_hw_syscfg)
{
    return (amhw_stm32f103rbt6_syscfg_bootmode_remap_t)p_hw_syscfg->cfgr;
}

/**
 * \brief ��ӳ��ĳЩ����(UART1, TIM16��TIM17)��DMAͨ��
 *
 * \param[in] remap       ����ӳ���DMAͨ����ֵΪ amhw_stm32f103rbt6_syscfg_dma_chan_remap_t
 *                         ��ö�����ͣ�����ʹ�û����
 * \param[in] p_hw_syscfg ��ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_syscfg_dma_chan_remap_set (
                                   amhw_stm32f103rbt6_syscfg_t               *p_hw_syscfg,
                                   amhw_stm32f103rbt6_syscfg_dma_chan_remap_t remap)
{
    AM_BITS_SET(p_hw_syscfg->cfgr, 8, 5, remap);
}

/**
 * \brief ѡ�� EXTIx(x=A...D) �ⲿ�жϵ�����Դ
 *
 * \param[in] p_hw_syscfg ��ָ��ϵͳ���üĴ������ָ��
 * \param[in] portsource  ���˿�Դ,ֵΪ AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE* ��һ���
 *                          (# AMHW_STM32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOA)
 * \param[in] pinsource   ������Դ��ֵΪ  AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE* ��һ���
 *                          (# AMHW_STM32F103RBT6_SYSCFG_EXTI_PINSOURCE_0)
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_syscfg_exti_line_config (amhw_stm32f103rbt6_syscfg_t *p_hw_syscfg,
                                       uint8_t            portsource,
                                       uint8_t            pinsource)
{
    uint32_t tmp = 0x00;

    /*
     * ԭ����ѡ���0�����ţ���Ӧ���������4λ��������4λΪ0���������PA0����
     */

    tmp = ((uint32_t)0x0F) << (0x04 * (pinsource & (uint8_t)0x03));

    p_hw_syscfg->exticr[pinsource >> 0x02] &= ~tmp;
    p_hw_syscfg->exticr[pinsource >> 0x02] |= \
               (((uint32_t)portsource) << (0x04 * (pinsource & (uint8_t)0x03)));
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_STM32F103RBT6_SYSCFG_H */

/* end of file */
