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
 * \brief ��ʱ��TIM�ӿ�
 *
 * \internal
 * \par History
 * - 1.00 20-03-12  yrz, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZSN700_TIM_H
#define __AMHW_ZSN700_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zsn700_if_tim
 * \copydoc amhw_zsn700_tim.h
 * @{
 */

typedef struct ccrxx {
    __IO uint32_t a;          /**< \brief A */
    __IO uint32_t b;          /**< \brief B */
}ccrxx_t;                     /**< \brief �Ƚϲ���Ĵ���*/

/**
  * \brief ��ʱ���Ĵ�����ṹ��
  */
typedef struct amhw_zsn700_tim {
    __IO uint32_t arr;            /**< \brief Timer���ؼĴ���/���� */
    __IO uint32_t cnt;            /**< \brief Timer16λģʽ�����Ĵ��� */
    __IO uint32_t cnt32;          /**< \brief Timer32λģʽ�����Ĵ��� */

         union mxcr {
             __IO uint32_t m0cr;  /**< \brief Timerģʽ0���ƼĴ��� */
             __IO uint32_t m1cr;  /**< \brief Timerģʽ1���ƼĴ��� */
             __IO uint32_t m23cr; /**< \brief Timerģʽ23���ƼĴ��� */
         }mxcr_t;                 /**< \brief Timerģʽ0���ƼĴ���������ͬģʽ����������*/

    __IO uint32_t ifr;            /**< \brief Timer�жϱ�־ */
    __IO uint32_t iclr;           /**< \brief Timer�ж�����Ĵ��� */
    __IO uint32_t mscr;           /**< \brief ����ģʽ���� */
    __IO uint32_t fltr;           /**< \brief �˲����� */
    __IO uint32_t adtr;           /**< \brief ADC�������� */
    __IO uint32_t crchx[3];       /**< \brief �Ƚϵ�Ԫ0��1��2���ƼĴ��� */
    __IO uint32_t dtr;            /**< \brief �����Ĵ��� */
    __IO uint32_t rcr;            /**< \brief �ظ������Ĵ��� */
    __IO uint32_t arrdm;          /**< \brief Timer���ؼĴ���/����ӳ���ַ */
    ccrxx_t       ccrxx[3];       /**< \brief ͨ�� 0/1/2�Ƚϲ���Ĵ���*/

} amhw_zsn700_tim_t;

/**
 * \brief ��ʱ������
 */
typedef enum amhw_zsn700_tim_type {
    AMHW_ZSN700_TIM_TYPE_TIM0 = 0,  /**< \brief TIM0 */
    AMHW_ZSN700_TIM_TYPE_TIM1,      /**< \brief TIM1 */
    AMHW_ZSN700_TIM_TYPE_TIM2,      /**< \brief TIM2 */
    AMHW_ZSN700_TIM_TYPE_TIM3,      /**< \brief TIM3 */
} amhw_zsn700_tim_type_t;

/**
 * \brief �ſؿ�������
 */
typedef enum amhw_zsn700_tim_gate {
    AMHW_ZSN700_TIM_GATE_DISABLE = 0,
    AMHW_ZSN700_TIM_GATE_ENABLE,
} amhw_zsn700_tim_gate_t;

/*
 * ��ʱ��ͨ���Ŷ���
 *
 * ��ʱ��012ֻ��2��ͨ�����ֱ���CH0A��CH0B(�������ط���������Ϊͨ��0��1)
 * ��ʱ��3����6��ͨ�����ֱ���CH0A��CH0B��CH1A��CH1B��CH2A��CH2B
 *
 * CHxA��CHxB��ĳЩ�������Ϊһ���������ͨ��
 */
#define ZSN700_TIM_CH0A    0
#define ZSN700_TIM_CH0B    1
#define ZSN700_TIM_CH1A    2
#define ZSN700_TIM_CH1B    3
#define ZSN700_TIM_CH2A    4
#define ZSN700_TIM_CH2B    5

/**
 * \brief ARR-16λģʽ���ؼĴ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ARR���ؼĴ�����ֵ
 */
am_static_inline
uint16_t amhw_zsn700_tim_arr_count_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return p_hw_tim->arr;
}

/**
 * \brief ARR-16λģʽ���ؼĴ���       ���õ�ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : ���õļ�������ֵ
 *
 *\ return ��
 */
am_static_inline
void amhw_zsn700_tim_arr_count_set (amhw_zsn700_tim_t *p_hw_tim, uint16_t value)
{
    p_hw_tim->arr = value;
}

/**
 * \brief CNT-16λģʽ�����Ĵ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return CNT�����Ĵ�����ֵ
 */
am_static_inline
uint16_t amhw_zsn700_tim_cnt16_count_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return p_hw_tim->cnt;
}

/**
 * \brief CNT-16λģʽ�����Ĵ���       ���õ�ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : ���õļ�������ֵ
 *
 *\ return ��
 */
am_static_inline
void amhw_zsn700_tim_cnt16_count_set (amhw_zsn700_tim_t *p_hw_tim, uint16_t value)
{
    p_hw_tim->cnt = value;
}

/**
 * \brief CNT32-32λģʽ�����Ĵ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ����ģʽ0 32λ��ʱ�����ɼ���ģʽ����Ч������ģʽ��ֹд�üĴ���
 *
 * \return CNT32�����Ĵ�����ֵ
 */
am_static_inline
uint32_t amhw_zsn700_tim_cnt32_count_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return p_hw_tim->cnt32;
}

/**
 * \brief CNT32-32λģʽ�����Ĵ���       ���õ�ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : ���õļ�������ֵ
 *
 * \note ����ģʽ0 32λ��ʱ�����ɼ���ģʽ����Ч������ģʽ��ֹд�üĴ���
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_cnt32_count_set (amhw_zsn700_tim_t *p_hw_tim, uint32_t value)
{
    p_hw_tim->cnt32 = value;
}

/**
 * \brief ��ʱ��ģʽö��
 */
typedef enum {
    AMHW_ZSN700_TIM_MODE_TIMING = 0,        /* ��ʱ��ģʽ */
    AMHW_ZSN700_TIM_MODE_PWC,               /* PWCģʽ */
    AMHW_ZSN700_TIM_MODE_ZIGZAG,            /* ��ݲ�ģʽ */
    AMHW_ZSN700_TIM_MODE_TRIANGULAR,        /* ���ǲ�ģʽ */
}amhw_zsn700_tim_mode_t;

/**
 * \brief MODE ����ģʽ  ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ���õĹ���ģʽ��amhw_zsn700_tim_mode_tö������
 */
am_static_inline
amhw_zsn700_tim_mode_t amhw_zsn700_tim_mode_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_mode_t)((p_hw_tim->mxcr_t.m0cr >> 12) & 0x3ul);
}

/**
 * \brief CMODE ����ģʽ  ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] mode     : ���õĹ���ģʽ��amhw_zsn700_tim_mode_tö������
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode_set (amhw_zsn700_tim_t     *p_hw_tim,
                               amhw_zsn700_tim_mode_t mode)
{
    p_hw_tim->mxcr_t.m0cr = (p_hw_tim->mxcr_t.m0cr & (~(0x3ul << 12))) |
                            ((mode & 0x3ul) << 12);
}

/**
 * \brief CTEN ��ʱ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_disable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr &= ~(0x1ul << 0);
}

/**
 * \brief CTEN ��ʱ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_enable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr |= (0x1ul << 0);
}

/**
 * \brief �ڲ�ʱ�ӷ�Ƶѡ��
 */
typedef enum {
    AMHW_ZSN700_TIM_CLK_DIV1 = 0,    /* 1��Ƶ */
    AMHW_ZSN700_TIM_CLK_DIV2,        /* 2��Ƶ */
    AMHW_ZSN700_TIM_CLK_DIV4,        /* 4��Ƶ */
    AMHW_ZSN700_TIM_CLK_DIV8,        /* 8��Ƶ */
    AMHW_ZSN700_TIM_CLK_DIV16,       /* 16��Ƶ */
    AMHW_ZSN700_TIM_CLK_DIV32,       /* 32��Ƶ */
    AMHW_ZSN700_TIM_CLK_DIV64,       /* 64��Ƶ */
    AMHW_ZSN700_TIM_CLK_DIV256,      /* 256��Ƶ */
}amhw_zsn700_tim_clkdiv_t;

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ���õķ�Ƶϵ����amhw_zsn700_tim_clkdiv_tö������
 */
am_static_inline
amhw_zsn700_tim_clkdiv_t
    amhw_zsn700_tim_mode_clkdiv_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_clkdiv_t)((p_hw_tim->mxcr_t.m0cr >> 4) & 0x7ul);
}

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] clkdiv   : ���õķ�Ƶϵ����amhw_zsn700_tim_clkdiv_tö������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode_clkdiv_set (amhw_zsn700_tim_t       *p_hw_tim,
                                      amhw_zsn700_tim_clkdiv_t clkdiv)
{
    p_hw_tim->mxcr_t.m0cr = (p_hw_tim->mxcr_t.m0cr & (~(0x7ul << 4))) |
                            ((clkdiv & 0x7ul) << 4);
}

/**
 * \brief ����ʱ��ѡ��
 */
typedef enum {
    AMHW_ZSN700_TIM_CLK_SRC_TCLK = 0,   /* �ڲ�����ʱ��TCLK */
    AMHW_ZSN700_TIM_CLK_SRC_ETR,        /* �ⲿ����ʱ��ETR */
}amhw_zsn700_tim_clk_src_t;
/**
 * \brief CT ����ʱ��ѡ��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ���õ�ʱ��Դ��amhw_zsn700_tim_clk_src_tö������
 */
am_static_inline
amhw_zsn700_tim_clk_src_t
    amhw_zsn700_tim_mode_clk_src_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_clk_src_t)((p_hw_tim->mxcr_t.m0cr >> 2) & 0x1ul);
}

/**
 * \brief CT ����ʱ��ѡ��   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] src      : ���õ�ʱ��Դ��amhw_zsn700_tim_clk_src_tö������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode_clk_src_set(amhw_zsn700_tim_t        *p_hw_tim,
                                      amhw_zsn700_tim_clk_src_t src)
{
    p_hw_tim->mxcr_t.m0cr = (p_hw_tim->mxcr_t.m0cr & (~(0x1ul << 2))) |
                            ((src & 0x1ul) << 2);
}

/******************************************************************************/
/***************************Timerģʽ0���ƼĴ���     ��ؿ��ƺ���**************************/
/******************************************************************************/

