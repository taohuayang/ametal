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
 * \brief �߼���ʱ��VCɲ�����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - �������裺
 *   1.VC0_P("+"�����PA1)����һ��ģ���ѹ�����鲻����3.3V��
 *   2.VC0_N("-"�����PA0)����һ��ģ���ѹ�����鲻����3.3V��
 *   3.����VC0_P��VC0_N֮��Ĵ�С��ϵ������������ʵ������
 *
 * - ʵ������
 *   1.VC0_P("+"�����PA1)�ĵ�ѹ����VC0_N("-"�����PA0)�ĵ�ѹ��VC0_OUT(PA6)����ߵ�ƽ��
 *     ����VC0�ж�(�ߵ�ƽһֱ�����ж�)����ʱ��4ɲ��������Ч��TIM4_CHA(PA8)��PWM���ֹͣ��
 *   2.VC0_P("+"�����PA1)�ĵ�ѹС��VC0_N("-"�����PA0)�ĵ�ѹ��VC0_OUT(PA6)����͵�ƽ��
 *     VC0���жϲ�����TIM4_CHA(PA8)��PWM���������
 *
 * \note ��ʵ���������ڸ߼���ʱ����TIM4��5��6����
 *       VCĬ��ʹ��VC0�˿���Ϊ��ʾʵ����
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_adtim_vc_brake.c src_zlg118_hw_adtim_vc_brake
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_adtim_vc_brake
 * \copydoc demo_zlg118_hw_adtim_vc_brake.c
 */

/** [src_zlg118_hw_adtim_vc_brake] */
#include "ametal.h"
#include "am_clk.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "am_zlg118.h"
#include "hw/amhw_zlg118_adtim.h"
#include "hw/amhw_zlg118_vc.h"

/*
 * \brief VC�жϷ�����
 */
static void __vc0_irq_handler (void *drv)
{

    amhw_zlg118_vc_t *p_hw_vc = (amhw_zlg118_vc_t *)drv;

    /* VC0 ͨ����Ч */
    if(amhw_zlg118_vc_int_status_check(p_hw_vc, AMHW_ZLG118_VC0_FLT_INT_FLAG)) {
        amhw_zlg118_vc_int_status_clr(p_hw_vc,AMHW_ZLG118_VC0_FLT_INT_FLAG_CLR);

        AM_DBG_INFO("vc int!\r\n");
    }
}

/*
 * \brief VC��ʼ��
 */
static am_bool_t __vc_init (amhw_zlg118_vc_t       *p_hw_vc,
                            amhw_zlg118_vc0_n_sel_t vc0_n,
                            amhw_zlg118_vc0_p_sel_t vc0_p)
{
    /* ʹ��BGR */
    amhw_zlg118_bgr_enable(AM_TRUE);

    /* ���òο���ѹΪVCC */
    amhw_zlg118_vc_ref2p5_sel(p_hw_vc, AMHW_ZLG118_VC_REF2P5_VCC);

    /* ���òο���ѹ����ѹ */
    amhw_zlg118_vc_div_enable(p_hw_vc);
    amhw_zlg118_vc_div_sel(p_hw_vc, AMHW_ZLG118_VC_DIV_1);

    /* ѡ�� ���͵�ѹ������*/
    amhw_zlg118_vc0_hys_sel(p_hw_vc, AMHW_ZLG118_VC0_HYS_10_MV);
    amhw_zlg118_vc0_bias_sel(p_hw_vc, AMHW_ZLG118_VC0_BIAS_10_UA);

    /*  ͨ��N�����롢ͨ��P���������� */
    amhw_zlg118_vc0_n_sel(p_hw_vc, vc0_n);
    amhw_zlg118_vc0_p_sel(p_hw_vc, vc0_p);

    /* �ߵ�ƽ�����ж� */
    amhw_zlg118_vc0_out_tri_int_sel(p_hw_vc,
                                    AMHW_ZLG118_VC_OUT_TRI_INT_HIGH_LEVEL);

    /* VC0���ʹ�������Advanced Timerɲ�� */
    amhw_zlg118_vc_outcfg_enable(p_hw_vc,
                                 AMHW_ZLG118_VC_OUT_CFG_BREAK_EN,
                                 AMHW_ZLG118_VC0);

    /* ������� */
    amhw_zlg118_vc_outcfg_enable(p_hw_vc,
                                 AMHW_ZLG118_VC_OUT_CFG_DISABLE,
                                 AMHW_ZLG118_VC0);

    /* �˲�ʹ�� */
    amhw_zlg118_vc_flt_disable (p_hw_vc, AMHW_ZLG118_VC0);

    /* ��������ж�ʹ�� */
    amhw_zlg118_vc_int_enable (p_hw_vc, AMHW_ZLG118_VC0);

    am_int_connect(INUM_VC0, __vc0_irq_handler, (void *)p_hw_vc);
    am_int_enable (INUM_VC0);

    return AM_TRUE;
}

