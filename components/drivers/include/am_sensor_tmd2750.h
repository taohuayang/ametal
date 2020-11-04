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
 * \brief �����⡢�ӽ������� TMD2750 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TMD2750_H
#define __AM_SENSOR_TMD2750_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ TMD2750 ʹ������
 */
#define AM_TMD2750_WEN                            (1u << 3)
#define AM_TMD2750_PEN                            (1u << 2)
#define AM_TMD2750_AEN                            (1u << 1)
#define AM_TMD2750_PON                            (1u << 0)

/**
 * \brief ������ TMD2750 ALS ADC�Ļ���ʱ��
 */
#define AM_TMD2750_ATIME_2_78MS                   (0x00)
#define AM_TMD2750_ATIME_5_56MS                   (0x01)
#define AM_TMD2750_ATIME_50MS                     (0x11)
#define AM_TMD2750_ATIME_100MS                    (0x23)
#define AM_TMD2750_ATIME_178MS                    (0x3F)
#define AM_TMD2750_ATIME_712MS                    (0xFF)

/**
 * \brief ������ TMD2750 ALS��Prox�ȴ�ʱ��
 */
#define AM_TMD2750_WTIME_2_78MS_OR_33_4MS         (0x00)
#define AM_TMD2750_WTIME_5_56MS_OR_66_7MS         (0x01)
#define AM_TMD2750_WTIME_50MS_OR_600MS            (0x11)
#define AM_TMD2750_WTIME_100MS_OR_1_2S            (0x23)
#define AM_TMD2750_WTIME_178MS_OR_2_14S           (0x3F)
#define AM_TMD2750_WTIME_712MS_OR_8_54S           (0xFF)

/**
 * \brief ������ TMD2750 Prox���峤��
 */
#define AM_TMD2750_PULSE_LEN_4US_OR_64US          (0x00)
#define AM_TMD2750_PULSE_LEN_8US_OR_128US         (0x01)
#define AM_TMD2750_PULSE_LEN_16US_OR_256US        (0x02)
#define AM_TMD2750_PULSE_LEN_32US_OR_512US        (0x03)

/**
 * \brief ������ TMD2750 Prox IR����������
 */
#define AM_TMD2750_PGAIN_1                        (0x00)
#define AM_TMD2750_PGAIN_2                        (0x01)
#define AM_TMD2750_PGAIN_4                        (0x02)
#define AM_TMD2750_PGAIN_8                        (0x03)

/**
 * \brief ������ TMD2750 Prox IR VCSEL����������������
 */
#define AM_TMD2750_PLDRIVE_2MA                    (0x00)
#define AM_TMD2750_PLDRIVE_4MA                    (0x01)
#define AM_TMD2750_PLDRIVE_6MA                    (0x02)
#define AM_TMD2750_PLDRIVE_8MA                    (0x03)
#define AM_TMD2750_PLDRIVE_10MA                   (0x04)
#define AM_TMD2750_PLDRIVE_12MA                   (0x05)
#define AM_TMD2750_PLDRIVE_14MA                   (0x06)
#define AM_TMD2750_PLDRIVE_17MA                   (0x07)
#define AM_TMD2750_PLDRIVE_19MA                   (0x08)

/**
 * \brief ������ TMD2750 ALS����������
 */
#define AM_TMD2750_AGAIN_1                        (0x01)
#define AM_TMD2750_AGAIN_4                        (0x03)
#define AM_TMD2750_AGAIN_16                       (0x05)
#define AM_TMD2750_AGAIN_64                       (0x07)
#define AM_TMD2750_AGAIN_128                      (0x08)
#define AM_TMD2750_AGAIN_256                      (0x09)
#define AM_TMD2750_AGAIN_512                      (0x0A)

/**
 * \brief ������ TMD2750 STATUSλ
 */
