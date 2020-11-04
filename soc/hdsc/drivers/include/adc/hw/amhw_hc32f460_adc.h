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
 * - 1.00 20-04-16  cds, first implementation
 *
 * \endinternal
 */

#ifndef __AMHW_HC32F460_ADC_H
#define __AMHW_HC32F460_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "hc32f460_regbase.h"

/**
 * \addtogroup amhw_hc32f460_if_adc
 * \copydoc amhw_hc32f460_adc.h
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
 * \brief ADC - �����Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t STRT                       : 1;   /**< \brief ת����ʼ*/
    uint8_t RESERVED1                       : 7;   /**< \brief ����*/
} stc_adc_str_field_t;

/**
 * \brief ADC - ���ƼĴ���0λ��ṹ��
 */
typedef struct
{
    __IO uint16_t MS                        : 2;  /**< \brief ģʽѡ��*/
    uint16_t RESERVED2                      : 2;  /**< \brief ����*/
    __IO uint16_t ACCSEL                    : 2;  /**< \brief �ֱ���ѡ��*/
    __IO uint16_t CLREN                     : 1;  /**< \brief ���ݼĴ����Զ����*/
    __IO uint16_t DFMT                      : 1;  /**< \brief ���ݸ�ʽ*/
    __IO uint16_t AVCNT                     : 3;  /**< \brief ����ѡ��*/
    uint16_t RESERVED11                     : 5;  /**< \brief ����*/
} stc_adc_cr0_field_t;

/**
 * \brief ADC - ���ƼĴ���1λ��ṹ��
 */
typedef struct
{
    uint16_t RESERVED0                      : 2;  /**< \brief ����*/
    __IO uint16_t RSCHSEL                   : 1;  /**< \brief ����A����ͨ��ѡ��*/
    uint16_t RESERVED3                      :13;  /**< \brief ����*/
} stc_adc_cr1_field_t;

/**
 * \brief ADC - ת����ʼ�����Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t TRGSELA                   : 3;  /**< \brief ����A��������ѡ��*/
    uint16_t RESERVED3                      : 4;  /**< \brief ����*/
    __IO uint16_t TRGENA                    : 1;  /**< \brief ����A����ʹ��*/
    __IO uint16_t TRGSELB                   : 3;  /**< \brief ����B��������ѡ��*/
    uint16_t RESERVED11                     : 4;  /**< \brief ����*/
    __IO uint16_t TRGENB                    : 1;  /**< \brief ����B����ʹ��*/
} stc_adc_trgsr_field_t;

/**
 * \brief ADC - ת��ͨ��ѡ��Ĵ���Aλ��ṹ��
 */
typedef struct
{
    __IO uint16_t CHSELA16                  : 1;  /**< \brief ת��ͨ��ѡ��*/
    uint16_t RESERVED1                      :15;  /**< \brief ����*/
} stc_adc_chselra1_field_t;

/**
 * \brief ADC - ת��ͨ��ѡ��Ĵ���Bλ��ṹ��
 */
typedef struct
{
    __IO uint16_t CHSELB16                  : 1;  /**< \brief ת��ͨ��ѡ��*/
    uint16_t RESERVED1                      :15;  /**< \brief ����*/
} stc_adc_chselrb1_field_t;

/**
 * \brief ADC - ƽ��ͨ��ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t AVCHSEL16                 : 1;  /**< \brief ƽ��ͨ��ѡ��*/
    uint16_t RESERVED1                      :15;  /**< \brief ����*/
} stc_adc_avchselr1_field_t;

/**
 * \brief ADC - ADͨ��ӳ����ƼĴ���0λ��ṹ��
 */
typedef struct
{
    __IO uint16_t CH00MUX                   : 4;  /**< \brief ͨ��0ӳ��ѡ��*/
    __IO uint16_t CH01MUX                   : 4;  /**< \brief ͨ��1ӳ��ѡ��*/
    __IO uint16_t CH02MUX                   : 4;  /**< \brief ͨ��2ӳ��ѡ��*/
    __IO uint16_t CH03MUX                   : 4;  /**< \brief ͨ��3ӳ��ѡ��*/
} stc_adc_chmuxr0_field_t;

/**
 * \brief ADC - ADͨ��ӳ����ƼĴ���1λ��ṹ��
 */
typedef struct
{
    __IO uint16_t CH04MUX                   : 4;  /**< \brief ͨ��4ӳ��ѡ��*/
    __IO uint16_t CH05MUX                   : 4;  /**< \brief ͨ��5ӳ��ѡ��*/
    __IO uint16_t CH06MUX                   : 4;  /**< \brief ͨ��6ӳ��ѡ��*/
    __IO uint16_t CH07MUX                   : 4;  /**< \brief ͨ��7ӳ��ѡ��*/
} stc_adc_chmuxr1_field_t;

/**
 * \brief ADC - ADͨ��ӳ����ƼĴ���2λ��ṹ��
 */
typedef struct
{
    __IO uint16_t CH08MUX                   : 4;  /**< \brief ͨ��8ӳ��ѡ��*/
    __IO uint16_t CH09MUX                   : 4;  /**< \brief ͨ��9ӳ��ѡ��*/
    __IO uint16_t CH10MUX                   : 4;  /**< \brief ͨ��10ӳ��ѡ��*/
    __IO uint16_t CH11MUX                   : 4;  /**< \brief ͨ��11ӳ��ѡ��*/
} stc_adc_chmuxr2_field_t;

/**
 * \brief ADC - ADͨ��ӳ����ƼĴ���3λ��ṹ��
 */
typedef struct
{
    __IO uint16_t CH12MUX                   : 4;  /**< \brief ͨ��12ӳ��ѡ��*/
    __IO uint16_t CH13MUX                   : 4;  /**< \brief ͨ��13ӳ��ѡ��*/
    __IO uint16_t CH14MUX                   : 4;  /**< \brief ͨ��14ӳ��ѡ��*/
    __IO uint16_t CH15MUX                   : 4;  /**< \brief ͨ��15ӳ��ѡ��*/
} stc_adc_chmuxr3_field_t;

/**
 * \brief ADC - AD�ж�״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t EOCAF                      : 1;  /**< \brief ����Aת����ɱ�־*/
    __IO uint8_t EOCBF                      : 1;  /**< \brief ����Bת����ɱ�־*/
    uint8_t RESERVED2                       : 6;  /**< \brief ����*/
} stc_adc_isr_field_t;

/**
 * \brief ADC - AD�ж�ʹ�ܼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t EOCAIEN                    : 1;  /**< \brief ����Aת������ж�ʹ��*/
    __IO uint8_t EOCBIEN                    : 1;  /**< \brief ����Aת������ж�ʹ��*/
    uint8_t RESERVED2                       : 6;  /**< \brief ����*/
} stc_adc_icr_field_t;

