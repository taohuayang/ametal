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
 * \brief ͨ�ö�ʱ���������Ļ���PWM���̣�ͨ�� HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ��Ϣ.
 *   2.PIOA_2(TIM0_CHA)��PIOA_1(TIM0_CHB)���ռ�ձ�25%��20Hz��PWM��������ʱ��Ϊ100us��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ʹ��ʾ�������߼������ǲ�������PWM������ʱ�䡣
 *    3. ����ʱ��ӦС��PWM������ʱ�䡣����ʱ����趨��Χ��6����2686us���������Ҫ�趨��������ʱ�䣬����
 *       Ҫ����demo_zlg118_hw_tim_pwm_dead.c�еķ�Ƶϵ��������ʱ������������
 *
 * \par Դ����
 * \snippet demo_zlg118116_hw_tim_pwm_dead.c src_zlg118116_hw_tim_pwm_dead
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12  zp, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zlg118116_hw_tim_pwm_dead
 * \copydoc demo_zlg118116_hw_tim_pwm_dead.c
 */

/** [src_zlg118116_hw_tim_pwm_dead] */
#include "ametal.h"
#include "am_clk.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zlg118.h"
#include "hw/amhw_zlg118_tim.h"

static am_bool_t __zlg118_hw_tim_init (amhw_zlg118_tim_t *p_hw_tim,
                                       uint8_t            type,
                                       uint8_t            chan_a,
                                       uint8_t            chan_b,
                                       uint32_t           duty_us,
                                       uint32_t           period_us,
                                       uint16_t           dead_us)
{
	float    deadtime = 0.0;
    uint32_t clkfreq  = 0;
    uint16_t fre_div  = 1;
    uint32_t period_c, duty_c;

    /* ���ö�ʱ��ģʽ2(��ݲ�ģʽ) */
    amhw_zlg118_tim_mode_set(p_hw_tim, AMHW_ZLG118_TIM_MODE_ZIGZAG);

    /* ���ϼ��� */
    amhw_zlg118_tim_mode23_counter_up(p_hw_tim);

    /* ʹ�ܻ������ */
    amhw_zlg118_tim_mode23_enable(p_hw_tim, AMHW_ZLG118_TIM_COMP);

    /* ����ͨ��AΪ�Ƚ�ģʽ */
    amhw_zlg118_tim_mode23_csa_compare(p_hw_tim, chan_a);

    /* ����ͨ�� BΪ�Ƚ�ģʽ */
    amhw_zlg118_tim_mode23_csb_compare(p_hw_tim, chan_b);

    /* ��ʱ��ʱ��Ϊ�ڲ�ʱ�� */
    amhw_zlg118_tim_mode_clk_src_set(p_hw_tim,AMHW_ZLG118_TIM_CLK_SRC_TCLK);

    /* ��ȡ����ʱ��Ƶ�� */
    clkfreq = am_clk_rate_get(CLK_TIM012);

    /* ��������õ����Ǽ���ֵCNT, ��ʽus * 10e-6= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_us) * (clkfreq) / (uint64_t)1000000;
    duty_c   = (uint64_t)(duty_us)   * (clkfreq) / (uint64_t)1000000;

    /* ���÷�Ƶֵ */
    amhw_zlg118_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZLG118_TIM_CLK_DIV64);

    fre_div = 64;

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / fre_div;
    duty_c   = duty_c   / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return AM_FALSE;
    }

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg118_tim_arr_count_set(p_hw_tim, period_c - 1);

    /* ��������� */
    amhw_zlg118_tim_cnt16_count_set(p_hw_tim, 0);

    /* ����ĳһͨ��A�ıȽ�ֵ */
    amhw_zlg118_tim_mode23_ccrxy_set(p_hw_tim, chan_a, duty_c - 1);

    /* ����ĳһͨ��B�ıȽ�ֵ */
    amhw_zlg118_tim_mode23_ccrxy_set(p_hw_tim, chan_b, duty_c - 1);

    /* ����ͨ��A��PWM���ģʽΪPWM2 */
    amhw_zlg118_tim_mode23_compare_set(
       p_hw_tim,
       (amhw_zlg118_tim_compare_type_t)(chan_a * 4),
       AMHW_ZLG118_TIM_COMPARE_PWM2);

    /* ����ͨ��B��PWM���ģʽΪPWM2 */
    amhw_zlg118_tim_mode23_compare_set(
       p_hw_tim,
       (amhw_zlg118_tim_compare_type_t)(chan_b * 4),
       AMHW_ZLG118_TIM_COMPARE_PWM2);

    /* ͨ��A������� */
    amhw_zlg118_tim_mode23_phase_same(
       p_hw_tim,
       (amhw_zlg118_tim_phase_type_t)(chan_a * 4 + 3));

    /* ͨ��A������� */
    amhw_zlg118_tim_mode23_phase_same(
       p_hw_tim,
       (amhw_zlg118_tim_phase_type_t)(chan_b * 4 + 3));

    /* �����־λ */
    amhw_zlg118_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZLG118_TIM_INT_FLAG_ALL);

    /* ��������ʹ��  */
    amhw_zlg118_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZLG118_TIM_DTR_DTEN);

    deadtime = (float)dead_us * (float)clkfreq / (float)(fre_div * 1000000) + 0.5;

    /* ����ʱ������  */
    amhw_zlg118_tim_mode23_dtr_set(p_hw_tim, (uint8_t)deadtime);

    /* PWM����ʹ�� */
    amhw_zlg118_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZLG118_TIM_DTR_MOE);

    return AM_TRUE;
}

/**
 * \brief �������
 */
void demo_zlg118_hw_tim_pwm_dead_entry (void    *p_hw_tim,
                                        uint8_t  type,
                                        uint8_t  chan_a,
                                        uint8_t  chan_b,
                                        uint32_t duty_us,
                                        uint32_t period_us,
                                        uint16_t dead_us)
{

    amhw_zlg118_tim_t *p_tim = (amhw_zlg118_tim_t *)p_hw_tim;

    /* ��ʱ������ */
    if((__zlg118_hw_tim_init(p_tim,
                             type,
                             chan_a,
                             chan_b,
                             duty_us ,
                             period_us,
                             dead_us)) ==
       AM_FALSE) {
        return;
    }

    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_zlg118_tim_enable(p_tim);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg118116_hw_tim_pwm_dead] */

/* end of file */
