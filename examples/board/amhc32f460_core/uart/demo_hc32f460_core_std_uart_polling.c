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
 * \brief UART ��ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "STD-UART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. �� PIOC_13 �������� PC ���ڵ� TXD��PIOH_2 �������� PC ���ڵ� RXD��
 *    3. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_uart_polling.c src_hc32f460_std_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.01 20-03-11  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_uart_polling
 * \copydoc demo_hc32f460_std_uart_polling.c
 */

/** [src_hc32f460_std_uart_polling] */
#include "ametal.h"
#include "am_board.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_uart_polling_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core std uart polling!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    demo_std_uart_polling_entry(am_hc32f460_uart4_inst_init());
}
/** [src_hc32f460_std_uart_polling] */

/* end of file */
