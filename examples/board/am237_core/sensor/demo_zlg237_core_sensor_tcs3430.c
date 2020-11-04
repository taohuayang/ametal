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
 * \brief ������/��ɫ������ TCS3430 ���̣�ͨ����׼�ӿ�ʵ��(ͨ����ѯ��ʽ��ȡ����)
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡͨ��ֵ
 *
 * \par Դ����
 * \snippet demo_zlg237_core_sensor_tcs3430.c src_zlg237_core_sensor_tcs3430
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_delay.h"
#include "am_zlg237.h"
#include "am_sensor.h"
#include "am_hwconf_sensor_tcs3430.h"
#include "demo_std_entries.h"
#include "demo_am237_core_entries.h"

/* 1.8Vʹ�����ţ����ڿ�����ͬ�ӻ���ַ��ͨ�ϵ� */
#define PIN_1P8_OUT1    PIOC_4
#define PIN_1P8_OUT2    PIOC_5

/**
 * \brief �������������
 */
void demo_zlg237_core_sensor_tcs3430_entry (void)
{
    /* ʹ�� 1.8V_OUT2 ���� */
    am_gpio_pin_cfg(PIN_1P8_OUT2, AM_GPIO_OUTPUT_INIT_HIGH);

    /* �ȴ������ȶ� */
    am_mdelay(2);

    am_sensor_handle_t handle = am_sensor_tcs3430_inst_init();

    demo_std_tcs3430_entry(handle);
}


/* end of file */
