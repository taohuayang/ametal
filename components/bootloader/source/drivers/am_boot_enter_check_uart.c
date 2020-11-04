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
 * \brief ����Ӧ�ó����׼�ӿ�ʵ�֣�������������������
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-25  yrh, first implementation.
 * \endinternal
 */
#include "am_boot_enter_check_uart.h"
#include "am_uart.h"
#include "am_softimer.h"
#include "am_vdebug.h"

#define OPTION_APP                0
#define OPTION_BOOT               1

/** \brief һ�볬ʱ��־ */
volatile static uint8_t second_timeout   = 0;
volatile static uint8_t user_option      = OPTION_APP;
volatile static uint8_t time_count       = 5;

static am_softimer_t timer;
/**
 * \brief ���ڽ��ջص�����
 */
static void __uart_rec_callback(void *p_arg, char inchar)
{
    user_option = OPTION_BOOT;
}

/**
 * \brief ���ڽ������������ʱ���ص�����
 */
static void __receive_callback_timer_handle(void *p_arg)
{
    if(time_count != 0){
        time_count--;
        second_timeout = 1;
    }
}

am_bool_t  __boot_enter_check_uart(void *p_drv)
{
    am_boot_enter_check_uart_dev_t *p_dev = (am_boot_enter_check_uart_dev_t *)p_drv;
    /* ʹ�ܴ����ж�ģʽ */
    am_uart_ioctl(p_dev->uart_handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);
    /* ע�ᷢ�ͻص����� */
    am_uart_callback_set(p_dev->uart_handle, AM_UART_CALLBACK_RXCHAR_PUT, __uart_rec_callback, NULL);

    am_softimer_init(&timer, __receive_callback_timer_handle, NULL);

    am_kprintf("if don't input anything,Device will enter application after %ds\r\n",time_count);
    am_softimer_start(&timer, 1000);

    /* ��ʱ�ȴ�������û������ݷ������ͽ���bootloader��������ת��Ӧ�ó��� */
    while(1) {
        if(second_timeout == 1) {
            if(time_count == 0 ) {
                am_softimer_stop(&timer);
                second_timeout = 0;
                return AM_TRUE;
            }
            am_kprintf("if don't input anything,Device will enter application after %ds\r\n",time_count);
            second_timeout = 0;
        }

        if(user_option == OPTION_BOOT) {
            am_softimer_stop(&timer);
            return AM_FALSE;
        }
    }
}

static const struct am_boot_enter_check_drv_funcs __g_enter_check_uart_drv_funcs = {
    __boot_enter_check_uart,
    NULL
};

static am_boot_enter_check_uart_dev_t __g_enter_check_uart_dev;

am_boot_enter_check_handle_t am_boot_enter_check_uart_init(am_uart_handle_t uart_handle)
{
    __g_enter_check_uart_dev.enter_check_serv.p_drv   = &__g_enter_check_uart_dev;
    __g_enter_check_uart_dev.enter_check_serv.p_funcs = &__g_enter_check_uart_drv_funcs;
    __g_enter_check_uart_dev.uart_handle              = uart_handle;

    return &__g_enter_check_uart_dev.enter_check_serv;
}

/* end of file */

