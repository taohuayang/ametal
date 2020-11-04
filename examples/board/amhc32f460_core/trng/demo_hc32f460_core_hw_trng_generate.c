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
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   TRNG ģ���ϵ����һ�����������ϵ����������Աȣ������ͬ��TRNG�����������ȷ����ӡ
 *   ��Trng generate test success!\r\n������ӡ�����������,
 *   ��֮��ӡ ��Trng generate test failed!\r\n����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *       PIOE_5 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f460_core_trng_dac.c src_hc32f460_core_trng_generate
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-26  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_core_trng_generate
 * \copydoc demo_hc32f460_core_trng_generate.c
 */

/** [src_hc32f460_core_trng_generate] */
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_hc32f460_trng.h"
#include "demo_hc32f460_entries.h"
/**
 * \brief �������
 */
void demo_hc32f460_core_hw_trng_generate_entry (void)
{

    AM_DBG_INFO("demo amhc32f460_core hw trng generate test!\r\n");

    /* ����trngʱ�� */
    am_clk_enable (CLK_TRNG);

    demo_hc32f460_hw_trng_generate_entry(HC32F460_TRNG);
}

/* end of file */
