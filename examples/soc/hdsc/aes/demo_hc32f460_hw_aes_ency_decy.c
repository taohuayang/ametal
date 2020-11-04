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
 * \snippet demo_hc32f460_hw_aes_ency_decy.c src_hc32f460_hw_aes_ency_decy
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-26  cds, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_hw_aes_ency_decy
 * \copydoc demo_hc32f460_hw_aes_ency_decy.c
 */

/** [src_hc32f460_hw_aes_ency_decy] */
#include "ametal.h"
#include "am_hc32f460.h"
#include "am_board.h"
#include "am_hc32f460_aes.h"
#include "hw/amhw_hc32f460_aes.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_hc32f460_aes_t       *gp_hw_aes   = NULL;  /**< \brief aes ���� */

/**< \brief ��ż��ܺ������ */
static uint32_t ency_data[4] = {0};

/**< \brief ��Ž��ܺ������ */
static uint32_t decy_data[4]  = {0};

/**
 * \brief AES ����
 */
static void aes_ency (uint32_t *p_aes_data,
                      uint32_t *p_key_data,
                      uint32_t *p_ency_data)
{
    /* ������Ҫ���ܵ��������� */
    amhw_hc32f460_aes_data_write (gp_hw_aes, p_aes_data);

    /* ������Կ  */
    amhw_hc32f460_aes_key_save (gp_hw_aes, p_key_data);

    /* ʹ�ܼ������� */
    amhw_hc32f460_aes_encrypt (gp_hw_aes);

    /* ������������ */
    amhw_hc32f460_aes_start (gp_hw_aes);

    /* �ȴ������������ */
    while (amhw_hc32f460_aes_stu_check (gp_hw_aes)){

        am_kprintf ("Encrypt ... !\r\n");

        /* ��ʱ10us�������ʱ�����ʧ�� */
        am_udelay (10);
        if (amhw_hc32f460_aes_stu_check (gp_hw_aes)){

            return ;
        }
    }

    /* ��ȡ���ܺ������ */
    amhw_hc32f460_aes_data_read (gp_hw_aes, p_ency_data);
}

/**
 * \brief AES ����
 */
static void aes_decy (uint32_t *p_ency_data,
                      uint32_t *p_key_data,
                      uint32_t *p_decy_data)
{
    /* ������Ҫ���ܵ��������� */
    amhw_hc32f460_aes_data_write (gp_hw_aes, p_ency_data);

    /* ������Կ  */
    amhw_hc32f460_aes_key_save (gp_hw_aes, p_key_data);

    /* ʹ�ܽ������� */
    amhw_hc32f460_aes_decrypt (gp_hw_aes);

    /* ������������ */
    amhw_hc32f460_aes_start (gp_hw_aes);

    /* �ȴ������������ */
    while (amhw_hc32f460_aes_stu_check (gp_hw_aes)){

        am_kprintf ("Decrypt ... !\r\n");

        /* ��ʱ10us�������ʱ�����ʧ�� */
        am_udelay (10);
        if (amhw_hc32f460_aes_stu_check (gp_hw_aes)){

            return ;
        }
    }

    /* ��ȡ���ܺ������ */
    amhw_hc32f460_aes_data_read (gp_hw_aes, p_decy_data);
}

/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_hw_aes_ency_decy_entry (void     *p_hw_aes,
                                           uint32_t *p_aes_data,
                                           uint32_t *p_key_data)
{
    int i = 0;

    if (p_hw_aes == NULL)
    {
        return ;
    }

    gp_hw_aes  = (amhw_hc32f460_aes_t *)p_hw_aes;

    /* ���� */
    aes_ency (p_aes_data, p_key_data, ency_data);

    /* ���� */
    aes_decy (ency_data, p_key_data, decy_data);

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

    while (1){
        ;
    }
}

/* end of file */
