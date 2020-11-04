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
 * \brief UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� "HW example---UART test in interrupt mode:"��
 *   2. ָ������������յ����ַ���
 *
 * \note
 *   1.���ô�������Դ���һ�£���رյ��Դ�������Ӱ��Ч��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_uart_int.c src_zsn700_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zsn700_hw_uart_int
 * \copydoc demo_zsn700_hw_uart_int.c
 */

/** [src_zsn700_hw_uart_int] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_zsn700_uart.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE      (115200)           /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static const uint8_t hw_polling_str[] =
                              {"HW example---UART test in interrupt mode:\r\n"};

static const uint8_t   *gp_tx_buf   = NULL; /**< \brief ���ͻ����� */
static volatile uint8_t g_tx_index  = 0;    /**< \brief ��ǰ������������ */
static volatile uint8_t g_tx_nbytes = 0;    /**< \brief ��Ҫ���͵����ֽ��� */

/**
 * \brief ���ڷ������ݣ��ж�ģʽ�£��ú�������������
 *
 * \param[in] p_hw_uartָ������ƵĴ����豸�ṹ��
 * \param[in] p_buf    ָ�������ݵĻ�����
 * \param[in] len      ���͵��ֽ���
 *
 * \retval 1 ���;���
 * \retval 0 ����ģ��æµ���޷�����
 *
 * \note ���ͻ����������ȫ�ֵģ���֤���������ݷ������ǰ��������û�б��ͷŵ�
 */
static uint8_t uart_int_send (amhw_zsn700_uart_t *p_hw_uart,
                              const uint8_t   *p_buf,
                              uint32_t         len)
{
    if (g_tx_index >= g_tx_nbytes)  {   /* �ϴη����Ѿ�������� */
        gp_tx_buf   = p_buf;            /* ���¶��巢�ͻ������� */
        g_tx_index  = 0;                /* �ӻ�������ʼ�ֽڿ�ʼ���� */
        g_tx_nbytes = len;              /* ����g_tx_nbytes���ֽ� */

        /* ������дһ��һ���ֽڵ����ݲ��Բ��������ж� */
        while(amhw_zsn700_uart_flag_check(p_hw_uart,
                                          AMHW_ZSN700_UART_FLAG_TX_EMPTY) ==
                                          AM_FALSE);

        amhw_zsn700_uart_data_write(p_hw_uart, p_buf[g_tx_index++]);

        amhw_zsn700_uart_int_enable(p_hw_uart,
                                    AMHW_ZSN700_UART_FLAG_TX_COMPLETE);

        return 1;
    }

    return 0;
}

/**
 * \brief �����жϷ�����
 *
 * \param[in] p_arg ָ������ƵĴ����豸�ṹ�� ���� am_int_connect() ע��
 */
static void uart_hw_irq_handler (void *p_arg)
{
    amhw_zsn700_uart_t *p_hw_uart = (amhw_zsn700_uart_t *)p_arg;
    uint8_t             data;

    if (amhw_zsn700_uart_flag_check(p_hw_uart,
                                    AMHW_ZSN700_UART_FLAG_RX_COMPLETE) ==
                                    AM_TRUE) {

        amhw_zsn700_uart_flag_clr(p_hw_uart, AMHW_ZSN700_UART_FLAG_RX_COMPLETE);

        /* ��ȡ�½������ݣ������ͳ�ȥ */
        data = amhw_zsn700_uart_data_read(p_hw_uart);
        amhw_zsn700_uart_data_write(p_hw_uart, data);

    } else  if (amhw_zsn700_uart_flag_check(p_hw_uart,
                                            AMHW_ZSN700_UART_FLAG_TX_COMPLETE) ==
                                            AM_TRUE) {

        amhw_zsn700_uart_flag_clr(p_hw_uart, AMHW_ZSN700_UART_FLAG_TX_COMPLETE);

        /* �����ж� */
        if(g_tx_index < g_tx_nbytes) {

            /* ���������д��������� */
            amhw_zsn700_uart_data_write(p_hw_uart, gp_tx_buf[g_tx_index++]);

        } else {

            /* ������û�з������ݣ��رշ����ж� */
            amhw_zsn700_uart_int_disable(p_hw_uart,
                                         AMHW_ZSN700_UART_INT_TX_COMPLETE);
        }
    }
}

/**
 * \brief UART hw �ж��շ���ʼ��
 */
void uart_int_init (amhw_zsn700_uart_t *p_hw_uart,
                    void (* pfn_init)(void),
                    uint32_t         clk_rate,
                    unsigned long    uart_base,
                    unsigned char    inum_uart)
{
    /* ����ģʽ����  */
    amhw_zsn700_uart_mode_sel(p_hw_uart, AMHW_ZSN700_UART_WORK_MODE_1);

    /* ��Ƶϵ������  */
    amhw_zsn700_uart_clk_div_sel(p_hw_uart, AMHW_ZSN700_UART_CLK_DIV_MODE13_8);

    /* ֹͣλ���� */
    amhw_zsn700_uart_stop_bit_sel(p_hw_uart  , AMHW_ZSN700_UART_STOP_1_0_BIT);

    /* У������ */
    amhw_zsn700_uart_parity_bit_sel(p_hw_uart, AMHW_ZSN700_UART_PARITY_NO);

    /* ���������� */
    amhw_zsn700_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    /* ��������ж�ʹ�� */
    amhw_zsn700_uart_int_enable(p_hw_uart, AMHW_ZSN700_UART_INT_RX_COMPLETE);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsn700_uart_enable(p_hw_uart,AMHW_ZSN700_UART_RX);

    /* �����ж������ţ������ж� */
    am_int_connect(inum_uart, uart_hw_irq_handler, (void *)p_hw_uart);
    am_int_enable(inum_uart);
    if(pfn_init != NULL){
        pfn_init();
    }
}

/**
 * \brief �������
 */
void demo_zsn700_hw_uart_int_entry (void             *p_hw_uart,
                                    void (* pfn_init)(void),
                                    uint32_t         clk_rate,
                                    unsigned long    uart_base,
                                    unsigned char    inum_uart)
{
    amhw_zsn700_uart_t *p_uart = (amhw_zsn700_uart_t *)p_hw_uart;

    if (pfn_init == NULL) {
        return;
    }
    uart_int_init(p_uart, pfn_init, clk_rate , uart_base, inum_uart);

    uart_int_send(p_uart, hw_polling_str, sizeof(hw_polling_str));

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zsn700_hw_uart_int] */

/* end of file */
