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

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_mpl3115a2.h"
#include "am_delay.h"

/** \brief MPL3115A2��������ID */
const static int __mpl3115a2_id[2] = {AM_MPL3115A2_CHAN_1, AM_MPL3115A2_CHAN_2};

/* \breif MPL3115A2���������� */
static am_sensor_val_t __mpl3115a2_data[2];

/**
 * \brief ͨ��1����ѹ/���εĻص�����
 */
static void __pfn_pressure_or_altitude (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__mpl3115a2_id[0], 1, &__mpl3115a2_data[0]);
        am_sensor_val_unit_convert(&__mpl3115a2_data[0], 1, AM_SENSOR_UNIT_MICRO);

#if(__MPL3115A2_MODE == __MPL3115A2_PRE_MODE) /* ��ѹ */
        am_kprintf("The channel %d,type is pressure, value is: %d.%06d KPa!\r\n",
                   __mpl3115a2_id[0],
                   (__mpl3115a2_data[0].val/1000000),
                   (__mpl3115a2_data[0].val%1000000));
#elif(__MPL3115A2_MODE == __MPL3115A2_ALT_MODE) /* ���� */
        am_kprintf("The channel %d,type is altitude, value is: %d.%04d Meters!\r\n",
                   __mpl3115a2_id[0],
                   (__mpl3115a2_data[0].val/1000000),
                   (__mpl3115a2_data[0].val%1000000));
#endif
    }
}

/**
 * \brief ͨ��2���¶ȵĻص�����
 */
static void __pfn_temprature (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__mpl3115a2_id[1], 1, &__mpl3115a2_data[1]);
        am_sensor_val_unit_convert(&__mpl3115a2_data[1], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is temprature, value is: %d.%06d  ��!\r\n",
                   __mpl3115a2_id[1],
                   (__mpl3115a2_data[1].val)/1000000,
                   (__mpl3115a2_data[1].val)%1000000);
        am_kprintf("\r\n");
    }
}

/**
 * \brief �������
 */
void demo_std_mpl3115a2_int_entry (am_sensor_handle_t handle)
{
    /* ���øô������Ĳ���ʱ��Ϊ��2��0�η� �� */
    am_sensor_val_t mpl3115a2_rate = {0, AM_SENSOR_UNIT_BASE};
    
    am_err_t ret = AM_OK;

    ret = am_sensor_attr_set(handle,
                             __mpl3115a2_id[0],
                             AM_SENSOR_ATTR_SAMPLING_RATE,
                             &mpl3115a2_rate);
    if (ret != AM_OK) {
        am_kprintf("sensor_attr_set faild!\r\n");
    }

    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __mpl3115a2_id, 2, __mpl3115a2_data);

    /* ����ͨ��0��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __mpl3115a2_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_pressure_or_altitude,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __mpl3115a2_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_temprature,
                          (void*)handle);

    /* ��ͨ��0��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __mpl3115a2_id[0]);
    am_sensor_trigger_on(handle, __mpl3115a2_id[1]);
}

/* end of file */
