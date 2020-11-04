/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief LPUART�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-26  zp, first implementation
 * \endinternal
 */
#include "hw/amhw_zlg118_lpuart.h"

/**
 * \brief LPUART���ݷ���(��ѯģʽ)
 */
uint32_t amhw_zlg118_lpuart_poll_send (amhw_zlg118_lpuart_t *p_hw_lpuart,
                                       const uint8_t        *p_txbuf,
                                       uint32_t              nbytes)
{
    uint32_t len = nbytes;

    while (len--) {

         while(amhw_zlg118_lpuart_flag_check(p_hw_lpuart,
                                           AMHW_ZLG118_LPUART_FLAG_TX_EMPTY)==
                                           AM_FALSE);

         amhw_zlg118_lpuart_data_write(p_hw_lpuart, (uint8_t)(*p_txbuf++));
    }

    return nbytes;
}

/**
 * \brief LPUART���ݽ���(��ѯģʽ)
 */
uint32_t amhw_zlg118_lpuart_poll_receive (amhw_zlg118_lpuart_t    *p_hw_lpuart,
                                        uint8_t            *p_rxbuf,
                                        uint32_t            nbytes)
{
    uint32_t len = nbytes;

    while (len--) {

        while(amhw_zlg118_lpuart_flag_check(
                  p_hw_lpuart,
                  AMHW_ZLG118_LPUART_FLAG_RX_COMPLETE)==
                  AM_FALSE);

        *p_rxbuf++ = (uint8_t)amhw_zlg118_lpuart_data_read(p_hw_lpuart);

        amhw_zlg118_lpuart_flag_clr(p_hw_lpuart,
                                    AMHW_ZLG118_LPUART_FLAG_RX_COMPLETE);
    }

    return nbytes;
}

/**
 * \brief LPLPUART(Version 0) baud ratio set
 */
int amhw_zlg118_lpuart_baudrate_set (amhw_zlg118_lpuart_t *p_hw_lpuart,
                                     uint32_t              lpuart_clk,
                                     uint32_t              baud)
{
    uint8_t                        clk_bits = 0;
    uint8_t                        clk_div  = 0;
    uint32_t                       val_set  = 0;
    amhw_zlg118_lpuart_work_mode_t mode     = AMHW_ZLG118_LPUART_WORK_MODE_0;

    /* ȷ����Ч�� clock value */
    if ((lpuart_clk > 48000000)) {
        lpuart_clk = 0;

        /* ��ʼ���쳣������������ϵͳʱ��ֵ��Ч */
        return AM_ERROR;
    }

    /* ��ȡʱ��ģʽ */
    mode = amhw_zlg118_lpuart_mode_get(p_hw_lpuart);

    /* ģʽ0����£������ʹ̶�Ϊ PCLK/12 */
    if(mode == AMHW_ZLG118_LPUART_WORK_MODE_0) {

    	baud = (uint32_t)((float)lpuart_clk / 12.0);

    /* ģʽ2����£������� = ʱ�� / ��Ƶϵ�� */
    } else if (mode == AMHW_ZLG118_LPUART_WORK_MODE_2) {

        /* ��ȡ��Ƶϵ������λ�������� */
        clk_bits = amhw_zlg118_lpuart_clk_div_get(p_hw_lpuart);

        /* ������������Ӧ�ķ�Ƶֵ */
        switch(clk_bits) {
        case 0:
            clk_div = 32;
            break;

        case 1:
            clk_div = 16;
            break;

        case 2:
            clk_div = 8;
            break;
        }

        baud = (uint32_t)((float)lpuart_clk / (float)clk_div);

    /* ģʽ1/3����£������� = ʱ�� / ����Ƶϵ��*�����ʼĴ����趨ֵ�� */
    } else if ((mode == AMHW_ZLG118_LPUART_WORK_MODE_1) ||
               (mode == AMHW_ZLG118_LPUART_WORK_MODE_3) ||
               (mode == AMHW_ZLG118_LPUART_WORK_MODE_4)) {

        /* ��ȡ��Ƶϵ������λ�������� */
        clk_bits = amhw_zlg118_lpuart_clk_div_get(p_hw_lpuart);

        /* ������������Ӧ�ķ�Ƶֵ */
        switch(clk_bits) {
        case 0:
            clk_div = 16;
            break;

        case 1:
            clk_div = 8;
            break;

        case 2:
            clk_div = 4;
            break;
        }

        /* ������벨���ʼĴ�����ֵ */
        val_set = (uint32_t)((float)lpuart_clk / (float)baud / (float)clk_div);

        /* �������ֵ��ֱ���������������ֵ */
        if (val_set > 0xFFFF) {
            p_hw_lpuart->scnt = 0xFFFF;

            /* ���¼���ʵ�ʲ����ʣ�����*/
            baud = (uint32_t)((float)lpuart_clk / (float)clk_div / (float)0xFFFF);

        /* ������Χ�ڣ�����趨ֵ */
        } else {
            p_hw_lpuart->scnt = val_set;

        }
    }

    return baud;
}

/* end of file */
