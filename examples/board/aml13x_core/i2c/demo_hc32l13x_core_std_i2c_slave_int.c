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
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ����׼��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_11 �������� I2C ������ SCL ���ţ�
 *   2. PIOA_12 �������� I2C ������ SDA ���š�
 *
 * - ʵ������:
 *      �����߼������Ǻ�ʾ�����۲쵽i2c�������ݵĲ��Σ�
 *      �ɵ��Բ鿴���ݻ��档
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOA_11��SDA ����ʹ�õ��� PIOA_12��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_hc32l13x_std_i2c_slave_int.c src_hc32l13x_std_i2c_slave_int
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l13x_std_i2c_slave_int
 * \copydoc demo_hc32l13x_std_i2c_slave_int.c
 */

/** [src_hc32l13x_std_i2c_slave_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "am_hc32_clk.h"
#include "hw/amhw_hc32_rcc.h"
#include "demo_std_entries.h"
#include "am_hc32l13x_inst_init.h"

#define DEV_ADDR    0x50

/**
 * \brief �������
 */
void demo_hc32l13x_core_std_i2c_slave_int_entry (void)
{
    am_kprintf("demo aml13x_core std i2c slave int!\r\n");

    demo_std_i2c_slave_entry(am_hc32_i2c1_slv_inst_init(), DEV_ADDR);
}
/** [src_hc32l13x_std_i2c_slave_int] */

/* end of file */
