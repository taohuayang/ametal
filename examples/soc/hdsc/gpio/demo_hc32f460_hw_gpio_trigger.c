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
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ��Ӧ���ж������ϲ����½��ء�
 *
 * - ʵ������
 *   1. �жϲ���ʱ���Դ������ "the gpio interrupt happen!"��
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_gpio_trigger.c src_hc32f460_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 20-01-16  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_gpio_trigger
 * \copydoc demo_hc32f460_hw_gpio_trigger.c
 */

/** [src_hc32f460_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_hc32f460_gpio.h"
#include "hw/amhw_hc32f460_rcc.h"

/**
 * \brief �����жϷ�����
 */
static void __gpio_isr (void *p_arg)
{
    AM_DBG_INFO("the gpio interrupt happen!\r\n");
}

/**
 * \brief �������
 */
void demo_hc32f460_hw_gpio_trigger_entry (void *p_hw_gpio, int pin)
{
    amhw_hc32f460_gpio_t *p_gpio = (amhw_hc32f460_gpio_t *)p_hw_gpio;

    /* ȡ�����ŵĸ��ù��� */
    amhw_hc32f460_gpio_pin_afr_set(p_hw_gpio, AMHW_HC32F460_AFIO_GPIO, pin);

    /* ���ֶ˿�����*/
    amhw_hc32f460_gpio_pin_digital_set(p_gpio, pin);

    /* �������� */
    amhw_hc32f460_gpio_pin_dir_input(p_gpio, pin);

    /* ʹ�����ŵ��������� */
    amhw_hc32f460_gpio_pin_pu_enable(p_gpio, pin);

    /* ���ô�����ʽ */
    amhw_hc32f460_intc_pin_rising_int_enable(pin & 0xf);

    /* �����ⲿ�ж�������� */
    amhw_hc32f460_gpio_pin_ext_int_enable(p_hw_gpio, pin);

    /* �����û�ע����жϻص����� */
    am_gpio_trigger_connect(pin, __gpio_isr, NULL);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f460_hw_gpio_trigger] */

/* end of file */
