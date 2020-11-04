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
 * \brief �¶ȴ����� AS621X �Ƚ�ģʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ�¶ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_std_as621x_comparator_mode.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-21  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_as621x_comparator_mode
 * \copydoc demo_std_as621x_comparator_mode.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_as621x.h"
#include "am_delay.h"

am_local void __alert_bit_info_get(am_sensor_handle_t handle)
{
    am_sensor_as621x_dev_t *p_dev = handle->p_drv;

    uint8_t alert_bit;

    am_sensor_as621x_ioctl(handle, AM_SENSOR_AS621X_ALERT_BIT_GET, &alert_bit);
    if (alert_bit == p_dev->dev_info->p_param_default->polarity_high) {
        am_kprintf("The temperature has exceeded THIGH!\r\n");
    } else {
        am_kprintf("The temperature has fallen below TLOW or Reset!\r\n");
    }
}

/**
 * \brief �������
 */
void demo_std_as621x_comparator_mode_entry (am_sensor_handle_t handle)
{
    /* AS621X�ṩ������ͨ��ID�о� */
    const int       id[1] = {AM_AS621X_CHAN_1};

    /* ����һ��ͨ�����ݵĻ��� */
    am_sensor_val_t data[1];

    int             i;

    /* ��ȡSMλ��ֵ */
    uint8_t         sm_bit;

    /*
     * �г�һ��ͨ�����¶ȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"temperature"};
    const char *data_unit_string[] = {"��"};

    am_sensor_enable(handle, id, 1, data);

    while(1) {
        am_sensor_data_get(handle, id, 1, data);
        for(i = 0; i < 1; i++) {
            if (AM_SENSOR_VAL_IS_VALID(data[i])) { /* ��ͨ��������Ч����������ʹ�� */
                /* ��λת��Ϊ AM_SENSOR_UNIT_MICRO���Դ�ӡ��ʾ6λС�� */
                am_sensor_val_unit_convert(&data[i], 1, AM_SENSOR_UNIT_MICRO);
                am_kprintf("The %s is : %d.%06d %s.\r\n", data_name_string[i],
                                                          (data[i].val)/1000000,
                                                          (data[i].val)%1000000,
                                                          data_unit_string[i]);
            } else {       //��ͨ��������Ч�����ݻ�ȡʧ��
                am_kprintf("The %s get failed!\r\n", data_name_string[i]);
            }
        }
        __alert_bit_info_get(handle);
        am_sensor_as621x_ioctl(handle, AM_SENSOR_AS621X_SM_GET, &sm_bit);
        if (sm_bit == AM_AS621X_SLEEP_MODE) {
            /* ˯��ģʽ�����¿�������ת�� */
            am_sensor_as621x_ioctl(handle, AM_SENSOR_AS621X_SS_SET, (void *)AM_TRUE);
        }
        am_mdelay(1000);
    }
}

/* end of file */
