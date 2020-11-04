/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.hc32.cn/
*******************************************************************************/

/**
 * \file
 * \brief HC32 SPI DMA �û������ļ�
 * \sa am_hwconf_hc32_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-18  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32_spi_dma.h"
#include "am_gpio.h"
#include "hw/amhw_hc32_spi.h"
#include "am_clk.h"
#include "am_hc32.h"
#include "hc32_dma_chan.h"
#include "am_hc32_spi_dma.h"
/**
 * \addtogroup am_if_src_hwconf_hc32_spi_dma
 * \copydoc am_hwconf_hc32_spi_dma.c
 * @{
 */
/** \brief SPI0 ƽ̨��ʼ�� */
static void __hc32_plfm_spi0_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_3,  PIOB_3_SPI0_SCK   | PIOB_3_OUT_PP);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_SPI0_MOSI | PIOA_12_OUT_PP);
    am_gpio_pin_cfg(PIOA_11, PIOA_11_SPI0_MISO | PIOA_11_INPUT_PU);

    am_clk_enable(CLK_SPI0);
}

/** \brief ��� SPI0 ƽ̨��ʼ�� */
static void __hc32_plfm_spi0_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOB_3,  PIOB_3_INPUT_PU);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_INPUT_PU);
    am_gpio_pin_cfg(PIOA_11, PIOA_11_INPUT_PU);

    am_clk_disable(CLK_SPI0);
}

/** \brief SPI0 �豸��Ϣ */
static const  struct am_hc32_spi_dma_devinfo  __g_spi0_dma_devinfo = {
    HC32_SPI0_BASE,                        /**< \brief SPI0�Ĵ���ָ�� */
    CLK_SPI0,                                /**< \brief ʱ��ID�� */
    INUM_SPI0,                               /**< \brief SPI0�жϺ� */
    DMA_CHAN_1,
    DMA_CHAN_2,
    __hc32_plfm_spi0_dma_init,             /**< \brief SPI0ƽ̨��ʼ������ */
    __hc32_plfm_spi0_dma_deinit            /**< \brief SPI0ƽ̨���ʼ������ */
};
/** \brief SPI0 �豸ʵ�� */
static am_hc32_spi_dma_dev_t __g_spi0_dma_dev;


/** \brief SPI0 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_hc32_spi0_dma_inst_init (void)
{
    return am_hc32_spi_dma_init(&__g_spi0_dma_dev, &__g_spi0_dma_devinfo);
}

/** \brief SPI0 ʵ�����ʼ�� */
void am_hc32_spi0_dma_inst_deinit (am_spi_handle_t handle)
{
    am_hc32_spi_dma_deinit(handle);
}

/** \brief SPI1 ƽ̨��ʼ�� */
static void __hc32_plfm_spi1_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_SPI1_SCK  | PIOB_10_OUT_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_SPI1_MISO  | PIOC_2_INPUT_PU);

    am_clk_enable(CLK_SPI1);
}

/** \brief ��� SPI1 ƽ̨��ʼ�� */
static void __hc32_plfm_spi1_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_INPUT_PU);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_INPUT_PU);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_INPUT_PU);

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 �豸��Ϣ */
static const  struct am_hc32_spi_dma_devinfo  __g_spi1_dma_devinfo = {
    HC32_SPI1_BASE,                        /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                                /**< \brief ʱ��ID�� */
    INUM_SPI1,                               /**< \brief SPI1�жϺ� */
    DMA_CHAN_1,
    DMA_CHAN_2,
    __hc32_plfm_spi1_dma_init,             /**< \brief SPI1ƽ̨��ʼ������ */
    __hc32_plfm_spi1_dma_deinit            /**< \brief SPI1ƽ̨���ʼ������ */
};
/** \brief SPI1 �豸ʵ�� */
static am_hc32_spi_dma_dev_t __g_spi1_dma_dev;


/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_hc32_spi1_dma_inst_init (void)
{
    return am_hc32_spi_dma_init(&__g_spi1_dma_dev, &__g_spi1_dma_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_hc32_spi1_dma_inst_deinit (am_spi_handle_t handle)
{
    am_hc32_spi_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */
