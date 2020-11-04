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

#include <am_hc32f460_gpio.h>
#include <am_hc32f460_gpio_util.h>
#include "am_gpio_util.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_bitops.h"
#include "hc32f460_irq_handle.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define AM_HC32F460_GPIO_INVALID_PIN_MAP    0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev)  \
        const am_hc32f460_gpio_devinfo_t *p_gpio_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_hc32f460_gpio_dev_t *__gp_gpio_dev;

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
    amhw_hc32f460_gpio_t *p_hw_gpio  = NULL;
    amhw_hc32f460_gpio_mode_t pin_mode   = AMHW_HC32F460_GPIO_MODE_IPU;

    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }
    
    __pin_calc(pin, &en_portx, &pin_pos);
    p_hw_gpio = (amhw_hc32f460_gpio_t*)p_gpio_devinfo->gpio_regbase;

    func      = AM_GPIO_COM_FUNC_GET(flags);
    mode      = AM_GPIO_COM_MODE_GET(flags);

    /* ��׼����� */
    if (func != AM_GPIO_FUNC_INVALID_VAL) {
        /* ʹ�ñ�׼��ǰ���˻�����ΪGPIOģʽ */
        if (amhw_hc32f460_gpio_pin_afr_get(p_hw_gpio, pin) != AMHW_HC32F460_AFIO_GPIO) {

            /* ���ù��ܻص�Ĭ��״̬������ʹ��GPIO���� */
            amhw_hc32f460_gpio_pin_afr_set(p_hw_gpio, AMHW_HC32F460_AFIO_GPIO, pin);

        }

        switch (func) {

        case AM_GPIO_INPUT_VAL:
            amhw_hc32f460_gpio_pin_dir_input(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH_VAL:
            /* ����ߵ�ƽ */
            amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, pin);
            /* ������� */
            amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_HC32F460_GPIO_MODE_OUT_PP,
                                          pin);
            break;

        case AM_GPIO_OUTPUT_INIT_LOW_VAL:
            /* ����͵�ƽ */
            amhw_hc32f460_gpio_pin_out_low(p_hw_gpio, pin);
            /* ������� */
            amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_HC32F460_GPIO_MODE_OUT_PP,
                                          pin);

            break;

        default:
            return -AM_ENOTSUP;
        }
    }
    
    /* ��ȡ����������� */
    
    if (mode != AM_GPIO_MODE_INVALID_VAL) {
        dir = amhw_hc32f460_gpio_pin_dir_get(p_hw_gpio, pin);

        switch (mode) {              
        case AM_GPIO_PULL_UP_VAL:
            if (dir != 1) {
                /* ��������ģʽ  */
                pin_mode = AMHW_HC32F460_GPIO_MODE_IPU;
            } else {
                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_PULL_DOWN_VAL:  //HC32F46X cannot Support 
            break;

        case AM_GPIO_FLOAT_VAL:    //HC32F46X cannot Support 
            if (dir != 1) {
                pin_mode = AMHW_HC32F460_GPIO_MODE_IN_FLOATING;
            } else {
                /* ���û�и���ģʽ������Ϊ��©ģʽ */
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_OPEN_DRAIN_VAL:
            if (dir != 1) {
                /* ����û�п�©ģʽ������Ϊ���� */
                pin_mode = AMHW_HC32F460_GPIO_MODE_IN_FLOATING;
            } else {
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_OD;
            }

            break;

        case AM_GPIO_PUSH_PULL_VAL:
            if (dir != 1) {
                /* ����û������ģʽ������Ϊ���� */
                pin_mode = AMHW_HC32F460_GPIO_MODE_IPU;
            } else {
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_PP;
            }
            break;

        default:
            return -AM_ENOTSUP;
        }        
        amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /*
     * ƽ̨�������
     */

    /* �ܽŵ�ģʽ */
    if ((flags & AM_HC32F460_GPIO_MODE) != 0) {

       switch (AM_HC32F460_GPIO_MODE_GET(flags)) {

       case 0:
           /* ģ������ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AIN;
           break;

       case 1:
           /* �������� */       
           pin_mode = AMHW_HC32F460_GPIO_MODE_IN_FLOATING;       
           break;

       case 2:  
           /* ��������ģʽ  */
           pin_mode = AMHW_HC32F460_GPIO_MODE_IPD;                             
           break;

       case 3:
           /* ��������ģʽ  */
           pin_mode = AMHW_HC32F460_GPIO_MODE_IPU;                  
           break;

       case 4:
           /* ͨ���������ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_PP;                  
           break;

       case 5:
           /* ��©���ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_OD;
           break;

       case 6:   
           /* �����������ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AOUT;
           break;

       case 7:  
           /* ���ÿ�©���ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AF_PP;
           break;
           
       case 8:  
           /* ���ÿ�©���ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AF_OD;
           break;

       default:
           return -AM_ENOTSUP;
       }       
       amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ���ùܽŵ�������� */
    if ((flags & AM_HC32F460_GPIO_OUTRES_RATE) != 0) {
        amhw_hc32f460_gpio_pin_driver_capability(p_hw_gpio,(amhw_hc32f460_gpio_speed_mode_t)(AM_HC32F460_GPIO_OUTRES_RATE_GET(flags)), pin);
    }

    /* ���ùܽŵĸ��ù��� */
    if ((flags & AM_HC32F460_GPIO_FUNEN) != 0) {
        amhw_hc32f460_gpio_pin_afr_set(p_hw_gpio, AM_HC32F460_GPIO_FUNC_GET(flags), pin);
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

    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    return amhw_hc32f460_gpio_pin_get(p_hw_gpio, pin);
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

    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (value == 0) {
        amhw_hc32f460_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, pin);

    }
    return AM_OK;
}

/**
 * \brief �������״̬��ת
 */
int am_gpio_toggle (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    amhw_hc32f460_gpio_pin_toggle(p_hw_gpio, pin);

    return AM_OK;
}

/**
 * \brief ���Ŵ�����ʽ����
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;

    __pin_calc(pin, &en_portx, &pin_pos);

    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_hc32f460_gpio_t     *p_hw_gpio  = NULL;

    uint8_t                 slot       = pin & 0x0f;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;


    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    if (p_gpio_devinfo->p_infomap[slot] != pin) {
        return -AM_EINVAL;
    }

    /* ���ùܽ�Ϊ���뷽�� */
    amhw_hc32f460_gpio_pin_dir_input(p_hw_gpio, pin);

    switch (flag) {

    case AM_GPIO_TRIGGER_OFF:
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
 * \brief ʹ�������жϡ�
 */
int am_gpio_trigger_on (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    uint8_t               slot       = pin & 0x0f;
    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    if (p_gpio_devinfo->p_infomap[slot] == pin) {

        /* ʹ�������ⲿ�ж�������� */
        amhw_hc32f460_gpio_pin_ext_int_enable(p_hw_gpio, pin);

        switch (__gp_gpio_dev->int_type) {

            case AM_GPIO_TRIGGER_OFF:
            break;

            case AM_GPIO_TRIGGER_LOW:
                /* ����Ϊ���� */
                amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, pin);
                amhw_hc32f460_intc_pin_ext_int_trigger_cfg(slot, AMHW_HC32F460_INTC_PIN_EXT_INT_LOW);
                break;

            case AM_GPIO_TRIGGER_RISE:
                /* ����Ϊ���� */
                amhw_hc32f460_gpio_pin_out_low(p_hw_gpio, pin);
                /* rising  edge */
                amhw_hc32f460_intc_pin_ext_int_trigger_cfg(slot, AMHW_HC32F460_INTC_PIN_EXT_INT_RISE);
                break;

            case AM_GPIO_TRIGGER_FALL:
                /* ����Ϊ���� */
                amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, pin);
                /* falling  edge */
                amhw_hc32f460_intc_pin_ext_int_trigger_cfg(slot, AMHW_HC32F460_INTC_PIN_EXT_INT_FALL);
                break;
            case AM_GPIO_TRIGGER_BOTH_EDGES:
                /* ����Ϊ���� */
                amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, pin);
                /* both  edge */
                amhw_hc32f460_intc_pin_ext_int_trigger_cfg(slot, AMHW_HC32F460_INTC_PIN_EXT_INT_BOTHEDGE);
                break;
        }
    } else {
        return -AM_ENXIO;
    }

    return AM_OK;
}

/**
 * \brief ���������жϡ�
 */
int am_gpio_trigger_off (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    amhw_hc32f460_gpio_pin_ext_int_disable(p_hw_gpio, pin);
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
    uint8_t                  slot        = pin & 0x0f;
    int key;

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

    if (p_gpio_devinfo->p_infomap[slot] == AM_HC32F460_GPIO_INVALID_PIN_MAP) {

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
 * \brief ɾ�������жϻص���������
 */
int am_gpio_trigger_disconnect (int           pin,
                                am_pfnvoid_t  pfn_callback,
                                void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t                  slot        = pin & 0x0f;
    int key;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    key = am_int_cpu_lock();

    if (p_gpio_devinfo->p_infomap[slot] == pin) {

        p_gpio_devinfo->p_infomap[slot] = AM_HC32F460_GPIO_INVALID_PIN_MAP;
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
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_hc32f460_gpio_init (am_hc32f460_gpio_dev_t           *p_dev,
                           const am_hc32f460_gpio_devinfo_t *p_devinfo)
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

    for (i = 0 ; i < p_devinfo->exti_num_max ; i++) {
        p_devinfo->p_infomap[i] = AM_HC32F460_GPIO_INVALID_PIN_MAP;
        p_devinfo->p_triginfo[i].p_arg = NULL;
        p_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_connect(p_devinfo->inum_pin[0], IRQ128_Handler, NULL);
    amhw_hc32f460_intc_int_vssel_bits_set(p_devinfo->inum_pin[0], 0xFFFF);
    am_int_enable(p_devinfo->inum_pin[0]);

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
void am_hc32f460_gpio_deinit (void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int i = 0;

    if (__gp_gpio_dev->valid_flg) {
        for (i = 0; i < p_gpio_devinfo->exti_num_max; i++) {
            (p_gpio_devinfo->p_infomap)[i]               = AM_HC32F460_GPIO_INVALID_PIN_MAP;
            (p_gpio_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    am_int_disable(p_gpio_devinfo->inum_pin[0]);
    am_int_disconnect(p_gpio_devinfo->inum_pin[0], IRQ128_Handler, NULL);


    if (__gp_gpio_dev->p_devinfo->pfn_plfm_deinit) {
        __gp_gpio_dev->p_devinfo->pfn_plfm_deinit();
    }
}

void Extint00_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[0].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[0].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint01_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[1].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[1].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint02_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[2].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[2].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint03_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[3].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[3].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint04_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[4].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[4].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint05_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[5].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[5].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint06_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[6].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[6].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}


void Extint07_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[7].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[7].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint08_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[8].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[8].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint09_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[9].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[9].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint10_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[10].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[10].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}


void Extint11_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[11].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[11].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

void Extint12_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[12].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[12].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}


void Extint13_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[13].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[13].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}


void Extint14_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[14].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[14].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}


void Extint15_IrqHandler(void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[15].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[15].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}
/* end of file */
