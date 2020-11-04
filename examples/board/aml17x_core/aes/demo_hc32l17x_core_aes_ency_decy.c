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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32l17x_core_aes_ency_decy.c src_hc32l17x_core_aes_ency_decy
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-09  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l17x_core_aes_ency_decy
 * \copydoc demo_hc32l17x_core_aes_ency_decy.c
 */

/** [src_hc32l17x_core_aes_ency_decy] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "hc32_pin.h"
#include "am_hc32_aes.h"
#include "demo_hc32_entries.h"

/**
 * \brief ��Կ����
 */
#define AES_KEY_LEN    AM_HC32_AES_KEY_LEN_128_BIT

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
void demo_hc32l17x_core_hw_aes_ency_decy_entry (void)
{
    AM_DBG_INFO("Test start: demo-aes-ency-decy test !\r\n");

    /* ����AESʱ�� */
    am_clk_enable (CLK_AES);

    /* ������� */
    demo_hc32_hw_aes_ency_decy_entry(HC32_AES,
                                       AES_KEY_LEN,
                                       aes_data,
                                       aes_key);
}

/* end of file */
