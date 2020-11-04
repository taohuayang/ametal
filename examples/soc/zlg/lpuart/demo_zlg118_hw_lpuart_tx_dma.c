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
 * - ʵ������
 *   1. ָ�����ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ��ָ�����ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      lpuart tx dma test running
 *      lpuart tx dma test done
 *
 * \note
 *    1. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_lpuart_tx_dma.c src_zlg118_hw_lpuart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-26  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_lpuart_tx_dma
 * \copydoc demo_zlg118_hw_lpuart_tx_dma.c
 */

/** [src_zlg118_hw_lpuart_tx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "am_zlg118_dma.h"
#include "hw/amhw_zlg118_lpuart.h"
#include "hw/amhw_zlg118_rcc.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static uint32_t lpuart_baudrate = 0;

/** \brief DMA ���������� */
static amhw_zlg118_dma_xfer_desc_t g_desc;

/** \brief ������ɱ�־ */
static volatile am_bool_t g_trans_done = AM_FALSE;

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst[]  = "lpuart tx dma test running\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst1[] = "lpuart tx dma test done\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst2[] = "DMA tx transfer start:\r\n";

static int32_t               g_dma_chan = 0;      /**< \brief DMA ͨ���� */
static amhw_zlg118_lpuart_t *gp_hw_lpuart = NULL; /**< \brief LPUART ���� */

/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zlg118_dma_isr_connect() �������ݡ�
 * \param[in] flag  : DMA�жϱ�־���ɵײ���������
 *
 * \return �ޡ�
 */
static void lpuart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZLG118_DMA_INT_COMPLETE) {
        if (flag_chan == g_dma_chan) {

            /* ����LPUART����ʱʹ��DMA���� */
            amhw_zlg118_lpuart_disable(gp_hw_lpuart, AMHW_ZLG118_LPUART_DMA_TX);
            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }

}

/**
 * \brief DMA�������á�
 */
static int lpuart_tx_dma_tran_cfg (amhw_zlg118_lpuart_t *p_hw_lpuart,
                                   int32_t             dma_chan,
                                   const uint8_t      *p_txbuf,
                                   uint32_t            dma_tran_len)
{
    uint32_t flags;

    /* ����DMA�жϷ����� */
    am_zlg118_dma_isr_connect(dma_chan, lpuart_dma_isr, (void *)dma_chan);

    /* DMA �������� */
       flags = AMHW_ZLG118_DMA_CHAN_TRANSFER_MODE_BLOCK    | /* SPIֻ�п鴫��ģʽ */
               AMHW_ZLG118_DMA_CHAN_SIZE_8BIT              | /* ����λ�� 8bit */

               AMHW_ZLG118_DMA_CHAN_SRC_ADD_INC_ENABLE     | /* Դ��ַ���� */
               AMHW_ZLG118_DMA_CHAN_RELOAD_SRC_ADD_DISABLE | /* Դ��ַ������*/

               AMHW_ZLG118_DMA_CHAN_DST_ADD_INC_DISABLE    | /* Ŀ���ַ������ */
               AMHW_ZLG118_DMA_CHAN_RELOAD_DST_ADD_ENABLE  | /* Ŀ���ַ���� */

               AMHW_ZLG118_DMA_CHAN_RELOAD_COUNTER_ENABLE  | /* �������������� */
               AMHW_ZLG118_DMA_CHAN_INT_ERR_DISABLE        | /* ��������жϽ��� */
               AMHW_ZLG118_DMA_CHAN_INT_TX_CMP_ENABLE      | /* ��������ж�ʹ�� */
               AMHW_ZLG118_DMA_CHAN_CIRCULAR_MODE_DISABLE ;  /* �ر�ѭ��ģʽ */

    /* ����ͨ�������� */
    am_zlg118_dma_xfer_desc_build(&g_desc,                       /* ͨ�������� */
                                  (uint32_t)(p_txbuf),           /* Դ�����ݻ����� */
                                  (uint32_t)(&(p_hw_lpuart->sbuf)),/* Ŀ������ݻ����� */
                                  dma_tran_len,                  /* �����ֽ��� */
                                  flags);                        /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_zlg118_dma_xfer_desc_chan_cfg(&g_desc,
                                         AMHW_ZLG118_DMA_PER_TO_MER,/* �ڴ浽���� */
                                         dma_chan) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief LPUART��ʼ��
 */
static void lpuart_hw_init (amhw_zlg118_lpuart_t *p_hw_lpuart,
                            uint8_t               clk_src,
                            uint32_t              clk_rate)
{
    /* ����ģʽ����  */
    amhw_zlg118_lpuart_mode_sel(p_hw_lpuart, AMHW_ZLG118_LPUART_WORK_MODE_1);

    /* ����ͨ��ʱ��Դ */
    amhw_zlg118_lpuart_clk_src_sel(p_hw_lpuart,
                                   (amhw_zlg118_lpuart_sclk_src_t)clk_src);

    if(clk_src == AMHW_ZLG118_LPUART_SCLK_SRC_XTL) {

        /* �ⲿ������������ѡ�� */
        amhw_zlg118_rcc_xtl_xtal_driver_set(AMHW_ZLG118_XTL_XTAL_DRIVER_DEFAULT);

        /* XTL�����񵴷��ȵĵ��� */
        amhw_zlg118_rcc_xtl_xtal_amplitude_set(
            AMHW_ZLG118_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

        /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
        amhw_zlg118_rcc_xtl_waittime_set(AMHW_ZLG118_XTL_WAITTIME_16384);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_xtl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_xtl_state_get() == AM_FALSE);

    } else if(clk_src == AMHW_ZLG118_LPUART_SCLK_SRC_RCL) {

        /* ����RCLʱ��Ƶ��У׼ֵ ��38.4KHz��*/
        amhw_zlg118_rcc_rcl_trim_set(*((uint16_t*)0x00100C20));

        amhw_zlg118_rcc_rcl_waittime_set(AMHW_ZLG118_RCL_WAITTIME_256);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_rcl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_rcl_state_get() == AM_FALSE);
    }

    /* ��Ƶϵ������  */
    amhw_zlg118_lpuart_clk_div_sel(p_hw_lpuart,
                                   AMHW_ZLG118_LPUART_SCLK_DIV_MODE13_8);

    /* �ȴ����Ϳ���� */
    while (amhw_zlg118_lpuart_flag_check(p_hw_lpuart,
                                       AMHW_ZLG118_LPUART_FLAG_TX_EMPTY) ==
                                       AM_FALSE);

    /* ֹͣλ���� */
    amhw_zlg118_lpuart_stop_bit_sel(p_hw_lpuart,
                                    AMHW_ZLG118_LPUART_STOP_1_0_BIT);

    /* У������ */
    amhw_zlg118_lpuart_parity_bit_sel(p_hw_lpuart,
                                      AMHW_ZLG118_LPUART_PARITY_NO);

    /* ���������� */
    amhw_zlg118_lpuart_baudrate_set( p_hw_lpuart, clk_rate, lpuart_baudrate);

    /* �ر����д����ж� */
    amhw_zlg118_lpuart_int_disable(p_hw_lpuart, AMHW_ZLG118_LPUART_INT_ALL);
}


