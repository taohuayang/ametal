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
 * \brief SWDT�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-11
 * \endinternal
 */

#ifndef __AMHW_HC32F460_SWDT_H
#define __AMHW_HC32F460_SWDT_H

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
 * \addtogroup amhw_hc32f460_if_swdt
 * \copydoc amhw_hc32f460_swdt.h
 * @{
 */

/**
 * \brief SWDT ״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CNT                       :16;  /**< \brief ����ֵ*/
    __IO uint32_t UDF                       : 1;  /**< \brief ���������־*/
    __IO uint32_t REF                       : 1;  /**< \brief ˢ�´����־*/
    uint32_t RESERVED18                     :14;  /**< \brief ����*/
} stc_swdt_sr_field_t;

/**
 * \brief SWDT ˢ�¼Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t RF                        :16;  /**< \brief ˢ��ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_swdt_rr_field_t;

/**
 * \brief SWDT�Ĵ�����ṹ��
 */
typedef struct
{
    uint8_t RESERVED0[4];        /**< \brief ����*/
    union
    {
        __IO uint32_t SR;        /**< \brief ״̬�Ĵ���*/
        stc_swdt_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t RR;        /**< \brief ˢ�¼Ĵ���*/
        stc_swdt_rr_field_t RR_f;
    };
}amhw_hc32f460_swdt_t;


/**
 * \brief ��ȡ��������ǰ����ֵ
 *
 * \param[in] p_hw_swdt : ָ��WDT�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
uint16_t amhw_hc32f460_swdt_count_value_get (amhw_hc32f460_swdt_t  *p_hw_swdt)
{
    return p_hw_swdt->SR_f.CNT;
}

typedef enum {
    AMHW_HC32F460_SWDT_STATUS_REF   = 1 << 17,   /**< \brief ˢ�´����־ */
    AMHW_HC32F460_SWDT_STATUS_UDF   = 1 << 16,   /**< \brief ���������־ */
} amhw_hc32f460_swdt_status_flag_t;

/**
 * \brief ��ȡ���Ź�״̬
 *
 * \param[in] p_hw_swdt : ָ��WDT�Ĵ������ָ��
 * \param[in] flag     : ״̬��־
 *
 * \return ��
 */
am_static_inline
am_bool_t amhw_hc32f460_swdt_status_get (amhw_hc32f460_swdt_t             *p_hw_swdt,
                                         amhw_hc32f460_swdt_status_flag_t  flag)
{
    return (p_hw_swdt->SR & flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ������Ź�״̬
 *
 * \param[in] p_hw_swdt : ָ��WDT�Ĵ������ָ��
 * \param[in] flag     : ״̬��־
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_swdt_status_clr (amhw_hc32f460_swdt_t             *p_hw_swdt,
                                    amhw_hc32f460_swdt_status_flag_t  flag)
{
    p_hw_swdt->SR &= ~flag;
}

typedef enum {
    AMHW_HC32F460_SWDT_REFRESH_START = 0x0123, /**< \brief ˢ�¼�����Ҫд��ĵ�һ��ֵ */
    AMHW_HC32F460_SWDT_REFRESH_END   = 0x3210, /**< \brief ˢ�¼�����Ҫд��ĵڶ���ֵ */
} amhw_hc32f460_swdt_refresh_set_t;

/**
 * \brief ˢ�¿��Ź�������
 *
 * \param[in] p_hw_swdt : ָ��WDT�Ĵ������ָ��
 * \param[in] flag      : ˢ�¼�����Ҫд����ض�ֵ��amhw_hc32f460_swdt_refresh_set_t��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_swdt_refresh_set (amhw_hc32f460_swdt_t             *p_hw_swdt,
                                     amhw_hc32f460_swdt_refresh_set_t  flag)
{
    p_hw_swdt->RR_f.RF = flag;
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
#endif /* __AMHW_HC32F460_WDT_H */

#endif

/* end of file */
