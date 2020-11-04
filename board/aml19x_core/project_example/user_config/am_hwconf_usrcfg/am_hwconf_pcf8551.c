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
 * \brief PCF8551 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-02-25  YRZ, first implementation.
 * \endinternal
 */

#include "hc32_pin.h"
#include "am_pcf8551.h"
#include "am_hc32l19x_inst_init.h"

/** \brief PCF8551 �豸��Ϣʵ�� */
am_const am_local struct am_pcf8551_devinfo __g_pcf8551_devinfo = {
    0x38               /*< \breif PCF8551 I2C��ַ */
};

/** \breif PCF8551 �豸�ṹ�嶨�� */
am_local struct am_pcf8551_dev __g_pcf8551_dev;

/** \brief PCF8551 �豸ʵ���� */
am_pcf8551_handle_t am_pcf8551_inst_init (void)
{
    return am_pcf8551_init(&__g_pcf8551_dev,
                           &__g_pcf8551_devinfo,
                            am_hc32_i2c1_inst_init());
}

/** \brief PCF8551 ʵ�����ʼ�� */
am_err_t am_pcf8551_inst_deinit (am_pcf8551_handle_t handle)
{
    return am_pcf8551_deinit(handle);
}

/* end of file */
