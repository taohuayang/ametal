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
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ͨ����λ������һ������ MCU ���� 5 ���ַ���
 *
 * - ʵ������
 *   1. ָ�����ڴ�ӡ�����յ������ݣ�
 *   2. Ȼ��ָ�����ڴ�ӡ�� "DMA transfer done!"��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_lpuart_rx_dma.c src_zsn700_hw_lpuart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-16  YRZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_lpuart_rx_dma
 * \copydoc demo_zsn700_hw_lpuart_rx_dma.c
 */

/** [src_zsn700_hw_lpuart_rx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "am_zsn700_dma.h"
#include "hw/amhw_zsn700_lpuart.h"
#include "hw/amhw_zsn700_rcc.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zsn700_dma_xfer_desc_t g_desc;           /**< \brief DMA ���������� */
static volatile am_bool_t       g_trans_done = AM_FALSE; /**< \brief ������ɱ�־ */
static uint8_t                  g_buf_dst[5] = {0};  /**< \brief Ŀ������ݻ����� */
static int32_t                  g_dma_chan   = 0;    /**< \brief DMA ͨ���� */
static amhw_zsn700_lpuart_t    *gp_hw_lpuart = NULL; /**< \brief LPUART ���� */

static uint32_t lpuart_baudrate = 0;

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zsn700_dma_isr_connect() ��������
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ
 *
 * \return ��
 */
static void lpuart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZSN700_DMA_INT_COMPLETE) {
        if (flag_chan == g_dma_chan) {

            /* ����LPUART����ʱʹ��DMA���� */
            amhw_zsn700_lpuart_disable(gp_hw_lpuart, AMHW_ZSN700_LPUART_DMA_RX);

            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief LPUART����DMA��������
 */
static int lpuart_rx_dma_tran_cfg (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                 int32_t          dma_chan,
                                 uint32_t         dma_tran_len)
{
    uint32_t i;
    uint32_t flags;

    for (i = 0; i < sizeof(g_buf_dst); i++) {
        g_buf_dst[i] = 0;
    }

    /* ����DMA�жϷ����� */
    am_zsn700_dma_isr_connect(dma_chan, lpuart_dma_isr, (void *)dma_chan);

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
                                   (uint32_t)(&(p_hw_lpuart->sbuf)), /* Դ�����ݻ��� */
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
 * \brief LPUART ��ʼ��
 */
static void lpuart_hw_init (amhw_zsn700_lpuart_t *p_hw_lpuart,
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
    amhw_zsn700_lpuart_baudrate_set( p_hw_lpuart, clk_rate, lpuart_baudrate);

    /* �ر����д����ж� */
    amhw_zsn700_lpuart_int_disable(p_hw_lpuart, AMHW_ZSN700_LPUART_INT_ALL);
}

/**
 * \brief LPUART���մ���ʱDMA��ʼ��
 */
static void lpuart_hw_dma_init (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    /* ���ڷ���DMA����ʹ�� */
    amhw_zsn700_lpuart_enable(p_hw_lpuart, AMHW_ZSN700_LPUART_DMA_RX);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsn700_lpuart_enable(p_hw_lpuart,AMHW_ZSN700_LPUART_RX);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_lpuart_rx_dma_entry (void    *p_hw_lpuart,
                                         uint8_t  clk_src,
                                         uint32_t clk_rate,
                                         uint32_t baudrate,
                                         int32_t  dma_chan,
                                         int32_t  dma_src)
{
    gp_hw_lpuart = (amhw_zsn700_lpuart_t *)p_hw_lpuart;
    g_dma_chan = dma_chan;

    lpuart_baudrate = baudrate;

    /* LPUART��ʼ�� */
    lpuart_hw_init(gp_hw_lpuart, clk_src, clk_rate);

    /* LPUART����DMA����ĳ�ʼ�� */
    lpuart_hw_dma_init(gp_hw_lpuart);

    amhw_zsn700_lpuart_poll_send(gp_hw_lpuart,
                                 (uint8_t *)"LPUART DMA RX start:\r\n",
                                 sizeof("LPUART DMA RX start:\r\n") - 1);
    /* ��ʼDMA���� */
    lpuart_rx_dma_tran_cfg(gp_hw_lpuart, dma_chan, sizeof(g_buf_dst));

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

    amhw_zsn700_lpuart_poll_send(gp_hw_lpuart, g_buf_dst, sizeof(g_buf_dst));
    amhw_zsn700_lpuart_poll_send(gp_hw_lpuart,
                                 (uint8_t *)"\r\nDMA transfer done!\r\n",
                                  sizeof("\r\nDMA transfer done!\r\n") - 1);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zsn700_hw_lpuart_rx_dma] */

/* end of file */
