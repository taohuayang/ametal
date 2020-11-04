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
 * \brief ZSN700 SPI �û������ļ�
 * \sa am_hwconf_zsn700_spi_poll.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-17  zp, first implementation.
 * \endinternal
 */

#include "am_zsn700.h"
#include "ametal.h"
#include "am_zsn700_spi_poll.h"
#include "am_gpio.h"
#include "hw/amhw_zsn700_spi.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zsn700_spi_poll
 * \copydoc am_hwconf_zsn700_spi_poll.c
 * @{
 */
/** \brief SPI1 ƽ̨��ʼ�� */
static void __zsn700_plfm_spi1_poll_init (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_SPI1_SCK  | PIOB_10_OUT_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_SPI1_MISO  | PIOC_2_INPUT_PU);

    am_clk_enable(CLK_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __zsn700_plfm_spi1_poll_deinit (void)
{

    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOB_10, PIOB_10_INPUT_PU);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_INPUT_PU);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_INPUT_PU);

    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 �豸��Ϣ
 */
const  struct am_zsn700_spi_poll_devinfo  __g_spi1_poll_devinfo = {
    ZSN700_SPI1_BASE,                       /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                               /**< \brief ʱ��ID�� */
    __zsn700_plfm_spi1_poll_init,           /**< \brief SPI1ƽ̨��ʼ������ */
    __zsn700_plfm_spi1_poll_deinit          /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_zsn700_spi_poll_dev_t __g_spi1_poll_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zsn700_spi1_poll_inst_init (void)
{
    return am_zsn700_spi_poll_init(&__g_spi1_poll_dev, &__g_spi1_poll_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_zsn700_spi1_poll_inst_deinit (am_spi_handle_t handle)
{
    am_zsn700_spi_poll_deinit(handle);
}

/**
 * @}
 */

/* end of file */
