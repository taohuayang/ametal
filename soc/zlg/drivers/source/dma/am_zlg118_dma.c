/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief DMA ����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-17  zp, first implementation
 * \endinternal
 */

#include "am_zlg118_dma.h"
#include "am_int.h"
#include "am_vdebug.h"

/*******************************************************************************
  ˽�ж���
*******************************************************************************/


/** \brief �ж�δ���ӱ�ʶ */
#define __INT_NOT_CONNECTED      0xFF

/** \brief ͨ��δ���ӱ�ʶ */
#define __CHAN_NOT_CONNECTED     0xFF

/** \brief ����ָ��DMA�豸��Ϣ��ָ�� */
#define __DMA_DEVINFO_DECL(p_dma_devinfo, p_dev)  \
        const am_zlg118_dma_devinfo_t *p_dma_devinfo = p_dev->p_devinfo

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief ָ��DMA�豸��ָ�� */
static am_zlg118_dma_dev_t *__gp_dma_dev;

/** \brief DMA�жϻص�������Ϣ���� */
static struct am_zlg118_dma_int_info __dma_int_info[AMHW_ZLG118_DMA_CHAN_CNT];

/** \brief DMA�жϻص�������Ϣӳ�� */
static uint8_t __dma_int_map[AMHW_ZLG118_DMA_CHAN_CNT];


/*******************************************************************************
  ��������
*******************************************************************************/

/* �������������� */
int am_zlg118_dma_xfer_desc_build (amhw_zlg118_dma_xfer_desc_t *p_desc,
                                   uint32_t                     src_addr,
                                   uint32_t                     dst_addr,
                                   uint32_t                     nbytes,
                                   uint32_t                     flags)
{
    if (p_desc == NULL) {
        return AM_ERROR;
    }

    if (nbytes > 0xFFFF) {
        return AM_ERROR;
    }

    p_desc->xfercfg  = flags;
    p_desc->src_addr = src_addr;
    p_desc->dst_addr = dst_addr;
    p_desc->nbytes   = nbytes;

    return AM_OK;
}

/* ��ʼDMA���� */
int am_zlg118_dma_xfer_desc_chan_cfg (amhw_zlg118_dma_xfer_desc_t    *p_desc,
                                      amhw_zlg118_dma_transfer_type_t type,
                                      uint8_t                         chan)
{

    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)
                                  p_dma_devinfo->dma_reg_base;

    if (p_desc == NULL) {
        return AM_ERROR;
    }

    if (chan > AMHW_ZLG118_DMA_CHAN_CNT) {
        return AM_ERROR;
    }

    switch(type) {

    case AMHW_ZLG118_DMA_PER_TO_MER:
    case AMHW_ZLG118_DMA_MER_TO_PER:
    case AMHW_ZLG118_DMA_MER_TO_MER:
    case AMHW_ZLG118_DMA_PER_TO_PER:

        amhw_zlg118_dma_chan_src_address_set(p_hw_dma,
                                             chan,
                                             p_desc->src_addr);

        amhw_zlg118_dma_chan_dst_address_set(p_hw_dma,
                                             chan,
                                             p_desc->dst_addr);
        break;

    default:
        break;
    }

    amhw_zlg118_dma_chan_tran_data_num_set(p_hw_dma,
                                           chan,
                                           p_desc->nbytes - 1);

    amhw_zlg118_dma_chan_config_set(p_hw_dma,
                                    chan,
                                    p_desc->xfercfg);

    return AM_OK;
}

/* ͨ�����ȼ��趨��ͨ��0���ȼ���� */
void am_zlg118_dma_priority_ch0_highest (void)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_priority_set(p_hw_dma, AMHW_ZLG118_DMA_CHAN_PRIORITY_CH0_BEST);
}

/* ͨ�����ȼ��趨��ͨ�����ȼ���ͬ����ѯ�� */
void am_zlg118_dma_priority_same (void)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_priority_set(p_hw_dma, AMHW_ZLG118_DMA_CHAN_PRIORITY_POLL);
}

