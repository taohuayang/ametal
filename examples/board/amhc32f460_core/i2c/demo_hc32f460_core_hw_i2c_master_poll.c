/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
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
 *   1. PIOC_4 �������� I2C �ӻ��� SCL ���ţ�
 *   2. PIOC_5 �������� I2C �ӻ��� SDA ���š�
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOC_4��SDA ����ʹ�õ��� PIOC_5��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_hc32f460_core_hw_i2c_slave_poll.c
 *          src_hc32f460_core_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-16  licl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_core_hw_i2c_slave_poll
 * \copydoc demo_hc32f460_core_hw_i2c_slave_poll.c
 */

/** [src_hc32f460_core_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "am_hc32f460_clk.h"
#include "hw/amhw_hc32f460_i2c.h"
#include "demo_hc32f460_entries.h"
#include "demo_hc32f460_core_entries.h"
#include "hc32f460_regbase.h"

#define MASTER_ADDR      0x06
#define MASTER_SPEED     400000

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_i2c_master_poll_entry (void)
{
    am_kprintf("demo hc32f460_core hw i2c master poll!\r\n");

    am_gpio_pin_cfg(PIOC_4, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SCL));    
    am_gpio_pin_cfg(PIOC_5, GPIO_AFIO(AMHW_HC32F460_AFIO_I2C1_SDA));    

    demo_hc32f460_hw_i2c_master_poll_entry((void *)HC32F460_I2C1_BASE, CLK_IIC1, MASTER_SPEED, MASTER_ADDR);
}
/** [src_hc32f460_core_hw_i2c_slave_poll] */

/* end of file */
