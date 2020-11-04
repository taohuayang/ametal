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
 * \brief I2S Ӳ�������ӿ�
 */
 
#ifndef __AMHW_HC32F07X_I2S_H
#define __AMHW_HC32F07X_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_hc32f07x_if_i2s
 * \copydoc amhw_hc32f07x_i2s.h
 * @{
 */

/**
 * \brief SPI structure of register
 */
typedef struct amhw_hc32f07x_i2s {
    __IO uint32_t  reserve0;     /**< \brief ����*/
    __IO uint32_t  cr;           /**< \brief I2S ���ƼĴ��� */
    __IO uint32_t  sr;           /**< \brief I2S �жϺ�״̬�Ĵ��� */
    __IO uint32_t  reserve1[4];  /**< \brief ����*/
    __IO uint32_t  cfgr;         /**< \brief I2S ���üĴ��� */
    __IO uint32_t  pr;           /**< \brief I2S ��ģʽ��Ƶ�Ĵ��� */
    __IO uint32_t  icr;          /**< \brief I2S �жϱ�־����Ĵ���  */
    __IO uint32_t  drl;          /**< \brief I2S ����������������������ݼĴ��� */
    __IO uint32_t  drr;          /**< \brief I2S ����������������������ݼĴ��� */
} amhw_hc32f07x_i2s_t;	

/**
 * \brief I2S ���ͻ��������ж�ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_tx_empty_enable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr |= (0x1ul << 7);
}

/**
 * \brief I2S ���ͻ��������жϽ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_tx_empty_disable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr &= ~(0x1ul << 7);
}

/**
 * \brief I2S ���ջ������ǿ��ж�ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_rx_not_empty_enable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr |= (0x1ul << 6);
}

/**
 * \brief I2S ���ջ��������жϽ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_rx_not_empty_disable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr &= ~(0x1ul << 6);
}

/**
 * \brief I2S �����ж�ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_err_enable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr |= (0x1ul << 5);
}

/**
 * \brief I2S �����жϽ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_err_disable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr &= ~(0x1ul << 5);
}

/**
 * \brief I2S ������������DMA���ݷ���ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_right_dma_enable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr |= (0x1ul << 1);
}

/**
 * \brief I2S ������������DMA���ݷ��ͽ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_right_dma_disable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr &= ~(0x1ul << 1);
}

/**
 * \brief I2S ������������DMA���ݷ���ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_left_dma_enable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr |= (0x1ul << 0);
}

/**
 * \brief I2S ������������DMA���ݷ��ͽ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_left_dma_disable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cr &= ~(0x1ul << 0);
}

/**
 * \brief I2S״̬��־
 *  @{
 */
#define AMHW_HC32F07X_I2S_FLAG_RIGHT_TX_EMPTY         (1U << 15) /* ��ͨ�����ͻ������ձ�־ */
#define AMHW_HC32F07X_I2S_FLAG_RIGHT_RX_NOT_EMPTY     (1U << 14) /* ��ͨ�����ջ������ǿձ�־ */
#define AMHW_HC32F07X_I2S_FLAG_LEFT_TX_EMPTY          (1U << 1 ) /* ��ͨ�����ͻ������ձ�־ */
#define AMHW_HC32F07X_I2S_FLAG_LEFT_RX_NOT_EMPTY      (1U << 0 ) /* ��ͨ�����ջ������ǿձ�־ */
#define AMHW_HC32F07X_I2S_FLAG_FRE_ERR                (1U << 8 ) /* ֡�����־ */
#define AMHW_HC32F07X_I2S_FLAG_BUSY                   (1U << 7 ) /* æ��־ */
#define AMHW_HC32F07X_I2S_FLAG_RIGHT_OVER             (1U << 13) /* ��ͨ�������־ */
#define AMHW_HC32F07X_I2S_FLAG_RIGHT_UNDER            (1U << 3 ) /* ��ͨ������ձ�־ */
#define AMHW_HC32F07X_I2S_FLAG_LEFT_OVER              (1U << 6 ) /* ��ͨ�������־ */
#define AMHW_HC32F07X_I2S_FLAG_LEFT_UNDER             (1U << 2 ) /* ��ͨ�������־ */
/**
 * \brief ��־��Ч���ж�
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : ��־�궨��
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_i2s_flag_check (amhw_hc32f07x_i2s_t *p_hw_i2s,
                                        uint16_t            flag)
{
    return ((p_hw_i2s->sr & flag)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ��־����
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : ��־�궨��
 *
 * \return 
 */
am_static_inline
void amhw_hc32f07x_i2s_flag_clr (amhw_hc32f07x_i2s_t *p_hw_i2s,
                                        uint8_t            flag)
{
   p_hw_i2s->sr &= ~flag;
}

/**
 * \brief I2S ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_enable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cfgr |= (0x1ul << 10);
}

/**
 * \brief I2S ����
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_disable (amhw_hc32f07x_i2s_t *p_hw_i2s)
{
    p_hw_i2s->cfgr &= ~(0x1ul << 10);
}

/**
 * \brief I2S����ģʽѡ��
 */
typedef enum {
    AMHW_HC32F07X_I2S_MODE_SLAVER_TX = 0,  /**< \brief �ӻ�ģʽ���� */
    AMHW_HC32F07X_I2S_MODE_SLAVER_RX = 1,  /**< \brief �ӻ�ģʽ���� */
    AMHW_HC32F07X_I2S_MODE_MASTER_TX = 2,  /**< \brief ����ģʽ���� */
    AMHW_HC32F07X_I2S_MODE_MASTER_RX = 3,  /**< \brief ����ģʽ���� */
}amhw_hc32f07x_i2s_mode_t;

/**
 * \brief I2S ����/�ӻ�ģʽѡ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : amhw_hc32f07x_i2s_mode_tö����
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_mode_sel (amhw_hc32f07x_i2s_t          *p_hw_i2s,
                                   amhw_hc32f07x_i2s_mode_t mode_type)
{
    p_hw_i2s->cfgr = (p_hw_i2s->cfgr & (~(3u << 8))) | (mode_type << 8);
}

/**
 * \brief I2S PCM֡ͬ��ѡ��
 */
typedef enum {
    AMHW_HC32F07X_I2S_PCM_SHORT = 0,  /**< \brief PCM ��֡ͬ�� */
    AMHW_HC32F07X_I2S_PCM_LONG  = 1,  /**< \brief PCM ��֡ͬ�� */
}amhw_hc32f07x_i2s_pcm_t;

/**
 * \brief I2S PCM֡ͬ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : amhw_hc32f07x_i2s_mode_tö����
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_pcm (amhw_hc32f07x_i2s_t          *p_hw_i2s,
                              amhw_hc32f07x_i2s_pcm_t mode_type)
{
    p_hw_i2s->cfgr = (p_hw_i2s->cfgr & (~(1u << 7))) | (mode_type << 7 );
}

/**
 * \brief I2S ʱ��ѡ��
 */
typedef enum {
    AMHW_HC32F07X_I2S_PCLK = 0,  /**< \brief PCLKʱ�� */
    AMHW_HC32F07X_I2S_HCLK = 1,  /**< \brief HCLKʱ�� */
}amhw_hc32f07x_i2s_clk_t;
/**
 * \brief I2S ʱ��ѡ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : amhw_hc32f07x_i2s_mode_tö����
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_clk (amhw_hc32f07x_i2s_t          *p_hw_i2s,
                              amhw_hc32f07x_i2s_clk_t mode_clk)
{
    p_hw_i2s->cfgr = (p_hw_i2s->cfgr & (~(1u << 6))) | (mode_clk << 6 );
}

/**
 * \brief I2S ��׼ѡ��
 */
typedef enum {
    AMHW_HC32F07X_I2S_PHI = 0,  /**< \brief I2S philips ��׼*/
    AMHW_HC32F07X_I2S_MSB = 1,  /**< \brief MSB������׼ */
    AMHW_HC32F07X_I2S_LSB = 2,  /**< \brief LSB�Ҷ����׼ */
    AMHW_HC32F07X_I2S_PCM = 3,  /**< \brief PCM ��׼ */
}amhw_hc32f07x_i2s_std_t;

/**
 * \brief I2S ��׼ѡ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : amhw_hc32f07x_i2s_std_tö����
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_std (amhw_hc32f07x_i2s_t          *p_hw_i2s,
                              amhw_hc32f07x_i2s_std_t std)
{
    p_hw_i2s->cfgr = (p_hw_i2s->cfgr & (~(3u << 4))) | (std << 4 );
}

/**
 * \brief I2S ���ݳ���
 */
typedef enum {
    AMHW_HC32F07X_I2S_DATA_LEN16  = 0,  /**< \brief 16λ���ݳ��� */
    AMHW_HC32F07X_I2S_DATA_LEN24  = 1,  /**< \brief 24λ���ݳ��� */
    AMHW_HC32F07X_I2S_DATA_LEN32  = 2,  /**< \brief 32λ���ݳ��� */
    AMHW_HC32F07X_I2S_DATA_FORBID = 3,  /**< \brief ������ */
}amhw_hc32f07x_i2s_data_t;

/**
 * \brief I2S Ҫ��������ݳ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : amhw_hc32f07x_i2s_data_tö����
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_data_length (amhw_hc32f07x_i2s_t          *p_hw_i2s,
                                      amhw_hc32f07x_i2s_data_t length)
{
    p_hw_i2s->cfgr = (p_hw_i2s->cfgr & (~(3u << 1))) | (length << 1 );
}

/**
 * \brief I2S ͨ�����ݳ���
 */
typedef enum {
    AMHW_HC32F07X_I2S_CH_LEN16  = 0,  /**< \brief 16λͨ������ */

    AMHW_HC32F07X_I2S_CH_LEN32  = 1,  /**< \brief 32λͨ������ */

}amhw_hc32f07x_i2s_ch_t;

/**
 * \brief I2S Ҫ��������ݳ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : amhw_hc32f07x_i2s_ch_tö����
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_ch_length (amhw_hc32f07x_i2s_t   *p_hw_i2s,
                                  amhw_hc32f07x_i2s_ch_t ch_length)
{
    p_hw_i2s->cfgr = (p_hw_i2s->cfgr & (~(1u << 1))) | (ch_length << 0 );
}

/**
 * \brief I2S ��ʱ�����ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_clk_enable (amhw_hc32f07x_i2s_t   *p_hw_i2s)
{
    p_hw_i2s->pr |= (1u<<9);
}

/**
 * \brief I2S ��ʱ���������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_clk_disable (amhw_hc32f07x_i2s_t   *p_hw_i2s)
{
    p_hw_i2s->pr &= ~(1u<<9);
}

/**
 * \brief I2S Ԥ��Ƶ��С������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] value    : ����ֵ
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_fract_set (amhw_hc32f07x_i2s_t   *p_hw_i2s,
                                  uint8_t               value)
{
    p_hw_i2s->pr = (p_hw_i2s->pr & (~(0x3fu << 10))) | ((value & 0x3f) << 10);
}

/**
 * \brief I2S Ԥ��Ƶ����������ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_odd_enable (amhw_hc32f07x_i2s_t   *p_hw_i2s)
{
    p_hw_i2s->pr |= (1 << 8);
}

/**
 * \brief I2S Ԥ��Ƶ���������ӽ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_odd_disable (amhw_hc32f07x_i2s_t   *p_hw_i2s)
{
    p_hw_i2s->pr &= ~(1 << 8);
}

/**
 * \brief I2S ����Ԥ��Ƶ������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] value    : Ԥ��Ƶ������ֵ
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_div_set (amhw_hc32f07x_i2s_t   *p_hw_i2s,
                                  uint8_t               value)
{
    p_hw_i2s->pr = (p_hw_i2s->pr & (~0xffu )) | (value & 0xff);
}

/**
 * \brief I2S�ж�״̬��־
 *  @{
 */
#define AMHW_HC32F07X_I2S_INT_FRE                  (1U << 8 ) /* ֡�����־ */
#define AMHW_HC32F07X_I2S_INT_OVER                 (1U << 6 ) /* �����־ */
#define AMHW_HC32F07X_I2S_INT_UNDER                (1U << 3 ) /* �����־ */

/**
 * \brief I2S ����Ԥ��Ƶ������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] flag     : �ж�״̬��־���ο��궨��AMHW_HC32_I2S_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_intstat_clr (amhw_hc32f07x_i2s_t   *p_hw_i2s,
                                    uint32_t               flag)
{
    p_hw_i2s->icr &= flag;
}

/**
 * \brief I2S д���ݼĴ�������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] value    : ����ֵ
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_data_left_write (amhw_hc32f07x_i2s_t   *p_hw_i2s,
                                        uint16_t               value)
{
    p_hw_i2s->drl = value;
}

/**
 * \brief I2S �����ݼĴ�������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return  ���ջ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f07x_i2s_data_left_read (amhw_hc32f07x_i2s_t   *p_hw_i2s)
{
    return (uint16_t)(p_hw_i2s->drl & 0xffff);
}

/**
 * \brief I2S д���ݼĴ������ң�
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 * \param[in] value    : ����ֵ
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_i2s_data_right_write (amhw_hc32f07x_i2s_t   *p_hw_i2s,
                                         uint16_t               value)
{
    p_hw_i2s->drr = value;
}

/**
 * \brief I2S �����ݼĴ������ң�
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ����ṹ���ָ��
 *
 * \return  ���ջ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f07x_i2s_data_right_read (amhw_hc32f07x_i2s_t   *p_hw_i2s)
{
    return (uint16_t)(p_hw_i2s->drr & 0xffff);
}

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32_SPI_H */

/* end of file */	
