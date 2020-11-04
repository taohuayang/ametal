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
 * \snippet demo_hk32f103rbt6_drv_flash.c src_hk32f103rbt6_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_drv_flash
 * \copydoc demo_hk32f103rbt6_drv_flash.c
 */

/** [src_hk32f103rbt6_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_hk32f103rbt6_flash.h"
#include "am_hk32f103rbt6.h"
#include "demo_hk32f103rbt6_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

#define FLASH_PAGE           50    /**< \brief ҳ�� */



/**
 * \brief �������
 */
void demo_hk32f103rbt6_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo hk32f103rbt6_core drv flash!\r\n");

    demo_hk32f103rbt6_drv_flash_entry((void *)HK32F103RBT6_FLASH, FLASH_PAGE);
}

/** [src_hk32f103rbt6_drv_flash] */

/* end of file */
