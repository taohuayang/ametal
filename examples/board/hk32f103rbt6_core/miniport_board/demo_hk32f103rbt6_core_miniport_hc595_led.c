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
 * \brief MiniPort-LED + MiniPort-595 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. ��ȷ��am_hwconf_hk32f103rbt6_spi_int��c��spi2�豸��Ϣ�ṹ����cs_delay����ֵΪ0��
 *   2. �Ƚ� MiniPort-595 ����ֱ���� HK32F103RBT6 �� MiniPort �����ӣ�
 *   3. �� MiniPort-LED ������ MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ��ˮ������
 *
 * \par Դ����
 * \snippet demo_miniport_hc595_led.c src_miniport_hc595_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_led
 * \copydoc demo_miniport_hc595_led.c
 */

/** [src_miniport_hc595_led] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hk32f103rbt6_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_hk32f103rbt6_core_miniport_hc595_led_entry (void)
{
    AM_DBG_INFO("demo hk32f103rbt6_core miniport hc595 led!\r\n");

    demo_std_hc595_led_entry(am_miniport_595_inst_init());
}
/** [src_miniport_hc595_led] */

/* end of file */
