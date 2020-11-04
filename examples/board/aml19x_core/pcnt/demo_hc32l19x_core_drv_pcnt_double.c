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
 * \brief PCNT ˫ͨ����������������̣�ͨ����׼�ӿں��м������㺯��ʵ��
 *
 * - ʵ������
 *   1. PCNTͨ�����������������PB5��PB7�����������������źţ����ڴ�ӡ����ֵ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l19x_drv_pcnt_double.c src_hc32l19x_drv_pcnt_double
 *
 * \internal
 * \par Modification history
 * - 1.00 19-11-22  RZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l19x_drv_pcnt_double
 * \copydoc demo_hc32l19x_drv_pcnt_double.c
 */

/** [src_hc32l19x_drv_pcnt_double] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32_pcnt.h"
#include "am_hc32l19x_inst_init.h"
#include "demo_aml19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l19x_core_drv_pcnt_double_entry (void)
{
    am_hc32_pcnt_handle_t handle;
    uint16_t cnt = 0;

    AM_DBG_INFO("demo aml19x_core pcnt double entry!\r\n");

    handle = am_hc32_pcnt_inst_init();

    am_hc32_pcnt_clk_sel(handle, HC32_PCNT_PCLK);

    am_hc32_pcnt_polar_set(handle, HC32_PCNT_S0PNOINVERT);

    am_hc32_pcnt_flt_enable(handle, 5, 5);

    am_hc32_pcnt_timeover_disable(handle);

    am_hc32_pcnt_start(handle,
                       HC32_PCNT_DOUBLE,
                       HC32_PCNT_UP,
                       100,
                       HC32_PCNT_DGB_0);
    while(1) {
        cnt = am_hc32_pcnt_cnt_get(handle);
        AM_DBG_INFO("pcnt double cnt is %d !\r\n", cnt);
        am_mdelay(500); 
    }
}
/** [src_hc32l19x_drv_pcnt_double] */

/* end of file */
