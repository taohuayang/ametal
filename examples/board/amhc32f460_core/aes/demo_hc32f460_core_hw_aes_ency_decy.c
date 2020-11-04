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
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   AES�����ݼ���Ȼ����ܣ�������ܳ������������ǰ����һ�����򴮿ڴ�ӡ��Aes ency-decy success!\r\n����
 *   ��֮��ӡ"Aes ency-decy failed!\r\n"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *       PIOE_5 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f460_core_aes_ency_decy.c src_hc32f460_core_aes_ency_decy
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-26  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_core_hw_aes_ency_decy
 * \copydoc demo_hc32f460_core_hw_aes_ency_decy.c
 */

/** [src_hc32f460_core_aes_ency_decy] */
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_hc32f460_aes.h"
#include "am_vdebug.h"
#include "demo_hc32f460_entries.h"

/*******************************************************************************
 * ȫ�ֱ���
 ******************************************************************************/
/**< \brief ��Ŵ����ܵ�����*/
static uint32_t aes_data[4] = {0x33221100, 0x77665544, 0xBBAA9988, 0xFFEEDDCC};

/**< \brief AES�ܳ� */
static uint32_t aes_key[8]  = {0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C,\
                               0x13121110, 0x17161514, 0x1B1A1918, 0x1F1E1D1C};

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_aes_ency_decy_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core hw aes-ency-decy !\r\n");

    /* ����AESʱ�� */
    am_clk_enable (CLK_AES);

    /* ������� */
    demo_hc32f460_hw_aes_ency_decy_entry(HC32F460_AES,
                                         aes_data,
                                         aes_key);
}

/* end of file */
