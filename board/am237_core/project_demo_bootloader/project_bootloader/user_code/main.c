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
 * \brief zlg237 bootloader ʾ������
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-027  yrh, first implementation
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
#include "demo_am237_core_entries.h"

int am_main (void)
{

    AM_DBG_INFO("Start up successful!\r\n");

    /* ����bootloader demo */
    //demo_zlg237_core_single_bootloader_uart_entry();

    /* ˫��bootloader demo */
    demo_zlg237_core_double_bootloader_uart_entry();

    /* ������λ���� bootloader demo */
    //demo_zlg237_core_bootloader_kft_entry();
    while (1) {

    }
}

/* end of file */
