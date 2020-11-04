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
 * \brief STM32F103RBT6 USART �û������ļ�
 * \sa am_stm32f103rbt6l_hwconfig_usart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation
 * \endinternal
 */

#include "am_stm32f103rbt6.h"
#include "am_stm32f103rbt6_usart.h"
#include "amhw_stm32f103rbt6_gpio.h"
#include "amhw_stm32f103rbt6_rcc.h"
#include "amhw_stm32f103rbt6_usart.h"
#include "stm32f103rbt6_periph_map.h"
#include "stm32f103rbt6_pin.h"
#include "am_gpio.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_stm32f103rbt6_usart
 * \copydoc am_hwconf_stm32f103rbt6_usart.c
 * @{
 */

/** \brief ����1ƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_usart1_init (void)
{
    am_gpio_pin_cfg(PIOA_9,  PIOA_9_NO_REMAP);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_NO_REMAP);

    am_gpio_pin_cfg(PIOA_9,  PIOA_9_AF_PP | AM_GPIO_PULLUP | PIOA_9_SPEED_50MHz);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_INPUT_FLOAT );
}

/** \brief �������1ƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_usart1_deinit (void)
{
    am_clk_disable(CLK_USART1);

    am_gpio_pin_cfg(PIOA_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_10,AM_GPIO_INPUT);
}

/** \brief ����1�豸��Ϣ */
static const am_stm32f103rbt6_usart_devinfo_t __g_usart1_devinfo = {

    STM32F103RBT6_USART1_BASE,            /**< \brief ����1 */
    INUM_USART1,                   /**< \brief ����1���жϱ�� */
    CLK_USART1,                    /**< \brief ����1��ʱ�� */

    AMHW_STM32F103RBT6_USART_DATA_8BIT |  /**< \brief 8λ���� */
    AMHW_STM32F103RBT6_USART_PARITY_NO |  /**< \brief �޼��� */
    AMHW_STM32F103RBT6_USART_STOP_10_BIT, /**< \brief 1��ֹͣλ */

    115200,                       /**< \brief ���õĲ����� */

    0,                            /**< \brief �������ж� */

    NULL,                          /**< \brief USART1ʹ��RS485 */
    __stm32f103rbt6_plfm_usart1_init,     /**< \brief USART1��ƽ̨��ʼ�� */
    __stm32f103rbt6_plfm_usart1_deinit,   /**< \brief USART1��ƽ̨ȥ��ʼ�� */

    /* ���������ڹ������óɶ�Ӧģʽ�Ż���г�ʼ�� */
    {PIOA_8, PIOA_8_NO_REMAP | PIOA_8_AF_PP},             /**< \brief ck������ض��� */
    {PIOA_11, PIOA_11_NO_REMAP |  PIOA_11_INPUT_FLOAT},    /**< \brief cts������ض��� */
    {PIOA_12, PIOA_12_NO_REMAP | PIOA_12_AF_PP}           /**< \brief rts������ض��� */

};

/**< \brief ���崮��1 �豸 */
static am_stm32f103rbt6_usart_dev_t  __g_usart1_dev;

/** \brief USART1ʵ����ʼ�������usart1��׼������ */
am_uart_handle_t am_stm32f103rbt6_usart1_inst_init (void)
{
    return am_stm32f103rbt6_usart_init(&__g_usart1_dev, &__g_usart1_devinfo);
}

/** \brief USART1ʵ�����ʼ�� */
void am_stm32f103rbt6_usart1_inst_deinit (am_uart_handle_t handle)
{
    am_stm32f103rbt6_usart_deinit((am_stm32f103rbt6_usart_dev_t *)handle);
}

/** \brief ����2ƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_usart2_init (void)
{
    am_gpio_pin_cfg(PIOA_2, PIOA_2_NO_REMAP | PIOA_2_AF_PP );
    am_gpio_pin_cfg(PIOA_3, PIOA_3_NO_REMAP | PIOA_3_INPUT_FLOAT);
}

/** \brief �������2 ƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_usart2_deinit (void)
{

    /* �ر�USART2ʱ�� */
    am_clk_disable(CLK_USART2);

    am_gpio_pin_cfg(PIOA_3, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_2, AM_GPIO_INPUT);
}

