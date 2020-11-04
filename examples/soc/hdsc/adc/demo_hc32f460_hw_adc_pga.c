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
 * \brief ADC PGA ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ����λ�������VRIN��3.3V�����ӡ�
 *   2. ��ָ��ADCͨ����Ӧ���������ӵ�λ������� VRO��
 *
 * - ʵ������
 *   1. ���Դ��������λ�������ѹ����PGA�Ŵ�ǰ��Ĳ���ֵ������ӡ���汶����
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
    static uint8_t i = 0;

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

    __g_adc_dat[i] = amhw_hc32f460_adc_ch_data_get (p_hw_adc,
                                                    ADC_CHAN,
                                                    AMHW_HC32F460_ADC_RESOLUTION_12BIT,
                                                    AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    i++;
    if (i == 10) {

        i = 0;

        __g_adc_complete = AM_TRUE;

        /* ����ת��ֹͣ */
        amhw_hc32f460_adc_convert_stop(p_hw_adc);
    } else {

        /* ����ת������ */
    	amhw_hc32f460_adc_convert_start(p_hw_adc);
    }
}

/** \brief �������  */
void demo_hc32f460_hw_adc_pga_entry (void    *p_hw_adc,
                                     int      int_num,
                                     uint8_t  chan,
                                     uint32_t vref_mv)
{
    uint8_t                    i        = 0;
    uint32_t                   adc_mv   = 0;    /* ������ѹ */
    uint32_t                   sum      = 0;
    amhw_hc32f460_adc_t       *p_adc    = (amhw_hc32f460_adc_t *)p_hw_adc;

    am_kprintf("The ADC HW Int Demo\r\n");

    /* ����ת������ж� */
    amhw_hc32f460_int_sel0_31(int_num, EVT_ADC1_EOCA);
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

    /* ADC�ɱ�̷Ŵ���������汶������ */
    amhw_hc32f460_adc_pga_gain_set(p_hw_adc, AMHW_HC32F460_ADC_PGA_GAIN_3_200);

    /* ADC�ɱ�̷Ŵ������ģ������ѡ�� */
    amhw_hc32f460_adc_pga_analog_input_set(p_hw_adc, AMHW_HC32F460_ADC_CH_MUX_ADC1_IN0);

    /* ADC�ɱ�̷Ŵ��������������ѡ�� */
    amhw_hc32f460_adc_pga_negative_input_set(p_hw_adc, AMHW_HC32F460_ADC_PGA_N_INPUT_INAVSS);

    /* ��ֹת������ж� */
    amhw_hc32f460_adc_int_disable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);
    amhw_hc32f460_adc_int_disable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCBF);

    /* ʹ��ת������ж� */
    amhw_hc32f460_adc_int_enable(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);

    /* ������������ */
    amhw_hc32f460_adc_sampling_period_set(p_hw_adc, chan, 50);

    while(1) {

        /* ��ֹPGA���� */
        amhw_hc32f460_adc_pga_disable(p_hw_adc);

        /* ����ת������ */
        amhw_hc32f460_adc_convert_start(p_hw_adc);

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        __g_adc_complete = AM_FALSE;

        for (sum = 0,i = 0; i < 10 ; i++) {
            sum += __g_adc_dat[i];
        }

        sum = sum / 10;

        /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
        adc_mv = sum * 3300 / ((1UL << 12) -1);

        AM_DBG_INFO("Before pga enable\r\n");
        AM_DBG_INFO("Sample : %d, Vol: %d mv\r\n", sum, adc_mv);

        /* ����PGA����*/
        amhw_hc32f460_adc_pga_enable(p_hw_adc);

        /* ����ת������ */
        amhw_hc32f460_adc_convert_start(p_hw_adc);

        /* �ȴ�ת����� */
         while (__g_adc_complete == AM_FALSE);
         __g_adc_complete = AM_FALSE;

         for (sum = 0,i = 0; i < 10 ; i++) {
             sum += __g_adc_dat[i];
         }

         sum = sum / 10;

         /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
         adc_mv = sum * 3300 / ((1UL << 12) -1);

         AM_DBG_INFO("after pga enable\r\n");
         AM_DBG_INFO("Sample : %d, Vol: %d mv\r\n", sum, adc_mv);
         AM_DBG_INFO("Gain factor : 3.2000\r\n", sum, adc_mv);
         AM_DBG_INFO("\r\n");

         am_mdelay(500);

    }
}
/** [src_hc32f460_hw_adc_int] */

/* end of file */
