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
 * \brief CMP hardware operation interface
 *
 * -note:�ڶ�ͬһ�Ĵ������ж�дʱ������Ӧ�Ĺ��ܲ�ͬ
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-05  zcb, first implementation
 * \endinternal
 */

#ifndef __AMHW_HC32F460_CMP_H
#define __AMHW_HC32F460_CMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"
#include "am_bitops.h"
#include "hc32f460_regbase.h"
/**
 * \addtogroup amhw_hc32f460_if_cmp
 * \copydoc amhw_hc32f460_cmp.h
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
 * \brief CMP���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t FLTSL                     : 3;  /** <brief �˲�����ѡ��*/
    uint16_t RESERVED3                      : 2;  /** <brief ����*/
    __IO uint16_t EDGSL                     : 2;  /** <brief �ȽϽ����Ч����ѡ��*/
    __IO uint16_t IEN                       : 1;  /** <brief �Ƚ��ж����*/
    __IO uint16_t CVSEN                     : 1;  /** <brief �Ƚϵ�ѹɨ�����*/
    uint16_t RESERVED9                      : 3;  /** <brief ����*/
    __IO uint16_t OUTEN                     : 1;  /** <brief �ȽϽ��������*/
    __IO uint16_t INV                       : 1;  /** <brief �Ƚ����������ѡ��*/
    __IO uint16_t CMPOE                     : 1;  /** <brief �Ƚ���������*/
    __IO uint16_t CMPON                     : 1;  /** <brief �Ƚ����������*/
} stc_cmp_ctrl_field_t;

/**
 * \brief CMP��ѹѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t RVSL                      : 4;  /** <brief INM����ѡ��*/
    uint16_t RESERVED4                      : 4;  /** <brief ����*/
    __IO uint16_t CVSL                      : 4;  /** <brief INP����ѡ��*/
    __IO uint16_t C4SL                      : 3;  /** <brief INP4����ѡ��*/
    uint16_t RESERVED15                     : 1;  /** <brief ����*/
} stc_cmp_vltsel_field_t;

/**
 * \brief CMP������ӼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t OMON                      : 1;  /** <brief �ȽϽ������λ*/
    uint16_t RESERVED1                      : 7;  /** <brief ����*/
    __IO uint16_t CVST                      : 4;  /** <brief INP����״̬λ*/
    uint16_t RESERVED12                     : 4;  /** <brief ����*/
} stc_cmp_mon_field_t;

/**
 * \brief CMP�ȶ�ʱ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t STB                       : 4;  /** <brief �����л��ȶ�ʱ��*/
    uint16_t RESERVED4                      :12;  /** <brief ����*/
} stc_cmp_cvsstb_field_t;

/**
 * \brief CMP�Ƚϵ�ѹɨ�����ڼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t PRD                       : 8;  /** <brief �Ƚϵ�ѹɨ������*/
    uint16_t RESERVED8                      : 8;  /** <brief ����*/
} stc_cmp_cvsprd_field_t;

/**
 * \brief CMP��8-bit-DAC���ݼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t DATA                      : 8;  /** <brief DAת������*/
    uint16_t RESERVED8                      : 8;  /** <brief ����*/
} stc_cmp_cr_dadr1_field_t;

/**
 * \brief CMP��8-bit-DAC���ݼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t DATA                      : 8;  /** <brief DAת������*/
    uint16_t RESERVED8                      : 8;  /** <brief ����*/
} stc_cmp_cr_dadr2_field_t;

/**
 * \brief CMP��8-bit-DAC���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t DA1EN                     : 1;  /** <brief DA1����λ*/
    __IO uint16_t DA2EN                     : 1;  /** <brief DA2����λ*/
    uint16_t RESERVED2                      :14;  /** <brief ����*/
} stc_cmp_cr_dacr_field_t;

/**
 * \brief CMP�ڲ���׼��ѹADת���Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t DA1SW                     : 1;  /** <brief DA1 AD ת������*/
    __IO uint16_t DA2SW                     : 1;  /** <brief DA2 AD ת������*/
    uint16_t RESERVED2                      : 2;  /** <brief ����*/
    __IO uint16_t VREFSW                    : 1;  /** <brief �ڲ�Vref ADת������*/
    uint16_t RESERVED5                      :11;  /** <brief ����*/
} stc_cmp_cr_rvadc_field_t;
 
