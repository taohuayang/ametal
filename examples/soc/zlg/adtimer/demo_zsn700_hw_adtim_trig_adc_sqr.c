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
 * \brief �߼���ʱ����������ADC˳��ɨ��ת�����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1.ADC��10Hz��Ƶ�ʽ���˳��ɨ��ת������ʱ����ʱ100ms����ÿת��һ��LED��תһ�Σ���˸Ƶ��10/2=5Hz��
 *   2.�������ݴ�ӡ��Ƶ����ADCת����ʱ������ͬ�����ڴ�ӡ���Ϊ500ms��
 *
 * \note
 *   1.adcͨ��������sqr_num�����趨��ΧΪ1~16
 *   2.��ʱ������ʱ�䣨period_us�����趨��ΧΪ0~262140us��0~262ms֮�䣩��������趨����ʱ��ֵ��
 *     ����Ҫ����demo_zsn700_hw_adtim_trig_adc_sqr.c�ж�ʱ����Ƶϵ�����趨��
 *   3.��ͬ����£�ADC��ת���ٶ����ޣ���Ҫ���Ƕ�ʱ��������ʱ���Ƿ����ADCת��ʱ�䣨���ͨ������Ҫ�ۼ�ת��ʱ�䣩
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_adtim_trig_adc_sqr.c src_zsn700_hw_adtim_trig_adc_sqr
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-11  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_adtim_trig_adc_sqr
 * \copydoc demo_zsn700_hw_adtim_trig_adc_sqr.c
 */

/** [src_zsn700_hw_adtim_trig_adc_sqr] */
#include "ametal.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_clk.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_adtim.h"
#include "hw/amhw_zsn700_adc.h"

static volatile uint16_t  __g_adc_dat[20];             /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;

static volatile uint16_t  __vref_mv     = 0;
static volatile uint16_t  __adc_sqr_num = 0;
/**
 * \brief ADC �жϷ�����
 */
static void __adc_isr (void *p_arg)
{
    uint8_t i = 0;

    amhw_zsn700_adc_t *p_hw_adc = (amhw_zsn700_adc_t *)p_arg;

    if(amhw_zsn700_adc_flag_check(p_hw_adc,
                                  AMHW_ZSN700_ADC_FLAG_CONVERT_SQR) ==
                                  AM_TRUE) {

        amhw_zsn700_adc_flag_clr(p_hw_adc, AMHW_ZSN700_ADC_FLAG_CONVERT_SQR);

        for(i = 0; i < __adc_sqr_num; i++) {

            __g_adc_dat[i] = amhw_zsn700_adc_sqr_chan_data_get(p_hw_adc, i);
        }

        __g_adc_complete = AM_TRUE;

        am_led_toggle(LED0);
    }
}

static am_bool_t __zsn700_hw_adtim_init (amhw_zsn700_adtim_t *p_hw_adtim,
                                         uint32_t             period_us)
{
    amhw_zsn700_adtim_basecnt_cfg_t   basecnt;
    amhw_zsn700_adtim_irq_trig_cfg_t irq_trig;

    uint32_t clkfreq;
    uint16_t fre_div = 1;
    uint32_t period_c;

    /* ��ȡ����ʱ��Ƶ�� */
    clkfreq = am_clk_rate_get(CLK_TIM456);

    /* ��������õ����Ǽ���ֵCNT, ��ʽus * 10e-6= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_us) * (clkfreq) / (uint64_t)1000000;

    /* ��ݲ������ϼ�����64��Ƶ */
    basecnt.cntmode   = AMHW_ZSN700_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_ZSN700_ADTIM_CNT_DIR_UP;
    basecnt.cntclkdiv = AMHW_ZSN700_ADTIM_PCLK_DIV64;

    fre_div = 64;

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / fre_div;

    /* �������Ϸ� */
    if ((period_c == 0) || (period_c > 65535UL)) {
        return AM_FALSE;
    }

    /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
    amhw_zsn700_adtim_init(p_hw_adtim, &basecnt);

    /* ���� ADC��������������ƥ��ʹ�ܴ���ADC��*/
    irq_trig.specilmatch_B_trigdma = AM_FALSE;
    irq_trig.specilmatch_A_trigdma = AM_FALSE;
    irq_trig.underflow_trigdma     = AM_FALSE;
    irq_trig.overflow_trigdma      = AM_FALSE;
    irq_trig.cntmatch_D_trigdma    = AM_FALSE;
    irq_trig.cntmatch_C_trigdma    = AM_FALSE;
    irq_trig.cntmatch_B_trigdma    = AM_FALSE;
    irq_trig.cntmatch_A_trigdma    = AM_FALSE;
    irq_trig.specilmatch_B_trig    = AM_FALSE;
    irq_trig.specilmatch_A_trig    = AM_FALSE;
    irq_trig.underflow_trig        = AM_FALSE;
    irq_trig.overflow_trig         = AM_TRUE;
    irq_trig.cntmatch_D_trig       = AM_FALSE;
    irq_trig.cntmatch_C_trig       = AM_FALSE;
    irq_trig.cntmatch_B_trig       = AM_FALSE;
    irq_trig.cntmatch_A_trig       = AM_FALSE;
    amhw_zsn700_adtim_irqtrigcfg(p_hw_adtim, &irq_trig);

    /* ���ü������� */
    amhw_zsn700_adtim_setperiod(p_hw_adtim, period_c);

    /* ��������� */
    amhw_zsn700_adtim_clearcount(p_hw_adtim);

    return AM_TRUE;
}

