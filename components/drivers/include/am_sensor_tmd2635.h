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
 * \brief �ӽ������� TMD2635 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TMD2635_H
#define __AM_SENSOR_TMD2635_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ TMD2635 ʹ������
 */
#define AM_TMD2635_PWEN                         (1u << 4)
#define AM_TMD2635_PEN                          (1u << 2)
#define AM_TMD2635_PON                          (1u << 0)

/**
 * \brief ������ TMD2635 Prox IR����������
 */
#define AM_TMD2635_PGAIN_1                      (0x00)
#define AM_TMD2635_PGAIN_2                      (0x01)
#define AM_TMD2635_PGAIN_4                      (0x02)
#define AM_TMD2635_PGAIN_8                      (0x03)

/**
 * \brief ������ TMD2635 Prox���峤��
 */
#define AM_TMD2635_PULSE_LEN_1US                (0x00)
#define AM_TMD2635_PULSE_LEN_2US                (0x01)
#define AM_TMD2635_PULSE_LEN_4US                (0x02)
#define AM_TMD2635_PULSE_LEN_8US                (0x03)
#define AM_TMD2635_PULSE_LEN_12US               (0x04)
#define AM_TMD2635_PULSE_LEN_16US               (0x05)
#define AM_TMD2635_PULSE_LEN_24US               (0x06)
#define AM_TMD2635_PULSE_LEN_32US               (0x07)

/**
 * \brief ������ TMD2635 Prox IR VCSEL����������������
 */
#define AM_TMD2635_PLDRIVE_2MA                  (0x00)
#define AM_TMD2635_PLDRIVE_3MA                  (0x01)
#define AM_TMD2635_PLDRIVE_4MA                  (0x02)
#define AM_TMD2635_PLDRIVE_5MA                  (0x03)
#define AM_TMD2635_PLDRIVE_6MA                  (0x04)
#define AM_TMD2635_PLDRIVE_7MA                  (0x05)
#define AM_TMD2635_PLDRIVE_8MA                  (0x06)
#define AM_TMD2635_PLDRIVE_9MA                  (0x07)
#define AM_TMD2635_PLDRIVE_10MA                 (0x08)

/**
 * \brief ������ TMD2635 STATUSλ
 */
#define AM_TMD2635_STATUS_PHIGH                 (1u << 7)
#define AM_TMD2635_STATUS_PLOW                  (1u << 6)
#define AM_TMD2635_STATUS_PSAT                  (1u << 5)
#define AM_TMD2635_STATUS_PINT                  (1u << 4)
#define AM_TMD2635_STATUS_CINT                  (1u << 3)
#define AM_TMD2635_STATUS_ZINT                  (1u << 2)
#define AM_TMD2635_STATUS_PSAT_REFLECTIVE       (1u << 1)
#define AM_TMD2635_STATUS_PSAT_AMBIENT          (1u << 0)

/**
 * \brief ������ TMD2635 Prox�ȴ�ʱ��
 */
#define AM_TMD2635_PWTIME_2_78MS_OR_33_4MS      (0x00)
#define AM_TMD2635_PWTIME_5_56MS_OR_66_7MS      (0x01)
#define AM_TMD2635_PWTIME_50MS_OR_600MS         (0x11)
#define AM_TMD2635_PWTIME_100MS_OR_1_2S         (0x23)
#define AM_TMD2635_PWTIME_178MS_OR_2_14S        (0x3F)
#define AM_TMD2635_PWTIME_712MS_OR_8_54S        (0xFF)

/**
 * \brief ������ TMD2635 ��������ѡ��
 */
#define AM_TMD2635_PDSELECT_NO_PHOTODIODE       (0x00)
#define AM_TMD2635_PDSELECT_FAR_PHOTODIODE      (0x01)
#define AM_TMD2635_PDSELECT_NEAR_PHOTODIODE     (0x02)
#define AM_TMD2635_PDSELECT_BOTH_PHOTODIODES    (0x03)

/**
 * \brief ������ TMD2635 APC����
 */
