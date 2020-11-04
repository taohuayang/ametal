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
 * \brief ADC���̣����ò�ѯ��ʽ��ȡADC���ͨ��ת�������ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ָ��ADCͨ����Ӧ����������ģ�����롣
 *  am_hwconf_hc32l19x_adc.c�ļ��޸��豸��Ϣ�У�
 *   2. �ο���ѹѡ�� AMHW_HC32_ADC_REFVOL_AVCC��
 *   3. �ο���ѹ(mv)�� 3300(AVCC)��
 *   4. ����ADCͨ��28�ڲ��¶ȴ�����.(1��ʹ�ܣ�0������)
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_std_multichan_adc.c src_std_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-28  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_multichan_adc
 * \copydoc demo_std_multichan_adc.c
 */

/** [src_std_multichan_adc] */
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
void demo_std_multichan_adc_entry (am_adc_handle_t handle, int *p_chan, int chan_num)
{
    if (p_chan == NULL || chan_num <= 0) {
        return;
    }

    int adc_bits = am_adc_bits_get(handle , p_chan[0]);        /* ��ȡADCת������ */
    int adc_vref = am_adc_vref_get(handle , p_chan[0]);

    uint32_t i = 0;
    uint32_t adc_code;                                    /* ���� Code ֵ   */
    uint32_t adc_mv;                                      /* ������ѹ */

    if (adc_bits < 0 || adc_bits >= 32) {
        am_kprintf("The ADC  channel is error, Please check! \r\n");
        return;
    }

    while (1) {

        if (i > chan_num - 1) {
            i = 0;
            am_kprintf("\r\n");
            am_mdelay(500);
        }

        adc_code = __adc_code_get(handle, p_chan[i]);
        adc_mv   = adc_code * adc_vref / ((1UL << adc_bits) - 1);

        /* �������������ѹֵ */
        am_kprintf("chan : %d, Sample : %d, Vol: %d mv\r\n", p_chan[i], adc_code, adc_mv);

        i++;
    }
}
/** [src_std_multichan_adc] */

/* end of file */
