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
 * \brief ZSN700 UART �û������ļ�
 * \sa am_zsn700l_hwconfig_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-19  zp, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_zsn700_uart.h"
#include "hw/amhw_zsn700_uart.h"
#include "am_clk.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_gpio.h"
#include "hw/amhw_zsn700_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_zsn700_uart
 * \copydoc am_hwconf_zsn700_uart.c
 * @{
 */
/** \brief ����0ƽ̨��ʼ�� */
static void __zsn700_plfm_uart0_init (void)
{
    am_clk_enable(CLK_UART0);

    am_gpio_pin_cfg(PIOA_9,  PIOA_9_UART0_TXD  | PIOA_9_OUT_PP );
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART0_RXD | PIOA_10_INPUT_FLOAT);
}

/** \brief �������0ƽ̨��ʼ�� */
static void __zsn700_plfm_uart0_deinit (void)
{
    am_clk_disable(CLK_UART0);

    am_gpio_pin_cfg(PIOA_9,  PIOA_9_GPIO  | PIOA_9_INPUT_PU);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_GPIO | PIOA_10_INPUT_PU);
}

/** \brief ����0�豸��Ϣ */
static const am_zsn700_uart_devinfo_t __g_uart0_devinfo = {

    ZSN700_UART0_BASE,            /**< \brief ����0 */
    INUM_UART0_2,                 /**< \brief ����0���жϱ�� */
    AMHW_ZSN700_UART_WORK_MODE_1, /**< \brief ���ڹ���ģʽ */

    AMHW_ZSN700_UART_PARITY_NO |  /**< \brief żУ��  MODE0/1:����У��  MODE2/3:����У�� */
    AMHW_ZSN700_UART_STOP_1_0_BIT,/**< \brief 1��ֹͣλ */

    115200,                       /**< \brief ���õĲ����� */

    0,                            /**< \brief �������ж� */

    {
        AM_FALSE,                 /**< \brief ���ܶ����ַ�Զ�ʶ�� */
        0x00,                     /**< \brief ��ַ0x00 */
        0x00,                     /**< \brief ��ַȫ�������� */
    },

    {
        AM_FALSE,                 /**< \brief �������� */
        0,                        /**< \brief CTS���ű�� */
        0,                        /**< \brief RTS���ű��*/
    },

    NULL,                         /**< \brief ʹ��RS485 */
    __zsn700_plfm_uart0_init,     /**< \brief UART0��ƽ̨��ʼ�� */
    __zsn700_plfm_uart0_deinit,   /**< \brief UART0��ƽ̨ȥ��ʼ�� */
};

/* �����ж�Դ������Ҫ�����豸��Ϣ */
am_zsn700_uart_dev_t  *__gp_uart0 = NULL;

/**< \brief ���崮��0 �豸 */
static am_zsn700_uart_dev_t  __g_uart0_dev;

/** \brief UART0ʵ����ʼ�������uart0��׼������ */
am_uart_handle_t am_zsn700_uart0_inst_init (void)
{
    __gp_uart0 = &__g_uart0_dev;
    return am_zsn700_uart_init(&__g_uart0_dev, &__g_uart0_devinfo);
}

/** \brief UART0ʵ�����ʼ�� */
void am_zsn700_uart0_inst_deinit (am_uart_handle_t handle)
{
    am_zsn700_uart_deinit((am_zsn700_uart_dev_t *)handle);
}

/** \brief uart1ƽ̨��ʼ�� */
static void __zsn700_plfm_uart1_init (void)
{
    am_clk_enable(CLK_UART1);

    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART1_TXD | PIOA_2_OUT_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_UART1_RXD | PIOA_3_INPUT_FLOAT);
}

/** \brief �������1ƽ̨��ʼ�� */
static void __zsn700_plfm_uart1_deinit (void)
{
    am_clk_disable(CLK_UART1);

    am_gpio_pin_cfg(PIOA_2, PIOA_2_GPIO | PIOA_2_INPUT_PU);
    am_gpio_pin_cfg(PIOA_3, PIOA_3_GPIO | PIOA_3_INPUT_PU);
}

