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
 * \brief ������ HTS221 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-26  wan, first implementation.
 * \endinternal
 */

#include "hc32x3x_pin.h"
#include "am_sensor_hts221.h"
#include "am_common.h"
#include "am_hc32f03x_inst_init.h"

/** \brief ������ HTS221 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_hts221_devinfo __g_hts221_info = {
        PIOB_0,            /*< \brief �������Ŷ���   */
        0x5f               /*< \breif HTS221 I2C��ַ */
};

/** \breif ������ HTS221 �豸�ṹ�嶨�� */
am_local struct am_sensor_hts221_dev __g_hts221_dev;

/** \brief ������ HTS221 �豸ʵ���� */
am_sensor_handle_t am_sensor_hts221_inst_init (void)
{
    return am_sensor_hts221_init(&__g_hts221_dev,
                                 &__g_hts221_info,
                                 am_hc32_i2c1_inst_init());
}

/** \brief ������ HTS221 ʵ�����ʼ�� */
am_err_t am_sensor_hts221_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_hts221_deinit(handle);
}

/* end of file */
