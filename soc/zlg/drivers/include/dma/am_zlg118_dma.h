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
 * \brief DMA����������DMA�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-17  zp, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG118_DMA_H
#define __AM_ZLG118_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_zlg118_dma.h"

/**
 * \addtogroup am_zlg118_if_dma
 * \copydoc am_zlg118_dma.h
 * @{
 */

/**
 * \name ͨ�������жϱ�־
 * \anchor am_zlg118_dma_chan_cfg_flags
 * @{
 */

#define AM_ZLG118_DMA_INT_COMPLETE            0  /** \brief ����жϱ�ʶ */
#define AM_ZLG118_DMA_INT_ERR_ADDR_OVERFLOW   1  /** \brief ��ַ���������� */
#define AM_ZLG118_DMA_INT_ERR_STOPASK         2  /** \brief ����ֹͣ����������ֹ */
#define AM_ZLG118_DMA_INT_ERR_SRCADDR         3  /** \brief ����Դ��ַ���ʴ��� */
#define AM_ZLG118_DMA_INT_ERR_DSTADDR         4  /** \brief ����Ŀ�ĵص�ַ���ʴ��� */
#define AM_ZLG118_DMA_INT_ERR_STOP            5  /** \brief ������ͣ */

/** @} */

/** \brief DMA�жϻص��������� */
typedef void (*am_zlg118_pfn_dma_isr_t)(void *p_arg, uint32_t flag);

/** \brief DMA�жϻص�������Ϣ */
struct am_zlg118_dma_int_info {

    /** \brief DMA�����ص����� */
    am_zlg118_pfn_dma_isr_t  pfn_isr;

    /** \brief �ص������ĵ�һ����ڲ��� */
    void                    *p_arg;
};

/** \brief DMA�豸��Ϣ */
typedef struct am_zlg118_dma_devinfo {

    /** \brief ָ��DMA�Ĵ������ָ�� */
    uint32_t   dma_reg_base;

    /** \brief DMA�жϺſ�ʼ */
    uint8_t    inum;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_zlg118_dma_devinfo_t;

/**
 * \brief DMA�豸ʵ��
 */
typedef struct am_zlg118_dma_dev {

    /** \brief ָ��DMA�豸��Ϣ��ָ�� */
    const am_zlg118_dma_devinfo_t *p_devinfo;

}am_zlg118_dma_dev_t;

/**
 * \brief ����ͨ��0���ȼ����
 */
void am_zlg118_dma_priority_ch0_highest (void);

/**
 * \brief ����ͨ��0��ͨ��1���ȼ���ͬ��������ѯ��ʽ��������
 */
void am_zlg118_dma_priority_same (void);

/**
 * \brief ����ԴΪ����ǣ�����������
 */
void am_zlg118_dma_chan_soft_ask_start (int chan);

/**
 * \brief ����ԴΪ����ǣ��������ֹͣ
 */
void am_zlg118_dma_chan_soft_ask_stop (int chan);

/**
 * \brief ����DMA����ͨ��
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 * \param[in] src  : �趨ͨ������Ĵ���Դ����鿴zlg118_dma_chan.h�궨�壩
 *
 */
void am_zlg118_dma_chan_src_set (int chan, uint8_t src);

/**
 * \brief ����DMA����ͨ��
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 * \param[in] src  : �趨ͨ������Ĵ���Դ����鿴zlg118_dma_chan.h�궨�壩
 *
 * \retval AM_OK    : ���óɹ�
 * \retval AM_ERROR : ���ô��󣬸�ͨ��֮ǰ���ù�
 */
int am_zlg118_dma_chan_start (int chan);

/**
 * \brief ֹͣͨ������
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 *
 * \retval AM_OK   : �����ɹ�
 */
int am_zlg118_dma_chan_stop (int chan);

/**
 * \brief ��������������
 *
 * \param[in] p_desc   : ָ��DMA������������ָ��
 * \param[in] src_addr : Դ���׵�ַ
 * \param[in] dst_addr : Ŀ����׵�ַ
 * \param[in] nbytes   : �����ֽ���
 * \param[in] flags    : ���ò���
 *
 * \retval  AM_OK      : �����ɹ�
 * \retval -AM_EINVAL  : δ���룬��Ч����
 */
int am_zlg118_dma_xfer_desc_build (amhw_zlg118_dma_xfer_desc_t *p_desc,
                                   uint32_t                  src_addr,
                                   uint32_t                  dst_addr,
                                   uint32_t                  nbytes,
                                   uint32_t                  flags);

/**
 * \brief ��ʼDMA����
 *
 * \param[in] p_desc  : ָ��DMA������������ָ��
 * \param[in] type    : DMA����ģʽ���� ���ж�Ӧ��ö����dma_transfer_type_t
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 */
int am_zlg118_dma_xfer_desc_chan_cfg (amhw_zlg118_dma_xfer_desc_t    *p_desc,
                                      amhw_zlg118_dma_transfer_type_t type,
                                      uint8_t                         chan);

/**
 * \brief ����DMA�ص�����
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AM_ZLG118_DMA_INT*
 *            �����ļ��Ϸ��궨�崦
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ��� �������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ���ӳɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_zlg118_dma_isr_connect (int                       chan,
                               am_zlg118_pfn_dma_isr_t      pfn_isr,
                               void                     *p_arg);

/**
 * \brief ɾ��DMA�ص�����������
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AM_ZLG118_DMA_INT*
 *            �����ļ��Ϸ��궨�崦
 *            �ûص������ĵ����������ǲ����жϵ�ͨ������ȡֵ��Χ��DMA_CHAN_* (#DMA_CHAN_1)
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ����������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ɾ���ɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_zlg118_dma_isr_disconnect (int                      chan,
                                  am_zlg118_pfn_dma_isr_t  pfn_isr,
                                  void                    *p_arg);

/**
 * \breif ��ȡ  ĳͨ����ǰ����ʣ����ֽ���
 *
 * \param[in] chan DMA ͨ���ţ�ֵΪ DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 *
 * \retval  �ֽ���
 */
uint16_t am_zlg118_dma_tran_data_get (int chan);

/**
 * \breif ���� ĳͨ����ǰ����ʣ����ֽ���
 *
 * \param[in] chan            DMA ͨ���ţ�ֵΪ DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 * \param[in] trans_data_byte Ҫ������ֽ���
 *
 * \retval  ��
 *
 * \note �����ô�����ֽ���֮ǰ����ֹͣͨ������
 */
void am_zlg118_dma_tran_data_size (int chan, uint32_t trans_data_byte);

/**
 * \breif ����ÿ�δ���ʱ�����С
 *
 * \param[in] chan            DMA ͨ���ţ�ֵΪ DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_2)
 * \param[in] block_data_num  ���С����
 *
 * \retval  ��
 *
 * \note �����ô�����ֽ���֮ǰ����ֹͣͨ������
 */
void am_zlg118_dma_block_data_size (int chan, uint8_t block_data_num);

/**
 * \brief DMA��ʼ��
 *
 * \param[in] p_dev         : ָ��DMA�豸��ָ��
 * \param[in] p_dma_devinfo : ָ��DMA�豸��Ϣ��ָ��
 *
 * \retval  AM_OK       : ��ʼ���ɹ�
 */
int am_zlg118_dma_init (am_zlg118_dma_dev_t           *p_dev,
                        const am_zlg118_dma_devinfo_t *p_dma_devinfo);

/**
 * \brief DMAȥ��ʼ��
 *
 * \return ��
 */
void am_zlg118_dma_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_DMA_H */

/* end of file */
