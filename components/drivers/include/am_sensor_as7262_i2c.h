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
 * \brief ���״����� AS7262 (I2Cģʽ) ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_AS7262_I2C_H
#define __AM_SENSOR_AS7262_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_sensor_as7262.h"
#include "am_i2c.h"

/**
 * \brief ������ AS7262 (I2Cģʽ) �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_as7262_i2c_devinfo {

    const am_sensor_as7262_devinfo_t        *p_devinfo;

    am_i2c_handle_t (*pfn_i2c_handle_get) (void);           /**< \brief I2C�����ȡ���� */

    void (*pfn_i2c_deinit) (am_i2c_handle_t i2c_handle);    /**< \brief I2C���ʼ������ */

    uint8_t                                 i2c_addr;       /**< \brief I2C 7λ �豸��ַ */

} am_sensor_as7262_i2c_devinfo_t;

/**
 * \breif ������ AS7262 (I2Cģʽ) �豸�ṹ�嶨��
 */
typedef struct am_sensor_as7262_i2c_dev {
    am_sensor_as7262_dev_t                  isa;                    /**< \breif ��������׼���� */

    am_i2c_device_t                         i2c_dev;                /**< \brief I2C�豸ʵ�� */

    const am_sensor_as7262_i2c_devinfo_t    *sensor_i2c_dev_info;   /**< \brief �豸��Ϣ */

} am_sensor_as7262_i2c_dev_t;

/**
 * \brief ������ AS7262 (I2Cģʽ) ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���AS7262(I2Cģʽ)�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���AS7262(I2Cģʽ)�豸��Ϣ��ָ��
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_as7262_i2c_init (
        am_sensor_as7262_i2c_dev_t              *p_dev,
        const am_sensor_as7262_i2c_devinfo_t    *p_devinfo);

/**
 * \brief ������ AS7262 (I2Cģʽ) ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_as7262_i2c_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_as7262_i2c_deinit (am_sensor_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_AS7262_I2C_H */

/* end of file */