typedef struct
{
    uint8_t RESERVED0[256];             /** <brief ���� */
    union
    {
        __IO uint16_t DADR1;            /** <brief CMP��8bitDAC���ݼĴ���1 */
        stc_cmp_cr_dadr1_field_t DADR1_f;
    };
    union
    {
        __IO uint16_t DADR2;            /** <brief CMP��8bitDAC���ݼĴ���2 */
        stc_cmp_cr_dadr2_field_t DADR2_f;
    };
    uint8_t RESERVED2[4];               /** <brief ���� */
    union
    {
        __IO uint16_t DACR;             /** <brief CMP��8bitDAC���ƼĴ��� */
        stc_cmp_cr_dacr_field_t DACR_f;
    };
    uint8_t RESERVED3[2];               /** <brief ���� */
    union
    {
        __IO uint16_t RVADC;            /** <brief CMP�ڲ���׼��ѹADת���Ĵ��� */
        stc_cmp_cr_rvadc_field_t RVADC_f;
    };
}amhw_hc32f460_cmp_cr_t;

typedef struct
{
    union
    {
        __IO uint16_t CTRL;           /** <brief CMP���ƼĴ��� */
        stc_cmp_ctrl_field_t CTRL_f;
    };
    union
    {
        __IO uint16_t VLTSEL;         /** <brief CMP��ѹѡ��Ĵ��� */
        stc_cmp_vltsel_field_t VLTSEL_f;
    };
    union
    {
        __IO uint16_t MON;            /** <brief CMP������ӼĴ��� */
        stc_cmp_mon_field_t MON_f;
    };
    union
    {
        __IO uint16_t CVSSTB;         /** <brief CMP�ȶ�ʱ��Ĵ��� */
        stc_cmp_cvsstb_field_t CVSSTB_f;
    };
    union
    {
        __IO uint16_t CVSPRD;          /** <brief CMPɨ�����ڼĴ��� */
        stc_cmp_cvsprd_field_t CVSPRD_f;
    };
}amhw_hc32f460_cmp_t;


typedef enum en_cmp_dac_ch
{
    CmpDac1 = 0u,                              /** <brief DAC1 */
    CmpDac2 = 1u,                              /** <brief DAC2 */
} en_cmp_dac_ch_t;

typedef enum en_cmp_functional_state
{
    CMP_Disable = 0u,
    CMP_Enable  = 1u,
} en_cmp_functional_state_t;

typedef struct stc_cmp_dac_init
{
    uint8_t               u8DacData;            /** <brief CMP DAC Data register value */

    en_cmp_functional_state_t enCmpDacEN;       /** <brief CMP DAC enable */
} stc_cmp_dac_init_t;

/**
 *******************************************************************************
 ** \brief CMP edge selection enumeration
 ******************************************************************************/
typedef enum en_cmp_edge_sel
{
    CmpNoneEdge     = 0u,              /** <brief None edge detection */
    CmpRisingEdge   = 1u,              /** <brief Rising edge detection */
    CmpFaillingEdge = 2u,              /** <brief Falling edge detection */
    CmpBothEdge     = 3u,              /** <brief Falling or Rising edge detection */
} en_cmp_edge_sel_t;

/**
 *******************************************************************************
 ** \brief CMP filter sample clock division enumeration
 ******************************************************************************/
typedef enum en_cmp_fltclk_div
{
    CmpNoneFlt       = 0u,              /** <brief Unuse filter */
    CmpFltPclk3Div1  = 1u,              /** <brief PCLK3/1 */
    CmpFltPclk3Div2  = 2u,              /** <brief PCLK3/2 */
    CmpFltPclk3Div4  = 3u,              /** <brief PCLK3/4 */
    CmpFltPclk3Div8  = 4u,              /** <brief PCLK3/8 */
    CmpFltPclk3Div16 = 5u,              /** <brief PCLK3/16 */
    CmpFltPclk3Div32 = 6u,              /** <brief PCLK3/32 */
    CmpFltPclk3Div64 = 7u,              /** <brief PCLK3/64 */
} en_cmp_fltclk_div_t;


