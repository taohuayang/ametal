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
 * \note: ���ж�ʱ����֧��˫���� ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation
 * \endinternal
 */

#include "am_hk32f103rbt6_tim_cap.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_clk.h"

/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ����������� */
static int __hk32f103rbt6_tim_cap_config (void              *p_cookie,
                                 int                chan,
                                 unsigned int       flags,
                                 am_cap_callback_t  pfn_callback,
                                 void              *p_arg);

/** \brief ʹ�ܲ���ͨ�� */
static int __hk32f103rbt6_tim_cap_enable (void *p_drv, int chan);

/** \brief ���ܲ���ͨ�� */
static int __hk32f103rbt6_tim_cap_disable (void *p_drv, int chan);

/** \brief ��λ����ͨ������ֵ */
static int __hk32f103rbt6_tim_cap_reset (void *p_drv, int chan);

static int __hk32f103rbt6_tim_cap_count_to_time (void         *p_drv,
                                        int           chan,
                                        unsigned int  count1,
                                        unsigned int  count2,
                                        unsigned int *p_time_ns);

static void __hk32f103rbt6_tim_cap_irq_handler (void *p_arg);

/** \brief ��������������� */
static const struct am_cap_drv_funcs __g_tim_cap_drv_funcs = {
    __hk32f103rbt6_tim_cap_config,
    __hk32f103rbt6_tim_cap_enable,
    __hk32f103rbt6_tim_cap_disable,
    __hk32f103rbt6_tim_cap_reset,
    __hk32f103rbt6_tim_cap_count_to_time,
};

/******************************************************************************/

/** \brief ����һ�����벶��ͨ�� */
static int __hk32f103rbt6_tim_cap_config (void              *p_drv,
                                 int                chan,
                                 unsigned int       options,
                                 am_cap_callback_t  pfn_callback,
                                 void              *p_arg)
{
    am_hk32f103rbt6_tim_cap_dev_t *p_dev    = (am_hk32f103rbt6_tim_cap_dev_t *)p_drv;
    amhw_hk32f103rbt6_tim_t       *p_hw_tim = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    /* ��֧��˫���ش��� */
    if ( (options & AM_CAP_TRIGGER_BOTH_EDGES) == AM_CAP_TRIGGER_BOTH_EDGES ) {
        return - AM_ENOTSUP;
    }

    /* �������벻��Ƶ, 1�α��ؾʹ��� 1�β��� */
    amhw_hk32f103rbt6_tim_icpsc_set(p_hw_tim, 0, chan);

    /* ѡ�������ͨ��ӳ�䲻���� */
    amhw_hk32f103rbt6_tim_ccs_set(p_hw_tim, 1, chan);

    /* ���������˲����ķ�ƵֵΪ0(Ĭ�ϲ�ʹ���˲�) */
    amhw_hk32f103rbt6_tim_icf_set(p_hw_tim, AMHW_HK32F103RBT6_TIM_ICF_FSAMPLING0, chan);

    /*  ѡ�������ش��� */
    if ((options & AM_CAP_TRIGGER_RISE) == AM_CAP_TRIGGER_RISE) {
        amhw_hk32f103rbt6_tim_ccp_captrigger_set(p_hw_tim,
                                           p_dev->p_devinfo->tim_type,
                                           AM_CAP_TRIGGER_RISE,
                                           chan);
    }

    /*  ѡ���½��ش��� */
    if ((options & AM_CAP_TRIGGER_FALL) == AM_CAP_TRIGGER_FALL) {
        amhw_hk32f103rbt6_tim_ccp_captrigger_set(p_hw_tim,
                                           p_dev->p_devinfo->tim_type,
                                           AM_CAP_TRIGGER_FALL,
                                           chan);
    }

    p_dev->callback_info[chan].callback_func = pfn_callback;
    p_dev->callback_info[chan].p_arg         = p_arg;

    return AM_OK;
}

