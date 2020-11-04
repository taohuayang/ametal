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
 * \brief ������/��ɫ���ӽ�/���ƴ����� TMG49037 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_TMG49037_H
#define __AM_SENSOR_TMG49037_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������ TMG49037 ʹ������
 */
#define AM_TMG49037_GEN                             (1u << 6)
#define AM_TMG49037_WEN                             (1u << 3)
#define AM_TMG49037_PEN                             (1u << 2)
#define AM_TMG49037_AEN                             (1u << 1)
#define AM_TMG49037_PON                             (1u << 0)

/**
 * \brief ������ TMG49037 ALS ADC�Ļ���ʱ��
    ����ʱ��(��λ:ms) = 2.78ms * (256 - ATIME)
 */
#define AM_TMG49037_ATIME_2_78MS                    (0xFF)
#define AM_TMG49037_ATIME_27_8MS                    (0xF6)
#define AM_TMG49037_ATIME_100MS                     (0xDC)
#define AM_TMG49037_ATIME_178MS                     (0xC0)
#define AM_TMG49037_ATIME_711MS                     (0x00)

/**
 * \brief ������ TMG49037 Prox����ʱ��
    Prox����ʱ��(��λ:ms) = 2.78ms * (PTIME + 1)
 */
#define AM_TMG49037_PTIME_2_78MS                    (0x00)
#define AM_TMG49037_PTIME_5_56MS                    (0x01)
#define AM_TMG49037_PTIME_11_1MS                    (0x03)
#define AM_TMG49037_PTIME_100MS                     (0x23)
#define AM_TMG49037_PTIME_711MS                     (0xFF)

/**
 * \brief ������ TMG49037 ALS�ȴ�ʱ��
    �ȴ�ʱ��(��λ:ms) ---- (WLONG = 0) : 2.78ms * (256 - WTIME)
                      ---- (WLONG = 1) : 33.3ms * (256 - WTIME)
 */
#define AM_TMG49037_WTIME_2_78MS_OR_0_03S           (0xFF)
#define AM_TMG49037_WTIME_100MS_OR_1_2S             (0xDC)
#define AM_TMG49037_WTIME_417MS_OR_5S               (0x6A)
#define AM_TMG49037_WTIME_711MS_OR_8_53S            (0x00)

/**
 * \brief ������ TMG49037 �͹��Ŀ���
 */
#define AM_TMG49037_LOWPOWER_IDLE_DISABLE           (0x00)
#define AM_TMG49037_LOWPOWER_IDLE_ENABLE            (0x01)

/**
 * \brief ������ TMG49037 Prox���峤��
 */
#define AM_TMG49037_PULSE_LEN_4US                   (0x00)
#define AM_TMG49037_PULSE_LEN_8US                   (0x01)
#define AM_TMG49037_PULSE_LEN_16US                  (0x02)
#define AM_TMG49037_PULSE_LEN_32US                  (0x03)

/**
 * \brief ������ TMG49037 Prox IR����������
 */
#define AM_TMG49037_PGGAIN_1                        (0x00)
#define AM_TMG49037_PGGAIN_2                        (0x01)
#define AM_TMG49037_PGGAIN_4                        (0x02)
#define AM_TMG49037_PGGAIN_8                        (0x03)

/**
 * \brief ������ TMG49037 Prox IR VCSEL����������������
    ��������(��λ:mA) = 10mA + (20mA * PGLDRIVE)
 */
#define AM_TMG49037_PGLDRIVE_10MA                   (0x00)
#define AM_TMG49037_PGLDRIVE_30MA                   (0x01)
#define AM_TMG49037_PGLDRIVE_50MA                   (0x02)
#define AM_TMG49037_PGLDRIVE_290MA                  (0x0E)
#define AM_TMG49037_PGLDRIVE_310MA                  (0x0F)

/**
 * \brief ������ TMG49037 ALS/Color����������
 */
#define AM_TMG49037_AGAIN_1                         (0x00)
#define AM_TMG49037_AGAIN_4                         (0x01)
#define AM_TMG49037_AGAIN_16                        (0x02)
#define AM_TMG49037_AGAIN_64                        (0x03)

/**
 * \brief ������ TMG49037 STATUSλ
 */
