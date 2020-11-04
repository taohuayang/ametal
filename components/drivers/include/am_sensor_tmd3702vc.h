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
 * \brief ������/��ɫ���ӽ������� TMD3702VC ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TMD3702VC_H
#define __AM_SENSOR_TMD3702VC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ TMD3702VC ʹ������
 */
#define AM_TMD3702VC_WEN                            (1u << 3)
#define AM_TMD3702VC_PEN                            (1u << 2)
#define AM_TMD3702VC_AEN                            (1u << 1)
#define AM_TMD3702VC_PON                            (1u << 0)

/**
 * \brief ������ TMD3702VC ALS ADC�Ļ���ʱ��
 */
#define AM_TMD3702VC_ATIME_2_78MS                   (0x00)
#define AM_TMD3702VC_ATIME_5_56MS                   (0x01)
#define AM_TMD3702VC_ATIME_50MS                     (0x11)
#define AM_TMD3702VC_ATIME_100MS                    (0x23)
#define AM_TMD3702VC_ATIME_178MS                    (0x3F)
#define AM_TMD3702VC_ATIME_712MS                    (0xFF)

/**
 * \brief ������ TMD3702VC ALS��Prox�ȴ�ʱ��
 */
#define AM_TMD3702VC_WTIME_2_78MS_OR_33_4MS         (0x00)
#define AM_TMD3702VC_WTIME_5_56MS_OR_66_7MS         (0x01)
#define AM_TMD3702VC_WTIME_50MS_OR_600MS            (0x11)
#define AM_TMD3702VC_WTIME_100MS_OR_1_2S            (0x23)
#define AM_TMD3702VC_WTIME_178MS_OR_2_14S           (0x3F)
#define AM_TMD3702VC_WTIME_712MS_OR_8_54S           (0xFF)

/**
 * \brief ������ TMD3702VC Prox���峤��
 */
#define AM_TMD3702VC_PULSE_LEN_4US_OR_64US          (0x00)
#define AM_TMD3702VC_PULSE_LEN_8US_OR_128US         (0x01)
#define AM_TMD3702VC_PULSE_LEN_16US_OR_256US        (0x02)
#define AM_TMD3702VC_PULSE_LEN_32US_OR_512US        (0x03)

/**
 * \brief ������ TMD3702VC Prox IR����������
 */
#define AM_TMD3702VC_PGAIN_1                        (0x00)
#define AM_TMD3702VC_PGAIN_2                        (0x01)
#define AM_TMD3702VC_PGAIN_4                        (0x02)
#define AM_TMD3702VC_PGAIN_8                        (0x03)

/**
 * \brief ������ TMD3702VC Prox IR VCSEL����������������
 */
#define AM_TMD3702VC_PLDRIVE_2MA                    (0x00)
#define AM_TMD3702VC_PLDRIVE_4MA                    (0x01)
#define AM_TMD3702VC_PLDRIVE_6MA                    (0x02)
#define AM_TMD3702VC_PLDRIVE_8MA                    (0x03)
#define AM_TMD3702VC_PLDRIVE_10MA                   (0x04)
#define AM_TMD3702VC_PLDRIVE_12MA                   (0x05)
#define AM_TMD3702VC_PLDRIVE_14MA                   (0x06)
#define AM_TMD3702VC_PLDRIVE_17MA                   (0x07)
#define AM_TMD3702VC_PLDRIVE_19MA                   (0x08)

/**
 * \brief ������ TMD3702VC IR_MUX����
 */
#define AM_TMD3702VC_IR_MUX_DISABLE                 (0x00)
#define AM_TMD3702VC_IR_MUX_ENABLE                  (0x01)

/**
 * \brief ������ TMD3702VC ALS/Color����������
 */
#define AM_TMD3702VC_AGAIN_1                        (0x01)
#define AM_TMD3702VC_AGAIN_4                        (0x03)
#define AM_TMD3702VC_AGAIN_16                       (0x05)
#define AM_TMD3702VC_AGAIN_64                       (0x07)
#define AM_TMD3702VC_AGAIN_128                      (0x08)
#define AM_TMD3702VC_AGAIN_256                      (0x09)
#define AM_TMD3702VC_AGAIN_512                      (0x0A)