/**
 * \brief ADC - Эͬģʽ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t SYNCEN                    : 1;  /**< \brief ͬ��ģʽ���*/
    uint16_t RESERVED1                      : 3;  /**< \brief ����*/
    __IO uint16_t SYNCMD                    : 3;  /**< \brief ͬ��ģʽѡ��*/
    uint16_t RESERVED7                      : 1;  /**< \brief ����*/
    __IO uint16_t SYNCDLY                   : 8;  /**< \brief ͬ���ӳ�ʱ��*/
} stc_adc_synccr_field_t;

/**
 * \brief ADC - ģ�⿴�Ź����ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t AWDEN                     : 1;  /**< \brief ���Ź��ȽϹ���ʹ��*/
    uint16_t RESERVED1                      : 3;  /**< \brief ����*/
    __IO uint16_t AWDMD                     : 1;  /**< \brief ���Ź��Ƚ�ģʽ*/
    uint16_t RESERVED5                      : 1;  /**< \brief ����*/
    __IO uint16_t AWDSS                     : 2;  /**< \brief ���Ź�����ѡ��*/
    __IO uint16_t AWDIEN                    : 1;  /**< \brief ���Ź��ж�ʹ��*/
    uint16_t RESERVED9                      : 7;  /**< \brief ����*/
} stc_adc_awdcr_field_t;

/**
 * \brief ADC - ģ�⿴�Ź��Ƚ�ͨ��ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t AWDCH16                   : 1;  /**< \brief ���Ź��ȽϹ���ͨ��ѡ��*/
    uint16_t RESERVED1                      :15;  /**< \brief ����*/
} stc_adc_awdchsr1_field_t;

/**
 * \brief ADC - ģ�⿴�Ź�״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t AWDF16                    : 1;  /**< \brief ���Ź��Ƚ�״̬λ*/
    uint16_t RESERVED1                      :15;  /**< \brief ����*/
} stc_adc_awdsr1_field_t;

/**
 * \brief ADC - �ɱ������Ŵ������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t PGACTL                    : 4;  /**< \brief �Ŵ�������*/
    uint16_t RESERVED4                      :12;  /**< \brief ����*/
} stc_adc_pgacr_field_t;

/**
 * \brief ADC - �ɱ�����汶���Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t GAIN                      : 4;  /**< \brief �Ŵ��������趨*/
    uint16_t RESERVED4                      :12;  /**< \brief ����*/
} stc_adc_pgagsr_field_t;

/**
 * \brief ADC - �ɱ������Ŵ�������ѡ��Ĵ���0λ��ṹ��
 */
typedef struct
{
    __IO uint16_t PGAINSEL                  : 9;  /**< \brief �Ŵ���ģ������ѡ��*/
    uint16_t RESERVED9                      : 7;  /**< \brief ����*/
} stc_adc_pgainsr0_field_t;

/**
 * \brief ADC - �ɱ������Ŵ�������ѡ��Ĵ���1λ��ṹ��
 */
typedef struct
{
    __IO uint16_t PGAVSSEN                  : 1;  /**< \brief �Ŵ������г�����ѡ��*/
    uint16_t RESERVED1                      :15;  /**< \brief ����*/
} stc_adc_pgainsr1_field_t;


/**
 * \brief ADC - Register Layout Typedef
 */
