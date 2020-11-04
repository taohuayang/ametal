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
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. DMA ����ɹ�����ӡ "transfer success"��
 *   2. DMA ���������ӡ "transfer failure"��
 *
 * \par Դ����
 * \snippet demo_hc32f460_drv_dma_m2m.c src_hc32f460_drv_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-04  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_drv_dma_m2m
 * \copydoc demo_hc32f460_drv_dma_m2m.c
 */

/** [src_hc32f460_drv_dma_m2m] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_hc32f460_dma.h"
#include "hw/amhw_hc32f460_dma.h"
#include "hc32f460_intctrl.h"
#include "hc32f460_clk.h"
#include "hc32f460_inum.h"
#include "am_clk.h"

static volatile uint8_t g_buf_src[128];      /**< \brief Դ�����ݻ����� */
static volatile uint8_t g_buf_dst[128];      /**< \brief Ŀ������ݻ����� */

static volatile am_bool_t g_trans_done;      /**< \brief ������ɱ�־ */

static amhw_hc32f460_dma_xfer_desc_t g_desc; /**< \brief ������ */
/**
 * \brief DMA �жϷ������
 */
static void dma_isr (void *p_arg , uint32_t flag)
{
    if (flag == AM_HC32F460_DMA_INT_COMPLETE) {
        g_trans_done = AM_TRUE;
    } else if (flag == AM_HC32F460_DMA_INT_BLK_COMPLETE) {
        am_hc32f460_dma_soft_trig();
    }
}

/**
 * \brief DMA M2M ģʽ���Գ���
 *
 * \retval  AM_OK    ����ɹ�
 * \retval  AM_ERROR ����ʧ��
 */
static int dma_m2m_test (am_hc32f460_dma_dev_t *p_dev, uint8_t dma_chan)
{
    uint32_t flags;
    uint32_t i;

    for (i = 0; i < 128; i++) {
        g_buf_src[i] = i;
        g_buf_dst[i] = 0;
    }

    /* ���� DMA �жϷ����� */
    am_hc32f460_dma_isr_connect(p_dev, dma_chan, dma_isr, (void *)0);

    /* DMA �������� */
    flags = AMHW_HC32F460_DMA_CHAN_CFG_INT_ENABLE            |  /* ͨ���ж�ʹ�� */
            AMHW_HC32F460_DMA_CHAN_CFG_SIZE_8BIT             |  /* ���ݿ�� 1 �ֽ� */
            AMHW_HC32F460_DMA_CHAN_CFG_LLP_DISABLE           |  /* ����������� */
            AMHW_HC32F460_DMA_CHAN_CFG_DSTADD_NOTSEQ_DISABLE |  /* Ŀ���ַ������������� */
            AMHW_HC32F460_DMA_CHAN_CFG_SRCADD_NOTSEQ_DISABLE |  /* Դ��ַ������������� */
            AMHW_HC32F460_DMA_CHAN_CFG_DST_DRPT_DISABLE      |  /* Ŀ���ظ�������� */
            AMHW_HC32F460_DMA_CHAN_CFG_SRC_DRPT_DISABLE      |  /* Դ�ظ�������� */
            AMHW_HC32F460_DMA_CHAN_DST_ADD_INCREASING        |  /* Ŀ���ַ���� */
            AMHW_HC32F460_DMA_CHAN_SRC_ADD_INCREASING;          /* Դ��ַ���� */



    /* ����ͨ�������� */
    am_hc32f460_dma_xfer_desc_build(&g_desc,                /* ͨ�������� */
                                     (uint32_t)(g_buf_src), /* Դ�����ݻ����� */
                                     (uint32_t)(g_buf_dst), /* Ŀ������ݻ����� */
                                     128,                   /* �����ֽ��� */
                                     flags);                /* �������� */

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dev,
                                           &g_desc,
                                           AMHW_HC32F460_DMA_MER_TO_MER, /* �ڴ浽�ڴ� */
                                           dma_chan) == AM_ERROR) {
        return AM_ERROR;
    } else {
        /*�����·��������ʹ��*/
        am_clk_enable(CLK_PTDIS);

        am_mdelay(500);

        /* ���ô���ԴΪ�ڲ��¼����� */
        am_hc32f460_dma_chan_src_set(p_dev, dma_chan, EVT_AOS_STRG);

        am_hc32f460_dma_chan_start(p_dev, dma_chan);
    }

    /* ���ʹ���ڲ������¼�����DMA */
    am_hc32f460_dma_soft_trig();

    while(g_trans_done == AM_FALSE); /* �ȴ�������� */

    for (i = 0; i < 128; i++) {
        if (g_buf_src[i] != g_buf_dst[i]) {
            return AM_ERROR;
        }
    }
    return AM_OK;
}

/**
 * \brief �������
 */
void demo_hc32f460_drv_dma_m2m_entry (am_hc32f460_dma_dev_t *p_dev, uint32_t dma_chan)
{
    if (dma_m2m_test(p_dev, dma_chan) == AM_OK){
        am_kprintf("DMA transfer success !\n");
    } else {
        am_kprintf("DMA transfer failure !\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f460_drv_dma_m2m] */

/* end of file */
