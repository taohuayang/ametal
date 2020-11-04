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
 * \brief �߼���ʱ��ADTIM�ӿ�
 *
 * \internal
 * \par History
 * - 1.00 19-10-08  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_HC32F460_ADTIM_H
#define __AMHW_HC32F460_ADTIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "hc32f460_regbase.h"

/**
 * \addtogroup amhw_hc32f460_if_adtim
 * \copydoc amhw_hc32f460_adtim.h
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
 * \brief TMR6 - ͨ�ü���ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CNT                       :16;  /**< \brief ��ǰ��ʱ���ļ���ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_cnter_field_t;

/**
 * \brief TMR6 - ͨ�����ڻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PERA                      :16;  /**< \brief ��������ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_perar_field_t;

/**
 * \brief TMR6 - ͨ�����ڻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PERB                      :16;  /**< \brief ��������ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_perbr_field_t;

/**
 * \brief TMR6 - ͨ�����ڻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PERC                      :16;  /**< \brief ��������ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_percr_field_t;

/**
 * \brief TMR6 - ͨ�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t GCMA                      :16;  /**< \brief �����Ƚϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_gcmar_field_t;

/**
 * \brief TMR6 - ͨ�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t GCMB                      :16;  /**< \brief �����Ƚϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_gcmbr_field_t;

/**
 * \brief TMR6 - ͨ�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t GCMC                      :16;  /**< \brief �����Ƚϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_gcmcr_field_t;

/**
 * \brief TMR6 - ͨ�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t GCMD                      :16;  /**< \brief �����Ƚϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_gcmdr_field_t;

/**
 * \brief TMR6 - ͨ�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t GCME                      :16;  /**< \brief �����Ƚϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_gcmer_field_t;

/**
 * \brief TMR6 - ͨ�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t GCMF                      :16;  /**< \brief �����Ƚϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_gcmfr_field_t;

/**
 * \brief TMR6 - ר�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SCMA                      :16;  /**< \brief ר�ñȽϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_scmar_field_t;

/**
 * \brief TMR6 - ר�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SCMB                      :16;  /**< \brief ר�ñȽϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_scmbr_field_t;

/**
 * \brief TMR6 - ר�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SCMC                      :16;  /**< \brief ר�ñȽϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_scmcr_field_t;

/**
 * \brief TMR6 - ר�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SCMD                      :16;  /**< \brief ר�ñȽϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_scmdr_field_t;

/**
 * \brief TMR6 - ר�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SCME                      :16;  /**< \brief ר�ñȽϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_scmer_field_t;

/**
 * \brief TMR6 - ר�ñȽϻ�׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SCMF                      :16;  /**< \brief ר�ñȽϻ�׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_scmfr_field_t;

/**
 * \brief TMR6 - ����ʱ���׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DTUA                      :16;  /**< \brief ����ʱ��ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_dtuar_field_t;

/**
 * \brief TMR6 - ����ʱ���׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DTDA                      :16;  /**< \brief ����ʱ��ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_dtdar_field_t;

/**
 * \brief TMR6 - ����ʱ���׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DTUB                      :16;  /**< \brief ����ʱ��ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_dtubr_field_t;

/**
 * \brief TMR6 - ����ʱ���׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DTDB                      :16;  /**< \brief ����ʱ��ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr6_dtdbr_field_t;

/**
 * \brief TMR6 - ͨ�ÿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t START                     : 1;  /**< \brief ��ʱ������*/
    __IO uint32_t MODE                      : 3;  /**< \brief ����ģʽ*/
    __IO uint32_t CKDIV                     : 3;  /**< \brief ����ʱ��ѡ��*/
    uint32_t RESERVED7                      : 1;  /**< \brief ����*/
    __IO uint32_t DIR                       : 1;  /**< \brief ��������*/
    uint32_t RESERVED9                      : 7;  /**< \brief ����*/
    __IO uint32_t ZMSKREV                   : 1;  /**< \brief Z�����빫ת��ʱ��ѡ��*/
    __IO uint32_t ZMSKPOS                   : 1;  /**< \brief Z������λ�ö�ʱ��ѡ��*/
    __IO uint32_t ZMSKVAL                   : 2;  /**< \brief Z����������������*/
    uint32_t RESERVED20                     :12;  /**< \brief ����*/
} stc_tmr6_gconr_field_t;

/**
 * \brief TMR6 - �жϿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t INTENA                    : 1;  /**< \brief ����ƥ���ж�ʹ��A*/
    __IO uint32_t INTENB                    : 1;  /**< \brief ����ƥ���ж�ʹ��B*/
    __IO uint32_t INTENC                    : 1;  /**< \brief ����ƥ���ж�ʹ��C*/
    __IO uint32_t INTEND                    : 1;  /**< \brief ����ƥ���ж�ʹ��D*/
    __IO uint32_t INTENE                    : 1;  /**< \brief ����ƥ���ж�ʹ��E*/
    __IO uint32_t INTENF                    : 1;  /**< \brief ����ƥ���ж�ʹ��F*/
    __IO uint32_t INTENOVF                  : 1;  /**< \brief �����ж�ʹ��*/
    __IO uint32_t INTENUDF                  : 1;  /**< \brief �����ж�ʹ��*/
    __IO uint32_t INTENDTE                  : 1;  /**< \brief ����ʱ������ж�ʹ��*/
    uint32_t RESERVED9                      : 7;  /**< \brief ����*/
    __IO uint32_t INTENSAU                  : 1;  /**< \brief ר�����ϼ����ж�ʹ��A*/
    __IO uint32_t INTENSAD                  : 1;  /**< \brief ר�����¼����ж�ʹ��A*/
    __IO uint32_t INTENSBU                  : 1;  /**< \brief ר�����ϼ����ж�ʹ��B*/
    __IO uint32_t INTENSBD                  : 1;  /**< \brief ר�����¼����ж�ʹ��B*/
    uint32_t RESERVED20                     :12;  /**< \brief ����*/
} stc_tmr6_iconr_field_t;

/**
 * \brief TMR6 - �˿ڿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CAPMDA                    : 1;  /**< \brief ����ģʽѡ��A*/
    __IO uint32_t STACA                     : 1;  /**< \brief ������ʼ�˿�״̬�趨A*/
    __IO uint32_t STPCA                     : 1;  /**< \brief ����ֹͣ�˿�״̬A*/
    __IO uint32_t STASTPSA                  : 1;  /**< \brief ������ʼֹͣ�˿�״̬ѡ��A*/
    __IO uint32_t CMPCA                     : 2;  /**< \brief ����ֵƥ��ʱ�˿��趨A*/
    __IO uint32_t PERCA                     : 2;  /**< \brief ����ֵƥ��ʱ�˿��趨A*/
    __IO uint32_t OUTENA                    : 1;  /**< \brief ���ʹ��A*/
    __IO uint32_t EMBSELA                   : 2;
    __IO uint32_t EMBVALA                   : 2;  /**< \brief EMB״̬����A*/
    uint32_t RESERVED13                     : 3;  /**< \brief ����*/
    __IO uint32_t CAPMDB                    : 1;  /**< \brief ����ģʽѡ��B*/
    __IO uint32_t STACB                     : 1;  /**< \brief ������ʼ�˿�״̬�趨B*/
    __IO uint32_t STPCB                     : 1;  /**< \brief ����ֹͣ�˿�״̬B*/
    __IO uint32_t STASTPSB                  : 1;  /**< \brief ������ʼֹͣ�˿�״̬ѡ��B*/
    __IO uint32_t CMPCB                     : 2;  /**< \brief �Ƚ�ֵƥ��ʱ�˿��趨B*/
    __IO uint32_t PERCB                     : 2;  /**< \brief ����ֵƥ��ʱ�˿��趨B*/
    __IO uint32_t OUTENB                    : 1;  /**< \brief ���ʹ��B*/
    __IO uint32_t EMBSELB                   : 2;
    __IO uint32_t EMBVALB                   : 2;  /**< \brief EMB״̬����B*/
    uint32_t RESERVED29                     : 3;  /**< \brief ����*/
} stc_tmr6_pconr_field_t;

/**
 * \brief TMR6 - ������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t BENA                      : 1;  /**< \brief ͨ�ñȽ�ֵ���洫��Aʹ��*/
    __IO uint32_t BSEA                      : 1;  /**< \brief ͨ�ñȽ�ֵ���洫��ѡ��A*/
    __IO uint32_t BENB                      : 1;  /**< \brief ͨ�ñȽ�ֵ���洫��Bʹ��*/
    __IO uint32_t BSEB                      : 1;  /**< \brief ͨ�ñȽ�ֵ���洫��ѡ��B*/
    uint32_t RESERVED4                      : 4;  /**< \brief ����*/
    __IO uint32_t BENP                      : 1;  /**< \brief ����ֵ���洫��ʹ��*/
    __IO uint32_t BSEP                      : 1;  /**< \brief ����ֵ���洫��*/
    uint32_t RESERVED10                     : 6;  /**< \brief ����*/
    __IO uint32_t BENSPA                    : 1;  /**< \brief ר�ñȽϻ�׼ֵ���洫��ʹ��A*/
    __IO uint32_t BSESPA                    : 1;  /**< \brief ר�ñȽϻ�׼ֵ���洫��ѡ��A*/
    uint32_t RESERVED18                     : 2;  /**< \brief ����*/
    __IO uint32_t BTRSPA                    : 2;  /**< \brief ר�ñȽϻ�׼ֵ���洫��ʱ���A*/
    uint32_t RESERVED22                     : 2;  /**< \brief ����*/
    __IO uint32_t BENSPB                    : 1;  /**< \brief ר�ñȽϻ�׼ֵ���洫��ʹ��B*/
    __IO uint32_t BSESPB                    : 1;  /**< \brief ר�ñȽϻ�׼ֵ���洫��ѡ��B*/
    uint32_t RESERVED26                     : 2;  /**< \brief ����*/
    __IO uint32_t BTRSPB                    : 2;  /**< \brief ר�ñȽϻ�׼ֵ���洫��ʱ���B*/
    uint32_t RESERVED30                     : 2;  /**< \brief ����*/
} stc_tmr6_bconr_field_t;