typedef struct amhw_hc32f460_adc{
    union
    {
        __IO uint8_t STR;             /**< \brief AD�����Ĵ��� */
        stc_adc_str_field_t STR_f;    /**< \brief AD�����Ĵ���λ��ṹ�� */
    };
    uint8_t RESERVED1[1];             /**< \brief ����*/
    union
    {
        __IO uint16_t CR0;            /**< \brief AD ���ƼĴ���0*/
        stc_adc_cr0_field_t CR0_f;    /**< \brief AD ���ƼĴ���0λ��ṹ��*/
    };
    union
    {
        __IO uint16_t CR1;            /**< \brief AD ���ƼĴ���1*/
        stc_adc_cr1_field_t CR1_f;    /**< \brief AD ���ƼĴ���1λ��ṹ��*/
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint16_t TRGSR;          /**< \brief AD ת����ʼ�����Ĵ���*/
        stc_adc_trgsr_field_t TRGSR_f;/**< \brief AD ת����ʼ�����Ĵ���λ��ṹ��*/
    };
    __IO uint16_t CHSELRA0;           /**< \brief AD ͨ��ѡ��Ĵ���A0*/
    union
    {
        __IO uint16_t CHSELRA1;       /**< \brief AD ͨ��ѡ��Ĵ���A1*/
        stc_adc_chselra1_field_t CHSELRA1_f;  /**< \brief AD ͨ��ѡ��Ĵ���A1λ��ṹ��*/
    };
    __IO uint16_t CHSELRB0;           /**< \brief AD ͨ��ѡ��Ĵ���B0*/
    union
    {
        __IO uint16_t CHSELRB1;       /**< \brief AD ͨ��ѡ��Ĵ���B1*/
        stc_adc_chselrb1_field_t CHSELRB1_f;  /**< \brief AD ͨ��ѡ��Ĵ���B1λ��ṹ��*/
    };
    __IO uint16_t AVCHSELR0;          /**< \brief AD ƽ��ͨ��ѡ��Ĵ���0*/
    union
    {
        __IO uint16_t AVCHSELR1;      /**< \brief AD ƽ��ͨ��ѡ��Ĵ���1*/
        stc_adc_avchselr1_field_t AVCHSELR1_f;  /**< \brief AD ƽ��ͨ��ѡ��Ĵ���1λ��ṹ��*/
    };
    uint8_t RESERVED10[8];
    __IO uint8_t SSTR0;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR1;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR2;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR3;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR4;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR5;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR6;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR7;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR8;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR9;               /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR10;              /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR11;              /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR12;              /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR13;              /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR14;              /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTR15;              /**< \brief AD �������ڼĴ���*/
    __IO uint8_t SSTRL;               /**< \brief AD �������ڼĴ���*/
    uint8_t RESERVED27[7];            /**< \brief ����*/
    union
    {
        __IO uint16_t CHMUXR0;             /**< \brief ADͨ��ӳ����ƼĴ���0*/
        stc_adc_chmuxr0_field_t CHMUXR0_f; /**< \brief ADͨ��ӳ����ƼĴ���0λ��ṹ��*/
    };
    union
    {
        __IO uint16_t CHMUXR1;             /**< \brief ADͨ��ӳ����ƼĴ���1*/
        stc_adc_chmuxr1_field_t CHMUXR1_f; /**< \brief ADͨ��ӳ����ƼĴ���1λ��ṹ��*/
    };
    union
    {
        __IO uint16_t CHMUXR2;             /**< \brief ADͨ��ӳ����ƼĴ���2*/
        stc_adc_chmuxr2_field_t CHMUXR2_f; /**< \brief ADͨ��ӳ����ƼĴ���2λ��ṹ��*/
    };
    union
    {
        __IO uint16_t CHMUXR3;             /**< \brief ADͨ��ӳ����ƼĴ���3*/
        stc_adc_chmuxr3_field_t CHMUXR3_f; /**< \brief ADͨ��ӳ����ƼĴ���3λ��ṹ��*/
    };
    uint8_t RESERVED31[6];                 /**< \brief ����*/
    union
    {
        __IO uint8_t ISR;                  /**< \brief AD�ж�״̬�Ĵ���*/
        stc_adc_isr_field_t ISR_f;         /**< \brief AD�ж�״̬�Ĵ���λ��ṹ��*/
    };
    union
    {
        __IO uint8_t ICR;                  /**< \brief AD�ж���ɼĴ���*/
        stc_adc_icr_field_t ICR_f;         /**< \brief AD�ж���ɼĴ���λ��ṹ��*/
    };
    uint8_t RESERVED33[4];                 /**< \brief ����*/
    union
    {
        __IO uint16_t SYNCCR;              /**< \brief ADЭͬģʽ���ƼĴ���*/
        stc_adc_synccr_field_t SYNCCR_f;   /**< \brief ADЭͬģʽ���ƼĴ���λ��ṹ��*/
    };
    uint8_t RESERVED34[2];
    __IO uint16_t DR0;                     /**< \brief ch0 AD���ݼĴ���*/
    __IO uint16_t DR1;                     /**< \brief ch1 AD���ݼĴ���*/
    __IO uint16_t DR2;                     /**< \brief ch2 AD���ݼĴ���*/
    __IO uint16_t DR3;                     /**< \brief ch3 AD���ݼĴ���*/
    __IO uint16_t DR4;                     /**< \brief ch4 AD���ݼĴ���*/
    __IO uint16_t DR5;                     /**< \brief ch5 AD���ݼĴ���*/
    __IO uint16_t DR6;                     /**< \brief ch6 AD���ݼĴ���*/
    __IO uint16_t DR7;                     /**< \brief ch7 AD���ݼĴ���*/
    __IO uint16_t DR8;                     /**< \brief ch8 AD���ݼĴ���*/
    __IO uint16_t DR9;                     /**< \brief ch9 AD���ݼĴ���*/
    __IO uint16_t DR10;                    /**< \brief ch10 AD���ݼĴ���*/
    __IO uint16_t DR11;                    /**< \brief ch11 AD���ݼĴ���*/
    __IO uint16_t DR12;                    /**< \brief ch12 AD���ݼĴ���*/
    __IO uint16_t DR13;                    /**< \brief ch13 AD���ݼĴ���*/
    __IO uint16_t DR14;                    /**< \brief ch14 AD���ݼĴ���*/
    __IO uint16_t DR15;                    /**< \brief ch15 AD���ݼĴ���*/
    __IO uint16_t DR16;                    /**< \brief ch16 AD���ݼĴ���*/
    uint8_t RESERVED51[46];                /**< \brief ����*/
    union
    {
        __IO uint16_t AWDCR;               /**< \brief ģ�⿴�Ź����ƼĴ���*/
        stc_adc_awdcr_field_t AWDCR_f;     /**< \brief ģ�⿴�Ź����ƼĴ���λ��ṹ��*/
    };
    uint8_t RESERVED52[2];                 /**< \brief ����*/
    __IO uint16_t AWDDR0;                  /**< \brief ģ�⿴�Ź���ֵ�Ĵ���0*/
    __IO uint16_t AWDDR1;                  /**< \brief ģ�⿴�Ź���ֵ�Ĵ���1*/
    uint8_t RESERVED54[4];                 /**< \brief ����*/
    __IO uint16_t AWDCHSR0;                /**< \brief ģ�⿴�Ź��Ƚ�ͨ��ѡ��Ĵ���0*/
    union
    {
        __IO uint16_t AWDCHSR1;               /**< \brief ģ�⿴�Ź��Ƚ�ͨ��ѡ��Ĵ���1*/
        stc_adc_awdchsr1_field_t AWDCHSR1_f;  /**< \brief ģ�⿴�Ź��Ƚ�ͨ��ѡ��Ĵ���1λ��ṹ��*/
    };
    __IO uint16_t AWDSR0;                  /**< \brief ģ�⿴�Ź�״̬�Ĵ���0*/
    union
    {
        __IO uint16_t AWDSR1;              /**< \brief ģ�⿴�Ź�״̬�Ĵ���1*/
        stc_adc_awdsr1_field_t AWDSR1_f;   /**< \brief ģ�⿴�Ź�״̬�Ĵ���1λ��ṹ��*/
    };
    uint8_t RESERVED58[12];                /**< \brief ����*/
    union
    {
        __IO uint16_t PGACR;               /**< \brief AD�ɱ������Ŵ���ƼĴ���*/
        stc_adc_pgacr_field_t PGACR_f;     /**< \brief AD�ɱ������Ŵ���ƼĴ���λ��ṹ��*/
    };
    union
    {
        __IO uint16_t PGAGSR;              /**< \brief AD�ɱ�����汶���Ĵ���*/
        stc_adc_pgagsr_field_t PGAGSR_f;   /**< \brief AD�ɱ�����汶���Ĵ���λ��ṹ��*/
    };
    uint8_t RESERVED60[8];                 /**< \brief ����*/
    union
    {
        __IO uint16_t PGAINSR0;               /**< \brief AD�ɱ������Ŵ�������ѡ��Ĵ���0*/
        stc_adc_pgainsr0_field_t PGAINSR0_f;  /**< \brief AD�ɱ������Ŵ�������ѡ��Ĵ���0λ��ṹ��*/
    };
    union
    {
        __IO uint16_t PGAINSR1;               /**< \brief AD�ɱ������Ŵ�������ѡ��Ĵ���1*/
        stc_adc_pgainsr1_field_t PGAINSR1_f;  /**< \brief AD�ɱ������Ŵ�������ѡ��Ĵ���1λ��ṹ��*/
    };
} amhw_hc32f460_adc_t;

/* ͨ������ */
typedef enum {
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN0       = 0,
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN1       = 1,
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN2       = 2,
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN3       = 3,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN4       = 4,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN5       = 5,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN6       = 6,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN7       = 7,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN8       = 8,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN9       = 9,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN10      = 10,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN11      = 11,
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN12       = 12,
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN13       = 13,
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN14       = 14,
    AMHW_HC32F460_ADC_CH_MUX_ADC1_IN15       = 15,
    AMHW_HC32F460_ADC_CH_MUX_ADC12_IN_ANALOG      = 16,
}amhw_hc32f460_adc_chan_sel_t;


