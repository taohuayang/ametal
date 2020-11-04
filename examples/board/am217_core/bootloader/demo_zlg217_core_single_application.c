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
 *   1.eclipse���̴�demo_am217_core_boot_application.ld�ļ�����:
 *
 *       FLASH (rx)  : ORIGIN = 0x08007000, LENGTH = 100K  //single
 *
 *     ������, ��������flash���á�
 *
 *     keil���̴�demo_am217_core_application.sct�ļ����򿪵��������ã�������������
 *
 *   2.���빤��
 *   3.�̼������ο�����note��ʾ
 *
 * - ��������
 *   1. LED����˸������ѭ����ӡ��
 *   
 *
 * \note
 *    ���̱��������ɶ�Ӧ�Ĺ���bin�ļ�����Ҫ��bin�ļ����д���������Ϊ�̼�����
 *
 *    �̼�����
 *
 *    ����ametal/tools/bootloader/�̼�У��/ �ļ��У�Ŀ¼����һ��bin_chek_sum.bin��ִ���ļ���
 *    �������̱������bin�ļ���������bin_chek_sum.binͬһ��Ŀ¼�£�
 *    �ڸ�Ŀ¼�´�cmd�������������������룺
 *         bin_chek_sum.bin  xxx.bin��������bin�ļ����ƣ� xxx.bin��Ŀ������ļ�����������ȡ��
 *
 *    ִ������������һ�����û��Լ�ȡ����Ŀ������ļ�������ļ�������Ҫ���͵Ĺ̼���
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

void demo_zlg217_core_single_application_entry (void)
{
    AM_DBG_INFO("application : am217_core single application start up successful!\r\n");

    while(1) {
        AM_DBG_INFO("application : am217_core single application running\r\n");
        am_led_toggle(0);
        am_mdelay(1000);
    }
}

/* end of file */
