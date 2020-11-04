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
 * \brief ��ʱ��ADTIM������PWM������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */
#include "zsn700_clk.h"
#include "am_zsn700_adtim_pwm.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"

/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ����PWM */
static int __adtim_pwm_config (void          *p_drv,
                               int            chan,
                               unsigned long  duty_ns,
                               unsigned long  period_ns);

/** \brief ʹ��PWM��� */
static int __adtim_pwm_enable (void *p_drv, int chan);

/** \brief ����PWM��� */
static int __adtim_pwm_disable (void *p_drv, int chan);

/** \brief PWM�������� */
static const struct am_pwm_drv_funcs __g_adtim_pwm_drv_funcs = {
    __adtim_pwm_config,
    __adtim_pwm_enable,
    __adtim_pwm_disable,
};

/******************************************************************************/

/** \brief ����PWM */
static int __adtim_pwm_config (void          *p_drv,
                               int            chan,
                               unsigned long  duty_ns,
                               unsigned long  period_ns)
{
    am_zsn700_adtim_pwm_dev_t *p_dev      = (am_zsn700_adtim_pwm_dev_t *)p_drv;
    amhw_zsn700_adtim_t       *p_hw_adtim = (amhw_zsn700_adtim_t *)
                                            p_dev->p_devinfo->adtim_regbase;

    amhw_zsn700_adtim_basecnt_cfg_t basecnt;

    amhw_zsn700_adtim_timx_chx_port_cfg_t  portcfg;
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
        basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV1;
        fre_div = 1;
    } else if(fre_div <= 2) {
        basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV2;
        fre_div = 2;
    } else if(fre_div <= 4) {
        basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV4;
        fre_div = 4;
    } else if(fre_div <= 8) {
        basecnt.cntclkdiv = AMHW_ZSN700_ADTIM_PCLK_DIV8;
        fre_div = 8;
    } else if(fre_div <= 16) {
        basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV16;
        fre_div = 16;
    } else if(fre_div <= 64) {
        basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV64;
        fre_div = 64;
    } else if(fre_div <= 256) {
        basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV256;
        fre_div = 256;
    } else {
        basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV1024;
        fre_div = 1024;
    }

    basecnt.cntmode   = AMHW_ZSN700_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_ZSN700_ADTIM_CNT_DIR_UP;

    /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
    amhw_zsn700_adtim_init(p_hw_adtim, &basecnt);

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / fre_div;
    duty_c   = duty_c   / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return -AM_EINVAL;
    }

    /* ���ü������� */
    amhw_zsn700_adtim_setperiod(p_hw_adtim, period_c);

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    duty_c = period_c - duty_c;

    portcfg.portmode  = AMHW_ZSN700_ADTIM_PORT_MODE_CMP_OUTPUT;
    portcfg.outenable = AM_TRUE;
    portcfg.perc      = AMHW_ZSN700_ADTIM_PERIOD_INV;
    portcfg.cmpc      = AMHW_ZSN700_ADTIM_COMPARE_INV;
    portcfg.stastps   = AMHW_ZSN700_ADTIM_STATE_SEL_SS;
    portcfg.disval    = AMHW_ZSN700_ADTIM_DISVAL_NORM;
    portcfg.dissel    = AMHW_ZSN700_ADTIM_DISSEL0;
    portcfg.fltenable = AM_FALSE;
    portcfg.fltclk    = AMHW_ZSN700_ADTIM_FLTCLK_PCLK_DIV1;

    /* ����PWM��� */
    if(p_dev->p_devinfo->comp == 1) {

        amhw_zsn700_adtim_setcomparevalue(p_hw_adtim, 
                                          AMHW_ZSN700_ADTIM_COMPARE_A, 
                                          duty_c);
        amhw_zsn700_adtim_setcomparevalue(p_hw_adtim, 
                                          AMHW_ZSN700_ADTIM_COMPARE_B, 
                                          duty_c);

        portcfg.staout = (amhw_zsn700_adtim_port_out_t)p_dev->p_devinfo->ocpolarity;
        portcfg.stpout = (amhw_zsn700_adtim_port_out_t)p_dev->p_devinfo->ocpolarity;
        amhw_zsn700_adtim_timxchxportcfg(p_hw_adtim,
                                         AMHW_ZSN700_ADTIM_CHX_A,
                                         &portcfg);

        portcfg.staout = (amhw_zsn700_adtim_port_out_t)(!p_dev->p_devinfo->ocpolarity);
        portcfg.stpout = (amhw_zsn700_adtim_port_out_t)(!p_dev->p_devinfo->ocpolarity);
        amhw_zsn700_adtim_timxchxportcfg(p_hw_adtim,
                                         AMHW_ZSN700_ADTIM_CHX_B,
                                         &portcfg);

    /* ����PWM���*/
    } else {

        amhw_zsn700_adtim_setcomparevalue(p_hw_adtim, 
                                          (amhw_zsn700_adtim_compare_x_t)chan, 
                                          duty_c);

        portcfg.staout = (amhw_zsn700_adtim_port_out_t)p_dev->p_devinfo->ocpolarity;
        portcfg.stpout = (amhw_zsn700_adtim_port_out_t)p_dev->p_devinfo->ocpolarity;
        amhw_zsn700_adtim_timxchxportcfg(p_hw_adtim,
                                         (amhw_zsn700_adtim_chx_t)chan,
                                         &portcfg);
    }

    return AM_OK;
}

/**
 * \brief ʹ��PWMͨ�����
 */
