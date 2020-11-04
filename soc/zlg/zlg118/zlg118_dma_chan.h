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
 * \brief ZLG118 DMA ͨ����Ŷ���
 *
 * \internal
 * \par Modification History
 *
 * - 1.00 17-08-23  lqy, first implementation
 *
 * \endinternal
 */

#ifndef __ZLG118_DMA_CHAN_H
#define __ZLG118_DMA_CHAN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zlg118_if_dma_chan
 * \copydoc zlg118_dma_chan.h
 * @{
 */

/**
 * \name zlg118 DMA ͨ�����
 * @{
 */
#define DMA_CHAN_1                0               /**< \brief DMAͨ��1 */
#define DMA_CHAN_2                1               /**< \brief DMAͨ��2 */

/** @} */

/**
 * \name �����DMA����ͨ��
 * \anchor dma_request_src
 * @{
 */

#define ZLG118_DMA_SRC_TYPE_SOFT         0x00  /* �������󴥷�ԴΪ ��� */
#define ZLG118_DMA_SRC_TYPE_SPI0_RX      0x40  /* �������󴥷�ԴΪ SPI0_RX */
#define ZLG118_DMA_SRC_TYPE_SPI0_TX      0x41  /* �������󴥷�ԴΪ SPI0_TX */
#define ZLG118_DMA_SRC_TYPE_SPI1_RX      0x42  /* �������󴥷�ԴΪ SPI1_RX */
#define ZLG118_DMA_SRC_TYPE_SPI1_TX      0x43  /* �������󴥷�ԴΪ SPI1_TX */
#define ZLG118_DMA_SRC_TYPE_ADC_JRQ0_RX  0x44  /* �������󴥷�ԴΪ ADC_JRQ0_RX */
#define ZLG118_DMA_SRC_TYPE_ADC_SRQ0_RX  0x45  /* �������󴥷�ԴΪ ADC_SRQ0_RX */
#define ZLG118_DMA_SRC_TYPE_LCD_TX       0x45  /* �������󴥷�ԴΪ LCD_TX */

#define ZLG118_DMA_SRC_TYPE_UART0_RX     0x48  /* �������󴥷�ԴΪ UART0_RX */
#define ZLG118_DMA_SRC_TYPE_UART0_TX     0x49  /* �������󴥷�ԴΪ UART0_TX */
#define ZLG118_DMA_SRC_TYPE_UART1_RX     0x4A  /* �������󴥷�ԴΪ UART1_RX */
#define ZLG118_DMA_SRC_TYPE_UART1_TX     0x4B  /* �������󴥷�ԴΪ UART1_TX */
#define ZLG118_DMA_SRC_TYPE_LPUART0_RX   0x4C  /* �������󴥷�ԴΪ LPUART0_RX */
#define ZLG118_DMA_SRC_TYPE_LPUART0_TX   0x4D  /* �������󴥷�ԴΪ LPUART0_TX */
#define ZLG118_DMA_SRC_TYPE_LPUART1_RX   0x4E  /* �������󴥷�ԴΪ LPUART1_RX */
#define ZLG118_DMA_SRC_TYPE_LPUART1_TX   0x4F  /* �������󴥷�ԴΪ LPUART1_TX */
#define ZLG118_DMA_SRC_TYPE_DAC0         0x50  /* �������󴥷�ԴΪ DAC0 */

#define ZLG118_DMA_SRC_TYPE_TIM0_CHA     0x52  /* �������󴥷�ԴΪ TIM0_CHA */
#define ZLG118_DMA_SRC_TYPE_TIM0_CHB     0x53  /* �������󴥷�ԴΪ TIM0_CHB */
#define ZLG118_DMA_SRC_TYPE_TIM1_CHA     0x54  /* �������󴥷�ԴΪ TIM1_CHA */
#define ZLG118_DMA_SRC_TYPE_TIM1_CHB     0x55  /* �������󴥷�ԴΪ TIM1_CHB */
#define ZLG118_DMA_SRC_TYPE_TIM2_CHA     0x56  /* �������󴥷�ԴΪ TIM2_CHA */
#define ZLG118_DMA_SRC_TYPE_TIM2_CHB     0x57  /* �������󴥷�ԴΪ TIM2_CHB */
#define ZLG118_DMA_SRC_TYPE_TIM3_CHA     0x58  /* �������󴥷�ԴΪ TIM3_CHA */
#define ZLG118_DMA_SRC_TYPE_TIM3_CHB     0x59  /* �������󴥷�ԴΪ TIM3_CHB */
#define ZLG118_DMA_SRC_TYPE_TIM4_CHA     0x5A  /* �������󴥷�ԴΪ TIM4_CHA */
#define ZLG118_DMA_SRC_TYPE_TIM4_CHB     0x5B  /* �������󴥷�ԴΪ TIM4_CHB */
#define ZLG118_DMA_SRC_TYPE_TIM5_CHA     0x5C  /* �������󴥷�ԴΪ TIM5_CHA */
#define ZLG118_DMA_SRC_TYPE_TIM5_CHB     0x5D  /* �������󴥷�ԴΪ TIM5_CHB */
#define ZLG118_DMA_SRC_TYPE_TIM6_CHA     0x5E  /* �������󴥷�ԴΪ TIM6_CHA */
#define ZLG118_DMA_SRC_TYPE_TIM6_CHB     0x5F  /* �������󴥷�ԴΪ TIM6_CHB */
#define ZLG118_DMA_SRC_TYPE_UART4_RX     0x60  /* �������󴥷�ԴΪ UART4_RX */
#define ZLG118_DMA_SRC_TYPE_UART4_TX     0x61  /* �������󴥷�ԴΪ UART4_TX */
#define ZLG118_DMA_SRC_TYPE_UART5_RX     0x62  /* �������󴥷�ԴΪ UART5_RX */
#define ZLG118_DMA_SRC_TYPE_UART5_TX     0x63  /* �������󴥷�ԴΪ UART5_TX */

/** @} */

/**
 * @} zlg118_if_dma_chan
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG118_DMA_CHAN_H */

/* end of file */