/**
 * \brief TMR6 - �������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DTCEN                     : 1;  /**< \brief ��������ʹ��*/
    uint32_t RESERVED1                      : 3;  /**< \brief ����*/
    __IO uint32_t DTBENU                    : 1;  /**< \brief ����ʱ�仺�洫��U*/
    __IO uint32_t DTBEND                    : 1;  /**< \brief ����ʱ�仺�洫��D*/
    uint32_t RESERVED6                      : 2;  /**< \brief ����*/
    __IO uint32_t SEPA                      : 1;  /**< \brief �����趨*/
    uint32_t RESERVED9                      :23;  /**< \brief ����*/
} stc_tmr6_dconr_field_t;

/**
 * \brief TMR6 - �˲����ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t NOFIENGA                  : 1;  /**< \brief ��������˿��˲�GA*/
    __IO uint32_t NOFICKGA                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��GA*/
    uint32_t RESERVED3                      : 1;  /**< \brief ����*/
    __IO uint32_t NOFIENGB                  : 1;  /**< \brief ��������˿��˲�GB*/
    __IO uint32_t NOFICKGB                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��GB*/
    uint32_t RESERVED7                      : 9;  /**< \brief ����*/
    __IO uint32_t NOFIENTA                  : 1;  /**< \brief ��������˿��˲�TA*/
    __IO uint32_t NOFICKTA                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��TA*/
    uint32_t RESERVED19                     : 1;  /**< \brief ����*/
    __IO uint32_t NOFIENTB                  : 1;  /**< \brief ��������˿��˲�TB*/
    __IO uint32_t NOFICKTB                  : 2;  /**< \brief �˲�������׼ʱ��ѡ��TB*/
    uint32_t RESERVED23                     : 9;  /**< \brief ����*/
} stc_tmr6_fconr_field_t;

/**
 * \brief TMR6 - ��Ч���ڼĴ���λ��ṹ��
 */
typedef struct
{
    uint32_t RESERVED0                      : 8;  /**< \brief ����*/
    __IO uint32_t SPPERIA                   : 1;  /**< \brief ר���ź���Ч����ѡ��A*/
    __IO uint32_t SPPERIB                   : 1;  /**< \brief ר���ź���Ч����ѡ��B*/
    uint32_t RESERVED10                     : 6;  /**< \brief ����*/
    __IO uint32_t PCNTE                     : 2;  /**< \brief ��Ч���ڼ�������ѡ��*/
    __IO uint32_t PCNTS                     : 3;  /**< \brief ��Ч����ѡ��*/
    uint32_t RESERVED21                     :11;  /**< \brief ����*/
} stc_tmr6_vperr_field_t;

/**
 * \brief TMR6 - ״̬��־�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CMAF                      : 1;  /**< \brief ����ƥ��A*/
    __IO uint32_t CMBF                      : 1;  /**< \brief ����ƥ��B*/
    __IO uint32_t CMCF                      : 1;  /**< \brief ����ƥ��C*/
    __IO uint32_t CMDF                      : 1;  /**< \brief ����ƥ��D*/
    __IO uint32_t CMEF                      : 1;  /**< \brief ����ƥ��E*/
    __IO uint32_t CMFF                      : 1;  /**< \brief ����ƥ��F*/
    __IO uint32_t OVFF                      : 1;  /**< \brief ����ƥ��*/
    __IO uint32_t UDFF                      : 1;  /**< \brief ����ƥ��*/
    __IO uint32_t DTEF                      : 1;  /**< \brief ����ʱ�����*/
    __IO uint32_t CMSAUF                    : 1;  /**< \brief ���ϼ���ר�ñȽϻ�׼ֵƥ��A*/
    __IO uint32_t CMSADF                    : 1;  /**< \brief ���¼���ר�ñȽϻ�׼ֵƥ��A*/
    __IO uint32_t CMSBUF                    : 1;  /**< \brief ���ϼ���ר�ñȽϻ�׼ֵƥ��B*/
    __IO uint32_t CMSBDF                    : 1;  /**< \brief ���¼���ר�ñȽϻ�׼ֵƥ��B*/
    uint32_t RESERVED13                     : 8;  /**< \brief ����*/
    __IO uint32_t VPERNUM                   : 3;  /**< \brief ���ڴ���*/
    uint32_t RESERVED24                     : 7;  /**< \brief ����*/
    __IO uint32_t DIRF                      : 1;  /**< \brief ��������*/
} stc_tmr6_stflr_field_t;

/**
 * \brief TMR6 - Ӳ�������¼�ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HSTA0                     : 1;  /**< \brief Ӳ����������0*/
    __IO uint32_t HSTA1                     : 1;  /**< \brief Ӳ����������1*/
    uint32_t RESERVED2                      : 2;  /**< \brief ����*/
    __IO uint32_t HSTA4                     : 1;  /**< \brief Ӳ����������4*/
    __IO uint32_t HSTA5                     : 1;  /**< \brief Ӳ����������5*/
    __IO uint32_t HSTA6                     : 1;  /**< \brief Ӳ����������6*/
    __IO uint32_t HSTA7                     : 1;  /**< \brief Ӳ����������7*/
    __IO uint32_t HSTA8                     : 1;  /**< \brief Ӳ����������8*/
    __IO uint32_t HSTA9                     : 1;  /**< \brief Ӳ����������9*/
    __IO uint32_t HSTA10                    : 1;  /**< \brief Ӳ����������10*/
    __IO uint32_t HSTA11                    : 1;  /**< \brief Ӳ����������11*/
    uint32_t RESERVED12                     :19;  /**< \brief ����*/
    __IO uint32_t STARTS                    : 1;  /**< \brief Ӳ������ʹ��*/
} stc_tmr6_hstar_field_t;

/**
 * \brief TMR6 - Ӳ��ֹͣ�¼�ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HSTP0                     : 1;  /**< \brief Ӳ��ֹͣ����0*/
    __IO uint32_t HSTP1                     : 1;  /**< \brief Ӳ��ֹͣ����1*/
    uint32_t RESERVED2                      : 2;
    __IO uint32_t HSTP4                     : 1;  /**< \brief Ӳ��ֹͣ����4*/
    __IO uint32_t HSTP5                     : 1;  /**< \brief Ӳ��ֹͣ����5*/
    __IO uint32_t HSTP6                     : 1;  /**< \brief Ӳ��ֹͣ����6*/
    __IO uint32_t HSTP7                     : 1;  /**< \brief Ӳ��ֹͣ����7*/
    __IO uint32_t HSTP8                     : 1;  /**< \brief Ӳ��ֹͣ����8*/
    __IO uint32_t HSTP9                     : 1;  /**< \brief Ӳ��ֹͣ����9*/
    __IO uint32_t HSTP10                    : 1;  /**< \brief Ӳ��ֹͣ����10*/
    __IO uint32_t HSTP11                    : 1;  /**< \brief Ӳ��ֹͣ����11*/
    uint32_t RESERVED12                     :19;  /**< \brief ����*/
    __IO uint32_t STOPS                     : 1;  /**< \brief Ӳ��ֹͣʹ��*/
} stc_tmr6_hstpr_field_t;

/**
 * \brief TMR6 - Ӳ�������¼�ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HCLE0                     : 1;  /**< \brief Ӳ����������0*/
    __IO uint32_t HCLE1                     : 1;  /**< \brief Ӳ����������1*/
    uint32_t RESERVED2                      : 2;  /**< \brief ����*/
    __IO uint32_t HCLE4                     : 1;  /**< \brief Ӳ����������4*/
    __IO uint32_t HCLE5                     : 1;  /**< \brief Ӳ����������5*/
    __IO uint32_t HCLE6                     : 1;  /**< \brief Ӳ����������6*/
    __IO uint32_t HCLE7                     : 1;  /**< \brief Ӳ����������7*/
    __IO uint32_t HCLE8                     : 1;  /**< \brief Ӳ����������8*/
    __IO uint32_t HCLE9                     : 1;  /**< \brief Ӳ����������9*/
    __IO uint32_t HCLE10                    : 1;  /**< \brief Ӳ����������10*/
    __IO uint32_t HCLE11                    : 1;  /**< \brief Ӳ����������11*/
    uint32_t RESERVED12                     :19;  /**< \brief ����*/
    __IO uint32_t CLEARS                    : 1;  /**< \brief Ӳ������ʹ��*/
} stc_tmr6_hclrr_field_t;

