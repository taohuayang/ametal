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
 * 1. ��������PC����USB���������ӡ�
 * 2. PC���ô�������(xcom)�����ӷ������ݣ���������յ����ݣ���ش���recv success��.
 *
 * \par Դ����
 * \snippet demo_zlg237_core_usbd_printer.c src_zlg237_core_usbd_printer
 *
 * \internal
 * \par Modification History
 * - 1.00 19-05-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_demo_zlg237_core_usbd_printer
 * \copydoc demo_zlg237_core_usbd_printer.c
 */

/** [src_demo_zlg237_core_usbd_printer] */

#include "demo_zlg_entries.h"
#include "am_zlg237_inst_init.h"
#include "demo_am237_core_entries.h"

void demo_zlg237_usbd_vcom_entry (void)
{

    AM_DBG_INFO("demo zlg237_core usbd vcom!\r\n");

    /* usb��ӡ��ʵ����ʼ��*/
    am_usbd_cdc_vcom_handle handle = am_zlg237_usbd_vcom_inst_init();

    demo_usbd_vcom_entry(handle);
}

/** [src_demo_zlg237_core_usbd_printer] */

/* end of file */
