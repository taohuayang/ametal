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
 * \brief ������ TSL2540 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tsl2540.h"
#include "am_common.h"
#include "zlg237_pin.h"
#include "am_zlg237_inst_init.h"

am_const am_local tsl2540_param_config_t __g_tsl2540_param_default = {
        AM_TSL2540_ATIME_2_8MS,                 /* ALS ADC�Ļ���ʱ�� */
        AM_TSL2540_WTIME_2_8MS_OR_33_8MS,       /* (��wlong_en�������)���wlong_enΪ�棬�ȴ�ʱ��Ϊ���ߣ�����Ϊǰ�� */
        2,                                      /* �������ϴ�������ALS�жϣ��ò���ֱ�����üĴ���ֵ����ϸ���ݲ��������ֲ�Page17 */
        AM_FALSE,                               /* WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
        AM_TSL2540_AGAIN_1,                     /* ALS���������� */
        AM_FALSE,                               /* sleep_after_interrupt */
        0x7f,                                   /* AZ_NTH_ITERATION */
};

/** \brief ������ TSL2540 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tsl2540_devinfo __g_tsl2540_info = {
        &__g_tsl2540_param_default,             /**< \brief ������ʼ�� */
        PIOB_0,                                 /**< \brief ����������� */
        0x39,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ TSL2540 �豸�ṹ�嶨�� */
am_local struct am_sensor_tsl2540_dev __g_tsl2540_dev;

/** \brief ������ TSL2540 �豸ʵ���� */
am_sensor_handle_t am_sensor_tsl2540_inst_init (void)
{
    return am_sensor_tsl2540_init(&__g_tsl2540_dev,
                                  &__g_tsl2540_info,
                                  am_zlg237_i2c1_inst_init());
}

/** \brief ������ TSL2540 ʵ�����ʼ�� */
am_err_t am_sensor_tsl2540_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tsl2540_deinit(handle);
}

/* end of file */
