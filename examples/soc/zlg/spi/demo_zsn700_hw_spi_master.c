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
 *   2. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_spi_master.c src_zsn700_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 20-03-09  yrz, first implementation
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_zsn700_hw_spi_master
 * \copydoc demo_zsn700_hw_spi_master.c
 */
 
/** [src_zsn700_hw_spi_master] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_zsn700_spi.h"


#define SPI_CFG_MODE_0      0           /**< \brief ģʽ0 */
#define SPI_CFG_MODE_1      1           /**< \brief ģʽ1 */
#define SPI_CFG_MODE_2      2           /**< \brief ģʽ2 */
#define SPI_CFG_MODE_3      3           /**< \brief ģʽ3 */

/** @} */

/** 
 * \brief SPI����ṹ��
 */
typedef struct spi_transfer {
    const void  *p_txbuf;           /**< \brief ָ�������ݻ����ָ�� */
    void        *p_rxbuf;           /**< \brief ָ��������ݻ����ָ�� */
    uint32_t     nbytes;            /**< \brief ���ݳ��� */
    uint32_t     flags;             /**< \brief SPI������Ʊ�־λ */
} spi_transfer_t;

spi_transfer_t g_spi_transfer;      /* ����һ��SPI����ṹ��ʵ�� */

static void spi_master_cs_ctr (amhw_zsn700_spi_t *p_hw_spi,
                               int                pin,
                               am_bool_t          state)
{

    /* Ƭѡ��Ч */
    if (state) {
        amhw_zsn700_spi_cs_sel(p_hw_spi,AM_TRUE);

        /* SPI�ײ�Ĵ����ڲ�CS���ƣ���ЧSPI����Ź�������һ������������� */
        amhw_zsn700_spi_cs_sel(p_hw_spi, AM_TRUE);

    /* Ƭѡ��Ч */
    } else {
        amhw_zsn700_spi_cs_sel(p_hw_spi, AM_FALSE);

        /* SPI�ײ�Ĵ����ڲ�CS���ƣ���ЧSPI����Ź�������һ������������� */
        amhw_zsn700_spi_cs_sel(p_hw_spi, AM_FALSE);
    }
}

/**
 * \brief SPI�ػ��������
 */
void spi_loop_trans (amhw_zsn700_spi_t *p_hw_spi,
                     spi_transfer_t *p_trans,
                     int32_t         cs_pin)
{
    uint32_t pos = 0;

    spi_master_cs_ctr(p_hw_spi, cs_pin, AM_TRUE);

    while(pos < p_trans->nbytes) {

        /* �ȴ����Է��� */
        while(amhw_zsn700_spi_flag_check (p_hw_spi,
                                          AMHW_ZSN700_SPI_FLAG_TX_EMPTY) ==
                                          AM_FALSE);

            amhw_zsn700_spi_tx_data8_put(p_hw_spi,
                                         *((uint8_t*)(p_trans->p_txbuf) + pos),
                                         AM_FALSE);

        /* �ȴ����Խ��� */
        while (amhw_zsn700_spi_flag_check (p_hw_spi,
                                           AMHW_ZSN700_SPI_FLAG_RX_NOT_EMPTY) ==
                                           AM_FALSE);

        *(uint8_t*)((uint8_t*)p_trans->p_rxbuf + pos) =
             amhw_zsn700_spi_rx_data8_get(p_hw_spi, AM_FALSE);
        pos += 1;
    }

    /* ����Ƭѡ */
    spi_master_cs_ctr(p_hw_spi, cs_pin, AM_FALSE);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_spi_master_entry (void    *p_hw_spi,
                                      int32_t  cs_pin)
{
    uint8_t         i;
    uint8_t         spi_send_buf[40];
    uint8_t         spi_recv_buf[40];
    const uint32_t  length     = 40;
    am_bool_t       error_ocur = AM_FALSE;
    spi_transfer_t *p_trans    = &g_spi_transfer;
    amhw_zsn700_spi_t *p_spi   = (amhw_zsn700_spi_t *)p_hw_spi;

    p_trans->p_txbuf = spi_send_buf;
    p_trans->p_rxbuf = spi_recv_buf;
    p_trans->nbytes  = length;

    /* ����Ϊ����ģʽ */
    amhw_zsn700_spi_mode_sel(p_spi, AMHW_ZSN700_SPI_MODE_TYPE_MASTER);

    /* ����SPIģʽ */
    amhw_zsn700_spi_clk_mode_set(p_spi, SPI_CFG_MODE_1);

    /* ����SPI���� */
    amhw_zsn700_spi_baud_rate_set(p_spi, AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV16);

    /* SPIʹ�� */
    amhw_zsn700_spi_enable(p_spi, AM_TRUE);

    /* �������� */
    for (i = 0; i < length; i++) {
        spi_send_buf[i] = i;
    }

    /* ���ݴ��� */
    spi_loop_trans(p_spi, p_trans, cs_pin);

    /* ���ݼ��� */
    for (i = 0; i < length; i++) {
        if (spi_recv_buf[i] != spi_send_buf[i]) {
            error_ocur = AM_TRUE;
            break;
        }
    }

    if (!error_ocur) {
        am_kprintf("trans done!\n");
    } else {
        am_kprintf("trans error!\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zsn700_hw_spi_master] */

/* end of file */
