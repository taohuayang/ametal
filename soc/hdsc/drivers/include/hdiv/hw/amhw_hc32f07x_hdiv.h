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
 * \brief HDIV Peripheral Access Layer
 *
 *   The Miscellaneous System Control Module (FTFC) contains CPU configuration
 *   registers and on-chip memory controller registers.
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-04  zp, first implementation
 *
 * \endinternal
 */

#ifndef __AMHW_HC32F07X_HDIV_H
#define __AMHW_HC32F07X_HDIV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_hc32f07x_if_hdiv
 * \copydoc amhw_hc32f07x_hdiv.h
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

/*
 * \brief the structure of hidv register
 */
typedef struct amhw_hc32f07x_hdiv {
    __IO uint32_t divdend;   /**< \brief �������Ĵ���           offset : 0x00 */
    __IO uint32_t divisor;   /**< \brief �����Ĵ���             offset : 0x04 */
    __IO uint32_t quotient;  /**< \brief �̼Ĵ���              offset : 0x08 */
    __IO uint32_t remainder; /**< \brief �����Ĵ���           offset : 0x0c */
    __IO uint32_t sign;      /**< \brief ���żĴ���                offset : 0x10 */
    __IO uint32_t stat;      /**< \brief ״̬�Ĵ���                offset : 0x14 */
} amhw_hc32f07x_hdiv_t;



typedef struct amhw_hc32f07x_hdiv_unsigned {
    uint32_t undividend;
    uint32_t undivisor;
    uint32_t quotient;
    uint32_t remainder;	
} amhw_hc32f07x_hdiv_unsigned_t;

typedef struct amhw_hc32f07x_hdiv_signed {
    int32_t dividend;
    int32_t divisor;
    int32_t quotient;
    int32_t remainder;	
} amhw_hc32f07x_hdiv_signed_t;

/**
 * \brief hdiv �з��ų�����������
 *
 * \param[in] p_hw_hdiv : ָ��hdiv�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_hdiv_signed_set (amhw_hc32f07x_hdiv_t *p_hw_hdiv)
{
    p_hw_hdiv->sign |= (0x1ul << 0);
}

/**
 * \brief hdiv �޷��ų�����������
 *
 * \param[in] p_hw_hdiv : ָ��hdiv�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_hdiv_unsigned_set (amhw_hc32f07x_hdiv_t *p_hw_hdiv)
{
    p_hw_hdiv->sign &= ~(0x1ul << 0);
}

/**
 * \brief hdiv ����Ϊ�㾯���־��ȡ
 *
 * \param[in] p_hw_hdiv : ָ��hdiv�Ĵ�����ָ��
 *
 * \return    AM_TRUE  : ����Ϊ��
 *            AM_FALSE : ������Ϊ��
 */
am_static_inline
am_bool_t amhw_hc32f07x_hdiv_zerostat_get (amhw_hc32f07x_hdiv_t *p_hw_hdiv)
{
    return (am_bool_t)((p_hw_hdiv->stat >> 1)&0x01);
}

/**
 * \brief hdiv ���������־��ȡ
 *
 * \param[in] p_hw_hdiv : ָ��hdiv�Ĵ�����ָ��
 *
 * \return    AM_TRUE  : �������
 *            AM_FALSE : ���������
 */
am_static_inline
am_bool_t amhw_hc32f07x_hdiv_endstat_get (amhw_hc32f07x_hdiv_t *p_hw_hdiv)
{
    return (am_bool_t)((p_hw_hdiv->stat >> 0)&0x01);
}

/**
* \brief    HDIV �޷��ų���
*
* \param[in] p_hw_hdiv : ָ��hdiv�Ĵ�����ָ��
* \param[in] p_divd    �������ṹ��
*
* \retval  AM_OK       : ����ɹ�
* \retval  -AM_EINVAL  : ������Ч
*/
int am_hc32f07x_hdiv_unsigned(amhw_hc32f07x_hdiv_t *p_hw_hdiv, 
	                            amhw_hc32f07x_hdiv_unsigned_t *p_undivd);

/**
* \brief    HDIV �з��ų���
*
* \param[in] p_hw_hdiv : ָ��hdiv�Ĵ�����ָ��
* \param[in] p_divd    �������ṹ��
*
* \retval  AM_OK       : ����ɹ�
* \retval  -AM_EINVAL  : ������Ч
*/
int am_hc32f07x_hdiv_signed(amhw_hc32f07x_hdiv_t *p_hw_hdiv, 
	                            amhw_hc32f07x_hdiv_signed_t *p_divd);

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

#endif /* __AMHW_HC32F07X_HDIV_H */

/* end of file */
