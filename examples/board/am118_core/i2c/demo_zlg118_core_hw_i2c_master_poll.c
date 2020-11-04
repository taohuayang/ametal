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
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_11 �������� EEPROM �� SCL ���ţ�
 *   2. PIOA_12 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. �� EEPROM �豸д�� 16 �ֽ����ݣ�
 *   2. ��ȡ EEPROM �е�����ͨ�����ڴ�ӡ������
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ��ǰ I2C �� SCL ����ʹ�õ��� PIOA_11��SDA ����ʹ�õ��� PIOA_12��
 *       �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_zlg118_core_hw_i2c_master_poll.c
 *          src_zlg118_core_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 19-12-16  licl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_core_hw_i2c_master_poll
 * \copydoc demo_zlg118_core_hw_i2c_master_poll.c
 */

/** [src_zlg118_core_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg118.h"
#include "am_zlg118_clk.h"
#include "hw/amhw_zlg118_i2c.h"
#include "demo_zlg_entries.h"
#include "demo_am118_core_entries.h"

/**
 * \brief �������
 */
void demo_zlg118_core_hw_i2c_master_poll_entry (void)
{
    am_kprintf("demo zlg118_core hw i2c master poll!\r\n");

    am_gpio_pin_cfg(PIOA_11, PIOA_11_I2C1_SCL | PIOA_11_OUT_OD);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_I2C1_SDA | PIOA_12_OUT_OD);

    am_clk_enable(CLK_I2C1);

    demo_zlg118_hw_i2c_master_poll_entry(ZLG118_I2C1,
                                         am_clk_rate_get (CLK_PCLK));
}
/** [src_zlg118_core_hw_i2c_master_poll] */

/* end of file */
