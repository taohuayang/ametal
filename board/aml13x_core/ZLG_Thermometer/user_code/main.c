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
 * \brief HC32L13x ģ�幤��
 *
 * - ʵ������:
 *   ģ������:��demoΪ����ǹר��demo  ������ʹ����˾���׵�Ӳ������������ǹ���߼����ܣ��������ڶ��ִ��������������л�ֱ���л�VT��RT��������ɣ�
 *						����ʾ���а������ִ��������������д��������������л�ʹ�ã�δ�д��������Լ���ӡ�VT��RT��Ĳ��������
 *					\board\aml13x_core\project_template\infrared_sensor_interpolation\include
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "hc32x3x_pin.h"
#include "hc32_periph_map.h"
#include "ir_thremometer.h"

int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");
	
	ir_thremometer_init();
	
	ir_thremometer_run();
	
	return 0;

}

/* end of file */