/**
 * \brief UIE �жϽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_int_update_disable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr &= ~(0x1ul << 10);
}

/**
 * \brief UIE �ж�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_int_update_enable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr |= (0x1ul << 10);
}

/**
 * \brief GATEP �˿�GATE���Կ���   �ߵ�ƽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_gate_high (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr &= ~(0x1ul << 9);
}

/**
 * \brief GATEP �˿�GATE���Կ���   �͵�ƽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_gate_low (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr |= (0x1ul << 9);
}

/**
 * \brief GATE ��ʱ���ſؽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_gate_disable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr &= ~(0x1ul << 8);
}

/**
 * \brief GATE ��ʱ���ſ�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_gate_enable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr |= (0x1ul << 8);
}

/**
 * \brief TOGEN ģʽ0�·�ת�������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 1����ת���ʹ��
 *       0����ת����ر�CHA,CHB���Ϊ�͵�ƽ
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_toggle_disable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr &= ~(0x1ul << 3);
}

/**
 * \brief TOGEN ģʽ0�·�ת���ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 1����ת���ʹ��
 *       0����ת����ر�CHA,CHB���Ϊ�͵�ƽ
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_toggle_enable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m0cr |= (0x1ul << 3);
}

/**
 * \brief ģʽѡ��32��ʱ/16��ʱģʽѡ��
 *
 * \note 32λ���ɼ���  �� 0 - 0xffffffff������Χ�����ϼ�����������ģʽ0�У������趨����ֵ��
 *       16λ���ؼ���  �� �����趨ֵ - 0xffff ������Χ�����趨����ֵ��
 *
 *       ע�⣺���ʹ��32λ���ɼ������������ڹ̶�Ϊ 0 - 0xffffffff �� ���ɸ��ġ�
 *
 */
typedef enum {
    AMHW_ZSN700_TIM_MODE0_COUNTER_32 = 0,   /* 32λ���ɼ���  */
    AMHW_ZSN700_TIM_MODE0_COUNTER_16,       /* 16λ���ؼ��� */
}amhw_zsn700_tim_mode0_counter_t;
/**
 * \brief MD ģʽѡ��32��ʱ/16��ʱģʽѡ��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ���õ�32��ʱ/16��ʱģʽ��amhw_zsn700_tim_mode0_counter_tö������
 */
am_static_inline
amhw_zsn700_tim_mode0_counter_t amhw_zsn700_tim_mode0_counter_get (amhw_zsn700_tim_t  *p_hw_tim)
{
    return (amhw_zsn700_tim_mode0_counter_t)((p_hw_tim->mxcr_t.m0cr >> 1) & 0x1ul);
}

/**
 * \brief MD ģʽѡ��32��ʱ/16��ʱģʽѡ��   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] src      : ���õ�32��ʱ/16��ʱģʽ��amhw_zsn700_tim_mode0_counter_tö������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_counter_set(amhw_zsn700_tim_t              *p_hw_tim,
                                       amhw_zsn700_tim_mode0_counter_t src)
{
    p_hw_tim->mxcr_t.m0cr = (p_hw_tim->mxcr_t.m0cr & (~(0x1ul << 1))) |
                            ((src & 0x1ul) << 1);
}

/**
 * \brief UIF ����ж� ��־��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return AM_TRUE  �� ��־��Ч
 *         AM_FALSE �� ��־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode0_int_update_flag_check(amhw_zsn700_tim_t *p_hw_tim)
{
    return (p_hw_tim->ifr & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief UIF ����ж� ��־���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_int_update_flag_clr(amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->iclr &= ~(0x1ul << 0);
}

/**
 * \brief MOE ��ת���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0����ת�˿�Ϊ����״̬
 *       1����ת�˿�Ϊ���״̬
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_toggle_output (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->dtr |= (0x1ul << 12);
}

/**
 * \brief MOE ��ת����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0����ת�˿�Ϊ����״̬
 *       1����ת�˿�Ϊ���״̬
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode0_toggle_input (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->dtr |= (0x1ul << 12);
}


/******************************************************************************/
/***************************Timerģʽ1���ƼĴ���     ��ؿ��ƺ���**************************/
/******************************************************************************/
/**
 * \brief Oneshot ���δ���ģʽѡ��   ���δ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 1�����һ����������Զ������� �ٴβ�����Ҫ����ʹ��CTEN
 *       0��ѭ������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_trigger_single (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m1cr |= (0x1ul << 14);
}

/**
 * \brief Oneshot ���δ���ģʽѡ��  ѭ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 1�����һ����������Զ������� �ٴβ�����Ҫ����ʹ��CTEN
 *       0��ѭ������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_trigger_cyclic (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m1cr &= ~(0x1ul << 14);
}

/**
 * \brief UIE ����жϽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_int_update_disable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m1cr &= ~(0x1ul << 10);
}

/**
 * \brief UIE ����ж�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_int_update_enable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m1cr |= (0x1ul << 10);
}

/**
 * \brief CIEA �����Ȳ�������жϽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_int_edge_finish_disable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->crchx[0] &= ~(0x1ul << 10);
}

/**
 * \brief CIEA �����Ȳ�������ж�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_int_edge_finish_enable (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->crchx[0] |= (0x1ul << 10);
}

/**
 * \brief �����Ȳ�������ѡ��
 */
typedef enum {
    AMHW_ZSN700_TIM_PULSE_CYCLE_RISING,    /* ����-�������� */
    AMHW_ZSN700_TIM_PULSE_WIDTH_LOW,       /* �͵�ƽ��� */
    AMHW_ZSN700_TIM_PULSE_WIDTH_HIGH,      /* �ߵ�ƽ��� */
    AMHW_ZSN700_TIM_PULSE_CYCLE_FALLING,   /* ����-�������� */
}amhw_zsn700_tim_measure_edge_t;
/**
 * \brief Edg2nd Edg1st �����Ȳ�������ѡ��  ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return �����Ȳ�������ѡ��(amhw_zsn700_tim_measure_edge_tö����)
 */
am_static_inline
amhw_zsn700_tim_measure_edge_t
    amhw_zsn700_tim_mode1_measure_edge_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_measure_edge_t)((p_hw_tim->mxcr_t.m1cr >> 8) & 0x3ul);
}

/**
 * \brief Edg2nd Edg1st �����Ȳ�������ѡ��  ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : �����Ȳ�������ѡ��(amhw_zsn700_tim_measure_edge_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_measure_edge_set(
    amhw_zsn700_tim_t             *p_hw_tim,
    amhw_zsn700_tim_measure_edge_t choice)
{
    p_hw_tim->mxcr_t.m1cr =(p_hw_tim->mxcr_t.m1cr & (~(0x3ul << 8))) |
                           ((choice & 0x3ul) << 8);
}

/**
 * \brief UIF ����ж� ��־��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return AM_TRUE  �� ��־��Ч
 *         AM_FALSE �� ��־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode1_int_update_flag_check(
    amhw_zsn700_tim_t *p_hw_tim)
{
    return (p_hw_tim->ifr & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief UIF ����ж� ��־���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_int_update_flag_clr(amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->iclr &= ~(0x1ul << 0);
}

/**
 * \brief UIF �����Ȳ����ж�   ��־��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return AM_TRUE  �� ��־��Ч
 *         AM_FALSE �� ��־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode1_int_edge_flag_check(amhw_zsn700_tim_t *p_hw_tim)
{
    return ((p_hw_tim->ifr >> 2) & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief UIF �����Ȳ����ж�   ��־���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_int_edge_flag_clr (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->iclr &= ~(0x1ul << 2);
}

/**
 * \brief CCR0A �����Ȳ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return  �����Ȳ������
 */
am_static_inline
uint16_t amhw_zsn700_tim_mode1_measure_data_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (p_hw_tim->ccrxx[0].a & 0xfffful);
}

/**
 * \brief IB0S CH0B����ѡ��      CH0B
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0B
 *       1���ڲ�����TSѡ���ź�
 *
 * \note ��PWM�������ʱ�Զ�ѡ��GATE�˿���ΪCH0B������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_ch0b_in_ch0b (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr &= ~(0x1ul << 12);
}

/**
 * \brief IB0S CH0B����ѡ��     �ڲ�����TSѡ���ź�
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0B
 *       1���ڲ�����TSѡ���ź�
 *
 * \note ��PWM�������ʱ�Զ�ѡ��GATE�˿���ΪCH0B������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_ch0b_in_ts (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr |= (0x1ul << 12);
}

/**
 * \brief IA0S  CH0A����ѡ��      CH0A
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0A
 *       1��CH0A CH1A CH2A XOR(TIM3)    ��          CH0A ETR GATE XOR(TIM0)
 *
 * \note ����Ϊ1��˿ڵ�����һ���˿ڱ仯����������仯
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_ch0a_in_ch0a (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr &= ~(0x1ul << 11);
}

/**
 * \brief IA0S  CH0A����ѡ��     �ڲ�����TSѡ���ź�
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0A
 *       1��CH0A CH1A CH2A XOR(TIM3)    ��          CH0A ETR GATE XOR(TIM0)
 *
 * \note ����Ϊ1��˿ڵ�����һ���˿ڱ仯����������仯
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_ch0a_in_other (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr |= (0x1ul << 11);
}

/**
 * \brief ����ѡ��
 */
typedef enum {
    AMHW_ZSN700_TIM_TS_SRC_ETR_ETFP = 0,    /* �˿�ETR���˲���λѡ�����ź�ETFP */
    AMHW_ZSN700_TIM_TS_SRC_ITR0,            /* �ڲ������ź� ITR0 */
    AMHW_ZSN700_TIM_TS_SRC_ITR1,            /* �ڲ������ź� ITR1 */
    AMHW_ZSN700_TIM_TS_SRC_ITR2,            /* �ڲ������ź� ITR2 */
    AMHW_ZSN700_TIM_TS_SRC_ITR3,            /* �ڲ������ź� ITR3 */
    AMHW_ZSN700_TIM_TS_SRC_CH0A_EDGE,       /* �˿�CH0A�ı����ź� */
    AMHW_ZSN700_TIM_TS_SRC_CH0A_IAFP,       /* �˿�CH0A���˲���λѡ�����ź�IAFP */
    AMHW_ZSN700_TIM_TS_SRC_CH0B_IBFP,       /* �˿�CH0B���˲���λѡ�����ź�IBFP */
}amhw_zsn700_tim_ts_src_t;
/**
 * \brief TS ����ѡ��  ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ����ѡ��(amhw_zsn700_tim_ts_src_tö����)
 */
