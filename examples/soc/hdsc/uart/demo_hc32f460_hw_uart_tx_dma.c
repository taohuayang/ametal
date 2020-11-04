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
 * - ʵ������
 *   1. ָ�����ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ��ָ�����ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      uart tx dma test running
 *      uart tx dma test done
 *
 * \note
 *    1. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_uart_tx_dma.c src_hc32f460_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-10  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_uart_tx_dma
 * \copydoc demo_hc32f460_hw_uart_tx_dma.c
 */

/** [src_hc32f460_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "am_hc32f460_dma.h"
#include "hw/amhw_hc32f460_uart.h"
#include "hc32f460_intctrl.h"
#include "hc32f460_inum.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE      (115200)             /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief DMA ���������� */
static amhw_hc32f460_dma_xfer_desc_t g_desc;

/** \brief ������ɱ�־ */
static volatile am_bool_t g_trans_done = AM_FALSE;

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst[]  = "uart tx dma test running\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst1[] = "uart tx dma test done\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst2[] = "DMA tx transfer start:\r\n";

static int32_t             g_dma_chan = 0;    /**< \brief DMA ͨ���� */
static amhw_hc32f460_uart_t *gp_hw_uart = NULL; /**< \brief UART ���� */


/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_hc32f460_dma_isr_connect() �������ݡ�
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (# AM_HC32F460_DMA_INT_COMPLETE) �� (# AM_HC32F460_DMA_INT_BLK_COMPLETE)
 *                    ��(# AM_HC32F460_DMA_INT_ERR_TRNERR)��(# AM_HC32F460_DMA_INT_ERR_REQERR)
 *
 * \return �ޡ�
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
 * \brief DMA�������á�
 */
static int uart_tx_dma_tran_cfg (amhw_hc32f460_uart_t  *p_hw_uart,
                                 am_hc32f460_dma_dev_t *p_dma_dev,
                                 int32_t                dma_chan,
                                 const uint8_t         *p_txbuf,
                                 uint32_t               dma_tran_len)
{
    uint32_t flags;

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
             AMHW_HC32F460_DMA_CHAN_DST_ADD_FIXED             |  /* Ŀ���ַ�̶� */
             AMHW_HC32F460_DMA_CHAN_SRC_ADD_INCREASING;          /* Դ��ַ���� */

    /* ����ͨ�������� */
    am_hc32f460_dma_xfer_desc_build(&g_desc,                         /* ͨ�������� */
                                    (uint32_t)(p_txbuf),             /* Դ�����ݻ����� */
                                    (uint32_t)(&(p_hw_uart->DR)),    /* Ŀ������ݻ����� */
                                    dma_tran_len,                    /* �����ֽ��� */
                                    flags);                          /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dma_dev,
    		                               &g_desc,
                                           AMHW_HC32F460_DMA_PER_TO_MER,/* �ڴ浽���� */
                                           dma_chan) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief UART��ʼ��
 */
static void uart_hw_init (amhw_hc32f460_uart_t *p_hw_uart, uint32_t clk_rate)
{
    /* ֹͣλ���� */
    amhw_hc32f460_uart_stop_bit_sel(p_hw_uart  , AMHW_HC32F460_UART_STOP_1BIT);

    /* У������ */
    amhw_hc32f460_uart_parity_bit_sel(p_hw_uart, AMHW_HC32F460_UART_PARITY_NO);

    /* ���������� */
    amhw_hc32f460_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    /* ���ܴ��������ж� */
    amhw_hc32f460_uart_int_disable(p_hw_uart, AMHW_HC32F460_UART_INT_ALL_ENABLE_MASK);

    /* ʹ�ܴ��ڷ��� */
    amhw_hc32f460_uart_tx_enable (p_hw_uart, AM_TRUE);
}

/**
 * \brief �������
 */
void demo_hc32f460_hw_uart_tx_dma_entry (void                   *p_hw_uart,
                                         uint32_t                clk_rate,
                                         am_hc32f460_dma_dev_t  *p_dma_dev,
                                         int32_t                 dma_chan)
{
    uint8_t i = 0;
    uint8_t j = 0;

    gp_hw_uart = (amhw_hc32f460_uart_t *)p_hw_uart;
    g_dma_chan = dma_chan;

    /* UART��ʼ�� */
    uart_hw_init(gp_hw_uart, clk_rate);

    /* ����ÿ��DMA������СΪ�ѿ�����ͨ��������1�� */
    am_hc32f460_dma_block_data_size(p_dma_dev, dma_chan, 1);

    uart_tx_dma_tran_cfg(gp_hw_uart,
                         p_dma_dev,
                         dma_chan,
                         &g_buf_dst2[1],
                         sizeof(g_buf_dst2) - 1 -1);

    /* ���ô��������ź���ԴΪ����4�ķ��Ϳ��¼� */
    am_hc32f460_dma_chan_src_set(p_dma_dev, dma_chan, EVT_USART4_TI);

    /* ��ʼͨ������ */
    am_hc32f460_dma_chan_start(p_dma_dev, dma_chan);

    /*
     * �����Ǳ��ش�������ˣ��¼�����������ͨ������֮��Ϊ��֤��������
     * �򴮿����ݼĴ���дһ�����ݣ�����������λ�Ĵ����󣬷��Ϳձ�־��1��
     * �������Ϳ��¼�������DMA
     *  */
    amhw_hc32f460_uart_data_write(gp_hw_uart, g_buf_dst2[0]);

    while (1) {

        if (g_trans_done == AM_TRUE) {

            j++;
            g_trans_done = AM_FALSE;

            if (j < 3) {
                am_hc32f460_dma_chan_stop(p_dma_dev, dma_chan);

               /* �ȴ���һ�δ������ */
                while (amhw_hc32f460_uart_status_flag_check(p_hw_uart,
                	   AMHW_HC32F460_UART_TX_COMPLETE_FALG) == AM_FALSE);
                if (0 == i) {

                    uart_tx_dma_tran_cfg(gp_hw_uart,
                                         p_dma_dev,
                                         dma_chan,
                                         &g_buf_dst[1],
                                         sizeof(g_buf_dst) - 1 -1);

                	amhw_hc32f460_uart_data_write(gp_hw_uart, g_buf_dst[0]);


                } else {
                    uart_tx_dma_tran_cfg(gp_hw_uart,
                                         p_dma_dev,
                                         dma_chan,
                                         &g_buf_dst1[1],
                                         sizeof(g_buf_dst1) - 1 - 1);

                	amhw_hc32f460_uart_data_write(gp_hw_uart, g_buf_dst1[0]);

                }

                i++;

                am_hc32f460_dma_chan_start(p_dma_dev, dma_chan);

            }

        }
    }
}
/** [src_hc32f460_hw_uart_tx_dma] */

/* end of file */