/* �趨ͨ������Ĵ���Դ����鿴zlg118_dma_chan.h�궨�壩*/
void am_zlg118_dma_chan_src_set (int chan, uint8_t src)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_chan_trigger_src_set(p_hw_dma, chan, src);
}

/* ��ʼͨ������ */
int am_zlg118_dma_chan_start (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_enable(p_hw_dma);

    amhw_zlg118_dma_chan_enable(p_hw_dma, chan);

    return AM_OK;
}

/* ֹͣͨ������ */
int am_zlg118_dma_chan_stop (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_chan_int_disable(p_hw_dma,
                                     chan,
                                     AMHW_ZLG118_DMA_CHAN_INT_TX_CMP);

    amhw_zlg118_dma_disable(p_hw_dma);

    amhw_zlg118_dma_chan_disable(p_hw_dma, chan);

    return AM_OK;
}

/* ����ԴΪ����ǣ����������� */
/* ������䴥�����������ͨ����ʼ���䡣������ɺ� DMA�����λ������λ�ڴ�������"0"�� ����ֹͣ��*/
void am_zlg118_dma_chan_soft_ask_start (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_chan_soft_transfer_ask(p_hw_dma, chan, 1);
}

/* ����ԴΪ����ǣ��������ֹͣ */
/* ������䴥�����������ͨ����ʼ���䡣������ɺ� DMA�����λ������λ�ڴ�������"0"�� ����ֹͣ��*/
void am_zlg118_dma_chan_soft_ask_stop (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);

    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_chan_soft_transfer_ask(p_hw_dma, chan, 0);
}

/* DMA�жϴ����� */
static void __dma_int_handler (void *p_arg)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    int      i;
    int      chan = 0xFF;
    uint8_t  flag = 0xFF;

    am_zlg118_pfn_dma_isr_t  pfn_isr;
    void                    *p_isr_arg;

    for (i = 0 ; i < AMHW_ZLG118_DMA_CHAN_CNT; i++) {
        if (amhw_zlg118_dma_chan_stat_check(
                p_hw_dma, i, AMHW_ZLG118_DMA_FLAG_TX_COMPLETE) == AM_TRUE){

            chan = i;
            flag = AM_ZLG118_DMA_INT_COMPLETE;
            amhw_zlg118_dma_chan_flag_clear(p_hw_dma, i);

        } else if (amhw_zlg118_dma_chan_stat_check(
                p_hw_dma, i, AMHW_ZLG118_DMA_FLAG_ERR_ADDR_OVERFLOW) == AM_TRUE){

            chan = i;
            flag = AM_ZLG118_DMA_INT_ERR_ADDR_OVERFLOW;
            amhw_zlg118_dma_chan_flag_clear(p_hw_dma, i);

        } else if (amhw_zlg118_dma_chan_stat_check(
                p_hw_dma, i, AMHW_ZLG118_DMA_FLAG_STOP_ASK) == AM_TRUE){

            chan = i;
            flag = AM_ZLG118_DMA_INT_ERR_STOPASK;
            amhw_zlg118_dma_chan_flag_clear(p_hw_dma, i);

        } else if (amhw_zlg118_dma_chan_stat_check(
                p_hw_dma, i, AMHW_ZLG118_DMA_FLAG_ERR_SRCADDR) == AM_TRUE){

            chan = i;
            flag = AM_ZLG118_DMA_INT_ERR_SRCADDR;
            amhw_zlg118_dma_chan_flag_clear(p_hw_dma, i);

        } else if (amhw_zlg118_dma_chan_stat_check(
                p_hw_dma, i, AMHW_ZLG118_DMA_FLAG_ERR_DSTADDR) == AM_TRUE) {

            chan = i;
            flag = AM_ZLG118_DMA_INT_ERR_DSTADDR;
            amhw_zlg118_dma_chan_flag_clear(p_hw_dma, i);

        } else if (amhw_zlg118_dma_chan_stat_check(
                p_hw_dma, i, AMHW_ZLG118_DMA_FLAG_TX_STOP) == AM_TRUE) {

            chan = i;
            flag = AM_ZLG118_DMA_INT_ERR_STOP;
            amhw_zlg118_dma_chan_flag_clear(p_hw_dma, i);
        }

        if (0xFF != chan) {

            pfn_isr   = __dma_int_info[chan].pfn_isr;
            p_isr_arg = __dma_int_info[chan].p_arg;

            if (pfn_isr) {
                pfn_isr(p_isr_arg , flag);
            }
        }
    }
}

