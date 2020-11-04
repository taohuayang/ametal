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
 * \brief MiniPort-KEY ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �� MiniPort-KEY ����ֱ���� AM118BLE �� MiniPort�ӿ������ӡ�
 *
 * - ʵ������
 *   1. �������˵��Դ��ڣ����°���ʱ�����ӡ����ǰ�İ�����Ϣ��
 *   2. �������£�ͬʱ�� AM118BLE ���ϵ�LED�Ʒ�Ӧ����ǰ�İ�����ţ�
 *      ��Ҫ�̽� J9 �� J10��
 *
 *           ------------------------------------
 *            ���°���        | LED1״̬ |  LED0״̬
 *           -------------|---------|------------
 *             KEY0       |    Ϩ��   |   Ϩ��
 *             KEY1       |    Ϩ��   |   ����
 *             KEY2       |    ����   |   Ϩ��
 *             KEY3       |    ����   |   ����
 *
 * \note
 *    ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��
 *    AM_CFG_KEY_ENABLE �� AM_CFG_SOFTIMER_ENABLE ����Ϊ 1������Щ��
 *    �Ѿ�Ĭ������Ϊ 1�� �û������ٴ����á�
 *
 * \par Դ����
 * \snippet demo_miniport_key.c src_miniport_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_key
 * \copydoc demo_miniport_key.c
 */

/** [src_miniport_key] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_event_category_input.h"
#include "am_event_input_key.h"
#include "am_hc32f19x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_miniport_key_entry (void)
{
    AM_DBG_INFO("demo amf19x_core miniport key!\r\n");

    am_miniport_key_inst_init();

    demo_std_4key_entry();
}
/** [src_miniport_key] */

/* end of file */
