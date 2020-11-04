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
 * - ʵ������
 *    ÿ�ΰ���ʱ���ڴ�ӡ "the gpio interrupt happen!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f03x_hw_gpio_trigger.c src_hc32f03x_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f03x_hw_gpio_trigger
 * \copydoc demo_hc32f03x_hw_gpio_trigger.c
 */

/** [src_hc32f03x_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_hc32.h"
#include "hw/amhw_hc32_gpio.h"
#include "demo_hc32_entries.h"
#include "demo_amf03x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f03x_core_hw_gpio_trigger_entry (void)
{

    AM_DBG_INFO("demo am217_core hw gpio trigger!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_GPIO);

    demo_hc32_hw_gpio_trigger_entry((void *)HC32_GPIO0, PIOA_7);
}
/** [src_hc32f03x_hw_gpio_trigger] */

/* end of file */
