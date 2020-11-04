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
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� "HW example---UART test in polling mode:"��
 *   2. ָ������������յ����ַ�����
 *
 * \par Դ����
 * \snippet demo_mm32_hw_uart_polling.c src_mm32_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_mm32_hw_uart_polling
 * \copydoc demo_mm32_hw_uart_polling.c
 */

/** [src_mm32_hw_uart_polling] */
#include "ametal.h"
//#include "am_mm32l073.h"
#include "hw/amhw_mm32_uart.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE     (115200)              /** <\brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static const uint8_t uart_hw_str[] =
                                {"HW example---UART test in polling mode:\r\n"};

/**
 * \brief UART HW ��ѯ�շ���ʼ��
 */
static void uart_polling_init (amhw_mm32_uart_t *p_hw_uart, uint32_t clk_rate)
{

    /* ���ô��ڲ����� */
    amhw_mm32_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    amhw_mm32_uart_stop_bit_sel(p_hw_uart, AMHW_MM32_UART_STOP_1BIT);
    amhw_mm32_uart_data_length(p_hw_uart, AMHW_MM32_UART_DATA_8BIT);
    amhw_mm32_uart_parity_bit_sel(p_hw_uart,  AMHW_MM32_UART_PARITY_NO);

    /* ʹ�ܴ��� */
    amhw_mm32_uart_rx_enable(p_hw_uart,AM_TRUE);
    amhw_mm32_uart_tx_enable(p_hw_uart,AM_TRUE);
    amhw_mm32_uart_enable(p_hw_uart);
}

/**
 * \brief �������
 */
void demo_mm32_hw_uart_polling_entry (amhw_mm32_uart_t *p_hw_uart,
                                     uint32_t         clk_rate)
{

    /* ���ݻ����� */
    uint8_t buf_src[256];

    /* UART��ѯ��ʼ�� */
    uart_polling_init(p_hw_uart, clk_rate);

    amhw_mm32_uart_poll_send(p_hw_uart, uart_hw_str, sizeof(uart_hw_str));

    while (1) {

        /* �����ַ� */
        amhw_mm32_uart_poll_receive(p_hw_uart, buf_src, 1);

        /* ���͸ոս��յ��ַ� */
        amhw_mm32_uart_poll_send(p_hw_uart, buf_src, 1);
    }
}
/** [src_mm32l073_hw_uart_polling] */

/* end of file */
