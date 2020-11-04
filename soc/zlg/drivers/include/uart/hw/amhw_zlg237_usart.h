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
 * \brief USART�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-07-05  ari, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG237_USART_H
#define __AMHW_ZLG237_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_zlg237_if_usart
 * \copydoc amhw_zlg237_usart.h
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
 * \brief usart �Ĵ�����ṹ��
 */
typedef struct amhw_zlg237_usart {
    __IO uint32_t sr;        /**< \brief USART ״̬�Ĵ��� */
    __IO uint32_t dr;        /**< \brief USART ���ݼĴ��� */
    __IO uint32_t brr;       /**< \brief USART ���ر��ʼĴ��� */
    __IO uint32_t cr1;       /**< \brief USART ���ƼĴ���1 */
    __IO uint32_t cr2;       /**< \brief USART ���ƼĴ���2 */
    __IO uint32_t cr3;       /**< \brief USART ���ƼĴ���3 */
    __IO uint32_t gtpr;      /**< \brief USART ����ʱ���Ԥ��Ƶ�Ĵ��� */
} amhw_zlg237_usart_t;


/**
 * \brief ��ȡ״̬�Ĵ���ĳһ��־λ�Ƿ���Ч
 *
 * \param[in] none
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_all_clr (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->sr   = 0x00c0;
    p_hw_usart->dr   = 0x0000;
    p_hw_usart->brr  = 0x0000;
    p_hw_usart->cr1  = 0x0000;
    p_hw_usart->cr2  = 0x0000;
    p_hw_usart->cr3  = 0x0000;
    p_hw_usart->gtpr = 0x0000;
}


/**
 * \name  ״̬��־
 * \anchor amhw_zlg237_usart_
 * @{
 */
/** \brief CTS nCTS״̬�߱仯��־ */
#define AMHW_ZLG237_USART_CTS_FLAG               AM_BIT(9)

/** \brief LIN �Ͽ�����־ */
#define AMHW_ZLG237_USART_LIN_BREAK_FLAG         AM_BIT(8)

/** \brief TXE �������ݼĴ����ձ�־ */
#define AMHW_ZLG237_USART_TX_EMPTY_FLAG          AM_BIT(7)

/** \brief TC ������ɱ�־ */
#define AMHW_ZLG237_USART_TX_COMPLETE_FLAG       AM_BIT(6)

/** \brief RXNE �����ݼĴ����ǿձ�־ */
#define AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG      AM_BIT(5)

/** \brief IDLE ��⵽���߿��б�־ */
#define AMHW_ZLG237_USART_IDLE_FREE_FLAG         AM_BIT(4)

/** \brief ORE ���ش����־ */
#define AMHW_ZLG237_USART_OVERRUN_ERROR_FLAG     AM_BIT(3)

/** \brief NE ���������־ */
#define AMHW_ZLG237_USART_NOISE_ERROR_FLAG       AM_BIT(2)

/** \brief FE ֡�����־ */
#define AMHW_ZLG237_USART_FRAMING_ERROR_FLAG     AM_BIT(1)

/** \brief PE ��������־ */
#define AMHW_ZLG237_USART_PARITY_ERROR_FLAG      AM_BIT(0)
/** @} */

/**
 * \brief ��ȡ״̬�Ĵ���ĳһ��־λ�Ƿ���Ч
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag      : ���鿴��־λ�궨��
 *
 * \retval TRUE or FALSE
 */
