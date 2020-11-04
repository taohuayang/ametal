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
 * \brief RAM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. д��ɹ������ڴ�ӡ256��ʮ���������ݡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f07x_hw_ram.c src_hc32f07x_hw_ram
 *
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f07x_hw_ram
 * \copydoc demo_hc32f07x_hw_ram.c
 */

/** [src_hc32f07x_hw_clk] */
#include "hw/amhw_hc32_ram.h"
#include "am_hc32_ram.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_hc32f07x.h"
#include "am_clk.h"
#include "demo_amf07x_core_entries.h"

#define START_ADDR    0X20002000
#define SIZE          0X100
amhw_hc32_ram_t *p_hw_ram = (amhw_hc32_ram_t *)HC32_RAM_BASE;

/**
 * \brief �������
 */
void demo_hc32f07x_core_hw_ram_entry (void)
{
    int    i = 0;
    static uint8_t data[SIZE] = {0}; /* Ҫд�� RAM ������ */
    static uint8_t temp[SIZE] = {0}; /* �� RAM �ж��������� */

    /* ���ݳ�ʼ�� */
    for (i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    /* RAM��������ʼ�� */
    am_hc32_ram_init(p_hw_ram);

    /* RAM���� */
    am_hc32_ram_erase (p_hw_ram,
                       START_ADDR,
                       SIZE);

    /* RAMд�� */
    am_hc32_ram_write (p_hw_ram,
                       START_ADDR,
                       data,
                       SIZE);

    /* RAM��ȡ */
    am_hc32_ram_read (p_hw_ram,
                      START_ADDR,
                      temp,
                      SIZE);

    for(i = 0; i < SIZE; i++) {
        AM_DBG_INFO("%04d  ", temp[i]);
            if(data[i] != temp[i]) {
                AM_DBG_INFO("\r\nverify error!\r\n");
                AM_FOREVER;
            }
    }
    AM_DBG_INFO("\r\nram test success!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f07x_hw_ram] */

/* end of file */
