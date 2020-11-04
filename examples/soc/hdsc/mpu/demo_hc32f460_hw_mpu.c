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
 * \brief MPU���̣�ͨ��Ӳ����ӿ�ʵ��
 *
 * - ʵ������
 *   1. ʹ��ǰMPUǰ��DMA������д�ڴ棬���ڴ�ӡ"dma test success";
 *   2. ����MPU������DMAԴ��ַ�ڴ��ֹ����DMA�޷���ȡ���ݣ�������ȫΪ0�����ڴ�ӡ"mpu test success";
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_mpu.c src_hc32f460_hw_mpu
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-14  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_mpu
 * \copydoc demo_hc32f460_hw_mpu.c
 */

/** [src_hc32f460_hw_mpu] */

#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_clk.h"
#include "hw/amhw_hc32f460_mpu.h"
#include "am_hc32f460_dma.h"
#include "hw/amhw_hc32f460_dma.h"
#include "hc32f460_intctrl.h"
#include "hc32f460_clk.h"
#include "string.h"


/* �����С */
#define __REGION_SIZE    32

/* ������ */
#define __REGION_NUM     AMHW_HC32F460_MPU_REGION_NUM0

/* ����buffer����ʼ��ַ������size���ֽڶ��� */
static uint8_t __attribute__((aligned(__REGION_SIZE))) g_buf_src[__REGION_SIZE];    /**< \brief Դ�����ݻ����� */
static uint8_t __attribute__((aligned(__REGION_SIZE))) g_buf_dst[__REGION_SIZE];    /**< \brief Ŀ������ݻ����� */

extern am_hc32f460_dma_dev_t __g_dma1_dev;
#define  DMA_TEST_DEV     __g_dma1_dev
#define  DMA_M2M_CH       DMA_CHAN_1   /**< \brief ͨ�� */

static volatile am_bool_t g_trans_done; /**< \brief ������ɱ�־ */

static amhw_hc32f460_dma_xfer_desc_t g_desc; /**< \brief ������ */
/**
 * \brief DMA �жϷ������
 */
static void dma_isr (void *p_arg , uint32_t flag)
{
    if (flag == AM_HC32F460_DMA_INT_COMPLETE) {
        g_trans_done = AM_TRUE;
    } else if (flag == AM_HC32F460_DMA_INT_BLK_COMPLETE) {
        *(volatile uint32_t *)HC32F460_AOS_BASE = 0x1;
    }
}

/**
 * \brief DMA ����
 */
am_err_t dma_cfg(am_hc32f460_dma_dev_t *p_dma_dev, int dma_chan)
{
    uint32_t flags;

    /* ���� DMA �жϷ����� */
    am_hc32f460_dma_isr_connect(p_dma_dev, dma_chan, dma_isr, (void *)0);

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
                                      __REGION_SIZE,        /* �����ֽ��� */
                                     flags);

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dma_dev,
                                          &g_desc,
                                           AMHW_HC32F460_DMA_MER_TO_MER, /* �ڴ浽�ڴ� */
                                           dma_chan) == AM_ERROR) {
        return AM_ERROR;
    } else {
        /*�����·��������ʹ��*/
        am_clk_enable(CLK_PTDIS);

        am_mdelay(500);

        /* ���ô���ԴΪ�ڲ��¼����� */
        am_hc32f460_dma_chan_src_set(p_dma_dev, dma_chan, EVT_AOS_STRG);

        return AM_OK;
    }

}

