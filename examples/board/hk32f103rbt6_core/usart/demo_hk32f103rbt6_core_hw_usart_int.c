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
 * \brief USART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "HW example---USART test in interrupt mode:"��
 *   2. ����������յ����ַ���
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_3 �������� PC ���ڵ� TXD��
 *       PIOA_2 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hk32f103rbt6_hw_usart_int.c src_hk32f103rbt6_hw_usart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-01-20  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hk32f103rbt6_hw_usart_int
 * \copydoc demo_hk32f103rbt6_hw_usart_int.c
 */

/** [src_hk32f103rbt6_hw_usart_int] */
#include "ametal.h"
#include "am_hk32f103rbt6.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_hk32f103rbt6_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"


static void __hk32f103rbt6_usart_pins_intit (void)
{
    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_NO_REMAP | PIOA_2_AF_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_NO_REMAP | PIOA_3_INPUT_FLOAT);
}

/**
 * \brief �������
 */
void demo_hk32f103rbt6_core_hw_usart_int_entry (void)
{
    AM_DBG_INFO("demo hk32f103rbt6_core hw usart int!\r\n");

    /* �ȴ����Դ��ڷ���������� */
    am_mdelay(100);

    /* ʹ�ܴ���ʱ�� */
    am_clk_enable(CLK_USART2);

    demo_hk32f103rbt6_hw_usart_int_entry((void *)HK32F103RBT6_USART2,
                                   __hk32f103rbt6_usart_pins_intit,
                                   am_clk_rate_get(CLK_USART2),
                                   HK32F103RBT6_USART2_BASE,
                                   INUM_USART2);
}
/** [src_hk32f103rbt6_hw_usart_int] */

/* end of file */
