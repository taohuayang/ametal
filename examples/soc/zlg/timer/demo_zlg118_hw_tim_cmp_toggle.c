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
 * \brief ��ʱ��ͨ���Ƚ�ƥ�����ŷ�ת���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ�������� 10Hz ��Ƶ�ʽ��з�ת��
 *   2. LED0 ��ת��
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_tim_cmp_toggle.c src_zlg118_hw_tim_cmp_toggle
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zlg118_hw_tim_cmp_toggle
 * \copydoc demo_zlg118_hw_tim_cmp_toggle.c
 */

/** [src_zlg118_hw_tim_cmp_toggle] */
#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg118_tim.h"
#include "am_led.h"

#define LED0          0

static uint8_t chan_num = 0;

/**
 * \brief CMP �жϷ�����
 */
static void __zlg118_tim_cmp_irq_handler (void *p_arg)
{
    amhw_zlg118_tim_t *p_hw_tim = (amhw_zlg118_tim_t *)p_arg;
    uint8_t         i        = 1;

    /* �жϱ�־  ��CH0A��CH1A��CH2A */
    for(i = 0; i < chan_num;i = i + 2) {
        if ((amhw_zlg118_tim_mode23_int_flag_check(p_hw_tim,
                                                   (i / 2) + 2)) ==
                                                   AM_TRUE) {

            if(amhw_zlg118_tim_mode23_ciea_int_get(p_hw_tim,i) == AM_TRUE)
            {
                am_led_toggle(LED0);

                /* ���ͨ��i��־ */
                amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim, (i / 2) + 2);
            }
        }
    }

    /* �жϱ�־  ��CH0B��CH1B��CH2B */
    for(i = 1; i < chan_num;i = i + 2) {
        if ((amhw_zlg118_tim_mode23_int_flag_check(p_hw_tim,
                                                   (i / 2) + 5)) ==
                                                   AM_TRUE) {

            if(amhw_zlg118_tim_mode23_cieb_int_get(p_hw_tim,i) == AM_TRUE)
            {
                am_led_toggle(LED0);

                /* ���ͨ��i��־ */
                amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim,  (i / 2) + 5);
            }
        }
    }
}

/**
 * \brief ���ö�ʱ������Ƚ�ģʽ��ƥ����ƽ������ת
 */
static void tim_cmp_toggle_chan_config (amhw_zlg118_tim_t *p_hw_tim,
                                        uint32_t        chan,
                                        uint32_t        cnt,
                                        uint8_t         clk_div)
{

    uint32_t match    = 0;
    uint16_t fre_div  = 1;

    /* ��Ƶϵ������ */
    amhw_zlg118_tim_mode_clkdiv_set(p_hw_tim,
                                    (amhw_zlg118_tim_clkdiv_t)clk_div);

    switch(clk_div) {
    case 0:
        fre_div = 1;
        break;

    case 1:
        fre_div = 2;
        break;

    case 2:
        fre_div = 4;
        break;

    case 3:
        fre_div = 8;
        break;

    case 4:
        fre_div = 16;
        break;

    case 5:
        fre_div = 32;
        break;

    case 6:
        fre_div = 64;
        break;

    case 7:
        fre_div = 256;
        break;

    default:
        break;
    }

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    match = cnt / fre_div ;

    if(match > 65535ul) {
        return ;
    }

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg118_tim_arr_count_set(p_hw_tim, match - 1);

    /* ��������� */
    amhw_zlg118_tim_cnt16_count_set(p_hw_tim, 0);

    /* ����ĳһͨ���ıȽ�ֵ */
    amhw_zlg118_tim_mode23_ccrxy_set(p_hw_tim, chan, match / 2 - 1);

    /* �Ƚ�ƥ��ʱ��ת */
    amhw_zlg118_tim_mode23_compare_set(
        p_hw_tim,
        (amhw_zlg118_tim_compare_type_t)(chan * 4),
        AMHW_ZLG118_TIM_COMPARE_FIT_TOGGLE);

    /* ������� */
    amhw_zlg118_tim_mode23_phase_same(
        p_hw_tim,
        (amhw_zlg118_tim_phase_type_t)(chan * 4 + 3));
}

void tim_cmp_toggle_enable (amhw_zlg118_tim_t     *p_hw_tim,
                            amhw_zlg118_tim_type_t type,
                            uint32_t               chan,
                            uint8_t                int_num)
{

    /* �����жϻص����� */
    am_int_connect(int_num, __zlg118_tim_cmp_irq_handler, (void *)p_hw_tim);
    am_int_enable(int_num);

    /* ����Ƚϴ����ж�ʹ�� */
    if((chan % 2) == 0) {

        amhw_zlg118_tim_mode23_ciea_int_enable(p_hw_tim, chan);
    } else {

        amhw_zlg118_tim_mode23_cieb_int_enable(p_hw_tim, chan);
    }

    /* ��������� */
    amhw_zlg118_tim_cnt16_count_set(p_hw_tim, 0);

    /* ����жϱ�־ */
    amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZLG118_TIM_INT_FLAG_ALL);

    /* PWM����ʹ�� */
    amhw_zlg118_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZLG118_TIM_DTR_MOE);

    /* ʹ�ܶ�ʱ�� */
    amhw_zlg118_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ�� TIM ����Ƚ�ͨ����ת��ʼ������
 */
void tim_cmp_toggle_init (amhw_zlg118_tim_t     *p_hw_tim,
                          amhw_zlg118_tim_type_t type,
                          uint8_t                chan)
{
    if((amhw_zlg118_tim_type_t)type == AMHW_ZLG118_TIM_TYPE_TIM3) {
        chan_num = 6;
    } else {
        chan_num = 2;
    }

    /* ���ö�ʱ��ģʽ2 */
    amhw_zlg118_tim_mode_set(p_hw_tim, AMHW_ZLG118_TIM_MODE_ZIGZAG);

    /* ���ϼ��� */
    amhw_zlg118_tim_mode23_counter_up(p_hw_tim);

    /* ����ͨ��Ϊ�Ƚ�ģʽ */
    if((chan % 2) == 0) {
        amhw_zlg118_tim_mode23_csa_compare(p_hw_tim, chan);
    } else {
        amhw_zlg118_tim_mode23_csb_compare(p_hw_tim, chan);
    }

    /* ��ʱ��ʱ��Ϊ�ڲ�ʱ�� */
    amhw_zlg118_tim_mode_clk_src_set(p_hw_tim,AMHW_ZLG118_TIM_CLK_SRC_TCLK);;
}

/**
 * \brief �������
 */
void demo_zlg118_hw_tim_cmp_toggle_entry (void    *p_hw_tim,
                                          uint8_t  type,
                                          uint32_t chan,
                                          uint32_t clk_rate,
                                          uint8_t  clk_div,
                                          uint8_t  inum)
{
    amhw_zlg118_tim_t *p_tim = (amhw_zlg118_tim_t *)p_hw_tim;

    /* ��ʼ����ʱ��Ϊ����Ƚ�ͨ����ת���� */
    tim_cmp_toggle_init(p_tim, (amhw_zlg118_tim_type_t)type, chan);
    tim_cmp_toggle_chan_config(p_tim, chan, clk_rate / 20 , clk_div);
    tim_cmp_toggle_enable(p_tim, (amhw_zlg118_tim_type_t)type, chan,inum);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg118_hw_tim_cmp_toggle] */

/* end of file */
