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
 * \brief ZLG116 SPI �û������ļ�
 * \sa am_hwconf_zlg116_spi_int.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-10-23  ari, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg116.h"
#include "am_zlg_spi_int.h"
#include "am_gpio.h"
#include "hw/amhw_zlg_spi.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_spi_int
 * \copydoc am_hwconf_zlg116_spi_int.c
 * @{
 */

/** \brief SPI1 ƽ̨��ʼ�� */
static void __zlg_plfm_spi1_int_init (void)
{
    am_gpio_pin_cfg(PIOA_5, PIOA_5_SPI1_SCK  | PIOA_5_AF_PP);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_SPI1_MISO | PIOA_6_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOA_7, PIOA_7_SPI1_MOSI | PIOA_7_AF_PP);

    am_clk_enable(CLK_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __zlg_plfm_spi1_int_deinit (void)
{

    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOA_5, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_6, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_7, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 �豸��Ϣ
 */
const  struct am_zlg_spi_int_devinfo  __g_spi1_int_devinfo = {
    ZLG116_SPI1_BASE,                   /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                           /**< \brief ʱ��ID�� */
    INUM_SPI1,                          /**< \brief SPI1�жϺ� */
    PIOA_7_SPI1_MOSI | PIOA_7_AF_PP,    /**< \brief SPI1���ñ�ʶ */
    PIOA_7,                             /**< \brief MOSI���ź� */
    __zlg_plfm_spi1_int_init,           /**< \brief SPI1ƽ̨��ʼ������ */
    __zlg_plfm_spi1_int_deinit          /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_zlg_spi_int_dev_t __g_spi1_int_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zlg116_spi1_int_inst_init (void)
{
    return am_zlg_spi_int_init(&__g_spi1_int_dev, &__g_spi1_int_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_zlg116_spi1_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
