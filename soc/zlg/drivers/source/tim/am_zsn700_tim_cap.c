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
 * \brief TIM���������벶��������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */

#include "zsn700_clk.h"
#include "am_zsn700_tim_cap.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_clk.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/
static uint16_t  __update_num = 0;

/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ����������� */
static int __zsn700_tim_cap_config (void              *p_cookie,
                                    int                chan,
                                    unsigned int       flags,
                                    am_cap_callback_t  pfn_callback,
                                    void              *p_arg);

/** \brief ʹ�ܲ���ͨ�� */
static int __zsn700_tim_cap_enable (void *p_drv, int chan);

/** \brief ���ܲ���ͨ�� */
static int __zsn700_tim_cap_disable (void *p_drv, int chan);

/** \brief ��λ����ͨ������ֵ */
static int __zsn700_tim_cap_reset (void *p_drv, int chan);

static int __zsn700_tim_cap_count_to_time (void         *p_drv,
                                           int           chan,
                                           unsigned int  count1,
                                           unsigned int  count2,
                                           unsigned int *p_time_ns);

static void __zsn700_tim_cap_irq_handler (void *p_arg);

/** \brief ��������������� */
static const struct am_cap_drv_funcs __g_tim_cap_drv_funcs = {
    __zsn700_tim_cap_config,
    __zsn700_tim_cap_enable,
    __zsn700_tim_cap_disable,
    __zsn700_tim_cap_reset,
    __zsn700_tim_cap_count_to_time,
};

/******************************************************************************/

/** \brief ����һ�����벶��ͨ�� */
static int __zsn700_tim_cap_config (void              *p_drv,
                                    int                chan,
                                    unsigned int       options,
                                    am_cap_callback_t  pfn_callback,
                                    void              *p_arg)
{
    am_zsn700_tim_cap_dev_t *p_dev    = (am_zsn700_tim_cap_dev_t *)p_drv;
    amhw_zsn700_tim_t       *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    amhw_zsn700_tim_filter_type_t filter_type = AMHW_ZSN700_TIM_FLITER_TYPE_FLTA0;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->chan_max) {
        return -AM_EINVAL;
    }

    /* ��Ƶϵ������ */
    amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, p_dev->p_devinfo->clk_div);

    filter_type = (amhw_zsn700_tim_filter_type_t)(chan * 4);

    /* ���������˲����ķ�ƵֵΪ0(Ĭ�ϲ�ʹ���˲�) */
    amhw_zsn700_tim_mode23_fliter_set(p_hw_tim,
                                      filter_type,
                                      AMHW_ZSN700_TIM_FILTER_NO);

    /*  ѡ�������ش��� */
    if ((options & AM_CAP_TRIGGER_RISE) == AM_CAP_TRIGGER_RISE) {
        if(chan & 0x1) {
            amhw_zsn700_tim_mode23_crb_enable(p_hw_tim, chan);
            amhw_zsn700_tim_mode23_cfb_disable(p_hw_tim, chan);
        } else {
            amhw_zsn700_tim_mode23_cra_enable(p_hw_tim, chan);
            amhw_zsn700_tim_mode23_cfa_disable(p_hw_tim, chan);
        }
    }

    /*  ѡ���½��ش��� */
    if ((options & AM_CAP_TRIGGER_FALL) == AM_CAP_TRIGGER_FALL) {
        if(chan & 0x1) {
            amhw_zsn700_tim_mode23_crb_disable(p_hw_tim, chan);
            amhw_zsn700_tim_mode23_cfb_enable(p_hw_tim, chan);

        } else {
            amhw_zsn700_tim_mode23_cra_disable(p_hw_tim, chan);
            amhw_zsn700_tim_mode23_cfa_enable(p_hw_tim, chan);
        }
    }

    if((options & AM_CAP_TRIGGER_BOTH_EDGES) == AM_CAP_TRIGGER_BOTH_EDGES ) {
        if(chan & 0x1) {
            amhw_zsn700_tim_mode23_crb_enable(p_hw_tim, chan);
            amhw_zsn700_tim_mode23_cfb_enable(p_hw_tim, chan);
        } else {
            amhw_zsn700_tim_mode23_cra_enable(p_hw_tim, chan);
            amhw_zsn700_tim_mode23_cfa_enable(p_hw_tim, chan);
        }
    }


    p_dev->callback_info[chan].callback_func = pfn_callback;
    p_dev->callback_info[chan].p_arg         = p_arg;

    return AM_OK;
}

