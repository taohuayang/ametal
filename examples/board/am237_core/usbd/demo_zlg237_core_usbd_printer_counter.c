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
 * \brief USB printer_counter ����
 *
 * - ʵ������
 * 1.��USB����˵����PC����
 * 2.��������¼�����̣��ȴ�3��(��������3����ʱ��Ϊ��ģ��USB�γ�����)��3���pc������ʾ��װ������
 *   ����Ĭ�ϰ�װwindows ͨ�ô�ӡ����������ϸ�ɿ�������װ˵���ĵ�������û���Ҫ���Լ����������������и��¡�
 * 3.�ڵ��������½�һ��txt�ļ��������ַ���,֮�����ļ���ӡ�����ڴ����п��Կ����ļ����ݣ�������ʾ�ôδ���������
 *   ��������ʱ�䡣
 *
 * \par Դ����
 * \snippet demo_zlg237_core_usbd_printer_counter.c src_zlg237_core_usbd_printer_counter
 *
 * \internal
 * \par Modification History
 * - 1.00 19-05-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_demo_zlg237_core_usbd_printer_counter
 * \copydoc demo_zlg237_core_usbd_printer_counter.c
 */

/** [src_demo_zlg237_core_usbd_printer_counter] */

#include "demo_zlg_entries.h"
#include "am_zlg237_inst_init.h"
#include "demo_am237_core_entries.h"

void demo_zlg237_usbd_printer_counter_entry (void)
{

    AM_DBG_INFO("demo zlg237_core usbd printer counter!\r\n");

    /* usb��ӡ��ʵ����ʼ��*/
    am_usbd_printer_handle handle = am_zlg237_usbd_printer_inst_init();

    demo_usbd_printer_counter_entry(handle);
}

/** [src_demo_zlg237_core_usbd_printer_counter] */

/* end of file */
