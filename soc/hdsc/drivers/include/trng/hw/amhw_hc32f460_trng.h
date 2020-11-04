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
 * \brief TRNG �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 20-05-26
 * \endinternal
 */

#ifndef __AMHW_HC32F460_TRNG_H
#define __AMHW_HC32F460_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_hc32f460_if_trng
 * \copydoc amhw_hc32f460_trng.h
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
 * \brief TRNG ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t EN                        : 1;  /**< \brief ģ�ⷢ����ʹ��*/
    __IO uint32_t RUN                       : 1;  /**< \brief ��������㿪ʼ*/
    uint32_t RESERVED2                      :30;  /**< \brief ����*/
} stc_trng_cr_field_t;

/**
 * \brief TRNG ģʽ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t LOAD                      : 1;  /**< \brief װ�ؿ���λ*/
    uint32_t RESERVED1                      : 1;  /**< \brief ����*/
    __IO uint32_t CNT                       : 3;  /**< \brief ��λ��������λ*/
    uint32_t RESERVED5                      :27;  /**< \brief ����*/
} stc_trng_mr_field_t;

typedef struct amhw_hc32f460_trng {
    union
    {
        __IO uint32_t CR;           /**< \brief TRNG���ƼĴ���*/
        stc_trng_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t MR;           /**< \brief TRNGģʽ�Ĵ���*/
        stc_trng_mr_field_t MR_f;
    };
    uint8_t RESERVED2[4];           /**< \brief ����*/
    __IO uint32_t DR0;              /**< \brief ���ݼĴ���0*/
    __IO uint32_t DR1;              /**< \brief ���ݼĴ���1*/
} amhw_hc32f460_trng_t;

/**
 * \brief TRNG �������������
 *
 * \note :Ӳ������
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_trng_run (amhw_hc32f460_trng_t *p_hw_trng)
{
    p_hw_trng->CR_f.RUN = 1;
}

/**
 * \brief TRNG ���������״̬��ȡ
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : AM_TRUE: ���ڲ�������� / AM_FASLE ������������
 */
am_static_inline
am_bool_t amhw_hc32f460_trng_stu_check (amhw_hc32f460_trng_t *p_hw_trng)
{
    return p_hw_trng->CR_f.RUN;
}

/**
 * \brief ���Դ��·ʹ��
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_trng_cir_enable (amhw_hc32f460_trng_t *p_hw_trng)
{
    p_hw_trng->CR_f.EN = 1;
}

/**
 * \brief ���Դ��·����
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_trng_cir_disable (amhw_hc32f460_trng_t *p_hw_trng)
{
	p_hw_trng->CR_f.EN = 0;
}

/**
 * \brief RNG ��������λ����
 */
typedef enum amhw_hc32f460_trng_cnt {
    AMHW_HC32F460_TRNG_CNT_32  = 3u,
    AMHW_HC32F460_TRNG_CNT_64  = 4u,
    AMHW_HC32F460_TRNG_CNT_128 = 5u,
    AMHW_HC32F460_TRNG_CNT_256 = 6u,
}amhw_hc32f460_trng_cnt_t;

/**
 * \brief RNG������λ����ѡ��
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 * \param[in] flag      : ������λ�������ο�ö�ٶ��壺RNG ��������λ����
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_trng_cnt_sel (amhw_hc32f460_trng_t *p_hw_trng ,uint32_t flag)
{
    p_hw_trng->MR_f.CNT = flag;
}


/**
 * \brief �ڲ����µ������ʱ��64bits RNG�Ƿ�����Դ����µĳ�ʼֵ
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 * \param[in] flag      : �Ƿ��������ñ�־ ��AM_TRUE��,AM_FALSE��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_trng_load_set (amhw_hc32f460_trng_t *p_hw_trng,
                                  am_bool_t             flag)
{
    p_hw_trng->MR_f.LOAD = flag;
}

/**
 * \brief TRNG ��ȡ��32λ�����
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��32Ϊ�����
 */
am_static_inline
uint32_t amhw_hc32f460_trng_low32_data_read (amhw_hc32f460_trng_t *p_hw_trng)
{
    return (p_hw_trng->DR0);
}

/**
 * \brief TRNG ��ȡ��32λ�����
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��32Ϊ�����
 */
am_static_inline
uint32_t amhw_hc32f460_trng_high32_data_read (amhw_hc32f460_trng_t *p_hw_trng)
{
    return (p_hw_trng->DR1);
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
 * @} amhw_if_hc32f460_trng
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_TRNG_H */

/* end of file */