/** \brief ����1�豸��Ϣ */
static const am_zsn700_uart_devinfo_t __g_uart1_devinfo = {

    ZSN700_UART1_BASE,            /**< \brief ����1 */
    INUM_UART1_3,                 /**< \brief ����1���жϱ�� */
    AMHW_ZSN700_UART_WORK_MODE_1, /**< \brief ���ڹ���ģʽ */

    AMHW_ZSN700_UART_PARITY_NO |  /**< \brief �޼���  MODE0/1:����У��  MODE2/3:����У��*/
    AMHW_ZSN700_UART_STOP_1_0_BIT,/**< \brief 1��ֹͣλ */

    115200,                       /**< \brief ���õĲ����� */

    0,                            /**< \brief �������ж� */

    {
        AM_FALSE,                 /**< \brief ���ܶ����ַ�Զ�ʶ�� */
        0x00,                     /**< \brief ��ַ0x00 */
        0x00,                     /**< \brief ��ַȫ�������� */
    },

    {
        AM_FALSE,                 /**< \brief �������� */
        0,                        /**< \brief CTS���ű�� */
        0,                        /**< \brief RTS���ű��*/
    },

    NULL,                         /**< \brief ʹ��RS485 */
    __zsn700_plfm_uart1_init,     /**< \brief UART1��ƽ̨��ʼ�� */
    __zsn700_plfm_uart1_deinit,   /**< \brief UART1��ƽ̨ȥ��ʼ�� */
};

/* �����ж�Դ������Ҫ�����豸��Ϣ */
am_zsn700_uart_dev_t  *__gp_uart1 = NULL;

/**< \brief ���崮��1 �豸 */
static am_zsn700_uart_dev_t  __g_uart1_dev;

/** \brief UART1ʵ����ʼ�������uart1��׼������ */
am_uart_handle_t am_zsn700_uart1_inst_init (void)
{
    __gp_uart1 = &__g_uart1_dev;
    return am_zsn700_uart_init(&__g_uart1_dev, &__g_uart1_devinfo);
}

/** \brief UART1ʵ�����ʼ�� */
void am_zsn700_uart1_inst_deinit (am_uart_handle_t handle)
{
    am_zsn700_uart_deinit((am_zsn700_uart_dev_t *)handle);
}

/** \brief ����2ƽ̨��ʼ�� */
static void __zsn700_plfm_uart2_init (void)
{
    am_clk_enable(CLK_UART2);

    am_gpio_pin_cfg(PIOC_3, PIOC_3_UART2_TXD | PIOC_3_OUT_PP );
    am_gpio_pin_cfg(PIOC_2, PIOC_2_UART2_RXD | PIOC_2_INPUT_FLOAT);
}

/** \brief �������2ƽ̨��ʼ�� */
static void __zsn700_plfm_uart2_deinit (void)
{
    am_clk_disable(CLK_UART2);

    am_gpio_pin_cfg(PIOC_3, PIOC_3_GPIO | PIOC_3_INPUT_PU);
    am_gpio_pin_cfg(PIOC_2, PIOC_2_GPIO | PIOC_2_INPUT_PU);
}

/** \brief ����2�豸��Ϣ */
static const am_zsn700_uart_devinfo_t __g_uart2_devinfo = {

    ZSN700_UART2_BASE,            /**< \brief ����2 */
    INUM_UART0_2,                 /**< \brief ����2���жϱ�� */
    AMHW_ZSN700_UART_WORK_MODE_1, /**< \brief ���ڹ���ģʽ */

    AMHW_ZSN700_UART_PARITY_NO |  /**< \brief �޼���  MODE0/1:����У��  MODE2/3:����У��*/
    AMHW_ZSN700_UART_STOP_1_0_BIT,/**< \brief 1��ֹͣλ */

    115200,                       /**< \brief ���õĲ����� */

    0,                            /**< \brief �������ж� */

    {
        AM_FALSE,                 /**< \brief ���ܶ����ַ�Զ�ʶ�� */
        0x00,                     /**< \brief ��ַ0x00 */
        0x00,                     /**< \brief ��ַȫ�������� */
    },

    {
        AM_FALSE,                 /**< \brief �������� */
        0,                        /**< \brief CTS���ű�� */
        0,                        /**< \brief RTS���ű��*/
    },

    NULL,                         /**< \brief ʹ��RS485 */
    __zsn700_plfm_uart2_init,     /**< \brief UART2��ƽ̨��ʼ�� */
    __zsn700_plfm_uart2_deinit,   /**< \brief UART2��ƽ̨ȥ��ʼ�� */
};

