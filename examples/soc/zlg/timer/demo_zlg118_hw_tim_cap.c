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
 * \snippet demo_zlg118_hw_tim_cap.c src_zlg118_hw_tim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_tim_cap
 * \copydoc demo_zlg118_hw_tim_cap.c
 */

/** [src_zlg118_hw_tim_cap] */
#include "ametal.h"
#include "am_cap.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg118_tim.h"

static volatile am_bool_t g_flag       = AM_FALSE; /**< \brief �����־ */
static volatile uint32_t  g_time_ns    = 0;        /**< \brief �������ֵ */
static uint32_t           __g_clk_rate = 0;        /**< \brief ʱ��Ƶ�� */
static uint8_t            chans_num    = 0;        /**< \brief ĳһ��ʱ����ͨ������ */
static uint16_t           __update_num = 0;        /**< \brief ������� */
static uint16_t           pre          = 1;        /**< \brief ��Ƶϵ�� */

static void __zlg118_tim_hw_cap_irq_handler (void *p_arg)
{
    amhw_zlg118_tim_t *p_hw_tim  = (amhw_zlg118_tim_t *)p_arg;

    uint8_t            i         = 1;
    uint32_t           value     = 0;

    uint32_t           count_err = 0;
    uint64_t           time_ns   = 0;

    static uint32_t   count16   = 0;

    static am_bool_t  first     = AM_TRUE;

    if ((amhw_zlg118_tim_mode23_int_flag_check(p_hw_tim,
                AMHW_ZLG118_TIM_INT_FLAG_UPDATE)) == AM_TRUE) {

        __update_num++;

        amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim,
                                            AMHW_ZLG118_TIM_INT_FLAG_UPDATE);
    }

    for(i = 0; i < chans_num;i = i + 2) {
           if ((amhw_zlg118_tim_mode23_int_flag_check(p_hw_tim,
                                                      (i / 2) + 2)) ==
                                                      AM_TRUE) {

               /* �õ���Ӧͨ����ֵ */
               value = amhw_zlg118_tim_mode23_ccrxy_get(p_hw_tim, i) +
                       (__update_num << 16ul);

               if (g_flag == AM_FALSE) {

                   if (first == AM_TRUE) {

                       count16 = value;

                       first  = AM_FALSE;

                   } else {

                       /* ��ʱ��TIM����32λ������ʱ, �������ʱ���ݴ��� */
                       if(count16 < value) {

                            count_err = value - count16;

                            /* �����ζ�ȡֵ�Ĳ�ת����ʱ�� */
                            time_ns = (uint64_t)1000000000 *
                                                (uint64_t)count_err *
                                                pre /
                                                (uint64_t)__g_clk_rate;

                            g_time_ns = time_ns;
                       }

                       first = AM_TRUE;

                       /* �ñ�־Ϊ�棬����������� */
                       g_flag = AM_TRUE;
                   }
               }

               /* ���ͨ��i��־ */
               amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim, (i / 2) + 2);
           }
       }

       /* �жϱ�־  ��CH0B��CH1B��CH2B */
       for(i = 1; i < chans_num;i = i + 2) {
           if ((amhw_zlg118_tim_mode23_int_flag_check(p_hw_tim,
                                                      (i / 2) + 5)) ==
                                                      AM_TRUE) {

               /* �õ���Ӧͨ����ֵ */
               value = amhw_zlg118_tim_mode23_ccrxy_get(p_hw_tim, i) +
                       (__update_num << 16ul);

               if (g_flag == AM_FALSE) {

                   if (first == AM_TRUE) {

                       count16 = value;

                       first  = AM_FALSE;

                   } else {

                       /* ��ʱ��TIM����32λ������ʱ, �������ʱ���ݴ��� */
                       if(count16 < value) {

                            count_err = value - count16;

                            /* �����ζ�ȡֵ�Ĳ�ת����ʱ�� */
                            time_ns = (uint64_t)1000000000 *
                                                (uint64_t)count_err *
                                                pre /
                                                (uint64_t)__g_clk_rate;

                            g_time_ns = time_ns;
                       }

                       first = AM_TRUE;

                       /* �ñ�־Ϊ�棬����������� */
                       g_flag = AM_TRUE;
                   }
               }

               /* ���ͨ��i��־ */
               amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim,  (i / 2) + 5);
           }
       }
}

/**
 * \brief ���ö�ʱ��Ϊ���벶��
 */
