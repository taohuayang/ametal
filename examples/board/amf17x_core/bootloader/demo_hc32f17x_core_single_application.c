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
 *    1. eclipse���̴�demo_amf17x_core_application.ld�ļ���������Ӧ�ó��������ʼ��ַ�����£�
 *           FLASH (rx)  : ORIGIN = 0x00006800, LENGTH = 115K //Ӧ�ó��������ʼ��ַ��Ӧ����0x6A00
 *
 *      keil���̴�demo_amf17x_core_application.sct�ļ���������ʾ�޸�boot�����С�����£�
 *          #define     ALL_START    0X00006800    //�����鳬��0x6A00
 *          #define     ALL_SIZE     0X0000CC00    //����ʵ���������
 *
 *      Ĭ��flash����������£�
 *      ���򻮷�:    |----------|-------------------|
 *      ����:        bootloader     application
 *      ��С:           25.5K           102k
 *
 *   1.���빤��
 *   2.�̼������ο�����note��ʾ
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
 *         bin_chek_sum.exe  xxx.bin��������bin�ļ����ƣ� xxx.bin��Ŀ������ļ�����������ȡ��
 *
 *    ִ������������һ�����û��Լ�ȡ����Ŀ������ļ�������ļ�������Ҫ���͵Ĺ̼���
 *
 * \internal
 * \par Modification History
 * - 1.00 20-8-21  xjy, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_delay.h"

void demo_hc32f17x_core_single_application_entry (void)
{
    AM_DBG_INFO("application : amf17x_core single application start up successful!\r\n");

    while(1) {
        AM_DBG_INFO("application : amf17x_core single application running\r\n");
        am_led_toggle(0);
        am_mdelay(1000);
    }
}

/* end of file */
