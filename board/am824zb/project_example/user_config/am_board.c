/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AM824ZB
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_prj_config.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_lpc82x_clk.h"
#include "am_softimer.h"
#include "am_lpc82x_inst_init.h"
#include "am_lpc82x.h"
#include "am_system.h"
#include "am_buzzer.h"
#include "am_buzzer_pwm.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"
#include "am_hwconf_key_gpio.h"
#include "am_hwconf_led_gpio.h"
#include "am_arm_nvic.h"

#include "am_bsp_system_heap.h"
#include "am_bsp_isr_defer_pendsv.h"
#include "am_bsp_delay_timer.h"
#include "am_service_inst_init.h"

#ifdef __CC_ARM
#ifdef __MICROLIB
#include "am_bsp_microlib.h"
#else
#include "am_bsp_armlib.h"
#endif /* __MICROLIB */
#elif defined(__GNUC__)
#include "am_bsp_newlib.h"
#endif

/** \brief SRAM ��Ϣ,ʹ�� ARMCC ʱ��Ҫ�ṩ SRAM������ַ */
#ifdef __CC_ARM
#define SRAM_SIZE   8
#define SRAM_START  0x10000000
#define SRAM_END    (SRAM_START + SRAM_SIZE * 1024)
#endif /* __CC_ARM */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/**
 * \brief SCT0_PWM ��handle
 *
 * ��ʹ�÷�����ʱ��Ĭ�Ͻ�ʹ��SCT��OUT1���PWM���Σ�����Ѿ���SCT��ʼ��ΪPWM���ܣ�
 * ����SCT���������·PWM����˿���ʹ�ø�handle���Ա�ʹ������5·PWM��
 */
am_pwm_handle_t g_sct0_pwm_handle;

/**
 * \brief MRT ��handle
 *
 * ��ʹ�������ʱ��ʱ��Ĭ�Ͻ�ʹ��MRT��Ϊ������ʱ��Ԫ������Ѿ���MRT��ʼ��Ϊ��ʱ��
 * ���ܣ�����MRT����֧��4·��ʱ����˿���ʹ�ø� handle���Ա�ʹ������3· handle
 */
am_timer_handle_t g_mrt_handle;

/**
 * \brief CAT823 ���Ź���handle
 *
 *  CAT823 WDI������  PIO0_22��ע���������ò�Ҫʹ�ã��Է�оƬ���⸴λ
 */
am_wdt_handle_t   g_cat823_handle;

/*******************************************************************************
  ����LED�����Ϣ
*******************************************************************************/

#if (AM_CFG_LED_ENABLE == 1)

#include "am_led.h"

#endif /* (AM_CFG_LED_ENABLE == 1) */

/*******************************************************************************
  ������Դ�����������Ϣ
*******************************************************************************/

#if (AM_CFG_BUZZER_ENABLE == 1)

#include "am_lpc_sct_pwm.h"

#define __BUZZER_PWM_PERIOD_NS \
            (1000000000 / AM_CFG_BUZZER_PWM_FREQ)

#define __BUZZER_PWM_DUTY_NS   \
            (10000000 * AM_CFG_BUZZER_PWM_DUTY / AM_CFG_BUZZER_PWM_FREQ)

#endif /* (AM_CFG_BUZZER_ENABLE == 1) */

/*******************************************************************************
  ��������
*******************************************************************************/

#if (AM_CFG_SYSTEM_TICK_ENABLE == 1)

/* ϵͳ��ʱ�������ڲ���ϵͳ�δ����������ʱ���ȵ� */
static void __system_timer_callback (void *p_arg)
{
    am_system_module_tick();       /* ����ϵͳ�δ� */

#if (AM_CFG_SOFTIMER_ENABLE == 1)
    am_softimer_module_tick();     /* ���������ʱ�� */
#endif /* (AM_CFG_SOFTIMER_ENABLE == 1) */

}

#endif /* (AM_CFG_SYSTEM_TICK_ENABLE == 1) */

#if (AM_CFG_CAT823_WDT_ENABLE == 1)

am_softimer_t     g_softimer;

/* ι������ */
static void __cat823_wdt_feed (void *p_arg)
{
    am_wdt_feed(g_cat823_handle);
}

#endif

/**
 * \brief �弶��ʼ��
 */
