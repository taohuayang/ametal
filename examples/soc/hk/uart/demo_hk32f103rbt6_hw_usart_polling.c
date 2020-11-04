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
 * \brief USART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� "HW example---USART test in polling mode:"��
 *   2. ָ������������յ����ַ�����
 *
 * \par Դ����
 * \snippet demo_hk32f103rbt6_hw_usart_polling.c src_hk32f103rbt6_hw_usart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hk32f103rbt6_hw_usart_polling
 * \copydoc demo_hk32f103rbt6_hw_usart_polling.c
 */

/** [src_hk32f103rbt6_hw_usart_polling] */
#include <amhw_hk32f103rbt6_usart.h>
#include "ametal.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define USART_BAUDRATE     (115200)              /** <\brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static const uint8_t usart_hw_str[] =
                                {"HW example---USART test in polling mode:\r\n"};

/**
 * \brief USART HW ��ѯ�շ���ʼ��
 */
static void usart_polling_init (amhw_hk32f103rbt6_usart_t *p_hw_usart, uint32_t clk_rate)
{

    /* ���ô��ڲ����� */
    amhw_hk32f103rbt6_usart_baudrate_set(p_hw_usart, clk_rate, USART_BAUDRATE);

    amhw_hk32f103rbt6_usart_stop_bit_sel(p_hw_usart, AMHW_HK32F103RBT6_USART_STOP_10_BIT);
    amhw_hk32f103rbt6_usart_word_length_sel(p_hw_usart, AMHW_HK32F103RBT6_USART_DATA_8BIT);
    amhw_hk32f103rbt6_usart_parity_bit_sel(p_hw_usart,  AMHW_HK32F103RBT6_USART_PARITY_NO);

    /* ʹ�ܴ��� */
    amhw_hk32f103rbt6_usart_receiver_enable(p_hw_usart);
    amhw_hk32f103rbt6_usart_transmitter_enable(p_hw_usart);
    amhw_hk32f103rbt6_usart_enable(p_hw_usart);
}

/**
 * \brief �������
 */
void demo_hk32f103rbt6_hw_usart_polling_entry (amhw_hk32f103rbt6_usart_t *p_hw_usart,
                                         uint32_t             clk_rate)
{

    /* ���ݻ����� */
    uint8_t buf_src[256];

    /* USART��ѯ��ʼ�� */
    usart_polling_init(p_hw_usart, clk_rate);

    amhw_hk32f103rbt6_usart_poll_send(p_hw_usart, usart_hw_str, sizeof(usart_hw_str));

    while (1) {

        /* �����ַ� */
        amhw_hk32f103rbt6_usart_poll_receive(p_hw_usart, buf_src, 1);

        /* ���͸ոս��յ��ַ� */
        amhw_hk32f103rbt6_usart_poll_send(p_hw_usart, buf_src, 1);
    }
}
/** [src_hk32f103rbt6_hw_usart_polling] */

/* end of file */
