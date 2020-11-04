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
 * \brief HC32F460 SDIOC �û������ļ�
 * \sa am_hwconf_hc32f460_sdioc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-29  cds, first implementation
 * \endinternal
 */

#include "am_hc32f460_sdioc.h"
#include "hw/amhw_hc32f460_sdioc.h"
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32f460_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_sdioc
 * \copydoc am_hwconf_hc32f460_sdioc.c
 * @{
 */

/** \brief SDIO ƽ̨��ʼ������ */
static void __hc32f460_sdioc1_plfm_init (void)
{

    am_gpio_pin_cfg(PIOC_8,  GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
    am_gpio_pin_cfg(PIOC_9,  GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
    am_gpio_pin_cfg(PIOC_10, GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
    am_gpio_pin_cfg(PIOC_11, GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
    am_gpio_pin_cfg(PIOC_12, GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
    am_gpio_pin_cfg(PIOD_2,  GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));

    am_clk_enable(CLK_SDIOC1);
}

/** \brief ���SDIO ƽ̨��ʼ������ */
static void __hc32f460_sdioc1_plfm_deinit (void)
{
    am_clk_disable(CLK_SDIOC1);
}

/**
 * \brief SDIOC1 �豸��Ϣ
 */
static const am_hc32f460_sdioc_devinfo_t __g_sdioc1_devinfo = {

    HC32F460_SDIOC1_BASE,               /**< \brief �Ĵ������ַ */
    1,
    INUM_SDIOC1,                        /**< \brief �жϱ�� */
    CLK_SDIOC1,                         /**< \brief ʱ��IDֵ */

    AMHW_HC32F460_SDIO_SPEED_MODE_LOW,  /**< \brief SDIO����ģʽ */
    __hc32f460_sdioc1_plfm_init,        /**< \brief ƽ̨��ʼ�� */
    __hc32f460_sdioc1_plfm_deinit       /**< \brief ƽ̨ȥ��ʼ�� */
};

am_hc32f460_sdioc_dev_t __g_sdioc1_dev;          /**< \brief  �豸ʵ�� */
static am_sdio_handle_t  __g_sdio_handle = NULL; /**< \brief  ��׼������ */

/** \brief SDIO ʵ����ʼ�������SDIO��׼������ */
am_sdio_handle_t am_hc32f460_sdioc1_inst_init (void)
{
    if (NULL == __g_sdio_handle) {
        __g_sdio_handle = am_hc32f460_sdioc_init(&__g_sdioc1_dev, &__g_sdioc1_devinfo);
    }

    return __g_sdio_handle;
}

/** \brief SDIOC ʵ�����ʼ�� */
void am_hc32f460_sdioc1_inst_deinit (am_sdio_handle_t handle)
{
    am_hc32f460_sdioc_deinit(handle);
    __g_sdio_handle = NULL;
}




/** \brief SDIO ƽ̨��ʼ������ */
static void __hc32f460_sdioc2_plfm_init (void)
{

//    am_gpio_pin_cfg(PIOC_8,  GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
//    am_gpio_pin_cfg(PIOC_9,  GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
//    am_gpio_pin_cfg(PIOC_10, GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
//    am_gpio_pin_cfg(PIOC_11, GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
//    am_gpio_pin_cfg(PIOC_12, GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));
//    am_gpio_pin_cfg(PIOD_2,  GPIO_AFIO(AMHW_HC32F460_AFIO_SDIO));

    am_clk_enable(CLK_SDIOC2);

}

/** \brief ���SDIO ƽ̨��ʼ������ */
static void __hc32f460_sdioc2_plfm_deinit (void)
{
    am_clk_disable(CLK_SDIOC2);
}

/**
 * \brief SDIOC2 �豸��Ϣ
 */
static const am_hc32f460_sdioc_devinfo_t __g_sdioc2_devinfo = {

    HC32F460_SDIOC2_BASE,               /**< \brief �Ĵ������ַ */
    2,
    INUM_SDIOC2,                        /**< \brief �жϱ�� */
    CLK_SDIOC2,                         /**< \brief ʱ��IDֵ */

    AMHW_HC32F460_SDIO_SPEED_MODE_LOW,  /** \brief SDIO����ģʽ */
    __hc32f460_sdioc2_plfm_init,        /**< \brief ƽ̨��ʼ�� */
    __hc32f460_sdioc2_plfm_deinit       /**< \brief ƽ̨ȥ��ʼ�� */
};

am_hc32f460_sdioc_dev_t __g_sdioc2_dev;   /**< \brief  �豸ʵ�� */
static am_sdio_handle_t  __g_sdio2_handle = NULL; /**< \brief  ��׼������ */

/** \brief SDIO ʵ����ʼ�������SDIO��׼������ */
am_sdio_handle_t am_hc32f460_sdioc2_inst_init (void)
{
    if (NULL == __g_sdio2_handle) {
        __g_sdio2_handle = am_hc32f460_sdioc_init(&__g_sdioc2_dev, &__g_sdioc2_devinfo);
    }

    return __g_sdio2_handle;
}

/** \brief SDIOC ʵ�����ʼ�� */
void am_hc32f460_sdioc2_inst_deinit (am_sdio_handle_t handle)
{
    am_hc32f460_sdioc_deinit(handle);
    __g_sdio2_handle = NULL;
}


/** @} */

/* end of file */
