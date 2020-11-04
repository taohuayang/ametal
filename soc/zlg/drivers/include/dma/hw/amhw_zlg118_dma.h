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
 * \brief DMA hardware operation interface.
 *
 * 1. 2 independent programmable DMA channel.
 * 2. 8,16,32 bits data to transfer.
 * 3. support programmable source address,destination address and data size��
 *
 * ����һ�� Ӳ������� AMHW_ZLG118_DMA_CHAN_CNT���������� DMAͨ����Ŀ��ʹ�ñ��ļ�ʱ��
 * Ӧ�� soc_cfg.h �ļ��ж���úꡣ
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG118_DMA_H
#define __AMHW_ZLG118_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"
#include "soc_cfg.h"
#include "am_vdebug.h"
/**
 * \addtogroup amhw_zlg118_if_dma
 * \copydoc amhw_zlg118_dma.h
 * @{
 */

/** \brief DMA ͨ����Ŀ  */
#define AMHW_ZLG118_DMA_CHAN_CNT  SOC_CFG_ZLG_DMA_CHAN_CNT

/**
 * \brief structure of DMA controller register
 */
typedef struct amhw_zlg118_dma_chan {
    __IO uint32_t  dma_conf;           /**< \brief ����ͨ�����üĴ��� */
         uint32_t  reserved[3];        /**< \brief Reserved */
    struct {                        
        __IO uint32_t  dma_confa;      /**< \brief ͨ������A�Ĵ��� */
        __IO uint32_t  dma_confb;      /**< \brief ͨ������B�Ĵ��� */
        __IO uint32_t  dma_srcadr;     /**< \brief ͨ������Դ��ַ�Ĵ��� */
        __IO uint32_t  dma_dstadr;     /**< \brief ͨ������Ŀ�ĵ�ַ�Ĵ��� */
    } chcfg[AMHW_ZLG118_DMA_CHAN_CNT]; /**< \brief DMAͨ���ṹ�� */

} amhw_zlg118_dma_t;

/**
 * \brief DMA transfer mode select
 */
typedef enum {
    AMHW_ZLG118_DMA_PER_TO_MER,     /**< \brief DMA peripheral to memory mode */
    AMHW_ZLG118_DMA_MER_TO_PER,     /**< \brief DMA memory to peripheral mode */
    AMHW_ZLG118_DMA_MER_TO_MER,     /**< \brief DMA memory to memory mode */
    AMHW_ZLG118_DMA_PER_TO_PER      /**< \brief DMA peripheral to peripheral mode */
} amhw_zlg118_dma_transfer_type_t;

/**
 * \brief DMA descriptor
 */
typedef struct amhw_zlg118_dma_xfer_desc {
    volatile uint32_t          xfercfg;        /**< \brief transfer configuration */
    volatile uint32_t          src_addr;       /**< \brief source address */
    volatile uint32_t          dst_addr;       /**< \brief destination address */
    volatile uint32_t          nbytes;         /**< \brief the bytes of data to transfer */
} amhw_zlg118_dma_xfer_desc_t;

/**
 * \brief DMA ͨ����ʹ�ܿ���λ     ʹ��
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_enable(amhw_zlg118_dma_t *p_hw_dma)
{
    p_hw_dma->dma_conf |= (0x1ul << 31);
}

/**
 * \brief DMA ͨ����ʹ�ܿ���λ     ����
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_disable(amhw_zlg118_dma_t *p_hw_dma)
{
    p_hw_dma->dma_conf &= ~(0x1ul << 31);
}

/**
 * \brief DMA ����ͨ���Ĵ���״̬   ��ȡ
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 *
 * \note  ��������κ�����ڴ����з����� DMAC ����λ�á�1����
 *            1.��"0"д�� CONF:EN λ�� ��������ͨ�����������
 *            2.����"0000"���ֵд�� CONF:HALT λ�� ��������ͨ��������ͣ��
 *
 *        �� CONF:EN=1�� CONF:HALT=0000��Ч���������е�ͨ��ʹ�ܲ����� ��λ���㡣
 *
 * \return none
 */