/** \brief ����ʹ�� */
static int __hk32f103rbt6_tim_cap_enable (void *p_drv, int chan)
{
    am_hk32f103rbt6_tim_cap_dev_t    *p_dev    = (am_hk32f103rbt6_tim_cap_dev_t *)p_drv;
    amhw_hk32f103rbt6_tim_t          *p_hw_tim = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;
    am_hk32f103rbt6_tim_cap_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    /* �������� */
    am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].func);

    /* �ж����Ӳ�ʹ�� */
    am_int_connect(p_dev->p_devinfo->inum, __hk32f103rbt6_tim_cap_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_hk32f103rbt6_tim_arr_set(p_hw_tim, 0xffffffff);

    /* ��������� */
    amhw_hk32f103rbt6_tim_count_set(p_hw_tim, 0);

    /* ���������¼������³�ʼ��Prescaler������ ��Repetition������ */
    amhw_hk32f103rbt6_tim_egr_set(p_hw_tim, AMHW_HK32F103RBT6_TIM_UG);

    if (amhw_hk32f103rbt6_tim_status_flg_get(p_hw_tim, AMHW_HK32F103RBT6_TIM_UG) != 0) {

        /* ���¶�ʱ��ʱ����������¼�,�����־λ */
        amhw_hk32f103rbt6_tim_status_flg_clr(p_hw_tim, AMHW_HK32F103RBT6_TIM_UG);
    }

    /* �������������ֵ������Ĵ����� */
    amhw_hk32f103rbt6_tim_cce_cap_enable(p_hw_tim, chan);

    /* �������ж� */
    amhw_hk32f103rbt6_tim_int_enable(p_hw_tim, (1UL << (chan + 1)));

    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_hk32f103rbt6_tim_enable(p_hw_tim);

    return AM_OK;
}

/** \brief ������� */
static int __hk32f103rbt6_tim_cap_disable (void *p_drv, int chan)
{
    am_hk32f103rbt6_tim_cap_dev_t    *p_dev    = (am_hk32f103rbt6_tim_cap_dev_t *)p_drv;
    amhw_hk32f103rbt6_tim_t          *p_hw_tim = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;
    am_hk32f103rbt6_tim_cap_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    /* ��ԭGPIO���� */
    am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].dfunc);

    /* �Ͽ�NVIC�жϻص����� */
    am_int_disconnect(p_dev->p_devinfo->inum, __hk32f103rbt6_tim_cap_irq_handler, (void *)p_dev);
    am_int_disable(p_dev->p_devinfo->inum);

    /* ���ܲ����ж� */
    amhw_hk32f103rbt6_tim_int_disable(p_hw_tim, (1UL << (chan + 1)));

    /* ���ܶ�ʱ��TIM������� */
    amhw_hk32f103rbt6_tim_disable(p_hw_tim);

    return AM_OK;
}

/**
  * \brief ��λ����ͨ������ֵ
  */
static int __hk32f103rbt6_tim_cap_reset (void *p_drv, int chan)
{
    am_hk32f103rbt6_tim_cap_dev_t *p_dev    = (am_hk32f103rbt6_tim_cap_dev_t *)p_drv;
    amhw_hk32f103rbt6_tim_t       *p_hw_tim = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ���ܶ�ʱ��TIM������� */
    amhw_hk32f103rbt6_tim_disable(p_hw_tim);

    /* ��������� */
    amhw_hk32f103rbt6_tim_count_set(p_hw_tim, 0);

    /* ���������¼������³�ʼ��Prescaler������ ��Repetition������ */
    amhw_hk32f103rbt6_tim_egr_set(p_hw_tim, AMHW_HK32F103RBT6_TIM_UG);

    if (amhw_hk32f103rbt6_tim_status_flg_get(p_hw_tim, AMHW_HK32F103RBT6_TIM_UG) != 0) {

        /* ���¶�ʱ��ʱ����������¼�,�����־λ */
        amhw_hk32f103rbt6_tim_status_flg_clr(p_hw_tim, AMHW_HK32F103RBT6_TIM_UG);
    }

    return AM_OK;
}

/**
  * \brief ת�����β���ֵΪʱ��ֵ
  */
static int __hk32f103rbt6_tim_cap_count_to_time (void         *p_drv,
                                        int           chan,
                                        unsigned int  count1,
                                        unsigned int  count2,
                                        unsigned int *p_time_ns)
{
    am_hk32f103rbt6_tim_cap_dev_t *p_dev    = (am_hk32f103rbt6_tim_cap_dev_t *)p_drv;
    amhw_hk32f103rbt6_tim_t       *p_hw_tim = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    uint32_t count_err;
    uint64_t time_ns;
    uint16_t reg_pre, pre;

    uint32_t clkfreq  = am_clk_rate_get(p_dev->p_devinfo->clk_num);

    reg_pre = (uint16_t)amhw_hk32f103rbt6_tim_prescale_get(p_hw_tim);

    pre = reg_pre + 1;

    count_err = count2 - count1;

    /* �����ζ�ȡֵ�Ĳ�ת����ʱ�� */
    time_ns = (uint64_t)1000000000 * (uint64_t)count_err * pre / (uint64_t)clkfreq;

    *p_time_ns = time_ns;

    return AM_OK;
}

/**
  * \brief �жϷ�����
  */
static void __hk32f103rbt6_tim_cap_irq_handler (void *p_arg)
{
    am_hk32f103rbt6_tim_cap_dev_t *p_dev     = (am_hk32f103rbt6_tim_cap_dev_t *)p_arg;
    amhw_hk32f103rbt6_tim_t       *p_hw_tim  = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;
    uint8_t               chans_num = p_dev->p_devinfo->channels_num;

    uint8_t           i = 1;
    am_cap_callback_t callback_func;
    uint32_t          value;

    for (i = 1; i <= chans_num; i++) {
        if ((amhw_hk32f103rbt6_tim_status_flg_get(p_hw_tim, 1UL << i)) != 0) {

            callback_func = p_dev->callback_info[i - 1].callback_func;

            /* �õ���Ӧͨ����ֵ */
            value = amhw_hk32f103rbt6_tim_ccr_cap_val_get(p_hw_tim, i - 1);

            if (callback_func != NULL) {
                callback_func(p_dev->callback_info[i - 1].p_arg, value);
            }

            /* ���ͨ��i��־ */
            amhw_hk32f103rbt6_tim_status_flg_clr(p_hw_tim, (1UL << i));
        }
    }
}

/**
  * \brief �����ʼ��
  */
void __hk32f103rbt6_tim_cap_init (amhw_hk32f103rbt6_tim_t     *p_hw_tim,
                         amhw_hk32f103rbt6_tim_type_t type)
{
    if ((type == AMHW_HK32F103RBT6_TIM_TYPE0) || (type == AMHW_HK32F103RBT6_TIM_TYPE1))  {

        /* ���ض���ģʽ */
        amhw_hk32f103rbt6_tim_cms_set(p_hw_tim, 0);

        /* ���ϼ��� */
        amhw_hk32f103rbt6_tim_dir_set(p_hw_tim, 0);
    }

    /* ����ʱ�ӷָ�(����ȷ�������˲���������ʱ��Ƶ��,Ĭ�� Fdts = Fck_in */
    amhw_hk32f103rbt6_tim_ckd_set(p_hw_tim, 0);

    /* ��������� */
    amhw_hk32f103rbt6_tim_count_set(p_hw_tim, 0);

    /* ���÷�Ƶ�� */
    amhw_hk32f103rbt6_tim_prescale_set(p_hw_tim, 0x00);

    /* ��������¼� */
    amhw_hk32f103rbt6_tim_udis_enable(p_hw_tim);
}

am_cap_handle_t am_hk32f103rbt6_tim_cap_init (am_hk32f103rbt6_tim_cap_dev_t           *p_dev,
                                        const am_hk32f103rbt6_tim_cap_devinfo_t *p_devinfo)
{
    amhw_hk32f103rbt6_tim_t *p_hw_tim = NULL;
    uint8_t    i;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo        = p_devinfo;
    p_hw_tim                = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;
    p_dev->cap_serv.p_funcs = (struct am_cap_drv_funcs *)&__g_tim_cap_drv_funcs;
    p_dev->cap_serv.p_drv   = p_dev;

    for (i = 0; i < p_devinfo->channels_num; i++) {
        p_dev->callback_info[i].callback_func = NULL;
    }

    /* �����ʼ�� */
    __hk32f103rbt6_tim_cap_init(p_hw_tim, p_devinfo->tim_type);

    return &(p_dev->cap_serv);
}

void am_hk32f103rbt6_tim_cap_deinit (am_cap_handle_t handle)
{
    uint8_t i = 0;

    am_hk32f103rbt6_tim_cap_dev_t *p_dev    = (am_hk32f103rbt6_tim_cap_dev_t *)handle;
    amhw_hk32f103rbt6_tim_t       *p_hw_tim = NULL;

    am_hk32f103rbt6_tim_cap_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_tim     = (amhw_hk32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��������� */
    amhw_hk32f103rbt6_tim_count_set(p_hw_tim, 0);

    /* �ر�TIMģ�� */
    amhw_hk32f103rbt6_tim_disable(p_hw_tim);

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
