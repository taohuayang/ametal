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
 * \brief MM32L073 UART �û������ļ�
 * \sa am_hwconf_mm32l073_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation.
 * \endinternal
 */

#include "am_mm32l073.h"
#include "am_mm32_uart.h"
#include "am_gpio.h"
#include "hw/amhw_mm32_uart.h"
#include "hw/amhw_mm32_gpio.h"
#include "hw/amhw_mm32l073_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_mm32l073_uart
 * \copydoc am_hwconf_mm32l073_uart.c
 * @{
 */

/** \brief ����1ƽ̨��ʼ�� */
static void __mm32_plfm_uart1_init (void)
{

     /* ���ų�ʼ�� PIOA_9_UART1_TX  PIOA_10_UART1_RX */
     am_gpio_pin_cfg(PIOA_9, PIOA_9_UART1_TX | PIOA_9_AF_PP);
     am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX | PIOA_10_INPUT_FLOAT);

}

/** \brief �������1ƽ̨��ʼ�� */
static void __mm32_plfm_uart1_deinit (void)
{

     /* �ر�UART1ʱ�� */
     am_clk_disable(CLK_UART1);

     am_gpio_pin_cfg(PIOA_9, AM_GPIO_INPUT);
     am_gpio_pin_cfg(PIOA_10, AM_GPIO_INPUT);
}

/** \brief ����1�豸��Ϣ */
static const am_mm32_uart_devinfo_t __g_uart1_devinfo = {
    MM32L073_UART1_BASE,              /**< \brief ����1 */
    INUM_UART1,                     /**< \brief ����1���жϱ�� */
    CLK_UART1,                      /**< \brief ����1��ʱ�� */

    AMHW_MM32_UART_DATA_8BIT   |  /**< \brief 8λ���� */
    AMHW_MM32_UART_PARITY_NO   |  /**< \brief �޼��� */
    AMHW_MM32_UART_STOP_1BIT,     /**< \brief 1��ֹͣλ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief USART1ʹ��RS485 */
    __mm32_plfm_uart1_init,          /**< \brief USART1��ƽ̨��ʼ�� */
    __mm32_plfm_uart1_deinit,        /**< \brief USART1��ƽ̨ȥ��ʼ�� */
};

static am_mm32_uart_dev_t  __g_uart1_dev;   /**< \brief ���崮��1 �豸 */

/** \brief ����2ƽ̨��ʼ�� */
static void __mm32_plfm_uart2_init (void)
{

    /* ���ų�ʼ�� PIOA_3_UART2_RX  PIOA_2_UART2_TX */
     am_gpio_pin_cfg(PIOA_3, PIOA_3_UART2_RX | PIOA_3_INPUT_FLOAT);
     am_gpio_pin_cfg(PIOA_2, PIOA_2_UART2_TX | PIOA_2_AF_PP);
}

/** \brief �������2 ƽ̨��ʼ�� */
static void __mm32_plfm_uart2_deinit (void)
{

    /* �ر�UART2ʱ�� */
    am_clk_disable(CLK_UART2);

    am_gpio_pin_cfg(PIOA_3, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_2, AM_GPIO_INPUT);
}

/** \brief ����2 �豸��Ϣ */
static const am_mm32_uart_devinfo_t __g_uart2_devinfo = {

    MM32L073_UART2_BASE,                /**< \brief ����2 */
    INUM_UART2,                       /**< \brief ����2���жϱ�� */
    CLK_UART2,                        /**< \brief ����2��ʱ�� */

    AMHW_MM32_UART_DATA_8BIT   |    /**< \brief 8λ���� */
    AMHW_MM32_UART_PARITY_NO   |    /**< \brief �޼��� */
    AMHW_MM32_UART_STOP_1BIT,       /**< \brief 1��ֹͣλ */

    115200,                           /**< \brief ���õĲ����� */

    0,                                /**< \brief �������ж� */

    NULL,                             /**< \brief USART2ʹ��RS485 */
    __mm32_plfm_uart2_init,            /**< \brief USART2��ƽ̨��ʼ�� */
    __mm32_plfm_uart2_deinit,          /**< \brief USART2��ƽ̨ȥ��ʼ�� */
};

static am_mm32_uart_dev_t  __g_uart2_dev;   /**< \brief ���崮��2�豸 */

/** \brief UART1ʵ����ʼ�������uart1��׼������ */
am_uart_handle_t am_mm32l073_uart1_inst_init (void)
{
    return am_mm32_uart_init(&__g_uart1_dev, &__g_uart1_devinfo);
}

/** \brief UART1ʵ�����ʼ�� */
void am_mm32l073_uart1_inst_deinit (am_uart_handle_t handle)
{
    am_mm32_uart_deinit((am_mm32_uart_dev_t *)handle);
}

/** \brief UART2ʵ����ʼ�������uart2��׼������ */
am_uart_handle_t am_mm32l073_uart2_inst_init (void)
{
    return am_mm32_uart_init(&__g_uart2_dev, &__g_uart2_devinfo);
}

/** \brief UART2ʵ�����ʼ�� */
void am_mm32l073_uart2_inst_deinit (am_uart_handle_t handle)
{
    am_mm32_uart_deinit((am_mm32_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