/**
 * \brief TMR6 - Ӳ�������¼�ѡ��Ĵ���Aλ��ṹ��
 */
typedef struct
{
    __IO uint32_t HCPA0                     : 1;  /**< \brief Ӳ������A����0*/
    __IO uint32_t HCPA1                     : 1;  /**< \brief Ӳ������A����1*/
    uint32_t RESERVED2                      : 2;  /**< \brief ����*/
    __IO uint32_t HCPA4                     : 1;  /**< \brief Ӳ������A����4*/
    __IO uint32_t HCPA5                     : 1;  /**< \brief Ӳ������A����5*/
    __IO uint32_t HCPA6                     : 1;  /**< \brief Ӳ������A����6*/
    __IO uint32_t HCPA7                     : 1;  /**< \brief Ӳ������A����7*/
    __IO uint32_t HCPA8                     : 1;  /**< \brief Ӳ������A����8*/
    __IO uint32_t HCPA9                     : 1;  /**< \brief Ӳ������A����9*/
    __IO uint32_t HCPA10                    : 1;  /**< \brief Ӳ������A����10*/
    __IO uint32_t HCPA11                    : 1;  /**< \brief Ӳ������A����11*/
    uint32_t RESERVED12                     :20;  /**< \brief ����*/
} stc_tmr6_hcpar_field_t;

/**
 * \brief TMR6 - Ӳ�������¼�ѡ��Ĵ���Bλ��ṹ��
 */
typedef struct
{
    __IO uint32_t HCPB0                     : 1;  /**< \brief Ӳ������B����0*/
    __IO uint32_t HCPB1                     : 1;  /**< \brief Ӳ������B����1*/
    uint32_t RESERVED2                      : 2;  /**< \brief ����*/
    __IO uint32_t HCPB4                     : 1;  /**< \brief Ӳ������B����4*/
    __IO uint32_t HCPB5                     : 1;  /**< \brief Ӳ������B����5*/
    __IO uint32_t HCPB6                     : 1;  /**< \brief Ӳ������B����6*/
    __IO uint32_t HCPB7                     : 1;  /**< \brief Ӳ������B����7*/
    __IO uint32_t HCPB8                     : 1;  /**< \brief Ӳ������B����8*/
    __IO uint32_t HCPB9                     : 1;  /**< \brief Ӳ������B����9*/
    __IO uint32_t HCPB10                    : 1;  /**< \brief Ӳ������B����10*/
    __IO uint32_t HCPB11                    : 1;  /**< \brief Ӳ������B����11*/
    uint32_t RESERVED12                     :20;  /**< \brief ����*/
} stc_tmr6_hcpbr_field_t;

/**
 * \brief TMR6 - Ӳ���ݼ��¼�ѡ��Ĵ���λ��ṹ��
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
    uint32_t RESERVED12                     : 4;  /**< \brief ����*/
    __IO uint32_t HCUP16                    : 1;  /**< \brief Ӳ���ݼ�����16*/
    __IO uint32_t HCUP17                    : 1;  /**< \brief Ӳ���ݼ�����17*/
    uint32_t RESERVED18                     :14;  /**< \brief ����*/
} stc_tmr6_hcupr_field_t;

/**
 * \brief TMR6 - Ӳ���ݼ��¼�ѡ��Ĵ���λ��ṹ��
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
    uint32_t RESERVED12                     : 4;  /**< \brief ����*/
    __IO uint32_t HCDO16                    : 1;  /**< \brief Ӳ���ݼ�����16*/
    __IO uint32_t HCDO17                    : 1;  /**< \brief Ӳ���ݼ�����17*/
    uint32_t RESERVED18                     :14;  /**< \brief ����*/
} stc_tmr6_hcdor_field_t;

/**
 * \brief TMR6 - ���ͬ���������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SSTA1                     : 1;  /**< \brief ��Ԫ1�������*/
    __IO uint32_t SSTA2                     : 1;  /**< \brief ��Ԫ2�������*/
    __IO uint32_t SSTA3                     : 1;  /**< \brief ��Ԫ3�������*/
    uint32_t RESERVED3                      :13;  /**< \brief ����*/
    __IO uint32_t RESV0                     : 1;
    uint32_t RESERVED17                     : 7;  /**< \brief ����*/
    __IO uint32_t RESV                      : 1;
    uint32_t RESERVED25                     : 7;  /**< \brief ����*/
} stc_tmr6_cr_sstar_field_t;

/**
 * \brief TMR6 - ���ͬ��ֹͣ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SSTP1                     : 1;  /**< \brief ��Ԫ1���ֹͣ*/
    __IO uint32_t SSTP2                     : 1;  /**< \brief ��Ԫ2���ֹͣ*/
    __IO uint32_t SSTP3                     : 1;  /**< \brief ��Ԫ3���ֹͣ*/
    uint32_t RESERVED3                      :29;  /**< \brief ����*/
} stc_tmr6_cr_sstpr_field_t;

/**
 * \brief TMR6 - ���ͬ��������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SCLE1                     : 1;  /**< \brief ��Ԫ1�������*/
    __IO uint32_t SCLE2                     : 1;  /**< \brief ��Ԫ2�������*/
    __IO uint32_t SCLE3                     : 1;  /**< \brief ��Ԫ3�������*/
    uint32_t RESERVED3                      :29;  /**< \brief ����*/
} stc_tmr6_cr_sclrr_field_t;

/**
 * \brief ��ʱ���Ĵ�����ṹ��
 */
typedef struct {
    union
    {
        __IO uint32_t CNTER;           /**< \brief ͨ�ü���ֵ�Ĵ��� */
        stc_tmr6_cnter_field_t CNTER_f;
    };
    union
    {
        __IO uint32_t PERAR;           /**< \brief ͨ�����ڻ�׼ֵ�Ĵ���A */
        stc_tmr6_perar_field_t PERAR_f;
    };
    union
    {
        __IO uint32_t PERBR;          /**< \brief ͨ�����ڻ�׼ֵ�Ĵ���B */
        stc_tmr6_perbr_field_t PERBR_f;
    };
    union
    {
        __IO uint32_t PERCR;          /**< \brief ͨ�����ڻ�׼ֵ�Ĵ���C */
        stc_tmr6_percr_field_t PERCR_f;
    };
    union
    {
        __IO uint32_t GCMAR;          /**< \brief ͨ�ñȽϻ�׼ֵ�Ĵ���A */
        stc_tmr6_gcmar_field_t GCMAR_f;
    };
    union
    {
        __IO uint32_t GCMBR;          /**< \brief ͨ�ñȽϻ�׼ֵ�Ĵ���B */
        stc_tmr6_gcmbr_field_t GCMBR_f;
    };
    union
    {
        __IO uint32_t GCMCR;          /**< \brief ͨ�ñȽϻ�׼ֵ�Ĵ���C */
        stc_tmr6_gcmcr_field_t GCMCR_f;
    };
    union
    {
        __IO uint32_t GCMDR;          /**< \brief ͨ�ñȽϻ�׼ֵ�Ĵ���D */
        stc_tmr6_gcmdr_field_t GCMDR_f;
    };
    union
    {
        __IO uint32_t GCMER;          /**< \brief ͨ�ñȽϻ�׼ֵ�Ĵ���E */
        stc_tmr6_gcmer_field_t GCMER_f;
    };
    union
    {
        __IO uint32_t GCMFR;          /**< \brief ͨ�ñȽϻ�׼ֵ�Ĵ���F */
        stc_tmr6_gcmfr_field_t GCMFR_f;
    };
    union
    {
        __IO uint32_t SCMAR;          /**< \brief ר�ñȽϻ�׼ֵ�Ĵ���A */
        stc_tmr6_scmar_field_t SCMAR_f;
    };
    union
    {
        __IO uint32_t SCMBR;          /**< \brief ר�ñȽϻ�׼ֵ�Ĵ���B */
        stc_tmr6_scmbr_field_t SCMBR_f;
    };
    union
    {
        __IO uint32_t SCMCR;          /**< \brief ר�ñȽϻ�׼ֵ�Ĵ���C */
        stc_tmr6_scmcr_field_t SCMCR_f;
    };
    union
    {
        __IO uint32_t SCMDR;          /**< \brief ר�ñȽϻ�׼ֵ�Ĵ���D */
        stc_tmr6_scmdr_field_t SCMDR_f;
    };
    union
    {
        __IO uint32_t SCMER;          /**< \brief ר�ñȽϻ�׼ֵ�Ĵ���E */
        stc_tmr6_scmer_field_t SCMER_f;
    };
    union
    {
        __IO uint32_t SCMFR;          /**< \brief ר�ñȽϻ�׼ֵ�Ĵ���F */
        stc_tmr6_scmfr_field_t SCMFR_f;
    };
    union
    {
        __IO uint32_t DTUAR;          /**< \brief ����ʱ���׼ֵ�Ĵ���UA */
        stc_tmr6_dtuar_field_t DTUAR_f;
    };
    union
    {
        __IO uint32_t DTDAR;          /**< \brief ����ʱ���׼ֵ�Ĵ���DA */
        stc_tmr6_dtdar_field_t DTDAR_f;
    };
    union
    {
        __IO uint32_t DTUBR;          /**< \brief ����ʱ���׼ֵ�Ĵ���UB */
        stc_tmr6_dtubr_field_t DTUBR_f;
    };
    union
    {
        __IO uint32_t DTDBR;          /**< \brief ����ʱ���׼ֵ�Ĵ���DB */
        stc_tmr6_dtdbr_field_t DTDBR_f;
    };
    union
    {
        __IO uint32_t GCONR;          /**< \brief ͨ�ÿ��ƼĴ��� */
        stc_tmr6_gconr_field_t GCONR_f;
    };
    union
    {
        __IO uint32_t ICONR;          /**< \brief �жϿ��ƼĴ��� */
        stc_tmr6_iconr_field_t ICONR_f;
    };
    union
    {
        __IO uint32_t PCONR;          /**< \brief �˿ڿ��ƼĴ��� */
        stc_tmr6_pconr_field_t PCONR_f;
    };
    union
    {
        __IO uint32_t BCONR;          /**< \brief ������ƼĴ��� */
        stc_tmr6_bconr_field_t BCONR_f;
    };
    union
    {
        __IO uint32_t DCONR;          /**< \brief �������ƼĴ��� */
        stc_tmr6_dconr_field_t DCONR_f;
    };
    uint8_t RESERVED25[4];            /**< \brief ���� */
    union
    {
        __IO uint32_t FCONR;          /**< \brief �˲����ƼĴ��� */
        stc_tmr6_fconr_field_t FCONR_f;
    };
    union
    {
        __IO uint32_t VPERR;          /**< \brief ��Ч���ڼĴ��� */
        stc_tmr6_vperr_field_t VPERR_f;
    };
    union
    {
        __IO uint32_t STFLR;          /**< \brief ״̬��־�Ĵ��� */
        stc_tmr6_stflr_field_t STFLR_f;
    };
    union
    {
        __IO uint32_t HSTAR;          /**< \brief Ӳ�������¼�ѡ��Ĵ��� */
        stc_tmr6_hstar_field_t HSTAR_f;
    };
    union
    {
        __IO uint32_t HSTPR;          /**< \brief Ӳ��ֹͣ�¼�ѡ��Ĵ��� */
        stc_tmr6_hstpr_field_t HSTPR_f;
    };
    union
    {
        __IO uint32_t HCLRR;          /**< \brief Ӳ�������¼�ѡ��Ĵ��� */
        stc_tmr6_hclrr_field_t HCLRR_f;
    };
    union
    {
        __IO uint32_t HCPAR;          /**< \brief Ӳ�������¼�ѡ��Ĵ���A */
        stc_tmr6_hcpar_field_t HCPAR_f;
    };
    union
    {
        __IO uint32_t HCPBR;          /**< \brief Ӳ�������¼�ѡ��Ĵ���B */
        stc_tmr6_hcpbr_field_t HCPBR_f;
    };
    union
    {
        __IO uint32_t HCUPR;          /**< \brief Ӳ���ݼ��¼�ѡ��Ĵ��� */
        stc_tmr6_hcupr_field_t HCUPR_f;
    };
    union
    {
        __IO uint32_t HCDOR;          /**< \brief Ӳ���ݼ��¼�ѡ��Ĵ��� */
        stc_tmr6_hcdor_field_t HCDOR_f;
    };
} amhw_hc32f460_adtim_t;

