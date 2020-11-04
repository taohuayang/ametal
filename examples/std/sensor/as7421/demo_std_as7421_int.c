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
 * \brief �߹��״����� AS7421 ���̣�ͨ������ģʽʵ��
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
#include "am_sensor_as7421.h"
#include "am_delay.h"

const char *__as7421_data_name_string[] = {"TEMP0", "TEMP1", "TEMP2", "TEMP3"};

/** \brief AS7421��������ID */
const static int __as7421_id[2] = {AM_AS7421_CHAN_1, AM_AS7421_CHAN_2};

/** \brief AS7421���������� */
static am_sensor_val_t __as7421_data[68];

/**
 * \brief ͨ��1���¶ȵĻص�����
 */
static void __pfn_temprature (void *p_arg, uint32_t trigger_src)
{
    uint8_t i = 0;

    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7421_id[0], 1, &__as7421_data[0]);
        am_kprintf("The channel %d,type is temprature!\r\n",
                   __as7421_id[0]);

        for (i = 0; i < 4; i++) {
            am_kprintf("The %s channel ADC value is: %d !\r\n",
                       __as7421_data_name_string[i],
                       __as7421_data[i].val);
        }
    }
}

/**
 * \brief ͨ��2��SPECTRAL�Ļص�����
 */
static void __pfn_spectral (void *p_arg, uint32_t trigger_src)
{
    uint8_t i = 0;

    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__as7421_id[1], 1, &__as7421_data[4]);
        am_kprintf("The channel %d,type is SPECTRAL!\r\n",
                   __as7421_id[1]);

        for (i = 4; i < 68; i++) {
            am_kprintf("The CH[%d] ADC value is: %d !\r\n",
                       i,
                       __as7421_data[i].val);
        }
    }
}

/**
 * \brief �������
 */
void demo_std_as7421_int_entry (am_sensor_handle_t handle)
{
    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __as7421_id, 2, __as7421_data);

    /* ����ͨ��0��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __as7421_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_temprature,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __as7421_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_spectral,
                          (void*)handle);

    /* ��ͨ��0��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __as7421_id[0]);
    am_sensor_trigger_on(handle, __as7421_id[1]);

    while (1) {

    }
}

/* end of file */