#define AM_TMD2635_APC_ENABLE                   (0x00)
#define AM_TMD2635_APC_DISABLE                  (0x01)

/**
 * \brief ������ TMD2635 ����PMAVG
 */
#define AM_TMD2635_PMAVG_DISABLE                (0x00)
#define AM_TMD2635_PMAVG_2                      (0x01)
#define AM_TMD2635_PMAVG_4                      (0x02)
#define AM_TMD2635_PMAVG_8                      (0x03)

/**
 * \brief ������ TMD2635 CALAVG����
 */
#define AM_TMD2635_NO_HARDWARE_AVERAGING        (0x00)
#define AM_TMD2635_HARDWARE_AVERAGING_ENABLED   (0x01)

/**
 * \brief ������ TMD2635 ProxУ׼����ѡ��
 */
#define AM_TMD2635_ELECTRICAL_OPTICAL_CROSSTALK (0x00)
#define AM_TMD2635_ELECTRICAL_CROSSTALK_ONLY    (0x01)

/**
 * \brief ������ TMD2635 CALPRATE����
 */
#define AM_TMD2635_PRATE_IGNORED                (0x00)
#define AM_TMD2635_PRATE_APPLIED                (0x01)

/**
 * \brief ������ TMD2635 ����������Ŀ��
 */
#define AM_TMD2635_BINSRCH_TARGET_3             (0x00)
#define AM_TMD2635_BINSRCH_TARGET_7             (0x01)
#define AM_TMD2635_BINSRCH_TARGET_15            (0x02)
#define AM_TMD2635_BINSRCH_TARGET_31            (0x03)
#define AM_TMD2635_BINSRCH_TARGET_63            (0x04)
#define AM_TMD2635_BINSRCH_TARGET_127           (0x05)
#define AM_TMD2635_BINSRCH_TARGET_255           (0x06)
#define AM_TMD2635_BINSRCH_TARGET_511           (0x07)

/**
 * \brief ������ TMD2635 PROX_AVG ��������
 */
#define AM_TMD2635_SAMPLE_SIZE_DISABLE          (0x00)
#define AM_TMD2635_SAMPLE_SIZE_2                (0x01)
#define AM_TMD2635_SAMPLE_SIZE_4                (0x02)
#define AM_TMD2635_SAMPLE_SIZE_8                (0x03)
#define AM_TMD2635_SAMPLE_SIZE_16               (0x04)
#define AM_TMD2635_SAMPLE_SIZE_32               (0x05)
#define AM_TMD2635_SAMPLE_SIZE_64               (0x06)
#define AM_TMD2635_SAMPLE_SIZE_128              (0x07)

/**
 * \brief ������ TMD2635 �ж�ʹ��
 */
#define AM_TMD2635_PIM                          (1u << 5)
#define AM_TMD2635_PIEN                         (1u << 4)
#define AM_TMD2635_PSIEN                        (1u << 3)
#define AM_TMD2635_CIEN                         (1u << 2)
#define AM_TMD2635_ZIEN                         (1u << 1)

/**
 * \brief ������ TMD2635 ����ָ���
 */
