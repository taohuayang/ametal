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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_aes_ency_decy.c src_zsn700_hw_aes_ency_decy
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-09  YRZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_aes_ency_decy
 * \copydoc demo_zsn700_hw_aes_ency_decy.c
 */

/** [src_zsn700_hw_aes_ency_decy] */
#include "ametal.h"
#include "am_zsn700.h"
#include "am_board.h"
#include "am_zsn700_aes.h"
#include "hw/amhw_zsn700_aes.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zsn700_aes_t       *gp_hw_aes   = NULL;  /**< \brief aes ���� */

/**< \brief ��ż��ܺ������ */
static uint32_t ency_data[4] = {0};

/**< \brief ��Ž��ܺ������ */
static uint32_t decy_data[4]  = {0};

/**
 * \brief AES ����
 */
static void aes_ency (uint8_t key_len,
                     uint32_t *p_aes_data,
                     uint32_t *p_key_data,
                     uint32_t *p_ency_data)
{
    /* ������Ҫ���ܵ��������� */
    amhw_zsn700_aes_data_write (gp_hw_aes, p_aes_data);

    /* ������Կ  */
    switch (key_len){

        case AM_ZSN700_AES_KEY_LEN_128_BIT:
            /* ������Կ���� */
            amhw_zsn700_aes_key_len_sel (gp_hw_aes,
                                         AMHW_ZSN700_AES_KEY_LEN_128_BIT);

            amhw_zsn700_aes_key_save (gp_hw_aes,
                                      AMHW_ZSN700_AES_KEY_LEN_128_BIT,
                                      p_key_data);
            break;
        case AM_ZSN700_AES_KEY_LEN_192_BIT:
            /* ������Կ���� */
            amhw_zsn700_aes_key_len_sel (gp_hw_aes,
                                         AMHW_ZSN700_AES_KEY_LEN_192_BIT);

            amhw_zsn700_aes_key_save (gp_hw_aes,
                                      AMHW_ZSN700_AES_KEY_LEN_192_BIT,
                                      p_key_data);
            break;
        case AM_ZSN700_AES_KEY_LEN_256_BIT:
            /* ������Կ���� */
            amhw_zsn700_aes_key_len_sel (gp_hw_aes,
                                         AMHW_ZSN700_AES_KEY_LEN_256_BIT);

            amhw_zsn700_aes_key_save (gp_hw_aes,
                                      AMHW_ZSN700_AES_KEY_LEN_256_BIT,
                                      p_key_data);
            break;
    }

    /* ʹ�ܼ������� */
    amhw_zsn700_aes_encrypt (gp_hw_aes);

    /* ������������ */
    amhw_zsn700_aes_start (gp_hw_aes);

    /* �ȴ������������ */
    while (amhw_zsn700_aes_stu_check (gp_hw_aes)){

        am_kprintf ("Encrypt ... !\r\n");

        /* ��ʱ10us�������ʱ�����ʧ�� */
        am_udelay (10);
        if (amhw_zsn700_aes_stu_check (gp_hw_aes)){

            return ;
        }
    }

    /* ��ȡ���ܺ������ */
    amhw_zsn700_aes_data_read (gp_hw_aes, p_ency_data);
}

/**
 * \brief AES ����
 */
static void aes_decy (uint8_t key_len,
                     uint32_t *p_ency_data,
                     uint32_t *p_key_data,
                     uint32_t *p_decy_data)
{
    /* ������Ҫ���ܵ��������� */
    amhw_zsn700_aes_data_write (gp_hw_aes, p_ency_data);

    /* ������Կ  */
    switch (key_len){

        case AM_ZSN700_AES_KEY_LEN_128_BIT:
            /* ������Կ���� */
            amhw_zsn700_aes_key_len_sel (gp_hw_aes,
                                         AMHW_ZSN700_AES_KEY_LEN_128_BIT);

            amhw_zsn700_aes_key_save (gp_hw_aes,
                                      AMHW_ZSN700_AES_KEY_LEN_128_BIT,
                                      p_key_data);
            break;
        case AM_ZSN700_AES_KEY_LEN_192_BIT:
            /* ������Կ���� */
            amhw_zsn700_aes_key_len_sel (gp_hw_aes,
                                         AMHW_ZSN700_AES_KEY_LEN_192_BIT);

            amhw_zsn700_aes_key_save (gp_hw_aes,
                                      AMHW_ZSN700_AES_KEY_LEN_192_BIT,
                                      p_key_data);
            break;
        case AM_ZSN700_AES_KEY_LEN_256_BIT:
            /* ������Կ���� */
            amhw_zsn700_aes_key_len_sel (gp_hw_aes,
                                         AMHW_ZSN700_AES_KEY_LEN_256_BIT);

            amhw_zsn700_aes_key_save (gp_hw_aes,
                                      AMHW_ZSN700_AES_KEY_LEN_256_BIT,
                                      p_key_data);
            break;
    }

    /* ʹ�ܽ������� */
    amhw_zsn700_aes_decrypt (gp_hw_aes);

    /* ������������ */
    amhw_zsn700_aes_start (gp_hw_aes);

    /* �ȴ������������ */
    while (amhw_zsn700_aes_stu_check (gp_hw_aes)){

        am_kprintf ("Encrypt ... !\r\n");

        /* ��ʱ10us�������ʱ�����ʧ�� */
        am_udelay (10);
        if (amhw_zsn700_aes_stu_check (gp_hw_aes)){

            return ;
        }
    }

    /* ��ȡ���ܺ������ */
    amhw_zsn700_aes_data_read (gp_hw_aes, p_decy_data);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_aes_ency_decy_entry (void     *p_hw_aes,
                                         uint8_t   key_len,
                                         uint32_t *p_aes_data,
                                         uint32_t *p_key_data)
{
    int i = 0;

    if (p_hw_aes == NULL)
    {
        return ;
    }

    gp_hw_aes  = (amhw_zsn700_aes_t *)p_hw_aes;

    /* ���� */
    aes_ency (key_len, p_aes_data, p_key_data, ency_data);

    /* ���� */
    aes_decy (key_len, ency_data, p_key_data, decy_data);

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
