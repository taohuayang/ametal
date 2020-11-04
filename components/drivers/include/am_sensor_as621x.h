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
 * \brief �¶ȴ����� AS621X ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-21  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_AS621X_H
#define __AM_SENSOR_AS621X_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ AS621X ת������ѡ��
 */
#define AM_AS621X_CONVERSION_RATE_0_25HZ        (0x00)  /* 0.25Hz */
#define AM_AS621X_CONVERSION_RATE_1HZ           (0x01)  /* 1Hz */
#define AM_AS621X_CONVERSION_RATE_4HZ           (0x02)  /* 4Hz */
#define AM_AS621X_CONVERSION_RATE_8HZ           (0x03)  /* 8Hz */
#define AM_AS621X_CONVERSION_RATE_4S            (AM_AS621X_CONVERSION_RATE_0_25HZ)
#define AM_AS621X_CONVERSION_RATE_1S            (AM_AS621X_CONVERSION_RATE_1HZ)
#define AM_AS621X_CONVERSION_RATE_250MS         (AM_AS621X_CONVERSION_RATE_4HZ)
#define AM_AS621X_CONVERSION_RATE_125MS         (AM_AS621X_CONVERSION_RATE_8HZ)

/**
 * \brief ������ AS621X SMλѡ��
 */
#define AM_AS621X_CONTINUOUS_CONVERSION_MODE    (0x00)  
#define AM_AS621X_SLEEP_MODE                    (0x01)

/**
 * \brief ������ AS621X IMλѡ��
 */
#define AM_AS621X_COMPARATOR_MODE               (0x00)  /* �Ƚ�ģʽ */
#define AM_AS621X_INTERRUPT_MODE                (0x01)  /* �ж�ģʽ */

/**
 * \brief ������ AS621X �������ϴ���ѡ��
 */
#define AM_AS621X_CONSECUTIVE_FAULTS_1          (0x00)
#define AM_AS621X_CONSECUTIVE_FAULTS_2          (0x01)
#define AM_AS621X_CONSECUTIVE_FAULTS_3          (0x02)
#define AM_AS621X_CONSECUTIVE_FAULTS_4          (0x03)

/**
 * \brief ������ AS621X ����ָ���
 */
#define AM_SENSOR_AS621X_ALERT_BIT_GET          (1)
#define AM_SENSOR_AS621X_CR_SET                 (2)
#define AM_SENSOR_AS621X_SM_SET                 (3)
#define AM_SENSOR_AS621X_SM_GET                 (4)
#define AM_SENSOR_AS621X_IM_SET                 (5)
#define AM_SENSOR_AS621X_POLARITY_SET           (6)
#define AM_SENSOR_AS621X_CF_SET                 (7)
#define AM_SENSOR_AS621X_SS_SET                 (8)
#define AM_SENSOR_AS621X_TLOW_THRESHOLD_SET     (9)
#define AM_SENSOR_AS621X_THIGH_THRESHOLD_SET    (10)
#define AM_SENSOR_AS621X_TLOW_THRESHOLD_GET     (11)
#define AM_SENSOR_AS621X_THIGH_THRESHOLD_GET    (12)

/**
 * \brief ������AS621X�ṩ������ͨ��ID����
 */
#define AM_AS621X_CHAN_1      0             /* AS621X ��ͨ��1���¶ȴ�����ͨ�� */

/**
 * \brief AS621X�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct as621x_param_config
{
    uint8_t     conversion_rate;    /* ת������ */
    uint8_t     sleep_mode;         /* SMλ */
    am_bool_t   polarity_high;      /* ��������:�Ƿ�ߵ�ƽ���� */
    uint8_t     consecutive_faults; /* ���������� */
    float       tlow_temp;          /* ���¶���ֵ */
    float       thigh_temp;         /* ���¶���ֵ */
} as621x_param_config_t;

/**
 * \brief ������ AS621X �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_as621x_devinfo {

    const   as621x_param_config_t   *p_param_default;   /**< \brief ������ʼ�� */

    int                              trigger_pin;       /**< \brief ����������� */

    uint8_t                          i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_as621x_devinfo_t;

/**
 * \brief AS621X ����ṹ�嶨��
 */
typedef struct as621x_result_info
{
    int  as621x_temperature;           /**< \brief ʵ���¶�ֵ����10^6�� */
} as621x_result_info_t;

/**
 * \breif ������ AS621X �豸�ṹ�嶨��
 */
typedef struct am_sensor_as621x_dev {
    am_sensor_serv_t                  as621x_dev; /*< \breif ��������׼���� */
    am_i2c_device_t                   i2c_dev;    /*< \brief i2c�豸ʵ�� */
    void                             *p_arg[1];   /*< \brief �����ص��������� */
    uint8_t                           flags[1];   /*< \brief ������־λ */
    am_isr_defer_job_t                g_myjob;    /*< \brief �ж���ʱ�������� */
    uint8_t                           trigger;    /*< \brief ��¼��־λ */
    am_sensor_val_t                   data[1];    /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t            pfn_trigger_cb[1];

    /** \brief �豸��Ϣ */
    const am_sensor_as621x_devinfo_t *dev_info;

} am_sensor_as621x_dev_t;

/**
 * \brief ������ AS621X ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���AS621X�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���AS621X�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_as621x_init (
        am_sensor_as621x_dev_t           *p_dev,
        const am_sensor_as621x_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ AS621X ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_as621x_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_as621x_deinit (am_sensor_handle_t handle);

/**
 * \brief ������ AS621X ���ƺ���
 *
 * \param[in] handle    : am_sensor_as621x_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *   - AM_SENSOR_AS621X_ALERT_BIT_GET       : ��ȡ����λ, p_argΪ (uint8_t *)����
 *   - AM_SENSOR_AS621X_CR_SET              : ����ת������, p_argΪ uint8_t����
 *   - AM_SENSOR_AS621X_SM_SET              : ����SMλ(Sleep Mode), p_argΪ uint8_t����
 *   - AM_SENSOR_AS621X_SM_GET              : ��ȡSMλ, p_argΪ (uint8_t *)����
 *   - AM_SENSOR_AS621X_IM_SET              : ����IMλ(Interrupt Mode), p_argΪ uint8_t����
 *   - AM_SENSOR_AS621X_POLARITY_SET        : ����POLλ(Polarity), p_argΪ am_bool_t����
 *   - AM_SENSOR_AS621X_CF_SET              : ��������������(Consecutive Faults), p_argΪ uint8_t����
 *   - AM_SENSOR_AS621X_SS_SET              : ����SSλ, p_argΪ am_bool_t����
 *   - AM_SENSOR_AS621X_TLOW_THRESHOLD_SET  : ���õ��¶���ֵ, p_argΪ float����
 *   - AM_SENSOR_AS621X_THIGH_THRESHOLD_SET : ���ø��¶���ֵ, p_argΪ float����
 *   - AM_SENSOR_AS621X_TLOW_THRESHOLD_GET  : ��ȡ���¶���ֵ, p_argΪ (float *)����
 *   - AM_SENSOR_AS621X_THIGH_THRESHOLD_GET : ��ȡ���¶���ֵ, p_argΪ (float *)����
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_as621x_ioctl (am_sensor_handle_t  handle,
                                 int                 cmd,
                                 void               *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_AS621X_H */

/* end of file */
