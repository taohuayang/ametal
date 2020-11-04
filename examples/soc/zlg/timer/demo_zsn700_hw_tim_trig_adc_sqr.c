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
 * \brief ��ʱ����������ADC˳��ɨ��ת�����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1.��ʱ��ͨ��һ��Ƶ��Ϊ10Hz��ռ�ձ�25%��PWM��
 *   2.ADC��10Hz��Ƶ�ʽ���˳��ɨ��ת������ʱ����ʱ100ms����ÿת��һ��LED��תһ�Σ���˸Ƶ��10/2=5Hz��
 *   2.�������ݴ�ӡ��Ƶ����ADCת����ʱ������ͬ�����ڴ�ӡ���Ϊ500ms��
 *
 * \note
 *   1.adcͨ��������sqr_num�����趨��ΧΪ1~16
 *   2.��ʱ������ʱ�䣨period_us�����趨��ΧΪ0~262140us��0~262ms֮�䣩��������趨����ʱ��ֵ��
 *     ����Ҫ����demo_zsn700_hw_tim_trig_adc_sqr.c�ж�ʱ����Ƶϵ�����趨��
 *   3.��ͬ����£�ADC��ת���ٶ����ޣ���Ҫ���Ƕ�ʱ��������ʱ���Ƿ����ADCת��ʱ�䣨���ͨ������Ҫ�ۼ�ת��ʱ�䣩
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_tim_trig_adc_sqr.c src_zsn700_hw_tim_trig_adc_sqr
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-11  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_tim_trig_adc_sqr
 * \copydoc demo_zsn700_hw_tim_trig_adc_sqr.c
 */

/** [src_zsn700_hw_tim_trig_adc_sqr] */
#include "ametal.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_clk.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_tim.h"
#include "hw/amhw_zsn700_adc.h"

static volatile uint16_t  __g_adc_dat[20];             /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;

static volatile uint16_t  __vref_mv     = 0;
static volatile uint16_t  __adc_sqr_num = 0;

static volatile uint8_t   chan_num = 0;
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

static am_bool_t __zsn700_hw_tim_init (amhw_zsn700_tim_t *p_hw_tim,
                                       uint8_t            type,
                                       uint8_t            chan,
                                       uint32_t           duty_us,
                                       uint32_t           period_us)
{
    uint32_t clkfreq;
    uint16_t fre_div = 1;
    uint32_t period_c, duty_c;

    if((amhw_zsn700_tim_type_t)type == AMHW_ZSN700_TIM_TYPE_TIM3) {
        chan_num = 6;
    } else {
        chan_num = 2;
    }

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

    /* ��������õ����Ǽ���ֵCNT, ��ʽus * 10e-6= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_us) * (clkfreq) / (uint64_t)1000000;
    duty_c   = (uint64_t)(duty_us)   * (clkfreq) / (uint64_t)1000000;

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

    /* ʹ��ADC����ȫ�ֿ��ƣ��ܿ��أ� */
    amhw_zsn700_tim_mode23_adc_trigger_enable(
        p_hw_tim,
        AMHW_ZSN700_TIM_ADC_TRIGGER_ADTE);

    /* ʹ���¼����´���ADC��ʵ���¼�ѡ�� */
    amhw_zsn700_tim_mode23_adc_trigger_enable(
        p_hw_tim,
        AMHW_ZSN700_TIM_ADC_TRIGGER_UEVE);

    return AM_TRUE;
}

static void __zsn700_hw_adc_init (amhw_zsn700_tim_t *p_hw_tim,
                                  amhw_zsn700_adc_t *p_hw_adc,
                                  int                int_num,
                                  int               *p_adc_chan,
                                  uint8_t            sqr_num)
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
    if((uint32_t)p_hw_tim == ZSN700_TIM0_BASE) {
        amhw_zsn700_adc_sgl_sqr_trigger_src_set(
            p_hw_adc,
            AMHW_ZSN700_ADC_INT_TRIGGER_TIM0);
    } else if((uint32_t)p_hw_tim == ZSN700_TIM1_BASE) {
        amhw_zsn700_adc_sgl_sqr_trigger_src_set(
            p_hw_adc,
            AMHW_ZSN700_ADC_INT_TRIGGER_TIM1);
    } else if((uint32_t)p_hw_tim == ZSN700_TIM2_BASE) {
        amhw_zsn700_adc_sgl_sqr_trigger_src_set(
            p_hw_adc,
            AMHW_ZSN700_ADC_INT_TRIGGER_TIM2);
    } else if((uint32_t)p_hw_tim == ZSN700_TIM3_BASE) {
        amhw_zsn700_adc_sgl_sqr_trigger_src_set(
            p_hw_adc,
            AMHW_ZSN700_ADC_INT_TRIGGER_TIM3);
    }

    /* �ж�ʹ��*/
    amhw_zsn700_adc_int_enable(p_hw_adc);

    /* ADCʹ��*/
    amhw_zsn700_adc_enable(p_hw_adc);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_tim_trig_adc_sqr_entry (void    *p_hw_tim,
                                            uint8_t  type,
                                            uint8_t  chan,
                                            uint32_t duty_us,
                                            uint32_t period_us,
                                            void    *p_hw_adc,
                                            int      adc_int_num,
                                            int     *p_adc_chan,
                                            uint8_t  sqr_num)
{

    amhw_zsn700_tim_t *p_tim = (amhw_zsn700_tim_t *)p_hw_tim;
    amhw_zsn700_adc_t *p_adc = (amhw_zsn700_adc_t *)p_hw_adc;

    uint16_t adc_mv = 0;
    uint8_t  i      = 0;

    /* ��ʱ������ */
    if((__zsn700_hw_tim_init(p_tim, type, chan, duty_us , period_us)) ==
       AM_FALSE) {
        return;
    }

    /* ADC���� */
    __zsn700_hw_adc_init(p_tim, p_adc, adc_int_num, p_adc_chan, sqr_num);

    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_zsn700_tim_enable(p_tim);

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
/** [src_zsn700_hw_tim_trig_adc_sqr] */

/* end of file */
