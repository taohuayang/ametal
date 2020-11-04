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
 * \brief I2C �ӻ����̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_6 �������� I2C ������ SCL ���ţ�
 *   2. PIOB_7 �������� I2C ������ SDA ���š�
 *
 * \note
 *    1. ��ǰ I2C �� SCL ����ʹ�õ��� PIOB_6��SDA ����ʹ�õ��� PIOB_7��
 *       �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_aml165_core_std_i2c_slave.c src_aml165_core_std_i2c_slave
 *
 * \internal
 * \par Modification history
 * - 1.00  17-09-06  vir, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_std_i2c_slave
 * \copydoc demo_aml165_core_std_i2c_slave.c
 */

/** [src_aml165_core_std_i2c_slave] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

#define __I2C_SLV_ADDR   0X50  /**< \brief ���豸�ĵ�ַ */

/**
 * \brief �������
 */
void demo_aml165_core_std_i2c_slave_entry (void)
{
    AM_DBG_INFO("demo aml165_core std i2c slave!\r\n");

    demo_std_i2c_slave_entry(am_zml165_i2c1_slv_inst_init(), __I2C_SLV_ADDR);
}
/** [src_aml165_core_std_i2c_slave] */

/* end of file */
