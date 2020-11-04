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
 * \brief ��ʱ��TIM������PWM������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-16  nwt, first implementation
 * \endinternal
 */
#include "hc32f460_clk.h"
#include "am_hc32f460_timea_pwm.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "hc32f460_regbase.h"

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
    am_hc32f460_timea_pwm_dev_t *p_dev    = (am_hc32f460_timea_pwm_dev_t *)p_drv;
    amhw_hc32f460_timea_t       *p_hw_tim = (amhw_hc32f460_timea_t *)p_dev->p_devinfo->tim_regbase;
    stc_timera_compare_init_t   stcTimerCompareInit;
    
    uint32_t clkfreq;
    uint16_t fre_div = 1;
    uint32_t period_c, duty_c, temp;

    /* �������Ϸ� */
    if ((period_ns == 0) || (duty_ns > 4294967295UL) ||
        (period_ns > 4294967295UL) || (duty_ns > period_ns)) {
        return -AM_EINVAL;
    }

    clkfreq  = am_clk_rate_get(CLK_TIMERA_1);

    /* ��������õ����Ǽ���ֵCNT, ��ʽns * 10e-9= cnt * (1/clkfrq) */
    period_c = ((uint64_t)(period_ns) * (clkfreq) / (uint64_t)1000000000) / 2;
    duty_c   = ((uint64_t)(duty_ns)   * (clkfreq) / (uint64_t)1000000000) / 2;

    /* ������С��65536ʱ������Ƶ(ֵΪ1,1����Ϊ1��Ƶ) */
    temp = period_c / 65536 + 1;

    /* 16λ��ʱ����Ҫ����ȡ�ú��ʵķ�Ƶֵ */
    for (fre_div = 1; fre_div < temp; ) {
        fre_div++;          /* ��Ƶϵ�� */
    }

    /* ��Ƶϵ������ */
    if(fre_div <= 1) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV0);
        fre_div = 1;
    } else if(fre_div <= 2) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV2);
        fre_div = 2;
    } else if(fre_div <= 4) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV4);
        fre_div = 4;
    } else if(fre_div <= 8) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV8);
        fre_div = 8;
    } else if(fre_div <= 16) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV16);
        fre_div = 16;
    } else if(fre_div <= 32) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV32);
        fre_div = 32;
    } else if(fre_div <= 64) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV64);
        fre_div = 64;
    } else if(fre_div <= 128) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV128);
        fre_div = 128;
    }else if(fre_div <= 256) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV256);
        fre_div = 256;
    }else if(fre_div <= 512) {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV512);
        fre_div = 512;
    }else {
        amhw_hc32f460_timea_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIMEA_CLK_DIV1024);
        fre_div = 1024;
    }



    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / fre_div;
    duty_c   = duty_c   / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return -AM_EINVAL;
    }

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_hc32f460_timea_arr_count_set(p_hw_tim, chan,  period_c);

    /* ��������� */
    amhw_hc32f460_timea_cnt16_count_set(p_hw_tim, 0);

    /* Configuration timera unit 1 compare structure */
    stcTimerCompareInit.u16CompareVal = duty_c;
    stcTimerCompareInit.enStartCountOutput = TimeraCountStartOutputLow;
    stcTimerCompareInit.enStopCountOutput = TimeraCountStopOutputLow;
    stcTimerCompareInit.enCompareMatchOutput = TimeraCompareMatchOutputReverse;
    stcTimerCompareInit.enPeriodMatchOutput = TimeraPeriodMatchOutputKeep;
    stcTimerCompareInit.enSpecifyOutput = TimeraSpecifyOutputInvalid;
    stcTimerCompareInit.enCacheEn = Enable;
    stcTimerCompareInit.enTriangularTroughTransEn = Disable;
    stcTimerCompareInit.enTriangularCrestTransEn = Disable;
    stcTimerCompareInit.u16CompareCacheVal = stcTimerCompareInit.u16CompareVal;

    amhw_hc32f460_timea_compare_init(p_hw_tim, (timea_channel_t)chan, &stcTimerCompareInit);
    amhw_hc32f460_timea_compare_cmd(p_hw_tim, (timea_channel_t)chan, Enable);
    return AM_OK;
}

/**
 * \brief ʹ��PWMͨ�����
 */
