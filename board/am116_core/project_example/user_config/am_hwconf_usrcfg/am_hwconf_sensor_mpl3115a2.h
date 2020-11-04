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
 * \brief ��ѹ�¶ȴ����� MPL3115A2 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-11  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_SENSOR_MPL3115A2_H
#define __AM_HWCONF_SENSOR_MPL3115A2_H

#include "ametal.h"
#include "am_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ������ MPL3115A2 �豸ʵ����
 */
am_sensor_handle_t am_sensor_mpl3115a2_inst_init (void);

/**
 * \brief ������ MPL3115A2 ʵ�����ʼ��
 */
am_err_t am_sensor_mpl3115a2_inst_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
