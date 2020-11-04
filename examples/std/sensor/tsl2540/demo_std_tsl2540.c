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
 * \brief �����⴫���� TSL2540 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ�ɼ���ͺ�����ֵ
 *
 * \par Դ����
 * \snippet demo_std_tsl2540.c src_std_tsl2540
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_tsl2540
 * \copydoc demo_std_tsl2540.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_tsl2540.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_tsl2540_entry (am_sensor_handle_t handle)
{
    /* TSL2540�ṩ������ͨ��ID�о� */
    const int id[2] = {AM_TSL2540_CHAN_1, AM_TSL2540_CHAN_2};

    /* ��������ͨ�����ݵĻ��� */
    am_sensor_val_t data[2];

    int i;

    /*
     * �г�����ͨ�����ɼ���ͺ���⣩���ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"visible", "ir"};
    const char *data_unit_string[] = {" ", " "};

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
