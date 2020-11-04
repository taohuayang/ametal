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
 * \brief uartcmd����ID��ͨ����׼�ӿ�ʵ��
 *
 * - ������
 * - 1. ׼������AMKS16RFID-8�����壬��Ϊ��1�Ͱ�2��
 *   2. ��1��������ߣ�ִ��projects_keil5\examples_uart_cmd_read_card\demo_kl26_uartcmd_handle�е����̣�
 *   3. ����1��PIOC_3���2��PIOC_4���ӣ���1��PIOC_4���2��PIOC_3���ӣ���1���2���أ�
 *   4. ����2��PIOE_20����Դ��ڽ��ն����ӣ�
 *   5. ��������ϵ����������ӵĸ�λ����Ȼ�����ɿ���1�ĸ�λ����1������ɿ���2
 *      �ĸ�λ����
 *   6. ��A�࿨Ƭ���ڰ�1�����߸�Ӧ����
 *
 * - ʵ������
 * - 1. ��5������������1�ϵ���������LED�ύ����˸�������ظ���5�����������������⡣
 *   2. ��6�����������ȡ����Ƭ�����2�Ĵ��ڣ�PIOE_20)���ӡ���ߵ���ż����ţ����ҷ���������һ����
 *
 * \par Դ����
 * \snippet demo_kl26_std_uartcmd_picca_8ante_read_id.c src_kl26_std_uartcmd_picca_8ante_read_id
 *
 * \internal
 * \par Modification history
 * - 1.00 18-03-16  sdq, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_kl26_if_std_uartcmd_8ante_picca_read_id
 * \copydoc demo_kl26_std_uartcmd_picca_8ante_read_id.c
 */

/** [src_kl26_std_uartcmd_picca_8ante_read_id] */
#include <am_uartcmd_send.h>
#include "ametal.h"
#include "am_board.h"
#include "am_kl26.h"
#include "am_int.h"
#include "am_buzzer.h"
#include "string.h"
#include "am_kl26_inst_init.h"

#ifndef AM_VDEBUG
#define AM_VDEBUG           /* ��������ģʽ */
#endif

#include "am_vdebug.h"


static uint8_t __g_uartcmd_uart_txbuf[128];
static uint8_t __g_uartcmd_uart_rxbuf[128];

static const am_uartcmd_uart_dev_info_t __g_uartcmd_uart_devinfo = {
    __g_uartcmd_uart_rxbuf,
    __g_uartcmd_uart_txbuf,
    128,
    128,
    AM_UARTCMD_BAUDRATE_115200,
    AM_UARTCMD_MODE_AUTO_CHECK,
    0x59
};

static void __error_happen(int line)
{
    AM_DBG_INFO("error_happen %d\r\n", line);
    am_led_on(0);
    while(1);
}

/**
 * \uartcmd 8���߶�ȡ��ƬID
 */
void demo_amks16rfid8_uartcmd_picca_8ante_read_id_entry (void)
{
    int      ret;
    int      i, j;
    uint16_t atq;
    uint8_t  saq;
    uint8_t  uid_len;
    uint8_t  uid[10];
    am_uart_handle_t      uart1_handle;
    am_uartcmd_uart_dev_t  uartcmd_uart_dev;
    am_uartcmd_send_handle_t    uartcmd_handle;

    uart1_handle  = am_kl26_uart1_inst_init();
    uartcmd_handle = am_uartcmd_uart_new_init(&uartcmd_uart_dev,
                                               uart1_handle,
                                              &__g_uartcmd_uart_devinfo);

    if (uartcmd_handle == NULL) {
        __error_happen(__LINE__);
    }

    while (1) {
        for (j = 0; j < 8; j++) {
            am_uartcmd_ante_select(uartcmd_handle, j);
            ret = uartcmd_card_active(uartcmd_handle,
                                      AM_UARTCMD_MIFARE_CARD_REQ_ALL,
                                      &atq,
                                      &saq,
                                      &uid_len,
                                      uid,
                                      10);
            AM_DBG_INFO("ante %d\r\n", j);
            if (ret == AM_OK) {
                for (i = 0; i < uid_len; i++) {
                    AM_DBG_INFO("%02x   ", uid[i]);
                }
                AM_DBG_INFO ("\r\n\r\n");
                
                am_uartcmd_picca_halt(uartcmd_handle);
                am_buzzer_beep_async(100);
            }
        }
    }
}

/** [src_kl26_std_uartcmd_picca_8ante_read_id] */

/* end of file */
