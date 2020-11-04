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

#ifndef __AMHW_HC32F460_TIMEA_H
#define __AMHW_HC32F460_TIMEA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"


/**
 *******************************************************************************
 ** \brief Timer0 counter mode enumeration
 **
 ******************************************************************************/

#define TMRA_OVF   (1 << 0)
#define TMRA_UDF   (1 << 1)
#define TMRA_CMP   (1 << 2)
 
 #if defined(__CC_ARM)
    #pragma push
    #pragma anon_unions
#elif defined(__ICCARM__)
    #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
    #pragma warning 586
#else
    #warning Not supported compiler t
#endif
 
 
 
/**
 * \brief ��ʱ������
 */
typedef enum amhw_hc32f460_timea_type {
    AMHW_HC32F460_TIMEA_TYPE_TIM0 = 0,  /**< \brief TIM0 */
    AMHW_HC32F460_TIMEA_TYPE_TIM1,      /**< \brief TIM1 */
    AMHW_HC32F460_TIMEA_TYPE_TIM2,      /**< \brief TIM2 */
    AMHW_HC32F460_TIMEA_TYPE_TIM3,      /**< \brief TIM3 */
} amhw_hc32f460_timea_type_t;


typedef enum timea_counter_mode
{
    timea_count_mode_sawtooth_wave   = 0u, 
    timea_count_mode_triangular_wave = 1u, 
}timea_counter_mode_t;

typedef enum timea_count_dir
{
    timea_count_dir_down = 0u,            
    timea_count_dir_up   = 1u,            
} timea_count_dir_t;

typedef enum timea_irq_type
{
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH1 = 0u,               
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH2 = 1u,              
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH3 = 2u,              
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH4 = 3u,              
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH5 = 4u,              
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH6 = 5u,              
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH7 = 6u,              
    TIMERA_IRQ_CAPTURE_OR_COMPARE_CH8 = 7u,              
    TIMERA_IRQ_OVERFLOW               = 8u,              
    TIMERA_IRQ_UNDERFLOW              = 9u,              
} timea_irq_type_t;

/******************************************************************************/
typedef enum timera_flag_type
{
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH1 = 0u,              
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH2 = 1u,             
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH3 = 2u,             
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH4 = 3u,             
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH5 = 4u,             
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH6 = 5u,             
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH7 = 6u,             
    TIMEA_FLAG_CAPTURE_OR_COMPARE_CH8 = 7u,             
    TIMEA_FLAG_OVERFLOW               = 8u,             
    TIMEA_FLAG_UNDERFLOW              = 9u,             
} timea_flag_type_t;

/**
 * \brief TMRA ͨ�ü���ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CNT                       :16;  /**< \brief ��ǰ��ʱ���ļ���ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmra_cnter_field_t;

/**
 * \brief TMRA ���ڻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PER                       :16;  /**< \brief ��������ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmra_perar_field_t;

/**
 * \brief TMRA �Ƚϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CMP                       :16;  /**< \brief �����Ƚϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmra_cmpar_field_t;

/**
 * \brief TMRA ����״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t START                     : 1;  /**< \brief ��ʱ������*/
    __IO uint32_t DIR                       : 1;  /**< \brief ��������*/
    __IO uint32_t MODE                      : 1;  /**< \brief ����ģʽ*/
    __IO uint32_t SYNST                     : 1;  /**< \brief ͬ������ʹ��*/
    __IO uint32_t CKDIV                     : 4;  /**< \brief ����ʱ��ѡ��*/
    uint32_t RESERVED8                      : 4;  /**< \brief ����*/
    __IO uint32_t ITENOVF                   : 1;  /**< \brief �����ж�ʹ��*/
    __IO uint32_t ITENUDF                   : 1;  /**< \brief �����ж�ʹ��*/
    __IO uint32_t OVFF                      : 1;  /**< \brief �����־*/
    __IO uint32_t UDFF                      : 1;  /**< \brief �����־*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmra_bcstr_field_t;

/**
 * \brief TMRA Ӳ�������¼�ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HSTA0                     : 1;  /**< \brief Ӳ����������0*/
    __IO uint32_t HSTA1                     : 1;  /**< \brief Ӳ����������1*/
    __IO uint32_t HSTA2                     : 1;  /**< \brief Ӳ����������2*/
    uint32_t RESERVED3                      : 1;  /**< \brief ����*/
    __IO uint32_t HSTP0                     : 1;  /**< \brief Ӳ��ֹͣ����0*/
    __IO uint32_t HSTP1                     : 1;  /**< \brief Ӳ����������1*/
    __IO uint32_t HSTP2                     : 1;  /**< \brief Ӳ����������2*/
    uint32_t RESERVED7                      : 1;  /**< \brief ����*/
    __IO uint32_t HCLE0                     : 1;  /**< \brief Ӳ����������0*/
    __IO uint32_t HCLE1                     : 1;  /**< \brief Ӳ����������1*/
    __IO uint32_t HCLE2                     : 1;  /**< \brief Ӳ����������2*/
    uint32_t RESERVED11                     : 1;  /**< \brief ����*/
    __IO uint32_t HCLE3                     : 1;  /**< \brief Ӳ����������3*/
    __IO uint32_t HCLE4                     : 1;  /**< \brief Ӳ����������4*/
    __IO uint32_t HCLE5                     : 1;  /**< \brief Ӳ����������5*/
    __IO uint32_t HCLE6                     : 1;  /**< \brief Ӳ����������6*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmra_hconr_field_t;

/**
 * \brief TMRA Ӳ���ݼ��¼�ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HCUP0                     : 1;  /**< \brief Ӳ���ݼ�����0*/
    __IO uint32_t HCUP1                     : 1;  /**< \brief Ӳ���ݼ�����1*/
    __IO uint32_t HCUP2                     : 1;  /**< \brief Ӳ���ݼ�����2*/
    __IO uint32_t HCUP3                     : 1;  /**< \brief Ӳ���ݼ�����3*/
    __IO uint32_t HCUP4                     : 1;  /**< \brief Ӳ���ݼ�����4*/
    __IO uint32_t HCUP5                     : 1;  /**< \brief Ӳ���ݼ�����5*/
    __IO uint32_t HCUP6                     : 1;  /**< \brief Ӳ���ݼ�����6*/
    __IO uint32_t HCUP7                     : 1;  /**< \brief Ӳ���ݼ�����7*/
    __IO uint32_t HCUP8                     : 1;  /**< \brief Ӳ���ݼ�����8*/
    __IO uint32_t HCUP9                     : 1;  /**< \brief Ӳ���ݼ�����9*/
    __IO uint32_t HCUP10                    : 1;  /**< \brief Ӳ���ݼ�����10*/
    __IO uint32_t HCUP11                    : 1;  /**< \brief Ӳ���ݼ�����11*/
    __IO uint32_t HCUP12                    : 1;  /**< \brief Ӳ���ݼ�����12*/
    uint32_t RESERVED13                     :19;  /**< \brief ����*/
} stc_tmra_hcupr_field_t;

