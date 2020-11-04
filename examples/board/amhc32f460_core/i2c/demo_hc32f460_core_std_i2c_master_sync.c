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
 * \brief I2C �������� EEPROM ���̣�ͨ��ͬ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_4 �������� EEPROM �� SCL ���ţ�
 *   2. PIOC_5 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. ����д��ַ�����ݵ��ӻ���
 *   2. �������մӻ����ݣ���ͨ�����ڴ�ӡ����
 *   3. ����д������ݺͽ��յ��Ĵӻ��ӻ�����һ�£�
 *   4. LED0 �� 200ms ʱ������˸��
 *
 * \note
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_i2c_master_sync.c src_hc32f460_std_i2c_master_sync
 *
 * \internal
 * \par Modification history
 * - 1.00  17-04-24  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_i2c_master_sync
 * \copydoc demo_hc32f460_std_i2c_master_sync.c
 */

/** [src_hc32f460_std_i2c_master_sync] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_i2c.h"
#include "am_hc32f460_inst_init.h"
#include "am_hc32f460_i2c.h"
#include "demo_std_entries.h"
#include "demo_hc32f460_core_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define EEPROM_ADDR  0x50  /**< \brief EEPROM�豸�ĵ�ַ */
//#define EEPROM_ADDR  0x06  /**< \brief EEPROM�豸�ĵ�ַ */

#define TEST_LEN     8     /**< \brief ����EEPROM��ҳ��С����Ҫ���ݾ���оƬ���� */

/**
 * \brief �������
 */
void demo_hc32f460_core_std_i2c_master_sync_entry (void)
{
    AM_DBG_INFO("demo hc32f460_core std i2c master sync!\r\n");

    demo_std_i2c_master_sync_entry(am_hc32f460_i2c1_inst_init(),
                                   EEPROM_ADDR,
                                   TEST_LEN);
}
/** [src_hc32f460_std_i2c_master_sync] */

/* end of file */