am_static_inline
am_bool_t amhw_zlg237_usart_status_flag_check (amhw_zlg237_usart_t *p_hw_usart,
                                               uint32_t             flag)
{
    return ((0x3ffu & p_hw_usart->sr) & flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ���״̬�Ĵ�����־
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : �������־λ�궨��
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_status_flag_clr (amhw_zlg237_usart_t    *p_hw_usart,
                                        uint32_t                flag)
{
    p_hw_usart->sr = p_hw_usart->sr & (~(flag));
}

/**
 * \brief ���뷢������
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] data_w     : ����������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_data_write (amhw_zlg237_usart_t    *p_hw_usart,
                                   uint32_t                data_w)
{
    p_hw_usart->dr = (uint32_t)(0x1ffu & data_w);
}
/**
 * \brief ��ȡ��������
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return the data of RDR register
 */
am_static_inline
uint8_t amhw_zlg237_usart_data_read (amhw_zlg237_usart_t *p_hw_usart)
{
    return (uint8_t)(0x1ffu & p_hw_usart->dr);
}


/**
 * \brief ���ò����ʷ�Ƶϵ����������
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] data_w     : ����������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_br_div_mantissa_set (amhw_zlg237_usart_t    *p_hw_usart,
                                            uint32_t                data_w)
{
    AM_BITS_SET(p_hw_usart->brr, 4, 12, data_w);
}

/**
 * \brief ���ò����ʷ�Ƶϵ��С������
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] data_w     : ����������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_br_div_fraction_set (amhw_zlg237_usart_t    *p_hw_usart,
                                            uint32_t                data_w)
{
    AM_BITS_SET(p_hw_usart->brr, 0, 4, data_w);
}

/**
 * \brief ����һ���Ͽ�֡
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_send_break_set (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 |= (1u << 0);
}

/**
 * \brief ��ȡ�Ƿ����ڷ��ͶϿ�֡
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
am_bool_t amhw_zlg237_usart_send_break_check (amhw_zlg237_usart_t *p_hw_usart)
{
    return ((p_hw_usart->cr1) & (1u << 0)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief RWU ���ջ���ʹ�ܣ���Ĭģʽ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \note: �ڰ� USART���ھ�Ĭģʽ(���� RWUλ)֮ǰ��USARTҪ�Ѿ��Ƚ���
 *        ��һ�������ֽڡ������ھ�Ĭģʽ�£����ܱ��������߼�⻽�ѡ�
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_receiver_wakeup_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 |= (1u << 1);
}

/**
 * \brief RWU ���ջ��ѽ��ܣ���������ģʽ��
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_receiver_wakeup_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 &= ~(1u << 1);
}

/**
 * \brief RE ����ʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_receiver_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 |= (1u << 2);
}

/**
 * \brief RE ���ս���
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_receiver_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 &= ~(1u << 2);
}

/**
 * \brief TE ����ʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_transmitter_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 |= (1u << 3);
}

/**
 * \brief TE ���ͽ���
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_transmitter_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 &= ~(1u << 3);
}

/**
 * \name  Interrupt enable
 * \anchor amhw_zlg_uart_
 * @{
 */
/** \brief CTSIE CTS�ж�ʹ��          CR3 BIT 10*/
#define AMHW_ZLG237_USART_INT_CTS_ENABLE               (0x1u << 11)

/** \brief EIE �����ж�ʹ��                 CR3 BIT 0*/
#define AMHW_ZLG237_USART_INT_ERROR_ENABLE             (0x1u << 10)

/** \brief LBDIE �Ͽ�������ж�ʹ��     CR2 BIT 6*/
#define AMHW_ZLG237_USART_LIN_ENABLE                   (0x1u << 9)

/** \brief PE interrupt enable */
#define AMHW_ZLG237_USART_INT_PARITY_ENABLE            (0x1u << 8)

/** \brief TXE interrupt enable */
#define AMHW_ZLG237_USART_INT_TX_EMPTY_ENABLE          (0x1u << 7)

/** \brief TCIE interrupt enable */
#define AMHW_ZLG237_USART_INT_COMPLETE_ENABLE          (0x1u << 6)

/** \brief RXNE interrupt enable */
#define AMHW_ZLG237_USART_INT_RX_NOT_EMPTY_ENABLE      (0x1u << 5)

/** \brief IDLE interrupt enable */
#define AMHW_ZLG237_USART_INT_IDLE_FREE_ENABLE         (0x1u << 4)

/** \brief �����жϱ�־λ */
#define AMHW_ZLG237_USART_INT_ALL_ENABLE_MASK         (0xffu << 4)
/** @} */


/**
 * \brief �ж�ʹ��
 *
 * \param[in] p_hw_usart : pointer to UART register block
 * \param[in] flag       : interrupt enable   see the filed of interrupt enable
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_int_enable (amhw_zlg237_usart_t *p_hw_uart, uint32_t flag)
{

    /* ���������жϵ���� */
    if(flag == (0xffu << 4)) {
        p_hw_uart->cr1 |= (0x1fu << 4);             /* ����cr1�е�IDLE��RXNE��TCIE��TXE��PE*/
        p_hw_uart->cr2 |= (0x01u << 6);             /* ����cr2�е�LBDIE*/
        p_hw_uart->cr3 |= (0x01u << 0);             /* ����cr3�е�EIE*/
        p_hw_uart->cr3 |= (0x01u << 10);            /* ����cr3�е�CTSIE*/
    }else {
        if (flag == AMHW_ZLG237_USART_LIN_ENABLE){
            p_hw_uart->cr2 |= (0x01u << 6);         /* ����cr2�е�LBDIE*/
        } else if (flag == AMHW_ZLG237_USART_INT_ERROR_ENABLE) {
            p_hw_uart->cr3 |= (0x01u << 0);         /* ����cr3�е�EIE*/
        } else if (flag == AMHW_ZLG237_USART_INT_CTS_ENABLE) {
            p_hw_uart->cr3 |= (0x01u << 10);        /* ����cr3�е�CTSIE*/
        } else {
            p_hw_uart->cr1 |= (flag);               /* ����cr1�еĶ�Ӧ�ж�*/
        }
    }
}

/**
 * \brief �жϽ���
 *
 * \param[in] p_hw_uart : pointer to UART register block
 * \param[in] flag      : interrupt enable   see the filed of interrupt enable
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_int_disable (amhw_zlg237_usart_t *p_hw_uart, uint32_t flag)
{
    /* �ر������жϵ���� */
    if(flag == (0xffu << 4)) {
        p_hw_uart->cr1 &= ~(0x1fu << 4);             /* �ر�cr1�е�IDLE��RXNE��TCIE��TXE��PE*/
        p_hw_uart->cr2 &= ~(0x01u << 6);             /* �ر�cr2�е�LBDIE*/
        p_hw_uart->cr3 &= ~(0x01u << 0);             /* �ر�cr3�е�EIE*/
        p_hw_uart->cr3 &= ~(0x01u << 10);            /* �ر�cr3�е�CTSIE*/
    }else {
        if (flag == AMHW_ZLG237_USART_LIN_ENABLE){
            p_hw_uart->cr2 &= ~(0x01u << 6);         /* �ر�cr2�е�LBDIE*/
        } else if (flag == AMHW_ZLG237_USART_INT_ERROR_ENABLE) {
            p_hw_uart->cr3 &= ~(0x01u << 0);         /* �ر�cr3�е�EIE*/
        } else if (flag == AMHW_ZLG237_USART_INT_CTS_ENABLE) {
            p_hw_uart->cr3 &= ~(0x01u << 10);        /* �ر�cr3�е�CTSIE*/
        } else {
            p_hw_uart->cr1 &= ~(flag);               /* �ر�cr1�еĶ�Ӧ�ж�*/
        }
    }
}
/**
 * \brief USART parity bit select
 * @{
 */
