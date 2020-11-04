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
 * \brief ADTIM��ʱ����������ʵ��
 *
 * \note
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */
#include "zsn700_clk.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_zsn700_adtim_timing.h"
#include "am_clk.h"

/*******************************************************************************
  ��ʱ��������������
*******************************************************************************/

static const am_timer_info_t * __adtim_timing_info_get (void *p_drv);

static int __adtim_timing_clkin_freq_get (void *, uint32_t *);
static int __adtim_timing_prescale_set (void *, uint8_t, uint32_t );
static int __adtim_timing_prescale_get (void *, uint8_t, uint32_t *);
static int __adtim_timing_count_get (void *, uint8_t, void *);
static int __adtim_timing_rollover_get (void *, uint8_t, void *);
static int __adtim_timing_disable (void *, uint8_t);
static int __adtim_timing_enable (void *, uint8_t, void *);
static int __adtim_timing_callback_set (void *, uint8_t, void (*)(void *), void *);

static void __adtim_irq_handler (void *p_arg);

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/* ��ʱ����Ϣ */
static am_timer_info_t __g_adtim_timing_info;

/* ADTIM��ʱ���������� */
static const struct am_timer_drv_funcs __g_adtim_timing_drv_funcs = {
    __adtim_timing_info_get,
    __adtim_timing_clkin_freq_get,
    __adtim_timing_prescale_set,
    __adtim_timing_prescale_get,
    __adtim_timing_count_get,
    __adtim_timing_rollover_get,
    __adtim_timing_enable,
    __adtim_timing_disable,
    __adtim_timing_callback_set,
};

/*******************************************************************************
  �жϴ���
*******************************************************************************/

void __adtim_irq_handler (void *p_arg)
{
    am_zsn700_adtim_timing_dev_t *p_dev      = (am_zsn700_adtim_timing_dev_t *)p_arg;
    amhw_zsn700_adtim_t          *p_hw_adtim = (amhw_zsn700_adtim_t *)
                                               p_dev->p_devinfo->adtim_regbase;

    /*
     * �ж��Ƿ��Ƕ�ʱ������ж�
     */
    if ((amhw_zsn700_adtim_getirqflag(p_hw_adtim, AMHW_ZSN700_ADTIM_OVFIrq)) ==
         AM_TRUE) {

        if (p_dev->pfn_callback != NULL) {
            p_dev->pfn_callback(p_dev->p_arg);
        }

        amhw_zsn700_adtim_clearcount(p_hw_adtim);

        amhw_zsn700_adtim_clearirqflag(p_hw_adtim, AMHW_ZSN700_ADTIM_OVFIrq);
    }
}

/*******************************************************************************
  ��׼��ʱ������ʵ��
*******************************************************************************/

static const am_timer_info_t * __adtim_timing_info_get (void *p_drv)
{
    return &__g_adtim_timing_info;
}

