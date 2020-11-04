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
 * \brief �����⴫���� TSL2540 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TSL2540_H
#define __AM_SENSOR_TSL2540_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ TSL2540 ʹ������
 */
#define AM_TSL2540_WEN                      (1u << 3)
#define AM_TSL2540_AEN                      (1u << 1)
#define AM_TSL2540_PON                      (1u << 0)

/**
 * \brief ������ TSL2540 ALS ADC�Ļ���ʱ��
 */
#define AM_TSL2540_ATIME_2_8MS              (0x00)
#define AM_TSL2540_ATIME_5_6MS              (0x01)
#define AM_TSL2540_ATIME_180MS              (0x3F)
#define AM_TSL2540_ATIME_721MS              (0xFF)

/**
 * \brief ������ TSL2540 ALS�ȴ�ʱ��
 */
#define AM_TSL2540_WTIME_2_8MS_OR_33_8MS    (0x00)
#define AM_TSL2540_WTIME_5_6MS_OR_67_6MS    (0x01)
#define AM_TSL2540_WTIME_180MS_OR_2_16S     (0x3F)
#define AM_TSL2540_WTIME_721MS_OR_8_65S     (0xFF)

/**
 * \brief ������ TSL2540 ALS����������
 */
#define AM_TSL2540_AGAIN_1_2                (0x01)  /**< \brief 1/2 Gain */
#define AM_TSL2540_AGAIN_1                  (0x02)  /**< \brief 1 Gain */
#define AM_TSL2540_AGAIN_4                  (0x03)  /**< \brief 4 Gain */
#define AM_TSL2540_AGAIN_16                 (0x04)  /**< \brief 16 Gain */
#define AM_TSL2540_AGAIN_64                 (0x05)  /**< \brief 64 Gain */
#define AM_TSL2540_AGAIN_128                (0x06)  /**< \brief 128 Gain */

/**
 * \brief ������ TSL2540 STATUSλ
 */
#define AM_TSL2540_STATUS_ASAT              (1u << 7)
#define AM_TSL2540_STATUS_AINT              (1u << 4)
#define AM_TSL2540_STATUS_CINT              (1u << 3)

/**
 * \brief ������ TSL2540 �ж�ʹ��
 */
#define AM_TSL2540_ASIEN                    (1u << 7)
#define AM_TSL2540_AIEN                     (1u << 4)

/**
 * \brief ������ TSL2540 ����ָ���
 */
#define AM_SENSOR_TSL2540_FUNC_ENABLE               (1)
#define AM_SENSOR_TSL2540_FUNC_DISABLE              (2)
#define AM_SENSOR_TSL2540_ATIME_SET                 (3)
#define AM_SENSOR_TSL2540_WTIME_SET                 (4)
#define AM_SENSOR_TSL2540_LOW_ALS_THRESHOLD_SET     (5)
#define AM_SENSOR_TSL2540_HIGH_ALS_THRESHOLD_SET    (6)
#define AM_SENSOR_TSL2540_LOW_ALS_THRESHOLD_GET     (7)
#define AM_SENSOR_TSL2540_HIGH_ALS_THRESHOLD_GET    (8)
#define AM_SENSOR_TSL2540_APERS_SET                 (9)
#define AM_SENSOR_TSL2540_WLONG_SET                 (10)
#define AM_SENSOR_TSL2540_AGAIN_SET                 (11)
#define AM_SENSOR_TSL2540_REVID_GET                 (12)
#define AM_SENSOR_TSL2540_ID_GET                    (13)
#define AM_SENSOR_TSL2540_STATUS_FLAG_CLR           (14)
#define AM_SENSOR_TSL2540_REVID2_GET                (15)
#define AM_SENSOR_TSL2540_AZ_NTH_ITERATION_SET      (16)
#define AM_SENSOR_TSL2540_INT_ENABLE                (17)
#define AM_SENSOR_TSL2540_INT_DISABLE               (18)

/*
 * \brief ������TSL2540�ṩ������ͨ��ID����
 */