/**
 * \brief TMRA Ӳ���ݼ��¼�ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HCDO0                     : 1;  /**< \brief Ӳ���ݼ�����0*/
    __IO uint32_t HCDO1                     : 1;  /**< \brief Ӳ���ݼ�����1*/
    __IO uint32_t HCDO2                     : 1;  /**< \brief Ӳ���ݼ�����2*/
    __IO uint32_t HCDO3                     : 1;  /**< \brief Ӳ���ݼ�����3*/
    __IO uint32_t HCDO4                     : 1;  /**< \brief Ӳ���ݼ�����4*/
    __IO uint32_t HCDO5                     : 1;  /**< \brief Ӳ���ݼ�����5*/
    __IO uint32_t HCDO6                     : 1;  /**< \brief Ӳ���ݼ�����6*/
    __IO uint32_t HCDO7                     : 1;  /**< \brief Ӳ���ݼ�����7*/
    __IO uint32_t HCDO8                     : 1;  /**< \brief Ӳ���ݼ�����8*/
    __IO uint32_t HCDO9                     : 1;  /**< \brief Ӳ���ݼ�����9*/
    __IO uint32_t HCDO10                    : 1;  /**< \brief Ӳ���ݼ�����10*/
    __IO uint32_t HCDO11                    : 1;  /**< \brief Ӳ���ݼ�����11*/
    __IO uint32_t HCDO12                    : 1;  /**< \brief Ӳ���ݼ�����12*/
    uint32_t RESERVED13                     :19;  /**< \brief ����*/
} stc_tmra_hcdor_field_t;

/**
 * \brief TMRA �жϿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t ITEN1                     : 1;  /**< \brief ����ƥ���ж�ʹ��1*/
    __IO uint32_t ITEN2                     : 1;  /**< \brief ����ƥ���ж�ʹ��2*/
    __IO uint32_t ITEN3                     : 1;  /**< \brief ����ƥ���ж�ʹ��3*/
    __IO uint32_t ITEN4                     : 1;  /**< \brief ����ƥ���ж�ʹ��4*/
    __IO uint32_t ITEN5                     : 1;  /**< \brief ����ƥ���ж�ʹ��5*/
    __IO uint32_t ITEN6                     : 1;  /**< \brief ����ƥ���ж�ʹ��6*/
    __IO uint32_t ITEN7                     : 1;  /**< \brief ����ƥ���ж�ʹ��7*/
    __IO uint32_t ITEN8                     : 1;  /**< \brief ����ƥ���ж�ʹ��8*/
    uint32_t RESERVED8                      :24;  /**< \brief ����*/
} stc_tmra_iconr_field_t;

/**
 * \brief TMRA �¼����ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t ETEN1                     : 1;  /**< \brief ����ƥ���¼�ʹ��1*/
    __IO uint32_t ETEN2                     : 1;  /**< \brief ����ƥ���¼�ʹ��2*/
    __IO uint32_t ETEN3                     : 1;  /**< \brief ����ƥ���¼�ʹ��3*/
    __IO uint32_t ETEN4                     : 1;  /**< \brief ����ƥ���¼�ʹ��4*/
    __IO uint32_t ETEN5                     : 1;  /**< \brief ����ƥ���¼�ʹ��5*/
    __IO uint32_t ETEN6                     : 1;  /**< \brief ����ƥ���¼�ʹ��6*/
    __IO uint32_t ETEN7                     : 1;  /**< \brief ����ƥ���¼�ʹ��7*/
    __IO uint32_t ETEN8                     : 1;  /**< \brief ����ƥ���¼�ʹ��8*/
    uint32_t RESERVED8                      :24;  /**< \brief ����*/
} stc_tmra_econr_field_t;

/**
 * \brief TMRA �˲����ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t NOFIENTG                  : 1;  /**< \brief ��������˿��˲�TG*/
    __IO uint32_t NOFICKTG                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��TG*/
    uint32_t RESERVED3                      : 5;  /**< \brief ����*/
    __IO uint32_t NOFIENCA                  : 1;  /**< \brief ��������˿��˲�CA*/
    __IO uint32_t NOFICKCA                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��CA*/
    uint32_t RESERVED11                     : 1;  /**< \brief ����*/
    __IO uint32_t NOFIENCB                  : 1;  /**< \brief ��������˿��˲�CB*/
    __IO uint32_t NOFICKCB                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��CB*/
    uint32_t RESERVED15                     :17;  /**< \brief ����*/
} stc_tmra_fconr_field_t;

