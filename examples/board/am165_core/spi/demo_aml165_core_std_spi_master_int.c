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
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_3 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml165_core_std_spi_master_int.c src_aml165_core_std_spi_master_int
 *
 * \internal
 * \par History
 * - 1.00 17-04-25  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_std_spi_master_int
 * \copydoc demo_aml165_core_std_spi_master_int.c
 */

/** [src_aml165_core_std_spi_master_int] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_std_spi_master_int_entry (void)
{
    AM_DBG_INFO("demo aml165_core std spi master int!\r\n");

    demo_std_spi_master_entry(am_zml165_spi1_int_inst_init(), PIOA_4);
}
/** [src_aml165_core_std_spi_master_int] */

/* end of file */
