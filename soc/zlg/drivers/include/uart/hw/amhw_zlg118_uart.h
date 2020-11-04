/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief UART�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-19  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG118_UART_H
#define __AMHW_ZLG118_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_zlg118_if_uart
 * \copydoc amhw_zlg118_uart.h
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
typedef struct amhw_zlg118_uart {
    __IO uint32_t sbuf;       /**< \brief ���ݼĴ��� */
    __IO uint32_t scon;       /**< \brief ���ƼĴ��� */
    __IO uint32_t saddr;      /**< \brief ��ַ�Ĵ��� */
    __IO uint32_t saden;      /**< \brief ��ַ����Ĵ��� */
    __IO uint32_t isr;        /**< \brief �жϱ�־λ�Ĵ��� */
    __IO uint32_t icr;        /**< \brief �жϱ�־λ����Ĵ��� */
    __IO uint32_t scnt;       /**< \brief �����ʼĴ��� */
} amhw_zlg118_uart_t;

/**
 * \brief �趨DATA[8]
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] am_bool_t : AM_TRUE��1��  ����      AM_FALSE��0��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_uart_data_8th_set (amhw_zlg118_uart_t *p_hw_uart,
                                    am_bool_t           stat)
{
    p_hw_uart->sbuf = (p_hw_uart->sbuf & (~(0x1ul << 8))) | (stat << 8);
}

/**
 * \brief ��ȡDATA[8]
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return  AM_TRUE��1��  ����      AM_FALSE��0��
 */
am_static_inline
am_bool_t amhw_zlg118_uart_data_8th_get (amhw_zlg118_uart_t *p_hw_uart)
{
    return ((p_hw_uart->sbuf >> 8) & 0x1ul);
}

/**
 * \brief д����
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] data_w    : ��д������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_uart_data_write (amhw_zlg118_uart_t *p_hw_uart,
                                  uint8_t             data_w)
{
    p_hw_uart->sbuf = (p_hw_uart->sbuf & (~0xfful)) | (0xff & data_w);
}

/**
 * \brief ������
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return �Ĵ�������
 */
am_static_inline
uint8_t amhw_zlg118_uart_data_read (amhw_zlg118_uart_t *p_hw_uart)
{
    return (0xffu & p_hw_uart->sbuf);
}

/**
 * \brief HDSEL ���߰�˫��ģʽ   ����
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��
 */

am_static_inline
void amhw_zlg118_uart_single_line_half_disable (amhw_zlg118_uart_t *p_hw_uart)
{
    p_hw_uart->scon &= ~(0x1ul << 22);
}

/**
 * \brief HDSEL ���߰�˫��ģʽ   ʹ��
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��
 */

am_static_inline
void amhw_zlg118_uart_single_line_half_enable (amhw_zlg118_uart_t *p_hw_uart)
{
    p_hw_uart->scon |= (0x1ul << 22);
}


#define AMHW_ZLG118_UART_INT_FRAME_ERR   (1ul << 21)   /* ֡�����ж�ʹ��λ */
#define AMHW_ZLG118_UART_INT_CTS_TRIGGER (1ul << 20)   /* CTS��ת�ж�ʹ��λ */
#define AMHW_ZLG118_UART_INT_PARITY_ERR  (1ul << 13)   /* ��żУ������ж�ʹ��λ */
#define AMHW_ZLG118_UART_INT_TX_EMPTY    (1ul << 8)    /* TX���ж�ʹ��λ  */
#define AMHW_ZLG118_UART_INT_TX_COMPLETE (1ul << 1)    /* �����ж�ʹ��λ */
#define AMHW_ZLG118_UART_INT_RX_COMPLETE (1ul << 0)    /* �����ж�ʹ��λ */
#define AMHW_ZLG118_UART_INT_ALL         0xFF          /* �����жϱ�־ */

/**
 * \brief UART ����ж�  ����
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type      : �жϺ궨��  AMHW_ZLG118_UART_INT_FRAME_ERR
 *                               ��
 *                               ��
 *                               ��
 *                               AMHW_ZLG118_UART_INT_ALL
 *
 * \return ��
 */

am_static_inline
void amhw_zlg118_uart_int_disable (amhw_zlg118_uart_t *p_hw_uart,
                                   uint32_t            type)
{
    if(type == 0xFF) {
        p_hw_uart->scon &= ~(1ul << 21);
        p_hw_uart->scon &= ~(1ul << 20);
        p_hw_uart->scon &= ~(1ul << 13);
        p_hw_uart->scon &= ~(1ul << 8);
        p_hw_uart->scon &= ~(1ul << 1);
        p_hw_uart->scon &= ~(1ul << 0);
    } else {
        p_hw_uart->scon &= ~type;
    }
}

/**
 * \brief UART ����ж�  ʹ��
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type      : �жϺ궨��  AMHW_ZLG118_UART_INT_FRAME_ERR
 *                               ��
 *                               ��
 *                               ��
 *                               AMHW_ZLG118_UART_INT_ALL
 *
 * \return ��
 */

am_static_inline
void amhw_zlg118_uart_int_enable (amhw_zlg118_uart_t *p_hw_uart,
                                  uint32_t            type)
{
    if(type == 0xFF) {
        p_hw_uart->scon |= (1ul << 21);
        p_hw_uart->scon |= (1ul << 20);
        p_hw_uart->scon |= (1ul << 13);
        p_hw_uart->scon |= (1ul << 8);
        p_hw_uart->scon |= (1ul << 1);
        p_hw_uart->scon |= (1ul << 0);
    } else {
        p_hw_uart->scon |= type;
    }
}

/**
 * \brief UART �����жϱ�־�鿴
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return 1 �ж�ʹ��
 *         0 �жϽ���
 */

am_static_inline
uint8_t amhw_zlg118_uart_int_check (amhw_zlg118_uart_t *p_hw_uart)
{
    return (p_hw_uart->scon & 0x01);
}

#define AMHW_ZLG118_UART_CTS          (1ul << 19) /* Ӳ����CTSʹ��λ */
#define AMHW_ZLG118_UART_RTS          (1ul << 18) /* Ӳ����RTSʹ��λ */
#define AMHW_ZLG118_UART_DMA_TX       (1ul << 17) /* ����DMAʹ��λ */
#define AMHW_ZLG118_UART_DMA_RX       (1ul << 16) /* ����DMAʹ��λ */
#define AMHW_ZLG118_UART_MUT_ADR_AUTO (1ul << 5)  /* �����ַ�Զ�ʶ��ʹ��λ */
#define AMHW_ZLG118_UART_RX           (1ul << 4)  /* ����ʹ��
                                                   * Mode0:     0������; 1������
                                                   * Mode1/2/3: 0������; 1�� ����/����
                                                   */
/**
 * \brief UART ��ؿ���  ����
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type      : �жϺ궨��  AMHW_ZLG118_UART_CTS
 *                               ��
 *                               ��
 *                               ��
 *                               AMHW_ZLG118_UART_RX
 *
 * \return ��
 */

am_static_inline
void amhw_zlg118_uart_disable (amhw_zlg118_uart_t *p_hw_uart,
                               uint32_t            type)
{
    p_hw_uart->scon &= ~type;
}

/**
 * \brief UART ��ؿ���  ʹ��
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] type      : �жϺ궨��  AMHW_ZLG118_UART_CTS
 *                               ��
 *                               ��
 *                               ��
 *                               AMHW_ZLG118_UART_RX
 *
 * \return ��
 */

am_static_inline
void amhw_zlg118_uart_enable (amhw_zlg118_uart_t *p_hw_uart,
                              uint32_t            type)
{
    p_hw_uart->scon |= type;
}

#define AMHW_ZLG118_UART_STOP_1_0_BIT   (0ul << 14)  /* 1��ֹͣλ */
#define AMHW_ZLG118_UART_STOP_1_5_BIT   (1ul << 14)  /* 1.5��ֹͣλ */
#define AMHW_ZLG118_UART_STOP_2_0_BIT   (2ul << 14)  /* 2��ֹͣλ */

/**
 * \brief ֹͣλ����
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] stop_bit  : ֹͣλ�궨��   AMHW_ZLG118_UART_STOP_1_0_BIT ��
 *                                 AMHW_ZLG118_UART_STOP_1_5_BIT ��
 *                                 AMHW_ZLG118_UART_STOP_2_0_BIT
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_uart_stop_bit_sel (amhw_zlg118_uart_t *p_hw_uart,
                                    uint32_t            stop_bit)
{
    p_hw_uart->scon = (p_hw_uart->scon & (~(0x3ul << 14))) | stop_bit;
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
    AMHW_ZLG118_UART_WORK_MODE_0 = 0,
    AMHW_ZLG118_UART_WORK_MODE_1,
    AMHW_ZLG118_UART_WORK_MODE_2,
    AMHW_ZLG118_UART_WORK_MODE_3,
    AMHW_ZLG118_UART_WORK_MODE_4,
}amhw_zlg118_uart_work_mode_t;
/**
 * \brief ����ģʽ�趨
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] stop_bit  : AMHW_ZLG118_UART_WORK_MODE_0 ��
 *                        AMHW_ZLG118_UART_WORK_MODE_1 ��
 *                        AMHW_ZLG118_UART_WORK_MODE_2 ��
 *                        AMHW_ZLG118_UART_WORK_MODE_3
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_uart_mode_sel (amhw_zlg118_uart_t           *p_hw_uart,
                                amhw_zlg118_uart_work_mode_t  mode_type)
{
    p_hw_uart->scon = (p_hw_uart->scon & (~(0x3ul << 6))) |
                      ((mode_type & 0x3ul) << 6);
}

/**
 * \brief ����ģʽ��ȡ
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��ǰ����ģʽ0/1/2/3
 */