void am_board_init (void)
{
    am_uart_handle_t dbg_handle = NULL;

#ifdef  __GNUC__
    extern char __heap_start__;            /* Defined by the linker */
    extern char __heap_end__;              /* Defined by the linker */

    static char *heap_start = &__heap_start__;
    static char *heap_end   = &__heap_end__;

#elif defined(__CC_ARM)

    extern int Image$$RW_IRAM1$$ZI$$Limit; /* Defined by the linker */

    int *heap_start = (int *)&Image$$RW_IRAM1$$ZI$$Limit;
    int *heap_end   = (int *)SRAM_END;
#endif

    /* ϵͳ��ջ��ʼ�� */
    am_bsp_system_heap_init((void *)heap_start, (void *)heap_end);

/*
 * ��ʹ����ʱ������ʹ�ã���ִ�г�ʼ����Ĭ��ʵ��Ϊʹ�� Systick ��ʱ��
 */
#if (AM_CFG_DELAY_ENABLE == 1)
    am_bsp_delay_timer_init(am_arm_systick_inst_init(), 0);
#endif /* (AM_CFG_DELAY_ENABLE == 1) */

/**
 * \brief ���Ϊ1�����ʼ��led����ع��ܣ�����Ĭ��������LED
 *
 * ID: 0 --- PIO0.8 ����Ҫ�̽�����ñ J9��
 * ID: 1 --- PIO0.9 ����Ҫ�̽�����ñ J10��
 */
#if (AM_CFG_LED_ENABLE == 1)
    am_led_gpio_inst_init();
#endif /* (AM_CFG_LED_ENABLE == 1) */

#ifdef AM_VDEBUG
#if (AM_CFG_DEBUG_ENABLE == 1)

    dbg_handle = am_debug_uart_inst_init();

#endif /* (AM_CFG_DEBUG_ENABLE == 1) */
#endif /* AM_VDEBUG */

#if (AM_CFG_STDLIB_ENABLE == 1)
    #ifdef __CC_ARM
        #ifdef __MICROLIB

            /* ��ʼ��Micro LIB */
            am_bsp_microlib_init(dbg_handle);
        #else

            /* ��ʼ��ARM LIB */
            am_bsp_armlib_init(dbg_handle);
        #endif /* __MICROLIB */

    #elif defined(__GNUC__)

        /* ��ʼ�� NEW LIB �� */
        am_bsp_newlib_init(dbg_handle);
    #endif
#endif /* (AM_CFG_STDLIB_ENABLE == 2) */

#if (AM_CFG_SYSTEM_TICK_ENABLE == 1)

    /* ʹ��һ����ʱ����ΪϵͳTICK */
    {

        g_mrt_handle = am_lpc82x_mrt_inst_init();

        /* �������ʱ�����ж����ȼ�����Ϊ��� */
        am_arm_nvic_priority_set(INUM_MRT, 0x03, 0x03);

        am_timer_callback_set(g_mrt_handle,
                              0,
                              __system_timer_callback,
                              NULL);

        am_system_module_init(AM_CFG_SYSTEM_TICK_RATE);

        am_timer_enable_us(g_mrt_handle,
                           0,
                           1000000 / AM_CFG_SYSTEM_TICK_RATE);
    }


#if (AM_CFG_SOFTIMER_ENABLE == 1)
    am_softimer_module_init(AM_CFG_SYSTEM_TICK_RATE);
#endif /* (AM_CFG_SOFTIMER_ENABLE == 1) */

#endif /* (AM_CFG_SYSTEM_TICK_ENABLE == 1) */

    g_cat823_handle = am_cat823_inst_init();

#if (AM_CFG_CAT823_WDT_ENABLE == 1)

    /* CAT823���Ź�оƬֻ֧��ι����ʱʱ������Ϊ1120ms */
    am_wdt_enable(g_cat823_handle, 1120);

    am_softimer_init(&g_softimer, __cat823_wdt_feed, NULL);
    am_softimer_start(&g_softimer, AM_CFG_CAT823_FEED_TIME_MS);

#endif

    /**
     * \brief ���Ϊ1�����ʼ������������ع��ܣ�����Ĭ����һ��������
     *
     * Ĭ��ʹ��SCT_OU1 ��PIO0_2�����PWM ����Ҫ�̽�����ñ J7��
     */
#if (AM_CFG_BUZZER_ENABLE == 1)

    g_sct0_pwm_handle = am_lpc82x_sct0_pwm_inst_init();

    am_buzzer_pwm_init(g_sct0_pwm_handle,
                       1,                    /* ʹ��ͨ��1, SCT_OUT1, PIO0_2 */
                      __BUZZER_PWM_DUTY_NS,
                      __BUZZER_PWM_PERIOD_NS);

#endif /* (AM_CFG_BUZZER_ENABLE == 1) */

#if (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_event_input_inst_init();                   /* �¼���������������ʼ�� */
#endif /* (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1) */

#if (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_key_gpio_inst_init();
#endif /* (AM_CFG_KEY_GPIO_ENABLE == 1) */

    /* �������ݴ���� */

}

/* end of file */
