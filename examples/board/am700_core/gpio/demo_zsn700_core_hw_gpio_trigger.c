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
 * \snippet demo_zsn700_hw_gpio_trigger.c src_zsn700_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_gpio_trigger
 * \copydoc demo_zsn700_hw_gpio_trigger.c
 */

/** [src_zsn700_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_gpio.h"
#include "demo_zlg_entries.h"
#include "demo_am700_core_entries.h"

/**
 * \brief �������
 */
void demo_zsn700_core_hw_gpio_trigger_entry (void)
{

    AM_DBG_INFO("demo am217_core hw gpio trigger!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_GPIO);

    demo_zsn700_hw_gpio_trigger_entry((void *)ZSN700_GPIO0, PIOA_8);
}
/** [src_zsn700_hw_gpio_trigger] */

/* end of file */
