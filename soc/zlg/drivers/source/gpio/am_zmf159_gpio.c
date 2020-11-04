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
 * - 1.00 19-02-22  ipk,first implementation
 * \endinternal
 */

#include "am_zmf159_gpio.h"
#include "am_gpio_util.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_bitops.h"
#include "hw/amhw_zmf159_exti.h"
#include "zmf159_pin.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define AM_ZMF159_GPIO_INVALID_PIN_MAP    0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev)  \
        const am_zmf159_gpio_devinfo_t *p_gpio_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_zmf159_gpio_dev_t *__gp_gpio_dev;

/**
 * \brief �ⲿ�ж���0�жϺ���
 */
static void __port_exit0_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 0;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zmf159_exti_t   *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zmf159_exti_pr_read(p_hw_exti,
                                 (amhw_zmf159_exti_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zmf159_exti_pending_clear(p_hw_exti,
                                   (amhw_zmf159_exti_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���1�жϺ���
 */
static void __port_exit1_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 1;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zmf159_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zmf159_exti_pr_read(p_hw_exti,
                                 (amhw_zmf159_exti_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zmf159_exti_pending_clear(p_hw_exti,
                                   (amhw_zmf159_exti_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���2�жϺ���
 */
static void __port_exit2_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 2;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zmf159_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zmf159_exti_pr_read(p_hw_exti,
                                 (amhw_zmf159_exti_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zmf159_exti_pending_clear(p_hw_exti,
                                   (amhw_zmf159_exti_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���2�жϺ���
 */
static void __port_exit3_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 3;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zmf159_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zmf159_exti_pr_read(p_hw_exti,
                                 (amhw_zmf159_exti_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zmf159_exti_pending_clear(p_hw_exti,
                                   (amhw_zmf159_exti_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���4�жϺ���
 */
static void __port_exit4_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 4;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zmf159_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zmf159_exti_pr_read(p_hw_exti,
                                 (amhw_zmf159_exti_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zmf159_exti_pending_clear(p_hw_exti,
                                   (amhw_zmf159_exti_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���9_5�жϺ���
 */
static void __port_exit9_5_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    am_pfnvoid_t pfn_isr    = NULL;
    void         *p_arg_tmp = NULL;
    uint8_t      slot       = 5;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zmf159_exti_t   *)p_gpio_devinfo->exti_regbase;

    for (slot = 5 ; slot < 10 ; slot++) {
        if (amhw_zmf159_exti_pr_read(p_hw_exti,
                                     (amhw_zmf159_exti_line_num_t)(1ul << slot))) {

            pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

            if (NULL != pfn_isr) {
                pfn_isr(p_arg_tmp);
            }

            amhw_zmf159_exti_pending_clear(p_hw_exti,
                                         (amhw_zmf159_exti_line_num_t)(1ul << slot));

            break;
        }
    }
}

/**
 * \brief �ⲿ�ж���5_10�жϺ���
 */
static void __port_exit15_10_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    am_pfnvoid_t pfn_isr    = NULL;
    void         *p_arg_tmp = NULL;
    uint8_t      slot       = 10;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zmf159_exti_t   *)p_gpio_devinfo->exti_regbase;

    for (slot = 10 ; slot < 16 ; slot++) {
        if (amhw_zmf159_exti_pr_read(p_hw_exti,
                                     (amhw_zmf159_exti_line_num_t)(1ul << slot))) {

            pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

            if (NULL != pfn_isr) {
                pfn_isr(p_arg_tmp);
            }

            amhw_zmf159_exti_pending_clear(p_hw_exti,
                                         (amhw_zmf159_exti_line_num_t)(1ul << slot));

            break;
        }
    }
}

/*******************************************************************************
  ��������
*******************************************************************************/

/**
 * \brief ���Ź�������
 *
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] flags     : ���Ź���
 *
 * \return AM_OK     �����óɹ�
 */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    /* IO�ڷ��� */
    uint8_t dir = 0;

    uint32_t func = 0, mode = 0;

    uint32_t iocon_cfg = 0;

    amhw_zlg_gpio_t *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio = (amhw_zlg_gpio_t*)p_gpio_devinfo->gpio_regbase;

    func      = AM_GPIO_COM_FUNC_GET(flags);
    mode      = AM_GPIO_COM_MODE_GET(flags) << 3;

    /*
     * ���й�������
     */
    if (func != 0x00) {

        /* ��������Ҫ�����÷��� */
        flags &= ~AM_ZLG116_GPIO_DIR;

        /* ��������Ҫ���������Ÿ��ù��ܣ���ʹ��GPIO���� */
        flags &= ~AM_ZMF159_GPIO_FUNEN;

        if (amhw_zlg_gpio_pin_afr_get(p_hw_gpio, pin) != AMHW_ZLG_GPIO_AF_DEFAULT) {

            /* ���ù��ܻص�Ĭ��״̬������ʹ��GPIO���� */
            amhw_zlg_gpio_pin_afr_set(p_hw_gpio, AMHW_ZLG_GPIO_AF_DEFAULT, pin);

        }

        switch (func) {

        case AM_GPIO_INPUT:
            AM_BITS_SET(iocon_cfg, 0, 2, 0X00);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH:

            amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

            /* ���ʱ����δ���ùܽ�������Ĭ��Ϊ 10MHz */
            if ((flags & AM_ZMF159_GPIO_OUTRES_RATE) == 0) {
                AM_BITS_SET(iocon_cfg, 0, 2, AMHW_ZLG_GPIO_SPEED_10MHz);
            }

            dir = 1;

            break;

        case AM_GPIO_OUTPUT_INIT_LOW:
            amhw_zlg_gpio_pin_out_low(p_hw_gpio, pin);

            /* ���ʱ����δ���ùܽ�������Ĭ��Ϊ 10MHz */
            if ((flags & AM_ZMF159_GPIO_OUTRES_RATE) == 0) {
                AM_BITS_SET(iocon_cfg, 0, 2, AMHW_ZLG_GPIO_SPEED_10MHz);
            }

            dir = 1;

            break;

        default:
            break;
        }
    }

    if (mode != 0x00) {

        switch (mode) {

        case AM_GPIO_PULLUP:
            if (dir != 1) {

                /* ʹODλ��Ϊ1, ���������� */
                amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IPU);
            } else {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_OUT_PP);
            }
            break;

        case AM_GPIO_PULLDOWN:
            if (dir != 1) {

                /* ʹODλ��Ϊ0, ���������� */
                amhw_zlg_gpio_pin_out_low(p_hw_gpio, pin);
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IPD);
            } else {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_OUT_PP);
            }
            break;

        case AM_GPIO_FLOAT:
            if (dir != 1) {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IN_FLOATING);
            } else {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_OUT_OD);
            }
            break;

        case AM_GPIO_OPEN_DRAIN:
            if (dir == 0) {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IN_FLOATING);
            } else {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_OUT_OD);
            }
            break;

        case AM_GPIO_PUSH_PULL:
            if (dir == 0) {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IPU);
            } else {
                AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_OUT_PP);
            }
            break;

        default:
            return -AM_ENOTSUP;
        }
    }

    /*
     * ƽ̨�������
     */

    /* �ܽŵ�ģʽ */
    if ((flags & AM_ZMF159_GPIO_MODE) != 0) {

       switch (AM_ZMF159_GPIO_MODE_GET(flags)) {

       case 0:
           AM_BITS_SET(iocon_cfg, 0, 2, 0x00);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_AIN);

           break;

       case 1:
           AM_BITS_SET(iocon_cfg, 0, 2, 0x00);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IN_FLOATING);

           break;

       case 2:

           /* ʹODλ��Ϊ0, ���������� */
           amhw_zlg_gpio_pin_out_low(p_hw_gpio, pin);
           AM_BITS_SET(iocon_cfg, 0, 2, 0x00);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IPD);

           break;

       case 3:

           /* ʹODλ��Ϊ1, ���������� */
           amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);
           AM_BITS_SET(iocon_cfg, 0, 2, 0x00);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_IPU);

           break;

       case 4:
           AM_BITS_SET(iocon_cfg, 0, 2, AMHW_ZLG_GPIO_SPEED_10MHz);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_OUT_PP);

           break;

       case 5:
           AM_BITS_SET(iocon_cfg, 0, 2, AMHW_ZLG_GPIO_SPEED_10MHz);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_OUT_OD);

           break;

       case 6:
           AM_BITS_SET(iocon_cfg, 0, 2, AMHW_ZLG_GPIO_SPEED_10MHz);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_AF_PP);

           break;

       case 7:
           AM_BITS_SET(iocon_cfg, 0, 2, AMHW_ZLG_GPIO_SPEED_10MHz);
           AM_BITS_SET(iocon_cfg, 2, 2, AMHW_ZLG_GPIO_MODE_AF_OD);
           break;

       default:
           return -AM_ENOTSUP;
       }
    }

    /* ���ùܽŵ�������� */
    if ((flags & AM_ZMF159_GPIO_OUTRES_RATE) != 0) {

        AM_BITS_SET(iocon_cfg, 0, 2, AM_ZMF159_GPIO_OUTRES_RATE_GET(flags));

    }

    /* ���ùܽŵĸ��ù��� */
    if ((flags & AM_ZMF159_GPIO_FUNEN) != 0) {
        amhw_zlg_gpio_pin_afr_set(p_hw_gpio, AM_ZMF159_GPIO_FUNC_GET(flags), pin);
    }

    /* ���ø��ù���ʱ�ܽ�ģʽ */
    amhw_zlg_gpio_pin_set(p_hw_gpio, iocon_cfg, pin);

    return AM_OK;
}

