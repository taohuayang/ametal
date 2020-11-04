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
 * \brief I2C �ӻ�ģ�� TMP100 ���̣�ͨ����׼�ӿ�ʵ��
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
 * \snippet demo_aml165_core_std_i2c_slave_subaddr.c src_aml165_core_std_i2c_slave_subaddr
 *
 * \internal
 * \par Modification history
 * - 1.00  17-09-12  vir, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_std_i2c_slave_subaddr
 * \copydoc demo_aml165_core_std_i2c_slave_subaddr.c
 */

/** [src_aml165_core_std_i2c_slave_subaddr] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_std_i2c_slave_subaddr_entry (void)
{
    AM_DBG_INFO("demo aml165_core std i2c slave subaddr!\r\n");

    demo_std_i2c_slave_subaddr_entry(am_zml165_i2c1_slv_inst_init());
}
/** [src_aml165_core_std_i2c_slave_subaddr] */

/* end of file */
