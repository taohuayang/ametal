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
 * \brief LED �û������ļ���GPIOֱ��������
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-09  zp, first implementation
 * \endinternal
 */
#ifndef __AM_HWCONF_HC32_LED_GPIO_H
#define __AM_HWCONF_HC32_LED_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \brief LED ʵ����ʼ����GPIOֱ��������
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ�����C�ļ��и��������Ƿ�Ϸ�
 */
int am_hc32_led_gpio_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
