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
 *   2. ��6�����������ȡ����Ƭ�����2�Ĵ��ڣ�PIOE_20)���ӡ���š�
 *
 * \par Դ����
 * \snippet demo_kl26_std_uartcmd_picca_auto_detect_entry.c src_kl26_std_uartcmd_picca_auto_detect_entry
 *
 * \internal
 * \par Modification history
 * - 1.00 18-05-17  sdq, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_kl26_if_std_uartcmd_picca_auto_detect
 * \copydoc demo_kl26_std_uartcmd_picca_auto_detect_entry.c
 */

/** [src_kl26_std_uartcmd_picca_auto_detect_entry] */
#include <am_uartcmd_send.h>
#include "ametal.h"
#include "am_board.h"
#include "am_kl26.h"
#include "am_int.h"
#include "am_kl26_inst_init.h"
#include "am_buzzer.h"
#include "string.h"

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


const am_uartcmd_auto_detect_info_t __g_uartcmd_auto_detect_info = {
    0,
    AM_UARTCMD_MIFARE_CARD_TX_TX1,
    AM_UARTCMD_MIFARE_CARD_REQ_IDLE,
    AM_UARTCMD_MIFARE_CARD_AUTH_DIRECT,       /* ����֤ʱ��������������� */
    AM_UARTCMD_IC_KEY_TYPE_B,
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    6,
    0x0C
};

static void __error_happen(int line)
{
    AM_DBG_INFO("error_happen %d\r\n", line);
    am_led_on(0);
    while(1);
}

/**
 * \brief �Զ����ص�����
 */
static void __uartcmd_callback (void *p_arg)
{
    uint32_t *detect_flag = (uint32_t *)p_arg;

    *detect_flag = 1;
}

/**
 * \uartcmd �Զ�����������
 */
void demo_amks16rfid8_uartcmd_picca_auto_detect_entry (void)
{
    int      ret;
    int      i;
    am_uart_handle_t       uart1_handle;
    am_uartcmd_uart_dev_t  uartcmd_uart_dev;
    am_uartcmd_send_handle_t    uartcmd_handle;
    volatile uint32_t      detect_flag = 0;     /* �Զ������ɱ�־ */
    am_uartcmd_mifare_card_info_t card_info;

    uart1_handle  = am_kl26_uart1_inst_init();
    uartcmd_handle = am_uartcmd_uart_new_init(&uartcmd_uart_dev,
                                               uart1_handle,
                                              &__g_uartcmd_uart_devinfo);

    if (uartcmd_handle == NULL) {
        __error_happen(__LINE__);
    }
    
    /* �����Զ����ص����� */
    am_uartcmd_mifare_card_auto_detect_cb_set(uartcmd_handle,
                                              __uartcmd_callback,
                                              (void *)&detect_flag);

    /* ��ʼ�Զ���� */
    am_uartcmd_mifare_card_auto_detect_start(uartcmd_handle,
                                             &__g_uartcmd_auto_detect_info);

    while (1) {
        if (detect_flag) {
            detect_flag = 0;
            
            ret = am_uartcmd_mifare_card_auto_detect_read(uartcmd_handle,
                                                          &card_info);

            if (ret == AM_OK) {

                AM_DBG_INFO("��⵽������IDΪ %d bytes �� \r\n", card_info.uid_len);

                for (i = 0; i < card_info.uid_len; i++) {
                    AM_DBG_INFO("%02x   ", card_info.uid[i]);
                }
                AM_DBG_INFO ("\r\n");

                am_led_on(1);
            } else {
                am_led_off(1);
                AM_DBG_INFO("ʧ�ܣ�%d \r\n", ret);
            }

            /* һ���Զ������ɺ���Ҫ���������Զ���� */
            am_uartcmd_mifare_card_auto_detect_start(uartcmd_handle,
                                                     &__g_uartcmd_auto_detect_info);
        }
    }
}

/** [src_kl26_std_uartcmd_picca_auto_detect_entry] */

/* end of file */
