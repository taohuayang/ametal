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
 * \brief �����⴫���� TSL2560 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TSL2560_H
#define __AM_SENSOR_TSL2560_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ TSL2560 ʹ������
 */
#define AM_TSL2560_NPIEN                        (1u << 7)
#define AM_TSL2560_SAI                          (1u << 6)
#define AM_TSL2560_AIEN                         (1u << 4)
#define AM_TSL2560_AEN                          (1u << 1)
#define AM_TSL2560_PON                          (1u << 0)

/**
 * \brief ������ TSL2560 ALS����
 */
#define AM_TSL2560_AGAIN_LOW_GAIN_MODE          (0x00)
#define AM_TSL2560_AGAIN_MEDIUM_GAIN_MODE       (0x01)
#define AM_TSL2560_AGAIN_HIGH_GAIN_MODE         (0x02)
#define AM_TSL2560_AGAIN_MAXIMUM_GAIN_MODE      (0x03)

/**
 * \brief ������ TSL2560 ALS ADC�Ļ���ʱ��
 */
#define AM_TSL2560_ATIME_100MS                  (0x00)
#define AM_TSL2560_ATIME_200MS                  (0x01)
#define AM_TSL2560_ATIME_300MS                  (0x02)
#define AM_TSL2560_ATIME_400MS                  (0x03)
#define AM_TSL2560_ATIME_500MS                  (0x04)
#define AM_TSL2560_ATIME_600MS                  (0x05)

/**
 * \brief ������ TSL2560 STATUSλ
 */
#define AM_TSL2560_STATUS_NPINTR                (1u << 5)
#define AM_TSL2560_STATUS_AINT                  (1u << 4)
#define AM_TSL2560_STATUS_AVALID                (1u << 0)

/**
 * \brief ������ TSL2560 ����ָ���
 */
typedef enum am_sensor_tsl2560_control_cmd {
    AM_SENSOR_TSL2560_FUNC_ENABLE = 1,
    AM_SENSOR_TSL2560_FUNC_DISABLE,
    AM_SENSOR_TSL2560_SOFTRST,
    AM_SENSOR_TSL2560_AGAIN_SET,
    AM_SENSOR_TSL2560_ATIME_SET,
    AM_SENSOR_TSL2560_LOW_ALS_THRESHOLD_SET,
    AM_SENSOR_TSL2560_HIGH_ALS_THRESHOLD_SET,
    AM_SENSOR_TSL2560_LOW_ALS_THRESHOLD_GET,
    AM_SENSOR_TSL2560_HIGH_ALS_THRESHOLD_GET,
    AM_SENSOR_TSL2560_NO_PERSIST_LOW_ALS_THRESHOLD_SET,
    AM_SENSOR_TSL2560_NO_PERSIST_HIGH_ALS_THRESHOLD_SET,
    AM_SENSOR_TSL2560_NO_PERSIST_LOW_ALS_THRESHOLD_GET,
    AM_SENSOR_TSL2560_NO_PERSIST_HIGH_ALS_THRESHOLD_GET,
    AM_SENSOR_TSL2560_APERS_SET,
    AM_SENSOR_TSL2560_PID_GET,
    AM_SENSOR_TSL2560_ID_GET,
    AM_SENSOR_TSL2560_NPINTR_GET,
    AM_SENSOR_TSL2560_AINT_GET,
    AM_SENSOR_TSL2560_AVALID_GET,
    AM_SENSOR_TSL2560_INTERRUPT_SET,
    AM_SENSOR_TSL2560_ALS_INTERRUPT_CLEAR,
    AM_SENSOR_TSL2560_ALS_AND_NO_PERSIST_ALS_INTERRUPT_CLEAR,
    AM_SENSOR_TSL2560_NO_PERSIST_ALS_INTERRUPT_CLEAR,
} am_sensor_tsl2560_control_cmd_t;

/*
 * \brief ������TSL2560�ṩ������ͨ��ID����
 */
#define AM_TSL2560_CHAN_1       0               /* TSL2560 ��ͨ��1��ALS_CH0 */
#define AM_TSL2560_CHAN_2       1               /* TSL2560 ��ͨ��2��ALS_CH1 */

/**
 * \brief TSL2560�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct tsl2560_param_config
{
    uint8_t     again_val;
    uint8_t     atime_val;
    uint8_t     apers_val;
    uint8_t     interrupt_type;
    uint16_t    als_low_threshold;
    uint16_t    als_high_threshold;
    uint16_t    no_persist_als_low_threshold;
    uint16_t    no_persist_als_high_threshold;
} tsl2560_param_config_t;

/**
 * \brief ������ TSL2560 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tsl2560_devinfo {

    const   tsl2560_param_config_t      *p_param_default;   /**< \brief ������ʼ�� */

    int                                  trigger_pin;       /**< \brief ����������� */

    uint8_t                              i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_tsl2560_devinfo_t;

/**
 * \brief TSL2560 У׼ֵ���� (�˴�������)
 */
typedef struct am_tsl2560_calibration_data {
    int16_t offset_chx_data;
} am_tsl2560_calibration_data_t;

/**
 * \brief TSL2560 ����ṹ�嶨��
 */
typedef struct tsl2560_result_info
{
    uint16_t als_ch0_data;          /**< \brief ALS (CH0) */
    uint16_t als_ch1_data;          /**< \brief ALS (CH1) */
} tsl2560_result_info_t;

/**
 * \breif ������ TSL2560 �豸�ṹ�嶨��
 */
typedef struct am_sensor_tsl2560_dev {
    am_sensor_serv_t                    tsl2560_dev;    /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    am_tsl2560_calibration_data_t       cal_val[1];     /*< \brief ����У׼ֵ */
    void                                *p_arg[2];      /*< \brief �����ص��������� */
    uint8_t                             flags[2];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint8_t                             trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[2];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[2];

    /** \brief �豸��Ϣ */
    const am_sensor_tsl2560_devinfo_t *dev_info;

} am_sensor_tsl2560_dev_t;

/**
 * \brief ������ TSL2560 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TSL2560�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TSL2560�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tsl2560_init (
        am_sensor_tsl2560_dev_t             *p_dev,
        const am_sensor_tsl2560_devinfo_t   *p_devinfo,
        am_i2c_handle_t                      handle);

/**
 * \brief ������ TSL2560 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tsl2560_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tsl2560_deinit (am_sensor_handle_t   handle);

/**
 * \brief ������ TSL2560 ���ƺ���
 *
 * \param[in] handle    : am_sensor_tsl2560_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_tsl2560_ioctl (am_sensor_handle_t    handle,
                                  int                   cmd,
                                  void                 *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TSL2560_H */

/* end of file */


