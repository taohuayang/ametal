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
 *   ��Trng generate tset success!\r\n��,��֮��ӡ ��Trng generate tset failed!\r\n����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f17x_core_trng_dac.c src_hc32f17x_core_trng_generate
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-12  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f17x_core_trng_generate
 * \copydoc demo_hc32f17x_core_trng_generate.c
 */

/** [src_hc32f17x_core_trng_generate] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "hc32_pin.h"
#include "am_hc32_trng.h"
#include "demo_hc32_entries.h"
/**
 * \brief �������
 */
void demo_hc32f17x_core_hw_trng_generate_entry (void)
{

    AM_DBG_INFO("demo amf17x_core hw trng generate test!\r\n");

    /* ����trngʱ�� */
    am_clk_enable (CLK_RNG);

    demo_hc32_hw_trng_generate_entry(HC32_TRNG);
}

/* end of file */
