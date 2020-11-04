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
 * \brief �͹��Ķ�ʱ��LPTIM�ӿ�
 *
 * \internal
 * \par History
 * - 1.00 19-09-27  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG118_LPTIM_H
#define __AMHW_ZLG118_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zlg118_if_lptim
 * \copydoc amhw_zlg118_lptim.h
 * @{
 */

/**
  * \brief ��ʱ���Ĵ�����ṹ��
  */
typedef struct amhw_zlg118_lptim {
    __I  uint32_t cnt;         /**< \brief ����ֵֻ���Ĵ��� */
    __IO uint32_t arr;         /**< \brief ���ؼĴ��� */
    __IO uint32_t reserve;     /**< \brief ����λ */
    __IO uint32_t cr;          /**< \brief ���ƼĴ��� */
    __I  uint32_t ifr;         /**< \brief �жϱ�־�Ĵ��� */
    __IO uint32_t iclr;        /**< \brief �ж�����Ĵ��� */
} amhw_zlg118_lptim_t;

/**
 * \brief �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��ǰ��������ֵ
 */
am_static_inline
uint16_t amhw_zlg118_lptim_cnt16_count_get (amhw_zlg118_lptim_t *p_hw_lptim)
{
    return p_hw_lptim->cnt;
}

/**
 * \brief �������ؼĴ�����ֵ
 *
 * \param[in] p_hw_lptim :    ָ��LPTIM��ʱ���Ĵ������ָ��
 * \param[in] value      :    ���õ����ؼĴ�����ֵ
 *
 * \note  д ARRǰ��Ҫ��ȡ CR.WT_FLAG�����Ҿ��� WT_FLAGΪ1ʱ��д��ʱ����д�����ݡ�
 *        дARR�Ĵ����� WT_FLAG���͡�
 *
 *        ע���ڶ�ʱ������ʱ��������ʱ���ֵ��װ�ص���ʱ���������С���ʱ��������ֵ����������ġ�
 *
 *\ return ��
 */
am_static_inline
void amhw_zlg118_lptim_arr_count_set (amhw_zlg118_lptim_t *p_hw_lptim,
                                      uint16_t value)
{
    p_hw_lptim->arr = value;
}

/**
 * \brief �������ؼĴ�����ֵ
 *
 * \param[in] p_hw_lptim :    ָ��LPTIM��ʱ���Ĵ������ָ��
 * \param[in] value      :    ���õ����ؼĴ�����ֵ
 *
 * \note  д ARRǰ��Ҫ��ȡ CR.WT_FLAG�����Ҿ��� WT_FLAGΪ1ʱ��д��ʱ����д�����ݡ�
 *        дARR�Ĵ����� WT_FLAG���͡�
 *
 *        ע���ڶ�ʱ������ʱ��������ʱ���ֵ��װ�ص���ʱ���������С���ʱ��������ֵ����������ġ�
 *
 *\ return ��
 */
am_static_inline
uint16_t amhw_zlg118_lptim_arr_count_get (amhw_zlg118_lptim_t *p_hw_lptim)
{
    return p_hw_lptim->arr;
}

/**
 * \brief ʱ�ӷ�Ƶѡ���ڶ�ʱ������ʱ�����Ը��ģ�
 */
typedef enum {
    AMHW_ZLG118_LPTIM_CLK_DIV1 = 0,    /* 1��Ƶ */
    AMHW_ZLG118_LPTIM_CLK_DIV2,        /* 2��Ƶ */
    AMHW_ZLG118_LPTIM_CLK_DIV4,        /* 4��Ƶ */
    AMHW_ZLG118_LPTIM_CLK_DIV8,        /* 8��Ƶ */
    AMHW_ZLG118_LPTIM_CLK_DIV16,       /* 16��Ƶ */
    AMHW_ZLG118_LPTIM_CLK_DIV32,       /* 32��Ƶ */
    AMHW_ZLG118_LPTIM_CLK_DIV64,       /* 64��Ƶ */
    AMHW_ZLG118_LPTIM_CLK_DIV256,      /* 256��Ƶ */
}amhw_zlg118_lptim_clk_div_t;

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ��ȡ
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ���õķ�Ƶϵ����amhw_zlg118_lptim_clk_div_tö������
 */
am_static_inline
amhw_zlg118_lptim_clk_div_t
amhw_zlg118_lptim_clk_div_get (amhw_zlg118_lptim_t *p_hw_lptim)
{
    return (amhw_zlg118_lptim_clk_div_t)((p_hw_lptim->cr >> 11) & 0x7ul);
}

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ����
 *
 * \param[in] p_hw_lptim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] clkdiv   : ���õķ�Ƶϵ����amhw_zlg118_lptim_clkdiv_tö������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_clk_div_set (amhw_zlg118_lptim_t        *p_hw_lptim,
                                    amhw_zlg118_lptim_clk_div_t clkdiv)
{
    p_hw_lptim->cr = (p_hw_lptim->cr & (~(0x7ul << 11))) |
                     ((clkdiv & 0x7ul) << 11);
}

/**
 * \brief IE �жϽ���
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_int_disable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr &= ~(0x1ul << 10);
}

/**
 * \brief IE �ж�ʹ��
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_int_enable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr |= (0x1ul << 10);
}

/**
 * \brief GATEP �˿�GATE���Կ���   �ߵ�ƽ
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_gate_high (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr &= ~(0x1ul << 9);
}

/**
 * \brief GATEP �˿�GATE���Կ���   �͵�ƽ
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_gate_low (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr |= (0x1ul << 9);
}

/**
 * \brief GATE ��ʱ���ſؽ���
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_gate_disable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr &= ~(0x1ul << 8);
}

/**
 * \brief GATE ��ʱ���ſ�ʹ��
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_gate_enable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr |= (0x1ul << 8);
}

/**
 * \brief WT_FLAG     WT,дͬ����־
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_TRUE  : ͬ����ɣ��ɸ���ARR
 *         AM_FALSE : ����ͬ���� дARR��Ч
 */
