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
 * \brief MMC5883MA �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-28  wk, first implementation
 * \endinternal
 */

#ifndef __AM_HWCONF_SENSOR_MMC5883MA_H
#define __AM_HWCONF_SENSOR_MMC5883MA_H

#include "ametal.h"
#include "am_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * \brief ������ MMC5883MA ʵ����ʼ�� 
 */
am_sensor_handle_t am_sensor_mmc5883ma_inst_init (void);

/** 
 * \brief ������ MMC5883MA ʵ�����ʼ�� 
 */
am_err_t am_sensor_mmc5883ma_inst_deinit (am_sensor_handle_t handle);   
       
#ifdef __cplusplus
}
#endif

#endif

/* end of file */
