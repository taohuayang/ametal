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
 * \brief UART �����ʼ�����̣�ͨ����׼�ӿ�ʵ��(�����̲�����֧�ַ�Χ 1200~12800)
 *
 * - ʵ������
 *   1. ������� "uart connect success"��
 *   2. ����������յ����ַ�����
 *
 * \note�� ����޷���⵽��λ���Ĳ����ʣ���һֱѭ����⣬��������Ҳ�������κλ�Ӧ
 *
 * \par Դ����
 * \snippet demo_amks16z_core_uart_auto_baudrate.c src_amks16z_core_uart_auto_baudrate
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-10  yrh, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_uart_auto_baudrate
 * \copydoc demo_amks16z_core_uart_auto_baudrate.c
 */

/** [src_amks16z_core_uart_auto_baudrate] */
#include "ametal.h"
#include "am_uart.h"
#include "am_baudrate_detect.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "demo_components_entries.h"

static const uint8_t __ch[] = {"uart connect success\r\n"};

/**
 * \brief ���ڲ����ʼ���������
 */
void demo_amks16z_core_uart_auto_baudrate_entry (void)
{
    am_uart_handle_t uart_handle;
    am_baudrate_detect_handle_t baudrate_hande;

    uint32_t baudrate;
    baudrate_hande = am_kl26_baudrate_detect_inst_init();

    /** \brief ��Ҫ���͵��ַ��� */

    while(AM_OK != am_baudrate_get(baudrate_hande, &baudrate)) {
    }
    /* �����ʻ�ȡ�ɹ���Ҫ���ʼ�����������³�ʼ������ */
    am_kl26_baudrate_detect_inst_deinit(baudrate_hande);

    /* UART��ʼ�� ,ֻ���ô���2����ȡ�����ʻ�ȡ���Ǵ���2�Ľ�������*/
    uart_handle = am_kl26_uart2_inst_init();

    am_uart_ioctl(uart_handle, AM_UART_BAUD_SET, (void *)baudrate);

    am_uart_poll_send(uart_handle,
                      __ch,
                      sizeof(__ch));

    uint8_t uart1_buf[5];    /* ���ݻ����� */

    while(1) {
        /* �����ַ� */
        am_uart_poll_receive(uart_handle, uart1_buf, 1);

        /* ���͸ոս��յ��ַ� */
        am_uart_poll_send(uart_handle, uart1_buf, 1);
    }
}

/** [src_amks16z_core_uart_auto_baudrate] */

/* end of file */