/**
 * \brief ADC��ʼת��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_convert_start(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->STR_f.STRT = 1;
}

/**
 * \brief ADCֹͣת��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_convert_stop(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->STR_f.STRT = 0;
}


typedef enum amhw_hc32f460_adc_average_count{
    AMHW_HC32F460_ADC_AVERAGE_COUNT_2   = 0x0,
    AMHW_HC32F460_ADC_AVERAGE_COUNT_4   = 0x1,
    AMHW_HC32F460_ADC_AVERAGE_COUNT_8   = 0x2,
    AMHW_HC32F460_ADC_AVERAGE_COUNT_16  = 0x3,
    AMHW_HC32F460_ADC_AVERAGE_COUNT_32  = 0x4,
    AMHW_HC32F460_ADC_AVERAGE_COUNT_64  = 0x5,
    AMHW_HC32F460_ADC_AVERAGE_COUNT_128 = 0x6,
    AMHW_HC32F460_ADC_AVERAGE_COUNT_256 = 0x7,
}amhw_hc32f460_adc_average_count_t;


/**
 * \brief ADCƽ��ת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_average_count_set(amhw_hc32f460_adc_t              *p_hw_adc,
                                         amhw_hc32f460_adc_average_count_t flag)
{
    p_hw_adc->CR0_f.AVCNT = flag;
}


typedef enum amhw_hc32f460_adc_data_align_format{
    AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT = 0x0, /** <brief �����Ҷ��� */
    AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_LEFT  = 0x1, /** <brief ��������� */
}amhw_hc32f460_adc_data_align_format_t;

/**
 * \brief ADCת��������뷽ʽ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_data_align_set(amhw_hc32f460_adc_t                  *p_hw_adc,
                                      amhw_hc32f460_adc_data_align_format_t flag)
{
    p_hw_adc->CR0_f.DFMT = flag;
}

/**
 * \brief ADC���ݼĴ����Զ����ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_data_autoclr_enable(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->CR0_f.CLREN = 1;
}

/**
 * \brief ADC���ݼĴ����Զ��������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_data_autoclr_disable(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->CR0_f.CLREN = 0;
}

/**
 * \brief ADCת������
 */
typedef enum amhw_hc32f460_adc_resolution{
    AMHW_HC32F460_ADC_RESOLUTION_12BIT = 12, /** <brief 12λ�ֱ��� */
    AMHW_HC32F460_ADC_RESOLUTION_10BIT = 10, /** <brief 10λ�ֱ��� */
    AMHW_HC32F460_ADC_RESOLUTION_8BIT  = 8,  /** <brief 8λ�ֱ��� */
}amhw_hc32f460_adc_resolution_t;

/**
 * \brief ADC�ֱ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_resolution_set(amhw_hc32f460_adc_t           *p_hw_adc,
                                      amhw_hc32f460_adc_resolution_t flag)
{
    p_hw_adc->CR0_f.ACCSEL = flag;
}

typedef enum amhw_hc32f460_adc_mode{
    AMHW_HC32F460_ADC_SEQ_A_ONCE              = 0x0, /** <brief ����A����ɨ�� */
    AMHW_HC32F460_ADC_SEQ_A_CONTINUOUS        = 0x1, /** <brief ����A����ɨ�� */
    AMHW_HC32F460_ADC_SEQ_A_ONCE_B_ONCE       = 0x2, /** <brief ����A����ɨ�裬B����ɨ�� */
    AMHW_HC32F460_ADC_SEQ_A_CONTINUOUS_B_ONCE = 0x3, /** <brief ����A����ɨ�裬B����ɨ�� */
}amhw_hc32f460_adc_mode_t;
/**
 * \brief ADCģʽ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_mode_set(amhw_hc32f460_adc_t      *p_hw_adc,
                                amhw_hc32f460_adc_mode_t  flag)
{
    p_hw_adc->CR0_f.MS = flag;
}

typedef enum amhw_hc32f460_adc_seq_a_restart_position{
    AMHW_HC32F460_ADC_SEQ_A_RESTART_POSITION_CONTINUOUS = 0x0, /** <brief ������B�жϺ�����A����ʱ�ӱ��ж�ͨ����ʼ����ɨ�� */
    AMHW_HC32F460_ADC_SEQ_A_RESTART_POSITION_RESTART    = 0x1, /** <brief ������B�жϺ�����A����ʱ�ӵ�һ��ͨ����ʼ����ɨ�� */
}amhw_hc32f460_adc_seq_a_restart_position_t;

/**
 * \brief ADC����A������ʽ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_seq_a_restart_position_set(amhw_hc32f460_adc_t                       *p_hw_adc,
                                                  amhw_hc32f460_adc_seq_a_restart_position_t flag)
{
    p_hw_adc->CR1_f.RSCHSEL = 0;
}

/**
 * \brief ADC����BƬ�ڻ��ⲿ���Ŵ������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_seq_b_trigger_enable(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->TRGSR_f.TRGENB = 1;
}

/**
 * \brief ADC����BƬ�ڻ��ⲿ���Ŵ�����ֹ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_seq_b_trigger_disable(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->TRGSR_f.TRGENB = 0;
}

/**
 * \brief ADC����AƬ�ڻ��ⲿ���Ŵ������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_seq_a_trigger_enable(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->TRGSR_f.TRGENA = 1;
}

/**
 * \brief ADC����AƬ�ڻ��ⲿ���Ŵ�����ֹ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_seq_a_trigger_disable(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->TRGSR_f.TRGENA = 0;
}

typedef enum amhw_hc32f460_adc_seq_trigger_source{
    AMHW_HC32F460_ADC_SEQ_TRIGGER_ADTRx                 = 0x0,
    AMHW_HC32F460_ADC_SEQ_TRIGGER_IN_TRGx0              = 0x1,
    AMHW_HC32F460_ADC_SEQ_TRIGGER_IN_TRGx1              = 0x2,
    AMHW_HC32F460_ADC_SEQ_TRIGGER_IN_TRGx0_AND_IN_TRGx1 = 0x3,
}amhw_hc32f460_adc_seq_trigger_source_t;

/**
 * \brief ADC����B��������ѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_seq_b_trigger_source_sel(amhw_hc32f460_adc_t *p_hw_adc,
                                                amhw_hc32f460_adc_seq_trigger_source_t flag)
{
    p_hw_adc->TRGSR_f.TRGSELB = flag;
}

/**
 * \brief ADC����A��������ѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_seq_a_trigger_source_sel(amhw_hc32f460_adc_t                   *p_hw_adc,
                                                amhw_hc32f460_adc_seq_trigger_source_t flag)
{
    p_hw_adc->TRGSR_f.TRGSELA = flag;
}

#define HC32F460_AOS_ADC_ITRGSELR0_BASE    (0x40010858UL)
#define HC32F460_AOS_ADC_ITRGSELR1_BASE    (0x40010860UL)
/**
 * \brief ADCƬ�ڴ���Դ��IN_TRGx0��ѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_intrgx0_sel(int32_t flag)
{
    *(volatile uint32_t *)((uint32_t)(HC32F460_AOS_ADC_ITRGSELR0_BASE)) = flag;
}

/**
 * \brief ADCƬ�ڴ���Դ��IN_TRGx1��ѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_intrgx1_sel(int32_t flag)
{
    *(volatile uint32_t *)((uint32_t)(HC32F460_AOS_ADC_ITRGSELR1_BASE)) = flag;
}

/**
 * \brief ADC����Aͨ��ѡ��(CHSELA[15:0])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 *
 * \note ��Ҫ������A������B��ѡ����ͬ��ͨ��
 */
