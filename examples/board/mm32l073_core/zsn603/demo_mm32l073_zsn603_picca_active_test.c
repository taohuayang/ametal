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
 * \brief zsn603 A�࿨���Գ���
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *   2. ��A�࿨���������߸�Ӧ����
 *
 * - ʵ������
 *   1. MCU�����ӡ��A�࿨�������Ϣ
 *
 * \par Դ����
 * \snippet demo_mm32l073_zsn603_picca_test.c src_mm32l073_zsn603_picca_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_mm32l073_if_zsn603_picca_test
 * \copydoc demo_mm32l073_zsn603_picca_test.c
 */

/** [src_mm32l073_zsn603_picca_test] */

#include "zsn603.h"
#include "demo_components_entries.h"
#include "demo_mm32l073_core_entries.h"
#include "am_hwconf_zsn603_uart.h"

void demo_mm32l073_zsn603_picca_test_entry()
{
    zsn603_handle_t  handle = am_zsn603_uart_inst_init();
    demo_zsn603_picca_active_test_entry(handle);
}
/** [src_mm32l073_zsn603_picca_test] */

/* end of file */