/**
 * \brief TMRA ״̬��־�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CMPF1                     : 1;  /**< \brief ����ƥ���־1*/
    __IO uint32_t CMPF2                     : 1;  /**< \brief ����ƥ���־2*/
    __IO uint32_t CMPF3                     : 1;  /**< \brief ����ƥ���־3*/
    __IO uint32_t CMPF4                     : 1;  /**< \brief ����ƥ���־4*/
    __IO uint32_t CMPF5                     : 1;  /**< \brief ����ƥ���־5*/
    __IO uint32_t CMPF6                     : 1;  /**< \brief ����ƥ���־6*/
    __IO uint32_t CMPF7                     : 1;  /**< \brief ����ƥ���־7*/
    __IO uint32_t CMPF8                     : 1;  /**< \brief ����ƥ���־8*/
    uint32_t RESERVED8                      :24;  /**< \brief ����*/
} stc_tmra_stflr_field_t;

/**
 * \brief TMRA ������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t BEN                       : 1;  /**< \brief ����ʹ��*/
    __IO uint32_t BSE0                      : 1;  /**< \brief ���ǲ����洫��ѡ��0*/
    __IO uint32_t BSE1                      : 1;  /**< \brief ���ǲ����洫��ѡ��1*/
    uint32_t RESERVED3                      :29;  /**< \brief ����*/
} stc_tmra_bconr_field_t;

/**
 * \brief TMRA ������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CAPMDA                    : 1;  /**< \brief ����ģʽѡ��*/
    uint32_t RESERVED1                      : 3;  /**< \brief ����*/
    __IO uint32_t HICP0                     : 1;  /**< \brief ������������ʹ��0*/
    __IO uint32_t HICP1                     : 1;  /**< \brief ������������ʹ��1*/
    __IO uint32_t HICP2                     : 1;  /**< \brief ������������ʹ��2*/
    uint32_t RESERVED7                      : 1;  /**< \brief ����*/
    __IO uint32_t HICP3                     : 1;  /**< \brief ������������ʹ��3*/
    __IO uint32_t HICP4                     : 1;  /**< \brief ������������ʹ��4*/
    uint32_t RESERVED10                     : 2;  /**< \brief ����*/
    __IO uint32_t NOFIENCP                  : 1;  /**< \brief ��������˿��˲�CP*/
    __IO uint32_t NOFICKCP                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��CP*/
    uint32_t RESERVED15                     :17;  /**< \brief ����*/
} stc_tmra_cconr_field_t;

/**
 * \brief TMRA �˿ڿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t STAC                      : 2;  /**< \brief ������ʼʱ�˿�״̬�趨*/
    __IO uint32_t STPC                      : 2;  /**< \brief ����ֹͣʱ�˿�״̬�趨*/
    __IO uint32_t CMPC                      : 2;  /**< \brief �Ƚ�ֵƥ��ʱ�˿�״̬�趨*/
    __IO uint32_t PERC                      : 2;  /**< \brief ����ֵƥ��ʱ�˿�״̬�趨*/
    __IO uint32_t FORC                      : 2;  /**< \brief ǿ�ƶ˿�״̬�趨*/
    uint32_t RESERVED10                     : 2;  /**< \brief ����*/
    __IO uint32_t OUTEN                     : 1;  /**< \brief ���ʹ��*/
    uint32_t RESERVED13                     :19;  /**< \brief ����*/
} stc_tmra_pconr_field_t;


