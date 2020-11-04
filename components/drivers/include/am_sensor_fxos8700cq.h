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
 * \brief ���ᴫ���� FXOS8700CQ ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 19-09-29  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_FXOS8700CQ_H
#define __AM_SENSOR_FXOS8700CQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

typedef enum am_sensor_fxos8700cq_m_hms_type{
    AM_FXOS8700CQ_ACCELEROMETER_SENSOR = 0,
    AM_FXOS8700CQ_MAGNETOMETER_SENSOR  = 1,
    AM_FXOS8700CQ_HYBRID_MODE = 3,
} am_sensor_fxos8700cq_m_hms_type_t;

typedef enum am_sensor_fxos8700cq_auto_cal{
    AM_FXOS8700CQ_AUTO_CALIBRATION_FEATURE_DISABLED = 0,
    AM_FXOS8700CQ_AUTO_CALIBRATION_FEATURE_ENABLED,
} am_sensor_fxos8700cq_auto_cal_t;

typedef enum am_sensor_fxos8700cq_hyb_autoinc_mode{
    AM_FXOS8700CQ_HYB_AUTOINC_DISABLED = 0,
    AM_FXOS8700CQ_HYB_AUTOINC_ENABLED,
} am_sensor_fxos8700cq_hyb_autoinc_mode_t;

typedef enum am_sensor_fxos8700cq_acc_wake_mode_osr{
    AM_FXOS8700CQ_NORMAL = 0,
    AM_FXOS8700CQ_LOW_NOISE_LOW_POWER,
    AM_FXOS8700CQ_HIGH_RESOLUTION,
    AM_FXOS8700CQ_LOW_POWER,
} am_sensor_fxos8700cq_acc_wake_mode_osr_t;

typedef enum am_sensor_fxos8700cq_lnoise_mode{
    AM_FXOS8700CQ_LNOISE_NORMAL_MODE = 0,
    AM_FXOS8700CQ_LNOISE_REDUCED_NOISE_MODE,
} am_sensor_fxos8700cq_lnoise_mode_t;

#define AM_FXOS8700CQ_DATA_RATE_1250US          0
#define AM_FXOS8700CQ_DATA_RATE_2500US          1
#define AM_FXOS8700CQ_DATA_RATE_5MS             2
#define AM_FXOS8700CQ_DATA_RATE_10MS            3
#define AM_FXOS8700CQ_DATA_RATE_20MS            4
#define AM_FXOS8700CQ_DATA_RATE_80MS            5
#define AM_FXOS8700CQ_DATA_RATE_160MS           6
#define AM_FXOS8700CQ_DATA_RATE_640MS           7

#define AM_FXOS8700CQ_ODR_ONLY_MODE_800HZ       (AM_FXOS8700CQ_DATA_RATE_1250US)
#define AM_FXOS8700CQ_ODR_ONLY_MODE_400HZ       (AM_FXOS8700CQ_DATA_RATE_2500US)
#define AM_FXOS8700CQ_ODR_ONLY_MODE_200HZ       (AM_FXOS8700CQ_DATA_RATE_5MS)
#define AM_FXOS8700CQ_ODR_ONLY_MODE_100HZ       (AM_FXOS8700CQ_DATA_RATE_10MS)
#define AM_FXOS8700CQ_ODR_ONLY_MODE_50HZ        (AM_FXOS8700CQ_DATA_RATE_20MS)
#define AM_FXOS8700CQ_ODR_ONLY_MODE_12_5HZ      (AM_FXOS8700CQ_DATA_RATE_80MS)
#define AM_FXOS8700CQ_ODR_ONLY_MODE_6_25HZ      (AM_FXOS8700CQ_DATA_RATE_160MS)
#define AM_FXOS8700CQ_ODR_ONLY_MODE_1_56HZ      (AM_FXOS8700CQ_DATA_RATE_640MS)

