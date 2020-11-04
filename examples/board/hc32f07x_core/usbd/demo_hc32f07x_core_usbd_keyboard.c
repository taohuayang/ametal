/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB keyboard ����
 *
 * - ʵ������
 * 1.���ڰ�����Դ���ޣ����İ���ֻ��һ���������ã����뽫���İ��ϵ�res/key����ñ��key�̽ӣ�������������Ч��
 * 2.��USBһ�˽Ӱ��ӣ���һ�˽�PC����
 * 3.¼����󣬵ȴ��ڴ�ӡ"usb device init successful."�󣬰������£���ʾ��Сд���������£���ʱ������LED0
 *   ����ͬʱ�����û�������֤��
 * 4.����ɸ�����ͬ�ļ�ֵ�����ԣ����̵ļ�ֵ����"am_usbd_keyboard.h"�л�ȡ��
 *
 * \par Դ����
 * \snippet demo_hc32f07x_core_usbd_keyboard.c src_hc32f07x_core_usbd_keyboard
 *
 * \internal
 * \par Modification History
 * - 1.00 19-05-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_demo_hc32f07x_core_usbd_keyboard
 * \copydoc demo_hc32f07x_core_usbd_keyboard.c
 */

/** [src_demo_hc32f07x_core_usbd_keyboard] */
#include "am_usbd_keyboard.h"
#include "demo_hc32f07x_entries.h"
#include "am_hc32f07x_inst_init.h"
#include "demo_amf07x_core_entries.h"
#include "am_led.h"
#include "string.h"
#include "am_input.h"
#include "am_delay.h"
#include "demo_std_entries.h"
#include "demo_amf07x_core_entries.h"
#include "am_board.h"

void demo_hc32f07x_usbd_keyboard_entry (void)
{

    AM_DBG_INFO("demo hc32f07x_core usbd keyboard!\r\n");
	
    /* usb��ӡ��ʵ����ʼ��*/
    am_usbd_keyboard_handle handle = am_hc32f07x_usbd_keyboard_inst_init();

    demo_usbd_keyboard_entry(handle);
}

/** [src_demo_hc32f07x_core_usbd_keyboard] */

/* end of file */
