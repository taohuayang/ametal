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
 * \brief ADC ����A�¼����� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ָ��ADCͨ����Ӧ����������ģ�����롣
 *
 * - ʵ������
 *   1. ��������PB7 �󴥷�ADC1 ����Aת����
 *   2. ���Դ��������ѹ����ֵ��������Ϊ32��ת����ƽ��ֵ����
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_adc_int.c src_hc32f460_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-17  cds, first implementation
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
#define ADC_CHAN    0


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

/** \brief �������  */
void demo_hc32f460_hw_adc_seq_a_event_trigger_entry (void    *p_hw_adc,
                                                     int      int_num,
                                                     uint8_t  chan,
                                                     uint32_t vref_mv)
{
    uint32_t                   adc_mv   = 0;    /* ������ѹ */
    amhw_hc32f460_adc_t         *p_adc    = (amhw_hc32f460_adc_t *)p_hw_adc;

    am_kprintf("The ADC HW Int Demo\r\n");

    /* ӳ���ж�Դ�������ж����� */
    amhw_hc32f460_int_sel0_31(int_num, EVT_ADC1_EOCA);
    /* ����ת������ж� */
    am_int_connect(int_num, __adc_isr, p_adc);
    am_int_enable(int_num);

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

    /* ����ADCƽ��ת������ */
    amhw_hc32f460_adc_average_count_set(p_hw_adc, AMHW_HC32F460_ADC_AVERAGE_COUNT_32);

    /* ADCƽ��ͨ��ѡ�� */
    amhw_hc32f460_adc_average_channel_sel0(p_hw_adc, chan);

    /* ����ADC����A��������Ϊ�ⲿ���Ŵ��� */
    amhw_hc32f460_adc_seq_a_trigger_source_sel(p_hw_adc, AMHW_HC32F460_ADC_SEQ_TRIGGER_ADTRx);
    /* ʹ��ADC����AƬ�ڻ��ⲿ���Ŵ������ */
    amhw_hc32f460_adc_seq_a_trigger_enable(p_hw_adc);

    /* ��ֹת������ж� */
    amhw_hc32f460_adc_int_disable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);
    amhw_hc32f460_adc_int_disable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCBF);

    /* ʹ��ת������ж� */
    amhw_hc32f460_adc_int_enable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);

    amhw_hc32f460_adc_sampling_period_set(p_hw_adc, chan, 50);

    while(1) {

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
        adc_mv = __g_adc_dat[0] * 3300 / ((1UL << 12) -1);

        AM_DBG_INFO("Sample : %d, Vol: %d mv\r\n", __g_adc_dat[0], adc_mv);

        __g_adc_complete = AM_FALSE;

        am_mdelay(500);
    }
}
/** [src_hc32f460_hw_adc_int] */

/* end of file */