/**
 * \brief ADT CHxͨ������
 */
typedef enum {
    AMHW_HC32F460_ADTIM_CHX_A = 0u,            /** <brief CHx Aͨ�� */
    AMHW_HC32F460_ADTIM_CHX_B = 1u,            /** <brief CHx Bͨ�� */
}amhw_hc32f460_adtim_chx_t;

/**
 * \brief ADT TRIG�˿ڶ���
 */
typedef enum {
    AMHW_HC32F460_ADTIM_TRIG_PORT_A = 0u,   /** <brief TIMx ����A�˿� */
    AMHW_HC32F460_ADTIM_TRIG_PORT_B = 1u,   /** <brief TIMx ����B�˿� */
    AMHW_HC32F460_ADTIM_TRIG_PORT_C = 2u,   /** <brief TIMx ����C�˿� */
    AMHW_HC32F460_ADTIM_TRIG_PORT_D = 3u,   /** <brief TIMx ����D�˿� */
}amhw_hc32f460_adtim_trig_port_t;

/**
 * \brief ADTͨ�ÿ��� - Z����������������
 */
typedef enum {
    AMHW_HC32F460_ADTIM_ZMASK_NO = 0u,  /** <brief Z���������ι�����Ч */
    AMHW_HC32F460_ADTIM_ZMASK_4  = 1u,  /** <brief λ�ü���������������4�����������ڵ�Z�����뱻���� */
    AMHW_HC32F460_ADTIM_ZMASK_8  = 2u,  /** <brief λ�ü���������������8�����������ڵ�Z�����뱻���� */
    AMHW_HC32F460_ADTIM_ZMASK_16 = 3u,  /** <brief λ�ü���������������16�����������ڵ�Z�����뱻���� */
}amhw_hc32f460_adtim_zmask_t;

/**
 * \brief ADTͨ�ÿ��� - ����ʱ��ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_PCLK_DIV1    = 0ul,  /** <brief PCLK0 */
    AMHW_HC32F460_ADTIM_PCLK_DIV2    = 1ul,  /** <brief PCLK0/2 */
    AMHW_HC32F460_ADTIM_PCLK_DIV4    = 2ul,  /** <brief PCLK0/4 */
    AMHW_HC32F460_ADTIM_PCLK_DIV8    = 3ul,  /** <brief PCLK0/8 */
    AMHW_HC32F460_ADTIM_PCLK_DIV16   = 4ul,  /** <brief PCLK0/16 */
    AMHW_HC32F460_ADTIM_PCLK_DIV64   = 5ul,  /** <brief PCLK0/64 */
    AMHW_HC32F460_ADTIM_PCLK_DIV256  = 6ul,  /** <brief PCLK0/256 */
    AMHW_HC32F460_ADTIM_PCLK_DIV1024 = 7ul,  /** <brief PCLK0/1024 */
}amhw_hc32f460_adtim_pclk_div_t;

/**
 * \brief ADT����ģʽ
 */
typedef enum {
    AMHW_HC32F460_ADTIM_CNT_MODE_SAWTOOTH   = 0u,  /** <brief ��ݲ�ģʽ */
    AMHW_HC32F460_ADTIM_CNT_MODE_TRIANGLE_A = 4u,  /** <brief ���ǲ�Aģʽ */
    AMHW_HC32F460_ADTIM_CNT_MODE_TRIANGLE_B = 5u,  /** <brief ���ǲ�Bģʽ */
}amhw_hc32f460_adtim_cnt_mode_t;

/**
 * \brief ADT��������
 */
typedef enum {
    AMHW_HC32F460_ADTIM_CNT_DIR_DOWN = 0u,        /** <brief �ݼ����� */
    AMHW_HC32F460_ADTIM_CNT_DIR_UP   = 1u,        /** <brief �ݼӼ��� */
}amhw_hc32f460_adtim_cnt_dir_t;

/**
 * \brief ADTͨ�ñȽϻ�׼
 */
typedef enum {
    AMHW_HC32F460_ADTIM_COMPARE_A = 0u,           /** <brief ͨ�ñȽϻ�׼A */
    AMHW_HC32F460_ADTIM_COMPARE_B = 1u,           /** <brief ͨ�ñȽϻ�׼B */
    AMHW_HC32F460_ADTIM_COMPARE_C = 2u,           /** <brief ͨ�ñȽϻ�׼C */
    AMHW_HC32F460_ADTIM_COMPARE_D = 3u,           /** <brief ͨ�ñȽϻ�׼D */
    AMHW_HC32F460_ADTIM_COMPARE_E = 4u,           /** <brief ͨ�ñȽϻ�׼E */
    AMHW_HC32F460_ADTIM_COMPARE_F = 5u,           /** <brief ͨ�ñȽϻ�׼F */
}amhw_hc32f460_adtim_compare_x_t;

/**
 * \brief ADTר�ñȽϻ�׼
 */
typedef enum {
    AMHW_HC32F460_ADTIM_SPCL_COMP_A = 0u,         /** <brief ר�ñȽϻ�׼A */
    AMHW_HC32F460_ADTIM_SPCL_COMP_B = 1u,         /** <brief ר�ñȽϻ�׼B */
}amhw_hc32f460_adtim_special_compare_x_t;

/**
 * \brief ADT�˿ڿ��� - TIMx���״̬����
 */
typedef enum {
    AMHW_HC32F460_ADTIM_DISVAL_NORM = 0u,  /** <brief ǿ�������Ч����0~3����������ʱ��CHx�˿�������� */
    AMHW_HC32F460_ADTIM_DISVAL_HIZ  = 1u,  /** <brief ǿ�������Ч����0~3����������ʱ��CHx�˿��������̬ */
    AMHW_HC32F460_ADTIM_DISVAL_LOW  = 2u,  /** <brief ǿ�������Ч����0~3����������ʱ��CHx�˿�����͵�ƽ */
    AMHW_HC32F460_ADTIM_DISVAL_HIGH = 3u,  /** <brief ǿ�������Ч����0~3����������ʱ��CHx�˿�����ߵ�ƽ */
}amhw_hc32f460_adtim_disval_t;

