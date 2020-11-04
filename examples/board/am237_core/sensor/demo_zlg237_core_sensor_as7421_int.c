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
 * \brief �߹��״����� AS7421 ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. ���ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
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
#include "am_hwconf_sensor_as7421.h"
#include "demo_std_entries.h"
#include "demo_am237_core_entries.h"

/* 3.3V_LED_EN */
#define PIN_3P3_LED_EN      PIOA_8

/**
 * \brief �������������
 */
void demo_zlg237_core_sensor_as7421_int_entry (void)
{
    /* ʹ�� 3.3V_LED_EN ���� */
    am_gpio_pin_cfg(PIN_3P3_LED_EN, AM_GPIO_OUTPUT_INIT_HIGH);

    /* �ȴ������ȶ� */
    am_mdelay(2);

    am_sensor_handle_t handle = am_sensor_as7421_inst_init();

    demo_std_as7421_int_entry(handle);
}


/* end of file */
