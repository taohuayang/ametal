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
 * \brief ���ᴫ����FXOS8700CQ ���̣�ͨ����׼�ӿ�ʵ��(ͨ����ѯ��ʽ��ȡ����)
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ���ٶȺʹŸ�Ӧǿ�ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_sensor_fxos8700cq.c src_mm32l073_core_sensor_fxos8700cq
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  fzb, first implementation
 * \endinternal
 */

#include "am_sensor.h"
#include "am_hwconf_sensor_fxos8700cq.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������������
 */
void demo_mm32l073_core_sensor_fxos8700cq_entry (void)
{
    am_sensor_handle_t handle = am_sensor_fxos8700cq_inst_init();

    demo_std_fxos8700cq_entry(handle);
}


/* end of file */