typedef struct stc_cmp_init
{
    en_cmp_edge_sel_t     enEdgeSel;              /** <brief CMP edge sel */

    en_cmp_fltclk_div_t   enFltClkDiv;            /** <brief CMP FLTclock division */

    en_cmp_functional_state_t enCmpOutputEn;      /** <brief CMP Output enable */

    en_cmp_functional_state_t enCmpVcoutOutputEn; /** <brief CMP output result enable */

    en_cmp_functional_state_t enCmpInvEn;         /** <brief CMP INV sel for output */

    en_cmp_functional_state_t enCmpIntEN;         /** <brief CMP interrupt enable */
} stc_cmp_init_t;

typedef enum en_cmp_inm_sel
{
    CmpInmNone = 0u,                       /** <brief None input */
    CmpInm1    = 1u,                       /** <brief INM1 input */
    CmpInm2    = 2u,                       /** <brief INM2 input */
    CmpInm3    = 4u,                       /** <brief INM3 input */
    CmpInm4    = 8u,                       /** <brief INM4 input */
} en_cmp_inm_sel_t;

typedef enum en_cmp_inp_sel
{
    CmpInpNone             = 0u,           /** <brief None input */
    CmpInp1                = 1u,           /** <brief INP1 input */
    CmpInp2                = 2u,           /** <brief INP2 input */
    CmpInp1_Inp2           = 3u,           /** <brief INP1 INP2 input */
    CmpInp3                = 4u,           /** <brief INP3 input */
    CmpInp1_Inp3           = 5u,           /** <brief INP1 INP3 input */
    CmpInp2_Inp3           = 6u,           /** <brief INP2 INP3 input */
    CmpInp1_Inp2_Inp3      = 7u,           /** <brief INP1 INP2 INP3 input */
    CmpInp4                = 8u,           /** <brief INP4 input */
    CmpInp1_Inp4           = 9u,           /** <brief INP1 INP4 input */
    CmpInp2_Inp4           = 10u,          /** <brief INP2 INP4 input */
    CmpInp1_Inp2_Inp4      = 11u,          /** <brief INP1 INP2 INP4 input */
    CmpInp3_Inp4           = 12u,          /** <brief INP3 INP4 input */
    CmpInp1_Inp3_Inp4      = 13u,          /** <brief INP1 INP3 INP4 input */
    CmpInp2_Inp3_Inp4      = 14u,          /** <brief INP2 INP3 INP4 input */
    CmpInp1_Inp2_Inp3_Inp4 = 15u,          /** <brief INP1 INP2 INP3 INP4 input */
} en_cmp_inp_sel_t;

typedef enum en_cmp_inp4_sel
{
    CmpInp4None      = 0u,                 /** <brief None input */
    CmpInp4PGAO      = 1u,                 /** <brief PGAO output */
    CmpInp4PGAO_BP   = 2u,                 /** <brief PGAO_BP output */
    CmpInp4CMP1_INP4 = 4u,                 /** <brief CMP1_INP4 */
} en_cmp_inp4_sel_t;

typedef struct stc_cmp_input_sel
{
    en_cmp_inm_sel_t  enInmSel;            /** <brief CMP INM sel */

    en_cmp_inp_sel_t  enInpSel;            /** <brief CMP INP sel */

    en_cmp_inp4_sel_t enInp4Sel;           /** <brief CMP INP4 sel */
} stc_cmp_input_sel_t;