am_static_inline
amhw_zsn700_tim_ts_src_t
    amhw_zsn700_tim_mode1_ts_src_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_ts_src_t)((p_hw_tim->mscr >> 5) & 0x7ul);
}

/**
 * \brief TS ����ѡ��  ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : ����ѡ��(amhw_zsn700_tim_ts_src_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_ts_src_set(amhw_zsn700_tim_t       *p_hw_tim,
                                      amhw_zsn700_tim_ts_src_t choice)
{
    p_hw_tim->mscr =(p_hw_tim->mscr & (~(0x7ul << 5))) |
                    ((choice & 0x7ul) << 5);
}

/**
 * \brief ETP  ETR������λѡ��      ͬ��λ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_etr_in_phase_same (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->fltr &= ~(0x1ul << 31);
}

/**
 * \brief ETP  ETR������λѡ��         ��������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_etr_in_phase_reversed (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->fltr |= (0x1ul << 31);
}

/**
 * \brief �˲����ƣ�����
 */
typedef enum {
    AMHW_ZSN700_TIM_FILTER_NO = 0,          /* �˲���Ч */
    AMHW_ZSN700_TIM_FILTER_PCLKDIV1_3 = 4,  /* pclk 3��������Ч */
    AMHW_ZSN700_TIM_FILTER_PCLKDIV4_3,      /* pclk/4 3��������Ч */
    AMHW_ZSN700_TIM_FILTER_PCLKDIV16_3,     /* pclk/16 3��������Ч */
    AMHW_ZSN700_TIM_FILTER_PCLKDIV64_3,     /* pclk/64 3��������Ч */
}amhw_zsn700_tim_filter_t;

/**
 * \brief FLTET  ETR�˲�����    ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return �˲�����(amhw_zsn700_tim_filter_tö����)
 */
am_static_inline
amhw_zsn700_tim_filter_t
    amhw_zsn700_tim_mode1_etr_fliter_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_filter_t)(amhw_zsn700_tim_filter_t)((p_hw_tim->fltr >> 28) & 0x7ul);
}

/**
 * \brief FLTET  ETR�˲�����     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : �˲�����(amhw_zsn700_tim_filter_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_etr_fliter_set(amhw_zsn700_tim_t       *p_hw_tim,
                                          amhw_zsn700_tim_filter_t choice)
{
    p_hw_tim->fltr =(p_hw_tim->fltr & (~(0x7ul << 28))) |
                    ((choice & 0x7ul) << 28);
}

/**
 * \brief FLTB0  CHB�˲�����    ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return �˲�����(amhw_zsn700_tim_filter_tö����)
 */
am_static_inline
amhw_zsn700_tim_filter_t
    amhw_zsn700_tim_mode1_chb_fliter_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_filter_t)((p_hw_tim->fltr >> 4) & 0x7ul);
}

/**
 * \brief FLTB0  CHB�˲�����     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : �˲�����(amhw_zsn700_tim_filter_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_chb_fliter_set(amhw_zsn700_tim_t       *p_hw_tim,
                                          amhw_zsn700_tim_filter_t choice)
{
    p_hw_tim->fltr =(p_hw_tim->fltr & (~(0x7ul << 4))) |
                    ((choice & 0x7ul) << 4);
}

/**
 * \brief FLTA0  CHA�˲�����    ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return �˲�����(amhw_zsn700_tim_filter_tö����)
 */
am_static_inline
amhw_zsn700_tim_filter_t
    amhw_zsn700_tim_mode1_cha_fliter_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_filter_t)((p_hw_tim->fltr >> 0) & 0x7ul);
}

/**
 * \brief FLTA0  CHA�˲�����    ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : �˲�����(amhw_zsn700_tim_filter_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode1_cha_fliter_set(amhw_zsn700_tim_t       *p_hw_tim,
                                          amhw_zsn700_tim_filter_t choice)
{
    p_hw_tim->fltr =(p_hw_tim->fltr & (~(0x7ul << 0))) |
                    ((choice & 0x7ul) << 0);
}




/******************************************************************************/
/***************************Timerģʽ23���ƼĴ���     ��ؿ��ƺ���*************************/
/******************************************************************************/
/**
 * \brief DIR  ���ϼ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��������ֻ���ھ�ݲ�ģʽ�¿���д������ģʽ��ֻ����д��Ч.
 *       ������ģʽ�л������Ķ���ģʽDIR�Զ���0������¼����ºʹ�ģʽ�ⲿ������λģʽDIR�Զ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_counter_up (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr &= ~(0x1ul << 27);
}

/**
 * \brief DIR  ���¼���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��������ֻ���ھ�ݲ�ģʽ�¿���д������ģʽ��ֻ����д��Ч.
 *       ������ģʽ�л������Ķ���ģʽDIR�Զ���0������¼����ºʹ�ģʽ�ⲿ������λģʽDIR�Զ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_counter_down (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1ul << 27);
}

/**
 * \brief BG  ���ɲ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note �Զ����㣬д0��Ч
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_soft_brake (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1ul << 26);
}

/**
 * \brief UG  �������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note �Զ����㣬д0��Ч
 *       ��ʼ�������������»���Ĵ�������Ӧ�Ĵ���������ʹ�ܣ���Ԥ��Ƶ������Ҳ�ᱻ����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_soft_update (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1ul << 25);
}

/**
 * \brief TG  �������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note �Զ����㣬д0��Ч
 *       ��Ҫ�ڴ���ģʽSMS=2��mode=2/3�¶����Դ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_soft_trigger (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1ul << 24);
}

/**
 * \brief ���Ķ���A�Ƚ��ж�ģʽ
 */
typedef enum {
    AMHW_ZSN700_TIM_CISA_INT_MODE_NO = 0,  /* ���ж� */
    AMHW_ZSN700_TIM_CISA_INT_MODE_RISING,  /* �����ж� */
    AMHW_ZSN700_TIM_CISA_INT_MODE_FALLING, /* �����ж� */
    AMHW_ZSN700_TIM_CISA_INT_MODE_BOTH,    /* �����ض��ж� */
}amhw_zsn700_tim_int_mode_t;

/**
 * \brief CIS ���Ķ���A�Ƚ��ж�ģʽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] mode     : amhw_zsn700_tim_int_mode_tö����
 *
 * \note ���Ķ���A�Ƚ��ж�ģʽ(B�Ƚ��жϵ���������CRx�Ĵ�����CISB)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_int_mode_set(amhw_zsn700_tim_t         *p_hw_tim,
                                         amhw_zsn700_tim_int_mode_t mode )
{
    p_hw_tim->mxcr_t.m23cr = (p_hw_tim->mxcr_t.m23cr & (~(0x3ul << 21))) |
                             ((mode & 0x3ul) << 21);
}

#define AMHW_ZSN700_TIM_INT_BIE     (0x1UL << 20)  /* ɲ���ж�ʹ�� */
#define AMHW_ZSN700_TIM_INT_TIE     (0x1UL << 19)  /* �����ж�ʹ�� */
#define AMHW_ZSN700_TIM_INT_UIE     (0x1UL << 10)  /* �����ж�ʹ�� */
#define AMHW_ZSN700_TIM_INT_ALL     0xFF           /* �����ж� */

/**
 * \brief �����궨��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_INT_BIE   ��
 *                       AMHW_ZSN700_TIM_INT_TIE   ��
 *                       AMHW_ZSN700_TIM_INT_UIE   ��
 *                       AMHW_ZSN700_TIM_INT_ALL
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_int_enable (amhw_zsn700_tim_t *p_hw_tim,
                                        uint32_t           type)
{
    if(0xFF == type) {
        p_hw_tim->mxcr_t.m23cr |= AMHW_ZSN700_TIM_INT_BIE;
        p_hw_tim->mxcr_t.m23cr |= AMHW_ZSN700_TIM_INT_TIE;
        p_hw_tim->mxcr_t.m23cr |= AMHW_ZSN700_TIM_INT_UIE;
    }
    else {
        p_hw_tim->mxcr_t.m23cr |= type;
    }
}

/**
 * \brief �����궨�����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_INT_BIE   ��
 *                       AMHW_ZSN700_TIM_INT_TIE   ��
 *                       AMHW_ZSN700_TIM_INT_UIE   ��
 *                       AMHW_ZSN700_TIM_INT_ALL
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_int_disable (amhw_zsn700_tim_t  *p_hw_tim,
                                     uint32_t           type)
{
    if(0xFF == type) {
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_INT_BIE;
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_INT_TIE;
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_INT_UIE;
    }
    else {
        p_hw_tim->mxcr_t.m23cr &= ~type;
    }
}

#define AMHW_ZSN700_TIM_OCCE    (0x1UL << 23)  /* OCREF���ʹ��ʹ�� */
#define AMHW_ZSN700_TIM_TDE     (0x1UL << 18)  /* ����DMAʹ�� */
#define AMHW_ZSN700_TIM_UDE     (0x1UL << 11)  /* ����DMAʹ�� */
#define AMHW_ZSN700_TIM_BUFPEN  (0x1UL << 7)   /* ���ػ���ʹ�� */
#define AMHW_ZSN700_TIM_PWM2S   (0x1UL << 3)   /* OCREFA����Ƚ�ʹ�� */
#define AMHW_ZSN700_TIM_COMP    (0x1UL << 1)   /* ����PWMʹ�� */
#define AMHW_ZSN700_TIM_ALL     0XFF           /* ����ʹ�ܣ���ʱ��ʹ�ܳ��⣩*/

