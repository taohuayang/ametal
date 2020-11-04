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
 * \brief ����ʱ�䴫���� TMF8801 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-02  YRZ, first implementation.
 * \endinternal
 */

#include "stm32f103rbt6_pin.h"
#include "am_sensor_tmf8801.h"
#include "am_common.h"
#include "am_stm32f103rbt6_inst_init.h"

/** \brief TOF������ TMF8801 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tmf8801_devinfo __g_tmf8801_info = {
        PIOC_11,           /*< \brief ʹ�����Ŷ���    */
        PIOA_5,            /*< \brief �������Ŷ���    */
        0x41               /*< \breif TMF8801 I2C��ַ */
};

/** \breif TOF������ TMF8801 �豸�ṹ�嶨�� */
am_local struct am_sensor_tmf8801_dev __g_tmf8801_dev;

/** \brief TOF������ TMF8801 �豸ʵ���� */
am_sensor_handle_t am_sensor_tmf8801_inst_init (void)
{
    return am_sensor_tmf8801_init(&__g_tmf8801_dev,
                                  &__g_tmf8801_info,
                                   am_stm32f103rbt6_i2c2_inst_init());
}

/** \brief TOF������ TMF8801 ʵ�����ʼ�� */
am_err_t am_sensor_tmf8801_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tmf8801_deinit(handle);
}

/* end of file */
