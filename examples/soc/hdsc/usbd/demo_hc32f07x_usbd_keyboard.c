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
 * \snippet demo_usbd_keyboard.c src_usbd_keyboard
 *
 * \internal
 * \par Modification History
 * - 1.00 19-2-18  adw, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_usbd_keyboard
 * \copydoc demo_usbd_keyboard.c
 */

/** [src_usbd_keyboard] */
#include "ametal.h"
#include "am_led.h"
#include "string.h"
#include "am_input.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_usbd_keyboard.h"
#include "demo_hc32f07x_entries.h"
#include "demo_std_entries.h"
#include "am_board.h"

#define __KEY0_CODE 82         /*������ֵ�������ڼ��̼�ֵ*/

// �����¼�������
am_local void __input_key_proc (void *p_arg, int key_code, int key_state, int keep_time)
{
    am_usbd_keyboard_handle handle = (am_usbd_keyboard_handle)p_arg;
    uint8_t key_board_val[8] = {0,0,0,0,0,0,0,0};   // ��ֵ���飬��Сһ�㶼Ϊ8

    if (key_code == __KEY0_CODE) {
        /* �жϰ�������״̬�Ƿ񴥷�*/
        if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
            key_board_val[2] = AM_USBD_KEY_CAPS_LOCK;

            /* ���뷢���Σ���һ��Ϊ��ֵ���ڶ�����ռ�ֵ��������Ļ��һֱ����ĸ��ӡ*/
            am_usbd_keyboard_send(handle, key_board_val, 8);

        }else{
            key_board_val[2] = 0;
            am_usbd_keyboard_send(handle, key_board_val, 8);
        }
    }
}

/* ���ջص�����  */
void __g_keybroad_rec_cb(void *p_arg, uint8_t *p_buffer, uint8_t len)
{    
    if ((*p_buffer) & AM_USBD_CAP_LOCK_LIGHT) {   /* ��д���� */
        am_led_on(0);
    } else {
        am_led_off(0);
    }
}

/**
 * \brief �������
 */
void demo_usbd_keyboard_entry (void* p_handle)
{
    am_usbd_keyboard_handle handle = p_handle;
    am_input_key_handler_t  key_handler;
    am_usbd_keyboard_recv_cb_set(handle, __g_keybroad_rec_cb, NULL);
    am_input_key_handler_register(&key_handler, __input_key_proc, handle);
    /* �ȴ�����ö�ٳɹ�  */
    while(handle->is_ready == AM_FALSE);
    am_mdelay(30);

    while(1){
        ;
    }
}
/** [src_usbd_keyboard] */

/* end of file */