/**
 * \brief �����궨��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_OCCE  ��
 *                       AMHW_ZSN700_TIM_TDE   ��
 *                       AMHW_ZSN700_TIM_UDE   ��
 *                       AMHW_ZSN700_TIM_BUFPEN   ��
 *                       AMHW_ZSN700_TIM_PWM2S   ��
 *                       AMHW_ZSN700_TIM_COMP   ��
 *                       AMHW_ZSN700_TIM_ALL
 *
 *
 * \note 1�� OCREF_CLR�źſ������OCREF���
 *       0�� OCREF�������OCREF_CLRӰ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_enable (amhw_zsn700_tim_t *p_hw_tim,
                                    uint32_t           type)
{
    if(0xFF == type) {
        p_hw_tim->mxcr_t.m23cr |= AMHW_ZSN700_TIM_OCCE;
        p_hw_tim->mxcr_t.m23cr |= AMHW_ZSN700_TIM_TDE;
        p_hw_tim->mxcr_t.m23cr |= AMHW_ZSN700_TIM_UDE;
    }
    else {
        p_hw_tim->mxcr_t.m23cr |= type;
    }
}

/**
 * \brief �����궨�����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_OCCE  ��
 *                       AMHW_ZSN700_TIM_TDE   ��
 *                       AMHW_ZSN700_TIM_UDE   ��
 *                       AMHW_ZSN700_TIM_BUFPEN   ��
 *                       AMHW_ZSN700_TIM_PWM2S   ��
 *                       AMHW_ZSN700_TIM_COMP   ��
 *                       AMHW_ZSN700_TIM_ALL
 *
 * \note 1�� OCREF_CLR�źſ������OCREF���
 *       0�� OCREF�������OCREF_CLRӰ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_disable (amhw_zsn700_tim_t  *p_hw_tim,
                                     uint32_t           type)
{
    if(0xFF == type) {
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_OCCE;
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_TDE;
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_UDE;
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_BUFPEN;
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_PWM2S;
        p_hw_tim->mxcr_t.m23cr &= ~AMHW_ZSN700_TIM_COMP;
    }
    else {
        p_hw_tim->mxcr_t.m23cr &= ~type;
    }
}

/**
 * \brief URS ����Դ    0
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0�������/�����/�������UG/��ģʽ��λ
 *       1�������/�����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_uodate_src_0 (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr &= ~(0x1UL << 17);
}

/**
 * \brief URS ����Դ    1
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0�������/�����/�������UG/��ģʽ��λ
 *       1�������/�����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_uodate_src_1 (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1UL << 17);
}

/**
 * \brief OCCS  OCREF���Դѡ��    0
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0����ѹ�Ƚ���VC����� VCѡ����VCx_OUTCFG�Ĵ�������
 *       1��ETR�˿��˲���λѡ�����ź�
 *
 *       ��OCCE��Чʱ�� OC_clr�������OCREF�ıȽ�����ź�Ϊ�㣬����OCMx>1ʱ��Ч�� ��
 *       ��һ��uev�¼�������Ƚ����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_occref_src_0 (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr &= ~(0x1UL << 16);
}

/**
 * \brief OCCS  OCREF���Դѡ��    1
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0�������/�����/�������UG/��ģʽ��λ
 *       1�������/�����
 *
 *       ��OCCE��Чʱ�� OC_clr�������OCREF�ıȽ�����ź�Ϊ�㣬����OCMx>1ʱ��Ч�� ��
 *       ��һ��uev�¼�������Ƚ����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_occref_src_1 (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1UL << 16);
}

/**
 * \brief CSG  GATE ��PWM����ģʽ�²���/�Ƚ�ѡ��     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч,ʹ��CCR0B��ΪGATE�ıȽϻ򲶻�ͨ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_gate_set_cap (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1UL << 15);
}

/**
 * \brief CSG  GATE ��PWM����ģʽ�²���/�Ƚ�ѡ��     �Ƚ�
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч,ʹ��CCR0B��ΪGATE�ıȽϻ򲶻�ͨ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_gate_set_cmp (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr &= ~(0x1UL << 15);
}

/**
 * \brief CFG  GATE��Ϊ��������ʱ�� ���ز�����Ч����     ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч
 *
 * \return AM_TRUE :���ز�����Ч
 *         AM_FALSE:���ز�����Ч
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode23_cfg_get (amhw_zsn700_tim_t  *p_hw_tim)
{
    return ((p_hw_tim->mxcr_t.m23cr >> 9) & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief CFG  GATE��Ϊ��������ʱ�� ���ز�����Ч����     ��Ч
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cfg_enable (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1UL << 9);
}

/**
 * \brief CFG  GATE��Ϊ��������ʱ�� ���ز�����Ч����    ��Ч
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cfg_disable (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr &= ~(0x1UL << 9);
}

/**
 * \brief CFG  GATE��Ϊ��������ʱ�� ���ز�����Ч����     ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч
 *
 * \return AM_TRUE :���ز�����Ч
 *         AM_FALSE:���ز�����Ч
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode23_crg_get (amhw_zsn700_tim_t  *p_hw_tim)
{
    return ((p_hw_tim->mxcr_t.m23cr >> 8) & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief CFG  GATE��Ϊ��������ʱ�� ���ز�����Ч����     ��Ч
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_crg_enable (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1UL << 8);
}

/**
 * \brief CFG  GATE��Ϊ��������ʱ�� ���ز�����Ч����    ��Ч
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ֻ����PWM�������ʱ��Ч
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_crg_disable (amhw_zsn700_tim_t  *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr &= ~(0x1UL << 8);
}

/**
 * \brief Oneshot ���δ���ģʽѡ��   ���δ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 1�������¼����º�ʱ��ֹͣ��
 *       0��ѭ������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_trigger_single (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr |= (0x1ul << 14);
}

/**
 * \brief Oneshot ���δ���ģʽѡ��  ѭ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 1�������¼����º�ʱ��ֹͣ��
 *       0��ѭ������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_trigger_cyclic (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mxcr_t.m23cr &= ~(0x1ul << 14);
}


#define AMHW_ZSN700_TIM_INT_FLAG_TRIGGER   15    /* �����жϱ�־ */
#define AMHW_ZSN700_TIM_INT_FLAG_BRAKE     14    /* ɲ���жϱ�־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CB2E      13    /* ͨ��CB2E�������ݶ�ʧ��־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CB1E      12    /* ͨ��CB1E�������ݶ�ʧ��־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CB0E      11    /* ͨ��CB0E�������ݶ�ʧ��־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CA2E      10    /* ͨ��CA2E�������ݶ�ʧ��־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CA1E      9     /* ͨ��CA1E�������ݶ�ʧ��־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CA0E      8     /* ͨ��CA0E�������ݶ�ʧ��־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CB2F      7     /* ͨ��CH2B��������/�Ƚ�ƥ���־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CB1F      6     /* ͨ��CH1B��������/�Ƚ�ƥ���־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CB0F      5     /* ͨ��CH0B��������/�Ƚ�ƥ���־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CA2F      4     /* ͨ��CH2A��������/�Ƚ�ƥ���־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CA1F      3     /* ͨ��CH1A��������/�Ƚ�ƥ���־ */
#define AMHW_ZSN700_TIM_INT_FLAG_CA0F      2     /* ͨ��CH0A��������/�Ƚ�ƥ���־ */
#define AMHW_ZSN700_TIM_INT_FLAG_UPDATE    0     /* �¼������жϱ�־ */
#define AMHW_ZSN700_TIM_INT_FLAG_ALL     0xffff
/**
 * \brief ģʽ23��  ��־��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] flag     : �����Ӧ�궨��
 *                       AMHW_ZSN700_TIM_INT_FLAG_TRIGGER
 *                       .
 *                       .
 *                       .
 *                       AMHW_ZSN700_TIM_INT_FLAG_UPDATE
 *
 * \return AM_TRUE  �� ��־��Ч
 *         AM_FALSE �� ��־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode23_int_flag_check(amhw_zsn700_tim_t *p_hw_tim,
                                                uint32_t           flag)
{
    return (p_hw_tim->ifr  & (0x1ul << flag)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ģʽ23��   ��־���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] flag     : �����Ӧ�궨��
 *                       AMHW_ZSN700_TIM_INT_FLAG_TRIGGER
 *                       .
 *                       .
 *                       .
 *                       AMHW_ZSN700_TIM_INT_FLAG_UPDATE
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_int_flag_clr (amhw_zsn700_tim_t *p_hw_tim,
                                          uint32_t           flag)
{
    if(flag == 0xffff) {
        p_hw_tim->iclr = 0;
    } else {
        p_hw_tim->iclr &= ~(0x1ul << flag);
    }
}

/**
 * \brief IB0S CH0B����ѡ��      CH0B
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0B
 *       1���ڲ�����TSѡ���ź�
 *
 * \note ��PWM�������ʱ�Զ�ѡ��GATE�˿���ΪCH0B������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ch0b_in_ch0b (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr &= ~(0x1ul << 12);
}

/**
 * \brief IB0S CH0B����ѡ��     �ڲ�����TSѡ���ź�
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0B
 *       1���ڲ�����TSѡ���ź�
 *
 * \note ��PWM�������ʱ�Զ�ѡ��GATE�˿���ΪCH0B������
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ch0b_in_ts (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr |= (0x1ul << 12);
}

/**
 * \brief IA0S  CH0A����ѡ��      CH0A
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0A
 *       1��CH0A CH1A CH2A XOR(TIM3)    ��          CH0A ETR GATE XOR(TIM0)
 *
 * \note ����Ϊ1��˿ڵ�����һ���˿ڱ仯����������仯
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ch0a_in_ch0a (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr &= ~(0x1ul << 11);
}

/**
 * \brief IA0S  CH0A����ѡ��     �ڲ�����TSѡ���ź�
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note 0��CH0A
 *       1��CH0A CH1A CH2A XOR(TIM3)    ��          CH0A ETR GATE XOR(TIM0)
 *
 * \note ����Ϊ1��˿ڵ�����һ���˿ڱ仯����������仯
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ch0a_in_other (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr |= (0x1ul << 11);
}

/**
 * \brief ��ģʽ����ѡ��
 */
typedef enum {
    AMHW_ZSN700_TIM_SLAVER_MODE_INCLK = 0,  /* ʹ���ڲ�ʱ�� */
    AMHW_ZSN700_TIM_SLAVER_MODE_RESET,      /* ��λ���� */
    AMHW_ZSN700_TIM_SLAVER_MODE_TRIGGER,    /* ����ģʽ */
    AMHW_ZSN700_TIM_SLAVER_MODE_OUTCLK,     /* �ⲿʱ��ģʽ */
    AMHW_ZSN700_TIM_SLAVER_MODE_COUNTER1,   /* �����������ģʽ1 */
    AMHW_ZSN700_TIM_SLAVER_MODE_COUNTER2,   /* �����������ģʽ2 */
    AMHW_ZSN700_TIM_SLAVER_MODE_COUNTER3,   /* �����������ģʽ3 */
    AMHW_ZSN700_TIM_SLAVER_MODE_GATE,       /* �ſع��� */
}amhw_zsn700_tim_slaver_mode_t;

