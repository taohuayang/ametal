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
 * \brief ���״����� AS7341 ���̣�ͨ������ģʽʵ��
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
#include "am_sensor_as7341.h"
#include "am_delay.h"

const char *__as7341_data_name_string[] = {"F1", "F2", "F3", "F4", "F5", "F6",
                                           "F7", "F8", "clear", "dark", "prox", "flicker"
};

/** \brief AS7341��������ID */
const static int __as7341_id[1] = {AM_AS7341_CHAN_1};

/** \brief AS7341���������� */
static am_sensor_val_t __as7341_data[12];

/**
 * \brief ͨ��1��SPECTRAL�Ļص�����
 */
static void __pfn_spectral (void *p_arg, uint32_t trigger_src)
{
    uint8_t i = 0;

    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_THRESHOLD) {
        am_sensor_data_get(handle, &__as7341_id[0], 1, &__as7341_data[0]);
        am_kprintf("The channel %d,type is SPECTRAL!\r\n",
                   __as7341_id[0]);

        for (i = 0; i < 12; i++) {
            am_kprintf("The %s ADC value is: %d !\r\n",
                       __as7341_data_name_string[i],
                       __as7341_data[i].val);
        }
    }
}

/**
 * \brief �������
 */
void demo_std_as7341_int_entry (am_sensor_handle_t handle)
{
    /* ���õ͡�����ֵ */
    am_sensor_as7341_ioctl(handle, AM_SENSOR_AS7341_LOW_SPECTRAL_THRESHOLD_SET, (void *)200);
    am_sensor_as7341_ioctl(handle, AM_SENSOR_AS7341_HIGH_SPECTRAL_THRESHOLD_SET, (void *)500);

    /* ʹ��һ·ͨ�� */
    am_sensor_enable(handle, __as7341_id, 1, __as7341_data);

    /* ����ͨ��0�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __as7341_id[0],
                          AM_SENSOR_TRIGGER_THRESHOLD,
                          __pfn_spectral,
                          (void*)handle);

    /* ��ͨ��0�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __as7341_id[0]);

    while (1) {

    }
}

/* end of file */
