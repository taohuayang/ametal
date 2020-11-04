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
 * \brief SPI 主机 DMA 方式例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 将 SPI 的 MOSI 引脚和 MISO 引脚用线相连，模拟从机设备，回环测试；。
 *
 * - 实验现象：
 *   1. 主机通过 MOSI 发送数据，发出的数据从 MOSI 读回；
 *   2. 串口打印出测试结果。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOE_4 引脚连接 PC 串口的 TXD，
 *    PIOE_5 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_hc32f460_std_spi_master_poll.c src_hc32f460_std_spi_master_poll
 *
 * \internal
 * \par History
 * - 1.00 20-04-16 cds, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_spi_master_poll
 * \copydoc demo_hc32f460_std_spi_master_poll.c
 */

/** [src_hc32f460_std_spi_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_hc32f460_core_std_spi_master_poll_entry (void)
{
    AM_DBG_INFO("demo amhc32f460_core std spi master poll!\r\n");

    demo_std_spi_master_entry(am_hc32f460_spi3_poll_inst_init(), PIOE_1);
}
/** [src_hc32f460_std_spi_master_poll] */

/* end of file */
