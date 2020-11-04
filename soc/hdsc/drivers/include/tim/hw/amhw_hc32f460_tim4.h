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
 * - 1.00 
 * \endinternal
 */

#ifndef __AMHW_HC32F460_TIM4_H
#define __AMHW_HC32F460_TIM4_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

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
 *******************************************************************************
 ** \brief Timer4 counter mode enumeration
 **
 ******************************************************************************/
typedef enum tim4_functional_state
{
    TIM4_DISABLE = 0u,
    TIM4_ENABLE  = 1u,
} tim4_functional_state_t;

typedef enum tim4_counter_mode
{
    TIM4_COUNT_MODE_SAWTOOTH_WAVE   = 0u, 
    TIM4_COUNT_MODE_TRIANGULAR_WAVE = 1u, 
}tim4_counter_mode_t;

typedef enum tim4_count_dir
{
    TIM4_COUNT_DIR_DOWN = 0u,            
    TIM4_COUNT_DIR_UP   = 1u,            
} tim4_count_dir_t;

typedef enum tim4_irq_type
{
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH1 = 0u,               
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH2 = 1u,              
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH3 = 2u,              
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH4 = 3u,              
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH5 = 4u,              
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH6 = 5u,              
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH7 = 6u,              
    TIMER4_IRQ_CAPTURE_OR_COMPARE_CH8 = 7u,              
    TIMER4_IRQ_OVERFLOW               = 8u,              
    TIMER4_IRQ_UNDERFLOW              = 9u,              
} tim4_irq_type_t;

/******************************************************************************/
typedef enum timer4_cnt_int
{
    TIMER4_CNT_ZERO_MATCH_INT = (1ul << 8),    
    TIMER4_CNT_PEAK_MATCH_INT = (1ul << 13),    
} timer4_cnt_int_t;

/**
 * \brief TMR4 ͨ�ÿ���״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t OCEH                      : 1;  /**< \brief �˿����ʹ��H*/
    __IO uint16_t OCEL                      : 1;  /**< \brief �˿����ʹ��L*/
    __IO uint16_t OCPH                      : 1;  /**< \brief �����Чʱ�˿�״̬H*/
    __IO uint16_t OCPL                      : 1;  /**< \brief �����Чʱ�˿�״̬L*/
    __IO uint16_t OCIEH                     : 1;  /**< \brief ����ƥ��H�ж�ʹ��*/
    __IO uint16_t OCIEL                     : 1;  /**< \brief ����ƥ��L�ж�ʹ��*/
    __IO uint16_t OCFH                      : 1;  /**< \brief ����ƥ��H*/
    __IO uint16_t OCFL                      : 1;  /**< \brief ����ƥ��L*/
    uint16_t RESERVED8                      : 8;  /**< \brief ����*/
} stc_tmr4_ocsr_field_t;

/**
 * \brief TMR4 ͨ����չ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t CHBUFEN                   : 2;  /**< \brief OCCRxh���洫��*/
    __IO uint16_t CLBUFEN                   : 2;  /**< \brief OCCRxl���洫��*/
    __IO uint16_t MHBUFEN                   : 2;  /**< \brief OCMRxh����ת��*/
    __IO uint16_t MLBUFEN                   : 2;  /**< \brief OCMRxl����ת��*/
    __IO uint16_t LMCH                      : 1;  /**< \brief ���ڼ����Ӧ��������H*/
    __IO uint16_t LMCL                      : 1;  /**< \brief ���ڼ����Ӧ��������L*/
    __IO uint16_t LMMH                      : 1;  /**< \brief ���ڼ����Ӧ��������H*/
    __IO uint16_t LMML                      : 1;  /**< \brief ���ڼ����Ӧ��������L*/
    __IO uint16_t MCECH                     : 1;  /**< \brief ��չ����ʹ��H*/
    __IO uint16_t MCECL                     : 1;  /**< \brief ��չ����ʹ��L*/
    uint16_t RESERVED14                     : 2;  /**< \brief ����*/
} stc_tmr4_ocer_field_t;

/**
 * \brief TMR4 ͨ��ģʽ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t OCFDCH                    : 1;  /**< \brief ���¼���OCFH״̬H*/
    __IO uint16_t OCFPKH                    : 1;  /**< \brief �����OCFH״̬H*/
    __IO uint16_t OCFUCH                    : 1;  /**< \brief ���ϼ���OCFH״̬H*/
    __IO uint16_t OCFZRH                    : 1;  /**< \brief �����OCFH״̬H*/
    __IO uint16_t OPDCH                     : 2;  /**< \brief ���¼����˿�״̬H*/
    __IO uint16_t OPPKH                     : 2;  /**< \brief �����˿�״̬H*/
    __IO uint16_t OPUCH                     : 2;  /**< \brief ���ϼ����˿�״̬H*/
    __IO uint16_t OPZRH                     : 2;  /**< \brief �����˿�״̬H*/
    __IO uint16_t OPNPKH                    : 2;  /**< \brief �����˿�״̬H*/
    __IO uint16_t OPNZRH                    : 2;  /**< \brief �����˿�״̬H*/
} stc_tmr4_ocmrh_field_t;

/**
 * \brief TMR4 ͨ��ģʽ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t OCFDCL                    : 1;  /**< \brief ���¼���OCFL״̬L*/
    __IO uint32_t OCFPKL                    : 1;  /**< \brief �����OCFL״̬L*/
    __IO uint32_t OCFUCL                    : 1;  /**< \brief ���ϼ���OCFL״̬L*/
    __IO uint32_t OCFZRL                    : 1;  /**< \brief �����OCFL״̬L*/
    __IO uint32_t OPDCL                     : 2;  /**< \brief ���¼����˿�״̬L*/
    __IO uint32_t OPPKL                     : 2;  /**< \brief �����˿�״̬L*/
    __IO uint32_t OPUCL                     : 2;  /**< \brief ���ϼ����˿�״̬L*/
    __IO uint32_t OPZRL                     : 2;  /**< \brief �����˿�״̬L*/
    __IO uint32_t OPNPKL                    : 2;  /**< \brief �����˿�״̬L*/
    __IO uint32_t OPNZRL                    : 2;  /**< \brief �����˿�״̬L*/
    __IO uint32_t EOPNDCL                   : 2;  /**< \brief �������¼����˿�״̬L*/
    __IO uint32_t EOPNUCL                   : 2;  /**< \brief �������ϼ����˿�״̬L*/
    __IO uint32_t EOPDCL                    : 2;  /**< \brief �������¼����˿�״̬L*/
    __IO uint32_t EOPPKL                    : 2;  /**< \brief ���������˿�״̬L*/
    __IO uint32_t EOPUCL                    : 2;  /**< \brief �������ϼ����˿�״̬L*/
    __IO uint32_t EOPZRL                    : 2;  /**< \brief ���������˿�*/
    __IO uint32_t EOPNPKL                   : 2;  /**< \brief ���������˿�״̬L*/
    __IO uint32_t EOPNZRL                   : 2;  /**< \brief ���������˿�״̬L*/
} stc_tmr4_ocmrl_field_t;

