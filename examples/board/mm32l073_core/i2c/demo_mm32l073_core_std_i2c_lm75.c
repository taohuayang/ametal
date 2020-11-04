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
 * \brief I2C ������ LM75 ��������ȡ�¶�ֵ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *   1. �� J14 �� KEY �� RES �̽���һ��ʹ�ð��� RES ����ͨ���ʵ��裻
 *   2. �̽�����ñ J11 �� J13��ʹ I2C1 �� LM75 ���ӡ�
 *
 * - ʵ������:
 *   1. ��������¶�ֵ��
 *   2. ���� RES ��������һ�������������¶�ֵ���ߡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_i2c_lm75.c src_mm32l073_core_std_i2c_lm75
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-10 win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_std_i2c_lm75
 * \copydoc demo_mm32l073_core_std_i2c_lm75.c
 */

/** [src_mm32l073_core_std_i2c_lm75] */

/*******************************************************************************
  includes
*******************************************************************************/
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_std_i2c_lm75_entry (void)
{
    am_kprintf("demo mm32l073_core std i2c lm75!\r\n");

    demo_std_i2c_lm75_entry(am_temp_lm75_inst_init());
}
/** [src_mm32l073_core_std_i2c_lm75] */

/* end of file */
