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
 * \brief zsn603 LED���Գ���
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *
 * - ʵ������
 *   1. ZSN600��LED�ƽ�����˸����ִ�д�������ӡ��Ӧ�Ĵ����ʶ�� ��
 *
 * \par Դ����
 * \snippet demo_mm32l073_zsn603_led_test.c src_mm32l073_zsn603_led_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_mm32l073_if_zsn603_led_test
 * \copydoc demo_mm32l073_zsn603_led_test.c
 */

/** [src_mm32l073_zsn603_led_test] */

#include "zsn603.h"
#include "demo_components_entries.h"
#include "demo_mm32l073_core_entries.h"
#include "am_hwconf_zsn603_uart.h"

void demo_mm32l073_zsn603_led_test_entry()
{
    zsn603_handle_t  handle = am_zsn603_uart_inst_init();
    demo_zsn603_led_test_entry(handle);
}
/** [src_mm32l073_zsn603_led_test] */

/* end of file */
