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
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ�󴮿ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      usart tx dma test running
 *      usart tx dma test done
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_3 �������� PC ���ڵ� TXD��
 *       PIOA_2 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *    3. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_hw_usart_tx_dma.c src_stm32f103rbt6_hw_usart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-10  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_hw_usart_tx_dma
 * \copydoc demo_stm32f103rbt6_hw_usart_tx_dma.c
 */

/** [src_stm32f103rbt6_hw_usart_tx_dma] */
#include "ametal.h"
#include "am_stm32f103rbt6.h"
#include "demo_stm32f103rbt6_entries.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_hw_usart_tx_dma_entry (void)
{
    AM_DBG_INFO("demo stm32f103rbt6_core hw usart tx dma!\r\n");

    /* �ȴ����Դ��ڷ���������� */
    am_mdelay(100);

    /* ʹ�ܴ���ʱ��*/
    am_clk_enable(CLK_USART2);

    /* ʹ�ܴ����������*/
    am_gpio_pin_cfg(PIOA_2, PIOA_2_NO_REMAP | PIOA_2_AF_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_NO_REMAP | PIOA_3_INPUT_FLOAT);

    demo_stm32f103rbt6_hw_usart_tx_dma_entry((void *)STM32F103RBT6_USART2,
                                      am_clk_rate_get(CLK_USART2),
                                      DMA_CHAN_USART2_TX);
}
/** [src_stm32f103rbt6_hw_usart_tx_dma] */

/* end of file */
