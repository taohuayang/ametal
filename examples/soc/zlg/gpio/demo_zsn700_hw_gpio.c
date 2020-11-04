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
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ��������Ϊ�͵�ƽ��
 *
 * - ʵ������
 *   2. ��������Ϊ�͵�ƽʱ���������״̬��ת��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_gpio.c src_zsn700_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-12  YRZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_gpio
 * \copydoc demo_zsn700_hw_gpio.c
 */

/** [src_zsn700_hw_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "hw/amhw_zsn700_gpio.h"

/**
 * \brief �������
 */
void demo_zsn700_hw_gpio_entry (void    *p_hw_gpio,
                                int32_t  input_pin,
                                int32_t  output_pin)
{
	amhw_zsn700_gpio_t *p_gpio = (amhw_zsn700_gpio_t *)p_hw_gpio;

    uint32_t dir_input = 0;

    /* ȡ�����ŵĸ��ù��� */
    amhw_zsn700_gpio_afio_set(p_gpio, AMHW_ZSN700_AFIO_NO, input_pin);

    /* ���ֶ˿�����*/
    amhw_zsn700_gpio_pin_digital_set(p_gpio, input_pin);

    /* �������� */
    amhw_zsn700_gpio_pin_dir_input(p_gpio, input_pin);

    /* ʹ�����ŵ��������� */
    amhw_zsn700_gpio_pin_pu_enable(p_gpio, input_pin);

    /* ȡ�����ŵĸ��ù��� */
    amhw_zsn700_gpio_afio_set(p_gpio, AMHW_ZSN700_AFIO_NO, output_pin);

    /* ���ֶ˿�����*/
    amhw_zsn700_gpio_pin_digital_set(p_gpio, output_pin);

    /* ������� */
    amhw_zsn700_gpio_pin_dir_output(p_gpio, output_pin);

    /* ��������ǿ������ */
    amhw_zsn700_gpio_pin_driver_high(p_gpio, output_pin);

    /* ʹ�����ŵ��������� */
    amhw_zsn700_gpio_pin_pu_enable(p_gpio, output_pin);

    while (1) {

        dir_input = amhw_zsn700_gpio_pin_input_get(p_gpio, input_pin);

        if (dir_input == 0) {
            am_gpio_toggle(output_pin);
            am_mdelay(500);
        }
    }
}
/** [src_zsn700_hw_gpio] */

/* end of file */
