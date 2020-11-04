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
#include "am_hc32f460_tim4_pwm.h"
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
    am_hc32f460_tim4_pwm_dev_t *p_dev    = (am_hc32f460_tim4_pwm_dev_t *)p_drv;
    amhw_hc32f460_tim4_t       *p_hw_tim = (amhw_hc32f460_tim4_t *)p_dev->p_devinfo->tim_regbase;
    
    uint32_t clkfreq;
    uint16_t fre_div = 1;
    uint32_t period_c, duty_c, temp;
    timer4_oco_ch_t enOcohigCh = TIMER4_OCO_OUH;
    timer4_oco_ch_t enOcoLowCh = TIMER4_OCO_OUL;
    uint16_t u8OcoOccrVal = 0;
    
    /* �������Ϸ� */
    if ((period_ns == 0) || (duty_ns > 4294967295UL) ||
        (period_ns > 4294967295UL) || (duty_ns > period_ns)) {
        return -AM_EINVAL;
    }

    clkfreq  = am_clk_rate_get(CLK_TIMER4_1);

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
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV0);
        fre_div = 1;
    } else if(fre_div <= 2) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV2);
        fre_div = 2;
    } else if(fre_div <= 4) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV4);
        fre_div = 4;
    } else if(fre_div <= 8) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV8);
        fre_div = 8;
    } else if(fre_div <= 16) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV16);
        fre_div = 16;
    } else if(fre_div <= 32) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV32);
        fre_div = 32;
    } else if(fre_div <= 64) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV64);
        fre_div = 64;
    } else if(fre_div <= 128) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV128);
        fre_div = 128;
    }else if(fre_div <= 256) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV256);
        fre_div = 256;
    }else if(fre_div <= 512) {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV512);
        fre_div = 512;
    }else {
        amhw_hc32f460_tim4_mode_clkdiv_set(p_hw_tim, chan, AMHW_HC32F460_TIM4_CLK_DIV1024);
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
    amhw_hc32f460_tim4_arr_count_set(p_hw_tim, chan,  period_c);

    /* ��������� */
    amhw_hc32f460_tim4_cnt16_count_set(p_hw_tim, chan, 0);

    if (p_dev->p_devinfo->pwm_ch == TIMER4_PWM_U)
    {
        enOcohigCh = TIMER4_OCO_OUH;
        enOcoLowCh = TIMER4_OCO_OUL;        
    } else if (p_dev->p_devinfo->pwm_ch == TIMER4_PWM_V) {
        enOcohigCh = TIMER4_OCO_OVH;
        enOcoLowCh = TIMER4_OCO_OVL;        
    } else if (p_dev->p_devinfo->pwm_ch == TIMER4_PWM_W) {
        enOcohigCh = TIMER4_OCO_OWH;
        enOcoLowCh = TIMER4_OCO_OWL; 
    } else {
        ;
    }
    
    u8OcoOccrVal = period_c / 2;

    amhw_hc32f460_tim4_oco_write_occr(p_hw_tim, enOcohigCh, u8OcoOccrVal);
    amhw_hc32f460_tim4_oco_write_occr(p_hw_tim, enOcoLowCh, u8OcoOccrVal);

    amhw_hc32f460_tim4_oco_output_cmp_cmd(p_hw_tim, enOcohigCh, TIM4_ENABLE);    
    amhw_hc32f460_tim4_oco_output_cmp_cmd(p_hw_tim, enOcoLowCh, TIM4_ENABLE);
    return AM_OK;
}

/**
 * \brief ʹ��PWMͨ�����
 */