static int __adtim_pwm_enable (void *p_drv, int chan)
{
    int i = 0, t = 0, enable_flag = 0;
    am_zsn700_adtim_pwm_dev_t      *p_dev      = (am_zsn700_adtim_pwm_dev_t *)
                                                 p_drv;
    amhw_zsn700_adtim_t            *p_hw_adtim = (amhw_zsn700_adtim_t *)
                                                 p_dev->p_devinfo->adtim_regbase;
    am_zsn700_adtim_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;

    uint8_t comp_pin_flag = 0;

    for(i = 0; i <= p_dev->p_devinfo->channels_num; i++) {

        if((p_chaninfo[i].channel & 0x7f) ==  chan) {

            /* ����PWM��� */
            if(p_dev->p_devinfo->comp == 1){

                /* ����Bͨ��������ʼ������ */
                for(t = 0; t <= p_dev->p_devinfo->channels_num; t++) {
                    if( p_chaninfo[t].channel == 0) {
                        am_gpio_pin_cfg(p_chaninfo[t].gpio, p_chaninfo[t].func);
                        comp_pin_flag |= (1 << 0);
                    }
                    if( p_chaninfo[t].channel == 1) {
                        am_gpio_pin_cfg(p_chaninfo[t].gpio, p_chaninfo[t].func);
                        comp_pin_flag |= (1 << 1);
                    }
                    if(comp_pin_flag == 0x3) {
                        break;
                    }
                }

                enable_flag = 1;
                break;

            /* ����PWM��� */
            } else {
                am_gpio_pin_cfg(p_chaninfo[chan].gpio, p_chaninfo[chan].func);

                enable_flag = 1;
                break;
            }
        }
    }

    /* ����ͨ������Ч */
    if(enable_flag == 0){
        return -AM_EINVAL;
    }

    /* ��������жϱ�־ */
    amhw_zsn700_adtim_clearallirqflag(p_hw_adtim);

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    /* ��ʱ������ */
    amhw_zsn700_adtim_startcount(p_hw_adtim);

    return AM_OK;
}

/**
 * \brief ����PWMͨ�����
 */
static int __adtim_pwm_disable (void *p_drv, int chan)
{
    int i = 0, t = 0, disable_flag = 0;
    am_zsn700_adtim_pwm_dev_t      *p_dev    = (am_zsn700_adtim_pwm_dev_t *)p_drv;
    amhw_zsn700_adtim_t            *p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;
    am_zsn700_adtim_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;

    uint8_t comp_pin_flag = 0;

    for(i = 0; i <= p_dev->p_devinfo->channels_num; i++) {

        if((p_chaninfo[i].channel & 0x7f) ==  chan) {

            /* ����PWM��� */
            if(p_dev->p_devinfo->comp == 1){

                /* ����Bͨ���������ʼ������ */
                for(t = 0; t <= p_dev->p_devinfo->channels_num; t++) {
                    if( p_chaninfo[t].channel == 0) {
                        am_gpio_pin_cfg(p_chaninfo[t].gpio, p_chaninfo[t].dfunc);
                        comp_pin_flag |= (1 << 0);
                    }
                    if( p_chaninfo[t].channel == 1) {
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
            }else{
                am_gpio_pin_cfg(p_chaninfo[chan].gpio, p_chaninfo[chan].dfunc);

                disable_flag = 1;
                break;
            }
        }
    }

    /* ����ͨ������Ч */
    if(disable_flag == 0){
        return -AM_EINVAL;
    }

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    /* ��ʱ��ֹͣ */
    amhw_zsn700_adtim_stopcount(p_hw_adtim);

    /* ��������жϱ�־ */
    amhw_zsn700_adtim_clearallirqflag(p_hw_adtim);

    return AM_OK;
}

/**
  * \brief adtim pwm�����ʼ��
  */
am_pwm_handle_t am_zsn700_adtim_pwm_init (am_zsn700_adtim_pwm_dev_t      *p_dev,
                                     const am_zsn700_adtim_pwm_devinfo_t *p_devinfo)
{
    amhw_zsn700_adtim_basecnt_cfg_t basecnt;
    amhw_zsn700_adtim_t  *p_hw_adtim = NULL;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->chan_max = 2;

    if(p_dev->chan_max < p_devinfo->channels_num) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo        = p_devinfo;
    p_hw_adtim              = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;
    p_dev->pwm_serv.p_funcs = (struct am_pwm_drv_funcs *)&__g_adtim_pwm_drv_funcs;
    p_dev->pwm_serv.p_drv   = p_dev;

    basecnt.cntmode   = AMHW_ZSN700_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_ZSN700_ADTIM_CNT_DIR_UP;
    basecnt.cntclkdiv = AMHW_ZSN700_ADTIM_PCLK_DIV1;

    /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
    amhw_zsn700_adtim_init(p_hw_adtim, &basecnt);

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    return &(p_dev->pwm_serv);
}

void am_zsn700_adtim_pwm_deinit (am_pwm_handle_t handle)
{

    am_zsn700_adtim_pwm_dev_t *p_dev    = (am_zsn700_adtim_pwm_dev_t *)handle;
    amhw_zsn700_adtim_t       *p_hw_adtim = NULL;

    if (p_dev == NULL ) {
        return;
    }

    p_hw_adtim   = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    /* �ر�TIMģ�� */
    amhw_zsn700_adtim_stopcount(p_hw_adtim);

    /* �ֶ���λ�Ĵ��� */
    amhw_zsn700_adtim_deinit(p_hw_adtim);

    p_dev->pwm_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
