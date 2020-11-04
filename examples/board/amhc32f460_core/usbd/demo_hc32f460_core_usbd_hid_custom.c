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
 * \brief USB_hid_custom���̣�ͨ��driver��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. ��usbͨ�������ļ�����������user_config\am_hwconf_usrcfg\am_usb_common_config.h
 *   #define USB_DEVICE_CLASS_HID_CUSTOM   1
 *   //#define USB_DEVICE_CLASS_MSC_ON     1
 *   //#define USB_DEVICE_CLASS_HID_MOUSE  1
 *   2. ��USB�����ϵ��Ժ����س���
 *
 *
 * - ʵ������
 *   1.�ϵ�󣬿���PC�豸�������鿴��һ���µ�hid deviceʶ����
 *   2.ʹ�����bus hound���ҵ�����豸�ڵ㣬˫������ڵ㣬��������ͽ���
 *   3.�ڸý���ͨ��OUT�˵����豸�������ݿ��Կ���LED1-LED4��״̬
 *     ���� 0x01 0x00 LED1��
 *     ���� 0x01 0x01 LED1����
 *     ���� 0x02 0x00 LED2��
 *     ���� 0x02 0x01 LED2����
 *     ���� 0x03 0x00 LED3��
 *     ���� 0x03 0x01 LED3����
 *     ���� 0x04 0x00 LED4��
 *     ���� 0x04 0x01 LED4����
 *
 * \par Դ����
 * \snippet demo_hc32f460_core_usbd_hid_custom.c src_hc32f460_core_usbd_hid_custom
 *
 * \internal
 * \par Modification History
 * - 1.00 
 * \endinternal
 */

/**
 * \addtogroup demo_if_demo_hc32f460_core_usbd_hid_custom
 * \copydoc demo_hc32f460_core_usbd_hid_custom.c
 */

/** [src_demo_hc32f460_core_usbd_mouse] */

#include "demo_hc32f460_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"
#include "am_usbd_msc.h"
#include "am_vdebug.h"

extern void demo_usbd_hid_custom_entry (void* p_handle);

void demo_hc32f460_usbd_hid_custom_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core usbd hid custom!\r\n");

    am_usbd_dev_t handle = am_hc32f460_usb_hid_custom_inst_init();

    demo_usbd_hid_custom_entry(&handle);  
}

/** [src_demo_hc32f460_core_usbd_mouse] */

/* end of file */