/**
 * \brief ADT�˿ڿ��� - CHxǿ�������Ч����ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_DISSEL0 = 0u,      /** <brief ѡ��ǿ�������Ч����0 */
    AMHW_HC32F460_ADTIM_DISSEL1 = 1u,      /** <brief ѡ��ǿ�������Ч����1 */
    AMHW_HC32F460_ADTIM_DISSEL2 = 2u,      /** <brief ѡ��ǿ�������Ч����2 */
    AMHW_HC32F460_ADTIM_DISSEL3 = 3u,      /** <brief ѡ��ǿ�������Ч����3 */
}amhw_hc32f460_adtim_dissel_t;

/**
 * \brief ADT�˿ڿ��� - CHx����ֵƥ��ʱ�˿�״̬�趨
 */
typedef enum {
    AMHW_HC32F460_ADTIM_PERIOD_LOW  = 0u,  /** <brief ����������ֵ������ֵ���ʱ��CHx�˿��������Ϊ�͵�ƽ */
    AMHW_HC32F460_ADTIM_PERIOD_HIGH = 1u,  /** <brief ����������ֵ������ֵ���ʱ��CHx�˿�����趨Ϊ�ߵ�ƽ */
    AMHW_HC32F460_ADTIM_PERIOD_KEEP = 2u,  /** <brief ����������ֵ������ֵ���ʱ��CHx�˿�����趨Ϊ��ǰ״̬ */
    AMHW_HC32F460_ADTIM_PERIOD_INV  = 3u,  /** <brief ����������ֵ������ֵ���ʱ��CHx�˿�����趨Ϊ��ת��ƽ */
}amhw_hc32f460_adtim_perc_t;

/**
 * \brief ADT�˿ڿ��� - CHx�Ƚ�ֵƥ��ʱ�˿�״̬�趨
 */
typedef enum {
    AMHW_HC32F460_ADTIM_COMPARE_LOW  = 0u, /** <brief ������������GCMxR���ʱ��CHx�˿��������Ϊ�͵�ƽ */
    AMHW_HC32F460_ADTIM_COMPARE_HIGH = 1u, /** <brief ������������GCMxR���ʱ��CHx�˿�����趨Ϊ�ߵ�ƽ */
    AMHW_HC32F460_ADTIM_COMPARE_KEEP = 2u, /** <brief ������������GCMxR���ʱ��CHx�˿�����趨Ϊ��ǰ״̬ */
    AMHW_HC32F460_ADTIM_COMPARE_INV  = 3u, /** <brief ������������GCMxR���ʱ��CHx�˿�����趨Ϊ��ת��ƽ */
}amhw_hc32f460_adtim_cmpc_t;

/**
  * \brief ADT�˿ڿ��� - CHx�˿����
  */
typedef enum {
    AMHW_HC32F460_ADTIM_PORT_OUT_LOW  = 0u, /** <brief CHx�˿�����趨Ϊ�͵�ƽ */
    AMHW_HC32F460_ADTIM_PORT_OUT_HIGH = 1u, /** <brief CHx�˿�����趨Ϊ�ߵ�ƽ */
}amhw_hc32f460_adtim_port_out_t;

/**
 * \brief ADT�˿ڿ��� - CHx�˿ڹ���ģʽѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_PORT_MODE_CMP_OUTPUT = 0u, /** <brief CHx�˿��趨Ϊ�Ƚ�������� */
    AMHW_HC32F460_ADTIM_PORT_MODE_CAP_INPUT  = 1u, /** <brief CHx�˿��趨Ϊ�������빦�� */
}amhw_hc32f460_adtim_port_mode_t;

/**
 * \brief ADT�˿ڿ��� - CHx������ʼֹͣ�˿�״̬ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_STATE_SEL_SS   = 0u, /** <brief ������ʼ��ֹͣʱ��CHx�˿������STACB��STPCB���� */
    AMHW_HC32F460_ADTIM_STATE_SEL_KEEP = 1u, /** <brief ������ʼ��ֹͣʱ��CHx�˿�����趨Ϊ��ǰ״̬ */
}amhw_hc32f460_adtim_stastps_t;

/**
 * \brief ADT�������� - CHx���������趨
 */
typedef enum {
    AMHW_HC32F460_ADTIM_DtSeperate = 0u,      /** <brief DTUAR��DTDAR�ֱ��趨 */
    AMHW_HC32F460_ADTIM_DtEqual    = 1u,      /** <brief DTDAR��ֵ��DTUAR��ֵ�Զ���� */
}amhw_hc32f460_adtim_sepa_t;

/**
 * \brief ADT�˲����� - TRIx/TIMxIx�˿��˲�������׼ʱ��ѡ��
 */
typedef enum
{
    AMHW_HC32F460_ADTIM_FLTCLK_PCLK_DIV1  = 0u, /** <brief PCLK0 */
    AMHW_HC32F460_ADTIM_FLTCLK_PCLK_DIV4  = 1u, /** <brief PCLK0/4 */
    AMHW_HC32F460_ADTIM_FLTCLK_PCLK_DIV16 = 2u, /** <brief PCLK0/16 */
    AMHW_HC32F460_ADTIM_FLTCLK_PCLK_DIV64 = 3u, /** <brief PCLK0/64 */
}amhw_hc32f460_adtim_fltclk_pclkdiv_t;

/**
 * \brief ADT��Ч���� - TIMx��Ч����ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_PeriodCnts0 = 0u,       /** <brief ��Ч����ѡ������Ч */
    AMHW_HC32F460_ADTIM_PeriodCnts1 = 1u,       /** <brief ÿ��1��������Чһ�� */
    AMHW_HC32F460_ADTIM_PeriodCnts2 = 2u,       /** <brief ÿ��2��������Чһ�� */
    AMHW_HC32F460_ADTIM_PeriodCnts3 = 3u,       /** <brief ÿ��3��������Чһ�� */
    AMHW_HC32F460_ADTIM_PeriodCnts4 = 4u,       /** <brief ÿ��4��������Чһ�� */
    AMHW_HC32F460_ADTIM_PeriodCnts5 = 5u,       /** <brief ÿ��5��������Чһ�� */
    AMHW_HC32F460_ADTIM_PeriodCnts6 = 6u,       /** <brief ÿ��6��������Чһ�� */
    AMHW_HC32F460_ADTIM_PeriodCnts7 = 7u,       /** <brief ÿ��7��������Чһ�� */
}amhw_hc32f460_adtim_pcnts_t;

/**
 * \brief ADT��Ч���� - ��������ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_PeriodCnteDisable = 0u,  /** <brief ��Ч����ѡ������Ч */
    AMHW_HC32F460_ADTIM_PeriodCnteMin     = 1u,  /** <brief ��ݲ������ϡ����������ǲ�������Ϊ�������� */
    AMHW_HC32F460_ADTIM_PeriodCnteMax     = 2u,  /** <brief ��ݲ������ϡ����������ǲ�������Ϊ�������� */
    AMHW_HC32F460_ADTIM_PeriodCnteBoth    = 3u,  /** <brief ��ݲ������ϡ����������ǲ����壬������Ϊ�������� */
}amhw_hc32f460_adtim_pcnte_t;

/**
 * \brief ADT�˿ڴ������� - ����Դѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_TRIG_PA3  = 0u,    /** <brief PA3 */
    AMHW_HC32F460_ADTIM_TRIG_PB3  = 1u,    /** <brief PB3 */
    AMHW_HC32F460_ADTIM_TRIG_PC3  = 2u,    /** <brief PC3 */
    AMHW_HC32F460_ADTIM_TRIG_PD3  = 3u,    /** <brief PD3 */
    AMHW_HC32F460_ADTIM_TRIG_PA7  = 4u,    /** <brief PA7 */
    AMHW_HC32F460_ADTIM_TRIG_PB7  = 5u,    /** <brief PB7 */
    AMHW_HC32F460_ADTIM_TRIG_PC7  = 6u,    /** <brief PC7 */
    AMHW_HC32F460_ADTIM_TRIG_PD7  = 7u,    /** <brief PD7 */
    AMHW_HC32F460_ADTIM_TRIG_PA11 = 8u,    /** <brief PA11 */
    AMHW_HC32F460_ADTIM_TRIG_PB11 = 9u,    /** <brief PB11 */
    AMHW_HC32F460_ADTIM_TRIG_PC11 = 10u,   /** <brief PC11 */
    AMHW_HC32F460_ADTIM_TRIG_PD1  = 11u,   /** <brief PD1 */
    AMHW_HC32F460_ADTIM_TRIG_PA15 = 12u,   /** <brief PA15 */
    AMHW_HC32F460_ADTIM_TRIG_PB15 = 13u,   /** <brief PB15 */
    AMHW_HC32F460_ADTIM_TRIG_PC5  = 14u,   /** <brief PC5 */
    AMHW_HC32F460_ADTIM_TRIG_PD5  = 15u,   /** <brief PD5 */
}amhw_hc32f460_adtim_trigsel_t;

