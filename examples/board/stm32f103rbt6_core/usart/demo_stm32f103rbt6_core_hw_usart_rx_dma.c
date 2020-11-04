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
 * \brief USART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ͨ����λ������һ������ MCU ���� 5 ���ַ���
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����յ������ݣ�
 *   2. Ȼ�󴮿ڴ�ӡ�� "DMA transfer done!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_3 �������� PC ���ڵ� TXD��
 *       PIOA_2 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_hw_usart_rx_dma.c src_stm32f103rbt6_hw_usart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 17-03-10  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_hw_usart_rx_dma
 * \copydoc demo_stm32f103rbt6_hw_usart_rx_dma.c
 */

/** [src_stm32f103rbt6_hw_usart_rx_dma] */
#include "ametal.h"
#include "am_stm32f103rbt6.h"
#include "demo_stm32f103rbt6_entries.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_hw_usart_rx_dma_entry (void)
{


    AM_DBG_INFO("demo stm32f103rbt6_core hw usart tx dma!\r\n");

    /* �ȴ����Դ��ڷ���������� */
    am_mdelay(100);

    /* ʹ�ܴ���ʱ��*/
    am_clk_enable(CLK_USART2);

    /* ʹ�ܴ����������*/
    am_gpio_pin_cfg(PIOA_2, PIOA_2_NO_REMAP | PIOA_2_AF_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_NO_REMAP | PIOA_3_INPUT_FLOAT);

    demo_stm32f103rbt6_hw_usart_rx_dma_entry((void *)STM32F103RBT6_USART2,
                                      am_clk_rate_get(CLK_USART2),
                                      DMA_CHAN_USART2_RX);
}

/** [src_stm32f103rbt6_hw_usart_rx_dma] */

/* end of file */
