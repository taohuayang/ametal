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
 * \brief �������û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-02  htf, first implementation
 * \endinternal
 */
#ifndef __AM_HWCONF_ZSN700_READER_H
#define __AM_HWCONF_ZSN700_READER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \brief ������ʵ����ʼ��
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_zsn700_reader_handle_t am_zsn700_reader_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_HWCONF_ZSN700_READER_H */

/* end of file */