#define AM_TMG49037_STATUS_ASAT                     (1u << 7)
#define AM_TMG49037_STATUS_PGSAT                    (1u << 6)
#define AM_TMG49037_STATUS_PINT                     (1u << 5)
#define AM_TMG49037_STATUS_AINT                     (1u << 4)
#define AM_TMG49037_STATUS_GINT                     (1u << 2)
#define AM_TMG49037_STATUS_CINT                     (1u << 1)

/**
 * \brief ������ TMG49037 STATUS2λ
 */
#define AM_TMG49037_STATUS2_PVALID                  (1u << 7)
#define AM_TMG49037_STATUS2_AVALID                  (1u << 6)
#define AM_TMG49037_STATUS2_ASAT_DIGITAL            (1u << 4)
#define AM_TMG49037_STATUS2_ASAT_ANALOG             (1u << 3)
#define AM_TMG49037_STATUS2_PGSAT_ADC               (1u << 2)
#define AM_TMG49037_STATUS2_PGSAT_REFLECTIVE        (1u << 1)
#define AM_TMG49037_STATUS2_PGSAT_AMBIENT           (1u << 0)

/**
 * \brief ������ TMG49037 �����������
    д 1 ����x�����������
 */
#define AM_TMG49037_PMASK_E                         (1u << 7)
#define AM_TMG49037_PMASK_W                         (1u << 6)
#define AM_TMG49037_PMASK_S                         (1u << 5)
#define AM_TMG49037_PMASK_N                         (1u << 4)
#define AM_TMG49037_AMASK                           (1u << 3)   /* ALS Mask */

/**
 * \brief ������ TMG49037 CFG4λ
 */
#define AM_TMG49037_ALS_INT_DIRECT                  (1u << 7)
#define AM_TMG49037_ALS_INT_DIRECT_GPIO             (1u << 6)
#define AM_TMG49037_PROX_INT_DIRECT                 (1u << 5)
#define AM_TMG49037_PROX_INT_DIRECT_GPIO            (1u << 4)

/**
 * \brief ������ TMG49037 CFG5λ
 */
#define AM_TMG49037_LONG_LTFSTOP_DISCARD_ALS        (1u << 5)
#define AM_TMG49037_DISABLE_IR_CORRECTION           (1u << 3)
#define AM_TMG49037_PROX_FILTER_DOWNSAMPLE          (1u << 2)
#define AM_TMG49037_PROX_FILTER_SIZE                (1u << 1)
#define AM_TMG49037_PROX_FILTER                     (1u << 0)

/**
 * \brief ������ TMG49037 �����˳�����
 */
#define AM_TMG49037_GTHR_MASK_E                     (1u << 5)
#define AM_TMG49037_GTHR_MASK_W                     (1u << 4)
#define AM_TMG49037_GTHR_MASK_S                     (1u << 3)
#define AM_TMG49037_GTHR_MASK_N                     (1u << 2)

/**
 * \brief ������ TMG49037 �����˳�����������
 */
#define AM_TMG49037_GTHR_OUT_NR_1                   (0x00)
#define AM_TMG49037_GTHR_OUT_NR_2                   (0x01)
#define AM_TMG49037_GTHR_OUT_NR_4                   (0x02)
#define AM_TMG49037_GTHR_OUT_NR_8                   (0x03)

/**
 * \brief ������ TMG49037 ��������FIFO����NSWE���ݼ�������
 */
#define AM_TMG49037_GFIFOTHR_1                      (0x00)
#define AM_TMG49037_GFIFOTHR_4                      (0x01)
#define AM_TMG49037_GFIFOTHR_8                      (0x02)
#define AM_TMG49037_GFIFOTHR_16                     (0x03)

/**
 * \brief ������ TMG49037 ���ƹ�����������
 */
#define AM_TMG49037_GEST_FILTER_SIZE_2              (0x00)
#define AM_TMG49037_GEST_FILTER_SIZE_4              (0x01)

/**
 * \brief ������ TMG49037 ���ƹ����� ʹ��/����
 */
#define AM_TMG49037_GEST_FILTER_DISABLE             (0x00)
#define AM_TMG49037_GEST_FILTER_ENABLE              (0x01)


/**
 * \brief ������ TMG49037 ���Ʋ���ʱ��
    ����ʱ��(��λ:us) = 88us * (GTIME + 1)
 */
#define AM_TMG49037_GTIME_88US                      (0x00)
#define AM_TMG49037_GTIME_176US                     (0x01)
#define AM_TMG49037_GTIME_968US                     (0x0A)
#define AM_TMG49037_GTIME_9_9MS                     (0x70)
#define AM_TMG49037_GTIME_22_5MS                    (0xFF)

