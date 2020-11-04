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
 * \brief ˯��ģʽ���̣�ʹ�ö�ʱ�����ڻ��ѣ�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �������ȴ� 5 ��󣬿�ʼ�͹��Ĳ��ԣ����ʱ���û��ɲ�������ģʽ�Ĺ��ģ�
 *   2. �������"enter sleep!"��Ϩ�� LED0��������ʱ����
 *      ����˯��ģʽ��J-Link ���ԶϿ�����ʱ�û��ɲ���˯��ģʽ�Ĺ��ģ�
 *   3. �ȴ���ʱʱ�䵽��MCU �����ѣ��������"wake_up!"������ LED0��Ȼ�����½���
 *      ˯��ģʽ��
 *
 * \note
 *   ���� TIM4 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã��ᶨ�ڲ����жϵ��»��ѣ� ���Ա�����
 *   ֮ǰӦ�� am_prj_config.h �еĺ� AM_CFG_SYSTEM_TICK_ENABLE��
 *   AM_CFG_SOFTIMER_ENABLE ��   AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_mm32l373_drv_sleepmode_timer_wake_up.c src_mm32l373_drv_sleepmode_timer_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 18-05-16  pea, first implementation
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_mm32l373_drv_sleepmode_timer_wake_up
 * \copydoc demo_mm32l373_drv_sleepmode_timer_wake_up.c
 */
 
/** [src_mm32l373_drv_sleepmode_timer_wake_up] */
#include "ametal.h"
#include "am_int.h"
#include "am_board.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_mm32l373.h"
#include "am_mm32l373_pwr.h"
#include "am_mm32l373_clk.h"
#include "am_mm32l373_inst_init.h"
#include "mm32l373_periph_map.h"
#include "amhw_mm32_uart.h"

/** \brief LSI ʱ��Ƶ�� */
#define    __LSI_CLK    (40000UL)

/**
 * \brief �ȴ� RTC ����Ϊ����״̬
 */
am_local void __wait_rtc_idle (void)
{
    while(!amhw_mm32l373_rtc_crl_read_statu(MM32L373_RTC, AMHW_MM32L373_RTC_RSF));
    while(!amhw_mm32l373_rtc_crl_read_statu(MM32L373_RTC, AMHW_MM32L373_RTC_RTOFF));
}

/**
 * \brief ��ʱ���ص�����
 */
am_local void __rtc_handler (void *p_arg)
{

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();
    
    /* �ж��ж�Դ */
    if (amhw_mm32l373_rtc_crl_read_statu(MM32L373_RTC, AMHW_MM32L373_RTC_ALRF)) {
        
        /* �ȴ� RTC ����Ϊ����״̬ */
        __wait_rtc_idle();
        
        /* ����жϱ�־λ */
        amhw_mm32l373_rtc_clr_status_clear(MM32L373_RTC, AMHW_MM32L373_RTC_ALRF);
    }
}

/**
 *  \brief ���� RTC ����ʱ��
 */
am_local void __rtc_alarm_set (uint32_t second)
{
    uint32_t sec = 0;

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();

    /* ��ȡ��ǰ RTC ʱ�� */
    sec = amhw_mm32l373_rtc_cnth_get(MM32L373_RTC) << 16;
    sec |= amhw_mm32l373_rtc_cntl_get(MM32L373_RTC);

    sec += second - 1;
    
    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();
    
    amhw_mm32l373_rtc_crl_cnf_enter(MM32L373_RTC); /* �������� */
    amhw_mm32l373_rtc_alrl_set(MM32L373_RTC, sec & 0xffff);
    amhw_mm32l373_rtc_alrh_set(MM32L373_RTC, sec >> 16);
    amhw_mm32l373_rtc_crl_cnf_out(MM32L373_RTC); /* ���ø��� */
}

/** \brief RTC ƽ̨��ʼ�� */
am_local void __rtc_init (void)
{
    
    /* ʹ�� LSI */
    amhw_mm32l373_rcc_lsi_enable();
    while (amhw_mm32l373_rcc_lsirdy_read() == AM_FALSE);

    amhw_mm32l373_rcc_apb1_enable(AMHW_MM32L373_RCC_APB1_PWR); /* ʹ�ܵ�Դʱ�� */
    amhw_mm32l373_rcc_apb1_enable(AMHW_MM32L373_RCC_APB1_BKP); /* ʹ�ܱ���ʱ�� */
    amhw_mm32_pwr_bkp_access_enable(MM32L373_PWR, 1);         /* ȡ���������д���� */
    amhw_mm32l373_rcc_bdcr_bdrst_reset();                    /* �������������λ */
    am_udelay(5);
    amhw_mm32l373_rcc_bdcr_bdrst_reset_end();                /* �����������λ���� */
    
    /* RTC ʱ��Դѡ��Ϊ LSI */
    amhw_mm32l373_rcc_bdcr_rtc_clk_set(AMHW_MM32L373_RTCCLK_LSI);
    am_mdelay(1);
    amhw_mm32l373_rcc_bdcr_rtc_enable();                     /* RTCʱ��ʹ�� */

    /* ��ʱ�ȴ�Ԥ��Ƶ�Ĵ����ȶ� */
    am_mdelay(10);

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();

    /* ���������ж� */
    amhw_mm32l373_rtc_crh_allow_int(MM32L373_RTC, AMHW_MM32L373_RTC_ALRIE);

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();

    amhw_mm32l373_rtc_crl_cnf_enter(MM32L373_RTC); /* �������� RTC */
    amhw_mm32l373_rtc_prll_div_write(MM32L373_RTC, (__LSI_CLK - 1) & 0xffff);
    amhw_mm32l373_rtc_prlh_div_write(MM32L373_RTC, (__LSI_CLK - 1) >> 16);
    amhw_mm32l373_rtc_crl_cnf_out(MM32L373_RTC); /* ���ø��� */

    /* ���Ӳ�ʹ�� RTC �����ж� */
    am_int_connect(INUM_RTC, __rtc_handler, NULL);
    am_int_enable(INUM_RTC);
    
}

/**
 * \brief �������
 */
void demo_mm32l373_drv_sleepmode_timer_wake_up_entry (void)
{
    uint32_t i;
    
    AM_DBG_INFO("low power test!\r\n");
    am_led_on(LED0);

    /* ��ʼ�� RTC */
    __rtc_init();
    
    /* ��ʼ�� PWR */
    am_mm32l373_pwr_inst_init();

    /* �������� */
    am_mm32l373_wake_up_cfg(AM_MM32L373_PWR_MODE_SLEEP, NULL, NULL);

    for (i = 0; i < 5; i++) {
        am_mdelay(1000);
    }

    while (1) {

        /* ˯��֮ǰ�ر� LED */
        am_led_off(LED0);

        /* ���ö�ʱ�ж�����Ϊ 1S����������ʱ�� */        
        __rtc_alarm_set(1);

        /* ����˯��ģʽ */
        am_mm32l373_pwr_mode_into(AM_MM32L373_PWR_MODE_SLEEP);

        AM_DBG_INFO("wake_up!\r\n");

        /* ����֮����� LED */
        am_led_on(LED0);
        am_mdelay(10);
    }
}

/** [src_mm32l373_drv_sleepmode_timer_wake_up] */

/* end of file */
