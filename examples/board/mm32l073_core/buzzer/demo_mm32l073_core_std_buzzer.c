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
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� J7 ����ñ��PIOB_8 ���Ʒ�������
 *
 * - ʵ������
 *   1. �������� 0.5s ��ʱ�������С�
 *
 * \note
 *    ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_BUZZER_ENABLE 
 *��    ����Ϊ 1�����ú��Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_buzzer.c src_mm32l073_core_std_buzzer
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-20  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_std_buzzer
 * \copydoc demo_mm32l073_core_std_buzzer.c
 */

/** [src_mm32l073_core_std_buzzer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_std_buzzer_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core std buzzer!\r\n");

    demo_std_buzzer_entry();
}
/** [src_mm32l073_core_std_buzzer] */

/* end of file */
