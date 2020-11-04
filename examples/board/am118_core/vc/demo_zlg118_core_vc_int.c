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
 * \brief VC�жϴ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PA07��VCC��GND��ӦPA06����ߵ�ƽ��͵�ƽ����PA07 ��ѹ���� PC00 (��DAC0_out ���2400mv)
 *   �����жϣ����ڴ�ӡ�� "vc trigger interrupt !"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_vc_int.c src_zlg118_hw_vc_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-30  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_vc_int
 * \copydoc demo_zlg118_hw_vc_int.c
 */

/** [src_zlg118_hw_vc_int] */
#include "ametal.h"
#include "am_zlg118.h"
#include "am_gpio.h"
#include "zlg118_pin.h"
#include "am_zlg118_vc.h"
#include "demo_zlg_entries.h"

/**
 *  \brief �û������жϴ����ص�����
 */
static void vc_tri_callback (void *p_cookie)
{
    am_kprintf ("TSET:vc trigger interrupt !\r\n");
}

/* DAC��ѹֵ���� */
static uint16_t mv_val = 2400;

/**
 * \brief �������
 */
void demo_zlg118_core_hw_vc_int_entry (void)
{

    /* ����PIOA_4ΪDAC0_OUT���� */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AOUT);

    /* ����DACʱ�� */
    am_clk_enable(CLK_DAC);

    /* ����PIOA_6ΪVC_OUT���� */
    am_gpio_pin_cfg(PIOA_6, PIOA_6_VC0_OUT | PIOA_6_OUT_PP);

    /* ����PIOC_0ΪVC0 P������ */
    am_gpio_pin_cfg(PIOC_0, PIOC_0_AIN);

    /* ����PIOC_0ΪVC0 P������ */
    am_gpio_pin_cfg(PIOA_7, PIOA_7_AIN);

    /* ����VCʱ�� */
    am_clk_enable(CLK_VC_LVD);

    /* ����BGRʱ�� */
    am_clk_enable(CLK_ADC_BGR);

    demo_zlg118_hw_vc_int_entry((void *)ZLG118_VC_BASE,
                                vc_tri_callback,
                                ZLG118_DAC,
                                mv_val);
}

/* end of file */
