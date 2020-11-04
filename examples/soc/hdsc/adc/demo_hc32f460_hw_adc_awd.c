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
 * \brief ADC AWD ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ָ��ADCͨ����Ӧ���������ӵ�λ������� VRO��
 *
 * - ʵ������
 *   1. ���Դ��������λ�������ѹ,������AWD�趨��ֵ������жϣ���ӡADת�������AWD��ֵ��
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_adc_awd.c src_hc32f460_hw_awd_int
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-26  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_adc_int
 * \copydoc demo_hc32f460_hw_adc_int.c
 */

/** [src_hc32f460_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_int.h"
#include "hw/amhw_hc32f460_adc.h"
#include "am_hc32f460.h"
#include "hc32f460_irq_handle.h"

static volatile uint16_t  __g_adc_dat[10];              /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;
static volatile am_bool_t __g_adc_seqcmp   = AM_FALSE;
#define ADC_CHAN    0

#define THRESHOLD_VALUE_LOW  500
#define THRESHOLD_VALUE_HIGH 1000

/**
 * \brief ADC �жϷ�����
 */
static void __adc_isr (void *p_arg)
{

    amhw_hc32f460_adc_t *p_hw_adc = (amhw_hc32f460_adc_t *)p_arg;

    if (amhw_hc32f460_adc_int_flag_check(p_hw_adc,
                                         AMHW_HC32F460_ADC_INT_EOCAF)){
        amhw_hc32f460_adc_int_flag_clr(p_hw_adc,
                                       AMHW_HC32F460_ADC_INT_EOCAF);
    } else if(amhw_hc32f460_adc_int_flag_check(p_hw_adc,
                                               AMHW_HC32F460_ADC_INT_EOCBF)){
        amhw_hc32f460_adc_int_flag_clr(p_hw_adc,
                                       AMHW_HC32F460_ADC_INT_EOCBF);
    }

    __g_adc_dat[0] = amhw_hc32f460_adc_ch_data_get (p_hw_adc,
                                                    ADC_CHAN,
                                                    AMHW_HC32F460_ADC_RESOLUTION_12BIT,
                                                    AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    __g_adc_complete = AM_TRUE;

    /* ����ת��ֹͣ */
    amhw_hc32f460_adc_convert_stop(p_hw_adc);

}

static void __adc_seqcmp_isr(void *p_arg)
{

    amhw_hc32f460_adc_t *p_hw_adc = (amhw_hc32f460_adc_t *)p_arg;

    if (amhw_hc32f460_adc_awd_chan0_15_cmpstat_get(p_hw_adc) & AMHW_HC32F460_ADC_CHAN0_MASK) {
        amhw_hc32f460_adc_awd_chan0_15_cmpstat_clr(p_hw_adc, AMHW_HC32F460_ADC_CHAN0_MASK);
    }

    __g_adc_seqcmp = AM_TRUE;

}

/** \brief �������  */
void demo_hc32f460_hw_adc_awd_entry (void    *p_hw_adc,
                                     int      int_num_eoc,
                                     int      int_num_seqcmp,
                                     uint8_t  chan,
                                     uint32_t vref_mv)
{
    uint32_t                   adc_mv   = 0;    /* ������ѹ */
    uint32_t                   sum      = 0;
    amhw_hc32f460_adc_t       *p_adc    = (amhw_hc32f460_adc_t *)p_hw_adc;
	  uint16_t                   threshold_value_low  = THRESHOLD_VALUE_LOW;
	  uint16_t                   threshold_value_high = THRESHOLD_VALUE_HIGH;	

    am_kprintf("The ADC HW Int Demo\r\n");

    /* ����ת������ж� */
    amhw_hc32f460_int_sel0_31(int_num_eoc, EVT_ADC1_EOCA);
    am_int_connect(int_num_eoc, __adc_isr, p_adc);
    am_int_enable(int_num_eoc);

    /* ����ת������ж� */
    amhw_hc32f460_int_sel0_31(int_num_seqcmp, EVT_ADC1_SEQCMP);
    am_int_connect(int_num_seqcmp, __adc_seqcmp_isr, p_adc);
    am_int_enable(int_num_seqcmp);

    /* ֹͣADCת�� */
    amhw_hc32f460_adc_convert_stop(p_hw_adc);

    /* �������ݶ��뷽ʽΪ�Ҷ��� */
    amhw_hc32f460_adc_data_align_set(p_hw_adc,
                                     AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    /* ��ֹ���ݼĴ����Զ���� */
    amhw_hc32f460_adc_data_autoclr_disable(p_hw_adc);

    /* ����ADC����Ϊ12bit */
    amhw_hc32f460_adc_resolution_set(p_hw_adc,AMHW_HC32F460_ADC_RESOLUTION_12BIT);

    /* ת��ģʽΪ����A����ת�� */
    amhw_hc32f460_adc_mode_set(p_hw_adc, AMHW_HC32F460_ADC_SEQ_A_ONCE);

    /* ADC����Aͨ��ѡ�� */
    amhw_hc32f460_adc_seq_a_channel_sel0(p_hw_adc, chan);

    /* �趨�ͷ�ֵ */
    amhw_hc32f460_adc_awd_low_threshold_set(p_hw_adc,
                                            threshold_value_low,
                                            AMHW_HC32F460_ADC_RESOLUTION_12BIT,
                                            AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    /* �趨�߷�ֵ */
    amhw_hc32f460_adc_awd_high_threshold_set(p_hw_adc,
                                            threshold_value_high,
                                            AMHW_HC32F460_ADC_RESOLUTION_12BIT,
                                            AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    amhw_hc32f460_adc_awd_chan0_15_set (p_hw_adc, AMHW_HC32F460_ADC_CHAN0_MASK);
    amhw_hc32f460_adc_awd_seq_set(p_hw_adc, AMHW_HC32F460_ADC_AWD_SEQ_A_ONLY);
    amhw_hc32f460_adc_awd_cmp_mode_set(p_hw_adc, AMHW_HC32F460_ADC_AWD_CMPMODE0);
    amhw_hc32f460_adc_awd_int_enable(p_hw_adc);
    amhw_hc32f460_adc_awd_enable(p_hw_adc);


    /* ��ֹת������ж� */
    amhw_hc32f460_adc_int_disable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);
    amhw_hc32f460_adc_int_disable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCBF);

    /* ʹ��ת������ж� */
    amhw_hc32f460_adc_int_enable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);

    amhw_hc32f460_adc_sampling_period_set(p_hw_adc, chan, 50);

    while(1) {

        /* ����ת������ */
        amhw_hc32f460_adc_convert_start(p_hw_adc);

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        if (__g_adc_seqcmp == AM_TRUE) {
            AM_DBG_INFO("ADC_SEQCMP happen !\r\n");
            __g_adc_seqcmp = AM_FALSE;
        }

        sum = __g_adc_dat[0];

        /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
        adc_mv = sum * 3300 / ((1UL << 12) -1);

        AM_DBG_INFO("threshold value low  : %d\r\n", threshold_value_low);
        AM_DBG_INFO("threshold value high : %d\r\n", threshold_value_high);
        AM_DBG_INFO("Sample : %d, Vol: %d mv\r\n", sum, adc_mv);

        __g_adc_complete = AM_FALSE;

        am_mdelay(500);

    }
}
/** [src_hc32f460_hw_adc_int] */

/* end of file */
