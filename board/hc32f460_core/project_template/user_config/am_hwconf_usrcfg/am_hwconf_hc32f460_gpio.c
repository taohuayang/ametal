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
 * \brief HC32F460 GPIO �û������ļ���
 * \sa am_hwconf_hc32f460_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-12  zcb, first implementation
 * \endinternal
 */

#include <am_hc32f460_gpio.h>
#include <hc32f460_pin.h>
#include "am_gpio.h"
#include "am_clk.h"
#include "hc32f460_regbase.h"
#include "hc32f460_inum.h"


/**
 * \addtogroup am_if_src_hwconf_hc32f460_gpio
 * \copydoc am_hwconf_hc32f460_gpio.c
 * @{
 */

/** \brief GPIOƽ̨��ʼ�� */
void __hc32f460_plfm_gpio_init (void)
{

}

/** \brief GPIOƽ̨���ʼ�� */
void __hc32f460_plfm_gpio_deinit (void)
{

}

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_hc32f460_gpio_trigger_info __g_gpio_triginfos[PIN_INT_MAX];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t __g_gpio_infomap[PIN_INT_MAX];

/** \brief GPIO�豸��Ϣ */
const am_hc32f460_gpio_devinfo_t __g_gpio_devinfo = {
    HC32F460_GPIO_BASE,   /**< \brief GPIO�������Ĵ������ַ */
    0,                    /**< \brief EXTI�������Ĵ������ַ */
    0,                    /**< \brief AFIO�������Ĵ������ַ */

    {
        INUM_PORT_EIRQ0,
        INUM_PORT_EIRQ1,
        INUM_PORT_EIRQ2,
        INUM_PORT_EIRQ3,
        INUM_PORT_EIRQ4,
        INUM_PORT_EIRQ5,
        INUM_PORT_EIRQ6,
        INUM_PORT_EIRQ7,
        INUM_PORT_EIRQ8,
        INUM_PORT_EIRQ9,
        INUM_PORT_EIRQ10,
        INUM_PORT_EIRQ11,
        INUM_PORT_EIRQ12,
        INUM_PORT_EIRQ13,
        INUM_PORT_EIRQ14,
        INUM_PORT_EIRQ15,
    },

    PIN_NUM,                       /**< \brief GPIO PIN���� */
    PIN_INT_MAX,                   /**< \brief GPIOʹ�õ�����ⲿ�ж��߱��+1 */

    &__g_gpio_infomap[0],          /**< \brief GPIO �����ⲿ�¼���Ϣ */
    &__g_gpio_triginfos[0],        /**< \brief GPIO PIN������Ϣ */

    __hc32f460_plfm_gpio_init,     /**< \brief GPIO ƽ̨��ʼ�� */
    __hc32f460_plfm_gpio_deinit    /**< \brief GPIO ƽ̨ȥ��ʼ�� */
};

/** \brief GPIO�豸ʵ�� */
am_hc32f460_gpio_dev_t __g_gpio_dev;

/** \brief GPIO ʵ����ʼ�� */
int am_hc32f460_gpio_inst_init (void)
{
    return am_hc32f460_gpio_init(&__g_gpio_dev, &__g_gpio_devinfo);
}

/** \brief GPIO ʵ�����ʼ�� */
void am_hc32f460_gpio_inst_deinit (void)
{
    am_hc32f460_gpio_deinit();
}

/**
 * @}
 */

/* end of file */
