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
 * \brief ZSN700 I2C0 �û������ļ�
 * \sa am_hwconf_zsn700_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_zsn700.h"
#include "am_zlg_i2c.h"
#include "am_zsn700_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zsn700_i2c
 * \copydoc am_hwconf_zsn700_i2c.c
 * @{
 */

/** \brief I2C0 ���߻ָ����� */
static void __zsn700_i2c0_bus_clean (void)
{
    uint8_t i;

    am_gpio_pin_cfg(PIOA_9,  AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_HIGH);
    am_gpio_pin_cfg(PIOA_10, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    if (am_gpio_get(PIOA_10) != 1) {
        for (i = 0; i < 9; i++) {
            am_gpio_set(PIOA_9, 0);
            am_gpio_set(PIOA_9, 1);
        }
    }

    am_gpio_pin_cfg(PIOA_9,  PIOA_9_I2C0_SCL  | PIOA_9_OUT_OD);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_I2C0_SDA | PIOA_10_OUT_OD);
}



/**
 * \brief I2C0 ƽ̨��ʼ������
 */
am_local void __zsn700_i2c0_plfm_init (void)
{
    am_gpio_pin_cfg(PIOA_9,  PIOA_9_I2C0_SCL  | PIOA_9_OUT_OD);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_I2C0_SDA | PIOA_10_OUT_OD);

    am_clk_enable(CLK_I2C0);
}

/**
 * \brief I2C0 ƽ̨���ʼ������
 */
am_local void __zsn700_i2c0_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C0);
}

/** \brief I2C0 �������ʲ������� */
#define __BUS_SPEED_I2C0     (50000)

/** \brief I2C0 �豸��Ϣ */
am_local am_const am_zlg_i2c_devinfo_t __g_zsn700_i2c0_devinfo = {
    ZSN700_I2C0_BASE,           /* I2C0 �Ĵ������ַ */
    CLK_I2C0,                   /* I2C0 ʱ�Ӻ� */
    INUM_I2C0,                  /* I2C0 �жϺ� */
    __BUS_SPEED_I2C0,           /* I2C0 �������� */
    20,                         /* ��ʱʱ�� */
    __zsn700_i2c0_bus_clean,    /* ���߻ָ����� */
    __zsn700_i2c0_plfm_init,    /* ƽ̨��ʼ������ */
    __zsn700_i2c0_plfm_deinit   /* ƽ̨���ʼ������ */
};

/** \brief I2C0 �豸ʵ�� */
am_local am_zlg_i2c_dev_t __g_zsn700_i2c0_dev;

/**
 * \brief I2C0 ʵ����ʼ��
 */
am_i2c_handle_t am_zsn700_i2c0_inst_init (void)
{
    return am_zlg_i2c_init(&__g_zsn700_i2c0_dev, &__g_zsn700_i2c0_devinfo);
}

/**
 * \brief I2C0 ʵ�����ʼ��
 */
void am_zsn700_i2c0_inst_deinit (am_i2c_handle_t handle)
{
    am_zlg_i2c_deinit(handle);
}

/******************************************************************************/

/** \brief I2C1 ���߻ָ����� */
static void __zsn700_i2c1_bus_clean (void)
{
    uint8_t i;

    am_gpio_pin_cfg(PIOA_11, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_HIGH);
    am_gpio_pin_cfg(PIOA_12, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    if (am_gpio_get(PIOA_12) != 1) {
        for (i = 0; i < 9; i++) {
            am_gpio_set(PIOA_11, 0);
            am_gpio_set(PIOA_11, 1);
        }
    }

    am_gpio_pin_cfg(PIOA_11, PIOA_11_I2C1_SCL | PIOA_11_OUT_OD);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_I2C1_SDA | PIOA_12_OUT_OD);
}

/**
 * \brief I2C1 ƽ̨��ʼ������
 */
am_local void __zsn700_i2c1_plfm_init (void)
{
    am_gpio_pin_cfg(PIOA_11, PIOA_11_I2C1_SCL | PIOA_11_OUT_OD);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_I2C1_SDA | PIOA_12_OUT_OD);

    am_clk_enable(CLK_I2C1);
}

/**
 * \brief I2C1 ƽ̨���ʼ������
 */
am_local void __zsn700_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C1);
}

/** \brief I2C1 �������ʲ������� */
#define __BUS_SPEED_I2C1     (50000)

/** \brief I2C1 �豸��Ϣ */
am_local am_const am_zlg_i2c_devinfo_t __g_zsn700_i2c1_devinfo = {
    ZSN700_I2C1_BASE,           /* I2C1 �Ĵ������ַ */
    CLK_I2C1,                   /* I2C1 ʱ�Ӻ� */
    INUM_I2C1,                  /* I2C1 �жϺ� */
    __BUS_SPEED_I2C1,           /* I2C1 �������� */
    20,                         /* ��ʱʱ�� */
    __zsn700_i2c1_bus_clean,    /* ���߻ָ����� */
    __zsn700_i2c1_plfm_init,    /* ƽ̨��ʼ������ */
    __zsn700_i2c1_plfm_deinit   /* ƽ̨���ʼ������ */
};

/** \brief I2C1 �豸ʵ�� */
am_local am_zlg_i2c_dev_t __g_zsn700_i2c1_dev;

/**
 * \brief I2C1 ʵ����ʼ��
 */
am_i2c_handle_t am_zsn700_i2c1_inst_init (void)
{
    return am_zlg_i2c_init(&__g_zsn700_i2c1_dev, &__g_zsn700_i2c1_devinfo);
}

/**
 * \brief I2C1 ʵ�����ʼ��
 */
void am_zsn700_i2c1_inst_deinit (am_i2c_handle_t handle)
{
    am_zlg_i2c_deinit(handle);
}

/**
 * @}
 */

/* end of file */