/**
 * \brief TMR4 ����״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t CKDIV                     : 4;  /**< \brief ����ʱ�ӷ�Ƶ*/
    __IO uint16_t CLEAR                     : 1;  /**< \brief ����������*/
    __IO uint16_t MODE                      : 1;  /**< \brief ����ģʽ*/
    __IO uint16_t STOP                      : 1;  /**< \brief ������ʹ��*/
    __IO uint16_t BUFEN                     : 1;  /**< \brief ����ʹ��*/
    __IO uint16_t IRQPEN                    : 1;  /**< \brief �����ж�ʹ��*/
    __IO uint16_t IRQPF                     : 1;  /**< \brief ����״̬*/
    uint16_t RESERVED10                     : 3;  /**< \brief ����*/
    __IO uint16_t IRQZEN                    : 1;  /**< \brief �����ж�ʹ��*/
    __IO uint16_t IRQZF                     : 1;  /**< \brief ����״̬*/
    __IO uint16_t ECKEN                     : 1;  /**< \brief ʱ��Դѡ��*/
} stc_tmr4_ccsr_field_t;

/**
 * \brief TMR4 ��Ч���ڼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t ZIM                       : 4;  /**< \brief �����ж������趨*/
    __IO uint16_t PIM                       : 4;  /**< \brief �����ж������趨*/
    __IO uint16_t ZIC                       : 4;  /**< \brief �����ж�����״̬*/
    __IO uint16_t PIC                       : 4;  /**< \brief �����ж�����״̬*/
} stc_tmr4_cvpr_field_t;

/**
 * \brief TMR4 PWM�������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t DIVCK                     : 4;  /**< \brief ����ʱ�ӷ�Ƶ*/
    __IO uint16_t PWMMD                     : 2;  /**< \brief PWM���ģʽ*/
    __IO uint16_t LVLS                      : 2;  /**< \brief PWM������Կ���*/
    uint16_t RESERVED8                      : 8;  /**< \brief ����*/
} stc_tmr4_pocr_field_t;

/**
 * \brief TMR4 ���ؿ���״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t RTIDU                     : 1;  /**< \brief �����ж�����U*/
    __IO uint16_t RTIDV                     : 1;  /**< \brief �����ж�����V*/
    __IO uint16_t RTIDW                     : 1;  /**< \brief �����ж�����W*/
    uint16_t RESERVED3                      : 1;  /**< \brief ����*/
    __IO uint16_t RTIFU                     : 1;  /**< \brief ����ƥ��״̬U*/
    __IO uint16_t RTICU                     : 1;  /**< \brief �������ƥ��״̬U*/
    __IO uint16_t RTEU                      : 1;  /**< \brief ���ؼ���������U*/
    __IO uint16_t RTSU                      : 1;  /**< \brief ���ؼ�����ֹͣU*/
    __IO uint16_t RTIFV                     : 1;  /**< \brief ����ƥ��״̬V*/
    __IO uint16_t RTICV                     : 1;  /**< \brief �������ƥ��״̬V*/
    __IO uint16_t RTEV                      : 1;  /**< \brief ���ؼ���������V*/
    __IO uint16_t RTSV                      : 1;  /**< \brief ���ؼ�����ֹͣV*/
    __IO uint16_t RTIFW                     : 1;  /**< \brief ����ƥ��״̬W*/
    __IO uint16_t RTICW                     : 1;  /**< \brief �������ƥ��״̬W*/
    __IO uint16_t RTEW                      : 1;  /**< \brief ���ؼ���������W*/
    __IO uint16_t RTSW                      : 1;  /**< \brief ���ؼ�����ֹͣW*/
} stc_tmr4_rcsr_field_t;

/**
 * \brief TMR4 ר�ÿ���״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t BUFEN                     : 2;  /**< \brief SCCR&SCMR���洫��*/
    __IO uint16_t EVTOS                     : 3;  /**< \brief EVT���ѡ��*/
    __IO uint16_t LMC                       : 1;  /**< \brief ���ڼ����Ӧ��������*/
    uint16_t RESERVED6                      : 2;  /**< \brief ����*/
    __IO uint16_t EVTMS                     : 1;  /**< \brief EVTģʽѡ��*/
    __IO uint16_t EVTDS                     : 1;  /**< \brief EVT��ʱ����ѡ��*/
    uint16_t RESERVED10                     : 2;  /**< \brief ����*/
    __IO uint16_t DEN                       : 1;  /**< \brief ���¼���EVTʹ��*/
    __IO uint16_t PEN                       : 1;  /**< \brief �����EVTʹ��*/
    __IO uint16_t UEN                       : 1;  /**< \brief ���ϼ���EVTʹ��*/
    __IO uint16_t ZEN                       : 1;  /**< \brief �����EVTʹ��*/
} stc_tmr4_scsr_field_t;

/**
 * \brief TMR4 ר��ģʽ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t AMC                       : 4;  /**< \brief ר���¼�������ڼ��ֵ*/
    uint16_t RESERVED4                      : 2;  /**< \brief ����*/
    __IO uint16_t MZCE                      : 1;  /**< \brief ���ڼ����Ӧʹ��*/
    __IO uint16_t MPCE                      : 1;  /**< \brief ���ڼ����Ӧʹ��*/
    uint16_t RESERVED8                      : 8;  /**< \brief ����*/
} stc_tmr4_scmr_field_t;

/**
 * \brief TMR4 EMB����״̬�Ĵ���
 */
typedef struct
{
    uint16_t RESERVED0                      : 7;  /**< \brief ����*/
    __IO uint16_t HOLD                      : 1;  /**< \brief PWM����*/
    uint16_t RESERVED8                      : 8;  /**< \brief ����*/
} stc_tmr4_ecsr_field_t;

/**
 * \brief TMR4 EMB��չ���ƼĴ���
 */
typedef struct
{
    __IO uint16_t EMBVAL                    : 2;  /**< \brief EMB״̬����*/
    uint16_t RESERVED2                      :14;  /**< \brief ����*/
} stc_tmr4_cr_ecer1_field_t;

/**
 * \brief TMR4 EMB��չ���ƼĴ���
 */
typedef struct
{
    __IO uint16_t EMBVAL                    : 2;  /**< \brief EMB״̬����*/
    uint16_t RESERVED2                      :14;  /**< \brief ����*/
} stc_tmr4_cr_ecer2_field_t;

/**
 * \brief TMR4 EMB��չ���ƼĴ���
 */
typedef struct
{
    __IO uint16_t EMBVAL                    : 2;  /**< \brief EMB״̬����*/
    uint16_t RESERVED2                      :14;  /**< \brief ����*/
} stc_tmr4_cr_ecer3_field_t;

