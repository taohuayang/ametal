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
 * \brief bootloader ���̣���demo����Ϊbootloader����demo��Ҫ���kboot����λ��KinetiesFlashTools��
 *
 * - �������裨������������
 *   1. eclipse���̴�demo_stm32f103rbt6_core_bootloader.ld�ļ�����:
 *
 *       FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 28K   // single
 *
 *      ������, ��������flash���á�
 *
 *      keil���̴�demo_stm32f103rbt6_core_bootloader.sct�ļ�������λ�������ã�������������
 *
 *   2. ����λ��KinetiesFlashTools : ��port set����ѡ��uart;
 *   3. ���ر����򵽿���������
 *   4. �����λ����connect�������ȷ���ӣ����д�ӡ��Ϣ��ʾ
 *   5. ��Updateѡ����
 *   6. ѡ�������Ĺ̼���������Ŀ���ַ��Ҳ���ǹ̼���Ŀ���flash�д�ŵ���ʼ��ַ
 *   7. ���update�������鿴��ӡ��Ϣ�Ƿ������ɹ�
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-18  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_led.h"
#include "stm32f103rbt6_pin.h"
#include "am_boot.h"
#include "am_boot_mem_flash.h"
#include "am_boot_kft.h"
#include "am_boot_enter_check_key.h"
#include "am_baudrate_detect.h"
#include "demo_boot_entries.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "am_bootconf_stm32f103rbt6.h"

#define RAM_START_ADDR 0x20000000
#define RAM_SIZE       20 * 1024

void demo_stm32f103rbt6_core_bootloader_kft_entry (void)
{
    am_uart_handle_t             uart_handle;
    am_boot_flash_handle_t       flash_handle;
    am_boot_mem_handle_t         memory_handle;
    am_boot_enter_check_handle_t enter_check_handle;
    am_baudrate_detect_handle_t  baudrate_detect_handle;

    flash_handle  = am_stm32f103rbt6_boot_kft_flash_inst_init();
    memory_handle = am_boot_mem_flash_init(flash_handle);

    am_stm32f103rbt6_boot_kft_inst_init();

    enter_check_handle = am_boot_enter_check_key_init(
        PIOC_7, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    if (am_boot_enter_check(enter_check_handle) && am_boot_app_is_ready()) {
        am_boot_go_application();
    }

    baudrate_detect_handle = am_stm32f103rbt6_baudrate_detect_inst_init();

    int ret;
    uint32_t baund;
    while(1) {
       ret = am_baudrate_get(baudrate_detect_handle, &baund);
       if (ret == AM_OK) {
           if(baund <= 7200 && baund > 3000) {
               baund = 4800;
           } else if(baund <=384000  && baund > 192000) {
               baund = 256000;
           }
           break;
       }
    }

    am_stm32f103rbt6_baudrate_detect_inst_deinit(baudrate_detect_handle);
    /* ���ڳ�ʼ��Ӧ���ڻ�ȡ������֮�� */
    uart_handle = am_stm32f103rbt6_usart1_inst_init();

    demo_std_bootloader_kft_entry(flash_handle,
                                  memory_handle,
                                  baund,
                                  uart_handle,
                                  RAM_START_ADDR,
                                  RAM_SIZE);
}

/* end of file */
