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
 * \brief ������/��ɫ������ TCS3430 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡͨ��ֵ
 *
 * \par Դ����
 * \snippet demo_std_tcs3430.c src_std_tcs3430
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_tcs3430
 * \copydoc demo_std_tcs3430.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_tcs3430.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_tcs3430_entry (am_sensor_handle_t handle)
{
    /* TCS3430�ṩ������ͨ��ID�о� */
    const int id[4] = {AM_TCS3430_CHAN_1, AM_TCS3430_CHAN_2,
                       AM_TCS3430_CHAN_3, AM_TCS3430_CHAN_4};

    /* �����ĸ�ͨ�����ݵĻ��� */
    am_sensor_val_t data[4];

    int i;

    /*
     * �г��ĸ�ͨ����CH0~CH3�����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"CH0", "CH1", "CH2", "CH3"};
    const char *data_unit_string[] = {" ", " ", " ", " "};

    am_sensor_enable(handle, id, 4, data);

    while(1) {
        am_sensor_data_get(handle, id, 4, data);
        for(i = 0; i < 4; i++) {
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