typedef struct
{
    uint8_t RESERVED0[2];               /**< \brief ����*/
    __IO uint16_t OCCRUH;               /**< \brief ͨ�ñȽϻ�׼�Ĵ���UH*/
    uint8_t RESERVED1[2];               /**< \brief ����*/
    __IO uint16_t OCCRUL;               /**< \brief ͨ�ñȽϻ�׼�Ĵ���UL*/
    uint8_t RESERVED2[2];               /**< \brief ����*/
    __IO uint16_t OCCRVH;               /**< \brief ͨ�ñȽϻ�׼�Ĵ���VH*/
    uint8_t RESERVED3[2];               /**< \brief ����*/
    __IO uint16_t OCCRVL;               /**< \brief ͨ�ñȽϻ�׼�Ĵ���VL*/
    uint8_t RESERVED4[2];               /**< \brief ����*/
    __IO uint16_t OCCRWH;               /**< \brief ͨ�ñȽϻ�׼�Ĵ���WH*/
    uint8_t RESERVED5[2];               /**< \brief ����*/
    __IO uint16_t OCCRWL;               /**< \brief ͨ�ñȽϻ�׼�Ĵ���WL*/
    union
    {
        __IO uint16_t OCSRU;            /**< \brief ͨ�ÿ���״̬�Ĵ���U*/
        stc_tmr4_ocsr_field_t OCSRU_f;
    };
    union
    {
        __IO uint16_t OCERU;            /**< \brief ͨ����չ���ƼĴ���U*/
        stc_tmr4_ocer_field_t OCERU_f;
    };
    union
    {
        __IO uint16_t OCSRV;            /**< \brief ͨ�ÿ���״̬�Ĵ���V*/
        stc_tmr4_ocsr_field_t OCSRV_f;
    };
    union
    {
        __IO uint16_t OCERV;            /**< \brief ͨ����չ���ƼĴ���V*/
        stc_tmr4_ocer_field_t OCERV_f;
    };
    union
    {
        __IO uint16_t OCSRW;            /**< \brief ͨ�ÿ���״̬�Ĵ���W*/
        stc_tmr4_ocsr_field_t OCSRW_f;
    };
    union
    {
        __IO uint16_t OCERW;            /**< \brief ͨ����չ���ƼĴ���W*/
        stc_tmr4_ocer_field_t OCERW_f;
    };
    union
    {
        __IO uint16_t OCMRHUH;          /**< \brief ͨ��ģʽ���ƼĴ���UH*/
        stc_tmr4_ocmrh_field_t OCMRHUH_f;
    };
    uint8_t RESERVED13[2];              /**< \brief ����*/
    union
    {
        __IO uint32_t OCMRLUL;          /**< \brief ͨ��ģʽ���ƼĴ���UL*/
        stc_tmr4_ocmrl_field_t OCMRLUL_f;
    };
    union
    {
        __IO uint16_t OCMRHVH;          /**< \brief ͨ��ģʽ���ƼĴ���VH*/
        stc_tmr4_ocmrh_field_t OCMRHVH_f;
    };
    uint8_t RESERVED15[2];              /**< \brief ����*/
    union
    {
        __IO uint32_t OCMRLVL;          /**< \brief ͨ��ģʽ���ƼĴ���VL*/
        stc_tmr4_ocmrl_field_t OCMRLVL_f;
    };
    union
    {
        __IO uint16_t OCMRHWH;          /**< \brief ͨ��ģʽ���ƼĴ���WH*/
        stc_tmr4_ocmrh_field_t OCMRHWH_f;
    };
    uint8_t RESERVED17[2];              /**< \brief ����*/
    union
    {
        __IO uint32_t OCMRLWL;          /**< \brief ͨ��ģʽ���ƼĴ���WL*/
        stc_tmr4_ocmrl_field_t OCMRLWL_f;
    };
    uint8_t RESERVED18[6];              /**< \brief ����*/
    __IO uint16_t CPSR;                 /**< \brief ���ڻ�׼�Ĵ���*/
    uint8_t RESERVED19[2];              /**< \brief ����*/
    __IO uint16_t CNTR;                 /**< \brief ����ֵ�Ĵ���*/
    union
    {
        __IO uint16_t CCSR;             /**< \brief ����״̬�Ĵ���*/
        stc_tmr4_ccsr_field_t CCSR_f;
    };
    union
    {
        __IO uint16_t CVPR;             /**< \brief ��Ч���ڼĴ���*/
        stc_tmr4_cvpr_field_t CVPR_f;
    };
    uint8_t RESERVED22[54];             /**< \brief ����*/
    __IO uint16_t PFSRU;                /**< \brief PWM�˲����ƼĴ���U*/
    __IO uint16_t PDARU;                /**< \brief PWM�������ƼĴ���AU*/
    __IO uint16_t PDBRU;                /**< \brief PWM�������ƼĴ���BU*/
    uint8_t RESERVED25[2];              /**< \brief ����*/
    __IO uint16_t PFSRV;                /**< \brief PWM�˲����ƼĴ���V*/
    __IO uint16_t PDARV;                /**< \brief PWM�������ƼĴ���AU*/
    __IO uint16_t PDBRV;                /**< \brief PWM�������ƼĴ���BU*/
    uint8_t RESERVED28[2];              /**< \brief ����*/
    __IO uint16_t PFSRW;                /**< \brief PWM�˲����ƼĴ���V*/
    __IO uint16_t PDARW;                /**< \brief PWM�������ƼĴ���AW*/
    __IO uint16_t PDBRW;                /**< \brief PWM�������ƼĴ���BW*/
    union
    {
        __IO uint16_t POCRU;            /**< \brief PWM�������ƼĴ���U*/
        stc_tmr4_pocr_field_t POCRU_f;
    };
    uint8_t RESERVED32[2];              /**< \brief ����*/
    union
    {
        __IO uint16_t POCRV;            /**< \brief PWM�������ƼĴ���V*/
        stc_tmr4_pocr_field_t POCRV_f;
    };
    uint8_t RESERVED33[2];              /**< \brief ����*/
    union
    {
        __IO uint16_t POCRW;            /**< \brief PWM�������ƼĴ���W*/
        stc_tmr4_pocr_field_t POCRW_f;
    };
    uint8_t RESERVED34[2];              /**< \brief ����*/
    union
    {
        __IO uint16_t RCSR;             /**< \brief ���ؿ���״̬�Ĵ���*/
        stc_tmr4_rcsr_field_t RCSR_f;
    };
    uint8_t RESERVED35[12];             /**< \brief ����*/
    __IO uint16_t SCCRUH;               /**< \brief ר�ñȽϻ�׼�Ĵ���UH*/
    uint8_t RESERVED36[2];              /**< \brief ����*/
    __IO uint16_t SCCRUL;               /**< \brief ר�ñȽϻ�׼�Ĵ���UL*/
    uint8_t RESERVED37[2];              /**< \brief ����*/
    __IO uint16_t SCCRVH;               /**< \brief ר�ñȽϻ�׼�Ĵ���VH*/
    uint8_t RESERVED38[2];              /**< \brief ����*/
    __IO uint16_t SCCRVL;               /**< \brief ר�ñȽϻ�׼�Ĵ���VL*/
    uint8_t RESERVED39[2];              /**< \brief ����*/
    __IO uint16_t SCCRWH;               /**< \brief ר�ñȽϻ�׼�Ĵ���WH*/
    uint8_t RESERVED40[2];              /**< \brief ����*/
    __IO uint16_t SCCRWL;               /**< \brief ר�ñȽϻ�׼�Ĵ���WL*/
    union
    {
        __IO uint16_t SCSRUH;           /**< \brief ר�ÿ���״̬�Ĵ���UH*/
        stc_tmr4_scsr_field_t SCSRUH_f;
    };
    union
    {
        __IO uint16_t SCMRUH;           /**< \brief ר��ģʽ���ƼĴ���UH*/
        stc_tmr4_scmr_field_t SCMRUH_f;
    };
    union
    {
        __IO uint16_t SCSRUL;           /**< \brief ר�ÿ���״̬�Ĵ���UL*/
        stc_tmr4_scsr_field_t SCSRUL_f;
    };
    union
    {
        __IO uint16_t SCMRUL;           /**< \brief ר��ģʽ���ƼĴ���UL*/
        stc_tmr4_scmr_field_t SCMRUL_f;
    };
    union
    {
        __IO uint16_t SCSRVH;           /**< \brief ר�ÿ���״̬�Ĵ���VH*/
        stc_tmr4_scsr_field_t SCSRVH_f;
    };
    union
    {
        __IO uint16_t SCMRVH;           /**< \brief ר��ģʽ���ƼĴ���VH*/
        stc_tmr4_scmr_field_t SCMRVH_f;
    };
    union
    {
        __IO uint16_t SCSRVL;           /**< \brief ר�ÿ���״̬�Ĵ���VL*/
        stc_tmr4_scsr_field_t SCSRVL_f;
    };
    union
    {
        __IO uint16_t SCMRVL;           /**< \brief ר��ģʽ���ƼĴ���VL*/
        stc_tmr4_scmr_field_t SCMRVL_f;
    };
    union
    {
        __IO uint16_t SCSRWH;           /**< \brief ר�ÿ���״̬�Ĵ���WH*/
        stc_tmr4_scsr_field_t SCSRWH_f;
    };
    union
    {
        __IO uint16_t SCMRWH;           /**< \brief ר��ģʽ���ƼĴ���WH*/
        stc_tmr4_scmr_field_t SCMRWH_f;
    };
    union
    {
        __IO uint16_t SCSRWL;           /**< \brief ר�ÿ���״̬�Ĵ���WL*/
        stc_tmr4_scsr_field_t SCSRWL_f;
    };
    union
    {
        __IO uint16_t SCMRWL;           /**< \brief ר��ģʽ���ƼĴ���WL*/
        stc_tmr4_scmr_field_t SCMRWL_f;
    };
    uint8_t RESERVED53[16];             /**< \brief ����*/
    union
    {
        __IO uint16_t ECSR;             /**< \brief EMB����״̬�Ĵ���*/
        stc_tmr4_ecsr_field_t ECSR_f;
    };
}amhw_hc32f460_tim4_t;
;

