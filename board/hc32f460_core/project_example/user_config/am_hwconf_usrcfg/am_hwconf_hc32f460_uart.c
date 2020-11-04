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
 * \brief HC32F460 UART �û������ļ�
 * \sa am_hc32f460_hwconfig_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_hc32f460_uart.h"
#include "am_clk.h"
#include "am_hc32f460.h"
#include "hw/amhw_hc32f460_gpio.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_uart
 * \copydoc am_hwconf_hc32f460_uart.c
 * @{
 */

/*********************************USART1*****************************************/
/** \brief USART1 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __USART1_PIN_RX    PIOA_3
#define __USART1_PIN_TX    PIOA_2
/** \brief ����1ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart1_init(void)
{
    am_clk_enable(CLK_USART1);
    am_gpio_pin_cfg(__USART1_PIN_RX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART1_RX));
    am_gpio_pin_cfg(__USART1_PIN_TX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART1_TX));
}

/** \brief �������1ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart1_deinit(void)
{
    am_clk_disable(CLK_USART1);

    am_gpio_pin_cfg(__USART1_PIN_RX, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__USART1_PIN_TX, AM_GPIO_INPUT);
}

/** \brief ����1�豸��Ϣ */
static const am_hc32f460_uart_devinfo_t __g_uart1_devinfo = {

        HC32F460_UART1_BASE,           /**< \brief ����1 */
        INT_VECTOR_0,                  /**< \brief ����1�Ľ��մ����жϱ�� */
        INT_VECTOR_1,                  /**< \brief ����1�Ľ������жϱ�� */
        INT_VECTOR_2,                  /**< \brief ����1�ķ��Ϳ��жϱ�� */
        INT_VECTOR_3,                  /**< \brief ����1�ķ�������жϱ�� */
        INT_VECTOR_4,                  /**< \brief ����1�ĳ�ʱ�жϱ�� */

        1,                             /**< \brief ����1���豸��� */
        CLK_USART1,                    /**< \brief ����1��ʱ�� */

        AMHW_HC32F460_UART_DATA_8BIT | /**< \brief 8λ���� */
        AMHW_HC32F460_UART_PARITY_NO | /**< \brief �޼��� */
        AMHW_HC32F460_UART_STOP_1BIT,  /**< \brief 1��ֹͣλ */

        115200,                        /**< \brief ���õĲ����� */

        0,                             /**< \brief �������ж� */

        NULL,                          /**< \brief ��ʹ��RS485 */
        __hc32f460_plfm_uart1_init,    /**< \brief UART3��ƽ̨��ʼ�� */
        __hc32f460_plfm_uart1_deinit,  /**< \brief UART3��ƽ̨ȥ��ʼ�� */
};

/** \brief ���崮��1 �豸 */
am_hc32f460_uart_dev_t __g_uart1_dev;

/** \brief UART1ʵ����ʼ�������uart1��׼������ */
am_uart_handle_t am_hc32f460_uart1_inst_init(void)
{
    return am_hc32f460_uart_init(&__g_uart1_dev, &__g_uart1_devinfo);
}

/** \brief UART1ʵ�����ʼ�� */
void am_hc32f460_uart1_inst_deinit(am_uart_handle_t handle)
{
    am_hc32f460_uart_deinit((am_hc32f460_uart_dev_t *) handle);
}

/*********************************USART2*****************************************/
/** \brief USART2 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __USART2_PIN_RX    PIOA_3
#define __USART2_PIN_TX    PIOA_2
/** \brief ����2ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart2_init (void)
{
    am_clk_enable(CLK_USART2);
    am_gpio_pin_cfg(__USART2_PIN_RX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART2_RX));
    am_gpio_pin_cfg(__USART2_PIN_TX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART2_TX));
}

/** \brief �������2 ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart2_deinit (void)
{

    /* �ر�UART2ʱ�� */
    am_clk_disable(CLK_USART2);

    am_gpio_pin_cfg(__USART2_PIN_RX, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__USART2_PIN_TX, AM_GPIO_INPUT);
}