/**
 * \brief ��ȡ����״̬
 *
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
int am_gpio_get (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_zlg_gpio_t *p_hw_gpio = (amhw_zlg_gpio_t *)p_gpio_devinfo->gpio_regbase;

    return amhw_zlg_gpio_pin_get(p_hw_gpio, pin);
}

/**
 * \brief �����������״̬
 *
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] value     : ����ֵ
 *
 * \return AM_OK     �����óɹ�
 */
int am_gpio_set (int pin, int value)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_zlg_gpio_t *p_hw_gpio = (amhw_zlg_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (value == 0) {
        amhw_zlg_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

    }
    return AM_OK;
}

/**
 * \brief �������״̬��ת
 */
int am_gpio_toggle (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_zlg_gpio_t *p_hw_gpio = (amhw_zlg_gpio_t *)p_gpio_devinfo->gpio_regbase;

    amhw_zlg_gpio_pin_toggle(p_hw_gpio, pin);

    return AM_OK;
}

/**
 * \brief ���Ŵ�����ʽ����
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int  port = 0;
    int  slot = -1;

    amhw_zlg_gpio_t   *p_hw_gpio   = NULL;
    amhw_zlg_syscfg_t *p_hw_syscfg = NULL;
    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    port = pin >> 4;       /* ������Ŷ�Ӧ�Ķ˿ں� */

    if (port > 3) {        /* �˿ڲ����� */
        return -AM_EINVAL;
    }

    p_hw_gpio   = (amhw_zlg_gpio_t   *)p_gpio_devinfo->gpio_regbase;
    p_hw_syscfg = (amhw_zlg_syscfg_t *)p_gpio_devinfo->syscfg_regbase;
    p_hw_exti   = (amhw_zmf159_exti_t   *)p_gpio_devinfo->exti_regbase;

    /* ��û�п�ʼ���ùܽ� */
    if ((p_gpio_devinfo->p_infomap)[pin & 0x0f] == pin) {
        slot = pin & 0x0f;
    } else {
        return -AM_ENXIO;
    }

    /* ���ù��ܻص�Ĭ��״̬������ʹ��GPIO���� */
    amhw_zlg_gpio_pin_afr_set(p_hw_gpio, AMHW_ZLG_GPIO_AF_DEFAULT, pin);

    /* ������Ӹ��ж���������ΪGPIO���ܵĺ������� */

    /* ���ùܽ�Ϊ���뷽�� */
    amhw_zlg_gpio_pin_dir_input(p_hw_gpio, pin);

    /* �ܽ�Ϊ����/����ģʽ */
    amhw_zlg_gpio_pin_mode_set(p_hw_gpio, AMHW_ZLG_GPIO_MODE_IPD, pin);

    /*
     * �ж���0ֻ����һ���˿ڱ��Ϊ0��GPIO���ţ�����˵��PIOA_0���ӵ����ж���0��
     * PIOB_0��PIOC_0��PIOD_0�Ͳ��������ж���0, ����ʱPIOA_1�������ӵ��ж���1��
     */
    amhw_zlg_syscfg_exti_line_config(p_hw_syscfg, port, slot);

    /* ����ж������� */
    amhw_zmf159_exti_imr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));
    amhw_zmf159_exti_emr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

    /* ����ж��ߴ�����ʽ���� */
    amhw_zmf159_exti_rtsr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));
    amhw_zmf159_exti_ftsr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

    switch (flag) {

    case AM_GPIO_TRIGGER_OFF:           /* �رմ��� */
        amhw_zmf159_exti_imr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));
        amhw_zmf159_exti_emr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));
        break;

    case AM_GPIO_TRIGGER_HIGH:          /* �ߵ�ƽ���� */
        return -AM_ENOTSUP;

    case AM_GPIO_TRIGGER_LOW:           /* �͵�ƽ���� */
        return -AM_ENOTSUP;

    case AM_GPIO_TRIGGER_RISE:          /* �����ش��� */

        /* ʹODλ��Ϊ0, ���������� */
        amhw_zlg_gpio_pin_out_low(p_hw_gpio, pin);

        /* rising  edge */
        amhw_zmf159_exti_rtsr_set(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

        break;

    case AM_GPIO_TRIGGER_FALL:          /* �½��ش��� */

        /* ʹODλ��Ϊ1, ���������� */
        amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

        /* falling  edge */
        amhw_zmf159_exti_ftsr_set(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

        break;

    case AM_GPIO_TRIGGER_BOTH_EDGES:    /* ˫���ش��� */

        /* ʹODλ��Ϊ1, ���������� */
        amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

        /* rising falling edge */
        amhw_zmf159_exti_rtsr_set(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));
        amhw_zmf159_exti_ftsr_set(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

        break;

    default:
        break;
    }

    return AM_OK;
}

