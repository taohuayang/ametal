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
 * \brief I2C �������� EEPROM ���̣�ͨ���첽��׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_6 �������� EEPROM �� SCL ���ţ�
 *   2. PIOB_7 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. ����д��ַ�����ݵ��ӻ���
 *   2. �������մӻ����ݣ���ͨ�����ڴ�ӡ����
 *   3. ����д������ݺͽ��յ��Ĵӻ��ӻ�����һ�£�
 *   4. LED0 �� 200ms ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    3. ��ǰ I2C �� SCL ����ʹ�õ��� PIOB_6��SDA ����ʹ�õ��� PIOB_7��
 *       �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_std_i2c_master_async.c src_stm32f103rbt6_std_i2c_master_async
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-26  zc, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_std_i2c_master_async
 * \copydoc demo_stm32f103rbt6_std_i2c_master_async.c
 */

/** [src_stm32f103rbt6_std_i2c_master_async] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_i2c.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_std_entries.h"
#include "demo_stm32f103rbt6_core_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define EEPROM_ADDR    (0xb2 >> 1)   /**< \brief EEPROM�豸�ĵ�ַ */

#define TEST_LEN       8      /**< \brief ����EEPROM��ҳ��С����Ҫ���ݾ���оƬ���� */

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_std_i2c_master_async_entry (void)
{

    AM_DBG_INFO("demo stm32f103rbt6_core std i2c master async!\r\n");

    demo_std_i2c_master_async_entry(am_stm32f103rbt6_i2c1_inst_init(),
                                    EEPROM_ADDR,
                                    TEST_LEN);
}
/** [src_stm32f103rbt6_std_i2c_master_async] */

/* end of file */
