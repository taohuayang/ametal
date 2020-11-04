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
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ͨ����λ������һ������ MCU ���� 5 ���ַ���
 *
 * - ʵ������
 *   1. ָ�����ڴ�ӡ�����յ������ݣ�
 *   2. Ȼ��ָ�����ڴ�ӡ�� "DMA transfer done!"��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_uart_rx_dma.c src_zsn700_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_uart_rx_dma
 * \copydoc demo_zsn700_hw_uart_rx_dma.c
 */

/** [src_zsn700_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "am_zsn700_dma.h"
#include "hw/amhw_zsn700_uart.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE      (115200)                    /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zsn700_dma_xfer_desc_t g_desc;             /**< \brief DMA ���������� */
static volatile am_bool_t       g_trans_done = AM_FALSE; /**< \brief ������ɱ�־ */
static uint8_t                  g_buf_dst[5] = {0};    /**< \brief Ŀ������ݻ����� */
static int32_t                  g_dma_chan = 0;        /**< \brief DMA ͨ���� */
static amhw_zsn700_uart_t      *gp_hw_uart = NULL;     /**< \brief UART ���� */

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zsn700_dma_isr_connect() ��������
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AM_ZLG116_DMA_INT_ERROR) �� (#AM_ZLG116_DMA_INT_NORMAL)
 *
 * \return ��
 */
static void uart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZSN700_DMA_INT_COMPLETE) {
        if (flag_chan == g_dma_chan) {

            /* ����UART����ʱʹ��DMA���� */
            amhw_zsn700_uart_disable(gp_hw_uart, AMHW_ZSN700_UART_DMA_RX);

            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief UART����DMA��������
 */
static int uart_rx_dma_tran_cfg (amhw_zsn700_uart_t *p_hw_uart,
                                 int32_t          dma_chan,
                                 uint32_t         dma_tran_len)
{
    uint32_t i;
    uint32_t flags;

    for (i = 0; i < sizeof(g_buf_dst); i++) {
        g_buf_dst[i] = 0;
    }

    /* ����DMA�жϷ����� */
    am_zsn700_dma_isr_connect(dma_chan, uart_dma_isr, (void *)dma_chan);

    /* DMA �������� */
    flags = AMHW_ZSN700_DMA_CHAN_TRANSFER_MODE_BLOCK    | /* SPIֻ�п鴫��ģʽ */
            AMHW_ZSN700_DMA_CHAN_SIZE_8BIT              | /* ����λ�� 8bit */

            AMHW_ZSN700_DMA_CHAN_SRC_ADD_INC_DISABLE    | /* Դ��ַ������ */
            AMHW_ZSN700_DMA_CHAN_RELOAD_SRC_ADD_ENABLE  | /* Դ��ַ����*/

            AMHW_ZSN700_DMA_CHAN_DST_ADD_INC_ENABLE     | /* Ŀ���ַ���� */
            AMHW_ZSN700_DMA_CHAN_RELOAD_DST_ADD_DISABLE | /* Ŀ���ַ������ */

            AMHW_ZSN700_DMA_CHAN_RELOAD_COUNTER_ENABLE  | /* �������������� */
            AMHW_ZSN700_DMA_CHAN_INT_ERR_DISABLE        | /* ��������жϽ��� */
            AMHW_ZSN700_DMA_CHAN_INT_TX_CMP_ENABLE      | /* ��������ж�ʹ�� */
            AMHW_ZSN700_DMA_CHAN_CIRCULAR_MODE_DISABLE ;  /* �ر�ѭ��ģʽ */

    /* ����ͨ�������� */
    am_zsn700_dma_xfer_desc_build(&g_desc,                      /* ͨ�������� */
                                   (uint32_t)(&(p_hw_uart->sbuf)), /* Դ�����ݻ��� */
                                   (uint32_t)(g_buf_dst),       /* Ŀ�����ݻ��� */
                                   (uint32_t)dma_tran_len,      /* �����ֽ��� */
                                   flags);                      /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_zsn700_dma_xfer_desc_chan_cfg(&g_desc,
                                          AMHW_ZSN700_DMA_PER_TO_MER, /* ���赽 �ڴ� */
                                          (uint8_t)dma_chan) == AM_ERROR) {
        return AM_ERROR;
    } else {
        /* �������� */
    }

    return AM_OK;
}

/**
 * \brief UART ��ʼ��
 */
static void uart_hw_init (amhw_zsn700_uart_t *p_hw_uart, uint32_t clk_rate)
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

    /* �ر����д����ж� */
    amhw_zsn700_uart_int_disable(p_hw_uart, AMHW_ZSN700_UART_INT_ALL);
}

/**
 * \brief UART���մ���ʱDMA��ʼ��
 */
static void uart_hw_dma_init (amhw_zsn700_uart_t *p_hw_uart)
{
    /* ���ڷ���DMA����ʹ�� */
    amhw_zsn700_uart_enable(p_hw_uart, AMHW_ZSN700_UART_DMA_RX);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsn700_uart_enable(p_hw_uart,AMHW_ZSN700_UART_RX);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_uart_rx_dma_entry (void    *p_hw_uart,
                                       uint32_t clk_rate,
                                       int32_t  dma_chan,
                                       int32_t  dma_src)
{
    gp_hw_uart = (amhw_zsn700_uart_t *)p_hw_uart;
    g_dma_chan = dma_chan;

    /* UART��ʼ�� */
    uart_hw_init(gp_hw_uart, clk_rate);

    /* UART����DMA����ĳ�ʼ�� */
    uart_hw_dma_init(gp_hw_uart);

    amhw_zsn700_uart_poll_send(gp_hw_uart,
                               (uint8_t *)"UART DMA RX start:\r\n",
                               (uint32_t)sizeof("UART DMA RX start:\r\n") - 1);
    /* ��ʼDMA���� */
    uart_rx_dma_tran_cfg(gp_hw_uart, dma_chan, sizeof(g_buf_dst));

    /* Ĭ��ͨ��0��ͨ��1���ȼ�һ������ѯ��*/
    am_zsn700_dma_priority_same();

    /* ���ô��������ź���Դ */
    am_zsn700_dma_chan_src_set (dma_chan, dma_src);

    /* ����ÿ��DMA������СΪ�ѿ�����ͨ��������1�� */
    am_zsn700_dma_block_data_size(dma_chan, 1);

    /* ��ʼͨ������ */
    am_zsn700_dma_chan_start(dma_chan);

    /* �ȴ�������� */
    while (g_trans_done == AM_FALSE);

    g_trans_done = AM_FALSE;

    amhw_zsn700_uart_poll_send(gp_hw_uart, g_buf_dst, sizeof(g_buf_dst));
    amhw_zsn700_uart_poll_send(gp_hw_uart,
                               (uint8_t *)"\r\nDMA transfer done!\r\n",
                               sizeof("\r\nDMA transfer done!\r\n") - 1);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zsn700_hw_uart_rx_dma] */

/* end of file */
