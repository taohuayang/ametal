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
 * \brief SPI ���� DMA ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �� MOSI ���ź� MISO ��������������ģ��ӻ��豸���ػ����ԡ�
 *
 * - ʵ������
 *   1. ����ͨ�� MOSI �������ݣ����������ݴ� MOSI ���أ�
 *   2. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *    PIOE_5 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_spi_master_dma.c src_hc32f460_std_spi_master_dma
 *
 * \internal
 * \par History
 * - 1.00 20-04-16  cds, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_spi_master_dma
 * \copydoc demo_hc32f460_std_spi_master_dma.c
 */

/** [src_hc32f460_std_spi_master_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_spi_master_dma_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core std spi master dma!\r\n");

    demo_std_spi_master_entry(am_hc32f460_spi4_dma_inst_init(), PIOE_1);
}
/** [src_hc32f460_std_spi_master_dma] */

/* end of file */