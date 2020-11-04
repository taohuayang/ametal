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
 * \brief ZML165 I2C�ӻ� �û������ļ�
 * \sa am_hwconf_zml165_i2c_slv.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-07  vir, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zml165.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg_i2c_slv.h"
#include "am_zml165_clk.h"
#include "hw/amhw_zlg_i2c.h"

/**
 * \addtogroup am_if_src_hwconf_zml165_i2c_slv
 * \copydoc am_hwconf_zml165_i2c_slv.c
 * @{
 */

/** \brief I2C1 ƽ̨��ʼ������ */
static void __zlg_i2c1_plfm_init (void)
{

    /**
     * PIOA_5 ~ I2C1_SCL, PIOA_4 ~ I2C1_SDA
     */
    am_gpio_pin_cfg(PIOA_5, PIOA_5_I2C_SCL | PIOA_5_AF_OD | PIOA_5_SPEED_20MHz);
    am_gpio_pin_cfg(PIOA_4, PIOA_4_I2C_SDA | PIOA_4_AF_OD | PIOA_4_SPEED_20MHz);


    am_clk_enable(CLK_I2C1);
    am_zml165_clk_reset(CLK_I2C1);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
static void __zlg_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C1);
}

/**
 * \name I2C1 ��������������
 * @{
 */

/** @} */

/**
 * \brief I2C1�� �豸��Ϣ
 */
static const am_zlg_i2c_slv_devinfo_t __g_i2c1_devinfo = {

    ZML165_I2C1_BASE,                /**< \brief I2C1�Ĵ������ַ */
    INUM_I2C1,                       /**< \brief I2C1 �жϱ�� */

    __zlg_i2c1_plfm_init,            /**< \brief ƽ̨��ʼ�� */
    __zlg_i2c1_plfm_deinit           /**< \brief ƽ̨ȥ��ʼ�� */
};

static am_zlg_i2c_slv_dev_t __g_i2c1_dev; /**< \brief I2C1 �豸ʵ�� */


/** \brief I2C1 ʵ����ʼ�������I2C��׼������ */
am_i2c_slv_handle_t  am_zml165_i2c1_slv_inst_init (void)
{
    return am_zlg_i2c_slv_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief I2C1 ʵ�����ʼ�� */
void am_zml165_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_zlg_i2c_slv_deinit(handle);
}

/** @} */

/* end of file */