#define AMHW_ZLG237_USART_PARITY_NO   (0U)  /** <brief ��У��  00 */
#define AMHW_ZLG237_USART_PARITY_ODD  (3U)  /** <brief ��У��  11 */
#define AMHW_ZLG237_USART_PARITY_EVEN (2U)  /** <brief żУ��  10 */
/** @} */

/**
 * \brief У�鷽ʽ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : У�鷽ʽ�궨��
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_parity_bit_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                       uint32_t                parity)
{
    p_hw_usart->cr1 = (p_hw_usart->cr1 & (~(0x3u << 9))) | (parity << 9);
}

/**
 * \brief ���ѷ�������
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : 0�����������߻���
 *                            1������ַ��ǻ���
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_wakeup_method_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                          uint32_t                flag)
{
    p_hw_usart->cr1 = (p_hw_usart->cr1 & (~(0x1u << 11))) | (flag << 11);
}

/**
 * \brief USART data length
 * @{
 */
#define AMHW_ZLG237_USART_DATA_8BIT   (0u << 4) /** <brief 8-bit data */
#define AMHW_ZLG237_USART_DATA_9BIT   (1u << 4) /** <brief 9-bit data */
/** @} */
/**
 * \brief �ֳ�����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : 0��1����ʼλ��8������λ��n��ֹͣλ
 *                         1��1����ʼλ��9������λ��n��ֹͣλ
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_word_length_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                        uint32_t                flag)
{
    p_hw_usart->cr1 = (p_hw_usart->cr1 & (~(0x1u << 12))) | ((flag >> 4) << 12);
}

/**
 * \brief USARTʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 |= (1 << 13);
}

/**
 * \brief USART����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr1 &= ~(1u << 13);
}

/**
 * \brief ���豸�ڵ��ַ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : �ڵ��ַ�趨ֵ��0~15��
 *
 *  note: �ڶദ����ͨ���µľ�Ĭģʽ��ʹ�ã�ʹ�õ�ַ���������ĳ�� USART�豸
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_addr_set (amhw_zlg237_usart_t    *p_hw_usart,
                                 uint32_t                flag)
{
    p_hw_usart->cr2 = (p_hw_usart->cr2 & (~(0xfu << 0))) | (flag << 0);
}

/**
 * \brief LIN�Ͽ�����ⳤ������
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : 0��10 λ�ĶϿ������
 *                         1��11 λ�ĶϿ������
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_lbd_length_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                       uint32_t                flag)
{
    p_hw_usart->cr2 = (p_hw_usart->cr2 & (~(0x1u << 5))) | (flag << 5);
}

/**
 * \brief LBCL ���һλʱ������
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag      : 0�����һλ���ݵ�ʱ�����岻�� CK���
 *                        1�����һλ���ݵ�ʱ�������� CK���
 *
 * \noet: ��ͬ��ģʽ�£�ʹ�ø�λ�������Ƿ��� CK������������ ���͵�
 *        �Ǹ������ֽ�(MSB)��Ӧ��ʱ������.
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_last_bit_clock_pulse (amhw_zlg237_usart_t    *p_hw_usart,
                                             uint32_t                flag)
{
    p_hw_usart->cr2 = (p_hw_usart->cr2 & (~(0x1u << 8))) | (flag << 8);
}

/**
 * \brief CPHA ʱ����λ
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag      : 0����ʱ�ӵĵ�һ�����ؽ������ݲ���
 *                        1����ʱ�ӵĵ�һ�����ؽ������ݲ���
 *
 * \noet: ��ͬ��ģʽ�£������ø�λѡ�� SLCK������ʱ���������λ����
 *        CPOLλһ�������������Ҫ��ʱ��/���ݵĲ�����ϵ��
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_clock_phase (amhw_zlg237_usart_t    *p_hw_usart,
                                    uint32_t                flag)
{
    p_hw_usart->cr2 = (p_hw_usart->cr2 & (~(0x1u << 9))) | (flag << 9);
}

/**
 * \brief CPOL ʱ�Ӽ���
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag      : 0�����߿���ʱ CK�����ϱ��ֵ͵�ƽ
 *                        1�����߿���ʱ CK�����ϱ��ָߵ�ƽ
 *
 * \noet: ��ͬ��ģʽ�£������ø�λѡ�� SLCK������ʱ������ļ��ԡ�
 *        �� CPHAλһ�������������Ҫ��ʱ��/���ݵĲ�����ϵ
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_clock_polarity (amhw_zlg237_usart_t    *p_hw_usart,
                                       uint32_t                flag)
{
    p_hw_usart->cr2 = (p_hw_usart->cr2 & (~(0x1u << 10))) | (flag << 10);
}

/**
 * \brief CLKEN ʱ��ʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_clock_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr2 |= (0x1u << 11);
}

/**
 * \brief CLKEN ʱ�ӽ���
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_clock_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr2 &= ~(0x1u << 11);
}


/**
 * \brief USART stop bit select
 * @{
 */
