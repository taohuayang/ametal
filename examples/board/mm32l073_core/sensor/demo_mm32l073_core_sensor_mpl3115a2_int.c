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
 * \brief ��ѹ�¶ȴ����� MPL3115A2 ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. �������õ�Ƶ�ʣ����ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-11  fzb, first implementation
 * \endinternal
 */

#include "am_sensor.h"
#include "am_hwconf_sensor_mpl3115a2.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������������
 */
void demo_mm32l073_core_sensor_mpl3115a2_int_entry (void)
{
    am_sensor_handle_t handle = am_sensor_mpl3115a2_inst_init();

    demo_std_mpl3115a2_int_entry(handle);
}


/* end of file */
