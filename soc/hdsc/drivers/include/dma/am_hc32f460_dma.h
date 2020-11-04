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
 * \brief DMA����������DMA�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-09-17  cds, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_DMA_H
#define __AM_HC32F460_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_hc32f460_dma.h"
#include "hc32f460_inum.h"

/**
 * \addtogroup am_hc32f460_if_dma
 * \copydoc am_hc32f460_dma.h
 * @{
 */

/**
 * \name ͨ�������жϱ�־
 * \anchor am_hc32f460_dma_chan_cfg_flags
 * @{
 */
#define AM_HC32F460_DMA_INT_DEFAULE           (0 << 0)  /** \brief ���ж�*/
#define AM_HC32F460_DMA_INT_ERR_REQERR        (1 << 0)  /** \brief ������������жϱ�ʶ */
#define AM_HC32F460_DMA_INT_ERR_TRNERR        (1 << 1)  /** \brief ��������жϱ�ʶ */
#define AM_HC32F460_DMA_INT_BLK_COMPLETE      (1 << 2)  /** \brief �鴫������жϱ�ʶ */
#define AM_HC32F460_DMA_INT_COMPLETE          (1 << 3)  /** \brief ����жϱ�ʶ */

/* ʣ�ഫ��������������÷�ʽ */
typedef enum am_hc32f460_dma_rcfg_cntmd {
    AM_HC32F460_DMA_RFG_CNTMD_KEEP            = 0, /* ���ֲ��� */
	AM_HC32F460_DMA_RFG_CNTMD_BY_SRCADDR      = 1, /* ��Դ��ַ��ʽ */
	AM_HC32F460_DMA_RFG_CNTMD_KEEP_BY_DSRADDR = 2  /* ��Ŀ���ַ��ʽ */
} am_hc32f460_dma_rfg_cntmd_t;

/* Ŀ���ַ���÷�ʽ */
typedef enum am_hc32f460_dma_rcfg_darmd {
    AM_HC32F460_DMA_RFG_DARMD_KEEP        = 0, /* ���ֲ��� */
	AM_HC32F460_DMA_RFG_DARMD_NOSEQ       = 1, /* ������ʽ���� */
	AM_HC32F460_DMA_RFG_DARMD_KEEP_REPEAT = 2  /* �ظ�ʽ���� */
} am_hc32f460_dma_rcfg_darmd_t;

/* Դ��ַ���÷�ʽ */
typedef enum am_hc32f460_dma_rcfg_sarmd {
    AM_HC32F460_DMA_RFG_SARMD_KEEP        = 0, /* ���ֲ��� */
	AM_HC32F460_DMA_RFG_SARMD_NOSEQ       = 1, /* ������ʽ���� */
	AM_HC32F460_DMA_RFG_SARMD_KEEP_REPEAT = 2  /* �ظ�ʽ���� */
} am_hc32f460_dma_rcfg_sarmd_t;


/** @} */

/** \brief DMA�жϻص��������� */
typedef void (*am_hc32f460_pfn_dma_isr_t)(void *p_arg, uint32_t flag);

/** \brief DMA�жϻص�������Ϣ */
struct am_hc32f460_dma_int_info {

    /** \brief DMA�����ص����� */
    am_hc32f460_pfn_dma_isr_t  pfn_isr;

    /** \brief �ص������ĵ�һ����ڲ��� */
    void                    *p_arg;
};