am_static_inline
amhw_zlg118_uart_work_mode_t amhw_zlg118_uart_mode_get (amhw_zlg118_uart_t
                                                            *p_hw_uart)
{
    return (amhw_zlg118_uart_work_mode_t)((p_hw_uart->scon >> 6) & 0x3ul);
}

#define AMHW_ZLG118_UART_SOFT           (0ul << 2)  /* �����дSBUF[8] */
#define AMHW_ZLG118_UART_HW_PARITY_EVEN (1ul << 2)  /* Ӳ��żУ�� */
#define AMHW_ZLG118_UART_HW_PARITY_ODD  (2ul << 2)  /* Ӳ����У�� */
#define AMHW_ZLG118_UART_PARITY_NO      (3ul << 2)  /* ���� */
/**
 * \brief UART parity bit select
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity    : ��żУ��궨��       AMHW_ZLG118_UART_SOFT              ��
 *                                    AMHW_ZLG118_UART_HW_PARITY_EVEN    ��
 *                                    AMHW_ZLG118_UART_HW_PARITY_ODD     ��
 *                                    AMHW_ZLG118_UART_PARITY_NO
 * \return none
 */
am_static_inline
void amhw_zlg118_uart_parity_bit_sel (amhw_zlg118_uart_t *p_hw_uart,
                                      uint32_t            parity)
{
    p_hw_uart->scon = (p_hw_uart->scon & (~(0x3ul << 2))) | parity;
}

typedef enum {
    AMHW_ZLG118_UART_CLK_DIV_MODE0_NO  = 0,    /* ģʽ0��������Ƶ��Ч */
    AMHW_ZLG118_UART_CLK_DIV_MODE13_16 = 0,    /* ģʽ1/3��16������Ƶ */
    AMHW_ZLG118_UART_CLK_DIV_MODE13_8  = 1,    /* ģʽ1/3��8������Ƶ */
    AMHW_ZLG118_UART_CLK_DIV_MODE2_32  = 0,    /* ģʽ2��32������Ƶ */
    AMHW_ZLG118_UART_CLK_DIV_MODE2_16  = 1,    /* ģʽ2��16������Ƶ */
}amhw_zlg118_uart_clk_div_t;
/**
 * \brief UART ������Ƶ����
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity    : ��Ƶϵ��amhw_zlg118_uart_clk_div_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_uart_clk_div_sel (amhw_zlg118_uart_t         *p_hw_uart,
                                   amhw_zlg118_uart_clk_div_t  clk_div)
{
    p_hw_uart->scon = (p_hw_uart->scon & (~(0x1ul << 9))) | (clk_div << 9);
}

/**
 * \brief UART ������Ƶ��ȡ
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ��Ƶϵ���趨ֵ������ķ�Ƶֵ��Ҫ��Ϲ���ģʽһ���ж�����amhw_zlg118_uart_clk_div_tö������
 */
am_static_inline
uint8_t amhw_zlg118_uart_clk_div_get (amhw_zlg118_uart_t *p_hw_uart)
{
    return ((p_hw_uart->scon >> 9) & 0x1ul);
}

/**
 * \brief UART ���豸��ַ����
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity    : ���豸��ַ��8λ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_uart_slaver_addr_set (amhw_zlg118_uart_t *p_hw_uart,
                                       uint8_t             slaver_addr)
{
    p_hw_uart->saddr = slaver_addr & 0xFF;
}

/**
 * \brief UART ���豸��ַ��ȡ
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ���豸��ַ��8λ��
 */
am_static_inline
uint8_t amhw_zlg118_uart_slaver_addr_get (amhw_zlg118_uart_t *p_hw_uart)
{
    return (p_hw_uart->saddr & 0xFF);
}

/**
 * \brief UART ���豸��ַ��������
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] parity    : ���豸��ַ���루0��������           1�����ģ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_uart_slaver_addr_mask_set (amhw_zlg118_uart_t *p_hw_uart,
                                            uint8_t             addr_mask)
{
    p_hw_uart->saden = addr_mask & 0xFF;
}

/**
 * \brief UART ���豸��ַ�����ȡ
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ���豸��ַ���루0��������           1�����ģ�
 */
am_static_inline
uint8_t amhw_zlg118_uart_slaver_addr_mask_get (amhw_zlg118_uart_t *p_hw_uart)
{
    return (p_hw_uart->saden & 0xFF);
}