#define AM_TMD2750_STATUS_ASAT                    (1u << 7)
#define AM_TMD2750_STATUS_PSAT                    (1u << 6)
#define AM_TMD2750_STATUS_PINT                    (1u << 5)
#define AM_TMD2750_STATUS_AINT                    (1u << 4)
#define AM_TMD2750_STATUS_CINT                    (1u << 3)
#define AM_TMD2750_STATUS_ZINT                    (1u << 2)
#define AM_TMD2750_STATUS_PSAT_REFLECTIVE         (1u << 1)
#define AM_TMD2750_STATUS_PSAT_AMBIENT            (1u << 0)


/**
 * \brief ������ TMD2750 APC����
 */
#define AM_TMD2750_APC_ENABLE                     (0x00)
#define AM_TMD2750_APC_DISABLE                    (0x01)

/**
 * \brief ������ TMD2750 ProxУ׼����ѡ��
 */
#define AM_TMD2750_ELECTRICAL_OPTICAL_CROSSTALK   (0x00)
#define AM_TMD2750_ELECTRICAL_CROSSTALK_ONLY      (0x01)

/**
 * \brief ������ TMD2750 ����������Ŀ��
 */
#define AM_TMD2750_BINSRCH_TARGET_3               (0x00)
#define AM_TMD2750_BINSRCH_TARGET_7               (0x01)
#define AM_TMD2750_BINSRCH_TARGET_15              (0x02)
#define AM_TMD2750_BINSRCH_TARGET_31              (0x03)
#define AM_TMD2750_BINSRCH_TARGET_63              (0x04)
#define AM_TMD2750_BINSRCH_TARGET_127             (0x05)
#define AM_TMD2750_BINSRCH_TARGET_255             (0x06)
#define AM_TMD2750_BINSRCH_TARGET_511             (0x07)

/**
 * \brief ������ TMD2750 PROX_AVG ��������
 */
#define AM_TMD2750_SAMPLE_SIZE_DISABLE            (0x00)
#define AM_TMD2750_SAMPLE_SIZE_2                  (0x01)
#define AM_TMD2750_SAMPLE_SIZE_4                  (0x02)
#define AM_TMD2750_SAMPLE_SIZE_8                  (0x03)
#define AM_TMD2750_SAMPLE_SIZE_16                 (0x04)
#define AM_TMD2750_SAMPLE_SIZE_32                 (0x05)
#define AM_TMD2750_SAMPLE_SIZE_64                 (0x06)
#define AM_TMD2750_SAMPLE_SIZE_128                (0x07)

/**
 * \brief ������ TMD2750 �ж�ʹ��
 */
#define AM_TMD2750_ASIEN                          (1u << 7)
#define AM_TMD2750_PSIEN                          (1u << 6)
#define AM_TMD2750_PIEN                           (1u << 5)
#define AM_TMD2750_AIEN                           (1u << 4)
#define AM_TMD2750_CIEN                           (1u << 3)
#define AM_TMD2750_ZIEN                           (1u << 2)

/**
 * \brief ������ TMD2750 ����ָ���
 */