/**
 * \brief ʹ�������жϡ�
 */
int am_gpio_trigger_on (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int slot = -1;
    int port = 0;

    int err = 0;

    uint32_t extipinsource = 0;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    port = pin >> 4;       /* ������Ŷ�Ӧ�Ķ˿ں� */

    if (port > 3) {        /* �˿ڲ����� */
        return -AM_EINVAL;
    }

    extipinsource = pin & 0x0f;

    /* ��û�п�ʼ���ùܽ� */
    if ((p_gpio_devinfo->p_infomap)[extipinsource] == pin) {
        slot = extipinsource;
    } else {
        return -AM_ENXIO;
    }

    p_hw_exti   = (amhw_zmf159_exti_t   *)p_gpio_devinfo->exti_regbase;

    /* �������ж��߱�־λ */
    amhw_zmf159_exti_pending_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

    /* ���ÿ����ж������� */
    amhw_zmf159_exti_imr_set(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

    return err;
}

/**
 * \brief ���������жϡ�
 */
int am_gpio_trigger_off (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int slot = -1;
    int port = 0;

    uint32_t extipinsource = 0;

    amhw_zmf159_exti_t   *p_hw_exti   = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    port = pin >> 4;       /* ������Ŷ�Ӧ�Ķ˿ں� */

    if (port > 3) {        /* �˿ڲ����� */
        return -AM_EINVAL;
    }

    extipinsource = pin & 0x0f;

    /* ��û�п�ʼ���ùܽ� */
    if ((p_gpio_devinfo->p_infomap)[extipinsource] == pin) {
        slot = extipinsource;
    } else {
        return -AM_ENXIO;
    }

    p_hw_exti = (amhw_zmf159_exti_t *)p_gpio_devinfo->exti_regbase;

    /* �����ж������� */
    amhw_zmf159_exti_imr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));
    amhw_zmf159_exti_emr_clear(p_hw_exti, (amhw_zmf159_exti_line_num_t)(1UL << slot));

    return AM_OK;
}