/** \brief ����2 �豸��Ϣ */
static const am_hc32f460_uart_devinfo_t __g_uart2_devinfo = {

        HC32F460_UART2_BASE,           /**< \brief ����2 */

        INT_VECTOR_5,                  /**< \brief ����2�Ľ��մ����жϱ�� */
        INT_VECTOR_6,                  /**< \brief ����2�Ľ������жϱ�� */
        INT_VECTOR_7,                  /**< \brief ����2�ķ��Ϳ��жϱ�� */
        INT_VECTOR_8,                  /**< \brief ����2�ķ�������жϱ�� */
        INT_VECTOR_9,                  /**< \brief ����2�ĳ�ʱ�жϱ�� */

        2,                             /**< \brief ����2���豸��� */
        CLK_USART2,                    /**< \brief ����2��ʱ�� */

        AMHW_HC32F460_UART_DATA_8BIT | /**< \brief 8λ���� */
        AMHW_HC32F460_UART_PARITY_NO | /**< \brief �޼��� */
        AMHW_HC32F460_UART_STOP_1BIT,  /**< \brief 1��ֹͣλ */

        9600,                        /**< \brief ���õĲ����� */

        0,                             /**< \brief �������ж� */

        NULL,                          /**< \brief ��ʹ��RS485 */
        __hc32f460_plfm_uart2_init,    /**< \brief UART2��ƽ̨��ʼ�� */
        __hc32f460_plfm_uart2_deinit,  /**< \brief UART2��ƽ̨ȥ��ʼ�� */
};

/** \brief ���崮��2�豸 */
am_hc32f460_uart_dev_t __g_uart2_dev;

/** \brief UART2ʵ����ʼ�������uart2��׼������ */
am_uart_handle_t am_hc32f460_uart2_inst_init (void)
{
    return am_hc32f460_uart_init(&__g_uart2_dev, &__g_uart2_devinfo);
}

/** \brief UART2ʵ�����ʼ�� */
void am_hc32f460_uart2_inst_deinit (am_uart_handle_t handle)
{
    am_hc32f460_uart_deinit((am_hc32f460_uart_dev_t *)handle);
}

/*********************************USART3*****************************************/
/** \brief USART3 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __USART3_PIN_RX    PIOE_4
#define __USART3_PIN_TX    PIOE_5
/** \brief ����3ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart3_init(void)
{
    am_clk_enable(CLK_USART3);
    am_gpio_pin_cfg(__USART3_PIN_RX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART3_RX));
    am_gpio_pin_cfg(__USART3_PIN_TX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART3_TX));
}

/** \brief �������3ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart3_deinit(void)
{
    am_clk_disable(CLK_USART3);

    am_gpio_pin_cfg(__USART3_PIN_RX, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__USART3_PIN_TX, AM_GPIO_INPUT);
}

/** \brief ����3�豸��Ϣ */
static const am_hc32f460_uart_devinfo_t __g_uart3_devinfo = {

        HC32F460_UART3_BASE,           /**< \brief ����3 */

        INT_VECTOR_10,                 /**< \brief ����3�Ľ��մ����жϱ�� */
        INT_VECTOR_11,                 /**< \brief ����3�Ľ������жϱ�� */
        INT_VECTOR_12,                 /**< \brief ����3�ķ��Ϳ��жϱ�� */
        INT_VECTOR_13,                 /**< \brief ����3�ķ�������жϱ�� */
        INT_VECTOR_14,                 /**< \brief ����3�ĳ�ʱ�жϱ�� */

        3,                             /**< \brief ����3���豸��� */
        CLK_USART3,                    /**< \brief ����3��ʱ�� */

        AMHW_HC32F460_UART_DATA_8BIT | /**< \brief 8λ���� */
        AMHW_HC32F460_UART_PARITY_NO | /**< \brief �޼��� */
        AMHW_HC32F460_UART_STOP_1BIT,  /**< \brief 1��ֹͣλ */

        115200,                        /**< \brief ���õĲ����� */

        0,                             /**< \brief �������ж� */

        NULL,                          /**< \brief ��ʹ��RS485 */
        __hc32f460_plfm_uart3_init,    /**< \brief UART3��ƽ̨��ʼ�� */
        __hc32f460_plfm_uart3_deinit,  /**< \brief UART3��ƽ̨ȥ��ʼ�� */
};

