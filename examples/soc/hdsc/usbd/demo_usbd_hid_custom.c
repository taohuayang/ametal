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
 * \brief USB hid custom���̣�ͨ��driver��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. 
 *   2. 
 *
 * - ʵ������
 *   1. 
 *   2. 
 *
 * \note
 *
 *
 *
 * \par Դ����
 * \snippet demo_usbd_msc.c src_usbd_msc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-01-15  adw, first implementation
 * \endinternal
 */
/**
 * \brief �������
 */
#include "demo_hc32f460_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"
#include "am_vdebug.h"
#include "hc32f460_pin.h"
#include "hc32f460_periph_map.h"


/**
 * \brief �������
 */
void demo_usbd_hid_custom_entry (void* p_handle)
{
    AM_DBG_INFO("wait for data from out endponit\r\n");
    while (1) {
    }  
}
/**
 * \addtogroup demo_if_usbd_msc
 * \copydoc demo_usbd_msc.c
 */

/** [src_usbd_msc] */

/* end of file */
