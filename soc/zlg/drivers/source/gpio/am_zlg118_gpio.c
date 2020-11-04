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
 * - 1.00 19-09-06  zp, first implementation
 * \endinternal
 */

#include "am_zlg118_gpio.h"
#include "am_gpio_util.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_bitops.h"
#include "am_zlg118_gpio_util.h"
#include "zlg118_pin.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define AM_ZLG118_GPIO_INVALID_PIN_MAP    0xFF

const am_zlg118_gpio_devinfo_t *p_gpio_devinfo = NULL;

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_zlg118_gpio_dev_t *__gp_gpio_dev;

/*******************************************************************************
  ��������
*******************************************************************************/

static int __am_zlg118_peripheral_afio_clear(int pin)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (NULL == p_gpio_devinfo) {
        return -AM_ENXIO;
    }

    if (p_gpio_devinfo->p_afio[pin] == AMHW_ZLG118_AFIO_NO) {
        return -AM_ENXIO;
    }

    amhw_zlg118_gpio_afio_set(p_hw_gpio, AMHW_ZLG118_AFIO_NO, pin);

    if(amhw_zlg118_gpio_afio_get(p_hw_gpio, pin) == AMHW_ZLG118_AFIO_NO)
    {
        p_gpio_devinfo->p_afio[pin] = AMHW_ZLG118_AFIO_NO;
    }

    return AM_OK;
}

