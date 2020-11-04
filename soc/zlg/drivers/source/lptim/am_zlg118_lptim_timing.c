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
 * \brief   LPLPTIM��ʱ����������ʵ��
 *
 * \note
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27  zp, first implementation
 * \endinternal
 */
#include "am_int.h"
#include "am_clk.h"
#include "am_zlg118_lptim_timing.h"
#include "hw/amhw_zlg118_rcc.h"
#include "am_clk.h"
#include "zlg118_clk.h"

/* ����ͬһ�жϺŵ��豸���� */
#define PUBLIC_INUM_DEV_NUM      2

/*******************************************************************************
  ��ʱ��������������
*******************************************************************************/

static const am_timer_info_t * __lptim_timing_info_get (void *p_drv);

static int __lptim_timing_clkin_freq_get (void *, uint32_t *);
static int __lptim_timing_prescale_set (void *, uint8_t, uint32_t );
static int __lptim_timing_prescale_get (void *, uint8_t, uint32_t *);
static int __lptim_timing_count_get (void *, uint8_t, void *);
static int __lptim_timing_rollover_get (void *, uint8_t, void *);
static int __lptim_timing_disable (void *, uint8_t);
static int __lptim_timing_enable (void *, uint8_t, void *);
static int __lptim_timing_callback_set (void *, uint8_t, void (*)(void *), void *);

static void __lptim_irq_handler (void *p_arg);

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/* �豸�ṹ��ָ�� */
static
am_zlg118_lptim_timing_dev_t *__gp_dev[PUBLIC_INUM_DEV_NUM] = {NULL, NULL};

/* LPTIM��ʱ���������� */
static const struct am_timer_drv_funcs __g_lptim_timing_drv_funcs = {
    __lptim_timing_info_get,
    __lptim_timing_clkin_freq_get,
    __lptim_timing_prescale_set,
    __lptim_timing_prescale_get,
    __lptim_timing_count_get,
    __lptim_timing_rollover_get,
    __lptim_timing_enable,
    __lptim_timing_disable,
    __lptim_timing_callback_set,
};

/*******************************************************************************
  �жϴ���
*******************************************************************************/

void __lptim_irq_handler (void *p_arg)
{
    amhw_zlg118_lptim_t *p_hw_tim = NULL;

    if(__gp_dev[0] != NULL) {

        p_hw_tim = (amhw_zlg118_lptim_t *)__gp_dev[0]->p_devinfo->lptim_regbase;
        if (amhw_zlg118_lptim_int_flag_check(p_hw_tim) == AM_TRUE ) {

           if (__gp_dev[0]->pfn_callback != NULL) {
               __gp_dev[0]->pfn_callback(__gp_dev[0]->p_arg);
           }

           /* ��������־ */
           amhw_zlg118_lptim_int_flag_clr(p_hw_tim);
       }
    }

    if(__gp_dev[1] != NULL) {

        p_hw_tim = (amhw_zlg118_lptim_t *)__gp_dev[1]->p_devinfo->lptim_regbase;
        if (amhw_zlg118_lptim_int_flag_check(p_hw_tim) == AM_TRUE ) {

           if (__gp_dev[1]->pfn_callback != NULL) {
               __gp_dev[1]->pfn_callback(__gp_dev[1]->p_arg);
           }

           /* ��������־ */
           amhw_zlg118_lptim_int_flag_clr(p_hw_tim);
       }
    }

}

/*******************************************************************************
  ��׼��ʱ������ʵ��
*******************************************************************************/

static const am_timer_info_t * __lptim_timing_info_get (void *p_drv)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;

    if(p_dev->p_devinfo->lptim_regbase == ZLG118_LPTIM0_BASE) {
        return &(p_dev->timer_info);
    } else {
        return &(p_dev->timer_info);
    }
}

/******************************************************************************/
static int __lptim_timing_clkin_freq_get (void *p_drv, uint32_t *p_freq)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq =  p_dev->clk_rate;

    return AM_OK;
}

