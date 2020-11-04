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
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �� MOSI ���ź� MISO ��������������ģ��ӻ��豸���ػ����ԡ�
 *
 * - ʵ������
 *   1. ����ͨ�� MISO �������ݣ����������ݴ� MOSI ���أ�
 *   2. �ȽϷ����Ͷ��ص����ݣ������ͬ LED0 ����,������ 200ms ʱ������˸��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_spi_master.c src_hc32f460_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 20-03-25  cds, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_spi_master
 * \copydoc demo_hc32f460_hw_spi_master.c
 */

/** [src_hc32f460_hw_spi_master] */
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_hc32f460_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_entries.h"

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_spi_master_entry (void)
{
    am_kprintf("demo amhc32f460_core hw spi master!\r\n");

    /* ����ʱ�� */
    am_clk_enable(CLK_SPI3);

    /* �������� */
    am_gpio_pin_cfg(PIOE_1, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PULLUP);
    am_gpio_set(PIOE_1, 1);

    am_gpio_pin_cfg(PIOE_0,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_SCK));
    am_gpio_pin_cfg(PIOE_2,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MOSI));
    am_gpio_pin_cfg(PIOE_3,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MISO));

    demo_hc32f460_hw_spi_master_entry(HC32F460_SPI3, PIOE_1);
}
/** [src_hc32f460_hw_spi_master] */

/* end of file */
