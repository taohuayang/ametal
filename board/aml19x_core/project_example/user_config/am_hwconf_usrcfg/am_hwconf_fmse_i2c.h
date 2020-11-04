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

#ifndef __AM_HWCONF_FMSE_I2C_H
#define __AM_HWCONF_FMSE_I2C_H

#include "ametal.h"
#include "am_fmse_a03.h"
#include "am_fmse_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ��ȫоƬFMSE A03 �豸ʵ����
 */
am_fmse_handle_t am_fmse_i2c_inst_init (void);

/**
 * \brief ��ȫоƬFMSE A03 ʵ�����ʼ��
 */
am_err_t am_fmse_i2c_inst_deinit (am_fmse_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif

/* end of file */
