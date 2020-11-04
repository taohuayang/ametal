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
 * \brief ��ѹ�¶ȴ����� MPL3115A2 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ��ѹ/���� �� �¶ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_std_mpl3115a2.c src_std_mpl3115a2
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-11  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_mpl3115a2
 * \copydoc demo_std_mpl3115a2.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_mpl3115a2.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_mpl3115a2_entry (am_sensor_handle_t handle)
{
    /* MPL3115A2��������ͨ��ID�о� */
    const int       id[2] = {AM_MPL3115A2_CHAN_1, AM_MPL3115A2_CHAN_2};

    /* ��������ͨ�����ݵĻ��� */
    am_sensor_val_t data[2];

    int             i;

    /*
     * �г�����ͨ������ѹ/���� �� �¶ȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {
                                    #if(__MPL3115A2_MODE == __MPL3115A2_PRE_MODE) /* ��ѹ */
                                        "pressure", 
                                    #elif(__MPL3115A2_MODE == __MPL3115A2_ALT_MODE) /* ���� */
                                        "altitude",
                                    #endif
                                        "temperature"};
    const char *data_unit_string[] = {
                                    #if(__MPL3115A2_MODE == __MPL3115A2_PRE_MODE) /* ��ѹ */
                                        "KPa",
                                    #elif(__MPL3115A2_MODE == __MPL3115A2_ALT_MODE) /* ���� */
                                        "Meters",
                                    #endif
                                        "��"};

    am_sensor_enable(handle, id, 2, data);

    while(1) {
        am_sensor_data_get(handle, id, 2, data);
        for(i=0; i<2; i++) {
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
        am_kprintf("\r\n");
        am_mdelay(1000);
    }
}

/* end of file */
