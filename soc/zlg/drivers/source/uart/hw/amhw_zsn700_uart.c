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
 * \brief UART�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */
#include "hw/amhw_zsn700_uart.h"

/**
 * \brief UART���ݷ���(��ѯģʽ)
 */
uint32_t amhw_zsn700_uart_poll_send (amhw_zsn700_uart_t *p_hw_uart,
                                     const uint8_t      *p_txbuf,
                                     uint32_t            nbytes)
{
    uint32_t len = nbytes;

    while (len--) {

         while(amhw_zsn700_uart_flag_check(p_hw_uart,
                                           AMHW_ZSN700_UART_FLAG_TX_EMPTY)==
                                           AM_FALSE);

         amhw_zsn700_uart_data_write(p_hw_uart, (uint8_t)(*p_txbuf++));
    }

    return nbytes;
}

/**
 * \brief UART���ݽ���(��ѯģʽ)
 */
uint32_t amhw_zsn700_uart_poll_receive (amhw_zsn700_uart_t    *p_hw_uart,
                                        uint8_t            *p_rxbuf,
                                        uint32_t            nbytes)
{
    uint32_t len = nbytes;

    while (len--) {

        while(amhw_zsn700_uart_flag_check(p_hw_uart,
                                          AMHW_ZSN700_UART_FLAG_RX_COMPLETE)==
                                          AM_FALSE);

        *p_rxbuf++ = (uint8_t)amhw_zsn700_uart_data_read(p_hw_uart);\

        amhw_zsn700_uart_flag_clr(p_hw_uart,AMHW_ZSN700_UART_FLAG_RX_COMPLETE);
    }

    return nbytes;
}

/**
 * \brief LPUART(Version 0) baud ratio set
 */
int amhw_zsn700_uart_baudrate_set (amhw_zsn700_uart_t *p_hw_uart,
                                   uint32_t            uart_clk,
                                   uint32_t            baud)
{
    uint8_t  clk_bit = 0;
    uint8_t  clk_div = 0;
    uint32_t val_set = 0;
     volatile uint8_t waittime = 0;
    amhw_zsn700_uart_work_mode_t mode = AMHW_ZSN700_UART_WORK_MODE_0;

    /* ȷ����Ч�� clock value */
    if ((uart_clk > 48000000)) {
        uart_clk = 0;

        /* ��ʼ���쳣������������ϵͳʱ��ֵ��Ч */
        return AM_ERROR;
    }

    /* ��ȡʱ��ģʽ */
    mode = amhw_zsn700_uart_mode_get(p_hw_uart);

    /* ģʽ0����£������ʹ̶�Ϊ PCLK/12 */
    if(mode == AMHW_ZSN700_UART_WORK_MODE_0) {

    	baud = (uint32_t)((float)uart_clk / 12.0);

    /* ģʽ2����£������� = ʱ�� / ��Ƶϵ�� */
    } else if (mode == AMHW_ZSN700_UART_WORK_MODE_2) {
        /* ��ȡ��Ƶϵ������λ�������� */
        clk_bit = amhw_zsn700_uart_clk_div_get(p_hw_uart);

        /* ������������Ӧ�ķ�Ƶֵ */
        if(clk_bit == 0) {
            clk_div = 32;
        } else {
            clk_div = 16;
        }

        baud = (uint32_t)((float)uart_clk / (float)clk_div);

    /* ģʽ1/3����£������� = ʱ�� / ����Ƶϵ��*�����ʼĴ����趨ֵ�� */
    } else if ((mode == AMHW_ZSN700_UART_WORK_MODE_1) ||
               (mode == AMHW_ZSN700_UART_WORK_MODE_3) ||
               (mode == AMHW_ZSN700_UART_WORK_MODE_4)) {

        /* ��ȡ��Ƶϵ������λ�������� */
        clk_bit = amhw_zsn700_uart_clk_div_get(p_hw_uart);

        /* ������������Ӧ�ķ�Ƶֵ */
        if(clk_bit == 0) {
            clk_div = 16;
        } else {
            clk_div = 8;
        }

        /* ������벨���ʼĴ�����ֵ */
        val_set = (uint32_t)((float)uart_clk / (float)(baud * clk_div) + 0.5);

        /* �������ֵ��ֱ���������������ֵ */
        if (val_set > 0xFFFF) {
            p_hw_uart->scnt = 0xFFFF;

            /* ���¼���ʵ�ʲ����ʣ�����*/
            baud = (uint32_t)((float)uart_clk / (float)clk_div / (float)0xFFFF);

        /* ������Χ�ڣ�����趨ֵ */
        } else {
            p_hw_uart->scnt = val_set;

        }
    }

    waittime = 100;
    while(waittime--);

    return baud;
}

/* end of file */
