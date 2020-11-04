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
 * \brief aes ϵͳ��λ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   AES�����ݼ���Ȼ����ܣ�������ܳ������������ǰ����һ�����򴮿ڴ�ӡ��Aes ency-decy success!\r\n����
 *   ��֮��ӡ"Aes ency-decy failed!\r\n"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOE_4 �������� PC ���ڵ� TXD��
 *       PIOE_5 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32f460_drv_aes_ency_decy.c src_hc32f460_drv_aes_ency_decy
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-26  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_drv_aes_ency_decy
 * \copydoc demo_hc32f460_drv_aes_ency_decy.c
 */

/** [src_hc32f460_drv_aes_ency_decy] */
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_board.h"
#include "am_hc32f460_aes.h"
#include "hw/amhw_hc32f460_aes.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/**< \brief ��ż��ܺ������ */
static uint32_t ency_data[4] = {0};

/**< \brief ��Ž��ܺ������ */
static uint32_t decy_data[4]  = {0};


/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_drv_aes_ency_decy_entry (am_aes_handle_t  handle,
                                            uint32_t        *p_aes_data,
                                            uint32_t        *p_key_data)
{
	uint32_t i = 0;

    am_hc32f460_aes_encrypt(handle, p_aes_data, p_key_data, ency_data);

    am_hc32f460_aes_decrypt(handle, ency_data, p_key_data, decy_data);

    /* �жϼ��ܽ��ܺ���������ʼ�����Ƿ�һ�� */
    for (i = 0; i < 4; i++){

        if (decy_data[i] != p_aes_data[i]){
            am_kprintf ("Aes ency-decy failed!\r\n");
            return ;
        }

        if (i == 3){
            am_kprintf ("Aes ency-decy success!\r\n");
        }
    }
}

/* end of file */
