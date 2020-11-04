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
 *   1. �� MicroPort RS485 ������ӵ� AM237 �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. �������"MicroPort RS485 Test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *   1. TP8485E Ϊ RS485 ת����оƬ��
 *
 * \par Դ����
 * \snippet demo_microport_rs485.c src_microport_rs485
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_rs485
 * \copydoc demo_microport_rs485.c
 */

/** [src_microport_rs485] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg237_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am237_core_entries.h"

/**
 * \brief MicroPort RS485 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg237_core_microport_rs485_entry (void)
{
    AM_DBG_INFO("demo am237_core microport rs485!\r\n");

    demo_std_uart_rs485_entry(am_microport_rs485_inst_init());

}
/** [src_microport_rs485] */

/* end of file */