/**
 * \brief ������ TMG49037 ����/�˳� ����ģʽ
 */
#define AM_TMG49037_EXIT_GESTURE_MODE               (0x00)
#define AM_TMG49037_ENTER_GESTURE_MODE              (0x01)


/**
 * \brief ������ TMG49037 ProxУ׼����ѡ��
 */
#define AM_TMG49037_ELECTRICAL_OPTICAL_CROSSTALK    (0x00)
#define AM_TMG49037_ELECTRICAL_CROSSTALK_ONLY       (0x01)

/**
 * \brief ������ TMG49037 У׼��/��������������������
 */
#define AM_TMG49037_BINSRCH_SKIP_DISABLE            (0x00)
#define AM_TMG49037_BINSRCH_SKIP_ENABLE             (0x01)

/**
 * \brief ������ TMG49037 DCAVG_ITERATIONS
 */
#define AM_TMG49037_DCAVG_ITERATIONS_SKIP           (0x00)
#define AM_TMG49037_DCAVG_ITERATIONS_2              (0x01)
#define AM_TMG49037_DCAVG_ITERATIONS_4              (0x02)
#define AM_TMG49037_DCAVG_ITERATIONS_8              (0x03)
#define AM_TMG49037_DCAVG_ITERATIONS_16             (0x04)
#define AM_TMG49037_DCAVG_ITERATIONS_32             (0x05)
#define AM_TMG49037_DCAVG_ITERATIONS_64             (0x06)
#define AM_TMG49037_DCAVG_ITERATIONS_128            (0x07)

/**
 * \brief ������ TMG49037 PXDCAVG_BASELINE_WINDOW
 */
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_SKIP    (0x00)
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_2       (0x01)
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_4       (0x02)
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_8       (0x03)
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_16      (0x04)
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_32      (0x05)
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_64      (0x06)
#define AM_TMG49037_PXDCAVG_BASELINE_WINDOW_128     (0x07)

/**
 * \brief ������ TMG49037 ����������Ŀ��
 */
#define AM_TMG49037_BINSRCH_TARGET_0                (0x00)
#define AM_TMG49037_BINSRCH_TARGET_1                (0x01)
#define AM_TMG49037_BINSRCH_TARGET_3                (0x02)
#define AM_TMG49037_BINSRCH_TARGET_7                (0x03)
#define AM_TMG49037_BINSRCH_TARGET_15               (0x04)
#define AM_TMG49037_BINSRCH_TARGET_31               (0x05)
#define AM_TMG49037_BINSRCH_TARGET_63               (0x06)
#define AM_TMG49037_BINSRCH_TARGET_127              (0x07)

/**
 * \brief ������ TMG49037 AUTO_GTHR_IN_MULT
    factor = (AUTO_GTHR_IN_MULT + 4) / 4
 */
#define AM_TMG49037_AUTO_GTHR_IN_MULT_1_00          (0x00)
#define AM_TMG49037_AUTO_GTHR_IN_MULT_1_25          (0x01)
#define AM_TMG49037_AUTO_GTHR_IN_MULT_1_50          (0x02)
#define AM_TMG49037_AUTO_GTHR_IN_MULT_4_50          (0x0E)
#define AM_TMG49037_AUTO_GTHR_IN_MULT_4_75          (0x0F)

/**
 * \brief ������ TMG49037 �ж�ʹ��
 */
#define AM_TMG49037_ASIEN                           (1u << 7)
#define AM_TMG49037_PGSIEN                          (1u << 6)
#define AM_TMG49037_PIEN                            (1u << 5)
#define AM_TMG49037_AIEN                            (1u << 4)
#define AM_TMG49037_GIEN                            (1u << 2)
#define AM_TMG49037_CIEN                            (1u << 1)

/**
 * \brief ������ TMG49037 �ж����
 */
#define AM_TMG49037_INTCLEAR_ASAT                   (1u << 7)
#define AM_TMG49037_INTCLEAR_PGSAT                  (1u << 6)
#define AM_TMG49037_INTCLEAR_PINT                   (1u << 5)
#define AM_TMG49037_INTCLEAR_AINT                   (1u << 4)
#define AM_TMG49037_INTCLEAR_GINT                   (1u << 2)
#define AM_TMG49037_INTCLEAR_CINT                   (1u << 1)

