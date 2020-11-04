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
 * \brief HC32 GPIO �û������ļ���
 * \sa am_hwconf_hc32_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-09  zp, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32.h"
#include "am_hc32_clk.h"
#include "am_hc32_gpio.h"
#include "hw/amhw_hc32_gpio.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_gpio
 * \copydoc am_hwconf_hc32_gpio.c
 * @{
 */

/** \brief GPIOƽ̨��ʼ�� */
void __hc32_plfm_gpio_init (void)
{
    am_clk_enable(CLK_GPIO);

    am_hc32_clk_reset(CLK_GPIO);
}

/** \brief GPIOƽ̨���ʼ�� */
void __hc32_plfm_gpio_deinit (void)
{
    am_hc32_clk_reset(CLK_GPIO);

    am_clk_disable(CLK_GPIO);
}

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_hc32_gpio_trigger_info __g_gpio_triginfos[PIN_INT_MAX];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t __g_gpio_infomap[PIN_INT_MAX];

/** \brief GPIO�豸��Ϣ */
const am_hc32_gpio_devinfo_t __g_gpio_devinfo = {
    HC32_PORT0_BASE,              /**< \brief GPIO�������Ĵ������ַ */

    {
        INUM_PORTA,
        INUM_PORTB,
        INUM_PORTC_E,
        INUM_PORTD_F,
    },

    PIN_INT_MAX,                   /**< \brief GPIOʹ�õ�����ⲿ�ж��߱��+1 */

    &__g_gpio_infomap[0],          /**< \brief GPIO �����ⲿ�¼���Ϣ */
    &__g_gpio_triginfos[0],        /**< \brief GPIO PIN������Ϣ */

    __hc32_plfm_gpio_init,       /**< \brief GPIO ƽ̨��ʼ�� */
    __hc32_plfm_gpio_deinit      /**< \brief GPIO ƽ̨ȥ��ʼ�� */
};

/** \brief GPIO�豸ʵ�� */
am_hc32_gpio_dev_t __g_gpio_dev;

/** \brief GPIO ʵ����ʼ�� */
int am_hc32_gpio_inst_init (void)
{
    return am_hc32_gpio_init(&__g_gpio_dev, &__g_gpio_devinfo);
}

/** \brief GPIO ʵ�����ʼ�� */
void am_hc32_gpio_inst_deinit (void)
{
    am_hc32_gpio_deinit();
}

/**
 * @}
 */

/* end of file */