am_static_inline
am_bool_t amhw_zlg118_dma_transfer_check (amhw_zlg118_dma_t  *p_hw_dma)
{
    return ((p_hw_dma->dma_conf >> 30) & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief DMA ����ͨ���Ĵ���״̬   ����
 *
 * \param[in] p_hw_dma : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] set      : ����ֵ
 *
 * \note  ���ܱ�λ�������� RW,CPUд"1"��Ӱ�� DMA�Ĳ�����Ȼ�����
 *        CONF�Ĵ�����Ҫ���¶��ֲ���ı䵱ǰλ�� Ӧ�����ȶ������λ��Ȼ������д��ͬ����ֵ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_transfer_set (amhw_zlg118_dma_t *p_hw_dma, uint8_t set)
{
    p_hw_dma->dma_conf = (p_hw_dma->dma_conf & (~(0x1ul << 30))) |
                         ((set & 0x1ul) << 30);
}

/**< \brief DMA ��ͨ�����ȼ��̶��� CH0 ���ȼ� > CH1 ���ȼ� */
#define  AMHW_ZLG118_DMA_CHAN_PRIORITY_CH0_BEST   (0ul << 28)
/**< \brief DMA ��ͨ�����ȼ�������ѯ��ʽ���� */
#define  AMHW_ZLG118_DMA_CHAN_PRIORITY_POLL       (1ul << 28)
/**
 * \brief DMA ͨ�����ȼ�����
 *
 * \param[in] p_hw_dma : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] set      : ���ȼ��궨��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_priority_set (amhw_zlg118_dma_t *p_hw_dma, uint32_t set)
{
    p_hw_dma->dma_conf = (p_hw_dma->dma_conf & (~(1ul << 28))) | set;
}

/**
 * \brief DMA  HALTλ��������ͨ���Ĵ�����ͣ��ȡ����
 *
 * \param[in] p_hw_dma : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] set      : ����ֵ
 *
 * \note  ����Щλ����Ϊ"0000"�����ֵʱ,�������ڴ����ͨ��������ͣ״̬��
 *        ������Ϊ"0000"�� ���д��������
 *
 *        ���������ⲿ��������Ĵ���������Ч����ͣ״̬��ͨ�����Դ�����������ǿ鴫���ͻ�����䣬
 *        ������ͣ����� ��ص�ͨ��Ҳ���������䡣Ϊ����ɴ����������ͣ�Ĵ��䣬��Ҫ����ͣȡ����
 *        ������Ĵ�������
 *
 *        ��Щλ����������ͣ���������λ��ͨ�������üĴ�����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_halt_set (amhw_zlg118_dma_t *p_hw_dma, uint8_t set)
{
    p_hw_dma->dma_conf = (p_hw_dma->dma_conf & (~(0xful << 24))) |
                         ((set & 0xful) << 24);
}

/**
 * \brief DMA ĳһͨ����ʹ�ܿ���λ    ʹ��
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 *
 * \note ����λ��"1", ���ͨ��ʹ�ܣ��ȴ���������ʼ���书��(CONF:EN ������ "1")��
 *       ��� MSK λ (CONFB[0]) λ�� "0"�� DMA����ɴ���������λ����"0"��
 *       ����λΪ"0", ���ͨ����ֹ�����������ݴ��䡣ͬʱ�� ��������ڴ�������У���ôֹͣ���䡣
 *       ��λ������ǿ��ֹͣ���ڴ�����������ͨ����ͬʱ��λ���üĴ�����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_enable(amhw_zlg118_dma_t *p_hw_dma,
                                 uint8_t            channel)
{
    p_hw_dma->chcfg[channel].dma_confa |= (0x1ul << 31);
}

/**
 * \brief DMA ĳһͨ����ʹ�ܿ���λ    ����
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 *
 * \note ����λ��"1", ���ͨ��ʹ�ܣ��ȴ���������ʼ���书��(CONF:EN ������ "1")��
 *       ��� MSK λ (CONFB[0]) λ�� "0"�� DMA����ɴ���������λ����"0"��
 *       ����λΪ"0", ���ͨ����ֹ�����������ݴ��䡣ͬʱ�� ��������ڴ�������У���ôֹͣ���䡣
 *       ��λ������ǿ��ֹͣ���ڴ�����������ͨ����ͬʱ��λ���üĴ�����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_disable(amhw_zlg118_dma_t *p_hw_dma,
                                  uint8_t            channel)
{
    p_hw_dma->chcfg[channel].dma_confa &= ~(0x1ul << 31);
}

/**
 * \brief DMA PASλ���Ƹ���ͨ���Ĵ�����ͣ��ȡ��        ��ͣ
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 *
 * \note ����λ�� "1" ��������ڴ����ͨ��������ͣ״̬�������λ�� 0�����¿�ʼ���䡣
 *       ��λ���Ϊ"0" ��ͨ���Ĵ�������󡣼����ⲿ�����贫��������Ч����ͣ״̬ͨ��
 *       ���Դ�����������ǿ鴫���ͻ�����䣬���ͨ�����Ὺʼ���䣬��ʹ���������ͣλ��
 *       Ϊ�������ͣ�Ĵ��䣬�������ͣ��������Ĵ�������
 *
 *       ��λ��������ͣ���������λ���ͨ�������üĴ�����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_stop(amhw_zlg118_dma_t *p_hw_dma,
                                 uint8_t          channel)
{
    p_hw_dma->chcfg[channel].dma_confa |= (0x1ul << 30);
}

/**
 * \brief DMA PASλ���Ƹ���ͨ���Ĵ�����ͣ��ȡ��        ��ʼ
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 *
 * \note ����λ�� "1" ��������ڴ����ͨ��������ͣ״̬�������λ�� 0�����¿�ʼ���䡣
 *       ��λ���Ϊ"0" ��ͨ���Ĵ�������󡣼����ⲿ�����贫��������Ч����ͣ״̬ͨ��
 *       ���Դ�����������ǿ鴫���ͻ�����䣬���ͨ�����Ὺʼ���䣬��ʹ���������ͣλ��
 *       Ϊ�������ͣ�Ĵ��䣬�������ͣ��������Ĵ�������
 *
 *       ��λ��������ͣ���������λ���ͨ�������üĴ�����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_start(amhw_zlg118_dma_t *p_hw_dma,
                                  uint8_t          channel)
{
    p_hw_dma->chcfg[channel].dma_confa &= ~(0x1ul << 30);
}

/**
 * \brief DMA ST λ���ڲ�������ͨ���������������
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] stat       : ����ֵ
 *
 * \note ����λ��"1", ������䴥�����������ͨ����ʼ���䡣������ɺ� DMA�����λ��"0"��
 *       ����λ�ڴ�������"0"�� ����ֹͣ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_soft_transfer_ask(amhw_zlg118_dma_t *p_hw_dma,
                                            uint8_t            channel,
                                            uint8_t            stat)
{
    p_hw_dma->chcfg[channel].dma_confa =
        (p_hw_dma->chcfg[channel].dma_confa & (~(0x1ul << 29))) |
        ((stat & 0x1ul) << 29) ;
}

/**
 * \brief DMA TRI_SEL[6:0]λѡ��������Ĵ���Դ
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] src        : ���������趨����鿴zlg118_dma_chan.h�궨�壩
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_trigger_src_set(amhw_zlg118_dma_t *p_hw_dma,
                                          uint8_t            channel,
                                          uint8_t            src)
{
    p_hw_dma->chcfg[channel].dma_confa =
        (p_hw_dma->chcfg[channel].dma_confa & (~(0x7ful << 22))) |
        ((src & 0x7ful) << 22) ;
}

/**
 * \brief DMA BC[3:0]λָ����/ͻ������ĸ���
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] num        : ����ֵ
 *
 * \note ����Ϊ������ʱ������"0000"��
 *       ����"BC[3:0]=������ - 1"�����������Ŀ���Ϊ 16��
 *
 *       �⼸λ�ڴ���Ĺ����п���ȥ����ͨ���������һ��Դ��ַ���ʣ�����һ��Ŀ�ĵ�ַ�ķ��ʳɹ���ɣ�
 *       BC[3:0] ��ȥ 1��
 *
 *       �� CONFB:RC=1 ������£����俪ʼʱ���õ�ֵ���ڴ�����ɺ����ء�
 *       �� CONFB:RC=0 ������£��ɹ���ɴ���󣬸�λ���㣬ͬʱ�ڴ�����ͣ����Ĵ���ǳɹ����ʱ����ֵ���ֲ��䡣
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_bc_set(amhw_zlg118_dma_t *p_hw_dma,
                                 uint8_t            channel,
                                 uint8_t            num)
{
    p_hw_dma->chcfg[channel].dma_confa =
        (p_hw_dma->chcfg[channel].dma_confa & (~(0xful << 16))) |
        ((num & 0xful) << 16);
}

/**
 * \brief DMA TC[15:0] λ����ָ����/ͻ��/������Ĵ��������
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] num        : ����ֵ
 *
 * \note �趨ֵ"TC = �������� - 1". �������Ϊ 65536��
 *
 *       ����ʱ����Щֵ�ǿ��Զ��ġ������������һ�ο鴫����ɣ� TC ��ȥ 1
 *
 *       �� CONFB:RC=1 ������£����俪ʼʱ���õ�ֵ���ڴ�����ɺ����ء�
 *       �� CONFB:RC=0 ������£��ɹ���ɴ���󣬸�λ���㣬ͬʱ�ڴ�����ͣ����Ĵ���ǳɹ����ʱ����ֵ���ֲ��䡣
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_tran_data_num_set (amhw_zlg118_dma_t *p_hw_dma,
                                             uint8_t            channel,
                                             uint16_t           num)
{
    p_hw_dma->chcfg[channel].dma_confa =
        (p_hw_dma->chcfg[channel].dma_confa & (~(0xfffful << 0))) |
        ((num & 0xfffful) << 0);
}

/**
 * \brief DMA TC[15:0] λ����ָ����/ͻ��/������Ĵ��������     ��ȡ
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 *
 * \note �趨ֵ"TC = �������� - 1". �������Ϊ 65536��
 *
 *       ����ʱ����Щֵ�ǿ��Զ��ġ������������һ�ο鴫����ɣ� TC ��ȥ 1
 *
 *       �� CONFB:RC=1 ������£����俪ʼʱ���õ�ֵ���ڴ�����ɺ����ء�
 *       �� CONFB:RC=0 ������£��ɹ���ɴ���󣬸�λ���㣬ͬʱ�ڴ�����ͣ����Ĵ���ǳɹ����ʱ����ֵ���ֲ��䡣
 *
 * \return ��ǰ����ʣ����ֽ���
 */
am_static_inline
uint16_t amhw_zlg118_dma_chan_tran_data_num_get (amhw_zlg118_dma_t *p_hw_dma,
                                                 uint8_t            channel)
{
    return ( p_hw_dma->chcfg[channel].dma_confa & 0xfffful);
}


#define  AMHW_ZLG118_DMA_CHAN_TRANSFER_MODE_BLOCK    (0UL << 28) /**< \brief Block����ģʽ */
#define  AMHW_ZLG118_DMA_CHAN_TRANSFER_MODE_BURST    (1UL << 28) /**< \brief Burst����ģʽ */

#define  AMHW_ZLG118_DMA_CHAN_SIZE_8BIT              (0UL << 26) /**< \brief ���ݿ�� 8bit */
#define  AMHW_ZLG118_DMA_CHAN_SIZE_16BIT             (1UL << 26) /**< \brief ���ݿ�� 16bit */
#define  AMHW_ZLG118_DMA_CHAN_SIZE_32BIT             (2UL << 26) /**< \brief ���ݿ�� 32bit */

#define  AMHW_ZLG118_DMA_CHAN_SRC_ADD_INC_DISABLE    (1UL << 25) /**< \brief Դ��ַ�������� */
#define  AMHW_ZLG118_DMA_CHAN_SRC_ADD_INC_ENABLE     (0UL << 25) /**< \brief Դ��ַ����ʹ�� */

#define  AMHW_ZLG118_DMA_CHAN_DST_ADD_INC_DISABLE    (1UL << 24) /**< \brief Ŀ���ַ��������  */
#define  AMHW_ZLG118_DMA_CHAN_DST_ADD_INC_ENABLE     (0UL << 24) /**< \brief Ŀ���ַ����ʹ��  */

#define  AMHW_ZLG118_DMA_CHAN_RELOAD_COUNTER_DISABLE (0UL << 23) /**< \brief �������������ؽ���  */
#define  AMHW_ZLG118_DMA_CHAN_RELOAD_COUNTER_ENABLE  (1UL << 23) /**< \brief ��������������ʹ��  */

#define  AMHW_ZLG118_DMA_CHAN_RELOAD_SRC_ADD_DISABLE (0UL << 22) /**< \brief Դ��ַ���ؽ���  */
#define  AMHW_ZLG118_DMA_CHAN_RELOAD_SRC_ADD_ENABLE  (1UL << 22) /**< \brief Դ��ַ����ʹ��  */

#define  AMHW_ZLG118_DMA_CHAN_RELOAD_DST_ADD_DISABLE (0UL << 21) /**< \brief Ŀ���ַ���ؽ���  */
#define  AMHW_ZLG118_DMA_CHAN_RELOAD_DST_ADD_ENABLE  (1UL << 21) /**< \brief Ŀ���ַ����ʹ��  */

#define  AMHW_ZLG118_DMA_CHAN_INT_ERR_DISABLE        (0UL << 20) /**< \brief ��������жϽ���  */
#define  AMHW_ZLG118_DMA_CHAN_INT_ERR_ENABLE         (1UL << 20) /**< \brief ��������ж�ʹ��  */

#define  AMHW_ZLG118_DMA_CHAN_INT_TX_CMP_DISABLE     (0UL << 19) /**< \brief ����жϽ��� */
#define  AMHW_ZLG118_DMA_CHAN_INT_TX_CMP_ENABLE      (1UL << 19) /**< \brief ����ж�ʹ�� */

#define  AMHW_ZLG118_DMA_CHAN_CIRCULAR_MODE_DISABLE  (0UL << 0)  /**< \brief ѭ��ģʽ���� */
#define  AMHW_ZLG118_DMA_CHAN_CIRCULAR_MODE_ENABLE   (1UL << 0)  /**< \brief ѭ��ģʽʹ�� */

/**
 * \brief DMA ͨ������
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] num        : ���ñ�־
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_config_set(amhw_zlg118_dma_t *p_hw_dma,
                                     uint8_t            channel,
                                     uint32_t           flag)

{
    p_hw_dma->chcfg[channel].dma_confb =
        (p_hw_dma->chcfg[channel].dma_confb & (~0x3ff8fffful)) |
        flag;
}


#define  AMHW_ZLG118_DMA_CHAN_INT_ERR      (1UL << 20) /**< \brief δ����ж�  */
#define  AMHW_ZLG118_DMA_CHAN_INT_TX_CMP   (1UL << 19) /**< \brief ����ж� */
/**
 * \brief DMA ĳһͨ���ж�ʹ��
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] num        : ���ñ�־
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_int_enable(amhw_zlg118_dma_t *p_hw_dma,
                                     uint8_t            channel,
                                     uint32_t           flag)
{
    p_hw_dma->chcfg[channel].dma_confb |= flag;
}

/**
 * \brief DMA ĳһͨ���жϽ���
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] num        : ���ñ�־
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_int_disable(amhw_zlg118_dma_t *p_hw_dma,
                                      uint8_t            channel,
                                      uint32_t           flag)
{
    p_hw_dma->chcfg[channel].dma_confb &= ~flag;
}

/**
 * \brief DMA ״̬��־
 *@{
 */
typedef enum {
    AMHW_ZLG118_DMA_FLAG_DEFAULT = 0,               /* ��ʼĬ��ֵ */
    AMHW_ZLG118_DMA_FLAG_ERR_ADDR_OVERFLOW,         /* ��ַ���������� */
    AMHW_ZLG118_DMA_FLAG_STOP_ASK,                  /* ����ֹͣ����������ֹ */
    AMHW_ZLG118_DMA_FLAG_ERR_SRCADDR,               /* ����Դ��ַ���ʴ��� */
    AMHW_ZLG118_DMA_FLAG_ERR_DSTADDR,               /* ����Ŀ�ĵص�ַ���ʴ��� */
    AMHW_ZLG118_DMA_FLAG_TX_COMPLETE,               /* �ɹ�������� */
    AMHW_ZLG118_DMA_FLAG_RESERVE,                   /* ���� */
    AMHW_ZLG118_DMA_FLAG_TX_STOP,                   /* ������ͣ */
}amhw_zlg118_dma_flag_t;


/**
 * \brief ״̬��־��ȡ
 *
 * \param[in] p_hw_dma : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel  : ͨ����
 * \param[in] flag     : ״̬��־
 *
 * \return AM_TRUE or AM_FALSE
 */
am_static_inline
am_bool_t amhw_zlg118_dma_chan_stat_check (amhw_zlg118_dma_t     *p_hw_dma,
                                           uint8_t                channel,
                                           amhw_zlg118_dma_flag_t flag)
{
    return ((((p_hw_dma->chcfg[channel].dma_confb >> 16) & 0x7ul) == flag) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ״̬��־���
 *
 * \param[in] p_hw_dma    : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel     : ͨ����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_flag_clear (amhw_zlg118_dma_t *p_hw_dma,
                                      uint8_t            channel)
{
    p_hw_dma->chcfg[channel].dma_confb &= ~(0x7ul << 16);
}

/**
 * \brief Դ��ַ����
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] address    : ��ַ
 *
 * \note  ��� CONFB:FS=��1��������Դ��ַ�趨Ϊ�̶�ֵ�����Ҳ���ı䡣
 *
 *        ��� CONFB:FS=��0���� �� CONFB:RS=��0��������ʱԴ��ַ���� CONFB:WIDTH[1:0]������λ��������
 *        �������ɹ���ɣ����ֵΪ������ɵ�ַ����һ��ַ���������δ�ɹ���ɣ����ֵΪ��ͣʱ���趨��ֵ
 *
 *        ��� CONFB:FS=��0���� CONFB:RS=��1��������ʱԴ��ַ���� CONFB:WIDTH[1:0]������λ��������
 *        ������ɺ󣬴��俪ʼʱ�趨��Դ��ַ���¼��ص����Ĵ���λ�С�
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_src_address_set(amhw_zlg118_dma_t *p_hw_dma,
                                          uint8_t            channel,
                                          uint32_t           address)
{
    p_hw_dma->chcfg[channel].dma_srcadr = address;
}

/**
 * \brief Ŀ���ַ����
 *
 * \param[in] p_hw_dma   : ָ��DMA�Ĵ����ṹ���ָ��
 * \param[in] channel    : ͨ����
 * \param[in] address    : ��ַ
 *
 * \note  ��� CONFB:FD=��1���� ����Ŀ�ĵ�ַ����Ϊ�̶���ַ�����Ҳ��ı䡣
 *
 *        ��� CONFB:FD=��0���� �� CONFB:RD=��0��, ����ʱĿ�ĵ�ַ���� CONFB:WIDTH[1:0]������λ��
 *        �������������ɹ���ɣ����ֵΪ������ɵ�ַ����һ��ַ���������δ�ɹ���ɣ����ֵΪ��ͣʱ���趨��ֵ��
 *
 *        ��� CONFB:FD=��0�� �� CONFB:RD=��1��, ����ʱĿ�ĵ�ַ���� CONFB:WIDTH[1:0]������λ��
 *        ������������ɺ󣬴��俪ʼʱ�趨��Ŀ�ĵ�ַ���¼��ص����Ĵ���λ�С�

 * \return none
 */
am_static_inline
void amhw_zlg118_dma_chan_dst_address_set(amhw_zlg118_dma_t *p_hw_dma,
                                          uint8_t            channel,
                                          uint32_t           address)
{
    p_hw_dma->chcfg[channel].dma_dstadr = address;
}

/**
 * @} amhw_if_zlg118_dma
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_ZLG118_DMA_H */

/* end of file */