#define AMHW_ZLG237_USART_STOP_10_BIT   (0u << 2)  /** <brief 1   stop bit */
#define AMHW_ZLG237_USART_STOP_05_BIT   (1u << 2)  /** <brief 0.5 stop bit */
#define AMHW_ZLG237_USART_STOP_20_BIT   (2u << 2)  /** <brief 2   stop bit */
#define AMHW_ZLG237_USART_STOP_15_BIT   (3u << 2)  /** <brief 1.5 stop bit */
/** @} */

/**
 * \brief STOP ֹͣλ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : ֹͣλ�궨��
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_stop_bit_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                     uint32_t                flag)
{
    p_hw_usart->cr2 = (p_hw_usart->cr2 & (~(0x3u << 12))) | ((flag >> 2) << 12);
}

/**
 * \brief LINEN LINģʽʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_lin_mode_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr2 |= (1u << 14);
}

/**
 * \brief LINEN LINģʽ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_lin_mode_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr2 &= ~(1u << 14);
}

/**
 * \brief IREN ����ģʽʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \note: �ڶ໺����ͨ��ģʽ�£�����֡���󡢹��ػ�����������ʱ(USART_SR
 *        �е� FE=1������ ORE=1������ NE=1)�����жϡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_irda_mode_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 1);
}

/**
 * \brief IREN ����ģʽ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_irda_mode_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 1);
}

/**
 * \brief IRLP ����͹���ʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_irda_lowpower_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 2);
}

/**
 * \brief IRLP ����͹��Ľ���
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_irda_lowpower_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 2);
}

/**
 * \brief HDSEL ��˫��ѡ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : 0����ѡ���˫��ģʽ
 *                         1��    ѡ���˫��ģʽ
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_half_duplex_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                        uint32_t                flag)
{
    p_hw_usart->cr3 = (p_hw_usart->cr3 & (~(0x1u << 3))) | (flag << 3);
}

/**
 * \brief NACK ���ܿ� NACKʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_smartcard_nack_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 4);
}

/**
 * \brief NACK ���ܿ� NACK����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_smartcard_nack_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 4);
}

/**
 * \brief SCEN ���ܿ�ģʽʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_smartcard_mode_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 5);
}

/**
 * \brief SCEN ���ܿ�ģʽ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_smartcard_mode_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 5);
}

/**
 * \brief DMAR DMAʹ�ܽ���ʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_dmar_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 6);
}

/**
 * \brief DMAR DMAʹ�ܽ��ս���
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_dmar_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 6);
}

/**
 * \brief DMAT DMAʹ�ܷ���ʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_dmat_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 7);
}

/**
 * \brief DMAT DMAʹ�ܷ��ͽ���
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_dmat_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 7);
}

/**
 * \brief RTSE RTSʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \note:RTS �ж�ʹ�ܣ�ֻ�н��ջ��������п���Ŀռ�ʱ��������һ�����ݡ�
 *           ��ǰ���ݷ�����ɺ󣬷��Ͳ�������Ҫ��ͣ������������Խ���
 *           �����ˣ��� nRTS�����Ϊ��Ч(�����͵�ƽ)��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_rts_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 8);
}

/**
 * \brief RTSE RTS����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_rts_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 8);
}

/**
 * \brief CTSE CTSʹ��
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \note: CTS ģʽʹ�ܣ�ֻ�� nCTS �����ź���Ч(���ɵ͵�ƽ)ʱ���ܷ������ݡ�
 *            ��������ݴ���Ĺ����У�nCTS �źű����Ч����ô�����������
 *            �󣬴����ֹͣ�����������nCTS Ϊ��Чʱ�������ݼĴ�����д��
 *            �ݣ���Ҫ�ȵ� nCTS��Чʱ�Żᷢ��������ݡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_cts_enable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 |= (1u << 9);
}

/**
 * \brief CTSE CTS����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_usart_cts_disable (amhw_zlg237_usart_t *p_hw_usart)
{
    p_hw_usart->cr3 &= ~(1u << 9);
}

/**
 * \brief PSC[7:0] Ԥ��Ƶ��ֵ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag       : Ԥ��Ƶ��ֵ����
 *
 * \note: 1.�ں���(IrDA)�͹���ģʽ�£�
 *          PSC[7:0]=����͹��Ĳ����ʶ�ϵͳʱ�ӷ�Ƶ�Ի�õ͹���ģʽ�µ�Ƶ��:
 *              00000000������ �C ��Ҫд���ֵ��
 *                00000001����Դʱ�� 1 ��Ƶ��
 *                00000010����Դʱ�� 2 ��Ƶ��
 *                ......
 *          2.�ں���(IrDA)������ģʽ�£�
 *            PSCֻ������Ϊ 00000001
 *          3.�����ܿ�ģʽ��,λ[7:5]�����ܿ�ģʽ��û������. ��ϵͳʱ�ӽ��з�Ƶ�������ܿ��ṩʱ�ӡ�
 *                    �Ĵ����и�����ֵ(�� 5 λ��Ч)���� 2 ����Ϊ��Դʱ�ӵķ�Ƶ����
 *              00000������ �C ��Ҫд���ֵ��
 *              00001����Դʱ�ӽ��� 2 ��Ƶ��
 *              00010����Դʱ�ӽ��� 4 ��Ƶ��
 *              00011����Դʱ�ӽ��� 6 ��Ƶ��
 *              ......
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_prescaler_value_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                            uint32_t                data)
{
    p_hw_usart->gtpr = (p_hw_usart->gtpr & (~(0xffu << 0))) | (data << 0);
}

/**
 * \brief GT[7:0] ����ʱ��ֵ����
 *
 * \param[in] p_hw_usart : ���ڼĴ����ṹ���ָ��
 * \param[in] flag      : �趨ʱ��ֵ����
 *
 * \note: ��λ��涨���Բ���ʱ��Ϊ��λ�ı���ʱ�䡣�����ܿ�ģʽ�£�
 *        ��Ҫ������ܡ�������ʱ���ȥ�󣬲Ż����÷�����ɱ�־��
 *
 * \retval none
 */
