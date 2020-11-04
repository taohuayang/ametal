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
 * \brief ����ʱ�䴫���� TMF8801 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-02-28  YRZ, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TMF8801_H
#define __AM_SENSOR_TMF8801_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/*
 * \brief ������TMF8801�ṩ������ͨ��ID����
 */
#define AM_TMF8801_CHAN_1      0             /* TMF8801 ��ͨ��1������ */
#define AM_TMF8801_CHAN_2      1             /* TMF8801 ��ͨ��2���¶� */

/**
 * \brief APP0 ���ó�ʼ���ṹ�嶨�� 
 */
typedef struct app0_config
{    
    uint8_t calibration_state_mask;    
    uint8_t gpio_control;           /**< \brief GPIOx ���� */
    uint8_t gpio_output_control;    /**< \brief GPIOx ������� */
    uint8_t repetition_period_ms;   /**< \brief ���������������� */
    uint16_t iterations;            /**< \brief �������� */
} app0_config_t;

/**
 * \brief TMF8x01 ��������ṹ�嶨��
 */
typedef struct result_info
{
    int8_t   temperature;           /**< \brief �¶� */
    uint8_t  result_num;            /**< \brief ��� ID */
    uint8_t  reliability;           /**< \brief ���Ŷ� */
    uint16_t distance_peak;         /**< \brief ����(mm) */
    uint32_t time_stamp;            /**< \brief ʱ���(100us) */
    uint32_t reference_hits;        /**< \brief ����ģʽ�£��ο� SPADs �����ӻ��������� */
    uint32_t object_hits;           /**< \brief ����ģʽ�£�Ŀ�� SPADs �����ӻ��������� */
} result_info_t;

/**
 * \brief ������ TMF8801 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tmf8801_devinfo {

    /**
     * \brief ʹ������
     */
    int     enable_pin;

    /**
     * \brief �жϴ�������
     */
    int     trigger_pin;

    /*
     * \brief I2C 7λ �豸��ַ
     *
     * ���豸7λ��ַĬ��Ϊ 0x41
     */
    uint8_t i2c_addr;

} am_sensor_tmf8801_devinfo_t;

/**
 * \breif ������ TMF8801 �豸�ṹ�嶨��
 */
typedef struct am_sensor_tmf8801_dev {
    am_sensor_serv_t                  tmf8801_dev; /**< \breif ��������׼���� */
    am_i2c_device_t                   i2c_dev;     /**< \brief i2c�豸ʵ�� */
    void                             *p_arg[3];    /**< \brief �����ص��������� */
    uint8_t                           flags[3];    /**< \brief ������־λ */
    am_isr_defer_job_t                g_myjob;     /**< \brief �ж���ʱ�������� */
    uint8_t                           trigger;     /**< \brief ��¼��־λ */
    am_sensor_val_t                   data[3];     /**< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t            pfn_trigger_cb[3];

    /** \brief �豸��Ϣ */
    const am_sensor_tmf8801_devinfo_t *dev_info;

} am_sensor_tmf8801_dev_t;

/**
 * \brief ������ TMF8801 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TMF8801�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TMF8801�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tmf8801_init (
        am_sensor_tmf8801_dev_t           *p_dev,
        const am_sensor_tmf8801_devinfo_t *p_devinfo,
        am_i2c_handle_t                    handle);

/**
 * \brief ������ TMF8801 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tmf8801_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tmf8801_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TMF8801_H */

/* end of file */
