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
 * \brief; SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ���ӻ�ʹ��STM32F103RBT6�������Ӧ��spi_slaverʱ��demo_stm32f103rbt6_hw_spi_master_entry���������
 *      CS��ʱ����Ϊ100.
 *   2. ���������� SPI�ӿ���ӻ�SPI�ӿڶ�Ӧ���� ��
 *   3. �ȸ�λ�������ٸ�λ�ӻ�����������������
 *   4. �ر�ע�⣬������������λ���������һ����Ч��Ƭѡ�źţ����´ӻ�����ʶ���ϴ�һ����ʷ���ݡ�
 *      ��ע�ⲽ��2����˳���Ա���ӻ����������ϴ���
 *
 * - ʵ������
 *   1. �������͵����ݲ����ۼ�1���ӻ����ص����ݱ��ֲ��䡣���ӻ�ΪSTM32F103RBT6�������Ӧ��spi_slaver��
 *   2. ��ֱ�Ӷ̽������MOSI��MISO��
 *   3. ���Դ��ڴ�ӡͨ��SPI���պͷ��͵ľ������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_hw_spi_master.c src_stm32f103rbt6_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 19-07-23  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_hw_spi_master
 * \copydoc demo_stm32f103rbt6_hw_spi_master.c
 */

/** [src_stm32f103rbt6_hw_spi_master] */
#include "ametal.h"
#include "am_stm32f103rbt6.h"
#include "am_stm32f103rbt6_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_stm32f103rbt6_entries.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief �������
 */
void demo_stm32f103rbt6_core_hw_spi_master_entry (void)
{
    am_kprintf("demo stm32f103rbt6_core hw spi master!\r\n");

    /* ����ʱ�� */
    am_clk_enable(CLK_SPI2);

    /* ����Ƭѡ���� */
    am_gpio_pin_cfg(PIOB_12, PIOB_12_OUT_PP);
    am_gpio_set(PIOB_12, 1);

    /* ����SPI���� */
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK  | PIOB_13_AF_PP);
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI | PIOB_15_AF_PP);

    demo_stm32f103rbt6_hw_spi_master_entry((void *)STM32F103RBT6_SPI2,
                                    PIOB_12,
                                    am_clk_rate_get(CLK_SPI2),
                                    100);
}
/** [src_stm32f103rbt6_hw_spi_master] */

/* end of file */
