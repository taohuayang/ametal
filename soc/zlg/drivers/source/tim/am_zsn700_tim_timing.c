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
 * \brief TIM��ʱ����������ʵ��
 *
 * \note
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */
#include "zsn700_clk.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_zsn700_tim_timing.h"
#include "am_clk.h"

/*******************************************************************************
  ��ʱ��������������
*******************************************************************************/

static const am_timer_info_t * __tim_timing_info_get (void *p_drv);

static int __tim_timing_clkin_freq_get (void *, uint32_t *);
static int __tim_timing_prescale_set (void *, uint8_t, uint32_t );
static int __tim_timing_prescale_get (void *, uint8_t, uint32_t *);
static int __tim_timing_count_get (void *, uint8_t, void *);
static int __tim_timing_rollover_get (void *, uint8_t, void *);
static int __tim_timing_disable (void *, uint8_t);
static int __tim_timing_enable (void *, uint8_t, void *);
static int __tim_timing_callback_set (void *, uint8_t, void (*)(void *), void *);

static void __tim_irq_handler (void *p_arg);

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/* ��ʱ����Ϣ */
static am_timer_info_t __g_tim_timing_info;

/* TIM��ʱ���������� */
static const struct am_timer_drv_funcs __g_tim_timing_drv_funcs = {
    __tim_timing_info_get,
    __tim_timing_clkin_freq_get,
    __tim_timing_prescale_set,
    __tim_timing_prescale_get,
    __tim_timing_count_get,
    __tim_timing_rollover_get,
    __tim_timing_enable,
    __tim_timing_disable,
    __tim_timing_callback_set,
};

/*******************************************************************************
  �жϴ���
*******************************************************************************/

void __tim_irq_handler (void *p_arg)
{
    am_zsn700_tim_timing_dev_t *p_dev    = (am_zsn700_tim_timing_dev_t *)p_arg;
    amhw_zsn700_tim_t          *p_hw_tim = (amhw_zsn700_tim_t *)
                                           p_dev->p_devinfo->tim_regbase;

    /*
     * �ж��Ƿ��Ƕ�ʱ������ж�
     */
    if (amhw_zsn700_tim_mode0_int_update_flag_check(p_hw_tim) == AM_TRUE ) {

        if (p_dev->pfn_callback != NULL) {
            p_dev->pfn_callback(p_dev->p_arg);
        }

        /* ��������־ */
        amhw_zsn700_tim_mode0_int_update_flag_clr(p_hw_tim);
    }
}

/*******************************************************************************
  ��׼��ʱ������ʵ��
*******************************************************************************/

static const am_timer_info_t * __tim_timing_info_get (void *p_drv)
{
    return &__g_tim_timing_info;
}

