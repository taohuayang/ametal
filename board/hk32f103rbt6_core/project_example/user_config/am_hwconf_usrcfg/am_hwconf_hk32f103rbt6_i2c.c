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
 * \brief HK32F103RBT6 I2C �û������ļ�
 * \sa am_hwconf_hk32f103rbt6_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-5  fra, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hk32f103rbt6.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hk32f103rbt6_i2c.h"
#include "am_hk32f103rbt6_clk.h"
#include "amhw_hk32f103rbt6_i2c.h"

/**
 * \addtogroup am_if_src_hwconf_hk32f103rbt6_i2c
 * \copydoc am_hwconf_hk32f103rbt6_i2c.c
 * @{
 */

/** \brief I2C1 ���߻ָ����� */
static void __hk32f103rbt6_i2c1_bus_clean (void)
{
    uint8_t i;

    am_gpio_pin_cfg(PIOB_6, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_HIGH);
    am_gpio_pin_cfg(PIOB_7, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    if (am_gpio_get(PIOB_7) != 1) {
        for (i = 0; i < 9; i++) {
            am_gpio_set(PIOB_6, 0);
            am_gpio_set(PIOB_6, 1);
        }
    }

    am_gpio_pin_cfg(PIOB_6, PIOB_6_I2C1_SCL_REMAP0 | PIOB_6_AF_OD);
    am_gpio_pin_cfg(PIOB_7, PIOB_7_I2C1_SDA_REMAP0 | PIOB_7_AF_OD);
}
/** \brief I2C1 ƽ̨��ʼ������ */
static void __hk32f103rbt6_i2c1_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_6, PIOB_6_I2C1_SCL_REMAP0 | PIOB_6_AF_OD|PIOB_6_SPEED_50MHz);
    am_gpio_pin_cfg(PIOB_7, PIOB_7_I2C1_SDA_REMAP0 | PIOB_7_AF_OD|PIOB_7_SPEED_2MHz);

    am_clk_enable(CLK_I2C1);
    am_hk32f103rbt6_clk_reset(CLK_I2C1);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
static void __hk32f103rbt6_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C1);

    am_gpio_pin_cfg(PIOB_6, PIOB_6_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_7, PIOB_7_INPUT_FLOAT);
}

/**
 * \brief I2C1 �豸��Ϣ
 */
static const am_hk32f103rbt6_i2c_devinfo_t __g_i2c1_devinfo = {

    HK32F103RBT6_I2C1_BASE,                   /**< \brief I2C1�Ĵ������ַ */
    CLK_I2C1,                           /**< \brief ʱ��IDֵ */
    INUM_I2C1_EV,                       /**< \brief I2C1 �жϱ�� */

    100000,                             /**< \brief I2C ���� */
    10,                                 /**< \brief ��ʱֵ0 */

    __hk32f103rbt6_i2c1_bus_clean,               /**< \brief ���߻ָ����� */
    __hk32f103rbt6_i2c1_plfm_init,               /**< \brief ƽ̨��ʼ�� */
    __hk32f103rbt6_i2c1_plfm_deinit              /**< \brief ƽ̨ȥ��ʼ�� */
};

static am_hk32f103rbt6_i2c_dev_t __g_i2c1_dev; /**< \brief I2C1 �豸ʵ�� */

/** \brief I2C1 ʵ����ʼ�������I2C��׼������ */
am_i2c_handle_t am_hk32f103rbt6_i2c1_inst_init (void)
{
    return am_hk32f103rbt6_i2c_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief I2C1 ʵ�����ʼ�� */
void am_hk32f103rbt6_i2c1_inst_deinit (am_i2c_handle_t handle)
{
    am_hk32f103rbt6_i2c_deinit(handle);
}

/** \brief I2C2 ���߻ָ����� */
static void __hk32f103rbt6_i2c2_bus_clean (void)
{
    uint8_t i;

    am_gpio_pin_cfg(PIOB_10, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_HIGH);
    am_gpio_pin_cfg(PIOB_11, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    if (am_gpio_get(PIOB_11) != 1) {
        for (i = 0; i < 9; i++) {
            am_gpio_set(PIOB_10, 0);
            am_gpio_set(PIOB_10, 1);
        }
    }

    am_gpio_pin_cfg(PIOB_10, PIOB_10_I2C2_SCL | PIOB_10_AF_OD | PIOB_10_SPEED_2MHz );
    am_gpio_pin_cfg(PIOB_11, PIOB_11_I2C2_SDA | PIOB_11_AF_OD | PIOB_11_SPEED_2MHz);
}

/** \brief I2C2 ƽ̨��ʼ������ */
static void __hk32f103rbt6_i2c2_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_I2C2_SCL | PIOB_10_AF_OD | PIOB_10_SPEED_50MHz );
    am_gpio_pin_cfg(PIOB_11, PIOB_11_I2C2_SDA | PIOB_11_AF_OD | PIOB_11_SPEED_2MHz);

    am_clk_enable(CLK_I2C2);
    am_hk32f103rbt6_clk_reset(CLK_I2C2);
}

/** \brief ���I2C2 ƽ̨��ʼ������ */
static void __hk32f103rbt6_i2c2_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C2);
}

/**
 * \brief I2C2 �豸��Ϣ
 */
static const am_hk32f103rbt6_i2c_devinfo_t __g_i2c2_devinfo = {

    HK32F103RBT6_I2C2_BASE,                   /**< \brief I2C2�Ĵ������ַ */
    CLK_I2C2,                           /**< \brief ʱ��IDֵ */
    INUM_I2C2_EV,                       /**< \brief I2C2 �жϱ�� */

    400000,                             /**< \brief I2C ���� */
    10,                                 /**< \brief ��ʱֵ0 */

    __hk32f103rbt6_i2c2_bus_clean,               /**< \brief ���߻ָ����� */
    __hk32f103rbt6_i2c2_plfm_init,               /**< \brief ƽ̨��ʼ�� */
    __hk32f103rbt6_i2c2_plfm_deinit              /**< \brief ƽ̨ȥ��ʼ�� */
};

static am_hk32f103rbt6_i2c_dev_t __g_i2c2_dev; /**< \brief I2C2 �豸ʵ�� */

/** \brief I2C2 ʵ����ʼ�������I2C��׼������ */
am_i2c_handle_t am_hk32f103rbt6_i2c2_inst_init (void)
{
    return am_hk32f103rbt6_i2c_init(&__g_i2c2_dev, &__g_i2c2_devinfo);
}

/** \brief I2C2 ʵ�����ʼ�� */
void am_hk32f103rbt6_i2c2_inst_deinit (am_i2c_handle_t handle)
{
    am_hk32f103rbt6_i2c_deinit(handle);
}

/** @} */

/* end of file */
