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
 * \brief SPI �ӻ����������� SPI �ӻ���׼�ӿ�
 *
 * \internal
 * \par Modification History
 * -1.00 19-07-18 fra, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG237_SPI_SLV_DMA_H
#define __AM_ZLG237_SPI_SLV_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_spi_slv.h"
#include "am_softimer.h"
#include "am_zlg_dma.h"
#include "hw/amhw_zlg237_spi.h"

/**
 * \addtogroup am_zlg237_if_spi_slv_dma
 * \copydoc am_zlg_spi_slv_dma.h
 * @{
 */

/**
 * \brief SPI �ӻ��豸��Ϣ�ṹ��
 */
typedef struct am_zlg237_spi_slv_dma_devinfo {
    uint32_t spi_reg_base;           /**< \brief �ӻ� SPI �Ĵ�����Ļ���ַ */
    int      clk_id;                 /**< \brief ʱ�� ID */
    uint32_t dma_chan_tx;            /**< \brief DMA ����ͨ���� */
    uint32_t dma_chan_rx;            /**< \brief DMA ����ͨ���� */
    int      cs_pin;                 /**< \breif Ƭѡ���� */
    void   (*pfn_plfm_init)(void);   /**< \brief SPI ƽ̨��ʼ������ */
    void   (*pfn_plfm_deinit)(void); /**< \brief SPI ƽ̨���ʼ������ */
} am_zlg237_spi_slv_dma_devinfo_t;

/**
 * \brief SPI �豸�ṹ��
 */
typedef struct am_zlg237_spi_slv_dma_dev {

    /** \brief SPI �ӻ���׼������ */
    am_spi_slv_serv_t                      spi_slv_serve;

    /** \brief SPI �ӻ��豸��Ϣ��ָ�� */
    const am_zlg237_spi_slv_dma_devinfo_t *p_devinfo;

    /** \brief �ӻ��豸  */
    am_spi_slv_device_t                   *p_spi_slv_dev;

    /** \brief ������ */
    am_spi_slv_transfer_t                  tansfer;

    /** \brief ��Ƭѡ��Ч��Ƭѡ��Ч��������ֽ��� */
    size_t                                 sum_nbytes;

    /** \brief DMA ͨ�������� */
    amhw_zlg_dma_xfer_desc_t               g_desc[2];

    uint32_t                               dma_flags;

    /** \breif �����������ܵ����ݻ��Ϳ����� */
    uint32_t                               dummy_dma_flags;

    uint32_t                               dummy_txbuf;
    uint32_t                               dummy_rxbuf;

} am_zlg237_spi_slv_dma_dev_t;

/**
 * \brief SPI �ӻ���ʼ��
 *
 * \param[in] p_dev     ָ�� SPI ���豸�ṹ���ָ��
 * \param[in] p_devinfo ָ�� SPI ���豸��Ϣ�ṹ���ָ��
 *
 * \return SPI ��׼����������
 */
am_spi_slv_handle_t
am_zlg237_spi_slv_dma_init (am_zlg237_spi_slv_dma_dev_t           *p_dev,
                            const am_zlg237_spi_slv_dma_devinfo_t *p_devinfo);

/**
 * \brief ��� SPI �ӻ���ʼ��
 *
 * \param[in] handle SPI ���豸��׼����������
 *
 * \return ��
 */
void am_zlg237_spi_slv_dma_deinit (am_spi_slv_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG_SPI_SLV_DMA_H */

/* end of file */
