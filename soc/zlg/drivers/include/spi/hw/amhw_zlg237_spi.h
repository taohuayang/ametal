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
 * \brief SPI Ӳ�������ӿ�
 *
 * 1. ֧�������ʹӻ����䣻
 * 2. ֧�ֵ�������ģʽ��
 * 3. ȫ˫��ͬ������
 * 4. ֧��DMA����(���ͺͽ���)��
 * 5. �����ʿ����ã�
 * 6. ʱ����λ�ͼ��Կ����ã�
 * 7. ������LSB����MSB���䣻
 * 8. ��������ƥ��������ݣ�ƥ��ɹ�ʱ�����жϣ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-18  ari, first implementation
 * \endinternal
 */

#ifndef _AMHW_ZLG237_SPI_H_
#define _AMHW_ZLG237_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zlg237_if_spi
 * \copydoc amhw_zlg237_spi.h
 * @{
 */

/**
 * \brief SPI structure of register
 */
typedef struct amhw_zlg237_spi {
    __IO uint16_t  cr1;           /**< \brief SPI ���ƼĴ���1 */
    __I  uint16_t  reserve1;      /**< \brief ����λ */
    __IO uint16_t  cr2;           /**< \brief SPI ���ƼĴ���2 */
    __I  uint16_t  reserve2;      /**< \brief ����λ */
    __IO uint16_t  sr;            /**< \brief SPI ״̬�Ĵ��� */
    __I  uint16_t  reserve3;      /**< \brief ����λ */
    __IO uint16_t  dr;            /**< \brief SPI ���ݼĴ��� */
    __I  uint16_t  reserve4;      /**< \brief ����λ */
    __IO uint16_t  crcpr;         /**< \brief SPI CRC����ʽ�Ĵ��� */
    __I  uint16_t  reserve5;      /**< \brief ����λ */
    __I  uint16_t  rxcrcr;        /**< \brief SPI RX_CRC�Ĵ��� */
    __I  uint16_t  reserve6;      /**< \brief ����λ */
    __I  uint16_t  txcrcr;        /**< \brief SPI TX_CRC�Ĵ��� */
    __I  uint16_t  reserve7;      /**< \brief ����λ */
    __IO uint16_t  cr3;           /**< \brief SPI ���ƼĴ���3 */
    __I  uint16_t  reserve8;      /**< \brief ����λ */
} amhw_zlg237_spi_t;

/**
 * \brief BIDIMODE ģʽѡ�񡪡�˫��˫��ģʽ
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_bidimode_double (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 &= ~(1u << 15);
}

/**
 * \brief BIDIMODE ģʽѡ�񡪡�����˫��ģʽ
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_bidimode_single (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 |= (1u << 15);
}

/**
 * \brief BIDIOE ˫��ģʽ��������ơ������루ֻ�գ�
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note �� BIDIMODEλһ������ڡ�����˫��ģʽ�����ݵ��������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_bidioe_input (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 &= ~(1u << 14);
}

/**
 * \brief BIDIOE ˫��ģʽ��������ơ��������ֻ����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note �� BIDIMODEλһ������ڡ�����˫��ģʽ�����ݵ��������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_bidioe_output (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 |= (1u << 14);
}

/**
 * \brief CRCEN��Ӳ�� CRCУ�����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ֻ���ڽ�ֹ SPI ʱ(SPE=0)������д��λ�����������λֻ����ȫ˫��ģʽ��ʹ�á�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_crc_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 &= ~(1u << 13);
}

/**
 * \brief CRCEN��Ӳ�� CRCУ��ʹ��
 * \\param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ֻ���ڽ�ֹ SPI ʱ(SPE=0)������д��λ�����������λֻ����ȫ˫��ģʽ��ʹ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_crc_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 |= (1u << 13);
}

/**
 * \brief current status
 *  @{
 */
#define AMHW_ZLG237_SPI_CRC_NEXT_BUFF          0     /**< ��һ�����͵�ֵ���Է��ͻ����� */
#define AMHW_ZLG237_SPI_CRC_NEXT_CRCREG        1     /**< ��һ�����͵�ֵ����CRC�Ĵ��� */

#define AMHW_ZLG237_SPI_DATA_8BIT              0     /**<  8λ����֡��ʽ */
#define AMHW_ZLG237_SPI_DATA_16BIT             1     /**< 16λ����֡��ʽ */
/** @}*/

/**
 * \brief CRCNEXT ��һ�����͵�ֵ��Դ����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_CRC_NEXT_BUFF  ��
 *                            AMHW_ZLG237_SPI_CRC_NEXT_CRCREG
 *
 * \note ���� SPI_DR�Ĵ���д�����һ�����ݺ�Ӧ�������ø�λ
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_crcnext_set (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr1 = (p_hw_spi->cr1 & (~(1u << 12))) | ((uint16_t)flag << 12);
}

/**
 * \brief DFF ����֡��ʽ��������
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_DATA_8BIT  ��
 *                            AMHW_ZLG237_SPI_DATA_16BIT
 *
 * \note ��ֻ�е� SPI��ֹ(SPE=0)ʱ������д��λ���������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_data_length_set (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr1 = (p_hw_spi->cr1 & (~(1u << 11))) | ((uint16_t)flag << 11);
}

/**
 * \brief RXONLY ֻ���ս���
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ��λ�� BIDIMODE λһ������ڡ�˫��˫��ģʽ�µĴ��䷽���ڶ�����豸��
 *       �����У���δ�����ʵĴ��豸�ϸ�λ���� 1��ʹ��ֻ�б����ʵĴ��豸��������Ӷ���
 *       ����������������ݳ�ͻ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_rxonly_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 &= ~(1u << 10);
}

/**
 * \brief RXONLY ֻ����ʹ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ��λ�� BIDIMODE λһ������ڡ�˫��˫��ģʽ�µĴ��䷽���ڶ�����豸��
 *       �����У���δ�����ʵĴ��豸�ϸ�λ���� 1��ʹ��ֻ�б����ʵĴ��豸��������Ӷ���
 *       ����������������ݳ�ͻ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_rxonly_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 |= (1u << 10);
}

/**
 * \brief SSM ������豸������ܣ�NSS���������ܣ�
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note �� SSM ����λʱ��NSS �����ϵĵ�ƽ�� SSI λ��ֵ����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_ssm_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 &= ~(1u << 9);
}

/**
 * \brief SSM ������豸����ʹ�� ��NSS�������ʹ�ܣ�
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note �� SSM ����λʱ��NSS �����ϵĵ�ƽ�� SSI λ��ֵ����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_ssm_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 |= (1u << 9);
}

/**
 * \brief current status
 *  @{
 */
#define AMHW_ZLG237_SPI_SSI_TO_NSS_IGNORED      0     /**< NSS���ź���  */
#define AMHW_ZLG237_SPI_SSI_TO_NSS_ENABLE       1     /**< NSS����ʹ��  */

#define AMHW_ZLG237_SPI_LSB_FIRST_SEND_MSB      0     /**< ֡��ʽ����   �ȷ��� MSB */
#define AMHW_ZLG237_SPI_LSB_FIRST_SEND_LSB      1     /**< ֡��ʽ����   �ȷ���LSB */
/** @}*/

/**
 * \brief SSI �ڲ����豸ѡ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_SSI_TO_NSS_IGNORED  ��
 *                            AMHW_ZLG237_SPI_SSI_TO_NSS_ENABLE
 *
 * \note ����λֻ�� SSMλΪ��1��ʱ�����塣�������� NSS�ϵĵ�ƽ���� NSS�����ϵ� I/O������Ч�����������޹�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_ssi_set (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr1 = (p_hw_spi->cr1 & (~(1u << 8))) | ((uint16_t)flag << 8);
}

/**
 * \brief LSBFIRST ֡��ʽ����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_LSB_FIRST_MSB  ��
 *                            AMHW_ZLG237_SPI_LSB_FIRST_LSB
 *
 * \note ����ͨ���ڽ���ʱ���ܸı��λ��ֵ��
 *
 * \return none
 */
am_static_inline

void amhw_zlg237_spi_lsbfirst_set (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr1 = (p_hw_spi->cr1 & (~(1u << 7))) | ((uint16_t)flag << 7);
}

/**
 * \brief SPE SPI����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 &= ~(1u << 6);
}

/**
 * \brief SPE SPIʹ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr1 |= (1u << 6);
}

/**
 * \brief current status
 *  @{
 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_2       0     /**< fPCLK/2 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_4       1     /**< fPCLK/4 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_8       2     /**< fPCLK/8 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_16      3     /**< fPCLK/16 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_32      4     /**< fPCLK/32 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_64      5     /**< fPCLK/64 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_128     6     /**< fPCLK/128 */
#define AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_256     7     /**< fPCLK/256 */
/** @}*/

/**
 * \brief BR[2:0] �����ʷ�Ƶ����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_2
 *                            .
 *                            .
 *                            .
 *                            AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_256
 *
 * \note ����ͨ���ڽ���ʱ���ܸı��λ��ֵ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_baudratefre_set (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr1 = (p_hw_spi->cr1 & (~(0x7u << 3))) | ((uint16_t)( 0x7u & flag ) << 3);
}

/**
 * \brief current status
 *  @{
 */
#define AMHW_ZLG237_SPI_MASTER                   1     /**< ����Ϊ���豸 */
#define AMHW_ZLG237_SPI_SLAVER                   0     /**< ����Ϊ���豸 */
/** @}*/

/**
 * \brief MSTR ���豸ѡ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_MASTER  ��
 *                            AMHW_ZLG237_SPI_MASTER
 *
 * \note ����ͨ���ڽ���ʱ���ܸı��λ��ֵ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_master_salver_set (amhw_zlg237_spi_t *p_hw_spi, uint16_t flag)
{
    p_hw_spi->cr1 = (p_hw_spi->cr1 & (~(1u << 2))) | ((uint16_t)flag << 2);
}

/**
 * \brief SPI Clock mode set
 * \ @{
 */
#define AMHW_ZLG237_SPI_CLK_MODE_0    (0U << 0) /* ģʽ0�����е͵�ƽ����һ��ʱ���أ�*/
#define AMHW_ZLG237_SPI_CLK_MODE_1    (1U << 0) /* ģʽ1�����е͵�ƽ���ڶ���ʱ���أ�*/
#define AMHW_ZLG237_SPI_CLK_MODE_2    (2U << 0) /* ģʽ2�����иߵ�ƽ����һ��ʱ���أ�*/
#define AMHW_ZLG237_SPI_CLK_MODE_3    (3U << 0) /* ģʽ3�����иߵ�ƽ���ڶ���ʱ���أ�*/
/** @}*/

/**
 * \brief SPI ʱ��ģʽѡ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG_SPI_CLK_MODE_0  ��
 *                            AMHW_ZLG_SPI_CLK_MODE_1  ��
 *                            AMHW_ZLG_SPI_CLK_MODE_2  ��
 *                            AMHW_ZLG_SPI_CLK_MODE_3  ��
 *
 * \note ����ͨ���ڽ���ʱ���ܸı��λ��ֵ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_clk_mode_set (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr1 = (p_hw_spi->cr1 & (~(3u << 0))) | ((uint16_t)flag << 0);
}

/**
 * \brief current status
 *  @{
 */
#define AMHW_ZLG237_SPI_INT_TX_EMPTY          (1u << 7)     /**< ���ͻ��������ж�ʹ�ܿ���λ */
#define AMHW_ZLG237_SPI_INT_RX_NOT_EMPTY      (1u << 6)     /**< ���ջ������ǿ��ж�ʹ�ܿ���λ */
#define AMHW_ZLG237_SPI_INT_ERROR             (1u << 5)     /**< �����ж�ʹ�ܿ���λ */
#define AMHW_ZLG237_SPI_INT_ALL             (0x7u << 5)     /**< �����ж�ʹ�ܿ���λ */

/** @}*/

/**
 * \brief cr2�жϿ��ƽ���
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_INT_TX_EMPTY      ��
 *                            AMHW_ZLG237_SPI_INT_RX_NOT_EMPTY  ��
 *                            AMHW_ZLG237_SPI_INT_ERROR
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_int_disable (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr2 &= ~flag;
}

/**
 * \brief cr2�жϿ���ʹ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_INT_TX_EMPTY      ��
 *                            AMHW_ZLG237_SPI_INT_RX_NOT_EMPTY  ��
 *                            AMHW_ZLG237_SPI_INT_ERROR
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_int_enable (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->cr2 |= flag;
}

/**
 * \brief SSOE Ӳ��SPI��NSS�����������
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_ssout_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(1u << 2);
}

/**
 * \brief SSOE Ӳ��SPI��NSS�������ʹ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_ssout_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (1u << 2);
}

/**
 * \brief TXDMAEN ���ͻ����� DMA����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_dma_tx_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(1u << 1);
}

/**
 * \brief TXDMAEN ���ͻ����� DMAʹ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_dma_tx_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (1u << 1);
}

/**
 * \brief RXDMAEN ���ջ�����DMA����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_dma_rx_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(1u << 0);
}

/**
 * \brief RXDMAEN ���ջ�����DMAʹ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_dma_rx_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (1u << 0);
}

/**
 * \brief current status
 *  @{
 */
/** æ��־
 *
 *  note: ��λ��Ӳ����λ���߸�λ
 */
#define AMHW_ZLG237_SPI_BUSY_FLAG            (1u << 7)

/** �����־
 *
 *  note: ��λ��Ӳ����λ����������и�λ
 */
#define AMHW_ZLG237_SPI_OVERRUN_FLAG         (1u << 6)

/** ģʽ�����־
 *
 *  note: ��λ��Ӳ����λ����������и�λ��
 */
#define AMHW_ZLG237_SPI_MDOE_ERROR_FLAG      (1u << 5)

/** CRC�����־
 *
 *  note ����λ��Ӳ����λ�������д��0������λ��
 */
#define AMHW_ZLG237_SPI_CRC_ERROR_FLAG       (1u << 4)

/** �����־
 *
 *  note: �ñ�־λ��Ӳ���á�1������һ����������塮0��
 *       �� SPI ģʽ�²�ʹ�á�
 */
#define AMHW_ZLG237_SPI_UNDERRUN_FLAG        (1u << 3)

/** ������־
 *  ����������־���ԣ����ú�����ķ���ֵ�ֱ����
 *              AM_TRUE  : ��Ҫ������߽���������
 *              AM_FALSE : ��Ҫ������߽���������
 *
 *  note ���� SPI ģʽ�²�ʹ�á��� PCM ģʽ�������塣
 */
#define AMHW_ZLG237_SPI_CHANNEL_SIDE_FLAG    (1u << 2)

/** ���ͻ���Ϊ�ձ�־
 *
 *  note ��ֻ��
 */
#define AMHW_ZLG237_SPI_TX_EMPTY_FLAG        (1u << 1)

/** ���ջ���ǿձ�־
 *
 *  note ��ֻ��
 */
#define AMHW_ZLG237_SPI_RX_NOT_EMPTY_FLAG    (1u << 0)

/** @}*/

/**
 * \brief ״̬�Ĵ�����־λ��ȡ
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_SPI_BUSY_FLAG          ��
 *                            AMHW_ZLG237_SPI_OVERRUN_FLAG       ��
 *                            AMHW_ZLG237_SPI_MDOE_ERROR_FLAG    ��
 *                            AMHW_ZLG237_SPI_CRC_ERROR_FLAG     ��
 *                            AMHW_ZLG237_SPI_UNDERRUN_FLAG      ��
 *                            AMHW_ZLG237_SPI_CHANNEL_SIDE_FLAG  ��
 *                            AMHW_ZLG237_SPI_TX_EMPTY_FLAG      ��
 *                            AMHW_ZLG237_SPI_RX_NOT_EMPTY_FLAG
 *
 * \return none
 */
am_static_inline
am_bool_t amhw_zlg237_spi_status_flag_check (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    return (p_hw_spi->sr & flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ״̬�Ĵ�����־λ���
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag     : �������Ӧֻ��Ϊ   AMHW_ZLG237_SPI_CRC_ERROR_FLAG
 *                       �����궨��ֻ��������������и�λ
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_status_flag_clr (amhw_zlg237_spi_t *p_hw_spi, uint8_t flag)
{
    p_hw_spi->sr &= ~flag;
}

/**
 * \brief д���ݺ���
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] data     : ��д������
 *
 * \note : ���� SPI_CR1�� DFFλ������֡��ʽ��ѡ�����ݵķ��ͺͽ��տ����� 8λ���� 16λ�ġ�
 *         Ϊ��֤��ȷ�Ĳ�������Ҫ������ SPI ֮ǰ��ȷ��������֡��ʽ.
 *
 *         ���� 8 λ�����ݣ��������� 8λ�ģ����ͺͽ���ʱֻ���õ�SPI_DR[7:0]���ڽ���ʱ��
 *         SPI_DR[15:8]��ǿ��Ϊ 0��
 *
 *         ���� 16 λ�����ݣ��������� 16 λ�ģ����ͺͽ���ʱ���õ��������ݼĴ������� SPI_DR[15:0]��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_tx_put (amhw_zlg237_spi_t *p_hw_spi, uint16_t data)
{
    p_hw_spi->dr = (uint16_t)data;
}

/**
 * \brief �����ݺ���
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note : ���� SPI_CR1�� DFFλ������֡��ʽ��ѡ�����ݵķ��ͺͽ��տ����� 8λ���� 16λ�ġ�
 *         Ϊ��֤��ȷ�Ĳ�������Ҫ������ SPI ֮ǰ��ȷ��������֡��ʽ��
 *
 *         ���� 8 λ�����ݣ��������� 8λ�ģ����ͺͽ���ʱֻ���õ�SPI_DR[7:0]���ڽ���ʱ��
 *         SPI_DR[15:8]��ǿ��Ϊ 0��
 *
 *         ���� 16 λ�����ݣ��������� 16 λ�ģ����ͺͽ���ʱ���õ��������ݼĴ������� SPI_DR[15:0]��
 *
 * \return ��������
 */
am_static_inline
uint16_t amhw_zlg237_spi_rx_get (amhw_zlg237_spi_t *p_hw_spi)
{
    return p_hw_spi->dr;
}

/**
 * \brief CRC����ʽ�Ĵ���
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag     : ��д��CRC����ʱ�õ��Ķ���ʽ����
 *
 * \note ��  �üĴ��������� CRC����ʱ�õ��Ķ���ʽ��
 *         �临λֵΪ 0x0007������Ӧ�ÿ�������������ֵ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_crcpr_write (amhw_zlg237_spi_t *p_hw_spi, uint16_t crc_data)
{
    p_hw_spi->crcpr = crc_data;
}

/**
 * \brief CRC����ʽ�Ĵ���  ��������
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ��  �üĴ��������� CRC����ʱ�õ��Ķ���ʽ��
 *         �临λֵΪ 0x0007������Ӧ�ÿ�������������ֵ��
 *
 * \return ��ǰ�Ĵ����洢��CRC����ʱ�õ��Ķ���ʽ����
 */
am_static_inline
uint16_t amhw_zlg237_spi_crcpr_read (amhw_zlg237_spi_t *p_hw_spi)
{
    return p_hw_spi->crcpr;
}

/**
 * \brief RxCRC�Ĵ�����ֻ����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ��  ����SPI_CR1 ��CRCEN λд�롮1��ʱ���üĴ�������λ��
 *         CRC����ʹ��SPI_CRCPR �еĶ���ʽ��
 *
 *         ������֡��ʽ������Ϊ8λʱ������8λ������㣬���Ұ���CRC8�ķ������У�������֡
 *         ��ʽΪ 16λʱ���Ĵ����е�����16λ��������㣬���Ұ���CRC16�ı�׼
 *
 *         ��BSY ��־Ϊ��1��ʱ���üĴ����������ܶ�������ȷ����ֵ��
 *
 * \return �����յ����ֽڼ����CRC��ֵ
 */
am_static_inline
uint16_t amhw_zlg237_spi_rxcrc_read (amhw_zlg237_spi_t *p_hw_spi)
{
    return p_hw_spi->rxcrcr;
}

/**
 * \brief TxCRC�Ĵ�����ֻ����
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ��  ����SPI_CR1 ��CRCEN λд�롮1��ʱ���üĴ�������λ��
 *         CRC����ʹ��SPI_CRCPR �еĶ���ʽ��
 *
 *         ������֡��ʽ������Ϊ8λʱ������8λ������㣬���Ұ���CRC8�ķ������У�������֡
 *         ��ʽΪ 16λʱ���Ĵ����е�����16λ��������㣬���Ұ���CRC16�ı�׼
 *
 *         ��BSY ��־Ϊ��1��ʱ���üĴ����������ܶ�������ȷ����ֵ��
 *
 * \return ��Ҫ���͵��ֽڼ����CRC��ֵ
 */
am_static_inline
uint16_t amhw_zlg237_spi_txcrc_read (amhw_zlg237_spi_t *p_hw_spi)
{
    return p_hw_spi->txcrcr;
}

/**
 * \brief FlexLenEn �ɱ��������
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ��ʹ��2~32�������ݰ����ȿ��书�ܡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_flexlength_disable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr3 &= ~(1u << 7);
}

/**
 * \brief FlexLenEn �ɱ����ʹ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ʹ��2~32�������ݰ����ȿ��书�ܣ�����λ����Len[4:0]����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_flexlength_enable (amhw_zlg237_spi_t *p_hw_spi)
{
    p_hw_spi->cr3 |= (1u << 7);
}

/**
 * \brief Len[4:0] �ɱ�������ã�λ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 * \param[in] flag     : ���ݰ����趨ֵ������������-1��
 *
 * \note ��  ���ݰ���ΪLen[4:0]+1�����أ�����Len[4:0] =5��b00101, ���ݰ���Ϊ6���ء�
 *         �趨ֵ��[4:0]λ��Ч
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_spi_flex_length_set (amhw_zlg237_spi_t *p_hw_spi, uint8_t length)
{
    p_hw_spi->crcpr = ( p_hw_spi->crcpr & (~(0x1fu << 0))) | ((0x1fu & length) << 0);
}

/**
 * \brief Len[4:0] �ɱ�����������ݶ�����λ��
 * \param[in] p_hw_spi : ָ��SPI�ṹ���ָ��
 *
 * \note ��  ���ݰ���ΪLen[4:0]+1�����أ�����Len[4:0] =5��b00101, ���ݰ���Ϊ6���ء�
 *
 * \return ��ǰ���ݰ����趨ֵ��ʵ�ʰ�����-1��
 */
am_static_inline
uint8_t amhw_zlg237_flex_length_get (amhw_zlg237_spi_t *p_hw_spi)
{
    return (p_hw_spi->crcpr) & 0x1fu;
}

/**
 * @} amhw_zlg_if_spi
 */

#ifdef __cplusplus
}
#endif

#endif /* SOC_ZLG_DRIVERS_INCLUDE_SPI_HW_AMHW_ZLG237_SPI_H_ */
