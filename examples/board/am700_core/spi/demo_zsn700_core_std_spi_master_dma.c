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
 *   1. �� SPI �� MOSI ���ź� MISO ��������������ģ��ӻ��豸���ػ����ԣ���
 *
 * - ʵ������
 *   1. ����ͨ�� MOSI �������ݣ����������ݴ� MOSI ���أ�
 *   2. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsn700_std_spi_master_dma.c src_zsn700_std_spi_master_dma
 *
 * \internal
 * \par History
 * - 1.00 19-09-20  zp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_std_spi_master_dma
 * \copydoc demo_zsn700_std_spi_master_dma.c
 */

/** [src_zsn700_std_spi_master_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "zsn700_pin.h"
#include "am_zsn700_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am700_core_entries.h"

/**
 * \brief �������
 */
void demo_zsn700_core_std_spi_master_dma_entry (void)
{
    am_spi_handle_t spi_handle = am_zsn700_spi1_dma_inst_init();

    AM_DBG_INFO("demo am700_core std spi master dma!\r\n");

    demo_std_spi_master_entry(spi_handle, PIOA_4); 
}
/** [src_zsn700_std_spi_master_dma] */

/* end of file */
