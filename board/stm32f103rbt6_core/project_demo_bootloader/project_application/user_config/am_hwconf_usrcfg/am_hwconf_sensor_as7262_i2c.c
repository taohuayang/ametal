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
 * \brief ������ AS7262 (I2Cģʽ) �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_as7262_i2c.h"
#include "am_common.h"
#include "stm32f103rbt6_pin.h"
#include "am_stm32f103rbt6_inst_init.h"

am_const am_local as7262_param_config_t __g_as7262_param_default = {
    AM_AS7262_GAIN_1,                   /**< \brief GAIN    */
    AM_AS7262_BANK_MODE_3,              /**< \brief BANK    */
    0x39,                               /**< \brief ITIME (����ʱ��Ϊ ITIME * 2.8ms)  */
    AM_AS7262_LED_DRV_12P5_MA,          /**< \brief ICL_DRV */
    AM_AS7262_LED_DRV_DISABLE,          /**< \brief LED_DRV */
    AM_AS7262_LED_IND_1_MA,             /**< \brief ICL_IND */
    AM_AS7262_LED_IND_ENABLE,           /**< \brief LED_IND */
};

/** \brief ������ AS7262 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_as7262_devinfo __g_as7262_info = {
    &__g_as7262_param_default,          /**< \brief ������ʼ�� */
    PIOA_6,                             /**< \brief INT���� */
    -1,                                 /**< \brief RST���� */
};

/** \brief ������ AS7262 (I2Cģʽ) �豸��Ϣʵ�� */
am_const am_local am_sensor_as7262_i2c_devinfo_t __g_as7262_i2c_info = {
    &__g_as7262_info,                   /**< \brief �豸��Ϣ */
    am_stm32f103rbt6_i2c2_inst_init,           /**< \brief I2C�����ȡ����*/
    am_stm32f103rbt6_i2c2_inst_deinit,         /**< \brief I2C���ʼ������*/
    0x49,                               /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ AS7262 �豸�ṹ�嶨�� */
am_local am_sensor_as7262_i2c_dev_t __g_as7262_i2c_dev;

/** \brief ������ AS7262 �豸ʵ���� */
am_sensor_handle_t am_sensor_as7262_i2c_inst_init (void)
{
    return am_sensor_as7262_i2c_init(&__g_as7262_i2c_dev,
                                     &__g_as7262_i2c_info);
}

/** \brief ������ AS7262 ʵ�����ʼ�� */
am_err_t am_sensor_as7262_i2c_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_as7262_i2c_deinit(handle);
}

/* end of file */

