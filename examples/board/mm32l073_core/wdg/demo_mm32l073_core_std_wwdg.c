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
 * \brief WWDG��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __WWDG_FEED_TIME_MS ��ֵ������ __WWDG_TIMEOUT_MS��оƬ��λ��
 *   2. �޸ĺ궨�� __WWDG_FEED_TIME_MS ��ֵ��С�� __WWDG_TIMEOUT_MS�������������С�
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_wwdg.c src_mm32l073_core_std_wwdg
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_std_wwdg
 * \copydoc demo_mm32l073_core_std_wwdg.c
 */

/** [src_mm32l073_core_std_wwdg] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 */
#define __WWDG_TIMEOUT_MS       50

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��WWDG_TIMEOUT_MS��ֵ,
 *        ��������Ź��¼���
 */
#define __WWDG_FEED_TIME_MS     75

/**
 * \brief �������
 */
void demo_mm32l073_core_std_wwdg_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core std wwdg!\r\n");

    demo_std_wdt_entry(am_mm32l073_wwdg_inst_init(),
                       __WWDG_TIMEOUT_MS,
                       __WWDG_FEED_TIME_MS);
}
/** [src_mm32l073_core_std_wwdg] */

/* end of file */
