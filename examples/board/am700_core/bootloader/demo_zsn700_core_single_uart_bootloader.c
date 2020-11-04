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
 * \brief bootloader �������̡�
 *
 * - �������裨������������
 *   1. eclipse���̴�demo_am700_core_bootloader.ld�ļ����ɸ��ݾ����boot�����С���ò��������£�
 *          FLASH  (rx) : ORIGIN = 0x00000000, LENGTH = 0X6600  //�������Ϊ26.5K
 *
 *      keil���̴�demo_am700_core_bootloader.sct�ļ���������ʾ�޸�boot�����С�����£�
 *          #define     ALL_SIZE      0X00006600     //ֻ�ɸ��Ĵ˲���
 *
 *      �����湤�������ļ�֮�⣬��Ҫ����/user_config/../am_bootconf_zsn700_single.c�ļ��ڵ���Ϣ�ṹ������
 *
 *      Ĭ��flash����������£�
 *      ���򻮷�:    |----------|----------------------------|
 *      ����:        bootloader         application
 *      ��С:           25.5K                 114k
 *
 *   2. ���ӿ��������λ���������֣�����������Ϊ115200��������ʹ�ô���1��
 *   
 *   3. �����������ر����̱���ĳ��򣬸�λ���������С�
 *
 *   4. �������ִ�ӡ5�뵹��ʱ����5����ͨ���������ַ����������ݸ������壬������׼�����չ̼���
 *
 *   5. ������õĹ̼�ͨ���������ַ��͸������壨����ڷ��͵Ĺ��̳��������½��չ̼�����λ�����·��ͣ���
 *
 *   6. ���ճɹ���������ת��Ӧ�ó���ִ�У����ڴ�ӡ��Ӧ�ó�����Ϣ��LED����˸��
 *
 * \note
 *    �̼�����
 *
 *    ����ametal/tools/bootloader/�̼�У��/ �ļ��У�Ŀ¼����һ��bin_chek_sum.bin��ִ���ļ���
 *    �����Ե�Ӧ�ù��̱������bin�ļ���������bin_chek_sum.binͬһ��Ŀ¼�£�
 *    �ڸ�Ŀ¼�´�cmd�������������������룺
 *         bin_chek_sum.exe  xxx.bin��������bin�ļ����ƣ� xxx.bin��Ŀ������ļ�����������ȡ��
 *
 *    ִ������������һ�����û��Լ�ȡ����Ŀ������ļ�������ļ�������Ҫ���͵Ĺ̼���
 *    
 *
 * \internal
 * \par Modification History
 * - 1.00 19-6-06  yrh, first implementation
 * \endinternal
 */


#include "am_uart.h"
#include "am_vdebug.h"
#include "am_boot_firmware.h"
#include "am_boot_flash.h"
#include "am_bootconf_zsn700.h"
#include "am_zsn700_inst_init.h"
#include "am_boot_enter_check_uart.h"
#include "am_boot_firmware_recv_uart.h"
#include "demo_boot_entries.h"

void demo_zsn700_core_single_bootloader_uart_entry (void)
{
    am_uart_handle_t           uart_handle;
    am_boot_firmware_handle_t  firmware_handle;

    /* bootloader ��׼�ӿڳ�ʼ��  */
    am_zsn700_boot_single_inst_init();

    firmware_handle = am_zsn700_boot_single_firmware_flash_inst_init();

    uart_handle = am_zsn700_uart0_inst_init();
    am_debug_init(uart_handle, 115200);

    //check_handle = am_boot_enter_check_key_init(PIOC_7, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    demo_std_single_bootloader_entry(
        am_boot_firwa_recv_uart_init(firmware_handle, uart_handle),
        am_boot_enter_check_uart_init(uart_handle));
}

/* end of file */