static int __tim_pwm_enable (void *p_drv, int chan)
{
    int  enable_flag = 0, high_pin, low_pin;
    am_hc32f460_tim4_pwm_dev_t    *p_dev    = (am_hc32f460_tim4_pwm_dev_t *)p_drv;
    amhw_hc32f460_tim4_t          *p_hw_tim = (amhw_hc32f460_tim4_t *)p_dev->p_devinfo->tim_regbase;
    am_hc32f460_tim4_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;    
    stc_timer4_pwm_init_t stcPwmInit;

    if (chan == TIMER4_PWM_U)
    {
        high_pin = 0;
        low_pin  = 1;
        enable_flag = 1;
    } else if (chan == TIMER4_PWM_V)
    {
        high_pin = 2;
        low_pin  = 3;
        enable_flag = 1;
    } else if (chan == TIMER4_PWM_W)
    {
        high_pin = 4;
        low_pin  = 5;
        enable_flag = 1;
    } else {
        ;
    }

    /* ����ͨ������Ч */
    if(enable_flag == 0){
        return -AM_EINVAL;
    } else {    
        am_gpio_pin_cfg(p_chaninfo[high_pin].gpio, p_chaninfo[high_pin].func);/* high chan */        
        am_gpio_pin_cfg(p_chaninfo[low_pin].gpio, p_chaninfo[low_pin].func);  /* low chan */      
    }

    /* Timer4 PWM: Initialize PWM configuration structure */
    stcPwmInit.enRtIntMaskCmd = TIM4_ENABLE;
    stcPwmInit.enClkDiv = PwmPlckDiv1;
    stcPwmInit.enOutputState = PwmHHoldPwmLReverse;
    stcPwmInit.enMode = PwmThroughMode;
    amhw_hc32f460_tim4_pwm_init(p_hw_tim, p_dev->p_devinfo->pwm_ch, &stcPwmInit); /* Initialize timer4 pwm */
    amhw_hc32f460_tim4_cnt_value_clr(p_hw_tim);

    /* ʹ�ܶ�ʱ�� */
    amhw_hc32f460_tim4_enable(p_hw_tim, chan);

    return AM_OK;
}

/**
 * \brief ����PWMͨ�����
 */
static int __tim_pwm_disable (void *p_drv, int chan)
{
    int  i = 0, disable_flag = 0;
    am_hc32f460_tim4_pwm_dev_t      *p_dev    = (am_hc32f460_tim4_pwm_dev_t *)p_drv;
    amhw_hc32f460_tim4_t            *p_hw_tim = (amhw_hc32f460_tim4_t *)p_dev->p_devinfo->tim_regbase;
    am_hc32f460_tim4_pwm_chaninfo_t *p_chaninfo = p_dev->p_devinfo->p_chaninfo;

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
    amhw_hc32f460_tim4_disable(p_hw_tim, chan);
    return AM_OK;
}

/**
  * \brief pwm��ʼ��
  */
