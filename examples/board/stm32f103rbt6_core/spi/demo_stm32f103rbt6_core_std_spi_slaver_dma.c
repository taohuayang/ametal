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
 *   1. demo_stm32f103rbt6_core_std_spi_slaver_dma_entry()��
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
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_std_spi_slave_dma.c src_stm32f103rbt6_std_spi_slave_dma
 *
 * \internal
 * \par History
 * - 1.00 19-07-23  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_std_spi_slave_dma
 * \copydoc demo_stm32f103rbt6_std_spi_slave_dma.c
 */

/** [src_stm32f103rbt6_std_spi_slave_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "stm32f103rbt6_pin.h"
#include "demo_std_entries.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_std_spi_slaver_dma_entry (void)
{
    AM_DBG_INFO("demo stm32f103rbt6_core std spi slaver dma!\r\n");

    demo_std_spi_slave_entry(am_stm32f103rbt6_spi2_slv_dma_inst_init());
}
/** [src_stm32f103rbt6_std_spi_slave_dma] */

/* end of file */