#define AM_SENSOR_TMD2635_FUNC_ENABLE               (1)
#define AM_SENSOR_TMD2635_FUNC_DISABLE              (2)
#define AM_SENSOR_TMD2635_PRATE_SET                 (3)
#define AM_SENSOR_TMD2635_LOW_PROX_THRESHOLD_SET    (4)
#define AM_SENSOR_TMD2635_HIGH_PROX_THRESHOLD_SET   (5)
#define AM_SENSOR_TMD2635_LOW_PROX_THRESHOLD_GET    (6)
#define AM_SENSOR_TMD2635_HIGH_PROX_THRESHOLD_GET   (7)
#define AM_SENSOR_TMD2635_PPERS_SET                 (8)
#define AM_SENSOR_TMD2635_PWLONG_SET                (9)
#define AM_SENSOR_TMD2635_PGAIN_SET                 (10)
#define AM_SENSOR_TMD2635_PPULSE_SET                (11)
#define AM_SENSOR_TMD2635_PPULSE_LEN_SET            (12)
#define AM_SENSOR_TMD2635_PLDRIVE_SET               (13)
#define AM_SENSOR_TMD2635_REVID_GET                 (14)
#define AM_SENSOR_TMD2635_ID_GET                    (15)
#define AM_SENSOR_TMD2635_STATUS_FLAG_CLR           (16)
#define AM_SENSOR_TMD2635_REVID2_GET                (17)
#define AM_SENSOR_TMD2635_SOFTRST                   (18)
#define AM_SENSOR_TMD2635_PWTIME_SET                (19)
#define AM_SENSOR_TMD2635_PDSELECT_SET              (20)
#define AM_SENSOR_TMD2635_APC_SET                   (21)
#define AM_SENSOR_TMD2635_PMAVG_SET                 (22)
#define AM_SENSOR_TMD2635_CALAVG_SET                (23)
#define AM_SENSOR_TMD2635_PROX_CAL_TYPE_SEL         (24)
#define AM_SENSOR_TMD2635_CALPRATE_SET              (25)
#define AM_SENSOR_TMD2635_START_OFFSET_CAL_SET      (26)
#define AM_SENSOR_TMD2635_BINSRCH_TARGET_SET        (27)
#define AM_SENSOR_TMD2635_AUTO_OFFSET_ADJ_SET       (28)
#define AM_SENSOR_TMD2635_PROX_AVG_SET              (29)
#define AM_SENSOR_TMD2635_INT_ENABLE                (30)
#define AM_SENSOR_TMD2635_INT_DISABLE               (31)

/*
 * \brief ������TMD2635�ṩ������ͨ��ID����
 */
#define AM_TMD2635_CHAN_1      0              /* TMD2635 ��ͨ��1��Prox */

/**
 * \brief TMD2635�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct tmd2635_param_config
{
    uint8_t     ppers_val;              /**< \brief Prox�жϹ����� */
    am_bool_t   pwlong_en;              /**< \brief PWLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
    uint8_t     pgain_val;              /**< \brief Prox���峤�� */
    uint8_t     pulse;                  /**< \brief һ��Prox���ڵ���������� */
    uint8_t     pulse_len;              /**< \brief Prox IR���������� */
    uint8_t     pldrive_val;            /**< \brief Prox IR VCSEL���� */
    uint8_t     pwtime_val;             /**< \brief Prox�ȴ�ʱ�� */
    uint8_t     pdselect;               /**< \brief ��������ѡ�� */
    am_bool_t   sleep_after_interrupt;  /**< \brief SAI */
    uint8_t     apc_disable;            /**< \brief APC�������� */
    uint8_t     pmavg_val;              /**< \brief PMAVG���� */
    uint8_t     calavg;                 /**< \brief CALAVG���� */
    uint8_t     prox_cal_type;          /**< \brief ProxУ׼���� */
    uint8_t     calprate;               /**< \brief CALPRATE���� */
    uint8_t     binsrch_target;         /**< \brief BINSRCH_TARGET */
    am_bool_t   auto_offset_adj;        /**< \brief AUTO_OFFSET_ADJ */
    uint8_t     prox_avg;               /**< \brief PROX_AVG */
    uint32_t    prox_sample_time_us;    /**< \brief Prox��������ʱ��:(PRATE + 1) * 88us */
} tmd2635_param_config_t;

/**
 * \brief ������ TMD2635 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tmd2635_devinfo {

    const   tmd2635_param_config_t      *p_param_default;   /**< \brief ������ʼ�� */

    int                                  trigger_pin;       /**< \brief ����������� */

    uint8_t                              i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_tmd2635_devinfo_t;

/**
 * \brief TMD2635 ProxУ׼ֵ����
 */
typedef struct am_tmd2635_calibration_data {
    int16_t   prox_offset_adj;
} am_tmd2635_calibration_data_t;

/**
 * \brief TMD2635 ����ṹ�嶨��
 */
