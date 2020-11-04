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
 * \brief ZML165 ADC�����̶���ѹ��ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Ӻô��ڣ�����������ѹ�����Ӧ��ͨ��(ͨ��A)��
 *   2. ѡ���Ӧ�����汶���������ѹ*����ӦС�ڻ�׼��ѹ
 *   3. ���ڽ����ӡ����ѹֵ
 *   4. ���ڳ����������л���ѹֵ  ֱ��������Ӧ�����ּ��ɡ�
 *
 * \par Դ����
 * \snippet dome_zml165_adc_adjust_vol_entry.c src_dome_zml165_adc_adjust_vol_entry
 *
 * \internal
 * \par Modification History
 * - 1.00 20-02-25  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zml165_adc_adjust_vol_entry
 * \copydoc demo_zml165_adc_vol_measure_entry.c
 */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zml165_adc.h"
#include "demo_zlg_entries.h"
/**
 * \brief ZML165 ADC��ѹ��������
 */
void demo_zml165_adc_vol_measure_entry(void  *p_handle)
{
    uint8_t  gpa[4] = {1, 2, 64, 128};
    am_zml165_adc_handle_t  handle = (am_zml165_adc_handle_t)p_handle;
    am_zml165_adc_config_t  config;

    config.pga = AM_ZML165_ADC_PGA_1;
    config.speed = AM_ZML165_ADC_SPEED_1280HZ;
    config.channel = AM_ZML165_ADC_CHANNEL_A;
    config.refo_off = AM_ZML165_ADC_VOUT_DISABLE;

    am_zml165_adc_config_load(handle, &config);

    while(1){
        uint8_t i = 0;
        int32_t adc_val[10];
        float   vol = 0;
        volatile uint32_t time = am_sys_tick_get();
        am_adc_read(&handle->adc_serve, 0, (void *)adc_val, AM_NELEMENTS(adc_val));
        time = am_sys_tick_get() - time;
        /* ����ǰ�ĸ������Ա�֤������Ч�����ݽ���ʱ�� */ 
        for(i = 4 ; i < AM_NELEMENTS(adc_val); i++){
            if(adc_val[i] >= 0x800000)  {
                adc_val[i] &= 0x7fffff;
                adc_val[i] |= 0xff800000;
            }
            vol += (adc_val[i] / ((double)AM_NELEMENTS(adc_val) - 4));
        }

        vol = (double)((double)(vol  / ((1 << 24) -1)) * handle->p_devinfo->vref);
        vol *= 10000;

        vol /= gpa[config.pga];

        if(vol > 0){
            am_kprintf("Voltage is %d.%04d mV\r\n", (int32_t)vol/10000, (int32_t)vol%10000);
        }else {
            vol *= -1;
            am_kprintf("Voltage is  -%d.%04d mV\r\n", (int32_t)vol/10000, (int32_t)vol%10000);
        }
        am_mdelay(500);
    }
}
