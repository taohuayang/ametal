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
 * \brief GPIO
 *
 * ����ֱ��ʹ���� ZSN700 ����Ĵ�������ַ�� ��ˣ��������������� ZSN700
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */
#include "hw/amhw_zsn700_gpio.h"
#include "am_gpio.h"

/**
 * \brief ����GPIO���ŵ�ģʽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] gpio_mode : ���ŵ�ģʽ��ֵΪ amhw_zlg217_gpiomode_t ���ö������
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
void amhw_zsn700_gpio_pin_mode_set (amhw_zsn700_gpio_t     *p_hw_gpio,
                                    amhw_zsn700_gpiomode_t  gpio_mode,
                                    int                     pin)
{

    switch(gpio_mode) {

    /* �������� */
    case AMHW_ZSN700_GPIO_MODE_IPU:

        /* ���ֶ˿�/ģ��˿�����*/
        amhw_zsn700_gpio_pin_digital_set(p_hw_gpio, pin);

        /* ��������������� */
        amhw_zsn700_gpio_pin_dir_input(p_hw_gpio, pin);

        /* ��������ǿ������ */
        amhw_zsn700_gpio_pin_driver_high(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pu_enable(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pd_disable(p_hw_gpio, pin);

        /* ��©�������*/
        amhw_zsn700_gpio_pin_od_disable(p_hw_gpio, pin);
        break;

    /* �������� */
    case AMHW_ZSN700_GPIO_MODE_IPD:

        /* ���ֶ˿�/ģ��˿�����*/
        amhw_zsn700_gpio_pin_digital_set(p_hw_gpio, pin);

        /* ��������������� */
        amhw_zsn700_gpio_pin_dir_input(p_hw_gpio, pin);

        /* ��������ǿ������ */
        amhw_zsn700_gpio_pin_driver_high(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pu_disable(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pd_enable(p_hw_gpio, pin);

        /* ��©�������*/
        amhw_zsn700_gpio_pin_od_disable(p_hw_gpio, pin);
        break;

    /* ģ������ */
    case AMHW_ZSN700_GPIO_MODE_AIN:

        /* ���ֶ˿�/ģ��˿�����*/
        amhw_zsn700_gpio_pin_analog_set(p_hw_gpio, pin);

        /* ��������������� */
        amhw_zsn700_gpio_pin_dir_input(p_hw_gpio, pin);

        /* ��������ǿ������ */
        amhw_zsn700_gpio_pin_driver_high(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pu_disable(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pd_disable(p_hw_gpio, pin);

        /* ��©�������*/
        amhw_zsn700_gpio_pin_od_disable(p_hw_gpio, pin);
        break;

    /* �������� */
    case AMHW_ZSN700_GPIO_MODE_IN_FLOATING:

        /* ���ֶ˿�/ģ��˿�����*/
        amhw_zsn700_gpio_pin_digital_set(p_hw_gpio, pin);

        /* ��������������� */
        amhw_zsn700_gpio_pin_dir_input(p_hw_gpio, pin);

        /* ��������ǿ������ */
        amhw_zsn700_gpio_pin_driver_high(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pu_disable(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pd_disable(p_hw_gpio, pin);

        /* ��©�������*/
        amhw_zsn700_gpio_pin_od_disable(p_hw_gpio, pin);
        break;

    /* ������� */
    case AMHW_ZSN700_GPIO_MODE_OUT_PP:

        /* ���ֶ˿�/ģ��˿�����*/
        amhw_zsn700_gpio_pin_digital_set(p_hw_gpio, pin);

        /* ��������������� */
        amhw_zsn700_gpio_pin_dir_output(p_hw_gpio, pin);

        /* ��������ǿ������ */
        amhw_zsn700_gpio_pin_driver_high(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pu_enable(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pd_enable(p_hw_gpio, pin);

        /* ��©�������*/
        amhw_zsn700_gpio_pin_od_disable(p_hw_gpio, pin);
        break;

    /* ��©��� */
    case AMHW_ZSN700_GPIO_MODE_OUT_OD:

        /* ���ֶ˿�/ģ��˿�����*/
        amhw_zsn700_gpio_pin_digital_set(p_hw_gpio, pin);

        /* ��������������� */
        amhw_zsn700_gpio_pin_dir_output(p_hw_gpio, pin);

        /* ��������ǿ������ */
        amhw_zsn700_gpio_pin_driver_high(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pu_disable(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pd_disable(p_hw_gpio, pin);

        /* ��©�������*/
        amhw_zsn700_gpio_pin_od_enable(p_hw_gpio, pin);
        break;

    /* ģ����� */
    case AMHW_ZSN700_GPIO_MODE_AOUT:

        /* ���ֶ˿�/ģ��˿�����*/
        amhw_zsn700_gpio_pin_analog_set(p_hw_gpio, pin);

        /* ��������������� */
        amhw_zsn700_gpio_pin_dir_output(p_hw_gpio, pin);

        /* ��������ǿ������ */
        amhw_zsn700_gpio_pin_driver_high(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pu_disable(p_hw_gpio, pin);

        /* �������� */
        amhw_zsn700_gpio_pin_pd_disable(p_hw_gpio, pin);

        /* ��©�������*/
        amhw_zsn700_gpio_pin_od_disable(p_hw_gpio, pin);
        break;
    }
}


/* end of file */