/**
 * \brief ADT AOS�������� - AOSx����Դѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_AosxTrigSelTim0Int   = 0u,    /** <brief TIM0_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelTim1Int   = 1u,    /** <brief TIM1_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelTim2Int   = 2u,    /** <brief TIM2_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelLpTimInt  = 3u,    /** <brief LPTIMER_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelTim4Int   = 4u,    /** <brief TIM4_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelTim5Int   = 5u,    /** <brief TIM5_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelTim6Int   = 6u,    /** <brief TIM6_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelUart0Int  = 7u,    /** <brief UART0_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelUart1Int  = 8u,    /** <brief UART1_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelLpUartInt = 9u,    /** <brief LPUART_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelVc0Int    = 10u,   /** <brief VC0_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelVc1Int    = 11u,   /** <brief VC1_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelRtcInt    = 12u,   /** <brief RTC_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelPcaInt    = 13u,   /** <brief PCA_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelSpiInt    = 14u,   /** <brief SPI_INT */
    AMHW_HC32F460_ADTIM_AosxTrigSelAdcInt    = 15u,   /** <brief ADC_INT */
}amhw_hc32f460_adtim_iaosxs_t;

/**
 * \brief ADTӲ��(����/ֹͣ/����/����)�¼�����ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_HwTrigAos0        = 0u,       /** <brief ��AOS�����¼�����0��Ч */
    AMHW_HC32F460_ADTIM_HwTrigAos1        = 1u,       /** <brief ��AOS�����¼�����1��Ч */
    AMHW_HC32F460_ADTIM_HwTrigAos2        = 2u,       /** <brief ��AOS�����¼�����2��Ч */
    AMHW_HC32F460_ADTIM_HwTrigAos3        = 3u,       /** <brief ��AOS�����¼�����3��Ч */
    AMHW_HC32F460_ADTIM_HwTrigCHxARise    = 4u,       /** <brief CHxA�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwTrigCHxAFall    = 5u,       /** <brief CHxA�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwTrigCHxBRise    = 6u,       /** <brief CHxB�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwTrigCHxBFall    = 7u,       /** <brief CHxB�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriARise = 8u,       /** <brief TIMTRIA�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriAFall = 9u,       /** <brief TIMTRIA�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriBRise = 10u,      /** <brief TIMTRIB�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriBFall = 11u,      /** <brief TIMTRIB�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriCRise = 12u,      /** <brief TIMTRIC�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriCFall = 13u,      /** <brief TIMTRIC�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriDRise = 14u,      /** <brief TIMTRID�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwTrigTimTriDFall = 15u,      /** <brief TIMTRID�˿��ϲ������½��� */
}amhw_hc32f460_adtim_hw_trig_t;

/**
 * \brief ADTӲ��(�ݼ�/�ݼ�)�¼�����ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_HwCntCHxALowCHxBRise   = 0u,  /** <brief CHxA�˿�Ϊ�͵�ƽʱ��CHxB�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntCHxALowCHxBFall   = 1u,  /** <brief CHxA�˿�Ϊ�͵�ƽʱ��CHxB�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntCHxAHighCHxBRise  = 2u,  /** <brief CHxA�˿�Ϊ�ߵ�ƽʱ��CHxB�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntCHxAHighCHxBFall  = 3u,  /** <brief CHxA�˿�Ϊ�ߵ�ƽʱ��CHxB�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntCHxBLowCHxARise   = 4u,  /** <brief CHxB�˿�Ϊ�͵�ƽʱ��CHxA�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntCHxBLowCHxAFall   = 5u,  /** <brief CHxB�˿�Ϊ�͵�ƽʱ��CHxA�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntCHxBHighChxARise  = 6u,  /** <brief CHxB�˿�Ϊ�ߵ�ƽʱ��CHxA�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntCHxBHighCHxAFall  = 7u,  /** <brief CHxB�˿�Ϊ�ߵ�ƽʱ��CHxA�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntTimTriARise       = 8u,  /** <brief TIMTRIA�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntTimTriAFall       = 9u,  /** <brief TIMTRIA�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntTimTriBRise       = 10u, /** <brief TIMTRIB�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntTimTriBFall       = 11u, /** <brief TIMTRIB�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntTimTriCRise       = 12u, /** <brief TIMTRIC�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntTimTriCFall       = 13u, /** <brief TIMTRIC�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntTimTriDRise       = 14u, /** <brief TIMTRID�˿��ϲ����������� */
    AMHW_HC32F460_ADTIM_HwCntTimTriDFall       = 15u, /** <brief TIMTRID�˿��ϲ������½��� */
    AMHW_HC32F460_ADTIM_HwCntAos0              = 16u, /** <brief ��AOS�����¼�����0��Ч */
    AMHW_HC32F460_ADTIM_HwCntAos1              = 17u, /** <brief ��AOS�����¼�����1��Ч */
    AMHW_HC32F460_ADTIM_HwCntAos2              = 18u, /** <brief ��AOS�����¼�����2��Ч */
    AMHW_HC32F460_ADTIM_HwCntAos3              = 19u, /** <brief ��AOS�����¼�����3��Ч */
}amhw_hc32f460_adtim_hw_cnt_t;

/**
 * \brief ADT�˿�ɲ�����Կ���
 */
typedef enum {
    AMHW_HC32F460_ADTIM_PtBrkHigh = 0u,              /** <brief �˿�ɲ�����Ըߵ�ƽ��Ч */
    AMHW_HC32F460_ADTIM_PtBrkLow  = 1u,              /** <brief �˿�ɲ�����Ե͵�ƽ��Ч */
}amhw_hc32f460_adtim_ptbrk_polarity_t;

/**
 * \brief ADT PWMչƵ����ѡ��
 */
typedef enum {
    AMHW_HC32F460_ADTIM_PwmDitherUnderFlow = 0u,     /** <brief PWMչƵ��������� */
    AMHW_HC32F460_ADTIM_PwmDitherOverFlow  = 1u,     /** <brief PWMչƵ��������� */
}amhw_hc32f460_adtim_pwm_dither_type_t;

/**
 * \brief ADT�ж�����
 */
typedef enum {
    AMHW_HC32F460_ADTIM_CMAIrq  = 0u,                /** <brief ����ƥ��A���򲶻����룩�ж� */
    AMHW_HC32F460_ADTIM_CMBIrq  = 1u,                /** <brief ����ƥ��B���򲶻����룩�ж� */
    AMHW_HC32F460_ADTIM_CMCIrq  = 2u,                /** <brief ����ƥ��C�ж� */
    AMHW_HC32F460_ADTIM_CMDIrq  = 3u,                /** <brief ����ƥ��D�ж� */
    AMHW_HC32F460_ADTIM_CMEIrq  = 4u,                /** <brief ����ƥ��E�ж� */
    AMHW_HC32F460_ADTIM_CMFIrq  = 5u,                /** <brief ����ƥ��F�ж� */
    AMHW_HC32F460_ADTIM_OVFIrq  = 6u,                /** <brief ����ƥ���ж� */
    AMHW_HC32F460_ADTIM_UDFIrq  = 7u,                /** <brief ����ƥ���ж� */
    AMHW_HC32F460_ADTIM_DTEIrq  = 8u,                /** <brief ����ʱ������ж� */
    AMHW_HC32F460_ADTIM_INTENSAUIrq = 16u,               
    AMHW_HC32F460_ADTIM_INTENSADIrq = 17u,              
    AMHW_HC32F460_ADTIM_INTENSBUIrq = 18u,               
    AMHW_HC32F460_ADTIM_INTENSBDIrq = 19u,               
}amhw_hc32f460_adtim_irq_type_t;

/**
 * \brief ADT��־����
 */
typedef enum {
    AMHW_HC32F460_ADTIM_CMAF_FLAG = 0,                    /** <brief ����ƥ��A��־ */
    AMHW_HC32F460_ADTIM_CMBF_FLAG = 1,                    /** <brief ����ƥ��B��־ */
    AMHW_HC32F460_ADTIM_CMCF_FLAG = 2,                    /** <brief ����ƥ��C��־ */
    AMHW_HC32F460_ADTIM_CMDF_FLAG = 3,                    /** <brief ����ƥ��D��־ */
    AMHW_HC32F460_ADTIM_OVFF_FLAG = 6,                    /** <brief ����ƥ���־ */
    AMHW_HC32F460_ADTIM_UDFF_FLAG = 7,                    /** <brief ����ƥ���־ */
    AMHW_HC32F460_ADTIM_DTEF_FLAG = 8,                    /** <brief ����ʱ������־ */
    AMHW_HC32F460_ADTIM_CMSAUF_FLAG = 9,                  /** <brief ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־ */
    AMHW_HC32F460_ADTIM_CMSADF_FLAG = 10,                 /** <brief ���¼���ר�ñȽϻ�׼ֵƥ��B��־ */
    AMHW_HC32F460_ADTIM_CMSBUF_FLAG = 11,                 /** <brief ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־ */
    AMHW_HC32F460_ADTIM_CMSBDF_FLAG = 12,                 /** <brief ���¼���ר�ñȽϻ�׼ֵƥ��B��־ */
}amhw_hc32f460_adtim_state_type_t;

/**
 * \brief ADT���ͬ������
 */
typedef struct {
    am_bool_t adtim4;                              /** <brief Timer 4 */
    am_bool_t adtim5;                              /** <brief Timer 5 */
    am_bool_t adtim6;                              /** <brief Timer 6 */
}amhw_hc32f460_adtim_sw_sync_t;

/**
 * \brief ADT AOS��������
 */
