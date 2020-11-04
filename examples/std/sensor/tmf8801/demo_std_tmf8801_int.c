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
 * \brief ����ʱ�䴫���� TMF8801 ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. �������õ�Ƶ�ʣ����ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yrz, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_tmf8801.h"
#include "am_delay.h"

/** \brief TMF8801��������ID */
const static int __tmf8801_id[2] = {0, 1};

/* \breif TMF8801���������� */
static am_sensor_val_t __tmf8801_data[2];

/**
 * \brief ͨ��1������Ļص�����
 */
static void __pfn_distance (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__tmf8801_id[0], 1, &__tmf8801_data[0]);
        am_kprintf("The channel %d,type is distance, value is: %d mm!\r\n",
                   __tmf8801_id[0],
                   __tmf8801_data[0]);
    }
}

/**
 * \brief ͨ��2���¶ȵĻص�����
 */
static void __pfn_temprature (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__tmf8801_id[1], 1, &__tmf8801_data[1]);
        am_kprintf("The channel %d,type is temprature, value is: %d ��!\r\n",
                   __tmf8801_id[1],
                   __tmf8801_data[1].val);
    }
}

/**
 * \brief �������
 */
void demo_std_tmf8801_int_entry (am_sensor_handle_t handle)
{
    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __tmf8801_id, 2, __tmf8801_data);

    /* ����ͨ��0��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __tmf8801_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_distance,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __tmf8801_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_temprature,
                          (void*)handle);

    /* ��ͨ��0��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __tmf8801_id[0]);
    am_sensor_trigger_on(handle, __tmf8801_id[1]);

    while (1) {
    
    }
}

/* end of file */
