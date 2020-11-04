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
 * \brief HC32 UART �û������ļ�
 * \sa am_hc32l_hwconfig_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-19  zp, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_hc32_uart.h"
#include "hw/amhw_hc32_uart.h"
#include "am_clk.h"
#include "am_hc32.h"
#include "hw/amhw_hc32_gpio.h"
#include "hw/amhw_hc32_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_uart
 * \copydoc am_hwconf_hc32_uart.c
 * @{
 */
/** \brief ����0ƽ̨��ʼ�� */
static void __hc32_plfm_uart0_init (void)
{
    am_clk_enable(CLK_UART0);

    am_gpio_pin_cfg(PIOA_9,  PIOA_9_UART0_TXD  | PIOA_9_OUT_PP );
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART0_RXD | PIOA_10_INPUT_FLOAT);
}

/** \brief �������0ƽ̨��ʼ�� */
static void __hc32_plfm_uart0_deinit (void)
{
    am_clk_disable(CLK_UART0);

    am_gpio_pin_cfg(PIOA_9, PIOA_9_GPIO  | PIOA_9_INPUT_PU);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_GPIO | PIOA_10_INPUT_PU);
}

/** \brief ����0�豸��Ϣ */
static const am_hc32_uart_devinfo_t __g_uart0_devinfo = {

    HC32_UART0_BASE,                /**< \brief ����0 */
    INUM_UART0_2,                   /**< \brief ����0���жϱ�� */
    CLK_UART0,                      /**< \brief ����ʱ��ID */

    AMHW_HC32_UART_PARITY_NO |      /**< \brief �޼��� */
    AMHW_HC32_UART_STOP_1_0_BIT,    /**< \brief 1��ֹͣλ */

    AM_FALSE,                       /**< \brief ��ʹ���첽��˫�������ߣ�ģʽ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief ʹ��RS485 */
    __hc32_plfm_uart0_init,         /**< \brief UART0��ƽ̨��ʼ�� */
    __hc32_plfm_uart0_deinit,       /**< \brief UART0��ƽ̨ȥ��ʼ�� */
};

/**< \brief ���崮��0 �豸 */
static am_hc32_uart_dev_t  __g_uart0_dev;

/** \brief UART0ʵ����ʼ�������uart0��׼������ */
am_uart_handle_t am_hc32_uart0_inst_init (void)
{
    return am_hc32_uart_init(&__g_uart0_dev, &__g_uart0_devinfo);
}

/** \brief UART0ʵ�����ʼ�� */
void am_hc32_uart0_inst_deinit (am_uart_handle_t handle)
{
    am_hc32_uart_deinit((am_hc32_uart_dev_t *)handle);
}

/** \brief uart1ƽ̨��ʼ�� */
static void __hc32_plfm_uart1_init (void)
{
    am_clk_enable(CLK_UART1);

    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART1_TXD | PIOA_2_OUT_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_UART1_RXD | PIOA_3_INPUT_FLOAT);
}

/** \brief �������1ƽ̨��ʼ�� */
static void __hc32_plfm_uart1_deinit (void)
{
    am_clk_disable(CLK_UART1);

    am_gpio_pin_cfg(PIOA_2, PIOA_2_GPIO | PIOA_2_INPUT_PU);
    am_gpio_pin_cfg(PIOA_3, PIOA_3_GPIO | PIOA_3_INPUT_PU);
}

/** \brief ����1�豸��Ϣ */
static const am_hc32_uart_devinfo_t __g_uart1_devinfo = {

    HC32_UART1_BASE,                /**< \brief ����1 */
    INUM_UART1_3,                   /**< \brief ����1���жϱ�� */
    CLK_UART1,                      /**< \brief ����ʱ��ID */

    AMHW_HC32_UART_PARITY_NO |      /**< \brief �޼��� */
    AMHW_HC32_UART_STOP_1_0_BIT,    /**< \brief 1��ֹͣλ */

    AM_FALSE,                       /**< \brief ��ʹ���첽��˫�������ߣ�ģʽ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief ʹ��RS485 */
    __hc32_plfm_uart1_init,         /**< \brief UART1��ƽ̨��ʼ�� */
    __hc32_plfm_uart1_deinit,       /**< \brief UART1��ƽ̨ȥ��ʼ�� */
};

/**< \brief ���崮��1 �豸 */
static am_hc32_uart_dev_t  __g_uart1_dev;

/** \brief UART1ʵ����ʼ�������uart1��׼������ */
am_uart_handle_t am_hc32_uart1_inst_init (void)
{
    return am_hc32_uart_init(&__g_uart1_dev, &__g_uart1_devinfo);
}

/** \brief UART1ʵ�����ʼ�� */
void am_hc32_uart1_inst_deinit (am_uart_handle_t handle)
{
    am_hc32_uart_deinit((am_hc32_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
