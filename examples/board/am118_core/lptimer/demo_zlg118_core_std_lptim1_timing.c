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
 * \brief LPTIM1 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 5Hz ��Ƶ�ʷ�ת��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *
 * \note
 *   1.��am_hwconf_zlg118_lptim.c�ļ��У�__g_lptim1_timing_devinfo�豸��Ϣ�ṹ��ѡ��
 *             AMHW_ZLG118_LPTIM_FUNCTION_TIMER  ----------- ��ʱ��ģʽ
 *             AMHW_ZLG118_LPTIM_MODE_RELOAD     ----------- �Զ�����ģʽ
 *             AM_FALSE                          ----------- �ſعر�
 *             AM_TRUE                           ----------- TOG��TOGN���ʹ�ܴ�
 *
 * \par Դ����
 * \snippet demo_zlg118_std_lptim1_timing.c src_zlg118_std_lptim1_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_std_lptim1_timing
 * \copydoc demo_zlg118_std_lptim1_timing.c
 */

/** [src_zlg118_std_lptim1_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zlg118_inst_init.h"
#include "demo_am118_core_entries.h"

/**
 * \brief �������
 */
void demo_zlg118_core_std_lptim1_timing_entry (void)
{
    AM_DBG_INFO("demo am118_core std lptim1 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg118_lptim1_timing_inst_init(), 0);
}
/** [src_zlg118_std_lptim1_timing] */

/* end of file */
