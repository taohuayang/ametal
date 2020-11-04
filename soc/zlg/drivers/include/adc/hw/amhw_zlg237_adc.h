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
 * \brief ADC Peripheral Access Layer
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-12  ari, first implementation
 *
 * \endinternal
 */

#ifndef __AMHW_ZLG237_ADC_H
#define __AMHW_ZLG237_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zlg237_if_adc
 * \copydoc amhw_zlg237_adc.h
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
 * \brief ADC - Register Layout Typedef
 */
typedef struct amhw_zlg237_adc {
    __IO uint32_t sr;        /**< \brief ״̬�Ĵ��� */
    __IO uint32_t cr1;       /**< \brief ���ƼĴ���1 */
    __IO uint32_t cr2;       /**< \brief ���ƼĴ���2 */
    __IO uint32_t smpr[2];   /**< \brief ����ʱ��Ĵ���1��2 */
    __IO uint32_t jofr[4];   /**< \brief ע��ͨ������ƫ�ƼĴ���1��2��3��4 */
    __IO uint32_t htr;       /**< \brief ���Ź�����ֵ�Ĵ��� */
    __IO uint32_t ltr;       /**< \brief ���Ź�����ֵ�Ĵ��� */
    __IO uint32_t sqr[3];    /**< \brief �������мĴ���1��2��3 */
    __IO uint32_t jsqr;      /**< \brief ע�����мĴ��� */
    __I  uint32_t jdr[4];    /**< \brief ע�����ݼĴ���1��2��3��4 */
    __I  uint32_t dr;        /**< \brief �������ݼĴ��� */
} amhw_zlg237_adc_t;


/**
 * \brief ADC ״̬�Ĵ�������λ
 * \@{
 */
#define AMHW_ZLG237_ADC_DATA_VALID_12BIT          12    /* 12bit��ЧADC���� */

/**
 * \brief ADC ���ݶ��뷽ʽ
 * \@{
 */
#define AMHW_ZLG237_ADC_DATA_RIGHT                0     /**< \brief �����Ҷ��� */
#define AMHW_ZLG237_ADC_DATA_LEFT                 1     /**< \brief ��������� */
/** @}*/

/**
 * \brief ADC ���Ρ�����ת������
 * \@{
 */
#define AMHW_ZLG237_ADC_CONVERSION_SINGLE         0     /**< \brief ����ת�� */
#define AMHW_ZLG237_ADC_CONVERSION_CONTINUOUS     1     /**< \brief ����ת�� */
/** @}*/

/**
 * \brief ADC ״̬�Ĵ�������λ
 * \@{
 */
#define AMHW_ZLG237_ADC_REGULAR_CHAN_STRT_FLAG       (1ul << 4)  /**< \brief ����ͨ��ת����ʼ��־ */
#define AMHW_ZLG237_ADC_INJECTED_CHAN_STRT_FLAG      (1ul << 3)  /**< \brief ע��ͨ��ת����ʼ��־ */
#define AMHW_ZLG237_ADC_INJECTED_CHAN_END_FLAG       (1ul << 2)  /**< \brief ע��ͨ��ת��������־ */
#define AMHW_ZLG237_ADC_END_FLAG                     (1ul << 1)  /**< \brief ת��������־ */
#define AMHW_ZLG237_ADC_ANALOG_WDOG_FLAG             (1ul << 0)  /**< \brief ģ�⿴�Ź��¼���־ */
#define AMHW_ZLG237_ADC_ALL_FLAG                  (0x1ful << 0)  /**< \brief ģ�⿴�Ź��¼���־ */
/** @}*/

/**
 * \brief ADC ģ�⿴�Ź�����ѡ��
 * \@{
 */
#define AMHW_ZLG237_ADC_AWDG_NONE_CHAN            0     /**< \brief ������ģ�⿴�Ź� */
#define AMHW_ZLG237_ADC_AWDG_INJECTED_CHAN        1     /**< \brief ����ע��ͨ���ϵ�ģ�⿴�Ź� */
#define AMHW_ZLG237_ADC_AWDG_REGULAR_CHAN         2     /**< \brief ��������ͨ���ϵ�ģ�⿴�Ź� */
#define AMHW_ZLG237_ADC_AWDG_ALL_CHAN             3     /**< \brief ͬʱ����ע��ͨ��������ͨ���ϵ�ģ�⿴�Ź� */
/** @}*/

/**
 * \brief ADC �ж�ʹ�ܿ���λ
 * \@{
 */
#define AMHW_ZLG237_ADC_INT_INJECTED_END          (0x1ul << 7)  /**< \brief ע��ͨ��ת�������ж� */
#define AMHW_ZLG237_ADC_INT_AWDG                  (0x1ul << 6)  /**< \brief ģ�⿴�Ź��ж� */
#define AMHW_ZLG237_ADC_INT_END                   (0x1ul << 5)  /**< \brief ת�������ж� */
#define AMHW_ZLG237_ADC_INT_ALL                   (0x7ul << 5)  /**< \brief ȫ���ж� */
/** @}*/

/**
 * \brief ADC ѡ����������ͨ����ת�����ⲿ�¼�
 * \@{
 */
