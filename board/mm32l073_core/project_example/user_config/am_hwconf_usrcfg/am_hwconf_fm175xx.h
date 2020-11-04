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
 * \brief FM175xx �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_HWCONF_FM175XX_H
#define __AM_HWCONF_FM175XX_H

#include "ametal.h"
#include "am_fm175xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief fm175xxʵ����ʼ��
 * \return fm175xx����������ΪNULL��������ʼ��ʧ��
 */
am_fm175xx_handle_t am_fm175xx_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif
