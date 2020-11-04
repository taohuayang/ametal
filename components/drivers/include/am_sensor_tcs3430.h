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
 * \brief ������/��ɫ������ TCS3430 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TCS3430_H
#define __AM_SENSOR_TCS3430_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ TCS3430 ʹ������
 */
#define AM_TCS3430_WEN                      (1u << 3)
#define AM_TCS3430_AEN                      (1u << 1)
#define AM_TCS3430_PON                      (1u << 0)

/**
 * \brief ������ TCS3430 ALS ADC�Ļ���ʱ��
 */
#define AM_TCS3430_ATIME_2_78MS             (0x00)
#define AM_TCS3430_ATIME_5_56MS             (0x01)
#define AM_TCS3430_ATIME_50MS               (0x11)
#define AM_TCS3430_ATIME_181MS              (0x40)
#define AM_TCS3430_ATIME_711MS              (0xFF)

/**
 * \brief ������ TCS3430 ALS�ȴ�ʱ��
 */
#define AM_TCS3430_WTIME_2_78MS_OR_33_4MS   (0x00)
#define AM_TCS3430_WTIME_5_56MS_OR_66_7MS   (0x01)
#define AM_TCS3430_WTIME_100MS_OR_1_2S      (0x23)
#define AM_TCS3430_WTIME_711MS_OR_8_53S     (0xFF)

/**
 * \brief ������ TCS3430 AMUX����
 */
#define AM_TCS3430_AMUX_DISABLE             (0x00)
#define AM_TCS3430_AMUX_ENABLE              (0x01)

/**
 * \brief ������ TCS3430 ALS����������
 */
#define AM_TCS3430_AGAIN_1                  (0x01)
#define AM_TCS3430_AGAIN_4                  (0x02)
#define AM_TCS3430_AGAIN_16                 (0x03)
#define AM_TCS3430_AGAIN_64                 (0x04)
#define AM_TCS3430_AGAIN_128                (0x05)

/**
 * \brief ������ TCS3430 STATUSλ
 */
#define AM_TCS3430_STATUS_ASAT              (1u << 7)
#define AM_TCS3430_STATUS_AINT              (1u << 4)

/**
 * \brief ������ TCS3430 �ж�ʹ��
 */
#define AM_TCS3430_ASIEN                    (1u << 7)
#define AM_TCS3430_AIEN                     (1u << 4)

/**
 * \brief ������ TCS3430 ����ָ���
 */
#define AM_SENSOR_TCS3430_FUNC_ENABLE               (1)
#define AM_SENSOR_TCS3430_FUNC_DISABLE              (2)
#define AM_SENSOR_TCS3430_ATIME_SET                 (3)
#define AM_SENSOR_TCS3430_WTIME_SET                 (4)
#define AM_SENSOR_TCS3430_LOW_ALS_THRESHOLD_SET     (5)
#define AM_SENSOR_TCS3430_HIGH_ALS_THRESHOLD_SET    (6)
#define AM_SENSOR_TCS3430_LOW_ALS_THRESHOLD_GET     (7)
#define AM_SENSOR_TCS3430_HIGH_ALS_THRESHOLD_GET    (8)
#define AM_SENSOR_TCS3430_APERS_SET                 (9)
#define AM_SENSOR_TCS3430_WLONG_SET                 (10)
#define AM_SENSOR_TCS3430_AMUX_SET                  (11)
#define AM_SENSOR_TCS3430_AGAIN_SET                 (12)
#define AM_SENSOR_TCS3430_REVID_GET                 (13)
#define AM_SENSOR_TCS3430_ID_GET                    (14)
#define AM_SENSOR_TCS3430_STATUS_FLAG_CLR           (15)
#define AM_SENSOR_TCS3430_AZ_MODE_SET               (16)
#define AM_SENSOR_TCS3430_AZ_NTH_ITERATION_SET      (17)
#define AM_SENSOR_TCS3430_INT_ENABLE                (18)
#define AM_SENSOR_TCS3430_INT_DISABLE               (19)

/*
 * \brief ������TCS3430�ṩ������ͨ��ID����
 */
#define AM_TCS3430_CHAN_1      0        /* TCS3430 ��ͨ��1��Z */
#define AM_TCS3430_CHAN_2      1        /* TCS3430 ��ͨ��2��Y */
#define AM_TCS3430_CHAN_3      2        /* TCS3430 ��ͨ��3��IR1 */
#define AM_TCS3430_CHAN_4      3        /* TCS3430 ��ͨ��4��X/IR2 */

