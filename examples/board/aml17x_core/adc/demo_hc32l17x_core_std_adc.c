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
 *   1. am_hwconf_hc32l17x_adc.c�ļ�__g_adc_ioinfo_list[]����ĵ�һ����ЧԪ�����š�Ĭ����PA0
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l17x_std_adc.c src_std_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l17x_std_adc
 * \copydoc demo_hc32l17x_std_adc.c
 */

/** [src_std_adc] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_hc32l17x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_aml17x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l17x_core_std_adc_entry (void)
{
    AM_DBG_INFO("demo aml17x_core std adc int!\r\n");

    demo_std_adc_entry(am_hc32_adc_inst_init(), 0);

}
/** [src_std_adc] */

/* end of file */