typedef struct
{
    union
    {
        __IO uint16_t ECER1;              /**< \brief EMB��չ���ƼĴ���1*/
        stc_tmr4_cr_ecer1_field_t ECER1_f;
    };
    uint8_t RESERVED1[2];                 /**< \brief ����*/
    union
    {
        __IO uint16_t ECER2;              /**< \brief EMB��չ���ƼĴ���2*/
        stc_tmr4_cr_ecer2_field_t ECER2_f;
    };
    uint8_t RESERVED2[2];                 /**< \brief ����*/
    union
    {
        __IO uint16_t ECER3;              /**< \brief EMB��չ���ƼĴ���3*/
        stc_tmr4_cr_ecer3_field_t ECER3_f;
    };
} amhw_hc32f460_tim4_cr_t;

typedef enum timer4_cnt_int_mask
{
    TIMER4_CNT_INT_MASK0  = 0u,                 
    TIMER4_CNT_INT_MASK1  = 1u,                
    TIMER4_CNT_INT_MASK2  = 2u,                
    TIMER4_CNT_INT_MASK3  = 3u,                
    TIMER4_CNT_INT_MASK4  = 4u,                
    TIMER4_CNT_INT_MASK5  = 5u,                
    TIMER4_CNT_INT_MASK6  = 6u,                
    TIMER4_CNT_INT_MASK7  = 7u,                
    TIMER4_CNT_INT_MASK8  = 8u,                
    TIMER4_CNT_INT_MASK9  = 9u,                
    TIMER4_CNT_INT_MASK10 = 10u,               
    TIMER4_CNT_INT_MASK11 = 11u,               
    TIMER4_CNT_INT_MASK12 = 12u,               
    TIMER4_CNT_INT_MASK13 = 13u,               
    TIMER4_CNT_INT_MASK14 = 14u,               
    TIMER4_CNT_INT_MASK15 = 15u,               
} timer4_cnt_int_mask_t;

typedef enum timer4_oco_ch
{
    TIMER4_OCO_OUH = 0U,                       
    TIMER4_OCO_OUL = 1U,                      
    TIMER4_OCO_OVH = 2U,                      
    TIMER4_OCO_OVL = 3U,                      
    TIMER4_OCO_OWH = 4U,                      
    TIMER4_OCO_OWL = 5U,                      
} timer4_oco_ch_t;

typedef enum en_timer4_oco_occr_buf
{
    OccrBufDisable                              = 0u,  
    OccrBufTrsfByCntZero                        = 1u, 
    OccrBufTrsfByCntPeak                        = 2u, 
    OccrBufTrsfByCntZeroOrCntPeak               = 3u, 
    OccrBufTrsfByCntZeroZicZero                 = 4u, 
    OccrBufTrsfByCntPeakPicZero                 = 5u, 
    OccrBufTrsfByCntZeroZicZeroOrCntPeakPicZero = 6u,                                                       
} en_timer4_oco_occr_buf_t;

typedef enum en_timer4_oco_ocmr_buf
{
    OcmrBufDisable                              = 0u,  
    OcmrBufTrsfByCntZero                        = 1u, 
    OcmrBufTrsfByCntPeak                        = 2u, 
    OcmrBufTrsfByCntZeroOrCntPeak               = 3u,  
    OcmrBufTrsfByCntZeroZicZero                 = 4u, 
    OcmrBufTrsfByCntPeakPicZero                 = 5u, 
    OcmrBufTrsfByCntZeroZicZeroOrCntPeakPicZero = 6u, 
                                                      
} en_timer4_oco_ocmr_buf_t;

typedef enum en_timer4_oco_port_level
{
    OcPortLevelLow  = 0u,                   
    OcPortLevelHigh = 1u,                   
} en_timer4_oco_port_level_t;

typedef struct stc_timer4_oco_init
{
    en_timer4_oco_occr_buf_t   enOccrBufMode;  

    en_timer4_oco_ocmr_buf_t   enOcmrBufMode;  

    en_timer4_oco_port_level_t enPortLevel;    

    tim4_functional_state_t      enOcoIntCmd;    
} stc_timer4_oco_init_t;

#define TMR4_OCCRx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->OCCRUH + ((uint32_t)(__CH__))*4ul)
#define TMR4_OCMRx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->OCMRHUH + ((uint32_t)(__CH__))*4ul)
#define TMR4_OCERx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->OCERU + (((uint32_t)(__CH__))/2ul)*4ul)
#define TMR4_OCSRx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->OCSRU + (((uint32_t)(__CH__))/2ul)*4ul)

#define IS_VALID_OCO_HIGH_CH(x)                                                \
(   (TIMER4_OCO_OUH == (x))                   ||                              \
    (TIMER4_OCO_OVH == (x))                   ||                              \
    (TIMER4_OCO_OWH == (x)))

#define IS_VALID_OCO_LOW_CH(x)                                                 \
(   (TIMER4_OCO_OUL == (x))                   ||                                 \
    (TIMER4_OCO_OVL == (x))                   ||                                 \
    (TIMER4_OCO_OWL == (x)))