/**
 * \brief ���������жϻص�����
 */
int am_gpio_trigger_connect (int           pin,
                             am_pfnvoid_t  pfn_callback,
                             void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int      key;

    int      slot      = -1;
    int      port      = 0;

    uint32_t extipinsource = 0;

    am_bool_t already = AM_FALSE;

    extipinsource = pin & 0x0f;

    port = pin >> 4;

    if (port > 3) {
        return -AM_EINVAL;
    }

    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();

    if ((p_gpio_devinfo->p_infomap)[extipinsource] == AM_ZMF159_GPIO_INVALID_PIN_MAP) {
        slot = extipinsource;
    }  else {
        already = AM_TRUE;
    }

    if (already) {

        /* ��CPU�ж� */
        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }

    if (-1 != slot) {

        /*  ���津�����ż��ص����� */
        (p_gpio_devinfo->p_infomap)[slot]               = pin;
        (p_gpio_devinfo->p_triginfo)[slot].pfn_callback = pfn_callback;
        (p_gpio_devinfo->p_triginfo)[slot].p_arg        = p_arg;

        /* ���ж� */
        am_int_cpu_unlock(key);

    }

     return AM_OK;
}

/**
 * \brief ɾ�������жϻص���������
 */
int am_gpio_trigger_disconnect (int           pin,
                                am_pfnvoid_t  pfn_callback,
                                void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int key;

    int port = 0;

    int slot = -1;

    uint32_t extipinsource = 0;

    port = pin >> 4;

    if (port > 3) {
     return -AM_EINVAL;
    }

    extipinsource = pin & 0x0f;

    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();

    if ((p_gpio_devinfo->p_infomap)[extipinsource] == pin) {
      slot = extipinsource;
    }

    if (slot == -1) {

        /* ��CPU�ж� */
        am_int_cpu_unlock(key);

        return -AM_EINVAL;
    }

    (p_gpio_devinfo->p_infomap)[slot]               = AM_ZMF159_GPIO_INVALID_PIN_MAP;
    (p_gpio_devinfo->p_triginfo)[slot].pfn_callback = NULL;

    /* ��CPU�ж� */
    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zmf159_gpio_init (am_zmf159_gpio_dev_t           *p_dev,
                         const am_zmf159_gpio_devinfo_t *p_devinfo)
{
    uint8_t i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return -AM_EINVAL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;

    if ((p_devinfo->inum_pin == NULL)  ||
        (p_devinfo->p_infomap == NULL) ||
        (p_devinfo->p_triginfo == NULL)) {
        p_dev->valid_flg = AM_FALSE;
        return -AM_EINVAL;
    }

//    for (i = 0 ; i < p_devinfo->pin_count ; i++) {
//        if ((i == PIOA_13) || (i == PIOA_14) || (i == PIOA_15) ||
//             (i == PIOB_3) || (i == PIOB_4)) {
//            p_devinfo->p_remap[i] = AMHW_ZLG217_SWJ_CFG;
//        } else {
//            p_devinfo->p_remap[i] = AMHW_ZLG217_NO_REMAP;
//        }
//    }

    for (i = 0 ; i < p_devinfo->exti_num_max ; i++) {
        p_devinfo->p_infomap[i] = AM_ZMF159_GPIO_INVALID_PIN_MAP;
        p_devinfo->p_triginfo[i].p_arg = NULL;
        p_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_connect(p_devinfo->inum_pin[0], __port_exit0_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[1], __port_exit1_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[2], __port_exit2_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[3], __port_exit3_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[4], __port_exit4_int_isr, NULL);

    am_int_connect(p_devinfo->inum_pin[5], __port_exit9_5_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[6], __port_exit15_10_int_isr, NULL);

    am_int_enable(p_devinfo->inum_pin[0]);
    am_int_enable(p_devinfo->inum_pin[1]);
    am_int_enable(p_devinfo->inum_pin[2]);
    am_int_enable(p_devinfo->inum_pin[3]);
    am_int_enable(p_devinfo->inum_pin[4]);
    am_int_enable(p_devinfo->inum_pin[5]);
    am_int_enable(p_devinfo->inum_pin[6]);

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
void am_zmf159_gpio_deinit (void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int i = 0;

    if (__gp_gpio_dev->valid_flg) {
        for (i = 0; i < p_gpio_devinfo->exti_num_max; i++) {
            (p_gpio_devinfo->p_infomap)[i]               = AM_ZMF159_GPIO_INVALID_PIN_MAP;
            (p_gpio_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    am_int_disable((p_gpio_devinfo->inum_pin)[0]);
    am_int_disable((p_gpio_devinfo->inum_pin)[1]);
    am_int_disable((p_gpio_devinfo->inum_pin)[2]);

    am_int_disconnect(p_gpio_devinfo->inum_pin[0], __port_exit0_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[1], __port_exit1_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[2], __port_exit2_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[3], __port_exit3_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[4], __port_exit4_int_isr, NULL);

    am_int_disconnect(p_gpio_devinfo->inum_pin[5], __port_exit9_5_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[6], __port_exit15_10_int_isr, NULL);

    if (__gp_gpio_dev->p_devinfo->pfn_plfm_deinit) {
        __gp_gpio_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
