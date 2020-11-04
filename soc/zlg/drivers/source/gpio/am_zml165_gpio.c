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
 * \brief GPIO implementation
 *
 * - GPIO pins can be configured as input or output by software.
 * - All GPIO pins default to inputs with interrupt disabled at reset.
 * - Pin registers allow pins to be sensed and set individually.
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt,first implementation
 * \endinternal
 */

#include "am_zml165_gpio.h"
#include "am_zml165_gpio_util.h"
#include "am_gpio_util.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_bitops.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define AM_ZML165_GPIO_INVALID_PIN_MAP    0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev)  \
        const am_zml165_gpio_devinfo_t *p_gpio_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_zml165_gpio_dev_t *__gp_gpio_dev;

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
        flags &= ~AM_ZML165_GPIO_DIR;

        /* ��������Ҫ���������Ÿ��ù��ܣ���ʹ��GPIO���� */
        flags &= ~AM_ZML165_GPIO_FUNEN;

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
            if ((flags & AM_ZML165_GPIO_OUTRES_RATE) == 0) {
                AM_BITS_SET(iocon_cfg, 0, 2, AMHW_ZLG_GPIO_SPEED_10MHz);
            }

            dir = 1;

            break;

        case AM_GPIO_OUTPUT_INIT_LOW:
            amhw_zlg_gpio_pin_out_low(p_hw_gpio, pin);

            /* ���ʱ����δ���ùܽ�������Ĭ��Ϊ 10MHz */
            if ((flags & AM_ZML165_GPIO_OUTRES_RATE) == 0) {
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
    if ((flags & AM_ZML165_GPIO_MODE) != 0) {

       switch (AM_ZML165_GPIO_MODE_GET(flags)) {

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
    if ((flags & AM_ZML165_GPIO_OUTRES_RATE) != 0) {

        AM_BITS_SET(iocon_cfg, 0, 2, AM_ZML165_GPIO_OUTRES_RATE_GET(flags));

    }

    /* ���ø��ù���ʱ�ܽ�ģʽ */
    amhw_zlg_gpio_pin_set(p_hw_gpio, iocon_cfg, pin);

    /* ���ùܽŵĸ��ù��� */
    if ((flags & AM_ZML165_GPIO_FUNEN) != 0) {
        amhw_zlg_gpio_pin_afr_set(p_hw_gpio, AM_ZML165_GPIO_FUNC_GET(flags), pin);
    }

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
    amhw_zlg_exti_t   *p_hw_exti   = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    port = pin >> 4;       /* ������Ŷ�Ӧ�Ķ˿ں� */

    if (port > 3) {        /* �˿ڲ����� */
        return -AM_EINVAL;
    }

    p_hw_gpio   = (amhw_zlg_gpio_t   *)p_gpio_devinfo->gpio_regbase;
    p_hw_syscfg = (amhw_zlg_syscfg_t *)p_gpio_devinfo->syscfg_regbase;
    p_hw_exti   = (amhw_zlg_exti_t   *)p_gpio_devinfo->exti_regbase;

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
    amhw_zlg_exti_imr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
    amhw_zlg_exti_emr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

    /* ����ж��ߴ�����ʽ���� */
    amhw_zlg_exti_rtsr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
    amhw_zlg_exti_ftsr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

    switch (flag) {

    case AM_GPIO_TRIGGER_OFF:           /* �رմ��� */
        amhw_zlg_exti_imr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
        amhw_zlg_exti_emr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
        break;

    case AM_GPIO_TRIGGER_HIGH:          /* �ߵ�ƽ���� */
        return -AM_ENOTSUP;

    case AM_GPIO_TRIGGER_LOW:           /* �͵�ƽ���� */
        return -AM_ENOTSUP;

    case AM_GPIO_TRIGGER_RISE:          /* �����ش��� */

        /* ʹODλ��Ϊ0, ���������� */
        amhw_zlg_gpio_pin_out_low(p_hw_gpio, pin);

        /* rising  edge */
        amhw_zlg_exti_rtsr_set(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

        break;

    case AM_GPIO_TRIGGER_FALL:          /* �½��ش��� */

        /* ʹODλ��Ϊ1, ���������� */
        amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

        /* falling  edge */
        amhw_zlg_exti_ftsr_set(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

        break;

    case AM_GPIO_TRIGGER_BOTH_EDGES:    /* ˫���ش��� */

        /* ʹODλ��Ϊ1, ���������� */
        amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

        /* rising falling edge */
        amhw_zlg_exti_rtsr_set(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
        amhw_zlg_exti_ftsr_set(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

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

    amhw_zlg_exti_t   *p_hw_exti   = NULL;

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

    p_hw_exti   = (amhw_zlg_exti_t   *)p_gpio_devinfo->exti_regbase;

    /* �������ж��߱�־λ */
    amhw_zlg_exti_pending_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

    /* ���ÿ����ж������� */
    amhw_zlg_exti_imr_set(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

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

    amhw_zlg_exti_t   *p_hw_exti   = NULL;

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

    p_hw_exti = (amhw_zlg_exti_t *)p_gpio_devinfo->exti_regbase;

    /* �����ж������� */
    amhw_zlg_exti_imr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
    amhw_zlg_exti_emr_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

    return AM_OK;
}

/**
 * \brief GPIO �жϷ�����Ӧ������
 *
 * \param[in] p_arg : ��ǰ�ж�ӳ����
 *
 * \return ��
 */
static void __port_exit0_1_int_isr (void *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int          slot      = 0;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg_exti_t *p_hw_exti = NULL;

    p_hw_exti = (amhw_zlg_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    /* �ж��ж��߹����־�Ƿ���λ */
    if (amhw_zlg_exti_pr_read(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot)) != 0) {

        /* ��ȡ�йػص����������� */
        pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
        p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    } else {

        /* ��ȡ�йػص����������� */
        pfn_isr   = p_gpio_devinfo->p_triginfo[slot + 1].pfn_callback;
        p_arg_tmp = p_gpio_devinfo->p_triginfo[slot + 1].p_arg;

        slot = 1;
    }

    /* �����û����жϴ����߼� */
    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }

    /* ���жϱ�־ */
    amhw_zlg_exti_pending_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
}

/**
 * \brief GPIO �жϷ�����Ӧ����
 *
 * \param[in] p_arg : ��ǰ�ж�ӳ����
 *
 * \return ��
 */
static void __port_exit2_3_int_isr (void *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int          slot      = 2;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg_exti_t *p_hw_exti = NULL;

    p_hw_exti = (amhw_zlg_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    /* �ж��ж��߹����־�Ƿ���λ */
    if (amhw_zlg_exti_pr_read(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot)) != 0) {

        /* ��ȡ�йػص����������� */
        pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
        p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    } else {

        /* ��ȡ�йػص����������� */
        pfn_isr   = p_gpio_devinfo->p_triginfo[slot + 1].pfn_callback;
        p_arg_tmp = p_gpio_devinfo->p_triginfo[slot + 1].p_arg;

        slot = 3;
    }

    /* �����û����жϴ����߼� */
    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }

    /* ���жϱ�־ */
    amhw_zlg_exti_pending_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));
}

/**
 * \brief ����״̬�Ĵ���ת��Ϊ�жϺ�
 */
static int __get_inum (uint32_t int_status)
{
    int i = 0;
    if (int_status == 0) {
        return -AM_EINVAL;
    }

    for (i = 4; i < 16; ++i)  {
        if (((int_status >> i) & 0x0001) != 0){
            break;
        }

    }
    return i;
}

/**
 * \brief GPIO �жϷ�����Ӧ����
 *
 * \param[in] p_arg : ��ǰ�ж�ӳ����
 *
 * \return ��
 */
static void __port_exit4_15_int_isr (void *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int          slot      =  0;
    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg_exti_t   *p_hw_exti = NULL;

    p_hw_exti = (amhw_zlg_exti_t *)p_gpio_devinfo->exti_regbase;

    slot =  __get_inum(p_hw_exti->pr);

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    /* �����û����жϴ����߼� */
    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }

    /* ���жϱ�־ */
    amhw_zlg_exti_pending_clear(p_hw_exti, (amhw_zlg_exti_line_num_t)(1UL << slot));

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

    if ((p_gpio_devinfo->p_infomap)[extipinsource] == AM_ZML165_GPIO_INVALID_PIN_MAP) {
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

    (p_gpio_devinfo->p_infomap)[slot]               = AM_ZML165_GPIO_INVALID_PIN_MAP;
    (p_gpio_devinfo->p_triginfo)[slot].pfn_callback = NULL;

    /* ��CPU�ж� */
    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief GPIO��ʼ��
 */
int am_zml165_gpio_init (am_zml165_gpio_dev_t           *p_dev,
                         const am_zml165_gpio_devinfo_t *p_devinfo)
{
    int i;

    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }

    /* GPIOƽ̨��ʼ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* GPIO�豸�ṹ���ʼ�� */
    p_dev->p_devinfo  = p_devinfo;
    __gp_gpio_dev     = p_dev;
    p_dev->valid_flg  = AM_TRUE;

    if ((p_devinfo->p_triginfo == NULL) ||
        (p_devinfo->p_infomap == NULL)) {
        p_dev->valid_flg = AM_FALSE;
    }

    /* ��ʼ��ÿ�����ŵĻص���������������ʽ�ڴ�ӳ�� */
    if (p_dev->valid_flg) {
        for (i = 0; i < p_devinfo->pint_count; i++) {
            (p_devinfo->p_infomap)[i]              = AM_ZML165_GPIO_INVALID_PIN_MAP;
            (p_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    /* ����GPIO���ŵ��жϴ����� */
    am_int_connect((p_devinfo->inum_pin)[0], /* д���жϺ� */
                   (am_pfnvoid_t)__port_exit0_1_int_isr,
                   (void *)p_devinfo);
    am_int_connect((p_devinfo->inum_pin)[1], /* д���жϺ� */
                   (am_pfnvoid_t)__port_exit2_3_int_isr,
                   (void *)p_devinfo);
    am_int_connect((p_devinfo->inum_pin)[2], /* д���жϺ� */
                   (am_pfnvoid_t)__port_exit4_15_int_isr,
                   (void *)p_devinfo);

    /* ʹ��GPIO��NVIC�ж� */
    am_int_enable(p_devinfo->inum_pin[0]);
    am_int_enable(p_devinfo->inum_pin[1]);
    am_int_enable(p_devinfo->inum_pin[2]);

    return AM_OK;
}

/**
 * \brief GPIOȥ��ʼ��
 */
void am_zml165_gpio_deinit (void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int i = 0;

    if (__gp_gpio_dev->valid_flg) {
        for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
            (p_gpio_devinfo->p_infomap)[i]               = AM_ZML165_GPIO_INVALID_PIN_MAP;
            (p_gpio_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    am_int_disable((p_gpio_devinfo->inum_pin)[0]);
    am_int_disable((p_gpio_devinfo->inum_pin)[1]);
    am_int_disable((p_gpio_devinfo->inum_pin)[2]);

    am_int_disconnect((p_gpio_devinfo->inum_pin)[0], /* д���жϺ� */
                     (am_pfnvoid_t)__port_exit0_1_int_isr,
                     (void *)p_gpio_devinfo);
    am_int_disconnect((p_gpio_devinfo->inum_pin)[1], /* д���жϺ� */
                     (am_pfnvoid_t)__port_exit2_3_int_isr,
                     (void *)p_gpio_devinfo);
    am_int_disconnect((p_gpio_devinfo->inum_pin)[2], /* д���жϺ� */
                     (am_pfnvoid_t)__port_exit4_15_int_isr,
                     (void *)p_gpio_devinfo);

    if (__gp_gpio_dev->p_devinfo->pfn_plfm_deinit) {
        __gp_gpio_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