/* ADC1/ADC2�������� */
#define AMHW_ZLG237_ADC12_REGULAR_TIM1_CC1                 0     /**< \brief ��ʱ��1��CC1�¼� */
#define AMHW_ZLG237_ADC12_REGULAR_TIM1_CC2                 1     /**< \brief ��ʱ��1��CC2�¼� */
#define AMHW_ZLG237_ADC12_REGULAR_TIM1_CC3                 2     /**< \brief ��ʱ��1��CC3�¼� */
#define AMHW_ZLG237_ADC12_REGULAR_TIM2_CC2                 3     /**< \brief ��ʱ��2��CC2�¼� */
#define AMHW_ZLG237_ADC12_REGULAR_TIM3_TRGO                4     /**< \brief ��ʱ��3��TRGO�¼� */
#define AMHW_ZLG237_ADC12_REGULAR_TIM4_CC4                 5     /**< \brief ��ʱ��4��CC4�¼� */
#define AMHW_ZLG237_ADC12_REGULAR_TIM8_TRGO_OR_EXTI11      6     /**< \brief EXTI�� 11/TIM8_TRGO�� �� */
#define AMHW_ZLG237_ADC12_REGULAR_SWSTART                  7     /**< \brief SWSTART */
/* ADC3�������� */
#define AMHW_ZLG237_ADC3_REGULAR_TIM3_CC1                  0     /**< \brief ��ʱ��3��CC1�¼� */
#define AMHW_ZLG237_ADC3_REGULAR_TIM2_CC3                  1     /**< \brief ��ʱ��3��CC1�¼� */
#define AMHW_ZLG237_ADC3_REGULAR_TIM1_CC3                  2     /**< \brief ��ʱ��1��CC3�¼� */
#define AMHW_ZLG237_ADC3_REGULAR_TIM8_CC1                  3     /**< \brief ��ʱ��8��CC1�¼� */
#define AMHW_ZLG237_ADC3_REGULAR_TIM8_TRGO                 4     /**< \brief ��ʱ��8��TRGO�¼� */
#define AMHW_ZLG237_ADC3_REGULAR_TIM5_CC1                  5     /**< \brief ��ʱ��5��CC1�¼� */
#define AMHW_ZLG237_ADC3_REGULAR_TIM5_CC3                  6     /**< \brief ��ʱ��5��CC3�¼� */
#define AMHW_ZLG237_ADC3_REGULAR_SWSTART                   7     /**< \brief SWSTART */
/** @}*/

/**
 * \brief ADC ѡ������ע��ͨ��ת�����ⲿ�¼�
 * \@{
 */
/* ADC1/ADC2�������� */
#define AMHW_ZLG237_ADC12_INJECTED_TIM1_TRGO               0     /**< \brief ��ʱ��1��TRGO�¼� */
#define AMHW_ZLG237_ADC12_INJECTED_TIM1_CC4                1     /**< \brief ��ʱ��1��CC4�¼� */
#define AMHW_ZLG237_ADC12_INJECTED_TIM2_TRGO               2     /**< \brief ��ʱ��2��TRGO�¼� */
#define AMHW_ZLG237_ADC12_INJECTED_TIM2_CC1                3     /**< \brief ��ʱ��2��CC1�¼� */
#define AMHW_ZLG237_ADC12_INJECTED_TIM3_CC4                4     /**< \brief ��ʱ��3��CC4�¼� */
#define AMHW_ZLG237_ADC12_INJECTED_TIM4_TRGO               5     /**< \brief ��ʱ��4��TRGO�¼� */
#define AMHW_ZLG237_ADC12_INJECTED_TIM8_CC4_OR_EXTI15      6     /**< \brief EXTI�� 15/TIM8_CC4�� �� */
#define AMHW_ZLG237_ADC12_INJECTED_JSWSTART                7     /**< \brief JSWSTART */
/* ADC3�������� */
#define AMHW_ZLG237_ADC3_INJECTED_TIM1_TRGO                0     /**< \brief ��ʱ��1��TRG�¼� */
#define AMHW_ZLG237_ADC3_INJECTED_TIM1_CC4                 1     /**< \brief ��ʱ��1��CC4�¼� */
#define AMHW_ZLG237_ADC3_INJECTED_TIM4_CC3                 2     /**< \brief ��ʱ��4��CC3�¼� */
#define AMHW_ZLG237_ADC3_INJECTED_TIM8_CC2                 3     /**< \brief ��ʱ��8��CC2�¼� */
#define AMHW_ZLG237_ADC3_INJECTED_TIM8_CC4                 4     /**< \brief ��ʱ��8��CC4�¼� */
#define AMHW_ZLG237_ADC3_INJECTED_TIM5_TRGO                5     /**< \brief ��ʱ��5��TRGO�¼� */
#define AMHW_ZLG237_ADC3_INJECTED_TIM5_CC4                 6     /**< \brief ��ʱ��5��CC4�¼� */
#define AMHW_ZLG237_ADC3_INJECTED_JSWSTART                 7     /**< \brief JSWSTART */
/** @}*/

/**
 * \brief ADC channel
 */
