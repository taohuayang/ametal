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
 * \brief �����⴫���� TSL2560 ���̣�ͨ����׼�ӿ�ʵ��(ͨ����ѯ��ʽ��ȡ����)
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡͨ��ֵ
 *
 * \par Դ����
 * \snippet demo_zlg237_core_sensor_tsl2560.c src_zlg237_core_sensor_tsl2560
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

#include "am_sensor.h"
#include "am_hwconf_sensor_tsl2560.h"
#include "demo_std_entries.h"
#include "demo_am237_core_entries.h"

/**
 * \brief �������������
 */
void demo_zlg237_core_sensor_tsl2560_entry (void)
{
    am_sensor_handle_t handle = am_sensor_tsl2560_inst_init();

    demo_std_tsl2560_entry(handle);
}


/* end of file */
