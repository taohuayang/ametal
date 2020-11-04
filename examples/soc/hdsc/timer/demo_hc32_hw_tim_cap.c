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
 * \brief ��ʱ���������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �ڶ�ʱ���������������� PWM��
 *
 * - ʵ������
 *   1. ���Դ��ڴ�ӡ���񵽵� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \par Դ����
 * \snippet demo_hc32_hw_tim_cap.c src_hc32_hw_tim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_tim_cap
 * \copydoc demo_hc32_hw_tim_cap.c
 */

/** [src_hc32_hw_tim_cap] */
#include "ametal.h"
#include "am_cap.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_hc32_tim.h"

/** \brief ����ͨ�� */
static uint8_t            __g_cap_chan;

/** \brief ������ɱ�־ */
static volatile am_bool_t __g_flag     = AM_FALSE;

/** \brief ���񵽵�����ʱ�� */
static volatile uint32_t  __g_time_ns  = 0;

/** \brief TIM ����Ƶ�� */
static uint32_t           __g_clk_rate = 0;

/**
 *  \brief �����жϴ�����
 */
static void __tim_cap_irq_handler (void *p_arg)
{
    amhw_hc32_tim_t      *p_hw_tim = (amhw_hc32_tim_t *)p_arg;
    volatile uint32_t     ifr      =  p_hw_tim->ifr;
    static am_bool_t      first    = AM_TRUE;
    static uint32_t       count;
    volatile uint16_t     val;
    uint32_t              chan_flag;

    /* Update interrupt flag */
    if (AM_BIT_ISSET(ifr, AMHW_HC32_TIM_INT_FLAG_UPDATE)) {
        /* �޷��ж��Ƿ��ǵ�ǰͨ��������µĸ��� */
    }

    /* ((channel % 2) * 3 + 2) + (channel / 2) */
    chan_flag = ((__g_cap_chan & 0x1) * 3 + 2) + (__g_cap_chan >> 1);

    /* Channel flag */
    if (AM_BIT_ISSET(ifr, chan_flag)) {
        /* CCR */
        val = amhw_hc32_tim_mode23_ccr_get(p_hw_tim, __g_cap_chan);
        if (__g_flag  == AM_FALSE) {
            if (first == AM_TRUE) {
                /* First */
                first =  AM_FALSE;
                count =  val;
            } else {
                /* Second */
                if (count < val) {
                    count       = val - count;
                    __g_time_ns = (uint64_t)1000000000 * count / __g_clk_rate;
                }

                first       = AM_TRUE;
                __g_flag    = AM_TRUE;
            }
        }
    }
    /* ����жϱ�־ */
    p_hw_tim->iclr &= ~ifr;
}

/**
 * \brief ���ö�ʱ��Ϊ���벶��
 */
static void tim_cap_chan_config (amhw_hc32_tim_t *p_hw_tim,
                                 uint32_t           chan,
                                 uint32_t           cap_edge)
{

     amhw_hc32_tim_filter_type_t filter_type =
                                       AMHW_HC32_TIM_FLITER_TYPE_FLTA0;

    /* ��Ƶϵ������ */
    amhw_hc32_tim_mode_clkdiv_set(p_hw_tim, AMHW_HC32_TIM_CLK_DIV1);

    switch(chan) {
    case 0:
        break;

    case 1:
        filter_type = AMHW_HC32_TIM_FLITER_TYPE_FLTB0;
        break;

    case 2:
        filter_type = AMHW_HC32_TIM_FLITER_TYPE_FLTA1;
        break;

    case 3:
        filter_type = AMHW_HC32_TIM_FLITER_TYPE_FLTB1;
        break;

    case 4:
        filter_type = AMHW_HC32_TIM_FLITER_TYPE_FLTA2;
        break;

    case 5:
        filter_type = AMHW_HC32_TIM_FLITER_TYPE_FLTB2;
        break;

    default:
        break;
    }

    /* ���������˲����ķ�ƵֵΪ0(Ĭ�ϲ�ʹ���˲�) */
    amhw_hc32_tim_mode23_fliter_set(p_hw_tim,
                                      filter_type,
                                      AMHW_HC32_TIM_FILTER_NO);

    /*  ѡ�������ش��� */
    if ((cap_edge & AM_CAP_TRIGGER_RISE) == AM_CAP_TRIGGER_RISE) {

        if((chan % 2) == 0) {
            amhw_hc32_tim_mode23_cra_enable(p_hw_tim, chan);
            amhw_hc32_tim_mode23_cfa_disable(p_hw_tim, chan);
        } else {
            amhw_hc32_tim_mode23_crb_enable(p_hw_tim, chan);
            amhw_hc32_tim_mode23_cfb_disable(p_hw_tim, chan);
        }
    }

    /*  ѡ���½��ش��� */
    if ((cap_edge & AM_CAP_TRIGGER_FALL) == AM_CAP_TRIGGER_FALL) {

        if((chan % 2) == 0) {
            amhw_hc32_tim_mode23_cra_disable(p_hw_tim, chan);
            amhw_hc32_tim_mode23_cfa_enable(p_hw_tim, chan);
        } else {
            amhw_hc32_tim_mode23_crb_disable(p_hw_tim, chan);
            amhw_hc32_tim_mode23_cfb_enable(p_hw_tim, chan);
        }
    }
}

