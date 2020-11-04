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
 * \brief ������ FXOS8700CQ �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_fxos8700cq.h"
#include "am_common.h"
#include "zlg116_pin.h"
#include "am_zlg116_inst_init.h"

/** \brief ������ FXOS8700CQ �豸��Ϣʵ�� */
am_const am_local struct am_sensor_fxos8700cq_devinfo __g_fxos8700cq_info = {
    PIOB_0,                                                 /*< \brief �������Ŷ���    */
    0x1E,                                                   /*< \breif FXOS8700CQ I2C��ַ */
    AM_FXOS8700CQ_ODR_HYBRID_MODE_200HZ,                    /* ���� ODR */
    AM_FXOS8700CQ_HYBRID_MODE,                              /* ���ģʽ */
    7,                                                      /* Oversample ratio (OSR) for magnetometer data. range:0~7 */
    AM_FXOS8700CQ_AUTO_CALIBRATION_FEATURE_ENABLED,         /* ��У׼ʹ�� */
    AM_FXOS8700CQ_HYB_AUTOINC_ENABLED,                      /* ʹ�ܻ��ģʽ�µ�ַ��������ȡOUT_Z_LSB(0x06)ֵ���Զ���ת��M_OUT_X_MSB(0x33) */
    AM_FXOS8700CQ_HIGH_RESOLUTION,                          /* �߷ֱ��� */
    AM_FXOS8700CQ_LNOISE_REDUCED_NOISE_MODE,                /* ��������ģʽ */
};

/** \breif ������ FXOS8700CQ �豸�ṹ�嶨�� */
am_local struct am_sensor_fxos8700cq_dev __g_fxos8700cq_dev;

/** \brief ������ FXOS8700CQ �豸ʵ���� */
am_sensor_handle_t am_sensor_fxos8700cq_inst_init (void)
{
    return am_sensor_fxos8700cq_init(&__g_fxos8700cq_dev,
                                  &__g_fxos8700cq_info,
                                  am_zlg116_i2c1_inst_init());
}

/** \brief ������ FXOS8700CQ ʵ�����ʼ�� */
am_err_t am_sensor_fxos8700cq_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_fxos8700cq_deinit(handle);
}

/* end of file */
