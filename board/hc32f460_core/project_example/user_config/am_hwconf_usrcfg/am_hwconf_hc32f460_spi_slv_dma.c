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
 * \brief HC32F460 SPI SLV DMA �û������ļ�
 * \sa am_hwconf_hc32f460_spi_slv_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-01  cds, first implementation
 * \endinternal
 */

#include "am_hc32f460.h"
#include "ametal.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "hw/amhw_hc32f460_spi.h"
#include "am_hc32f460_spi_slv_dma.h"
/**
 * \addtogroup am_if_src_hwconf_hc32f460_spi_slv_dma
 * \copydoc am_hwconf_hc32f460_spi_slv_dma.c
 * @{
 */
/*********************************SPI3*****************************************/
/* SPI3 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI3_PIN_SCK    PIOE_0
#define __SPI3_PIN_MOSI   PIOE_2
#define __SPI3_PIN_MISO   PIOE_3
#define __SPI3_PIN_NSS    PIOE_1
/** \brief SPI3 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi3_slv_dma_init (void)
{
    am_gpio_pin_cfg(__SPI3_PIN_SCK,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_SCK));
    am_gpio_pin_cfg(__SPI3_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MOSI));
    am_gpio_pin_cfg(__SPI3_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MISO));

    am_clk_enable(CLK_SPI3);
    am_clk_enable(CLK_PTDIS);
}

/** \brief ��� SPI3 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi3_slv_dma_deinit (void)
{
    am_gpio_pin_cfg(__SPI3_PIN_SCK, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI3_PIN_MOSI, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI3_PIN_MISO, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI3);
}

/**
 * \brief SPI3 �豸��Ϣ
 */
static const struct am_hc32f460_spi_slv_dma_devinfo  __g_spi3_slv_dma_devinfo = {
    HC32F460_SPI3_BASE,                 /**< \brief SPI3�Ĵ���ָ�� */
    CLK_SPI3,                           /**< \brief ʱ��ID�� */
    3,
    1,
    DMA_CHAN_1,
    DMA_CHAN_2,
    __SPI3_PIN_NSS,                     /**< \brief SPI3��NSS���ţ�ֻ��ʹ��Ĭ�ϵ�NSS����*/
    __hc32f460_plfm_spi3_slv_dma_init,  /**< \brief SPI3ƽ̨��ʼ������ */
    __hc32f460_plfm_spi3_slv_dma_deinit /**< \brief SPI3ƽ̨���ʼ������ */
};

/** \brief SPI3 �豸ʵ�� */
static am_hc32f460_spi_slv_dma_dev_t __g_spi3_slv_dma_dev;


/** \brief SPI3 ʵ����ʼ�������SPI��׼������ */
am_spi_slv_handle_t am_hc32f460_spi3_slv_dma_inst_init (void)
{
    return am_hc32f460_spi_slv_dma_init(&__g_spi3_slv_dma_dev,
                                        &__g_spi3_slv_dma_devinfo);
}

/** \brief SPI3 ʵ�����ʼ�� */
void am_hc32f460_spi3_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_hc32f460_spi_slv_dma_deinit(handle);
}

/*********************************SPI4*****************************************/
/* SPI4 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI4_PIN_SCK    PIOE_0
#define __SPI4_PIN_MOSI   PIOE_2
#define __SPI4_PIN_MISO   PIOE_3
#define __SPI4_PIN_NSS    PIOE_1
/** \brief SPI3 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi4_slv_dma_init (void)
{
    am_gpio_pin_cfg(__SPI4_PIN_SCK,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI4_SCK));
    am_gpio_pin_cfg(__SPI4_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI4_MOSI));
    am_gpio_pin_cfg(__SPI4_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI4_MISO));

    am_clk_enable(CLK_SPI4);
    am_clk_enable(CLK_PTDIS);
}

/** \brief ��� SPI4 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi4_slv_dma_deinit (void)
{
    am_gpio_pin_cfg(__SPI4_PIN_SCK, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI4_PIN_MOSI, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI4_PIN_MISO, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI4);
}

/**
 * \brief SPI4 �豸��Ϣ
 */
static const struct am_hc32f460_spi_slv_dma_devinfo  __g_spi4_slv_dma_devinfo = {
    HC32F460_SPI4_BASE,                 /**< \brief SPI4�Ĵ���ָ�� */
    CLK_SPI4,                           /**< \brief ʱ��ID�� */
    4,                                  /**< \brief SPI�豸ID�� */
    1,                                  /**< \brief DMA�豸ID�� */
    DMA_CHAN_1,                         /**< \brief DMA����ͨ���� */
    DMA_CHAN_2,                         /**< \brief DMA����ͨ���� */
    __SPI4_PIN_NSS,                     /**< \brief SPI4��NSS���ţ�ֻ��ʹ��Ĭ�ϵ�NSS����*/
    __hc32f460_plfm_spi4_slv_dma_init,  /**< \brief SPI4ƽ̨��ʼ������ */
    __hc32f460_plfm_spi4_slv_dma_deinit /**< \brief SPI4ƽ̨���ʼ������ */
};

/** \brief SPI4 �豸ʵ�� */
static am_hc32f460_spi_slv_dma_dev_t __g_spi4_slv_dma_dev;


