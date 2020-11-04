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
 * \brief ����Ŵ����� MAG3110 ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. �������ݸ����ٶȣ����ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-03  fzb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_mag3110.h"
#include "am_delay.h"

/** \brief MAG3110��������ID */
const static int __mag3110_id[4] = {AM_MAG3110_CHAN_1, AM_MAG3110_CHAN_2,
                                    AM_MAG3110_CHAN_3, AM_MAG3110_CHAN_4};

/* \breif MAG3110���������� */
static am_sensor_val_t __mag3110_data[4];

/**
 * \brief ͨ��1��X��ŵĻص�����
 */
static void __pfn_mag_x (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg; 
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__mag3110_id[0], 1, &__mag3110_data[0]);
        am_sensor_val_unit_convert(&__mag3110_data[0], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is mag X, value is: %d.%06d  gauss!\r\n",
                   __mag3110_id[0],
                   (__mag3110_data[0].val)/1000000,
                   (uint32_t)(__mag3110_data[0].val)%1000000);
    }
}

/**
 * \brief ͨ��2��Y��ŵĻص�����
 */
static void __pfn_mag_y (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__mag3110_id[1], 1, &__mag3110_data[1]);
        am_sensor_val_unit_convert(&__mag3110_data[1], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is mag Y, value is: %d.%06d  gauss!\r\n",
                   __mag3110_id[1],
                   (__mag3110_data[1].val/1000000),
                   (uint32_t)(__mag3110_data[1].val)%1000000);
    }
}

/**
 * \brief ͨ��3��Z��ŵĻص�����
 */
static void __pfn_mag_z (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__mag3110_id[2], 1, &__mag3110_data[2]);
        am_sensor_val_unit_convert(&__mag3110_data[2], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is mag Z, value is: %d.%06d  gauss!\r\n",
                   __mag3110_id[2],
                   (__mag3110_data[2].val)/1000000,
                   (uint32_t)(__mag3110_data[2].val)%1000000);
    }
}

/**
 * \brief ͨ��4���¶ȵĻص�����
 */
static void __pfn_temprature (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__mag3110_id[3], 1, &__mag3110_data[3]);
        am_sensor_val_unit_convert(&__mag3110_data[3], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is temprature, value is: %d.%06d  ��!\r\n",
                   __mag3110_id[3],
                   (__mag3110_data[3].val)/1000000,
                   (uint32_t)(__mag3110_data[3].val)%1000000);
        am_kprintf("\r\n");
    }
}

/**
 * \brief �������
 */
void demo_std_mag3110_int_entry (am_sensor_handle_t handle)
{
    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __mag3110_id, 4, __mag3110_data);

    /* ����ͨ��0,1,2,3�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __mag3110_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_mag_x,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __mag3110_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_mag_y,
                          (void*)handle);    
    am_sensor_trigger_cfg(handle,
                          __mag3110_id[2],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_mag_z,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __mag3110_id[3],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_temprature,
                          (void*)handle);

    /* ��ͨ��0,1,2,3�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __mag3110_id[0]);
    am_sensor_trigger_on(handle, __mag3110_id[1]);
    am_sensor_trigger_on(handle, __mag3110_id[2]);
    am_sensor_trigger_on(handle, __mag3110_id[3]);
}

/* end of file */
