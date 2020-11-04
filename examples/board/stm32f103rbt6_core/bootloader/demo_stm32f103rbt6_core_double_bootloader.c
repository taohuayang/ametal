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
 * \brief bootloader ˫������(�ȿ��Ա�������Ҳ������Ӧ�ó���������)��
 *
 * - �������裨������������
 *   1. eclipse���̴�demo_stm32f103rbt6_core_bootloader.ld�ļ�����:
 *
 *       FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 29K  //double
 *
 *      ������, ��������flash���á�
 *
 *      keil���̴�demo_stm32f103rbt6_core_bootloader.sct�ļ�����˫�������ã�������������
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
 * - �������裨Ӧ������������
 *
 *   Ӧ����������ǰ���������Ѿ�ͨ�����������ķ�ʽ��˫��Ӧ�ó���̼����ص��˿������У����ɹ����С�
 *
 *   1. �����������0x5a 0xa6 0x11 0x66 0x0d����������16���Ƶ���ʽ���ͣ�ע�����ô������֣�
 *   
 *   2. �ȴ��������ִ�ӡ�Ѿ�׼�����չ̼���Ϣ�󣬷��͹̼���
 *
 *   3. �̼����ͳɹ���������������5����ʱ���ȥ�µ�Ӧ�ó�����ʱʱ���ڲ�Ҫ�����κ����ݣ���
 *
 *
 *
 * \note
 *    �̼�����
 *
 *    ����ametal/tools/bootloader/�̼�У��/ �ļ��У�Ŀ¼����һ��bin_chek_sum.bin��ִ���ļ���
 *    �����Ե�Ӧ�ù��̱������bin�ļ���������bin_chek_sum.binͬһ��Ŀ¼�£�
 *    �ڸ�Ŀ¼�´�cmd�������������������룺
 *         bin_chek_sum.bin  xxx.bin��������bin�ļ����ƣ� xxx.bin��Ŀ������ļ�����������ȡ��
 *
 *    ִ������������һ�����û��Լ�ȡ����Ŀ������ļ�������ļ�������Ҫ���͵Ĺ̼���
 *    
 *��    
 * \internal
 * \par Modification History
 * - 1.00 19-6-06  yrh, first implementation
 * \endinternal
 */


#include "am_uart.h"
#include "am_vdebug.h"
#include "am_boot_firmware.h"
#include "am_boot_flash.h"
#include "demo_boot_entries.h"
#include "am_bootconf_stm32f103rbt6.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "am_boot_enter_check_uart.h"
#include "am_boot_firmware_recv_uart.h"

void demo_stm32f103rbt6_core_double_bootloader_uart_entry (void)
{
    am_uart_handle_t           uart_handle;
    am_boot_firmware_handle_t  firmware_handle;

    /* bootloader ��׼�ӿڳ�ʼ��  */
    am_stm32f103rbt6_boot_double_inst_init();

    firmware_handle = am_stm32f103rbt6_boot_double_firmware_flash_inst_init();

    uart_handle = am_stm32f103rbt6_usart1_inst_init();
    am_debug_init(uart_handle, 115200);
    //check_handle = am_boot_enter_check_key_init(PIOC_7, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    demo_std_double_bootloader_entry(
        am_boot_firwa_recv_uart_init(firmware_handle, uart_handle),
        am_boot_enter_check_uart_init(uart_handle),
        am_stm32f103rbt6_boot_msg_flag_inst_init());
}

/* end of file */
