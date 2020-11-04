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
 * \brief ������ TSL2560 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tsl2560.h"
#include "am_common.h"
#include "zlg237_pin.h"
#include "am_zlg237_inst_init.h"

am_const am_local tsl2560_param_config_t __g_tsl2560_param_default = {
        AM_TSL2560_AGAIN_LOW_GAIN_MODE,         /* AGAIN */
        AM_TSL2560_ATIME_100MS,                 /* ALS ADC�Ļ���ʱ�� */
        0,                                      /* APERS */
        (AM_TSL2560_AIEN | AM_TSL2560_NPIEN),   /* �ж����ͣ������� am_sensor_trigger_cfg ʱ���ò�����Ч */
        200,    /* ALS ����ֵ�������ж�����ʹ�� AM_TSL2560_AIEN ʱ�ò�����Ч */
        500,    /* ALS ����ֵ�������ж�����ʹ�� AM_TSL2560_AIEN ʱ�ò�����Ч */
        100,    /* ���� ALS ����ֵ�������ж�����ʹ�� AM_TSL2560_NPIEN ʱ�ò�����Ч */
        800,    /* ���� ALS ����ֵ�������ж�����ʹ�� AM_TSL2560_NPIEN ʱ�ò�����Ч */
};

/** \brief ������ TSL2560 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tsl2560_devinfo __g_tsl2560_info = {
        &__g_tsl2560_param_default,             /**< \brief ������ʼ�� */
        PIOA_3,                                 /**< \brief ����������� */
        0x39,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ TSL2560 �豸�ṹ�嶨�� */
am_local struct am_sensor_tsl2560_dev __g_tsl2560_dev;

/** \brief ������ TSL2560 �豸ʵ���� */
am_sensor_handle_t am_sensor_tsl2560_inst_init (void)
{
    return am_sensor_tsl2560_init(&__g_tsl2560_dev,
                                  &__g_tsl2560_info,
                                  am_zlg237_i2c2_inst_init());
}

/** \brief ������ TSL2560 ʵ�����ʼ�� */
am_err_t am_sensor_tsl2560_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tsl2560_deinit(handle);
}

/* end of file */
