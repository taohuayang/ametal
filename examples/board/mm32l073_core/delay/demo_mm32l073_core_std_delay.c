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
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ���� LED0 �� 10Hz ��Ƶ����˸��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_delay.c src_mm32l073_core_std_delay
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-11 ari , first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_std_delay
 * \copydoc demo_mm32l073_core_std_delay.c
 */

/** [src_mm32l073_core_std_delay] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "am_board.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"
/**
 * \brief �������
 */
void demo_mm32l073_core_std_delay_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core std delay!\r\n");

    demo_std_delay_entry(LED0);
}
/** [src_mm32l073_core_std_delay] */

/* end of file */