typedef enum en_timer4_oco_op_state
{
    OcoOpOutputHold    = 0u,               
    OcoOpOutputHigh    = 1u,               
    OcoOpOutputLow     = 2u,               
    OcoOpOutputReverse = 3u,               
} en_timer4_oco_op_state_t;

typedef enum en_timer4_oco_ocf_state
{
    OcoOcfHold = 0u,                       
    OcoOcfSet  = 1u,                       
} en_timer4_oco_ocf_state_t;

typedef struct stc_oco_low_ch_compare_mode
{
    en_timer4_oco_op_state_t enCntZeroLowMatchHighMatchLowChOpState;         
    en_timer4_oco_op_state_t enCntZeroLowMatchHighNotMatchLowChOpState;      
    en_timer4_oco_op_state_t enCntZeroLowNotMatchHighMatchLowChOpState;      
    en_timer4_oco_op_state_t enCntZeroLowNotMatchHighNotMatchLowChOpState;   

    en_timer4_oco_op_state_t enCntUpCntLowMatchHighMatchLowChOpState;        
    en_timer4_oco_op_state_t enCntUpCntLowMatchHighNotMatchLowChOpState;     
    en_timer4_oco_op_state_t enCntUpCntLowNotMatchHighMatchLowChOpState;     

    en_timer4_oco_op_state_t enCntPeakLowMatchHighMatchLowChOpState;         
    en_timer4_oco_op_state_t enCntPeakLowMatchHighNotMatchLowChOpState;    
    en_timer4_oco_op_state_t enCntPeakLowNotMatchHighMatchLowChOpState;      
    en_timer4_oco_op_state_t enCntPeakLowNotMatchHighNotMatchLowChOpState;   

    en_timer4_oco_op_state_t enCntDownLowMatchHighMatchLowChOpState;         
    en_timer4_oco_op_state_t enCntDownLowMatchHighNotMatchLowChOpState;      
    en_timer4_oco_op_state_t enCntDownLowNotMatchHighMatchLowChOpState;      

    en_timer4_oco_ocf_state_t enCntZeroMatchOcfState;       
    en_timer4_oco_ocf_state_t enCntUpCntMatchOcfState;      
    en_timer4_oco_ocf_state_t enCntPeakMatchOcfState;       
    en_timer4_oco_ocf_state_t enCntDownCntMatchOcfState;    

    tim4_functional_state_t     enMatchConditionExtendCmd;                                                                
} stc_oco_low_ch_compare_mode_t;

typedef struct stc_oco_high_ch_compare_mode
{
    en_timer4_oco_op_state_t  enCntZeroMatchOpState;        
    en_timer4_oco_op_state_t  enCntZeroNotMatchOpState;     

    en_timer4_oco_op_state_t  enCntUpCntMatchOpState;       

    en_timer4_oco_op_state_t  enCntPeakMatchOpState;        
    en_timer4_oco_op_state_t  enCntPeakNotMatchOpState;     

    en_timer4_oco_op_state_t  enCntDownCntMatchOpState;     

    en_timer4_oco_ocf_state_t enCntZeroMatchOcfState;       
    en_timer4_oco_ocf_state_t enCntUpCntMatchOcfState;      
    en_timer4_oco_ocf_state_t enCntPeakMatchOcfState;       
    en_timer4_oco_ocf_state_t enCntDownCntMatchOcfState;    

    tim4_functional_state_t     enMatchConditionExtendCmd;    
                                                            
} stc_oco_high_ch_compare_mode_t;

typedef enum en_timer4_pwm_mode
{
    PwmThroughMode         = 0u,         
    PwmDeadTimerMode       = 1u,        
    PwmDeadTimerFilterMode = 2u,        
} en_timer4_pwm_mode_t;

typedef enum en_timer4_pwm_timer_clk_div
{
    PwmPlckDiv1   = 0u,                
    PwmPlckDiv2   = 1u,                
    PwmPlckDiv4   = 2u,                
    PwmPlckDiv8   = 3u,                
    PwmPlckDiv16  = 4u,                
    PwmPlckDiv32  = 5u,                
    PwmPlckDiv64  = 6u,                
    PwmPlckDiv128 = 7u,                
} en_timer4_pwm_timer_clk_div_t;

typedef enum en_timer4_pwm_output_state
{
    PwmHPwmLHold        = 0u,           
    PwmHPwmLReverse     = 1u,           
    PwmHReversePwmLHold = 2u,           
    PwmHHoldPwmLReverse = 3u,           
} en_timer4_pwm_output_state_t;

typedef struct stc_timer4_pwm_init
{
    en_timer4_pwm_mode_t          enMode;           

    en_timer4_pwm_timer_clk_div_t enClkDiv;         

    en_timer4_pwm_output_state_t  enOutputState;    

    tim4_functional_state_t         enRtIntMaskCmd;   
} stc_timer4_pwm_init_t;

typedef enum en_timer4_pwm_ch
{
    TIMER4_PWM_U = 0u,                    /**< \brief Timer4 PWM couple channel: U */
    TIMER4_PWM_V = 1u,                    /**< \brief Timer4 PWM couple channel: V */
    TIMER4_PWM_W = 2u,                    /**< \brief Timer4 PWM couple channel: W */
} en_timer4_pwm_ch_t;
/**
 * \brief ARR-16λģʽ���ؼĴ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ARR���ؼĴ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_tim4_arr_count_get (amhw_hc32f460_tim4_t *p_hw_tim,
                                           uint8_t               chan)
{
    return p_hw_tim->CPSR;
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
void amhw_hc32f460_tim4_arr_count_set (amhw_hc32f460_tim4_t *p_hw_tim, uint8_t chan, uint16_t value)
{
    p_hw_tim->CPSR = value;
}

/**
 * \brief CNT-16λģʽ�����Ĵ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return CNT�����Ĵ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_tim4_cnt16_count_get (amhw_hc32f460_tim4_t *p_hw_tim,
                                             uint8_t               chan)
{
    return (uint16_t)p_hw_tim->CNTR;
}

am_static_inline
void amhw_hc32f460_tim4_cnt16_count_set (amhw_hc32f460_tim4_t *p_hw_tim,
                                         uint8_t               chan,
                                         uint16_t              value)
{
    p_hw_tim->CNTR = value;
}

am_static_inline
am_bool_t amhw_hc32f460_tim4_oco_write_occr(amhw_hc32f460_tim4_t *p_hw_tim,
                                            timer4_oco_ch_t       enCh,
                                            uint16_t              u16Occr)
{
    __IO uint16_t *pu16OCCR = NULL;
    am_bool_t enRet = AM_FALSE;

    /* Check TMR4x pointer */
    if (NULL != p_hw_tim)
    {
        /* Get pointer of current channel OCO register address */
        pu16OCCR = (__IO uint16_t*)TMR4_OCCRx(p_hw_tim, enCh);
        /* set register */
        *pu16OCCR = u16Occr;

        enRet = AM_TRUE;
    }

    return enRet;
}