/** \brief DMA�豸��Ϣ */
typedef struct am_hc32f460_dma_devinfo {

    /** \brief ָ��DMA�Ĵ������ָ�� */
    uint32_t   dma_reg_base;

    /** \brief DMA�жϺſ�ʼ */
    uint8_t    inum;

    /** \brief DMA�豸ID */
    uint8_t    id;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_hc32f460_dma_devinfo_t;

/**
 * \brief DMA�豸ʵ��
 */
typedef struct am_hc32f460_dma_dev {

    /** \brief ָ��DMA�豸��Ϣ��ָ�� */
    const am_hc32f460_dma_devinfo_t *p_devinfo;

    /** \brief DMA�жϻص�������Ϣ���� */
    struct am_hc32f460_dma_int_info __dma_int_info[AMHW_HC32F460_DMA_CHAN_CNT];

    /** \brief DMA�жϻص�������Ϣӳ�� */
    uint8_t __dma_int_map[AMHW_HC32F460_DMA_CHAN_CNT];

}am_hc32f460_dma_dev_t;



/**
 * \brief ����DMA����ͨ��
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] src  : �趨ͨ������Ĵ���Դ��en_event_src_t��
 *
 */
void am_hc32f460_dma_chan_src_set (am_hc32f460_dma_dev_t *p_dev, int chan, en_event_src_t src);

/**
 * \brief ����DMA����ͨ��
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] src  : �趨ͨ������Ĵ���Դ��en_event_src_t��
 *
 * \retval AM_OK    : ���óɹ�
 * \retval AM_ERROR : ���ô��󣬸�ͨ��֮ǰ���ù�
 */
int am_hc32f460_dma_chan_start (am_hc32f460_dma_dev_t *p_dev, int chan);

/**
 * \brief ֹͣͨ������
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 *
 * \retval AM_OK   : �����ɹ�
 */
int am_hc32f460_dma_chan_stop (am_hc32f460_dma_dev_t *p_dev, int chan);

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
int am_hc32f460_dma_xfer_desc_build (amhw_hc32f460_dma_xfer_desc_t *p_desc,
                                     uint32_t                       src_addr,
                                     uint32_t                       dst_addr,
                                     uint32_t                       nbytes,
                                     uint32_t                       flags);

int am_hc32f460_dma_chain_xfer_desc_build (amhw_hc32f460_dma_chain_xfer_desc_t *p_desc,   /**< \brief �������ṹ��ָ���ַ */
                                           uint32_t                             src_addr, /**< \brief Դ��ַ  */
                                           uint32_t                             dst_addr, /**< \brief Ŀ�ĵ�ַ  */
                                           uint32_t                             count,    /**< \brief �������  */
                                           uint32_t                             blk_size, /**< \brief ���ݿ��С  */
                                           uint32_t                             drpt,     /**< \brief Ŀ���ַ�ظ������С  */
                                           uint32_t                             srpt,     /**< \brief Դ��ַ�ظ������С  */
                                           uint32_t                             snscnt,   /**< \brief Դ��ַ��ת��������  */
                                           uint32_t                             soffset,  /**< \brief Դ��ַ��ת�ĵ�ַƫ����  */
                                           uint32_t                             dnscnt,   /**< \brief Ŀ���ַ��ת��������  */
                                           uint32_t                             dsoffset, /**< \brief Ŀ���ַ��ת�ĵ�ַƫ����  */
                                           uint32_t                             link,     /**< \brief ��һ�δ�������������ڵ�ַ  */
                                           uint32_t                             ch_ctl);  /**< \brief ͨ�����ƼĴ�������ֵ  */

/** \brief DMA������������ */
int am_hc32f460_dma_chain_xfer_desc_chan_cfg (am_hc32f460_dma_dev_t                  *p_dev,
                                              amhw_hc32f460_dma_chain_xfer_desc_t    *p_desc,
                                              amhw_hc32f460_dma_transfer_type_t       type,
                                              uint8_t                                 chan);

/**
 * \brief ��ʼDMA����
 *
 * \param[in] p_dev   : ָ��DMA�豸��ָ��
 * \param[in] p_desc  : ָ��DMA������������ָ��
 * \param[in] type    : DMA����ģʽ���� ���ж�Ӧ��ö����dma_transfer_type_t
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 */
int am_hc32f460_dma_xfer_desc_chan_cfg (am_hc32f460_dma_dev_t            *p_dev,
                                        amhw_hc32f460_dma_xfer_desc_t    *p_desc,
                                        amhw_hc32f460_dma_transfer_type_t type,
                                        uint8_t                           chan);

/**
 * \brief ����DMA�ص�����
 *
 * \param[in] p_dev   : ָ��DMA�豸��ָ��
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ��� �������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ���ӳɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_hc32f460_dma_isr_connect (am_hc32f460_dma_dev_t    *p_dev,
                                 int                       chan,
                                 am_hc32f460_pfn_dma_isr_t pfn_isr,
                                 void                     *p_arg);

/**
 * \brief ɾ��DMA�ص�����������
 *
 * \param[in] p_dev   : ָ��DMA�豸��ָ��
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ����������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ɾ���ɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_hc32f460_dma_isr_disconnect (am_hc32f460_dma_dev_t     *p_dev,
                                    int                        chan,
                                    am_hc32f460_pfn_dma_isr_t  pfn_isr,
                                    void                      *p_arg);


/**
 * \brief �����ж�����
 *
 * \param[in] p_dev    : ָ��DMA�豸��ָ��
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] int_flag : �жϱ�־
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 */
void am_hc32f460_dma_chan_int_mask_set (am_hc32f460_dma_dev_t *p_dev,
                                        int                    chan,
                                        uint32_t               int_flag);

/**
 * \brief ����ж�����
 *
 * \param[in] p_dev    : ָ��DMA�豸��ָ��
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] int_flag : �жϱ�־
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 */
void am_hc32f460_dma_chan_int_mask_clr (am_hc32f460_dma_dev_t *p_dev,
                                        int                    chan,
                                        uint32_t               int_flag);

/**
 * \breif ��ȡ  ĳͨ����ǰ����ʣ����ֽ���
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 *
 * \retval  �ֽ���
 */
uint16_t am_hc32f460_dma_tran_data_get (am_hc32f460_dma_dev_t *p_dev, int chan);

/**
 * \breif ���� ĳͨ����ǰ����ʣ����ֽ���
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] trans_data_byte Ҫ������ֽ���
 *
 * \retval  ��
 *
 * \note �����ô�����ֽ���֮ǰ����ֹͣͨ������
 */
void am_hc32f460_dma_tran_data_size (am_hc32f460_dma_dev_t *p_dev,
                                     int                    chan,
                                     uint32_t               trans_data_byte);

/**
 * \breif ����ÿ�δ���ʱ�����С
 *
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_*(* Ϊ1/2/3/4)
 * \param[in] block_data_num  ���С����
 *
 * \retval  AM_OK     : ���óɹ�
 *          -AM_EINVAL: ��������
 *
 * \note �����ô�����ֽ���֮ǰ����ֹͣͨ������
 */
int am_hc32f460_dma_block_data_size (am_hc32f460_dma_dev_t *p_dev,
                                     int                    chan,
                                     uint16_t               block_data_num);

/**
 * \breif �趨ͨ����������Ĵ���Դ
 *
 * \param[in] src : ����Դ
 *
 * \retval  ��
 */
void am_hc32f460_dma_chan_rcfg_src_set (en_event_src_t src);

/**
 * \breif ͨ�����ÿ��ƼĴ�������
 *
 * \param[in] p_dev   ָ��DMA�豸��ָ��
 * \param[in] cntmd   ʣ�ഫ��������������÷�ʽ
 * \param[in] darmd   Ŀ���ַ���÷�ʽ
 * \param[in] sarmd   Դ��ַ���÷�ʽ
 * \param[in] chan    ����ͨ��ѡ��
 * \param[in] rcfgllp ��ָ��ʽͨ������
 * \param[in] rcfgen  ͨ���������
 *
 * \retval  ��
 *
 * \note ��DMAʹ��ǰ���øüĴ������üĴ�������������ͨ���ĵ�һ�δ���ǰ���á�
 */
void am_hc32f460_dma_chan_rcfg_set (am_hc32f460_dma_dev_t *p_dev,
                                    uint8_t                cntmd,
                                    uint8_t                darmd,
                                    uint8_t                sarmd,
                                    uint8_t                chan,
                                    uint8_t                rcfgllp,
                                    uint8_t                rcfgen);

/**
 * \brief ����Դ��ַ�ظ������С
 *        Դ�豸��ÿ����size�����ݺ�Դ��ַ����ΪDMA_SARx�Ĵ�����ֵ��
 *
 * \param[in] p_dev  ָ��DMA�豸��ָ��
 * \param[in] chan : ͨ����
 * \param[in] size : Դ��ַ�ظ������С
 *
 * \retval  ��
 */
int am_hc32f460_dma_srpt_size_set (am_hc32f460_dma_dev_t *p_dev,
                                   int                    chan,
                                   uint16_t               size);
/**
 * \brief ����Ŀ���ַ�ظ������С
 *        Դ�豸��ÿ����size�����ݺ�Ŀ���ַ����ΪDMA_DARx�Ĵ�����ֵ��
 *
 * \param[in] p_dev  ָ��DMA�豸��ָ��
 * \param[in] chan : ͨ����
 * \param[in] size : Դ��ַ�ظ������С
 *
 * \retval  ��
 */
int am_hc32f460_dma_drpt_size_set (am_hc32f460_dma_dev_t *p_dev, int chan, uint16_t size);

/**
 * \brief Դ�豸��������ַ��������
 *
 * \param[in] p_dev   : ָ��DMA�豸��ָ��
 * \param[in] chan    : ͨ����
 * \param[in] snscnt  : Դ��ַ��ת��������
 * \param[in] soffset : Դ��ַ��ת�ĵ�ַƫ����
 *
 * \retval  ��
 */
int am_hc32f460_dma_snseqctl_cfg (am_hc32f460_dma_dev_t *p_dev,
                                  int                    chan,
                                  uint16_t               snscnt,
                                  uint16_t               soffset);

/**
 * \brief Ŀ���豸��������ַ��������
 *
 * \param[in] p_dev   : ָ��DMA�豸��ָ��
 * \param[in] chan    : ͨ����
 * \param[in] dnscnt  : Ŀ���ַ��ת��������
 * \param[in] doffset : Ŀ���ַ��ת�ĵ�ַƫ����
 *
 * \retval  ��
 */
int am_hc32f460_dma_dnseqctl_cfg (am_hc32f460_dma_dev_t *p_dev,
                                  int                    chan,
                                  uint16_t               dnscnt,
                                  uint16_t               doffset);

/**
 * \brief DMA�������
 */
void am_hc32f460_dma_soft_trig(void);


/**
 * \brief DMA��ʼ��
 *
 * \param[in] p_dev         : ָ��DMA�豸��ָ��
 * \param[in] p_dma_devinfo : ָ��DMA�豸��Ϣ��ָ��
 *
 * \retval  AM_OK       : ��ʼ���ɹ�
 */
int am_hc32f460_dma_init (am_hc32f460_dma_dev_t           *p_dev,
                          const am_hc32f460_dma_devinfo_t *p_dma_devinfo);

/**
 * \brief DMAȥ��ʼ��
 *
 * \param[in] p_dev      : ָ��DMA�豸��ָ��
 *
 * \return ��
 */
void am_hc32f460_dma_deinit (am_hc32f460_dma_dev_t *p_dev);

/**
 * \brief DMA�жϺ���
 *
 * \param[in] p_arg : �жϺ�������
 *
 * \return ��
 */
void dma_int_handler(void *p_arg);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_DMA_H */

/* end of file */
