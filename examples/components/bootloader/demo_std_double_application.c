/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief bootloader ˫��Ӧ�ó�������
 *
 *
 * \par Դ����
 * \snippet demo_std_double_application.c src_std_double_application
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-04 yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_double_application
 * \copydoc demo_std_double_application.c
 */

/** [src_std_double_application] */
#include "am_boot_firmware_recv.h"
#include "am_boot_firmware.h"
#include "am_boot_enter_check.h"
#include "am_boot_msg_flag.h"
#include "am_delay.h"
#include "am_boot.h"
#include "am_vdebug.h"

void demo_std_double_application_entry(am_boot_firwa_recv_handle_t  firwa_recv_handle,
                                       am_boot_enter_check_handle_t check_handle,
                                       am_boot_msg_handle_t         msg_handle)
{
    int ret;
    /* �Ƿ������չ̼� */
    if(am_boot_enter_check(check_handle)) {
        /* ���չ̼� */
        ret = am_boot_firmware_recv(firwa_recv_handle);
        if(ret != AM_OK) {
            am_boot_enter_check_reinit(check_handle);
            am_kprintf("app : firmware receive fail\r\n");
            return;
        } else {
            /* �̼����ճɹ���������Ϣ���µĹ̼��Ѿ�������� */
            am_boot_msg_set(msg_handle, (void *)AM_BOOTLOADER_FLAG_UPDATE);
            /* ϵͳ����ǰ����С�ε���ʱ����ֹĳЩ�Ĵ���û��ִ���� */
            am_mdelay(200);
            /* ϵͳ�����λ */
            am_boot_reset();
        }
    }
}

/** [src_std_double_application] */

/* end of file */
