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
 * \brief LED �û������ļ���GPIOֱ��������
 * \sa am_hwconf_hc32f03x_led_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  tee, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led_gpio.h"
#include "hc32x3x_pin.h"
#include "am_input.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f03x_led_gpio
 * \copydoc am_hwconf_hc32f03x_led_gpio.c
 * @{
 */

/** \brief ���� LED ��ص� GPIO �ܽ���Ϣ */
static const int __g_hc32f03x_led_pins[] = {PIOD_5};

/** \brief �豸��Ϣ */
static const am_led_gpio_info_t __g_hc32f03x_led_gpio_info = {
    {
        0,                             /* ��ʼ��� */
        AM_NELEMENTS(__g_hc32f03x_led_pins) - 1 /* ������� */
    },
    __g_hc32f03x_led_pins,
    AM_TRUE
};

/** \brief �豸ʵ�� */
static am_led_gpio_dev_t  __g_hc32f03x_led_gpio;

/** \brief ʵ����ʼ������ */
int am_hc32_led_gpio_inst_init (void)
{
    return am_led_gpio_init(&__g_hc32f03x_led_gpio, &__g_hc32f03x_led_gpio_info);
}

/**
 * @}
 */

/* end of file */
