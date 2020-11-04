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
 * \brief cs1237 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-11-11  htf, first implementation.
 * \endinternal
 */
#ifndef __AM_HWCONF_CS1237_H
#define __AM_HWCONF_CS1237_H

#include "ametal.h"
#include "am_cs1237.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief cs1237ʵ����ʼ��
 * \return cs1237����������ΪNULL��������ʼ��ʧ��
 */
am_cs1237_adc_handle_t am_cs1237_inst_init(void);

#ifdef __cplusplus
}
#endif

#endif