am_static_inline
void amhw_hc32f460_adc_seq_a_channel_sel0(amhw_hc32f460_adc_t *p_hw_adc,
                                          uint32_t             chan)
{
    p_hw_adc->CHSELRA0 |= (uint16_t)((1 << chan) & 0xFFFF);
}

/**
 * \brief ADC����Aͨ��ѡ��(CHSELA[31:16])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 *
 * \note ��Ҫ������A������B��ѡ����ͬ��ͨ��
 */
am_static_inline
void amhw_hc32f460_adc_seq_a_channel_sel1(amhw_hc32f460_adc_t *p_hw_adc,
                                          uint32_t             chan)
{
    p_hw_adc->CHSELRA1 |= (uint16_t)((1 << (chan - 16)) & 0xFFFF);
}

/**
 * \brief ADC����Bͨ��ѡ��(CHSELB[15:0])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 *
 * \note ��Ҫ������A������B��ѡ����ͬ��ͨ��
 */
am_static_inline
void amhw_hc32f460_adc_seq_b_channel_sel0(amhw_hc32f460_adc_t *p_hw_adc,
                                          uint32_t             chan)
{
    p_hw_adc->CHSELRB0 |= (uint16_t)((1 << chan) & 0xFFFF);
}

/**
 * \brief ADC����Bͨ��ѡ��(CHSELB[31:16])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 *
 * \note ��Ҫ������A������B��ѡ����ͬ��ͨ��
 */
am_static_inline
void amhw_hc32f460_adc_seq_b_channel_sel1(amhw_hc32f460_adc_t *p_hw_adc,
                                          uint32_t             chan)
{
    p_hw_adc->CHSELRB1 |= (uint16_t)((1 << (chan - 16)) & 0xFFFF);
}

typedef enum {
    AMHW_HC32F460_ADC_CHAN0_MASK = 1 << 0,
    AMHW_HC32F460_ADC_CHAN1_MASK = 1 << 1,
    AMHW_HC32F460_ADC_CHAN2_MASK = 1 << 2,
    AMHW_HC32F460_ADC_CHAN3_MASK = 1 << 3,
    AMHW_HC32F460_ADC_CHAN4_MASK = 1 << 4,
    AMHW_HC32F460_ADC_CHAN5_MASK = 1 << 5,
    AMHW_HC32F460_ADC_CHAN6_MASK = 1 << 6,
    AMHW_HC32F460_ADC_CHAN7_MASK = 1 << 7,
    AMHW_HC32F460_ADC_CHAN8_MASK = 1 << 8,
    AMHW_HC32F460_ADC_CHAN9_MASK = 1 << 9,
    AMHW_HC32F460_ADC_CHAN10_MASK = 1 << 10,
    AMHW_HC32F460_ADC_CHAN11_MASK = 1 << 11,
    AMHW_HC32F460_ADC_CHAN12_MASK = 1 << 12,
    AMHW_HC32F460_ADC_CHAN13_MASK = 1 << 13,
    AMHW_HC32F460_ADC_CHAN14_MASK = 1 << 14,
    AMHW_HC32F460_ADC_CHAN15_MASK = 1 << 15,
    AMHW_HC32F460_ADC_CHAN16_MASK = 1 << 16,
}amhw_hc32f460_adc_chan_mask_t;


/**
 * \brief ADC����ƽ��ͨ��ѡ��(AVCHSEL[15:0])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_average_channel_sel0(amhw_hc32f460_adc_t *p_hw_adc,
                                            uint32_t             chan)
{
    p_hw_adc->AVCHSELR0 |= (uint16_t)(1 << chan);
}

/**
 * \brief ADC����ƽ��ͨ��ѡ��(AVCHSEL[31:16])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_average_channel_sel1(amhw_hc32f460_adc_t *p_hw_adc,
                                            uint32_t             chan)
{
	p_hw_adc->AVCHSELR1 |= (uint16_t)((1 << (chan - 16)));
}

/**
 * \brief ADC����ƽ��ͨ�����(AVCHSEL[15:0])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_average_channel_clr0(amhw_hc32f460_adc_t *p_hw_adc,
                                            uint32_t             chan)
{
    p_hw_adc->AVCHSELR0 &= ~(uint16_t)(1 << chan);
}

/**
 * \brief ADC����ƽ��ͨ�����(AVCHSEL[31:16])
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_average_channel_clr1(amhw_hc32f460_adc_t *p_hw_adc,
                                            uint32_t             chan)
{
	p_hw_adc->AVCHSELR1 &= ~(uint16_t)((1 << (chan - 16)));
}



/**
 * \brief ADC������������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] channel  : ͨ����
 * \param[in] count    : ������������5~255��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_sampling_period_set(amhw_hc32f460_adc_t *p_hw_adc,
                                           uint8_t              channel,
                                           uint8_t              count)
{
    if (channel <= 15) {
        *(uint8_t *)((&p_hw_adc->SSTR0) + channel) = count;
    } else {
        p_hw_adc->SSTRL = count;
    }
}

/**
 * \brief ADC�������ڻ�ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] channel  : ͨ����
 *
 * \return none
 */
am_static_inline
uint8_t amhw_hc32f460_adc_sampling_period_get(amhw_hc32f460_adc_t *p_hw_adc,
                                              uint8_t              channel)
{
    if (channel <= 15) {
        return *(uint8_t *)((&p_hw_adc->SSTR0) + channel);
    } else {
        return p_hw_adc->SSTRL;
    }
}


typedef struct amhw_adc_chmux{
    uint8_t                           chan;
    uint8_t                           pin;
    amhw_hc32f460_adc_chan_sel_t      type;
}amhw_adc_chmux_t;


/**
 * \brief ADC1ͨ��ӳ������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] channel  : ͨ����
 * \param[in] count    : ӳ�������
 *
 * \return none
 */
