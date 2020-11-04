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
#include "hw/amhw_zlg237_adc.h"

static volatile uint16_t  __g_adc_dat[10];              /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;

/**
 * \brief ADC �жϷ�����
 */
static void __adc_isr (void *p_arg)
{
    static uint8_t i = 0;

    amhw_zlg237_adc_t *p_hw_adc = (amhw_zlg237_adc_t *)p_arg;

    __g_adc_dat[i]  = amhw_zlg237_adc_regular_data_get(p_hw_adc);
    __g_adc_dat[i] &= 0x0fff;

    i++;

    amhw_zlg237_adc_swstart_enable(p_hw_adc);

    if (i == 10) {
        i = 0;
        __g_adc_complete = AM_TRUE;

        amhw_zlg237_adc_swstart_disable(p_hw_adc);

    }
}

/** \brief �������  */
void demo_zlg237_hw_adc_int_entry (amhw_zlg237_adc_t *p_hw_adc,
                                   int                int_num,
                                   int                chan,
                                   uint32_t           vref_mv)
{
    uint8_t  i      = 0;
    uint32_t adc_mv = 0;    /* ������ѹ */
    uint32_t sum    = 0;

    am_kprintf("The ADC HW Int Demo\r\n");

    /* ADC���� */
    amhw_zlg237_adc_disable(p_hw_adc);

    /* �ر�ɨ��ģʽ��ע��ͨ�����ģʽ������ͨ�����ģʽ*/
    amhw_zlg237_adc_scan_mode_disable(p_hw_adc);
    amhw_zlg237_adc_injected_disc_disable(p_hw_adc);
    amhw_zlg237_adc_regular_disc_disable(p_hw_adc);

    /* ����ת�� */
    amhw_zlg237_adc_cont_set(p_hw_adc, AMHW_ZLG237_ADC_CONVERSION_SINGLE);
    amhw_zlg237_adc_extsel_set(p_hw_adc, AMHW_ZLG237_ADC12_REGULAR_SWSTART);

    /* ���óɶ���ģʽ*/
    amhw_zlg237_adc_dul_mode_set(p_hw_adc, AMHW_ZLG237_ADC_DUL_MODE_0);

    /* ����ĳһͨ���Ĳ���ʱ��*/
    amhw_zlg237_adc_smpr_set(p_hw_adc,
                             AMHW_ZLG237_ADC_CHAN_ST239_5,
                             AMHW_ZLG237_ADC_CHAN_0);

    /* ���ù���ͨ������  1�� */
    amhw_zlg237_adc_regular_channel_length_set(
        p_hw_adc, AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_1);

    /* ���ӹ�������ͨ����ADC����ͨ�� */
    amhw_zlg237_adc_regular_channel_order_set(
        p_hw_adc,
        AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_1st,
        AMHW_ZLG237_ADC_CHAN_0);

    /* ���ù���ͨ���ⲿ�����������ó����������ʽ */
    amhw_zlg237_adc_extirig_enable(p_hw_adc);
    amhw_zlg237_adc_extsel_set(p_hw_adc, AMHW_ZLG237_ADC12_REGULAR_SWSTART);

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
    amhw_zlg237_adc_int_enable(p_hw_adc, AMHW_ZLG237_ADC_INT_END);

    while(1) {

        /* ��ʼת�� */
        amhw_zlg237_adc_swstart_enable(p_hw_adc);

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        for (sum = 0,i = 0; i < 10 ; i++) {
        sum += __g_adc_dat[i];
        }

        sum = sum / 10;

        /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
        adc_mv = sum * 3300 / ((1UL << 12) -1);

        am_kprintf("Sample : %d, Vol: %d mv\r\n", sum, adc_mv);

        am_mdelay(500);
    }

}
/** [src_zlg_hw_adc_int] */

/* end of file */
