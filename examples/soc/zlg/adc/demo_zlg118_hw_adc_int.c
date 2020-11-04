/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
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
 * \snippet demo_zlg118_hw_adc_int.c src_zlg118_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-18  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_adc_int
 * \copydoc demo_zlg118_hw_adc_int.c
 */

/** [src_zlg118_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_int.h"
#include "hw/amhw_zlg118_adc.h"
#include "am_zlg118.h"

static volatile uint16_t  __g_adc_dat[10];              /**< \brief ����ֵ���� */
static volatile am_bool_t __g_adc_complete = AM_FALSE;



/**
 * \brief ADC �жϷ�����
 */
static void __adc_isr (void *p_arg)
{
    static uint8_t i = 0;

    amhw_zlg118_adc_t *p_hw_adc = (amhw_zlg118_adc_t *)p_arg;

    amhw_zlg118_adc_flag_clr(p_hw_adc,
                             AMHW_ZLG118_ADC_FLAG_CONVERT_SINGLE);

    __g_adc_dat[i] = amhw_zlg118_adc_data_get (p_hw_adc) & 0x0fff;

    i++;
    if (i == 10) {

        i = 0;

        __g_adc_complete = AM_TRUE;

        /* ����ת��ֹͣ */
        amhw_zlg118_adc_single_convert_stop(p_hw_adc);
    } else {

        /* ����ת������ */
        amhw_zlg118_adc_single_convert_start(p_hw_adc);
    }
}

/** \brief �������  */
void demo_zlg118_hw_adc_int_entry (void    *p_hw_adc,
                                   int      int_num,
                                   uint8_t  chan,
                                   uint32_t vref_mv)
{
    uint8_t                    i        = 0;
    uint32_t                   adc_mv   = 0;    /* ������ѹ */
    uint32_t                   sum      = 0;
    amhw_zlg118_adc_chan_sel_t chan_sel = (amhw_zlg118_adc_chan_sel_t)chan;
    amhw_zlg118_adc_t         *p_adc    = (amhw_zlg118_adc_t *)p_hw_adc;

    am_kprintf("The ADC HW Int Demo\r\n");

    /* ����ת������ж� */
    am_int_connect(int_num, __adc_isr, p_adc);
    am_int_enable(int_num);

    /* �ڲ��ο���ѹʹ�� */
    amhw_zlg118_adc_inrefvol_enable(p_adc);

    /* ���òο���ѹԴ */
    amhw_zlg118_adc_refvol_sel(p_adc, AMHW_ZLG118_ADC_REFVOL_AVCC);

    /* BGRģ��ʹ�� */
    amhw_zlg118_bgr_enable(AM_TRUE);

    /* ADCʹ��*/
    amhw_zlg118_adc_enable(p_adc);

    /* ��ʱ 20us���ȴ� ADC�� BGRģ��������� */
    am_udelay(20);

    /* ADC���� */
    amhw_zlg118_adc_disable(p_adc);

    /* ʹ�ܵ���ת��ģʽ */
    amhw_zlg118_adc_mode_sel(p_adc, AMHW_ZLG118_ADC_MODE_SINGLE);

    amhw_zlg118_adc_align_way_sel(p_adc, AMHW_ZLG118_ADC_DATA_ALIGN_RIGHT);

    /* ����ת������ */
    amhw_zlg118_adc_sample_period_sel(p_adc,
                                      AMHW_ZLG118_ADC_SAMPLE_PERIOD_12);

    /* ����ADCʱ�ӷ�Ƶ */
    amhw_zlg118_adc_pclk_div_sel(p_adc, AMHW_ZLG118_ADC_PCLK_DIV8);

    /* ����ADC����ͨ�������� */
    amhw_zlg118_adc_sgl_chan_sel(p_adc, chan_sel);

    /* ���뷽ʽ���� */
    amhw_zlg118_adc_align_way_sel(p_adc,
                                  AMHW_ZLG118_ADC_DATA_ALIGN_RIGHT);

    /* �ж�ʹ��*/
    amhw_zlg118_adc_int_enable(p_adc);

    /* ���־λ */
    amhw_zlg118_adc_flag_clr(p_adc, AMHW_ZLG118_ADC_FLAG_ALL);

    /* ADCʹ��*/
    amhw_zlg118_adc_enable(p_adc);


    while(1) {

        /* ����ת������ */
        amhw_zlg118_adc_single_convert_start(p_adc);

        /* �ȴ�ת����� */
        while (__g_adc_complete == AM_FALSE);

        for (sum = 0,i = 0; i < 10 ; i++) {
            sum += __g_adc_dat[i];
        }

        sum = sum / 10;

        /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
        adc_mv = sum * 3300 / ((1UL << 12) -1);

        AM_DBG_INFO("Sample : %d, Vol: %d mv\r\n", sum, adc_mv);

        am_mdelay(500);
    }
}
/** [src_zlg118_hw_adc_int] */

/* end of file */
