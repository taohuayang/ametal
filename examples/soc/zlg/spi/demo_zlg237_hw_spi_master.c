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
 *   1. ���������� SPI�ӿ���ӻ�SPI�ӿڶ�Ӧ���� ��
 *   2. �ȸ�λ�������ٸ�λ�ӻ�����������������
 *   3. �ر�ע�⣬������������λ���������һ����Ч��Ƭѡ�źţ����´ӻ�����ʶ���ϴ�һ����ʷ���ݡ�
 *      ��ע�ⲽ��2����˳���Ա���ӻ����������ϴ���
 *
 * - ʵ������
 *   1. �������͵����ݲ����ۼ�1���ӻ����ص����ݱ��ֲ��䡣
 *   2. ���Դ��ڴ�ӡͨ��SPI���պͷ��͵ľ������ݡ�
 *
 * \par Դ����
 * \snippet demo_zlg237_hw_spi_master.c src_zlg237_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 19-07-23  ari, first implementation
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_zlg237_hw_spi_master
 * \copydoc demo_zlg237_hw_spi_master.c
 */
 
/** [src_zlg_hw_spi_master] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg237_spi.h"

/**
 * \name SPI����ṹ�����ò���
 */

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
    uint32_t     spi_clk;           /**< \brief SPIʱ��Ƶ�� */
} spi_transfer_t;

spi_transfer_t g_spi_transfer;      /* ����һ��SPI����ṹ��ʵ�� */

static void spi_master_cfg (amhw_zlg237_spi_t *p_hw_spi)
{
    /* �ر�spi����*/
    amhw_zlg237_spi_disable(p_hw_spi);

    /* NSS�����������*/
    amhw_zlg237_spi_ssm_enable(p_hw_spi);

    /* �ر�Ӳ��SPI��NSS�������*/
    amhw_zlg237_spi_ssout_disable(p_hw_spi);

    /* ��������£�NSS�ڲ�Ϊ�ߣ��������޹ء��ر�ע�⣬����Ӳ��������������ó�����ģʽ��NSS����Ϊ��*/
    amhw_zlg237_spi_ssi_set(p_hw_spi,AMHW_ZLG237_SPI_SSI_TO_NSS_ENABLE);

    /* ����Ϊ����ģʽ*/
    amhw_zlg237_spi_master_salver_set(p_hw_spi, AMHW_ZLG237_SPI_MASTER);

    /* ����ʱ����λ�ͼ��� */
    amhw_zlg237_spi_clk_mode_set(p_hw_spi, SPI_CFG_MODE_1 );

    /* ֡��ʽ���ã��ȷ���MSB*/
    amhw_zlg237_spi_lsbfirst_set(p_hw_spi, AMHW_ZLG237_SPI_LSB_FIRST_SEND_MSB);

    /* ��Ƶϵ��Ϊ128*/
    amhw_zlg237_spi_baudratefre_set(p_hw_spi,
                                    AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_128);

    /* ���ݳ���Ϊ8*/
    amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_8BIT);

    /* SPIʹ��*/
    amhw_zlg237_spi_enable(p_hw_spi);

}

/**
 * \brief SPI�ػ��������
 */
void spi_loop_trans (amhw_zlg237_spi_t *p_hw_spi,
                     spi_transfer_t    *p_trans,
                     int32_t            cs_pin,
					 uint32_t           cs_mdelay)
{
    uint32_t pos = 0;

    /* Ƭѡ��������͵�ƽ */
    am_gpio_set(cs_pin, AM_GPIO_LEVEL_LOW);

    /* CSѡͨ��������Ҫ�ȴ�100ms���ȴ��ӻ�(��Ƭ��)���������ò�����ȷ�������ݣ����򲿷����ݻᶪʧ������*/
    /* �����������ӻ���λ����Ӧ�Ͽ죬�ɿ���ȡ���˴���ʱ*/
    if(cs_mdelay != 0) {
    	am_mdelay(cs_mdelay);
    }

    while(pos < p_trans->nbytes) {

        /* �ȴ����Է��� */
        while (amhw_zlg237_spi_status_flag_check (
            p_hw_spi, AMHW_ZLG237_SPI_TX_EMPTY_FLAG) == AM_FALSE);

        amhw_zlg237_spi_tx_put(p_hw_spi,*((uint8_t*)(p_trans->p_txbuf) + pos));

        /* �ȴ����Խ��� */
        while (amhw_zlg237_spi_status_flag_check (
            p_hw_spi,AMHW_ZLG237_SPI_RX_NOT_EMPTY_FLAG) == AM_FALSE) {
        	;
        }

        *(uint8_t*)((uint8_t*)p_trans->p_rxbuf + pos) =
            amhw_zlg237_spi_rx_get(p_hw_spi);
        pos += 1;
    }

    /* Ƭѡ��������ߵ�ƽ */
    am_gpio_set(cs_pin, AM_GPIO_LEVEL_HIGH);
}

/**
 * \brief �������
 */
void demo_zlg237_hw_spi_master_entry (amhw_zlg237_spi_t *p_hw_spi,
                                      int32_t            cs_pin,
                                      uint32_t           clk_rate,
                                      uint32_t           cs_mdelay)
{
    uint8_t         i = 0, t = 0;
    uint8_t         spi_send_buf[21] = {0};
    uint8_t         spi_recv_buf[21] = {0};
    const uint32_t  length     = 20;
    spi_transfer_t *p_trans    = &g_spi_transfer;

    p_trans->p_txbuf = spi_send_buf;
    p_trans->p_rxbuf = spi_recv_buf;
    p_trans->nbytes  = length;
    p_trans->spi_clk = clk_rate;

    /* ���췢������*/
    for (i = 0; i < length; i++) {
        spi_send_buf[i] = i +'A';
    }

    /* SPI����ģʽ���� */
    spi_master_cfg(p_hw_spi);

    AM_FOREVER {

        /* ���ݴ��� */
        spi_loop_trans(p_hw_spi, p_trans, cs_pin, cs_mdelay);

        am_kprintf("spi_recv_buf: %s\r\n",spi_recv_buf);
        am_kprintf("spi_send_buf: %s\r\n",spi_send_buf);

        /* ��ս��ջ����� */
        for (i = 0; i < length; i++) {
            spi_recv_buf[i] = '\0';
        }

        /* �����µķ�������*/
        for (i = 0; i < length; i++) {
            spi_send_buf[i] = i +'A' + t;
        }

        t++;

        if (t == 50) {
            t = 0;
        }
        am_mdelay(1000);
    }
}
/** [src_zlg_hw_spi_master] */

/* end of file */