/* ����DMA�жϷ����� */
int am_zlg118_dma_isr_connect (int                        chan,
                               am_zlg118_pfn_dma_isr_t    pfn_isr,
                                void                     *p_arg)
{
    if (__dma_int_map[chan] == __INT_NOT_CONNECTED) {
        __dma_int_info[chan].pfn_isr = pfn_isr;
        __dma_int_info[chan].p_arg   = p_arg;
        __dma_int_map[chan]          = chan;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}

/* ɾ��DMA�жϷ��������� */
int am_zlg118_dma_isr_disconnect (int                     chan,
                                  am_zlg118_pfn_dma_isr_t pfn_isr,
                                  void                   *p_arg)
{
    if (__dma_int_map[chan] == chan) {
        __dma_int_info[chan].pfn_isr = NULL;
        __dma_int_map[chan]          = __INT_NOT_CONNECTED;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}

/**
 * \breif ��ȡĳͨ����ǰ����ʣ����ֽ���
 */
uint16_t am_zlg118_dma_tran_data_get (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    return amhw_zlg118_dma_chan_tran_data_num_get(p_hw_dma, chan) + 1;
}

/**
 * \brief ���ô�����ֽ���
 */
void am_zlg118_dma_tran_data_size (int chan, uint32_t trans_data_byte)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_chan_tran_data_num_set(p_hw_dma,
                                           chan,
                                           trans_data_byte - 1);
}

/**
 * \brief ����������
 */
void am_zlg118_dma_block_data_size (int chan, uint8_t block_data_num)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_zlg118_dma_t *p_hw_dma = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    amhw_zlg118_dma_chan_bc_set(p_hw_dma,
                                chan,
                                block_data_num - 1);
}

/* DMA��ʼ�� */
int am_zlg118_dma_init (am_zlg118_dma_dev_t           *p_dev,
                        const am_zlg118_dma_devinfo_t *p_devinfo)
{
    uint32_t i = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return AM_ERROR;
    }

    p_dev->p_devinfo = p_devinfo;
    __gp_dma_dev     = p_dev;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    for (i = 0; i < AMHW_ZLG118_DMA_CHAN_CNT; i++) {
        __dma_int_info[i].pfn_isr = NULL;
        __dma_int_map[i]          = __INT_NOT_CONNECTED;
    }

    am_int_connect(p_devinfo->inum, __dma_int_handler, (void *)0);
    am_int_enable(p_devinfo->inum);

    return AM_OK;
}

/* DMAȥ��ʼ�� */
void am_zlg118_dma_deinit (void)
{
    am_zlg118_dma_devinfo_t *p_dma_devinfo = NULL;
    amhw_zlg118_dma_t       *p_hw_dma;
    
    int i = 0;

    if (NULL == __gp_dma_dev) {
        return;
    }

    p_dma_devinfo = (am_zlg118_dma_devinfo_t *)__gp_dma_dev->p_devinfo;
    p_hw_dma      = (amhw_zlg118_dma_t *)p_dma_devinfo->dma_reg_base;

    for (i = 0; i < AMHW_ZLG118_DMA_CHAN_CNT; i++) {
        __dma_int_info[i].pfn_isr = NULL;
        __dma_int_map[i]          = 0;
        amhw_zlg118_dma_chan_disable(p_hw_dma , i);
    }

    am_int_disconnect(p_dma_devinfo->inum, __dma_int_handler, (void *)0);

    am_int_disable(p_dma_devinfo->inum);


    if (p_dma_devinfo->pfn_plfm_deinit) {
        p_dma_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