/******************************************************************************/
static int __tim_timing_clkin_freq_get (void *p_drv, uint32_t *p_freq)
{
    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq =  am_clk_rate_get(CLK_PCLK);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_prescale_set (void    *p_drv, 
                                      uint8_t  chan, 
                                      uint32_t prescale)
{
    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim;

    if ((p_drv == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    if ((prescale != 0) && (prescale <= 256)) {

        if(prescale <= 1) {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV1);
            p_dev->prescale_in = 1;
        } else if(prescale <= 2) {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV2);
            p_dev->prescale_in = 2;
        } else if(prescale <= 4) {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV4);
            p_dev->prescale_in = 4;
        } else if(prescale <= 8) {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV8);
            p_dev->prescale_in = 8;
        } else if(prescale <= 16) {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV16);
            p_dev->prescale_in = 16;
        } else if(prescale <= 32) {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV32);
            p_dev->prescale_in = 32;
        } else if(prescale <= 64) {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV64);
            p_dev->prescale_in = 64;
        } else {
            amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV256);
            p_dev->prescale_in = 256;
        }

        p_dev->prescale_to = prescale;

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __tim_timing_prescale_get (void     *p_drv, 
                                      uint8_t   chan, 
                                      uint32_t *p_prescale)
{

    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim;

    uint16_t div = 1;

    if ((p_dev == NULL) || (p_prescale == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��ȡ��Ƶֵ */
    div = (uint16_t)amhw_zsn700_tim_mode_clkdiv_get(p_hw_tim);

    if(div == 7) {
        *p_prescale = 256;
    } else {
        *p_prescale = 1 << div;
    }

    p_dev->prescale_in = *p_prescale;

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_count_get (void *p_drv, uint8_t chan, void *p_count)
{
    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_count == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;
    if(p_dev->p_devinfo->counter_type == AMHW_ZSN700_TIM_MODE0_COUNTER_32) {
        *(uint32_t *)p_count = amhw_zsn700_tim_cnt32_count_get(p_hw_tim);
    } else {
        *(uint32_t *)p_count = amhw_zsn700_tim_cnt16_count_get(p_hw_tim);
    }


    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_rollover_get (void *p_drv,uint8_t chan,void *p_rollover)
{
    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_rollover == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    if(p_dev->p_devinfo->counter_type == AMHW_ZSN700_TIM_MODE0_COUNTER_32) {
        *(uint32_t *)p_rollover = 0;
    } else {
        *(uint32_t *)p_rollover = 0xffff - amhw_zsn700_tim_arr_count_get(p_hw_tim);
    }

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_disable (void *p_drv, uint8_t chan)
{
    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim;
    
    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
    
    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ���ܸ����ж� */
    amhw_zsn700_tim_mode0_int_update_disable(p_hw_tim);

    amhw_zsn700_tim_disable(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_enable (void *p_drv, uint8_t chan, void *p_count)
{
    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim;
    uint16_t                    count = *(uint16_t *)p_count;

    if ((p_dev == NULL) || (chan != 0) || (p_count == NULL)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��ֹ��ʱ�������ж� */
    amhw_zsn700_tim_mode0_int_update_disable(p_hw_tim);

    count = count * p_dev->prescale_to / p_dev->prescale_in;

    /* ֻ����16λ������ģʽ�¿��������ؼĴ�����ֵ */
    if(p_dev->p_devinfo->counter_type == AMHW_ZSN700_TIM_MODE0_COUNTER_16) {

        amhw_zsn700_tim_arr_count_set(p_hw_tim, 65535 - count);
    }

    /* ���ü�������ֵ CNT */
    if(p_dev->p_devinfo->counter_type == AMHW_ZSN700_TIM_MODE0_COUNTER_16) {
        amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 65535 - count);
    } else {
        amhw_zsn700_tim_cnt32_count_set(p_hw_tim, 0xffffffff - count);
    }

    /* �Ƿ����ſ� */
    if(p_dev->p_devinfo->gate_enable == AMHW_ZSN700_TIM_GATE_ENABLE) {
        amhw_zsn700_tim_mode0_gate_enable(p_hw_tim);
    } else {
        amhw_zsn700_tim_mode0_gate_disable(p_hw_tim);
    }

    /* �ſ���Ч�ź����� */
    if(p_dev->p_devinfo->gate_state == AM_TRUE) {
        amhw_zsn700_tim_mode0_gate_high(p_hw_tim);
    } else {
        amhw_zsn700_tim_mode0_gate_low(p_hw_tim);
    }

    /* ����ʱ������ */
    if(p_dev->p_devinfo->clk_src == AMHW_ZSN700_TIM_CLK_SRC_TCLK) {
        amhw_zsn700_tim_mode_clk_src_set(p_hw_tim,AMHW_ZSN700_TIM_CLK_SRC_TCLK);
    } else {
        amhw_zsn700_tim_mode_clk_src_set(p_hw_tim,AMHW_ZSN700_TIM_CLK_SRC_ETR);
    }

    /* ���¶�ʱ��ʱ����������¼�,�����־λ */
    amhw_zsn700_tim_mode0_int_update_flag_clr(p_hw_tim);

    if (p_dev->pfn_callback != NULL) {

        /* ��������ж� */
        amhw_zsn700_tim_mode0_int_update_enable(p_hw_tim);
    }

    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_enable(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_callback_set (void     *p_drv,
                                      uint8_t   chan,
                                      void    (*pfn_callback)(void *),
                                      void     *p_arg)
{
    am_zsn700_tim_timing_dev_t *p_dev = (am_zsn700_tim_timing_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ����Ҫ�����ж� */
    if (pfn_callback == NULL) {
        amhw_zsn700_tim_mode0_int_update_disable(p_hw_tim);
    } else {
        p_dev->pfn_callback = pfn_callback;
        p_dev->p_arg   = p_arg;
    }

    return AM_OK;
}

/*******************************************************************************
  Public functions
*******************************************************************************/

am_timer_handle_t am_zsn700_tim_timing_init (
    am_zsn700_tim_timing_dev_t             *p_dev,
    const am_zsn700_tim_timing_devinfo_t  *p_devinfo)
{
    amhw_zsn700_tim_t *p_hw_tim = NULL;

    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo          = p_devinfo;
    p_hw_tim                  = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;
    p_dev->timer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_tim_timing_drv_funcs;
    p_dev->timer_serv.p_drv   = p_dev;

    p_dev->pfn_callback = NULL;
    p_dev->p_arg        = NULL;

    if(p_devinfo->counter_type == AMHW_ZSN700_TIM_MODE0_COUNTER_32) {

        amhw_zsn700_tim_mode0_counter_set(p_hw_tim,
                                          AMHW_ZSN700_TIM_MODE0_COUNTER_32);

        /* 32λ���ɼ���  0-0xFFFFFFFF��������������*/
        __g_tim_timing_info.counter_width = 32;

        __g_tim_timing_info.features =
            AM_TIMER_CAN_INTERRUPT   |  /* ���Բ����ж� */
            AM_TIMER_INTERMEDIATE_COUNT;/* ��ȡ��ǰ��������ֵ   */
    } else {

        amhw_zsn700_tim_mode0_counter_set(p_hw_tim,
                                          AMHW_ZSN700_TIM_MODE0_COUNTER_16);

        /* 16λ���ؼ���  ARR�Ĵ�����ֵ-0xFFFF������������*/
        __g_tim_timing_info.counter_width = 16;

        __g_tim_timing_info.features =
            AM_TIMER_CAN_INTERRUPT   |  /* ���Բ����ж� */
            AM_TIMER_AUTO_RELOAD     |  /* ֧���Զ����� */
            AM_TIMER_INTERMEDIATE_COUNT;/* ��ȡ��ǰ��������ֵ   */
    }

    /* ��ʱ��3 ������ͨ��*/
    if(p_devinfo->tim_type == AMHW_ZSN700_TIM_TYPE_TIM3) {
        __g_tim_timing_info.chan_num = 3;
    } else {
        __g_tim_timing_info.chan_num = 1;
    }

    __g_tim_timing_info.prescaler = 0xff;

    /* ���ö�ʱ��ģʽ0 */
    amhw_zsn700_tim_mode_set(p_hw_tim, AMHW_ZSN700_TIM_MODE_TIMING);

    am_int_connect(p_dev->p_devinfo->inum, __tim_irq_handler, (void *)p_dev);

    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->timer_serv);
}

/******************************************************************************/
void am_zsn700_tim_timing_deinit (am_timer_handle_t handle)
{

    am_zsn700_tim_timing_dev_t *p_dev    = (am_zsn700_tim_timing_dev_t *)handle;
    amhw_zsn700_tim_t          *p_hw_tim = NULL;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* �رո����ж� */
    amhw_zsn700_tim_mode0_int_update_disable(p_hw_tim);

    /* �رն�ʱ�� */
    amhw_zsn700_tim_disable(p_hw_tim);

    am_int_disconnect(p_dev->p_devinfo->inum, __tim_irq_handler, (void *)p_dev);
    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->timer_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