typedef struct {
    amhw_hc32f460_adtim_iaosxs_t   aos0trig_src;     /** <brief AOS0����Դѡ�� */
    amhw_hc32f460_adtim_iaosxs_t   aos1trig_src;     /** <brief AOS1����Դѡ�� */
    amhw_hc32f460_adtim_iaosxs_t   aos2trig_src;     /** <brief AOS2����Դѡ�� */
    amhw_hc32f460_adtim_iaosxs_t   aos3trig_src;     /** <brief AOS3����Դѡ�� */
}amhw_hc32f460_adtim_aos_trig_cfg_t;

/**
 * \brief ADT �жϴ�������
 */
typedef struct {
    am_bool_t   specilmatch_B_trigdma;  /** <brief ר�ñȽϻ�׼ֵƥ��Bʹ�ܴ���DMA */
    am_bool_t   specilmatch_A_trigdma;  /** <brief ר�ñȽϻ�׼ֵƥ��Aʹ�ܴ���DMA */
    am_bool_t   underflow_trigdma;      /** <brief ����ƥ��ʹ�ܴ���DMA */
    am_bool_t   overflow_trigdma;       /** <brief ����ƥ��ʹ�ܴ���DMA */
    am_bool_t   cntmatch_D_trigdma;     /** <brief ����ƥ��Dʹ�ܴ���DMA */
    am_bool_t   cntmatch_C_trigdma;     /** <brief ����ƥ��Cʹ�ܴ���DMA */
    am_bool_t   cntmatch_B_trigdma;     /** <brief ����ƥ��Bʹ�ܴ���DMA */
    am_bool_t   cntmatch_A_trigdma;     /** <brief ����ƥ��Aʹ�ܴ���DMA */
    am_bool_t   specilmatch_B_trig;     /** <brief ר�ñȽϻ�׼ֵƥ��Bʹ�ܴ���ADC */
    am_bool_t   specilmatch_A_trig;     /** <brief ר�ñȽϻ�׼ֵƥ��Aʹ�ܴ���ADC */
    am_bool_t   underflow_trig;         /** <brief ����ƥ��ʹ�ܴ���ADC */
    am_bool_t   overflow_trig;          /** <brief ����ƥ��ʹ�ܴ���ADC */
    am_bool_t   cntmatch_D_trig;        /** <brief ����ƥ��Dʹ�ܴ���ADC */
    am_bool_t   cntmatch_C_trig;        /** <brief ����ƥ��Cʹ�ܴ���ADC */
    am_bool_t   cntmatch_B_trig;        /** <brief ����ƥ��Bʹ�ܴ���ADC */
    am_bool_t   cntmatch_A_trig;        /** <brief ����ƥ��Aʹ�ܴ���ADC */
}amhw_hc32f460_adtim_irq_trig_cfg_t;

/**
 * \brief ADT Trig�˿�����
 */
typedef struct {
    amhw_hc32f460_adtim_trigsel_t        trigsrc;    /** <brief ����Դѡ�� */
    am_bool_t                          flt_enable;   /** <brief ����Դ���������˲�ʹ�� */
    amhw_hc32f460_adtim_fltclk_pclkdiv_t fltclk;     /** <brief �˲�������׼ʱ�� */
}amhw_hc32f460_adtim_port_trig_cfg_t;

/**
 * \brief ADT Z���������ι�������
 */
typedef struct {
    amhw_hc32f460_adtim_zmask_t zmask_cycle; /** <brief Z���������μ�������ѡ�� */
    am_bool_t                 fltposcntmask; /** <brief Z������ʱ�����������ڣ�λ�ü����������㹦�ܲ����Σ�FALSE��������(TRUE) */
    am_bool_t                 fltrevcntmask; /** <brief Z������ʱ�����������ڣ���ת�������ļ������ܲ����Σ�FALSE��������(TRUE) */
}amhw_hc32f460_adtim_zmask_cfg_t;

/**
 * \brief ADT TIMxX�˿�����
 */
typedef struct {
    amhw_hc32f460_adtim_port_mode_t portmode;    /** <brief �˿ڹ���ģʽ */
    am_bool_t                     outenable;     /** <brief ���ʹ�� */
    amhw_hc32f460_adtim_perc_t      perc;        /** <brief ����ֵƥ��ʱ�˿�״̬ */
    amhw_hc32f460_adtim_cmpc_t      cmpc;        /** <brief �Ƚ�ֵƥ��ʱ�˿�״̬ */
    amhw_hc32f460_adtim_stastps_t   stastps;     /** <brief ������ʼֹͣ�˿�״̬ѡ�� */
    amhw_hc32f460_adtim_port_out_t  staout;      /** <brief ������ʼ�˿����״̬ */
    amhw_hc32f460_adtim_port_out_t  stpout;      /** <brief ����ֹͣ�˿����״̬ */
    amhw_hc32f460_adtim_disval_t    disval;      /** <brief ǿ�������Чʱ���״̬���� */
    amhw_hc32f460_adtim_dissel_t    dissel;      /** <brief ǿ�������Ч����ѡ�� */
    am_bool_t                     fltenable;     /** <brief �˿ڲ��������˲�ʹ�� */
    amhw_hc32f460_adtim_fltclk_pclkdiv_t fltclk; /** <brief �˿��˲�������׼ʱ�� */
}amhw_hc32f460_adtim_timx_chx_port_cfg_t;

/**
 * \brief ADTɲ���˿�����
 */
typedef struct {
    am_bool_t                          portenable;    /** <brief �˿�ʹ�� */
    amhw_hc32f460_adtim_ptbrk_polarity_t polaritysel; /** <brief ����ѡ�� */
}amhw_hc32f460_adtim_break_port_cfg_t;

/**
 * \brief ADT��Ч����3����
 */
typedef struct amhw_hc32f460_adtim_disable_3_cfg
{
    amhw_hc32f460_adtim_break_port_cfg_t stcbrkptcfg[16]; /** <brief ɲ���˿����� */
    am_bool_t                          fltenable;         /** <brief ɲ���˿��˲�ʹ�� */
    amhw_hc32f460_adtim_fltclk_pclkdiv_t fltclk;          /** <brief �˲�������׼ʱ�� */
}amhw_hc32f460_adtim_disable_3_cfg_t;

/**
 * \brief ADT��Ч����1����
 */
typedef struct {
    am_bool_t   tim6_outsh;     /** <brief TIM6���ͬ�� */
    am_bool_t   tim5_outsh;     /** <brief TIM5���ͬ�� */
    am_bool_t   tim4_outsh;     /** <brief TIM4���ͬ�� */
    am_bool_t   tim6_outsl;     /** <brief TIM6���ͬ�� */
    am_bool_t   tim5_outsl;     /** <brief TIM5���ͬ�� */
    am_bool_t   tim4_outsl;     /** <brief TIM4���ͬ�� */
}amhw_hc32f460_adtim_disable_1_cfg_t;

/**
 * \brief ADT PWMչƵ��������
 */
typedef struct {
    amhw_hc32f460_adtim_pwm_dither_type_t enAMHW_HC32F460_ADTIM_PDType;/** <brief PWMչƵ����ѡ�� */
    am_bool_t   bTimxBPDEn;                      /** <brief PWMͨ��BչƵʹ�� */
    am_bool_t   bTimxAPDEn;                      /** <brief PWMͨ��AչƵʹ�� */
}amhw_hc32f460_adtim_pwm_dither_cfg_t;

/**
 * \brief ADT������������
 */
typedef struct {
    amhw_hc32f460_adtim_cnt_mode_t cntmode;        /** <brief ����ģʽ */
    amhw_hc32f460_adtim_cnt_dir_t  cntdir;         /** <brief �������� */
    amhw_hc32f460_adtim_pclk_div_t cntclkdiv;      /** <brief ����ʱ��ѡ�� */
}amhw_hc32f460_adtim_basecnt_cfg_t;

/**
 * \brief ADT����״̬
 */
typedef struct {
    uint16_t  u16counter;                  /** <brief ��ǰ�������ļ���ֵ */
    am_bool_t cntdir;                      /** <brief �������� */
    uint8_t   u8validperiod;               /** <brief ��Ч���ڼ��� */
    am_bool_t cmsbdf;                      /** <brief ���¼���ר�ñȽϻ�׼ֵƥ��B��־ */
    am_bool_t cmsbuf;                      /** <brief ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־ */
    am_bool_t cmsadf;                      /** <brief ���¼���ר�ñȽϻ�׼ֵƥ��B��־ */
    am_bool_t cmsauf;                      /** <brief ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־ */
    am_bool_t dtff;                        /** <brief ����ʱ������־ */
    am_bool_t udff;                        /** <brief ����ƥ���־ */
    am_bool_t ovff;                        /** <brief ����ƥ���־ */
    am_bool_t cmdf;                        /** <brief ����ƥ��D��־ */
    am_bool_t cmcf;                        /** <brief ����ƥ��C��־ */
    am_bool_t cmbf;                        /** <brief ����ƥ��B��־ */
    am_bool_t cmaf;                        /** <brief ����ƥ��A��־ */
}amhw_hc32f460_adtim_cntstate_cfg_t;

/**
 * \brief ADT��Ч��������
 */
