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
 * \brief WWDG�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  sdy, first implementation
 * \endinternal
 */

#ifndef __AMHW_HK32F103RBT6_WWDG_H
#define __AMHW_HK32F103RBT6_WWDG_H

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
 * \addtogroup amhw_hk32f103rbt6_if_wwdg
 * \copydoc amhw_hk32f103rbt6_wwdg.h
 * @{
 */

/**
 * \brief WWDG�Ĵ�����ṹ��
 */
typedef struct amhw_hk32f103rbt6_wwdg {
    __IO uint32_t cr;    /**< \brief ���ƼĴ��� */
    __IO uint32_t cfr;   /**< \brief ���üĴ��� */
    __IO uint32_t sr;    /**< \brief ״̬�Ĵ��� */
} amhw_hk32f103rbt6_wwdg_t;

#ifndef AMHW_HK32F103RBT6_WWDG
#define AMHW_HK32F103RBT6_WWDG  ((amhw_hk32f103rbt6_wwdg_t *)0x40002C00UL) /**< \brief �������ַ */
#endif

/**
 * \brief д����ֵ
 *
 * \param[in] p_hw_wwdg : ָ��WWDG�Ĵ������ָ��
 * \param[in] count     : ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_wwdg_counter_set (amhw_hk32f103rbt6_wwdg_t *p_hw_wwdg,
                                   uint8_t             count)
{
    p_hw_wwdg->cr = (p_hw_wwdg->cr & ~0x7ful) |
                    (count & 0x7ful);
}

/**
 * \brief ʹ�ܴ��ڿ��Ź�
 *
 * \param[in] p_hw_wwdg : ָ��WWDG�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_wwdg_enable (amhw_hk32f103rbt6_wwdg_t *p_hw_wwdg)
{
    p_hw_wwdg->cr |= (1ul << 7);
}

/**
 * \brief д����ֵ
 *
 * \param[in] p_hw_wwdg : ָ��WWDG�Ĵ������ָ��
 * \param[in] key       : ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_wwdg_winvalue_set (amhw_hk32f103rbt6_wwdg_t    *p_hw_wwdg,
                                 uint8_t             key)
{
    p_hw_wwdg->cfr = (p_hw_wwdg->cfr & ~0x7ful) |
                     (key & 0x7ful);
}

/**
 * \brief дʱ��ֵ
 *
 * \param[in] p_hw_wwdg : ָ��WWDG�Ĵ������ָ��
 * \param[in] val       : ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_wwdg_timerbase_set (amhw_hk32f103rbt6_wwdg_t    *p_hw_wwdg,
                                  uint8_t             val)
{
    p_hw_wwdg->cfr = (p_hw_wwdg->cfr & ~(0x3ul << 7)) |
                     ((val & 0x3ul) << 7);
}

/**
 * \brief ��ǰ�����ж�
 *
 * \param[in] p_hw_wwdg : ָ��WWDG�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_wwdg_ewi_set (amhw_hk32f103rbt6_wwdg_t *p_hw_wwdg)
{
    p_hw_wwdg->cfr |= (1ul << 9);
}

/**
 * \brief ��ǰ�����жϱ�־��ȡ
 *
 * \param[in] p_hw_wwdg : ָ��WWDG�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
am_bool_t amhw_hk32f103rbt6_wwdg_ewif_read (amhw_hk32f103rbt6_wwdg_t *p_hw_wwdg)
{
    return (am_bool_t)((p_hw_wwdg->sr & 1ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ��ǰ�����жϱ�־���
 *
 * \param[in] p_hw_wwdg : ָ��WWDG�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_wwdg_ewif_clear (amhw_hk32f103rbt6_wwdg_t *p_hw_wwdg)
{
    p_hw_wwdg->sr &= ~1ul;
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

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
#endif /* __AMHW_HK32F103RBT6_WWDG_H */

#endif

/* end of file */