/**
 * \brief ������ TMD3702VC STATUSλ
 */
#define AM_TMD3702VC_STATUS_ASAT                    (1u << 7)
#define AM_TMD3702VC_STATUS_PSAT                    (1u << 6)
#define AM_TMD3702VC_STATUS_PINT                    (1u << 5)
#define AM_TMD3702VC_STATUS_AINT                    (1u << 4)
#define AM_TMD3702VC_STATUS_CINT                    (1u << 3)
#define AM_TMD3702VC_STATUS_ZINT                    (1u << 2)
#define AM_TMD3702VC_STATUS_PSAT_REFLECTIVE         (1u << 1)
#define AM_TMD3702VC_STATUS_PSAT_AMBIENT            (1u << 0)


/**
 * \brief ������ TMD3702VC APC����
 */
#define AM_TMD3702VC_APC_ENABLE                     (0x00)
#define AM_TMD3702VC_APC_DISABLE                    (0x01)

/**
 * \brief ������ TMD3702VC ProxУ׼����ѡ��
 */
#define AM_TMD3702VC_ELECTRICAL_OPTICAL_CROSSTALK   (0x00)
#define AM_TMD3702VC_ELECTRICAL_CROSSTALK_ONLY      (0x01)

/**
 * \brief ������ TMD3702VC ����������Ŀ��
 */
#define AM_TMD3702VC_BINSRCH_TARGET_3               (0x00)
#define AM_TMD3702VC_BINSRCH_TARGET_7               (0x01)
#define AM_TMD3702VC_BINSRCH_TARGET_15              (0x02)
#define AM_TMD3702VC_BINSRCH_TARGET_31              (0x03)
#define AM_TMD3702VC_BINSRCH_TARGET_63              (0x04)
#define AM_TMD3702VC_BINSRCH_TARGET_127             (0x05)
#define AM_TMD3702VC_BINSRCH_TARGET_255             (0x06)
#define AM_TMD3702VC_BINSRCH_TARGET_511             (0x07)

/**
 * \brief ������ TMD3702VC PROX_AVG ��������
 */
#define AM_TMD3702VC_SAMPLE_SIZE_DISABLE            (0x00)
#define AM_TMD3702VC_SAMPLE_SIZE_2                  (0x01)
#define AM_TMD3702VC_SAMPLE_SIZE_4                  (0x02)
#define AM_TMD3702VC_SAMPLE_SIZE_8                  (0x03)
#define AM_TMD3702VC_SAMPLE_SIZE_16                 (0x04)
#define AM_TMD3702VC_SAMPLE_SIZE_32                 (0x05)
#define AM_TMD3702VC_SAMPLE_SIZE_64                 (0x06)
#define AM_TMD3702VC_SAMPLE_SIZE_128                (0x07)

/**
 * \brief ������ TMD3702VC �ж�ʹ��
 */
#define AM_TMD3702VC_ASIEN                          (1u << 7)
#define AM_TMD3702VC_PSIEN                          (1u << 6)
#define AM_TMD3702VC_PIEN                           (1u << 5)
#define AM_TMD3702VC_AIEN                           (1u << 4)
#define AM_TMD3702VC_CIEN                           (1u << 3)
#define AM_TMD3702VC_ZIEN                           (1u << 2)

/**
 * \brief ������ TMD3702VC ����ָ���
 */
