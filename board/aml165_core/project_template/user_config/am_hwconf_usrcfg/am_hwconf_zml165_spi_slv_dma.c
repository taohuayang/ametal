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
 * \brief ZML165 SPI ���豸�û������ļ�
 * \sa am_hwconf_zml165_spi_slv_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-12-07  vir, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zml165.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zml165_spi_slv_dma.h"
#include "hw/amhw_zlg_spi.h"

/**
 * \addtogroup am_if_src_hwconf_zml165_spi_slv_dma
 * \copydoc am_hwconf_zml165_spi_slv_dma.c
 * @{
 */

/** \brief SPI1 ���豸ƽ̨��ʼ�� */
static void __zml165_spi1_slv_dma_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_3, PIOB_3_SPI1_SCK  | PIOB_3_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_4, PIOB_4_SPI1_MISO | PIOB_4_AF_PP);
    am_gpio_pin_cfg(PIOB_5, PIOB_5_SPI1_MOSI | PIOB_5_INPUT_FLOAT);

    am_clk_enable(CLK_SPI1);
}

/** \brief ��� SPI1 ���豸ƽ̨��ʼ�� */
static void __zml165_spi1_slv_dma_plfm_deinit (void)
{
    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 ���豸�豸��Ϣ
 */
const  struct am_zml165_spi_slv_dma_devinfo __g_spi1_slv_devinfo = {
    ZML165_SPI1_BASE,                      /* SPI1 �Ĵ���ָ�� */
    CLK_SPI1,                              /* ʱ�� ID �� */
    DMA_CHAN_SPI1_TX,
    DMA_CHAN_SPI1_RX,
    PIOA_4,
    __zml165_spi1_slv_dma_plfm_init,       /* SPI1 ƽ̨��ʼ������ */
    __zml165_spi1_slv_dma_plfm_deinit      /* SPI1 ƽ̨���ʼ������ */
};

/** \brief SPI1 �ӻ��豸ʵ�� */
static am_zlg_spi_slv_dma_dev_t __g_spi1_slv_dev;

/** \brief SPI1 �ӻ�ʵ����ʼ������� SPI �ӻ���׼������ */
am_spi_slv_handle_t am_zml165_spi1_slv_dma_inst_init (void)
{
    return am_zlg_spi_slv_dma_init(&__g_spi1_slv_dev, &__g_spi1_slv_devinfo);
}

/** \brief SPI1 ���豸ʵ�����ʼ�� */
void am_zml165_spi1_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_zlg_spi_slv_dma_deinit(handle);
}
/**
 * @}
 */

/* end of file */
