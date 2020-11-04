/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
*******************************************************************************/

/**
 * \file
 * \brief ��ʱ��TIM������PWM������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */
#include "zsn700_clk.h"
#include "am_zsn700_tim_pwm.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"

/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ����PWM */
static int __tim_pwm_config (void          *p_drv,
                             int            chan,
                             unsigned long  duty_ns,
                             unsigned long  period_ns);

/** \brief ʹ��PWM��� */
static int __tim_pwm_enable (void *p_drv, int chan);

/** \brief ����PWM��� */
static int __tim_pwm_disable (void *p_drv, int chan);

/** \brief PWM�������� */
static const struct am_pwm_drv_funcs __g_tim_pwm_drv_funcs = {
    __tim_pwm_config,
    __tim_pwm_enable,
    __tim_pwm_disable,
};

/******************************************************************************/

/** \brief ����PWM */
static int __tim_pwm_config (void          *p_drv,
                             int            chan,
                             unsigned long  duty_ns,
                             unsigned long  period_ns)
{
    am_zsn700_tim_pwm_dev_t *p_dev    = (am_zsn700_tim_pwm_dev_t *)p_drv;
    amhw_zsn700_tim_t       *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    uint32_t clkfreq;
    uint16_t fre_div = 1;
    uint32_t period_c, duty_c, temp;

    /* �������Ϸ� */
    if ((period_ns == 0) || (duty_ns > 4294967295UL) ||
        (period_ns > 4294967295UL) || (duty_ns > period_ns)) {
        return -AM_EINVAL;
    }

    clkfreq  = am_clk_rate_get(CLK_PCLK);

    /* ��������õ����Ǽ���ֵCNT, ��ʽns * 10e-9= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_ns) * (clkfreq) / (uint64_t)1000000000;
    duty_c   = (uint64_t)(duty_ns)   * (clkfreq) / (uint64_t)1000000000;

    /* ������С��65536ʱ������Ƶ(ֵΪ1,1����Ϊ1��Ƶ) */
    temp = period_c / 65536 + 1;

    /* 16λ��ʱ����Ҫ����ȡ�ú��ʵķ�Ƶֵ */
    for (fre_div = 1; fre_div < temp; ) {
        fre_div++;          /* ��Ƶϵ�� */
    }

    /* ��Ƶϵ������ */
    if(fre_div <= 1) {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV1);
        fre_div = 1;
    } else if(fre_div <= 2) {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV2);
        fre_div = 2;
    } else if(fre_div <= 4) {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV4);
        fre_div = 4;
    } else if(fre_div <= 8) {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV8);
        fre_div = 8;
    } else if(fre_div <= 16) {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV16);
        fre_div = 16;
    } else if(fre_div <= 32) {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV32);
        fre_div = 32;
    } else if(fre_div <= 64) {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV64);
        fre_div = 64;
    } else {
        amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV256);
        fre_div = 256;
    }

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / fre_div;
    duty_c   = duty_c   / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return -AM_EINVAL;
    }

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zsn700_tim_arr_count_set(p_hw_tim, period_c - 1);

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    /* ����PWM��� */
    if(p_dev->p_devinfo->comp == 1) {

        /* ����ĳһͨ��A�ıȽ�ֵ */
        amhw_zsn700_tim_mode23_ccrxy_set(p_hw_tim, (chan / 2) * 2, duty_c - 1);

        /* ����ĳһͨ��B�ıȽ�ֵ */
        amhw_zsn700_tim_mode23_ccrxy_set(p_hw_tim, (chan / 2) * 2 + 1, duty_c - 1);

        /* ����PWM����������� */
        amhw_zsn700_tim_mode23_compare_set(
           p_hw_tim,
           (amhw_zsn700_tim_compare_type_t)(((chan / 2) * 2) * 4),
           (amhw_zsn700_tim_compare_t)p_dev->p_devinfo->ocpolarity);

        amhw_zsn700_tim_mode23_compare_set(
            p_hw_tim,
            (amhw_zsn700_tim_compare_type_t)((((chan / 2) * 2) + 1) * 4),
            (amhw_zsn700_tim_compare_t)p_dev->p_devinfo->ocpolarity);

    /* ����PWM���*/
    } else {

        /* ����ĳһͨ���ıȽ�ֵ */
        amhw_zsn700_tim_mode23_ccrxy_set(p_hw_tim, chan, duty_c - 1);

        /* ����PWM���ģʽΪPWM1 */
        amhw_zsn700_tim_mode23_compare_set(
            p_hw_tim,
            (amhw_zsn700_tim_compare_type_t)(chan * 4),
            (amhw_zsn700_tim_compare_t)p_dev->p_devinfo->ocpolarity);
    }

    /* ������� */
    amhw_zsn700_tim_mode23_phase_same(
        p_hw_tim,
        (amhw_zsn700_tim_phase_type_t)(chan * 4 + 3));

    return AM_OK;
}

/**
 * \brief ʹ��PWMͨ�����
 */
static int __tim_pwm_enable (void *p_drv, int chan)
{
    int i = 0, t = 0, t1 = 0, t2 = 0, enable_flag = 0;
    am_zsn700_tim_pwm_dev_t    *p_dev    = (am_zsn700_tim_pwm_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;
    am_zsn700_tim_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;

    uint8_t comp_pin_flag = 0;

    /* �ж������б����Ƿ��ж�Ӧͨ��������Ϣ */
    for(i = 0; i <= p_dev->chan_max; i++){
        if((p_chaninfo[i].channel & 0x7f) ==  chan){

            /* ����PWM��� */
            if(p_dev->p_devinfo->comp == 1){

                t1 = (i / 2) * 2;
                t2 = t1 + 1;

                /* ����Aͨ�����źţ�����ʼ�� */
                for(t = 0; t <= p_dev->chan_max; t++) {
                    if( p_chaninfo[t].channel == t1) {
                        am_gpio_pin_cfg(p_chaninfo[t].gpio, p_chaninfo[t].func);
                        comp_pin_flag |= (1 << 0);
                    }
                    if( p_chaninfo[t].channel == t2) {
                        am_gpio_pin_cfg(p_chaninfo[t].gpio, p_chaninfo[t].func);
                        comp_pin_flag |= (1 << 1);
                    }

                    if(comp_pin_flag == 0x3) {
                        break;
                    }
                }

                /* ʹ�ܻ������ */
                amhw_zsn700_tim_mode23_enable(p_hw_tim, AMHW_ZSN700_TIM_COMP);

                enable_flag = 1;
                break;

            /* ����PWM��� */
            }else{

                am_gpio_pin_cfg(p_chaninfo[i].gpio, p_chaninfo[i].func);

                /* ���ܻ������ */
                amhw_zsn700_tim_mode23_disable(p_hw_tim, AMHW_ZSN700_TIM_COMP);

                enable_flag = 1;
                break;
            }
        }
    }

    /* ����ͨ������Ч */
    if(enable_flag == 0){
        return -AM_EINVAL;
    }

    /* �����־λ */
    amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZSN700_TIM_INT_FLAG_ALL);

    /* PWM����ʹ�� */
    amhw_zsn700_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZSN700_TIM_DTR_MOE);

    /* ʹ�ܶ�ʱ�� */
    amhw_zsn700_tim_enable(p_hw_tim);

    return AM_OK;
}

/**
 * \brief ����PWMͨ�����
 */
static int __tim_pwm_disable (void *p_drv, int chan)
{
    int  i = 0, t = 0, t1 = 0, t2 = 0, disable_flag = 0;
    am_zsn700_tim_pwm_dev_t      *p_dev    = (am_zsn700_tim_pwm_dev_t *)p_drv;
    amhw_zsn700_tim_t            *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;
    am_zsn700_tim_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;

    uint8_t comp_pin_flag = 0;

    /* �ж������б����Ƿ��ж�Ӧͨ��������Ϣ */
    for(i = 0; i <= p_dev->chan_max; i++){
        if((p_chaninfo[i].channel & 0x7f) ==  chan){

            /* ����PWM��� */
            if(p_dev->p_devinfo->comp == 1){

                t1 = (i / 2) * 2;
                t2 = t1 + 1;

                /* ����Aͨ�����źţ������ʼ�� */
                for(t = 0; t <= p_dev->chan_max; t++) {
                    if(p_chaninfo[t].channel == t1) {
                        am_gpio_pin_cfg(p_chaninfo[t].gpio, p_chaninfo[t].dfunc);
                        comp_pin_flag |= (1 << 0);
                    }
                    if(p_chaninfo[t].channel == t2) {
                        am_gpio_pin_cfg(p_chaninfo[t].gpio, p_chaninfo[t].dfunc);
                        comp_pin_flag |= (1 << 1);

                    }
                    if(comp_pin_flag == 0x3) {
                         break;
                    }
                }

                disable_flag = 1;
                break;

            /* ����PWM��� */
            } else {

                am_gpio_pin_cfg(p_chaninfo[i].gpio, p_chaninfo[i].dfunc);

                disable_flag = 1;
                break;
            }
        }
    }

    /* ����ͨ������Ч */
    if(disable_flag == 0){
        return -AM_EINVAL;
    }

    /* ���ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_disable(p_hw_tim);

    /* ����ͨ��PWM��� */
    amhw_zsn700_tim_mode23_dtr_disable(p_hw_tim, AMHW_ZSN700_TIM_DTR_MOE);

    return AM_OK;
}

/**
  * \brief pwm��ʼ��
  */
void __tim_pwm_init (amhw_zsn700_tim_t       *p_hw_tim,
                     am_zsn700_tim_pwm_dev_t *p_dev,
                     amhw_zsn700_tim_type_t   type)
{
    uint8_t i = 0;

    /* ���ö�ʱ��ģʽ2 */
    amhw_zsn700_tim_mode_set(p_hw_tim, AMHW_ZSN700_TIM_MODE_ZIGZAG);

    /* ���ϼ��� */
    amhw_zsn700_tim_mode23_counter_up(p_hw_tim);

    /* ����ͨ��Ϊ�Ƚ�ģʽ ��CH0A��CH1A��CH2A��*/
    for(i = 0; i < p_dev->chan_max;i = i + 2) {
        amhw_zsn700_tim_mode23_csa_compare(p_hw_tim, i);
    }

    /* ����ͨ��Ϊ�Ƚ�ģʽ ��CH0B��CH1B��CH2B */
    for(i = 1; i < p_dev->chan_max;i = i + 2) {
        amhw_zsn700_tim_mode23_csa_compare(p_hw_tim, i);
    }

    /* ��ʱ��ʱ��Ϊ�ڲ�ʱ�� */
    amhw_zsn700_tim_mode_clk_src_set(p_hw_tim,AMHW_ZSN700_TIM_CLK_SRC_TCLK);

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);
}

/**
  * \brief tim pwm�����ʼ��
  */
am_pwm_handle_t am_zsn700_tim_pwm_init (am_zsn700_tim_pwm_dev_t           *p_dev,
                                        const am_zsn700_tim_pwm_devinfo_t *p_devinfo)
{
    amhw_zsn700_tim_t  *p_hw_tim = NULL;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    if(p_devinfo->tim_type == AMHW_ZSN700_TIM_TYPE_TIM3) {
        p_dev->chan_max = 6;
    } else {
        p_dev->chan_max = 2;
    }

    if(p_dev->chan_max < p_devinfo->channels_num) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo        = p_devinfo;
    p_hw_tim                = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;
    p_dev->pwm_serv.p_funcs = (struct am_pwm_drv_funcs *)&__g_tim_pwm_drv_funcs;
    p_dev->pwm_serv.p_drv   = p_dev;

    __tim_pwm_init(p_hw_tim, p_dev, p_devinfo->tim_type);

    return &(p_dev->pwm_serv);
}

void am_zsn700_tim_pwm_deinit (am_pwm_handle_t handle)
{

    am_zsn700_tim_pwm_dev_t *p_dev    = (am_zsn700_tim_pwm_dev_t *)handle;
    amhw_zsn700_tim_t       *p_hw_tim = NULL;

    if (p_dev == NULL ) {
        return;
    }

    p_hw_tim   = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    /* ���ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_disable(p_hw_tim);

    p_dev->pwm_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