typedef struct
{
    union
    {
        __IO uint32_t CNTER;           /**< \brief ͨ�ü���ֵ�Ĵ���*/
        stc_tmra_cnter_field_t CNTER_f;
    };
    union
    {
        __IO uint32_t PERAR;           /**< \brief ���ڻ�׼ֵ�Ĵ���*/
        stc_tmra_perar_field_t PERAR_f;
    };
    uint8_t RESERVED2[56];             /**< \brief ����*/
    union
    {
        __IO uint32_t CMPAR1;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���1*/
        stc_tmra_cmpar_field_t CMPAR1_f;
    };
    union
    {
        __IO uint32_t CMPAR2;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���2*/
        stc_tmra_cmpar_field_t CMPAR2_f;
    };
    union
    {
        __IO uint32_t CMPAR3;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���3*/
        stc_tmra_cmpar_field_t CMPAR3_f;
    };
    union
    {
        __IO uint32_t CMPAR4;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���4*/
        stc_tmra_cmpar_field_t CMPAR4_f;
    };
    union
    {
        __IO uint32_t CMPAR5;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���5*/
        stc_tmra_cmpar_field_t CMPAR5_f;
    };
    union
    {
        __IO uint32_t CMPAR6;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���6*/
        stc_tmra_cmpar_field_t CMPAR6_f;
    };
    union
    {
        __IO uint32_t CMPAR7;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���7*/
        stc_tmra_cmpar_field_t CMPAR7_f;
    };
    union
    {
        __IO uint32_t CMPAR8;          /**< \brief �Ƚϻ�׼ֵ�Ĵ���8*/
        stc_tmra_cmpar_field_t CMPAR8_f;
    };
    uint8_t RESERVED10[32];            /**< \brief ����*/
    union
    {
        __IO uint32_t BCSTR;           /**< \brief ����״̬�Ĵ���*/
        stc_tmra_bcstr_field_t BCSTR_f;
    };
    union
    {
        __IO uint32_t HCONR;           /**< \brief Ӳ�������¼�ѡ��Ĵ���*/
        stc_tmra_hconr_field_t HCONR_f;
    };
    union
    {
        __IO uint32_t HCUPR;           /**< \brief Ӳ���ݼ��¼�ѡ��Ĵ���*/
        stc_tmra_hcupr_field_t HCUPR_f;
    };
    union
    {
        __IO uint32_t HCDOR;           /**< \brief Ӳ���ݼ��¼�ѡ��Ĵ���*/
        stc_tmra_hcdor_field_t HCDOR_f;
    };
    union
    {
        __IO uint32_t ICONR;           /**< \brief �жϿ��ƼĴ���*/
        stc_tmra_iconr_field_t ICONR_f;
    };
    union
    {
        __IO uint32_t ECONR;           /**< \brief �¼����ƼĴ���*/
        stc_tmra_econr_field_t ECONR_f;
    };
    union
    {
        __IO uint32_t FCONR;           /**< \brief �˲����ƼĴ���*/
        stc_tmra_fconr_field_t FCONR_f;
    };
    union
    {
        __IO uint32_t STFLR;           /**< \brief ״̬��־�Ĵ���*/
        stc_tmra_stflr_field_t STFLR_f;
    };
    uint8_t RESERVED18[32];            /**< \brief ����*/
    union
    {
        __IO uint32_t BCONR1;          /**< \brief ������ƼĴ���1*/
        stc_tmra_bconr_field_t BCONR1_f;
    };
    uint8_t RESERVED19[4];             /**< \brief ����*/
    union
    {
        __IO uint32_t BCONR2;          /**< \brief ������ƼĴ���2*/
        stc_tmra_bconr_field_t BCONR2_f;
    };
    uint8_t RESERVED20[4];             /**< \brief ����*/
    union
    {
        __IO uint32_t BCONR3;          /**< \brief ������ƼĴ���3*/
        stc_tmra_bconr_field_t BCONR3_f;
    };
    uint8_t RESERVED21[4];             /**< \brief ����*/
    union
    {
        __IO uint32_t BCONR4;          /**< \brief ������ƼĴ���4*/
        stc_tmra_bconr_field_t BCONR4_f;
    };
    uint8_t RESERVED22[36];            /**< \brief ����*/
    union
    {
        __IO uint32_t CCONR1;          /**< \brief ������ƼĴ���1*/
        stc_tmra_cconr_field_t CCONR1_f;
    };
    union
    {
        __IO uint32_t CCONR2;          /**< \brief ������ƼĴ���2*/
        stc_tmra_cconr_field_t CCONR2_f;
    };
    union
    {
        __IO uint32_t CCONR3;          /**< \brief ������ƼĴ���3*/
        stc_tmra_cconr_field_t CCONR3_f;
    };
    union
    {
        __IO uint32_t CCONR4;          /**< \brief ������ƼĴ���4*/
        stc_tmra_cconr_field_t CCONR4_f;
    };
    union
    {
        __IO uint32_t CCONR5;          /**< \brief ������ƼĴ���5*/
        stc_tmra_cconr_field_t CCONR5_f;
    };
    union
    {
        __IO uint32_t CCONR6;          /**< \brief ������ƼĴ���6*/
        stc_tmra_cconr_field_t CCONR6_f;
    };
    union
    {
        __IO uint32_t CCONR7;          /**< \brief ������ƼĴ���7*/
        stc_tmra_cconr_field_t CCONR7_f;
    };
    union
    {
        __IO uint32_t CCONR8;          /**< \brief ������ƼĴ���8*/
        stc_tmra_cconr_field_t CCONR8_f;
    };
    uint8_t RESERVED30[32];            /**< \brief ����*/
    union
    {
        __IO uint32_t PCONR1;          /**< \brief �˿ڿ��ƼĴ���1*/
        stc_tmra_pconr_field_t PCONR1_f;
    };
    union
    {
        __IO uint32_t PCONR2;          /**< \brief �˿ڿ��ƼĴ���2*/
        stc_tmra_pconr_field_t PCONR2_f;
    };
    union
    {
        __IO uint32_t PCONR3;          /**< \brief �˿ڿ��ƼĴ���3*/
        stc_tmra_pconr_field_t PCONR3_f;
    };
    union
    {
        __IO uint32_t PCONR4;          /**< \brief �˿ڿ��ƼĴ���4*/
        stc_tmra_pconr_field_t PCONR4_f;
    };
    union
    {
        __IO uint32_t PCONR5;          /**< \brief �˿ڿ��ƼĴ���5*/
        stc_tmra_pconr_field_t PCONR5_f;
    };
    union
    {
        __IO uint32_t PCONR6;          /**< \brief �˿ڿ��ƼĴ���6*/
        stc_tmra_pconr_field_t PCONR6_f;
    };
    union
    {
        __IO uint32_t PCONR7;          /**< \brief �˿ڿ��ƼĴ���7*/
        stc_tmra_pconr_field_t PCONR7_f;
    };
    union
    {
        __IO uint32_t PCONR8;          /**< \brief �˿ڿ��ƼĴ���8*/
        stc_tmra_pconr_field_t PCONR8_f;
    };
} amhw_hc32f460_timea_t;

typedef enum timea_channel
{
    TIMERA_CH1 = 0U,                      
    TIMERA_CH2 = 1U,                     
    TIMERA_CH3 = 2U,                     
    TIMERA_CH4 = 3U,                     
    TIMERA_CH5 = 4U,                     
    TIMERA_CH6 = 5U,                     
    TIMERA_CH7 = 6U,                     
    TIMERA_CH8 = 7U,                   
} timea_channel_t;

