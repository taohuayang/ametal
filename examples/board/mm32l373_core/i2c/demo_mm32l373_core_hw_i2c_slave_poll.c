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
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_6 �������� I2C ������ SCL ���ţ�
 *   2. PIOB_7 �������� I2C ������ SDA ���š�
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOB_6��SDA ����ʹ�õ��� PIOB_7��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_mm32l373_hw_i2c_slave_poll.c src_mm32l373_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l373_hw_i2c_slave_poll
 * \copydoc demo_mm32l373_hw_i2c_slave_poll.c
 */

/** [src_mm32l373_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_mm32l373.h"
#include "am_mm32l373_clk.h"
#include "amhw_mm32_i2c.h"
#include "amhw_mm32l373_rcc.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l373_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l373_core_hw_i2c_slave_poll_entry (void)
{
    am_kprintf("demo mm32l373_core hw i2c slave poll!\r\n");

    /**
     * PIOB_6 ~ I2C1_SCL, PIOB_7 ~ I2C1_SDA
     */
    am_gpio_pin_cfg(PIOB_6, PIOB_6_I2C1_SCL_REMAP0 | PIOB_6_AF_OD);
    am_gpio_pin_cfg(PIOB_7, PIOB_7_I2C1_SDA_REMAP0 | PIOB_7_AF_OD);

    am_clk_enable(CLK_I2C1);
    am_mm32l373_clk_reset(CLK_I2C1);

    demo_mm32_hw_i2c_slave_poll_entry(MM32L373_I2C1);
}
/** [src_mm32l373_hw_i2c_slave_poll] */

/* end of file */
