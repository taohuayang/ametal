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
 * \brief ������ TCS3430 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tcs3430.h"
#include "am_common.h"
#include "zlg237_pin.h"
#include "am_zlg237_inst_init.h"

am_const am_local tcs3430_param_config_t __g_tcs3430_param_default = {
        AM_TCS3430_ATIME_50MS,                  /* ALS ADC�Ļ���ʱ�� */
        AM_TCS3430_WTIME_2_78MS_OR_33_4MS,      /* (��wlong_en�������)���wlong_enΪ�棬�ȴ�ʱ��Ϊ���ߣ�����Ϊǰ�� */
        2,                                      /* �������ϴ�������ALS�жϣ��ò���ֱ�����üĴ���ֵ����ϸ���ݲ��������ֲ�Page16 */
        AM_FALSE,                               /* WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
        AM_TCS3430_AMUX_DISABLE,                /* AMUX */
        AM_TCS3430_AGAIN_128,                   /* ALS���������� */
        AM_FALSE,                               /* sleep_after_interrupt */
        0,                                      /* AZ_MODE */
        0x7f,                                   /* AZ_NTH_ITERATION */
};

/** \brief ������ TCS3430 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tcs3430_devinfo __g_tcs3430_info = {
        &__g_tcs3430_param_default,             /**< \brief ������ʼ�� */
        PIOA_1,                                 /**< \brief ����������� */
        0x39,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ TCS3430 �豸�ṹ�嶨�� */
am_local struct am_sensor_tcs3430_dev __g_tcs3430_dev;

/** \brief ������ TCS3430 �豸ʵ���� */
am_sensor_handle_t am_sensor_tcs3430_inst_init (void)
{
    return am_sensor_tcs3430_init(&__g_tcs3430_dev,
                                  &__g_tcs3430_info,
                                  am_zlg237_i2c1_inst_init());
}

/** \brief ������ TCS3430 ʵ�����ʼ�� */
am_err_t am_sensor_tcs3430_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tcs3430_deinit(handle);
}

/* end of file */