/* ����DMA��û��ʹ��MPUʱ�Ƿ��������� */
am_err_t dma_test(am_hc32f460_dma_dev_t *p_dma_dev, int dma_chan) {

    uint32_t i;

    for (i = 0; i < 32; i++) {
        g_buf_src[i] = i;
        g_buf_dst[i] = 0;
    }

    am_hc32f460_dma_chan_start(p_dma_dev, dma_chan);

    /* ���ʹ���ڲ������¼�����DMA */
    *(volatile uint32_t *)HC32F460_AOS_BASE = 0x1;

    while(g_trans_done == AM_FALSE); /* �ȴ�������� */

    g_trans_done = AM_FALSE;

    am_hc32f460_dma_chan_stop(p_dma_dev, dma_chan);

    for (i = 0; i < __REGION_SIZE; i++) {
        if (g_buf_dst[i] != g_buf_src[i]) {
            return AM_ERROR;
        }
    }

    return AM_OK;
}

/* ���Կ���MPU��DMA�Ƿ��ܷ��ʵ����� */
am_err_t dma_mpu_test(am_hc32f460_dma_dev_t *p_dma_dev, int dma_chan) {

    uint32_t i = 0;

    for (i = 0; i < __REGION_SIZE; i++) {
        g_buf_src[i] = i;
        g_buf_dst[i] = 0xFF;
    }

    if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dma_dev,
                                          &g_desc,
                                           AMHW_HC32F460_DMA_MER_TO_MER,
                                           dma_chan) == AM_ERROR) {
        return AM_ERROR;
    }

    am_hc32f460_dma_chan_start(p_dma_dev, dma_chan);

    /* ���ʹ���ڲ������¼�����DMA */
    *(volatile uint32_t *)HC32F460_AOS_BASE = 0x1;

    while(g_trans_done == AM_FALSE); /* �ȴ�������� */

    if (!memcmp(g_buf_src, g_buf_dst, sizeof(g_buf_dst)))
    {
        return AM_ERROR;
    }

    return AM_OK;
}

static am_err_t __smpu1_cfg(void *p_hw_mpu)
{
    /* ����0����ַ���� */
    amhw_hc32f460_mpu_region_base_set(p_hw_mpu, __REGION_NUM, (uint32_t)g_buf_src);

    /* ����0��С���� */
    amhw_hc32f460_mpu_region_size_set(p_hw_mpu, __REGION_NUM, AMHW_HC32F460_MPU_RGSIZE_32BYTE);

    /* ����0дʹ�� */
    amhw_hc32f460_mpu_rgcrn_smpu1_wr_enable(p_hw_mpu, __REGION_NUM);

    /* ����0������ */
    amhw_hc32f460_mpu_rgcrn_smpu1_rd_disable(p_hw_mpu, __REGION_NUM);
	
    /* smpu1ʹ�� */
    amhw_hc32f460_mpu_rgcrn_smpu1_enable(p_hw_mpu, __REGION_NUM);	
  
    /* ���÷����Ƿ�����ʱ�Ĳ���Ϊ���ӣ��������ʶ���0��д���ʺ��ԣ� */
    amhw_hc32f460_mpu_smpu1act_set(p_hw_mpu, AMHW_HC32F460_MPU_ACT_NONEACTION);

    return AM_OK;
}

/**
 * \brief �������
 */
void demo_hc32f460_hw_mpu_entry (void *p_hw_mpu)
{
    /* DMA���� */
    dma_cfg(&DMA_TEST_DEV, DMA_M2M_CH);

    /* ����DMA�Ƿ����� */
    if (dma_test(&DMA_TEST_DEV, DMA_M2M_CH) == AM_OK){
        am_kprintf("dma test success\n");
    } else {
        am_kprintf("dma test failure\n");
    }

    /* ����MPU */
    __smpu1_cfg(p_hw_mpu);

    /* ʹ��MPU */
    amhw_hc32f460_mpu_smpu1_enable(p_hw_mpu);

    /* ����MPU�Ƿ���Ч������Ч����DMA�޷���ȡ��Ӧ�ڴ� */
    if (dma_mpu_test(&DMA_TEST_DEV, DMA_M2M_CH) == AM_OK){
        am_kprintf("mpu test success\n");
    } else {
        am_kprintf("mpu test failure\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f460_hw_mpu] */
/* end of file */
