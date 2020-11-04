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
 * \brief HC32F460 ģ�幤��
 *
 * - ʵ������:
 *         ��ӡ "Start up successful!"
 *
 * \internal
 * \par Modification history
 * - 1.00 20-01-10  cds, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"

int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");

    while (1) {

        am_led_toggle(LED0);

        am_mdelay(1000);
    }
}

/* end of file */
