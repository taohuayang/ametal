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
 * \brief �¶ȴ����� AS621X �ж�ģʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �ж�ģʽ���¶ȳ�����ֵ�󱨾���������ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-21  fzb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_as621x.h"
#include "am_delay.h"

/** \brief AS621X ��������ID */
const static int __as621x_id[1] = {AM_AS621X_CHAN_1};

/** \breif AS621X���������� */
static am_sensor_val_t __as621x_data[1];

/**
 * \brief ͨ��1���¶ȱ����Ļص�����
 */
static void __pfn_temprature (void *p_arg, uint32_t trigger_src)
{
    float low_temp = 0,high_temp = 0;
    int   m_low_temp = 0,m_high_temp = 0;/* mΪ�Ŵ�10^6����˼ */

    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_THRESHOLD) {
        am_sensor_data_get(handle, &__as621x_id[0], 1, &__as621x_data[0]);
        am_sensor_val_unit_convert(&__as621x_data[0], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is temprature alarm, value is: %d.%06d  ��!\r\n",
                   __as621x_id[0],
                   (__as621x_data[0].val)/1000000,
                   (__as621x_data[0].val)%1000000);

        am_sensor_as621x_ioctl(handle, AM_SENSOR_AS621X_TLOW_THRESHOLD_GET, &low_temp);
        am_sensor_as621x_ioctl(handle, AM_SENSOR_AS621X_THIGH_THRESHOLD_GET, &high_temp);
        m_low_temp = (int)(low_temp * 1000000);
        m_high_temp = (int)(high_temp * 1000000);
        if (__as621x_data[0].val >= m_high_temp) {
            am_kprintf("The temperature exceeds THIGH!\r\n");
        } else if (__as621x_data[0].val <= m_low_temp) {
            am_kprintf("The temperature falls below TLOW!\r\n");
        }
    }
}

/**
 * \brief �������
 */
void demo_std_as621x_interrupt_mode_entry (am_sensor_handle_t handle)
{
    am_err_t ret = AM_OK;

    /* ���øô��������������Ƶ��Ϊ1Hz */
    ret = am_sensor_as621x_ioctl(handle,
                                 AM_SENSOR_AS621X_CR_SET,
                                (void *)AM_AS621X_CONVERSION_RATE_1HZ);

    if (ret != AM_OK) {
        am_kprintf("sensor_attr_set faild!\r\n");
    }

    /* ʹ��һ·ͨ�� */
    am_sensor_enable(handle, __as621x_id, 1, __as621x_data);

    /* ����ͨ��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __as621x_id[0],
                          AM_SENSOR_TRIGGER_THRESHOLD,
                          __pfn_temprature,
                          (void*)handle);

    /* ��ͨ��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __as621x_id[0]);

}

/* end of file */
