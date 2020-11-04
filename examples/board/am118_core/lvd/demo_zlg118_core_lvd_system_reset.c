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
 * \brief LVD ϵͳ��λ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PIOB_7�����ƽ�������õĻ�׼��ѹ����ϵͳ���ڸ�λ״̬�����ٴθ��ڻ�׼��ѹLED��˸һ�Σ�ϵͳ����������
 *   ����������ӡ "Mcu is running!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_lvd_int.c src_zlg118_hw_lvd_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-09  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_lvd_int
 * \copydoc demo_zlg118_hw_lvd_int.c
 */

/** [src_zlg118_hw_lvd_int] */
#include "ametal.h"
#include "am_zlg118.h"
#include "am_gpio.h"
#include "zlg118_pin.h"
#include "am_zlg118_lvd.h"
#include "demo_zlg_entries.h"

/**
 * \brief �������
 */
void demo_zlg118_core_hw_lvd_system_reset_entry (void)
{
    /* ����LVDʱ�� */
    am_clk_enable (CLK_VC_LVD);

    /* PB07 LVD ��������*/
    am_gpio_pin_cfg(PIOB_7, PIOB_7_AIN);

    /* PA04 LVD �����*/
    am_gpio_pin_cfg(PIOA_4, PIOA_4_LVD_OUT | PIOA_4_OUT_PP);

    demo_zlg118_hw_lvd_system_reset_entry((void *)ZLG118_LVD);
}

/* end of file */
