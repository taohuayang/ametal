/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
*******************************************************************************/

/**
 * \file
 * \brief SPI Ӳ�������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-12  YRZ, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZSN700_SPI_H
#define __AMHW_ZSN700_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zsn700_if_spi
 * \copydoc amhw_zsn700_spi.h
 * @{
 */

/**
 * \brief SPI structure of register
 */
typedef struct amhw_zsn700_spi {
    __IO uint32_t  cr;       /**< \brief SPI ���üĴ��� */
    __IO uint32_t  ssn;      /**< \brief SPI Ƭѡ���üĴ��� */
    __I  uint32_t  stat;     /**< \brief SPI ״̬�Ĵ��� */
    __IO uint32_t  data;     /**< \brief SPI ���ݼĴ��� */
    __IO uint32_t  cr2;      /**< \brief SPI ���üĴ��� 2 */
    __O  uint32_t  iclr;     /**< \brief SPI �ж�����Ĵ��� */
} amhw_zsn700_spi_t;

/**
 * \brief ���������ò���
 */
typedef enum {
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV2 = 0,  /**< \brief ������Ϊ����ʱ�ӵ�2��Ƶ */
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV4,      /**< \brief ������Ϊ����ʱ�ӵ�4��Ƶ */
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV8,      /**< \brief ������Ϊ����ʱ�ӵ�8��Ƶ */
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV16,     /**< \brief ������Ϊ����ʱ�ӵ�16��Ƶ */
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV32,     /**< \brief ������Ϊ����ʱ�ӵ�32��Ƶ */
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV64,     /**< \brief ������Ϊ����ʱ�ӵ�64��Ƶ */
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_DIV128,    /**< \brief ������Ϊ����ʱ�ӵ�128��Ƶ */
    AMHW_ZSN700_SPI_BAUD_RATE_PCLK_0,         /**< \brief ������Ϊ0 */
}amhw_zsn700_spi_baud_rate_t;

/**
 * \brief SPI  ����������   ��ȡ
 * \param[in] p_hw_spi  : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return ���������ò���(amhw_zsn700_spi_baud_rate_tö����)
 */
am_static_inline
amhw_zsn700_spi_baud_rate_t
amhw_zsn700_spi_baud_rate_get (amhw_zsn700_spi_t *p_hw_spi)
{
   return (amhw_zsn700_spi_baud_rate_t)((p_hw_spi->cr & 0x3ul) | 
                                        ((p_hw_spi->cr >> 5) & 0x4ul));
}

/**
 * \brief SPI  ����������   ����
 * \param[in] p_hw_spi  : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] baud_rate : ���������ò���(amhw_zsn700_spi_baud_rate_tö����)
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_baud_rate_set (amhw_zsn700_spi_t          *p_hw_spi,
                                    amhw_zsn700_spi_baud_rate_t baud_rate)
{
    /* ��bit7 �� bit1 ��bit0 ���� */
    p_hw_spi->cr &= ~(0x83ul);

    /* ����bit7��ֵ */
    p_hw_spi->cr |= ((baud_rate & 0x4ul) << 5);

    /* ����bit1��bit0��ֵ */
    p_hw_spi->cr |= ((baud_rate & 0x3ul) << 0);
}

/**
 * \brief SPI ģ��ʹ������
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] flag     : AM_TRUE or AM_FALSE
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_enable (amhw_zsn700_spi_t *p_hw_spi, am_bool_t flag)
{
    p_hw_spi->cr = (p_hw_spi->cr & (~(1u << 6))) | (flag << 6);
}

/**
 * \brief ����/�ӻ�ģʽѡ��
 */
typedef enum {
    AMHW_ZSN700_SPI_MODE_TYPE_MASTER = 1,  /**< \brief ����ģʽ */
    AMHW_ZSN700_SPI_MODE_TYPE_SLAVER = 0,  /**< \brief �ӻ�ģʽ */
}amhw_zsn700_spi_mode_type_t;

/**
 * \brief SPI ����/�ӻ�ģʽѡ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] flag     : amhw_zsn700_spi_mode_type_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_mode_sel (amhw_zsn700_spi_t          *p_hw_spi,
                               amhw_zsn700_spi_mode_type_t mode_type)
{
    p_hw_spi->cr = (p_hw_spi->cr & (~(1u << 4))) | (mode_type << 4);
}

/**
 * \brief ʱ��ģʽѡ��
 * \ @{
 */
#define AMHW_ZSN700_SPI_CLK_MODE_0    0 /**< \brief Clock mode 0 */
#define AMHW_ZSN700_SPI_CLK_MODE_1    1 /**< \brief Clock mode 1 */
#define AMHW_ZSN700_SPI_CLK_MODE_2    2 /**< \brief Clock mode 2 */
#define AMHW_ZSN700_SPI_CLK_MODE_3    3 /**< \brief Clock mode 3 */

/** @}*/

