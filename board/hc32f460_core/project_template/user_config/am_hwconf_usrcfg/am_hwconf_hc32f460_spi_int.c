/*******************************************************************************

                                AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief HC32F460 SPI INT �û������ļ�
 * \sa am_hwconf_hc32f460_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-25  cds, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32f460_spi_int.h"
#include "am_gpio.h"
#include "hw/amhw_hc32f460_spi.h"
#include "am_clk.h"
#include "am_hc32f460.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_spi_int
 * \copydoc am_hwconf_hc32f460_spi_int.c
 * @{
 */
/*********************************SPI3*****************************************/
/* SPI3 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI3_PIN_SCK    PIOE_0
#define __SPI3_PIN_MOSI   PIOE_2
#define __SPI3_PIN_MISO   PIOE_3
/** \brief SPI3 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi3_int_init (void)
{
    am_gpio_pin_cfg(__SPI3_PIN_SCK,   GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_SCK));
    am_gpio_pin_cfg(__SPI3_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MOSI));
    am_gpio_pin_cfg(__SPI3_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MISO));

    am_clk_enable(CLK_SPI3);
}

/** \brief ���SPI3 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi3_int_deinit (void)
{
    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(__SPI3_PIN_SCK,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI3_PIN_MOSI,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI3_PIN_MISO,  GPIO_AFIO(AM_GPIO_INPUT));

    am_clk_disable(CLK_SPI3);
}

/** \brief SPI3 �豸��Ϣ */
const  struct am_hc32f460_spi_int_devinfo  __g_spi3_int_devinfo = {
    HC32F460_SPI3_BASE,                        /**< \brief SPI3�Ĵ���ָ�� */
    CLK_SPI3,                                  /**< \brief ʱ��ID�� */
    INUM_SPI3,                                 /**< \brief SPI3�жϺ� */
    GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MOSI),   /**< \brief SPI3���ñ�ʶ */
    3,                                         /**< \brief SPI3�豸ID */
    __SPI3_PIN_MOSI,                           /**< \brief MOSI���ź� */
    __hc32f460_plfm_spi3_int_init,             /**< \brief SPI3ƽ̨��ʼ������ */
    __hc32f460_plfm_spi3_int_deinit            /**< \brief SPI3ƽ̨���ʼ������ */
};

/** \brief SPI3 �豸ʵ�� */
am_hc32f460_spi_int_dev_t __g_spi3_int_dev;

/** \brief SPI3 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_hc32f460_spi3_int_inst_init (void)
{
    return am_hc32f460_spi_int_init(&__g_spi3_int_dev, &__g_spi3_int_devinfo);
}

/** \brief SPI3 ʵ�����ʼ�� */
void am_hcc32f460_spi3_int_inst_deinit (am_spi_handle_t handle)
{
    am_hc32f460_spi_int_deinit(handle);
}
/*********************************SPI4*****************************************/
/* SPI4 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI4_PIN_SCK    PIOE_0
#define __SPI4_PIN_MOSI   PIOE_2
#define __SPI4_PIN_MISO   PIOE_3

/** \brief SPI4 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi4_int_init (void)
{
    am_gpio_pin_cfg(__SPI4_PIN_SCK,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI4_SCK));
    am_gpio_pin_cfg(__SPI4_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI4_MOSI));
    am_gpio_pin_cfg(__SPI4_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI4_MISO));

    am_clk_enable(CLK_SPI4);
}

/** \brief ���SPI4 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi4_int_deinit (void)
{
    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(__SPI4_PIN_SCK,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI4_PIN_MOSI,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI4_PIN_MISO,  GPIO_AFIO(AM_GPIO_INPUT));

    am_clk_disable(CLK_SPI4);
}

/** \brief SPI4 �豸��Ϣ */
const  struct am_hc32f460_spi_int_devinfo  __g_spi4_int_devinfo = {
    HC32F460_SPI4_BASE,                        /**< \brief SPI4�Ĵ���ָ�� */
    CLK_SPI4,                                  /**< \brief ʱ��ID�� */
    INUM_SPI4,                                 /**< \brief SPI4�жϺ� */
    GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MOSI),   /**< \brief SPI4���ñ�ʶ */
    4,                                         /**< \brief SPI4�豸ID */
    __SPI4_PIN_MOSI,                           /**< \brief MOSI���ź� */
    __hc32f460_plfm_spi4_int_init,             /**< \brief SPI4ƽ̨��ʼ������ */
    __hc32f460_plfm_spi4_int_deinit            /**< \brief SPI4ƽ̨���ʼ������ */
};

/** \brief SPI4 �豸ʵ�� */
am_hc32f460_spi_int_dev_t __g_spi4_int_dev;

