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
 * \brief ����ʱ�䴫���� TMF8801 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-02  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_SENSOR_TMF8801_H
#define __AM_HWCONF_SENSOR_TMF8801_H

#include "ametal.h"
#include "am_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ������ TMF8801 �豸ʵ����
 */
am_sensor_handle_t am_sensor_tmf8801_inst_init (void);

/**
 * \brief ������ TMF8801 ʵ�����ʼ��
 */
am_err_t am_sensor_tmf8801_inst_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