/**
 * \brief SMS ��ģʽ����ѡ��  ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��ģʽ����ѡ��(amhw_zsn700_tim_slaver_mode_tö����)
 */
am_static_inline
amhw_zsn700_tim_slaver_mode_t
    amhw_zsn700_tim_mode23_slaver_mode_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_slaver_mode_t)((p_hw_tim->mscr >> 8) & 0x7ul);
}

/**
 * \brief SMS ��ģʽ����ѡ��  ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : ��ģʽ����ѡ��(amhw_zsn700_tim_slaver_mode_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_slaver_mode_set(amhw_zsn700_tim_t         *p_hw_tim,
                                            amhw_zsn700_tim_slaver_mode_t choice)
{
    p_hw_tim->mscr =(p_hw_tim->mscr & (~(0x7ul << 8))) |
                    ((choice & 0x7ul) << 8);
}

/**
 * \brief TS ����ѡ��  ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ����ѡ��(amhw_zsn700_tim_ts_src_tö����)
 */
am_static_inline
amhw_zsn700_tim_ts_src_t
    amhw_zsn700_tim_mode23_ts_src_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_ts_src_t)((p_hw_tim->mscr >> 5) & 0x7ul);
}

/**
 * \brief TS ����ѡ�� ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : ����ѡ��(amhw_zsn700_tim_ts_src_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ts_src_set(amhw_zsn700_tim_t       *p_hw_tim,
                                      amhw_zsn700_tim_ts_src_t choice)
{
    p_hw_tim->mscr =(p_hw_tim->mscr & (~(0x7ul << 5))) |
                    ((choice & 0x7ul) << 5);
}

/**
 * \brief MSM ����ѡ��  ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note  0:����ʱ
 *        1:��ʱʹ�ܣ�ʹ���ͼ�����ͬʱ����
 *
 *        ʹ�ô���ģʽʱ����ģʽ����Ϊ0����ģʽ����Ϊ1������ʹ���Ӽ���ͬʱ����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_slaver_enable(amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr &= ~(0x1ul << 4);
}

/**
 * \brief MSM ����ѡ��  ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note  0:����ʱ
 *        1:��ʱʹ�ܣ�ʹ���ͼ�����ͬʱ����
 *
 *        ʹ�ô���ģʽʱ����ģʽ����Ϊ0����ģʽ����Ϊ1������ʹ���Ӽ���ͬʱ����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_master_enable(amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr |= (0x1ul << 4);
}

/**
 * \brief CCDS �Ƚ�ģʽ��DMA�Ƚϴ���ѡ��    �Ƚ�ƥ�䴥��DMA
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note  0 �� �Ƚ�ƥ�䴥��DMA
 *        1 �� �Ƚ�ƥ�䲻����DMA���¼����´���Ƚ�ƥ�䴥��DMA
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cmp_dma(amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr &= ~(0x1ul << 3);
}

/**
 * \brief CCDS �Ƚ�ģʽ��DMA�Ƚϴ���ѡ��   �Ƚ�ƥ�䲻����DMA���¼����´���Ƚ�ƥ�䴥��DMA
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note  0 �� �Ƚ�ƥ�䴥��DMA
 *        1 �� �Ƚ�ƥ�䲻����DMA���¼����´���Ƚ�ƥ�䴥��DMA
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cmp_update(amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->mscr |= (0x1ul << 3);
}

/**
 * \brief ��ģʽ���ѡ�������ڲ����������ӵ�������ʱ����ITRx
 */
typedef enum {
    AMHW_ZSN700_TIM_MASTER_OUT_UG = 0,    /* ������� */
    AMHW_ZSN700_TIM_MASTER_OUT_CTEN,      /* ��ʱ��ʹ�� */
    AMHW_ZSN700_TIM_MASTER_OUT_UEV,       /* ��ʱ���¼����� */
    AMHW_ZSN700_TIM_MASTER_OUT_CMPSO,     /* �Ƚ�ƥ��ѡ����� */
    AMHW_ZSN700_TIM_MASTER_OUT_OCREF0A,   /* �Ƚϲ������ */
    AMHW_ZSN700_TIM_MASTER_OUT_OCREF0B_1A,/* �Ƚϲ������(��ʱ��012Ϊ0B����ʱ��3Ϊ1A) */
    AMHW_ZSN700_TIM_MASTER_OUT_OCREF0B_2A,/* �Ƚϲ������(��ʱ��012Ϊ0B����ʱ��3Ϊ2A) */
    AMHW_ZSN700_TIM_MASTER_OUT_OCREF0B,   /* �Ƚϲ������ */
}amhw_zsn700_tim_master_out_t;
/**
 * \brief MMS ��ģʽ���ѡ�� ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��ģʽ���ѡ��(amhw_zsn700_tim_master_out_tö����)
 */
am_static_inline
amhw_zsn700_tim_master_out_t
    amhw_zsn700_tim_mode23_master_out_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return (amhw_zsn700_tim_master_out_t)((p_hw_tim->mscr >> 0) & 0x7ul);
}

/**
 * \brief MMS ��ģʽ���ѡ��  ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] choice   : ��ģʽ���ѡ��(amhw_zsn700_tim_master_out_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_master_out_set(amhw_zsn700_tim_t          *p_hw_tim,
                                           amhw_zsn700_tim_master_out_t choice)
{
    p_hw_tim->mscr =(p_hw_tim->mscr & (~(0x7ul << 0))) |
                    ((choice & 0x7ul) << 0);
}

/**
 * \brief ��λ��������ö�٣���Ӧ�ڼĴ����е���ʼλ��
 */
typedef enum {
    AMHW_ZSN700_TIM_PHASE_ETP   = 31,   /* ETR������λѡ�� */
    AMHW_ZSN700_TIM_PHASE_BKP   = 27,   /* ɲ��BK������λѡ�� */
    AMHW_ZSN700_TIM_PHASE_CCPB2 = 23,   /* �ȽϹ��ܣ�CH2Bͨ���Ƚ������λ���� */
    AMHW_ZSN700_TIM_PHASE_CCPA2 = 19,   /* �ȽϹ��ܣ�CH2Aͨ���Ƚ������λ���� */
    AMHW_ZSN700_TIM_PHASE_CCPB1 = 15,   /* �ȽϹ��ܣ�CH1Bͨ���Ƚ������λ���� */
    AMHW_ZSN700_TIM_PHASE_CCPA1 = 11,   /* �ȽϹ��ܣ�CH1Aͨ���Ƚ������λ���� */
    AMHW_ZSN700_TIM_PHASE_CCPB0 = 7,    /* �ÿ���λ�ڲ�ͬģʽ�¾��в�ͬ����
                                         * �ȽϹ��ܣ�����Ƚ�ģʽ
                                         *        CCPBx�Ƚ����CHBx�˿ڼ��Կ���
                                         *
                                         * ����������ģʽ�ſع��ܣ�������λ����
                                         *        CCPB0��ģʽ�ſأ���λ���ⲿ������
                                         *        �ⲿʱ��ʹ��CH0B�˿����뼫�Կ���
                                         */
    AMHW_ZSN700_TIM_PHASE_CCPA0 = 3,    /* �ÿ���λ�ڲ�ͬģʽ�¾��в�ͬ����
                                         * �ȽϹ��ܣ�����Ƚ�ģʽ
                                         *        CCPAx�Ƚ����CHAx�˿ڼ��Կ���
                                         *
                                         * ����������ģʽ�ſع��ܣ�������λ����
                                         *        CCPA0��ģʽ�ſأ���λ���ⲿ������
                                         *        �ⲿʱ��ʹ��CH0A�˿����뼫�Կ���
                                         */
}amhw_zsn700_tim_phase_type_t;

/**
 * \brief ͬ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : ��Ӧ�Ŀ�������(amhw_zsn700_tim_phase_type_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_phase_same (amhw_zsn700_tim_t           *p_hw_tim,
                                        amhw_zsn700_tim_phase_type_t type)
{
    p_hw_tim->fltr &= ~(0x1ul << type);
}

/**
 * \brief ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : ��Ӧ�Ŀ�������(amhw_zsn700_tim_phase_type_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_phase_reversed (amhw_zsn700_tim_t         *p_hw_tim,
                                            amhw_zsn700_tim_phase_type_t type)
{
    p_hw_tim->fltr |= (0x1ul << type);
}

/**
 * \brief �˲���������ö�٣���Ӧ�ڼĴ����е���ʼλ��
 */
typedef enum {
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTET = 28,   /* ETR�˲����� */
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTBK = 24,   /* ɲ�������˲����� */
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTB2 = 20,   /* CH2B����ͨ���˲����� */
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTA2 = 16,   /* CH2A����ͨ���˲����� */
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTB1 = 12,   /* CH1B����ͨ���˲����� */
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTA1 = 8,    /* CH1A����ͨ���˲����� */
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTB0 = 4,    /* CH0B����ͨ���˲����� */
    AMHW_ZSN700_TIM_FLITER_TYPE_FLTA0 = 0,    /* CH0A����ͨ���˲����� */
}amhw_zsn700_tim_filter_type_t;

/**
 * \brief �˲�����    ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : ��Ӧ�Ŀ�������(amhw_zsn700_tim_filter_type_tö����)
 *
 * \return �˲�����(amhw_zsn700_tim_filter_tö����)
 */
am_static_inline
amhw_zsn700_tim_filter_t
    amhw_zsn700_tim_mode23_fliter_get (amhw_zsn700_tim_t            *p_hw_tim,
                                       amhw_zsn700_tim_filter_type_t type)
{
    return (amhw_zsn700_tim_filter_t)((p_hw_tim->fltr >> type) & 0x7ul);
}

