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
 * \brief SPI �����жϷ�ʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �� MOSI ���ź� MISO ��������������ģ��ӻ��豸���ػ����ԡ�
 *
 * - ʵ������
 *   1. ����ͨ�� MOSI �������ݣ����������ݴ� MOSI ���أ�
 *   2. ���Դ��ڴ�ӡ���Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_std_spi_master_int.c src_mm32l073_core_std_spi_master_int
 *
 * \internal
 * \par History
 * - 1.00 17-04-25  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_std_spi_master_int
 * \copydoc demo_mm32l073_core_std_spi_master_int.c
 */

/** [src_mm32l073_core_std_spi_master_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l073.h"
#include "am_mm32l073_inst_init.h"
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l073_core_std_spi_master_int_entry (void)
{
    AM_DBG_INFO("demo mm32l073_core std spi master int!\r\n");

    demo_std_spi_master_entry(am_mm32l073_spi1_int_inst_init(), PIOA_4);
}
/** [src_mm32l073_core_std_spi_master_int] */

/* end of file */
