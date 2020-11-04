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
 * \brief MiniPort-LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �� MiniPort-LED ����ֱ���� AM118BLE �� MiniPort�ӿ������ӡ�
 *
 * - ʵ������
 *   1. ��ˮ������
 *
 * - ע�⣺
 *   1. Ҫʹ�ø����̣���Ҫ�� am_prj_config.h ���潫 AM_CFG_LED_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_miniport_led.c src_miniport_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_led
 * \copydoc demo_miniport_led.c
 */

/** [src_miniport_led] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32l13x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_aml13x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l13x_core_miniport_led_entry (void)
{
    AM_DBG_INFO("demo aml13x_core miniport led!\r\n");

    am_miniport_led_inst_init();

    demo_std_led_water_light_entry (2, 8);
}
/** [src_miniport_led] */

/* end of file */
