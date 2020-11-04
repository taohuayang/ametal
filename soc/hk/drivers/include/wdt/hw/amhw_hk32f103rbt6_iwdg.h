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
 * \brief IWDG�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  sdy, first implementation
 * \endinternal
 */

#ifndef __AMHW_HK32F103RBT6_IWDG_H
#define __AMHW_HK32F103RBT6_IWDG_H

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
 * \addtogroup amhw_hk32f103rbt6_if_iwdg
 * \copydoc amhw_hk32f103rbt6_iwdg.h
 * @{
 */

/**
 * \brief IWDG�Ĵ�����ṹ��
 */
typedef struct amhw_hk32f103rbt6_iwdg {
    __IO uint32_t kr;  /**< \brief ���Ĵ��� */
    __IO uint32_t pr;  /**< \brief Ԥ��Ƶ�Ĵ��� */
    __IO uint32_t rlr; /**< \brief ��װ�ؼĴ��� */
    __IO uint32_t sr;  /**< \brief ״̬�Ĵ��� */
} amhw_hk32f103rbt6_iwdg_t;

/**
 * \brief д��ֵ
 *
 * \param[in] p_hw_iwdg : ָ��IWDG�Ĵ������ָ��
 * \param[in] key       : ��ֵ
 *
 *      - 0x5555 ��������� IWDG_PR �� IWDG_RLR �Ĵ���
 *      - 0xAAAA ��ι��
 *      - 0xCCCC ���������Ź�����
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_iwdg_keyvalue_set (amhw_hk32f103rbt6_iwdg_t    *p_hw_iwdg,
                                 uint16_t            key)
{
    p_hw_iwdg->kr = key;
}

/**
 * \brief ����Ԥ��Ƶֵ
 *
 * \param[in] p_hw_iwdg : ָ��IWDG�Ĵ������ָ��
 * \param[in] div       : ��Ƶֵ
 *
 *      - 0 ��Ԥ��Ƶ����  = 4
 *      - 1 ��Ԥ��Ƶ����  = 8
 *      - 2 ��Ԥ��Ƶ����  = 16
 *      - 3 ��Ԥ��Ƶ����  = 32
 *      - 4 ��Ԥ��Ƶ����  = 64
 *      - 5 ��Ԥ��Ƶ����  = 128
 *      - 6 ��Ԥ��Ƶ����  = 256
 *      - 7 ��Ԥ��Ƶ����  = 256
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_iwdg_div_set (amhw_hk32f103rbt6_iwdg_t    *p_hw_iwdg,
                            uint8_t             div)
{
    p_hw_iwdg->pr = (div & 0x7ul);
}

/**
 * \brief ��������װֵ
 *
 * \param[in] p_hw_iwdg : ָ��IWDG�Ĵ������ָ��
 * \param[in] val       : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_hk32f103rbt6_iwdg_reload_set (amhw_hk32f103rbt6_iwdg_t    *p_hw_iwdg,
                               uint16_t            val)
{
    p_hw_iwdg->rlr = (val & 0xffful);
}

/**
 * \brief ���Ź�״̬����
 *
 * \param[in] p_hw_iwdg : ָ��IWDG�Ĵ������ָ��
 *
 * \return ״ֵ̬������״̬�ǻ�Ĺ�ϵ��
 *
 *        - 0 �� ��״̬
 *        - 1 �� ���Ź�Ԥ��Ƶ����
 *        - 2 �� ���Ź���������װ��ֵ����
 */
am_static_inline
uint8_t amhw_hk32f103rbt6_iwdg_status_get (amhw_hk32f103rbt6_iwdg_t *p_hw_iwdg)
{
   return (uint8_t)(p_hw_iwdg->sr & 0x3);
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
#endif /* __AMHW_HK32F103RBT6_IWDG_H */

#endif

/* end of file */
