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
 * \brief bootloader ���̣���demo����ΪӦ�ó���̼���
 *
 * - ��������:
 *
 *   1. eclipse���̴�demo_amf17x_core_application.ld�ļ���������Ӧ�ó��������ʼ��ַ�����£�
 *           FLASH (rx)  : ORIGIN = 0x00006800, LENGTH = 51K //Ӧ�ó��������ʼ��ַ��Ӧ����0x6A00
 *
 *      keil���̴�demo_amf17x_core_application.sct�ļ���������ʾ�޸�boot�����С�����£�
 *          #define     ALL_START    0X00006800    //�����鳬��0x6A00
 *          #define     ALL_SIZE     0X0000CC00    //����ʵ��������ã����鱾������С��Ӧ������Сһ��
 *
 *      �����湤�������ļ�֮�⣬��Ҫ����/user_config/../am_appconf_double_hc32f17x.c�ļ��ڵ���Ϣ�ṹ������
 *
 *      Ĭ��flash����������£�
 *      ���򻮷�:    |------------|-------|-----------------|-------------------|
 *      ����:        bootloader    flag      application        save_flie
 *      ��С:         25.5k        0.5k          51k             51k
 *
 *   2.���빤��
 *   3.�̼������ο�����note��ʾ
 *6
 * - ��������
 *   1. LED����˸������ѭ����ӡ��
 *   2. �ȴ��û��������������Ӧ���������̼���
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
#include "am_appconf_double_hc32f17x.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_boot_enter_check_uart_cmd.h"
#include "am_boot_firmware_recv_uart.h"
#include "am_boot_msg.h"
#include "am_boot_firmware.h"
#include "am_hc32f17x_inst_init.h"
#include "demo_boot_entries.h"

void demo_hc32f17x_core_double_application_entry (void)
{
    AM_DBG_INFO("application : amf17x_core double application start up successful!\r\n");
    am_mdelay(1);

    am_uart_handle_t             uart_handle;
    am_boot_firmware_handle_t    firmware_handle;
    am_boot_enter_check_handle_t check_handle;
    am_boot_firwa_recv_handle_t  firwa_recv_handle;
    am_boot_msg_handle_t         msg_handle;
    am_hc32_boot_inst_init();
    firmware_handle = am_hc32_boot_firmware_flash_inst_init();

    uart_handle = am_hc32_uart0_inst_init();
    am_debug_init(uart_handle, 115200);
    firwa_recv_handle = am_boot_firwa_recv_uart_init(firmware_handle, uart_handle);
    check_handle = am_boot_enter_check_uart_cmd_init(uart_handle);
    msg_handle = am_hc32_boot_msg_flag_inst_init();

    while(1) {
        /* ��demo��Ҫѭ������ */
        demo_std_double_application_entry(
            firwa_recv_handle,
            check_handle,
            msg_handle);

        am_led_toggle(0);
        am_mdelay(1000);
        AM_DBG_INFO("application : amf17x_core double application running!\r\n");
    }
}

/* end of file */
