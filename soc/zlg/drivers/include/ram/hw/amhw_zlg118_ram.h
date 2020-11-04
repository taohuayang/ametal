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
 * \brief RAM�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-08
 * \endinternal
 */

#ifndef __AMHW_ZLG118_RAM_H
#define __AMHW_ZLG118_RAM_H

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
 * \addtogroup amhw_zlg118_if_ram
 * \copydoc amhw_zlg118_ram.h
 * @{
 */

/**
 * \brief RAM�Ĵ�����ṹ��
 */
typedef struct amhw_zlg118_ram {
    __IO uint32_t cr;       /* ram���üĴ��� */
    __I  uint32_t erraddr;  /* ram�����ַ�Ĵ��� */
    __I  uint32_t ifr;      /* ram�����жϱ�־�Ĵ��� */
    __IO uint32_t iclr;     /* ram�����жϱ�־����Ĵ��� */
} amhw_zlg118_ram_t;

/**
 * \brief ʹ�ܳ������ж�
 *
 * \param[in]  p_hw_ram  : ָ��RAM�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_ram_ie_enable (amhw_zlg118_ram_t *p_hw_ram)
{
    p_hw_ram->cr |= 0x2ul;
}

/**
 * \brief ���ܳ������ж�
 *
 * \param[in]  p_hw_ram  : ָ��RAM�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_ram_ie_disable (amhw_zlg118_ram_t *p_hw_ram)
{
    p_hw_ram->cr &= ~0x2ul;
}

/**
 * \brief ��ȡ�����ַ
 *
 * \param[in]  p_hw_ram  : ָ��RAM�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
uint16_t amhw_zlg118_ram_erraddr_get (amhw_zlg118_ram_t *p_hw_ram)
{
    return (p_hw_ram->erraddr & 0x7f);
}

/**
 * \brief ��ȡ�����־
 *
 * \param[in]  p_hw_ram  : ָ��RAM�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_ram_err_get (amhw_zlg118_ram_t *p_hw_ram)
{
    return (p_hw_ram->ifr & 0x01);
}

/**
 * \brief ��������־
 *
 * \param[in]  p_hw_ram  : ָ��RAM�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_ram_err_clear (amhw_zlg118_ram_t *p_hw_ram)
{
    p_hw_ram->iclr &= ~0x01;
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
#endif /* __AMHW_ZLG118_RAM_H */

#endif

/* end of file */