static am_bool_t __zlg118_hw_adtim_init(void          *p_hw_adtim,
                                        uint8_t        chan,
                                        unsigned long  duty_ns,
                                        unsigned long  period_ns) {
    amhw_zlg118_adtim_basecnt_cfg_t        basecnt;
    amhw_zlg118_adtim_timx_chx_port_cfg_t  portcfg;

    uint32_t clkfreq;
    uint16_t fre_div = 1;
    uint32_t period_c, duty_c;

    basecnt.cntmode   = AMHW_ZLG118_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_ZLG118_ADTIM_CNT_DIR_UP;
    basecnt.cntclkdiv = AMHW_ZLG118_ADTIM_PCLK_DIV16;

    /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
    amhw_zlg118_adtim_init(p_hw_adtim, &basecnt);

    fre_div = 16;

    /* ��ȡ����ʱ��Ƶ�� */
    clkfreq = am_clk_rate_get(CLK_TIM456);

    /* ��������õ����Ǽ���ֵCNT, ��ʽns * 10e-9= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_ns) * (clkfreq) / (uint64_t)1000000000;
    duty_c   = (uint64_t)(duty_ns)   * (clkfreq) / (uint64_t)1000000000;

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / fre_div;
    duty_c   = duty_c   / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return AM_FALSE;
    }

    /* ���ü������� */
    amhw_zlg118_adtim_setperiod(p_hw_adtim, period_c);

    /* ��������� */
    amhw_zlg118_adtim_clearcount(p_hw_adtim);

    duty_c = period_c - duty_c;

    /* ���ñȽ�ֵ */
    amhw_zlg118_adtim_setcomparevalue(p_hw_adtim, 
		                                  (amhw_zlg118_adtim_compare_x_t)chan, 
		                                  duty_c);

    portcfg.portmode  = AMHW_ZLG118_ADTIM_PORT_MODE_CMP_OUTPUT;
    portcfg.outenable = AM_TRUE;
    portcfg.perc      = AMHW_ZLG118_ADTIM_PERIOD_INV;
    portcfg.cmpc      = AMHW_ZLG118_ADTIM_COMPARE_INV;
    portcfg.stastps   = AMHW_ZLG118_ADTIM_STATE_SEL_SS;
    portcfg.staout    = AMHW_ZLG118_ADTIM_PORT_OUT_LOW;
    portcfg.stpout    = AMHW_ZLG118_ADTIM_PORT_OUT_LOW;
    portcfg.dissel    = AMHW_ZLG118_ADTIM_DISSEL0;    // ѡ��ǿ�������Ч����0(VCɲ��)
    portcfg.disval    = AMHW_ZLG118_ADTIM_DISVAL_LOW; // ǿ�������Ч����0~3����������ʱ��CHx�˿�����͵�ƽ
    portcfg.fltenable = AM_FALSE;
    portcfg.fltclk    = AMHW_ZLG118_ADTIM_FLTCLK_PCLK_DIV1;
    amhw_zlg118_adtim_timxchxportcfg(p_hw_adtim, 
		                                 (amhw_zlg118_adtim_chx_t)chan, 
																		 &portcfg);

    return AM_TRUE;
}

/**
 * \brief �������
 */
void demo_zlg118_hw_adtim_vc_brake_entry (void         *p_hw_adtim,
                                          uint8_t       chan,
                                          unsigned long duty_ns,
                                          unsigned long period_ns,
                                          void         *p_hw_vc,
                                          uint8_t       vc0_n,
                                          uint8_t       vc0_p)
{
    amhw_zlg118_adtim_t *p_adtim = (amhw_zlg118_adtim_t *)p_hw_adtim;
    amhw_zlg118_vc_t    *p_vc    = (amhw_zlg118_vc_t *)p_hw_vc;
    /* ��ʱ����ʼ������ */
    if(__zlg118_hw_adtim_init(p_adtim, chan, duty_ns, period_ns) ==
       AM_FALSE) {
        return;
    }

    /* VC��ʼ������ */
    if(__vc_init(p_vc, 
			           (amhw_zlg118_vc0_n_sel_t)vc0_n, 
		             (amhw_zlg118_vc0_p_sel_t)vc0_p) == 
		   AM_FALSE) {
        return;
    }

    /* ʹ�ܶ�ʱ�� */
    amhw_zlg118_adtim_startcount(p_adtim);

    /* ʹ�ܵ�ѹ�Ƚ��� */
    amhw_zlg118_vc_volt_cmp_enable(p_vc, AMHW_ZLG118_VC0);

    while (1) {
        ;
    }
}
/** [src_zlg118_hw_adtim_vc_brake] */

/* end of file */
