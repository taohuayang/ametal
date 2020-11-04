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
 * \brief I2C �������� EEPROM ���̣�ͨ��ͬ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_11 �������� EEPROM �� SCL ���ţ�
 *   2. PIOA_12 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. ����д��ַ�����ݵ��ӻ���
 *   2. �������մӻ����ݣ���ͨ�����ڴ�ӡ����
 *   3. ����д������ݺͽ��յ��Ĵӻ��ӻ�����һ�£�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ��ǰ I2C �� SCL ����ʹ�õ��� PIOA_11��SDA ����ʹ�õ��� PIOA_12��
 *       �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_zlg118_std_i2c_master_sync.c src_zlg118_std_i2c_master_sync
 *
 * \internal
 * \par Modification history
 * - 1.00  19-09-27  licl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_std_i2c_master_sync
 * \copydoc demo_zlg118_std_i2c_master_sync.c
 */

/** [src_zlg118_std_i2c_master_sync] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_i2c.h"
#include "am_zlg118_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am118_core_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define EEPROM_ADDR  0x50  /**< \brief EEPROM�豸�ĵ�ַ */

#define TEST_LEN     8     /**< \brief ����EEPROM��ҳ��С����Ҫ���ݾ���оƬ���� */

/**
 * \brief �������
 */
void demo_zlg118_core_std_i2c_master_sync_entry (void)
{
    AM_DBG_INFO("demo am118_core std i2c master sync!\r\n");

    demo_std_i2c_master_sync_entry(am_zlg118_i2c1_inst_init(),
                                   EEPROM_ADDR,
                                   TEST_LEN);
}
/** [src_zlg118_std_i2c_master_sync] */

/* end of file */