/**
 * \brief TCS3430�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct tcs3430_param_config
{
    uint8_t     atime_val;              /**< \brief ALS ADC�Ļ���ʱ�� */
    uint8_t     wtime_val;              /**< \brief ALS�ȴ�ʱ�� */
    uint8_t     apers_val;              /**< \brief ALS�жϹ����� */
    am_bool_t   wlong_en;               /**< \brief WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
    am_bool_t   a_mux;                  /**< \brief AMUX */
    uint8_t     again_val;              /**< \brief ALS���������� */
    am_bool_t   sleep_after_interrupt;  /**< \brief SAI */
    uint8_t     az_mode;                /**< \brief AZ_MODE */
    uint8_t     az_nth_iteration_val;   /**< \brief AZ_NTH_ITERATION */
} tcs3430_param_config_t;

/**
 * \brief ������ TCS3430 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tcs3430_devinfo {

    const   tcs3430_param_config_t  *p_param_default;   /**< \brief ������ʼ�� */

    int                              trigger_pin;       /**< \brief ����������� */

    uint8_t                          i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_tcs3430_devinfo_t;

/**
 * \brief TCS3430 ����ṹ�嶨��
 */
typedef struct tcs3430_result_info
{
    uint16_t channel_0_data;        /**< \brief CH0 */
    uint16_t channel_1_data;        /**< \brief CH1 */
    uint16_t channel_2_data;        /**< \brief CH2 */
    uint16_t channel_3_data;        /**< \brief CH3 */
} tcs3430_result_info_t;

/**
 * \breif ������ TCS3430 �豸�ṹ�嶨��
 */
typedef struct am_sensor_tcs3430_dev {
    am_sensor_serv_t                    tcs3430_dev;    /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    void                                *p_arg[4];      /*< \brief �����ص��������� */
    uint8_t                             flags[4];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint16_t                            trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[4];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[4];

    /** \brief �豸��Ϣ */
    const am_sensor_tcs3430_devinfo_t   *dev_info;

} am_sensor_tcs3430_dev_t;

/**
 * \brief ������ TCS3430 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TCS3430�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TCS3430�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tcs3430_init (
        am_sensor_tcs3430_dev_t             *p_dev,
        const am_sensor_tcs3430_devinfo_t   *p_devinfo,
        am_i2c_handle_t                      handle);

/**
 * \brief ������ TCS3430 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tcs3430_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tcs3430_deinit (am_sensor_handle_t handle);

/**
 * \brief ������ TCS3430 ���ƺ���
 *
 * \param[in] handle    : am_sensor_tcs3430_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *   - AM_SENSOR_TCS3430_FUNC_ENABLE            : ���ù���ʹ�� , p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_FUNC_DISABLE           : ���ù��ܽ��� , p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_ATIME_SET              : ����ATIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_WTIME_SET              : ����WTIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_LOW_ALS_THRESHOLD_SET  : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TCS3430_HIGH_ALS_THRESHOLD_SET : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TCS3430_LOW_ALS_THRESHOLD_GET  : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TCS3430_HIGH_ALS_THRESHOLD_GET : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TCS3430_APERS_SET              : ����APERS , p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_WLONG_SET              : ����WLONG, p_argΪ am_bool_t����
 *   - AM_SENSOR_TCS3430_AMUX_SET               : ����AMUX, p_argΪ am_bool_t����
 *   - AM_SENSOR_TCS3430_AGAIN_SET              : ����ALS���������� , p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_REVID_GET              : ��ȡREVID , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TCS3430_ID_GET                 : ��ȡID, p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TCS3430_STATUS_FLAG_CLR        : STATUS�Ĵ���λ���, p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_AZ_MODE_SET            : ����AZ_MODE , p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_AZ_NTH_ITERATION_SET   : ����AZ_NTH_ITERATION, p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_INT_ENABLE             : �ж�ʹ��, p_argΪ uint8_t����
 *   - AM_SENSOR_TCS3430_INT_DISABLE            : �жϽ���, p_argΪ uint8_t����
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_tcs3430_ioctl (am_sensor_handle_t    handle,
                                  int                   cmd,
                                  void                 *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TCS3430_H */

/* end of file */


