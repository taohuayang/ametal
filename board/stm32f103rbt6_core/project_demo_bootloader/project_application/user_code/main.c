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
 * \brief stm32f103rbt6 bootloader�����õ�Ӧ�ù���
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
#include "demo_stm32f103rbt6_core_entries.h"

int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");

    /* ����bootloader �Ĳ���Ӧ�ó��� demo */
//    demo_stm32f103rbt6_core_single_application_entry();

    /* ˫��bootloader �Ĳ���Ӧ�ó��� demo */
    demo_stm32f103rbt6_core_double_application_entry();

    /* ������λ���� bootloader �Ĳ���Ӧ�ó��� demo */
    //demo_stm32f103rbt6_core_kft_application_entry();

    while (1) {

    }
}

/* end of file */
