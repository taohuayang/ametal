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
 * \brief CLKTRIM ���̣�ͨ��HW�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ʱ��У׼�����ڴ�ӡ��У׼ʱ����ο�ʱ��Ƶ�ʱ�ֵ��
 *   2. ʱ�Ӽ�⣺���ڴ�ӡ�����ʱ�ӹ���״̬��Ϣ��
 *
 * \par Դ����
 * \snippet demo_hc32f07x_core_clktrim.c src_hc32f07x_core_clktrim
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f07x_core_clktrim
 * \copydoc demo_hc32f07x_core_clktrim.c
 */

/** [src_hc32f07x_core_fclktrim] */
#include "hw/amhw_hc32_rcc.h"
#include "ametal.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_hc32f07x_clktrim.h"
#include "am_hc32.h"
#include "am_hc32_clk.h"
#include "hc32_clk.h"

/**
 * \brief �������
 */
void demo_hc32f07x_core_clktrim_entry (void)
{
    uint16_t ret = 0;

    AM_DBG_INFO("demo amf07x_core clktrim entry!\r\n");

    /* У׼ʱ�Ӳ������� */
    amhw_hc32_rcc_rch_trim_set(*((volatile uint16_t*) AMHW_HC32_RCH_FRE_8MHz));

    /* ʱ��У׼ */
    ret = am_hc32f07x_clktrim_calibrate (1000,
                                     AMHW_CLKTRIM_REFCLK_XTH,
                                     AMHW_CLKTRIM_CALCLK_RCH);

    AM_DBG_INFO("the (Fcal * 1000)/Fref is: %d\r\n",ret);

    /* ʱ�Ӽ�� */
    ret = am_hc32f07x_clktrim_monitor (10000,
                                       100,
                                  AMHW_CLKTRIM_REFCLK_IRC10K,
                                  AMHW_CLKTRIM_CALCLK_XTL);
    if (ret == AM_OK){
        AM_DBG_INFO("the calclk is Ok!");
    } else {
        AM_DBG_INFO("the calclk is Fail!");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f07x_core_fclktrim] */

/* end of file */