/**
 * \brief ʱ��ģʽѡ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] flag     : ģʽ���ú궨��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_clk_mode_set (amhw_zsn700_spi_t *p_hw_spi, uint32_t flag)
{
    p_hw_spi->cr = (p_hw_spi->cr & (~(3u << 2))) | (flag << 2);
}

/**
 * \brief ����ģʽ��,������� ssnֵ���� SPI_CS�˿ڵ�ƽ�ߵ�
 * \param[in] p_hw_spi  : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] flag      : AM_TRUE : Ƭѡ��Ч
 *                        AM_FALSE: ƬѡʧЧ
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_cs_sel (amhw_zsn700_spi_t *p_hw_spi, am_bool_t flag)
{
    p_hw_spi->ssn = (~flag) & 0x1;
}

/**
 * \brief SPI״̬��־
 *  @{
 */
#define AMHW_ZSN700_SPI_FLAG_TX_FINISH        (1U << 7) /* ���������־ */
#define AMHW_ZSN700_SPI_FLAG_SLAVER_SSN_ERR   (1U << 5) /* �ӻ�ģʽSSN�����־*/
#define AMHW_ZSN700_SPI_FLAG_MASTER_ERR       (1U << 4) /* ����ģʽ�����־ */
#define AMHW_ZSN700_SPI_FLAG_BUSY             (1U << 3) /* SPI����æ��־ */
#define AMHW_ZSN700_SPI_FLAG_TX_EMPTY         (1U << 2) /* ���ͻ������ձ�־ */
#define AMHW_ZSN700_SPI_FLAG_RX_NOT_EMPTY     (1U << 1) /* ���ջ������ǿձ�־ */
/**
 * \brief ��־��Ч���ж�
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] flag     : ��־�궨��
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_spi_flag_check (amhw_zsn700_spi_t *p_hw_spi,
                                      uint8_t            flag)
{
    return ((p_hw_spi->stat & flag)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief  SPI�ж����
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_flag_clr (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->iclr &= ~(0x1ul << 0);
}

/**
 * \brief  SPI�жϱ���
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_flag_hold (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->iclr |= (0x1ul << 0);
}

/**
 * \brief  8bit����д
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] data     : ����������
 * \param[in] lsbfirst : ��λ�ȷ��ͱ�־��Ӳ��ֻ�и�λ�ȷ��͹��ܡ�Ϊ��Ӧ��׼�㣬���ʵ�ֵ�λ�ȷ��͹���
 *
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_tx_data8_put (amhw_zsn700_spi_t *p_hw_spi,
                                   uint8_t            data,
                                   am_bool_t          lsbfirst)
{
    uint8_t temp = 0,i = 0;

    /* ��λ���� */
    if(lsbfirst) {
        for(i = 0; i < 8; i++) {
            if(((data >> i) & 0x1ul) == 1) {
                temp |= (1 << (7 - i));
            }
        }
        data = temp;
    }

    p_hw_spi->data = data;
}

/**
 * \brief 8bit���ݶ�
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 * \param[in] lsbfirst : ��λ�ȷ��ͱ�־��Ӳ��ֻ�и�λ�ȷ��͹��ܡ�Ϊ��Ӧ��׼�㣬���ʵ�ֵ�λ�ȷ��͹���
 *
 * \return ��������
 */
am_static_inline
uint8_t amhw_zsn700_spi_rx_data8_get (amhw_zsn700_spi_t *p_hw_spi,
                                      am_bool_t          lsbfirst)
{
    uint8_t temp = 0,i = 0;

    uint8_t data = p_hw_spi->data;


    /* ��λ���� */
    if(lsbfirst) {
        for(i = 0; i < 8; i++) {
            if(((data >> i) & 0x1ul) == 1) {
                temp |= (1 << (7 - i));
            }
        }
        data = temp;
    }

    return data;
}

/**
 * \brief ���ջ������ǿ��ж�ʹ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_int_rx_not_empty_enable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (0x1ul << 6);
}

/**
 * \brief ���ջ������ǿ��жϽ���
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_int_rx_not_empty_disable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(0x1ul << 6);
}

/**
 * \brief ���ͻ��������ж�ʹ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_tx_empty_enable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (0x1ul << 5);
}

/**
 * \brief ���ͻ��������жϽ���
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_tx_empty_disable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(0x1ul << 5);
}

/**
 * \brief DMAӲ�����ʷ���ʹ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_dma_tx_enable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (0x1ul << 4);
}

/**
 * \brief DMAӲ�����ʷ��ͽ���
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_dma_tx_disable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(0x1ul << 4);
}

/**
 * \brief DMAӲ�����ʽ���ʹ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_dma_rx_enable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (0x1ul << 3);
}

/**
 * \brief DMAӲ�����ʽ��ս���
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_dma_rx_disable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(0x1ul << 3);
}

/**
 * \brief SPI�ж�ʹ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_int_enable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 |= (0x1ul << 2);
}

/**
 * \brief SPI�жϽ���
 * \param[in] p_hw_spi : ָ��SPI�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_spi_int_disable (amhw_zsn700_spi_t *p_hw_spi)
{
    p_hw_spi->cr2 &= ~(0x1ul << 2);
}

/**
 * @} amhw_zsn700_if_spi
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZSN700_SPI_H */

/* end of file */
