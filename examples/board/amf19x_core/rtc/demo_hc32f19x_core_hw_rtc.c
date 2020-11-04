/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2020 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ1�뷢��һ�������жϣ����ڲ���ӡ����ǰʱ����Ϣ��
 *   2. ��ָ��ʱ����������жϣ���ӡһ��"alarm clock int!"��ʾ��Ϣ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f19x_hw_rtc.c src_hc32f19x_hw_rtc
 *
 * \internal
 * \par History
 * - 1.00 20-05-14  licl, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f19x_hw_rtc
 * \copydoc demo_hc32f19x_hw_rtc.c
 */

/** [src_hc32f19x_hw_rtc] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_vdebug.h"
#include "demo_hc32_entries.h"
#include "am_hc32f19x_inst_init.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_hw_rtc_entry (void)
{
    AM_DBG_INFO("demo amf19x_core hw rtc!\r\n");

    demo_hc32_hw_rtc_entry((void *)HC32_RTC);
}
/** [src_hc32f19x_hw_rtc] */

/* end of file */
