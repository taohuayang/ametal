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
 * \brief �ӽ������� TMD2635 ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. �����޴����ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_tmd2635.h"
#include "am_delay.h"

/** \brief TMD2635��������ID */
const static int __tmd2635_id[1] = {AM_TMD2635_CHAN_1};

/** \brief TMD2635���������� */
static am_sensor_val_t __tmd2635_data[1];

/**
 * \brief ͨ��1��Prox�Ļص�����
 */
static void __pfn_proximity (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_THRESHOLD) {
        am_sensor_data_get(handle, &__tmd2635_id[0], 1, &__tmd2635_data[0]);
        am_kprintf("The channel %d,type is proximity, value is: %d !\r\n",
                   __tmd2635_id[0],
                   __tmd2635_data[0].val);
    }
}

/**
 * \brief �������
 */
void demo_std_tmd2635_int_entry (am_sensor_handle_t handle)
{
    /* ���õ͡�����ֵ */
    am_sensor_tmd2635_ioctl(handle, AM_SENSOR_TMD2635_LOW_PROX_THRESHOLD_SET, (void *)200);
    am_sensor_tmd2635_ioctl(handle, AM_SENSOR_TMD2635_HIGH_PROX_THRESHOLD_SET, (void *)500);

    /* ʹ��һ·ͨ�� */
    am_sensor_enable(handle, __tmd2635_id, 1, __tmd2635_data);

    /* ����ͨ��0�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __tmd2635_id[0],
                          AM_SENSOR_TRIGGER_THRESHOLD,
                          __pfn_proximity,
                          (void*)handle);

    /* ��ͨ��0�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __tmd2635_id[0]);

    while (1) {
    
    }
}

/* end of file */