typedef enum en_timera_count_start_output
{
    TimeraCountStartOutputLow  = 0u,       /**< \brief TIMA_<t>_PWMn port output low level */
    TimeraCountStartOutputHigh = 1u,       /**< \brief TIMA_<t>_PWMn port output high level */
    TimeraCountStartOutputKeep = 2u,       /**< \brief TIMA_<t>_PWMn port output to keep */
} en_timera_count_start_output_t;

typedef enum en_timera_count_stop_output
{
    TimeraCountStopOutputLow  = 0u,                /**< \brief TIMA_<t>_PWMn port output low level */
    TimeraCountStopOutputHigh = 1u,                /**< \brief TIMA_<t>_PWMn port output high level */
    TimeraCountStopOutputKeep = 2u,                /**< \brief TIMA_<t>_PWMn port output to keep */
} en_timera_count_stop_output_t;

typedef enum en_timera_compare_match_output
{
    TimeraCompareMatchOutputLow     = 0u,          /**< \brief TIMA_<t>_PWMn port output low level */
    TimeraCompareMatchOutputHigh    = 1u,          /**< \brief TIMA_<t>_PWMn port output high level */
    TimeraCompareMatchOutputKeep    = 2u,          /**< \brief TIMA_<t>_PWMn port output to keep */
    TimeraCompareMatchOutputReverse = 3u,          /**< \brief TIMA_<t>_PWMn port output reverse */
} en_timera_compare_match_output_t;

typedef enum en_timera_period_match_output
{
    TimeraPeriodMatchOutputLow     = 0u,           /**< \brief TIMA_<t>_PWMn port output low level */
    TimeraPeriodMatchOutputHigh    = 1u,           /**< \brief TIMA_<t>_PWMn port output high level */
    TimeraPeriodMatchOutputKeep    = 2u,           /**< \brief TIMA_<t>_PWMn port output to keep */
    TimeraPeriodMatchOutputReverse = 3u,           /**< \brief TIMA_<t>_PWMn port output reverse */
} en_timera_period_match_output_t;

typedef enum en_timera_specify_output
{
    TimeraSpecifyOutputInvalid = 0u,               /**< \brief TIMA_<t>_PWMn port output invalid */
    TimeraSpecifyOutputLow     = 2u,               /**< \brief TIMA_<t>_PWMn port output low level from next period */
    TimeraSpecifyOutputHigh    = 3u,               /**< \brief TIMA_<t>_PWMn port output high level from next period */
} en_timera_specify_output_t;

typedef enum en_functional_state
{
    Disable = 0u,
    Enable  = 1u,
} en_functional_state_t;

/**
 *******************************************************************************
 ** \brief Timera compare output init structure definition
 ******************************************************************************/
typedef struct stc_timera_compare_init
{
    uint16_t                         u16CompareVal;                /**< \brief Compare value */
    en_timera_count_start_output_t   enStartCountOutput;           /**< \brief Port status set when count start */
    en_timera_count_stop_output_t    enStopCountOutput;            /**< \brief Port status set when count stop */
    en_timera_compare_match_output_t enCompareMatchOutput;         /**< \brief Port status set when compare value match */
    en_timera_period_match_output_t  enPeriodMatchOutput;          /**< \brief Port status set when period value match */
    en_timera_specify_output_t       enSpecifyOutput;              /**< \brief Specify port status,next period valid,priority more than other port status set */
    en_functional_state_t            enCacheEn;                    /**< \brief Enable/Disable cache��Only unit 1��3��5��7 valid */
    en_functional_state_t            enTriangularTroughTransEn;    /**< \brief Enable/Disable triangular wave trough transmit cache value��Only unit 1��3��5��7 valid */
    en_functional_state_t            enTriangularCrestTransEn;     /**< \brief Enable/Disable triangular wave crest transmit cache value��Only unit 1��3��5��7 valid */
    uint16_t                         u16CompareCacheVal;           /**< \brief Compare cache value,Only unit 1��3��5��7 valid */
} stc_timera_compare_init_t;

#define TIMERA_CALC_REG_ADDR(reg, chl)          ((uint32_t)(&(reg)) + (chl)*0x4u)

/**
 *******************************************************************************
 ** \brief Input port filter clock division enumeration
 ******************************************************************************/
typedef enum en_timera_filter_clk_div
{
    TimeraFilterPclkDiv1  = 0u,        /**< \brief Filter clock: pclk */
    TimeraFilterPclkDiv4  = 1u,        /**< \brief Filter clock: pclk/4 */
    TimeraFilterPclkDiv16 = 2u,        /**< \brief Filter clock: pclk/16 */
    TimeraFilterPclkDiv64 = 3u,        /**< \brief Filter clock: pclk/64 */
} en_timera_filter_clk_div_t;

/**
 *******************************************************************************
 ** \brief Timera capture input init structure definition
 ******************************************************************************/
typedef struct stc_timera_capture_init
{
    en_functional_state_t      enCapturePwmRisingEn;               /**< \brief Enable/Disable capture channel n active when TIMA_<t>_PWMn sample rising */
    en_functional_state_t      enCapturePwmFallingEn;              /**< \brief Enable/Disable capture channel n active when TIMA_<t>_PWMn sample falling */
    en_functional_state_t      enCaptureSpecifyEventEn;            /**< \brief Enable/Disable capture channel n active when specify event trigger,event value is TMRA_HTSSR1 */
    en_timera_filter_clk_div_t enPwmClkDiv;                        /**< \brief TIMA_<t>_PWMn filter clock select */
    en_functional_state_t      enPwmFilterEn;                      /**< \brief Enable/Disable TIMA_<t>_PWMn filter functions */
    en_functional_state_t      enCaptureTrigRisingEn;              /**< \brief Enable/Disable capture channel 4 active when TIMA_<t>_TRIG sample rising, only CCONR4 valid */
    en_functional_state_t      enCaptureTrigFallingEn;             /**< \brief Enable/Disable capture channel 4 active when TIMA_<t>_TRIG sample falling, only CCONR4 valid */
    en_timera_filter_clk_div_t enTrigClkDiv;                       /**< \brief TIMA_<t>_TRIG filter clock select, only CCONR4 valid */
    en_functional_state_t      enTrigFilterEn;                     /**< \brief Enable/Disable TIMA_<t>_TRIG filter functions , only CCONR4 valid */
} stc_timera_capture_init_t;


