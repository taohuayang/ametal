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
 * \brief ������ AS7341 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_as7341.h"
#include "am_common.h"
#include "stm32f103rbt6_pin.h"
#include "am_stm32f103rbt6_inst_init.h"

am_const am_local as7341_param_config_t __g_as7341_param_default = {
    AM_AS7341_LED_CONTROLLED,           /* LED_SEL                  */
    AM_AS7341_LED_ACT_CONNECTED,        /* LED_ACT                  */
    4,                                  /* LED_DRIVE:12mA   2*(n+2) */
    1,                                  /* INT_SEL                  */
    AM_AS7341_INT_MODE_SPM,             /* INT_MODE                 */
    5,                                  /* EDGE (SYNDģʽ����Ч)    */
    AM_AS7341_PD_GPIO_CONNECTED,        /* PD_GPIO                  */
    AM_AS7341_PD_INT_CONNECTED,         /* PD_INT                   */

    0xFFFE,                             /* ASTEP (SYNDģʽ����Ч)   */
    0,                                  /* ATIME (SYNDģʽ����Ч) 
            Integration time = (ATIME + 1) * (ASTEP + 1) * 2.78us   */

    71,//AM_AS7341_WTIME_2_78MS_OR_44_48MS,  /* WTIME (SYNDģʽ����Ч)   */
    AM_AS7341_LOWPOWER_IDLE_DISABLE,    /* LOWPOWER_IDLE            */
    AM_FALSE,                           /* WLONG                    */
    AM_AS7341_AGAIN_32,                 /* AGAIN                    */
    AM_FALSE,                           /* SAI                      */
    AM_AS7341_FIFO_TH_8,                /* FIFO_TH                  */
    AM_AS7341_FD_AGC_DISABLE,           /* FD_AGC                   */
    AM_AS7341_SP_AGC_DISABLE,           /* SP_AGC                   */
    AM_AS7341_AGC_H_87_5_PERCENT,       /* AGC_H                    */
    AM_AS7341_AGC_L_50_PERCENT,         /* AGC_L                    */

    2,                                  /* FD_PERS
                                    persistence = (2^(FD_PERS - 1)) */

    AM_AS7341_SP_TH_CH0,                /* SP_TH_CH                 */

    1,                                  /* APERS
                Spectral Interrupt Persistence = APERS (APERS <= 3)
                Spectral Interrupt Persistence = 5 * (APERS - 3)    */

    0,                                  /* GPIO_INV     (�˴����ý���SPMģʽ����Ч)*/
    0,                                  /* GPIO_IN_EN   (�˴����ý���SPMģʽ����Ч)*/
    1,                                  /* GPIO_OUT     (�˴����ý���SPMģʽ����Ч)*/
    AM_AS7341_AGC_FD_GAIN_MAX_256,      /* AGC_FD_GAIN_MAX          */
    AM_AS7341_AGC_AGAIN_MAX_256,        /* AGC_AGAIN_MAX            */
    255,                                /* AZ_NTH_ITERATION         */
    0,                                  /* FD_TIME                  */
    AM_AS7341_FD_GAIN_256,              /* FD_GAIN                  */
    0,                                  /* FIFO_WRITE_FD            */
    0x00,                               /* FIFO_MAP_ENABLE          */
};

/** \brief ������ AS7341 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_as7341_devinfo __g_as7341_info = {
        &__g_as7341_param_default,              /**< \brief ������ʼ�� */
        PIOA_0,                                 /**< \brief INT���� */
        PIOC_6,                                 /**< \brief GPIO���� */
        0x39,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ AS7341 �豸�ṹ�嶨�� */
am_local struct am_sensor_as7341_dev __g_as7341_dev;

/** \brief ������ AS7341 �豸ʵ���� */
am_sensor_handle_t am_sensor_as7341_inst_init (void)
{
    return am_sensor_as7341_init(&__g_as7341_dev,
                                 &__g_as7341_info,
                                 am_stm32f103rbt6_i2c1_inst_init());
}

/** \brief ������ AS7341 ʵ�����ʼ�� */
am_err_t am_sensor_as7341_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_as7341_deinit(handle);
}

/* end of file */