/**
 * \brief ������ TMG49037 ����ָ���
 */
typedef enum am_sensor_tmg49037_control_cmd {
    AM_SENSOR_TMG49037_FUNC_ENABLE = 1,
    AM_SENSOR_TMG49037_FUNC_DISABLE,
    AM_SENSOR_TMG49037_ATIME_SET,
    AM_SENSOR_TMG49037_PTIME_SET,
    AM_SENSOR_TMG49037_WTIME_SET,
    AM_SENSOR_TMG49037_LOW_ALS_THRESHOLD_SET,
    AM_SENSOR_TMG49037_HIGH_ALS_THRESHOLD_SET,
    AM_SENSOR_TMG49037_LOW_PROX_THRESHOLD_SET,
    AM_SENSOR_TMG49037_HIGH_PROX_THRESHOLD_SET,
    AM_SENSOR_TMG49037_LOW_ALS_THRESHOLD_GET,
    AM_SENSOR_TMG49037_HIGH_ALS_THRESHOLD_GET,
    AM_SENSOR_TMG49037_LOW_PROX_THRESHOLD_GET,
    AM_SENSOR_TMG49037_HIGH_PROX_THRESHOLD_GET,
    AM_SENSOR_TMG49037_PPERS_SET,
    AM_SENSOR_TMG49037_APERS_SET,
    AM_SENSOR_TMG49037_LOWPOWER_IDLE_SET,
    AM_SENSOR_TMG49037_WLONG_SET,
    AM_SENSOR_TMG49037_PGPULSE_LEN_SET,
    AM_SENSOR_TMG49037_PPULSE_SET,
    AM_SENSOR_TMG49037_PGGAIN_SET,
    AM_SENSOR_TMG49037_PGLDRIVE_SET,
    AM_SENSOR_TMG49037_AGAIN_SET,
    AM_SENSOR_TMG49037_REVID_GET,
    AM_SENSOR_TMG49037_ID_GET,
    AM_SENSOR_TMG49037_CFG2_ENABLE,
    AM_SENSOR_TMG49037_CFG2_DISABLE,
    AM_SENSOR_TMG49037_LTF_USEPROX_SET,
    AM_SENSOR_TMG49037_SAI_SET,
    AM_SENSOR_TMG49037_CFG4_SET_BIT,
    AM_SENSOR_TMG49037_CFG4_RESET_BIT,
    AM_SENSOR_TMG49037_CFG5_SET_BIT,
    AM_SENSOR_TMG49037_CFG5_RESET_BIT,
    AM_SENSOR_TMG49037_GTHR_MASK_SET,
    AM_SENSOR_TMG49037_GTHR_OUT_NR_SET,
    AM_SENSOR_TMG49037_GFIFOTHR_SET,
    AM_SENSOR_TMG49037_GPULSE_SET,
    AM_SENSOR_TMG49037_GEST_FILTER_SIZE_SET,
    AM_SENSOR_TMG49037_GEST_FILTER_SET,
    AM_SENSOR_TMG49037_GTIME_SET,
    AM_SENSOR_TMG49037_GMODE_SET,
    AM_SENSOR_TMG49037_GESTURE_ENTRY_THRESHOLD_SET,
    AM_SENSOR_TMG49037_GESTURE_EXIT_THRESHOLD_SET,
    AM_SENSOR_TMG49037_SAI_ACTIVE_CLEAR,
    AM_SENSOR_TMG49037_AUXID_GET,
    AM_SENSOR_TMG49037_AZ_NTH_ITERATION_SET,
    AM_SENSOR_TMG49037_START_OFFSET_CAL_SET,
    AM_SENSOR_TMG49037_DCAVG_AUTO_OFFSET_ADJUST_SET,
    AM_SENSOR_TMG49037_PROX_CAL_TYPE_SEL,
    AM_SENSOR_TMG49037_BINSRCH_SKIP_SET,
    AM_SENSOR_TMG49037_DCAVG_ITERATIONS_SET,
    AM_SENSOR_TMG49037_PXDCAVG_AUTO_GTHR_SET,
    AM_SENSOR_TMG49037_PROX_AUTO_OFFSET_ADJUST_SET,
    AM_SENSOR_TMG49037_PXDCAVG_AUTO_BASELINE_SET,
    AM_SENSOR_TMG49037_PXDCAVG_BASELINE_WINDOW_SET,
    AM_SENSOR_TMG49037_DCAVG_AUTO_GTHR_SET,
    AM_SENSOR_TMG49037_BINSRCH_TARGET_SET,
    AM_SENSOR_TMG49037_AUTO_GTHR_IN_MULT_SET,
    AM_SENSOR_TMG49037_ZERO_WEIGHT_SET,
    AM_SENSOR_TMG49037_INT_ENABLE,
    AM_SENSOR_TMG49037_INT_DISABLE,
    AM_SENSOR_TMG49037_INT_CLEAR,
} am_sensor_tmg49037_control_cmd_t;