am_static_inline
void amhw_hc32f460_adc_channel_mux_set(amhw_hc32f460_adc_t               *p_hw_adc,
                                       uint8_t                           channel,
                                       amhw_hc32f460_adc_chan_sel_t      type)
{
    if ((uint32_t)p_hw_adc == HC32F460_ADC1_BASE) {
        *(uint16_t *)((&p_hw_adc->CHMUXR0) + (channel / 4)) &= ~(0xf << (4 * (channel % 4)));
        *(uint16_t *)((&p_hw_adc->CHMUXR0) + (channel / 4)) |= (type) << (4 * (channel % 4));
    } else {
        *(uint16_t *)((&p_hw_adc->CHMUXR0) + (channel / 4)) &= ~(((type < 16) ? (type - 4) : 8) << (4 * (channel % 4)));
        *(uint16_t *)((&p_hw_adc->CHMUXR0) + (channel / 4)) = ((type < 16) ? (type - 4) : 8) << (4 * (channel % 4));
    }

}


typedef enum amhw_hc32f460_adc_int_type{
    AMHW_HC32F460_ADC_INT_EOCAF = 0,  /* ����Aת������ж�*/
    AMHW_HC32F460_ADC_INT_EOCBF = 1,  /* ����Bת������ж�*/
}amhw_hc32f460_adc_int_type_t;

/**
 * \brief ADC�ж�״̬��־��ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_hc32f460_adc_int_type_tö������
 *
 * \return AM_TRUE  : 1
 *         AM_FALSE : 0
 */
am_static_inline
am_bool_t amhw_hc32f460_adc_int_flag_check (amhw_hc32f460_adc_t          *p_hw_adc,
                                            amhw_hc32f460_adc_int_type_t  type)
{
    return ((p_hw_adc->ISR >> type) & 0x1u) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ADC�ж�״̬��־���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_hc32f460_adc_int_type_tö������

 */
am_static_inline
void amhw_hc32f460_adc_int_flag_clr (amhw_hc32f460_adc_t          *p_hw_adc,
                                     amhw_hc32f460_adc_int_type_t  type)
{
    p_hw_adc->ISR &= ~(1 << type);
}

/**
 * \brief ADC�ж�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_hc32f460_adc_int_type_tö������
 */
am_static_inline
void amhw_hc32f460_adc_int_enable (amhw_hc32f460_adc_t          *p_hw_adc,
                                   amhw_hc32f460_adc_int_type_t  type)
{
    p_hw_adc->ICR |= (1 << type);
}

/**
 * \brief ADC�жϽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_hc32f460_adc_int_type_tö������
 */
am_static_inline
void amhw_hc32f460_adc_int_disable (amhw_hc32f460_adc_t          *p_hw_adc,
                                    amhw_hc32f460_adc_int_type_t  type)
{
    p_hw_adc->ICR &= (~(1 << type));
}

#define AMHW_HC32F460_ADC_DATA_RIGHT_12BIT_MASK  (0XFFF)
#define AMHW_HC32F460_ADC_DATA_RIGHT_10BIT_MASK  (0X3FF)
#define AMHW_HC32F460_ADC_DATA_RIGHT_8BIT_MASK   (0XFF)
#define AMHW_HC32F460_ADC_DATA_LEFT_12BIT_MASK   (0XFFF0)
#define AMHW_HC32F460_ADC_DATA_LEFT_10BIT_MASK   (0XFFC0)
#define AMHW_HC32F460_ADC_DATA_LEFT_8BIT_MASK    (0XFF00)

/**
 * \brief ADC��ȡͨ��x������
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] channel    : ͨ����
 * \param[in] resolution : �ֱ���
 * \param[in] format     : ���뷽ʽ
 */
am_static_inline
uint16_t amhw_hc32f460_adc_ch_data_get (amhw_hc32f460_adc_t                  *p_hw_adc,
                                        uint32_t                              channel,
                                        amhw_hc32f460_adc_resolution_t        resolution,
                                        amhw_hc32f460_adc_data_align_format_t format)
{
    if (format == AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_LEFT) {
        if (resolution == AMHW_HC32F460_ADC_RESOLUTION_8BIT) {
            return (*(uint16_t *)(&(p_hw_adc->DR0) + channel) & AMHW_HC32F460_ADC_DATA_LEFT_8BIT_MASK) >> 8;
        } else if(resolution == AMHW_HC32F460_ADC_RESOLUTION_10BIT) {
            return (*(uint16_t *)(&(p_hw_adc->DR0) + channel) & AMHW_HC32F460_ADC_DATA_LEFT_10BIT_MASK) >> 6;
        } else {
            return (*(uint16_t *)(&(p_hw_adc->DR0) + channel) & AMHW_HC32F460_ADC_DATA_LEFT_12BIT_MASK) >> 4;
        }
    } else {
        if (resolution == AMHW_HC32F460_ADC_RESOLUTION_8BIT) {
            return *(uint16_t *)(&(p_hw_adc->DR0) + channel) & AMHW_HC32F460_ADC_DATA_RIGHT_8BIT_MASK;
        } else if(resolution == AMHW_HC32F460_ADC_RESOLUTION_10BIT) {
            return *(uint16_t *)(&(p_hw_adc->DR0) + channel) & AMHW_HC32F460_ADC_DATA_RIGHT_10BIT_MASK;
        } else {
            return *(uint16_t *)(&(p_hw_adc->DR0) + channel) & AMHW_HC32F460_ADC_DATA_RIGHT_12BIT_MASK;
        }
    }
}

/**
 * \brief ADCģ�⿴�Ź��ж�ʹ��
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_awd_int_enable (amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->AWDCR_f.AWDIEN = AM_TRUE;
}

/**
 * \brief ADCģ�⿴�Ź��жϽ���
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_awd_int_disable (amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->AWDCR_f.AWDIEN = AM_FALSE;
}

/**
 * \brief ADCģ�⿴�Ź��ͷ�ֵ����
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] value      : �ͷ�ֵ�趨ֵ
 * \param[in] resolution : ת�����ȣ�amhw_hc32f460_adc_resolution_t��
 * \param[in] format     : ���ݶ��뷽ʽ��amhw_hc32f460_adc_data_align_format_t��
 */
am_static_inline
void amhw_hc32f460_adc_awd_low_threshold_set (amhw_hc32f460_adc_t                  *p_hw_adc,
                                              uint16_t                              value,
                                              amhw_hc32f460_adc_resolution_t        resolution,
                                              amhw_hc32f460_adc_data_align_format_t format)
{
    if (format == AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_LEFT) {
        p_hw_adc->AWDDR0 = value << (16 - resolution);
    } else {
        p_hw_adc->AWDDR0 = value;
    }
}

/**
 * \brief ADCģ�⿴�Ź��߷�ֵ����
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] value      : �ͷ�ֵ�趨ֵ
 * \param[in] resolution : ת�����ȣ�amhw_hc32f460_adc_resolution_t��
 * \param[in] format     : ���ݶ��뷽ʽ��amhw_hc32f460_adc_data_align_format_t��
 */
am_static_inline
void amhw_hc32f460_adc_awd_high_threshold_set (amhw_hc32f460_adc_t                  *p_hw_adc,
                                               uint16_t                              value,
                                               amhw_hc32f460_adc_resolution_t        resolution,
                                               amhw_hc32f460_adc_data_align_format_t format)
{
    if (format == AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_LEFT) {
        p_hw_adc->AWDDR1 = value << (16 - resolution);
    } else {
        p_hw_adc->AWDDR1 = value;
    }
}

/**
 * \brief ADCģ�⿴�Ź��Ƚ�ͨ������(ch0~ch15)
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] chan_mask  : ָ��ͨ�������루ch0~ch15��amhw_hc32f460_adc_chan_mask_t��
 */
am_static_inline
void amhw_hc32f460_adc_awd_chan0_15_set (amhw_hc32f460_adc_t     *p_hw_adc,
                                         uint16_t                 chan_mask)
{
    p_hw_adc->AWDCHSR0 = chan_mask;
}

/**
 * \brief ADCģ�⿴�Ź��Ƚ�ͨ������(ch16)
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] chan_mask  : ָ��ͨ�������루ch16��amhw_hc32f460_adc_chan_mask_t��
 */
am_static_inline
void amhw_hc32f460_adc_awd_chan_16_set (amhw_hc32f460_adc_t     *p_hw_adc,
                                        uint16_t                 chan_mask)
{
    p_hw_adc->AWDCHSR1_f.AWDCH16 = chan_mask;
}

/**
 * \brief ADCģ�⿴�Ź��Ƚ�״̬��ȡ(ch0~ch15)
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] chan_mask  : ָ��ͨ�������루ch0~ch15��amhw_hc32f460_adc_chan_mask_t��
 */
am_static_inline
uint16_t amhw_hc32f460_adc_awd_chan0_15_cmpstat_get (amhw_hc32f460_adc_t     *p_hw_adc)
{
    return p_hw_adc->AWDSR0;
}

/**
 * \brief ADCģ�⿴�Ź��Ƚ�ͨ����ȡ(ch16)
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] chan_mask  : ָ��ͨ�������루ch16��amhw_hc32f460_adc_chan_mask_t��
 */
am_static_inline
uint16_t amhw_hc32f460_adc_awd_chan16_cmpstat_get (amhw_hc32f460_adc_t     *p_hw_adc)
{
    return p_hw_adc->AWDSR1_f.AWDF16;
}

/**
 * \brief ADCģ�⿴�Ź��Ƚ�״̬���(ch0~ch15)
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] chan_mask  : ָ��ͨ�������루ch0~ch15��amhw_hc32f460_adc_chan_mask_t��
 */
am_static_inline
void amhw_hc32f460_adc_awd_chan0_15_cmpstat_clr (amhw_hc32f460_adc_t     *p_hw_adc,
                                                 uint16_t                 chan_mask)
{
    p_hw_adc->AWDSR0 &= (~chan_mask);
}

/**
 * \brief ADCģ�⿴�Ź��Ƚ�ͨ�����(ch16)
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] chan_mask  : ָ��ͨ�������루ch16��amhw_hc32f460_adc_chan_mask_t��
 */
am_static_inline
void amhw_hc32f460_adc_awd_chan16_cmpstat_clr (amhw_hc32f460_adc_t     *p_hw_adc,
                                               uint16_t                 chan_mask)
{
	p_hw_adc->AWDSR1_f.AWDF16 &= (~chan_mask);
}


/* ���Ź�����ѡ�� */
typedef enum {
    AMHW_HC32F460_ADC_AWD_SEQ_A_AND_B = 0,  /**<brief ����A��Bɨ�����ʱ�����ADC_SEQCMP�ж�/�¼� */
    AMHW_HC32F460_ADC_AWD_SEQ_A_ONLY  = 1,  /**<brief ����Aɨ�����ʱ���ADC_SEQCMP�ж�/�¼�������B����� */
    AMHW_HC32F460_ADC_AWD_SEQ_B_ONLY  = 2,  /**<brief ����Bɨ�����ʱ���ADC_SEQCMP�ж�/�¼�������A����� */
}amhw_hc32f460_adc_awd_seq_sel_t;


/**
 * \brief ADCģ�⿴�Ź�����ѡ��
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_awd_seq_set (amhw_hc32f460_adc_t             *p_hw_adc,
                                    amhw_hc32f460_adc_awd_seq_sel_t  flag)
{
    p_hw_adc->AWDCR_f.AWDSS = flag;
}

typedef enum {
    AMHW_HC32F460_ADC_AWD_CMPMODE0 = 0, /**<brief ת�����<AWDDR0,��ת�����>AWDDR1ʱ���Ƚ��������� */
    AMHW_HC32F460_ADC_AWD_CMPMODE1 = 1, /**<brief AWDDR0 <= ת����� <= AWDDR1 ʱ���Ƚ��������� */
}amhw_hc32f460_adc_awd_cmpmode_t;