/**
 * \brief ARR-16λģʽ���ؼĴ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ARR���ؼĴ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_timea_arr_count_get (amhw_hc32f460_timea_t *p_hw_tim, uint8_t chan)
{
    return p_hw_tim->PERAR;
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
void amhw_hc32f460_timea_arr_count_set (amhw_hc32f460_timea_t *p_hw_tim, uint8_t chan, uint16_t value)
{
    p_hw_tim->PERAR = value;
}

am_static_inline
void amhw_hc32f460_timea_cnt16_count_set (amhw_hc32f460_timea_t *p_hw_tim, uint16_t value)
{
    p_hw_tim->CNTER = value;
}

/**
 * \brief CNT-16λģʽ�����Ĵ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return CNT�����Ĵ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_timea_cnt16_count_get (amhw_hc32f460_timea_t *p_hw_tim, uint8_t chan)
{
    return (uint16_t)p_hw_tim->CNTER;
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
 * \return ���õĹ���ģʽ��amhw_hc32f460_timea_mode_tö������
 */
am_static_inline
timea_counter_mode_t amhw_hc32f460_timea_mode_get (amhw_hc32f460_timea_t *p_hw_tim)
{
    return (timea_counter_mode_t)(p_hw_tim->BCSTR_f.MODE);
}

/**
 * \brief CMODE ����ģʽ  ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] mode     : ���õĹ���ģʽ��amhw_hc32f460_timea_mode_tö������
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_timea_mode_set (amhw_hc32f460_timea_t     *p_hw_tim,
                                   timea_counter_mode_t       mode)
{
    p_hw_tim->BCSTR_f.MODE = mode;
}

am_static_inline
void amhw_hc32f460_timea_dir_set (amhw_hc32f460_timea_t     *p_hw_tim,
                                  timea_count_dir_t          dir)
{
    p_hw_tim->BCSTR_f.DIR = dir;
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
void amhw_hc32f460_timea_disable (amhw_hc32f460_timea_t *p_hw_tim, uint8_t chan)
{
    p_hw_tim->BCSTR_f.START = 0;

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
void amhw_hc32f460_timea_enable (amhw_hc32f460_timea_t *p_hw_tim, uint8_t chan)
{
    p_hw_tim->BCSTR_f.START = 1;
}

/**
 * \brief �ڲ�ʱ�ӷ�Ƶѡ��
 */
typedef enum {
    AMHW_HC32F460_TIMEA_CLK_DIV0 = 0,    /**< \brief 1��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV2,        /**< \brief 2��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV4,        /**< \brief 4��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV8,        /**< \brief 8��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV16,       /**< \brief 16��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV32,       /**< \brief 32��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV64,       /**< \brief 64��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV128,      /**< \brief 128��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV256,      /**< \brief 256��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV512,      /**< \brief 512��Ƶ */
    AMHW_HC32F460_TIMEA_CLK_DIV1024,     /**< \brief 1024��Ƶ */
}amhw_hc32f460_timea_clkdiv_t;

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ���õķ�Ƶϵ����amhw_hc32f460_timea_clkdiv_tö������
 */
