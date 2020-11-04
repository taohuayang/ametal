/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2020 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief ISO7816 �Ӵ�ʽ������
 *
 * - �������裺
 *   1. �� ��Ƭ���뿨���С�
 *
 * - ʵ������
 *   1. �������͸�λ���
 *   2. �������ͻ�ȡ��������
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \par Դ����
 * \snippet demo_iso7816.c src_iso7816
 *
 * \internal
 * \par Modification history
 * - 1.00  20-04-27  licl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_iso7816
 * \copydoc demo_iso7816.c
 */


/** [src_iso7816] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_iso7816.h"

am_local void __printf_rand_num (uint8_t *rx_buf, uint32_t rx_bytes) {
    uint8_t  i;

    am_kprintf("Rand num:");
    for (i = 0; i < (rx_bytes - 2); i++) {
        am_kprintf(" 0x%x ", rx_buf[i]);
    }
    am_kprintf("\r\n");
}

am_local void __printf_rest_msg (uint8_t *rx_buf, uint32_t rx_bytes) {
    uint8_t  i;

    am_kprintf("Rest msg:");
    for (i = 0; i < (rx_bytes); i++) {
        am_kprintf(" 0x%x ", rx_buf[i]);
    }
    am_kprintf("\r\n");
}

/**
 * \brief �������
 */
void demo_iso7816_entry (am_iso7816_handle_t iso7816_handle) {
    int      ret;

    uint8_t  rx_buf[20] = {0};
    uint32_t rx_bytes;
    uint8_t  tx_buf1[8] = {0x00, 0xA4, 0x00, 0x00, 0x02, 0X3F, 0X00, 0X01};
    uint8_t  tx_buf2[5] = {0x00, 0x84, 0x00, 0x00, 0x04};

    /* �临λ  */
    ret = am_iso7816_cold_reset(iso7816_handle, rx_buf, &rx_bytes, AM_FALSE);
    if (ret != AM_OK) {
            am_kprintf("Cold reset failed!\r\n");
    } else {
        am_kprintf("Cold reset successful!\r\n");
        __printf_rest_msg(rx_buf, rx_bytes);
    }

    /* �ļ�Ŀ¼����   */
    ret = am_iso7816_transfer(iso7816_handle, 0, tx_buf1, 8, rx_buf, &rx_bytes);
    if (ret != AM_OK) {
            am_kprintf("Set file directory failed!\r\n");
    } else {
        am_kprintf("Set file directory successful!\r\n");
    }

    /* ��ȡ4�ֽ������  */
    ret = am_iso7816_transfer(iso7816_handle, 0, tx_buf2, 5, rx_buf, &rx_bytes);
    if (ret != AM_OK) {
        am_kprintf("Get rand num failed!\r\n");
    } else {
        __printf_rand_num(rx_buf, rx_bytes);
    }

    /* �ȸ�λ  */
    am_iso7816_warm_reset(iso7816_handle, rx_buf, &rx_bytes);
    if (ret != AM_OK) {
            am_kprintf("Warm reset failed!\r\n");
    } else {
        am_kprintf("Warm reset successful!\r\n");
        __printf_rest_msg(rx_buf, rx_bytes);
    }

    /* ��ȡ4�ֽ������  */
    ret = am_iso7816_transfer(iso7816_handle, 0, tx_buf2, 5, rx_buf, &rx_bytes);
    if (ret != AM_OK) {
        am_kprintf("Get rand num failed!\r\n");
    } else {
        __printf_rand_num(rx_buf, rx_bytes);
    }

    /* �ϵ�  */
    am_iso7816_ic_deactivate(iso7816_handle);
    am_kprintf("IC deactivate!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}

/** [src_iso7816] */

/* end of file */