static void tim_cap_enable (amhw_hc32_tim_t *p_hw_tim,
                            uint32_t           chan,
                            uint8_t            int_num)
{

    /* �ж����Ӳ�ʹ�� */
    am_int_connect(int_num, __tim_cap_irq_handler, (void *)p_hw_tim);
    am_int_enable(int_num);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_hc32_tim_arr_count_set(p_hw_tim, 0xffff);

    /* ��������ж� */
    amhw_hc32_tim_mode23_int_enable(p_hw_tim, AMHW_HC32_TIM_INT_UIE);

    /* �����ж�ʹ�� */
    if((chan % 2) == 0) {
        amhw_hc32_tim_mode23_ciea_int_enable(p_hw_tim, chan);
    } else {
        amhw_hc32_tim_mode23_cieb_int_enable(p_hw_tim, chan);
    }

    /* ʹ�ܶ�ʱ�� */
    amhw_hc32_tim_enable(p_hw_tim);

    /* ��������� */
    amhw_hc32_tim_cnt16_count_set(p_hw_tim, 0);

    /* ����жϱ�־ */
    amhw_hc32_tim_mode23_int_flag_clr(p_hw_tim, AMHW_HC32_TIM_INT_FLAG_ALL);
}

/**
 * \brief ��ʱ�����벶���ʼ������
 */
static void tim_cap_init (amhw_hc32_tim_t *p_hw_tim, uint32_t chan)
{
    /* ���ö�ʱ��ģʽ2 */
    amhw_hc32_tim_mode_set(p_hw_tim, AMHW_HC32_TIM_MODE_ZIGZAG);

    /* ���ϼ��� */
    amhw_hc32_tim_mode23_counter_up(p_hw_tim);

    /* ����ͨ��Ϊ����ģʽ */
    if((chan % 2) == 0) {
        amhw_hc32_tim_mode23_csa_cap(p_hw_tim, chan);
    } else {
        amhw_hc32_tim_mode23_csb_cap(p_hw_tim, chan);
    }

    /* ��ʱ��ʱ��Ϊ�ڲ�ʱ�� */
    amhw_hc32_tim_mode_clk_src_set(p_hw_tim,AMHW_HC32_TIM_CLK_SRC_TCLK);

    /* ��������� */
    amhw_hc32_tim_cnt16_count_set(p_hw_tim, 0);
}

/**
 * \brief ��ʱ���������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32_hw_tim_cap_entry (void     *p_hw_tim,
                                 uint32_t  chan,
                                 uint32_t  clk_rate,
                                 int32_t   inum)
{
    amhw_hc32_tim_t *p_tim = (amhw_hc32_tim_t *)p_hw_tim;

    uint32_t freq = 0; /* ���񵽵�Ƶ�� */

    __g_clk_rate = clk_rate;

    /* ��ʼ����ʱ��Ϊ������ */
    tim_cap_init(p_tim, chan);

    /* ���ö�ʱ������ͨ�� (��֧��˫���ش�������) */
    tim_cap_chan_config(p_tim,
                        chan,
                        AM_CAP_TRIGGER_RISE);

    tim_cap_enable(p_tim, chan, inum);

    while (1) {

        if (__g_flag == AM_TRUE) {
            freq = 1000000000 / __g_time_ns;
            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n",
                        __g_time_ns,
                        freq);
            __g_flag = AM_FALSE;
        }
    }
}
/** [src_hc32_hw_tim_cap] */

/* end of file */
