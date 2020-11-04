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
 * \brief PCA�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-08
 * \endinternal
 */

#ifndef __AMHW_ZLG118_PCA_H
#define __AMHW_ZLG118_PCA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zlg118_if_pca
 * \copydoc amhw_zlg118_pca.h
 * @{
 */

/**
 * \brief PCA�Ĵ�����ṹ��
 */
typedef struct amhw_zlg118_pca {
    __IO uint32_t ccon;     /* ���ƼĴ��� */
    __IO uint32_t cmod;     /* ģʽ�Ĵ��� */
    __IO uint32_t cnt;      /* �����Ĵ��� */
    __O  uint32_t iclr;     /* �ж�����Ĵ��� */
    __IO uint32_t ccapm0;   /* �Ƚ�/����ģ��0ģʽ�Ĵ��� */
    __IO uint32_t ccapm1;   /* �Ƚ�/����ģ��1ģʽ�Ĵ��� */
    __IO uint32_t ccapm2;   /* �Ƚ�/����ģ��2ģʽ�Ĵ��� */
    __IO uint32_t ccapm3;   /* �Ƚ�/����ģ��3ģʽ�Ĵ��� */
    __IO uint32_t ccapm4;   /* �Ƚ�/����ģ��4ģʽ�Ĵ��� */
    __IO uint32_t ccap0h;   /* �Ƚ�/����ģ��0��8λ�Ĵ��� */
    __IO uint32_t ccap0l;   /* �Ƚ�/����ģ��0��8λ�Ĵ��� */
    __IO uint32_t ccap1h;   /* �Ƚ�/����ģ��1��8λ�Ĵ��� */
    __IO uint32_t ccap1l;   /* �Ƚ�/����ģ��1��8λ�Ĵ��� */
    __IO uint32_t ccap2h;   /* �Ƚ�/����ģ��2��8λ�Ĵ��� */
    __IO uint32_t ccap2l;   /* �Ƚ�/����ģ��2��8λ�Ĵ��� */
    __IO uint32_t ccap3h;   /* �Ƚ�/����ģ��3��8λ�Ĵ��� */
    __IO uint32_t ccap3l;   /* �Ƚ�/����ģ��3��8λ�Ĵ��� */
    __IO uint32_t ccap4h;   /* �Ƚ�/����ģ��4��8λ�Ĵ��� */
    __IO uint32_t ccap4l;   /* �Ƚ�/����ģ��4��8λ�Ĵ��� */
    __IO uint32_t ccapo;    /* PWM����������־�Ĵ��� */
    __IO uint32_t ccap0;    /* �Ƚ�/����ģ��0��16λ�Ĵ��� */
    __IO uint32_t ccap1;    /* �Ƚ�/����ģ��1��16λ�Ĵ��� */
    __IO uint32_t ccap2;    /* �Ƚ�/����ģ��2��16λ�Ĵ��� */
    __IO uint32_t ccap3;    /* �Ƚ�/����ģ��3��16λ�Ĵ��� */
    __IO uint32_t ccap4;    /* �Ƚ�/����ģ��4��16λ�Ĵ��� */
    __IO uint32_t carr;     /* ����װ�ؼĴ��� */
    __IO uint32_t epwm;     /* PWM��ǿ�Ĵ��� */
} amhw_zlg118_pca_t;

/**
 * \brief ��������ʼ����
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_start (amhw_zlg118_pca_t *p_hw_pca)
{
    p_hw_pca->ccon |= (0x1ul << 6);
}

/**
 * \brief ������ֹͣ����
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_stop (amhw_zlg118_pca_t *p_hw_pca)
{
    p_hw_pca->ccon &= ~(0x1ul << 6);
}

/**
 * \brief PCA����ģʽ��������
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  cidl      : ����ģʽѡ��, 1:����ģʽֹͣ����
 *                                      0:����ģʽ��������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_cidl_set (amhw_zlg118_pca_t    *p_hw_pca,
                               uint8_t               cidl)
{
    if(cidl > 1) {
        cidl = 1;
    }
    p_hw_pca->cmod &= ~(1ul << 7);
    p_hw_pca->cmod |= cidl << 7;
}

/**
 * \brief PCA WDT��������
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  wdte      : ����ģʽѡ��, 1:����ģ��4��WDT����
 *                                      0:�ر�ģ��4��WDT����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_wdte_set (amhw_zlg118_pca_t    *p_hw_pca,
                               uint8_t               wdte)
{
    if(wdte > 1) {
        wdte = 1;
    }
    p_hw_pca->cmod &= ~(1ul << 6);
    p_hw_pca->cmod |= wdte << 6;
}

/**
 * \brief PCA ʱ�ӷ�Ƶ��ʱ��Դ����
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  cps       : ����ģʽѡ��, 1:����ģ��4��WDT����
 *                                      0:�ر�ģ��4��WDT����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_cps_set (amhw_zlg118_pca_t    *p_hw_pca,
                              uint8_t               cps)
{
    if(cps > 7) {
        cps = 7;
    }
    p_hw_pca->cmod &= ~(7ul << 1);
    p_hw_pca->cmod |= cps << 1;
}

/**
 * \brief PCA �������ж�ʹ������
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  cfie      : ����ģʽѡ��, 1:ʹ���ж�
 *                                      0:�ر��ж�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_cfie_set (amhw_zlg118_pca_t    *p_hw_pca,
                               uint8_t               cfie)
{
    if(cfie > 1) {
        cfie = 1;
    }
    p_hw_pca->cmod &= ~1ul;
    p_hw_pca->cmod |= cfie;
}

/**
 * \brief PCA�����Ĵ�������
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  data      : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_cnt_set (amhw_zlg118_pca_t *p_hw_pca, uint8_t data)
{
    p_hw_pca->cnt = data;
}

/**
 * \brief PCA�жϻ�ȡ
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  flag     : �жϱ�־
 *
 * \return 0:��־λδ��λ, 1:��־λ��λ
 */
am_static_inline
uint8_t amhw_zlg118_pca_int_get (amhw_zlg118_pca_t   *p_hw_pca,
                                 uint8_t              flag)
{
    return (p_hw_pca->ccon & flag);
}

/**
 * \brief PCA�ж����
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  flag     : �жϱ�־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_int_clear (amhw_zlg118_pca_t  *p_hw_pca,
                                uint8_t             flag)
{
    p_hw_pca->iclr &= ~flag;
}

/**
 * \brief PCA ����Ƚ������ܿ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 * \papca[in]  ecom     : ����, 1:ʹ��, 0:����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_ecom_set (amhw_zlg118_pca_t  *p_hw_pca,
                               uint8_t             num,
                               uint8_t             ecom)
{
    if(ecom > 1) {
        ecom = 1;
    }

    switch(num) {
    case 0:
        p_hw_pca->ccapm0 &= ~(1 << 6);
        p_hw_pca->ccapm0 |= ecom << 6;
        break;

    case 1:
        p_hw_pca->ccapm1 &= ~(1 << 6);
        p_hw_pca->ccapm1 |= ecom << 6;
        break;

    case 2:
        p_hw_pca->ccapm2 &= ~(1 << 6);
        p_hw_pca->ccapm2 |= ecom << 6;
        break;

    case 3:
        p_hw_pca->ccapm3 &= ~(1 << 6);
        p_hw_pca->ccapm3 |= ecom << 6;
        break;

    case 4:
        p_hw_pca->ccapm4 &= ~(1 << 6);
        p_hw_pca->ccapm4 |= ecom << 6;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA ���ز����ܿ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 * \papca[in]  capp     : ����, 1:ʹ��, 0:����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_capp_set (amhw_zlg118_pca_t  *p_hw_pca,
                               uint8_t             num,
                               uint8_t             capp)
{
    if(capp > 1) {
        capp = 1;
    }

    switch(num) {
    case 0:
        p_hw_pca->ccapm0 &= ~(1 << 5);
        p_hw_pca->ccapm0 |= capp << 5;
        break;

    case 1:
        p_hw_pca->ccapm1 &= ~(1 << 5);
        p_hw_pca->ccapm1 |= capp << 5;
        break;

    case 2:
        p_hw_pca->ccapm2 &= ~(1 << 5);
        p_hw_pca->ccapm2 |= capp << 5;
        break;

    case 3:
        p_hw_pca->ccapm3 &= ~(1 << 5);
        p_hw_pca->ccapm3 |= capp << 5;
        break;

    case 4:
        p_hw_pca->ccapm4 &= ~(1 << 5);
        p_hw_pca->ccapm4 |= capp << 5;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA ���ز����ܿ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 * \papca[in]  capn     : ����, 1:ʹ��, 0:����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_capn_set (amhw_zlg118_pca_t  *p_hw_pca,
                               uint8_t             num,
                               uint8_t             capn)
{
    if(capn > 1) {
        capn = 1;
    }

    switch(num) {
    case 0:
        p_hw_pca->ccapm0 &= ~(1 << 4);
        p_hw_pca->ccapm0 |= capn << 4;
        break;

    case 1:
        p_hw_pca->ccapm1 &= ~(1 << 4);
        p_hw_pca->ccapm1 |= capn << 4;
        break;

    case 2:
        p_hw_pca->ccapm2 &= ~(1 << 4);
        p_hw_pca->ccapm2 |= capn << 4;
        break;

    case 3:
        p_hw_pca->ccapm3 &= ~(1 << 4);
        p_hw_pca->ccapm3 |= capn << 4;
        break;

    case 4:
        p_hw_pca->ccapm4 &= ~(1 << 4);
        p_hw_pca->ccapm4 |= capn << 4;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA ƥ�书�ܿ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 * \papca[in]  mat      : ����, 1:ʹ��, 0:����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_mat_set (amhw_zlg118_pca_t  *p_hw_pca,
                              uint8_t             num,
                              uint8_t             mat)
{
    if(mat > 1) {
        mat = 1;
    }

    switch(num) {
    case 0:
        p_hw_pca->ccapm0 &= ~(1 << 3);
        p_hw_pca->ccapm0 |= mat << 3;
        break;

    case 1:
        p_hw_pca->ccapm1 &= ~(1 << 3);
        p_hw_pca->ccapm1 |= mat << 3;
        break;

    case 2:
        p_hw_pca->ccapm2 &= ~(1 << 3);
        p_hw_pca->ccapm2 |= mat << 3;
        break;

    case 3:
        p_hw_pca->ccapm3 &= ~(1 << 3);
        p_hw_pca->ccapm3 |= mat << 3;
        break;

    case 4:
        p_hw_pca->ccapm4 &= ~(1 << 3);
        p_hw_pca->ccapm4 |= mat << 3;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA ��ת���ܿ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 * \papca[in]  tog      : ����, 1:ʹ��, 0:����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_tog_set (amhw_zlg118_pca_t  *p_hw_pca,
                              uint8_t             num,
                              uint8_t             tog)
{
    if(tog > 1) {
        tog = 1;
    }

    switch(num) {
    case 0:
        p_hw_pca->ccapm0 &= ~(1 << 2);
        p_hw_pca->ccapm0 |= tog << 2;
        break;

    case 1:
        p_hw_pca->ccapm1 &= ~(1 << 2);
        p_hw_pca->ccapm1 |= tog << 2;
        break;

    case 2:
        p_hw_pca->ccapm2 &= ~(1 << 2);
        p_hw_pca->ccapm2 |= tog << 2;
        break;

    case 3:
        p_hw_pca->ccapm3 &= ~(1 << 2);
        p_hw_pca->ccapm3 |= tog << 2;
        break;

    case 4:
        p_hw_pca->ccapm4 &= ~(1 << 2);
        p_hw_pca->ccapm4 |= tog << 2;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA ������ƹ��ܿ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 * \papca[in]  pwm      : ����, 1:ʹ��, 0:����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_pwm_set (amhw_zlg118_pca_t  *p_hw_pca,
                              uint8_t             num,
                              uint8_t             pwm)
{
    if(pwm > 1) {
        pwm = 1;
    }

    switch(num) {
    case 0:
        p_hw_pca->ccapm0 &= ~(1 << 1);
        p_hw_pca->ccapm0 |= pwm << 1;
        break;

    case 1:
        p_hw_pca->ccapm1 &= ~(1 << 1);
        p_hw_pca->ccapm1 |= pwm << 1;
        break;

    case 2:
        p_hw_pca->ccapm2 &= ~(1 << 1);
        p_hw_pca->ccapm2 |= pwm << 1;
        break;

    case 3:
        p_hw_pca->ccapm3 &= ~(1 << 1);
        p_hw_pca->ccapm3 |= pwm << 1;
        break;

    case 4:
        p_hw_pca->ccapm4 &= ~(1 << 1);
        p_hw_pca->ccapm4 |= pwm << 1;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA �ж�ʹ�ܿ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 * \papca[in]  ccie     : ����, 1:ʹ��, 0:����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_ccie_set (amhw_zlg118_pca_t  *p_hw_pca,
                               uint8_t             num,
                               uint8_t             ccie)
{
    if(ccie > 1) {
        ccie = 1;
    }

    switch(num) {
    case 0:
        p_hw_pca->ccapm0 &= ~(1);
        p_hw_pca->ccapm0 |= ccie;
        break;

    case 1:
        p_hw_pca->ccapm1 &= ~(1);
        p_hw_pca->ccapm1 |= ccie;
        break;

    case 2:
        p_hw_pca->ccapm2 &= ~(1);
        p_hw_pca->ccapm2 |= ccie;
        break;

    case 3:
        p_hw_pca->ccapm3 &= ~(1);
        p_hw_pca->ccapm3 |= ccie;
        break;

    case 4:
        p_hw_pca->ccapm4 &= ~(1);
        p_hw_pca->ccapm4 |= ccie;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA�Ƚϲ������ݼĴ����߰�λ����
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  data     : ����ֵ
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_ccaph_set (amhw_zlg118_pca_t  *p_hw_pca,
                                uint8_t             num,
                                uint8_t             data)
{
    switch(num) {
    case 0:
        p_hw_pca->ccap0h = data;
        break;

    case 1:
        p_hw_pca->ccap1h = data;
        break;

    case 2:
        p_hw_pca->ccap2h = data;
        break;

    case 3:
        p_hw_pca->ccap3h = data;
        break;

    case 4:
        p_hw_pca->ccap4h = data;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA�Ƚϲ������ݼĴ����߰�λ��ȡ
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_pca_ccaph_get (amhw_zlg118_pca_t  *p_hw_pca,
                                   uint8_t             num)
{
    switch(num) {
    case 0:
        return p_hw_pca->ccap0h & 0xff;

    case 1:
        return p_hw_pca->ccap1h & 0xff;

    case 2:
        return p_hw_pca->ccap2h & 0xff;

    case 3:
        return p_hw_pca->ccap3h & 0xff;

    case 4:
        return p_hw_pca->ccap4h & 0xff;

    default:
        break;
    }

    return 0;
}

/**
 * \brief PCA�Ƚϲ������ݼĴ����Ͱ�λ����
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  data     : ����ֵ
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_ccapl_set (amhw_zlg118_pca_t  *p_hw_pca,
                                uint8_t             num,
                                uint8_t             data)
{
    switch(num) {
    case 0:
        p_hw_pca->ccap0l = data;
        break;

    case 1:
        p_hw_pca->ccap1l = data;
        break;

    case 2:
        p_hw_pca->ccap2l = data;
        break;

    case 3:
        p_hw_pca->ccap3l = data;
        break;

    case 4:
        p_hw_pca->ccap4l = data;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA�Ƚϲ������ݼĴ����Ͱ�λ��ȡ
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_pca_ccapl_get (amhw_zlg118_pca_t  *p_hw_pca,
                                   uint8_t             num)
{
    switch(num) {
    case 0:
        return p_hw_pca->ccap0l & 0xff;

    case 1:
        return p_hw_pca->ccap1l & 0xff;

    case 2:
        return p_hw_pca->ccap2l & 0xff;

    case 3:
        return p_hw_pca->ccap3l & 0xff;

    case 4:
        return p_hw_pca->ccap4l & 0xff;

    default:
        break;
    }

    return 0;
}

/**
 * \brief PCA�Ƚϲ���16λ�Ĵ�������
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  data     : ����ֵ
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_ccap_set (amhw_zlg118_pca_t  *p_hw_pca,
                               uint8_t             num,
                               uint16_t            data)
{
    switch(num) {
    case 0:
        p_hw_pca->ccap0 = data;
        break;

    case 1:
        p_hw_pca->ccap1 = data;
        break;

    case 2:
        p_hw_pca->ccap2 = data;
        break;

    case 3:
        p_hw_pca->ccap3 = data;
        break;

    case 4:
        p_hw_pca->ccap4 = data;
        break;

    default:
        break;
    }
}

/**
 * \brief PCA�Ƚϲ���16λ�Ĵ�����ȡ
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
uint16_t amhw_zlg118_pca_ccap_get (amhw_zlg118_pca_t  *p_hw_pca,
                                   uint8_t             num)
{
    switch(num) {
    case 0:
        return p_hw_pca->ccap0 & 0xffff;

    case 1:
        return p_hw_pca->ccap1 & 0xffff;

    case 2:
        return p_hw_pca->ccap2 & 0xffff;

    case 3:
        return p_hw_pca->ccap3 & 0xffff;

    case 4:
        return p_hw_pca->ccap4 & 0xffff;

    default:
        break;
    }

    return 0;
}

/**
 * \brief PCA�Ƚϸ������ʹ��
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_ccapo_enable (amhw_zlg118_pca_t  *p_hw_pca,
                                   uint8_t             num)
{
    p_hw_pca->ccapo |= (1 << num);
}

/**
 * \brief PCA�Ƚϸ����������
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  num      : ģ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_ccapo_disable (amhw_zlg118_pca_t  *p_hw_pca,
                                    uint8_t             num)
{
    p_hw_pca->ccapo &= ~(1 << num);
}

/**
 * \brief PCA���ڼĴ�������
 *
 * \papca[in]  p_hw_pca  : ָ��PCA�Ĵ����ṹ���ָ��
 * \papca[in]  data      : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_carr_set (amhw_zlg118_pca_t *p_hw_pca, uint16_t data)
{
    p_hw_pca->carr = data;
}

/**
 * \brief PCA��ǿPWM����ʹ��
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_epwm_enable (amhw_zlg118_pca_t  *p_hw_pca)
{
    p_hw_pca->epwm = 1;
}

/**
 * \brief PCA��ǿPWM���ƽ���
 *
 * \papca[in]  p_hw_pca : ָ��PCA�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pca_epwm_disable (amhw_zlg118_pca_t  *p_hw_pca)
{
    p_hw_pca->epwm = 0;
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __AMHW_ZLG118_PCA_H */

#endif

/* end of file */
