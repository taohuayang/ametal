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
 * \brief ZLG237 GPIO �û������ļ���
 * \sa am_hwconf_zlg237_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-12  zcb, first implementation
 * \endinternal
 */

#include "am_zlg237.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg237_clk.h"
#include "am_zlg237_gpio.h"
#include "amhw_zlg237_afio.h"
#include "amhw_zlg237_gpio.h"

/**
 * \addtogroup am_if_src_hwconf_zlg237_gpio
 * \copydoc am_hwconf_zlg237_gpio.c
 * @{
 */

/** \brief GPIOƽ̨��ʼ�� */
void __zlg237_plfm_gpio_init (void)
{
    am_clk_enable(CLK_IOPA);
    am_clk_enable(CLK_IOPB);
    am_clk_enable(CLK_IOPC);
    am_clk_enable(CLK_IOPD);
    am_clk_enable(CLK_AFIO);

    am_zlg237_clk_reset(CLK_IOPA);
    am_zlg237_clk_reset(CLK_IOPB);
    am_zlg237_clk_reset(CLK_IOPC);
    am_zlg237_clk_reset(CLK_IOPD);
    am_zlg237_clk_reset(CLK_AFIO);
}

/** \brief GPIOƽ̨���ʼ�� */
void __zlg237_plfm_gpio_deinit (void)
{
    am_zlg237_clk_reset(CLK_IOPA);
    am_zlg237_clk_reset(CLK_IOPB);
    am_zlg237_clk_reset(CLK_IOPC);
    am_zlg237_clk_reset(CLK_IOPD);
    am_zlg237_clk_reset(CLK_AFIO);

    am_clk_disable(CLK_IOPA);
    am_clk_disable(CLK_IOPB);
    am_clk_disable(CLK_IOPC);
    am_clk_disable(CLK_IOPD);
    am_clk_disable(CLK_AFIO);
}

/** \brief ������ӳ����Ϣ */
static amhw_zlg237_afio_remap_peripheral_t __g_pin_remap[PIN_NUM];

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_zlg237_gpio_trigger_info __g_gpio_triginfos[PIN_INT_MAX];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t __g_gpio_infomap[PIN_INT_MAX];

/** \brief GPIO�豸��Ϣ */
const am_zlg237_gpio_devinfo_t __g_gpio_devinfo = {
    ZLG237_GPIO_BASE,            /**< \brief GPIO�������Ĵ������ַ */
    ZLG237_EXTI_BASE,            /**< \brief EXTI�������Ĵ������ַ */
    ZLG237_AFIO_BASE,            /**< \brief AFIO�������Ĵ������ַ */

    {
        INUM_EXTI0,
        INUM_EXTI1,
        INUM_EXTI2,
        INUM_EXTI3,
        INUM_EXTI4,
        INUM_EXTI9_5,
        INUM_EXTI15_10,
    },

    PIN_NUM,                       /**< \brief GPIO PIN���� */
    PIN_INT_MAX,                   /**< \brief GPIOʹ�õ�����ⲿ�ж��߱��+1 */

    &__g_gpio_infomap[0],          /**< \brief GPIO �����ⲿ�¼���Ϣ */
    &__g_pin_remap[0],             /**< \brief GPIO PIN��ӳ����Ϣ */
    &__g_gpio_triginfos[0],        /**< \brief GPIO PIN������Ϣ */

    __zlg237_plfm_gpio_init,       /**< \brief GPIO ƽ̨��ʼ�� */
    __zlg237_plfm_gpio_deinit      /**< \brief GPIO ƽ̨ȥ��ʼ�� */
};

/** \brief GPIO�豸ʵ�� */
am_zlg237_gpio_dev_t __g_gpio_dev;

/** \brief GPIO ʵ����ʼ�� */
int am_zlg237_gpio_inst_init (void)
{
    return am_zlg237_gpio_init(&__g_gpio_dev, &__g_gpio_devinfo);
}

/** \brief GPIO ʵ�����ʼ�� */
void am_zlg237_gpio_inst_deinit (void)
{
    am_zlg237_gpio_deinit();
}

/**
 * @}
 */

/* end of file */
