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
 * \brief ������ AS5600 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_as5600.h"
#include "am_common.h"
#include "zlg237_pin.h"
#include "am_zlg237_inst_init.h"

am_const am_local as5600_param_config_t __g_as5600_param_default = {
        AM_AS5600_WD_OFF,
        AM_AS5600_FTH_6_LSBS,
        AM_AS5600_SF_16,
        AM_AS5600_PWMF_115_HZ,
        AM_AS5600_OUTS_ANALOG_0_TO_100,
        AM_AS5600_HYST_OFF,
        AM_AS5600_PM_NOM,
        AM_AS5600_INCREASE_CLOCKWISE,
        AM_AS5600_OPTION_DISABLE,
        AM_AS5600_OPTION_C,     /* �������� option_enable = AM_AS5600_OPTION_ENABLE ��Ч */
        0xC00,                  /* ���� option = AM_AS5600_OPTION_C ʱ��Ч
                                   ���Ƕȷ�Χ�� 0~360 �ȶ�Ӧ 0~4096
                                   �磬90 �ȶ�Ӧ 1024 (0x400) */
};

/** \brief ������ AS5600 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_as5600_devinfo __g_as5600_info = {
        &__g_as5600_param_default,          /**< \brief ������ʼ�� */
        -1,                                 /**< \brief ����������� */
        PIOA_2,                             /**< \brief OUT���� */
        -1,                                 /**< \brief PGO���� */
        PIOC_7,                             /**< \brief DIR���� */
        0x36,                               /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ AS5600 �豸�ṹ�嶨�� */
am_local struct am_sensor_as5600_dev __g_as5600_dev;

/** \brief ������ AS5600 �豸ʵ���� */
am_sensor_handle_t am_sensor_as5600_inst_init (void)
{
    return am_sensor_as5600_init(&__g_as5600_dev,
                                 &__g_as5600_info,
                                 am_zlg237_i2c2_inst_init());
}

/** \brief ������ AS5600 ʵ�����ʼ�� */
am_err_t am_sensor_as5600_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_as5600_deinit(handle);
}

/* end of file */