/******************************************************************************/
static int __lptim_timing_prescale_set (void    *p_drv,
                                        uint8_t  chan,
                                        uint32_t prescale)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;
    amhw_zlg118_lptim_t          *p_hw_tim;

    if ((p_drv == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    if ((prescale != 0) && (prescale <= 256)) {

        if(prescale == 1) {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim, AMHW_ZLG118_LPTIM_CLK_DIV1);
        } else if(prescale == 2) {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim, AMHW_ZLG118_LPTIM_CLK_DIV2);
        } else if(prescale == 4) {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim, AMHW_ZLG118_LPTIM_CLK_DIV4);
        } else if(prescale == 8) {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim, AMHW_ZLG118_LPTIM_CLK_DIV8);
        } else if(prescale == 16) {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim,
                                          AMHW_ZLG118_LPTIM_CLK_DIV16);
        } else if(prescale == 32) {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim,
                                          AMHW_ZLG118_LPTIM_CLK_DIV32);
        } else if(prescale == 64) {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim,
                                          AMHW_ZLG118_LPTIM_CLK_DIV64);
        } else {
            amhw_zlg118_lptim_clk_div_set(p_hw_tim,
                                          AMHW_ZLG118_LPTIM_CLK_DIV256);
        }

        p_dev->timer_info.prescaler = prescale;

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __lptim_timing_prescale_get (void     *p_drv,
                                        uint8_t   chan,
                                        uint32_t *p_prescale)
{
    amhw_zlg118_lptim_clk_div_t   div   = AMHW_ZLG118_LPTIM_CLK_DIV1;
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;
    amhw_zlg118_lptim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_prescale == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    /* ��ȡ��Ƶֵ */
    div = amhw_zlg118_lptim_clk_div_get(p_hw_tim);

    switch(div) {
    case AMHW_ZLG118_LPTIM_CLK_DIV1:
        *p_prescale = 1;
        break;
    case AMHW_ZLG118_LPTIM_CLK_DIV2:
        *p_prescale = 2;
        break;
    case AMHW_ZLG118_LPTIM_CLK_DIV4:
        *p_prescale = 4;
        break;
    case AMHW_ZLG118_LPTIM_CLK_DIV8:
        *p_prescale = 8;
        break;
    case AMHW_ZLG118_LPTIM_CLK_DIV16:
        *p_prescale = 16;
        break;
    case AMHW_ZLG118_LPTIM_CLK_DIV32:
        *p_prescale = 32;
        break;
    case AMHW_ZLG118_LPTIM_CLK_DIV64:
        *p_prescale = 64;
        break;
    case AMHW_ZLG118_LPTIM_CLK_DIV256:
        *p_prescale = 256;
        break;
    default:
        break;
    }

    return AM_OK;
}

