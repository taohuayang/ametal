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
 * \brief ���ᴫ����FXOS8700CQ ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. �������ݸ����ٶȣ����ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  fzb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_fxos8700cq.h"
#include "am_delay.h"

/** \brief FXOS8700CQ��������ID */
const static int __fxos8700cq_id[6] = {AM_FXOS8700CQ_CHAN_1, AM_FXOS8700CQ_CHAN_2,
                                       AM_FXOS8700CQ_CHAN_3, AM_FXOS8700CQ_CHAN_4,
                                       AM_FXOS8700CQ_CHAN_5, AM_FXOS8700CQ_CHAN_6};

/* \breif FXOS8700CQ���������� */
static am_sensor_val_t __fxos8700cq_data[6];

/**
 * \brief ͨ��1��X����ٶȵĻص�����
 */
static void __pfn_accel_x (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__fxos8700cq_id[0], 1, &__fxos8700cq_data[0]);
        am_sensor_val_unit_convert(&__fxos8700cq_data[0], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is accel X, value is: %d.%06d  mg!\r\n",
                   __fxos8700cq_id[0],
                   (__fxos8700cq_data[0].val)/1000000,
                   (uint32_t)(__fxos8700cq_data[0].val)%1000000);
    }
}

/**
 * \brief ͨ��2��Y����ٶȵĻص�����
 */
static void __pfn_accel_y (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__fxos8700cq_id[1], 1, &__fxos8700cq_data[1]);
        am_sensor_val_unit_convert(&__fxos8700cq_data[1], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is accel Y, value is: %d.%06d  mg!\r\n",
                   __fxos8700cq_id[1],
                   (__fxos8700cq_data[1].val)/1000000,
                   (uint32_t)(__fxos8700cq_data[1].val)%1000000);
    }
}

/**
 * \brief ͨ��3��Z����ٶȵĻص�����
 */
static void __pfn_accel_z (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__fxos8700cq_id[2], 1, &__fxos8700cq_data[2]);
        am_sensor_val_unit_convert(&__fxos8700cq_data[2], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is accel Z, value is: %d.%06d  mg!\r\n",
                   __fxos8700cq_id[2],
                   (__fxos8700cq_data[2].val)/1000000,
                   (uint32_t)(__fxos8700cq_data[2].val)%1000000);
    }
}

/**
 * \brief ͨ��4��X��Ÿ�Ӧǿ�ȵĻص�����
 */
static void __pfn_mag_x (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__fxos8700cq_id[3], 1, &__fxos8700cq_data[3]);
        am_sensor_val_unit_convert(&__fxos8700cq_data[3], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is mag X, value is: %d.%06d  gauss!\r\n",
                   __fxos8700cq_id[3],
                   (__fxos8700cq_data[3].val)/1000000,
                   (uint32_t)(__fxos8700cq_data[3].val)%1000000);
    }
}

/**
 * \brief ͨ��5��Y��Ÿ�Ӧǿ�ȵĻص�����
 */
static void __pfn_mag_y (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__fxos8700cq_id[4], 1, &__fxos8700cq_data[4]);
        am_sensor_val_unit_convert(&__fxos8700cq_data[4], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is mag Y, value is: %d.%06d  gauss!\r\n",
                   __fxos8700cq_id[4],
                   (__fxos8700cq_data[4].val)/1000000,
                   (uint32_t)(__fxos8700cq_data[4].val)%1000000);
    }
}

/**
 * \brief ͨ��6��Z��Ÿ�Ӧǿ�ȵĻص�����
 */
static void __pfn_mag_z (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__fxos8700cq_id[5], 1, &__fxos8700cq_data[5]);
        am_sensor_val_unit_convert(&__fxos8700cq_data[5], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is mag Z, value is: %d.%06d  gauss!\r\n",
                   __fxos8700cq_id[5],
                   (__fxos8700cq_data[5].val)/1000000,
                   (uint32_t)(__fxos8700cq_data[5].val)%1000000);
        am_kprintf("\r\n");
    }
}

/**
 * \brief �������
 */
void demo_std_fxos8700cq_int_entry (am_sensor_handle_t handle)
{
    /* ���øô�����������Ϊ��4G����ͨ��ͬ���� */
    am_sensor_val_t fxos8700cq_range = {4, AM_SENSOR_UNIT_BASE};
    
    am_err_t ret = AM_OK;

    ret = am_sensor_attr_set(handle,
                             __fxos8700cq_id[0],
                             AM_SENSOR_ATTR_FULL_SCALE,
                             &fxos8700cq_range);
    if (ret != AM_OK) {
        am_kprintf("sensor_attr_set faild!\r\n");
    }

    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __fxos8700cq_id, 6, __fxos8700cq_data);

    /* ����ͨ��0,1,2,3,4,5�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __fxos8700cq_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_accel_x,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __fxos8700cq_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_accel_y,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __fxos8700cq_id[2],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_accel_z,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __fxos8700cq_id[3],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_mag_x,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __fxos8700cq_id[4],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_mag_y,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __fxos8700cq_id[5],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_mag_z,
                          (void*)handle);

    /* ��ͨ��0,1,2,3,4,5�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __fxos8700cq_id[0]);
    am_sensor_trigger_on(handle, __fxos8700cq_id[1]);
    am_sensor_trigger_on(handle, __fxos8700cq_id[2]);
    am_sensor_trigger_on(handle, __fxos8700cq_id[3]);
    am_sensor_trigger_on(handle, __fxos8700cq_id[4]);
    am_sensor_trigger_on(handle, __fxos8700cq_id[5]);
}

/* end of file */