am_static_inline
void amhw_zlg237_usart_guard_time_value_sel (amhw_zlg237_usart_t    *p_hw_usart,
                                             uint32_t                data)
{
    p_hw_usart->gtpr = (p_hw_usart->gtpr & (~(0xffu << 8))) | (data << 8);
}


/**
 * \brief baud rate  set
 *
 * \param[in] p_hw_usart : pointer to USART register block
 * \param[in] usart_clk  : the clock of USART module
 * \param[in] baud      :  baud rate
 * \return baud rate
 */
int amhw_zlg237_usart_baudrate_set (amhw_zlg237_usart_t    *p_hw_usart,
                                    uint32_t                usart_clk,
                                    uint32_t                baud);

/**
 * \brief USART receive data(polling mode)
 * \param[in] p_hw_usart : pointer to USART register block
 * \param[in] p_rxbuf    : the pointer buffer
 * \param[in] nbytes     : bytes
 *
 * \return bytes
 */
uint32_t amhw_zlg237_usart_poll_receive (amhw_zlg237_usart_t    *p_hw_usart,
                                         uint8_t                *p_rxbuf,
                                         uint32_t                nbytes);

/**
 * \brief USART transfer data (polling mode)
 * \param[in] p_hw_usart : pointer to USART register block
 * \param[in] p_txbuf    : the pointer to buffer
 * \param[in] nbytes     :  bytes
 *
 * \return bytes
 */
uint32_t amhw_zlg237_usart_poll_send (amhw_zlg237_usart_t     *p_hw_usart,
                                      const uint8_t           *p_txbuf,
                                      uint32_t                 nbytes);
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
 * @} amhw_zlg237_if_usart
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG237_USART_H */

/* end of file */