#define AM_TSL2540_CHAN_1      0        /* TSL2540 ��ͨ��1��visible */
#define AM_TSL2540_CHAN_2      1        /* TSL2540 ��ͨ��2��IR */

/**
 * \brief TSL2540�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct tsl2540_param_config
{
    uint8_t     atime_val;              /**< \brief ALS ADC�Ļ���ʱ�� */
    uint8_t     wtime_val;              /**< \brief ALS�ȴ�ʱ�� */
    uint8_t     apers_val;              /**< \brief ALS�жϹ����� */
    am_bool_t   wlong_en;               /**< \brief WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
    uint8_t     again_val;              /**< \brief ALS���������� */
    am_bool_t   sleep_after_interrupt;  /**< \brief SAI */
    uint8_t     az_nth_iteration_val;   /**< \brief AZ_NTH_ITERATION */
} tsl2540_param_config_t;

/**
 * \brief ������ TSL2540 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tsl2540_devinfo {

    const   tsl2540_param_config_t  *p_param_default;   /**< \brief ������ʼ�� */

    int                              trigger_pin;       /**< \brief ����������� */

    uint8_t                          i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_tsl2540_devinfo_t;

/**
 * \brief TSL2540 ����ṹ�嶨��
 */
typedef struct tsl2540_result_info
{
    uint16_t visible_channel_data;      /**< \brief visible */
    uint16_t ir_channel_data;           /**< \brief IR */
} tsl2540_result_info_t;

/**
 * \breif ������ TSL2540 �豸�ṹ�嶨��
 */
typedef struct am_sensor_tsl2540_dev {
    am_sensor_serv_t                    tsl2540_dev;    /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    void                                *p_arg[2];      /*< \brief �����ص��������� */
    uint8_t                             flags[2];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint8_t                             trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[2];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[2];

    /** \brief �豸��Ϣ */
    const am_sensor_tsl2540_devinfo_t   *dev_info;

} am_sensor_tsl2540_dev_t;

/**
 * \brief ������ TSL2540 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TSL2540�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TSL2540�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tsl2540_init (
        am_sensor_tsl2540_dev_t             *p_dev,
        const am_sensor_tsl2540_devinfo_t   *p_devinfo,
        am_i2c_handle_t                      handle);

/**
 * \brief ������ TSL2540 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tsl2540_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tsl2540_deinit (am_sensor_handle_t handle);

/**
 * \brief ������ TSL2540 ���ƺ���
 *
 * \param[in] handle    : am_sensor_tsl2540_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *   - AM_SENSOR_TSL2540_FUNC_ENABLE            : ���ù���ʹ�� , p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_FUNC_DISABLE           : ���ù��ܽ��� , p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_ATIME_SET              : ����ATIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_WTIME_SET              : ����WTIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_LOW_ALS_THRESHOLD_SET  : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TSL2540_HIGH_ALS_THRESHOLD_SET : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TSL2540_LOW_ALS_THRESHOLD_GET  : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TSL2540_HIGH_ALS_THRESHOLD_GET : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TSL2540_APERS_SET              : ����APERS , p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_WLONG_SET              : ����WLONG, p_argΪ am_bool_t����
 *   - AM_SENSOR_TSL2540_AGAIN_SET              : ����ALS���������� , p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_REVID_GET              : ��ȡREVID , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TSL2540_ID_GET                 : ��ȡID, p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TSL2540_STATUS_FLAG_CLR        : STATUS�Ĵ���λ���, p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_REVID2_GET             : ��ȡREVID2 , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TSL2540_AZ_NTH_ITERATION_SET   : ����AZ_NTH_ITERATION, p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_INT_ENABLE             : �ж�ʹ��, p_argΪ uint8_t����
 *   - AM_SENSOR_TSL2540_INT_DISABLE            : �жϽ���, p_argΪ uint8_t����
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_tsl2540_ioctl (am_sensor_handle_t    handle,
                                  int                   cmd,
                                  void                 *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TSL2540_H */

/* end of file */