typedef enum amhw_zlg237_adc_channel {
    AMHW_ZLG237_ADC_CHAN_0 = 0,
    AMHW_ZLG237_ADC_CHAN_1,
    AMHW_ZLG237_ADC_CHAN_2,
    AMHW_ZLG237_ADC_CHAN_3,
    AMHW_ZLG237_ADC_CHAN_4,
    AMHW_ZLG237_ADC_CHAN_5,
    AMHW_ZLG237_ADC_CHAN_6,
    AMHW_ZLG237_ADC_CHAN_7,
    AMHW_ZLG237_ADC_CHAN_8,
    AMHW_ZLG237_ADC_CHAN_9,
    AMHW_ZLG237_ADC_CHAN_10,
    AMHW_ZLG237_ADC_CHAN_11,
    AMHW_ZLG237_ADC_CHAN_12,
    AMHW_ZLG237_ADC_CHAN_13,
    AMHW_ZLG237_ADC_CHAN_14,
    AMHW_ZLG237_ADC_CHAN_15,
    AMHW_ZLG237_ADC_CHAN_16,
    AMHW_ZLG237_ADC_CHAN_17,
} amhw_zlg237_adc_channel_t;

/**
 * \brief ADC ˫ģʽѡ��
 */
typedef enum amhw_zlg237_adc_dul_mode {
    AMHW_ZLG237_ADC_DUL_MODE_0 = 0,    /**< \brief ����ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_1,        /**< \brief ��ϵ�ͬ������+ע��ͬ��ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_2,        /**< \brief ��ϵ�ͬ������+���津��ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_3,        /**< \brief ���ͬ��ע��+���ٽ���ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_4,        /**< \brief ���ͬ��ע��+���ٽ���ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_5,        /**< \brief ע��ͬ��ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_6,        /**< \brief ����ͬ��ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_7,        /**< \brief ���ٽ���ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_8,        /**< \brief ���ٽ���ģʽ */
    AMHW_ZLG237_ADC_DUL_MODE_9,        /**< \brief ���津��ģʽ�� */
} amhw_zlg237_adc_dul_mode_t;

/**
 * \brief ADC���ģʽͨ������
 */
typedef enum amhw_zlg237_adc_disc_num {
    AMHW_ZLG237_ADC_DISC_NUM_1 = 0,    /**< \brief 1��ͨ�� */
    AMHW_ZLG237_ADC_DISC_NUM_2,        /**< \brief 2��ͨ�� */
    AMHW_ZLG237_ADC_DISC_NUM_3,        /**< \brief 3��ͨ�� */
    AMHW_ZLG237_ADC_DISC_NUM_4,        /**< \brief 4��ͨ�� */
    AMHW_ZLG237_ADC_DISC_NUM_5,        /**< \brief 5��ͨ�� */
    AMHW_ZLG237_ADC_DISC_NUM_6,        /**< \brief 6��ͨ�� */
    AMHW_ZLG237_ADC_DISC_NUM_7,        /**< \brief 7��ͨ�� */
    AMHW_ZLG237_ADC_DISC_NUM_8,        /**< \brief 8��ͨ�� */
} amhw_zlg237_adc_disc_num_t;

/**
 * \brief ADC ģ�⿴�Ź�ͨ��ѡ��λ
 */
typedef enum amhw_zlg237_adc_awdg_channel {
    AMHW_ZLG237_ADC_AWDG_CHAN_0 = 0,        /**< \brief ADCģ������ͨ�� 0 */
    AMHW_ZLG237_ADC_AWDG_CHAN_1,            /**< \brief ADCģ������ͨ�� 1 */
    AMHW_ZLG237_ADC_AWDG_CHAN_2,            /**< \brief ADCģ������ͨ�� 2 */
    AMHW_ZLG237_ADC_AWDG_CHAN_3,            /**< \brief ADCģ������ͨ�� 3 */
    AMHW_ZLG237_ADC_AWDG_CHAN_4,            /**< \brief ADCģ������ͨ�� 4 */
    AMHW_ZLG237_ADC_AWDG_CHAN_5,            /**< \brief ADCģ������ͨ�� 5 */
    AMHW_ZLG237_ADC_AWDG_CHAN_6,            /**< \brief ADCģ������ͨ�� 6 */
    AMHW_ZLG237_ADC_AWDG_CHAN_7,            /**< \brief ADCģ������ͨ�� 7 */
    AMHW_ZLG237_ADC_AWDG_CHAN_8,            /**< \brief ADCģ������ͨ�� 8 */
    AMHW_ZLG237_ADC_AWDG_CHAN_9,            /**< \brief ADCģ������ͨ�� 9 */
    AMHW_ZLG237_ADC_AWDG_CHAN_10,           /**< \brief ADCģ������ͨ�� 10 */
    AMHW_ZLG237_ADC_AWDG_CHAN_11,           /**< \brief ADCģ������ͨ�� 11 */
    AMHW_ZLG237_ADC_AWDG_CHAN_12,           /**< \brief ADCģ������ͨ�� 12 */
    AMHW_ZLG237_ADC_AWDG_CHAN_13,           /**< \brief ADCģ������ͨ�� 13 */
    AMHW_ZLG237_ADC_AWDG_CHAN_14,           /**< \brief ADCģ������ͨ�� 14 */
    AMHW_ZLG237_ADC_AWDG_CHAN_15,           /**< \brief ADCģ������ͨ�� 15 */
    AMHW_ZLG237_ADC_AWDG_CHAN_16,           /**< \brief ADCģ������ͨ�� 16 */
    AMHW_ZLG237_ADC_AWDG_CHAN_17,           /**< \brief ADCģ������ͨ�� 17 */
} amhw_zlg237_adc_awdg_channel_t;

/**
 * \brief ADC sample time
 */
