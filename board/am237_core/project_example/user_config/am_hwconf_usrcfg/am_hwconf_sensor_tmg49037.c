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
 * \brief ������ TMG49037 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tmg49037.h"
#include "am_common.h"
#include "zlg237_pin.h"
#include "am_zlg237_inst_init.h"

am_const am_local tmg49037_param_config_t __g_tmg49037_param_default = {
        AM_TMG49037_ATIME_2_78MS,                   /* ALS ADC�Ļ���ʱ�� */
        AM_TMG49037_PTIME_2_78MS,                   /* Prox����ʱ�� */
        AM_TMG49037_WTIME_2_78MS_OR_0_03S,          /* ALS��Prox֮��ĵȴ�ʱ�� */
        0,                                          /* Prox�жϹ����� */
        0,                                          /* ALS�жϹ����� */
        AM_TMG49037_LOWPOWER_IDLE_ENABLE,           /* �͹��Ŀ��� */
        AM_FALSE,                                   /* WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
        AM_TMG49037_PULSE_LEN_8US,                  /* Prox���峤�� */
        16,                                         /* һ��Prox���ڵ���������� */
        AM_TMG49037_PGGAIN_4,                       /* Prox IR���������� */
        AM_TMG49037_PGLDRIVE_10MA,                  /* Prox IR VCSEL���� */
        AM_TMG49037_AGAIN_1,                        /* ALS/Color���������� */
        0,                                          /* LTF_USEPROX */
        AM_FALSE,                                   /* SAI */

        0x00,                                       /* CFG4λ��λ */

        (AM_TMG49037_ALS_INT_DIRECT       | \
         AM_TMG49037_ALS_INT_DIRECT_GPIO  | \
         AM_TMG49037_PROX_INT_DIRECT      | \
         AM_TMG49037_PROX_INT_DIRECT_GPIO ),        /* CFG4λ��� */

        (AM_TMG49037_DISABLE_IR_CORRECTION  | \
         AM_TMG49037_PROX_FILTER_DOWNSAMPLE | \
         AM_TMG49037_PROX_FILTER ),                 /* CFG5λ��λ */

        (AM_TMG49037_LONG_LTFSTOP_DISCARD_ALS | \
         AM_TMG49037_PROX_FILTER_SIZE ),            /* CFG5λ��� */

        0x00,                                       /* GTHR_MASK */
        AM_TMG49037_GTHR_OUT_NR_1,                  /* GTHR_OUT_NR */
        AM_TMG49037_GFIFOTHR_8,                     /* GFIFOTHR */
        16,                                         /* GPULSE */
        AM_TMG49037_GEST_FILTER_SIZE_2,             /* GEST_FILTER_SIZE */
        AM_TMG49037_GEST_FILTER_ENABLE,             /* GEST_FILTER */
        AM_TMG49037_GTIME_968US,                    /* GTIME */
        0xFF,                                       /* AZ_NTH_ITERATION */
        AM_TRUE,                                    /* DCAVG_AUTO_OFFSET_ADJUST */
        AM_TMG49037_ELECTRICAL_OPTICAL_CROSSTALK,   /* ProxУ׼���� */
        AM_TMG49037_BINSRCH_SKIP_DISABLE,           /* BINSRCH_SKIP */
        AM_TMG49037_DCAVG_ITERATIONS_16,            /* DCAVG_ITERATIONS */
        0,                                          /* PXDCAVG_AUTO_GTHR */
        0,                                          /* PROX_AUTO_OFFSET_ADJUST */
        1,                                          /* PXDCAVG_AUTO_BASELINE */
        AM_TMG49037_PXDCAVG_BASELINE_WINDOW_16,     /* PXDCAVG_BASELINE_WINDOW */
        0,                                          /* DCAVG_AUTO_GTHR */
        AM_TMG49037_BINSRCH_TARGET_3,               /* BINSRCH_TARGET */
        AM_TMG49037_AUTO_GTHR_IN_MULT_1_00,         /* AUTO_GTHR_IN_MULT */
        0,                                          /* ZERO_WEIGHT */
};

/** \brief ������ TMG49037 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tmg49037_devinfo __g_tmg49037_info = {
        &__g_tmg49037_param_default,            /**< \brief ������ʼ�� */
        PIOC_3,                                 /**< \brief ����������� */
        0x29,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ TMG49037 �豸�ṹ�嶨�� */
am_local struct am_sensor_tmg49037_dev __g_tmg49037_dev;

/** \brief ������ TMG49037 �豸ʵ���� */
am_sensor_handle_t am_sensor_tmg49037_inst_init (void)
{
    return am_sensor_tmg49037_init(&__g_tmg49037_dev,
                                   &__g_tmg49037_info,
                                   am_zlg237_i2c1_inst_init());
}

/** \brief ������ TMG49037 ʵ�����ʼ�� */
am_err_t am_sensor_tmg49037_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tmg49037_deinit(handle);
}

/* end of file */
