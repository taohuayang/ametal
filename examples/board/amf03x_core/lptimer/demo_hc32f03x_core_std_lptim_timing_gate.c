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
 * \brief LPTIM0��ʱ��TIMING���ܣ�LPTIM0��ʱ�����ⲿ�ź��½��ؽ��м�����ͨ����׼�ӿ�ʵ��
 *
 * \����
 *   1.��am_hwconf_hc32f03x_lptim.c�ļ��У�__g_lptim0_timing_devinfo�豸��Ϣ�ṹ��ѡ��
 *             AMHW_HC32_LPTIM_FUNCTION_TIMER  ----------- ��ʱ��ģʽ
 *             AMHW_HC32_LPTIM_MODE_RELOAD     ----------- �Զ�����ģʽ
 *             AM_FALSE                          ----------- �ſعر�
 *             AM_TRUE                           ----------- TOG��TOGN���ʹ�ܴ�
 *   2.��am_hwconf_hc32f03x_lptim.c�ļ��У�__g_lptim1_timing_devinfo�豸��Ϣ�ṹ��ѡ��
 *             AMHW_HC32_LPTIM_FUNCTION_COUNTER----------- ������ģʽ
 *             AMHW_HC32_LPTIM_MODE_RELOAD     ----------- �Զ�����ģʽ
 *             AM_FALSE                          ----------- �ſعر�
 *             AM_TRUE                           ----------- TOG��TOGN���ʹ�ܴ�
 *   3.��PIOD_6��LPTIM1_ETR����PIOC_1��LPTIM0_TOG�����ӡ�
 *
 *
 * - ʵ������
 *   1.PIOC_1��LPTIM0_TOG����PIOC_2��LPTIM0_TOGN��������ࡢƵ��Ϊ500kHz�ķ�����
 *   2.LED0��5Hz��Ƶ�ʷ�ת��
 *
 * \note���ڶ�ʱ����ʱ1us����ȷ��Ե�ʣ����ܴ��ڽϴ�������PIOC_1��LED0��˸��Ƶ�ʹ�ϵ�̶�Ϊ100000:1
 *
 * \par Դ����
 * \snippet demo_hc32f03x_std_lptim_timing.c src_hc32f03x_std_lptim_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f03x_std_lptim_timing
 * \copydoc demo_hc32f03x_std_lptim_timing.c
 */

/** [src_hc32f03x_std_lptim_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_timer.h"
#include "demo_std_entries.h"
#include "am_hc32f03x_inst_init.h"
#include "demo_amf03x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f03x_core_std_lptim_timing_gate_entry (void)
{
    am_timer_handle_t  handle = am_hc32_lptim0_timing_inst_init();
    
    AM_DBG_INFO("demo amf03x_core std lptim timing gate!\r\n");

    /* ���ûص����� */
    am_timer_callback_set(handle, 0, NULL, NULL);

    /* ���ö�ʱʱ��Ϊ1us,TOG��TOGN���Ƶ������ʱ��Ϊ1*2=2us����500KHz */
    am_timer_enable_us(handle, 0, 1);

    demo_std_timer_timing_entry(am_hc32_lptim0_timing_inst_init(), 0);
}
/** [src_hc32f03x_std_lptim_timing] */

/* end of file */