typedef enum am_sensor_tmd3702vc_control_cmd {
    AM_SENSOR_TMD3702VC_FUNC_ENABLE = 1,
    AM_SENSOR_TMD3702VC_FUNC_DISABLE,
    AM_SENSOR_TMD3702VC_ATIME_SET,
    AM_SENSOR_TMD3702VC_PRATE_SET,
    AM_SENSOR_TMD3702VC_WTIME_SET,
    AM_SENSOR_TMD3702VC_LOW_ALS_THRESHOLD_SET,
    AM_SENSOR_TMD3702VC_HIGH_ALS_THRESHOLD_SET,
    AM_SENSOR_TMD3702VC_LOW_PROX_THRESHOLD_SET,
    AM_SENSOR_TMD3702VC_HIGH_PROX_THRESHOLD_SET,
    AM_SENSOR_TMD3702VC_LOW_ALS_THRESHOLD_GET,
    AM_SENSOR_TMD3702VC_HIGH_ALS_THRESHOLD_GET,
    AM_SENSOR_TMD3702VC_LOW_PROX_THRESHOLD_GET,
    AM_SENSOR_TMD3702VC_HIGH_PROX_THRESHOLD_GET,
    AM_SENSOR_TMD3702VC_PPERS_SET,
    AM_SENSOR_TMD3702VC_APERS_SET,
    AM_SENSOR_TMD3702VC_WLONG_SET,
    AM_SENSOR_TMD3702VC_PPULSE_LEN_16X_SET,
    AM_SENSOR_TMD3702VC_PPULSE_LEN_SET,
    AM_SENSOR_TMD3702VC_PPULSE_SET,
    AM_SENSOR_TMD3702VC_PGAIN_SET,
    AM_SENSOR_TMD3702VC_PLDRIVE_SET,
    AM_SENSOR_TMD3702VC_IR_MUX_SET,
    AM_SENSOR_TMD3702VC_AGAIN_SET,
    AM_SENSOR_TMD3702VC_REVID_GET,
    AM_SENSOR_TMD3702VC_ID_GET,
    AM_SENSOR_TMD3702VC_STATUS_FLAG_CLR,
    AM_SENSOR_TMD3702VC_REVID2_GET,
    AM_SENSOR_TMD3702VC_SOFTRST,
    AM_SENSOR_TMD3702VC_APC_SET,
    AM_SENSOR_TMD3702VC_PROX_CAL_TYPE_SEL,
    AM_SENSOR_TMD3702VC_START_OFFSET_CAL_SET,
    AM_SENSOR_TMD3702VC_BINSRCH_TARGET_SET,
    AM_SENSOR_TMD3702VC_AUTO_OFFSET_ADJ_SET,
    AM_SENSOR_TMD3702VC_PROX_AVG_SET,
    AM_SENSOR_TMD3702VC_INT_ENABLE,
    AM_SENSOR_TMD3702VC_INT_DISABLE,
} am_sensor_tmd3702vc_control_cmd_t;

/*
 * \brief ������TMD3702VC�ṩ������ͨ��ID����
 */
#define AM_TMD3702VC_CHAN_1      0              /* TMD3702VC ��ͨ��1��Prox */
#define AM_TMD3702VC_CHAN_2      1              /* TMD3702VC ��ͨ��2��ALS */

/**
 * \brief TMD3702VC�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct tmd3702vc_param_config
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
    am_bool_t   ir_mux;                 /**< \brief IR_MUX */
    uint8_t     again_val;              /**< \brief ALS/Color���������� */
    am_bool_t   sleep_after_interrupt;  /**< \brief SAI */
    uint8_t     apc_disable;            /**< \brief APC�������� */
    uint8_t     prox_cal_type;          /**< \brief ProxУ׼���� */
    uint8_t     binsrch_target;         /**< \brief BINSRCH_TARGET */
    am_bool_t   auto_offset_adj;        /**< \brief AUTO_OFFSET_ADJ */
    uint8_t     prox_avg;               /**< \brief PROX_AVG */
    uint32_t    prox_sample_time_us;    /**< \brief Prox��������ʱ��:(PRATE + 1) * 88us */
} tmd3702vc_param_config_t;

/**
 * \brief ������ TMD3702VC �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tmd3702vc_devinfo {

    const   tmd3702vc_param_config_t    *p_param_default;   /**< \brief ������ʼ�� */

    int                                  trigger_pin;       /**< \brief ����������� */

    uint8_t                              i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_tmd3702vc_devinfo_t;

/**
 * \brief TMD3702VC ProxУ׼ֵ����
 */
typedef struct am_tmd3702vc_calibration_data {
    int16_t   prox_offset_adj;
} am_tmd3702vc_calibration_data_t;

/**
 * \brief TMD3702VC ����ṹ�嶨��
 */
typedef struct tmd3702vc_result_info
{
    uint16_t clear_channel_data;        /**< \brief clear */
    uint16_t red_channel_data;          /**< \brief red */
    uint16_t green_or_ir_channel_data;  /**< \brief green_or_ir */
    uint16_t blue_channel_data;         /**< \brief blue */
    uint16_t raw_prox_value;            /**< \brief Prox ADֵ */
    uint16_t prox_value;                /**< \brief Proxֵ */
    int16_t  prox_offset_adjust_value;  /**< \brief ProxУ׼ֵ */
} tmd3702vc_result_info_t;

