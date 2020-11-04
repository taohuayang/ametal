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
 *   1. PIOC_4 �������� I2C ������ SCL ���ţ�
 *   2. PIOC_5 �������� I2C ������ SDA ���š�
 *
 * - ʵ������:
 *      �����߼������Ǻ�ʾ�����۲쵽i2c�������ݵĲ��Σ�
 *      �ɵ��Բ鿴���ݻ��档
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOC_4��SDA ����ʹ�õ��� PIOC_5��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_i2c_slave_int.c src_hc32f460_std_i2c_slave_int
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_i2c_slave_int
 * \copydoc demo_hc32f460_std_i2c_slave_int.c
 */

/** [src_hc32f460_std_i2c_slave_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_clk.h"
#include "hw/amhw_hc32f460_rcc.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"

//#define DEV_ADDR    0x50
#define DEV_ADDR    0x06
/**
 * \brief �������
 */
void demo_hc32f460_core_std_i2c_slave_int_entry (void)
{
    am_kprintf("demo hc32f460_core std i2c slave int!\r\n");

    demo_std_i2c_slave_entry(am_hc32f460_i2c1_slv_inst_init(), DEV_ADDR);
}
/** [src_hc32f460_std_i2c_slave_int] */

/* end of file */