am_static_inline
am_bool_t CMP_DAC_Init(amhw_hc32f460_cmp_cr_t   *p_hw_cmp_cr,
                       en_cmp_dac_ch_t           enCh,
                       const stc_cmp_dac_init_t *pstcInitCfg)
{
    am_bool_t enRet = AM_FALSE;

    if (pstcInitCfg != NULL)
    {        
        p_hw_cmp_cr->DACR &= (uint16_t)(~(1ul << enCh));    /* Disable DAC */

        if (CmpDac1 == enCh) {
            *(__IO uint8_t *)(&p_hw_cmp_cr->DADR1) = pstcInitCfg->u8DacData;
        } else if (CmpDac2 == enCh) {
            *(__IO uint8_t *)(&p_hw_cmp_cr->DADR2) = pstcInitCfg->u8DacData;
        } else {
            ;
        }

//        *(__IO uint8_t *)CMP_CR_DADRx(p_hw_cmp_cr, enCh) = pstcInitCfg->u8DacData; /* Set DAC data */

        if (CMP_Enable == pstcInitCfg->enCmpDacEN)
        {
            p_hw_cmp_cr->DACR |= (uint16_t)(1ul << enCh); /* Enable DAC */
        }
        enRet = AM_OK;
    }

    return enRet;
}

am_static_inline
am_bool_t CMP_Init(amhw_hc32f460_cmp_t *p_hw_cmp, const stc_cmp_init_t *pstcInitCfg)
{
    am_bool_t enRet = AM_FALSE;

    /* Check CMPx && pstcInitCfg pointer */
    if (NULL != pstcInitCfg)
    {
        /* De-Initialize CMP */
        p_hw_cmp->CTRL = (uint16_t)0x0000u;
        p_hw_cmp->VLTSEL = (uint16_t)0x0000u;
        p_hw_cmp->CVSSTB = (uint16_t)0x0005u;
        p_hw_cmp->CVSPRD = (uint16_t)0x000Fu;

        p_hw_cmp->CTRL_f.IEN = (uint16_t)pstcInitCfg->enCmpIntEN;
        p_hw_cmp->CTRL_f.INV = (uint16_t)pstcInitCfg->enCmpInvEn;
        p_hw_cmp->CTRL_f.EDGSL = (uint16_t)pstcInitCfg->enEdgeSel;
        p_hw_cmp->CTRL_f.FLTSL = (uint16_t)pstcInitCfg->enFltClkDiv;
        p_hw_cmp->CTRL_f.CMPOE = (uint16_t)pstcInitCfg->enCmpOutputEn;
        p_hw_cmp->CTRL_f.OUTEN = (uint16_t)pstcInitCfg->enCmpVcoutOutputEn;
        enRet = AM_OK;
    }

    return enRet;
}

am_static_inline
am_bool_t CMP_InputSel(amhw_hc32f460_cmp_t *p_hw_cmp,
                            const stc_cmp_input_sel_t *pstcInputSel)
{
    am_bool_t enRet = AM_FALSE;

    /* Check CMPx && pstcInputSel pointer */
    if (NULL != pstcInputSel)
    {
        if ((CmpInp4PGAO == pstcInputSel->enInp4Sel) ||
            (CmpInp4PGAO_BP == pstcInputSel->enInp4Sel))
        {
            if ((amhw_hc32f460_cmp_t *)HC32F460_CMP3_BASE != p_hw_cmp)
            {
                enRet = AM_OK;
            }
        }
        else if (CmpInp4CMP1_INP4 == pstcInputSel->enInp4Sel)
        {
            if ((amhw_hc32f460_cmp_t *)HC32F460_CMP1_BASE == p_hw_cmp)
            {
                enRet = AM_OK;
            }
        }
        else
        {
            enRet = AM_OK;
        }

        if (enRet == AM_OK)
        {
            p_hw_cmp->VLTSEL_f.CVSL = (uint16_t)pstcInputSel->enInpSel;
            p_hw_cmp->VLTSEL_f.RVSL = (uint16_t)pstcInputSel->enInmSel;
            p_hw_cmp->VLTSEL_f.C4SL = (uint16_t)pstcInputSel->enInp4Sel;
        }
    }

    return enRet;
}

am_static_inline
am_bool_t CMP_Cmd(amhw_hc32f460_cmp_t *p_hw_cmp, en_cmp_functional_state_t enCmd)
{
    am_bool_t enRet = AM_FALSE;

    /* Check CMPx pointer */
    if (NULL != p_hw_cmp)
    {
        p_hw_cmp->CTRL_f.CMPON = (uint16_t)(enCmd);
        enRet = AM_OK;
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
 * @} amhw_hc32f460_if_cmp
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_CMP_H */

/* end of file */
