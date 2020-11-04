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
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ָ��ADCͨ����Ӧ����������ģ�����롣
 *
 * - ʵ������
 *   1. ���Դ��������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_multichan_adc.c src_zsn700_hw_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-09  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_multichan_adc
 * \copydoc demo_zsn700_hw_multichan_adc.c
 */

/** [src_zsn700_hw_multichan_adc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_zsn700_clk.h"
#include "hw/amhw_zsn700_adc.h"
#include "zsn700_periph_map.h"

static volatile uint16_t  __g_adc_dat[20];             /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;

static volatile uint16_t  __adc_sqr_num = 0;
static volatile am_bool_t __adc_jqr_num = 0;
/**
 * \brief ADC �жϷ�����
 */
static void __adc_isr (void *p_arg)
{
    static uint8_t i = 0;

    amhw_zsn700_adc_t *p_hw_adc = (amhw_zsn700_adc_t *)p_arg;

    if(amhw_zsn700_adc_flag_check(p_hw_adc,
                                  AMHW_ZSN700_ADC_FLAG_CONVERT_SQR) ==
                                  AM_TRUE) {

        amhw_zsn700_adc_flag_clr(p_hw_adc, AMHW_ZSN700_ADC_FLAG_CONVERT_SQR);

        for(i = 0; i < __adc_sqr_num; i++) {

            __g_adc_dat[i] = amhw_zsn700_adc_sqr_chan_data_get(p_hw_adc, i);
        }
    }

    if(amhw_zsn700_adc_flag_check(p_hw_adc,
                                  AMHW_ZSN700_ADC_FLAG_CONVERT_JQR) ==
                                  AM_TRUE) {

        amhw_zsn700_adc_flag_clr(p_hw_adc, AMHW_ZSN700_ADC_FLAG_CONVERT_JQR);

        for(i = __adc_sqr_num; i < __adc_sqr_num + __adc_jqr_num; i++) {

           __g_adc_dat[i] = amhw_zsn700_adc_jqr_chan_data_get(p_hw_adc,
                                                              i - __adc_sqr_num);
        }
    }

    if(i == __adc_sqr_num + __adc_jqr_num) {

        i = 0;

        __g_adc_complete = AM_TRUE;

        amhw_zsn700_adc_sqr_convert_stop(p_hw_adc);
        amhw_zsn700_adc_jqr_convert_stop(p_hw_adc);
    }
}

/** \brief �������  */
void demo_zsn700_hw_multichan_adc_entry (void    *p_hw_adc,
                                         int      int_num,
                                         uint32_t vref_mv,
                                         int     *p_adc_chan,
                                         uint8_t  sqr_num,
                                         uint8_t  jqr_num)
{
    uint8_t            i      = 0;
    uint32_t           adc_mv = 0;    /* ������ѹ */
    amhw_zsn700_adc_t *p_adc  = (amhw_zsn700_adc_t *)p_hw_adc;

    __adc_sqr_num = sqr_num;
    __adc_jqr_num = jqr_num;

    am_kprintf("The ADC HW Multichan Demo\r\n");

    /* ����ת������ж� */
    am_int_connect(int_num, __adc_isr, p_adc);
    am_int_enable(int_num);

    /* �ڲ��ο���ѹʹ�� */
    amhw_zsn700_adc_inrefvol_enable(p_adc);

    /* ���òο���ѹԴ */
    amhw_zsn700_adc_refvol_sel(p_adc, AMHW_ZSN700_ADC_REFVOL_INSIDE_2500MV);

    /* BGRģ��ʹ�� */
    amhw_zsn700_bgr_enable(AM_TRUE);

    /* ADCʹ��*/
    amhw_zsn700_adc_enable(p_adc);

    /* ��ʱ 20us���ȴ� ADC�� BGRģ��������� */
    am_udelay(20);

    /* ADC���� */
    amhw_zsn700_adc_disable(p_adc);

    /* ʹ��ɨ��ת��ģʽ */
    amhw_zsn700_adc_mode_sel(p_adc, AMHW_ZSN700_ADC_MODE_SCAN);

    amhw_zsn700_adc_align_way_sel(p_adc, AMHW_ZSN700_ADC_DATA_ALIGN_RIGHT);

    /* ����ת������ */
    amhw_zsn700_adc_sample_period_sel(p_adc,
                                      AMHW_ZSN700_ADC_SAMPLE_PERIOD_12);

    /* ����ADCʱ�ӷ�Ƶ */
    amhw_zsn700_adc_pclk_div_sel(p_adc, AMHW_ZSN700_ADC_PCLK_DIV8);

    /* ����ADC˳��ɨ��ת��ͨ�������� */
    for(i = 0; i < __adc_sqr_num; i++) {
        amhw_zsn700_adc_sqr_chan_sel(p_adc,
                                     i,
                                     (amhw_zsn700_adc_chan_sel_t)p_adc_chan[i]);
    }

    amhw_zsn700_adc_sqr_num_set(p_adc, __adc_sqr_num - 1);

    /* ����ADC����ɨ��ת��ͨ�������� */
    for(i = __adc_sqr_num; i < __adc_sqr_num + __adc_jqr_num; i++) {

        amhw_zsn700_adc_jqr_chan_sel(p_adc,
                                     i - __adc_sqr_num,
                                     (amhw_zsn700_adc_chan_sel_t)p_adc_chan[i]);
    }

    amhw_zsn700_adc_jqr_num_set(p_adc, __adc_jqr_num - 1);

    /* �ж�ʹ��*/
    amhw_zsn700_adc_int_enable(p_adc);

    /* ���־λ */
    amhw_zsn700_adc_flag_clr(p_adc, AMHW_ZSN700_ADC_FLAG_ALL);

    /* ADCʹ��*/
    amhw_zsn700_adc_enable(p_adc);

    while(1) {

        /* ��ʼת�� */
        amhw_zsn700_adc_sqr_convert_start(p_adc);
        amhw_zsn700_adc_jqr_convert_start(p_adc);

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        for(i = 0; i < __adc_sqr_num; i++) {

            /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
            adc_mv = __g_adc_dat[i] * vref_mv / ((1UL << 12) -1);

            am_kprintf("sqr chan : %d, Sample : %d, Vol: %d mv\r\n", i, __g_adc_dat[i], adc_mv);
        }

        am_kprintf("\r\n");

        for(i = __adc_sqr_num; i < __adc_sqr_num + __adc_jqr_num; i++) {

            /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
            adc_mv = __g_adc_dat[i] * vref_mv / ((1UL << 12) -1);

            am_kprintf("jqr chan : %d, Sample : %d, Vol: %d mv\r\n", i, __g_adc_dat[i], adc_mv);
        }

        am_kprintf("\r\n");

        am_mdelay(500);
    }

}
/** [src_zsn700_hw_multichan_adc] */

/* end of file */
