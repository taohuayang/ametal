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
 * \brief AM_ZML166_ADC�����̶���ѹ��ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Ӻô��ڣ���PT100�������RTDC��RTDB֮�䣬���̽�RTDA��
 *   2. ���ڽ����ӡ��PT100��ֵ�Լ��¶�ֵ
 *
 * \par Դ����
 * \snippet dome_zml166_adc_pt100_measure.c src_dome_zml166_adc_pt100_measure
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_dome_zml166_adc_pt100_measure
 * \copydoc dome_zml166_adc_pt100_measure.c
 */
#include "ametal.h"
#include "am_zml166_adc.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_pt100_to_temperature.h"
#include "am_common.h"

/**
 * \brief ��ȡPT100�ȵ�����ֵ
 */
float am_zml166_adc_thermistor_res_data_get(void *p_handle)
{
    am_zml166_adc_handle_t  handle = (am_zml166_adc_handle_t)p_handle;
    uint8_t  i;
    float  r_data = 0;
    int32_t   vol_rtdb_c = 0, vol_rtda_c = 0, vol_res = 0;
    int32_t  adc_val[4];
    am_adc_handle_t adc_handle = &handle->adc_serve;
    //����ͨ��ΪADC_2 ADC_4    RTDB---RTDC
    am_zml166_adc_mux_set(handle, AM_ZML166_ADC_INPS_AIN(2) | AM_ZML166_ADC_INNS_AIN(3));
    am_adc_read(adc_handle, 0, (uint32_t *)adc_val, AM_NELEMENTS(adc_val));
    for(i = 0; i < AM_NELEMENTS(adc_val); i++){
        vol_rtdb_c += adc_val[i];
    }
    vol_rtdb_c /= 4;

    /*  ����ͨ��ΪADC_3 ADC_4     RTDA---RTDC */
    am_zml166_adc_mux_set(handle, AM_ZML166_ADC_INPS_AIN(3) | AM_ZML166_ADC_INNS_AIN(3));
    am_adc_read(adc_handle, 0, (uint32_t *)adc_val, AM_NELEMENTS(adc_val));

    for(i = 0; i < AM_NELEMENTS(adc_val); i++){
        vol_rtda_c += adc_val[i];
    }
    vol_rtda_c /= AM_NELEMENTS(adc_val);

    vol_res = vol_rtdb_c * 2 - vol_rtda_c ;

    if(vol_res < 0){
        vol_res *= -1;
    }

    /* ���õ�ѹУ׼ϵ��  */
    r_data = (float)((float)(vol_res / 8388607.0) * 1999.36);

    return r_data;
}
/**
 * \brief ����AML166�弶���PT100�ȵ������ֵ�Լ���Ӧ��ת���¶�
 */
void demo_zml166_adc_pt100_measure_entry(am_zml166_adc_handle_t  handle,
                                         float                  *p_para)
{
    float  r_data = 0, temperature = 0;

    while(1){
        /* ����PT100���汶�� */
        am_zml166_adc_gain_set(handle, 1);

        r_data = am_zml166_adc_thermistor_res_data_get(handle);
        /* ����У׼ϵ��  */
        r_data = p_para[0] * r_data + p_para[1];

        /* PT100����ת�¶�  */
        temperature = pt100_to_temperature(r_data);

        if(temperature < 0){
            temperature *= -1;
            am_kprintf("Tem = -%d.%03d��\r\n",
               ((int32_t)(temperature * 1000) / 1000) ,
               ((int32_t)(temperature * 1000) % 1000));
        }else{
            am_kprintf("Tem = %d.%03d��\r\n\r\n",
               ((int32_t)(temperature * 1000) / 1000) ,
               ((int32_t)(temperature * 1000) % 1000));
        }
        am_mdelay(200);
    }
}
