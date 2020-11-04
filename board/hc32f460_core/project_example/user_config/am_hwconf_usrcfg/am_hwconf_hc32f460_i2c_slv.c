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
 * \brief I2C �ӻ��û������ļ�
 * \sa am_hwconf_hc32f460_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-25
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32f460_i2c_slv.h"
#include "am_hc32f460_clk.h"
#include "hw/amhw_hc32f460_i2c.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_i2c_slv
 * \copydoc am_hwconf_hc32f460_i2c_slv.c
 * @{
 */

/** \brief I2C1 ƽ̨��ʼ������ */
static void __hc32f460_i2c1_plfm_init (void)
{
    am_gpio_pin_cfg(PIOC_4, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SCL));
    am_gpio_pin_cfg(PIOC_5, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SDA));

    am_clk_enable(CLK_IIC1);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
static void __hc32f460_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_IIC1);
}

/**
 * \name I2C1 ��������������
 * @{
 */

/** @} */

/** \brief I2C1 �������ʲ������� */
#define __BUS_SPEED_I2C1_SLAVE     (400000)

/**
 * \brief I2C1 �ӻ��豸��Ϣ
 */
static const am_hc32f460_i2c_slv_devinfo_t __g_i2c1_devinfo = {
    HC32F460_I2C1_BASE,              /**< \brief I2C1�Ĵ������ַ */
    CLK_IIC1,                        /**< \brief I2C1 ʱ�Ӻ� */
    INUM_I2C1,                       /**< \brief I2C1 �жϱ�� */
    __BUS_SPEED_I2C1_SLAVE,          /**< \brief I2C1 �������� */
    __hc32f460_i2c1_plfm_init,       /**< \brief ƽ̨��ʼ�� */
    __hc32f460_i2c1_plfm_deinit      /**< \brief ƽ̨ȥ��ʼ�� */
};

/**< \brief I2C1 �豸ʵ�� */
am_hc32f460_i2c_slv_dev_t __g_i2c1_dev;

/** \brief I2C1 ʵ����ʼ�������I2C��׼������ */
am_i2c_slv_handle_t  am_hc32f460_i2c1_slv_inst_init (void)
{
    return am_hc32f460_i2c_slv_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief I2C1 ʵ�����ʼ�� */
void am_hc32f460_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_hc32f460_i2c_slv_deinit(handle);
}

am_hc32f460_i2c_slv_dev_t __g_i2c2_dev;
am_hc32f460_i2c_slv_dev_t __g_i2c3_dev;
/** @} */

/* end of file */