/* �����ж�Դ������Ҫ�����豸��Ϣ */
am_zsn700_uart_dev_t  *__gp_uart2 = NULL;

/**< \brief ���崮��2 �豸 */
static am_zsn700_uart_dev_t  __g_uart2_dev;

/** \brief UART2ʵ����ʼ�������uart2��׼������ */
am_uart_handle_t am_zsn700_uart2_inst_init (void)
{
    __gp_uart2 = &__g_uart2_dev;
    return am_zsn700_uart_init(&__g_uart2_dev, &__g_uart2_devinfo);
}

/** \brief UART2ʵ�����ʼ�� */
void am_zsn700_uart2_inst_deinit (am_uart_handle_t handle)
{
    am_zsn700_uart_deinit((am_zsn700_uart_dev_t *)handle);
}

/** \brief ����3ƽ̨��ʼ�� */
static void __zsn700_plfm_uart3_init (void)
{
    am_clk_enable(CLK_UART3);

    am_gpio_pin_cfg(PIOC_7, PIOC_7_UART3_TXD | PIOC_7_OUT_PP );
    am_gpio_pin_cfg(PIOC_6, PIOC_6_UART3_RXD | PIOC_6_INPUT_FLOAT);
}

/** \brief �������3ƽ̨��ʼ�� */
static void __zsn700_plfm_uart3_deinit (void)
{
    am_clk_disable(CLK_UART3);

    am_gpio_pin_cfg(PIOC_6, PIOC_6_GPIO | PIOC_6_INPUT_PU);
    am_gpio_pin_cfg(PIOC_7, PIOC_7_GPIO | PIOC_7_INPUT_PU);
}

/** \brief ����3�豸��Ϣ */
static const am_zsn700_uart_devinfo_t __g_uart3_devinfo = {

    ZSN700_UART3_BASE,            /**< \brief ����3 */
    INUM_UART1_3,                 /**< \brief ����3���жϱ�� */
    AMHW_ZSN700_UART_WORK_MODE_1, /**< \brief ���ڹ���ģʽ */

    AMHW_ZSN700_UART_PARITY_NO |  /**< \brief �޼���  MODE0/1:����У��  MODE2/3:����У��*/
    AMHW_ZSN700_UART_STOP_1_0_BIT,/**< \brief 1��ֹͣλ */

    115200,                       /**< \brief ���õĲ����� */

    0,                            /**< \brief �������ж� */

    {
        AM_FALSE,                 /**< \brief ���ܶ����ַ�Զ�ʶ�� */
        0x00,                     /**< \brief ��ַ0x00 */
        0x00,                     /**< \brief ��ַȫ�������� */
    },

    {
        AM_FALSE,                 /**< \brief �������� */
        0,                        /**< \brief CTS���ű�� */
        0,                        /**< \brief RTS���ű��*/
    },

    NULL,                         /**< \brief ʹ��RS485 */
    __zsn700_plfm_uart3_init,     /**< \brief UART3��ƽ̨��ʼ�� */
    __zsn700_plfm_uart3_deinit,   /**< \brief UART3��ƽ̨ȥ��ʼ�� */
};

/* �����ж�Դ������Ҫ�����豸��Ϣ */
am_zsn700_uart_dev_t  *__gp_uart3 = NULL;

/**< \brief ���崮��3 �豸 */
static am_zsn700_uart_dev_t  __g_uart3_dev;

/** \brief UART3ʵ����ʼ�������uart3��׼������ */
am_uart_handle_t am_zsn700_uart3_inst_init (void)
{
    __gp_uart3 = &__g_uart3_dev;
    return am_zsn700_uart_init(&__g_uart3_dev, &__g_uart3_devinfo);
}

/** \brief UART3ʵ�����ʼ�� */
void am_zsn700_uart3_inst_deinit (am_uart_handle_t handle)
{
    am_zsn700_uart_deinit((am_zsn700_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
