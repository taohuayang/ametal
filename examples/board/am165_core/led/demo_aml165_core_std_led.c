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
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOB_3 ���ƣ�
 *    2. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_LED_ENABLE ����Ϊ 1��
 *       ��������Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *
 * \par Դ����
 * \snippet demo_aml165_core_std_led.c src_aml165_core_std_led
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-18  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_std_led
 * \copydoc demo_aml165_core_std_led.c
 */

/** [src_aml165_core_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 *
 * note: ��SDK��LED�����봮�����Ÿ��ã�Ĭ��δ����LED���ܣ����� aw_prj_config.h �ļ��е�����Ӧ����в���
 *
 */
void demo_aml165_core_std_led_entry (void)
{
    AM_DBG_INFO("demo aml165_core std led!\r\n");

    demo_std_led_entry(LED0);
}
/** [src_aml165_core_std_led] */

/* end of file */
