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
 * \brief �߼���ʱ���˿ڡ����ɲ�������ν��иߵ�ƽɲ�������ɲ�����ܲ��ԣ����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ��Ϣ��ÿ5s���PWM�������Ϊɲ���ĸı���ı�
 *   2.demo���Կ�ʼ������ʱ5�룬��ʱ�������ߵ�ƽɲ��������PWM�����Ϊɲ�����ܱ�Ϊ�͵�ƽ��
 *                ����ʱ5�룬��ʱ�����������־��ɲ�����ý��ܣ�PWM���������
 *                ����ʱ5�룬��ʱ���������ɲ��ʹ�ܣ�PWM�����Ϊɲ�����ܱ�Ϊ�͵�ƽ��
 *                ����ʱ5�룬��ʱ���������ɲ�����ܣ�PWM�������������
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_adtim_port_sw_brake.c src_zlg118_hw_adtim_port_sw_brake
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_adtim_port_sw_brake
 * \copydoc demo_zlg118_hw_adtim_port_sw_brake.c
 */

/** [src_zlg118_hw_adtim_port_sw_brake] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_zlg118.h"
#include "hw/amhw_zlg118_adtim.h"

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
    portcfg.dissel    = AMHW_ZLG118_ADTIM_DISSEL3;       // ѡ��ǿ�������Ч����3
    portcfg.disval    = AMHW_ZLG118_ADTIM_DISVAL_LOW;    // ǿ�������Ч����0~3����������ʱ��CHx�˿�����͵�ƽ
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
void demo_zlg118_hw_adtim_port_sw_brake_entry (void          *p_hw_adtim,
                                               uint8_t        chan,
                                               unsigned long  duty_ns,
                                               unsigned long  period_ns,
                                               int            output_pin,
                                               uint8_t        src)
{
    char                              i;
    uint8_t                           t;
    amhw_zlg118_adtim_disable_3_cfg_t disable_cfg;
    amhw_zlg118_adtim_t              *p_adtim = (amhw_zlg118_adtim_t *)
                                                p_hw_adtim;

    /* ��ʱ����ʼ������ */
    if(__zlg118_hw_adtim_init(p_adtim, chan, duty_ns, period_ns) ==
       AM_FALSE) {
        return;
    }

    /* ��Ч����3�����ýṹ�壨�����portenable��Ա���ɣ���ʼ��*/
    for(t = 0; t < 15; t++) {
        disable_cfg.stcbrkptcfg[t].portenable  = AM_FALSE;
    }

    /* ��������͵�ƽ */
    am_gpio_set(output_pin, 0);

    src = (amhw_zlg118_adtim_trigsel_t)src;

    disable_cfg.stcbrkptcfg[src].portenable  = AM_TRUE;
    disable_cfg.stcbrkptcfg[src].polaritysel = AMHW_ZLG118_ADTIM_PtBrkHigh;
    disable_cfg.fltenable = AM_TRUE;
    disable_cfg.fltclk    = AMHW_ZLG118_ADTIM_FLTCLK_PCLK_DIV1;

    /* ��Ч����3����(�˿�ɲ��) */
    amhw_zlg118_adtim_disable3cfg(&disable_cfg);

    /* ������ʱ�� */
    amhw_zlg118_adtim_startcount(p_adtim);

    /* 5s��������Ž�����ߵ�ƽ��������ʱ��ɲ�� */
    for(i = 5; i > 0; i--) {
        am_mdelay(1000);
        AM_DBG_INFO("%d\r\n",i);
    }

    /* ��������ߵ�ƽ������ɲ����*/
    am_gpio_set(output_pin, 1);

    AM_DBG_INFO("high port_sw_brake was happened!\r\n");

    /* 5s��������Ž�����͵�ƽ��ͬʱ���ɲ�����ã�PWM����ָ����� */
    for(i = 5; i > 0; i--) {
        am_mdelay(1000);
        AM_DBG_INFO("%d\r\n",i);
    }

    /* ��������͵�ƽ��������������� */
    am_gpio_set(output_pin, 0);

    /* ��������͵�ƽ��C���ִ���꣬����ı���ܴ���Ӳ���ӳ٣����Լ�����ʱȷ�������Ѿ���ɵ͵�ƽ*/
    am_mdelay(1);

    /* ȷ��ɲ������������Ч���������ɲ����־��ɲ������֮ǰ�����ɲ����־�� */
    amhw_zlg118_adtim_clearportbrakeflag();

    AM_DBG_INFO("PWM function is normal!\r\n");

    /* ����������Ч����3����(�˿�ɲ��)--���ɲ������ */
    disable_cfg.stcbrkptcfg[src].portenable  = AM_FALSE;
    disable_cfg.fltenable = AM_FALSE;
    amhw_zlg118_adtim_disable3cfg(&disable_cfg);

    /* 5s��������Ž�����ߵ�ƽ��������ʱ��ɲ�� */
    for(i = 5; i > 0; i--) {
        am_mdelay(1000);
        AM_DBG_INFO("%d\r\n",i);
    }

    /* ���ɲ������ */
    amhw_zlg118_adtim_swbrake(AM_TRUE);

    AM_DBG_INFO("software port_sw_brake was happened!\r\n");

    /* 5s��������Ž�����͵�ƽ��ͬʱ���ɲ�����ã�PWM����ָ����� */
    for(i = 5; i > 0; i--) {
        am_mdelay(1000);
        AM_DBG_INFO("%d\r\n",i);
    }

    /* ���ɲ���ر� */
    amhw_zlg118_adtim_swbrake(AM_FALSE);

    AM_DBG_INFO("PWM function is normal!\r\n");

    while (1) {
        ;
    }
}
/** [src_zlg118_hw_adtim_port_sw_brake] */

/* end of file */
