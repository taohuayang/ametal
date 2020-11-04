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
 * \brief MiniPort-View + MiniPort-595 + MiniPort-KEY ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ����ֱ���� aml165-Core �� MiniPort �����ӣ�
 *   2. �� MiniPort-View ������ MiniPort-595 �ӿ������ӣ�
 *   3. �� MiniPort-KEY �� MiniPort-View ���ӡ�
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������ŵĶ����ƣ�
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \note
 *    ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��
 *    AM_CFG_KEY_ENABLE �� AM_CFG_SOFTIMER_ENABLE ����Ϊ 1������Щ��
 *    �Ѿ�Ĭ������Ϊ 1�� �û������ٴ����á�
 *
 * \par Դ����
 * \snippet demo_aml165_core_miniport_hc595_digitron_key.c src_aml165_core_miniport_hc595_digitron_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_miniport_hc595_digitron_key
 * \copydoc demo_aml165_core_miniport_hc595_digitron_key.c
 */

/** [src_aml165_core_miniport_hc595_digitron_key] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_miniport_hc595_digitron_key_entry (void)
{
    AM_DBG_INFO("demo aml165_core miniport hc595 digitron key!\r\n");

    am_miniport_view_key_595_inst_init();

    demo_std_key_digitron_entry(0);
}
/** [src_aml165_core_miniport_hc595_digitron_key] */

/* end of file */