/**
 * \brief �˲�����     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : ��Ӧ�Ŀ�������(amhw_zsn700_tim_filter_type_tö����)
 * \param[in] choice   : �˲�����(amhw_zsn700_tim_filter_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_fliter_set(amhw_zsn700_tim_t            *p_hw_tim,
                                       amhw_zsn700_tim_filter_type_t type,
                                       amhw_zsn700_tim_filter_t      choice)
{
    p_hw_tim->fltr =(p_hw_tim->fltr & (~(0x7ul << type))) |
                    ((choice & 0x7ul) << type);
}

/**
 * \brief �ȽϿ���(�Ƚ�)
 *
 * \note PWMģʽ1
 *            ����Ƚϣ�
 *                   �ϼ���ʱCNT<CCRxy����ߣ��¼���ʱCNT>CCRxy���Ϊ�͵�ƽ
 *            ˫��Ƚϣ�
 *                   1�� ��ݲ��ϼ��� CCRxA<CNT��CCRxB���Ϊ�͵�ƽ
 *                   2�� ��ݲ��¼��� CCRxA<CNT��CCRxB���Ϊ�ߵ�ƽ
 *                   3�� ���ǲ��ϼ���CNT<CCRxA����ߣ��¼���CNT>CCRxBΪ�͵�ƽ
 *
 *        PWMģʽ2
 *            ����Ƚϣ�
 *                   �ϼ���ʱCNT<CCRxy����ͣ��¼���ʱCNT>CCRxy���Ϊ�ߵ�ƽ
 *            ˫��Ƚϣ�
 *                   1�� ��ݲ��ϼ��� CCRxA<CNT��CCRxB���Ϊ�ߵ�ƽ
 *                   2�� ��ݲ��¼��� CCRxA<CNT��CCRxB���Ϊ�͵�ƽ
 *                   3�� ���ǲ��ϼ���CNT<CCRxA����ͣ��¼���CNT>CCRxBΪ�ߵ�ƽ
 */
typedef enum {
    AMHW_ZSN700_TIM_COMPARE_0 = 0,       /* ǿ��Ϊ0 */
    AMHW_ZSN700_TIM_COMPARE_1,           /* ǿ��Ϊ1 */
    AMHW_ZSN700_TIM_COMPARE_FIT_0,       /* �Ƚ�ƥ��ʱǿ��Ϊ0 */
    AMHW_ZSN700_TIM_COMPARE_FIT_1,       /* �Ƚ�ƥ��ʱǿ��Ϊ1 */
    AMHW_ZSN700_TIM_COMPARE_FIT_TOGGLE,  /* �Ƚ�ƥ��ʱ��ת */
    AMHW_ZSN700_TIM_COMPARE_FIT_HIGH,    /* �Ƚ�ƥ��ʱ���һ���������ڵĸߵ�ƽ */
    AMHW_ZSN700_TIM_COMPARE_PWM1,        /* PWMģʽ1 */
    AMHW_ZSN700_TIM_COMPARE_PWM2,        /* PWMģʽ2 */
}amhw_zsn700_tim_compare_t;

/**
 * \brief �ȽϿ�������ö�٣���Ӧ�ڼĴ����е���ʼλ��
 */
typedef enum {
    AMHW_ZSN700_TIM_COMPARE_TYPE_FLTB2 = 20,   /* CH2Bͨ���ȽϿ��� */
    AMHW_ZSN700_TIM_COMPARE_TYPE_FLTA2 = 16,   /* CH2Aͨ���ȽϿ��� */
    AMHW_ZSN700_TIM_COMPARE_TYPE_FLTB1 = 12,   /* CH1Bͨ���ȽϿ��� */
    AMHW_ZSN700_TIM_COMPARE_TYPE_FLTA1 = 8,    /* CH1Aͨ���ȽϿ��� */
    AMHW_ZSN700_TIM_COMPARE_TYPE_FLTB0 = 4,    /* CH0Bͨ���ȽϿ��� */
    AMHW_ZSN700_TIM_COMPARE_TYPE_FLTA0 = 0,    /* CH0Aͨ���ȽϿ��� */
}amhw_zsn700_tim_compare_type_t;

/**
 * \brief �ȽϿ���    ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : ��Ӧ�Ŀ�������(amhw_zsn700_tim_compare_type_tö����)
 *
 * \return �ȽϿ���(amhw_zsn700_tim_compare_tö����)
 */
am_static_inline
amhw_zsn700_tim_compare_t
    amhw_zsn700_tim_mode23_compare_get (amhw_zsn700_tim_t             *p_hw_tim,
                                        amhw_zsn700_tim_compare_type_t type)
{
    return (amhw_zsn700_tim_compare_t)((p_hw_tim->fltr >> type) & 0x7ul);
}

/**
 * \brief �ȽϿ���     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : ��Ӧ�Ŀ�������(amhw_zsn700_tim_compare_type_tö����)
 * \param[in] choice   : �˲�����(amhw_zsn700_tim_compare_tö����)
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_compare_set(amhw_zsn700_tim_t             *p_hw_tim,
                                        amhw_zsn700_tim_compare_type_t type,
                                        amhw_zsn700_tim_compare_t      choice)
{
    p_hw_tim->fltr =(p_hw_tim->fltr & (~(0x7ul << type))) |
                    ((choice & 0x7ul) << type);
}

/* ADC�������ƼĴ�����TIMx_ADTR����ؿ���λ�궨�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_ADTE   (0x1UL << 7) /* ʹ��ADC����ȫ�ֿ��� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_CMB2E  (0x1UL << 6) /* ͨ��2B�Ƚ�ƥ�䴥��ADCʹ�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_CMB1E  (0x1UL << 5) /* ͨ��1B�Ƚ�ƥ�䴥��ADCʹ�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_CMB0E  (0x1UL << 4) /* ͨ��0B�Ƚ�ƥ�䴥��ADCʹ�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_CMA2E  (0x1UL << 3) /* ͨ��2A�Ƚ�ƥ�䴥��ADCʹ�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_CMA1E  (0x1UL << 2) /* ͨ��1A�Ƚ�ƥ�䴥��ADCʹ�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_CMA0E  (0x1UL << 1) /* ͨ��0A�Ƚ�ƥ�䴥��ADCʹ�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_UEVE   (0x1UL << 0) /* �¼����´���ADCʹ�� */
#define AMHW_ZSN700_TIM_ADC_TRIGGER_ALL    0xFF         /* ���� */

/**
 * \brief �����궨��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_ADC_TRIGGER_ADTE
 *                       .
 *                       .
 *                       .
 *                       AMHW_ZSN700_TIM_ADC_TRIGGER_ALL
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_adc_trigger_enable (amhw_zsn700_tim_t *p_hw_tim,
                                                uint32_t           type)
{
    if(0xFF == type) {
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_ADTE;
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_CMB2E;
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_CMB1E;
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_CMB0E;
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_CMA2E;
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_CMA1E;
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_CMA0E;
        p_hw_tim->adtr |= AMHW_ZSN700_TIM_ADC_TRIGGER_UEVE;
    }
    else {
        p_hw_tim->adtr |= type;
    }
}

/**
 * \brief �����궨�����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_ADC_TRIGGER_ADTE
 *                       .
 *                       .
 *                       .
 *                       AMHW_ZSN700_TIM_ADC_TRIGGER_ALL
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_adc_trigger_disable (amhw_zsn700_tim_t  *p_hw_tim,
                                                 uint32_t           type)
{
    if(0xFF == type) {
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_ADTE;
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_CMB2E;
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_CMB1E;
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_CMB0E;
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_CMA2E;
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_CMA1E;
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_CMA0E;
        p_hw_tim->adtr &= ~AMHW_ZSN700_TIM_ADC_TRIGGER_UEVE;
    }
    else {
        p_hw_tim->adtr &= ~type;
    }
}

/**
 * \brief CCGB   ����Ƚ�B�������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 * \note Ӳ���Զ�����
 *       �ڱȽ�ģʽ��ֻ�����ж�
 *       �ڲ���ģʽ�²����жϲ��Ҳ����������ֵ������Ĵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_crchx_ccgb_enable (amhw_zsn700_tim_t *p_hw_tim,
                                               uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 15);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 15);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 15);
            break;

        default:
            break;
    }
}

/**
 * \brief CCGA   ����Ƚ�A�������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \note Ӳ���Զ�����
 *       �ڱȽ�ģʽ��ֻ�����ж�
 *       �ڲ���ģʽ�²����жϲ��Ҳ����������ֵ������Ĵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_crchx_ccga_enable (amhw_zsn700_tim_t *p_hw_tim,
                                               uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 14);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 14);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 14);
            break;

        default:
            break;
    }
}

/**
 * \brief Bͨ���Ƚ�ƥ������
 */
typedef enum {
    AMHW_ZSN700_TIM_CISB_TYPE_NO = 0,   /* ��ƥ�� */
    AMHW_ZSN700_TIM_CISB_TYPE_RISING,   /* ����ƥ�� */
    AMHW_ZSN700_TIM_CISB_TYPE_FALLING,  /* �½�ƥ�� */
    AMHW_ZSN700_TIM_CISB_TYPE_BOTH,     /* ˫ƥ�� */
}amhw_zsn700_tim_cisb_type_t;

/**
 * \brief CISB   Bͨ���Ƚ�ƥ������    ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return amhw_zsn700_tim_cisb_type_tö����
 */
am_static_inline
amhw_zsn700_tim_cisb_type_t
    amhw_zsn700_tim_mode23_cisb_get (amhw_zsn700_tim_t *p_hw_tim,
                                     uint8_t            chan)
{
    uint8_t get_value;
    switch(chan / 2) {
        case 0:
            get_value = (p_hw_tim->crchx[0] >> 12) & 0x3ul;
            break;

        case 1:
            get_value = (p_hw_tim->crchx[1] >> 12) & 0x3ul;
            break;

        case 2:
            get_value = (p_hw_tim->crchx[2] >> 12) & 0x3ul;
            break;

        default:
            break;
    }
    return (amhw_zsn700_tim_cisb_type_t)get_value;
}

