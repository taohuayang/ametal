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
 * \brief ��ͨ��ADC�ɼ� ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. am_hwconf_hc32l19x_adc.c�ļ�__g_adc_ioinfo_list[]����ĵ�һ����ЧԪ�����š�Ĭ����PA0
 *   2. am_hwconf_hc32l19x_adc.c�ļ�__g_adc_ioinfo_list[]����ĵ�һ����ЧԪ�����š�Ĭ����PA1
 *   3. am_hwconf_hc32l19x_adc.c�ļ�__g_adc_ioinfo_list[]����ĵ�һ����ЧԪ�����š�Ĭ����PA2
 *   4. am_hwconf_hc32l19x_adc.c�ļ�__g_adc_ioinfo_list[]����ĵ�һ����ЧԪ�����š�Ĭ����PA3
 *  am_hwconf_hc32l19x_adc.c�ļ��޸��豸��Ϣ�У�
 *   5. �ο���ѹѡ�� AMHW_HC32_ADC_REFVOL_AVCC��
 *   6. �ο���ѹ(mv)�� 3300(AVCC)��
 *   7. ����ADCͨ��28�ڲ��¶ȴ�����.(1��ʹ�ܣ�0������)
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ��Ҫ��֤am_hwconf_hc32l19x_adc.c�ļ��еĶ�Ӧͨ�����ŵĳ�ʼ��ע�ʹ򿪣�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l19x_core_std_multichan_adc.c src_hc32l19x_core_std_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-24  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l19x_core_std_multichan_adc
 * \copydoc demo_hc32l19x_core_std_multichan_adc.c
 */

/** [src_std_adc] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_hc32l19x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_aml19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l19x_core_std_multichan_adc_entry (void)
{
    /* ADCͨ��0,1,2,3 */
    int adc_chan[] = {0, 1, 2, 3};

    AM_DBG_INFO("demo aml19x_core std adc int!\r\n");

    demo_std_multichan_adc_entry(am_hc32_adc_inst_init(),
                                 adc_chan,
                                 sizeof(adc_chan) / sizeof(adc_chan[0]));

}
/** [src_std_adc] */

/* end of file */