/**
 * \brief ADCģ�⿴�Ź��Ƚ�ģʽ����
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_awd_cmp_mode_set (amhw_hc32f460_adc_t             *p_hw_adc,
                                         amhw_hc32f460_adc_awd_cmpmode_t  flag)
{
    p_hw_adc->AWDCR_f.AWDMD = flag;
}

/**
 * \brief ADCģ�⿴�Ź��ȽϹ���ʹ��
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_awd_enable (amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->AWDCR_f.AWDEN = AM_TRUE;
}

/**
 * \brief ADCģ�⿴�Ź��ȽϹ��ܽ�ֹ
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_awd_disable (amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->AWDCR_f.AWDEN = AM_FALSE;
}

/**
 * \brief ADC�����жϽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_all_int_disable (amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->ICR = 0;
    p_hw_adc->AWDCR_f.AWDIEN = 0;
}


/**
 * \brief ADC�ɱ�̷Ŵ������ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_pga_enable (amhw_hc32f460_adc_t  *p_hw_adc)
{
    p_hw_adc->PGACR_f.PGACTL = 0xE;
}

/**
 * \brief ADC�ɱ�̷Ŵ����������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 */
am_static_inline
void amhw_hc32f460_adc_pga_disable (amhw_hc32f460_adc_t  *p_hw_adc)
{
    p_hw_adc->PGACR_f.PGACTL = 0x0;
}

