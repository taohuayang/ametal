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
 * \snippet demo_zlg118_hw_gpio_trigger.c src_zlg118_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_gpio_trigger
 * \copydoc demo_zlg118_hw_gpio_trigger.c
 */

/** [src_zlg118_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg118_gpio.h"
#include "hw/amhw_zlg118_rcc.h"

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
void demo_zlg118_hw_gpio_trigger_entry (void *p_hw_gpio, int32_t pin)
{
	amhw_zlg118_gpio_t *p_gpio = (amhw_zlg118_gpio_t *)p_hw_gpio;

    /* ȡ�����ŵĸ��ù��� */
    amhw_zlg118_gpio_afio_set(p_gpio, AMHW_ZLG118_AFIO_NO, pin);

    /* ���ֶ˿�����*/
    amhw_zlg118_gpio_pin_digital_set(p_gpio, pin);

    /* �������� */
    amhw_zlg118_gpio_pin_dir_input(p_gpio, pin);

    /* ʹ�����ŵ��������� */
    amhw_zlg118_gpio_pin_pu_enable(p_gpio, pin);

    /* �½��ش��� */
    amhw_zlg118_gpio_pin_falling_int_enable(p_gpio, pin);

    /* �����û�ע����жϻص����� */
    am_gpio_trigger_connect(pin, __gpio_isr, NULL);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg118_hw_gpio_trigger] */

/* end of file */
