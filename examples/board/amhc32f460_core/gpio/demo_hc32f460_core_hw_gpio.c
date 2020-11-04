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
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 *
 * \par Դ����
 * \snippet demo_hc32f460_core_hw_gpio.c src_hc32f460_core_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 20-01-16  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_core_hw_gpio
 * \copydoc demo_hc32f460_core_hw_gpio.c
 */

/** [src_hc32f460_core_hw_gpio] */
#include <hc32f460_pin.h>
#include <hw/amhw_hc32f460_gpio.h>
#include "ametal.h"
#include "am_clk.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "demo_hc32f460_core_entries.h"
#include "demo_hc32f460_entries.h"

#define INPUT_PIN  PIOD_3 /**< \brief �������� */
#define OUTPUT_PIN PIOE_6 /**< \brief ������� */

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_gpio_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core hw gpio!\r\n");

    demo_hc32f460_hw_gpio_entry((void*)HC32F460_GPIO, INPUT_PIN, OUTPUT_PIN);
}
/** [src_hc32f460_core_hw_gpio] */

/* end of file */
