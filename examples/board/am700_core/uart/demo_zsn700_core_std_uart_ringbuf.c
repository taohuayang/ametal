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
 * \brief UART ���λ��������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "UART interrupt mode(Add ring buffer) test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. �� PIOA_2 �������� PC ���ڵ� RXD��PIOA_3 �������� PC ���ڵ� TXD��
 *    3. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zsn700_std_uart_ringbuf.c src_zsn700_std_uart_ringbuf
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_std_uart_ringbuf
 * \copydoc demo_zsn700_std_uart_ringbuf.c
 */

/** [src_zsn700_std_uart_ringbuf] */
#include "ametal.h"
#include "am_zsn700_inst_init.h"
#include "demo_std_entries.h"
#include "am_vdebug.h"
#include "demo_am700_core_entries.h"
/**
 * \brief �������
 */
void demo_zsn700_core_std_uart_ringbuf_entry (void)
{
    AM_DBG_INFO("demo am700_core std uart ringbuf!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    demo_std_uart_ringbuf_entry(am_zsn700_uart0_inst_init());
}
/** [src_zsn700_std_uart_ringbuf] */

/* end of file */