typedef struct tmd2635_result_info
{
    uint16_t raw_prox_value;            /**< \brief Prox ADֵ */
    uint16_t prox_value;                /**< \brief Prox ֵ */
    int16_t  prox_offset_adjust_value;  /**< \brief Prox У׼ֵ */
} tmd2635_result_info_t;

/**
 * \breif ������ TMD2635 �豸�ṹ�嶨��
 */
typedef struct am_sensor_tmd2635_dev {
    am_sensor_serv_t                    tmd2635_dev;  /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    am_tmd2635_calibration_data_t       cal_val[1];     /*< \brief ����ProxУ׼ֵ */
    void                                *p_arg[1];      /*< \brief �����ص��������� */
    uint8_t                             flags[1];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint8_t                             trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[1];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[1];

    /** \brief �豸��Ϣ */
    const am_sensor_tmd2635_devinfo_t   *dev_info;

} am_sensor_tmd2635_dev_t;

/**
 * \brief ������ TMD2635 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TMD2635�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TMD2635�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tmd2635_init (
        am_sensor_tmd2635_dev_t             *p_dev,
        const am_sensor_tmd2635_devinfo_t   *p_devinfo,
        am_i2c_handle_t                      handle);

/**
 * \brief ������ TMD2635 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tmd2635_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tmd2635_deinit (am_sensor_handle_t   handle);

/**
 * \brief ������ TMD2635 ���ƺ���
 *
 * \param[in] handle    : am_sensor_tmd2635_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *   - AM_SENSOR_TMD2635_FUNC_ENABLE             : ���ù���ʹ�� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_FUNC_DISABLE            : ���ù��ܽ��� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PRATE_SET               : ����PRATE, p_argΪ uint32_t����
 *   - AM_SENSOR_TMD2635_LOW_PROX_THRESHOLD_SET  : ����Prox����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD2635_HIGH_PROX_THRESHOLD_SET : ����Prox����ֵ, p_argΪ uint16_t����
 *   - AM_SENSOR_TMD2635_LOW_PROX_THRESHOLD_GET  : ��ȡProx����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD2635_HIGH_PROX_THRESHOLD_GET : ��ȡProx����ֵ, p_argΪ (uint16_t *)����
 *   - AM_SENSOR_TMD2635_PPERS_SET               : ����PPERS , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PWLONG_SET              : ����PWLONG, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD2635_PGAIN_SET               : ����Prox IR����������, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PPULSE_SET              : ����Prox���������������� , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PPULSE_LEN_SET          : ����PPULSE_LEN , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PLDRIVE_SET             : ����Prox IR VCSEL������������, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_REVID_GET               : ��ȡREVID , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD2635_ID_GET                  : ��ȡID, p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD2635_STATUS_FLAG_CLR         : STATUS�Ĵ���λ���, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_REVID2_GET              : ��ȡREVID2 , p_argΪ (uint8_t *)����
 *   - AM_SENSOR_TMD2635_SOFTRST                 : �����λ , p_argΪ NULL
 *   - AM_SENSOR_TMD2635_PWTIME_SET              : ����PWTIME, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PDSELECT_SET            : ���ù�������, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_APC_SET                 : ����APC, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PMAVG_SET               : ����PMAVG, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_CALAVG_SET              : ����CALAVG, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_PROX_CAL_TYPE_SEL       : ѡ��ProxУ׼����, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_CALPRATE_SET            : ����CALPRATE, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_START_OFFSET_CAL_SET    : ����ƫ��У׼, p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD2635_BINSRCH_TARGET_SET      : ����BINSRCH_TARGET , p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_AUTO_OFFSET_ADJ_SET     : ����AUTO_OFFSET_ADJ , p_argΪ am_bool_t����
 *   - AM_SENSOR_TMD2635_PROX_AVG_SET            : ����PROX_AVG, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_INT_ENABLE              : �ж�ʹ��, p_argΪ uint8_t����
 *   - AM_SENSOR_TMD2635_INT_DISABLE             : �жϽ���, p_argΪ uint8_t����
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_tmd2635_ioctl (am_sensor_handle_t    handle,
                                    int                 cmd,
                                    void               *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TMD2635_H */

/* end of file */


