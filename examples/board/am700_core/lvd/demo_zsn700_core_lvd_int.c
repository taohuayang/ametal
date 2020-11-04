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
 * \brief LVD �ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PIOB_7�����ѹ�Ӹ��ڻ�׼��ѹ��Ϊ���ڻ�׼��ѹ�������LVD�жϡ�
 *   ���ڴ�ӡ "LVD interrupt"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zsn700_core_lvd_int.c src_zsn700_core_lvd_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-09  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_core_lvd_int
 * \copydoc demo_zsn700_core_lvd_int.c
 */

/** [src_zsn700_hw_lvd_int] */
#include "ametal.h"
#include "am_zsn700.h"
#include "am_gpio.h"
#include "zsn700_pin.h"
#include "am_zsn700_lvd.h"
#include "demo_zlg_entries.h"

/**
 * \brief �û��ص�����
 */
static void __zsn700_lvd_callback (void *data)
{
    am_kprintf ("LVD interrupt!\r\n");
}

/**
 * \brief �������
 */
void demo_zsn700_core_hw_lvd_int_entry (void)
{
    AM_DBG_INFO("Test start: demo-lvd-intterput !\r\n");

    /* ����LVDʱ�� */
    am_clk_enable (CLK_VC_LVD);

    /* PB07 LVD ��������*/
    am_gpio_pin_cfg(PIOB_7, PIOB_7_AIN);

    /* PA04 LVD �����*/
    am_gpio_pin_cfg(PIOA_4, PIOA_4_LVD_OUT | PIOA_4_OUT_PP);

    demo_zsn700_hw_lvd_int_entry((void *)ZSN700_LVD, __zsn700_lvd_callback);
}

/* end of file */
