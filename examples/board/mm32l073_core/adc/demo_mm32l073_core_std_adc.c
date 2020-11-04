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
 * \brief ADC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1 (ADC ͨ�� 1) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_adcc.c src_mm32l073_core_std_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 14-04-18  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_std_adc
 * \copydoc demo_mm32l073_core_std_adc.c
 */

/** [src_std_adc] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_std_adc_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core std adc int!\r\n");

    demo_std_adc_entry(am_mm32l073_adc_inst_init(), 1);  /* ʹ��ͨ��1 ��PIOA_1��*/
}
/** [src_mm32l073_core_std_adc] */
 
/* end of file */
