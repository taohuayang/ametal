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
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_gpio.c src_zsn700_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20 zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_gpio
 * \copydoc demo_zsn700_hw_gpio.c
 */

/** [src_zsn700_hw_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_zsn700.h"
#include "am_vdebug.h"
#include "hw/amhw_zsn700_gpio.h"
#include "demo_zlg_entries.h"
#include "demo_am700_core_entries.h"

#define INPUT_PIN  PIOA_8  /**< \brief �������� */
#define OUTPUT_PIN PIOF_6  /**< \brief ������� */

/**
 * \brief �������
 */
void demo_zsn700_core_hw_gpio_entry (void)
{

    AM_DBG_INFO("demo am700_core hw gpio!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_GPIO);

    /* ����ϵͳ���õ�ʱ�� */
    am_clk_enable(CLK_GPIO);

    demo_zsn700_hw_gpio_entry((void *)ZSN700_GPIO0, INPUT_PIN, OUTPUT_PIN);
}
/** [src_zsn700_hw_gpio] */

/* end of file */
