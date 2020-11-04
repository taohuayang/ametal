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
 * \brief ������ TMD2635 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_SENSOR_TMD2635_H
#define __AM_HWCONF_SENSOR_TMD2635_H

#include "ametal.h"
#include "am_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ������ TMD2635 �豸ʵ����
 */
am_sensor_handle_t am_sensor_tmd2635_inst_init (void);

/**
 * \brief ������ TMD2635 ʵ�����ʼ��
 */
am_err_t am_sensor_tmd2635_inst_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
