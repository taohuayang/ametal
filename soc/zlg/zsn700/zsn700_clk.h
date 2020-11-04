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
 * \brief ZSN700 ʱ��ID����
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */

#ifndef __ZSN700_CLK_H
#define __ZSN700_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zsn700_if_clockid
 * \copydoc zsn700_clk.h
 * @{
 */

/**
 * \name ϵͳ�������ʱ��ID
 * \anchor grp_clk_id
 * @{
 */

/* ϵͳ��ʼ��� */
#define CLK_XTHOSC    (0ul)  /**< \brief �ⲿ����ʱ�� */
#define CLK_XTLOSC    (1ul)  /**< \brief �ⲿ����ʱ�� */
#define CLK_RCH       (2ul)  /**< \brief �ڲ�����ʱ�� */
#define CLK_RCL       (3ul)  /**< \brief �ڲ�����ʱ�� */
#define CLK_PLLIN     (4ul)  /**< \brief PLL����ʱ�� */
#define CLK_PLLOUT    (5ul)  /**< \brief PLL���ʱ�� */
#define CLK_SYSCLK    (6ul)  /**< \brief SYSʱ�� */
#define CLK_HCLK      (7ul)  /**< \brief ��ʱ�� */
#define CLK_PCLK      (8ul)  /**< \brief ����ʱ�� */

/* zsn700��������ʱ�Ӿ�������PCLKʱ���� */
#define CLK_FLASH     ((0x1ul << CLK_PCLK) | 31ul)
#define CLK_DMA       ((0x1ul << CLK_PCLK) | 29ul)
#define CLK_GPIO      ((0x1ul << CLK_PCLK) | 28ul)
#define CLK_AES       ((0x1ul << CLK_PCLK) | 27ul)
#define CLK_CRC       ((0x1ul << CLK_PCLK) | 26ul)
#define CLK_SWD       ((0x1ul << CLK_PCLK) | 25ul)
#define CLK_TICK      ((0x1ul << CLK_PCLK) | 24ul)
#define CLK_LCD       ((0x1ul << CLK_PCLK) | 22ul)
#define CLK_CLOCKTRIM ((0x1ul << CLK_PCLK) | 21ul)
#define CLK_RTC       ((0x1ul << CLK_PCLK) | 20ul)
#define CLK_PCNT      ((0x1ul << CLK_PCLK) | 19ul)
#define CLK_RNG       ((0x1ul << CLK_PCLK) | 18ul)
#define CLK_VC_LVD    ((0x1ul << CLK_PCLK) | 17ul)
#define CLK_ADC_BGR   ((0x1ul << CLK_PCLK) | 16ul)
#define CLK_WDT       ((0x1ul << CLK_PCLK) | 15ul)
#define CLK_PCA       ((0x1ul << CLK_PCLK) | 14ul)
#define CLK_OPA       ((0x1ul << CLK_PCLK) | 13ul)
#define CLK_TIM3      ((0x1ul << CLK_PCLK) | 11ul)
#define CLK_TIM456    ((0x1ul << CLK_PCLK) | 10ul)
#define CLK_LPTIM0    ((0x1ul << CLK_PCLK) | 9ul)
#define CLK_TIM012    ((0x1ul << CLK_PCLK) | 8ul)
#define CLK_SPI1      ((0x1ul << CLK_PCLK) | 7ul)
#define CLK_SPI0      ((0x1ul << CLK_PCLK) | 6ul)
#define CLK_I2C1      ((0x1ul << CLK_PCLK) | 5ul)
#define CLK_I2C0      ((0x1ul << CLK_PCLK) | 4ul)
#define CLK_LPUART1   ((0x1ul << CLK_PCLK) | 3ul)
#define CLK_LPUART0   ((0x1ul << CLK_PCLK) | 2ul)
#define CLK_UART1     ((0x1ul << CLK_PCLK) | 1ul)
#define CLK_UART0     ((0x1ul << CLK_PCLK) | 0ul)
#define CLK_UART3     ((0x1ul << CLK_PCLK) | 40ul)
#define CLK_UART2     ((0x1ul << CLK_PCLK) | 39ul)
#define CLK_LPTIM1    ((0x1ul << CLK_PCLK) | 35ul)
#define CLK_DAC       ((0x1ul << CLK_PCLK) | 34ul)

/**
 * @}
 */

/**
 * @} zsn700_if_clk
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZSN700_CLK_H */

/* end of file */
