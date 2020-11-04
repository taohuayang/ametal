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
 * \brief LPMODE Peripheral Access Layer
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  YRZ, first implementation
 *
 * \endinternal
 */

#ifndef __AMHW_ZSN700_LPMODE_H
#define __AMHW_ZSN700_LPMODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zsn700_if_lpmode
 * \copydoc amhw_zsn700_lpmode.h
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

#if   defined ( __CC_ARM )
  #define __ASM            __asm         /*!< asm keyword for ARM Compiler */
  #define __INLINE         __inline      /*!< inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline
#endif
#if defined ( __GNUC__ )
  #define __ASM            __asm         /*!< asm keyword for GNU Compiler */
  #define __INLINE         inline        /*!< inline keyword for GNU Compiler */
  #define __STATIC_INLINE  static inline
#endif

#include "core_cmInstr.h"

/** @} */

/**
 * \brief LPMODE - Register Layout Typedef
 */
typedef struct amhw_zsn700_lpmode {
    __IO  uint32_t cr;       /**< \brief ϵͳ���ƼĴ���  */
} amhw_zsn700_lpmode_t;

#define LPMODECTRL ((amhw_zsn700_lpmode_t *)0xE000ED10)

/**
 * \brief �жϹ����¼�����
 *
 * \param[in] stata : AM_TRUE  ��ÿ���µ��жϹ��𶼻����һ���¼�
 *                    AM_FALSE ��ÿ���µ��жϹ��𶼲������һ���¼�
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpmode_sevonpend (am_bool_t stata)
{
    LPMODECTRL->cr = (LPMODECTRL->cr & (~(1ul << 4))) |
                     (stata << 4);
}

/**
 * \brief ���˯��ģʽ����
 *
 * \param[in] stata : AM_TRUE  ��ִ�� WFI����������ߣ�����Deepsleepģʽ
 *                    AM_FALSE ��ִ�� WFI�������ߣ�����sleep/Idleģʽ
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpmode_sleepdeep (am_bool_t stata)
{
    LPMODECTRL->cr = (LPMODECTRL->cr & (~(1ul << 2))) |
                     (stata << 2);
}

/**
 * \brief �Զ�����˯��ģʽ����
 *
 * \param[in] stata : AM_TRUE  �����˳��쳣�������س����߳�ʱ���Զ���������ģʽ
 *                    AM_FALSE ��ִ�� WFIָ���������ģʽ
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpmode_sleeponexit (am_bool_t stata)
{
    LPMODECTRL->cr = (LPMODECTRL->cr & (~(1ul << 1))) |
                     (stata << 1);
}

/**
 * \brief WFIָ���
 *
 * \param[in] none
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpmode_wfi (void)
{
#ifdef __CC_ARM
    __ASM("WFI");
#endif

#ifdef __GNUC__
    __WFI();
#endif
}

/**
 * \brief WFEָ���
 *
 * \param[in] none
 *
 * \return none
 */
am_static_inline
void amhw_zsn700_lpmode_wfe (void)
{
#ifdef __CC_ARM
    __ASM("WFE");
#endif

#ifdef __GNUC__
    __WFE();
#endif
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

#endif /* __AMHW_ZSN700_LPMODE_H */

/* end of file */
