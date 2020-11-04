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
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOB_1 ���ƣ�
 *    2. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_LED_ENABLE ����Ϊ 1��
 *       ��������Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_led.c src_mm32l073_core_std_led
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-18  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_std_led
 * \copydoc demo_mm32l073_core_std_led.c
 */

/** [src_mm32l073_core_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_std_led_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core std led!\r\n");

    demo_std_led_entry(LED0);
}
/** [src_mm32l073_core_std_led] */

/* end of file */
