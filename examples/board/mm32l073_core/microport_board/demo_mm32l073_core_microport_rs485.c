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
 * \brief MicroPort RS485 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort RS485 ������ӵ� AM116-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. �������"MicroPort RS485 Test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *   1. TP8485E Ϊ RS485 ת����оƬ��
 *   2. ����ʹ�� UART1���� DEBUG ����ʹ�ô�����ͬ��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_microport_rs485.c src_mm32l073_core_microport_rs485
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_microport_rs485
 * \copydoc demo_mm32l073_core_microport_rs485.c
 */

/** [src_mm32l073_core_microport_rs485] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_microport_rs485_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core microport rs485!\r\n");

    demo_std_uart_rs485_entry(am_microport_rs485_inst_init());
}
/** [src_mm32l073_core_microport_rs485] */

/* end of file */