am_static_inline
am_bool_t amhw_hc32f460_tim4_oco_output_cmp_cmd(amhw_hc32f460_tim4_t   *p_hw_tim,
                                                timer4_oco_ch_t         enCh,
                                                tim4_functional_state_t enCmd)
{
    __IO stc_tmr4_ocsr_field_t *pstcOCSR = NULL;
    am_bool_t enRet = AM_FALSE;

    /* Check TMR4x pointer */
    if (NULL != p_hw_tim)
    {
        /* Get pointer of current channel OCO register address */
        pstcOCSR = (__IO stc_tmr4_ocsr_field_t*)TMR4_OCSRx(p_hw_tim, enCh);

        /* set register */
        IS_VALID_OCO_HIGH_CH(enCh) ? (pstcOCSR->OCEH = (uint16_t)enCmd) : (pstcOCSR->OCEL = (uint16_t)enCmd);
        enRet = AM_TRUE;
    }

    return enRet;
}

/**
 * \brief ��ʱ��ģʽö��
 */

/**
 * \brief MODE ����ģʽ  ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ���õĹ���ģʽ��amhw_hc32_tim_mode_tö������
 */
am_static_inline
tim4_counter_mode_t amhw_hc32f460_tim4_mode_get (amhw_hc32f460_tim4_t *p_hw_tim)
{
    return (tim4_counter_mode_t)(p_hw_tim->CCSR_f.MODE);
}

/**
 * \brief CMODE ����ģʽ  ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] mode     : ���õĹ���ģʽ��amhw_hc32_tim_mode_tö������
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim4_mode_set (amhw_hc32f460_tim4_t     *p_hw_tim,
                                  tim4_counter_mode_t       mode)
{
    p_hw_tim->CCSR_f.MODE = mode;
}

am_static_inline
void amhw_hc32f460_tim4_buf_set (amhw_hc32f460_tim4_t     *p_hw_tim,
                                 am_bool_t                 value)
{
    p_hw_tim->CCSR_f.BUFEN = value;
}

am_static_inline
void amhw_hc32f460_tim4_ext_clk_set (amhw_hc32f460_tim4_t     *p_hw_tim,
                                     am_bool_t                 value)
{
    p_hw_tim->CCSR_f.ECKEN = value;
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
void amhw_hc32f460_tim4_disable (amhw_hc32f460_tim4_t *p_hw_tim, uint8_t chan)
{
    p_hw_tim->CCSR_f.STOP = 1;
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
void amhw_hc32f460_tim4_enable (amhw_hc32f460_tim4_t *p_hw_tim, uint8_t chan)
{
    p_hw_tim->CCSR_f.STOP = 0;
}

/**
 * \brief �ڲ�ʱ�ӷ�Ƶѡ��
 */
typedef enum {
    AMHW_HC32F460_TIM4_CLK_DIV0 = 0,    /**< \brief 1��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV2,        /**< \brief 2��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV4,        /**< \brief 4��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV8,        /**< \brief 8��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV16,       /**< \brief 16��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV32,       /**< \brief 32��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV64,       /**< \brief 64��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV128,      /**< \brief 128��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV256,      /**< \brief 256��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV512,      /**< \brief 512��Ƶ */
    AMHW_HC32F460_TIM4_CLK_DIV1024,     /**< \brief 1024��Ƶ */
}amhw_hc32f460_tim4_clkdiv_t;

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ���õķ�Ƶϵ����amhw_hc32_tim_clkdiv_tö������
 */
am_static_inline
amhw_hc32f460_tim4_clkdiv_t
    amhw_hc32f460_tim4_mode_clkdiv_get (amhw_hc32f460_tim4_t *p_hw_tim, uint8_t chan)
{
    amhw_hc32f460_tim4_clkdiv_t clkdiv;
    clkdiv = (amhw_hc32f460_tim4_clkdiv_t)p_hw_tim->CCSR_f.CKDIV;
    return clkdiv;
}

#define TMR4_RCSRx(__TMR4x__)               ((uint32_t)&(__TMR4x__)->RCSR)
#define TMR4_POCRx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->POCRU + ((uint32_t)(__CH__))*4ul)
#define TMR4_PDARx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->PDARU + ((uint32_t)(__CH__))*8ul)
#define TMR4_PDBRx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->PDBRU + ((uint32_t)(__CH__))*8ul)
#define TMR4_PFSRx(__TMR4x__, __CH__)       ((uint32_t)&(__TMR4x__)->PFSRU + ((uint32_t)(__CH__))*8ul)

am_static_inline
am_bool_t amhw_hc32f460_tim4_pwm_init(amhw_hc32f460_tim4_t        *p_hw_tim,
                                      en_timer4_pwm_ch_t           enCh,
                                      const stc_timer4_pwm_init_t *pstcInitCfg)
{
    __IO stc_tmr4_pocr_field_t *pstcPOCR_f = NULL;
    __IO stc_tmr4_rcsr_field_t *pstcRCSR_f = NULL;
    am_bool_t enRet = AM_TRUE;

    /* Check TMR4x && pstcInitCfg pointer */
    if ((NULL != p_hw_tim) && (NULL != pstcInitCfg))
    {
        /* Get pointer of current channel PWM register address */
        pstcRCSR_f = (__IO stc_tmr4_rcsr_field_t*)TMR4_RCSRx(p_hw_tim);
        pstcPOCR_f = (__IO stc_tmr4_pocr_field_t*)TMR4_POCRx(p_hw_tim, enCh);

        /* Configure PWM mode */
        pstcPOCR_f->PWMMD = (uint16_t)(pstcInitCfg->enMode);

        /* Configure PWM mode */
        pstcPOCR_f->LVLS = (uint16_t)(pstcInitCfg->enOutputState);

        /* Set timer clock division */
        pstcPOCR_f->DIVCK = (uint16_t)(pstcInitCfg->enClkDiv);

        /* Set interrupt mask */
        switch (enCh)
        {
            case TIMER4_PWM_U:
                pstcRCSR_f->RTIDU = (uint16_t)(pstcInitCfg->enRtIntMaskCmd);
                break;
            case TIMER4_PWM_V:
                pstcRCSR_f->RTIDV = (uint16_t)(pstcInitCfg->enRtIntMaskCmd);
                break;
            case TIMER4_PWM_W:
                pstcRCSR_f->RTIDW = (uint16_t)(pstcInitCfg->enRtIntMaskCmd);
                break;
            default:
                enRet = AM_FALSE;
                break;
        }
    }
    else
    {
        enRet = AM_FALSE;
    }

    return enRet;
}


/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] clkdiv   : ���õķ�Ƶϵ����amhw_hc32_tim_clkdiv_tö������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim4_mode_clkdiv_set (amhw_hc32f460_tim4_t       *p_hw_tim,
                                         uint8_t                     chan,
                                         amhw_hc32f460_tim4_clkdiv_t clkdiv)
{
    p_hw_tim->CCSR_f.CKDIV = clkdiv;
}

am_static_inline
void amhw_hc32f460_tim4_intz_set (amhw_hc32f460_tim4_t *p_hw_tim,
                                  am_bool_t             value)
{
    p_hw_tim->CCSR_f.IRQZEN = value;
}

am_static_inline
void amhw_hc32f460_tim4_intp_set (amhw_hc32f460_tim4_t *p_hw_tim,
                                  am_bool_t             value)
{
    p_hw_tim->CCSR_f.IRQPEN = value;
}

am_static_inline
void amhw_hc32f460_tim4_zim_set (amhw_hc32f460_tim4_t *p_hw_tim,
                                 timer4_cnt_int_mask_t mask)
{
    p_hw_tim->CVPR_f.ZIM = mask;
}