typedef enum amhw_zlg237_adc_sample_time {
    AMHW_ZLG237_ADC_CHAN_ST1_5 = 0,
    AMHW_ZLG237_ADC_CHAN_ST7_5,
    AMHW_ZLG237_ADC_CHAN_ST13_5,
    AMHW_ZLG237_ADC_CHAN_ST28_5,
    AMHW_ZLG237_ADC_CHAN_ST41_5,
    AMHW_ZLG237_ADC_CHAN_ST55_5,
    AMHW_ZLG237_ADC_CHAN_ST71_5,
    AMHW_ZLG237_ADC_CHAN_ST239_5,
} amhw_zlg237_adc_sample_time_t;

/**
 * \brief ADC ע��ͨ������ƫ���趨��1��2��3��4��
 */
typedef enum amhw_zlg237_adc_injected_data_channel {
    AMHW_ZLG237_ADC_INJECTED_DATA_CHAN_1 = 0,
    AMHW_ZLG237_ADC_INJECTED_DATA_CHAN_2,
    AMHW_ZLG237_ADC_INJECTED_DATA_CHAN_3,
    AMHW_ZLG237_ADC_INJECTED_DATA_CHAN_4,
} amhw_zlg237_adc_injected_data_channel_t;

/**
 * \brief ADC ����ͨ�����г���
 */
typedef enum amhw_zlg237_adc_regular_channel_length {
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_1 = 0,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_2 = 1,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_3,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_4,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_5,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_6,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_7,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_8,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_9,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_10,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_11,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_12,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_13,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_14,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_15,
    AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_16,
} amhw_zlg237_adc_regular_channel_length_t;

/**
 * \brief ADC Regular channel sequence �������ã��磬3ͨ���������д��ڵ�4������ת����
 */
typedef enum amhw_zlg237_adc_regular_channel_order {
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_1st = 0,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_2nd = 1,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_3rd,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_4th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_5th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_6th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_7th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_8th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_9th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_10th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_11th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_12th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_13th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_14th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_15th,
    AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_16th,
} amhw_zlg237_adc_regular_channel_order_t;

/**
 * \brief ADC ע��ͨ�����г���
 */
typedef enum amhw_zlg237_adc_injected_channel_length {
    AMHW_ZLG237_ADC_INJECTED_CHAN_LENGTH_1 = 0,
    AMHW_ZLG237_ADC_INJECTED_CHAN_LENGTH_2,
    AMHW_ZLG237_ADC_INJECTED_CHAN_LENGTH_3,
    AMHW_ZLG237_ADC_INJECTED_CHAN_LENGTH_4,
} amhw_zlg237_adc_injected_channel_length_t;

/**
 * \brief ADC Regular channel sequence �������ã��磬3ͨ���������д��ڵ�4������ת����
 */
typedef enum amhw_zlg237_adc_injected_channel_order {
    AMHW_ZLG237_ADC_INJECTED_CHAN_ORDER_1st = 0,
    AMHW_ZLG237_ADC_INJECTED_CHAN_ORDER_2nd,
    AMHW_ZLG237_ADC_INJECTED_CHAN_ORDER_3rd,
    AMHW_ZLG237_ADC_INJECTED_CHAN_ORDER_4th,
} amhw_zlg237_adc_injected_channel_order_t;


/**
 * \brief ״̬�Ĵ�����־λ��ȡ
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC_REGULAR_CHAN_STRT_FLAG    ��
 *                            AMHW_ZLG237_ADC_INJECTED_CHAN_STRT_FLAG   ��
 *                            AMHW_ZLG237_ADC_INJECTED_CHAN_END_FLAG    ��
 *                            AMHW_ZLG237_ADC_END_FLAG                  ��
 *                            AMHW_ZLG237_ADC_ANALOG_WDOG_FLAG
 *
 * \return none
 */
am_static_inline
am_bool_t amhw_zlg237_adc_status_flag_check (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    return (p_hw_adc->sr & (uint32_t)flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ״̬�Ĵ�����־λ���
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC_REGULAR_CHAN_STRT_FLAG    ��
 *                             AMHW_ZLG237_ADC_INJECTED_CHAN_STRT_FLAG   ��
 *                             AMHW_ZLG237_ADC_INJECTED_CHAN_END_FLAG    ��
 *                             AMHW_ZLG237_ADC_END_FLAG                  ��
 *                             AMHW_ZLG237_ADC_ANALOG_WDOG_FLAG
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_status_flag_clr (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->sr &= ~((uint32_t)flag);
}


/**
 * \brief ģ�⿴�Ź�����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC_AWDG_NONE_CHAN       ��
 *                             AMHW_ZLG237_ADC_AWDG_INJECTED_CHAN   ��
 *                             AMHW_ZLG237_ADC_AWDG_REGULAR_CHAN    ��
                               AMHW_ZLG237_ADC_AWDG_REGULAR_CHAN
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_awdg_set (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->cr1 = (p_hw_adc->cr1 & (~(0x3ul << 22))) | (flag << 22);
}

/**
 * \brief ADC˫ģʽѡ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag     : �������ӦΪ   amhw_zlg237_adc_dul_mode_t �е�ö�ٱ���
 *
 *    \note : �� ADC2 �� ADC3 ����ЩλΪ����λ��
 *
 *                            ��˫ģʽ�У��ı�ͨ�������û����һ�����¿�ʼ���������⽫����ͬ����ʧ��
 *                            �����ڽ����κ����øı�ǰ�ر�˫ģʽ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_dul_mode_set (amhw_zlg237_adc_t *p_hw_adc, amhw_zlg237_adc_dul_mode_t flag)
{
    p_hw_adc->cr1 = (p_hw_adc->cr1 & (~(0xful << 16))) | ((uint32_t)flag << 16);
}



/**
 * \brief ADC���ģʽͨ����������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag     : �������ӦΪ   amhw_zlg237_adc_disc_num_t �е�ö�ٱ���
 *
 *    \note : ���ͨ����Щλ�����ڼ��ģʽ�£��յ��ⲿ������ת������ͨ������Ŀ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_disc_num_set (amhw_zlg237_adc_t *p_hw_adc, amhw_zlg237_adc_disc_num_t flag)
{
    p_hw_adc->cr1 = (p_hw_adc->cr1 & (~(0x7ul << 13))) | ((uint32_t)flag << 13);
}

/**
 * \brief JDISCEN ��ע��ͨ���ϵļ��ģʽ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_injected_disc_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 &= ~(1ul << 12);
}

/**
 * \brief JDISCEN ��ע��ͨ���ϵļ��ģʽʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_injected_disc_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 |= (1ul << 12);
}

/**
 * \brief DISCEN �ڹ���ͨ���ϵļ��ģʽ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_regular_disc_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 &= ~(1ul << 11);
}

/**
 * \brief DISCEN �ڹ���ͨ���ϵļ��ģʽʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_regular_disc_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 |= (1ul << 11);
}

/**
 * \brief JAUTO �Զ�ע��ͨ����ת������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ�����رչ���ͨ����ת���������Զ���ע��ͨ����ת��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jauto_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 &= ~(1ul << 10);
}

/**
 * \brief JAUTO �Զ�ע��ͨ����ת��ʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ�����رչ���ͨ����ת���������Զ���ע��ͨ����ת��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jauto_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 |= (1ul << 10);
}

/**
 * \brief AWDSGL ɨ��ģʽ����һ����һ��ͨ���Ͽ��Ź�����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ�����ر��� AWDCH[4:0]λָ����ͨ���ϵ�ģ�⿴�Ź�����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_awdg_single_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 &= ~(1ul << 9);
}

/**
 * \brief AWDSGL ɨ��ģʽ����һ����һ��ͨ���Ͽ��Ź�ʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ�����ر��� AWDCH[4:0]λָ����ͨ���ϵ�ģ�⿴�Ź�����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_awdg_single_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 |= (1ul << 9);
}

/**
 * \brief ɨ��ģʽ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��ɨ��ģʽ�У�ת���� ADC_SQRx�� ADC_JSQRx�Ĵ���ѡ�е�ͨ��.
 *
 *         ����ֱ������� EOCIE�� JEOCIEλ��ֻ�����һ��ͨ��ת����Ϻ�Ż���� EOC�� JEOC�жϡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_scan_mode_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 &= ~(1ul << 8);
}

/**
 * \brief ɨ��ģʽʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��ɨ��ģʽ�У�ת���� ADC_SQRx�� ADC_JSQRx�Ĵ���ѡ�е�ͨ��.
 *
 *         ����ֱ������� EOCIE�� JEOCIEλ��ֻ�����һ��ͨ��ת����Ϻ�Ż���� EOC�� JEOC�жϡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_scan_mode_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr1 |= (1ul << 8);
}

/**
 * \brief ADC�жϽ���
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC_INT_INJECTED_EOC    ��
 *                             AMHW_ZLG237_ADC_INT_AWDG            ��
 *                             AMHW_ZLG237_ADC_INT_EOC
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_int_disable (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->cr1 &= ~flag;
}

/**
 * \brief ADC�ж�ʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC_INT_INJECTED_EOC    ��
 *                            AMHW_ZLG237_ADC_INT_AWDG            ��
 *                            AMHW_ZLG237_ADC_INT_EOC
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_int_enable (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->cr1 |= flag;
}



/**
 * \brief AWDCH[4:0] ADCģ�⿴�Ź�ͨ��ѡ��λ
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   amhw_zlg237_adc_awdg_channel_t �е�ö�ٱ���
 *
 * \note : ����ѡ��ģ�⿴�Ź�����������ͨ��.
 *
 *         ADC1��ģ������ͨ�� 16��ͨ�� 17��оƬ�ڲ��ֱ��������¶ȴ������� Vrefint.
 *         ADC2��ģ������ͨ�� 16��ͨ�� 17��оƬ�ڲ������� Vss��
 *         ADC3��ģ������ͨ�� 9��14��15��16��17�� Vss������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_awdg_channel_set (amhw_zlg237_adc_t *p_hw_adc, amhw_zlg237_adc_awdg_channel_t flag)
{
    p_hw_adc->cr1 = (p_hw_adc->cr1 & (~(0x1ful << 0))) | (flag << 0);
}

/**
 * \brief TSVREFE �¶ȴ������� Vrefint����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ������ֹ�¶ȴ�������Vrefintͨ�����ڶ���1�� ADC�������У���λ�������� ADC1 �С�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_tsvrefe_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 &= ~(1ul << 23);
}

/**
 * \brief TSVREFE �¶ȴ�������Vrefintʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ������ֹ�¶ȴ�������Vrefintͨ�����ڶ���1�� ADC�������У���λ��������ADC1�С�
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_tsvrefe_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 23);
}

/**
 * \brief SWSTART ��ʼת���� ��ͨ������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��������ø�λ������ת����ת����ʼ��Ӳ�����������λ.
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_swstart_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 &= ~(1ul << 22);
}

/**
 * \brief SWSTART ��ʼת���� ��ͨ��ʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��������ø�λ������ת����ת����ʼ��Ӳ�����������λ.
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_swstart_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 22);
}

/**
 * \brief JSWSTART ��ʼת��ע��ͨ������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��������ø�λ������ת��������������λ����ת����ʼ��Ӳ�����������λ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jswstart_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 &= ~(1ul << 21);
}

/**
 * \brief JSWSTART ��ʼת��ע��ͨ��ʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��������ø�λ������ת��������������λ����ת����ʼ��Ӳ�����������λ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jswstart_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 21);
}

/**
 * \brief JSWSTART ע��ͨ�����ⲿ����ת��ģʽ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ������ֹ������������ͨ����ת�����ⲿ�����¼���
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_extirig_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 &= ~(1ul << 20);
}

/**
 * \brief JSWSTART ����ͨ�����ⲿ����ת��ģʽʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ������ֹ������������ͨ����ת�����ⲿ�����¼���
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_extirig_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 20);
}

/**
 * \brief JSWSTART ������������ͨ����ת�����ⲿ�¼�
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC12_REGULAR_TIM1_CC1
 *                            .
 *                            .
 *                            .
 *                            AMHW_ZLG237_ADC12_REGULAR_SWSTART
 *
 *                            ��
 *
 *                            AMHW_ZLG237_ADC3_REGULAR_TIM3_CC1
 *                            .
 *                            .
 *                            .
 *                            AMHW_ZLG237_ADC3_REGULAR_SWSTART
 *
 * \note : ��adc12�У��� �� �� �� �� Ʒ �� ��TIM8_TRGO����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_extsel_set (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->cr2 = (p_hw_adc->cr2 & (~(0x7ul << 17))) | (flag << 17);
}

/**
 * \brief JSWSTART ע��ͨ�����ⲿ����ת��ģʽ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ������ֹ������������ͨ����ת�����ⲿ�����¼���
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jextirig_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 &= ~(1ul << 15);
}

/**
 * \brief JSWSTART ע��ͨ�����ⲿ����ת��ģʽʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ���ڿ������ֹ������������ͨ����ת�����ⲿ�����¼���
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jextirig_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 15);
}

/**
 * \brief JEXTSEL[2:0] ѡ����������ͨ����ת�����ⲿ�¼�
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC12_INJECTED_TIM1_TRGO
 *                            .
 *                            .
 *                            .
 *                            AMHW_ZLG237_ADC12_INJECTED_JSWSTART
 *
 *                            ��
 *
 *                            AMHW_ZLG237_ADC3_INJECTED_TIM1_TRGO
 *                            .
 *                            .
 *                            .
 *                            AMHW_ZLG237_ADC3_INJECTED_JSWSTART
 *
 * \note : ��adc12�У�����������Ʒ���� TIM8_CC4
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jextsel_set (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->cr2 = (p_hw_adc->cr2 & (~(0x7ul << 12))) | (flag << 12);
}


/**
 * \brief ALIGN ���ݶ��뷽ʽ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC_DATA_RIGHT ��
 *                            AMHW_ZLG237_ADC_DATA_LEFT
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_data_alignment_set (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->cr2 = (p_hw_adc->cr2 & (~(0x1ul << 11))) | (flag << 11);
}

/**
 * \brief DMA ֱ�Ӵ洢������ģʽ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ֻ�� ADC1�� ADC3�ܲ��� DMA����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_dma_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 &= ~(1ul << 8);
}

/**
 * \brief DMA ֱ�Ӵ洢������ģʽʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ֻ�� ADC1�� ADC3�ܲ��� DMA����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_dma_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 8);
}

/**
 * \brief RSTCAL ��λУ׼ʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��λ��������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ�������.
 *
 *         ������ڽ���ת��ʱ���� RSTCAL�����У׼�Ĵ�����Ҫ���������.
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_rstcal_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 3);
}

/**
 * \brief RSTCAL ��λУ׼�����ж�
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \return  AM_FALSE������У׼      ��    AM_TRUE����У׼
 */
am_static_inline
am_bool_t amhw_zlg237_adc_rstcal_check (amhw_zlg237_adc_t *p_hw_adc)
{
    return (p_hw_adc->cr2 & (1ul << 3)) ?  AM_FALSE : AM_TRUE;
}

/**
 * \brief CAL ADУ׼ʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ��λ����������Կ�ʼУ׼������У׼����ʱ��Ӳ�������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_cal_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 2);
}

/**
 * \brief CAL ADУ׼�����ж�
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \return  AM_FALSE������У׼      ��    AM_TRUE����У׼
 */
am_static_inline
am_bool_t amhw_zlg237_adc_cal_check (amhw_zlg237_adc_t *p_hw_adc)
{
    return (p_hw_adc->cr2 & (1ul << 2)) ?  AM_FALSE : AM_TRUE;
}

/**
 * \brief CONT ���Ρ�����ת������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] flag : �������ӦΪ   AMHW_ZLG237_ADC_CONVERSION_SINGLE      ��
 *                             AMHW_ZLG237_ADC_CONVERSION_CONTINUOUS
 *
 * \note : ��������˴�λ����ת������������ֱ����λ�������
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_cont_set (amhw_zlg237_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->cr2 = (p_hw_adc->cr2 & (~(0x1ul << 1))) | (flag << 1);
}

/**
 * \brief ADON ADC����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ����λΪ��0��ʱ��д�롯1������ ADC �Ӷϵ�ģʽ�»��ѡ�
 *         ����λΪ��1��ʱ��д�롯1��������ת��
 *
 *         Ӧ�ó�����ע�⣬��ת�����ϵ���ת����ʼ��һ���ӳ� Tstab��
 *
 *         ADC�ϵ��ӳ�һ��ʱ���(tSTAB)���ٴ�����ADONλʱ��ʼ����ת����
 *
 *         ���������Ĵ������� ADON һ��������λ���ı䣬��ת����������������Ϊ�˷�ֹ���������ת����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_disable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 &= ~(1ul << 0);
}

/**
 * \brief ADCʹ��
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : ����λΪ��0��ʱ��д�롯1������ ADC �Ӷϵ�ģʽ�»��ѡ�
 *         ����λΪ��1��ʱ��д�롯1��������ת��
 *
 *         Ӧ�ó�����ע�⣬��ת�����ϵ���ת����ʼ��һ���ӳ� Tstab��
 *
 *         ADC�ϵ��ӳ�һ��ʱ���(tSTAB)���ٴ�����ADONλʱ��ʼ����ת����
 *
 *         ���������Ĵ������� ADON һ��������λ���ı䣬��ת����������������Ϊ�˷�ֹ���������ת����
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_enable (amhw_zlg237_adc_t *p_hw_adc)
{
    p_hw_adc->cr2 |= (1ul << 0);
}



/**
 * \brief ĳһͨ���Ĳ���ʱ������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] time     : �������ӦΪ   amhw_zlg237_adc_sample_time_t �е�ö�ٱ���
 * \param[in] channel  : �������ӦΪ   amhw_zlg237_adc_channel_t �е�ö�ٱ���
 *
 * \note : ��Щλ���ڶ�����ѡ��ÿ��ͨ���Ĳ���ʱ�䡣�ڲ���������ͨ��ѡ��λ���뱣�ֲ��䡣
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_smpr_set (amhw_zlg237_adc_t             *p_hw_adc,
                               amhw_zlg237_adc_sample_time_t  time,
                               amhw_zlg237_adc_channel_t      channel)
{
    if((channel / 10) == 1) {

        /* 10~17ͨ�������������趨λ��_SMPR1 �Ĵ��� */
        p_hw_adc->smpr[0] = (p_hw_adc->smpr[0] & (~(0x7ul << ((channel - 10) * 3)))) | (time << ((channel - 10) * 3));
    }else {

        /* 0~9ͨ�������������趨λ��_SMPR0 �Ĵ��� */
        p_hw_adc->smpr[1] = (p_hw_adc->smpr[1] & (~(0x7ul << (channel * 3)))) | (time << (channel * 3));
    }
}

am_static_inline
uint32_t amhw_zlg237_adc_smpr_get (amhw_zlg237_adc_t         *p_hw_adc,
                                   amhw_zlg237_adc_channel_t  channel)
{
    if((channel / 10) == 1) {

        /* 10~17ͨ�������������趨λ��_SMPR1 �Ĵ��� */
        return (p_hw_adc->smpr[1] >> ((channel - 10) * 3)) & 0x7ul ;
    }else {

        /* 0~9ͨ�������������趨λ��_SMPR0 �Ĵ��� */
        return (p_hw_adc->smpr[0] >> (channel * 3)) & 0x7ul ;
    }
}



/**
 * \brief ע��ͨ������ƫ�ƼĴ���
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] channel  : �������ӦΪ   amhw_zlg237_adc_injected_data_channel_t �е�ö�ٱ���
 * \param[in] value    : ����ƫ���趨ֵ(0~4095)
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_jofr_set (amhw_zlg237_adc_t                       *p_hw_adc,
                               amhw_zlg237_adc_injected_data_channel_t  channel,
                               uint16_t                                 value)
{
    p_hw_adc->jofr[channel] = value & (~(0xffful));
}

/**
 * \brief ���Ź�����ֵ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] value    : ���Ź������趨ֵ(0~4095)
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_awdg_htr_set (amhw_zlg237_adc_t *p_hw_adc, uint16_t value)
{
    p_hw_adc->htr = value & (~(0xffful));
}

/**
 * \brief ���Ź�����ֵ����
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] value    : ���Ź������趨ֵ(0~4095)
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_awdg_ltr_set (amhw_zlg237_adc_t *p_hw_adc, uint16_t value)
{
    p_hw_adc->ltr = value & (~(0xffful));
}


/**
 * \brief ����ͨ�����г�������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] length   : �������ӦΪ   amhw_zlg237_adc_regular_channel_length_t �е�ö�ٱ���
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_regular_channel_length_set (amhw_zlg237_adc_t                        *p_hw_adc,
                                                 amhw_zlg237_adc_regular_channel_length_t  length)
{
    p_hw_adc->sqr[0] = (p_hw_adc->sqr[0] & (~(0xful << 20))) | ((uint32_t)length << 20);
}


/**
 * \brief ����ͨ��������ͨ������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] order    : �������ӦΪ   amhw_zlg237_adc_regular_channel_order_t �е�ö�ٱ���
 * \param[in] channel  : �������ӦΪ   amhw_zlg237_adc_channel_t �е�ö�ٱ���
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_regular_channel_order_set (amhw_zlg237_adc_t                       *p_hw_adc,
                                                amhw_zlg237_adc_regular_channel_order_t  order,
                                                amhw_zlg237_adc_channel_t                channel)
{
    if ((order / 6) == 0) {

        /* ��1~6��ת������ SQR3  �Ĵ������趨 */
        p_hw_adc->sqr[2] = (p_hw_adc->sqr[2] & (~(0x1ful << (order * 5)))) | (channel << (order * 5));
    }else if ((order / 6) == 1) {

        /* ��7~12��ת������ SQR2  �Ĵ������趨 */
        p_hw_adc->sqr[1] = (p_hw_adc->sqr[1] & (~(0x1ful << ((order - 6) * 5)))) | (channel << ((order - 6) * 5));
    }
    else {

        /* ��13~16��ת������ SQR1  �Ĵ������趨 */
        p_hw_adc->sqr[0] = (p_hw_adc->sqr[0] & (~(0x1ful << ((order - 12) * 5)))) | (channel << ((order - 12) * 5));
    }
}


/**
 * \brief ע��ͨ�����г�������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] length   : �������ӦΪ   amhw_zlg237_adc_injected_channel_length_t �е�ö�ٱ���
 *
 * \note : ��ͬ�ڹ���ת�����У���� JL[1:0]�ĳ���С�� 4����ת��������˳���Ǵ�(4-JL)��ʼ��
 *         ���磺ADC_JSQR[21:0] =   10    00011   00011   00111  00010
 *                               3��ת��            3       3       7      2
 *         ��ζ��ɨ��ת����������ͨ��˳��ת����7�� 3��3�������� 2��7��3��
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_injected_channel_length_set (amhw_zlg237_adc_t                         *p_hw_adc,
                                                  amhw_zlg237_adc_injected_channel_length_t  length)
{
    p_hw_adc->jsqr = (p_hw_adc->jsqr & (~(0x3ul << 20))) | ((uint32_t)length << 20);
}



/**
 * \brief ע��ͨ��������ͨ������
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] order    : �������ӦΪ   amhw_zlg237_adc_injected_channel_order_t �е�ö�ٱ���
 * \param[in] channel  : �������ӦΪ   amhw_zlg237_adc_channel_t �е�ö�ٱ���
 *
 * \return none
 */
am_static_inline
void amhw_zlg237_adc_injected_channel_order_set (amhw_zlg237_adc_t                        *p_hw_adc,
                                                 amhw_zlg237_adc_injected_channel_order_t  order,
                                                 amhw_zlg237_adc_channel_t                 channel)
{
    p_hw_adc->jsqr = (p_hw_adc->jsqr & (~(0x1ful << (order * 5)))) | (channel << (order * 5));
}

/**
 * \brief ע��ͨ��adc���ݻ�ȡ
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 * \param[in] channel  : �������ӦΪ   amhw_zlg237_adc_injected_data_channel_t �е�ö�ٱ���
 *
 * \return ע��ͨ����ת����� (�����������Ҷ���)
 */
am_static_inline
uint16_t amhw_zlg237_adc_injected_data_get (amhw_zlg237_adc_t                       *p_hw_adc,
                                            amhw_zlg237_adc_injected_data_channel_t  channel)
{
    return p_hw_adc->jdr[channel];
}

/**
 * \brief ����ͨ��adc���ݻ�ȡ
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \return ����ͨ����ת����� (�����������Ҷ���)
 */
am_static_inline
uint16_t amhw_zlg237_adc_regular_data_get (amhw_zlg237_adc_t *p_hw_adc)
{
    return (p_hw_adc->dr & 0xffff);
}

/**
 * \brief ˫ģʽ�£�����ͨ��adc1���ݻ�ȡ
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : [31:16]  �� ADC1 �У�˫ģʽ�£���Щλ������ ADC2ת���Ĺ���ͨ�����ݡ�
 *         [31:16]  �� ADC2�� ADC3�У���ʹ����Щλ��
 *
 * \return ����ͨ����ת����� (�����������Ҷ���)
 */
am_static_inline
uint16_t amhw_zlg237_adc_regular_dul_mode_adc1_data_get (amhw_zlg237_adc_t *p_hw_adc)
{
    return (p_hw_adc->dr & 0xffff);
}

/**
 * \brief ˫ģʽ�£�����ͨ��adc2���ݻ�ȡ
 * \param[in] p_hw_adc : ָ��ADC�ṹ���ָ��
 *
 * \note : [31:16]  �� ADC1 �У�˫ģʽ�£���Щλ������ ADC2ת���Ĺ���ͨ�����ݡ�
 *         [31:16]  �� ADC2�� ADC3�У���ʹ����Щλ��
 *
 * \return ����ͨ����ת����� (�����������Ҷ���)
 */
am_static_inline
uint16_t amhw_zlg237_adc_regular_dul_mode_adc2_data_get (amhw_zlg237_adc_t *p_hw_adc)
{
    return ((p_hw_adc->dr >> 16) & 0xffff);
}

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
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG237_ADC_H */

/* end of file */
