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
 * \brief ��ADC Эͬ���� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ָ��ADCͨ����Ӧ������(PA0,PA5)����ģ�����롣
 *   2. ��PB7���Žӵأ������½��أ�����ADC1��ʼת��
 * - ʵ������
 *   1. PB7���ͺ�ͬʱ����ADC1��ADC2����ת�������ڴ�ӡ����ADC��Ӧͨ����ת�����
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_adc_int.c src_hc32f460_hw_adc_int
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

static volatile uint16_t  __g_adc1_data;              /**< \brief ����ֵ���� */
static volatile uint16_t  __g_adc2_data;              /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc1_complete = AM_FALSE;
static volatile am_bool_t __g_adc2_complete = AM_FALSE;
static uint8_t __g_adc1_chan;
static uint8_t __g_adc2_chan;

/**
 * \brief ADC1 �жϷ�����
 */
static void __adc1_isr (void *p_arg)
{

    amhw_hc32f460_adc_t *p_hw_adc = (amhw_hc32f460_adc_t *)p_arg;

    if (amhw_hc32f460_adc_int_flag_check(p_hw_adc,
                                         AMHW_HC32F460_ADC_INT_EOCAF)){
        amhw_hc32f460_adc_int_flag_clr(p_hw_adc,
                                       AMHW_HC32F460_ADC_INT_EOCAF);
    }

    __g_adc1_data = amhw_hc32f460_adc_ch_data_get (p_hw_adc,
                                                   __g_adc1_chan,
                                                   AMHW_HC32F460_ADC_RESOLUTION_12BIT,
                                                   AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    __g_adc1_complete = AM_TRUE;
}

/**
 * \brief ADC2 �жϷ�����
 */
static void __adc2_isr (void *p_arg)
{

    amhw_hc32f460_adc_t *p_hw_adc = (amhw_hc32f460_adc_t *)p_arg;

    if (amhw_hc32f460_adc_int_flag_check(p_hw_adc,
                                         AMHW_HC32F460_ADC_INT_EOCAF)){
        amhw_hc32f460_adc_int_flag_clr(p_hw_adc,
                                       AMHW_HC32F460_ADC_INT_EOCAF);
    }

    __g_adc2_data = amhw_hc32f460_adc_ch_data_get (p_hw_adc,
                                                   __g_adc2_chan,
                                                   AMHW_HC32F460_ADC_RESOLUTION_12BIT,
                                                   AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    __g_adc2_complete = AM_TRUE;
}

/** \brief �������  */
void demo_hc32f460_hw_adc_sync_entry (void    *p_hw_adc1,
                                      void    *p_hw_adc2,
                                      int      int_num_adc1,
                                      int      int_num_adc2,
                                      uint8_t  chan_adc1,
                                      uint8_t  chan_adc2,
                                      uint32_t vref_mv)
{
    uint32_t                   adc1_mv   = 0;    /* ������ѹ */
    uint32_t                   sum_adc1  = 0;
    uint32_t                   adc2_mv   = 0;    /* ������ѹ */
    uint32_t                   sum_adc2  = 0;
    amhw_hc32f460_adc_t       *p_adc1   = (amhw_hc32f460_adc_t *)p_hw_adc1;
    amhw_hc32f460_adc_t       *p_adc2   = (amhw_hc32f460_adc_t *)p_hw_adc2;

    __g_adc1_chan = chan_adc1;
    __g_adc2_chan = chan_adc2;

    am_kprintf("The ADC HW SYNC Demo\r\n");

    /* ӳ���ж�Դ�������ж����� */
    amhw_hc32f460_int_sel0_31(int_num_adc1, EVT_ADC1_EOCA);
    /* ����ת������ж� */
    am_int_connect(int_num_adc1, __adc1_isr, p_adc1);
    am_int_enable(int_num_adc1);

    /* ӳ���ж�Դ�������ж����� */
    amhw_hc32f460_int_sel0_31(int_num_adc2, EVT_ADC2_EOCA);
    /* ����ת������ж� */
    am_int_connect(int_num_adc2, __adc2_isr, p_adc2);
    am_int_enable(int_num_adc2);

    /* ֹͣADCת�� */
    amhw_hc32f460_adc_convert_stop(p_hw_adc1);
    amhw_hc32f460_adc_convert_stop(p_hw_adc2);

    /* �������ݶ��뷽ʽΪ�Ҷ��� */
    amhw_hc32f460_adc_data_align_set(p_hw_adc1,
                                     AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);
    amhw_hc32f460_adc_data_align_set(p_hw_adc2,
                                     AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    /* ƽ��ת��ͨ������ */
    amhw_hc32f460_adc_average_channel_sel0(p_hw_adc1, chan_adc1);
    amhw_hc32f460_adc_average_channel_sel0(p_hw_adc2, chan_adc2);

    /* ƽ��ת���������� */
    amhw_hc32f460_adc_average_count_set(p_hw_adc1, AMHW_HC32F460_ADC_AVERAGE_COUNT_32);
    amhw_hc32f460_adc_average_count_set(p_hw_adc2, AMHW_HC32F460_ADC_AVERAGE_COUNT_32);

    /* ��ֹ���ݼĴ����Զ���� */
    amhw_hc32f460_adc_data_autoclr_disable(p_hw_adc1);
    amhw_hc32f460_adc_data_autoclr_disable(p_hw_adc2);

    /* ����ADC����Ϊ12bit */
    amhw_hc32f460_adc_resolution_set(p_hw_adc1,AMHW_HC32F460_ADC_RESOLUTION_12BIT);
    amhw_hc32f460_adc_resolution_set(p_hw_adc2,AMHW_HC32F460_ADC_RESOLUTION_12BIT);

    /* ת��ģʽΪ����A����ת�� */
    amhw_hc32f460_adc_mode_set(p_hw_adc1, AMHW_HC32F460_ADC_SEQ_A_ONCE);
    amhw_hc32f460_adc_mode_set(p_hw_adc2, AMHW_HC32F460_ADC_SEQ_A_ONCE);

    /* ADC����Aͨ��ѡ�� */
    amhw_hc32f460_adc_seq_a_channel_sel0(p_hw_adc1, chan_adc1);
    amhw_hc32f460_adc_seq_a_channel_sel0(p_hw_adc2, chan_adc2);

    amhw_hc32f460_adc_sync_mode_set(p_hw_adc1,
                                    AMHW_HC32F460_ADC_SYNC_MODE_SINGLE |
                                    AMHW_HC32F460_ADC_SYNC_MODE_PARALLEL  |
                                    AMHW_HC32F460_ADC_SYNC_MODE_ADC0_1_2);

    amhw_hc32f460_adc_sync_mode_enable(p_hw_adc1);

    amhw_hc32f460_adc_seq_a_trigger_source_sel(p_hw_adc1, AMHW_HC32F460_ADC_SEQ_TRIGGER_ADTRx);

    amhw_hc32f460_adc_seq_a_trigger_enable(p_hw_adc1);

    /* ��ֹת������ж� */
    amhw_hc32f460_adc_int_disable(p_hw_adc1, AMHW_HC32F460_ADC_INT_EOCAF);
    amhw_hc32f460_adc_int_disable(p_hw_adc1, AMHW_HC32F460_ADC_INT_EOCBF);
    amhw_hc32f460_adc_int_disable(p_hw_adc2, AMHW_HC32F460_ADC_INT_EOCAF);
    amhw_hc32f460_adc_int_disable(p_hw_adc2, AMHW_HC32F460_ADC_INT_EOCBF);

    /* ʹ��ת������ж� */
    amhw_hc32f460_adc_int_enable(p_hw_adc1, AMHW_HC32F460_ADC_INT_EOCAF);
    amhw_hc32f460_adc_int_enable(p_hw_adc2, AMHW_HC32F460_ADC_INT_EOCAF);

    amhw_hc32f460_adc_sampling_period_set(p_hw_adc1, chan_adc1, 50);
    amhw_hc32f460_adc_sampling_period_set(p_hw_adc2, chan_adc2, 50);

    while(1) {

        /* �ȴ�ת����� */
        while ((__g_adc1_complete == AM_FALSE) ||
               (__g_adc2_complete == AM_FALSE));

        __g_adc1_complete = AM_FALSE;
        __g_adc2_complete = AM_FALSE;

        sum_adc1 = __g_adc1_data;

        /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
        adc1_mv = sum_adc1 * 3300 / ((1UL << 12) -1);

        AM_DBG_INFO("ADC1 Sample : %d, Vol: %d mv\r\n", sum_adc1, adc1_mv);

        sum_adc2 = __g_adc2_data;

        /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
        adc2_mv = sum_adc2 * 3300 / ((1UL << 12) -1);

        AM_DBG_INFO("ADC2 Sample : %d, Vol: %d mv\r\n", sum_adc2, adc2_mv);

        am_mdelay(500);
    }
}
/** [src_hc32f460_hw_adc_int] */

/* end of file */
