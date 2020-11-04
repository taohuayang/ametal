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
 * \brief zsn603 LED���Գ���
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *
 * - ʵ������
 *   1. ZSN600��LED�ƽ�����˸����ִ�д�������ӡ��Ӧ�Ĵ����ʶ�� ��
 *
 * \par Դ����
 * \snippet demo_zsn603_led_test.c src_zsn603_led_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn603_led_test
 * \copydoc demo_zsn603_led_test.c
 */

/** [src_zsn603_led_test] */
#include "zsn603.h"
#include "ametal.h"
#include "am_vdebug.h"
/* ZSN603  LED���Գ��� */
void demo_zsn603_led_test_entry (zsn603_handle_t handle)
{
    unsigned char ret = 0;
    ret = zsn603_control_led (handle,  ZSN603_CONTROL_LED_ON);
    if(ret == 0){
        am_kprintf("led on !\r\n");
    }else{
        am_kprintf("led control beacuse error 0x%02x", ret);
    }
    ret = zsn603_control_led (handle,  ZSN603_CONTROL_LED_OFF);
    if(ret == 0){
        am_kprintf("led off !\r\n");
    }else{
        am_kprintf("led control beacuse error 0x%02x", ret);
    }
}
/** [src_zsn603_led_test] */

/* end of file */
