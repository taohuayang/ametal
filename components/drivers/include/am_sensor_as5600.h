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
 * \brief �Ƕȴ����� AS5600 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_AS5600_H
#define __AM_SENSOR_AS5600_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ AS5600 Watchdog
 */
#define AM_AS5600_WD_OFF                        (0x00)
#define AM_AS5600_WD_ON                         (0x01)

/**
 * \brief ������ AS5600 Fast Filter Threshold
 */
#define AM_AS5600_FTH_SLOW_FILTER_ONLY          (0x00)
#define AM_AS5600_FTH_6_LSBS                    (0x01)
#define AM_AS5600_FTH_7_LSBS                    (0x02)
#define AM_AS5600_FTH_9_LSBS                    (0x03)
#define AM_AS5600_FTH_18_LSBS                   (0x04)
#define AM_AS5600_FTH_21_LSBS                   (0x05)
#define AM_AS5600_FTH_24_LSBS                   (0x06)
#define AM_AS5600_FTH_10_LSBS                   (0x07)

/**
 * \brief ������ AS5600 Slow Filter
 */
#define AM_AS5600_SF_16                         (0x00)  /* ǿ���ڵ͹���ģʽ(LPM) */
#define AM_AS5600_SF_8                          (0x01)
#define AM_AS5600_SF_4                          (0x02)
#define AM_AS5600_SF_2                          (0x03)

/**
 * \brief ������ AS5600 PWM Frequency
 */
#define AM_AS5600_PWMF_115_HZ                   (0x00)
#define AM_AS5600_PWMF_230_HZ                   (0x01)
#define AM_AS5600_PWMF_460_HZ                   (0x02)
#define AM_AS5600_PWMF_920_HZ                   (0x03)

/**
 * \brief ������ AS5600 Output Stage
 */
#define AM_AS5600_OUTS_ANALOG_0_TO_100          (0x00)
#define AM_AS5600_OUTS_ANALOG_10_TO_90          (0x01)
#define AM_AS5600_OUTS_DIGITAL_PWM              (0x02)

/**
 * \brief ������ AS5600 Hysteresis
 */
#define AM_AS5600_HYST_OFF                      (0x00)
#define AM_AS5600_HYST_1_LSB                    (0x01)
#define AM_AS5600_HYST_2_LSBS                   (0x02)
#define AM_AS5600_HYST_3_LSBS                   (0x03)

/**
 * \brief ������ AS5600 Power Mode
 */
#define AM_AS5600_PM_NOM                        (0x00)
#define AM_AS5600_PM_LPM1                       (0x01)
#define AM_AS5600_PM_LPM2                       (0x02)
#define AM_AS5600_PM_LPM3                       (0x03)

/**
 * \brief ������ AS5600 Burn Commands
 */
#define AM_AS5600_BURN_ANGLE                    (0x80)
#define AM_AS5600_BURN_SETTING                  (0x40)

/**
 * \brief ������ AS5600 Direction polarity
 */
#define AM_AS5600_INCREASE_CLOCKWISE            (0x00)
#define AM_AS5600_INCREASE_COUNTERCLOCKWISE     (0x01)

/**
 * \brief ������ AS5600 option
 */
#define AM_AS5600_OPTION_DISABLE                (0x00)
#define AM_AS5600_OPTION_ENABLE                 (0x01)

/**
 * \brief ������ AS5600 programming the angular range
 */
#define AM_AS5600_OPTION_A                      (0x00)
#define AM_AS5600_OPTION_B                      (0x01)
#define AM_AS5600_OPTION_C                      (0x02)

/**
 * \brief ������ AS5600 ����ָ���
 */