static int __tim_pwm_enable (void *p_drv, int chan)
{
    int i = 0, enable_flag = 0;
    am_hc32f460_timea_pwm_dev_t      *p_dev    = (am_hc32f460_timea_pwm_dev_t *)p_drv;
    amhw_hc32f460_timea_t            *p_hw_tim = (amhw_hc32f460_timea_t *)p_dev->p_devinfo->tim_regbase;
    am_hc32f460_timea_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;

    /* �ж������б����Ƿ��ж�Ӧͨ��������Ϣ */
    for(i = 0; i <= p_dev->chan_max; i++){
        if((p_chaninfo[i].channel) ==  chan){
            am_gpio_pin_cfg(p_chaninfo[i].gpio, p_chaninfo[i].func);
            enable_flag = 1;
            break;
        }
    }

    /* ����ͨ������Ч */
    if(enable_flag == 0){
        return -AM_EINVAL;
    }

    /* ʹ�ܶ�ʱ�� */
    amhw_hc32f460_timea_enable(p_hw_tim, chan);

    return AM_OK;
}

/**
 * \brief ����PWMͨ�����
 */
static int __tim_pwm_disable (void *p_drv, int chan)
{
    int  i = 0, disable_flag = 0;
    am_hc32f460_timea_pwm_dev_t      *p_dev    = (am_hc32f460_timea_pwm_dev_t *)p_drv;
    amhw_hc32f460_timea_t            *p_hw_tim = (amhw_hc32f460_timea_t *)p_dev->p_devinfo->tim_regbase;
    am_hc32f460_timea_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;

    /* �ж������б����Ƿ��ж�Ӧͨ��������Ϣ */
    for(i = 0; i <= p_dev->chan_max; i++){
        if((p_chaninfo[i].channel & 0x7f) ==  chan){
            am_gpio_pin_cfg(p_chaninfo[i].gpio, p_chaninfo[i].dfunc);
            disable_flag = 1;
            break;
        }
    }

    /* ����ͨ������Ч */
    if(disable_flag == 0){
        return -AM_EINVAL;
    }

    /* ���ܶ�ʱ��TIM������� */
    amhw_hc32f460_timea_disable(p_hw_tim, chan);
    return AM_OK;
}

/**
  * \brief pwm��ʼ��
  */
static void __tim_pwm_init (amhw_hc32f460_timea_t       *p_hw_tim,
                     am_hc32f460_timea_pwm_dev_t *p_dev,
                     amhw_hc32f460_timea_type_t   type)
{
    /* ���ö�ʱ��ģʽ2 */
    amhw_hc32f460_timea_mode_set(p_hw_tim, timea_count_mode_sawtooth_wave);

    /* ���ϼ��� */
    amhw_hc32f460_timea_dir_set(p_hw_tim, timea_count_dir_up);

    /* Unit 1 sync startup invalid */
    if(((amhw_hc32f460_timea_t *)HC32F460_TMRA1_BASE == p_hw_tim) &&
       (1 == p_dev->p_devinfo->sync_startup_en))
    {
        while(1);
    }
    
    p_hw_tim->BCSTR_f.SYNST = p_dev->p_devinfo->sync_startup_en;
}

/**
  * \brief tim pwm�����ʼ��
  */
am_pwm_handle_t am_hc32f460_timea_pwm_init (am_hc32f460_timea_pwm_dev_t           *p_dev,
                                            const am_hc32f460_timea_pwm_devinfo_t *p_devinfo)
{
    amhw_hc32f460_timea_t  *p_hw_tim = NULL;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->chan_max = 8;

    if(p_dev->chan_max < p_devinfo->channels_num) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo        = p_devinfo;
    p_hw_tim                = (amhw_hc32f460_timea_t *)p_dev->p_devinfo->tim_regbase;
    p_dev->pwm_serv.p_funcs = (struct am_pwm_drv_funcs *)&__g_tim_pwm_drv_funcs;
    p_dev->pwm_serv.p_drv   = p_dev;

    __tim_pwm_init(p_hw_tim, p_dev, p_devinfo->tim_type);

    return &(p_dev->pwm_serv);
}

void am_hc32f460_timea_pwm_deinit (am_pwm_handle_t handle)
{

    am_hc32f460_timea_pwm_dev_t *p_dev    = (am_hc32f460_timea_pwm_dev_t *)handle;
    amhw_hc32f460_timea_t       *p_hw_tim = NULL;

    if (p_dev == NULL ) {
        return;
    }

    p_hw_tim   = (amhw_hc32f460_timea_t *)p_dev->p_devinfo->tim_regbase;

    /* ��������� */
    amhw_hc32f460_timea_cnt16_count_set(p_hw_tim, 0);

    /* ���ܶ�ʱ��TIM������� */
    amhw_hc32f460_timea_disable(p_hw_tim, 0);

    p_dev->pwm_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
