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
 * \brief HK32F103RBT6 SPI DMA �û������ļ�
 * \sa am_hwconf_hk32f103rbt6_spi_slv_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-22  fra, first implementation
 * \endinternal
 */

#include "am_hk32f103rbt6.h"
#include "hk32f103rbt6_dma_chan.h"
#include "ametal.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "amhw_hk32f103rbt6_spi.h"
#include "am_hk32f103rbt6_spi_slv_dma.h"
/**
 * \addtogroup am_if_src_hwconf_hk32f103rbt6_spi_slv_dma
 * \copydoc am_hwconf_hk32f103rbt6_spi_slv_dma.c
 * @{
 */

/** \brief SPI1 ƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_spi1_slv_dma_init (void)
{
    am_gpio_pin_cfg(PIOA_5, PIOA_5_SPI1_SCK_REMAP0  | PIOA_5_AF_PP);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_SPI1_MISO_REMAP0 | PIOA_6_AF_PP);
    am_gpio_pin_cfg(PIOA_7, PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_INPUT_FLOAT);

    am_clk_enable(CLK_SPI1);
}

/** \brief ��� SPI1 ƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_spi1_slv_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOA_5, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_6, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_7, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI1);
}


/**
 * \brief SPI1 �豸��Ϣ
 */
static const struct am_hk32f103rbt6_spi_slv_dma_devinfo  __g_spi1_slv_dma_devinfo = {
    HK32F103RBT6_SPI1_BASE,                           /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                                   /**< \brief ʱ��ID�� */
    DMA_CHAN_SPI1_TX,
    DMA_CHAN_SPI1_RX,
    PIOA_4,                                    /* SPI1��NSS���ţ�ֻ��ʹ��Ĭ�ϵ�NSS����*/
    __hk32f103rbt6_plfm_spi1_slv_dma_init,            /**< \brief SPI1ƽ̨��ʼ������ */
    __hk32f103rbt6_plfm_spi1_slv_dma_deinit           /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_hk32f103rbt6_spi_slv_dma_dev_t __g_spi1_slv_dma_dev;


/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_slv_handle_t am_hk32f103rbt6_spi1_slv_dma_inst_init (void)
{
    return am_hk32f103rbt6_spi_slv_dma_init(&__g_spi1_slv_dma_dev,
                                      &__g_spi1_slv_dma_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_hk32f103rbt6_spi1_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_hk32f103rbt6_spi_slv_dma_deinit(handle);
}

/** \brief SPI2 ƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_spi2_slv_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK  | PIOB_13_AF_PP);
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_AF_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI | PIOB_15_INPUT_FLOAT);

    am_clk_enable(CLK_SPI2);
}

/** \brief ���SPI2 ƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_spi2_slv_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOB_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_14, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_15, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}

/**
 * \brief SPI2 �豸��Ϣ
 */
static const struct am_hk32f103rbt6_spi_slv_dma_devinfo  __g_spi2_slv_dma_devinfo = {
    HK32F103RBT6_SPI2_BASE,                           /**< \brief SPI2�Ĵ���ָ�� */
    CLK_SPI2,                                   /**< \brief ʱ��ID�� */
    DMA_CHAN_SPI2_TX,
    DMA_CHAN_SPI2_RX,
    PIOB_12,                                    /* SPI2��NSS���ţ�ֻ��ʹ��Ĭ�ϵ�NSS����*/
    __hk32f103rbt6_plfm_spi2_slv_dma_init,            /**< \brief SPI2ƽ̨��ʼ������ */
    __hk32f103rbt6_plfm_spi2_slv_dma_deinit           /**< \brief SPI2ƽ̨���ʼ������ */
};

/** \brief SPI2 �豸ʵ�� */
static am_hk32f103rbt6_spi_slv_dma_dev_t __g_spi2_slv_dma_dev;

/** \brief SPI2 ʵ����ʼ�������SPI��׼������ */
am_spi_slv_handle_t am_hk32f103rbt6_spi2_slv_dma_inst_init (void)
{
    return am_hk32f103rbt6_spi_slv_dma_init(&__g_spi2_slv_dma_dev,
                                      &__g_spi2_slv_dma_devinfo);
}


/** \brief SPI2 ʵ�����ʼ�� */
void am_hk32f103rbt6_spi2_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_hk32f103rbt6_spi_slv_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */
