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
 * 1. 16 λ���ϡ����¡�����/���Զ�װ�ؼ�����
 * 2. 16 λ�ɱ�̣�����ʵʱ�޸ģ�Ԥ��Ƶ����������ʱ��Ƶ�ʵķ�Ƶϵ��Ϊ 1 ~ 65536 ֮���������ֵ
 * 3. ��� 4������ͨ��(����TIM1��TIM2��TIM3������ֻ��һ��ͨ��)��
 *    -  ���벶��
 *    -  ����Ƚ�
 *    -  PWM ���ɣ���Ե���м����ģʽ��
 *    -  ������ģʽ���
 *    -  ����ʱ��ɱ�̵Ļ������
 *    -  ʹ���ⲿ�źſ��ƶ�ʱ���Ͷ�ʱ��������ͬ����·
 * 4. ������ָ����Ŀ�ļ���������֮����¶�ʱ���Ĵ������ظ�������
 * 5. ɲ�������źſ��Խ���ʱ������ź����ڸ�λ״̬����һ����֪״̬
 * 6. �����¼�����ʱ�����ж�/DMA��
 *    -  ���£��������������/�����������������ʼ����ͨ����������ڲ�/�ⲿ������
 *    -  �����¼���������������ֹͣ����ʼ���������ڲ�/�ⲿ����������
 *    -  ���벶��
 *    -  ����Ƚ�
 *    -  ɲ���ź�����
 * 7.  ֧����Զ�λ���������������������ͻ�����������·
 * 8.  ����������Ϊ�ⲿʱ�ӻ��߰����ڵĵ�������
 *
 * \note ͨ�ö�ʱ��TIMXû��rcr�� bdtr�Ĵ���
 *       ͨ�ö�ʱ��TIM14ֻ��һ��ccmr��ccr�Ĵ����� û��rcr�� bdtr���µļĴ���
 *       ͨ�ö�ʱ��TIM16��17ֻ��һ��ccmr��ccr�Ĵ���
 *
 * \internal
 * \par History
 * - 1.00 17-04-17  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_STM32F103RBT6_TIM_H
#define __AMHW_STM32F103RBT6_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_stm32f103rbt6_if_tim
 * \copydoc amhw_stm32f103rbt6_tim.h
 * @{
 */

/**
  * \brief ��ʱ���Ĵ�����ṹ��
  */
typedef struct amhw_stm32f103rbt6_tim {
    __IO uint32_t cr[2];         /**< \brief ���ƼĴ��� */
    __IO uint32_t smcr;          /**< \brief ��ģʽ���ƼĴ��� */
    __IO uint32_t dier;          /**< \brief DMA/�ж�ʹ�ܼĴ��� */
    __IO uint32_t sr;            /**< \brief ״̬�Ĵ��� */
    __O  uint32_t egr;           /**< \brief �¼������Ĵ��� */
    __IO uint32_t ccmr[2];       /**< \brief ��׽/�Ƚ�ģʽ�Ĵ��� */
    __O  uint32_t ccer;          /**< \brief ��׽/�Ƚ�ʹ�ܼĴ��� */
    __IO uint32_t cnt;           /**< \brief ������ */
    __IO uint32_t psc;           /**< \brief Ԥ��Ƶ�� */
    __IO uint32_t arr;           /**< \brief �Զ�װ�ؼĴ��� */
    __IO uint32_t rcr;           /**< \brief �ظ������Ĵ��� */
    __IO uint32_t ccr[4];        /**< \brief ����/�ȽϼĴ��� */
    __IO uint32_t bdtr;          /**< \brief ɲ���������Ĵ��� */
    __IO uint32_t dcr;           /**< \brief ��ʱ�� DMA���ƼĴ��� */
    __IO uint32_t dmar;          /**< \brief ����ģʽ�� DMA ��ַ */
} amhw_stm32f103rbt6_tim_t;

/**
 * \brief �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��ǰ��������ֵ
 */
am_static_inline
uint32_t amhw_stm32f103rbt6_tim_count_get (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    return p_hw_tim->cnt;
}

/**
 * \brief ���õ�ǰ��������ֵ
 *
 * \param[in] p_hw_tim :    ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    :    ���õļ�������ֵ
 *
 * \note: ͨ�ö�ʱ��TIM2��TIM3��ֵΪ32λ, ������Ϊ16λ
 *
 *\ return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_count_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint32_t value)
{
    p_hw_tim->cnt = value;
}

/**
 * \brief ����Ԥ��Ƶ�Ĵ�����ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : ���õ�Ԥ��Ƶ�Ĵ���ֵ�����յķ�ƵΪ value+1��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_prescale_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint16_t value)
{
    p_hw_tim->psc = value;
}

/**
 * \brief ��ȡԤ��Ƶ�Ĵ�����ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return Ԥ��Ƶ�Ĵ�����ֵ
 */
am_static_inline
uint32_t amhw_stm32f103rbt6_tim_prescale_get (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    return p_hw_tim->psc;
}

/**
 * \brief �����Զ�װ�ؼĴ�����ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : �Զ�װ�ؼĴ�����ֵ
 *
 * \note: ͨ�ö�ʱ��TIM2��TIM3��ֵΪ32λ, ������Ϊ16λ, ��ֵһ�������һ�θ����¼�����ʱ�Ż�������Ч
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_arr_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint32_t value)
{
    p_hw_tim->arr = value;
}

/**
 * \brief ��ȡ�Զ�װ�ؼĴ�����ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return �Զ�װ�ؼĴ�����ֵ
 */
am_static_inline
uint32_t amhw_stm32f103rbt6_tim_arr_get (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    return p_hw_tim->arr;
}

/**
 * \brief ʹ�ܶ�ʱ��(��ʼ����)
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_enable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 0 , 1);
}

/**
 * \brief ��ֹ��ʱ��(ֹͣ����)
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_disable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 0, 0);
}

/**
 * \brief ���UDISλ����������¼�UEV����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_udis_enable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 1 , 0);
}

/**
 * \brief ��UDISλ����ֹ�����¼�UEV����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_udis_disable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 1, 1);
}

/**
 * \brief �Զ���װ��Ԥװ������ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_arpe_enable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 7 , 1);
}

/**
 * \brief �Զ���װ��Ԥװ���������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_arpe_disable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 7, 0);
}

/**
 * \brief ���ø���Դ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] urs_opt  : ����Դ�����ֵ
 *                       0������ UGλ��  ��ģʽ�����������ĸ��¡�������������ж�/DMA����
 *                       1�� ֻ��������������ж�/DMA����
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_urs_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t urs_opt)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 2, urs_opt);
}

/**
 * \brief ���ø���Դ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] opm_opt  : �Ƿ�ѡ������ģʽ
 *                       0���ڷ��������¼�ʱ����������ֹͣ
 *                       1�� �ڷ�����һ�θ����¼������ CEN λ��ʱ��������ֹͣ
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_opm_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t opm_opt)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 3, opm_opt);
}

/**
 * \brief ���ü����ķ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] dir_opt  : ��������ѡ��
 *                       0�����������ϼ���
 *                       1�����������¼���
 *
 *\note :������������Ϊ�������ģʽ�������ģʽʱ����λΪֻ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_dir_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t dir_opt)
{
    AM_BIT_MODIFY(p_hw_tim->cr[0], 4, dir_opt);
}

/**
 * \brief ����ģʽ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] cms_opt  : ����ģʽѡ��
 *                       0: ���ض���ģʽ
 *                       1: �������ģʽ 1
 *                       2: �������ģʽ 2
 *                       3: �������ģʽ 3
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_cms_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t cms_opt)
{
    AM_BITS_SET(p_hw_tim->cr[0], 5, 2, cms_opt);
}

/**
 * \brief ʱ�ӷ�Ƶ��������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ckd_opt  : ʱ�ӷ�Ƶ����ѡ��
 *                       0: tDTS = tCK_INT(��ʱ������ʱ��)
 *                       1: tDTS = 2 * tCK_INT(��ʱ������ʱ��)
 *                       2: tDTS = 4 * tCK_INT(��ʱ������ʱ��)
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ckd_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t ckd_opt)
{
    AM_BITS_SET(p_hw_tim->cr[0], 8, 2, ckd_opt);
}

/**
 * \brief ����/�Ƚ�Ԥװ�ؿ���ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note : ��λֻ�Ծ��л��������ͨ�������á�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccpc_enable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[1], 1, 0);
}

/**
 * \brief ����/�Ƚ�Ԥװ�ؿ��ƽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note : ��λֻ�Ծ��л��������ͨ�������á�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccpc_disable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->cr[1], 0, 0);
}

/**
 * \brief ����/�ȽϿ��Ƹ�������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccus_opt : ����/�ȽϿ��Ƹ���ѡ��
 *                       0: ����/�ȽϿ���λ��Ԥװ�صģ�CCPC = 1����ֻ��ͨ������ COM λ����
 *                       1: ����/�ȽϿ���λ��Ԥװ�صģ�CCPC = 1��������ͨ������ COM λ�� TRGI�ϵ�һ�������ظ���
 *
 * \note : ��λֻ�Ծ��л��������ͨ�������á�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccus_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t ccus_opt)
{
    AM_BIT_MODIFY(p_hw_tim->cr[1], 2, ccus_opt);
}

/**
 * \brief ����/�Ƚϵ� DMA����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccds_opt : ����/�Ƚϵ� DMA ѡ��ѡ��
 *                       0: ������ CCx�¼�ʱ���ͳ� CCx�� DMA����
 *                       1: �����������¼�ʱ���ͳ� CCx�� DMA����
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccds_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t ccds_opt)
{
    AM_BIT_MODIFY(p_hw_tim->cr[1], 3, ccds_opt);
}

/**
 * \brief ��ģʽ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] mms_opt  : ��ģʽѡ��
 *                       0: ��λ; 1: ʹ��; 2: ����; 3: �Ƚ�����
 *                       4: �Ƚ�  �C OC1REF �źű�������Ϊ���������TRGO��
 *                       5: �Ƚ�  �C OC2REF �źű�������Ϊ���������TRGO��
 *                       6: �Ƚ�  �C OC3REF �źű�������Ϊ���������TRGO��
 *                       7: �Ƚ�  �C OC4REF �źű�������Ϊ���������TRGO��
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_mms_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t mms_opt)
{
    AM_BITS_SET(p_hw_tim->cr[1], 4, 3, mms_opt);
}

/**
 * \brief TI1����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ti1s_opt : TI1ѡ��
 *                       0: TIMx_CH1 �ܽ����� TI1 ����
 *                       1: TIMx_CH1��TIMx_CH2 �� TIMx_CH3 �ܽž��������� TI1 ����
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_tils_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t ti1s_opt)
{
    AM_BIT_MODIFY(p_hw_tim->cr[1], 7, ti1s_opt);
}

/**
 * \brief �������״̬����ö������
 */
typedef enum amhw_stm32f103rbt6_tim_ois {
    AMHW_STM32F103RBT6_TIM_OIS4   = (1UL << 14),  /**< \brief �������״̬ 4(OC4 ���) */
    AMHW_STM32F103RBT6_TIM_OIS3N  = (1UL << 13),  /**< \brief �������״̬ 3(OC3N ���) */
    AMHW_STM32F103RBT6_TIM_OIS3   = (1UL << 12),  /**< \brief �������״̬ 3(OC3 ���) */
    AMHW_STM32F103RBT6_TIM_OIS2N  = (1UL << 11),  /**< \brief �������״̬ 2(OC2N ���) */
    AMHW_STM32F103RBT6_TIM_OIS2   = (1UL << 10),  /**< \brief �������״̬ 2(OC2 ���) */
    AMHW_STM32F103RBT6_TIM_OIS1N  = (1UL << 9),   /**< \brief �������״̬ 1(OC1N���) */
    AMHW_STM32F103RBT6_TIM_OIS1   = (1UL << 8),   /**< \brief �������״̬ 1(OC1���) */
} amhw_stm32f103rbt6_tim_ois_t;

/**
 * \brief �������״̬��1
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ois_opt  : �������״̬ѡ��, ֵΪ amhw_stm32f103rbt6_tim_ois_t ��һ����ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ois_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                              amhw_stm32f103rbt6_tim_ois_t ois_opt)
{
    p_hw_tim->cr[1] |= ois_opt;
}

/**
 * \brief �������״̬��0
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ois_opt  : ������״̬ѡ��, ֵΪ amhw_stm32f103rbt6_tim_ois_t ��һ����ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ois_clr (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                              amhw_stm32f103rbt6_tim_ois_t ois_opt)
{
    p_hw_tim->cr[1] &= ~ois_opt;
}

/**
 * \brief ��ģʽѡ��ö������
 */
typedef enum amhw_stm32f103rbt6_tim_sms {
    AMHW_STM32F103RBT6_TIM_SLAVE_MODE_DISABLED  = 0,  /**< \brief �رմ�ģʽ */
    AMHW_STM32F103RBT6_TIM_ENCODER_MODE1        = 1,  /**< \brief ������ģʽ 1 */
    AMHW_STM32F103RBT6_TIM_ENCODER_MODE2        = 2,  /**< \brief ������ģʽ 2 */
    AMHW_STM32F103RBT6_TIM_ENCODER_MODE3        = 3,  /**< \brief ������ģʽ 3 */
    AMHW_STM32F103RBT6_TIM_RESET_MODE           = 4,  /**< \brief ��λģʽ */
    AMHW_STM32F103RBT6_TIM_GATED_MODE           = 5,  /**< \brief �ſ�ģʽ */
    AMHW_STM32F103RBT6_TIM_TRIGGER_MODE         = 6,  /**< \brief ����ģʽ */
    AMHW_STM32F103RBT6_TIM_EXTERNAL_CLOCK_MODE1 = 7,  /**< \brief �ⲿʱ��ģʽ 1 */
} amhw_stm32f103rbt6_tim_sms_t;

/**
 * \brief ��ģʽ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] sms_opt  : ��ģʽѡ��, ֵΪ amhw_stm32f103rbt6_tim_sms_t ��һ��ö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_sms_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t sms_opt)
{
    AM_BITS_SET(p_hw_tim->smcr, 0, 3, sms_opt);
}

/**
 * \brief ����ѡ��ö������
 */
typedef enum amhw_stm32f103rbt6_tim_ts {
    AMHW_STM32F103RBT6_TIM_ITR0       = 0,  /**< \brief �ڲ����� 0 */
    AMHW_STM32F103RBT6_TIM_ITR1       = 1,  /**< \brief �ڲ����� 1 */
    AMHW_STM32F103RBT6_TIM_ITR2       = 2,  /**< \brief �ڲ����� 2 */
    AMHW_STM32F103RBT6_TIM_ITR3       = 3,  /**< \brief �ڲ����� 3 */
    AMHW_STM32F103RBT6_TIM_TI1F_ED    = 4,  /**< \brief TI1�ı��ؼ���� */
    AMHW_STM32F103RBT6_TIM_TI1FP1     = 5,  /**< \brief �˲���Ķ�ʱ������1 */
    AMHW_STM32F103RBT6_TIM_TI2FP2     = 6,  /**< \brief �˲���Ķ�ʱ������2 */
    AMHW_STM32F103RBT6_TIM_ETRF       = 7,  /**< \brief �ⲿ�������� */
} amhw_stm32f103rbt6_tim_ts_t;

/**
 * \brief ��ʱ������
 */
typedef enum amhw_stm32f103rbt6_tim_type {
    AMHW_STM32F103RBT6_TIM_TYPE0       = 0,  /**< \brief TIM1 */
    AMHW_STM32F103RBT6_TIM_TYPE1       = 1,  /**< \brief TIM2��TIM3 */
    AMHW_STM32F103RBT6_TIM_TYPE2       = 2,  /**< \brief TIM14 */
    AMHW_STM32F103RBT6_TIM_TYPE3       = 3,  /**< \brief TIM16��TIM17 */
} amhw_stm32f103rbt6_tim_type_t;

/**
 * \brief ������������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ts_opt   : ��������ѡ��, ֵΪ  amhw_stm32f103rbt6_tim_ts_t ��һ��ö������
 *
 * \note : ��Щλֻ����δ�õ����� SMS = 000��ʱ���ı䣬�Ա����ڸı�ʱ��������ı��ؼ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ts_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t ts_opt)
{
    AM_BITS_SET(p_hw_tim->smcr, 4, 3, ts_opt);
}

/**
 * \brief ��/��ģʽ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] msm_opt  : ��/��ģʽѡ��
 *                       0�� ������
 *                       1�� �������루TRGI���ϵ��¼����ӳ��ˣ��������ڵ�ǰ��ʱ����ͨ�� TRGO�������ĴӶ�ʱ
 *                             ���������ͬ�������Ҫ��Ѽ�����ʱ��ͬ����һ����һ���ⲿ�¼�ʱ�Ƿǳ����õ�
 *
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_msm_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t msm_opt)
{
    AM_BIT_MODIFY(p_hw_tim->smcr, 7, msm_opt);
}

/**
 * \brief �ⲿ���������˲�ѡ��ö������
 */
typedef enum amhw_stm32f103rbt6_tim_etf {
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING0   = 0,  /**< \brief ���˲��� */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING1   = 1,  /**< \brief ����Ƶ�� fSAMPLING = fCK_INT��N = 2 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING2   = 2,  /**< \brief ����Ƶ�� fSAMPLING = fCK_INT��N = 4 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING3   = 3,  /**< \brief ����Ƶ�� fSAMPLING = fCK_INT��N = 8 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING4   = 4,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/2��N = 6 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING5   = 5,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/2��N = 8 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING6   = 6,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/4��N = 6 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING7   = 7,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/4��N = 8 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING8   = 8,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/8��N = 6 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING9   = 9,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/8��N = 8 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING10  = 10, /**< \brief ����Ƶ�� fSAMPLING = fDTS/16��N = 5 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING11  = 11, /**< \brief ����Ƶ�� fSAMPLING = fDTS/16��N = 6 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING12  = 12, /**< \brief ����Ƶ�� fSAMPLING = fDTS/16��N = 8 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING13  = 13, /**< \brief ����Ƶ�� fSAMPLING = fDTS/32��N = 5 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING14  = 14, /**< \brief ����Ƶ�� fSAMPLING = fDTS/32��N = 6 */
    AMHW_STM32F103RBT6_TIM_ETF_FSAMPLING15  = 15, /**< \brief ����Ƶ�� fSAMPLING = fDTS/32��N = 8 */
} amhw_stm32f103rbt6_tim_etf_t;

/**
 * \brief �ⲿ�����˲�����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] etf_opt  : �������˲�ѡ��, ֵΪ amhw_stm32f103rbt6_tim_etf_t ��һ����
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_etf_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t etf_opt)
{
    AM_BITS_SET(p_hw_tim->smcr, 8, 4, etf_opt);
}

/**
 * \brief �ⲿ����Ԥ��Ƶ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] etps_opt : �ⲿ����Ԥ��Ƶѡ��,
 *                       0: �ر�Ԥ��Ƶ;     1: ETRPƵ�ʳ��� 2;
 *                       2: ETRPƵ�ʳ��� 4; 3: ETRPƵ�ʳ��� 8;
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_etps_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t etps_opt)
{
    AM_BITS_SET(p_hw_tim->smcr, 12, 2, etps_opt);
}

/**
 * \brief �ⲿʱ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note : ��λֻ�Ծ��л��������ͨ�������á�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ece_enable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->smcr, 14, 1);
}

/**
 * \brief �ⲿʱ�ӽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note : ��λֻ�Ծ��л��������ͨ�������á�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ece_disable (amhw_stm32f103rbt6_tim_t *p_hw_tim)
{
    AM_BIT_MODIFY(p_hw_tim->smcr, 14, 0);
}

/**
 * \brief �ⲿ������������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] etp_opt  : �ⲿ��������ѡ��
 *                       0: ETR �����࣬�ߵ�ƽ����������Ч;
 *                       1: ETR �����࣬�͵�ƽ���½�����Ч;
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_etp_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t etp_opt)
{
    AM_BIT_MODIFY(p_hw_tim->smcr, 15, etp_opt);
}

/**
 * \brief ��ʱ����ص�DMA��������ö��
 */
typedef enum amhw_stm32f103rbt6_tim_dma_req {
    AMHW_STM32F103RBT6_TIM_UDE     = (1UL << 8),   /**< \brief ������ DMA ���� */
    AMHW_STM32F103RBT6_TIM_CC1DE   = (1UL << 9),   /**< \brief ������/�Ƚ� 1�� DMA���� */
    AMHW_STM32F103RBT6_TIM_CC2DE   = (1UL << 10),  /**< \brief ������/�Ƚ� 2�� DMA���� */
    AMHW_STM32F103RBT6_TIM_CC3DE   = (1UL << 11),  /**< \brief ������/�Ƚ� 3�� DMA���� */
    AMHW_STM32F103RBT6_TIM_CC4DE   = (1UL << 12),  /**< \brief ������/�Ƚ� 4�� DMA���� */
    AMHW_STM32F103RBT6_TIM_COMDE   = (1UL << 13),  /**< \brief ���� COM�� DMA���� */
    AMHW_STM32F103RBT6_TIM_TDE     = (1UL << 14),  /**< \brief ��������DMA���� */
} amhw_stm32f103rbt6_tim_dma_req_t;

/**
 * \brief ��ʱ����ص�DMA��������ʹ��
 *
 * \param[in] p_hw_tim   : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] dmareq_opt : ��ʱ����ص�DMA��������ѡ��, ֵΪ amhw_stm32f103rbt6_tim_dma_req_t ��һö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_dma_req_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                  uint8_t            dmareq_opt)
{
    p_hw_tim->dier |= dmareq_opt;
}

/**
 * \brief ��ʱ����ص�DMA�������ͽ���
 *
 * \param[in] p_hw_tim   : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] dmareq_opt : ��ʱ����ص�DMA��������ѡ��, ֵΪ amhw_stm32f103rbt6_tim_dma_req_t ��һö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_dma_req_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                   uint8_t            dmareq_opt)
{
    p_hw_tim->dier &= ~dmareq_opt;
}

/**
 * \brief ��ʱ������ж�����ö��
 */
typedef enum amhw_stm32f103rbt6_tim_int {
    AMHW_STM32F103RBT6_TIM_UIE     = (1UL << 0),  /**< \brief ��������ж� */
    AMHW_STM32F103RBT6_TIM_CC1IE   = (1UL << 1),  /**< \brief ������/�Ƚ� 1 �ж� */
    AMHW_STM32F103RBT6_TIM_CC2IE   = (1UL << 2),  /**< \brief ������/�Ƚ� 2 �ж� */
    AMHW_STM32F103RBT6_TIM_CC3IE   = (1UL << 3),  /**< \brief ������/�Ƚ� 3 �ж� */
    AMHW_STM32F103RBT6_TIM_CC4IE   = (1UL << 4),  /**< \brief ������/�Ƚ� 4 �ж� */
    AMHW_STM32F103RBT6_TIM_COMIE   = (1UL << 5),  /**< \brief ����COM�ж� */
    AMHW_STM32F103RBT6_TIM_TIE     = (1UL << 6),  /**< \brief �������ж� */
    AMHW_STM32F103RBT6_TIM_BIE     = (1UL << 7),  /**< \brief ����ɲ���ж� */
} amhw_stm32f103rbt6_tim_int_t;

/**
 * \brief ��ʱ������ж�����ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] int_opt  : ��ʱ������ж�������ѡ��, ֵΪ amhw_stm32f103rbt6_tim_int_t ��һö������
 *                       ���Ի���� (# (AMHW_STM32F103RBT6_TIM_UIE | AMHW_STM32F103RBT6_TIM_CC1IE))
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_int_enable (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t int_opt)
{
    p_hw_tim->dier |= int_opt;
}

/**
 * \brief ��ʱ������ж����ͽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] int_opt  : ��ʱ������ж�����ѡ��, ֵΪ amhw_stm32f103rbt6_tim_int_t ��һö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_int_disable (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t int_opt)
{
    p_hw_tim->dier &= ~int_opt;
}

/**
 * \brief ��ʱ�����״̬���λö������
 */
typedef enum amhw_stm32f103rbt6_tim_status_flag {
    AMHW_STM32F103RBT6_TIM_UIF     = (1UL << 0),  /**< \brief �����жϱ�� */
    AMHW_STM32F103RBT6_TIM_CC1IF   = (1UL << 1),  /**< \brief ����/�Ƚ� 1 �жϱ�� */
    AMHW_STM32F103RBT6_TIM_CC2IF   = (1UL << 2),  /**< \brief ����/�Ƚ� 2 �жϱ�� */
    AMHW_STM32F103RBT6_TIM_CC3IF   = (1UL << 3),  /**< \brief ����/�Ƚ� 3 �жϱ�� */
    AMHW_STM32F103RBT6_TIM_CC4IF   = (1UL << 4),  /**< \brief ����/�Ƚ� 4 �жϱ�� */
    AMHW_STM32F103RBT6_TIM_COMIF   = (1UL << 5),  /**< \brief COM�жϱ�� */
    AMHW_STM32F103RBT6_TIM_TIF     = (1UL << 6),  /**< \brief �����жϱ�� */
    AMHW_STM32F103RBT6_TIM_BIF     = (1UL << 7),  /**< \brief ɲ���жϱ�� */
    AMHW_STM32F103RBT6_TIM_CC1OF   = (1UL << 9),  /**< \brief ����/�Ƚ�1�ظ������� */
    AMHW_STM32F103RBT6_TIM_CC2OF   = (1UL << 10), /**< \brief ����/�Ƚ�2�ظ������� */
    AMHW_STM32F103RBT6_TIM_CC3OF   = (1UL << 11), /**< \brief ����/�Ƚ�3�ظ������� */
    AMHW_STM32F103RBT6_TIM_CC4OF   = (1UL << 12), /**< \brief ����/�Ƚ�4�ظ������� */
} amhw_stm32f103rbt6_tim_status_flag_t;

/**
 * \brief ȡ�ö�ʱ��״̬���
 *
 * \param[in] p_hw_tim   : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] status_flg : ��ʱ�����״̬���ѡ��, ֵΪ  amhw_stm32f103rbt6_tim_status_flag_t ��һö������
 *
 * \return amhw_stm32f103rbt6_tim_status_flag_t ��һö�����͵�ֵ(���Է��ػ����)
 */
am_static_inline
uint32_t amhw_stm32f103rbt6_tim_status_flg_get (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                      uint32_t           status_flg)
{
    return (p_hw_tim->sr & status_flg);
}

/**
 * \brief �����ʱ����ر�־
 *
 * \param[in] p_hw_tim   : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] status_flg : ��ʱ�����״̬���ѡ��, ֵΪ  amhw_stm32f103rbt6_tim_status_flag_t ��һö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_status_flg_clr (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                  uint32_t           status_flg)
{
    p_hw_tim->sr = ~status_flg;
}

/**
 * \brief ��ʱ������¼�����ö������
 */
typedef enum amhw_stm32f103rbt6_tim_egr {
    AMHW_STM32F103RBT6_TIM_UG     = (1UL << 0),  /**< \brief �����¼����� */
    AMHW_STM32F103RBT6_TIM_CC1G   = (1UL << 1),  /**< \brief ����/�Ƚ� 1�¼����� */
    AMHW_STM32F103RBT6_TIM_CC2G   = (1UL << 2),  /**< \brief ����/�Ƚ� 2�¼����� */
    AMHW_STM32F103RBT6_TIM_CC3G   = (1UL << 3),  /**< \brief ����/�Ƚ� 3�¼����� */
    AMHW_STM32F103RBT6_TIM_CC4G   = (1UL << 4),  /**< \brief ����/�Ƚ� 4�¼����� */
    AMHW_STM32F103RBT6_TIM_COMG   = (1UL << 5),  /**< \brief COM�¼����� */
    AMHW_STM32F103RBT6_TIM_TG     = (1UL << 6),  /**< \brief �����¼����� */
    AMHW_STM32F103RBT6_TIM_BG     = (1UL << 7),  /**< \brief ɲ���¼����� */
} amhw_stm32f103rbt6_tim_egr_t;

/**
 * \brief ��ʱ������¼���������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] egr_opt  : ��ʱ������¼�����ѡ��, ֵΪ  amhw_stm32f103rbt6_tim_egr_t ��һö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_egr_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t egr_opt)
{
    p_hw_tim->egr |= egr_opt;
}

/**
 * \brief ��������������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] utg_opt  : ����������ѡ��, ��������ʱ��Ϊ
 *
 *                       0 �� 15875nS��������ʱ��Ϊ 125nS��
 *                       6uS �� 31750nS��������ʱ��Ϊ 250nS��
 *                       32uS �� 63uS��������ʱ��Ϊ 1uS��
 *                       64uS �� 126uS��������ʱ��Ϊ 2 uS��
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_utg_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t utg_opt)
{
    AM_BITS_SET(p_hw_tim->bdtr, 0, 7, utg_opt);
}

/**
 * \brief ��������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] lock_opt : ����ѡ��
 *                       0: �����رգ��Ĵ�����д������
 *                       1: �������� 1������д�� TIMx_BDTR�Ĵ����� DTG�� BKE�� BKP�� AOEλ��
 *                          TIMx_CR2�Ĵ����� OISx/OISxN λ��
 *                       2: �������� 2������д���������� 1�еĸ�λ��Ҳ����д�� CC ����λ��һ�����ͨ��
 *                          ͨ����CCxSλ��Ϊ�����CC����λ�� TIMx_CCER�Ĵ����� CCxP/CCNxPλ����
 *                          ��OSSR/OSSI λ��
 *                       3:�������� 3������д���������� 2�еĸ�λ��Ҳ����д��CC����λ��һ�����ͨ��ͨ
 *                         ��  CCxSλ��Ϊ�����CC����λ�� TIMx_CCMRx �Ĵ����� OCxM/OCxPEλ����
 *
 * \note����ϵͳ��λ��ֻ��дһ�� LOCKλ��һ��д��TIMx_BDTR�Ĵ������������ݶ���ֱ����λ��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_lock_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t lock_opt)
{
    AM_BITS_SET(p_hw_tim->bdtr, 8, 2, lock_opt);
}

/**
 * \brief ����ģʽ�¡��ر�״̬������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ossi_opt : ����ģʽ�¡��ر�״̬��ѡ��
 *                       0: ����ʱ��������ʱ����ֹOC/OCN�����OC/OCNʹ������ź�  = 0��
 *                       1: ����ʱ��������ʱ��һ�� CCxE = 1 �� CCxNE = 1�����ȿ��� OC/OCN �������Ч
 *                              ��ƽ��Ȼ���� OC/OCN ʹ������ź�  = 1��
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ossi_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t ossi_opt)
{
    AM_BIT_MODIFY(p_hw_tim->bdtr, 10, ossi_opt);
}

/**
 * \brief ����ģʽ�¡��ر�״̬������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ossr_opt : ����ģʽ�¡��ر�״̬��ѡ��
 *                       0: ����ʱ��������ʱ����ֹOC/OCN�����OC/OCNʹ������ź�  = 0��
 *                       1: ����ʱ��������ʱ��һ�� CCxE = 1 �� CCxNE = 1�����ȿ��� OC/OCN �������Ч
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ossr_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t ossr_opt)
{
    AM_BIT_MODIFY(p_hw_tim->bdtr, 11, ossr_opt);
}

/**
 * \brief ��ʱ������ʹ������ö��
 */
typedef enum amhw_stm32f103rbt6_tim_bdtr_en {
    AMHW_STM32F103RBT6_TIM_MOE   = (1UL << 15),  /**< \brief �����ʹ�� */
    AMHW_STM32F103RBT6_TIM_AOE   = (1UL << 14),  /**< \brief �Զ����ʹ�� */
    AMHW_STM32F103RBT6_TIM_BKE   = (1UL << 12),  /**< \brief ɲ������ʹ�� */
} amhw_stm32f103rbt6_tim_bdtr_en_t;

/**
 * \brief ��ʱ�����������������ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] bdtr_opt : ��ʱ�����������������ʹ��ѡ��, ֵΪ  amhw_stm32f103rbt6_tim_bdtr_en_t ��һö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_bdtr_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                               uint32_t           bdtr_opt)
{
    p_hw_tim->bdtr |= bdtr_opt;
}

/**
 * \brief ��ʱ����������������ͽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] bdtr_opt : ��ʱ����������������ͽ���ѡ��, ֵΪ  amhw_stm32f103rbt6_tim_bdtr_en_t ��һö������
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_bdtr_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                uint32_t           bdtr_opt)
{
    p_hw_tim->bdtr &= ~bdtr_opt;
}

/**
 * \brief ɲ�����뼫������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] bkp_opt  : ɲ�����뼫��ѡ��, 0: ɲ������͵�ƽ��Ч; 1: ɲ������ߵ�ƽ��Ч
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_bkp_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t bkp_opt)
{
    AM_BIT_MODIFY(p_hw_tim->bdtr, 13, bkp_opt);
}

/**
 * \brief ��ʱ��DMA����ַ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] dba_opt  : ��ʱ��DMA����ַѡ��, ֵΪ0 ~ 31
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_dba_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t dba_opt)
{
    AM_BITS_SET(p_hw_tim->dcr, 0, 5, dba_opt);
}

/**
 * \brief ��ʱ��DMA �������ͳ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] dbl_opt  : DMA �������ͳ���ѡ��, ֵΪ0 ~ 31
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_dbl_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t dbl_opt)
{
    AM_BITS_SET(p_hw_tim->dcr, 8, 5, dbl_opt);
}

/**
 * \brief ��ʱ��DMA����ģʽ�Ļ���ַ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] dmab_opt : ��ʱ��DMA����ģʽ�Ļ���ַѡ��, ֵΪ0 ~ 65536
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_dmab_set (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint16_t dmab_opt)
{
    p_hw_tim->dcr = dmab_opt;
}

/**
 * \brief ��ʱ�����벶��/�Ƚ����ͨ��ö������
 */
typedef enum amhw_stm32f103rbt6_tim_ccs_chan {
    AMHW_STM32F103RBT6_TIM_CC1S   = 0,  /**< \brief CC1S */
    AMHW_STM32F103RBT6_TIM_CC2S   = 1,  /**< \brief CC2S */
    AMHW_STM32F103RBT6_TIM_CC3S   = 2,  /**< \brief CC3S */
    AMHW_STM32F103RBT6_TIM_CC4S   = 3,  /**< \brief CC4S */

} amhw_stm32f103rbt6_tim_ccs_chan_t;

/**
 * \brief ����/�Ƚ�ccsͨ������
 *
 * \param[in] p_hw_tim  : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccs_opt   : ����/�Ƚ�ccs ͨ��ѡ��
 *                        0: CC*ͨ��������Ϊ���
 *                        1: CC*ͨ��������Ϊ���룬IC1 ӳ���� TI1��
 *                        2: CC*ͨ��������Ϊ���룬IC2 ӳ���� TI1��
 *                        3: CC*ͨ��������Ϊ���룬IC* ӳ���� TRC��
 *
 * \note :  When ccs_opt is 1, TIM Input 1, 2, 3 or 4 is selected to be
 *          connected  to IC1, IC2, IC3 or IC4, respectively
 *
 * \note :  When ccs_opt is 2, TIM Input 1, 2, 3 or 4 is selected to be
 *          connected  to IC2, IC1, IC4 or IC3, respectively
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \note : CC*S ����ͨ���ر�ʱ��TIMx_CCER �Ĵ����� CC*E = 0�����ǿ�д��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccs_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                           uint8_t            ccs_opt,
                           uint32_t           ccs_chan)
{
    AM_BITS_SET(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01)) , 2, ccs_opt);
}

/*******************************************************************************
                   ���º�������ccmr�Ĵ�������cc*sλ����Ϊ ����Ƚ�ģʽʱ������
*******************************************************************************/

/**
 * \brief ͨ������ȽϿ���ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccs_ocfe_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                   uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 2), 1);
}

/**
 * \brief ͨ������ȽϿ��ٽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccs_ocfe_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                    uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 2), 0);
}

/**
 * \brief ͨ������Ƚ�Ԥװ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccs_ocpe_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                   uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 3), 1);
}

/**
 * \brief ͨ������Ƚ�Ԥװ�ؽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccs_ocpe_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                    uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 3), 0);
}

/**
 * \brief ͨ������Ƚ���0ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccs_occe_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                   uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 7), 1);
}

/**
 * \brief ͨ������Ƚ���0����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccs_occe_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                    uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 7), 0);
}

/**
 * \brief ��ʱ������Ƚ�ö������
 */
typedef enum amhw_stm32f103rbt6_tim_output_cmp_mode {
    AMHW_STM32F103RBT6_TIM_FROZEN                   = 0,  /**< \brief ���� */
    AMHW_STM32F103RBT6_TIM_MATCH_CHANNAL_SETACTIVE  = 1,  /**< \brief ƥ��ʱ����ͨ��Ϊ��Ч��ƽ */
    AMHW_STM32F103RBT6_TIM_MATCH_CHANNAL_SETINACTIV = 2,  /**< \brief ƥ��ʱ����ͨ�� Ϊ��Ч��ƽ */
    AMHW_STM32F103RBT6_TIM_TOGGLE                   = 3,  /**< \brief ��ת */
    AMHW_STM32F103RBT6_TIM_FORCE_INACTIVE_LEVEL     = 4,  /**< \brief ǿ��Ϊ��Ч��ƽ */
    AMHW_STM32F103RBT6_TIM_FORCE_ACTIVE_LEVEL       = 5,  /**< \brief ǿ��Ϊ��Ч��ƽ */
    AMHW_STM32F103RBT6_TIM_PWM_MODE1                = 6,  /**< \brief PWMģʽ1 */
    AMHW_STM32F103RBT6_TIM_PWM_MODE2                = 7,  /**< \brief PWMģʽ2 */
} amhw_stm32f103rbt6_tim_output_cmp_mode_t;

/**
 * \brief ͨ������Ƚ�ģʽ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ocm_opt  : ����Ƚ�ģʽѡ��, ֵΪ amhw_stm32f103rbt6_tim_output_cmp_mode_t ��һö������
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \note : 1. OC*M һ�� LOCK ������Ϊ 3 ��TIMx_BDTR �Ĵ����е� LOCK λ������ CC*S = 00 ����
 *           ͨ�����ó���������λ���ܱ��޸�
 *         2. �� PWM ģʽ 1 �� PWM ģʽ 2 �У�ֻ�е��ȽϽ���ı��˻�������Ƚ�ģʽ�д�
 *           ����ģʽ�л��� PWM ģʽʱ��OC*REF ��ƽ�Ÿı�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ocm_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                           uint8_t            ocm_opt,
                           uint8_t            ccs_chan)
{
    AM_BITS_SET(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 4) , 3, ocm_opt);
}

/**
 * \brief ͨ���Ƚ������ƽ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccp_opt  : ͨ���Ƚ������ƽ����ѡ��, 0: OC1�ߵ�ƽ��Ч; 1: OC1�͵�ƽ��Ч
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccp_output_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                  uint8_t            ccp_opt,
                                  uint32_t           ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan + 1), ccp_opt);
}

/**
 * \brief �Ƚ����ͨ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_cce_output_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                     uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan ), 1);
}

/**
 * \brief �Ƚ����ͨ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_cce_output_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                      uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan ), 0);
}

/**
 * \brief ��ȡ���ñȽ����ͨ����Ԥװ��ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ch       : ƥ��ͨ�����  ��Чֵ0-3
 *
 * \note:  ͨ�ö�ʱ��TIM2��TIM3�üĴ���Ϊ32λ������Ϊ16λ

 * \return �Ƚ����ͨ����Ԥװ�ص�ֵ
 */
am_static_inline
uint32_t amhw_stm32f103rbt6_tim_ouput_reload_val_get (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                            uint8_t            ch)
{
    return p_hw_tim->ccr[ch];
}

/**
 * \brief ���ñȽ����ͨ����Ԥװ��ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : �Ƚ����ͨ����Ԥװ��ֵ
 * \param[in] ch       : ����ͨ������Чֵ0-3
 *
 *\ note:  ͨ�ö�ʱ��TIM2��TIM3�üĴ���Ϊ32λ������Ϊ16λ
 *
 * \return ָ������ͨ���Ĳ���ֵ
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccr_ouput_reload_val_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                            uint32_t           value,
                                            uint8_t            ch)
{
    p_hw_tim->ccr[ch] = value;
}

/*******************************************************************************
                   ���º�������ccmr�Ĵ�������cc*sλ����Ϊ����Ƚ�ģʽʱ������
*******************************************************************************/

/**
 * \brief ͨ������/����Ԥ��Ƶ��
 *
 * \param[in] p_hw_tim  : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] icpsc_opt : ����/�Ƚ� ��Ƶѡ��
 *                        0: �޷�Ƶ;              1: ÿ 2���¼�����һ�β���
 *                        2: ÿ 4���¼�����һ�β���;   3: ÿ 8���¼�����һ�β���
 *
 * \param[in] ccs_chan  : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_icpsc_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                             uint8_t            icpsc_opt,
                             uint8_t            ccs_chan)
{
    AM_BITS_SET(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 2) , 2, icpsc_opt);
}

/**
 * \brief ͨ�����벶������˲�ѡ��ö������
 */
typedef enum amhw_stm32f103rbt6_tim_icf {
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING0   = 0x00,  /**< \brief ���˲��� */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING1   = 0x08,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/8��N = 6 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING2   = 0x01,  /**< \brief ����Ƶ�� fSAMPLING = fCK_INT��N = 2 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING3   = 0x09,  /**< \brief ����Ƶ�� fSAMPLING = fCK_INT��N = 4 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING4   = 0x02,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/16��N = 5 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING5   = 0x0A,  /**< \brief ����Ƶ�� fSAMPLING = fCK_INT��N = 8 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING6   = 0x03,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/16��N = 6 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING7   = 0x0B,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/2��N = 6 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING8   = 0x04,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/16��N = 8 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING9   = 0x0C,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/2��N = 8 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING10  = 0x05,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/16��N = 5 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING11  = 0x0D,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/4��N = 6 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING12  = 0x06,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/32��N = 6 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING13  = 0x0E,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/4��N = 8 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING14  = 0x07,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/4��N = 8 */
    AMHW_STM32F103RBT6_TIM_ICF_FSAMPLING15  = 0x0F,  /**< \brief ����Ƶ�� fSAMPLING = fDTS/32��N = 8 */
} amhw_stm32f103rbt6_tim_icf_t;

/**
 * \brief ͨ�����벶������˲�Ƶ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] icf_opt  : ���벶������˲�Ƶ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_icf_t ��һö������
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_icf_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                           uint8_t            icf_opt,
                           uint8_t            ccs_chan)
{
    AM_BITS_SET(p_hw_tim->ccmr[ccs_chan >> 1], (8 * (ccs_chan & 0x01) + 4) , 4, icf_opt);
}

/**
 * \brief ���벶��(�ⲿ����)��ƽ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] type     : ��ʱ������
 * \param[in] ccp_opt  : ���벶��ͨ����ƽ����ѡ��
 *                       1: �����ࣺ�������� ICx �������أ��������ⲿ������ʱ��ICx������;
 *                       2: ���ࣺ�������� ICx ���½��أ��������ⲿ������ʱ�� ICx����
 *                       ���� x������ͨ�������ݶ�ʱ���Ĳ�ͬ��ͨ������Ҳ������ͬ�����Ϊ4��ͨ��
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \note : һ�� LOCK ����TIMx_BDTR �Ĵ����е� LCCK λ����Ϊ 3 �� 2�����λ���ܱ��޸�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccp_captrigger_set (amhw_stm32f103rbt6_tim_t        *p_hw_tim,
                                      amhw_stm32f103rbt6_tim_type_t    type,
                                      uint8_t                ccp_opt,
                                      uint8_t                ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan + 1), ccp_opt >> 1);
}

/**
 * \brief ���벶��ͨ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_cce_cap_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                  uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan), 1);
}

/**
 * \brief ���벶��/�Ƚ�ͨ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_cce_cap_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                   uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan), 0);
}

/**
 * \brief ���벶�񻥲��������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccnp_opt : ���벶�񻥲��������ѡ��
 *                       0: OCN�ߵ�ƽ��Ч;
 *                       1: OCN�͵�ƽ��Ч;
 *
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \note : һ�� LOCK ����TIMx_BDTR �Ĵ����е� LCCK λ����Ϊ 3 �� 2�����λ���ܱ��޸�
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccne_set (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                            uint8_t            ccnp_opt,
                            uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan + 3), ccnp_opt);
}

/**
 * \brief ���벶�񻥲����ͨ��ʹ��
 *
 * \param[in] p_hw_tim :    ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccs_chan :  ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccne_enable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                               uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan + 2), 1);
}

/**
 * \brief ���벶�񻥲����ͨ������
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ccs_chan : ccsͨ��ѡ��ֵΪ amhw_stm32f103rbt6_tim_ccs_chan_t ��һ���͵�ö��
 *
 * \return ��
 */
am_static_inline
void amhw_stm32f103rbt6_tim_ccne_cap_disable (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                    uint8_t            ccs_chan)
{
    AM_BIT_MODIFY(p_hw_tim->ccer, (4 * ccs_chan + 2), 0);
}

/**
 * \brief ��һ������ͨ����ȡ����ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] ch       : ����ͨ������Чֵ0-3
 *
 * \return ����ָ������ͨ���Ĳ���ֵ
 */
am_static_inline
uint32_t amhw_stm32f103rbt6_tim_ccr_cap_val_get (amhw_stm32f103rbt6_tim_t    *p_hw_tim,
                                       uint8_t            ch)
{
    return p_hw_tim->ccr[ch];
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_STM32F103RBT6_TIM_H */

/* end of file */