#define AM_FXOS8700CQ_ODR_HYBRID_MODE_400HZ     (AM_FXOS8700CQ_DATA_RATE_1250US)
#define AM_FXOS8700CQ_ODR_HYBRID_MODE_200HZ     (AM_FXOS8700CQ_DATA_RATE_2500US)
#define AM_FXOS8700CQ_ODR_HYBRID_MODE_100HZ     (AM_FXOS8700CQ_DATA_RATE_5MS)
#define AM_FXOS8700CQ_ODR_HYBRID_MODE_50HZ      (AM_FXOS8700CQ_DATA_RATE_10MS)
#define AM_FXOS8700CQ_ODR_HYBRID_MODE_25HZ      (AM_FXOS8700CQ_DATA_RATE_20MS)
#define AM_FXOS8700CQ_ODR_HYBRID_MODE_6_25HZ    (AM_FXOS8700CQ_DATA_RATE_80MS)
#define AM_FXOS8700CQ_ODR_HYBRID_MODE_3_12HZ    (AM_FXOS8700CQ_DATA_RATE_160MS)
#define AM_FXOS8700CQ_ODR_HYBRID_MODE_0_78HZ    (AM_FXOS8700CQ_DATA_RATE_640MS)

/**
 * \brief ������FXOS8700CQ�ṩ������ͨ��ID����
 */
#define AM_FXOS8700CQ_CHAN_1      0           /* FXOS8700CQ ��ͨ��1��X����ٶ�      */
#define AM_FXOS8700CQ_CHAN_2      1           /* FXOS8700CQ ��ͨ��2��Y����ٶ�      */
#define AM_FXOS8700CQ_CHAN_3      2           /* FXOS8700CQ ��ͨ��3��Z����ٶ�      */
#define AM_FXOS8700CQ_CHAN_4      3           /* FXOS8700CQ ��ͨ��4��X��Ÿ�Ӧǿ��  */
#define AM_FXOS8700CQ_CHAN_5      4           /* FXOS8700CQ ��ͨ��5��Y��Ÿ�Ӧǿ��  */
#define AM_FXOS8700CQ_CHAN_6      5           /* FXOS8700CQ ��ͨ��6��Z��Ÿ�Ӧǿ��  */

/**
 * \brief ������ FXOS8700CQ �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_fxos8700cq_devinfo {

    int     trigger_pin;                                            //����׼��������������

    uint8_t i2c_addr;                                               //I2C 7λ �豸��ַ

    uint8_t odr_selection;                                          //�����������

    am_sensor_fxos8700cq_m_hms_type_t           m_hms_type; 

    uint8_t m_os;                                                   //���������ݹ�������

    am_sensor_fxos8700cq_auto_cal_t             m_acal;             //��У׼�Ƿ�ʹ��

    am_sensor_fxos8700cq_hyb_autoinc_mode_t     hyb_autoinc_mode;   //���ģʽ�µ�ַ�����Ƿ�ʹ��

    am_sensor_fxos8700cq_acc_wake_mode_osr_t    mods;               //���ٶȼƻ���ģʽOSRģʽѡ��

    am_sensor_fxos8700cq_lnoise_mode_t          lnoise;             //��������ģʽ�Ƿ�ʹ�� (FSR����Ϊ��2g/��4g)

} am_sensor_fxos8700cq_devinfo_t;

/**
 * \breif ������ FXOS8700CQ �豸�ṹ�嶨��
 */
typedef struct am_sensor_fxos8700cq_dev {
    am_sensor_serv_t               fxos8700cq_dev;  /**< \breif ��������׼����   */
    am_i2c_device_t                i2c_dev;      /**< \brief i2c�豸ʵ��      */
    void                          *p_arg[6];     /**< \brief �����ص��������� */
    uint8_t                        flags[6];     /**< \brief ������־λ       */
    am_isr_defer_job_t             g_myjob;      /**< \brief �ж���ʱ�������� */ 
    uint16_t                       trigger;      /**< \brief ��¼��־λ       */
    am_sensor_val_t                data[6];      /**< \brief �ڲ����ݻ���     */
    am_sensor_val_t                sam_range;    /**< \brief ������Χ         */
    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t         pfn_trigger_cb[6];
    
    /** \brief �豸��Ϣ */
    const am_sensor_fxos8700cq_devinfo_t *dev_info;

} am_sensor_fxos8700cq_dev_t;

/**
 * \brief ������ FXOS8700CQ ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���FXOS8700CQ�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���FXOS8700CQ�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_fxos8700cq_init (
        am_sensor_fxos8700cq_dev_t           *p_dev,
        const am_sensor_fxos8700cq_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ FXOS8700CQ ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_fxos8700cq_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_fxos8700cq_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_FXOS8700CQ_H */

/* end of file */
