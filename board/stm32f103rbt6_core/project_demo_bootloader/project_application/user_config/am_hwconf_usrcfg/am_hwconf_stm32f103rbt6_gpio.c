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
 * \brief STM32F103RBT6 GPIO �û������ļ���
 * \sa am_hwconf_stm32f103rbt6_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-12  zcb, first implementation
 * \endinternal
 */

#include "am_stm32f103rbt6.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_stm32f103rbt6_clk.h"
#include "am_stm32f103rbt6_gpio.h"
#include "amhw_stm32f103rbt6_afio.h"
#include "amhw_stm32f103rbt6_gpio.h"

/**
 * \addtogroup am_if_src_hwconf_stm32f103rbt6_gpio
 * \copydoc am_hwconf_stm32f103rbt6_gpio.c
 * @{
 */

/** \brief GPIOƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_gpio_init (void)
{
    am_clk_enable(CLK_IOPA);
    am_clk_enable(CLK_IOPB);
    am_clk_enable(CLK_IOPC);
    am_clk_enable(CLK_IOPD);
    am_clk_enable(CLK_AFIO);

    am_stm32f103rbt6_clk_reset(CLK_IOPA);
    am_stm32f103rbt6_clk_reset(CLK_IOPB);
    am_stm32f103rbt6_clk_reset(CLK_IOPC);
    am_stm32f103rbt6_clk_reset(CLK_IOPD);
    am_stm32f103rbt6_clk_reset(CLK_AFIO);
}

/** \brief GPIOƽ̨���ʼ�� */
void __stm32f103rbt6_plfm_gpio_deinit (void)
{
    am_stm32f103rbt6_clk_reset(CLK_IOPA);
    am_stm32f103rbt6_clk_reset(CLK_IOPB);
    am_stm32f103rbt6_clk_reset(CLK_IOPC);
    am_stm32f103rbt6_clk_reset(CLK_IOPD);
    am_stm32f103rbt6_clk_reset(CLK_AFIO);

    am_clk_disable(CLK_IOPA);
    am_clk_disable(CLK_IOPB);
    am_clk_disable(CLK_IOPC);
    am_clk_disable(CLK_IOPD);
    am_clk_disable(CLK_AFIO);
}

/** \brief ������ӳ����Ϣ */
static amhw_stm32f103rbt6_afio_remap_peripheral_t __g_pin_remap[PIN_NUM];

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_stm32f103rbt6_gpio_trigger_info __g_gpio_triginfos[PIN_INT_MAX];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t __g_gpio_infomap[PIN_INT_MAX];

/** \brief GPIO�豸��Ϣ */
const am_stm32f103rbt6_gpio_devinfo_t __g_gpio_devinfo = {
    STM32F103RBT6_GPIO_BASE,            /**< \brief GPIO�������Ĵ������ַ */
    STM32F103RBT6_EXTI_BASE,            /**< \brief EXTI�������Ĵ������ַ */
    STM32F103RBT6_AFIO_BASE,            /**< \brief AFIO�������Ĵ������ַ */

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

    __stm32f103rbt6_plfm_gpio_init,       /**< \brief GPIO ƽ̨��ʼ�� */
    __stm32f103rbt6_plfm_gpio_deinit      /**< \brief GPIO ƽ̨ȥ��ʼ�� */
};

/** \brief GPIO�豸ʵ�� */
am_stm32f103rbt6_gpio_dev_t __g_gpio_dev;

/** \brief GPIO ʵ����ʼ�� */
int am_stm32f103rbt6_gpio_inst_init (void)
{
    return am_stm32f103rbt6_gpio_init(&__g_gpio_dev, &__g_gpio_devinfo);
}

/** \brief GPIO ʵ�����ʼ�� */
void am_stm32f103rbt6_gpio_inst_deinit (void)
{
    am_stm32f103rbt6_gpio_deinit();
}

/**
 * @}
 */

/* end of file */