/*
 * \brief ������TMG49037�ṩ������ͨ��ID����
 */
#define AM_TMG49037_CHAN_1      0              /* TMG49037 ��ͨ��1��Prox */
#define AM_TMG49037_CHAN_2      1              /* TMG49037 ��ͨ��2��ALS */
#define AM_TMG49037_CHAN_3      2              /* TMG49037 ��ͨ��3��GESTURE */

/**
 * \brief TMG49037�������ó�ʼ���ṹ�嶨�� 
 */
typedef struct tmg49037_param_config
{
    uint8_t     atime_val;                  /**< \brief ALS ADC�Ļ���ʱ�� */
    uint8_t     ptime_val;                  /**< \brief Prox����ʱ�� */
    uint8_t     wtime_val;                  /**< \brief ALS��Prox֮��ĵȴ�ʱ�� */
    uint8_t     ppers_val;                  /**< \brief Prox�жϹ����� */
    uint8_t     apers_val;                  /**< \brief ALS�жϹ����� */
    uint8_t     lowpower_idle;              /**< \brief �͹��Ŀ��� */
    am_bool_t   wlong_en;                   /**< \brief WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
    uint8_t     pgpulse_len;                /**< \brief Prox���峤�� */
    uint8_t     pulse;                      /**< \brief һ��Prox���ڵ���������� */
    uint8_t     pggain_val;                 /**< \brief Prox IR���������� */
    uint8_t     pgldrive_val;               /**< \brief Prox IR VCSEL���� */
    uint8_t     again_val;                  /**< \brief ALS/Color���������� */
    uint8_t     ltf_useprox;                /**< \brief LTF_USEPROX */
    am_bool_t   sleep_after_interrupt;      /**< \brief SAI */
    uint8_t     cfg4_set_bit;               /**< \brief CFG4λ��λ */
    uint8_t     cfg4_reset_bit;             /**< \brief CFG4λ��� */
    uint8_t     cfg5_set_bit;               /**< \brief CFG5λ��λ */
    uint8_t     cfg5_reset_bit;             /**< \brief CFG5λ��� */
    uint8_t     gthr_mask;                  /**< \brief GTHR_MASK */
    uint8_t     gthr_out_nr;                /**< \brief GTHR_OUT_NR */
    uint8_t     gfifothr;                   /**< \brief GFIFOTHR */
    uint8_t     gpulse;                     /**< \brief GPULSE */
    uint8_t     gest_filter_size;           /**< \brief GEST_FILTER_SIZE */
    uint8_t     gest_filter;                /**< \brief GEST_FILTER */
    uint8_t     gtime_val;                  /**< \brief GTIME */
    uint8_t     az_nth_iteration;           /**< \brief AZ_NTH_ITERATION */
    am_bool_t   dcavg_auto_offset_adjust;   /**< \brief DCAVG_AUTO_OFFSET_ADJUST */
    uint8_t     prox_cal_type;              /**< \brief ProxУ׼���� */
    uint8_t     binsrch_skip;               /**< \brief BINSRCH_SKIP */
    uint8_t     dcavg_iterations;           /**< \brief DCAVG_ITERATIONS */
    uint8_t     pxdcavg_auto_gthr;          /**< \brief PXDCAVG_AUTO_GTHR */
    uint8_t     prox_auto_offset_adjust;    /**< \brief PROX_AUTO_OFFSET_ADJUST */
    uint8_t     pxdcavg_auto_baseline;      /**< \brief PXDCAVG_AUTO_BASELINE */
    uint8_t     pxdcavg_baseline_window;    /**< \brief PXDCAVG_BASELINE_WINDOW */
    uint8_t     dcavg_auto_gthr;            /**< \brief DCAVG_AUTO_GTHR */
    uint8_t     binsrch_target;             /**< \brief BINSRCH_TARGET */
    uint8_t     auto_gthr_in_mult;          /**< \brief AUTO_GTHR_IN_MULT */
    uint8_t     zero_weight;                /**< \brief ZERO_WEIGHT */
} tmg49037_param_config_t;