typedef enum {
    AMHW_HC32F460_ADC_PGA_GAIN_2_000 = 0, /**<brief �� 2.000 */
    AMHW_HC32F460_ADC_PGA_GAIN_2_133,     /**<brief �� 2.133 */
    AMHW_HC32F460_ADC_PGA_GAIN_2_286,     /**<brief �� 2.286 */
    AMHW_HC32F460_ADC_PGA_GAIN_2_667,     /**<brief �� 2.667 */
    AMHW_HC32F460_ADC_PGA_GAIN_2_909,     /**<brief �� 2.909 */
    AMHW_HC32F460_ADC_PGA_GAIN_3_200,     /**<brief �� 3.2 */
    AMHW_HC32F460_ADC_PGA_GAIN_3_556,     /**<brief �� 3.556 */
    AMHW_HC32F460_ADC_PGA_GAIN_4_000,     /**<brief �� 4.000 */
    AMHW_HC32F460_ADC_PGA_GAIN_4_571,     /**<brief �� 4.571 */
    AMHW_HC32F460_ADC_PGA_GAIN_5_333,     /**<brief �� 5.333 */
    AMHW_HC32F460_ADC_PGA_GAIN_6_400,     /**<brief �� 6.4 */
    AMHW_HC32F460_ADC_PGA_GAIN_8_000,     /**<brief �� 8 */
    AMHW_HC32F460_ADC_PGA_GAIN_10_667,    /**<brief �� 10.667 */
    AMHW_HC32F460_ADC_PGA_GAIN_16,        /**<brief �� 16 */
    AMHW_HC32F460_ADC_PGA_GAIN_32,        /**<brief �� 32 */
} amhw_hc32f460_adc_pga_gain_value_t;


/**
 * \brief ADC�ɱ�̷Ŵ���������汶������
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] gain_value : ���汶����amhw_hc32f460_adc_pga_gain_value_t��
 */
am_static_inline
void amhw_hc32f460_adc_pga_gain_set(amhw_hc32f460_adc_t               *p_hw_adc,
                                    amhw_hc32f460_adc_pga_gain_value_t gain_value)
{
    p_hw_adc->PGAGSR_f.GAIN = gain_value;
}

/**
 * \brief ADC�ɱ�̷Ŵ������ģ������ѡ��
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] adc_in_num : ADC������(ѡ���ڲ�ģ��ͨ��ʱֻ����8bitDAC_1)
 */
am_static_inline
void amhw_hc32f460_adc_pga_analog_input_set(amhw_hc32f460_adc_t               *p_hw_adc,
                                            amhw_hc32f460_adc_chan_sel_t       adc_in_num)
{
    p_hw_adc->PGAINSR0_f.PGAINSEL = (1 << adc_in_num);
}

typedef enum {
    AMHW_HC32F460_ADC_PGA_N_INPUT_PGAVSS = 0,  /* ʹ���ⲿ�˿�PGAVSS��ΪPGA�������� */
    AMHW_HC32F460_ADC_PGA_N_INPUT_INAVSS = 1,  /* ʹ���ڲ�ģ���AVSS��ΪPGA�������� */
}amhw_hc32f460_adc_pga_negative_input_t;


/**
 * \brief ADC�ɱ�̷Ŵ��������������ѡ��
 *
 * \param[in] p_hw_adc   : ָ��ADC�Ĵ�����ָ��
 * \param[in] adc_in_num : ADC������
 */
am_static_inline
void amhw_hc32f460_adc_pga_negative_input_set(amhw_hc32f460_adc_t                    *p_hw_adc,
                                              amhw_hc32f460_adc_pga_negative_input_t  flag)
{
    p_hw_adc->PGAINSR1_f.PGAVSSEN = flag;
}

/**
 * \brief ADCЭͬģʽͬ���ӳ�ʱ������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] time     : ͬ���ӳ�ʱ�䣨t = time * PCLK4, time = 1~255��
 *
 * note : ��SYNCENΪ0ʱ���øüĴ������벻Ҫд��0x00
 */
am_static_inline
void amhw_hc32f460_adc_sync_delaytime_set(amhw_hc32f460_adc_t *p_hw_adc,
                                          uint8_t              time)
{
    p_hw_adc->SYNCCR_f.SYNCDLY = time;
}

#define  AMHW_HC32F460_ADC_SYNC_MODE_SINGLE   (0 << 2) /* ���δ��� */
#define  AMHW_HC32F460_ADC_SYNC_MODE_CYCLE    (1 << 2) /* ѭ������ */

#define  AMHW_HC32F460_ADC_SYNC_MODE_DELAY    (0 << 1) /* �ӳٴ���ģʽ */
#define  AMHW_HC32F460_ADC_SYNC_MODE_PARALLEL (1 << 1) /* ���д���ģʽ */

#define  AMHW_HC32F460_ADC_SYNC_MODE_ADC0_1   (0 << 0) /* ADC0��ADC1ͬ��������ADC2�������� */
#define  AMHW_HC32F460_ADC_SYNC_MODE_ADC0_1_2 (1 << 0) /* ADC0��ADC1��ADC2ͬ������ */

/**
 * \brief ADCЭͬģʽѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] mode     : Эͬ����ģʽ
 *
 * note : ��SYNCENΪ0ʱ���øüĴ���
 *        ʹ�õ��δ���ʱ���뽫��Ҫͬ����ADC����Ϊ����A����ɨ�裬������A����ɨ��ģʽ��ʹ�ô���ģʽʱ��
 *        �뽫ADC����Ϊ����A����ɨ��ģʽ��
 */
am_static_inline
void amhw_hc32f460_adc_sync_mode_set(amhw_hc32f460_adc_t *p_hw_adc,
                                     uint8_t              mode)
{
    p_hw_adc->SYNCCR_f.SYNCMD = mode;
}


/**
 * \brief ADCͬ��ģʽ���
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * note : ͬ��ģʽֻ֧������A����SYNCENд1֮ǰ���뽫����ͬ���ļ���ADC������B�رգ���������Aѡ����ͬ
 *        ��Ŀ��ͨ����������ͬ��ͨ������ʱ�䣬�Ա����ADCɨ��ʱ�䲻һ�£����������ͬ��ʧ�ܡ����ǿ��
 *        ֹͣת��ʱ��SYNCEN�Զ����㡣
 */
am_static_inline
void amhw_hc32f460_adc_sync_mode_enable(amhw_hc32f460_adc_t *p_hw_adc)
{
    p_hw_adc->SYNCCR_f.SYNCEN = AM_TRUE;
}


#define HC32F460_AOS_ADC1_ITRGSEL0    ((uint32_t *)(0X40010858))
#define HC32F460_AOS_ADC1_ITRGSEL1    ((uint32_t *)(0X4001085C))
#define HC32F460_AOS_ADC2_ITRGSEL0    ((uint32_t *)(0X40010860))
#define HC32F460_AOS_ADC2_ITRGSEL1    ((uint32_t *)(0X40010864))

/**
 * \brief ADC�ڲ�����ʹ��
 *
 * \param[in] p_hw_adc : ָ��AOS ADC�����Ĵ�����ָ��
 * \param[in] event_src: �¼���ţ�en_event_src_tö������
 */
am_static_inline
void amhw_hc32f460_aos_adc_in_event_trigger_sel(uint32_t       *p_adc_itrgsel,
                                                uint32_t        event_src) {
    *p_adc_itrgsel = event_src;
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

#endif /* __AMHW_HC32F460_ADC_H */

/* end of file */
