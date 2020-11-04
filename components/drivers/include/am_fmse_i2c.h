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
 * \brief ��ȫоƬFMSE-A03 I2C����ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-07-02  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_FMSE_I2C_H
#define __AM_FMSE_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_fmse_a03.h"

typedef struct{
    uint8_t lenlo;
    uint8_t lenhi;
    uint8_t nad;
    union{
        uint8_t cmd;
        uint8_t sta;
    } flag;
} am_fmse_i2c_head_t;
    
/**
 * \brief FMSE-A03 �豸��Ϣ�ṹ��
 */
typedef struct am_fmse_i2c_devinfo {

    /**
     * \brief I2C 7λ �豸��ַ
     */
    uint8_t i2c_addr;

} am_fmse_i2c_devinfo_t;

/**
 * \breif FMSE-A03 �豸�ṹ�嶨��
 */
typedef struct am_fmse_i2c_dev {

    am_fmse_serv_t                    fmse_dev;  /**< \breif FMSE��׼���� */

    am_i2c_device_t                   i2c_dev;   /**< \brief i2c�豸ʵ�� */

    const am_fmse_i2c_devinfo_t      *dev_info;  /** \brief �豸��Ϣ */

} am_fmse_i2c_dev_t;

/**
 * \brief I2C����FMSE���豸��ʼ��
 *
 * \param[in] p_dev     : I2C������ FMSE�豸
 * \param[in] p_devinfo : FMSE�豸��Ϣ
 * \param[in] handle    : I2C��׼������
 *
 * \return FMSE��׼����������ΪNULL��������ʼ��ʧ��
 */
am_fmse_handle_t am_fmse_i2c_init (am_fmse_i2c_dev_t           *p_dev,
                                   const am_fmse_i2c_devinfo_t *p_devinfo,
                                   am_i2c_handle_t              handle);

/**
 * \brief FMSE���豸ȥ��ʼ��
 *
 * \param[in] handle : FMSE��ʼ����ȡ�ı�׼������
 *
 * \return 
 */
am_err_t am_fmse_i2c_deinit (am_fmse_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_FMSE_I2C_H */

/* end of file */
