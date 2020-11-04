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
 * \snippet demo_hk32f103rbt6_hw_gpio.c src_hk32f103rbt6_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_hw_gpio
 * \copydoc demo_hk32f103rbt6_hw_gpio.c
 */

/** [src_hk32f103rbt6_hw_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "hw/amhw_hk_gpio.h"

/**
 * \brief �������
 */
void demo_hk32f103rbt6_hw_gpio_entry (amhw_hk_gpio_t *p_hw_gpio,
                             int32_t          input_pin,
                             int32_t          output_pin)
{
    uint32_t dir_input = 0;

    /* ȡ�����ŵĸ��ù��� */
    amhw_hk_gpio_pin_afr_set(p_hw_gpio, AMHW_HK_GPIO_AF_DEFAULT, input_pin);

    /* �������ŵķ���Ϊ���뼰�������ŵ�ģʽ */
    amhw_hk_gpio_pin_set(p_hw_gpio, AMHW_HK_GPIO_MODE_IPU << 2 | 0x00, input_pin);

    /* ʹ�����ŵ��������� */
    amhw_hk_gpio_pin_out_high(p_hw_gpio, input_pin);

    /* ȡ�����ŵĸ��ù��� */
    amhw_hk_gpio_pin_afr_set(p_hw_gpio, AMHW_HK_GPIO_AF_DEFAULT, output_pin);

    /* �������ŵķ���Ϊ������������ŵ�ģʽ */
    amhw_hk_gpio_pin_set(p_hw_gpio, AMHW_HK_GPIO_MODE_OUT_PP << 2 | 0x00, output_pin);

    /* �������ŵ�����ٶ� */
    amhw_hk_gpio_pin_dir_output(p_hw_gpio, AMHW_HK_GPIO_SPEED_10MHz, output_pin);

    /* ʹ�����ŵ��������� */
    amhw_hk_gpio_pin_out_high(p_hw_gpio, output_pin);

    while (1) {

        dir_input = amhw_hk_gpio_pin_get(p_hw_gpio, input_pin);

        if (dir_input == 0) {
            am_gpio_toggle(output_pin);
            am_mdelay(500);
        }
    }
}
/** [src_hk32f103rbt6_hw_gpio] */

/* end of file */
