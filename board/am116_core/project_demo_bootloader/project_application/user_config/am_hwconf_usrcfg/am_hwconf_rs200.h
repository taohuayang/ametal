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
 * \brief RS200�����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-17  wan, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_RS200_H
#define __AM_HWCONF_RS200_H

#include "ametal.h"
#include "am_rs200.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief RS200 �豸ʵ����
 */
am_rs200_handle_t am_rs200_inst_init (void);

/**
 * \brief RS200 ʵ�����ʼ��
 */
am_err_t am_rs200_inst_deinit (am_rs200_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
