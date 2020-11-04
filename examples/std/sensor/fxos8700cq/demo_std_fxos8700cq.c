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
 * \brief ���ᴫ���� FXOS8700CQ ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ���ٶȺʹŸ�Ӧǿ�ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_std_fxos8700cq.c src_std_fxos8700cq
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_fxos8700cq
 * \copydoc demo_std_fxos8700cq.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_fxos8700cq.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_fxos8700cq_entry (am_sensor_handle_t handle)
{
    uint8_t i = 0;

    /* FXOS8700CQ�ṩ������ͨ��ID�о� */
    const int id[6] = {AM_FXOS8700CQ_CHAN_1, AM_FXOS8700CQ_CHAN_2,
                       AM_FXOS8700CQ_CHAN_3, AM_FXOS8700CQ_CHAN_4,
                       AM_FXOS8700CQ_CHAN_5, AM_FXOS8700CQ_CHAN_6};

    /* ��������ͨ�����ݵĻ��� */
    am_sensor_val_t data[6];

    /*
     * �г�����ͨ�������ٶȺʹŸ�Ӧǿ�ȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"ACC_X", "ACC_Y", "ACC_Z", "MAG_X", "MAG_Y", "MAG_Z"};
    const char *data_unit_string[] = {"mg", "mg", "mg", "gauss", "gauss", "gauss"};
    
    am_sensor_enable(handle, id, 6, data);

    while(1) {
        am_sensor_data_get(handle, id, 6, data);

        for (i = 0; i < 6; i++) {
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
