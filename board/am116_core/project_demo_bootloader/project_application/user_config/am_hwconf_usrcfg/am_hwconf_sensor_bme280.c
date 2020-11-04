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
 * \brief ������ bme280 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-30  yrz, first implementation.
 * \endinternal
 */

#include "am_sensor_bme280.h"
#include "am_common.h"
#include "zlg116_pin.h"
#include "am_zlg116_inst_init.h"

/** \brief ������ bme280 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_bme280_devinfo __g_bme280_info = {
        0x76               /*< \breif bme280 I2C��ַ */
};

/** \breif ������ bme280 �豸�ṹ�嶨�� */
am_local struct am_sensor_bme280_dev __g_bme280_dev;

/** \brief ������ bme280 �豸ʵ���� */
am_sensor_handle_t am_sensor_bme280_inst_init (void)
{
    return am_sensor_bme280_init(&__g_bme280_dev,
                                 &__g_bme280_info,
                                 am_zlg116_i2c1_inst_init());
}

/** \brief ������ bme280 ʵ�����ʼ�� */
am_err_t am_sensor_bme280_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_bme280_deinit(handle);
}

/* end of file */
