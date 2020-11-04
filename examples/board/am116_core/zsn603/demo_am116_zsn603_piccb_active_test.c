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
 * \brief zsn603 B�࿨���Գ���
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *   2. ��B�࿨���������߸�Ӧ����
 *
 * - ʵ������
 *   1. MCU�����ӡ��B�࿨�������Ϣ
 *
 * \par Դ����
 * \snippet demo_am116_zsn603_piccb_test.c src_am116_zsn603_piccb_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_am116_if_zsn603_piccb_test
 * \copydoc demo_am116_zsn603_piccb_test.c
 */

/** [src_am116_zsn603_piccb_test] */

#include "zsn603.h"
#include "demo_components_entries.h"
#include "demo_am116_core_entries.h"
#include "am_hwconf_zsn603_uart.h"

void demo_am116_zsn603_piccb_test_entry()
{
    zsn603_handle_t  handle = am_zsn603_uart_inst_init();
    demo_zsn603_piccb_active_test_entry(handle);
}
/** [src_am116_zsn603_piccb_test] */

/* end of file */