typedef struct {
    amhw_hc32f460_adtim_pcnts_t  validcnt;     /** <brief ��Ч����ѡ�� */
    amhw_hc32f460_adtim_pcnte_t  validcdt;     /** <brief ��Ч���ڼ������� */
    am_bool_t                    period_D;     /** <brief ͨ���ź���Ч����ѡ��D */
    am_bool_t                    period_C;     /** <brief ͨ���ź���Ч����ѡ��C */
    am_bool_t                    period_B;     /** <brief ͨ���ź���Ч����ѡ��B */
    am_bool_t                    period_A;     /** <brief ͨ���ź���Ч����ѡ��A */
} amhw_hc32f460_adtim_validper_cfg_t;


/**
 * \brief ����Aͨ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_hc32f460_adtim_hw_trig_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_cfghwcaptureA(amhw_hc32f460_adtim_t        *p_hw_adtim,
                                          amhw_hc32f460_adtim_hw_trig_t choice) {

    if(choice > AMHW_HC32F460_ADTIM_HwTrigTimTriDFall) {
        return AM_FALSE;
    }

    p_hw_adtim->HCPAR |= (1ul << choice);
    p_hw_adtim->PCONR |= (1ul << 0 );

    return AM_TRUE;
}

/**
 * \brief ����Bͨ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_hc32f460_adtim_hw_trig_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_cfghwcaptureB(amhw_hc32f460_adtim_t        *p_hw_adtim,
                                          amhw_hc32f460_adtim_hw_trig_t choice) {

    if(choice > AMHW_HC32F460_ADTIM_HwTrigTimTriDFall) {
        return AM_FALSE;
    }

    p_hw_adtim->HCPBR |= (1ul << choice);
    p_hw_adtim->PCONR |= (1ul << 16 );

    return AM_TRUE;
}

/**
 * \brief CHxX�˿�����
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] port       : amhw_hc32f460_adtim_chx_tͨ��ö����
 * \param[in] p_cfg      : ָ��TIMxX�˿����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_bool_t amhw_hc32f460_adtim_timxchxportcfg(
              amhw_hc32f460_adtim_t                   *p_hw_adtim,
              amhw_hc32f460_adtim_chx_t                port,
              amhw_hc32f460_adtim_timx_chx_port_cfg_t *p_cfg);

/**
 * \brief ADTIM��ʼ��
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] p_cfg      : ָ��ADT�����������ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_init(amhw_hc32f460_adtim_t             *p_hw_adtim,
                                 amhw_hc32f460_adtim_basecnt_cfg_t *p_cfg) {
    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    if((p_cfg->cntmode) > AMHW_HC32F460_ADTIM_CNT_MODE_TRIANGLE_B) {
        return AM_FALSE;
    }

    p_hw_adtim->GCONR &= ~(7ul << 1);
    p_hw_adtim->GCONR &= ~(7ul << 4);
    p_hw_adtim->GCONR &= ~(1ul << 8);

    p_hw_adtim->GCONR |= (p_cfg->cntmode << 1);
    p_hw_adtim->GCONR |= (p_cfg->cntclkdiv << 4);
    p_hw_adtim->GCONR |= (p_cfg->cntdir << 8);

    return AM_TRUE;
}

am_static_inline
amhw_hc32f460_adtim_pclk_div_t
amhw_hc32f460_adtim_clkdiv_get(amhw_hc32f460_adtim_t *p_hw_adtim) {

    return (amhw_hc32f460_adtim_pclk_div_t)((p_hw_adtim->GCONR >> 4) & 7ul);
}


/**
 * \brief ADTIMȥ��ʼ��
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_bool_t amhw_hc32f460_adtim_deinit(amhw_hc32f460_adtim_t *p_hw_adtim);

/**
 * \brief ADTIM����
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_startcount(amhw_hc32f460_adtim_t *p_hw_adtim) {

    p_hw_adtim->GCONR |= (1ul << 0);

    return AM_TRUE;
}

/**
 * \brief ADTIMֹͣ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_stopcount(amhw_hc32f460_adtim_t *p_hw_adtim) {

    p_hw_adtim->GCONR &= ~(1ul << 0);

    return AM_TRUE;
}

/**
 * \brief ���ü���ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] cnt        �� ����ֵ�趨
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_setcount(amhw_hc32f460_adtim_t *p_hw_adtim,
                                     uint16_t             cnt) {

    p_hw_adtim->CNTER= cnt;

    return AM_TRUE;
}

/**
 * \brief ��ȡ����ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_adtim_getcount(amhw_hc32f460_adtim_t *p_hw_adtim) {
    return p_hw_adtim->CNTER;
}

/**
 * \brief �������ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_clearcount(amhw_hc32f460_adtim_t *p_hw_adtim) {

    p_hw_adtim->CNTER = 0;

    return AM_TRUE;
}

typedef enum adtim_period_x
{
    ADTIM_PERIODA = 0u,         
    ADTIM_PERIODB = 1u,         
    ADTIM_PERIODC = 2u,         
}adtim_period_x_t;

/**
 * \brief ���ü�������
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] data       : ���������趨ֵ
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_setperiod(amhw_hc32f460_adtim_t *p_hw_adtim,
                                        adtim_period_x_t       pri,
                                        uint16_t               data) {
    switch (pri)
    {
        case ADTIM_PERIODA:
            p_hw_adtim->PERAR = data;
            break;
        case ADTIM_PERIODB:
            p_hw_adtim->PERBR = data;
            break;
        case ADTIM_PERIODC:
            p_hw_adtim->PERCR = data;
            break;
        default:
            break;
    }
    return AM_TRUE;
}

/**
 * \brief ��ȡ��������
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return ��������
 */
am_static_inline
uint16_t amhw_hc32f460_adtim_getperiod(amhw_hc32f460_adtim_t *p_hw_adtim, adtim_period_x_t pri) {
    uint16_t value = 0;
    switch (pri)
    {
        case ADTIM_PERIODA:
            value = p_hw_adtim->PERAR;
            break;
        case ADTIM_PERIODB:
            value = p_hw_adtim->PERBR;
            break;
        case ADTIM_PERIODC:
            value = p_hw_adtim->PERCR;
            break;
        default:
            break;
    }

    return value;
}

/**
 * \brief ���ñȽ����������׼ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] compare    : amhw_hc32f460_adtim_compare_x_tö����
 * \param[in] data       : �趨ֵ
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_setcomparevalue(
              amhw_hc32f460_adtim_t          *p_hw_adtim,
              amhw_hc32f460_adtim_compare_x_t compare,
              uint16_t                      data) {

    switch(compare) {
    case AMHW_HC32F460_ADTIM_COMPARE_A:
        p_hw_adtim->GCMAR = data;
        break;
    case AMHW_HC32F460_ADTIM_COMPARE_B:
        p_hw_adtim->GCMBR = data;
        break;
    case AMHW_HC32F460_ADTIM_COMPARE_C:
        p_hw_adtim->GCMCR = data;
        break;
    case AMHW_HC32F460_ADTIM_COMPARE_D:
        p_hw_adtim->GCMDR = data;
        break;
    case AMHW_HC32F460_ADTIM_COMPARE_E:
        p_hw_adtim->GCMER = data;
        break;
    case AMHW_HC32F460_ADTIM_COMPARE_F:
        p_hw_adtim->GCMFR = data;
        break;        
    default:
        return AM_FALSE;
    }

    return AM_TRUE;
}

/**
 * \brief ��ȡ����ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] port       : amhw_hc32f460_adtim_chx_tö����
 *
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_adtim_getcapturevalue(amhw_hc32f460_adtim_t    *p_hw_adtim,
                                           amhw_hc32f460_adtim_chx_t port) {
    switch(port) {
    case AMHW_HC32F460_ADTIM_CHX_A:
        return p_hw_adtim->GCMAR;
    case AMHW_HC32F460_ADTIM_CHX_B:
        return p_hw_adtim->GCMBR;
    default:
        return AM_FALSE;
    }
}

/**
 * \brief �����ж�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_hc32f460_adtim_irq_type_t�ж�����ö����
 * \param[in] equal      : ��Ӧ�ж�ʹ�ܣ�AM_FALSE��AM_TRUE��
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_cfgirq(amhw_hc32f460_adtim_t         *p_hw_adtim,
                                   amhw_hc32f460_adtim_irq_type_t type,
                                   am_bool_t                    enable) {
    if(enable == AM_TRUE) {
        p_hw_adtim->ICONR |= (1ul << type);
    } else {
        p_hw_adtim->ICONR &= ~(1ul << type);
    }

    return AM_TRUE;
}

/**
 * \brief ��ȡ�жϱ�־
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_hc32f460_adtim_irq_type_t�ж�����ö����
 *
 * \return AM_FALSE:��־��Ч
 *         AM_TRUE :��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_get_status_flag(amhw_hc32f460_adtim_t         *p_hw_adtim,
                                       amhw_hc32f460_adtim_state_type_t type) {
    return ((p_hw_adtim->STFLR >> type) & 1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ����жϱ�־
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_hc32f460_adtim_irq_type_t�ж�����ö����
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_clear_status_flag(amhw_hc32f460_adtim_t         *p_hw_adtim,
                                         amhw_hc32f460_adtim_state_type_t type) {
    p_hw_adtim->STFLR &= ~(1ul << type);

    return AM_TRUE;
}

/**
 * \brief ��������жϱ�־
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_hc32f460_adtim_clearallirqflag(amhw_hc32f460_adtim_t *p_hw_adtim) {

    p_hw_adtim->STFLR = 0;

    return AM_TRUE;
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

#endif /* __AMHW_HC32F460_ADTIM_H */

/* end of file */
