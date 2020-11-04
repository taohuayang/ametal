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
 * \snippet demo_zlg_hw_gpio.c src_zlg_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_gpio
 * \copydoc demo_zlg_hw_gpio.c
 */

/** [src_zlg_hw_gpio] */
#include <hw/amhw_hc32f460_gpio.h>
#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"

enum
{
    LEVEL_LOW  = 0,
    LEVEL_HIGH
};

/**
 * \brief �������
 */
void demo_hc32f460_hw_gpio_entry (amhw_hc32f460_gpio_t *p_hw_gpio,
                                  int32_t          input_pin,
                                  int32_t          output_pin)
{
    uint32_t level = 0;

    /* ȡ�����ŵĸ��ù��� */
    amhw_hc32f460_gpio_pin_afr_set(p_hw_gpio, AMHW_HC32F460_AFIO_GPIO, input_pin);

    /* ���ֶ˿�����*/
    amhw_hc32f460_gpio_pin_digital_set(p_hw_gpio, input_pin);

    /* �������� */
    amhw_hc32f460_gpio_pin_dir_input(p_hw_gpio, input_pin);

    /* ʹ�����ŵ��������� */
    amhw_hc32f460_gpio_pin_pu_enable(p_hw_gpio, input_pin);

    /* ȡ�����ŵĸ��ù��� */
    amhw_hc32f460_gpio_pin_afr_set(p_hw_gpio, AMHW_HC32F460_AFIO_GPIO, output_pin);

    /* ���ֶ˿�����*/
    amhw_hc32f460_gpio_pin_digital_set(p_hw_gpio, output_pin);

    /* ������� */
    amhw_hc32f460_gpio_pin_dir_output(p_hw_gpio, output_pin);

    /* ��������ǿ������ */
    amhw_hc32f460_gpio_pin_driver_capability(p_hw_gpio, AMHW_HC32F460_GPIO_SPEED_LOW, output_pin);

    /* ʹ�����ŵ��������� */
    amhw_hc32f460_gpio_pin_pu_enable(p_hw_gpio, output_pin);

    amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, output_pin);
    amhw_hc32f460_gpio_pin_out_low(p_hw_gpio, output_pin);

    while (1) {
        level = amhw_hc32f460_gpio_pin_get(p_hw_gpio, input_pin);
        if (LEVEL_LOW == level) {
            amhw_hc32f460_gpio_pin_toggle(p_hw_gpio, output_pin);
            am_mdelay(500);
        }
    }
}
/** [src_zlg_hw_gpio] */

/* end of file */
