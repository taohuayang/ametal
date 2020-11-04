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
 * \brief UART ��ѯ��ʽ�½��շ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "STD-UART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \note�� ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *       ���磺AM_DBG_INFO()��
 *
 * \par Դ����
 * \snippet demo_std_uart_polling.c src_std_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.01 17-05-04  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_uart_polling
 * \copydoc demo_std_uart_polling.c
 */

/** [src_std_uart_polling] */
#include "ametal.h"
#include "am_uart.h"

/** \brief ��Ҫ���͵��ַ��� */
static const uint8_t __ch[] = {"STD-UART test in polling mode:\r\n"};

/**
 * \brief �������
 */
void demo_std_uart_polling_entry (am_uart_handle_t handle)
{
    uint8_t uart1_buf[5];    /* ���ݻ����� */

    am_uart_poll_send(handle, __ch, sizeof(__ch));

    while (1) {
        /* �����ַ� */
        am_uart_poll_receive(handle, uart1_buf, 1);

        /* ���͸ոս��յ��ַ� */
        am_uart_poll_send(handle, uart1_buf, 1);

    }
}
/** [src_std_uart_polling] */

/* end of file */
