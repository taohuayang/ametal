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
 * \brief MicroPort DS1302 ���̣�ͨ�� RTC ��׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort DS1302 ������ӵ� aml165-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ���ڽ�ÿһ���ʱ����Ϣ��ӡ������
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_3 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml165_core_microport_ds1302.c src_aml165_core_microport_ds1302
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-16  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_microport_ds1302
 * \copydoc demo_aml165_core_microport_ds1302.c
 */

/** [src_aml165_core_microport_ds1302] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_microport_ds1302_entry (void)
{
    AM_DBG_INFO("demo aml165_core microport ds1302!\r\n");

    demo_std_rtc_entry(am_microport_ds1302_rtc_inst_init());
}
/** [src_aml165_core_microport_ds1302] */

/* end of file */