/** \brief ����ʹ�� */
static int __zsn700_tim_cap_enable (void *p_drv, int chan)
{
    int i = 0, enable_flag = 0;
    am_zsn700_tim_cap_dev_t    *p_dev    = (am_zsn700_tim_cap_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;
    am_zsn700_tim_cap_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->chan_max) {
        return -AM_EINVAL;
    }

    /* �������� */
    for(i = 0; i < p_dev->p_devinfo->channels_num; i++) {
        if((p_ioinfo[i].channel & 0x7f) ==  chan){
            am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].func);
            enable_flag = 1;
            break;
        }
    }

    /* ����ͨ������Ч */
    if(enable_flag == 0){
        return -AM_EINVAL;
    }

    /* �ж����Ӳ�ʹ�� */
    am_int_connect(p_dev->p_devinfo->inum, __zsn700_tim_cap_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zsn700_tim_arr_count_set(p_hw_tim, 0xffff);

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    /* ��������ж� */
    amhw_zsn700_tim_mode23_int_enable(p_hw_tim, AMHW_ZSN700_TIM_INT_UIE);

    /* �����ж�ʹ�� */
    if((chan & 0x01) == 0) {
        amhw_zsn700_tim_mode23_ciea_int_enable(p_hw_tim, chan);
    } else {
        amhw_zsn700_tim_mode23_cieb_int_enable(p_hw_tim, chan);
    }

    /* ʹ�ܶ�ʱ�� */
    amhw_zsn700_tim_enable(p_hw_tim);

    /* ����жϱ�־ */
    amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZSN700_TIM_INT_FLAG_ALL);

    return AM_OK;
}

/** \brief ������� */
static int __zsn700_tim_cap_disable (void *p_drv, int chan)
{
    int i = 0, disable_flag = 0;
    am_zsn700_tim_cap_dev_t    *p_dev    = (am_zsn700_tim_cap_dev_t *)p_drv;
    amhw_zsn700_tim_t          *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;
    am_zsn700_tim_cap_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    /* ��ԭ�������� */
    for(i = 0; i < p_dev->p_devinfo->channels_num; i++) {
        if((p_ioinfo[i].channel & 0x7f) ==  chan){
            am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].dfunc);
            disable_flag = 1;
            break;
        }
    }

    /* ����ͨ������Ч */
    if(disable_flag == 0){
        return -AM_EINVAL;
    }

    /* �Ͽ�NVIC�жϻص����� */
    am_int_disconnect(p_dev->p_devinfo->inum, __zsn700_tim_cap_irq_handler, (void *)p_dev);
    am_int_disable(p_dev->p_devinfo->inum);

    /* ��������ж� */
    amhw_zsn700_tim_mode23_int_disable(p_hw_tim, AMHW_ZSN700_TIM_INT_UIE);

    /* �����ж�ʹ�� */
    if((chan & 0x01) == 0) {
        amhw_zsn700_tim_mode23_ciea_int_disable(p_hw_tim, chan);
    } else {
        amhw_zsn700_tim_mode23_cieb_int_disable(p_hw_tim, chan);
    }

    /* ���ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_disable(p_hw_tim);

    return AM_OK;
}

/**
  * \brief ��λ����ͨ������ֵ
  */
static int __zsn700_tim_cap_reset (void *p_drv, int chan)
{
    am_zsn700_tim_cap_dev_t *p_dev    = (am_zsn700_tim_cap_dev_t *)p_drv;
    amhw_zsn700_tim_t       *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ���ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_disable(p_hw_tim);

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    /* ʹ�ܶ�ʱ�� */
    amhw_zsn700_tim_enable(p_hw_tim);

    /* ����жϱ�־ */
    amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZSN700_TIM_INT_FLAG_ALL);

    return AM_OK;
}

/**
  * \brief ת�����β���ֵΪʱ��ֵ
  */
static int __zsn700_tim_cap_count_to_time (void         *p_drv,
                                           int           chan,
                                           unsigned int  count1,
                                           unsigned int  count2,
                                           unsigned int *p_time_ns)
{
    am_zsn700_tim_cap_dev_t *p_dev    = (am_zsn700_tim_cap_dev_t *)p_drv;
    amhw_zsn700_tim_t       *p_hw_tim = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    uint32_t count_err;
    uint64_t time_ns;
    uint16_t reg_pre, pre;

    uint32_t clkfreq  = am_clk_rate_get(CLK_PCLK);

    reg_pre = (uint16_t)amhw_zsn700_tim_mode_clkdiv_get(p_hw_tim);

    if(reg_pre == 7) {
        pre = 256;
    } else {
        pre = 1 << reg_pre;
    }

    count_err =  count2 - count1;

    /* �����ζ�ȡֵ�Ĳ�ת����ʱ�� */
    time_ns = (uint64_t)1000000000 * (uint64_t)count_err * pre / (uint64_t)clkfreq;

    *p_time_ns = time_ns;

    return AM_OK;
}

/**
  * \brief �жϷ�����
  */
