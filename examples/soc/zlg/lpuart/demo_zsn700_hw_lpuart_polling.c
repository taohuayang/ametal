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
 * \brief LPUART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� "HW example---LPUART test in polling mode:"��
 *   2. ָ������������յ����ַ�����
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_lpuart_polling.c src_zsn700_hw_lpuart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-16  YRZ, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zsn700_hw_lpuart_polling
 * \copydoc demo_zsn700_hw_lpuart_polling.c
 */

/** [src_zsn700_hw_lpuart_polling] */
#include "ametal.h"
#include "hw/amhw_zsn700_lpuart.h"
#include "hw/amhw_zsn700_rcc.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static const uint8_t lpuart_hw_str[] =
                         {"HW example---LPUART test in polling mode:\r\n"};

static uint32_t lpuart_baudrate = 0;

/**
 * \brief LPUART HW ��ѯ�շ���ʼ��
 */
static void lpuart_polling_init (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                 uint8_t               clk_src,
                                 uint32_t              clk_rate)
{
    /* ����ģʽ����  */
    amhw_zsn700_lpuart_mode_sel(p_hw_lpuart, AMHW_ZSN700_LPUART_WORK_MODE_1);

    /* ����ͨ��ʱ��Դ */
    amhw_zsn700_lpuart_clk_src_sel(p_hw_lpuart,
                                   (amhw_zsn700_lpuart_sclk_src_t)clk_src);

    if(clk_src == AMHW_ZSN700_LPUART_SCLK_SRC_XTL) {

        /* �ⲿ������������ѡ�� */
        amhw_zsn700_rcc_xtl_xtal_driver_set(AMHW_ZSN700_XTL_XTAL_DRIVER_DEFAULT);

        /* XTL�����񵴷��ȵĵ��� */
        amhw_zsn700_rcc_xtl_xtal_amplitude_set(
            AMHW_ZSN700_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

        /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
        amhw_zsn700_rcc_xtl_waittime_set(AMHW_ZSN700_XTL_WAITTIME_16384);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_xtl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_xtl_state_get() == AM_FALSE);

    } else if(clk_src == AMHW_ZSN700_LPUART_SCLK_SRC_RCL) {

        /* ����RCLʱ��Ƶ��У׼ֵ ��38.4KHz��*/
        amhw_zsn700_rcc_rcl_trim_set(*((uint16_t*)0x00100C20));

        amhw_zsn700_rcc_rcl_waittime_set(AMHW_ZSN700_RCL_WAITTIME_256);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_rcl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_rcl_state_get() == AM_FALSE);
    }

    /* ��Ƶϵ������  */
    amhw_zsn700_lpuart_clk_div_sel(p_hw_lpuart,
                                   AMHW_ZSN700_LPUART_SCLK_DIV_MODE13_8);

    /* �ȴ����Ϳ���� */
    while (amhw_zsn700_lpuart_flag_check(p_hw_lpuart,
                                         AMHW_ZSN700_LPUART_FLAG_TX_EMPTY) ==
                                         AM_FALSE);

    /* ֹͣλ���� */
    amhw_zsn700_lpuart_stop_bit_sel(p_hw_lpuart,
                                    AMHW_ZSN700_LPUART_STOP_1_0_BIT);

    /* У������ */
    amhw_zsn700_lpuart_parity_bit_sel(p_hw_lpuart,
                                      AMHW_ZSN700_LPUART_PARITY_NO);

    /* ���������� */
    amhw_zsn700_lpuart_baudrate_set(p_hw_lpuart, clk_rate, lpuart_baudrate);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsn700_lpuart_enable(p_hw_lpuart,AMHW_ZSN700_LPUART_RX);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_lpuart_polling_entry (void     *p_hw_lpuart,
                                          uint8_t   clk_src,
                                          uint32_t  clk_rate,
                                          uint32_t  baudrate)
{

    /* ���ݻ����� */
    uint8_t buf_src[256];
    amhw_zsn700_lpuart_t * p_lpuart = (amhw_zsn700_lpuart_t * )p_hw_lpuart;

    lpuart_baudrate = baudrate;

    /* LPUART��ѯ��ʼ�� */
    lpuart_polling_init(p_lpuart, clk_src, clk_rate);

    amhw_zsn700_lpuart_poll_send(p_lpuart,
                                 lpuart_hw_str,
                                 sizeof(lpuart_hw_str));

    while (1) {

        /* �����ַ� */
        amhw_zsn700_lpuart_poll_receive(p_lpuart, buf_src, 1);

        /* ���͸ոս��յ��ַ� */
        amhw_zsn700_lpuart_poll_send(p_lpuart, buf_src, 1);
    }
}
/** [src_zsn700116_hw_lpuart_polling] */

/* end of file */
