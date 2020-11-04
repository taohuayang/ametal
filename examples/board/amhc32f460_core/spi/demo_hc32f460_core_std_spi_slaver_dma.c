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
 * \brief SPI �ӻ� DMA ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. demo_hc32f460_core_std_spi_slaver_dma_entry()��
 *
 * - ʵ������
 *   1. �����ӻ������������ӡ�      slaver     master
 *                        NSS ------ NSS
 *                        SCK ------ SCK
 *                        MOSI ----- MOSI
 *                        MISO ----- MISO
 *   2. �����������ݣ��ӻ����ô��ڴ�ӡ��Ӧ���ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *    PIOE_5 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_spi_slave_dma.c src_hc32f460_std_spi_slave_dma
 *
 * \internal
 * \par History
 * - 1.00 20-04-16  cds, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_spi_slave_dma
 * \copydoc demo_hc32f460_std_spi_slave_dma.c
 */

/** [src_hc32f460_std_spi_slave_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_std_spi_slaver_dma_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core std spi slaver dma!\r\n");

    demo_std_spi_slave_entry(am_hc32f460_spi3_slv_dma_inst_init());
}
/** [src_hc32f460_std_spi_slave_dma] */

/* end of file */