static void __zsn700_tim_cap_irq_handler (void *p_arg)
{
    am_zsn700_tim_cap_dev_t *p_dev     = (am_zsn700_tim_cap_dev_t *)p_arg;
    amhw_zsn700_tim_t       *p_hw_tim  = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    uint8_t           i = 0;
    am_cap_callback_t callback_func;
    uint32_t          value;

    if ((amhw_zsn700_tim_mode23_int_flag_check(p_hw_tim,
             AMHW_ZSN700_TIM_INT_FLAG_UPDATE)) == AM_TRUE) {

        __update_num++;

        amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim,
                                            AMHW_ZSN700_TIM_INT_FLAG_UPDATE);
    }

    /* �жϱ�־ ��CH0A��CH1A��CH2A��*/
    for(i = 0; i < p_dev->chan_max;i = i + 2) {
        if ((amhw_zsn700_tim_mode23_int_flag_check(p_hw_tim, (i / 2) + 2)) == AM_TRUE) {

            callback_func = p_dev->callback_info[i].callback_func;

            /* �õ���Ӧͨ����ֵ */
            value = amhw_zsn700_tim_mode23_ccrxy_get(p_hw_tim, i) + (__update_num << 16ul);

            if (callback_func != NULL) {
                callback_func(p_dev->callback_info[i].p_arg, value);
            }

            /* ���ͨ��i��־ */
            amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim, (i / 2) + 2);
        }
    }

    /* �жϱ�־  ��CH0B��CH1B��CH2B */
    for(i = 1; i < p_dev->chan_max;i = i + 2) {
        if ((amhw_zsn700_tim_mode23_int_flag_check(p_hw_tim, (i / 2) + 5)) == AM_TRUE) {

            callback_func = p_dev->callback_info[i].callback_func;

            /* �õ���Ӧͨ����ֵ */
            value = amhw_zsn700_tim_mode23_ccrxy_get(p_hw_tim, i) + (__update_num << 16ul);

            if (callback_func != NULL) {
                callback_func(p_dev->callback_info[i].p_arg, value);
            }

            /* ���ͨ��i��־ */
            amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim,  (i / 2) + 5);
        }
    }
}

/**
  * \brief �����ʼ��
  */
void __zsn700_tim_cap_init (amhw_zsn700_tim_t       *p_hw_tim,
                            am_zsn700_tim_cap_dev_t *p_dev,
                            amhw_zsn700_tim_type_t   type)
{
    uint8_t i = 0;

    /* ���ö�ʱ��ģʽ2 */
    amhw_zsn700_tim_mode_set(p_hw_tim, AMHW_ZSN700_TIM_MODE_ZIGZAG);

    /* ���ϼ��� */
    amhw_zsn700_tim_mode23_counter_up(p_hw_tim);

    /* ����ͨ��Ϊ����ģʽ ��CH0A��CH1A��CH2A��*/
    for(i = 0; i < p_dev->chan_max;i = i + 2) {
        amhw_zsn700_tim_mode23_csa_cap(p_hw_tim, i);
    }

    /* ����ͨ��Ϊ����ģʽ ��CH0B��CH1B��CH2B */
    for(i = 1; i < p_dev->chan_max;i = i + 2) {
        amhw_zsn700_tim_mode23_csb_cap(p_hw_tim, i);
    }

    /* ��ʱ��ʱ��Ϊ�ڲ�ʱ�� */
    amhw_zsn700_tim_mode_clk_src_set(p_hw_tim,AMHW_ZSN700_TIM_CLK_SRC_TCLK);

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    __update_num = 0;

}

am_cap_handle_t am_zsn700_tim_cap_init (am_zsn700_tim_cap_dev_t           *p_dev,
                                        const am_zsn700_tim_cap_devinfo_t *p_devinfo)
{
    amhw_zsn700_tim_t *p_hw_tim = NULL;
    uint8_t    i;

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
    p_dev->cap_serv.p_funcs = (struct am_cap_drv_funcs *)&__g_tim_cap_drv_funcs;
    p_dev->cap_serv.p_drv   = p_dev;

    for (i = 0; i < p_devinfo->channels_num; i++) {
        p_dev->callback_info[i].callback_func = NULL;
    }

    /* �����ʼ�� */
    __zsn700_tim_cap_init(p_hw_tim, p_dev, p_devinfo->tim_type);

    return &(p_dev->cap_serv);
}

void am_zsn700_tim_cap_deinit (am_cap_handle_t handle)
{
    uint8_t i = 0;

    am_zsn700_tim_cap_dev_t *p_dev    = (am_zsn700_tim_cap_dev_t *)handle;
    amhw_zsn700_tim_t       *p_hw_tim = NULL;

    am_zsn700_tim_cap_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_tim     = (amhw_zsn700_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    __update_num = 0;

    /* �ر�TIMģ�� */
    amhw_zsn700_tim_disable(p_hw_tim);

    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->cap_serv.p_drv = NULL;

    /* ��ԭGPIO���� */
    for (i = 0; i <p_dev->p_devinfo->channels_num; i++) {

        am_gpio_pin_cfg(p_ioinfo[i].gpio, p_ioinfo[i].dfunc);
    }

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