typedef enum am_sensor_tmd2750_control_cmd {
    AM_SENSOR_TMD2750_FUNC_ENABLE = 1,
    AM_SENSOR_TMD2750_FUNC_DISABLE,
    AM_SENSOR_TMD2750_ATIME_SET,
    AM_SENSOR_TMD2750_PRATE_SET,
    AM_SENSOR_TMD2750_WTIME_SET,
    AM_SENSOR_TMD2750_LOW_ALS_THRESHOLD_SET,
    AM_SENSOR_TMD2750_HIGH_ALS_THRESHOLD_SET,
    AM_SENSOR_TMD2750_LOW_PROX_THRESHOLD_SET,
    AM_SENSOR_TMD2750_HIGH_PROX_THRESHOLD_SET,
    AM_SENSOR_TMD2750_LOW_ALS_THRESHOLD_GET,
    AM_SENSOR_TMD2750_HIGH_ALS_THRESHOLD_GET,
    AM_SENSOR_TMD2750_LOW_PROX_THRESHOLD_GET,
    AM_SENSOR_TMD2750_HIGH_PROX_THRESHOLD_GET,
    AM_SENSOR_TMD2750_PPERS_SET,
    AM_SENSOR_TMD2750_APERS_SET,
    AM_SENSOR_TMD2750_WLONG_SET,
    AM_SENSOR_TMD2750_PPULSE_LEN_16X_SET,
    AM_SENSOR_TMD2750_PPULSE_LEN_SET,
    AM_SENSOR_TMD2750_PPULSE_SET,
    AM_SENSOR_TMD2750_PGAIN_SET,
    AM_SENSOR_TMD2750_PLDRIVE_SET,
    AM_SENSOR_TMD2750_AGAIN_SET,
    AM_SENSOR_TMD2750_REVID_GET,
    AM_SENSOR_TMD2750_ID_GET,
    AM_SENSOR_TMD2750_STATUS_FLAG_CLR,
    AM_SENSOR_TMD2750_REVID2_GET,
    AM_SENSOR_TMD2750_SOFTRST,
    AM_SENSOR_TMD2750_APC_SET,
    AM_SENSOR_TMD2750_PROX_CAL_TYPE_SEL,
    AM_SENSOR_TMD2750_START_OFFSET_CAL_SET,
    AM_SENSOR_TMD2750_BINSRCH_TARGET_SET,
    AM_SENSOR_TMD2750_AUTO_OFFSET_ADJ_SET,
    AM_SENSOR_TMD2750_PROX_AVG_SET,
    AM_SENSOR_TMD2750_INT_ENABLE,
    AM_SENSOR_TMD2750_INT_DISABLE,
} am_sensor_tmd2750_control_cmd_t;

/*
 * \brief ������TMD2750�ṩ������ͨ��ID����
 */
#define AM_TMD2750_CHAN_1      0              /* TMD2750 ��ͨ��1��Prox */
#define AM_TMD2750_CHAN_2      1              /* TMD2750 ��ͨ��2��ALS */

/**
 * \brief TMD2750�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct tmd2750_param_config
{
    uint8_t     atime_val;              /**< \brief ALS ADC�Ļ���ʱ�� */
    uint8_t     wtime_val;              /**< \brief ALS��Prox֮��ĵȴ�ʱ�� */
    uint8_t     ppers_val;              /**< \brief Prox�жϹ����� */
    uint8_t     apers_val;              /**< \brief ALS�жϹ����� */
    am_bool_t   wlong_en;               /**< \brief WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
    am_bool_t   ppulse_len_16x_en;      /**< \brief Prox���峤������16������ */
    uint8_t     pulse_len;              /**< \brief Prox���峤�� */
    uint8_t     pulse;                  /**< \brief һ��Prox���ڵ���������� */
    uint8_t     pgain_val;              /**< \brief Prox IR���������� */
    uint8_t     pldrive_val;            /**< \brief Prox IR VCSEL���� */
    uint8_t     again_val;              /**< \brief ALS���������� */
    am_bool_t   sleep_after_interrupt;  /**< \brief SAI */
    uint8_t     apc_disable;            /**< \brief APC�������� */
    uint8_t     prox_cal_type;          /**< \brief ProxУ׼���� */
    uint8_t     binsrch_target;         /**< \brief BINSRCH_TARGET */
    am_bool_t   auto_offset_adj;        /**< \brief AUTO_OFFSET_ADJ */
    uint8_t     prox_avg;               /**< \brief PROX_AVG */
    uint32_t    prox_sample_time_us;    /**< \brief Prox��������ʱ��:(PRATE + 1) * 88us */
} tmd2750_param_config_t;

/**
 * \brief ������ TMD2750 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tmd2750_devinfo {

    const   tmd2750_param_config_t      *p_param_default;   /**< \brief ������ʼ�� */

    int                                  trigger_pin;       /**< \brief ����������� */

    uint8_t                              i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_tmd2750_devinfo_t;

/**
 * \brief TMD2750 ProxУ׼ֵ����
 */
typedef struct am_tmd2750_calibration_data {
    int16_t   prox_offset_adj;
} am_tmd2750_calibration_data_t;

/**
 * \brief TMD2750 ����ṹ�嶨��
 */
