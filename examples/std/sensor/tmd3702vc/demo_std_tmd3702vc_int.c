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
 * \brief ������/��ɫ���ӽ������� TMD3702VC ���̣�ͨ������ģʽʵ��
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
#include "am_sensor_tmd3702vc.h"
#include "am_delay.h"

const char *__tmd3702vc_data_name_string[] = {"proximity", "clear", "red", "green", "blue"};

/** \brief TMD3702VC��������ID */
const static int __tmd3702vc_id[2] = {AM_TMD3702VC_CHAN_1, AM_TMD3702VC_CHAN_2};

/** \brief TMD3702VC���������� */
static am_sensor_val_t __tmd3702vc_data[5];

/**
 * \brief ͨ��1��Prox�Ļص�����
 */
static void __pfn_proximity (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_THRESHOLD) {
        am_sensor_data_get(handle, &__tmd3702vc_id[0], 1, &__tmd3702vc_data[0]);
        am_kprintf("The channel %d,type is proximity,ADC value is: %d !\r\n",
                   __tmd3702vc_id[0],
                   __tmd3702vc_data[0].val);
    }
}

/**
 * \brief ͨ��2��ALS�Ļص�����
 */
static void __pfn_als (void *p_arg, uint32_t trigger_src)
{
    uint8_t i = 0;

    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_THRESHOLD) {
        am_sensor_data_get(handle, &__tmd3702vc_id[1], 1, &__tmd3702vc_data[1]);
        am_kprintf("The channel %d,type is ALS!\r\n",
                   __tmd3702vc_id[1]);

        for (i = 1; i < 5; i++) {
            am_kprintf("The %s channel ADC value is: %d !\r\n",
                       __tmd3702vc_data_name_string[i],
                       __tmd3702vc_data[i].val);
        }
    }
}

/**
 * \brief �������
 */
void demo_std_tmd3702vc_int_entry (am_sensor_handle_t handle)
{
    /* ���õ͡�����ֵ */
    am_sensor_tmd3702vc_ioctl(handle, AM_SENSOR_TMD3702VC_LOW_ALS_THRESHOLD_SET, (void *)200);
    am_sensor_tmd3702vc_ioctl(handle, AM_SENSOR_TMD3702VC_HIGH_ALS_THRESHOLD_SET, (void *)500);
    am_sensor_tmd3702vc_ioctl(handle, AM_SENSOR_TMD3702VC_LOW_PROX_THRESHOLD_SET, (void *)200);
    am_sensor_tmd3702vc_ioctl(handle, AM_SENSOR_TMD3702VC_HIGH_PROX_THRESHOLD_SET, (void *)500);

    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __tmd3702vc_id, 2, __tmd3702vc_data);

    /* ����ͨ��0��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __tmd3702vc_id[0],
                          AM_SENSOR_TRIGGER_THRESHOLD,
                          __pfn_proximity,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __tmd3702vc_id[1],
                          AM_SENSOR_TRIGGER_THRESHOLD,
                          __pfn_als,
                          (void*)handle);

    /* ��ͨ��0��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __tmd3702vc_id[0]);
    am_sensor_trigger_on(handle, __tmd3702vc_id[1]);

    while (1) {
    
    }
}

/* end of file */