/**
 * \brief ������ TMG49037 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_tmg49037_devinfo {

    const   tmg49037_param_config_t     *p_param_default;   /**< \brief ������ʼ�� */

    int                                  trigger_pin;       /**< \brief ����������� */

    uint8_t                              i2c_addr;          /**< \brief I2C 7λ �豸��ַ */

} am_sensor_tmg49037_devinfo_t;

/**
 * \brief TMG49037 ProxУ׼ֵ����
 */
typedef struct am_tmg49037_calibration_data {
    int16_t offset_n;
    int16_t offset_s;
    int16_t offset_w;
    int16_t offset_e;
} am_tmg49037_calibration_data_t;

/**
 * \brief TMG49037 ����ṹ�嶨��
 */
typedef struct tmg49037_result_info
{
    uint16_t clear_channel_data;        /**< \brief clear */
    uint16_t red_channel_data;          /**< \brief red */
    uint16_t green_channel_data;        /**< \brief green */
    uint16_t blue_channel_data;         /**< \brief blue */
    uint16_t raw_prox_value;            /**< \brief Prox ADֵ */
    uint16_t raw_gfifo_n;               /**< \brief GFIFON ADֵ */
    uint16_t raw_gfifo_s;               /**< \brief GFIFOS ADֵ */
    uint16_t raw_gfifo_w;               /**< \brief GFIFOW ADֵ */
    uint16_t raw_gfifo_e;               /**< \brief GFIFOE ADֵ */
    int16_t  prox_offset_adjust_value;  /**< \brief ProxУ׼ֵ */
    int16_t  offset_n_adjust_value;     /**< \brief OFFSETN У׼ֵ */
    int16_t  offset_s_adjust_value;     /**< \brief OFFSETS У׼ֵ */
    int16_t  offset_w_adjust_value;     /**< \brief OFFSETW У׼ֵ */
    int16_t  offset_e_adjust_value;     /**< \brief OFFSETE У׼ֵ */
    uint16_t prox_value;                /**< \brief Proxֵ */
    uint16_t gfifo_n;                   /**< \brief GFIFON ֵ */
    uint16_t gfifo_s;                   /**< \brief GFIFOS ֵ */
    uint16_t gfifo_w;                   /**< \brief GFIFOW ֵ */
    uint16_t gfifo_e;                   /**< \brief GFIFOE ֵ */
} tmg49037_result_info_t;

/**
 * \breif ������ TMG49037 �豸�ṹ�嶨��
 */
typedef struct am_sensor_tmg49037_dev {
    am_sensor_serv_t                    tmg49037_dev;   /*< \breif ��������׼���� */
    am_i2c_device_t                     i2c_dev;        /*< \brief i2c�豸ʵ�� */
    am_tmg49037_calibration_data_t      cal_val[1];     /*< \brief ����ProxУ׼ֵ */
    void                                *p_arg[3];      /*< \brief �����ص��������� */
    uint8_t                             flags[3];       /*< \brief ������־λ */
    am_isr_defer_job_t                  g_myjob;        /*< \brief �ж���ʱ�������� */
    uint8_t                             trigger;        /*< \brief ��¼��־λ */
    am_sensor_val_t                     data[9];        /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t              pfn_trigger_cb[3];

    /** \brief �豸��Ϣ */
    const am_sensor_tmg49037_devinfo_t *dev_info;

} am_sensor_tmg49037_dev_t;

/**
 * \brief ������ TMG49037 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���TMG49037�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���TMG49037�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_tmg49037_init (
        am_sensor_tmg49037_dev_t            *p_dev,
        const am_sensor_tmg49037_devinfo_t  *p_devinfo,
        am_i2c_handle_t                      handle);

/**
 * \brief ������ TMG49037 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_tmg49037_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_tmg49037_deinit (am_sensor_handle_t handle);

/**
 * \brief ������ TMG49037 ���ƺ���
 *
 * \param[in] handle    : am_sensor_tmg49037_init()��ʼ��������õĴ�������׼������
 * \param[in] cmd       : ����ָ��
 *
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_err_t am_sensor_tmg49037_ioctl (am_sensor_handle_t    handle,
                                   int                   cmd,
                                   void                 *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_TMG49037_H */

/* end of file */

