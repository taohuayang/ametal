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
 *   3. д��ɹ������ڴ�ӡ 55 ������(1024/4)�� 32bit ʮ���������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zlg237_drv_flash.c src_zlg237_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg237_drv_flash
 * \copydoc demo_zlg237_drv_flash.c
 */

/** [src_zlg237_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_zlg237_flash.h"
#include "am_zlg237.h"
#include "demo_zlg_entries.h"
#include "demo_am237_core_entries.h"

#define FLASH_PAGE           50    /**< \brief ҳ�� */



/**
 * \brief �������
 */
void demo_zlg237_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo am237_core drv flash!\r\n");

    demo_zlg237_drv_flash_entry((void *)ZLG237_FLASH, FLASH_PAGE);
}

/** [src_zlg237_drv_flash] */

/* end of file */
