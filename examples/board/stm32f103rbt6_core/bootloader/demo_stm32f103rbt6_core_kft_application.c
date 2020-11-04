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
 * \brief bootloader ���̣���demo����Ϊ������Ӧ�ó����޷���Ӧ�ó�������������
 *
 * - ��������:
 *   1.eclipse���̴�demo_stm32f103rbt6_core_application.ld�ļ�����:
 *
 *       FLASH (rx)  : ORIGIN = 0x0800AC00, LENGTH = 85K     // kft
 *
 *     ������, ��������flash���á�
 *
 *     keil���̴�demo_stm32f103rbt6_core_application.sct�ļ�������λ�������ã�������������
 *
 *   2.���빤��
 *   3.���̳���bin�ļ���Ϊ�̼�
 *
 * - ��������
 *   1. LED����˸������ѭ����ӡ��
 *   
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-18  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_delay.h"

void demo_stm32f103rbt6_core_kft_application_entry (void)
{
    AM_DBG_INFO("application : stm32f103rbt6_core kft application start up successful!\r\n");

    while(1) {
        AM_DBG_INFO("application : stm32f103rbt6_core kft application running\r\n");
        am_led_toggle(0);
        am_mdelay(1000);
    }
}

/* end of file */