/** \brief SPI4 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_hc32f460_spi4_int_inst_init (void)
{
    return am_hc32f460_spi_int_init(&__g_spi4_int_dev, &__g_spi4_int_devinfo);
}

/** \brief SPI4 ʵ�����ʼ�� */
void am_hcc32f460_spi4_int_inst_deinit (am_spi_handle_t handle)
{
    am_hc32f460_spi_int_deinit(handle);
}

/*********************************SPI2*****************************************/
/* SPI2 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI2_PIN_SCK    PIOC_0
#define __SPI2_PIN_MOSI   PIOC_2
#define __SPI2_PIN_MISO   PIOC_3

/** \brief SPI2 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi2_int_init (void)
{
    am_gpio_pin_cfg(__SPI2_PIN_SCK,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI2_SCK));
    am_gpio_pin_cfg(__SPI2_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI2_MOSI));
    am_gpio_pin_cfg(__SPI2_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI2_MISO));

    am_clk_enable(CLK_SPI2);
}

/** \brief ���SPI2 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi2_int_deinit (void)
{
    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(__SPI2_PIN_SCK,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI2_PIN_MOSI,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI2_PIN_MISO,  GPIO_AFIO(AM_GPIO_INPUT));

    am_clk_disable(CLK_SPI2);
}

/** \brief SPI2 �豸��Ϣ */
const  struct am_hc32f460_spi_int_devinfo  __g_spi2_int_devinfo = {
    HC32F460_SPI2_BASE,                        /**< \brief SPI2�Ĵ���ָ�� */
    CLK_SPI2,                                  /**< \brief ʱ��ID�� */
    INUM_SPI2,                                 /**< \brief SPI2�жϺ� */
    GPIO_AFIO(AMHW_HC32F460_AFIO_SPI2_MOSI),   /**< \brief SPI2���ñ�ʶ */
    2,                                         /**< \brief SPI2�豸ID */
    __SPI2_PIN_MOSI,                           /**< \brief MOSI���ź� */
    __hc32f460_plfm_spi2_int_init,             /**< \brief SPI2ƽ̨��ʼ������ */
    __hc32f460_plfm_spi2_int_deinit            /**< \brief SPI2ƽ̨���ʼ������ */
};

/** \brief SPI2 �豸ʵ�� */
am_hc32f460_spi_int_dev_t __g_spi2_int_dev;

/** \brief SPI2 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_hc32f460_spi2_int_inst_init (void)
{
    return am_hc32f460_spi_int_init(&__g_spi2_int_dev, &__g_spi2_int_devinfo);
}

/** \brief SPI2 ʵ�����ʼ�� */
void am_hcc32f460_spi2_int_inst_deinit (am_spi_handle_t handle)
{
    am_hc32f460_spi_int_deinit(handle);
}
/*********************************SPI1*****************************************/
/* SPI1 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI1_PIN_SCK    PIOC_3
#define __SPI1_PIN_MOSI   PIOC_4
#define __SPI1_PIN_MISO   PIOC_5

/** \brief SPI1 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi1_int_init (void)
{
    am_gpio_pin_cfg(__SPI1_PIN_SCK,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI1_SCK));
    am_gpio_pin_cfg(__SPI1_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI1_MOSI));
    am_gpio_pin_cfg(__SPI1_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI1_MISO));

    am_clk_enable(CLK_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi1_int_deinit (void)
{
    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(__SPI1_PIN_SCK,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI1_PIN_MOSI,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(__SPI1_PIN_MISO,  GPIO_AFIO(AM_GPIO_INPUT));

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 �豸��Ϣ */
const  struct am_hc32f460_spi_int_devinfo  __g_spi1_int_devinfo = {
    HC32F460_SPI1_BASE,                        /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                                  /**< \brief ʱ��ID�� */
    INUM_SPI1,                                 /**< \brief SPI1�жϺ� */
    GPIO_AFIO(AMHW_HC32F460_AFIO_SPI1_MOSI),   /**< \brief SPI1���ñ�ʶ */
    1,                                         /**< \brief SPI1�豸ID */
    __SPI1_PIN_MOSI,                           /**< \brief MOSI���ź� */
    __hc32f460_plfm_spi1_int_init,             /**< \brief SPI1ƽ̨��ʼ������ */
    __hc32f460_plfm_spi1_int_deinit            /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
am_hc32f460_spi_int_dev_t __g_spi1_int_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_hc32f460_spi1_int_inst_init (void)
{
    return am_hc32f460_spi_int_init(&__g_spi1_int_dev, &__g_spi1_int_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_hcc32f460_spi1_int_inst_deinit (am_spi_handle_t handle)
{
    am_hc32f460_spi_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
