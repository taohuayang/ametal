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
 * \brief SD������д����
 *
 * - �������裺
 *   1. ��SD�����뿨��
 *
 * - ʵ������
 *   1. ����SD��ָ���飻
 *   2. д������ݣ�
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_hc32f460_core_std_sdcard.c src_hc32f460_core_std_sdcard
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-14  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_core_std_sdcard
 * \copydoc demo_hc32f460_core_std_sdcard.c
 */

/** [src_hc32f460_core_std_sdcard] */
#include "ametal.h"
#include "am_sdio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_sdcard.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_sdcard_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core std sdcard!\r\n");

    demo_std_sdcard_entry(am_sdcard1_inst_init());
}
/** [src_hc32f460_core_std_sdcard] */

/* end of file */
