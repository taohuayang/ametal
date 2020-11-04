/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief CMP���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *    1.J25ͨ����ð���ӣ��Ͽ�J24��ð����J24-VRO��J6-29���ӣ�J8-52��ʾ�������ӣ�
 *    2.�򿪹��̱��벢ȫ�����У�
 *    3.���ڿɵ�����R138��
 *    4.�۲�LED1(��ɫ��D26)��ʾ������
 *       a.J8-52��ƽΪ��ʱ��LED1��������ʾINP��ѹ����INM��
 *       b.J8-52��ƽΪ��ʱ��LED1Ϩ�𣬱�ʾINP��ѹ����INM��
 *
 * \note
 *    ����CMP��Ԫʱ�����������ö�Ӧ�����š�INP��INM��
 *    
 * \par Դ����
 * \snippet demo_hc32f460_core_hw_cmp_entry.c
 *          src_demo_hc32f460_core_hw_cmp_entry
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_core_hw_cmp_entry
 * \copydoc demo_hc32f460_core_hw_cmp_entry.c
 */

/** [src_hc32f460_core_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_hc32f460.h"
#include "am_hc32f460_clk.h"
#include "hw/amhw_hc32f460_i2c.h"
#include "demo_hc32f460_entries.h"
#include "demo_hc32f460_core_entries.h"
#include "hc32f460_regbase.h"


/**
 * \brief �������
 */
void demo_hc32f460_core_hw_cmp_entry (void)
{
    am_kprintf("demo hc32f460_core hw cmp!\r\n");

    /* Set PA4 as CMP2_INP1 input */
    am_gpio_pin_cfg(PIOA_4, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) | GPIO_AFIO(AMHW_HC32F460_AFIO_USBF));
    
    /* Set PB13 as Vcout output */
    am_gpio_pin_cfg(PIOB_13, GPIO_AFIO(AMHW_HC32F460_AFIO_VCOUT));

    /* Enable peripheral clock */
    am_clk_enable(CLK_CMP);
    am_clk_enable(CLK_DAC);

    demo_hc32f460_hw_cmp_entry(HC32F460_CMP2);
}
/** [src_hc32f460_core_hw_i2c_slave_poll] */

/* end of file */
