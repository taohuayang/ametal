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
 * \snippet demo_zsn700_hw_uart_polling.c src_zsn700_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zsn700_hw_uart_polling
 * \copydoc demo_zsn700_hw_uart_polling.c
 */

/** [src_zsn700_hw_uart_polling] */
#include "ametal.h"
#include "hw/amhw_zsn700_uart.h"

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
static void uart_polling_init (amhw_zsn700_uart_t *p_hw_uart, uint32_t clk_rate)
{
    /* ����ģʽ����  */
    amhw_zsn700_uart_mode_sel(p_hw_uart, AMHW_ZSN700_UART_WORK_MODE_1);

    /* ��Ƶϵ������  */
    amhw_zsn700_uart_clk_div_sel(p_hw_uart, AMHW_ZSN700_UART_CLK_DIV_MODE13_8);

    /* �ȴ����Ϳ���� */
    while (amhw_zsn700_uart_flag_check(p_hw_uart,
                                       AMHW_ZSN700_UART_FLAG_TX_EMPTY) ==
                                       AM_FALSE);

    /* ֹͣλ���� */
    amhw_zsn700_uart_stop_bit_sel(p_hw_uart  , AMHW_ZSN700_UART_STOP_1_0_BIT);

    /* У������ */
    amhw_zsn700_uart_parity_bit_sel(p_hw_uart, AMHW_ZSN700_UART_PARITY_NO);

    /* ���������� */
    amhw_zsn700_uart_baudrate_set( p_hw_uart, clk_rate, UART_BAUDRATE);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsn700_uart_enable(p_hw_uart,AMHW_ZSN700_UART_RX);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_uart_polling_entry (void     *p_hw_uart,
                                        uint32_t  clk_rate)
{

    /* ���ݻ����� */
    uint8_t buf_src[256];
    amhw_zsn700_uart_t * p_uart = (amhw_zsn700_uart_t * )p_hw_uart;

    /* UART��ѯ��ʼ�� */
    uart_polling_init(p_uart, clk_rate);

    amhw_zsn700_uart_poll_send(p_uart, uart_hw_str, sizeof(uart_hw_str));

    while (1) {

        /* �����ַ� */
        amhw_zsn700_uart_poll_receive(p_uart, buf_src, 1);

        /* ���͸ոս��յ��ַ� */
        amhw_zsn700_uart_poll_send(p_uart, buf_src, 1);
    }
}
/** [src_zsn700116_hw_uart_polling] */

/* end of file */
