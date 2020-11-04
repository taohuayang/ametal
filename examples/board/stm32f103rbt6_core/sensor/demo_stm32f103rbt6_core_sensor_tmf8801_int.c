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
 * \brief TOF������ TMF8801 ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. ���ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_delay.h"
#include "am_stm32f103rbt6.h"
#include "am_sensor.h"
#include "am_hwconf_sensor_tmf8801.h"
#include "demo_std_entries.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������������
 */
void demo_stm32f103rbt6_core_sensor_tmf8801_int_entry (void)
{
    am_sensor_handle_t handle = am_sensor_tmf8801_inst_init();

    demo_std_tmf8801_int_entry(handle);
}


/* end of file */