#define AMHW_ZLG118_UART_FLAG_CTS          (1ul << 6)   /* CTS�ߵ͵�ƽ��־λ,Ӳ������ */
#define AMHW_ZLG118_UART_FLAG_CTS_TRIGGER  (1ul << 5)   /* CTS��ת��־λ,�����0 */
#define AMHW_ZLG118_UART_FLAG_PARITY_ERR   (1ul << 4)   /* ��żУ������־λ,�����0 */
#define AMHW_ZLG118_UART_FLAG_TX_EMPTY     (1ul << 3)   /* ���Ϳձ�־λ,Ӳ������ */
#define AMHW_ZLG118_UART_FLAG_FRAME_ERR    (1ul << 2)   /* ֡�����־λ,�����0 */
#define AMHW_ZLG118_UART_FLAG_TX_COMPLETE  (1ul << 1)   /* ������ɱ�־λ,�����0 */
#define AMHW_ZLG118_UART_FLAG_RX_COMPLETE  (1ul << 0)   /* ������ɱ�־λ,�����0 */
#define AMHW_ZLG118_UART_FLAG_ALL          (0x7f)       /* ���б�־���� */
/**
 * \brief UART ��־��ȡ
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] flag      : ��־�궨��   AMHW_ZLG118_UART_FLAG_CTS          ��
 *                                AMHW_ZLG118_UART_FLAG_CTS_TRIGGER  ��
 *                                AMHW_ZLG118_UART_FLAG_PARITY_ERR   ��
 *                                AMHW_ZLG118_UART_FLAG_TX_EMPTY     ��
 *                                AMHW_ZLG118_UART_FLAG_FRAME_ERR    ��
 *                                AMHW_ZLG118_UART_FLAG_TX_COMPLETE  ��
 *                                AMHW_ZLG118_UART_FLAG_RX_COMPLETE  ��
 *
 * \return AM_TRUE  : ��־��Ч
 *         AM_FALSE : ��־��Ч
 */
am_static_inline
am_bool_t amhw_zlg118_uart_flag_check (amhw_zlg118_uart_t *p_hw_uart,
                                       uint8_t             flag)
{
    return (p_hw_uart->isr & flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief UART ��־���
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 * \param[in] flag      : ��־�궨��   AMHW_ZLG118_UART_FLAG_CTS_TRIGGER  ��
 *                                AMHW_ZLG118_UART_FLAG_PARITY_ERR   ��
 *                                AMHW_ZLG118_UART_FLAG_FRAME_ERR    ��
 *                                AMHW_ZLG118_UART_FLAG_TX_COMPLETE  ��
 *                                AMHW_ZLG118_UART_FLAG_RX_COMPLETE  ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_uart_flag_clr (amhw_zlg118_uart_t *p_hw_uart,
                                uint8_t             flag)
{
    p_hw_uart->icr &= ~ flag;
}

/**
 * \brief UART ״̬�Ĵ�����ֵ��ȡ
 *
 * \param[in] p_hw_uart : ָ��UART�Ĵ����ṹ���ָ��
 *
 * \return ״̬�Ĵ�����ֵ
 */
am_static_inline
uint32_t amhw_zlg118_uart_flag_get(amhw_zlg118_uart_t *p_hw_uart)
{

    return p_hw_uart->isr;
}


/**
 * \brief baud rate  set
 *
 * \param[in] p_hw_uart : pointer to UART register block
 * \param[in] uart_clk  : the clock of UART module
 * \param[in] baud      :  baud rate
 * \return baud rate
 */
int amhw_zlg118_uart_baudrate_set (amhw_zlg118_uart_t *p_hw_uart,
                                   uint32_t            uart_clk,
                                   uint32_t            baud);

/**
 * \brief UART receive data(polling mode)
 * \param[in] p_hw_uart : pointer to UART register block
 * \param[in] p_rxbuf   : the pointer buffer
 * \param[in] nbytes    : bytes
 *
 * \return bytes
 */
uint32_t amhw_zlg118_uart_poll_receive (amhw_zlg118_uart_t    *p_hw_uart,
                                        uint8_t            *p_rxbuf,
                                        uint32_t            nbytes);

/**
 * \brief UART transfer data (polling mode)
 * \param[in] p_hw_uart : pointer to UART register block
 * \param[in] p_txbuf   : the pointer to buffer
 * \param[in] nbytes    :  bytes
 *
 * \return bytes
 */
uint32_t amhw_zlg118_uart_poll_send (amhw_zlg118_uart_t     *p_hw_uart,
                                     const uint8_t       *p_txbuf,
                                     uint32_t             nbytes);
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
 * @} amhw_zlg118_if_uart
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_UART_H */

/* end of file */
