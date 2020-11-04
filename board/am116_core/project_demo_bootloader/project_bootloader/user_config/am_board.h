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
 * \brief AM116BLE
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_BOARD_H
#define __AM_BOARD_H

#include "ametal.h"
#include "am_prj_config.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_pwm.h"
#include "am_timer.h"
#include "am_bsp_delay_timer.h"


/** \brief LED ����ID�� */
#define LED0          0
#define LED1          1

/**
 * \brief �弶��ʼ��
 *
 * \return ��
 *
 * \note �ú������ʼ��ϵͳʱ�ӡ�GPIO���жϡ���������LED����ʱ����
 */
void am_board_init (void);

#endif /* __AM_BOARD_H */

/* end of file */
