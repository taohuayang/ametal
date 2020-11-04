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
 * \brief SWDT �ж���ʾ���̣�ͨ��������ӿ�ʵ��
 *
 *  SWDTֻ֧��Ӳ��������MCU����ʱ�������������ȡ���Ź����������趨��Ϣ��ICG0�Ĵ�������
 *  �������Զ���ʼ������
 *
 * - �������裺
 *   1. ����hc32f460_icg.h�� �ĺ�HC32F460_ICG0_SWDT_HARDWARE_START��ֵΪ
 *      ICG_FUNCTION_ON��ʹ��SWDT��Ӳ��������
 *   2. ����hc32f460_icg.h�� �ĺ� HC32F460_ICG0_SWDT_REG_CONFIG������SWDT�������Ŀ��Ʋ�����
 *      ���궨��HC32F460_ICG0_SWDT_ITS����ΪHC32F460_ICG_SWDT_INTERRUPT_REQUEST������
 *      SWDT�����¼�����Ϊ�жϡ�
 *
 * - ʵ������
 *   1. ���ݿ��Ź���ι��ʱ���Ƿ񳬹����õĿ��Ź���ʱʱ�䣬��ӡ"wdt counter underflow !"��
 *   "normal feed dog !"����ʾ��Ϣ��

 *
 * \par Դ����
 * \snippet demo_hc32f460_drv_wdt.c src_hc32f460_drv_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-12
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_drv_swdt
 * \copydoc demo_hc32f460_drv_swdt.c
 */

/** [src_hc32f460_drv_swdt] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460_swdt.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hc32f460_entries.h"

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬�����Ź���ʱʱ��,
 *        ��������Ź��¼���
 */
#define __WDT_FEED_TIME_MS     1200
extern am_hc32f460_swdt_dev_t __g_swdt_dev;


/**
 * \brief �������
 */
void demo_hc32f460_core_drv_swdt_int_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core drv swdt int !\r\n");

    demo_hc32f460_drv_swdt_int_entry(am_hc32f460_swdt_inst_init(), &__g_swdt_dev, __WDT_FEED_TIME_MS);
}
/** [src_hc32f460_drv_swdt] */

/* end of file */
