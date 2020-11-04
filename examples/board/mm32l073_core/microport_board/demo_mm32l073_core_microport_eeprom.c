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
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort EEPROM ������ӵ� AM116-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ����д���ݵ� EEPROM��
 *   2. ������ EEPROM ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_microport_eeprom.c src_mm32l073_core_microport_eeprom
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_microport_eeprom
 * \copydoc demo_mm32l073_core_microport_eeprom.c
 */

/** [src_mm32l073_core_microport_eeprom] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073_inst_init.h"
#include "demo_components_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_microport_eeprom_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core microport eeprom!\r\n");

    demo_ep24cxx_entry(am_microport_eeprom_inst_init(), 8);
}
/** [src_mm32l073_core_microport_eeprom] */

/* end of file */
