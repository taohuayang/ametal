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
 * \brief �����⴫���� TSL2560 ���̣�ͨ������ģʽʵ��
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
#include "am_sensor_tsl2560.h"
#include "am_delay.h"

/** \brief TSL2560��������ID */
const static int __tsl2560_id[2] = {AM_TSL2560_CHAN_1, AM_TSL2560_CHAN_2};

/** \brief TSL2560���������� */
static am_sensor_val_t __tsl2560_data[2];

/**
 * \brief ͨ��1��CH0�Ļص�����
 */
static void __pfn_ch0 (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_THRESHOLD) {
        am_sensor_data_get(handle, &__tsl2560_id[0], 1, &__tsl2560_data[0]);
        am_kprintf("The channel %d,type is CH0, value is: %d !\r\n",
                   __tsl2560_id[0],
                   __tsl2560_data[0].val);
    }
}

/**
 * \brief ͨ��2��CH1�Ļص�����
 */
static void __pfn_ch1 (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_THRESHOLD) {
        am_sensor_data_get(handle, &__tsl2560_id[1], 1, &__tsl2560_data[1]);
        am_kprintf("The channel %d,type is CH1, value is: %d !\r\n",
                   __tsl2560_id[1],
                   __tsl2560_data[1].val);
    }
}

/**
 * \brief �������
 */
void demo_std_tsl2560_int_entry (am_sensor_handle_t handle)
{
    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __tsl2560_id, 2, __tsl2560_data);

    /* ����ͨ��0��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __tsl2560_id[0],
                          AM_SENSOR_TRIGGER_THRESHOLD,
                          __pfn_ch0,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __tsl2560_id[1],
                          AM_SENSOR_TRIGGER_THRESHOLD,
                          __pfn_ch1,
                          (void*)handle);

    /* ��ͨ��0��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __tsl2560_id[0]);
    am_sensor_trigger_on(handle, __tsl2560_id[1]);

    while (1) {

    }
}

/* end of file */
