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
 * \brief ����ʱ�䴫���� TMF8801 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ������¶ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_std_tmf8801.c src_std_tmf8801
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10 yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_tmf8801
 * \copydoc demo_std_tmf8801.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_tmf8801.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_tmf8801_entry (am_sensor_handle_t handle)
{
    /* TMF8801�ṩ������ͨ��ID�о� */
    const int id[2] = {AM_TMF8801_CHAN_1, AM_TMF8801_CHAN_2};

    /* ��������ͨ�����ݵĻ��� */
    am_sensor_val_t data[2];

    int i;

    /*
     * �г�����ͨ����������¶ȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"distance", "temperature"};
    const char *data_unit_string[] = {"mm", "��"};

    am_sensor_enable(handle, id, 2, data);

    while(1) {
        am_sensor_data_get(handle, id, 2, data);
        for(i = 0; i < 2; i++) {
            if (AM_SENSOR_VAL_IS_VALID(data[i])) { /* ��ͨ��������Ч����������ʹ�� */
                am_kprintf("The %s is : %d %s.\r\n", data_name_string[i],
                                                          data[i].val,
                                                          data_unit_string[i]);
            } else { //��ͨ��������Ч�����ݻ�ȡʧ��
                am_kprintf("The %s get failed!\r\n", data_name_string[i]);
            }
        }
        am_mdelay(1000);
    }
}

/* end of file */