/**
 * \breif ������ TMD3702VC �豸�ṹ�嶨��
 */
typedef struct am_sensor_tmd3702vc_dev {
    am_sensor_serv_t                    tmd3702vc_dev;  /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    am_tmd3702vc_calibration_data_t     cal_val[1];     /*< \brief ����ProxУ׼ֵ */
    void                                *p_arg[2];      /*< \brief �����ص��������� */
    uint8_t                             flags[2];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint8_t                             trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[5];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[2];

    /** \brief �豸��Ϣ */
    const am_sensor_tmd3702vc_devinfo_t *dev_info;

} am_sensor_tmd3702vc_dev_t;

/**
 * \brief ������ TMD3702VC ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TMD3702VC�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TMD3702VC�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tmd3702vc_init (
        am_sensor_tmd3702vc_dev_t           *p_dev,
        const am_sensor_tmd3702vc_devinfo_t *p_devinfo,
        am_i2c_handle_t                     handle);

/**
 * \brief ������ TMD3702VC ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tmd3702vc_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tmd3702vc_deinit (am_sensor_handle_t handle);

/**
 * \brief ������ TMD3702VC ���ƺ���
 *
 * \param[in] handle    : am_sensor_tmd3702vc_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *   - AM_SENSOR_TMD3702VC_FUNC_ENABLE              : ���ù���ʹ�� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_FUNC_DISABLE             : ���ù��ܽ��� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_ATIME_SET                : ����ATIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_PRATE_SET                : ����PRATE, p_argΪ uint32_t����
 *   - AM_SENSOR_TMD3702VC_WTIME_SET                : ����WTIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_LOW_ALS_THRESHOLD_SET    : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD3702VC_HIGH_ALS_THRESHOLD_SET   : ����ALS����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD3702VC_LOW_PROX_THRESHOLD_SET   : ����Prox����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD3702VC_HIGH_PROX_THRESHOLD_SET  : ����Prox����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD3702VC_LOW_ALS_THRESHOLD_GET    : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD3702VC_HIGH_ALS_THRESHOLD_GET   : ��ȡALS����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD3702VC_LOW_PROX_THRESHOLD_GET   : ��ȡProx����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD3702VC_HIGH_PROX_THRESHOLD_GET  : ��ȡProx����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD3702VC_PPERS_SET                : ����PPERS , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_APERS_SET                : ����APERS , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_WLONG_SET                : ����WLONG, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD3702VC_PPULSE_LEN_16X_SET       : ����PPULSE_LEN_16X, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD3702VC_PPULSE_LEN_SET           : ����PPULSE_LEN , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_PPULSE_SET               : ����Prox���������������� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_PGAIN_SET                : ����Prox IR����������, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_PLDRIVE_SET              : ����Prox IR VCSEL������������, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_IR_MUX_SET               : ����IR_MUX, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD3702VC_AGAIN_SET                : ����ALS/Color���������� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_REVID_GET                : ��ȡREVID , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD3702VC_ID_GET                   : ��ȡID, p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD3702VC_STATUS_FLAG_CLR          : STATUS�Ĵ���λ���, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_REVID2_GET               : ��ȡREVID2 , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD3702VC_SOFTRST                  : �����λ , p_argΪ NULL
 *   - AM_SENSOR_TMD3702VC_APC_SET                  : ����APC, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_PROX_CAL_TYPE_SEL        : ѡ��ProxУ׼����, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_START_OFFSET_CAL_SET     : ����ƫ��У׼, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD3702VC_BINSRCH_TARGET_SET       : ����BINSRCH_TARGET , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_AUTO_OFFSET_ADJ_SET      : ����AUTO_OFFSET_ADJ , p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD3702VC_PROX_AVG_SET             : ����PROX_AVG, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_INT_ENABLE               : �ж�ʹ��, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD3702VC_INT_DISABLE              : �жϽ���, p_argΪ uint8_t����
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_tmd3702vc_ioctl (am_sensor_handle_t  handle,
                                    int                 cmd,
                                    void               *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TMD3702VC_H */

/* end of file */


