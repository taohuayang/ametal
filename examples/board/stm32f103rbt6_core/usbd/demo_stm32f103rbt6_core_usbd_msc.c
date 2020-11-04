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
 * \brief USBģ��U�����̣�ͨ��driver��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. ��USB�����ϵ��Ժ����س���
 *   2. �ڵ����ϻ���ʾ��һ���̷���
 *
 * - ʵ������
 *   1. ���̷������Կ���������һ��README.TXT�ļ���
 *   2. ������U���������϶��ļ�,���ڻ���ʾ���϶��ļ�����Ϣ��
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_core_usbd_msc.c src_stm32f103rbt6_core_usbd_msc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-05-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_demo_stm32f103rbt6_core_usbd_msc
 * \copydoc demo_stm32f103rbt6_core_usbd_msc.c
 */

/** [src_demo_stm32f103rbt6_core_usbd_msc] */

#include "demo_stm32f103rbt6_entries.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_stm32f103rbt6_core_entries.h"

void demo_stm32f103rbt6_usbd_msc_entry (void)
{

    AM_DBG_INFO("demo stm32f103rbt6_core usbd msc!\r\n");

    /* usb U��ʵ����ʼ��*/
    am_usbd_msc_handle handle = am_stm32f103rbt6_usb_msc_inst_init();

    demo_usbd_msc_entry(handle);
}

/** [src_demo_stm32f103rbt6_core_usbd_msc] */

/* end of file */
