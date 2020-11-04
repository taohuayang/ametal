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
 * \brief ������ MAG3110 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-03  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_mag3110.h"
#include "am_common.h"
#include "zlg116_pin.h"
#include "am_zlg116_inst_init.h"

/** \brief ������ MAG3110 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_mag3110_devinfo __g_mag3110_info = {
    PIOB_0,            /*< \brief �������Ŷ���    */
    0x0E               /*< \breif MAG3110 I2C��ַ */
};

/** \breif ������ MAG3110 �豸�ṹ�嶨�� */
am_local struct am_sensor_mag3110_dev __g_mag3110_dev;

/** \brief ������ MAG3110 �豸ʵ���� */
am_sensor_handle_t am_sensor_mag3110_inst_init (void)
{
    return am_sensor_mag3110_init(&__g_mag3110_dev,
                                  &__g_mag3110_info,
                                  am_zlg116_i2c1_inst_init());
}

/** \brief ������ MAG3110 ʵ�����ʼ�� */
am_err_t am_sensor_mag3110_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_mag3110_deinit(handle);
}

/* end of file */