/** \brief ����2 �豸��Ϣ */
static const am_stm32f103rbt6_usart_devinfo_t __g_usart2_devinfo = {

    STM32F103RBT6_USART2_BASE,              /**< \brief ����2 */
    INUM_USART2,                     /**< \brief ����2���жϱ�� */
    CLK_USART2,                     /**< \brief ����2��ʱ�� */

    AMHW_STM32F103RBT6_USART_DATA_8BIT |    /**< \brief 8λ���� */
    AMHW_STM32F103RBT6_USART_PARITY_NO |    /**< \brief �޼��� */
    AMHW_STM32F103RBT6_USART_STOP_10_BIT,   /**< \brief 1��ֹͣλ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief USART2ʹ��RS485 */
    __stm32f103rbt6_plfm_usart2_init,       /**< \brief USART2��ƽ̨��ʼ�� */
    __stm32f103rbt6_plfm_usart2_deinit,     /**< \brief USART2��ƽ̨ȥ��ʼ�� */

    /* ���������ڹ������óɶ�Ӧģʽ�Ż���г�ʼ�� */
    {PIOA_4, PIOA_4_NO_REMAP | PIOA_4_AF_PP},          /**< \brief ck������ض��� */
    {PIOA_0, PIOA_0_NO_REMAP | PIOA_0_INPUT_FLOAT},    /**< \brief cts������ض��� */
    {PIOA_1, PIOA_1_NO_REMAP | PIOA_1_AF_PP}           /**< \brief rts������ض��� */
};

/**< \brief ���崮��2�豸 */
static am_stm32f103rbt6_usart_dev_t  __g_usart2_dev;

/** \brief USART2ʵ����ʼ�������usart2��׼������ */
am_uart_handle_t am_stm32f103rbt6_usart2_inst_init (void)
{
    return am_stm32f103rbt6_usart_init(&__g_usart2_dev, &__g_usart2_devinfo);
}

/** \brief USART2ʵ�����ʼ�� */
void am_stm32f103rbt6_usart2_inst_deinit (am_uart_handle_t handle)
{
    am_stm32f103rbt6_usart_deinit((am_stm32f103rbt6_usart_dev_t *)handle);
}

/** \brief ����3ƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_usart3_init (void)
{
     am_gpio_pin_cfg(PIOB_10, PIOB_10_NO_REMAP | PIOB_10_AF_PP | PIOB_10_SPEED_10MHz);
     am_gpio_pin_cfg(PIOB_11, PIOB_11_NO_REMAP | PIOB_11_INPUT_FLOAT);
}

/** \brief �������3 ƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_usart3_deinit (void)
{
    am_clk_disable(CLK_USART3);

    am_gpio_pin_cfg(PIOB_10, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_11, AM_GPIO_INPUT);
}

/** \brief ����3 �豸��Ϣ */
static const am_stm32f103rbt6_usart_devinfo_t __g_usart3_devinfo = {

    STM32F103RBT6_USART3_BASE,              /**< \brief ����3 */
    INUM_USART3,                     /**< \brief ����2���жϱ�� */
    CLK_USART3,                     /**< \brief ����2��ʱ�� */

    AMHW_STM32F103RBT6_USART_DATA_8BIT |    /**< \brief 8λ���� */
    AMHW_STM32F103RBT6_USART_PARITY_NO |    /**< \brief �޼��� */
    AMHW_STM32F103RBT6_USART_STOP_10_BIT,     /**< \brief 1��ֹͣλ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief USART3ʹ��RS485 */
    __stm32f103rbt6_plfm_usart3_init,       /**< \brief USART3��ƽ̨��ʼ�� */
    __stm32f103rbt6_plfm_usart3_deinit,     /**< \brief USART3��ƽ̨ȥ��ʼ�� */

    /* ���������ڹ������óɶ�Ӧģʽ�Ż���г�ʼ�� */
    {PIOB_12, PIOB_12_NO_REMAP | PIOB_12_AF_PP},          /**< \brief ck������ض��� */
    {PIOB_13, PIOB_13_NO_REMAP | PIOB_13_INPUT_FLOAT},    /**< \brief cts������ض��� */
    {PIOB_14, PIOB_14_NO_REMAP | PIOB_14_AF_PP}           /**< \brief rts������ض��� */
};

/**< \brief ���崮��2�豸 */
static am_stm32f103rbt6_usart_dev_t  __g_usart3_dev;

/** \brief USART3ʵ����ʼ�������usart3��׼������ */
am_uart_handle_t am_stm32f103rbt6_usart3_inst_init (void)
{
    return am_stm32f103rbt6_usart_init(&__g_usart3_dev, &__g_usart3_devinfo);
}

/** \brief USART3ʵ�����ʼ�� */
void am_stm32f103rbt6_usart3_inst_deinit (am_uart_handle_t handle)
{
    am_stm32f103rbt6_usart_deinit((am_stm32f103rbt6_usart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