/** \brief SPI4 ʵ����ʼ�������SPI��׼������ */
am_spi_slv_handle_t am_hc32f460_spi4_slv_dma_inst_init (void)
{
    return am_hc32f460_spi_slv_dma_init(&__g_spi4_slv_dma_dev,
                                        &__g_spi4_slv_dma_devinfo);
}

/** \brief SPI4 ʵ�����ʼ�� */
void am_hc32f460_spi4_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_hc32f460_spi_slv_dma_deinit(handle);
}


/*********************************SPI2*****************************************/
/* SPI2 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI2_PIN_SCK    PIOC_0
#define __SPI2_PIN_MOSI   PIOC_2
#define __SPI2_PIN_MISO   PIOC_3
#define __SPI2_PIN_NSS    PIOC_1
/** \brief SPI2 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi2_slv_dma_init (void)
{
    am_gpio_pin_cfg(__SPI2_PIN_SCK,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI2_SCK));
    am_gpio_pin_cfg(__SPI2_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI2_MOSI));
    am_gpio_pin_cfg(__SPI2_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI2_MISO));

    am_clk_enable(CLK_SPI2);
    am_clk_enable(CLK_PTDIS);
}

/** \brief ��� SPI2 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi2_slv_dma_deinit (void)
{
    am_gpio_pin_cfg(__SPI2_PIN_SCK, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI2_PIN_MOSI, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI2_PIN_MISO, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}

/**
 * \brief SPI2 �豸��Ϣ
 */
static const struct am_hc32f460_spi_slv_dma_devinfo  __g_spi2_slv_dma_devinfo = {
    HC32F460_SPI2_BASE,                 /**< \brief SPI2�Ĵ���ָ�� */
    CLK_SPI2,                           /**< \brief ʱ��ID�� */
    2,                                  /**< \brief SPI�豸ID�� */
    1,                                  /**< \brief DMA�豸ID�� */
    DMA_CHAN_1,                         /**< \brief DMA����ͨ���� */
    DMA_CHAN_2,                         /**< \brief DMA����ͨ���� */
    __SPI2_PIN_NSS,                     /**< \brief SPI2��NSS���ţ�ֻ��ʹ��Ĭ�ϵ�NSS����*/
    __hc32f460_plfm_spi2_slv_dma_init,  /**< \brief SPI2ƽ̨��ʼ������ */
    __hc32f460_plfm_spi2_slv_dma_deinit /**< \brief SPI2ƽ̨���ʼ������ */
};

/** \brief SPI2 �豸ʵ�� */
static am_hc32f460_spi_slv_dma_dev_t __g_spi2_slv_dma_dev;


/** \brief SPI2 ʵ����ʼ�������SPI��׼������ */
am_spi_slv_handle_t am_hc32f460_spi2_slv_dma_inst_init (void)
{
    return am_hc32f460_spi_slv_dma_init(&__g_spi2_slv_dma_dev,
                                        &__g_spi2_slv_dma_devinfo);
}

/** \brief SPI2 ʵ�����ʼ�� */
void am_hc32f460_spi2_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_hc32f460_spi_slv_dma_deinit(handle);
}

/*********************************SPI1*****************************************/
/* SPI1 ���ţ��û�������Լ�ʵ��ʹ�������޸�*/
#define __SPI1_PIN_SCK    PIOC_0
#define __SPI1_PIN_MOSI   PIOC_2
#define __SPI1_PIN_MISO   PIOC_3
#define __SPI1_PIN_NSS    PIOC_1
/** \brief SPI1 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi1_slv_dma_init (void)
{
    am_gpio_pin_cfg(__SPI1_PIN_SCK,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI1_SCK));
    am_gpio_pin_cfg(__SPI1_PIN_MOSI,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI1_MOSI));
    am_gpio_pin_cfg(__SPI1_PIN_MISO,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI1_MISO));

    am_clk_enable(CLK_SPI1);
    am_clk_enable(CLK_PTDIS);
}

/** \brief ��� SPI1 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi1_slv_dma_deinit (void)
{
    am_gpio_pin_cfg(__SPI1_PIN_SCK, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI1_PIN_MOSI, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI1_PIN_MISO, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 �豸��Ϣ
 */
static const struct am_hc32f460_spi_slv_dma_devinfo  __g_spi1_slv_dma_devinfo = {
    HC32F460_SPI1_BASE,                 /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                           /**< \brief ʱ��ID�� */
    1,                                  /**< \brief SPI�豸ID�� */
    1,                                  /**< \brief DMA�豸ID�� */
    DMA_CHAN_1,                         /**< \brief DMA����ͨ���� */
    DMA_CHAN_2,                         /**< \brief DMA����ͨ���� */
    __SPI1_PIN_NSS,                     /**< \brief SPI1��NSS���ţ�ֻ��ʹ��Ĭ�ϵ�NSS����*/
    __hc32f460_plfm_spi1_slv_dma_init,  /**< \brief SPI1ƽ̨��ʼ������ */
    __hc32f460_plfm_spi1_slv_dma_deinit /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_hc32f460_spi_slv_dma_dev_t __g_spi1_slv_dma_dev;


/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_slv_handle_t am_hc32f460_spi1_slv_dma_inst_init (void)
{
    return am_hc32f460_spi_slv_dma_init(&__g_spi1_slv_dma_dev,
                                        &__g_spi1_slv_dma_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_hc32f460_spi1_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_hc32f460_spi_slv_dma_deinit(handle);
}


/**
 * @}
 */

/* end of file */
