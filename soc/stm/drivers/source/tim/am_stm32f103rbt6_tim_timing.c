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
 * \note ������һ�������¼�ʱ�����еļĴ����������£�Ӳ��ͬʱ������ URS λ����
 * �ø��±�־λ��TIMx_SR�Ĵ����е� UIF λ�����ظ������������¼���ΪTIMx_RCR �Ĵ�
 * ����ֵ,�Զ�װ��Ӱ�ӼĴ�������������Ԥװ�ؼĴ�����ֵ  Ԥ��Ƶ���Ļ�����������Ԥ
 * װ�ؼĴ�����ֵ��TIMx_PSC �Ĵ��������ݣ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation
 * \endinternal
 */
#include "am_int.h"
#include "am_clk.h"
#include "am_stm32f103rbt6_tim_timing.h"
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
static const am_timer_info_t __g_tim_timing_info = {
    16,                                      /* 16λ��ʱ��               */
    1,                                       /* ��ͨ��                   */
    AM_TIMER_CAN_INTERRUPT      |            /* ���Բ����ж�             */
    AM_TIMER_AUTO_RELOAD        |            /* ֧���Զ�����             */
    AM_TIMER_INTERMEDIATE_COUNT |            /* ��ǰ������ֵ�ɶ�         */
    AM_TIMER_SUPPORT_ALL_PRESCALE_1_TO_MAX,  /* Ԥ��Ƶ��1 ~ 65536 ����ֵ */
    65536                                    /* Ԥ��Ƶ���ֵ��65536      */
};

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
    am_stm32f103rbt6_tim_timing_dev_t *p_dev    = (am_stm32f103rbt6_tim_timing_dev_t *)p_arg;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /*
     * �ж��Ƿ��Ƕ�ʱ������ж�
     */
    if (amhw_stm32f103rbt6_tim_status_flg_get(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIF) != 0 ) {

        if (p_dev->pfn_callback != NULL) {
            p_dev->pfn_callback(p_dev->p_arg);
        }

        /* ��������־ */
        amhw_stm32f103rbt6_tim_status_flg_clr(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIF);
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
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq =  am_clk_rate_get(p_dev->p_devinfo->clk_num);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_prescale_set (void    *p_drv, 
                                      uint8_t  chan, 
                                      uint32_t prescale)
{
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim;

    if ((p_drv == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    if ((prescale != 0) && (prescale <= 65536)) {
 
        amhw_stm32f103rbt6_tim_prescale_set(p_hw_tim, prescale - 1);  /* ���÷�Ƶֵ */

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __tim_timing_prescale_get (void     *p_drv, 
                                      uint8_t   chan, 
                                      uint32_t *p_prescale)
{
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_prescale == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��ȡ��Ƶֵ */
    *p_prescale = amhw_stm32f103rbt6_tim_prescale_get(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_count_get (void *p_drv, uint8_t chan, void *p_count)
{
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_count == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    *(uint32_t *)p_count = amhw_stm32f103rbt6_tim_count_get(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_rollover_get (void *p_drv,uint8_t chan,void *p_rollover)
{
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_rollover == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    *(uint32_t *)p_rollover = amhw_stm32f103rbt6_tim_arr_get(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_disable (void *p_drv, uint8_t chan)
{
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim;
    
    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
    
    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ���ܸ����ж� */
    amhw_stm32f103rbt6_tim_int_disable(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIE);

    amhw_stm32f103rbt6_tim_disable(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_enable (void *p_drv, uint8_t chan, void *p_count)
{
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (chan != 0) || (p_count == NULL)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��ֹ��ʱ�������ж� */
    amhw_stm32f103rbt6_tim_int_disable(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIE);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_stm32f103rbt6_tim_arr_set(p_hw_tim, *((uint32_t *)p_count));

    /* ��������0 */
    amhw_stm32f103rbt6_tim_count_set(p_hw_tim, 0);

    /* ���������¼������³�ʼ��Prescaler������ ��Repetition������ */
    amhw_stm32f103rbt6_tim_egr_set(p_hw_tim, AMHW_STM32F103RBT6_TIM_UG);

    /* ���¶�ʱ��ʱ����������¼�,�����־λ */
    amhw_stm32f103rbt6_tim_status_flg_clr(p_hw_tim, AMHW_STM32F103RBT6_TIM_UG);

    if (p_dev->pfn_callback != NULL) {

        /* ��������ж� */
        amhw_stm32f103rbt6_tim_int_enable(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIE);
    }

    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_stm32f103rbt6_tim_enable(p_hw_tim);

    return AM_OK;
}

/******************************************************************************/
static int __tim_timing_callback_set (void     *p_drv,
                                      uint8_t   chan,
                                      void    (*pfn_callback)(void *),
                                      void     *p_arg)
{
    am_stm32f103rbt6_tim_timing_dev_t *p_dev = (am_stm32f103rbt6_tim_timing_dev_t *)p_drv;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim;

    if ((p_dev == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }
 
    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* ����Ҫ�����ж� */
    if (pfn_callback == NULL) {
        amhw_stm32f103rbt6_tim_int_disable(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIE);
    } else {
        p_dev->pfn_callback = pfn_callback;
        p_dev->p_arg   = p_arg;
    }

    return AM_OK;
}

/*******************************************************************************
  Public functions
*******************************************************************************/

am_timer_handle_t am_stm32f103rbt6_tim_timing_init (
    am_stm32f103rbt6_tim_timing_dev_t             *p_dev,
    const am_stm32f103rbt6_tim_timing_devinfo_t  *p_devinfo)
{
    amhw_stm32f103rbt6_tim_t *p_hw_tim = NULL;

    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo          = p_devinfo;
    p_hw_tim                  = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;
    p_dev->timer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_tim_timing_drv_funcs;
    p_dev->timer_serv.p_drv   = p_dev;

    p_dev->pfn_callback = NULL;
    p_dev->p_arg        = NULL;

    if ((p_devinfo->tim_type == AMHW_STM32F103RBT6_TIM_TYPE0) ||
        (p_devinfo->tim_type == AMHW_STM32F103RBT6_TIM_TYPE1))  {

        /* ���ض���ģʽ */
        amhw_stm32f103rbt6_tim_cms_set(p_hw_tim, 0);

        /* ���ϼ��� */
        amhw_stm32f103rbt6_tim_dir_set(p_hw_tim, 0);
    }

    /* ����ʱ�ӷָ�:TDTS = Tck_tin */
    amhw_stm32f103rbt6_tim_ckd_set(p_hw_tim, 0);

    /* ��������¼� */
    amhw_stm32f103rbt6_tim_udis_enable(p_hw_tim);

    am_int_connect(p_dev->p_devinfo->inum, __tim_irq_handler, (void *)p_dev);

    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->timer_serv);
}

/******************************************************************************/
void am_stm32f103rbt6_tim_timing_deinit (am_timer_handle_t handle)
{

    am_stm32f103rbt6_tim_timing_dev_t *p_dev    = (am_stm32f103rbt6_tim_timing_dev_t *)handle;
    amhw_stm32f103rbt6_tim_t          *p_hw_tim = NULL;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_dev->p_devinfo->tim_regbase;

    /* �رո����ж� */
    amhw_stm32f103rbt6_tim_int_disable(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIE);

    /* �ر�ʱ�ӣ�ֹͣ���� */
    amhw_stm32f103rbt6_tim_disable(p_hw_tim);

    am_int_disconnect(p_dev->p_devinfo->inum, __tim_irq_handler, (void *)p_dev);
    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->timer_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