am_static_inline
void amhw_hc32f460_tim4_pim_set (amhw_hc32f460_tim4_t *p_hw_tim,
                                 timer4_cnt_int_mask_t mask)
{
    p_hw_tim->CVPR_f.PIM = mask;
}

am_static_inline
am_bool_t amhw_hc32f460_tim4_oco_init(amhw_hc32f460_tim4_t        *p_hw_tim,
                                      timer4_oco_ch_t              enCh,
                                      const stc_timer4_oco_init_t *pstcInitCfg)
{
    __IO stc_tmr4_ocsr_field_t* pstcOCSR = NULL;
    __IO stc_tmr4_ocer_field_t* pstcOCER = NULL;
    am_bool_t enRet = AM_FALSE;

    /* Check TMR4x && pstcInitCfg pointer */
    if ((NULL != p_hw_tim) && (NULL != pstcInitCfg))
    {
        enRet = AM_TRUE;
        /* Get pointer of current channel OCO register address */
        pstcOCER = (__IO stc_tmr4_ocer_field_t*)TMR4_OCERx(p_hw_tim, enCh);
        pstcOCSR = (__IO stc_tmr4_ocsr_field_t*)TMR4_OCSRx(p_hw_tim, enCh);

        /* Set OCMR and OCCR buffer mode */
        if (IS_VALID_OCO_HIGH_CH(enCh)) /* channel: Timer4OcoOuh, Timer4OcoOvh, Timer4OcoOwh */
        {
            pstcOCSR->OCEH = (uint16_t)0u;
            pstcOCSR->OCFH = (uint16_t)0u;

            /* OCMR buffer */
            switch (pstcInitCfg->enOcmrBufMode)
            {
                case OcmrBufDisable:
                    pstcOCER->LMMH = (uint16_t)0u;
                    pstcOCER->MHBUFEN = (uint16_t)0u;
                    break;
                case OcmrBufTrsfByCntZero:
                    pstcOCER->LMMH = (uint16_t)0u;
                    pstcOCER->MHBUFEN = (uint16_t)1u;
                    break;
                case OcmrBufTrsfByCntPeak:
                    pstcOCER->LMMH = (uint16_t)0u;
                    pstcOCER->MHBUFEN = (uint16_t)2u;
                    break;
                case OcmrBufTrsfByCntZeroOrCntPeak:
                    pstcOCER->LMMH = (uint16_t)0u;
                    pstcOCER->MHBUFEN = (uint16_t)3u;
                    break;
                case OcmrBufTrsfByCntZeroZicZero:
                    pstcOCER->LMMH = (uint16_t)1u;
                    pstcOCER->MHBUFEN = (uint16_t)1u;
                    break;
                case OcmrBufTrsfByCntPeakPicZero:
                    pstcOCER->LMMH = (uint16_t)1u;
                    pstcOCER->MHBUFEN = (uint16_t)2u;
                    break;
                case OcmrBufTrsfByCntZeroZicZeroOrCntPeakPicZero:
                    pstcOCER->LMMH = (uint16_t)1u;
                    pstcOCER->MHBUFEN = (uint16_t)3u;
                    break;
                default:
                    enRet = AM_FALSE;
                    break;
            }

            if (enRet == AM_TRUE)
            {
                /* OCCR buffer */
                switch (pstcInitCfg->enOccrBufMode)
                {
                    case OccrBufDisable:
                        pstcOCER->LMCH = (uint16_t)0u;
                        pstcOCER->CHBUFEN = (uint16_t)0u;
                        break;
                    case OccrBufTrsfByCntZero:
                        pstcOCER->LMCH = (uint16_t)0u;
                        pstcOCER->CHBUFEN = (uint16_t)1u;
                        break;
                    case OccrBufTrsfByCntPeak:
                        pstcOCER->LMCH = (uint16_t)0u;
                        pstcOCER->CHBUFEN = (uint16_t)2u;
                        break;
                    case OccrBufTrsfByCntZeroOrCntPeak:
                        pstcOCER->LMCH = (uint16_t)0u;
                        pstcOCER->CHBUFEN = (uint16_t)3u;
                        break;
                    case OccrBufTrsfByCntZeroZicZero:
                        pstcOCER->LMCH = (uint16_t)1u;
                        pstcOCER->CHBUFEN = (uint16_t)1u;
                        break;
                    case OccrBufTrsfByCntPeakPicZero:
                        pstcOCER->LMCH = (uint16_t)1u;
                        pstcOCER->CHBUFEN = (uint16_t)2u;
                        break;
                    case OccrBufTrsfByCntZeroZicZeroOrCntPeakPicZero:
                        pstcOCER->LMCH = (uint16_t)1u;
                        pstcOCER->CHBUFEN = (uint16_t)3u;
                        break;
                    default:
                        enRet = AM_FALSE;
                        break;
                }
            }

            if (enRet == AM_TRUE)
            {
                /* Set initial OP level */
                pstcOCSR->OCPH = (uint16_t)(pstcInitCfg->enPortLevel);
                /* set interrupt enable */
                pstcOCSR->OCIEH = (uint16_t)(pstcInitCfg->enOcoIntCmd);
            }
        }/* channel: Timer4OcoOul, Timer4OcoOvl, Timer4OcoOwl */
        else if (IS_VALID_OCO_LOW_CH(enCh))
        {
            pstcOCSR->OCEL = (uint16_t)0u;
            pstcOCSR->OCFL = (uint16_t)0u;

            /* OCMR buffer */
            switch (pstcInitCfg->enOcmrBufMode)
            {
                case OcmrBufDisable:
                    pstcOCER->LMML = (uint16_t)0u;
                    pstcOCER->MLBUFEN = (uint16_t)0u;
                    break;
                case OcmrBufTrsfByCntZero:
                    pstcOCER->LMML = (uint16_t)0u;
                    pstcOCER->MLBUFEN = (uint16_t)1u;
                    break;
                case OcmrBufTrsfByCntPeak:
                    pstcOCER->LMML = (uint16_t)0u;
                    pstcOCER->MLBUFEN = (uint16_t)2u;
                    break;
                case OcmrBufTrsfByCntZeroOrCntPeak:
                    pstcOCER->LMML = (uint16_t)0u;
                    pstcOCER->MLBUFEN = (uint16_t)3u;
                    break;
                case OcmrBufTrsfByCntZeroZicZero:
                    pstcOCER->LMML = (uint16_t)1u;
                    pstcOCER->MLBUFEN = (uint16_t)1u;
                    break;
                case OcmrBufTrsfByCntPeakPicZero:
                    pstcOCER->LMML = (uint16_t)1u;
                    pstcOCER->MLBUFEN = (uint16_t)2u;
                    break;
                case OcmrBufTrsfByCntZeroZicZeroOrCntPeakPicZero:
                    pstcOCER->LMML = (uint16_t)1u;
                    pstcOCER->MLBUFEN = (uint16_t)3u;
                    break;
                default:
                    enRet = AM_FALSE;
                    break;
            }

            if (enRet == AM_TRUE)
            {
                /* OCCR buffer */
                switch (pstcInitCfg->enOccrBufMode)
                {
                    case OccrBufDisable:
                        pstcOCER->LMCL = (uint16_t)0u;
                        pstcOCER->CLBUFEN = (uint16_t)0u;
                        break;
                    case OccrBufTrsfByCntZero:
                        pstcOCER->LMCL = (uint16_t)0u;
                        pstcOCER->CLBUFEN = (uint16_t)1u;
                        break;
                    case OccrBufTrsfByCntPeak:
                        pstcOCER->LMCL = (uint16_t)0u;
                        pstcOCER->CLBUFEN = (uint16_t)2u;
                        break;
                    case OccrBufTrsfByCntZeroOrCntPeak:
                        pstcOCER->LMCL = (uint16_t)0u;
                        pstcOCER->CLBUFEN = (uint16_t)3u;
                        break;
                    case OccrBufTrsfByCntZeroZicZero:
                        pstcOCER->LMCL = (uint16_t)1u;
                        pstcOCER->CLBUFEN = (uint16_t)1u;
                        break;
                    case OccrBufTrsfByCntPeakPicZero:
                        pstcOCER->LMCL = (uint16_t)1u;
                        pstcOCER->CLBUFEN = (uint16_t)2u;
                        break;
                    case OccrBufTrsfByCntZeroZicZeroOrCntPeakPicZero:
                        pstcOCER->LMCL = (uint16_t)1u;
                        pstcOCER->CLBUFEN = (uint16_t)3u;
                        break;
                    default:
                        enRet = AM_FALSE;
                        break;
                }
            }

            if (enRet == AM_TRUE)
            {
                /* Set initial OP level */
                pstcOCSR->OCPL = (uint16_t)(pstcInitCfg->enPortLevel);
                /* set interrupt enable */
                pstcOCSR->OCIEL = (uint16_t)(pstcInitCfg->enOcoIntCmd);
            }
        }
        else
        {
            enRet = AM_FALSE;
        }
    }

    return enRet;
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
am_bool_t amhw_hc32f460_tim4_int_flag_check(amhw_hc32f460_tim4_t *p_hw_tim,
                                            timer4_cnt_int_t      flag)
{
    uint8_t value = 0;
    if(TIMER4_CNT_ZERO_MATCH_INT == flag)
    {
        value = p_hw_tim->CCSR_f.IRQZF;        
    } else if (TIMER4_CNT_PEAK_MATCH_INT == flag)
    {
        value = p_hw_tim->CCSR_f.IRQPF;
    }else {
        ;
    }
    return value ? AM_TRUE : AM_FALSE;
}

am_static_inline
void amhw_hc32f460_tim4_int_flag_clr(amhw_hc32f460_tim4_t *p_hw_tim,
                                     timer4_cnt_int_t      flag)
{
    if(TIMER4_CNT_ZERO_MATCH_INT == flag)
    {
        p_hw_tim->CCSR_f.IRQZF = 0;        
    } else if (TIMER4_CNT_PEAK_MATCH_INT == flag)
    {
        p_hw_tim->CCSR_f.IRQPF = 0;
    }else {
        ;
    }
}

/**
 * \brief UIF ����ж� ��־���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim4_cnt_value_clr(amhw_hc32f460_tim4_t *p_hw_tim)
{
    p_hw_tim->CCSR_f.CLEAR = (uint16_t)1u;
}

am_static_inline
am_bool_t amhw_hc32f460_tim4_oco_set_h_ch_cmp_mode(amhw_hc32f460_tim4_t                 *p_hw_tim,
                                                   timer4_oco_ch_t                       enCh,
                                                   const stc_oco_high_ch_compare_mode_t *pstcMode)
{
    uint16_t u16OCMR = 0u;
    __IO uint16_t *pu16OCMR = NULL;
    __IO stc_tmr4_ocer_field_t *pstcOCER = NULL;
    am_bool_t enRet = AM_FALSE;

    /* Check TMR4x && pstcMode pointer */
    if ((NULL != p_hw_tim) && (NULL != pstcMode))
    {
        /* Get pointer of current channel OCO register address */
        pu16OCMR = (__IO uint16_t*)TMR4_OCMRx(p_hw_tim, enCh);
        pstcOCER = (__IO stc_tmr4_ocer_field_t*)TMR4_OCERx(p_hw_tim, enCh);

        pstcOCER->MCECH = (uint16_t)(pstcMode->enMatchConditionExtendCmd);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntZeroMatchOpState    << 10u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntZeroNotMatchOpState << 14u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntUpCntMatchOpState   << 8u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntPeakMatchOpState    << 6u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntPeakNotMatchOpState << 12u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntDownCntMatchOpState << 4u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntZeroMatchOcfState    << 3u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntUpCntMatchOcfState   << 2u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntPeakMatchOcfState    << 1u);
        u16OCMR |= (uint16_t)((uint16_t)pstcMode->enCntDownCntMatchOcfState << 0u);

        *pu16OCMR = u16OCMR;
        enRet = AM_TRUE;
    }

    return enRet;
}