void __tim_pwm_init (amhw_hc32f460_tim4_t       *p_hw_tim,
                     am_hc32f460_tim4_pwm_dev_t *p_dev)
{
    stc_timer4_oco_init_t stcOcoInit;
    stc_oco_low_ch_compare_mode_t stcLowChCmpMode;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;    
    timer4_oco_ch_t enOcohigCh = TIMER4_OCO_OUH;
    timer4_oco_ch_t enOcoLowCh = TIMER4_OCO_OUL;
    
    /* ���ö�ʱ��ģʽ2 */
    amhw_hc32f460_tim4_mode_set(p_hw_tim, TIM4_COUNT_MODE_SAWTOOTH_WAVE);
   
    amhw_hc32f460_tim4_buf_set(p_hw_tim, AM_FALSE);    

    /* Ĭ��ʱ��ʹ��PCLK1 */    
    amhw_hc32f460_tim4_ext_clk_set(p_hw_tim, AM_FALSE);    

    amhw_hc32f460_tim4_intz_set(p_hw_tim, AM_FALSE);            
    amhw_hc32f460_tim4_intp_set(p_hw_tim, AM_FALSE);

    /* set intterrupt mask times */    
    amhw_hc32f460_tim4_zim_set(p_hw_tim, TIMER4_CNT_INT_MASK0);    
    amhw_hc32f460_tim4_pim_set(p_hw_tim, TIMER4_CNT_INT_MASK0);

    /* Timer4 OCO : Initialize OCO configuration structure */
    stcOcoInit.enOccrBufMode = OccrBufDisable;
    stcOcoInit.enOcmrBufMode = OcmrBufDisable;
    stcOcoInit.enPortLevel = OcPortLevelLow;
    stcOcoInit.enOcoIntCmd = TIM4_DISABLE;
    if (p_dev->p_devinfo->pwm_ch == TIMER4_PWM_U)
    {
        /* Initialize OCO high channel */
        amhw_hc32f460_tim4_oco_init(p_hw_tim, TIMER4_OCO_OUH, &stcOcoInit); 
        /* Initialize OCO low channel */
        amhw_hc32f460_tim4_oco_init(p_hw_tim, TIMER4_OCO_OUL, &stcOcoInit); 
        enOcohigCh = TIMER4_OCO_OUH;
        enOcoLowCh = TIMER4_OCO_OUL;        
    } else if (p_dev->p_devinfo->pwm_ch == TIMER4_PWM_V) {
        /* Initialize OCO high channel */
        amhw_hc32f460_tim4_oco_init(p_hw_tim, TIMER4_OCO_OVH, &stcOcoInit); 
        /* Initialize OCO low channel */
        amhw_hc32f460_tim4_oco_init(p_hw_tim, TIMER4_OCO_OVL, &stcOcoInit);         
        enOcohigCh = TIMER4_OCO_OVH;
        enOcoLowCh = TIMER4_OCO_OVL;        
    } else if (p_dev->p_devinfo->pwm_ch == TIMER4_PWM_W) {
        /* Initialize OCO high channel */
        amhw_hc32f460_tim4_oco_init(p_hw_tim, TIMER4_OCO_OWH, &stcOcoInit); 
        /* Initialize OCO low channel */
        amhw_hc32f460_tim4_oco_init(p_hw_tim, TIMER4_OCO_OWL, &stcOcoInit); 
        enOcohigCh = TIMER4_OCO_OWH;
        enOcoLowCh = TIMER4_OCO_OWL; 
    } else {
        ;
    }
    
    /* ocmr[15:0] = 0x0FFF */
    stcHighChCmpMode.enCntZeroMatchOpState = OcoOpOutputReverse;
    stcHighChCmpMode.enCntZeroNotMatchOpState = OcoOpOutputHold;
    stcHighChCmpMode.enCntUpCntMatchOpState = OcoOpOutputReverse;
    stcHighChCmpMode.enCntPeakMatchOpState = OcoOpOutputReverse;
    stcHighChCmpMode.enCntPeakNotMatchOpState = OcoOpOutputHold;
    stcHighChCmpMode.enCntDownCntMatchOpState = OcoOpOutputReverse;
    
    stcHighChCmpMode.enCntZeroMatchOcfState = OcoOcfSet;
    stcHighChCmpMode.enCntUpCntMatchOcfState = OcoOcfSet;
    stcHighChCmpMode.enCntPeakMatchOcfState = OcoOcfSet;
    stcHighChCmpMode.enCntDownCntMatchOcfState = OcoOcfSet;
    
    stcHighChCmpMode.enMatchConditionExtendCmd = TIM4_DISABLE;
    
    /* Set OCO high channel compare mode */
    amhw_hc32f460_tim4_oco_set_h_ch_cmp_mode(p_hw_tim, enOcohigCh, &stcHighChCmpMode);  
    
    /* OCMR[31:0] Ox 0FF0 0FFF    0000 1111 1111 0000   0000 1111 1111 1111 */
    stcLowChCmpMode.enCntZeroLowMatchHighMatchLowChOpState = OcoOpOutputReverse;         /* bit[27:26]  11 */
    stcLowChCmpMode.enCntZeroLowMatchHighNotMatchLowChOpState = OcoOpOutputReverse;      /* bit[11:10]  11 */
    stcLowChCmpMode.enCntZeroLowNotMatchHighMatchLowChOpState = OcoOpOutputHold;         /* bit[31:30]  00 */
    stcLowChCmpMode.enCntZeroLowNotMatchHighNotMatchLowChOpState = OcoOpOutputHold;      /* bit[15:14]  00 */
    
    stcLowChCmpMode.enCntUpCntLowMatchHighMatchLowChOpState = OcoOpOutputReverse;        /* bit[25:24]  11 */
    stcLowChCmpMode.enCntUpCntLowMatchHighNotMatchLowChOpState = OcoOpOutputReverse;     /* bit[9:8]    11 */
    stcLowChCmpMode.enCntUpCntLowNotMatchHighMatchLowChOpState = OcoOpOutputHold;        /* bit[19:18]  00 */
    
    stcLowChCmpMode.enCntPeakLowMatchHighMatchLowChOpState = OcoOpOutputReverse;         /* bit[23:22]  11 */
    stcLowChCmpMode.enCntPeakLowMatchHighNotMatchLowChOpState = OcoOpOutputReverse;      /* bit[7:6]    11 */
    stcLowChCmpMode.enCntPeakLowNotMatchHighMatchLowChOpState = OcoOpOutputHold;         /* bit[29:28]  00 */
    stcLowChCmpMode.enCntPeakLowNotMatchHighNotMatchLowChOpState = OcoOpOutputHold;      /* bit[13:12]  00 */
    
    stcLowChCmpMode.enCntDownLowMatchHighMatchLowChOpState = OcoOpOutputReverse;         /* bit[21:20]  11 */
    stcLowChCmpMode.enCntDownLowMatchHighNotMatchLowChOpState = OcoOpOutputReverse;      /* bit[5:4]    11 */
    stcLowChCmpMode.enCntDownLowNotMatchHighMatchLowChOpState = OcoOpOutputHold;         /* bit[17:16]  00 */
    
    stcLowChCmpMode.enCntZeroMatchOcfState = OcoOcfSet;    /* bit[3] 1 */
    stcLowChCmpMode.enCntUpCntMatchOcfState = OcoOcfSet;   /* bit[2] 1 */
    stcLowChCmpMode.enCntPeakMatchOcfState = OcoOcfSet;    /* bit[1] 1 */
    stcLowChCmpMode.enCntDownCntMatchOcfState = OcoOcfSet; /* bit[0] 1 */
    
    amhw_hc32f460_tim4_oco_set_l_ch_cmp_mode(p_hw_tim, enOcoLowCh, &stcLowChCmpMode);  /* Set OCO low channel compare mode */

}

