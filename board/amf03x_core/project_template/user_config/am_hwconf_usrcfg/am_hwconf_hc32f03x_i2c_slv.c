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
 * \brief HC32 I2C �ӻ��û������ļ�
 * \sa am_hwconf_hc32f03x_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-25
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32_i2c_slv.h"
#include "am_hc32_clk.h"
#include "hw/amhw_hc32_i2c.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f03x_i2c_slv
 * \copydoc am_hwconf_hc32f03x_i2c_slv.c
 * @{
 */

/** \brief I2C0 ƽ̨��ʼ������ */
static void __hc32f03x_i2c0_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_8, PIOB_8_I2C0_SCL | PIOB_8_OUT_OD);
    am_gpio_pin_cfg(PIOB_9, PIOB_9_I2C0_SDA | PIOB_9_OUT_OD);

    am_clk_enable(CLK_I2C0);
}

/** \brief ���I2C0 ƽ̨��ʼ������ */
static void __hc32f03x_i2c0_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C0);
}

/**
 * \name I2C0 ��������������
 * @{
 */

/** @} */

/**
 * \brief I2C0 �ӻ��豸��Ϣ
 */
static const am_hc32_i2c_slv_devinfo_t __g_i2c0_devinfo = {
    HC32_I2C0_BASE,               /**< \brief I2C0 �Ĵ������ַ */
    INUM_I2C0,                      /**< \brief I2C0 �жϱ�� */
    __hc32f03x_i2c0_plfm_init,           /**< \brief ƽ̨��ʼ�� */
    __hc32f03x_i2c0_plfm_deinit          /**< \brief ƽ̨ȥ��ʼ�� */
};

/**< \brief I2C0 �豸ʵ�� */
static am_hc32_i2c_slv_dev_t __g_i2c0_dev;

/** \brief I2C0 ʵ����ʼ�������I2C��׼������ */
am_i2c_slv_handle_t  am_hc32_i2c0_slv_inst_init (void)
{
    return am_hc32_i2c_slv_init(&__g_i2c0_dev, &__g_i2c0_devinfo);
}

/** \brief I2C0 ʵ�����ʼ�� */
void am_hc32_i2c0_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_hc32_i2c_slv_deinit(handle);
}


/** \brief I2C1 ƽ̨��ʼ������ */
static void __hc32f03x_i2c1_plfm_init (void)
{
    am_gpio_pin_cfg(PIOA_11, PIOA_11_I2C1_SCL | PIOB_11_OUT_OD);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_I2C1_SDA | PIOB_12_OUT_OD);

    am_clk_enable(CLK_I2C1);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
static void __hc32f03x_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C1);
}

/**
 * \name I2C1 ��������������
 * @{
 */

/** @} */

/**
 * \brief I2C1 �ӻ��豸��Ϣ
 */
static const am_hc32_i2c_slv_devinfo_t __g_i2c1_devinfo = {
    HC32_I2C1_BASE,           /**< \brief I2C1�Ĵ������ַ */
    INUM_I2C1,                  /**< \brief I2C1 �жϱ�� */
    __hc32f03x_i2c1_plfm_init,       /**< \brief ƽ̨��ʼ�� */
    __hc32f03x_i2c1_plfm_deinit      /**< \brief ƽ̨ȥ��ʼ�� */
};

/**< \brief I2C1 �豸ʵ�� */
static am_hc32_i2c_slv_dev_t __g_i2c1_dev;

/** \brief I2C1 ʵ����ʼ�������I2C��׼������ */
am_i2c_slv_handle_t  am_hc32_i2c1_slv_inst_init (void)
{
    return am_hc32_i2c_slv_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief I2C1 ʵ�����ʼ�� */
void am_hc32_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_hc32_i2c_slv_deinit(handle);
}

/** @} */

/* end of file */
