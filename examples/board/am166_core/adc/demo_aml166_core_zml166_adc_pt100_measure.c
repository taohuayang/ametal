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
 *
 * - ʵ������
 *   1. ���Ӻô��ڣ���PT100�������RTDC��RTDB֮�䣬���̽�RTDA��
 *   2. ���ڽ����ӡ��PT100�����¶�ֵ
 *
 * \par Դ����
 * \snippet demo_aml166_core_adc24_pt100_measure.c src_aml166_core_adc24_pt100_measure
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_aml166_core_adc24_pt100_measure
 * \copydoc demo_aml166_core_adc24_pt100_measure.c
 */

/** [src_aml166_core_adc24_pt100_measure] */

#include "string.h"
#include "am_zml166_adc.h"
#include "am_zlg_flash.h"
#include "zlg116_periph_map.h"
#include "demo_components_entries.h"
#include "demo_aml166_core_entries.h"
#include "am_aml166_inst_init.h"
#include "am_hwconf_zml166_adc.h"
#include "demo_zlg_entries.h"
/**
 * \brief ZML166 24λADC  PT100��������
 */
void demo_aml166_core_zml166_adc_pt100_measure (void)
{
    float para[2];
    am_zml166_adc_handle_t  handle = am_zml166_adc_inst_init();
    /* ��flash�л�ȡPT100���������ϵ�� */
    am_zlg_flash_init(ZLG116_FLASH);
    memcpy((void *)para, (uint32_t *)PT100_PARA_SAVE_ADDRESS, 4 * 2);
    /* ��flash��δ����ϵ�� */
    if(!(para[0] < 1.02 && para[0] > 0.98)){
        para[0] = 1;
    }
    if(!(para[1] < 0.15 && para[1] > -0.15)){
        para[1] = 0;
    }
    demo_zml166_adc_pt100_measure_entry((void *)handle, para);
}

/** [src_aml166_core_adc24_pt100_measure] */

/* end of file */
