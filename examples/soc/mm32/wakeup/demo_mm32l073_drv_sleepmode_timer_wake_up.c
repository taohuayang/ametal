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
 * \par Դ����
 * \snippet demo_mm32l073_drv_sleepmode_timer_wake_up.c src_mm32l073_drv_sleepmode_timer_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 18-05-16  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_drv_sleepmode_timer_wake_up
 * \copydoc demo_mm32l073_drv_sleepmode_timer_wake_up.c
 */

/** [src_mm32l073_drv_sleepmode_timer_wake_up] */
#include "ametal.h"
#include "am_timer.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "am_mm32l073_pwr.h"
#include "am_mm32l073_clk.h"
#include "hw/amhw_mm32_uart.h"

/**
 * \brief ��ʱ���ص�����
 */
am_local void __tim_timing_callback (void *p_arg)
{
    ; /* VOID */
}

/**
 * \brief ϵͳʱ��Դ�л�Ϊ LSI
 */
am_local void __sysclk_switch_to_lsi (void)
{

    /* ͣ��ģʽʹ�� LSI ��Ϊϵͳʱ�� */
    amhw_mm32l073_rcc_lsi_enable();

    /* �ȴ� LSI ʱ�Ӿ��� */
    while (amhw_mm32l073_rcc_lsirdy_read() == AM_FALSE);

    /* �л�ʱ�� */
    amhw_mm32l073_rcc_sys_clk_set(AMHW_MM32L073_SYSCLK_LSI);

    /* ʧ�� PLL */
    amhw_mm32l073_rcc_pll_disable();
}

/**
 * \brief ϵͳʱ��Դ�л�Ϊ PLL
 */
am_local void __sysclk_switch_to_pll (void)
{
    amhw_mm32l073_rcc_pll_enable();
    while (amhw_mm32l073_rcc_pllrdy_read() == AM_FALSE);

    /* ϵͳʱ��ѡΪ PLL */
    amhw_mm32l073_rcc_sys_clk_set(AMHW_MM32L073_SYSCLK_PLL);

    /* ������ģʽ�½��� LSI ��Ϊϵͳʱ�� */
    amhw_mm32l073_rcc_lsi_disable();
}

/**
 * \brief �������
 */
void demo_mm32l073_drv_sleepmode_timer_wake_up_entry (am_timer_handle_t timer_handle,
                                                    uint32_t          timer_clk_rate)
{
    am_timer_callback_set(timer_handle, 0, __tim_timing_callback, NULL);

    /* �������� */
    am_mm32l073_wake_up_cfg(AM_MM32L073_PWR_MODE_SLEEP, NULL, NULL);

    while (1) {

        AM_DBG_INFO("enter sleep!\r\n");

        /* �ȴ����ڷ������ */
        while((MM32L073_UART1->csr & AMHW_MM32_UART_TX_COMPLETE_FALG) == AM_FALSE);

        /* ��ϵͳʱ��Դ�л�Ϊ LSI */
        __sysclk_switch_to_lsi();

        /* ���ö�ʱ�ж�����Ϊ 1S����������ʱ�� */
        am_timer_enable(timer_handle, 0, timer_clk_rate * 1);

        /* ����˯��ģʽ */
        am_mm32l073_pwr_mode_into(AM_MM32L073_PWR_MODE_SLEEP);

        /* �رն�ʱ�� */
        am_timer_disable(timer_handle, 0);

        /* ��ϵͳʱ��Դ�л�Ϊ PLL */
        __sysclk_switch_to_pll();

        AM_DBG_INFO("wake_up!\r\n");

        am_mdelay(10);
    }
}
/** [src_mm32l073_drv_sleepmode_timer_wake_up] */

/* end of file */
