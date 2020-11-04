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
 * \brief ADC�ڲ��¶ȴ��������̣����ò�ѯ��ʽ��ȡADCת�������ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *  am_hwconf_hc32l19x_adc.c�ļ��޸��豸��Ϣ�У�
 *   1. �ο���ѹѡ�� AMHW_HC32_ADC_REFVOL_INSIDE_1500MV �� AMHW_HC32_ADC_REFVOL_INSIDE_2500MV��
 *   2. �ο���ѹ(mv)�� 1500 �� 2500��
 *   3. ʹ��ADCͨ��28�ڲ��¶ȴ�����.(1��ʹ�ܣ�0������)
 *
 *
 * - ʵ������
 *   1. ��������¶Ȳ���ֵ��
 *
 * \par Դ����
 * \snippet demo_std_adc_its.c src_std_adc_its
 *
 * \internal
 * \par Modification History
 * - 1.00 19-12-09  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_adc_its
 * \copydoc demo_std_adc_its.c
 */

/** [src_std_adc_its] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_adc.h"

/**
 * \brief ��ȡ ADC ת��ֵ
 */
static uint32_t __adc_code_get (am_adc_handle_t handle, int chan)
{
    int      adc_bits = am_adc_bits_get(handle, chan);
    int      i;
    uint32_t sum;

    /*
     * ����ADCת�������ɼ�12�� CODE ֵ
     *
     * ʵ��Ӧ���У���ʹ�õ� ADC λ����ȷ���ģ����������ֶ����������
     */
    if (adc_bits <= 8) {
        uint8_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    } else if (adc_bits <= 16) {
        uint16_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    } else {
        uint32_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* ��ֵ���� */
            sum += val_buf[i];
        }
    }
    return (sum / 12);
}

/**
 * \brief �������
 */
void demo_std_adc_its_entry (am_adc_handle_t handle, int chan)
{

    int adc_bits = am_adc_bits_get(handle , chan);          /* ��ȡADCת������  */
    int adc_vref = am_adc_vref_get(handle , chan);

    uint32_t adc_code;                                      /* ���� Code ֵ     */
    uint16_t adc_trim;                                      /* 16BitsУ׼ֵ     */
    int32_t adc_temp;                                       /* �����¶�         */

    am_kprintf("The ADC value channel is %d: \r\n",chan);

    if (adc_bits < 0 || adc_bits >= 32) {
        am_kprintf("The ADC  channel is error, Please check! \r\n");
        return;
    }

    if (adc_vref == 1500) {
        adc_trim = (*((volatile uint16_t*)(0x00100C34)));
    } else if (adc_vref == 2500) {
        adc_trim = (*((volatile uint16_t*)(0x00100C36)));
    } else {
        return;
    }

    /* ��������ο���ѹ��16Bits��У׼ֵ */
    am_kprintf("Reference Voltage : %d mV , Trim : %d \r\n", adc_vref, adc_trim);

    while (1) {

        adc_code = __adc_code_get(handle, chan);

        if (adc_vref == 1500) {
            adc_temp = (int32_t)(25 + 0.0839 * 1.5 * (int32_t)(adc_code - adc_trim));
        } else if (adc_vref == 2500) {
            adc_temp = (int32_t)(25 + 0.0839 * 2.5 * (int32_t)(adc_code - adc_trim));
        } else {
            return;
        }

        /* ������������¶�ֵ */
        am_kprintf("Sample : %d, Temperature: %d ��C\r\n", adc_code, adc_temp);

        am_mdelay(500);
    }
}
/** [src_std_adc_its] */

/* end of file */