/** \brief ���崮��3 �豸 */
am_hc32f460_uart_dev_t __g_uart3_dev;

/** \brief UART3ʵ����ʼ�������uart3��׼������ */
am_uart_handle_t am_hc32f460_uart3_inst_init(void)
{
    return am_hc32f460_uart_init(&__g_uart3_dev, &__g_uart3_devinfo);
}

/** \brief UART3ʵ�����ʼ�� */
void am_hc32f460_uart3_inst_deinit(am_uart_handle_t handle)
{
    am_hc32f460_uart_deinit((am_hc32f460_uart_dev_t *) handle);
}



/*********************************USART4*****************************************/
/** \brief USART4 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __USART4_PIN_RX    PIOC_13
#define __USART4_PIN_TX    PIOH_2

/** \brief ����4ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart4_init(void)
{
    am_clk_enable(CLK_USART4);
    am_gpio_pin_cfg(__USART4_PIN_RX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART4_RX));
    am_gpio_pin_cfg(__USART4_PIN_TX, GPIO_AFIO(AMHW_HC32F460_AFIO_USART4_TX));
}

/** \brief �������4ƽ̨��ʼ�� */
static void __hc32f460_plfm_uart4_deinit(void)
{
    am_clk_disable(CLK_USART4);

    am_gpio_pin_cfg(__USART4_PIN_RX, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__USART4_PIN_TX, AM_GPIO_INPUT);
}

/** \brief ����4�豸��Ϣ */
static const am_hc32f460_uart_devinfo_t __g_uart4_devinfo = {

    HC32F460_UART4_BASE,           /**< \brief ����4 */
    INT_VECTOR_15,                 /**< \brief ����4�Ľ��մ����жϱ�� */
    INT_VECTOR_16,                 /**< \brief ����4�Ľ������жϱ�� */
    INT_VECTOR_17,                 /**< \brief ����4�ķ��Ϳ��жϱ�� */
    INT_VECTOR_18,                 /**< \brief ����4�ķ�������жϱ�� */
    INT_VECTOR_19,                 /**< \brief ����4�ĳ�ʱ�жϱ�� */

    4,                             /**< \brief ����4���豸��� */
    CLK_USART4,                    /**< \brief ����4��ʱ�� */

    AMHW_HC32F460_UART_DATA_8BIT | /**< \brief 8λ���� */
    AMHW_HC32F460_UART_PARITY_NO | /**< \brief �޼��� */
    AMHW_HC32F460_UART_STOP_1BIT,  /**< \brief 1��ֹͣλ */

    115200,                        /**< \brief ���õĲ����� */

    0,                             /**< \brief �������ж� */

    NULL,                          /**< \brief ��ʹ��RS485 */
    __hc32f460_plfm_uart4_init,    /**< \brief UART4��ƽ̨��ʼ�� */
    __hc32f460_plfm_uart4_deinit,  /**< \brief UART4��ƽ̨ȥ��ʼ�� */
};

/** \brief ���崮��4 �豸 */
am_hc32f460_uart_dev_t __g_uart4_dev;

/** \brief UART4ʵ����ʼ�������uart4��׼������ */
am_uart_handle_t am_hc32f460_uart4_inst_init(void)
{
    return am_hc32f460_uart_init(&__g_uart4_dev, &__g_uart4_devinfo);
}

/** \brief UART4ʵ�����ʼ�� */
void am_hc32f460_uart4_inst_deinit(am_uart_handle_t handle)
{
    am_hc32f460_uart_deinit((am_hc32f460_uart_dev_t *) handle);
}

/**
 * @}
 */

/* end of file */