/**
 * \brief CISB   Bͨ���Ƚ�ƥ������     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 * \param[in] choice   : amhw_zsn700_tim_cisb_type_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cisb_set(amhw_zsn700_tim_t           *p_hw_tim,
                                     uint8_t                      chan,
                                     amhw_zsn700_tim_cisb_type_t  choice)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] = (p_hw_tim->crchx[0] & (~(0x3ul << 12))) |
                                 ((choice & 0x3ul) << 12);
            break;

        case 1:
            p_hw_tim->crchx[1] = (p_hw_tim->crchx[1] & (~(0x3ul << 12))) |
                                 ((choice & 0x3ul) << 12);
            break;

        case 2:
            p_hw_tim->crchx[2] = (p_hw_tim->crchx[2] & (~(0x3ul << 12))) |
                                 ((choice & 0x3ul) << 12);
            break;

        default:
            break;
    }
}

/**
 * \brief CDEB   B����Ƚϴ���DMA����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cdeb_dma_disable (amhw_zsn700_tim_t *p_hw_tim,
                                             uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 11);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 11);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 11);
            break;

        default:
            break;
    }
}

/**
 * \brief CDEB   B����Ƚϴ���DMAʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cdeb_dma_enable (amhw_zsn700_tim_t *p_hw_tim,
                                             uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 11);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 11);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 11);
            break;

        default:
            break;
    }
}

/**
 * \brief CDEA   A����Ƚϴ���DMA����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cdea_dma_disable (amhw_zsn700_tim_t *p_hw_tim,
                                             uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 10);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 10);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 10);
            break;

        default:
            break;
    }
}

/**
 * \brief CDEA   A����Ƚϴ���DMAʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cdea_dma_enable (amhw_zsn700_tim_t *p_hw_tim,
                                             uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 10);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 10);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 10);
            break;

        default:
            break;
    }
}

/**
 * \brief CIEB   B����Ƚϴ����жϽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cieb_int_disable (amhw_zsn700_tim_t *p_hw_tim,
                                              uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 9);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 9);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 9);
            break;

        default:
            break;
    }
}

/**
 * \brief CIEB   B����Ƚϴ����ж�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cieb_int_enable (amhw_zsn700_tim_t *p_hw_tim,
                                             uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 9);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 9);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 9);
            break;

        default:
            break;
    }
}

/**
 * \brief B����Ƚϴ����ж�ʹ��״̬��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ZSN700_TIM_CH0B
 *                       ZSN700_TIM_CH1B
 *                       ZSN700_TIM_CH2B
 *
 * \return  AM_TRUE  ��ʹ����Ч
 *          AM_FALSE ��ʹ����Ч
 *
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode23_cieb_int_get (amhw_zsn700_tim_t *p_hw_tim,
                                               uint8_t            chan)
{
	am_bool_t result = AM_FALSE;

    switch(chan / 2) {
        case 0:
        	result = (p_hw_tim->crchx[0] & (0x1ul << 9)) ? AM_TRUE : AM_FALSE;
            break;

        case 1:
        	result = (p_hw_tim->crchx[1] & (0x1ul << 9)) ? AM_TRUE : AM_FALSE;
            break;

        case 2:
        	result = (p_hw_tim->crchx[2] & (0x1ul << 9)) ? AM_TRUE : AM_FALSE;
            break;

        default:
            break;
    }

    return result;
}

/**
 * \brief CIEA   A����Ƚϴ����жϽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ciea_int_disable (amhw_zsn700_tim_t *p_hw_tim,
                                              uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 8);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 8);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 8);
            break;

        default:
            break;
    }
}

/**
 * \brief CIEA   A����Ƚϴ����ж�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ciea_int_enable (amhw_zsn700_tim_t *p_hw_tim,
                                             uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 8);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 8);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 8);
            break;

        default:
            break;
    }
}

/**
 * \brief A����Ƚϴ����ж�ʹ��״̬��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ZSN700_TIM_CH0A ��
 *                       ZSN700_TIM_CH1A ��
 *                       ZSN700_TIM_CH2A ��
 *
 * \return  AM_TRUE  ��ʹ����Ч
 *          AM_FALSE ��ʹ����Ч
 *
 */
am_static_inline
am_bool_t amhw_zsn700_tim_mode23_ciea_int_get (amhw_zsn700_tim_t *p_hw_tim,
                                               uint8_t            chan)
{
	am_bool_t result = AM_FALSE;

    switch(chan / 2) {
        case 0:
        	result = (p_hw_tim->crchx[0] & (0x1ul << 8)) ? AM_TRUE : AM_FALSE;
            break;

        case 1:
        	result = (p_hw_tim->crchx[1] & (0x1ul << 8)) ? AM_TRUE : AM_FALSE;
            break;

        case 2:
        	result = (p_hw_tim->crchx[2] & (0x1ul << 8)) ? AM_TRUE : AM_FALSE;
            break;

        default:
            break;
    }

    return result;
}

/**
 * \brief BUFEB   �ȽϹ��ܣ� B�Ƚϻ���ʹ�ܿ���     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_buffb_disable (amhw_zsn700_tim_t *p_hw_tim,
                                           uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 7);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 7);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 7);
            break;

        default:
            break;
    }
}

/**
 * \brief BUFEB   �ȽϹ��ܣ� B�Ƚϻ���ʹ�ܿ���     ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_buffb_enable (amhw_zsn700_tim_t *p_hw_tim,
                                          uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 7);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 7);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 7);
            break;

        default:
            break;
    }
}

/**
 * \brief BUFEA   �ȽϹ��ܣ�A�Ƚϻ���ʹ�ܿ���     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_buffa_disable (amhw_zsn700_tim_t *p_hw_tim,
                                           uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 6);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 6);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 6);
            break;

        default:
            break;
    }
}

/**
 * \brief BUFEA   �ȽϹ��ܣ� A�Ƚϻ���ʹ�ܿ���     ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_buffa_enable (amhw_zsn700_tim_t *p_hw_tim,
                                          uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 6);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 6);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 6);
            break;

        default:
            break;
    }
}

/**
 * \brief CSB   Bͨ������/�ȽϹ���ѡ��      �Ƚ�ģʽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_csb_compare (amhw_zsn700_tim_t *p_hw_tim,
                                         uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 5);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 5);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 5);
            break;

        default:
            break;
    }
}

/**
 * \brief CSB   Bͨ������/�ȽϹ���ѡ��      ����ģʽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_csb_cap (amhw_zsn700_tim_t *p_hw_tim,
                                     uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 5);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 5);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 5);
            break;

        default:
            break;
    }
}

/**
 * \brief CSA   Aͨ������/�ȽϹ���ѡ��      �Ƚ�ģʽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_csa_compare (amhw_zsn700_tim_t *p_hw_tim,
                                         uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 4);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 4);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 4);
            break;

        default:
            break;
    }
}

/**
 * \brief CSA   Aͨ������/�ȽϹ���ѡ��      ����ģʽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_csa_cap (amhw_zsn700_tim_t *p_hw_tim,
                                     uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 4);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 4);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 4);
            break;

        default:
            break;
    }
}

/**
 * \brief CFB   Bͨ���½��ز������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cfb_disable (amhw_zsn700_tim_t *p_hw_tim,
                                         uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 3);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 3);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 3);
            break;

        default:
            break;
    }
}

/**
 * \brief CFB   Bͨ���½��ز���ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cfb_enable (amhw_zsn700_tim_t *p_hw_tim,
                                        uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 3);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 3);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 3);
            break;

        default:
            break;
    }
}

/**
 * \brief CRB   Bͨ�������ز������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_crb_disable (amhw_zsn700_tim_t *p_hw_tim,
                                         uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 2);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 2);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 2);
            break;

        default:
            break;
    }
}

/**
 * \brief CRB   Bͨ�������ز���ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_crb_enable (amhw_zsn700_tim_t *p_hw_tim,
                                        uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 2);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 2);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 2);
            break;

        default:
            break;
    }
}

/**
 * \brief CFA   Aͨ���½��ز������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cfa_disable (amhw_zsn700_tim_t *p_hw_tim,
                                         uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 1);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 1);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 1);
            break;

        default:
            break;
    }
}

/**
 * \brief CFA   Aͨ���½��ز���ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cfa_enable (amhw_zsn700_tim_t *p_hw_tim,
                                        uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 1);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 1);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 1);
            break;

        default:
            break;
    }
}

/**
 * \brief CRA   Aͨ�������ز������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cra_disable (amhw_zsn700_tim_t *p_hw_tim,
                                         uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] &= ~(0x1ul << 0);
            break;

        case 1:
            p_hw_tim->crchx[1] &= ~(0x1ul << 0);
            break;

        case 2:
            p_hw_tim->crchx[2] &= ~(0x1ul << 0);
            break;

        default:
            break;
    }
}

/**
 * \brief CRA   Aͨ�������ز���ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_cra_enable (amhw_zsn700_tim_t *p_hw_tim,
                                        uint8_t            chan)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] |= (0x1ul << 0);
            break;

        case 1:
            p_hw_tim->crchx[1] |= (0x1ul << 0);
            break;

        case 2:
            p_hw_tim->crchx[2] |= (0x1ul << 0);
            break;

        default:
            break;
    }
}

/**
 * \brief �ȽϹ������ɲ����ƽ����
 */
typedef enum {
    AMHW_ZSN700_TIM_CMP_BRAKEOUT_Z = 0,      /* ������� */
    AMHW_ZSN700_TIM_CMP_BRAKEOUT_NO,         /* �������Ӱ�� */
    AMHW_ZSN700_TIM_CMP_BRAKEOUT_LOW,        /* ǿ������͵�ƽ */
    AMHW_ZSN700_TIM_CMP_BRAKEOUT_HIGH,       /* ǿ������ߵ�ƽ */
}amhw_zsn700_tim_cmp_brakeout_t;

/**
 * \brief BKSB  Bͨ���ȽϹ������ɲ����ƽ����     ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return amhw_zsn700_tim_cmp_brakeout_tö����
 */
am_static_inline
amhw_zsn700_tim_cmp_brakeout_t
    amhw_zsn700_tim_mode23_bksb_get (amhw_zsn700_tim_t *p_hw_tim,
                                     uint8_t            chan)
{
    uint8_t get_value;
    switch(chan / 2) {
        case 0:
            get_value = (p_hw_tim->crchx[0] >> 2) & 0x3ul;
            break;

        case 1:
            get_value = (p_hw_tim->crchx[1] >> 2) & 0x3ul;
            break;

        case 2:
            get_value = (p_hw_tim->crchx[2] >> 2) & 0x3ul;
            break;

        default:
            break;
    }
    return (amhw_zsn700_tim_cmp_brakeout_t)get_value;
}

