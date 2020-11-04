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
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_6 �������� EEPROM �� SCL ���ţ�
 *   2. PIOB_7 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. �� EEPROM �豸д�� 8�ֽڣ�С�ڻ����һҳ�����ݣ�
 *   2. ��ȡ EEPROM �е�����ͨ�����ڴ�ӡ������
 *   3. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED0 �� 200ms �����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    3. ��ǰ I2C �� SCL ����ʹ�õ��� PIOB_6��SDA ����ʹ�õ��� PIOB_7��
 *       �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_mm32l373_hw_i2c_master_poll.c src_mm32l373_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 17-09-5  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l373_hw_i2c_master_poll
 * \copydoc demo_mm32l373_hw_i2c_master_poll.c
 */

/** [src_mm32l373_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_mm32l373.h"
#include "am_mm32l373_clk.h"
#include "amhw_mm32l373_rcc.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l373_core_entries.h"

#define I2C_MASTER    (amhw_mm32_i2c_t *)MM32L373_I2C1_BASE   /**< \brief I2C����������ͨ���Ŷ��� */

/**
 * \brief �������
 */
void demo_mm32l373_core_hw_i2c_master_poll_entry (void)
{

    am_kprintf("demo mm32l373_core hw i2c master poll!\r\n");

    /**
     * PIOB_6 ~ I2C1_SCL, PIOB_7 ~ I2C1_SDA
     */
    am_gpio_pin_cfg(PIOB_6, PIOB_6_I2C1_SCL_REMAP0 | PIOB_6_AF_OD | PIOB_6_SPEED_2MHz);
    am_gpio_pin_cfg(PIOB_7, PIOB_7_I2C1_SDA_REMAP0 | PIOB_7_AF_OD | PIOB_7_SPEED_2MHz);

    am_clk_enable(CLK_I2C1);
    am_mm32l373_clk_reset(CLK_I2C1);

    demo_mm32_hw_i2c_master_poll_entry(I2C_MASTER, am_clk_rate_get(CLK_APB1));

}
/** [src_mm32l373_hw_i2c_master_poll] */

/* end of file */
