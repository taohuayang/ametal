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
 * \brief MicroPort RX8025T ���̣�ͨ�� RX8025T оƬʵ��
 *        RTC�����ӵĹ��ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort RX8025T ������ӵ� aml165-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ���ڽ�ÿһ���ʱ����Ϣ��ӡ������
 *   2. ����ʱ��һ���ͻ�ִ�����ӻص�������
 *   3. ÿ�ֻ�ʵ��ʱ������жϵĻص�������
 *   4. ÿ�����оͻ�ִ�ж�ʱ���жϵĻص�������
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_3 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml165_core_microport_rx8025t.c src_aml165_core_microport_rx8025t
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-14  vir, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_microport_rx8025t
 * \copydoc demo_aml165_core_microport_rx8025t.c
 */

/** [src_aml165_core_microport_rx8025t] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_microport_rx8025t_entry (void)
{
    AM_DBG_INFO("demo aml165_core microport rx8025t!\r\n");

    demo_std_rtc_entry(am_microport_rx8025t_rtc_inst_init());
}
/** [src_aml165_core_microport_rx8025t] */

/* end of file */