/******************************************************************************/
static int __adtim_timing_clkin_freq_get (void *p_drv, uint32_t *p_freq)
{
    am_zsn700_adtim_timing_dev_t *p_dev = (am_zsn700_adtim_timing_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq =  am_clk_rate_get(CLK_PCLK);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_prescale_set (void    *p_drv,
                                        uint8_t  chan,
                                        uint32_t prescale)
{
    am_zsn700_adtim_timing_dev_t   *p_dev = (am_zsn700_adtim_timing_dev_t *)
                                             p_drv;
    amhw_zsn700_adtim_t            *p_hw_adtim;
    amhw_zsn700_adtim_basecnt_cfg_t basecnt;

    if ((p_drv == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    basecnt.cntmode   = AMHW_ZSN700_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_ZSN700_ADTIM_CNT_DIR_UP;

    if ((prescale != 0) && (prescale <= 1024)) {

        if(prescale <= 1) {
            basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV1;
            p_dev->prescale_in = 1;
        } else if(prescale <= 2) {
            basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV2;
            p_dev->prescale_in = 2;
        } else if(prescale <= 4) {
            basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV4;
            p_dev->prescale_in = 4;
        } else if(prescale <= 8) {
            basecnt.cntclkdiv = AMHW_ZSN700_ADTIM_PCLK_DIV8;
            p_dev->prescale_in = 8;
        } else if(prescale <= 16) {
            basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV16;
            p_dev->prescale_in = 16;
        } else if(prescale <= 64) {
            basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV64;
            p_dev->prescale_in = 64;
        } else if(prescale <= 256) {
            basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV256;
            p_dev->prescale_in = 256;
        } else {
            basecnt.cntclkdiv  = AMHW_ZSN700_ADTIM_PCLK_DIV1024;
            p_dev->prescale_in = 1024;
        }

        p_dev->prescale_to = prescale;

        /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
        amhw_zsn700_adtim_init(p_hw_adtim, &basecnt);

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __adtim_timing_prescale_get (void     *p_drv,
                                        uint8_t   chan,
                                        uint32_t *p_prescale)
{
    amhw_zsn700_adtim_pclk_div_t  div   = AMHW_ZSN700_ADTIM_PCLK_DIV1;
    am_zsn700_adtim_timing_dev_t *p_dev = (am_zsn700_adtim_timing_dev_t *)p_drv;
    amhw_zsn700_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (p_prescale == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��ȡ��Ƶֵ */
    div = amhw_zsn700_adtim_clkdiv_get(p_hw_adtim);

    if(div >= 5) {
        *p_prescale = 1 << (div * 2 - 4);
    } else {
        *p_prescale = 1 << div;
    }

    p_dev->prescale_in = *p_prescale;

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_count_get (void *p_drv, uint8_t chan, void *p_count)
{
    am_zsn700_adtim_timing_dev_t *p_dev = (am_zsn700_adtim_timing_dev_t *)p_drv;
    amhw_zsn700_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (p_count == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    *(uint32_t *)p_count = amhw_zsn700_adtim_getcount(p_hw_adtim);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_rollover_get (void *p_drv,uint8_t chan,void *p_rollover)
{
    am_zsn700_adtim_timing_dev_t *p_dev = (am_zsn700_adtim_timing_dev_t *)p_drv;
    amhw_zsn700_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (p_rollover == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    *(uint32_t *)p_rollover = amhw_zsn700_adtim_getperiod(p_hw_adtim);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_disable (void *p_drv, uint8_t chan)
{
    am_zsn700_adtim_timing_dev_t *p_dev = (am_zsn700_adtim_timing_dev_t *)p_drv;
    amhw_zsn700_adtim_t          *p_hw_adtim;
    
    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
    
    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��ֹ�����ж� */
    amhw_zsn700_adtim_cfgirq(p_hw_adtim, AMHW_ZSN700_ADTIM_OVFIrq, AM_FALSE);

    /* ��ʱ��ֹͣ */
    amhw_zsn700_adtim_stopcount(p_hw_adtim);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_enable (void *p_drv, uint8_t chan, void *p_count)
{
    am_zsn700_adtim_timing_dev_t *p_dev = (am_zsn700_adtim_timing_dev_t *)p_drv;
    amhw_zsn700_adtim_t          *p_hw_adtim;
    uint16_t                      count = *(uint16_t *)p_count;


    if ((p_dev == NULL) || (chan != 0) || (p_count == NULL)) {
        return -AM_EINVAL;
    }

    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��ʱ��ֹͣ */
    amhw_zsn700_adtim_stopcount(p_hw_adtim);

    count = count * p_dev->prescale_to / p_dev->prescale_in;

    /* ���ü������� */
    amhw_zsn700_adtim_setperiod(p_hw_adtim, count);

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    /* ��������жϱ�־ */
    amhw_zsn700_adtim_clearallirqflag(p_hw_adtim);

    if (p_dev->pfn_callback != NULL) {

        /* ���������ж� */
        amhw_zsn700_adtim_cfgirq(p_hw_adtim, AMHW_ZSN700_ADTIM_OVFIrq, AM_TRUE);
    }

    /* ��ʱ������ */
    amhw_zsn700_adtim_startcount(p_hw_adtim);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_callback_set (void     *p_drv,
                                      uint8_t   chan,
                                      void    (*pfn_callback)(void *),
                                      void     *p_arg)
{
    am_zsn700_adtim_timing_dev_t *p_dev = (am_zsn700_adtim_timing_dev_t *)p_drv;
    amhw_zsn700_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ����Ҫ�����ж� */
    if (pfn_callback == NULL) {
        amhw_zsn700_adtim_cfgirq(p_hw_adtim, AMHW_ZSN700_ADTIM_OVFIrq, AM_FALSE);
    } else {
        p_dev->pfn_callback = pfn_callback;
        p_dev->p_arg   = p_arg;
    }

    return AM_OK;
}

/*******************************************************************************
  Public functions
*******************************************************************************/

am_timer_handle_t am_zsn700_adtim_timing_init (
    am_zsn700_adtim_timing_dev_t             *p_dev,
    const am_zsn700_adtim_timing_devinfo_t  *p_devinfo)
{
    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo            = p_devinfo;
    p_dev->adtimer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_adtim_timing_drv_funcs;
    p_dev->adtimer_serv.p_drv   = p_dev;

    p_dev->pfn_callback = NULL;
    p_dev->p_arg        = NULL;

    /* 16λ���ؼ��� ��������*/
    __g_adtim_timing_info.counter_width = 16;

    __g_adtim_timing_info.features =
        AM_TIMER_CAN_INTERRUPT   |  /* ���Բ����ж� */
        AM_TIMER_AUTO_RELOAD     |  /* ֧���Զ����� */
        AM_TIMER_INTERMEDIATE_COUNT;/* ��ȡ��ǰ��������ֵ   */

    __g_adtim_timing_info.prescaler = 0xff;

    am_int_connect(p_dev->p_devinfo->inum, __adtim_irq_handler, (void *)p_dev);

    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->adtimer_serv);
}

/******************************************************************************/
void am_zsn700_adtim_timing_deinit (am_timer_handle_t handle)
{

    am_zsn700_adtim_timing_dev_t *p_dev      = (am_zsn700_adtim_timing_dev_t *)
                                               handle;
    amhw_zsn700_adtim_t          *p_hw_adtim = NULL;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_adtim = (amhw_zsn700_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    /* �ر�TIMģ�� */
    amhw_zsn700_adtim_stopcount(p_hw_adtim);

    /* �ֶ���λ�Ĵ��� */
    amhw_zsn700_adtim_deinit(p_hw_adtim);

    am_int_disconnect(p_dev->p_devinfo->inum,
                      __adtim_irq_handler,
                      (void *)p_dev);

    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->adtimer_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