am_static_inline
am_bool_t amhw_zlg118_lptim_write_into_arr_stat (amhw_zlg118_lptim_t *p_hw_lptim)
{
   return ((p_hw_lptim->cr >> 7) & 0x1ul) ? AM_TRUE : AM_FALSE;
}

typedef enum {
    AMHW_ZLG118_LPTIM_CLK_SRC_PCLK = 0ul,    /* LPTIMʱ��Ϊ  PCLK */
    AMHW_ZLG118_LPTIM_CLK_SRC_XTL  = 2ul,    /* LPTIMʱ��Ϊ  �ⲿ����ʱ�� */
    AMHW_ZLG118_LPTIM_CLK_SRC_RCL  = 3ul,    /* LPTIMʱ��Ϊ  �ڲ�����ʱ�� */
}amhw_zlg118_lptim_clk_src_t;

/**
 * \brief LPTIM ʱ��ѡ��
 *
 * \param[in] p_hw_lptim : ָ��LPTIM�Ĵ����ṹ���ָ��
 * \param[in] clk_src    : amhw_zlg118_lptim_clk_src_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_lptim_clk_src_sel (amhw_zlg118_lptim_t          *p_hw_lptim,
                                    amhw_zlg118_lptim_clk_src_t   clk_src)
{
    p_hw_lptim->cr = (p_hw_lptim->cr & (~(0x3ul << 4))) | (clk_src << 4);
}

/**
 * \brief LPTIM ʱ�ӻ�ȡ
 *
 * \param[in] p_hw_lptim : ָ��UALPTIMRT�Ĵ����ṹ���ָ��
 *
 * \return amhw_zlg118_lptim_clk_src_tö����
 */
am_static_inline
amhw_zlg118_lptim_clk_src_t
amhw_zlg118_lptim_clk_src_get (amhw_zlg118_lptim_t *p_hw_lptim)
{
    return (amhw_zlg118_lptim_clk_src_t)((p_hw_lptim->cr >> 4) & 0x3ul);
}

/**
 * \brief TOG �������            ͬʱ���0
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \note 0�� TOG,TOGN ͬʱ���0
 *       1�� TOG,TOGN �����λ�෴���źš��ɹ� buzzer ʹ�á�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_tog_disable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr &= ~(0x1ul << 3);
}

/**
 * \brief TOG ���ʹ��            �����λ�෴���ź�
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \note 0�� TOG,TOGN ͬʱ���0
 *       1�� TOG,TOGN �����λ�෴���źš��ɹ� buzzer ʹ�á�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_tog_enable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr |= (0x1ul << 3);
}

typedef enum {
    AMHW_ZLG118_LPTIM_FUNCTION_TIMER   = 0,    /* ��ʱ�� */
    AMHW_ZLG118_LPTIM_FUNCTION_COUNTER = 1,    /* ������ */
}amhw_zlg118_lptim_function_t;

/**
 * \brief ������/��ʱ������ѡ��
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_zlg118_lptim_function_tö����
 *
 * \note    ��ʱ��ʹ��TCK_SELѡ���ʱ�ӽ��м���
 *
 *          ������ʹ���ⲿ������½��ؽ��м���������ʱ��ʹ��TCK_SELѡ���ʱ�ӣ�
 *          �ⲿ����ʱ��Ҫ���� 1/2 ����ʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_function_sel (amhw_zlg118_lptim_t         *p_hw_lptim,
                                     amhw_zlg118_lptim_function_t type)
{
    p_hw_lptim->cr = (p_hw_lptim->cr & (~(0x1ul << 2))) |
                     ((type & 0x1ul) << 2);
}

typedef enum {
    AMHW_ZLG118_LPTIM_MODE_NORELOAD = 0,    /* ������ */
    AMHW_ZLG118_LPTIM_MODE_RELOAD   = 1,    /* �Զ���װ�� */
}amhw_zlg118_lptim_mode_t;

/**
 * \brief ��ʱ������ģʽѡ��
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_zlg118_lptim_mode_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_mode_sel (amhw_zlg118_lptim_t     *p_hw_lptim,
                                 amhw_zlg118_lptim_mode_t type)
{
    p_hw_lptim->cr = (p_hw_lptim->cr & (~(0x1ul << 1))) |
                     ((type & 0x1ul) << 1);
}

/**
 * \brief TR ��ʱ������
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_disable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr &= ~(0x1ul << 0);
}

/**
 * \brief TR ��ʱ��ʹ��
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_lptim_enable (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->cr |= (0x1ul << 0);
}

/**
 * \brief ��ȡ��־�Ƿ���Ч
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_TRUE  : ��־��Ч
 *         AM_FALSE : ��־��Ч
 */
am_static_inline
am_bool_t amhw_zlg118_lptim_int_flag_check (amhw_zlg118_lptim_t *p_hw_lptim)
{
    return (p_hw_lptim->ifr & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ��־���
 *
 * \param[in] p_hw_lptim : ָ��LPTIM��ʱ���Ĵ������ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_lptim_int_flag_clr (amhw_zlg118_lptim_t *p_hw_lptim)
{
    p_hw_lptim->iclr &= ~0x1ul;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_LPTIM_H */

/* end of file */
