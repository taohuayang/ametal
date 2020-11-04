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
 * \brief ��ʪ�ȴ����� HTS221 ���̣�ͨ����׼�ӿ�ʵ��(ͨ����ѯ��ʽ��ȡ����)
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡʪ�Ⱥ��¶ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_hk32f103rbt6_core_sensor_hts221.c src_am116_core_sensor_hts221
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-27  wan, first implementation
 * \endinternal
 */

#include "am_sensor.h"
#include "am_hwconf_sensor_hts221.h"
#include "demo_std_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

/**
 * \brief �������������
 */
void demo_hk32f103rbt6_core_sensor_hts221_entry (void)
{
    am_sensor_handle_t handle = am_sensor_hts221_inst_init();

    demo_std_hts221_entry(handle);
}


/* end of file */
