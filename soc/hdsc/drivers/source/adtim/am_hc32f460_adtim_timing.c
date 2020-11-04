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
 * - 1.00 19-10-09  zp, first implementation
 * \endinternal
 */
#include "hc32f460_clk.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_hc32f460_adtim_timing.h"
#include "am_clk.h"
#include "hc32f460_irq_handle.h"
#include "hc32f460_intctrl.h"
#include "am_vdebug.h"
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

#define TMR6x_GCMA    (1 << 0)
#define TMR6x_GCMB    (1 << 1)
#define TMR6x_GCMC    (1 << 2)
#define TMR6x_GCMD    (1 << 3)
#define TMR6x_GCME    (1 << 4)
#define TMR6x_GCMF    (1 << 5)
#define TMR6x_GOVF    (1 << 6)
#define TMR6x_GUDF    (1 << 7)
#define TMR6x_GDTE    (1 << 8)
#define TMR6x_SCMA    (1 << 11)
#define TMR6x_SCMB    (1 << 12)

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
    am_hc32f460_adtim_timing_dev_t *p_dev      = (am_hc32f460_adtim_timing_dev_t *)p_arg;
    amhw_hc32f460_adtim_t          *p_hw_adtim = (amhw_hc32f460_adtim_t *)
                                                 p_dev->p_devinfo->adtim_regbase;

    /*
     * �ж��Ƿ��Ƕ�ʱ������ж�
     */
    if ((amhw_hc32f460_adtim_get_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFF_FLAG)) ==
         AM_TRUE) {

        if (p_dev->pfn_callback != NULL) {
            p_dev->pfn_callback(p_dev->p_arg);
        }

        amhw_hc32f460_adtim_clearcount(p_hw_adtim);

        amhw_hc32f460_adtim_clear_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFF_FLAG);
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
    am_hc32f460_adtim_timing_dev_t *p_dev = (am_hc32f460_adtim_timing_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq =  am_clk_rate_get(CLK_TIMER6_1);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_prescale_set (void    *p_drv,
                                        uint8_t  chan,
                                        uint32_t prescale)
{
    am_hc32f460_adtim_timing_dev_t   *p_dev = (am_hc32f460_adtim_timing_dev_t *)
                                             p_drv;
    amhw_hc32f460_adtim_t            *p_hw_adtim;
    amhw_hc32f460_adtim_basecnt_cfg_t basecnt;

    if ((p_drv == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    basecnt.cntmode   = AMHW_HC32F460_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_HC32F460_ADTIM_CNT_DIR_UP;

    if ((prescale != 0) && (prescale <= 1024)) {

        if(prescale <= 1) {
            basecnt.cntclkdiv  = AMHW_HC32F460_ADTIM_PCLK_DIV1;
            p_dev->prescale_in = 1;
        } else if(prescale <= 2) {
            basecnt.cntclkdiv  = AMHW_HC32F460_ADTIM_PCLK_DIV2;
            p_dev->prescale_in = 2;
        } else if(prescale <= 4) {
            basecnt.cntclkdiv  = AMHW_HC32F460_ADTIM_PCLK_DIV4;
            p_dev->prescale_in = 4;
        } else if(prescale <= 8) {
            basecnt.cntclkdiv = AMHW_HC32F460_ADTIM_PCLK_DIV8;
            p_dev->prescale_in = 8;
        } else if(prescale <= 16) {
            basecnt.cntclkdiv  = AMHW_HC32F460_ADTIM_PCLK_DIV16;
            p_dev->prescale_in = 16;
        } else if(prescale <= 64) {
            basecnt.cntclkdiv  = AMHW_HC32F460_ADTIM_PCLK_DIV64;
            p_dev->prescale_in = 64;
        } else if(prescale <= 256) {
            basecnt.cntclkdiv  = AMHW_HC32F460_ADTIM_PCLK_DIV256;
            p_dev->prescale_in = 256;
        } else {
            basecnt.cntclkdiv  = AMHW_HC32F460_ADTIM_PCLK_DIV1024;
            p_dev->prescale_in = 1024;
        }

        p_dev->prescale_to = prescale;

        /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
        amhw_hc32f460_adtim_init(p_hw_adtim, &basecnt);

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __adtim_timing_prescale_get (void     *p_drv,
                                        uint8_t   chan,
                                        uint32_t *p_prescale)
{
    amhw_hc32f460_adtim_pclk_div_t  div   = AMHW_HC32F460_ADTIM_PCLK_DIV1;
    am_hc32f460_adtim_timing_dev_t *p_dev = (am_hc32f460_adtim_timing_dev_t *)p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (p_prescale == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��ȡ��Ƶֵ */
    div = amhw_hc32f460_adtim_clkdiv_get(p_hw_adtim);

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
    am_hc32f460_adtim_timing_dev_t *p_dev = (am_hc32f460_adtim_timing_dev_t *)p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (p_count == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    *(uint32_t *)p_count = amhw_hc32f460_adtim_getcount(p_hw_adtim);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_rollover_get (void *p_drv,uint8_t chan,void *p_rollover)
{
    am_hc32f460_adtim_timing_dev_t *p_dev = (am_hc32f460_adtim_timing_dev_t *)p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (p_rollover == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    *(uint32_t *)p_rollover = amhw_hc32f460_adtim_getperiod(p_hw_adtim, ADTIM_PERIODA);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_disable (void *p_drv, uint8_t chan)
{
    am_hc32f460_adtim_timing_dev_t *p_dev = (am_hc32f460_adtim_timing_dev_t *)p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim;
    
    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
    
    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��ֹ�����ж� */
    amhw_hc32f460_adtim_cfgirq(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFIrq, AM_FALSE);

    /* ��ʱ��ֹͣ */
    amhw_hc32f460_adtim_stopcount(p_hw_adtim);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_enable (void *p_drv, uint8_t chan, void *p_count)
{
    am_hc32f460_adtim_timing_dev_t *p_dev = (am_hc32f460_adtim_timing_dev_t *)p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim;
    uint16_t                        count = *(uint16_t *)p_count;


    if ((p_dev == NULL) || (chan != 0) || (p_count == NULL)) {
        return -AM_EINVAL;
    }

    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��ʱ��ֹͣ */
    amhw_hc32f460_adtim_stopcount(p_hw_adtim);

    count = count * p_dev->prescale_to / p_dev->prescale_in;

    /* ���ü������� */
    amhw_hc32f460_adtim_setperiod(p_hw_adtim, ADTIM_PERIODA, count);

    /* ��������� */
    amhw_hc32f460_adtim_clearcount(p_hw_adtim);

    /* ��������жϱ�־ */
    amhw_hc32f460_adtim_clearallirqflag(p_hw_adtim);

    if (p_dev->pfn_callback != NULL) {

        /* ���������ж� */
        amhw_hc32f460_adtim_cfgirq(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFIrq, AM_TRUE);
    }

    /* ��ʱ������ */
    amhw_hc32f460_adtim_startcount(p_hw_adtim);

    return AM_OK;
}

/******************************************************************************/
static int __adtim_timing_callback_set (void     *p_drv,
                                        uint8_t   chan,
                                        void    (*pfn_callback)(void *),
                                        void     *p_arg)
{
    am_hc32f460_adtim_timing_dev_t *p_dev = (am_hc32f460_adtim_timing_dev_t *)p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim;

    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ����Ҫ�����ж� */
    if (pfn_callback == NULL) {
        amhw_hc32f460_adtim_cfgirq(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFIrq, AM_FALSE);
    } else {
        p_dev->pfn_callback = pfn_callback;
        p_dev->p_arg   = p_arg;
    }

    return AM_OK;
}

/*******************************************************************************
  Public functions
*******************************************************************************/

am_timer_handle_t am_hc32f460_adtim_timing_init (
    am_hc32f460_adtim_timing_dev_t             *p_dev,
    const am_hc32f460_adtim_timing_devinfo_t   *p_devinfo)
{
    amhw_hc32f460_adtim_t *p_hw_tim = NULL;

    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo            = p_devinfo;
    p_hw_tim                  = (amhw_hc32f460_adtim_t *)(p_dev->p_devinfo->adtim_regbase);
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

    __g_adtim_timing_info.prescaler = 0x55f;

    if ((amhw_hc32f460_adtim_t *)HC32F460_TMR61_BASE == p_hw_tim)
    {    
        am_int_connect(p_dev->p_devinfo->inum, IRQ131_Handler, NULL);
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, (TMR6x_GOVF) << 0);
    }else if ((amhw_hc32f460_adtim_t *)HC32F460_TMR62_BASE == p_hw_tim)
    {    
        am_int_connect(p_dev->p_devinfo->inum, IRQ131_Handler, NULL);
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, (TMR6x_GOVF) << 16);
    }else if ((amhw_hc32f460_adtim_t *)HC32F460_TMR63_BASE == p_hw_tim)
    {
        am_int_connect(p_dev->p_devinfo->inum, IRQ132_Handler, NULL);    
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, (TMR6x_GOVF) << 0);
    }else {
        ;
    }        
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->adtimer_serv);
}

/******************************************************************************/
void am_hc32f460_adtim_timing_deinit (am_timer_handle_t handle)
{

    am_hc32f460_adtim_timing_dev_t *p_dev      = (am_hc32f460_adtim_timing_dev_t *)
                                               handle;
    amhw_hc32f460_adtim_t          *p_hw_adtim = NULL;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->adtim_regbase;

    /* ��������� */
    amhw_hc32f460_adtim_clearcount(p_hw_adtim);

    /* �ر�TIMģ�� */
    amhw_hc32f460_adtim_stopcount(p_hw_adtim);

    /* �ֶ���λ�Ĵ��� */
    amhw_hc32f460_adtim_deinit(p_hw_adtim);

//    am_int_disconnect(p_dev->p_devinfo->inum,
//                      __adtim_irq_handler,
//                      (void *)p_dev);

//    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->adtimer_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

void Timer61GOV_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer61GOV_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer61GUD_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer61GUD_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer61GDT_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer61GDT_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer61SCMA_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer61SCMA_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer61SCMB_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer61SCMB_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}

void Timer62GOV_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer62GOV_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer62GUD_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer62GUD_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer62GDT_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer62GDT_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer62SCMA_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer62SCMA_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer62SCMB_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer62SCMB_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}

void Timer63GOV_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer63GOV_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer63GUD_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer63GUD_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer63GDT_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer63GDT_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer63SCMA_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer63SCMA_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}
void Timer63SCMB_IrqHandler(void *p_arg)
{
//    AM_DBG_INFO("Timer63SCMB_IrqHandler!\r\n");
    __adtim_irq_handler(p_arg);
}


/* end of file */
