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
 * \brief ��SPI�ж�ģʽ�²���SPI_FLASH��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �ӿں� SPI FLASH ��Ӧ�Ľӿ�����������
 *
 * - ʵ������
 *   1. д���ݵ� FLASH��
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ���������£�ֱ��ʹ�� am_spi_write_then_read() ��
 *       am_spi_write_then_write() �������ɡ�
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_spi_flash_int.c src_mm32l073_core_std_spi_flash_int
 *
 * \internal
 * \par History
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_mm32l073_core_std_spi_flash_int
 * \copydoc demo_mm32l073_core_std_spi_flash_int.c
 */
 
/** [src_mm32l073_core_std_spi_flash_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_std_spi_flash_int_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core std spi flash int!\r\n");

    demo_std_spi_flash_entry(am_mm32l073_spi1_int_inst_init(), PIOA_4, 0, 256);
}
/** [src_mm32l073_core_std_spi_flash_int] */

/* end of file */