/**
 * \brief LPUART����DMA�����ʼ��
 */
static void lpuart_hw_dma_init (amhw_zlg118_lpuart_t *p_hw_lpuart)
{
    /* ���ڷ���DMA����ʹ�� */
    amhw_zlg118_lpuart_enable(p_hw_lpuart, AMHW_ZLG118_LPUART_DMA_TX);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zlg118_lpuart_enable(p_hw_lpuart,AMHW_ZLG118_LPUART_RX);
}

/**
 * \brief �������
 */
void demo_zlg118_hw_lpuart_tx_dma_entry (void    *p_hw_lpuart,
                                         uint8_t  clk_src,
                                         uint32_t clk_rate,
                                         uint32_t baudrate,
                                         int32_t  dma_chan,
                                         int32_t  dma_src)
{
    uint8_t i = 0;
    uint8_t j = 0;

    gp_hw_lpuart = (amhw_zlg118_lpuart_t *)p_hw_lpuart;
    g_dma_chan = dma_chan;

    lpuart_baudrate = baudrate;

    /* LPUART��ʼ�� */
    lpuart_hw_init(gp_hw_lpuart, clk_src, clk_rate);

    /* LPUART��DMA����ĳ�ʼ�� */
    lpuart_hw_dma_init(gp_hw_lpuart);

    lpuart_tx_dma_tran_cfg(gp_hw_lpuart,
                           dma_chan,
                           g_buf_dst2,
                           sizeof(g_buf_dst2) - 1);

    /* Ĭ��ͨ��0��ͨ��1���ȼ�һ������ѯ��*/
    am_zlg118_dma_priority_same();

    /* ���ô��������ź���Դ */
    am_zlg118_dma_chan_src_set (dma_chan, dma_src);

    /* ����ÿ��DMA������СΪ�ѿ�����ͨ��������1�� */
    am_zlg118_dma_block_data_size(dma_chan, 1);

    /* ��ʼͨ������ */
    am_zlg118_dma_chan_start(dma_chan);

    while (1) {

        if (g_trans_done == AM_TRUE) {

            j++;
            g_trans_done = AM_FALSE;

            /* ���ڷ���DMA����ʹ�� */
            amhw_zlg118_lpuart_enable(p_hw_lpuart, AMHW_ZLG118_LPUART_DMA_TX);

            if (j < 3) {
                am_zlg118_dma_chan_stop(dma_chan);
                if (0 == i) {
                    lpuart_tx_dma_tran_cfg(gp_hw_lpuart,
                                         dma_chan,
                                         g_buf_dst,
                                         sizeof(g_buf_dst) - 1);
                } else {
                    lpuart_tx_dma_tran_cfg(gp_hw_lpuart,
                                         dma_chan,
                                         g_buf_dst1,
                                         sizeof(g_buf_dst1) - 1);
                }
                i++;
                am_zlg118_dma_chan_start(dma_chan);
            }

        }
    }
}
/** [src_zlg118116_hw_lpuart_tx_dma] */

/* end of file */
