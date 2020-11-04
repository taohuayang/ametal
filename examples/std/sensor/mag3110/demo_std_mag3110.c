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
 * \brief ����Ŵ����� MAG3110 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ����Ŵ��������¶ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_std_mag3110.c src_std_mag3110
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-03  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_mag3110
 * \copydoc demo_std_mag3110.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_mag3110.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_mag3110_entry (am_sensor_handle_t handle)
{
    uint8_t i = 0;
    
    /* MAG3110�ṩ������ͨ��ID�о� */
    const int id[4] = {AM_MAG3110_CHAN_1, AM_MAG3110_CHAN_2,
                       AM_MAG3110_CHAN_3, AM_MAG3110_CHAN_4};

    /* �����ĸ�ͨ�����ݵĻ��� */
    am_sensor_val_t data[4];

    /*
     * �г��ĸ�ͨ�����Ŵ��������¶ȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"MAG_X", "MAG_Y", "MAG_Z", "temperature"};
    const char *data_unit_string[] = {"gauss", "gauss", "gauss", "��"};

    am_sensor_enable(handle, id, 4, data);

    while(1) {
        am_sensor_data_get(handle, id, 4, data);

        for (i = 0; i < 4; i++) {
            if (AM_SENSOR_VAL_IS_VALID(data[i])) { /* ��ͨ��������Ч����������ʹ�� */

                /* ��λת��Ϊ AM_SENSOR_UNIT_MICRO���Դ�ӡ��ʾ6λС�� */
                am_sensor_val_unit_convert(&data[i], 1, AM_SENSOR_UNIT_MICRO);
                am_kprintf("The %s is : %d.%06d %s.\r\n", 
                                    data_name_string[i],
                                   (data[i].val)/1000000,
                                   (uint32_t)(data[i].val)%1000000,
                                    data_unit_string[i]);
            } else {       //��ͨ��������Ч�����ݻ�ȡʧ��
                am_kprintf("The %s get failed!\r\n", data_name_string[i]);
            }
        }
        am_kprintf("\r\n");
        am_mdelay(1000);
    }
}

/* end of file */
