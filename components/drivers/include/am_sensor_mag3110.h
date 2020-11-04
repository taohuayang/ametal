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
 * \brief ������������� MAG3110 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 19-07-03  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_MAG3110_H
#define __AM_SENSOR_MAG3110_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������MAG3110�ṩ������ͨ��ID����
 */
#define AM_MAG3110_CHAN_1      0           /* MAG3110 ��ͨ��1��X�����        */
#define AM_MAG3110_CHAN_2      1           /* MAG3110 ��ͨ��2��Y�����        */
#define AM_MAG3110_CHAN_3      2           /* MAG3110 ��ͨ��3��Z�����        */
#define AM_MAG3110_CHAN_4      3           /* MAG3110 ��ͨ��4���¶�           */
    
/**
 * \brief ������ MAG3110 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_mag3110_devinfo {
    
    /**
     * \brief ����׼��������������
     */
    int     trigger_pin;
    
    /**
     * \brief I2C 7λ �豸��ַ
     *
     * ���豸7λ��ַΪ 0x1C
     */
    uint8_t i2c_addr;

} am_sensor_mag3110_devinfo_t;

/**
 * \breif ������ MAG3110 �豸�ṹ�嶨��
 */
typedef struct am_sensor_mag3110_dev {
    am_sensor_serv_t               mag3110_dev;  /**< \breif ��������׼����   */
    am_i2c_device_t                i2c_dev;      /**< \brief i2c�豸ʵ��      */
    void                          *p_arg[4];     /**< \brief �����ص��������� */
    uint8_t                        flags[4];     /**< \brief ������־λ       */
    am_isr_defer_job_t             g_myjob;      /**< \brief �ж���ʱ�������� */ 
    uint16_t                       trigger;      /**< \brief ��¼��־λ       */
    am_sensor_val_t                data[4];      /**< \brief �ڲ����ݻ���     */
    am_sensor_val_t                sam_range;    /**< \brief ��������         */
    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t         pfn_trigger_cb[4];
    
    /** \brief �豸��Ϣ */
    const am_sensor_mag3110_devinfo_t *dev_info;

} am_sensor_mag3110_dev_t;

/**
 * \brief ������ MAG3110 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���MAG3110�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���MAG3110�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_mag3110_init (
        am_sensor_mag3110_dev_t           *p_dev,
        const am_sensor_mag3110_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ MAG3110 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_mag3110_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_mag3110_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_MAG3110_H */

/* end of file */
