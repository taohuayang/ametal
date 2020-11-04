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
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ˯��ģʽ���̣�ʹ�ö�ʱ�����ڻ��ѣ�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. �������"enter sleep!"��ϵͳʱ��Դ�л�Ϊ LSI��������ʱ����
 *      ����˯��ģʽ��J-Link ���ԶϿ�����ʱ�û��ɲ���˯��ģʽ�Ĺ��ģ�
 *   2. �ȴ���ʱʱ�䵽��MCU �����ѣ��������"wake_up!"��Ȼ�����½���
 *      ˯��ģʽ��
 *
 * \note
 *   ���� TIM14 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã��ᶨ�ڲ����жϵ��»��ѣ� ���Ա�����
 *   ֮ǰӦ�� am_prj_config.h �еĺ� AM_CFG_SYSTEM_TICK_ENABLE��
 *   AM_CFG_SOFTIMER_ENABLE ��   AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_drv_sleepmode_timer_wake_up.c src_mm32l073_core_drv_sleepmode_timer_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 18-05-16  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_drv_sleepmode_timer_wake_up
 * \copydoc demo_mm32l073_core_drv_sleepmode_timer_wake_up.c
 */

/** [src_mm32l073_core_drv_sleepmode_timer_wake_up] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073_inst_init.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l073_core_entries.h"

/** \brief LSI ʱ��Ƶ�� */
#define    __LSI_CLK    (40000UL)

/**
 * \brief �������
 */
void demo_mm32l073_core_drv_sleepmode_timer_wake_up_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core drv sleepmode timer wake up!\r\n");

    /* ��ʼ�� PWR */
    am_mm32l073_pwr_inst_init();

    demo_mm32l073_drv_sleepmode_timer_wake_up_entry(am_mm32l073_tim14_timing_inst_init(),
                                                  __LSI_CLK);
}
/** [src_mm32l073_core_drv_sleepmode_timer_wake_up] */

/* end of file */
