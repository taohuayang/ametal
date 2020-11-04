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
 *   1. �� J14 �� KEY �� PIOA_8 �̽���һ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOB_1 ���ơ�
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_hw_gpio.c src_mm32l073_core_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_hw_gpio
 * \copydoc demo_mm32l073_core_hw_gpio.c
 */

/** [src_mm32l073_core_hw_gpio] */
#include "ametal.h"
#include "am_clk.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l073_core_entries.h"

#define INPUT_PIN  PIOA_8 /**< \brief �������� */
#define OUTPUT_PIN PIOB_1 /**< \brief ������� */

/**
 * \brief �������
 */
void demo_mm32l073_core_hw_gpio_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core hw gpio!\r\n");

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_GPIOA);
    am_clk_enable(CLK_SYSCFG);

    demo_mm32_hw_gpio_entry(MM32L073_GPIO, INPUT_PIN, OUTPUT_PIN);
}
/** [src_mm32l073_core_hw_gpio] */

/* end of file */
