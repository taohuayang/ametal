/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
*******************************************************************************/

/**
 * \file
 * \brief SPI����������SPI��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_SPI_DMA_H
#define __AM_ZSN700_SPI_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_spi.h"
#include "am_int.h"

#include "am_zsn700_dma.h"
#include "hw/amhw_zsn700_dma.h"
#include "hw/amhw_zsn700_spi.h"

/**
 * \addtogroup am_zsn700_if_spi_dma
 * \copydoc am_zsn700_spi_dma.h
 * @{
 */

/** \brief ֹͣģʽSPI�������� */
#define AM_ZSN700_SPI_DMA_CFG_WIAT_EN        (AM_BIT(28) | AM_SBF(0,3))

/** \brief ֹͣģʽSPI������ */
#define AM_ZSN700_SPI_DMA_CFG_WIAT_DIS       (AM_BIT(28) | AM_SBF(1,3))

/**
 * \brief SPI �豸��Ϣ�ṹ��
 */
typedef struct am_zsn700_spi_dma_devinfo {
    uint32_t  spi_reg_base; /**< \brief SPI�Ĵ�����Ļ���ַ */
    int       clk_id;       /**< \brief ʱ��ID */
    uint16_t  inum;         /**< \brief SPI �жϱ�� */

    uint32_t  dma_chan_tx;  /**< \brief DMA����ͨ���� */
    uint32_t  dma_chan_rx;  /**< \brief DMA����ͨ���� */

    /** \brief SPIƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief SPIƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_zsn700_spi_dma_devinfo_t;

/**
 * \brief SPI �豸
 */
typedef struct am_zsn700_spi_dma_dev {

    am_spi_serv_t                   spi_serve;  /**< \brief SPI��׼������   */
    const am_zsn700_spi_dma_devinfo_t *p_devinfo;  /**< \brief SPI�豸��Ϣ��ָ�� */
    struct am_list_head             msg_list;   /**< \brief SPI��������Ϣ���� */

    /** \brief ָ�� SPI ��������ж�����Ҫʹ�õ���Ϣ */
    am_spi_message_t           *p_isr_msg;

    /** \brief ָ��SPI��Ϣ�ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ����Ϣ */
    am_spi_message_t           *p_cur_msg;

    /** \brief ָ��SPI����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_spi_transfer_t          *p_cur_trans;

    am_spi_device_t            *p_cur_spi_dev;  /**< \brief ��ǰ�����SPI�豸 */
    am_spi_device_t            *p_tgl_dev;      /**< \brief ��ǰ������SPI�豸 */

    uint32_t                    nbytes_to_recv; /**< \brief �����յ��ֽ���    */
    uint32_t                    data_ptr;       /**< \brief ���ݴ������      */

    am_bool_t                   busy;           /**< \brief SPIæ��ʶ         */
    uint32_t                    state;          /**< \brief SPI������״̬��״̬ */

    amhw_zsn700_dma_xfer_desc_t    g_desc[2];      /**< \brief DMAͨ�������� */

} am_zsn700_spi_dma_dev_t;

/**
 * \brief SPI ��ʼ��
 *
 * \param[in] p_dev     : ָ��SPI�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SPI�豸��Ϣ�ṹ���ָ��
 *
 * \return SPI��׼����������
 */
am_spi_handle_t am_zsn700_spi_dma_init (am_zsn700_spi_dma_dev_t           *p_dev,
                                     const am_zsn700_spi_dma_devinfo_t *p_devinfo);

/**
 * \brief ���SPI��ʼ��
 *
 * \param[in] handle : SPI��׼����������
 *
 * \return ��
 */
void am_zsn700_spi_dma_deinit (am_spi_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_SPI_DMA_H */

/* end of file */
