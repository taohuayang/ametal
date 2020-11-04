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
 * \brief USART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 *
 * - ʵ������
 *   1. ������� "HW example---USART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_3 �������� PC ���ڵ� TXD��
 *       PIOA_2 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_hw_usart_polling.c src_stm32f103rbt6_hw_usart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_stm32f103rbt6_hw_usart_polling
 * \copydoc demo_stm32f103rbt6_hw_usart_polling.c
 */

/** [src_stm32f103rbt6_hw_usart_polling] */
#include "ametal.h"
#include "am_board.h"
#include "am_stm32f103rbt6.h"
#include "am_gpio.h"
#include "demo_stm32f103rbt6_entries.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_hw_usart_polling_entry (void)
{
    AM_DBG_INFO("demo stm32f103rbt6_core hw uart polling!\r\n");

    /* �ȴ����Դ��ڷ���������� */
    am_mdelay(100);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_NO_REMAP | PIOA_2_AF_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_NO_REMAP | PIOA_3_INPUT_FLOAT);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_USART2);

    demo_stm32f103rbt6_hw_usart_polling_entry((void *)STM32F103RBT6_USART2, am_clk_rate_get(CLK_USART2));
}
/** [src_stm32f103rbt6_hw_usart_polling] */

/* end of file */
