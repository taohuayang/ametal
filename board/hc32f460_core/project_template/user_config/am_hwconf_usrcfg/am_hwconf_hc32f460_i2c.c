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
 * \brief HC32F460 I2C1 �û������ļ�
 * \sa am_hwconf_hc32f460_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_i2c.h"
#include "am_hc32f460_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_i2c
 * \copydoc am_hwconf_hc32f460_i2c.c
 * @{
 */

/** \brief I2C1 ���߻ָ����� */
static void __hc32f460_i2c1_bus_clean (void)
{
    uint8_t i;

    am_gpio_pin_cfg(PIOC_4, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_HIGH);
    am_gpio_pin_cfg(PIOC_5, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    if (am_gpio_get(PIOC_5) != 1) {
        for (i = 0; i < 9; i++) {
            am_gpio_set(PIOC_4, 0);
            am_gpio_set(PIOC_4, 1);
        }
    }

    am_gpio_pin_cfg(PIOC_4, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SCL));
    am_gpio_pin_cfg(PIOC_5, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SDA));
}



/**
 * \brief I2C1 ƽ̨��ʼ������
 */
am_local void __hc32f460_i2c1_plfm_init (void)
{
    am_gpio_pin_cfg(PIOC_4, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SCL));
    am_gpio_pin_cfg(PIOC_5, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SDA));
    am_clk_enable(CLK_IIC1);
}

/**
 * \brief I2C1 ƽ̨���ʼ������
 */
am_local void __hc32f460_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_IIC1);
}

/** \brief I2C1 �������ʲ������� */
#define __BUS_SPEED_I2C1     (400000)

/** \brief I2C1 �豸��Ϣ */
am_local am_const am_hc32f460_i2c_devinfo_t __g_hc32f460_i2c1_devinfo = {
    HC32F460_I2C1_BASE,           /**< \brief I2C1 �Ĵ������ַ */
    CLK_IIC1,                     /**< \brief I2C1 ʱ�Ӻ� */
    INUM_I2C1,                    /**< \brief I2C1 �жϺ� */
    __BUS_SPEED_I2C1,             /**< \brief I2C1 �������� */
    10,                           /**< \brief ��ʱʱ�� */
    __hc32f460_i2c1_bus_clean,    /**< \brief ���߻ָ����� */
    __hc32f460_i2c1_plfm_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f460_i2c1_plfm_deinit   /**< \brief ƽ̨���ʼ������ */
};

/** \brief I2C1 �豸ʵ�� */
am_hc32f460_i2c_dev_t __g_hc32f460_i2c1_dev;

/**
 * \brief I2C1 ʵ����ʼ��
 */
am_i2c_handle_t am_hc32f460_i2c1_inst_init (void)
{
    return am_hc32f460_i2c_init(&__g_hc32f460_i2c1_dev, &__g_hc32f460_i2c1_devinfo);
}

/**
 * \brief I2C1 ʵ�����ʼ��
 */
void am_hc32f460_i2c_inst1_deinit (am_i2c_handle_t handle)
{
    am_hc32f460_i2c_deinit(handle);
}

/******************************************************************************/

/** \brief I2C2 ���߻ָ����� */
static void __hc32f460_i2c2_bus_clean (void)
{
    uint8_t i;

    am_gpio_pin_cfg(PIOD_0, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_HIGH);
    am_gpio_pin_cfg(PIOD_1, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    if (am_gpio_get(PIOD_1) != 1) {
        for (i = 0; i < 9; i++) {
            am_gpio_set(PIOD_0, 0);
            am_gpio_set(PIOD_0, 1);
        }
    }

    am_gpio_pin_cfg(PIOD_0, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C2_SCL));
    am_gpio_pin_cfg(PIOD_1, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C2_SDA));
}



/**
 * \brief I2C2 ƽ̨��ʼ������
 */
am_local void __hc32f460_i2c2_plfm_init (void)
{
    am_gpio_pin_cfg(PIOD_0, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C2_SCL));
    am_gpio_pin_cfg(PIOD_1, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C2_SDA));
    am_clk_enable(CLK_IIC2);
}

/**
 * \brief I2C2 ƽ̨���ʼ������
 */
am_local void __hc32f460_i2c2_plfm_deinit (void)
{
    am_clk_disable(CLK_IIC2);
}

/** \brief I2C2 �������ʲ������� */
#define __BUS_SPEED_I2C2     (400000)

/** \brief I2C2 �豸��Ϣ */
am_local am_const am_hc32f460_i2c_devinfo_t __g_hc32f460_i2c2_devinfo = {
    HC32F460_I2C2_BASE,           /**< \brief I2C2 �Ĵ������ַ */
    CLK_IIC2,                     /**< \brief I2C2 ʱ�Ӻ� */
    INUM_I2C2,                    /**< \brief I2C2 �жϺ� */
    __BUS_SPEED_I2C2,             /**< \brief I2C2 �������� */
    10,                           /**< \brief ��ʱʱ�� */
    __hc32f460_i2c2_bus_clean,    /**< \brief ���߻ָ����� */
    __hc32f460_i2c2_plfm_init,    /**< \brief ƽ̨��ʼ������ */
    __hc32f460_i2c2_plfm_deinit   /**< \brief ƽ̨���ʼ������ */
};

/** \brief I2C2 �豸ʵ�� */
am_hc32f460_i2c_dev_t __g_hc32f460_i2c2_dev;

/**
 * \brief I2C2 ʵ����ʼ��
 */
am_i2c_handle_t am_hc32f460_i2c2_inst_init (void)
{
    return am_hc32f460_i2c_init(&__g_hc32f460_i2c2_dev, &__g_hc32f460_i2c2_devinfo);
}

/**
 * \brief I2C2 ʵ�����ʼ��
 */
void am_hc32f460_i2c_inst2_deinit (am_i2c_handle_t handle)
{
    am_hc32f460_i2c_deinit(handle);
}

/**
 * @}
 */

/* end of file */
