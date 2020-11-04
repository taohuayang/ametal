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
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���°��� KEY/RES��������� "the gpio interrupt happen!"��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *    PIOE_5 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_gpio_trigger.c src_hc32f460_std_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 20-01-16  cds, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_gpio_trigger
 * \copydoc demo_hc32f460_std_gpio_trigger.c
 */

/** [src_hc32f460_std_gpio_trigger] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_gpio_trigger_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core std gpio trigger!\r\n");

    demo_std_gpio_trigger_entry(PIOD_3);
}
/** [src_hc32f460_std_gpio_trigger] */

/* end of file */
