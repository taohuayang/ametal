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
 * \brief ��ȫоƬFMSE-A03 SPI����ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-07-02  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_FMSE_SPI_H
#define __AM_FMSE_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_spi.h"
#include "am_fmse_a03.h"

/**
 * \brief FMSE-A03 �豸��Ϣ�ṹ��
 */
typedef struct am_fmse_spi_devinfo {

    int       cs_pin;
    
    uint32_t  speed;

} am_fmse_spi_devinfo_t;

/**
 * \breif FMSE-A03 �豸�ṹ�嶨��
 */
typedef struct am_fmse_spi_dev {

    am_fmse_serv_t                    fmse_dev;  /**< \breif FMSE��׼���� */

    am_spi_device_t                   spi_dev;   /**< \brief spi�豸ʵ�� */

    const am_fmse_spi_devinfo_t      *dev_info;  /** \brief �豸��Ϣ */

} am_fmse_spi_dev_t;

/**
 * \brief SPI���� FMSE���豸��ʼ��
 *
 * \param[in] p_dev     : SPI������ FMSE�豸
 * \param[in] p_devinfo : FMSE�豸��Ϣ
 * \param[in] handle    : SPI��׼������
 *
 * \return FMSE��׼����������ΪNULL��������ʼ��ʧ��
 */
am_fmse_handle_t am_fmse_spi_init (am_fmse_spi_dev_t           *p_dev,
                                   const am_fmse_spi_devinfo_t *p_devinfo,
                                   am_spi_handle_t              handle);

/**
 * \brief FMSE���豸ȥ��ʼ��
 *
 * \param[in] handle : FMSE��ʼ����ȡ�ı�׼������
 *
 * \return 
 */
am_err_t am_fmse_spi_deinit (am_fmse_handle_t handle);
                                   
#ifdef __cplusplus
}
#endif

#endif /* __AM_FMSE_SPI_H */

/* end of file */
