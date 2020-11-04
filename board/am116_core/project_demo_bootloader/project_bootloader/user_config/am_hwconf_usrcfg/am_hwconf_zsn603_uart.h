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
 * \brief ZSN603 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-04-22  htf, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_ZSN603_UART_H
#define __AM_HWCONF_ZSN603_UART_H

#include "ametal.h"
#include "zsn603.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ZSN603 (UART ģʽ) ʵ����ʼ��
 *
 * \retval  handle  ��ʼ���ɹ�
 * \retval  NULL    ��ʼ��ʧ��
 */
zsn603_handle_t  am_zsn603_uart_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