/**
 * \brief ���Ź�������
 *
 * \param[in] pin   : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] flags : ���Ź���
 *
 * \return AM_OK �����óɹ�
 */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;
    amhw_zlg118_gpiomode_t  pin_mode   = AMHW_ZLG118_GPIO_MODE_IPU;
    uint32_t                func = 0, mode = 0;

    /* IO�ڷ��� */
    uint8_t dir = 0;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (AM_FALSE == __gp_gpio_dev->valid_flg) {
        return -AM_ENODEV;
    }

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    func = AM_GPIO_COM_FUNC_GET(flags);
    mode = AM_GPIO_COM_MODE_GET(flags);

    __am_zlg118_peripheral_afio_clear(pin);

    /* ��׼����� */
    if (0 != func) {

        /* ʹ�ñ�׼��ǰ���˻�����ΪGPIOģʽ */
        __am_zlg118_peripheral_afio_clear(pin);

        switch (func) {

        case AM_GPIO_INPUT_VAL:

            /* ���÷���Ϊ���� */
            amhw_zlg118_gpio_pin_dir_input(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH_VAL:

            /* ������� */
            amhw_zlg118_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_ZLG118_GPIO_MODE_OUT_PP,
                                          pin);

            /* ����ߵ�ƽ */
            amhw_zlg118_gpio_pin_out_high(p_hw_gpio, pin);

            break;

        case AM_GPIO_OUTPUT_INIT_LOW_VAL:

            /* ������� */
            amhw_zlg118_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_ZLG118_GPIO_MODE_OUT_PP,
                                          pin);

            /* ����͵�ƽ */
            amhw_zlg118_gpio_pin_out_low(p_hw_gpio, pin);

            break;

        default:
            return -AM_ENOTSUP;
        }
    }

    if (mode != 0x00) {

        /* ��ȡ����������� */
        dir = amhw_zlg118_gpio_pin_dir_get(p_hw_gpio, pin);

        switch (mode) {

        case AM_GPIO_PULL_UP_VAL:
            if (dir == 1) {

                /* ��������ģʽ  */
                pin_mode = AMHW_ZLG118_GPIO_MODE_IPU;

            } else {

                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_ZLG118_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_PULL_DOWN_VAL:
            if (dir == 1) {

                /* ��������ģʽ  */
                pin_mode = AMHW_ZLG118_GPIO_MODE_IPD;

            } else {

                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_ZLG118_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_FLOAT_VAL:
            if (dir == 1) {
                pin_mode = AMHW_ZLG118_GPIO_MODE_IN_FLOATING;
            } else {

                /* ���û�и���ģʽ������Ϊ��©ģʽ */
                pin_mode = AMHW_ZLG118_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_OPEN_DRAIN_VAL:
            if (dir == 1) {
                /* ����û�п�©ģʽ������Ϊ���� */
                pin_mode = AMHW_ZLG118_GPIO_MODE_IN_FLOATING;
            } else {
                pin_mode = AMHW_ZLG118_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_PUSH_PULL_VAL:
            if (dir == 1) {
                /* ����û������ģʽ������Ϊ���� */
                pin_mode = AMHW_ZLG118_GPIO_MODE_IPU;
            } else {
                pin_mode = AMHW_ZLG118_GPIO_MODE_OUT_PP;
            }
            break;

        default:
            return -AM_ENOTSUP;
        }

        amhw_zlg118_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ƽ̨��� */
    if (0 != (flags & AM_ZLG118_GPIO_MODE)) {

        /* ���������Ӧģʽ���� */

        switch (AM_ZLG118_GPIO_MODE_GET(flags)) {

        case 0:
            /* �������� */
            pin_mode = AMHW_ZLG118_GPIO_MODE_IPU;
            break;

        case 1:
            /* �������� */
            pin_mode = AMHW_ZLG118_GPIO_MODE_IPD;
            break;

        case 2:
            /* ģ������ */
            pin_mode = AMHW_ZLG118_GPIO_MODE_AIN;
            break;

        case 3:
            /* �������� */
            pin_mode = AMHW_ZLG118_GPIO_MODE_IN_FLOATING;
            break;

        case 4:
            /* �������  */
            pin_mode = AMHW_ZLG118_GPIO_MODE_OUT_PP;
            break;

        case 5:
            /* ��©��� */
            pin_mode = AMHW_ZLG118_GPIO_MODE_OUT_OD;
            break;

        case 6:
            /* ģ����� */
            pin_mode = AMHW_ZLG118_GPIO_MODE_AOUT;
            break;

        default:
            return -AM_ENOTSUP;
        }

        amhw_zlg118_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ��ӳ������ */
    if (0 != (flags & AM_ZLG118_GPIO_REMAP)) {

        __am_zlg118_peripheral_afio_clear(pin);

        amhw_zlg118_gpio_afio_set(
            p_hw_gpio,
            (amhw_zlg118_gpio_afio_t)AM_ZLG118_GPIO_REMAP_MODE_GET(flags),
            pin);
        p_gpio_devinfo->p_afio[pin] =
            (amhw_zlg118_gpio_afio_t)AM_ZLG118_GPIO_REMAP_MODE_GET(flags);
    }

    return AM_OK;
}

/**
 * \brief ��ȡGPIO����״̬
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \return ����״̬
 */
int am_gpio_get (int pin)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (0 == amhw_zlg118_gpio_pin_dir_get(p_hw_gpio, pin)) {
        return amhw_zlg118_gpio_pin_output_get(p_hw_gpio, pin);
    } else {
        return amhw_zlg118_gpio_pin_input_get(p_hw_gpio, pin);
    }
}

/**
 * \brief �����������״̬
 *
 * \param[in] pin   : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] value : ����״̬���μ�
 *                    \ref grp_am_gpio_pin_level
 *
 * \retval  AM_OK   : �����ɹ�
 */
int am_gpio_set (int pin, int value)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (value == 0) {
        amhw_zlg118_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_zlg118_gpio_pin_out_high(p_hw_gpio, pin);
    }

    return AM_OK;
}

/**
 * \brief ��תGPIO�������״̬
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_toggle (int pin)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;

    uint8_t t = 0;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    t= amhw_zlg118_gpio_pin_output_get(p_hw_gpio, pin);

    if(1 == t) {
        amhw_zlg118_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_zlg118_gpio_pin_out_high(p_hw_gpio, pin);
    }

    return AM_OK;
}

/**
 * \brief �˿�A���жϺ���
 */
static void __port_a_int_isr (void * p_arg)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;


    /* ���жϴ��� */
    for(pin = 0; pin < 16; pin++) {
        if (1 == amhw_zlg118_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_zlg118_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
}

/**
 * \brief �˿�B���жϺ���
 */
static void __port_b_int_isr (void * p_arg)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;


    /* ���жϴ��� */
    for(pin = 16; pin < 32; pin++) {
        if (1 == amhw_zlg118_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_zlg118_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
}

/**
 * \brief �˿�C/E���жϺ���
 */
static void __port_c_e_int_isr (void * p_arg)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    /* ���жϴ��� */
    for(pin = 32; pin < 48; pin++) {
        if (1 == amhw_zlg118_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_zlg118_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }

    /* ���жϴ��� */
    for(pin = 64; pin < 80; pin++) {
        if (1 == amhw_zlg118_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_zlg118_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
}

/**
 * \brief �˿�D/F���жϺ���
 */
static void __port_d_f_int_isr (void * p_arg)
{
    amhw_zlg118_gpio_t     *p_hw_gpio  = NULL;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    uint8_t      pin       = 0;

    p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    /* ���жϴ��� */
    for(pin = 48; pin < 64; pin++) {
        if (1 == amhw_zlg118_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_zlg118_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }

    /* ���жϴ��� */
    for(pin = 80; pin < 91; pin++) {
        if (1 == amhw_zlg118_gpio_pin_int_flag_get(p_hw_gpio, pin)) {

            /* ��ȡ�йػص����������� */
            pfn_isr   = p_gpio_devinfo->p_triginfo[pin].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[pin].p_arg;

            if (pfn_isr != NULL) {
                pfn_isr(p_arg_tmp);
            }
            /* ���жϱ�־ */
            amhw_zlg118_gpio_pin_int_flag_clr(p_hw_gpio, pin);
        }
    }
}

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zlg118_gpio_init (am_zlg118_gpio_dev_t           *p_dev,
                         const am_zlg118_gpio_devinfo_t *p_devinfo)
{
    uint8_t i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return -AM_EINVAL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;
    p_gpio_devinfo   = p_devinfo;

    if ((p_devinfo->p_afio == NULL) || (p_devinfo->inum_pin == NULL) ||
        (p_devinfo->p_infomap == NULL) || (p_devinfo->p_triginfo == NULL)) {
        p_dev->valid_flg = AM_FALSE;
        return -AM_EINVAL;
    }

    for (i = 0 ; i < p_devinfo->pin_count ; i++) {
        __am_zlg118_peripheral_afio_clear(i);
    }

    for (i = 0 ; i < p_devinfo->exti_num_max ; i++) {
        p_devinfo->p_infomap[i] = AM_ZLG118_GPIO_INVALID_PIN_MAP;
        p_devinfo->p_triginfo[i].p_arg = NULL;
        p_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_connect(p_devinfo->inum_pin[0], __port_a_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[1], __port_b_int_isr, NULL);
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
void am_zlg118_gpio_deinit (void)
{
    uint8_t i;

    if (p_gpio_devinfo->pfn_plfm_deinit) {
        p_gpio_devinfo->pfn_plfm_deinit();
    }

    if (__gp_gpio_dev->valid_flg == AM_FALSE) {
        return;
    }

    for (i = 0 ; i < p_gpio_devinfo->pin_count ; i++) {
        __am_zlg118_peripheral_afio_clear(i);
    }

    for (i = 0 ; i < p_gpio_devinfo->exti_num_max ; i++) {
        p_gpio_devinfo->p_infomap[i] = AM_ZLG118_GPIO_INVALID_PIN_MAP;
        p_gpio_devinfo->p_triginfo[i].p_arg = NULL;
        p_gpio_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_disable(p_gpio_devinfo->inum_pin[0]);
    am_int_disable(p_gpio_devinfo->inum_pin[1]);
    am_int_disable(p_gpio_devinfo->inum_pin[2]);
    am_int_disable(p_gpio_devinfo->inum_pin[3]);

    am_int_disconnect(p_gpio_devinfo->inum_pin[0], __port_a_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[1], __port_b_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[2], __port_c_e_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[3], __port_d_f_int_isr, NULL);

    __gp_gpio_dev = NULL;
}

/**
 * \brief ����GPIO���Ŵ�������
 *
 * \param[in] pin  : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] flag : ���ò������μ�
 *                   \ref grp_am_gpio_pin_trigger_function
 *
 * \retval AM_OK   : ���óɹ�
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    uint8_t                 slot       = pin;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    if (p_gpio_devinfo->p_infomap[slot] != pin) {
        return -AM_EINVAL;
    }

    switch (flag) {

    case AM_GPIO_TRIGGER_OFF:
        break;

    case AM_GPIO_TRIGGER_HIGH:
        __gp_gpio_dev->int_type = AM_GPIO_TRIGGER_HIGH;
        break;

    case AM_GPIO_TRIGGER_LOW:
        __gp_gpio_dev->int_type = AM_GPIO_TRIGGER_LOW;
        break;

    case AM_GPIO_TRIGGER_RISE:
        __gp_gpio_dev->int_type = AM_GPIO_TRIGGER_RISE;
        break;

    case AM_GPIO_TRIGGER_FALL:
        __gp_gpio_dev->int_type = AM_GPIO_TRIGGER_FALL;
        break;

    case AM_GPIO_TRIGGER_BOTH_EDGES:
        __gp_gpio_dev->int_type = AM_GPIO_TRIGGER_BOTH_EDGES;
        break;

    default:
        return -AM_ENOTSUP;
    }

    return AM_OK;
}

/**
 * \brief ���ӻص�����������
 *
 * \param[in] pin          : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص���������ڲ���
 *
 * \retval  AM_OK          : �����ɹ�
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

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    key = am_int_cpu_lock();

    if (p_gpio_devinfo->p_infomap[slot] == AM_ZLG118_GPIO_INVALID_PIN_MAP) {

        p_gpio_devinfo->p_infomap[slot] = pin;
        p_gpio_devinfo->p_triginfo[slot].p_arg = p_arg;
        p_gpio_devinfo->p_triginfo[slot].pfn_callback = pfn_callback;

    } else {

        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }

    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ɾ�����ӵ����ŵĻص�����
 *
 * \param[in] pin          : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص���������ڲ���
 *
 * \retval  AM_OK          : �����ɹ�
 */
int am_gpio_trigger_disconnect(int           pin,
                               am_pfnvoid_t  pfn_callback,
                               void         *p_arg)
{
    uint8_t                  slot        = pin;
    int key;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    key = am_int_cpu_lock();

    if (p_gpio_devinfo->p_infomap[slot] == pin) {

        p_gpio_devinfo->p_infomap[slot] = AM_ZLG118_GPIO_INVALID_PIN_MAP;
        p_gpio_devinfo->p_triginfo[slot].p_arg = NULL;
        p_gpio_devinfo->p_triginfo[slot].pfn_callback = NULL;

    } else {
        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }

    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ʹ�����Ŵ����ж�
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_trigger_on(int pin)
{
    uint8_t             slot       = pin;
    amhw_zlg118_gpio_t *p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    if (p_gpio_devinfo->p_infomap[slot] == pin) {

        switch (__gp_gpio_dev->int_type) {

            case AM_GPIO_TRIGGER_HIGH:
                amhw_zlg118_gpio_pin_high_int_enable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_low_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_raising_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_falling_int_disable(p_hw_gpio,pin);
                break;

            case AM_GPIO_TRIGGER_LOW:
                amhw_zlg118_gpio_pin_high_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_low_int_enable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_raising_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_falling_int_disable(p_hw_gpio,pin);
                break;

            case AM_GPIO_TRIGGER_RISE:
                amhw_zlg118_gpio_pin_high_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_low_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_raising_int_enable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_falling_int_disable(p_hw_gpio,pin);
                break;

            case AM_GPIO_TRIGGER_FALL:
                amhw_zlg118_gpio_pin_high_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_low_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_raising_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_falling_int_enable(p_hw_gpio,pin);
                break;

            case AM_GPIO_TRIGGER_BOTH_EDGES:
                amhw_zlg118_gpio_pin_high_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_low_int_disable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_raising_int_enable(p_hw_gpio,pin);
                amhw_zlg118_gpio_pin_falling_int_enable(p_hw_gpio,pin);
                break;
        }
    } else {
        return -AM_ENXIO;
    }

    return AM_OK;
}

/**
 * \brief �������Ŵ����ж�
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_trigger_off(int pin)
{
    uint8_t             slot       = pin;
    amhw_zlg118_gpio_t *p_hw_gpio  = (amhw_zlg118_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    /* �ر�ĳһ���ŵ����д����ж� */
    if (p_gpio_devinfo->p_infomap[slot] == pin) {
        amhw_zlg118_gpio_pin_high_int_disable(p_hw_gpio,pin);
        amhw_zlg118_gpio_pin_low_int_disable(p_hw_gpio,pin);
        amhw_zlg118_gpio_pin_raising_int_disable(p_hw_gpio,pin);
        amhw_zlg118_gpio_pin_falling_int_disable(p_hw_gpio,pin);
    } else {
        return -AM_ENXIO;
    }

    return AM_OK;
}

/* end of file */