am_static_inline
amhw_hc32f460_timea_clkdiv_t
amhw_hc32f460_timea_mode_clkdiv_get (amhw_hc32f460_timea_t *p_hw_tim,
                                         uint8_t                chan)
{
    amhw_hc32f460_timea_clkdiv_t clkdiv;
    clkdiv = (amhw_hc32f460_timea_clkdiv_t)p_hw_tim->BCSTR_f.CKDIV;
    return clkdiv;
}

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] clkdiv   : ���õķ�Ƶϵ����amhw_hc32f460_timea_clkdiv_tö������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_timea_mode_clkdiv_set (amhw_hc32f460_timea_t       *p_hw_tim,
                                          uint8_t                      chan, 
                                          amhw_hc32f460_timea_clkdiv_t clkdiv)
{
    p_hw_tim->BCSTR_f.CKDIV = clkdiv;
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
void amhw_hc32f460_timea_int_disable (amhw_hc32f460_timea_t *p_hw_tim,
                                      timea_irq_type_t       irq)
{
    switch (irq)
    {
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH1:
            p_hw_tim->ICONR_f.ITEN1 = 0;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH2:
            p_hw_tim->ICONR_f.ITEN2 = 0;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH3:
            p_hw_tim->ICONR_f.ITEN3 = 0;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH4:
            p_hw_tim->ICONR_f.ITEN4 = 0;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH5:
            p_hw_tim->ICONR_f.ITEN5 = 0;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH6:
            p_hw_tim->ICONR_f.ITEN6 = 0;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH7:
            p_hw_tim->ICONR_f.ITEN7 = 0;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH8:
            p_hw_tim->ICONR_f.ITEN8 = 0;
            break;
        case TIMERA_IRQ_OVERFLOW:
            p_hw_tim->BCSTR_f.ITENOVF = 0;
            break;
        case TIMERA_IRQ_UNDERFLOW:
            p_hw_tim->BCSTR_f.ITENUDF = 0;
            break;
        default:
            break;
    }
}

/**
 * \brief UIE �ж�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_timea_int_enable (amhw_hc32f460_timea_t *p_hw_tim,
                                     timea_irq_type_t       irq)
{
    switch (irq)
    {
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH1:
            p_hw_tim->ICONR_f.ITEN1 = 1;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH2:
            p_hw_tim->ICONR_f.ITEN2 = 1;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH3:
            p_hw_tim->ICONR_f.ITEN3 = 1;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH4:
            p_hw_tim->ICONR_f.ITEN4 = 1;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH5:
            p_hw_tim->ICONR_f.ITEN5 = 1;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH6:
            p_hw_tim->ICONR_f.ITEN6 = 1;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH7:
            p_hw_tim->ICONR_f.ITEN7 = 1;
            break;
        case TIMERA_IRQ_CAPTURE_OR_COMPARE_CH8:
            p_hw_tim->ICONR_f.ITEN8 = 1;
            break;
        case TIMERA_IRQ_OVERFLOW:
            p_hw_tim->BCSTR_f.ITENOVF = 1;
            break;
        case TIMERA_IRQ_UNDERFLOW:
            p_hw_tim->BCSTR_f.ITENUDF = 1;
            break;
        default:
            break;
    }

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
am_bool_t amhw_hc32f460_timea_int_flag_check(amhw_hc32f460_timea_t *p_hw_tim,
                                             timea_flag_type_t      flag)
{
//    return (p_hw_tim->ifr & 0x1ul) ? AM_TRUE : AM_FALSE;
    uint8_t value = 0;
    if(TIMEA_FLAG_CAPTURE_OR_COMPARE_CH1 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF1;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH2 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF2;
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH3 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF3;
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH4 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF4;
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH5 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF5;
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH6 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF6;
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH7 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF7;
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH8 == flag)
    {
        value = p_hw_tim->STFLR_f.CMPF8;
    }else if (TIMEA_FLAG_OVERFLOW == flag)
    {
        value = p_hw_tim->BCSTR_f.OVFF;
    }else if (TIMEA_FLAG_UNDERFLOW == flag)
    {
        value = p_hw_tim->BCSTR_f.UDFF;
    } else {
        ;
    }
    return value ? AM_TRUE : AM_FALSE;
}

/**
 * \brief UIF ����ж� ��־���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_timea_int_flag_clr(amhw_hc32f460_timea_t *p_hw_tim,
                                      timea_flag_type_t      flag)
{
    if(TIMEA_FLAG_CAPTURE_OR_COMPARE_CH1 == flag)
    {
        p_hw_tim->STFLR_f.CMPF1 = 0;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH2 == flag)
    {
        p_hw_tim->STFLR_f.CMPF2 = 0;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH3 == flag)
    {
        p_hw_tim->STFLR_f.CMPF3 = 0;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH4 == flag)
    {
        p_hw_tim->STFLR_f.CMPF4 = 0;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH5 == flag)
    {
        p_hw_tim->STFLR_f.CMPF5 = 0;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH6 == flag)
    {
        p_hw_tim->STFLR_f.CMPF6 = 0;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH7 == flag)
    {
        p_hw_tim->STFLR_f.CMPF7 = 0;        
    } else if (TIMEA_FLAG_CAPTURE_OR_COMPARE_CH8 == flag)
    {
        p_hw_tim->STFLR_f.CMPF8 = 0;        
    }else if (TIMEA_FLAG_OVERFLOW == flag)
    {
        p_hw_tim->BCSTR_f.OVFF = 0;
    }else if (TIMEA_FLAG_UNDERFLOW == flag)
    {
        p_hw_tim->BCSTR_f.UDFF = 0;
    } else {
        ;
    }
}

am_static_inline
void amhw_hc32f460_timea_int_all_flag_clr(amhw_hc32f460_timea_t *p_hw_tim)
{
    p_hw_tim->STFLR_f.CMPF1 = 0;        
    p_hw_tim->STFLR_f.CMPF2 = 0;   
    p_hw_tim->STFLR_f.CMPF3 = 0;        
    p_hw_tim->STFLR_f.CMPF4 = 0;        
    p_hw_tim->STFLR_f.CMPF5 = 0;        
    p_hw_tim->STFLR_f.CMPF6 = 0;        
    p_hw_tim->STFLR_f.CMPF7 = 0;        
    p_hw_tim->STFLR_f.CMPF8 = 0;        

    p_hw_tim->BCSTR_f.OVFF = 0;
    p_hw_tim->BCSTR_f.UDFF = 0;
}


am_static_inline
uint16_t amhw_hc32f460_timea_get_compare_value(amhw_hc32f460_timea_t *p_hw_tim,
                                               timea_channel_t        enChannel)
{
    uint16_t u16CompareVal = 0u;
    __IO stc_tmra_cmpar_field_t *pstcTimeraCompare;

    pstcTimeraCompare = (stc_tmra_cmpar_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->CMPAR1, enChannel);
    u16CompareVal = (uint16_t)pstcTimeraCompare->CMP;

    return u16CompareVal;
}

am_static_inline
am_bool_t amhw_hc32f460_timea_compare_init(amhw_hc32f460_timea_t           *p_hw_tim,
                                           timea_channel_t                  enChannel,
                                           const stc_timera_compare_init_t *pstcCompareInit)
{
    am_bool_t enRet = AM_FALSE;
    __IO stc_tmra_pconr_field_t *pstcTimeraPort;
    __IO stc_tmra_bconr_field_t *pstcTimeraCache;
    __IO stc_tmra_cmpar_field_t *pstcTimeraCompare;
    __IO stc_tmra_cconr_field_t *pstcTimeraCapture;

    /* Check parameters */
    if((NULL != p_hw_tim) && (NULL != pstcCompareInit))
    {
        /* Configure port control register */
        pstcTimeraPort = (stc_tmra_pconr_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->PCONR1, enChannel);
        pstcTimeraPort->STAC = pstcCompareInit->enStartCountOutput;
        pstcTimeraPort->STPC = pstcCompareInit->enStopCountOutput;
        pstcTimeraPort->CMPC = pstcCompareInit->enCompareMatchOutput;
        pstcTimeraPort->PERC = pstcCompareInit->enPeriodMatchOutput;
        pstcTimeraPort->FORC = pstcCompareInit->enSpecifyOutput;

        /* Configure cache control register */
        if ((TIMERA_CH1 == enChannel) || (TIMERA_CH3 == enChannel) ||
            (TIMERA_CH5 == enChannel) || (TIMERA_CH7 == enChannel))
        {
            pstcTimeraCache = (stc_tmra_bconr_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->BCONR1, enChannel);
            pstcTimeraCache->BSE0 = pstcCompareInit->enTriangularCrestTransEn;
            pstcTimeraCache->BSE1 = pstcCompareInit->enTriangularTroughTransEn;
            pstcTimeraCache->BEN = pstcCompareInit->enCacheEn;
            /* Configure compare cache value register */
            pstcTimeraCompare = (stc_tmra_cmpar_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->CMPAR1, enChannel + 1);
            pstcTimeraCompare->CMP = pstcCompareInit->u16CompareCacheVal;
        }

        /* Configure compare value register */
        pstcTimeraCompare = (stc_tmra_cmpar_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->CMPAR1, enChannel);
        pstcTimeraCompare->CMP = pstcCompareInit->u16CompareVal;

        /* Set compare output function */
        pstcTimeraCapture = (stc_tmra_cconr_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->CCONR1, enChannel);
        pstcTimeraCapture->CAPMDA = 0u;
        enRet = AM_TRUE;
    }

    return enRet;
}

