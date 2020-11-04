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
 * \snippet demo_hc32f460_hw_uart_int.c src_hc32f460_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-06  cds, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hc32f460_hw_uart_int
 * \copydoc demo_hc32f460_hw_uart_int.c
 */

/** [src_hc32f460_hw_uart_int] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_hc32f460_uart.h"
#include "hc32f460_irq_handle.h"

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
static uint8_t uart_int_send (amhw_hc32f460_uart_t *p_hw_uart,
                              const uint8_t        *p_buf,
                              uint32_t             len)
{
    if (g_tx_index >= g_tx_nbytes)  {   /* �ϴη����Ѿ�������� */
        gp_tx_buf   = p_buf;            /* ���¶��巢�ͻ������� */
        g_tx_index  = 0;                /* �ӻ�������ʼ�ֽڿ�ʼ���� */
        g_tx_nbytes = len;              /* ����g_tx_nbytes���ֽ� */

        while(amhw_hc32f460_uart_status_flag_check(p_hw_uart,
                AMHW_HC32F460_UART_TX_EMPTY_FLAG) ==
                                          AM_FALSE);

        /* ������дһ��һ���ֽڵ����ݲſ��Բ������Ϳ��ж� */
        amhw_hc32f460_uart_data_write(p_hw_uart, p_buf[g_tx_index++]);

        amhw_hc32f460_uart_int_enable(p_hw_uart,
                AMHW_HC32F460_UART_TX_EMPTY_FLAG);

        return 1;
    }

    return 0;
}

/**
 * \brief ���ڽ����жϷ�����
 *
 * \param[in] p_arg ָ������ƵĴ����豸�ṹ�� ���� am_int_connect() ע��
 */
static void uart_hw_irq_rx_handler (void *p_arg)
{
    amhw_hc32f460_uart_t *p_hw_uart = (amhw_hc32f460_uart_t *)p_arg;
    uint8_t               data;

    /* ��ȡ�½������ݣ������ͳ�ȥ */
    data = amhw_hc32f460_uart_data_read(p_hw_uart);

    amhw_hc32f460_uart_data_write(p_hw_uart, data);
}

/**
 * \brief ���ڷ����жϷ�����
 *
 * \param[in] p_arg ָ������ƵĴ����豸�ṹ�� ���� am_int_connect() ע��
 */
static void uart_hw_irq_tx_handler (void *p_arg)
{
    amhw_hc32f460_uart_t *p_hw_uart = (amhw_hc32f460_uart_t *)p_arg;

    /* �����ж� */
    if(g_tx_index < g_tx_nbytes) {

     /* ���������д��������� */
      amhw_hc32f460_uart_data_write(p_hw_uart, gp_tx_buf[g_tx_index++]);
      } else {
      /* ������û�з������ݣ��رշ����ж� */
      amhw_hc32f460_uart_int_disable(p_hw_uart,
              AMHW_HC32F460_UART_INT_TX_EMPTY_ENABLE);
    }
}




/**
 * \brief UART hw �ж��շ���ʼ��
 */
void uart_int_init (amhw_hc32f460_uart_t *p_hw_uart,
                    void               (* pfn_init)(void),
                    int                   clk_rate,
                    unsigned long         uart_base)
{
    /* ֹͣλ���� */
    amhw_hc32f460_uart_stop_bit_sel(p_hw_uart  , AMHW_HC32F460_UART_STOP_1BIT);

    /* У������ */
    amhw_hc32f460_uart_parity_bit_sel(p_hw_uart, AMHW_HC32F460_UART_PARITY_NO);

    /* ���������� */
    amhw_hc32f460_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    uint32_t enIRQ_RX = 16;
    uint32_t enIRQ_TX = 17;
    uint32_t INT_USART4_RI = 294u;
    uint32_t INT_USART4_TI = 295u;
    stc_intc_sel_field_t *stcIntSel;

    stcIntSel = (stc_intc_sel_field_t *)((uint32_t)(0x40051000UL + 0x5c) + (4u * enIRQ_RX));
    stcIntSel->INTSEL = INT_USART4_RI;
    am_int_connect(enIRQ_RX, uart_hw_irq_rx_handler, (void *)p_hw_uart);
    am_int_enable(enIRQ_RX);

    stcIntSel = (stc_intc_sel_field_t *)((uint32_t)(0x40051000UL + 0x5c) + (4u * enIRQ_TX));
    stcIntSel->INTSEL = INT_USART4_TI;
    am_int_connect(enIRQ_TX, uart_hw_irq_tx_handler, (void *)p_hw_uart);
    am_int_enable(enIRQ_TX);

    /* ��������ж�ʹ�� */
    amhw_hc32f460_uart_int_enable(p_hw_uart, AMHW_HC32F460_UART_RX_VAL_FLAG);

    /* ���ա�����ʹ�� */
    amhw_hc32f460_uart_rx_enable (p_hw_uart, AM_TRUE);
    amhw_hc32f460_uart_tx_enable (p_hw_uart, AM_TRUE);

    if(pfn_init != NULL){
        pfn_init();
    }
}

/**
 * \brief �������
 */
void demo_hc32f460_hw_uart_int_entry (void             *p_hw_uart,
                                      void (* pfn_init)(void),
                                      int              clk_rate,
                                      unsigned long    uart_base)
{
    amhw_hc32f460_uart_t *p_uart = (amhw_hc32f460_uart_t *)p_hw_uart;

    if (pfn_init == NULL) {
        return;
    }
    uart_int_init(p_uart, pfn_init, clk_rate , uart_base);

    uart_int_send(p_uart, hw_polling_str, sizeof(hw_polling_str));

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f460_hw_uart_int] */

/* end of file */
