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
 * \brief ZML165 UART �û������ļ�
 * \sa am_hwconf_zml165_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation.
 * \endinternal
 */

#include "am_zml165.h"
#include "am_zlg_uart.h"
#include "am_gpio.h"
#include "hw/amhw_zlg_uart.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zml165_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zml165_uart
 * \copydoc am_hwconf_zml165_uart.c
 * @{
 */

/** \brief ����1ƽ̨��ʼ�� */
static void __zlg_plfm_uart1_init (void)
{
    /* ���ų�ʼ�� PIOB_3_UART1_TX  PIOB_4_UART1_RX */
    am_gpio_pin_cfg(PIOB_3, PIOB_3_UART1_TX | PIOB_3_AF_PP);
    am_gpio_pin_cfg(PIOB_4, PIOB_4_UART1_RX | PIOB_4_INPUT_FLOAT);
}

/** \brief �������1ƽ̨��ʼ�� */
static void __zlg_plfm_uart1_deinit (void)
{
     /* �ر�UART1ʱ�� */
     am_clk_disable(CLK_UART1);
     am_gpio_pin_cfg(PIOB_3, AM_GPIO_INPUT);
     am_gpio_pin_cfg(PIOB_4, AM_GPIO_INPUT);
}

/** \brief ����1�豸��Ϣ */
static const am_zlg_uart_devinfo_t __g_uart1_devinfo = {
    ZML165_UART1_BASE,              /**< \brief ����1 */
    INUM_UART1,                     /**< \brief ����1���жϱ�� */
    CLK_UART1,                      /**< \brief ����1��ʱ�� */

    AMHW_ZLG_UART_DATA_8BIT   |  /**< \brief 8λ���� */
    AMHW_ZLG_UART_PARITY_NO   |  /**< \brief �޼��� */
    AMHW_ZLG_UART_STOP_1BIT,     /**< \brief 1��ֹͣλ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief USART1ʹ��RS485 */
    __zlg_plfm_uart1_init,          /**< \brief USART1��ƽ̨��ʼ�� */
    __zlg_plfm_uart1_deinit,        /**< \brief USART1��ƽ̨ȥ��ʼ�� */
};

static am_zlg_uart_dev_t  __g_uart1_dev;   /**< \brief ���崮��1 �豸 */

/** \brief UART1ʵ����ʼ�������uart1��׼������ */
am_uart_handle_t am_zml165_uart1_inst_init (void)
{
    return am_zlg_uart_init(&__g_uart1_dev, &__g_uart1_devinfo);
}

/** \brief UART1ʵ�����ʼ�� */
void am_zml165_uart1_inst_deinit (am_uart_handle_t handle)
{
    am_zlg_uart_deinit((am_zlg_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
