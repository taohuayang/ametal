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
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsn700_std_gpio.c src_zsn700_std_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_std_gpio
 * \copydoc demo_zsn700_std_gpio.c
 */

/** [src_zsn700_std_gpio] */
#include "am_vdebug.h"
#include "am_zsn700.h"
#include "am_board.h"
#include "demo_std_entries.h"
#include "demo_am700_core_entries.h"

#define INPUT_PIN  PIOA_8  /**< \brief �������� */
#define OUTPUT_PIN PIOF_6  /**< \brief ��LED���� */

/**
 * \brief �������
 */
void demo_zsn700_core_std_gpio_entry (void)
{
    AM_DBG_INFO("demo am700_core std gpio!\r\n");

    demo_std_gpio_entry(INPUT_PIN, OUTPUT_PIN);
}
/** [src_zsn700_std_gpio] */

/* end of file */
