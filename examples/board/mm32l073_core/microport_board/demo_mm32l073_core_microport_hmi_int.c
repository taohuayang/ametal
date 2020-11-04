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
 * \brief MicroPort RTC(PCF85063) ���̣�ͨ�� PCF85063 оƬʵ��
 *        HMI�Ĺ��ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort RTC ������ӵ� MM32L073-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ���ڽ�ÿ30���ӡʱ����Ϣ��
 *   2. LEDÿ30�뷭תһ��״̬��
 *
 * \note
 *   1.����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *   2.PCF85063���ж�INT����Ϊ PIOA_15
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_microport_hmi_int.c src_mm32l073_core_microport_hmi_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_microport_hmi_int
 * \copydoc demo_mm32l073_core_microport_hmi_int.c
 */

/** [src_mm32l073_core_microport_hmi_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief MicroPort HMI ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_mm32l073_core_microport_hmi_int_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core microport hmi int!\r\n");

    demo_std_hmi_int_entry(am_microport_rtc_inst_init());
}
/** [src_mm32l073_core_microport_hmi_int] */

/* end of file */