am_static_inline
am_bool_t  amhw_hc32f460_tim4_oco_set_l_ch_cmp_mode(amhw_hc32f460_tim4_t                *p_hw_tim,
                                                    timer4_oco_ch_t                      enCh,
                                                    const stc_oco_low_ch_compare_mode_t *pstcMode)
{
    uint32_t u32OCMR = 0ul;
    __IO uint32_t *pu32OCMR = NULL;
    __IO stc_tmr4_ocer_field_t *pstcOCER = NULL;
    am_bool_t enRet = AM_FALSE;

    /* Check TMR4x pointer and pstcMode pointer */
    if ((NULL != p_hw_tim) && (NULL != pstcMode))
    {
        /* Get pointer of current channel OCO register address */
        pu32OCMR = (__IO uint32_t*)TMR4_OCMRx(p_hw_tim, enCh);
        pstcOCER = (__IO stc_tmr4_ocer_field_t*)TMR4_OCERx(p_hw_tim, enCh);;

        pstcOCER->MCECL = (uint16_t)(pstcMode->enMatchConditionExtendCmd);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntZeroLowMatchHighMatchLowChOpState        << 26u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntZeroLowMatchHighNotMatchLowChOpState     << 10u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntZeroLowNotMatchHighMatchLowChOpState     << 30u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntZeroLowNotMatchHighNotMatchLowChOpState  << 14u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntUpCntLowMatchHighMatchLowChOpState       << 24u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntUpCntLowMatchHighNotMatchLowChOpState    << 8u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntUpCntLowNotMatchHighMatchLowChOpState    << 18u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntPeakLowMatchHighMatchLowChOpState        << 22u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntPeakLowMatchHighNotMatchLowChOpState     << 6u) ;
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntPeakLowNotMatchHighMatchLowChOpState     << 28u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntPeakLowNotMatchHighNotMatchLowChOpState  << 12u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntDownLowMatchHighMatchLowChOpState        << 20u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntDownLowMatchHighNotMatchLowChOpState     << 4u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntDownLowNotMatchHighMatchLowChOpState     << 16u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntZeroMatchOcfState     << 3u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntUpCntMatchOcfState    << 2u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntPeakMatchOcfState     << 1u);
        u32OCMR |= (uint32_t)((uint32_t)pstcMode->enCntDownCntMatchOcfState  << 0u);

        *pu32OCMR = u32OCMR;
        enRet = AM_TRUE;
    }

    return enRet;
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

#endif /* __AMHW_HC32F460_TIM4_H */

/* end of file */
