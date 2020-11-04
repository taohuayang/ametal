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
 *   1. �� J14 �� KEY �� PIOC_7 �̽���һ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_7 ���ơ�
 *
 * \par Դ����
 * \snippet demo_zlg237_hw_gpio.c src_zlg237_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-24 zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg237_hw_gpio
 * \copydoc demo_zlg237_hw_gpio.c
 */

/** [src_zlg237_hw_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_zlg237.h"
#include "am_vdebug.h"
#include "amhw_zlg237_gpio.h"
#include "demo_zlg_entries.h"
#include "demo_am237_core_entries.h"

#define INPUT_PIN  PIOC_7 /**< \brief �������� */
#define OUTPUT_PIN PIOC_9 /**< \brief ������� */

/**
 * \brief �������
 */
void demo_zlg237_core_hw_gpio_entry (void)
{

    AM_DBG_INFO("demo am237_core hw gpio!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_IOPC);

    /* ����ϵͳ���õ�ʱ�� */
    am_clk_enable(CLK_AFIO);

    demo_zlg_hw_gpio_entry((amhw_zlg_gpio_t*)ZLG237_GPIO, INPUT_PIN, OUTPUT_PIN);
}
/** [src_zlg237_hw_gpio] */

/* end of file */