/**
  * \brief tim pwm�����ʼ��
  */
am_pwm_handle_t am_hc32f460_tim4_pwm_init (am_hc32f460_tim4_pwm_dev_t           *p_dev,
                                        const am_hc32f460_tim4_pwm_devinfo_t *p_devinfo)
{
    amhw_hc32f460_tim4_t  *p_hw_tim = NULL;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->chan_max = 6;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo        = p_devinfo;
    p_hw_tim                = (amhw_hc32f460_tim4_t *)p_dev->p_devinfo->tim_regbase;
    p_dev->pwm_serv.p_funcs = (struct am_pwm_drv_funcs *)&__g_tim_pwm_drv_funcs;
    p_dev->pwm_serv.p_drv   = p_dev;

    /* Set default value */
    p_hw_tim->CCSR = (uint16_t)0x0050u;
    p_hw_tim->CNTR = (uint16_t)0x0000u;
    p_hw_tim->CPSR = (uint16_t)0xFFFFu;
    p_hw_tim->CVPR = (uint16_t)0x0000u;

    amhw_hc32f460_tim4_disable(p_hw_tim, 0);
    
    __tim_pwm_init(p_hw_tim, p_dev);

    return &(p_dev->pwm_serv);
}

void am_hc32f460_tim4_pwm_deinit (am_pwm_handle_t handle)
{

    am_hc32f460_tim4_pwm_dev_t *p_dev    = (am_hc32f460_tim4_pwm_dev_t *)handle;
    amhw_hc32f460_tim4_t       *p_hw_tim = NULL;

    if (p_dev == NULL ) {
        return;
    }

    p_hw_tim   = (amhw_hc32f460_tim4_t *)p_dev->p_devinfo->tim_regbase;

    /* ��������� */
    amhw_hc32f460_tim4_cnt16_count_set(p_hw_tim, p_dev->p_devinfo->pwm_ch, 0);

    /* ���ܶ�ʱ��TIM������� */
    amhw_hc32f460_tim4_disable(p_hw_tim, 0);

    p_dev->pwm_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
