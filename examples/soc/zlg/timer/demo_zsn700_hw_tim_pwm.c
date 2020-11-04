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
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_zsn700116_hw_tim_pwm.c src_zsn700116_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zsn700116_hw_tim_pwm
 * \copydoc demo_zsn700116_hw_tim_pwm.c
 */

/** [src_zsn700116_hw_tim_pwm] */
#include "ametal.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zsn700_tim.h"
#include "am_led.h"

#define LED0            0

static uint8_t chan_num = 0;

/**
  * \brief PWM �жϷ�����
  */
static void __zsn700_tim_hw_pwm_irq_handler (void *p_arg)
{
    amhw_zsn700_tim_t *p_hw_tim = (amhw_zsn700_tim_t *)p_arg;
    uint8_t         i        = 1;

    for(i = 0; i < chan_num;i = i + 2) {
        if ((amhw_zsn700_tim_mode23_int_flag_check(p_hw_tim,
                                                   (i / 2) + 2)) ==
                                                   AM_TRUE) {

            if(amhw_zsn700_tim_mode23_ciea_int_get(p_hw_tim,i) == AM_TRUE)
            {
                am_led_toggle(LED0);

                /* ���ͨ��i��־ */
                amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim, (i / 2) + 2);
            }
        }
    }

    /* �жϱ�־  ��CH0B��CH1B��CH2B */
    for(i = 1; i < chan_num;i = i + 2) {
        if ((amhw_zsn700_tim_mode23_int_flag_check(p_hw_tim,
                                                   (i / 2) + 5)) ==
                                                   AM_TRUE) {

            if(amhw_zsn700_tim_mode23_cieb_int_get(p_hw_tim,i) == AM_TRUE)
            {
                am_led_toggle(LED0);

                /* ���ͨ��i��־ */
                amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim,  (i / 2) + 5);
            }
        }
    }
}

/**
 * \brief ���ö�ʱ��Ϊ PWM ���(PWM ģʽ 2)
 */
void tim_pwm_chan_config (amhw_zsn700_tim_t *p_hw_tim,
                          uint32_t           chan,
                          uint32_t           duty_ns,
                          uint32_t           period_ns,
                          uint32_t           clk_rate,
                          uint8_t            clk_div)
{
    uint32_t period_c, duty_c;
    uint16_t fre_div  = 1;

    /* �������Ϸ� */
    if ((period_ns == 0) || (duty_ns > 4294967295UL) ||
        (period_ns > 4294967295UL) || (duty_ns > period_ns)) {
        return ;
    }

    /* ��������õ����Ǽ���ֵCNT, ��ʽns * 10e-9= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_ns) * (clk_rate) / (uint64_t)1000000000;
    duty_c   = (uint64_t)(duty_ns)   * (clk_rate) / (uint64_t)1000000000;

    /* ��Ƶϵ������ */
    amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, (amhw_zsn700_tim_clkdiv_t)clk_div);

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
    period_c = period_c / fre_div;
    duty_c   = duty_c   / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return ;
    }

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zsn700_tim_arr_count_set(p_hw_tim, period_c - 1);

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    duty_c = period_c - duty_c;

    /* ����ĳһͨ���ıȽ�ֵ */
    amhw_zsn700_tim_mode23_ccrxy_set(p_hw_tim, chan, duty_c - 1);

    /* ����PWM���ģʽΪPWM2 */
    amhw_zsn700_tim_mode23_compare_set(
        p_hw_tim,
        (amhw_zsn700_tim_compare_type_t)(chan * 4),
        AMHW_ZSN700_TIM_COMPARE_PWM2);

    /* ������� */
    amhw_zsn700_tim_mode23_phase_same(
        p_hw_tim,
        (amhw_zsn700_tim_phase_type_t)(chan * 4 + 3));
}

void tim_pwm_enable (amhw_zsn700_tim_t      *p_hw_tim,
                     amhw_zsn700_tim_type_t  type,
                     uint32_t                chan,
                     int32_t                 int_num)
{
    /* �����жϻص����� */
    am_int_connect(int_num, __zsn700_tim_hw_pwm_irq_handler, (void *)p_hw_tim);
    am_int_enable(int_num);

    /* ����Ƚϴ����ж�ʹ�� */
    if((chan % 2) == 0) {
        amhw_zsn700_tim_mode23_ciea_int_enable(p_hw_tim, chan);
    } else {
        amhw_zsn700_tim_mode23_cieb_int_enable(p_hw_tim, chan);
    }

    /* ��������� */
    amhw_zsn700_tim_cnt16_count_set(p_hw_tim, 0);

    /* ����жϱ�־ */
    amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZSN700_TIM_INT_FLAG_ALL);

    /* PWM����ʹ�� */
    amhw_zsn700_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZSN700_TIM_DTR_MOE);

    /* ʹ�ܶ�ʱ�� */
    amhw_zsn700_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ��TIM PWM�����ʼ������
 *
 * \param[in] p_hw_tim : ָ��ʱ���Ĵ������ָ��
 * \param[in] clk_id   : ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \return ��
 */
void tim_pwm_init (amhw_zsn700_tim_t *p_hw_tim, uint8_t type, uint8_t chan)
{
    if((amhw_zsn700_tim_type_t)type == AMHW_ZSN700_TIM_TYPE_TIM3) {
        chan_num = 6;
    } else {
        chan_num = 2;
    }

    /* ���ö�ʱ��ģʽ2 */
    amhw_zsn700_tim_mode_set(p_hw_tim, AMHW_ZSN700_TIM_MODE_ZIGZAG);

    /* ���ϼ��� */
    amhw_zsn700_tim_mode23_counter_up(p_hw_tim);

    /* ����ͨ��Ϊ�Ƚ�ģʽ */
    if((chan % 2) == 0) {
        amhw_zsn700_tim_mode23_csa_compare(p_hw_tim, chan);
    } else {
        amhw_zsn700_tim_mode23_csb_compare(p_hw_tim, chan);
    }

    /* ��ʱ��ʱ��Ϊ�ڲ�ʱ�� */
    amhw_zsn700_tim_mode_clk_src_set(p_hw_tim,AMHW_ZSN700_TIM_CLK_SRC_TCLK);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_tim_pwm_entry (void    *p_hw_tim,
                                   uint8_t  type,
                                   uint32_t chan,
                                   uint32_t clk_rate,
                                   uint8_t  clk_div,
                                   int32_t  inum)
{

    amhw_zsn700_tim_t *p_tim = (amhw_zsn700_tim_t *)p_hw_tim;

    /* ��ʼ����ʱ��TIMΪPWM���� */
    tim_pwm_init(p_tim, type, chan);

    /* ���ö�ʱ��TIM PWM���ͨ�� */
    tim_pwm_chan_config(p_tim,
                        chan,
                        50000000,
                        100000000,
                        clk_rate,
                        clk_div);

    tim_pwm_enable(p_tim, (amhw_zsn700_tim_type_t)type, chan, inum);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zsn700116_hw_tim_pwm] */

/* end of file */
