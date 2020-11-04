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
 * \brief ADC ��ͨ��ת�� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ָ��ADCͨ����Ӧ����������ģ�����롣
 *
 * - ʵ������
 *   1. ���Դ��������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_multichan_adc.c src_hc32_hw_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-22  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_multichan_adc
 * \copydoc demo_hc32f460_hw_multichan_adc.c
 */

/** [src_hc32f460_hw_multichan_adc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_hc32f460_clk.h"
#include "hw/amhw_hc32f460_adc.h"
#include "hc32f460_irq_handle.h"
#include "hc32f460_inum.h"

static volatile uint16_t  __g_adc_dat[20];             /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;

static volatile uint16_t  __adc_chan_num = 0;
static amhw_adc_chmux_t   __adc_chmux[17];

/**
 * \brief ADC �жϷ�����
 */
static void __adc_isr (void *p_arg)
{
    static uint8_t i = 0;

    amhw_hc32f460_adc_t *p_hw_adc = (amhw_hc32f460_adc_t *)p_arg;

    if (amhw_hc32f460_adc_int_flag_check(p_hw_adc,
                                        AMHW_HC32F460_ADC_INT_EOCAF) ==
                                        AM_TRUE) {

        amhw_hc32f460_adc_int_flag_clr(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);

        for(i = 0; i < __adc_chan_num; i++) {

            __g_adc_dat[i] = amhw_hc32f460_adc_ch_data_get(p_hw_adc, __adc_chmux[i].chan, AMHW_HC32F460_ADC_RESOLUTION_12BIT, AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);
        }
     }


    if(i == __adc_chan_num) {

        i = 0;

        __g_adc_complete = AM_TRUE;

        amhw_hc32f460_adc_convert_stop(p_hw_adc);
    }
}

/** \brief �������  */
void demo_hc32f460_hw_multichan_adc_entry (void    *p_hw_adc,
                                           int      int_num,
                                           uint32_t vref_mv,
                                           amhw_adc_chmux_t     *p_adc_chan,
                                           uint8_t  chan_num)
{
    uint8_t            i      = 0;
    uint8_t            j      = 0;
    uint32_t           adc_mv = 0;    /* ������ѹ */
    amhw_hc32f460_adc_t *p_adc  = (amhw_hc32f460_adc_t *)p_hw_adc;

    __adc_chan_num = chan_num;
    am_kprintf("The ADC HW Multichan Demo\r\n");

    /* ӳ���ж�Դ�������ж����� */
    amhw_hc32f460_int_sel0_31(int_num, EVT_ADC1_EOCA);
    /* ����ת������ж� */
    am_int_connect(int_num, __adc_isr, p_adc);
    am_int_enable(int_num);


    /* ֹͣADCת�� */
    amhw_hc32f460_adc_convert_stop(p_adc);

    /* ת��ģʽΪ����A����ת�� */
    amhw_hc32f460_adc_mode_set(p_adc, AMHW_HC32F460_ADC_SEQ_A_ONCE);

    /* �������ݶ��뷽ʽΪ�Ҷ��� */
    amhw_hc32f460_adc_data_align_set(p_adc,
                                     AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    /* ����ת������ */
    for(j = 0; j < chan_num; j++ ){
    amhw_hc32f460_adc_sampling_period_set(p_adc, p_adc_chan[j].chan, 10);
    }
    /* ����ADC˳��ɨ��ת��ͨ�������� */
    for(i = 0; i < chan_num; i++) {
        __adc_chmux[i].chan = p_adc_chan[i].chan;
        __adc_chmux[i].type =  p_adc_chan[i].type;
        amhw_hc32f460_adc_channel_mux_set(p_adc, p_adc_chan[i].chan,p_adc_chan[i].type);
        amhw_hc32f460_adc_seq_a_channel_sel0(p_adc, p_adc_chan[i].chan);
    }

    amhw_hc32f460_adc_int_flag_clr(p_adc, AMHW_HC32F460_ADC_INT_EOCAF);

    /* ��ֹת������ж� */
    amhw_hc32f460_adc_int_disable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);

    /* ʹ��ת������ж� */
    amhw_hc32f460_adc_int_enable(p_adc, AMHW_HC32F460_ADC_INT_EOCAF);

    while(1) {

        /* ��ʼת�� */
        amhw_hc32f460_adc_convert_start(p_adc);

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        for(i = 0; i < chan_num; i++) {

            /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
            adc_mv = __g_adc_dat[i] * vref_mv / ((1UL << 12) -1);

            am_kprintf("sqr chan : %d, Sample : %d, Vol: %d mv\r\n", i, __g_adc_dat[i], adc_mv);
        }

        am_mdelay(500);
    }

}
/** [src_hc32f460_hw_multichan_adc] */

/* end of file */
