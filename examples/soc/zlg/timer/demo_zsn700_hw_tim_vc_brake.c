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
 * \brief ͨ�ö�ʱ��VCɲ�����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - �������裺
 *   1.VC0_P("+"�����PA1)����һ��ģ���ѹ�����鲻����3.3V��
 *   2.VC0_N("-"�����PA0)����һ��ģ���ѹ�����鲻����3.3V��
 *   3.����VC0_P��VC0_N֮��Ĵ�С��ϵ������������ʵ������
 *
 * - ʵ������
 *   1.VC0_P("+"�����PA1)�ĵ�ѹ����VC0_N("-"�����PA0)�ĵ�ѹ��VC0_OUT(PA6)����ߵ�ƽ��
 *     ����VC0�ж�(�ߵ�ƽһֱ�����ж�)����ʱ��4ɲ��������Ч��TIM1_CHB(PIOB_6)��PWM���ֹͣ��
 *   2.VC0_P("+"�����PA1)�ĵ�ѹС��VC0_N("-"�����PA0)�ĵ�ѹ��VC0_OUT(PA6)����͵�ƽ��
 *     VC0���жϲ�����TIM1_CHB(PIOB_6)��PWM���������
 *
 * \note ��ʵ����������ͨ�ö�ʱ����TIM0��1��2����
 *       VCĬ��ʹ��VC0�˿���Ϊ��ʾʵ����
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_tim_vc_brake.c src_zsn700_hw_tim_vc_brake
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_tim_vc_brake
 * \copydoc demo_zsn700_hw_tim_vc_brake.c
 */

/** [src_zsn700_hw_tim_vc_brake] */
#include "ametal.h"
#include "am_clk.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_tim.h"
#include "hw/amhw_zsn700_vc.h"

/*
 * \brief VC�жϷ�����
 */
static void __vc0_irq_handler (void *p_arg)
{

    amhw_zsn700_vc_t *p_hw_vc = (amhw_zsn700_vc_t *)p_arg;

    //��VC�ߵ�ƽ�ж���Чʱ������Timer3PWMɲ��������MOE���Զ����㣬��AOE��Ҫʹ�ܣ�
    //��MOE�Զ����㣬PWM����ͻ�ضϣ�����Ҫ�ָ�PWM���������Ҫ�ٴ�ʹ��MOE
    /* VC0 ͨ����Ч */
    if(amhw_zsn700_vc_int_status_check(p_hw_vc, AMHW_ZSN700_VC0_FLT_INT_FLAG)) {
        amhw_zsn700_vc_int_status_clr(p_hw_vc,AMHW_ZSN700_VC0_FLT_INT_FLAG_CLR);

        AM_DBG_INFO("vc int!\r\n");
    }
}

/*
 * \brief VC��ʼ��
 */
static am_bool_t __vc_init (amhw_zsn700_vc_t       *p_hw_vc,
                            amhw_zsn700_vc0_n_sel_t vc0_n,
                            amhw_zsn700_vc0_p_sel_t vc0_p)
{
    /* ʹ��BGR */
    amhw_zsn700_bgr_enable(AM_TRUE);

    /* ���òο���ѹΪVCC */
    amhw_zsn700_vc_ref2p5_sel(p_hw_vc, AMHW_ZSN700_VC_REF2P5_VCC);

    /* ���òο���ѹ����ѹ */
    amhw_zsn700_vc_div_enable(p_hw_vc);
    amhw_zsn700_vc_div_sel(p_hw_vc, AMHW_ZSN700_VC_DIV_1);

    /* ѡ�� ���͵�ѹ������*/
    amhw_zsn700_vc0_hys_sel(p_hw_vc, AMHW_ZSN700_VC0_HYS_10_MV);
    amhw_zsn700_vc0_bias_sel(p_hw_vc, AMHW_ZSN700_VC0_BIAS_10_UA);

    /*  ͨ��N�����롢ͨ��P���������� */
    amhw_zsn700_vc0_n_sel(p_hw_vc, vc0_n);
    amhw_zsn700_vc0_p_sel(p_hw_vc, vc0_p);

    /* �ߵ�ƽ�����ж� */
    amhw_zsn700_vc0_out_tri_int_sel(p_hw_vc,
                                    AMHW_ZSN700_VC_OUT_TRI_INT_HIGH_LEVEL);

    /* VC0���ʹ�������Advanced Timerɲ�� */
    amhw_zsn700_vc_outcfg_enable(p_hw_vc,
                                 AMHW_ZSN700_VC_OUT_CFG_FIT_DATA_TIM0_1_2_3_EN,
                                 AMHW_ZSN700_VC0);

    /* ������� */
    amhw_zsn700_vc_outcfg_enable(p_hw_vc,
                                 AMHW_ZSN700_VC_OUT_CFG_DISABLE,
                                 AMHW_ZSN700_VC0);

    /* �˲�ʹ�� */
    amhw_zsn700_vc_flt_disable (p_hw_vc, AMHW_ZSN700_VC0);

    /* ��������ж�ʹ�� */
    amhw_zsn700_vc_int_enable (p_hw_vc, AMHW_ZSN700_VC0);

    am_int_connect(INUM_VC0, __vc0_irq_handler, (void *)p_hw_vc);
    am_int_enable (INUM_VC0);

    return AM_TRUE;
}

static am_bool_t __zsn700_hw_tim_init (amhw_zsn700_tim_t *p_hw_tim,
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

    /* VCɲ��ʹ�� */
    amhw_zsn700_tim_mode23_dtr_enable(p_hw_tim, AMHW_ZSN700_TIM_DTR_VCE);

    return AM_TRUE;
}

/**
 * \brief �������
 */
void demo_zsn700_hw_tim_vc_brake_entry (void         *p_hw_tim,
                                        uint8_t       chan,
                                        unsigned long duty_ns,
                                        unsigned long period_ns,
                                        void         *p_hw_vc,
                                        uint8_t       vc0_n,
                                        uint8_t       vc0_p)
{
    amhw_zsn700_tim_t *p_tim = (amhw_zsn700_tim_t *)p_hw_tim;
    amhw_zsn700_vc_t  *p_vc  = (amhw_zsn700_vc_t *)p_hw_vc;
    /* ��ʱ����ʼ������ */
    if(__zsn700_hw_tim_init(p_tim, chan, duty_ns, period_ns) ==
       AM_FALSE) {
        return;
    }

    /* VC��ʼ������ */
    if(__vc_init(p_vc, 
			           (amhw_zsn700_vc0_n_sel_t)vc0_n, 
		             (amhw_zsn700_vc0_p_sel_t)vc0_p) == AM_FALSE) {
        return;
    }

    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_enable(p_tim);

    /* ʹ�ܵ�ѹ�Ƚ��� */
    amhw_zsn700_vc_volt_cmp_enable(p_vc, AMHW_ZSN700_VC0);

    while (1) {
        ;
    }
}
/** [src_zsn700_hw_tim_vc_brake] */

/* end of file */
