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
 * \brief
 * - ʵ������
 *   1. ���Ӻô��ڣ�����������ѹ�����Ӧ��ͨ����
 *   2. ���ڽ����ӡ����ѹֵ
 *
 * \par Դ����
 * \snippet demo_aml166_core_adc24_vol_measure.c src_aml166_core_adc24_vol_measure
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_aml166_core_adc24_vol_measure
 * \copydoc demo_aml166_core_adc24_vol_measure.c
 */

/** [src_aml166_core_adc24_vol_measure] */
#include <am_aml166_inst_init.h>
#include <am_hwconf_zml166_adc.h>
#include "string.h"
#include "am_zml166_adc.h"
#include "am_zlg_flash.h"
#include "zlg116_periph_map.h"
#include "demo_components_entries.h"
#include "demo_aml166_core_entries.h"
#include "demo_zlg_entries.h"

#define AM_ZML166_ADC_PGA_SET_1         0      /**< \brief 1������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_2         1      /**< \brief 2������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_4         2      /**< \brief 4������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_8         3      /**< \brief 8������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_16        4     /**< \brief 16������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_32        5     /**< \brief 32������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_64        6     /**< \brief 64������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_128       7    /**< \brief 128������ѡ����� */
#define AM_ZML166_ADC_PGA_SET_256       8    /**< \brief 256������ѡ����� */


/**
 * \brief ZML166  24λADC �̶���ѹ��������
 */
void demo_aml166_core_zml166_adc_vol_measure (void)
{
    int i = 0;
    float para[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    am_zml166_adc_handle_t handle = am_zml166_adc_inst_init();
    /* ��ȡflash�е�ѹУ׼ϵ�� */
    am_zlg_flash_init(ZLG116_FLASH);
    memcpy((void *)para, (uint32_t *)((FLASH_BLOCK_NUM * 1024)), 4 * 16);
    /* ������ϵ������ȷ */
    if(!(para[0] < 1.1 && para[0] > 0.9)){
        for(i = 0; i < 8; i++){
            para[2 * i + 0] = 1;
            para[2 * i + 1] = 0;
        }
    }
    demo_zml166_adc_vol_measure_entry((void *)handle,
                                              para,
                                              AM_ZML166_ADC_PGA_SET_1);
}

/** [src_aml166_core_adc24_vol_measure] */

/* end of file */
