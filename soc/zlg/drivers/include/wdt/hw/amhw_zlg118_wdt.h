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
 * \brief WDT�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10
 * \endinternal
 */

#ifndef __AMHW_ZLG118_WDT_H
#define __AMHW_ZLG118_WDT_H

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
 * \addtogroup amhw_zlg118_if_wdt
 * \copydoc amhw_zlg118_wdt.h
 * @{
 */

/**
 * \brief WDT�Ĵ�����ṹ��
 */
typedef struct amhw_zlg118_wdt {
    __O  uint32_t rst;  /**< \brief ������ƼĴ��� */
    __IO uint32_t con;  /**< \brief ���ƼĴ��� */
} amhw_zlg118_wdt_t;


/**
 * \brief ���Ź�����/�������
 *
 * \param[in] p_hw_wdt : ָ��WDT�Ĵ������ָ��
 * \param[in] count    : ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_wdt_rst_set (amhw_zlg118_wdt_t *p_hw_wdt,
                              uint8_t             count)
{
    p_hw_wdt->rst = count;
}

/**
 * \brief ���Ź��жϱ�־��ȡ
 *
 * \param[in] p_hw_wdt : ָ��WDT�Ĵ������ָ��
 *
 * \return 0��δ����WDT�ж�, 1���ѷ���WDT�ж�
 */
am_static_inline
uint8_t amhw_zlg118_rcc_int_get (amhw_zlg118_wdt_t *p_hw_wdt)
{
    return ((p_hw_wdt->con >> 7) & 1);
}

/**
 * \brief ���Ź������������
 *
 * \param[in] p_hw_wdt : ָ��WDT�Ĵ������ָ��
 * \param[in] en       : ������־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_wdt_en_set (amhw_zlg118_wdt_t *p_hw_wdt,
                             uint8_t            en)
{
    p_hw_wdt->con = (p_hw_wdt->con & ~(1 << 5)) | en;
}

/**
 * \brief ���Ź�����״̬��ȡ
 *
 * \param[in] p_hw_wdt : ָ��WDT�Ĵ������ָ��
 *
 * \return 0��WDTֹͣ, 1��WDT��������
 */
am_static_inline
uint8_t amhw_zlg118_wdt_stat_get (amhw_zlg118_wdt_t *p_hw_wdt)
{
    return ((p_hw_wdt->con >> 4) & 1);
}

/**
 * \brief ���Ź����ʱ������
 *
 * \param[in] p_hw_wdt : ָ��WDT�Ĵ������ָ��
 * \param[in] time     : ���ʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_wdt_wov_set (amhw_zlg118_wdt_t *p_hw_wdt,
                              uint8_t            time)
{
    p_hw_wdt->con = (p_hw_wdt->con & ~0xf) | time;
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
#endif /* __AMHW_ZLG118_WDT_H */

#endif

/* end of file */
