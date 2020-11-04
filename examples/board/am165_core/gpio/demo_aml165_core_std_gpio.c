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
 * - �������裺
 *   1. �� J14 �� KEY �� PIOA_13 �̽���һ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOB_3 ���ơ�
 *    ��������SWD���Ÿ��ã�������ε�SWD�����߷�����������
 *
 * \par Դ����
 * \snippet demo_aml165_core_std_gpio.c src_aml165_core_std_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_std_gpio
 * \copydoc demo_aml165_core_std_gpio.c
 */

/** [src_aml165_core_std_gpio] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

#define INPUT_PIN  PIOA_13 /**< \brief �������� */
#define OUTPUT_PIN PIOB_3 /**< \brief ������� */

/**
 * \brief �������
 */
void demo_aml165_core_std_gpio_entry (void)
{
    AM_DBG_INFO("demo aml165_core std gpio!\r\n");

    demo_std_gpio_entry(INPUT_PIN, OUTPUT_PIN);
}
/** [src_aml165_core_std_gpio] */

/* end of file */
