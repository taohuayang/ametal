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
 * \brief HC32F460 QSPI �û������ļ�
 * \sa am_hc32f460_hwconfig_qspi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  cds, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_qspi.h"
#include "hw/amhw_hc32f460_qspi.h"


/**
 * \addtogroup am_if_src_hwconf_hc32f460_uart
 * \copydoc am_hwconf_hc32f460_uart.c
 * @{
 */

/** \brief QSPIƽ̨��ʼ�� */
static void __hc32f460_plfm_qspi_init(void)
{
    am_clk_enable(CLK_QSPI);
    am_gpio_pin_cfg(PIOC_6, GPIO_AFIO(AMHW_HC32F460_AFIO_QSPI));
    am_gpio_pin_cfg(PIOC_7, GPIO_AFIO(AMHW_HC32F460_AFIO_QSPI));
    am_gpio_pin_cfg(PIOD_8, GPIO_AFIO(AMHW_HC32F460_AFIO_QSPI));
    am_gpio_pin_cfg(PIOD_9, GPIO_AFIO(AMHW_HC32F460_AFIO_QSPI));
}

/** \brief QSPIƽ̨���ʼ�� */
static void __hc32f460_plfm_qspi_deinit(void)
{
    am_clk_disable(CLK_QSPI);
    am_gpio_pin_cfg(PIOC_6, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOC_7, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_8, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_9, AM_GPIO_INPUT);
}

/** \brief QSPI�豸��Ϣ */
static const am_hc32f460_qspi_devinfo_t __g_qspi_devinfo = {


    HC32F460_QSPI_BASE,                    /**< \brief QSPI */
    CLK_QSPI,                              /**< \brief ʱ�ӱ�� */
    INUM_QSPI,                             /**< \brief �жϱ�� */

    AMHW_HC32F460_QSPI_HCLK_DIV4,          /**< \brief ��׼ʱ��Ϊ4��HCLKʱ�� */
    AMHW_HC32F460_QSPI_PROTOCOL_EXTEND,    /**< \brief ���ݽ��ս׶β�����չʽSPIЭ�� */
    AMHW_HC32F460_QSPI_PROTOCOL_EXTEND,    /**< \brief ��ַ���ͽ׶β�����չʽSPIЭ�� */
    AMHW_HC32F460_QSPI_PROTOCOL_EXTEND,    /**< \brief ָ��ͽ׶β�����չʽSPIЭ�� */
    AMHW_HC32F460_QSPI_SPI_MODE0,          /**< \brief SPI Э�����ģʽ0 */
    AMHW_HC32F460_QSPI_READ_MODE_STANDARD, /**< \brief ��׼�� */

    __hc32f460_plfm_qspi_init,             /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_qspi_deinit            /**< \brief ƽ̨���ʼ������ */

};

/**< \brief ����QSPI�豸 */
am_hc32f460_qspi_dev_t __g_qspi_dev;


/** \brief QSPIʵ����ʼ�� */
am_qspi_handle_t am_hc32f460_qspi_inst_init(void)
{
    return am_hc32f460_qspi_init(&__g_qspi_dev, &__g_qspi_devinfo);
}

/** \brief QSPIʵ�����ʼ�� */
void am_hc32f460_qspi_inst_deinit(am_qspi_handle_t handle)
{
    am_hc32f460_qspi_deinit(handle);
}


/**
 * @}
 */

/* end of file */
