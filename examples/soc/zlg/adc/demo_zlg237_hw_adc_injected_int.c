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
 * \snippet demo_zlg_hw_adc_int.c src_zlg_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-18  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_adc_int
 * \copydoc demo_zlg_hw_adc_int.c
 */

/** [src_zlg_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_zlg237_clk.h"
#include "hw/amhw_zlg237_adc.h"

static volatile uint16_t  __g_adc_dat[4];               /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;

/**
 * \brief ADC �жϷ�����
 */
static void __adc_isr (void *p_arg)
{
    static uint8_t i = 0;

    amhw_zlg237_adc_t *p_hw_adc = (amhw_zlg237_adc_t *)p_arg;

    amhw_zlg237_adc_status_flag_clr(p_hw_adc, AMHW_ZLG237_ADC_INJECTED_CHAN_END_FLAG);

    for (i = 0 ; i < 4; i++) {

        /* ADֵ�Ļ�ȡ */
        /* �ر�ע�� �������ݼĴ����Ķ�����ֵ = ADʵ��ת��ֵ - ����ƫ�ƼĴ�����ƫ��ֵ*/
        __g_adc_dat[i]  = amhw_zlg237_adc_injected_data_get(p_hw_adc, i);
        __g_adc_dat[i] &= 0x0fff;
    }

    __g_adc_complete = AM_TRUE;
}

/** \brief �������  */
void demo_zlg237_hw_adc_injected_int_entry (amhw_zlg237_adc_t *p_hw_adc,
                                            int                int_num,
                                            uint32_t           vref_mv,
                                            int               *p_adc_chan,
                                            int                adc_chan_num)
{
    uint8_t  i      = 0;
    uint32_t adc_mv = 0;    /* ������ѹ */

    am_kprintf("The ADC HW Int Demo\r\n");

    /* ADC���� */
    amhw_zlg237_adc_disable(p_hw_adc);

    /* ����ADC����Ƶ�ʣ�72MHz��8��Ƶ */
    amhw_zlg237_rcc_adc_div_set (2);

    /* ����ADCע��ͨ������ */
    if(adc_chan_num < 4) {
        amhw_zlg237_adc_injected_channel_length_set(
            p_hw_adc,
            (amhw_zlg237_adc_injected_channel_length_t)(adc_chan_num-1));
    }
    else
    {
        amhw_zlg237_adc_injected_channel_length_set(
            p_hw_adc, AMHW_ZLG237_ADC_INJECTED_CHAN_LENGTH_4);

    }

    /**
     * \note : ��ͬ�ڹ���ת�����У���� JL[1:0]�ĳ���С�� 4����ת��������˳���Ǵ�(4-JL)��ʼ��
     *         ���磺ADC_JSQR[21:0] =   10    00011   00011   00111  00010
     *                               3��ת��            3       3       7      2
     *         ��ζ��ɨ��ת����������ͨ��˳��ת����7�� 3��3�������� 2��7��3��
     *
     *         ���������ͨ��������ADC����ͨ���������Ƿ����
     */
    for(i=0;i<adc_chan_num;i++) {

    /* ����ע��ͨ�����к�ADC����ͨ�� */
    amhw_zlg237_adc_injected_channel_order_set(
        p_hw_adc,
        AMHW_ZLG237_ADC_INJECTED_CHAN_ORDER_4th - i,
        p_adc_chan[adc_chan_num - 1 - i]);

    /* ע��ͨ������ƫ�ƼĴ�����ֵ����λֵΪ0�� */
    /* ���ݼĴ�����ֵ = ʵ��ת��ֵ - ƫ��ֵ*/
    amhw_zlg237_adc_jofr_set(
        p_hw_adc,
        AMHW_ZLG237_ADC_INJECTED_DATA_CHAN_4 - i,
        0);

    /* ���ò���ͨ���Ĳ������� */
    amhw_zlg237_adc_smpr_set(
        p_hw_adc,
        AMHW_ZLG237_ADC_CHAN_ST55_5,
        p_adc_chan[adc_chan_num - 1 - i]);

    }

    /* ����ɨ��ģʽ */
    amhw_zlg237_adc_scan_mode_enable(p_hw_adc);

    /* �ر�ע��ͨ�����ģʽ������ͨ�����ģʽ*/
    amhw_zlg237_adc_injected_disc_disable(p_hw_adc);
    amhw_zlg237_adc_regular_disc_disable(p_hw_adc);

    /* ����ת�� */
    amhw_zlg237_adc_cont_set(p_hw_adc, AMHW_ZLG237_ADC_CONVERSION_SINGLE);

    /* ����ע��ͨ���ⲿ�����������ó����������ʽ */
    amhw_zlg237_adc_jextirig_enable(p_hw_adc);
    amhw_zlg237_adc_jextsel_set(p_hw_adc, AMHW_ZLG237_ADC12_INJECTED_JSWSTART);

    /* ���óɶ���ģʽ,ADC1��ADC2��������*/
    amhw_zlg237_adc_dul_mode_set(p_hw_adc, AMHW_ZLG237_ADC_DUL_MODE_0);

    /* ���뷽ʽ--�Ҷ���*/
    amhw_zlg237_adc_data_alignment_set(p_hw_adc,AMHW_ZLG237_ADC_DATA_RIGHT);

    /* �ر�ADC16ͨ���ڲ��¶ȴ���������ADC1��Ч��*/
    amhw_zlg237_adc_tsvrefe_disable(p_hw_adc);

    /* ADCʹ��*/
    amhw_zlg237_adc_enable(p_hw_adc);

    /* ���ø�λУ׼*/
    amhw_zlg237_adc_rstcal_enable(p_hw_adc);

    /* �ȴ���λУ׼����*/
    while(amhw_zlg237_adc_rstcal_check(p_hw_adc) == AM_FALSE);

    /* ����ADУ׼*/
    amhw_zlg237_adc_cal_enable(p_hw_adc);

    /* �ȴ�ADУ׼����*/
    while(amhw_zlg237_adc_cal_check(p_hw_adc) == AM_FALSE);

    /* ����ת������ж� */
    am_int_connect(int_num, __adc_isr, p_hw_adc);
    am_int_enable(int_num);

    /* ת�������ж�ʹ��*/
    amhw_zlg237_adc_int_enable(p_hw_adc, AMHW_ZLG237_ADC_INT_INJECTED_END);

    while(1) {

        /* ��ʼת�� */
        amhw_zlg237_adc_jswstart_enable(p_hw_adc);

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        for (i = 0; i < 4 ; i++) {

            /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
            adc_mv = __g_adc_dat[i] * vref_mv / ((1UL << 12) -1);

            am_kprintf("chan : %d, Sample : %d, Vol: %d mv\r\n", p_adc_chan[i], __g_adc_dat[i], adc_mv);
        }

        am_kprintf("\r\n");

        am_mdelay(500);
    }

}
/** [src_zlg_hw_adc_int] */

/* end of file */