typedef struct tmd2750_result_info
{
    uint16_t als_channel_data;          /**< \brief ALS (CH0) */
    uint16_t ir_channel_data;           /**< \brief IR  (CH1) */
    uint16_t raw_prox_value;            /**< \brief Prox ADֵ */
    uint16_t prox_value;                /**< \brief Proxֵ */
    int16_t  prox_offset_adjust_value;  /**< \brief ProxУ׼ֵ */
} tmd2750_result_info_t;

/**
 * \breif ������ TMD2750 �豸�ṹ�嶨��
 */
typedef struct am_sensor_tmd2750_dev {
    am_sensor_serv_t                    tmd2750_dev;    /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    am_tmd2750_calibration_data_t       cal_val[1];     /*< \brief ����ProxУ׼ֵ */
    void                                *p_arg[2];      /*< \brief �����ص��������� */
    uint8_t                             flags[2];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint8_t                             trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[3];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[2];

    /** \brief �豸��Ϣ */
    const am_sensor_tmd2750_devinfo_t *dev_info;

} am_sensor_tmd2750_dev_t;

/**
 * \brief ������ TMD2750 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TMD2750�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TMD2750�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tmd2750_init (
        am_sensor_tmd2750_dev_t             *p_dev,
        const am_sensor_tmd2750_devinfo_t   *p_devinfo,
        am_i2c_handle_t                      handle);

/**
 * \brief ������ TMD2750 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tmd2750_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tmd2750_deinit (am_sensor_handle_t handle);

/**
 * \brief ������ TMD2750 ���ƺ���
 *
 * \param[in] handle    : am_sensor_tmd2750_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *   - AM_SENSOR_TMD2750_FUNC_ENABLE              : ���ù���ʹ�� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_FUNC_DISABLE             : ���ù��ܽ��� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_ATIME_SET                : ����ATIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_PRATE_SET                : ����PRATE, p_argΪ uint32_t����
 *   - AM_SENSOR_TMD2750_WTIME_SET                : ����WTIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_LOW_ALS_THRESHOLD_SET    : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD2750_HIGH_ALS_THRESHOLD_SET   : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD2750_LOW_PROX_THRESHOLD_SET   : ����Prox����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD2750_HIGH_PROX_THRESHOLD_SET  : ����Prox����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD2750_LOW_ALS_THRESHOLD_GET    : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD2750_HIGH_ALS_THRESHOLD_GET   : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD2750_LOW_PROX_THRESHOLD_GET   : ��ȡProx����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD2750_HIGH_PROX_THRESHOLD_GET  : ��ȡProx����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD2750_PPERS_SET                : ����PPERS , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_APERS_SET                : ����APERS , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_WLONG_SET                : ����WLONG, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD2750_PPULSE_LEN_16X_SET       : ����PPULSE_LEN_16X, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD2750_PPULSE_LEN_SET           : ����PPULSE_LEN , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_PPULSE_SET               : ����Prox���������������� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_PGAIN_SET                : ����Prox IR����������, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_PLDRIVE_SET              : ����Prox IR VCSEL������������, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_AGAIN_SET                : ����ALS���������� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_REVID_GET                : ��ȡREVID , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD2750_ID_GET                   : ��ȡID, p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD2750_STATUS_FLAG_CLR          : STATUS�Ĵ���λ���, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_REVID2_GET               : ��ȡREVID2 , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD2750_SOFTRST                  : �����λ , p_argΪ NULL
 *   - AM_SENSOR_TMD2750_APC_SET                  : ����APC, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_PROX_CAL_TYPE_SEL        : ѡ��ProxУ׼����, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_START_OFFSET_CAL_SET     : ����ƫ��У׼, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD2750_BINSRCH_TARGET_SET       : ����BINSRCH_TARGET , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_AUTO_OFFSET_ADJ_SET      : ����AUTO_OFFSET_ADJ , p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD2750_PROX_AVG_SET             : ����PROX_AVG, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_INT_ENABLE               : �ж�ʹ��, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2750_INT_DISABLE              : �жϽ���, p_argΪ uint8_t����
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_tmd2750_ioctl (am_sensor_handle_t  handle,
                                  int                 cmd,
                                  void               *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TMD2750_H */

/* end of file */


