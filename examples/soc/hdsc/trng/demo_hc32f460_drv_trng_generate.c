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
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   TRNG ģ���ϵ����һ�����������ϵ����������Աȣ������ͬ��TRNG�����������ȷ����ӡ
 *   ��Trng generate test success!\r\n��,��֮��ӡ ��Trng generate test failed!\r\n����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *       PIOE_5 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f460_hw_trng_dac.c src_hc32f460_hw_trng_generate
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-26  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_trng_generate
 * \copydoc demo_hc32f460_hw_trng_generate.c
 */

/** [src_hc32f460_hw_trng_generate] */
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_hc32f460_trng.h"
#include "hw/amhw_hc32f460_trng.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/**< \brief ����������� */
static uint32_t rng_data[2] = {0};


/**
 * \brief �������
 */
void demo_hc32f460_drv_trng_generate_entry (am_trng_handle_t handle)
{

    while(1) {
        am_hc32f460_trng_generate(handle, AM_HC32F460_TRNG_LOAD_NEW_INIT_VALUE, rng_data);

        am_kprintf ("Trng generate tset success!\r\n");
        am_kprintf ("Rand number: 0x%08x 0x%08x.\r\n", rng_data[0], rng_data[1]);

        am_mdelay(1000);
    }
}

/* end of file */