static void tim_cap_chan_config (amhw_zlg118_tim_t *p_hw_tim,
                                 uint32_t           chan,
                                 uint32_t           cap_edge)
{

     amhw_zlg118_tim_filter_type_t filter_type =
                                       AMHW_ZLG118_TIM_FLITER_TYPE_FLTA0;

    /* ��Ƶϵ������ */
    amhw_zlg118_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZLG118_TIM_CLK_DIV1);

    pre = 1;

    switch(chan) {
    case 0:
        break;

    case 1:
        filter_type = AMHW_ZLG118_TIM_FLITER_TYPE_FLTB0;
        break;

    case 2:
        filter_type = AMHW_ZLG118_TIM_FLITER_TYPE_FLTA1;
        break;

    case 3:
        filter_type = AMHW_ZLG118_TIM_FLITER_TYPE_FLTB1;
        break;

    case 4:
        filter_type = AMHW_ZLG118_TIM_FLITER_TYPE_FLTA2;
        break;

    case 5:
        filter_type = AMHW_ZLG118_TIM_FLITER_TYPE_FLTB2;
        break;

    default:
        break;
    }

    /* ���������˲����ķ�ƵֵΪ0(Ĭ�ϲ�ʹ���˲�) */
    amhw_zlg118_tim_mode23_fliter_set(p_hw_tim,
                                      filter_type,
                                      AMHW_ZLG118_TIM_FILTER_NO);

    /*  ѡ�������ش��� */
    if ((cap_edge & AM_CAP_TRIGGER_RISE) == AM_CAP_TRIGGER_RISE) {

        if((chan % 2) == 0) {
            amhw_zlg118_tim_mode23_cra_enable(p_hw_tim, chan);
            amhw_zlg118_tim_mode23_cfa_disable(p_hw_tim, chan);
        } else {
            amhw_zlg118_tim_mode23_crb_enable(p_hw_tim, chan);
            amhw_zlg118_tim_mode23_cfb_disable(p_hw_tim, chan);
        }
    }

    /*  ѡ���½��ش��� */
    if ((cap_edge & AM_CAP_TRIGGER_FALL) == AM_CAP_TRIGGER_FALL) {

        if((chan % 2) == 0) {
            amhw_zlg118_tim_mode23_cra_disable(p_hw_tim, chan);
            amhw_zlg118_tim_mode23_cfa_enable(p_hw_tim, chan);
        } else {
            amhw_zlg118_tim_mode23_crb_disable(p_hw_tim, chan);
            amhw_zlg118_tim_mode23_cfb_enable(p_hw_tim, chan);
        }
    }
}

static void tim_cap_enable (amhw_zlg118_tim_t *p_hw_tim,
                            uint32_t           chan,
                            uint8_t            int_num)
{

    /* �ж����Ӳ�ʹ�� */
    am_int_connect(int_num, __zlg118_tim_hw_cap_irq_handler, (void *)p_hw_tim);
    am_int_enable(int_num);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg118_tim_arr_count_set(p_hw_tim, 0xffff);

    /* ��������ж� */
    amhw_zlg118_tim_mode23_int_enable(p_hw_tim, AMHW_ZLG118_TIM_INT_UIE);

    /* �����ж�ʹ�� */
    if((chan % 2) == 0) {
        amhw_zlg118_tim_mode23_ciea_int_enable(p_hw_tim, chan);
    } else {
        amhw_zlg118_tim_mode23_cieb_int_enable(p_hw_tim, chan);
    }

    /* ʹ�ܶ�ʱ�� */
    amhw_zlg118_tim_enable(p_hw_tim);

    /* ��������� */
    amhw_zlg118_tim_cnt16_count_set(p_hw_tim, 0);

    /* ����жϱ�־ */
    amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZLG118_TIM_INT_FLAG_ALL);
}

/**
 * \brief ��ʱ�����벶���ʼ������
 */
static void tim_cap_init (amhw_zlg118_tim_t *p_hw_tim, uint32_t chan)
{
    /* ���ö�ʱ��ģʽ2 */
    amhw_zlg118_tim_mode_set(p_hw_tim, AMHW_ZLG118_TIM_MODE_ZIGZAG);

    /* ���ϼ��� */
    amhw_zlg118_tim_mode23_counter_up(p_hw_tim);

    /* ����ͨ��Ϊ����ģʽ */
    if((chan % 2) == 0) {
        amhw_zlg118_tim_mode23_csa_cap(p_hw_tim, chan);
    } else {
        amhw_zlg118_tim_mode23_csb_cap(p_hw_tim, chan);
    }

    /* ��ʱ��ʱ��Ϊ�ڲ�ʱ�� */
    amhw_zlg118_tim_mode_clk_src_set(p_hw_tim,AMHW_ZLG118_TIM_CLK_SRC_TCLK);

    /* ��������� */
    amhw_zlg118_tim_cnt16_count_set(p_hw_tim, 0);
}

/**
 * \brief �������
 */
void demo_zlg118_hw_tim_cap_entry (void     *p_hw_tim,
                                   uint8_t   type,
                                   uint32_t  chan,
                                   uint32_t  clk_rate,
                                   int32_t   inum)
{
    amhw_zlg118_tim_t *p_tim = (amhw_zlg118_tim_t *)p_hw_tim;

    uint32_t freq = 0; /* ���񵽵�Ƶ�� */

    __g_clk_rate = clk_rate;

    if((amhw_zlg118_tim_type_t)type == AMHW_ZLG118_TIM_TYPE_TIM3) {
        chans_num = 6;
    } else {
        chans_num = 2;
    }

    /* ��ʼ����ʱ��Ϊ������ */
    tim_cap_init(p_tim, chan);

    /* ���ö�ʱ������ͨ�� (��֧��˫���ش�������) */
    tim_cap_chan_config(p_tim,
                        chan,
                        AM_CAP_TRIGGER_RISE);

    tim_cap_enable(p_tim, chan, inum);

    while (1) {

        if (g_flag == AM_TRUE) {

            freq = 1000000000 / g_time_ns;
            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n",
                        g_time_ns,
                        freq);
            g_flag = AM_FALSE;
        }
    }
}
/** [src_zlg118_hw_tim_cap] */

/* end of file */