am_static_inline
am_bool_t  amhw_hc32f460_timea_compare_cmd(amhw_hc32f460_timea_t *p_hw_tim,
                                           timea_channel_t        enChannel,
                                           en_functional_state_t  enNewSta)
{
    am_bool_t enRet = AM_FALSE;
    __IO stc_tmra_pconr_field_t *pstcTimeraPort;

    pstcTimeraPort = (stc_tmra_pconr_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->PCONR1, enChannel);
    pstcTimeraPort->OUTEN = enNewSta;
    enRet = AM_TRUE;
    return enRet;
}

am_static_inline
am_bool_t amhw_hc32f460_timea_capture_init(amhw_hc32f460_timea_t           *p_hw_tim,
                                           timea_channel_t                  enChannel,
                                           const stc_timera_capture_init_t *pstcCapInit)
{
    am_bool_t enRet = AM_FALSE;
    __IO stc_tmra_cconr_field_t *pstcTimeraCapture;

    /* Check parameters */
    if((NULL != p_hw_tim) && (NULL != pstcCapInit))
    {
        /* Configure capture control register */
        pstcTimeraCapture = (stc_tmra_cconr_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->CCONR1, enChannel);
        pstcTimeraCapture->HICP0 = pstcCapInit->enCapturePwmRisingEn;
        pstcTimeraCapture->HICP1 = pstcCapInit->enCapturePwmFallingEn;
        pstcTimeraCapture->HICP2 = pstcCapInit->enCaptureSpecifyEventEn;
        pstcTimeraCapture->NOFICKCP = pstcCapInit->enPwmClkDiv;
        pstcTimeraCapture->NOFIENCP = pstcCapInit->enPwmFilterEn;

        /* TIMA_<t>_TRIG port capture function only valid for TimeraCh4 */
        if (TIMERA_CH4 == enChannel)
        {
            pstcTimeraCapture->HICP3 = pstcCapInit->enCaptureTrigRisingEn;
            pstcTimeraCapture->HICP4 = pstcCapInit->enCaptureTrigFallingEn;
            /* Configure filter control register */
            p_hw_tim->FCONR_f.NOFICKTG = pstcCapInit->enTrigClkDiv;
            p_hw_tim->FCONR_f.NOFIENTG = pstcCapInit->enTrigFilterEn;
        }

        /* Set capture input function */
        pstcTimeraCapture->CAPMDA = 1u;
        enRet = AM_TRUE;
    }

    return enRet;
}                               


am_static_inline
am_bool_t  amhw_hc32f460_timea_compare_cache_cmd(amhw_hc32f460_timea_t *p_hw_tim,
                                                 timea_channel_t        enChannel,
                                                 en_functional_state_t  enNewSta)
{
    /*attention: enChannel must TimeraCh1 TimeraCh3 TimeraCh5 TimeraCh7*/
    am_bool_t enRet = AM_FALSE;
    __IO stc_tmra_bconr_field_t *pstcTimeraCache;

    if (TIMERA_CH1 == enChannel || TIMERA_CH3 == enChannel || TIMERA_CH5 == enChannel || TIMERA_CH7 == enChannel)
    {
        /* Configure cache control register */
        pstcTimeraCache = (stc_tmra_bconr_field_t *)TIMERA_CALC_REG_ADDR(p_hw_tim->BCONR1, enChannel);
        pstcTimeraCache->BEN = enNewSta;
        enRet = AM_TRUE;
    }

    return enRet;
}

/**
 * @}
 */


/* ʹ�������ṹ�������������Ľ��� */
#if defined(__CC_ARM)
    #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
    #pragma warning restore
#else
    #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_TIMEA_H */

/* end of file */