static void __zsn700_hw_adc_init (amhw_zsn700_adtim_t *p_hw_adtim,
                                  amhw_zsn700_adc_t   *p_hw_adc,
                                  int                  int_num,
                                  int                 *p_adc_chan,
                                  uint8_t              sqr_num)
{
    uint8_t i = 0;

    __adc_sqr_num = sqr_num;

    /* ����ת������ж� */
    am_int_connect(int_num, __adc_isr, p_hw_adc);
    am_int_enable(int_num);

    /* �ڲ��ο���ѹʹ�� */
    amhw_zsn700_adc_inrefvol_enable(p_hw_adc);

    /* ���òο���ѹԴ */
    amhw_zsn700_adc_refvol_sel(p_hw_adc, AMHW_ZSN700_ADC_REFVOL_AVCC);

    __vref_mv = 3300;

    /* BGRģ��ʹ�� */
    amhw_zsn700_bgr_enable(AM_TRUE);

    /* ADCʹ��*/
    amhw_zsn700_adc_enable(p_hw_adc);

    /* ��ʱ 20us���ȴ� ADC�� BGRģ��������� */
    am_udelay(20);

    /* ADC���� */
    amhw_zsn700_adc_disable(p_hw_adc);

    /* ʹ��ɨ��ת��ģʽ */
    amhw_zsn700_adc_mode_sel(p_hw_adc, AMHW_ZSN700_ADC_MODE_SCAN);

    /* ����ת������ */
    amhw_zsn700_adc_sample_period_sel(p_hw_adc,
                                      AMHW_ZSN700_ADC_SAMPLE_PERIOD_4);

    /* ����ADCʱ�ӷ�Ƶ */
    amhw_zsn700_adc_pclk_div_sel(p_hw_adc, AMHW_ZSN700_ADC_PCLK_DIV2);

    /* ���뷽ʽ���� */
    amhw_zsn700_adc_align_way_sel(p_hw_adc,
                                  AMHW_ZSN700_ADC_DATA_ALIGN_RIGHT);

    /* ����ADC˳��ɨ��ת��ͨ�������� */
    for(i = 0; i < __adc_sqr_num; i++) {
        amhw_zsn700_adc_sqr_chan_sel(p_hw_adc,
                                     i,
                                     (amhw_zsn700_adc_chan_sel_t)p_adc_chan[i]);
    }

    amhw_zsn700_adc_sqr_num_set(p_hw_adc, __adc_sqr_num - 1);

    /* ���־λ */
    amhw_zsn700_adc_flag_clr(p_hw_adc, AMHW_ZSN700_ADC_FLAG_ALL);

    /* �ⲿ�жϴ���Դ���� */
    if((uint32_t)p_hw_adtim == ZSN700_TIM4_BASE) {
        amhw_zsn700_adc_sgl_sqr_trigger_src_set(
            p_hw_adc,
            AMHW_ZSN700_ADC_INT_TRIGGER_TIM4);
    } else if((uint32_t)p_hw_adtim == ZSN700_TIM5_BASE) {
        amhw_zsn700_adc_sgl_sqr_trigger_src_set(
            p_hw_adc,
            AMHW_ZSN700_ADC_INT_TRIGGER_TIM5);
    } else if((uint32_t)p_hw_adtim == ZSN700_TIM6_BASE) {
        amhw_zsn700_adc_sgl_sqr_trigger_src_set(
            p_hw_adc,
            AMHW_ZSN700_ADC_INT_TRIGGER_TIM6);
    }

    /* �ж�ʹ��*/
    amhw_zsn700_adc_int_enable(p_hw_adc);

    /* ADCʹ��*/
    amhw_zsn700_adc_enable(p_hw_adc);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_adtim_trig_adc_sqr_entry (void    *p_hw_adtim,
                                              uint32_t period_us,
                                              void    *p_hw_adc,
                                              int      adc_int_num,
                                              int     *p_adc_chan,
                                              uint8_t  sqr_num)
{

    amhw_zsn700_adtim_t *p_adtim = (amhw_zsn700_adtim_t *)p_hw_adtim;
    amhw_zsn700_adc_t   *p_adc   = (amhw_zsn700_adc_t *)p_hw_adc;

    uint16_t adc_mv = 0;
    uint8_t  i      = 0;

    /* ��ʱ������ */
    if((__zsn700_hw_adtim_init(p_adtim, period_us)) == AM_FALSE) {
        return;
    }

    /* ADC���� */
    __zsn700_hw_adc_init(p_adtim, p_adc, adc_int_num, p_adc_chan, sqr_num);

    /* ������ʱ�� */
    amhw_zsn700_adtim_startcount(p_adtim);

    while (1) {

        /* �ȴ�ת����� */
          while (__g_adc_complete == AM_FALSE);

          for(i = 0; i < __adc_sqr_num; i++) {

              /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
              adc_mv = __g_adc_dat[i] * __vref_mv / ((1UL << 12) -1);

              am_kprintf("sqr chan : %2d, Sample : %4d, Vol: %4d mv\r\n",
                         i,
                         __g_adc_dat[i],
                         adc_mv);
          }

          am_kprintf("\r\n");

          am_mdelay(500);
    }
}
/** [src_zsn700_hw_adtim_trig_adc_sqr] */

/* end of file */
