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
 * \snippet demo_zsn700_hw_spi_master.c src_zsn700_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 19-09-20  zp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_spi_master
 * \copydoc demo_zsn700_hw_spi_master.c
 */

/** [src_zsn700_hw_spi_master] */
#include "ametal.h"
#include "am_zsn700.h"
#include "am_zsn700_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_zlg_entries.h"
#include "am_zsn700_inst_init.h"
#include "demo_am700_core_entries.h"

/**
 * \brief �������
 */
void demo_zsn700_core_hw_spi_master_entry (void)
{
    am_kprintf("demo am217_core hw spi master!\r\n");

    /* ����ʱ�� */
    am_clk_enable(CLK_SPI1);

    /* �������� */
    am_gpio_pin_cfg(PIOB_12, PIOB_12_SPI1_CS   | PIOB_10_OUT_PP);
    am_gpio_pin_cfg(PIOB_10, PIOB_10_SPI1_SCK  | PIOB_10_OUT_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_SPI1_MISO  | PIOC_2_INPUT_PU);

    demo_zsn700_hw_spi_master_entry((void *)ZSN700_SPI1, PIOB_12);
}
/** [src_zsn700_hw_spi_master] */

/* end of file */
