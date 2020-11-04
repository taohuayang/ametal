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
 * \file SPI �ӻ� DMA ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI ������ӻ����ӡ�
 *
 * - ʵ������
 *   1. �������֮��ӻ���ӡ���ջ����������ݡ�
 *
 * \par Դ����
 * \snippet demo_aml165_core_std_spi_slave_dma.c src_aml165_core_std_spi_slave_dma
 *
 * \internal
 * \par History
 * - 1.00 17-09-19 fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_std_spi_slave_dma
 * \copydoc demo_aml165_core_std_spi_slave_dma.c
 */

/** [src_aml165_core_std_spi_slave_dma] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_std_spi_slave_dma_entry (void)
{
    AM_DBG_INFO("demo aml165_core std spi slave dma!\r\n");

    demo_std_spi_slave_entry(am_zml165_spi1_slv_dma_inst_init());
}
/** [src_aml165_core_std_spi_slave_dma] */

/* end of file */
