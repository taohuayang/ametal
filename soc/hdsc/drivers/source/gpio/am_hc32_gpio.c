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
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.01 20-04-26 zcb, Fix the problem that only one pin can be
 *                      configured as external interrupt
 * - 1.00 19-09-06  zp, first implementation
 * \endinternal
 */

#include "am_hc32_gpio.h"
#include "am_gpio_util.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_bitops.h"
#include "am_hc32_gpio_util.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

const am_hc32_gpio_devinfo_t *p_gpio_devinfo = NULL;

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_hc32_gpio_dev_t *__gp_gpio_dev;

/*******************************************************************************
  ��������
*******************************************************************************/

/**
 * \brief ���Ź�������
 */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;
    amhw_hc32_gpiomode_t  pin_mode   = AMHW_HC32_GPIO_MODE_IPU;
    uint32_t                func = 0, mode = 0;

    /* IO�ڷ��� */
    uint8_t dir = 0;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (AM_FALSE == __gp_gpio_dev->valid_flg) {
        return -AM_ENODEV;
    }

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    func = AM_GPIO_COM_FUNC_GET(flags);
    mode = AM_GPIO_COM_MODE_GET(flags);

    amhw_hc32_gpio_afio_set(p_hw_gpio, AMHW_HC32_AFIO_NO, pin);

    /* ��׼����� */
    if (0 != func) {

        switch (func) {

        case AM_GPIO_INPUT_VAL:

            /* ���÷���Ϊ���� */
            amhw_hc32_gpio_pin_dir_input(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH_VAL:

            /* ������� */
            amhw_hc32_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_HC32_GPIO_MODE_OUT_PP,
                                          pin);

            /* ����ߵ�ƽ */
            amhw_hc32_gpio_pin_out_high(p_hw_gpio, pin);

            break;

        case AM_GPIO_OUTPUT_INIT_LOW_VAL:

            /* ������� */
            amhw_hc32_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_HC32_GPIO_MODE_OUT_PP,
                                          pin);

            /* ����͵�ƽ */
            amhw_hc32_gpio_pin_out_low(p_hw_gpio, pin);

            break;

        default:
            return -AM_ENOTSUP;
        }
    }

    if (mode != 0x00) {

        /* ��ȡ����������� */
        dir = amhw_hc32_gpio_pin_dir_get(p_hw_gpio, pin);

        switch (mode) {

        case AM_GPIO_PULL_UP_VAL:
            if (dir == 1) {

                /* ��������ģʽ  */
                pin_mode = AMHW_HC32_GPIO_MODE_IPU;

            } else {

                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_HC32_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_PULL_DOWN_VAL:
            if (dir == 1) {

                /* ��������ģʽ  */
                pin_mode = AMHW_HC32_GPIO_MODE_IPD;

            } else {

                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_HC32_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_FLOAT_VAL:
            if (dir == 1) {
                pin_mode = AMHW_HC32_GPIO_MODE_IN_FLOATING;
            } else {

                /* ���û�и���ģʽ������Ϊ��©ģʽ */
                pin_mode = AMHW_HC32_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_OPEN_DRAIN_VAL:
            if (dir == 1) {
                /* ����û�п�©ģʽ������Ϊ���� */
                pin_mode = AMHW_HC32_GPIO_MODE_IN_FLOATING;
            } else {
                pin_mode = AMHW_HC32_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_PUSH_PULL_VAL:
            if (dir == 1) {
                /* ����û������ģʽ������Ϊ���� */
                pin_mode = AMHW_HC32_GPIO_MODE_IPU;
            } else {
                pin_mode = AMHW_HC32_GPIO_MODE_OUT_PP;
            }
            break;

        default:
            return -AM_ENOTSUP;
        }

        amhw_hc32_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ƽ̨��� */
    if (0 != (flags & AM_HC32_GPIO_MODE)) {

        /* ���������Ӧģʽ���� */

        switch (AM_HC32_GPIO_MODE_GET(flags)) {

        case 0:
            /* �������� */
            pin_mode = AMHW_HC32_GPIO_MODE_IPU;
            break;

        case 1:
            /* �������� */
            pin_mode = AMHW_HC32_GPIO_MODE_IPD;
            break;

        case 2:
            /* ģ������ */
            pin_mode = AMHW_HC32_GPIO_MODE_AIN;
            break;

        case 3:
            /* �������� */
            pin_mode = AMHW_HC32_GPIO_MODE_IN_FLOATING;
            break;

        case 4:
            /* �������  */
            pin_mode = AMHW_HC32_GPIO_MODE_OUT_PP;
            break;

        case 5:
            /* ��©��� */
            pin_mode = AMHW_HC32_GPIO_MODE_OUT_OD;
            break;

        case 6:
            /* ģ����� */
            pin_mode = AMHW_HC32_GPIO_MODE_AOUT;
            break;

        default:
            return -AM_ENOTSUP;
        }

        amhw_hc32_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ��ӳ������ */
    if (0 != (flags & AM_HC32_GPIO_REMAP)) {
        amhw_hc32_gpio_afio_set(
            p_hw_gpio,
            (amhw_hc32_gpio_afio_t)AM_HC32_GPIO_REMAP_MODE_GET(flags),
            pin);
    }
    return AM_OK;
}

/**
 * \brief ��ȡGPIO����״̬
 */
int am_gpio_get (int pin)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (0 == amhw_hc32_gpio_pin_dir_get(p_hw_gpio, pin)) {
        return amhw_hc32_gpio_pin_output_get(p_hw_gpio, pin);
    } else {
        return amhw_hc32_gpio_pin_input_get(p_hw_gpio, pin);
    }
}

/**
 * \brief �����������״̬
 */
int am_gpio_set (int pin, int value)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (value == 0) {
        amhw_hc32_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_hc32_gpio_pin_out_high(p_hw_gpio, pin);
    }

    return AM_OK;
}

/**
 * \brief ��תGPIO�������״̬
 */
int am_gpio_toggle (int pin)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;

    uint8_t t = 0;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    t= amhw_hc32_gpio_pin_output_get(p_hw_gpio, pin);

    if(1 == t) {
        amhw_hc32_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_hc32_gpio_pin_out_high(p_hw_gpio, pin);
    }

    return AM_OK;
}

/**
 * \brief �˿�A���жϺ���
 */
static void __port_a_int_isr (void * p_arg)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    (void)p_arg;

    /* ���жϴ��� */
    for(pin = 0; pin < 16; pin++) {
        if (1 == amhw_hc32_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_hc32_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
}

/**
 * \brief �˿�B���жϺ���
 */
static void __port_b_int_isr (void * p_arg)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    (void)p_arg;

    /* ���жϴ��� */
    for(pin = 16; pin < 32; pin++) {
        if (1 == amhw_hc32_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_hc32_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
}

/**
 * \brief �˿�C/E���жϺ���
 */
static void __port_c_e_int_isr (void * p_arg)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    (void)p_arg;

    /* ���жϴ��� */
    for(pin = 32; pin < 48; pin++) {
        if (1 == amhw_hc32_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_hc32_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }

#ifndef HC32X3X
    /* ���жϴ��� */
    for(pin = 64; pin < 80; pin++) {
        if (1 == amhw_hc32_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_hc32_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
#endif
}

/**
 * \brief �˿�D/F���жϺ���
 */
static void __port_d_f_int_isr (void * p_arg)
{
    amhw_hc32_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    (void)p_arg;

    /* ���жϴ��� */
    for(pin = 48; pin < 64; pin++) {
        if (1 == amhw_hc32_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_hc32_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }

#ifndef HC32X3X
    /* ���жϴ��� */
    for(pin = 80; pin < 91; pin++) {
        if (1 == amhw_hc32_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_hc32_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
#endif
}

/**
 * \brief GPIO��ʼ��
 */
int am_hc32_gpio_init (am_hc32_gpio_dev_t           *p_dev,
                       const am_hc32_gpio_devinfo_t *p_devinfo)
{
    uint8_t i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return -AM_EINVAL;
    }

    if (NULL == p_devinfo->inum_pin ||
        NULL == p_devinfo->p_trigger ||
        NULL == p_devinfo->p_triginfo) {
        p_dev->valid_flg = AM_FALSE;
        return -AM_EINVAL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;
    p_gpio_devinfo   = p_devinfo;

    for (i = 0 ; i < p_devinfo->exti_num_max ; i++) {
        p_gpio_devinfo->p_trigger[i]               = AM_GPIO_TRIGGER_OFF;
        p_gpio_devinfo->p_triginfo[i].p_arg        = NULL;
        p_gpio_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_connect(p_devinfo->inum_pin[0], __port_a_int_isr,   NULL);
    am_int_connect(p_devinfo->inum_pin[1], __port_b_int_isr,   NULL);
    am_int_connect(p_devinfo->inum_pin[2], __port_c_e_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[3], __port_d_f_int_isr, NULL);

    am_int_enable(p_devinfo->inum_pin[0]);
    am_int_enable(p_devinfo->inum_pin[1]);
    am_int_enable(p_devinfo->inum_pin[2]);
    am_int_enable(p_devinfo->inum_pin[3]);

    p_dev->valid_flg = AM_TRUE;

    __gp_gpio_dev = p_dev;

    return AM_OK;
}

/**
 * \brief GPIOȥ��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void am_hc32_gpio_deinit (void)
{
    uint8_t i;

    if (p_gpio_devinfo->pfn_plfm_deinit) {
        p_gpio_devinfo->pfn_plfm_deinit();
    }

    if (__gp_gpio_dev->valid_flg == AM_FALSE) {
        return;
    }

    for (i = 0 ; i < p_gpio_devinfo->exti_num_max ; i++) {
        p_gpio_devinfo->p_trigger[i]               = AM_GPIO_TRIGGER_OFF;
        p_gpio_devinfo->p_triginfo[i].p_arg        = NULL;
        p_gpio_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_disable(p_gpio_devinfo->inum_pin[0]);
    am_int_disable(p_gpio_devinfo->inum_pin[1]);
    am_int_disable(p_gpio_devinfo->inum_pin[2]);
    am_int_disable(p_gpio_devinfo->inum_pin[3]);

    am_int_disconnect(p_gpio_devinfo->inum_pin[0], __port_a_int_isr,   NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[1], __port_b_int_isr,   NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[2], __port_c_e_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[3], __port_d_f_int_isr, NULL);

    __gp_gpio_dev = NULL;
}

/**
 * \brief ����GPIO���Ŵ�������
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    uint8_t slot = pin;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot >= p_gpio_devinfo->exti_num_max) {
        return -AM_ENOSPC;
    }

    p_gpio_devinfo->p_trigger[slot] = flag;

    return AM_OK;
}

/**
 * \brief ���ӻص�����������
 */
int am_gpio_trigger_connect(int           pin,
                            am_pfnvoid_t  pfn_callback,
                            void         *p_arg)
{
    uint8_t slot = pin;
    int     key;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (AM_FALSE == __gp_gpio_dev->valid_flg) {
        return -AM_ENODEV;
    }

    if (slot >= p_gpio_devinfo->exti_num_max) {
        return -AM_ENOSPC;
    }

    key = am_int_cpu_lock();

    p_gpio_devinfo->p_triginfo[slot].p_arg        = p_arg;
    p_gpio_devinfo->p_triginfo[slot].pfn_callback = pfn_callback;

    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ɾ�����ӵ����ŵĻص�����
 */
int am_gpio_trigger_disconnect(int           pin,
                               am_pfnvoid_t  pfn_callback,
                               void         *p_arg)
{
    uint8_t slot = pin;
    int     key;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot >= p_gpio_devinfo->exti_num_max) {
        return -AM_ENOSPC;
    }

    (void)pfn_callback;
    (void)p_arg;

    key = am_int_cpu_lock();

    p_gpio_devinfo->p_triginfo[slot].p_arg        = NULL;
    p_gpio_devinfo->p_triginfo[slot].pfn_callback = NULL;

    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ʹ�����Ŵ����ж�
 */
int am_gpio_trigger_on(int pin)
{
    uint8_t           slot      = pin;
    amhw_hc32_gpio_t *p_hw_gpio = \
        (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot >= p_gpio_devinfo->exti_num_max) {
        return -AM_ENOSPC;
    }

    switch (p_gpio_devinfo->p_trigger[slot]) {

    case AM_GPIO_TRIGGER_OFF:
        am_gpio_trigger_off(pin);
        break;

    case AM_GPIO_TRIGGER_HIGH:
        amhw_hc32_gpio_pin_high_int_enable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_low_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_raising_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_falling_int_disable(p_hw_gpio,pin);
        break;

    case AM_GPIO_TRIGGER_LOW:
        amhw_hc32_gpio_pin_high_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_low_int_enable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_raising_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_falling_int_disable(p_hw_gpio,pin);
        break;

    case AM_GPIO_TRIGGER_RISE:
        amhw_hc32_gpio_pin_high_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_low_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_raising_int_enable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_falling_int_disable(p_hw_gpio,pin);
        break;

    case AM_GPIO_TRIGGER_FALL:
        amhw_hc32_gpio_pin_high_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_low_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_raising_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_falling_int_enable(p_hw_gpio,pin);
        break;

    case AM_GPIO_TRIGGER_BOTH_EDGES:
        amhw_hc32_gpio_pin_high_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_low_int_disable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_raising_int_enable(p_hw_gpio,pin);
        amhw_hc32_gpio_pin_falling_int_enable(p_hw_gpio,pin);
        break;

    default:
        return -AM_ENXIO;
    }

    return AM_OK;
}

/**
 * \brief �������Ŵ����ж�
 */
int am_gpio_trigger_off(int pin)
{
    amhw_hc32_gpio_t *p_hw_gpio = \
        (amhw_hc32_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    /* �ر�ĳһ���ŵ����д����ж� */
    amhw_hc32_gpio_pin_high_int_disable(p_hw_gpio,pin);
    amhw_hc32_gpio_pin_low_int_disable(p_hw_gpio,pin);
    amhw_hc32_gpio_pin_raising_int_disable(p_hw_gpio,pin);
    amhw_hc32_gpio_pin_falling_int_disable(p_hw_gpio,pin);

    return AM_OK;
}

/* end of file */
