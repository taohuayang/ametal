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
 * \brief ������ FXOS8700CQ �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_SENSOR_FXOS8700CQ_H
#define __AM_HWCONF_SENSOR_FXOS8700CQ_H

#include "ametal.h"
#include "am_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ������ FXOS8700CQ �豸ʵ����
 */
am_sensor_handle_t am_sensor_fxos8700cq_inst_init (void);

/**
 * \brief ������ FXOS8700CQ ʵ�����ʼ��
 */
am_err_t am_sensor_fxos8700cq_inst_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
