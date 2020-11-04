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
 * \brief ������ AS621X �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-21  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_as621x.h"
#include "am_common.h"
#include "stm32f103rbt6_pin.h"
#include "am_stm32f103rbt6_inst_init.h"

am_const am_local as621x_param_config_t __g_as621x_param_default = {
        AM_AS621X_CONVERSION_RATE_1HZ,          /* ת������ */
        AM_AS621X_SLEEP_MODE,                   /* ˯��ģʽ��ps:�ж�ģʽ�¸�λ��Ч��ǿ������Ϊ����ת��ģʽ */
        AM_FALSE,                               /* ��������:�͵�ƽ���� */
        AM_AS621X_CONSECUTIVE_FAULTS_1,         /* ���������� */
        20.5,                                   /* ���¶���ֵ */
        40.5,                                   /* ���¶���ֵ */
};

/*  ALERT/ADD1 Connection           ADD0            Alert Functionality Enabled             Device Address
 *      SCL                         VSS                     NO                                  0x44
 *      SCL                         VDD                     NO                                  0x45
 *      SCL                         SDA                     NO                                  0x46
 *      SCL                         SCL                     NO                                  0x47
 *
 *      VSS                         VSS                     NO                                  0x48
 *      VSS                         VDD                     NO                                  0x49
 *      VSS                         SDA                     NO                                  0x4A
 *      VSS                         SCL                     NO                                  0x4B
 *
 *      VDD                         VSS                     YES                                 0x48    (��ǰʹ��)
 *      VDD                         VDD                     YES                                 0x49
 *      VDD                         SDA                     YES                                 0x4A
 *      VDD                         SCL                     YES                                 0x4B
 */

/** \brief ������ AS621X �豸��Ϣʵ�� */
am_const am_local struct am_sensor_as621x_devinfo __g_as621x_info = {
        &__g_as621x_param_default,              /**< \brief ������ʼ�� */
        PIOA_4,                                 /**< \brief ����������� */
        0x48,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ AS621X �豸�ṹ�嶨�� */
am_local struct am_sensor_as621x_dev __g_as621x_dev;

/** \brief ������ AS621X �豸ʵ���� */
am_sensor_handle_t am_sensor_as621x_inst_init (void)
{
    return am_sensor_as621x_init(&__g_as621x_dev,
                                 &__g_as621x_info,
                                 am_stm32f103rbt6_i2c2_inst_init());
}

/** \brief ������ AS621X ʵ�����ʼ�� */
am_err_t am_sensor_as621x_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_as621x_deinit(handle);
}

/* end of file */
