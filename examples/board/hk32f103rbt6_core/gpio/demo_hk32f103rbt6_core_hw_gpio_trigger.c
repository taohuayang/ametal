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
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� J14 �� KEY �� PIOC_7 �̽���һ��
 *
 * - ʵ������
 *    ÿ�ΰ���ʱ���ڴ�ӡ "the gpio interrupt happen!"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hk32f103rbt6_hw_gpio_trigger.c src_hk32f103rbt6_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-24  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_hw_gpio_trigger
 * \copydoc demo_hk32f103rbt6_hw_gpio_trigger.c
 */

/** [src_hk32f103rbt6_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_hk32f103rbt6.h"
#include "amhw_hk32f103rbt6_gpio.h"
#include "amhw_hk32f103rbt6_exti.h"
#include "amhw_hk32f103rbt6_afio.h"
#include "demo_hk32f103rbt6_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_hk32f103rbt6_core_hw_gpio_trigger_entry (void)
{

    AM_DBG_INFO("demo hk32f103rbt6_core hw gpio trigger!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_IOPC);

    am_clk_enable(CLK_AFIO);

    demo_hk32f103rbt6_hw_gpio_trigger_entry((amhw_hk32f103rbt6_gpio_t *)HK32F103RBT6_GPIO,
                                   (amhw_hk32f103rbt6_syscfg_t *)HK32F103RBT6_AFIO,
                                   (amhw_hk32f103rbt6_exti_t *)HK32F103RBT6_EXTI,
                                   PIOC_7,
                                   AMHW_HK32F103RBT6_SYSCFG_EXTI_PORTSOURCE_GPIOC,
                                   AMHW_HK32F103RBT6_SYSCFG_EXTI_PINSOURCE_7,
                                   (amhw_hk32f103rbt6_exti_line_num_t)AMHW_HK32F103RBT6_LINE_NUM7);
}
/** [src_hk32f103rbt6_hw_gpio_trigger] */

/* end of file */