typedef enum am_sensor_as5600_control_cmd {
    AM_SENSOR_AS5600_ZMCO_GET = 1,
    AM_SENSOR_AS5600_ZPOS_SET,
    AM_SENSOR_AS5600_ZPOS_GET,
    AM_SENSOR_AS5600_MPOS_SET,
    AM_SENSOR_AS5600_MPOS_GET,
    AM_SENSOR_AS5600_MANG_SET,
    AM_SENSOR_AS5600_MANG_GET,
    AM_SENSOR_AS5600_WD_SET,
    AM_SENSOR_AS5600_FTH_SET,
    AM_SENSOR_AS5600_SF_SET,
    AM_SENSOR_AS5600_PWMF_SET,
    AM_SENSOR_AS5600_OUTS_SET,
    AM_SENSOR_AS5600_HYST_SET,
    AM_SENSOR_AS5600_PM_SET,
    AM_SENSOR_AS5600_CONF_GET,
    AM_SENSOR_AS5600_RAW_ANGLE_GET,
    AM_SENSOR_AS5600_ANGLE_GET,
    AM_SENSOR_AS5600_MD_GET,
    AM_SENSOR_AS5600_ML_GET,
    AM_SENSOR_AS5600_MH_GET,
    AM_SENSOR_AS5600_AGC_GET,
    AM_SENSOR_AS5600_MAGNITUDE_GET,
    AM_SENSOR_AS5600_BURN_SET,
} am_sensor_as5600_control_cmd_t;

/*
 * \brief ������AS5600�ṩ������ͨ��ID����
 */
#define AM_AS5600_CHAN_1      0              /* AS5600 ��ͨ��1��ANGLE */

/**
 * \brief AS5600�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct as5600_param_config
{
    uint8_t     watchdog;
    uint8_t     fast_filter_threshold;
    uint8_t     slow_filter;
    uint8_t     pwm_frequency;
    uint8_t     output_stage;
    uint8_t     hysteresis;
    uint8_t     power_mode;
    uint8_t     direction_polarity;
    uint8_t     option_enable;
    uint8_t     option;
    uint16_t    maximum_angle;
} as5600_param_config_t;

/**
 * \brief ������ AS5600 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_as5600_devinfo {

    const   as5600_param_config_t      *p_param_default;    /**< \brief ������ʼ�� */

    int                                 trigger_pin;        /**< \brief ����������� */

    int                                 out_pin;            /**< \brief OUT���� */

    int                                 pgo_pin;            /**< \brief PGO���� */

    int                                 dir_pin;            /**< \brief DIR���� */

    uint8_t                             i2c_addr;           /**< \brief I2C 7λ �豸��ַ */

} am_sensor_as5600_devinfo_t;

/**
 * \brief AS5600 У׼ֵ���� (�˴�������)
 */
typedef struct am_as5600_calibration_data {
    int16_t offset_chx_data;
} am_as5600_calibration_data_t;

/**
 * \brief AS5600 ����ṹ�嶨��
 */
typedef struct as5600_result_info
{
    uint16_t raw_angle;                 /**< \brief RAW_ANGLE */
    uint16_t angle;                     /**< \brief ANGLE */
} as5600_result_info_t;

/**
 * \breif ������ AS5600 �豸�ṹ�嶨��
 */
typedef struct am_sensor_as5600_dev {
    am_sensor_serv_t                    as5600_dev;     /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    am_as5600_calibration_data_t        cal_val[1];     /*< \brief ����У׼ֵ */
    void                                *p_arg[1];      /*< \brief �����ص��������� */
    uint8_t                             flags[1];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint8_t                             trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[1];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[1];

    /** \brief �豸��Ϣ */
    const am_sensor_as5600_devinfo_t *dev_info;

} am_sensor_as5600_dev_t;

/**
 * \brief ������ AS5600 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���AS5600�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���AS5600�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_as5600_init (
        am_sensor_as5600_dev_t             *p_dev,
        const am_sensor_as5600_devinfo_t   *p_devinfo,
        am_i2c_handle_t                     handle);

/**
 * \brief ������ AS5600 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_as5600_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_as5600_deinit (am_sensor_handle_t handle);

/**
 * \brief ������ AS5600 ���ƺ���
 *
 * \param[in] handle    : am_sensor_as5600_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_as5600_ioctl (am_sensor_handle_t     handle,
                                 int                    cmd,
                                 void                  *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_AS5600_H */

/* end of file */


