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
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. �����������ڴ�ӡ"erase error!"��
 *   2. д��������ڴ�ӡ"program error!"��
 *   3. д��ɹ������ڴ�ӡ 255 ������(1024/4)�� 32bit ʮ���������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *    PIOE_5 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_drv_flash.c src_hc32f460_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 20-06-17  cds, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_drv_flash
 * \copydoc demo_hc32f460_drv_flash.c
 */

/** [src_hc32f460_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_hc32f460_flash.h"
#include "am_hc32f460.h"
#include "demo_hc32f460_entries.h"
#include "demo_hc32f460_core_entries.h"

#define FLASH_SECTOR  60    /**< \brief ���� */

/**
 * \brief �������
 */
void demo_hc32f460_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core drv flash!\r\n");

    demo_hc32f460_drv_flash_entry(HC32F460_EFM, FLASH_SECTOR);
}

/** [src_hc32f460_drv_flash] */

/* end of file */
