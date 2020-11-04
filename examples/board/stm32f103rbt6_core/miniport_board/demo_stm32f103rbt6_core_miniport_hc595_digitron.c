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
 * \brief MiniPort-View + MiniPort-595 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. ��ȷ��am_hwconf_stm32f103rbt6_spi_int��c��spi2�豸��Ϣ�ṹ����cs_delay����ֵΪ0��
 *   2. ��ȷ��am_hwconf_stm32f103rbt6_spi_int��c��spi2�豸��Ϣ�ṹ����cs_delay����ֵΪ0��
 *   3. �Ƚ� MiniPort-595 ����ֱ���� STM32F103RBT6 �� MiniPort �����ӣ�
 *   4. �� MiniPort-View ������ MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ���Կ�����ֵ 0 ~ 59 �����������
 *   2. ����С�� 30 ʱ����λ��˸������ 30 ʱʮλ��˸��
 *
 * \par Դ����
 * \snippet demo_miniport_hc595_digitron.c src_miniport_hc595_digitron
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_digitron
 * \copydoc demo_miniport_hc595_digitron.c
 */

/** [src_miniport_hc595_digitron] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_arm_nvic.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "am_digitron_disp.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_miniport_hc595_digitron_entry (void)
{
    AM_DBG_INFO("demo stm32f103rbt6_core miniport hc595 digitron!\r\n");

    am_miniport_view_595_inst_init();

    demo_std_digitron_60s_counting_entry(0);
}
/** [src_miniport_hc595_digitron] */

/* end of file */
