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
 * \brief ��ȫоƬFMSE A03 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-07-03  yrz, first implementation.
 * \endinternal
 */

#include "hc32_pin.h"
#include "am_fmse_a03.h"
#include "am_fmse_i2c.h"
#include "am_common.h"
#include "am_hc32l19x_inst_init.h"

/** \brief ��ȫоƬFMSE A03 �豸��Ϣʵ�� */
am_const am_local struct am_fmse_i2c_devinfo __g_fmse_i2c_devinfo = {
    0x71               /* I2C��ַ */
};

/** \breif ��ȫоƬFMSE A03 �豸�ṹ�嶨�� */
am_local struct am_fmse_i2c_dev __g_fmse_i2c_dev;

/** \brief ��ȫоƬFMSE A03 �豸ʵ���� */
am_fmse_handle_t am_fmse_i2c_inst_init (void)
{
    return am_fmse_i2c_init(&__g_fmse_i2c_dev,
                            &__g_fmse_i2c_devinfo,
                             am_hc32_i2c0_inst_init());
}

/** \brief ��ȫоƬFMSE A03 ʵ�����ʼ�� */
am_err_t am_fmse_i2c_inst_deinit (am_fmse_handle_t handle)
{
    return am_fmse_i2c_deinit(handle);
}

/* end of file */
