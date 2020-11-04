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
 * \brief USART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ�����ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ��ָ�����ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      usart tx dma test running
 *      usart tx dma test done
 *
 * \note
 *    1. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_usart_tx_dma.c src_usart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-10  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_usart_tx_dma
 * \copydoc demo_usart_tx_dma.c
 */

/** [src_usart_tx_dma] */
#include "am_zlg237.h"
#include "amhw_zlg237_usart.h"
#include "ametal.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_zlg_dma.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define USART_BAUDRATE      (115200)             /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief DMA ���������� */
static amhw_zlg_dma_xfer_desc_t g_desc;

/** \brief ������ɱ�־ */
static volatile am_bool_t g_trans_done = AM_FALSE;

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst[]  = "usart tx dma test running\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst1[] = "usart tx dma test done\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst2[] = "DMA tx transfer start:\r\n";

static int32_t              g_dma_chan = 0;    /**< \brief DMA ͨ���� */
static amhw_zlg237_usart_t *gp_hw_usart = NULL; /**< \brief USART ���� */

/**
 * \brief DMA ƽ̨��ʼ����
 */
static void __zlg237_plfm_dma_init (void)
{
    am_clk_enable(CLK_DMA);
}

/**
 * \brief DMA ƽ̨ȥ��ʼ����
 */
static void __zlg237_plfm_dma_deinit (void)
{
    am_clk_disable(CLK_DMA);
}

/** \brief DMA �豸��Ϣ */
static const am_zlg_dma_devinfo_t __g_dma_devinfo = {
    ZLG237_DMA_BASE,           /**< \brief ָ��DMA�Ĵ������ָ�� */
    INUM_DMA1_1,               /**< \brief DMA�ж������ſ�ʼ */
    INUM_DMA1_7,               /**< \brief DMA�ж������Ž��� */
    __zlg237_plfm_dma_init,    /**< \brief DMAƽ̨��ʼ�� */
    __zlg237_plfm_dma_deinit   /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA�豸ʵ�� */
static am_zlg_dma_dev_t __g_dma_dev;

/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zlg_dma_isr_connect() �������ݡ�
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (# AM_ZLG_DMA_INT_NORMAL) �� (# AM_ZLG_DMA_INT_ERROR)
 *
 * \return �ޡ�
 */
static void usart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZLG_DMA_INT_NORMAL) {
        if (flag_chan == g_dma_chan) {

            /* ����USART����ʱʹ��DMA���� */
        	amhw_zlg237_usart_dmat_disable(gp_hw_usart);
            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }

}

/**
 * \brief DMA�������á�
 */
static int usart_tx_dma_tran_cfg (amhw_zlg237_usart_t *p_hw_usart,
                                 int32_t               dma_chan,
                                 const uint8_t        *p_txbuf,
                                 uint32_t              dma_tran_len)
{
    uint32_t flags;

    /* ����DMA�жϷ����� */
    am_zlg_dma_isr_connect(dma_chan, usart_dma_isr, (void *)dma_chan);

    /* DMA�������� */
    flags = AMHW_ZLG_DMA_CHAN_PRIORITY_HIGH         |  /* ��������Դ���� */
            AMHW_ZLG_DMA_CHAN_MEM_SIZE_8BIT         |  /* Դ��ַ1�ֽ� */
            AMHW_ZLG_DMA_CHAN_PER_SIZE_8BIT         |  /* Ŀ�ĵ�ַ1�ֽ�д�� */
            AMHW_ZLG_DMA_CHAN_MEM_ADD_INC_ENABLE    |  /* ������Ӱ�� */
            AMHW_ZLG_DMA_CHAN_PER_ADD_INC_DISABLE   |  /* ��ͨ������ */
            AMHW_ZLG_DMA_CHAN_CIRCULAR_MODE_DISABLE ,  /* DMA�ж�ʹ�� */

    /* ����ͨ�������� */
    am_zlg_dma_xfer_desc_build(&g_desc,                        /* ͨ�������� */
                               (uint32_t)(p_txbuf),            /* Դ�����ݻ����� */
                               (uint32_t)(&(p_hw_usart->dr)),  /* Ŀ������ݻ����� */
                                dma_tran_len,                  /* �����ֽ��� */
                                flags);                        /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_zlg_dma_xfer_desc_chan_cfg(&g_desc,
                                       AMHW_ZLG_DMA_MER_TO_PER,  /* �ڴ浽���� */
                                       dma_chan) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief USART��ʼ��
 */
static void usart_hw_init (amhw_zlg237_usart_t *p_hw_usart, uint32_t clk_rate)
{
	/* ���ڵĲ����ʡ�ֹͣλ������λ��У��λ���� */
	amhw_zlg237_usart_baudrate_set(p_hw_usart,clk_rate, USART_BAUDRATE);
    amhw_zlg237_usart_stop_bit_sel(p_hw_usart, AMHW_ZLG237_USART_STOP_10_BIT);
    amhw_zlg237_usart_word_length_sel(p_hw_usart, AMHW_ZLG237_USART_DATA_8BIT);
    amhw_zlg237_usart_parity_bit_sel(p_hw_usart,  AMHW_ZLG237_USART_PARITY_NO);

    /* ���ڷ���DMA����ʹ�� */
	amhw_zlg237_usart_dmat_enable(p_hw_usart);

    /* ���ա�����ʹ�ܣ�����ʹ�� */
    amhw_zlg237_usart_receiver_enable(p_hw_usart);
    amhw_zlg237_usart_transmitter_enable(p_hw_usart);
    amhw_zlg237_usart_enable(p_hw_usart);
}


/**
 * \brief �������
 */
void demo_zlg237_hw_usart_tx_dma_entry (amhw_zlg237_usart_t *p_hw_usart,
                                        uint32_t             clk_rate,
                                        int32_t              dma_chan)
{
    uint8_t i = 0;
    uint8_t j = 0;

    gp_hw_usart = p_hw_usart;
    g_dma_chan = dma_chan;

    /* USART��ʼ�� */
    usart_hw_init(p_hw_usart, clk_rate);

    am_zlg_dma_init(&__g_dma_dev, &__g_dma_devinfo);
    usart_tx_dma_tran_cfg(p_hw_usart, dma_chan, g_buf_dst2, sizeof(g_buf_dst2) - 1);

    am_zlg_dma_chan_start(dma_chan);

    while (1) {

        if (g_trans_done == AM_TRUE) {

            j++;
            g_trans_done = AM_FALSE;

            /* ���ڷ���DMA����ʹ�� */
            amhw_zlg237_usart_dmat_enable(p_hw_usart);

            /* ���ڷ��� */
            amhw_zlg237_usart_transmitter_enable(p_hw_usart);

            if (j < 3) {
                am_zlg_dma_chan_stop(dma_chan);
                if (0 == i) {
                    usart_tx_dma_tran_cfg(p_hw_usart,
                                          dma_chan,
                                          g_buf_dst,
                                          sizeof(g_buf_dst) - 1);
                } else {
                    usart_tx_dma_tran_cfg(p_hw_usart,
                                          dma_chan,
                                          g_buf_dst1,
                                          sizeof(g_buf_dst1) - 1);
                }
                i++;
                am_zlg_dma_chan_start(dma_chan);
            }

        }
    }
}
/** [src_zlg237_hw_usart_tx_dma] */

/* end of file */
