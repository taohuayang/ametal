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
 * \brief MicroPort EEPROM ���̣�ͨ�� NVRAM �ӿ�ʵ��
 *
 * ���� FM24C02 �� EEPROM �ǵ��͵ķ���ʧ�Դ洢�������ʹ�� NVRAM����
 * ��ʧ�Դ洢������׼�ӿڶ�д���ݾ�������ľ���������ˡ�
 *
 * - �������裺
 *   1. �� MicroPort EEPROM ������ӵ� aml165-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ����д���ݵ� EEPROM��
 *   2. ������ EEPROM ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_3 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml165_core_microport_eeprom_nvram.c src_aml165_core_microport_eeprom_nvram
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_microport_eeprom_nvram
 * \copydoc demo_aml165_core_microport_eeprom_nvram.c
 */

/** [src_aml165_core_microport_eeprom_nvram] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_microport_eeprom_nvram_entry (void)
{
    AM_DBG_INFO("demo aml165_core microport eeprom nvram!\r\n");

    am_microport_eeprom_nvram_inst_init();

    demo_std_nvram_entry("microport_eeprom", 0, 16);
}
/** [src_aml165_core_microport_eeprom_nvram] */

/* end of file */
