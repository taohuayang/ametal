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
 * \brief ��ʱ���˿�ɲ���ж�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_5��͵�ƽ���ӣ�TIM1_CHA��PIOA_0�����ռ�ձ�Ϊ25%��2Hz��PWM����
 *   2. PIOB_5��ߵ�ƽ���ӣ�����ɲ���жϣ����ڴ�ӡ"brake int!"��TIM1_CHA��PIOA_0����PWM
 *      ���ֹͣ���ٴν�PIOB_5��͵�ƽ���ӣ��ָ����������
 *
 * \par Դ����
 * \snippet demo_zsn700116_hw_tim_port_brake.c src_zsn700116_hw_tim_port_brake
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12  zp, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zsn700116_hw_tim_port_brake
 * \copydoc demo_zsn700116_hw_tim_port_brake.c
 */

/** [src_zsn700116_hw_tim_port_brake] */
#include "ametal.h"
#include "am_clk.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_tim.h"

/**
  * \brief �жϷ�����
  */
static void __irq_handler (void *p_arg)
{
    amhw_zsn700_tim_t *p_hw_tim = (amhw_zsn700_tim_t *)p_arg;

    if(amhw_zsn700_tim_mode23_int_flag_check(
           p_hw_tim,
           AMHW_ZSN700_TIM_INT_FLAG_BRAKE) ==
           AM_TRUE) {

        amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim,
                                            AMHW_ZSN700_TIM_INT_FLAG_BRAKE);

        AM_DBG_INFO("brake int!\r\n");
    }

}

static am_bool_t __zsn700_hw_tim_init (amhw_zsn700_tim_t *p_hw_tim,
                                       uint8_t            type,
                                       uint8_t            chan,
                                       uint32_t           duty_ns,
                                       uint32_t           period_ns)
{
    uint32_t clkfreq;
    uint16_t fre_div = 1;
    uint32_t period_c, duty_c;

    /* ���ö�ʱ��ģʽ2(��ݲ�ģʽ) */
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

    /* ��ȡ����ʱ��Ƶ�� */
    clkfreq = am_clk_rate_get(CLK_TIM012);

    /* ��������õ����Ǽ���ֵCNT, ��ʽns * 10e-9= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_ns) * (clkfreq) / (uint64_t)1000000000;
    duty_c   = (uint64_t)(duty_ns)   * (clkfreq) / (uint64_t)1000000000;

    /* ���÷�Ƶֵ */
    amhw_zsn700_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZSN700_TIM_CLK_DIV64);

    fre_div = 64;

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / fre_div;
    duty_c   = duty_c   / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return AM_FALSE;
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

    /* PWM����ʹ�� */
    amhw_zsn700_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZSN700_TIM_DTR_MOE);
    amhw_zsn700_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZSN700_TIM_DTR_AOE);

    /* TIM1/2ʹ�ñ���ĵ�ɲ������ */
    amhw_zsn700_tim_mode23_bksel_mine(p_hw_tim);

    /* ɲ�����������������ƽѡ�� */
    if((chan % 2) == 0) {
        amhw_zsn700_tim_mode23_bksa_set(p_hw_tim,
                                        chan,
                                        AMHW_ZSN700_TIM_CMP_BRAKEOUT_LOW);
    } else {
        amhw_zsn700_tim_mode23_bksb_set(p_hw_tim,
                                        chan,
                                        AMHW_ZSN700_TIM_CMP_BRAKEOUT_LOW);
    }

    /* ɲ��BK������λͬ�ࣨ�ߵ�ƽɲ���� */
    amhw_zsn700_tim_mode23_phase_same(p_hw_tim, AMHW_ZSN700_TIM_PHASE_BKP);

    /* ɲ�������˲���pclk 3��������Ч�� */
    amhw_zsn700_tim_mode23_fliter_set(p_hw_tim,
                                      AMHW_ZSN700_TIM_FLITER_TYPE_FLTBK,
                                      AMHW_ZSN700_TIM_FILTER_PCLKDIV1_3);

    /* ɲ��ʹ�� */
    amhw_zsn700_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZSN700_TIM_DTR_BKE);

    /* ɲ���ж�ʹ�� */
    amhw_zsn700_tim_mode23_int_enable(p_hw_tim, AMHW_ZSN700_TIM_INT_BIE);

    return AM_TRUE;
}

/**
 * \brief �������
 */
void demo_zsn700_hw_tim_port_brake_entry (void    *p_hw_tim,
                                          uint8_t  type,
                                          uint8_t  chan,
                                          int      inum,
                                          uint32_t duty_ns,
                                          uint32_t period_ns)
{

    amhw_zsn700_tim_t *p_tim = (amhw_zsn700_tim_t *)p_hw_tim;

    /* ��ʱ������ */
    if((__zsn700_hw_tim_init(p_tim, type, chan, duty_ns , period_ns)) ==
       AM_FALSE) {
        return;
    }

    am_int_connect(inum, __irq_handler, (void *)p_hw_tim);
    am_int_enable(inum);

    /* ����жϱ�־ */
    amhw_zsn700_tim_mode23_int_flag_clr(p_hw_tim, AMHW_ZSN700_TIM_INT_FLAG_ALL);


    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_enable(p_tim);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zsn700116_hw_tim_port_brake] */

/* end of file */
