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
 * - 1.00 17-04-11  ari, first implementation
 * \endinternal
 */

#ifndef __AM_STM32F103RBT6_DMA_H
#define __AM_STM32F103RBT6_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_stm32f103rbt6_dma.h"

/**
 * \addtogroup am_stm32f103rbt6_if_dma
 * \copydoc am_stm32f103rbt6_dma.h
 * @{
 */

/**
 * \name ͨ�������жϱ�־
 * \anchor am_stm32f103rbt6_dma_chan_cfg_flags
 * @{
 */

/** \brief ����жϱ�ʶ */
#define AM_STM32F103RBT6_DMA_INT_NORMAL         0

/** \brief �����жϱ�ʶ */
#define AM_STM32F103RBT6_DMA_INT_ERROR          1

/** @} */

/** \brief DMA�жϻص��������� */
typedef void (*am_stm32f103rbt6_pfn_dma_isr_t)(void *p_arg, uint32_t flag);

/** \brief DMA�жϻص�������Ϣ */
struct am_stm32f103rbt6_dma_int_info {

    /** \brief DMA�����ص����� */
    am_stm32f103rbt6_pfn_dma_isr_t  pfn_isr;

    /** \brief �ص������ĵ�һ����ڲ��� */
    void                    *p_arg;
};

/** \brief DMA�豸��Ϣ */
typedef struct am_stm32f103rbt6_dma_devinfo {

    /** \brief ָ��DMA�Ĵ������ָ�� */
    uint32_t   dma_reg_base;

    /** \brief DMA�жϺſ�ʼ */
    uint8_t    inum_start;

    /** \brief DMA�жϺŽ��� */
    uint8_t    inum_end;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_stm32f103rbt6_dma_devinfo_t;

/**
 * \brief DMA�豸ʵ��
 */
typedef struct am_stm32f103rbt6_dma_dev {

    /** \brief ָ��DMA�豸��Ϣ��ָ�� */
    const am_stm32f103rbt6_dma_devinfo_t *p_devinfo;

}am_stm32f103rbt6_dma_dev_t;

/**
 * \brief ����DMA����ͨ��
 *
 * \param[in] chan  : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_UART1_TX)
 *
 * \retval AM_OK    : ���óɹ�
 * \retval AM_ERROR : ���ô��󣬸�ͨ��֮ǰ���ù�
 */
int am_stm32f103rbt6_dma_chan_start (int chan);

/**
 * \brief ֹͣͨ������
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_UART1_TX)
 *
 * \retval AM_OK   : �����ɹ�
 */
int am_stm32f103rbt6_dma_chan_stop (int chan);

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
int am_stm32f103rbt6_dma_xfer_desc_build (amhw_stm32f103rbt6_dma_xfer_desc_t *p_desc,
                                uint32_t                  src_addr,
                                uint32_t                  dst_addr,
                                uint32_t                  nbytes,
                                uint32_t                  flags);

/**
 * \brief ��ʼDMA����
 *
 * \param[in] p_desc  : ָ��DMA������������ָ��
 * \param[in] type    : DMA����ģʽ���� ���ж�Ӧ��ö����dma_transfer_type_t
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_UART1_TX)
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_EINVAL : ������Ч
 */
int am_stm32f103rbt6_dma_xfer_desc_chan_cfg (amhw_stm32f103rbt6_dma_xfer_desc_t    *p_desc,
                                   amhw_stm32f103rbt6_dma_transfer_type_t type,
                                   uint8_t                      chan);

/**
 * \brief ����DMA�ص�����
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AM_STM32F103RBT6_DMA_INT*
 *            (#AM_STM32F103RBT6_DMA_INT_ERROR)��(#AM_STM32F103RBT6_DMA_INT_NORMAL)
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_UART1_TX)
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ��� �������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ���ӳɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_stm32f103rbt6_dma_isr_connect (int                       chan,
                            am_stm32f103rbt6_pfn_dma_isr_t      pfn_isr,
                            void                     *p_arg);

/**
 * \brief ɾ��DMA�ص�����������
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AM_STM32F103RBT6_DMA_INT*
 *            (#AM_STM32F103RBT6_DMA_INT_ERROR)��(#AM_STM32F103RBT6_DMA_INT_NORMAL)
 *            �ûص������ĵ����������ǲ����жϵ�ͨ������ȡֵ��Χ��DMA_CHAN_* (#DMA_CHAN_1)
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_UART1_TX)
 * \param[in] pfn_isr : �ص�����ָ��
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ����������ӹ����У���Ӧͨ��д�϶�Ӧ���֣�
 *                      ����DMA0ͨ������ò���Ϊ(void *)0
 *
 * \retval  AM_OK     : ɾ���ɹ�
 * \retval -AM_EPERM  : ��������
 */
int am_stm32f103rbt6_dma_isr_disconnect (int                      chan,
                               am_stm32f103rbt6_pfn_dma_isr_t     pfn_isr,
                               void                    *p_arg);

/**
 * \breif ��ȡ  ĳͨ����ǰ����ʣ����ֽ���
 *
 * \param[in] chan DMA ͨ���ţ�ֵΪ DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_UART1_TX)
 *
 * \retval  �ֽ���
 */
uint16_t am_stm32f103rbt6_dma_tran_data_get (int chan);

/**
 * \breif ���� ĳͨ����ǰ����ʣ����ֽ���
 *
 * \param[in] chan            DMA ͨ���ţ�ֵΪ DMA_CHAN_* (#DMA_CHAN_1) �� (#DMA_CHAN_UART1_TX)
 * \param[in] trans_data_byte Ҫ������ֽ���
 *
 * \retval  ��
 *
 * \note �����ô�����ֽ���֮ǰ����ֹͣͨ������
 */
void am_stm32f103rbt6_dma_tran_data_size (int chan, uint32_t trans_data_byte);

/**
 * \brief DMA��ʼ��
 *
 * \param[in] p_dev         : ָ��DMA�豸��ָ��
 * \param[in] p_dma_devinfo : ָ��DMA�豸��Ϣ��ָ��
 *
 * \retval  AM_OK       : ��ʼ���ɹ�
 */
int am_stm32f103rbt6_dma_init (am_stm32f103rbt6_dma_dev_t           *p_dev,
                     const am_stm32f103rbt6_dma_devinfo_t *p_dma_devinfo);

/**
 * \brief DMAȥ��ʼ��
 *
 * \return ��
 */
void am_stm32f103rbt6_dma_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_STM32F103RBT6_DMA_H */

/* end of file */