/******************************************************************************/
static int __lptim_timing_count_get (void *p_drv, uint8_t chan, void *p_count)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;
    amhw_zlg118_lptim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_count == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    *(uint32_t *)p_count = amhw_zlg118_lptim_cnt16_count_get(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __lptim_timing_rollover_get (void *p_drv,uint8_t chan,void *p_rollover)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;
    amhw_zlg118_lptim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_rollover == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    *(uint32_t *)p_rollover = 0xffff - amhw_zlg118_lptim_arr_count_get(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __lptim_timing_disable (void *p_drv, uint8_t chan)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;
    amhw_zlg118_lptim_t          *p_hw_tim;
    
    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
    
    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    /* �����ж� */
    amhw_zlg118_lptim_int_disable(p_hw_tim);

    /* ���ܶ�ʱ�� */
    amhw_zlg118_lptim_disable(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __lptim_timing_enable (void *p_drv, uint8_t chan, void *p_count)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;
    amhw_zlg118_lptim_t          *p_hw_tim;

    if ((p_dev == NULL) || (chan != 0) || (p_count == NULL)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    /* ��ֹ��ʱ�������ж� */
    amhw_zlg118_lptim_int_disable(p_hw_tim);

    /* �ȴ�ͬ����� */
    while(amhw_zlg118_lptim_write_into_arr_stat(p_hw_tim) == AM_FALSE);

    amhw_zlg118_lptim_arr_count_set(p_hw_tim, 65535 - (*(uint16_t *)p_count));

    /* �Ƿ����ſ� */
    if(p_dev->p_devinfo->gate_enable == AM_TRUE) {
        amhw_zlg118_lptim_gate_enable(p_hw_tim);
    } else {
        amhw_zlg118_lptim_gate_disable(p_hw_tim);
    }

    /* �ſ���Ч�ź����� */
    if(p_dev->p_devinfo->gate_state == AM_TRUE) {
        amhw_zlg118_lptim_gate_high(p_hw_tim);
    } else {
        amhw_zlg118_lptim_gate_low(p_hw_tim);
    }

    /* TOG��TOGN�ź�������� */
    if(p_dev->p_devinfo->tog_state == AM_TRUE) {
        amhw_zlg118_lptim_tog_enable(p_hw_tim);
    } else {
        amhw_zlg118_lptim_tog_disable(p_hw_tim);
    }

    /* �����־λ */
    amhw_zlg118_lptim_int_flag_clr(p_hw_tim);

    if (p_dev->pfn_callback != NULL) {

        /* �ж�ʹ�� */
        amhw_zlg118_lptim_int_enable(p_hw_tim);
    }

    /* ʹ�ܶ�ʱ��LPTIM������� */
    amhw_zlg118_lptim_enable(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __lptim_timing_callback_set (void     *p_drv,
                                        uint8_t   chan,
                                        void    (*pfn_callback)(void *),
                                        void     *p_arg)
{
    am_zlg118_lptim_timing_dev_t *p_dev = (am_zlg118_lptim_timing_dev_t *)p_drv;
    amhw_zlg118_lptim_t          *p_hw_tim;

    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    /* ����Ҫ�����ж� */
    if (pfn_callback == NULL) {
        amhw_zlg118_lptim_disable(p_hw_tim);
    } else {
        p_dev->pfn_callback = pfn_callback;
        p_dev->p_arg        = p_arg;
    }

    return AM_OK;
}

/*******************************************************************************
  Public functions
*******************************************************************************/

am_timer_handle_t am_zlg118_lptim_timing_init (
    am_zlg118_lptim_timing_dev_t             *p_dev,
    const am_zlg118_lptim_timing_devinfo_t   *p_devinfo)
{
    uint8_t              i        = 0;
    am_bool_t            stat     = AM_FALSE;
    amhw_zlg118_lptim_t *p_hw_tim = NULL;

    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo          = p_devinfo;
    p_hw_tim                  = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;
    p_dev->timer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_lptim_timing_drv_funcs;
    p_dev->timer_serv.p_drv   = p_dev;

    p_dev->pfn_callback = NULL;
    p_dev->p_arg        = NULL;

    /* ����/��ʱ����ѡ�� */
    amhw_zlg118_lptim_function_sel(p_hw_tim, p_devinfo->fun_sel);

    /* �ж��Ƿ��ж�ʹ�ܺ����Ѿ����ӵ��жϺ��� */
    for(i = 0; i < PUBLIC_INUM_DEV_NUM; i++) {
        if(__gp_dev[i] != NULL) {
            stat = AM_TRUE;
            break;
        }
    }

    /* ��δ�����жϺ� */
    if(stat == AM_FALSE) {

        am_int_connect(p_dev->p_devinfo->inum, __lptim_irq_handler, NULL);
        am_int_enable(p_dev->p_devinfo->inum);
    }

    /* �жϻ���ַ���ֱ��ȡ�豸�ṹ��ָ�룬�Ա��жϻص��������ò�ͬ�豸�ص����� */
    if(p_dev->p_devinfo->lptim_regbase == ZLG118_LPTIM0_BASE) {
        __gp_dev[0] = p_dev;
    } else {
        __gp_dev[1] = p_dev;
    }

    /* 16λ����  ARR�Ĵ�����ֵ-0xFFFF���� */
    p_dev->timer_info.counter_width = 16;
    p_dev->timer_info.prescaler     = 0xff;
    p_dev->timer_info.chan_num      = 1;

    if(p_devinfo->mode == AMHW_ZLG118_LPTIM_MODE_RELOAD) {

        amhw_zlg118_lptim_mode_sel(p_hw_tim, AMHW_ZLG118_LPTIM_MODE_RELOAD);

        p_dev->timer_info.features =
              AM_TIMER_CAN_INTERRUPT   |  /* ���Բ����ж� */
              AM_TIMER_AUTO_RELOAD     |  /* ֧���Զ����� */
              AM_TIMER_INTERMEDIATE_COUNT;/* ��ȡ��ǰ��������ֵ   */

    } else {

        amhw_zlg118_lptim_mode_sel(p_hw_tim, AMHW_ZLG118_LPTIM_MODE_NORELOAD);

        p_dev->timer_info.features =
            AM_TIMER_CAN_INTERRUPT   |  /* ���Բ����ж� */
            AM_TIMER_INTERMEDIATE_COUNT;/* ��ȡ��ǰ��������ֵ   */
    }

    /* ʱ��Դ���� */
    amhw_zlg118_lptim_clk_src_sel(p_hw_tim, p_dev->p_devinfo->clk_src);

    if(p_dev->p_devinfo->clk_src == AMHW_ZLG118_LPTIM_CLK_SRC_XTL) {

        /* �ⲿ������������ѡ�� */
        amhw_zlg118_rcc_xtl_xtal_driver_set(AMHW_ZLG118_XTL_XTAL_DRIVER_DEFAULT);

        /* XTL�����񵴷��ȵĵ��� */
        amhw_zlg118_rcc_xtl_xtal_amplitude_set(
            AMHW_ZLG118_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

        /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
        amhw_zlg118_rcc_xtl_waittime_set(AMHW_ZLG118_XTL_WAITTIME_16384);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_xtl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_xtl_state_get() == AM_FALSE);

        p_dev->clk_rate = 32768;

    } else if(p_dev->p_devinfo->clk_src == AMHW_ZLG118_LPTIM_CLK_SRC_RCL) {

        /* ����RCLʱ��Ƶ��У׼ֵ ��38.4KHz��*/
        amhw_zlg118_rcc_rcl_trim_set(*((uint16_t*)AMHW_ZLG118_RCl_FRE_32768Hz));

        amhw_zlg118_rcc_rcl_waittime_set(AMHW_ZLG118_RCL_WAITTIME_256);

        amhw_zlg118_rcc_set_start(0x5A5A);
        amhw_zlg118_rcc_set_start(0xA5A5);

        amhw_zlg118_rcc_rcl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zlg118_rcc_rcl_state_get() == AM_FALSE);

        p_dev->clk_rate = 32768;
    } else {
        p_dev->clk_rate = am_clk_rate_get(CLK_PCLK);
    }

    return &(p_dev->timer_serv);
}

/******************************************************************************/
void am_zlg118_lptim_timing_deinit (am_timer_handle_t handle)
{

    uint8_t                       i        = 0;
    am_bool_t                     stat     = AM_FALSE;

    am_zlg118_lptim_timing_dev_t *p_dev    = (am_zlg118_lptim_timing_dev_t *)handle;
    amhw_zlg118_lptim_t          *p_hw_tim = NULL;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_tim = (amhw_zlg118_lptim_t *)p_dev->p_devinfo->lptim_regbase;

    /* �ر��ж� */
    amhw_zlg118_lptim_int_disable(p_hw_tim);

    /* �رն�ʱ�� */
    amhw_zlg118_lptim_disable(p_hw_tim);

    /* �жϻ���ַ���ֱ��ȡ�豸�ṹ��ָ�룬�Ա��жϻص��������ò�ͬ�豸�ص����� */
    if(p_dev->p_devinfo->lptim_regbase == ZLG118_LPTIM0_BASE) {
        __gp_dev[0] = NULL;
    } else {
        __gp_dev[1] = NULL;
    }


    /* �ж��Ƿ������豸�����ʼ�� */
    for(i = 0; i < PUBLIC_INUM_DEV_NUM; i++) {
        if(__gp_dev[i] != NULL) {
            stat = AM_TRUE;
            break;
        }
    }

    /* �Ѿ�ȫ�����ʼ������ɾ���жϺ����� */
    if(stat == AM_FALSE) {
        am_int_disconnect(p_dev->p_devinfo->inum, __lptim_irq_handler, (void *)p_dev);
        am_int_disable(p_dev->p_devinfo->inum);
    }

    p_dev->timer_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
