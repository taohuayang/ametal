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
 * \snippet demo_hc32f460_hw_spi_master.c src_hc32f460_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 20-03-27  cds, first implementation
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hc32f460_hw_spi_master
 * \copydoc demo_hc32f460_hw_spi_master.c
 */
 
/** [src_hc32f460_hw_spi_master] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "hw/amhw_hc32f460_spi.h"


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



/**
 * \brief SPI�ػ��������
 */
void spi_loop_trans (amhw_hc32f460_spi_t *p_hw_spi,
                     spi_transfer_t      *p_trans,
                     int32_t              cs_pin,
                     uint32_t             cs_mdelay)
{
    uint32_t pos = 0;

    /* Ƭѡ��������͵�ƽ */
    am_gpio_set(cs_pin, AM_GPIO_LEVEL_LOW);

    /* CSѡͨ��������Ҫ�ȴ�100ms���ȴ��ӻ�(��Ƭ��)���������ò�����ȷ�������ݣ����򲿷����ݻᶪʧ������*/
    /* �����������ӻ���λ����Ӧ�Ͽ죬�ɿ���ȡ���˴���ʱ*/
    if (cs_mdelay != 0) {
        am_mdelay(cs_mdelay);
    }

    while (pos < p_trans->nbytes) {

        /* �ȴ����Է��� */
        while(amhw_hc32f460_spi_flag_check (p_hw_spi,
                                            AMHW_HC32F460_SPI_STATUS_TXBUFFER_EMPTY) ==
                                            AM_FALSE);

            amhw_hc32f460_spi_tx_data8_put(p_hw_spi,
                                           *((uint8_t*)(p_trans->p_txbuf) + pos));

        /* �ȴ����Խ��� */
        while (amhw_hc32f460_spi_flag_check (p_hw_spi,
                                             AMHW_HC32F460_SPI_STATUS_RXBUFFER_FULL) ==
                                             AM_FALSE);

        *(uint8_t*)((uint8_t*)p_trans->p_rxbuf + pos) =
             amhw_hc32f460_spi_rx_data8_get(p_hw_spi);
        pos += 1;
    }

    /* Ƭѡ��������ߵ�ƽ */
    am_gpio_set(cs_pin, AM_GPIO_LEVEL_HIGH);
}

/**
 * \brief �������
 */
void demo_hc32f460_hw_spi_master_entry (void    *p_hw_spi,
                                        int32_t  cs_pin)
{
    uint8_t              i;
    uint8_t              spi_send_buf[40];
    uint8_t              spi_recv_buf[40];
    const uint32_t       length     = 40;
    am_bool_t            error_ocur = AM_FALSE;
    spi_transfer_t      *p_trans    = &g_spi_transfer;
    amhw_hc32f460_spi_t *p_spi   = (amhw_hc32f460_spi_t *)p_hw_spi;

    p_trans->p_txbuf = spi_send_buf;
    p_trans->p_rxbuf = spi_recv_buf;
    p_trans->nbytes  = length;

    /* ����Ϊ����ģʽ */
    amhw_hc32f460_spi_mode_sel(p_spi, AMHW_HC32F460_SPI_MODE_MASTER);

    /* ����SPIͨ��ģʽ */
    amhw_hc32f460_spi_trans_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_TRANS_MODE_FULL_DUPLEX);

    /* ����SPI����ģʽ������/���ߣ� */
    amhw_hc32f460_spi_work_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_WORK_MODE_4LINE);

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_hc32f460_spi_clk_mode_set(p_spi, 0x3 & SPI_CFG_MODE_1);

    /* ֡��ʽ���ã��ȷ���MSB */
    amhw_hc32f460_spi_first_bit_position_set(p_hw_spi, AMHW_HC32F460_SPI_MSB_FIRST);

    /* ����SPI���� */
    amhw_hc32f460_spi_clk_div_set(p_spi, AMHW_HC32F460_SPI_CLK_DIV_16);

    /* ���ݳ���Ϊ8 */
    amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                      AMHW_HC32F460_SPI_DATA_LENGTH_BIT8);

    /* SPIʹ�� */
    amhw_hc32f460_spi_enable(p_spi, AM_TRUE);

    /* �������� */
    for (i = 0; i < length; i++) {
        spi_send_buf[i] = i;
    }

    /* ���ݴ��� */
    spi_loop_trans(p_spi, p_trans, cs_pin, 100);

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
/** [src_hc32f460_hw_spi_master] */

/* end of file */
