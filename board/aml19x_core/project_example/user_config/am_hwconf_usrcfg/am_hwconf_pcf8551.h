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

#ifndef __AM_HWCONF_PCF8551_H
#define __AM_HWCONF_PCF8551_H

#include "ametal.h"
#include "am_pcf8551.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief PCF8551 �豸ʵ����
 */
am_pcf8551_handle_t am_pcf8551_inst_init (void);

/**
 * \brief PCF8551 ʵ�����ʼ��
 */
am_err_t am_pcf8551_inst_deinit (am_pcf8551_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
