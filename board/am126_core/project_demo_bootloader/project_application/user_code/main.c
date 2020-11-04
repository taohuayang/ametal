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
 * \brief AM116 bootloader Ӧ�ù̼�����
 *
 * - �������裺
 *    �ο� {sdk}\ametal\documents\am116_coreĿ¼�� bootloader �����ֲᡣ
 *
 * \note
 *    ������Ϊ�̼������޷�ֱ��������
 *
 * \internal
 * \par Modification history
 * - 1.00 20-09-27  fzb, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_am116_core_entries.h"

/**
 * \brief AMetal Ӧ�ó������
 */
int am_main (void)
{
    demo_am116_core_single_application_entry();

    while (1) {

    }
}
