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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_3 �������� PC ���ڵ� RXD��
 *    2. ���������£�ֱ��ʹ�� am_spi_write_then_read() ��
 *       am_spi_write_then_write() �������ɡ�
 *
 * \par Դ����
 * \snippet demo_aml165_core_std_spi_flash_int.c src_aml165_core_std_spi_flash_int
 *
 * \internal
 * \par History
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_aml165_core_std_spi_flash_int
 * \copydoc demo_aml165_core_std_spi_flash_int.c
 */
 
/** [src_aml165_core_std_spi_flash_int] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_std_spi_flash_int_entry (void)
{
    AM_DBG_INFO("demo aml165_core std spi flash int!\r\n");

    demo_std_spi_flash_entry(am_zml165_spi1_int_inst_init(), PIOA_4, 0, 256);
}
/** [src_aml165_core_std_spi_flash_int] */

/* end of file */
