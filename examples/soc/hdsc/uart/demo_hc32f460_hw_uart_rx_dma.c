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
 * \snippet demo_hc32f460_hw_uart_rx_dma.c src_hc32f460_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-11  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_uart_rx_dma
 * \copydoc demo_hc32f460_hw_uart_rx_dma.c
 */

/** [src_hc32f460_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "am_hc32f460_dma.h"
#include "hw/amhw_hc32f460_uart.h"
#include "hc32f460_inum.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE      (115200)                    /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_hc32f460_dma_xfer_desc_t g_desc;              /**< \brief DMA ���������� */
static volatile am_bool_t       g_trans_done = AM_FALSE;  /**< \brief ������ɱ�־ */
static uint8_t                  g_buf_dst[5] = {0};       /**< \brief Ŀ������ݻ����� */
static int32_t                  g_dma_chan = 0;           /**< \brief DMA ͨ���� */
static amhw_hc32f460_uart_t    *gp_hw_uart = NULL;          /**< \brief UART ���� */

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_hc32f460_dma_isr_connect() ��������
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AM_ZLG116_DMA_INT_ERROR) �� (#AM_ZLG116_DMA_INT_NORMAL)
 *
 * \return ��
 */
static void uart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_HC32F460_DMA_INT_COMPLETE) {
        if (flag_chan == g_dma_chan) {
            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief UART����DMA��������
 */
static int uart_rx_dma_tran_cfg (amhw_hc32f460_uart_t  *p_hw_uart,
                                 int32_t                dma_chan,
                                 am_hc32f460_dma_dev_t *p_dma_dev,
                                 uint32_t               dma_tran_len)
{
    uint32_t i;
    uint32_t flags;

    for (i = 0; i < sizeof(g_buf_dst); i++) {
        g_buf_dst[i] = 0;
    }

    /* ����DMA�жϷ����� */
    am_hc32f460_dma_isr_connect(p_dma_dev, dma_chan, uart_dma_isr, (void *)dma_chan);

    /* DMA �������� */
    flags = AMHW_HC32F460_DMA_CHAN_CFG_INT_ENABLE            |  /* ͨ���ж�ʹ�� */
            AMHW_HC32F460_DMA_CHAN_CFG_SIZE_8BIT             |  /* ���ݿ�� 1 �ֽ� */
            AMHW_HC32F460_DMA_CHAN_CFG_LLP_DISABLE           |  /* ����������� */
            AMHW_HC32F460_DMA_CHAN_CFG_DSTADD_NOTSEQ_DISABLE |  /* Ŀ���ַ������������� */
            AMHW_HC32F460_DMA_CHAN_CFG_SRCADD_NOTSEQ_DISABLE |  /* Դ��ַ������������� */
            AMHW_HC32F460_DMA_CHAN_CFG_DST_DRPT_DISABLE      |  /* Ŀ���ظ�������� */
            AMHW_HC32F460_DMA_CHAN_CFG_SRC_DRPT_DISABLE      |  /* Դ�ظ�������� */
            AMHW_HC32F460_DMA_CHAN_DST_ADD_INCREASING        |  /* Ŀ���ַ���� */
            AMHW_HC32F460_DMA_CHAN_SRC_ADD_FIXED;               /* Դ��ַ�̶� */

    /* ����ͨ�������� */
    am_hc32f460_dma_xfer_desc_build(&g_desc,                         /* ͨ�������� */
                                   ((uint32_t)&(p_hw_uart->DR) + 2), /* Դ�����ݻ��� */
                                   (uint32_t)(g_buf_dst),            /* Ŀ�����ݻ��� */
                                   (uint32_t)dma_tran_len,           /* �����ֽ��� */
                                   flags);                           /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dma_dev,
                                           &g_desc,
                                           AMHW_HC32F460_DMA_PER_TO_MER, /* ���赽 �ڴ� */
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
static void uart_hw_init (amhw_hc32f460_uart_t *p_hw_uart, uint32_t clk_rate)
{
    /* �ȴ����Ϳ���� */
    while (amhw_hc32f460_uart_status_flag_check(p_hw_uart,
                                                AMHW_HC32F460_UART_TX_COMPLETE_FALG) ==
                                                AM_FALSE);

    /* ֹͣλ���� */
    amhw_hc32f460_uart_stop_bit_sel(p_hw_uart, AMHW_HC32F460_UART_STOP_1BIT);

    /* У������ */
    amhw_hc32f460_uart_parity_bit_sel(p_hw_uart, AMHW_HC32F460_UART_PARITY_NO);

    /* ���������� */
    amhw_hc32f460_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    /* ���ܴ��������ж� */
    amhw_hc32f460_uart_int_disable(p_hw_uart, AMHW_HC32F460_UART_INT_ALL_ENABLE_MASK);

    /* ʹ�ܴ��ڷ��� */
    amhw_hc32f460_uart_tx_enable (p_hw_uart, AM_TRUE);
    /* ʹ�ܴ��ڽ��� */
    amhw_hc32f460_uart_rx_enable (p_hw_uart, AM_TRUE);
}


/**
 * \brief �������
 */
void demo_hc32f460_hw_uart_rx_dma_entry (void    *p_hw_uart,
                                         uint32_t clk_rate,
                                         am_hc32f460_dma_dev_t *p_dma_dev,
                                         int32_t  dma_chan)
{
    gp_hw_uart = (amhw_hc32f460_uart_t *)p_hw_uart;
    g_dma_chan = dma_chan;

    /* UART��ʼ�� */
    uart_hw_init(gp_hw_uart, clk_rate);

    amhw_hc32f460_uart_poll_send(gp_hw_uart,
                                 (uint8_t *)"UART DMA RX start:\r\n",
                                 (uint32_t)sizeof("UART DMA RX start:\r\n") - 1);
    /* ��ʼDMA���� */
    uart_rx_dma_tran_cfg(gp_hw_uart, dma_chan, p_dma_dev, sizeof(g_buf_dst));

    /* ���ô��������ź���ԴΪ����4�Ľ������¼� */
    am_hc32f460_dma_chan_src_set(p_dma_dev, dma_chan, EVT_USART4_RI);

    /* ����ÿ��DMA������СΪ�ѿ�����ͨ��������1�� */
    am_hc32f460_dma_block_data_size(p_dma_dev, dma_chan, 1);

    /* ��ʼͨ������ */
    am_hc32f460_dma_chan_start(p_dma_dev, dma_chan);

    /* �ȴ�������� */
    while (g_trans_done == AM_FALSE);

    g_trans_done = AM_FALSE;

    amhw_hc32f460_uart_poll_send(gp_hw_uart, g_buf_dst, sizeof(g_buf_dst));
    amhw_hc32f460_uart_poll_send(gp_hw_uart,
                                (uint8_t *)"\r\nDMA transfer done!\r\n",
                                 sizeof("\r\nDMA transfer done!\r\n") - 1);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f460_hw_uart_rx_dma] */

/* end of file */
