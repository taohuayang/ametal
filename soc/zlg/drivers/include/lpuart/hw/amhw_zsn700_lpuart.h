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
 * \brief UART�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-15  YRZ, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZSN700_LPUART_H
#define __AMHW_ZSN700_LPUART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_zsn700_if_lpuart
 * \copydoc amhw_zsn700_lpuart.h
 * @{
 */

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */

/**
 * \brief uart �Ĵ�����ṹ��
 */
typedef struct amhw_zsn700_lpuart {
    __IO uint32_t sbuf;       /**< \brief ���ݼĴ��� */
    __IO uint32_t scon;       /**< \brief ���ƼĴ��� */
    __IO uint32_t saddr;      /**< \brief ��ַ�Ĵ��� */
    __IO uint32_t saden;      /**< \brief ��ַ����Ĵ��� */
    __IO uint32_t isr;        /**< \brief �жϱ�־λ�Ĵ��� */
    __IO uint32_t icr;        /**< \brief �жϱ�־λ����Ĵ��� */
    __IO uint32_t scnt;       /**< \brief �����ʼĴ��� */
} amhw_zsn700_lpuart_t;

/**
 * \brief �趨DATA[8]
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] am_bool_t   : AM_TRUE��1��  ����      AM_FALSE��0��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_lpuart_data_8th_set (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                      am_bool_t             stat)
{
    p_hw_lpuart->sbuf = (p_hw_lpuart->sbuf & (~(0x1ul << 8))) | (stat << 8);
}

/**
 * \brief ��ȡDATA[8]
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return  AM_TRUE��1��  ����      AM_FALSE��0��
 */
am_static_inline
am_bool_t amhw_zsn700_lpuart_data_8th_get (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    return ((p_hw_lpuart->sbuf >> 8) & 0x1ul);
}

/**
 * \brief д����
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] data_w      : ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_lpuart_data_write (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                    uint8_t               data_w)
{
    p_hw_lpuart->sbuf = (p_hw_lpuart->sbuf & (~0xfful)) | (0xff & data_w);
}

/**
 * \brief ������
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return �Ĵ�������
 */
am_static_inline
uint8_t amhw_zsn700_lpuart_data_read (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    return (0xffu & p_hw_lpuart->sbuf);
}

/**
 * \brief HDSEL ���߰�˫��ģʽ   ����
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��
 */

am_static_inline
void amhw_zsn700_lpuart_single_line_half_disable (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    p_hw_lpuart->scon &= ~(0x1ul << 22);
}

/**
 * \brief HDSEL ���߰�˫��ģʽ   ʹ��
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��
 */

am_static_inline
void amhw_zsn700_lpuart_single_line_half_enable (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    p_hw_lpuart->scon |= (0x1ul << 22);
}


#define AMHW_ZSN700_LPUART_INT_FRAME_ERR   (1ul << 21)   /* ֡�����ж�ʹ��λ */
#define AMHW_ZSN700_LPUART_INT_CTS_TRIGGER (1ul << 20)   /* CTS��ת�ж�ʹ��λ */
#define AMHW_ZSN700_LPUART_INT_PARITY_ERR  (1ul << 13)   /* ��żУ������ж�ʹ��λ */
#define AMHW_ZSN700_LPUART_INT_TX_EMPTY    (1ul << 8)    /* TX���ж�ʹ��λ  */
#define AMHW_ZSN700_LPUART_INT_TX_COMPLETE (1ul << 1)    /* �����ж�ʹ��λ */
#define AMHW_ZSN700_LPUART_INT_RX_COMPLETE (1ul << 0)    /* �����ж�ʹ��λ */
#define AMHW_ZSN700_LPUART_INT_ALL         0xFF          /* �����жϱ�־ */

/**
 * \brief UART ����ж�  ����
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type        : �жϺ궨��  AMHW_ZSN700_LPUART_INT_FRAME_ERR
 *                                 ��
 *                                 ��
 *                                 ��
 *                                 AMHW_ZSN700_LPUART_INT_ALL
 *
 * \return ��
 */

am_static_inline
void amhw_zsn700_lpuart_int_disable (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                     uint32_t            type)
{
    if(type == 0xFF) {
        p_hw_lpuart->scon &= ~(1ul << 21);
        p_hw_lpuart->scon &= ~(1ul << 20);
        p_hw_lpuart->scon &= ~(1ul << 13);
        p_hw_lpuart->scon &= ~(1ul << 8);
        p_hw_lpuart->scon &= ~(1ul << 1);
        p_hw_lpuart->scon &= ~(1ul << 0);
    } else {
        p_hw_lpuart->scon &= ~type;
    }
}

/**
 * \brief UART ����ж�  ʹ��
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type        : �жϺ궨��  AMHW_ZSN700_LPUART_INT_FRAME_ERR
 *                                 ��
 *                                 ��
 *                                 ��
 *                                 AMHW_ZSN700_LPUART_INT_ALL
 *
 * \return ��
 */

am_static_inline
void amhw_zsn700_lpuart_int_enable (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                    uint32_t              type)
{
    if(type == 0xFF) {
        p_hw_lpuart->scon |= (1ul << 21);
        p_hw_lpuart->scon |= (1ul << 20);
        p_hw_lpuart->scon |= (1ul << 13);
        p_hw_lpuart->scon |= (1ul << 8);
        p_hw_lpuart->scon |= (1ul << 1);
        p_hw_lpuart->scon |= (1ul << 0);
    } else {
        p_hw_lpuart->scon |= type;
    }
}

#define AMHW_ZSN700_LPUART_CTS          (1ul << 19)/* Ӳ����CTSʹ��λ */
#define AMHW_ZSN700_LPUART_RTS          (1ul << 18)/* Ӳ����RTSʹ��λ */
#define AMHW_ZSN700_LPUART_DMA_TX       (1ul << 17)/* ����DMAʹ��λ */
#define AMHW_ZSN700_LPUART_DMA_RX       (1ul << 16)/* ����DMAʹ��λ */
#define AMHW_ZSN700_LPUART_MUT_ADR_AUTO (1ul << 5) /* �����ַ�Զ�ʶ��ʹ��λ */
#define AMHW_ZSN700_LPUART_RX           (1ul << 4) /* ����ʹ��
                                                    * Mode0:     0������; 1������
                                                    * Mode1/2/3: 0������; 1�� ����/����
                                                    */
/**
 * \brief UART ��ؿ���  ����
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type      : �жϺ궨��  AMHW_ZSN700_LPUART_CTS
 *                               ��
 *                               ��
 *                               ��
 *                               AMHW_ZSN700_LPUART_RX
 *
 * \return ��
 */

am_static_inline
void amhw_zsn700_lpuart_disable (amhw_zsn700_lpuart_t *p_hw_lpuart,
                               uint32_t            type)
{
    p_hw_lpuart->scon &= ~type;
}

/**
 * \brief UART ��ؿ���  ʹ��
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type        : �жϺ궨��  AMHW_ZSN700_LPUART_CTS
 *                                 ��
 *                                 ��
 *                                 ��
 *                                 AMHW_ZSN700_LPUART_RX
 *
 * \return ��
 */

am_static_inline
void amhw_zsn700_lpuart_enable (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                uint32_t            type)
{
    p_hw_lpuart->scon |= type;
}

#define AMHW_ZSN700_LPUART_STOP_1_0_BIT   (0ul << 14)  /* 1��ֹͣλ */
#define AMHW_ZSN700_LPUART_STOP_1_5_BIT   (1ul << 14)  /* 1.5��ֹͣλ */
#define AMHW_ZSN700_LPUART_STOP_2_0_BIT   (2ul << 14)  /* 2��ֹͣλ */

/**
 * \brief ֹͣλ����
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] stop_bit    : ֹͣλ�궨��   AMHW_ZSN700_LPUART_STOP_1_0_BIT ��
 *                                   AMHW_ZSN700_LPUART_STOP_1_5_BIT ��
 *                                   AMHW_ZSN700_LPUART_STOP_2_0_BIT
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpuart_stop_bit_sel (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                      uint32_t              stop_bit)
{
    p_hw_lpuart->scon = (p_hw_lpuart->scon & (~(0x3ul << 14))) | stop_bit;
}


/**
 *  ģʽ0--ͬ������ģʽ����˫�����䲨���ʹ̶�Ϊ SCLKʱ��Ƶ�ʵ�1/12�� �շ����ݶ��� RXD���������RXD��ʱΪ
 *        ˫��˿ڡ�ͬ����λʱ���� TXD �����TXD��ʱΪ����˿ڡ�
 *
 *        ��������λ��Ϊ 8-Bit��û����ʼλ�ͽ���λ��

 *  ģʽ1--�첽����ģʽ��ȫ˫�������������ڲ� 16-Bit �ɱ�̲����ʷ�������������������ͨ�� TXD���ͣ���������
 *        ͨ�� RXD���ա�1-Bit ��ʼλ��0����ʼ�������� 8-Bit����λ����λ���ȣ���λ�ں󣩣������ 1/1.5/
 *        2-Bit����λ��1����

 *  ģʽ2--�첽����ģʽ��ȫ˫�����䲨���ʹ̶�Ϊ SCLK ʱ��Ƶ�ʵ�1/8�������������±���λ��ɣ�1-Bit��ʼλ��0��
 *        ��ʼ�������� 8-Bit����λ��1-Bit TB8 λ�� 1/1.5/2-Bit����λ������� TB8λ�����ڶ��ͨѶ������ʹ�ã�
 *        �� TB8=1�����������յ��ǵ�ַ֡���� TB8=0�����������յ�������֡��������Ҫ���ͨѶʱ����λҲ������Ϊ��
 *        żУ��λ��������λ��ʹ�á�
 *
 *  ģʽ3--�첽����ģʽ��ȫ˫���� ���������ڲ� 16-Bit�ɱ�̲����ʷ�������������������ͨ�� TXD ���ͣ���������
 *        ͨ�� RXD ���ա������������±���λ��ɣ�1-Bit ��ʼλ��0����ʼ�������� 8-Bit����λ��1-Bit TB8λ
 *        �� 1/1.5/2-Bit����λ������� TB8λ�����ڶ��ͨѶ������ʹ�ã�
 *        �� TB8=1�����������յ��ǵ�ַ֡���� TB8=0�����������յ�������֡��������Ҫ���ͨѶʱ����λҲ������Ϊ��
 *        żУ��λ��������λ��ʹ�á�����λ��
 *
 *  ģʽ4--�첽����ģʽ����˫���� �����ʼ�����ģʽ1��2��3��ͬ��ͨ�� TXD ������������ݣ�RXD����ʹ�á�
 *        TX �źŵķ��������Ӳ���߼���ɣ�����������ơ������ͻ���Ϊ��ʱ��TX �ź�ʼ��Ϊ���루����״̬����
 *        �����ͻ�������һ�����ݣ�TX �źű�Ϊ���������״̬������������ɣ����ͻ����Ϊ�գ�
 *        TX �ź��ֻص����루����״̬����
 */
typedef enum {
    AMHW_ZSN700_LPUART_WORK_MODE_0 = 0,
    AMHW_ZSN700_LPUART_WORK_MODE_1,
    AMHW_ZSN700_LPUART_WORK_MODE_2,
    AMHW_ZSN700_LPUART_WORK_MODE_3,
    AMHW_ZSN700_LPUART_WORK_MODE_4,
}amhw_zsn700_lpuart_work_mode_t;
/**
 * \brief ����ģʽ�趨
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] stop_bit    : AMHW_ZSN700_LPUART_WORK_MODE_0 ��
 *                          AMHW_ZSN700_LPUART_WORK_MODE_1 ��
 *                          AMHW_ZSN700_LPUART_WORK_MODE_2 ��
 *                          AMHW_ZSN700_LPUART_WORK_MODE_3
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpuart_mode_sel (amhw_zsn700_lpuart_t           *p_hw_lpuart,
                                  amhw_zsn700_lpuart_work_mode_t  mode_type)
{
    p_hw_lpuart->scon = (p_hw_lpuart->scon & (~(0x3ul << 6))) |
                        ((mode_type & 0x3ul) << 6);
}

/**
 * \brief ����ģʽ��ȡ
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��ǰ����ģʽ0/1/2/3
 */
am_static_inline
amhw_zsn700_lpuart_work_mode_t amhw_zsn700_lpuart_mode_get (amhw_zsn700_lpuart_t
                                                            *p_hw_lpuart)
{
    return (amhw_zsn700_lpuart_work_mode_t)((p_hw_lpuart->scon >> 6) & 0x3ul);
}

#define AMHW_ZSN700_LPUART_SOFT           (0ul << 2)  /* �����дSBUF[8] */
#define AMHW_ZSN700_LPUART_HW_PARITY_EVEN (1ul << 2)  /* Ӳ��żУ�� */
#define AMHW_ZSN700_LPUART_HW_PARITY_ODD  (2ul << 2)  /* Ӳ����У�� */
#define AMHW_ZSN700_LPUART_PARITY_NO      (3ul << 2)  /* ���� */
/**
 * \brief UART parity bit select
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity      : ��żУ��궨��       AMHW_ZSN700_LPUART_SOFT            ��
 *                                      AMHW_ZSN700_LPUART_HW_PARITY_EVEN  ��
 *                                      AMHW_ZSN700_LPUART_HW_PARITY_ODD   ��
 *                                      AMHW_ZSN700_LPUART_PARITY_NO
 * \return none
 */
am_static_inline
void amhw_zsn700_lpuart_parity_bit_sel (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                        uint32_t              parity)
{
    p_hw_lpuart->scon = (p_hw_lpuart->scon & (~(0x3ul << 2))) | parity;
}

typedef enum {
    AMHW_ZSN700_LPUART_SCLK_DIV_MODE0_NO  = 0,    /* ģʽ0��������Ƶ��Ч */
    AMHW_ZSN700_LPUART_SCLK_DIV_MODE13_16 = 0,    /* ģʽ1/3��16������Ƶ */
    AMHW_ZSN700_LPUART_SCLK_DIV_MODE13_8  = 1,    /* ģʽ1/3��8������Ƶ */
    AMHW_ZSN700_LPUART_SCLK_DIV_MODE13_4  = 2,    /* ģʽ1/3��4������Ƶ */
    AMHW_ZSN700_LPUART_SCLK_DIV_MODE2_32  = 0,    /* ģʽ2��32������Ƶ */
    AMHW_ZSN700_LPUART_SCLK_DIV_MODE2_16  = 1,    /* ģʽ2��16������Ƶ */
    AMHW_ZSN700_LPUART_SCLK_DIV_MODE2_8   = 2,    /* ģʽ2��8������Ƶ */
}amhw_zsn700_lpuart_sclk_div_t;
/**
 * \brief UART ������Ƶ����
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity      : ��Ƶϵ��amhw_zsn700_lpuart_sclk_div_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpuart_clk_div_sel (amhw_zsn700_lpuart_t          *p_hw_lpuart,
                                     amhw_zsn700_lpuart_sclk_div_t  clk_div)
{
    p_hw_lpuart->scon = (p_hw_lpuart->scon & (~(0x3ul << 9))) | (clk_div << 9);
}

/**
 * \brief UART ������Ƶ��ȡ
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��Ƶϵ���趨ֵ������ķ�Ƶֵ��Ҫ��Ϲ���ģʽһ���ж���
 *         ��amhw_zsn700_lpuart_sclk_div_tö������
 */
am_static_inline
uint8_t amhw_zsn700_lpuart_clk_div_get (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    return ((p_hw_lpuart->scon >> 9) & 0x3ul);
}

typedef enum {
    AMHW_ZSN700_LPUART_SCLK_SRC_PCLK = 0,    /* LPUARTͨ�Ŵ���ʱ��Ϊ  PCLK */
    AMHW_ZSN700_LPUART_SCLK_SRC_XTL  = 2,    /* LPUARTͨ�Ŵ���ʱ��Ϊ  �ⲿ����ʱ�� */
    AMHW_ZSN700_LPUART_SCLK_SRC_RCL  = 3,    /* LPUARTͨ�Ŵ���ʱ��Ϊ  �ڲ�����ʱ�� */
}amhw_zsn700_lpuart_sclk_src_t;

/**
 * \brief UART ����ʱ��ѡ��
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity      : amhw_zsn700_lpuart_sclk_src_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpuart_clk_src_sel (amhw_zsn700_lpuart_t          *p_hw_lpuart,
                                     amhw_zsn700_lpuart_sclk_src_t  clk_src)
{
    p_hw_lpuart->scon = (p_hw_lpuart->scon & (~(0x3ul << 11))) | (clk_src << 11);
}

/**
 * \brief UART ����ʱ�ӻ�ȡ
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return amhw_zsn700_lpuart_sclk_src_tö����
 */
am_static_inline
amhw_zsn700_lpuart_sclk_src_t
amhw_zsn700_lpuart_clk_src_get (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    return (amhw_zsn700_lpuart_sclk_src_t)((p_hw_lpuart->scon >> 11) & 0x3ul);
}

/**
 * \brief UART ���豸��ַ����
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity      : ���豸��ַ��8λ��
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpuart_slaver_addr_set (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                         uint8_t             slaver_addr)
{
    p_hw_lpuart->saddr = slaver_addr & 0xFF;
}

/**
 * \brief UART ���豸��ַ��ȡ
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ���豸��ַ��8λ��
 */
am_static_inline
uint8_t amhw_zsn700_lpuart_slaver_addr_get (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    return (p_hw_lpuart->saddr & 0xFF);
}

/**
 * \brief UART ���豸��ַ��������
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity      : ���豸��ַ���루0��������           1�����ģ�
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpuart_slaver_addr_mask_set (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                              uint8_t               addr_mask)
{
    p_hw_lpuart->saden = addr_mask & 0xFF;
}

/**
 * \brief UART ���豸��ַ�����ȡ
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ���豸��ַ���루0��������           1�����ģ�
 */
am_static_inline
uint8_t amhw_zsn700_lpuart_slaver_addr_mask_get (amhw_zsn700_lpuart_t *p_hw_lpuart)
{
    return (p_hw_lpuart->saden & 0xFF);
}

#define AMHW_ZSN700_LPUART_FLAG_CTS          (1ul << 6)   /* CTS�ߵ͵�ƽ��־λ,Ӳ������ */
#define AMHW_ZSN700_LPUART_FLAG_CTS_TRIGGER  (1ul << 5)   /* CTS��ת��־λ,�����0 */
#define AMHW_ZSN700_LPUART_FLAG_PARITY_ERR   (1ul << 4)   /* ��żУ������־λ,�����0 */
#define AMHW_ZSN700_LPUART_FLAG_TX_EMPTY     (1ul << 3)   /* ���Ϳձ�־λ,Ӳ������ */
#define AMHW_ZSN700_LPUART_FLAG_FRAME_ERR    (1ul << 2)   /* ֡�����־λ,�����0 */
#define AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE  (1ul << 1)   /* ������ɱ�־λ,�����0 */
#define AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE  (1ul << 0)   /* ������ɱ�־λ,�����0 */

/**
 * \brief UART ��־��ȡ
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] flag        : ��־�궨��   AMHW_ZSN700_LPUART_FLAG_CTS          ��
 *                                  AMHW_ZSN700_LPUART_FLAG_CTS_TRIGGER  ��
 *                                  AMHW_ZSN700_LPUART_FLAG_PARITY_ERR   ��
 *                                  AMHW_ZSN700_LPUART_FLAG_TX_EMPTY     ��
 *                                  AMHW_ZSN700_LPUART_FLAG_FRAME_ERR    ��
 *                                  AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE  ��
 *                                  AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE  ��
 *
 * \return AM_TRUE  : ��־��Ч
 *         AM_FALSE : ��־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_lpuart_flag_check (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                         uint8_t               flag)
{
    return (p_hw_lpuart->isr & flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief UART ��־���
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] flag        : ��־�궨��   AMHW_ZSN700_LPUART_FLAG_CTS_TRIGGER  ��
 *                                  AMHW_ZSN700_LPUART_FLAG_PARITY_ERR   ��
 *                                  AMHW_ZSN700_LPUART_FLAG_FRAME_ERR    ��
 *                                  AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE  ��
 *                                  AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE  ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_lpuart_flag_clr (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                  uint8_t               flag)
{
    p_hw_lpuart->icr &= ~ flag;
}

/**
 * \brief UART ״̬�Ĵ�����ֵ��ȡ
 *
 * \param[in] p_hw_lpuart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ״̬�Ĵ�����ֵ
 */
am_static_inline
uint32_t amhw_zsn700_lpuart_flag_get(amhw_zsn700_lpuart_t *p_hw_lpuart)
{

    return p_hw_lpuart->isr;
}


/**
 * \brief baud rate  set
 *
 * \param[in] p_hw_lpuart : pointer to UART register block
 * \param[in] uart_clk    : the clock of UART module
 * \param[in] baud        :  baud rate
 * \return baud rate
 */
int amhw_zsn700_lpuart_baudrate_set (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                     uint32_t              uart_clk,
                                     uint32_t              baud);

/**
 * \brief UART receive data(polling mode)
 * \param[in] p_hw_lpuart : pointer to UART register block
 * \param[in] p_rxbuf     : the pointer buffer
 * \param[in] nbytes      : bytes
 *
 * \return bytes
 */
uint32_t amhw_zsn700_lpuart_poll_receive (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                          uint8_t              *p_rxbuf,
                                          uint32_t              nbytes);

/**
 * \brief UART transfer data (polling mode)
 * \param[in] p_hw_lpuart : pointer to UART register block
 * \param[in] p_txbuf     : the pointer to buffer
 * \param[in] nbytes      : bytes
 *
 * \return bytes
 */
uint32_t amhw_zsn700_lpuart_poll_send (amhw_zsn700_lpuart_t  *p_hw_lpuart,
                                       const uint8_t         *p_txbuf,
                                       uint32_t               nbytes);
/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/** @} */

/**
 * @} amhw_zsn700_if_lpuart
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZSN700_LPUART_H */

/* end of file */