/**
 * \brief BKSB  Bͨ���ȽϹ������ɲ����ƽ����     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 * \param[in] choice   : amhw_zsn700_tim_cmp_brakeout_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_bksb_set(amhw_zsn700_tim_t             *p_hw_tim,
                                     uint8_t                        chan,
                                     amhw_zsn700_tim_cmp_brakeout_t choice)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] = (p_hw_tim->crchx[0] & (~(0x3ul << 2))) |
                                 ((choice & 0x3ul) << 2);
            break;

        case 1:
            p_hw_tim->crchx[1] = (p_hw_tim->crchx[1] & (~(0x3ul << 2))) |
                                 ((choice & 0x3ul) << 2);
            break;

        case 2:
            p_hw_tim->crchx[2] = (p_hw_tim->crchx[2] & (~(0x3ul << 2))) |
                                 ((choice & 0x3ul) << 2);
            break;

        default:
            break;
    }
}

/**
 * \brief BKSA  Aͨ���ȽϹ������ɲ����ƽ����     ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return amhw_zsn700_tim_cmp_brakeout_tö����
 */
am_static_inline
amhw_zsn700_tim_cmp_brakeout_t
    amhw_zsn700_tim_mode23_bksa_get (amhw_zsn700_tim_t *p_hw_tim,
                                     uint8_t            chan)
{
    uint8_t get_value;
    switch(chan / 2) {
        case 0:
            get_value = (p_hw_tim->crchx[0] >> 0) & 0x3ul;
            break;

        case 1:
            get_value = (p_hw_tim->crchx[1] >> 0) & 0x3ul;
            break;

        case 2:
            get_value = (p_hw_tim->crchx[2] >> 0) & 0x3ul;
            break;

        default:
            break;
    }
    return (amhw_zsn700_tim_cmp_brakeout_t)get_value;
}

/**
 * \brief BKSA  Aͨ���ȽϹ������ɲ����ƽ����     ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 * \param[in] choice   : amhw_zsn700_tim_cmp_brakeout_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_bksa_set(amhw_zsn700_tim_t             *p_hw_tim,
                                     uint8_t                        chan,
                                     amhw_zsn700_tim_cmp_brakeout_t choice)
{
    switch(chan / 2) {
        case 0:
            p_hw_tim->crchx[0] = (p_hw_tim->crchx[0] & (~(0x3ul << 0))) |
                                 ((choice & 0x3ul) << 0);
            break;

        case 1:
            p_hw_tim->crchx[1] = (p_hw_tim->crchx[1] & (~(0x3ul << 0))) |
                                 ((choice & 0x3ul) << 0);
            break;

        case 2:
            p_hw_tim->crchx[2] = (p_hw_tim->crchx[2] & (~(0x3ul << 0))) |
                                 ((choice & 0x3ul) << 0);
            break;

        default:
            break;
    }
}

#define AMHW_ZSN700_TIM_DTR_VCE     (0x1UL << 14)  /* VCɲ��ʹ�� */
#define AMHW_ZSN700_TIM_DTR_SAFEEN  (0x1UL << 13)  /* Safety ɲ��ʹ�� */
#define AMHW_ZSN700_TIM_DTR_MOE     (0x1UL << 12)  /* PWM���ʹ�� */
#define AMHW_ZSN700_TIM_DTR_AOE     (0x1UL << 11)  /* PWM����Զ�ʹ�� */
#define AMHW_ZSN700_TIM_DTR_BKE     (0x1UL << 10)  /* ɲ��ʹ�� */
#define AMHW_ZSN700_TIM_DTR_DTEN    (0x1UL << 9)   /* ��������ʹ�� */

/**
 * \brief ����ʱ��Ĵ�����TIMx_DTR��        ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_DTR_VCE
 *                       .
 *                       .
 *                       .
 *                       AMHW_ZSN700_TIM_DTR_DTEN
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_dtr_disable (amhw_zsn700_tim_t *p_hw_tim,
                                         uint16_t           type)
{
    p_hw_tim->dtr &= ~type;
}

/**
 * \brief ����ʱ��Ĵ�����TIMx_DTR��        ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : AMHW_ZSN700_TIM_DTR_VCE
 *                       .
 *                       .
 *                       .
 *                       AMHW_ZSN700_TIM_DTR_DTEN
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_dtr_enable (amhw_zsn700_tim_t *p_hw_tim,
                                        uint16_t           type)
{
    p_hw_tim->dtr |= type;
}

/**
 * \brief bksel    ɲ��ѡ��       TIM1/2ʹ�ñ���ĵ�ɲ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note TIM0/TIM3ѡ����Ч
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_bksel_mine (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->dtr &= ~(0x1ul << 8);
}

/**
 * \brief bksel    ɲ��ѡ��      TIM1/2ʹ�� TIM0�ĵ�ɲ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note TIM0/TIM3ѡ����Ч
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_bksel_tim0 (amhw_zsn700_tim_t *p_hw_tim)
{
    p_hw_tim->dtr |= (0x1ul << 8);
}

/**
 * \brief DTR  ����ʱ��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note  DTR[7]   = 0     T = DTR[6:0]+2             2-129      step=1
 *
 *        DTR[7:6] = 10    T = {DTR[5:0]+64}*2 +2     130-256    step=2
 *
 *        DTR[7:5] = 110   T = {DTR[4:0]+32}*8 +2     258-506    step=8
 *
 *        DTR[7:5] = 111   T = {DTR[4:0]+32}*16 +2    514-1010   step=16
 *
 * \return �趨��ֵ
 */
am_static_inline
uint8_t amhw_zsn700_tim_mode23_dtr_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return ((p_hw_tim->dtr >> 0) & 0xfful);
}

/**
 * \brief DTR  ����ʱ��   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] data     : ���趨��ֵ(2-256��258-506��514-1010)
 *
 * \note  DTR[7]   = 0     T = DTR[6:0]+2             2-129      step=1
 *
 *        DTR[7:6] = 10    T = {DTR[5:0]+64}*2 +2     130-256    step=2
 *
 *        DTR[7:5] = 110   T = {DTR[4:0]+32}*8 +2     258-506    step=8
 *
 *        DTR[7:5] = 111   T = {DTR[4:0]+32}*16 +2    514-1010   step=16
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_dtr_set(amhw_zsn700_tim_t *p_hw_tim,
                                    uint16_t           data)
{
	if(data <= 2) {
		data = 0;
    }else if(data <= 129) {
        data = data - 2;
    } else if(data <= 257) {
        if(data == 257) {
            data = 256;
        }
        data = (((data - 2) >> 1) - 64) | 0x80;
    } else if(data <= 513) {
        if((data <= 513) || (data > 506)) {
            data = 506;
        }
        data = (((data - 2) >> 3) - 32) | 0xC0;
    } else if(data <= 1010) {
        data = (((data - 2) >> 4) - 32) | 0xE0;
    } else {
        data = 0;
    }

    p_hw_tim->dtr = (p_hw_tim->dtr & (~(0xfful << 0))) |
                    ((data & 0xfful) << 0);
}

/**
 * \brief RCR  �ظ����ڼ���ֵ   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note  ����RCR+1�����ڸ�����������������¼����£�������������������ʱ�ڲ�RCR_CNT��1��
 *        �����������RCR_CNT����RCR��ֵ�����Ҳ����¼�����UEV�ź�
 *
 * \return �趨��ֵ
 */
am_static_inline
uint8_t amhw_zsn700_tim_mode23_rcr_get (amhw_zsn700_tim_t *p_hw_tim)
{
    return ((p_hw_tim->rcr >> 0) & 0xfful);
}

/**
 * \brief RCR  �ظ����ڼ���ֵ   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] data     : ���趨��ֵ
 *
 * \note  ����RCR+1�����ڸ�����������������¼����£�������������������ʱ�ڲ�RCR_CNT��1��
 *        �����������RCR_CNT����RCR��ֵ�����Ҳ����¼�����UEV�ź�
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_rcr_set(amhw_zsn700_tim_t *p_hw_tim,
                                    uint8_t            data)
{
    p_hw_tim->rcr = (p_hw_tim->rcr & (~(0xfful << 0))) |
                    ((data & 0xfful) << 0);
}

/**
 * \brief CCRxy  �Ƚϲ���Ĵ������ȽϾ��л��湦��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 *
 * \return �趨��ֵ
 */
am_static_inline
uint16_t amhw_zsn700_tim_mode23_ccrxy_get (amhw_zsn700_tim_t *p_hw_tim,
                                           uint8_t            chan)
{
    uint16_t data = 0;

    switch(chan / 2) {
        case 0:
            if(0 == (chan % 2)) {
                data = p_hw_tim->ccrxx[0].a & 0xfffful;
            } else {
                data = p_hw_tim->ccrxx[0].b & 0xfffful;
            }
            break;

        case 1:
            if(0 == (chan % 2)) {
                data = p_hw_tim->ccrxx[1].a & 0xfffful;
            } else {
                data = p_hw_tim->ccrxx[1].b & 0xfffful;
            }
            break;

        case 2:
            if(0 == (chan % 2)) {
                data = p_hw_tim->ccrxx[2].a & 0xfffful;
            } else {
                data = p_hw_tim->ccrxx[2].b & 0xfffful;
            }
            break;

        default:
            break;
    }

    return data;
}

/**
 * \brief CCRxy  �Ƚϲ���Ĵ������ȽϾ��л��湦��      ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] chan     : ͨ����  ZSN700_TIM_CH0A               ��
 *                            ZSN700_TIM_CH0B               ��
 *                            ZSN700_TIM_CH1A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH1B(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2A(TIM3����ͨ��)    ��
 *                            ZSN700_TIM_CH2B(TIM3����ͨ��)    ��
 * \param[in] data     : ���趨��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_tim_mode23_ccrxy_set(amhw_zsn700_tim_t *p_hw_tim,
                                      uint8_t            chan,
                                      uint16_t           data)
{
    switch(chan / 2) {
        case 0:
            if(0 == (chan % 2)) {
                p_hw_tim->ccrxx[0].a = data;
            } else {
                p_hw_tim->ccrxx[0].b = data;
            }
            break;

        case 1:
            if(0 == (chan % 2)) {
                p_hw_tim->ccrxx[1].a = data;
            } else {
                p_hw_tim->ccrxx[1].b = data;
            }
            break;

        case 2:
            if(0 == (chan % 2)) {
                p_hw_tim->ccrxx[2].a = data;
            } else {
                p_hw_tim->ccrxx[2].b = data;
            }
            break;

        default:
            break;
    }
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZSN700_TIM_H */

/* end of file */
