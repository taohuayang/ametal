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
 * \brief IWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __IWDG_FEED_TIME_MS ��ֵ������ 1500ms(���� 5ms ���)��оƬ��λ��
 *   2. �޸ĺ궨�� __IWDG_FEED_TIME_MS ��ֵ��С�� 1500ms(���� 5ms ���)�������������С�
 *
 * \par Դ����
 * \snippet demo_aml165_core_hw_iwdg.c src_aml165_core_hw_iwdg
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_hw_iwdg
 * \copydoc demo_aml165_core_hw_iwdg.c
 */

/** [src_aml165_core_hw_iwdg] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "hw/amhw_zml165_rcc.h"
#include "demo_zlg_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 *
 * \note ��Ϊ���Ź��ڲ�ʱ��WDTOSC����������__IWDG_TIMEOUT_MS��Ӧ��ʵ��ʱ��
 *       ������
 */
#define __IWDG_TIMEOUT_MS       1500

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��__IWDG_TIMEOUT_MS��ֵ������5ms���ϣ�,
 *        ��������Ź��¼���
 */
#define __IWDG_FEED_TIME_MS     1000

/**
 * \brief �������
 */
void demo_aml165_core_hw_iwdg_entry (void)
{
    AM_DBG_INFO("demo aml165_core hw iwdg!\r\n");

    amhw_zml165_rcc_lsi_enable();

    demo_zlg_hw_iwdg_entry(ZML165_IWDG,
                           __IWDG_TIMEOUT_MS,
                           __IWDG_FEED_TIME_MS);
}
/** [src_aml165_core_hw_iwdg] */

/* end of file */
