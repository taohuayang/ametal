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
 * \brief ������ LIS3MDL �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-22  yrz, first implementation.
 * \endinternal
 */

#include <am_aml165_inst_init.h>
#include "am_sensor_lis3mdl.h"
#include "am_common.h"
#include "zml165_pin.h"

/** \brief ������ LIS3MDL �豸��Ϣʵ�� */
am_const am_local struct am_sensor_lis3mdl_devinfo __g_lis3mdl_info = {
    PIOB_0,            /*< \brief �������Ŷ���    */
    0x1C               /*< \breif LIS3MDL I2C��ַ */
};

/** \breif ������ LIS3MDL �豸�ṹ�嶨�� */
am_local struct am_sensor_lis3mdl_dev __g_lis3mdl_dev;

/** \brief ������ LIS3MDL �豸ʵ���� */
am_sensor_handle_t am_sensor_lis3mdl_inst_init (void)
{
    return am_sensor_lis3mdl_init(&__g_lis3mdl_dev,
                                  &__g_lis3mdl_info,
                                  am_zml165_i2c1_inst_init());
}

/** \brief ������ LIS3MDL ʵ�����ʼ�� */
am_err_t am_sensor_lis3mdl_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_lis3mdl_deinit(handle);
}

/* end of file */
