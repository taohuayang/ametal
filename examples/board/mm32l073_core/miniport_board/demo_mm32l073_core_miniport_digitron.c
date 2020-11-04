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
 * \brief MiniPort-View ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �� MiniPort-View ����ֱ���� AM116-Core �� MiniPort �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ���Կ�����ֵ 0 ~ 59 �����������
 *   2. ����С��30ʱ����λ��˸������30ʱʮλ��˸��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_miniport_digitron.c src_mm32l073_core_miniport_digitron
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_miniport_digitron
 * \copydoc demo_mm32l073_core_miniport_digitron.c
 */

/** [src_mm32l073_core_miniport_digitron] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief ������� 
 */
void demo_mm32l073_core_miniport_digitron_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core miniport digitron!\r\n");

    am_miniport_view_inst_init();

    demo_std_digitron_60s_counting_entry(0);
}
/** [src_mm32l073_core_miniport_digitron] */

/* end of file */
