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
 * \brief DACת�� DMA�����������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   1. ���ڴ�ӡ�� "DMA transfer done!"��
 *   2. ��ӡ����ǰDAC�����ѹֵ��(�����ѹ����Ϊһ�����Ҳ�������ֵ0mv ������ֵ 3300 mv)
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_dac_dma.c src_zlg118_hw_dac_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_dac_dma
 * \copydoc demo_zlg118_hw_dac_dma.c
 */

/** [src_zlg118_hw_dac_dma] */

#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zlg118_dma.h"
#include "hw/amhw_zlg118_dac.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
static amhw_zlg118_dac_t      *gp_hw_dac = NULL;     /**< \brief dac ���� */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zlg118_dma_xfer_desc_t g_desc;             /**< \brief DMA ���������� */

static volatile am_bool_t       g_trans_done = AM_FALSE; /**< \brief ������ɱ�־ */

static int32_t                  g_dma_chan = 0;        /**< \brief DMA ͨ���� */

static uint16_t                 vol_data = 0;          /**< \brief Ŀ������ݻ��� */

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zlg118_dma_isr_connect() ��������
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AM_ZLG116_DMA_INT_ERROR) �� (#AM_ZLG116_DMA_INT_NORMAL)
 *
 * \return ��
 */
static void dac_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZLG118_DMA_INT_COMPLETE) {
        if (flag_chan == g_dma_chan) {

            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief DAC DMA��������
 */
static int dac_dma_tran_cfg (amhw_zlg118_dac_t *p_hw_dac,
                             int32_t           dma_chan)
{

    uint32_t flags;

    /* ����DMA�жϷ����� */
    am_zlg118_dma_isr_connect(dma_chan, dac_dma_isr, (void *)dma_chan);

    /* DMA �������� */
    flags = AMHW_ZLG118_DMA_CHAN_TRANSFER_MODE_BLOCK    | /* SPIֻ�п鴫��ģʽ */
            AMHW_ZLG118_DMA_CHAN_SIZE_16BIT             | /* ����λ�� 8bit */

            AMHW_ZLG118_DMA_CHAN_SRC_ADD_INC_DISABLE     | /* Դ��ַ������ */
            AMHW_ZLG118_DMA_CHAN_RELOAD_SRC_ADD_ENABLE   | /* Դ��ַ����*/

            AMHW_ZLG118_DMA_CHAN_DST_ADD_INC_DISABLE   | /* Ŀ���ַ������ */
            AMHW_ZLG118_DMA_CHAN_RELOAD_DST_ADD_ENABLE | /* Ŀ���ַ���� */

            AMHW_ZLG118_DMA_CHAN_RELOAD_COUNTER_ENABLE  | /* �������������� */
            AMHW_ZLG118_DMA_CHAN_INT_ERR_DISABLE        | /* ��������жϽ��� */
            AMHW_ZLG118_DMA_CHAN_INT_TX_CMP_ENABLE      | /* ��������ж�ʹ�� */
            AMHW_ZLG118_DMA_CHAN_CIRCULAR_MODE_ENABLE ;   /* ����ѭ��ģʽ */

    /* ����ͨ�������� */
    am_zlg118_dma_xfer_desc_build(&g_desc,                      /* ͨ�������� */
                                   (uint32_t)(&vol_data),       /* Դ�����ݻ��� */
                                   (uint32_t)(&(p_hw_dac->dacdhr12r0)), /* Ŀ�����ݻ��� */
                                   1,                           /* ������� */
                                   flags);                      /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_zlg118_dma_xfer_desc_chan_cfg(&g_desc,
                                          AMHW_ZLG118_DMA_PER_TO_MER, /* ���赽 �ڴ� */
                                          (uint8_t)dma_chan) == AM_ERROR) {
        return AM_ERROR;
    } else {
        /* �������� */
    }

    return AM_OK;
}

/**
 * \brief DAC��ʼ��
 */
static void dac_hw_init(amhw_zlg118_dac_t *p_hw_dac,
                        uint32_t           verf)
{

    if (p_hw_dac == NULL){
        return ;
    }

    /* ���òο���ѹԴ */
    amhw_zlg118_dac_chan_sref_sel(p_hw_dac, verf);

    /* ʧ�����������*/
    amhw_zlg118_dac_chan_output_buf_disable(p_hw_dac);

    /* ����ʹ�� */
    amhw_zlg118_dac_chan_trg_enable(p_hw_dac);

    /* ������ʽѡ��  �������*/
    amhw_zlg118_dac_chan_trg_sel(p_hw_dac, AMHW_ZLG118_DAC_CHAN_SOFTWARE_TRG);

    /* ʹ��dacͨ�� */
    amhw_zlg118_dac_chan_enable(p_hw_dac);

}

/**
 * \brief DAC DMA��ʼ��
 */
static void dac_hw_dma_init(amhw_zlg118_dac_t *p_hw_dac)
{
    if (p_hw_dac == NULL){
        return ;
    }

    /* ʹ��DAC DMA���� */
    amhw_zlg118_dac_chan_dma_enbale (p_hw_dac);
}

/**
 * \brief �������
 */
void demo_zlg118_hw_dac_dma_entry(void     *p_hw_dac,
                                  int32_t  dma_src,
                                  int32_t  dma_chan,
                                  uint16_t *vol_val)
{

    int i = 0;

    vol_data = vol_val[0];

    g_dma_chan = dma_chan;

    gp_hw_dac = (amhw_zlg118_dac_t *)p_hw_dac;

    /* DAC ��ʼ�� Ĭ�ϲο���ѹ���� �ⲿ�ο���ѹԴ  PB01*/
    dac_hw_init(gp_hw_dac, AMHW_ZLG118_DAC_CHAN_MASK_EXTER_REF);

    /* DAC DMAʹ�� */
    dac_hw_dma_init(gp_hw_dac);

    /* ��ʼDMA���� */
    dac_dma_tran_cfg(gp_hw_dac, dma_chan);

    /* Ĭ��ͨ��0��ͨ��1���ȼ�һ������ѯ��*/
    am_zlg118_dma_priority_same();

    /* ���ô��������ź���Դ */
    am_zlg118_dma_chan_src_set (dma_chan, dma_src);

    /* ��ʼͨ������ */
    am_zlg118_dma_chan_start(dma_chan);

    AM_FOREVER {

        /* ������� */
        amhw_zlg118_dac_chan_software_trg_enable(gp_hw_dac);

        /* �ȴ�������� */
        while (g_trans_done == AM_FALSE);

        g_trans_done = AM_FALSE;


        if (i == 128 )
        {
            vol_data = vol_val[0];
            i = 0;
        }else{
            i++;
            vol_data = vol_val[i];
        }

        am_kprintf("DMA transfer done!\r\n");
        am_kprintf("mv_out = %d mv\r\n", gp_hw_dac->dacdor0 * 3300 / 4096);

        am_mdelay(1000);
    }

}

