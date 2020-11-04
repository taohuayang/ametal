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
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsn700_std_gpio_trigger.c src_zsn700_std_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20  zp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_std_gpio_trigger
 * \copydoc demo_zsn700_std_gpio_trigger.c
 */

/** [src_zsn700_std_gpio_trigger] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_zsn700.h"
#include "demo_std_entries.h"
#include "demo_am700_core_entries.h"

/**
 * \brief �������
 */
void demo_zsn700_core_std_gpio_trigger_entry (void)
{
    AM_DBG_INFO("demo am700_core std gpio trigger!\r\n");

    demo_std_gpio_trigger_entry(PIOA_8);
}
/** [src_zsn700_std_gpio_trigger] */

/* end of file */
