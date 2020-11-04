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
 * \brief ���״����� AS7262 (I2Cģʽ) ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. ���ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_as7262.h"
#include "am_delay.h"

/** \brief AS7262��������ID */
const static int __as7262_id[6] = {AM_AS7262_CHAN_1, AM_AS7262_CHAN_2,
                                   AM_AS7262_CHAN_3, AM_AS7262_CHAN_4,
                                   AM_AS7262_CHAN_5, AM_AS7262_CHAN_6};

/** \brief AS7262���������� */
static am_sensor_val_t __as7262_data[6];

/**
 * \brief ͨ��1��CH_V�Ļص�����
 */
static void __pfn_ch_v (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7262_id[0], 1, &__as7262_data[0]);
        am_kprintf("The channel %d,type is V, value is: %d !\r\n",
                   __as7262_id[0],
                   __as7262_data[0].val);
    }
}

/**
 * \brief ͨ��2��CHB�Ļص�����
 */
static void __pfn_ch_b (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7262_id[1], 1, &__as7262_data[1]);
        am_kprintf("The channel %d,type is B, value is: %d !\r\n",
                   __as7262_id[1],
                   __as7262_data[1].val);
    }
}

/**
 * \brief ͨ��3��CHG�Ļص�����
 */
static void __pfn_ch_g (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7262_id[2], 1, &__as7262_data[2]);
        am_kprintf("The channel %d,type is G, value is: %d !\r\n",
                   __as7262_id[2],
                   __as7262_data[2].val);
    }
}

/**
 * \brief ͨ��4��CHY�Ļص�����
 */
static void __pfn_ch_y (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7262_id[3], 1, &__as7262_data[3]);
        am_kprintf("The channel %d,type is Y, value is: %d !\r\n",
                   __as7262_id[3],
                   __as7262_data[3].val);
    }
}

/**
 * \brief ͨ��5��CHO�Ļص�����
 */
static void __pfn_ch_o (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7262_id[4], 1, &__as7262_data[4]);
        am_kprintf("The channel %d,type is O, value is: %d !\r\n",
                   __as7262_id[4],
                   __as7262_data[4].val);
    }
}

/**
 * \brief ͨ��6��CHR�Ļص�����
 */
static void __pfn_ch_r (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7262_id[5], 1, &__as7262_data[5]);
        am_kprintf("The channel %d,type is R, value is: %d !\r\n",
                   __as7262_id[5],
                   __as7262_data[5].val);
    }
}

/**
 * \brief �������
 */
void demo_std_as7262_int_entry (am_sensor_handle_t handle)
{
    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __as7262_id, 6, __as7262_data);

    /* ����ͨ��0��1��2��3��4��5�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __as7262_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_ch_v,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __as7262_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_ch_b,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __as7262_id[2],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_ch_g,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __as7262_id[3],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_ch_y,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __as7262_id[4],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_ch_o,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __as7262_id[5],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_ch_r,
                          (void*)handle);

    /* ��ͨ��0��1��2��3��4��5�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __as7262_id[0]);
    am_sensor_trigger_on(handle, __as7262_id[1]);
    am_sensor_trigger_on(handle, __as7262_id[2]);
    am_sensor_trigger_on(handle, __as7262_id[3]);
    am_sensor_trigger_on(handle, __as7262_id[4]);
    am_sensor_trigger_on(handle, __as7262_id[5]);

    while (1) {

    }
}

/* end of file */
