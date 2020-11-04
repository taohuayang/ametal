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
 * \brief ZLG ʱ��ID����
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __ZML165_CLK_H
#define __ZML165_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zml165_if_clockid
 * \copydoc zml165_clk.h
 * @{
 */

/**
 * \name ϵͳ�������ʱ��ID
 * \anchor grp_clk_id
 * @{
 */

/* APB1����ʱ�� */
#define CLK_TIM2    (0x01ul << 8 | 0ul)   /**< \brief TIM2��ʱ�� ʱ�� */
#define CLK_TIM3    (0x01ul << 8 | 1ul)   /**< \brief TIM3��ʱ�� ʱ�� */
#define CLK_WWDG    (0x01ul << 8 | 11ul)  /**< \brief WWDG���ڿ��Ź� ʱ�� */
#define CLK_SPI2    (0x01ul << 8 | 14ul)  /**< \brief SPI2 ʱ�� */
#define CLK_UART2   (0x01ul << 8 | 17ul)  /**< \brief UART2 ʱ�� */
#define CLK_I2C1    (0x01ul << 8 | 21ul)  /**< \brief I2C1 ʱ�� */
#define CLK_USB     (0x01ul << 8 | 23ul)  /**< \brief USB ʱ�� */
#define CLK_CAN     (0x01ul << 8 | 25ul)  /**< \brief CAN ʱ�� */
#define CLK_CRS     (0x01ul << 8 | 27ul)  /**< \brief CRS ʱ�� */
#define CLK_PWR     (0x01ul << 8 | 28ul)  /**< \brief ��Դ�ӿ� ʱ�� */

/* APB2����ʱ�� */
#define CLK_SYSCFG  (0x02ul << 8 | 0ul)  /**< \brief ϵͳ���üĴ��� ʱ�� */
#define CLK_ADC1    (0x02ul << 8 | 9ul)  /**< \brief ADC1�ӿ� ʱ�� */
#define CLK_TIM1    (0x02ul << 8 | 11ul) /**< \brief TIM1��ʱ�� ʱ�� */
#define CLK_SPI1    (0x02ul << 8 | 12ul) /**< \brief SPI1 ʱ�� */
#define CLK_UART1   (0x02ul << 8 | 14ul) /**< \brief UART1 ʱ�� */
#define CLK_CPT     (0x02ul << 8 | 15ul) /**< \brief �Ƚ��� ʱ�� */
#define CLK_TIM14   (0x02ul << 8 | 16ul) /**< \brief TIM14 ʱ�� */
#define CLK_TIM16   (0x02ul << 8 | 17ul) /**< \brief TIM16 ʱ�� */
#define CLK_TIM17   (0x02ul << 8 | 18ul) /**< \brief TIM17 ʱ�� */
#define CLK_DBGMCU  (0x02ul << 8 | 22ul) /**< \brief DBGMCU ʱ�� */

/* AHB����ʱ�� */
#define CLK_DMA    (0x03ul << 8 | 0ul)   /**< \brief DMA ʱ�� */
#define CLK_SRAM   (0x03ul << 8 | 2ul)   /**< \brief SRAM ʱ�� */
#define CLK_FLITF  (0x03ul << 8 | 4ul)   /**< \brief FLITF ʱ�� */
#define CLK_AES    (0x03ul << 8 | 7ul)   /**< \brief AES ʱ�� */
#define CLK_GPIOA  (0x03ul << 8 | 17ul)  /**< \brief GPIOA ʱ�� */
#define CLK_GPIOB  (0x03ul << 8 | 18ul)  /**< \brief GPIOB ʱ�� */
#define CLK_GPIOC  (0x03ul << 8 | 19ul)  /**< \brief GPIOC ʱ�� */
#define CLK_GPIOD  (0x03ul << 8 | 20ul)  /**< \brief GPIOD ʱ�� */

/* ����ʱ�� */
#define CLK_PLLIN  (0x04ul << 8 | 0ul)  /**< \brief PLL���� ʱ�� */
#define CLK_PLLOUT (0x04ul << 8 | 1ul)  /**< \brief PLL��� ʱ�� */
#define CLK_AHB    (0x04ul << 8 | 2ul)  /**< \brief AHB ʱ�� */
#define CLK_APB1   (0x04ul << 8 | 3ul)  /**< \brief APB1 ʱ�� */
#define CLK_APB2   (0x04ul << 8 | 4ul)  /**< \brief APB2 ʱ�� */
#define CLK_HSEOSC (0x04ul << 8 | 5ul)  /**< \brief �ⲿ���� ʱ�� */
#define CLK_LSI    (0x04ul << 8 | 6ul)  /**< \brief LSI ʱ�� */
#define CLK_HSI    (0x04ul << 8 | 7ul)  /**< \brief HSI ʱ�� */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZML165_CLK_H */

/* end of file */
