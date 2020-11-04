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
 * \brief HASH �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 20-05-22
 * \endinternal
 */

#ifndef __AMHW_HC32F460_HASH_H
#define __AMHW_HC32F460_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_hc32f460_if_hash
 * \copydoc amhw_hc32f460_hash.h
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
 * \brief HASH - �Ĵ�����
 */

/**
 * \brief HASH���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t START                     : 1;  /**< \brief ����*/
    __IO uint32_t FST_GRP                   : 1;  /**< \brief ��Ϣ����ĵ�һ��*/
    uint32_t RESERVED2                      :30;  /**< \brief ���� */
} stc_hash_cr_field_t;

typedef struct amhw_hc32f460_hash{
    union
    {
        __IO uint32_t CR;         /**< \brief HASH���ƼĴ��� */
        stc_hash_cr_field_t CR_f;
    };
    uint8_t RESERVED1[12];        /**< \brief ���� */
    __IO uint32_t HR[8];          /**< \brief HASHժҪ�Ĵ��� */
    uint8_t RESERVED9[16];        /**< \brief ���� */
    __IO uint32_t DR[16];         /**< \brief HASH���ݼĴ��� */
} amhw_hc32f460_hash_t;

/* �����������ֽ��� */
#define AMHW_HC32F460_HASH_MAX_GROUP_SIZE    64
/* ���һ���������ֽ�����ʣ��8���ֽڴ洢ԭʼ����bit�� */
#define AMHW_HC32F460_HASH_LAST_GROUP_SIZE   56

/**
 * \brief ������������Ϊ��Ϣ����ĵ�һ������
 *
 * \param[in] p_hw_aes : ָ��HASH�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_hash_first_group (amhw_hc32f460_hash_t *p_hw_hash)
{
	p_hw_hash->CR |= (1 << 1);
}

/**
 * \brief ���������㲻��Ϊ��Ϣ����ĵ�һ������
 *
 * \param[in] p_hw_aes : ָ��HASH�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_hash_not_first_group (amhw_hc32f460_hash_t *p_hw_hash)
{
	p_hw_hash->CR &= ~(1 << 1);
}

/**
 * \brief HASH ��������
 *
 * \param[in] p_hw_aes : ָ��HASH�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_hash_start (amhw_hc32f460_hash_t *p_hw_hash)
{
	p_hw_hash->CR |= (1 << 0);
}

/**
 * \brief HASH ״̬���
 *
 * \param[in] p_hw_aes : ָ��HASH�Ĵ��������ַָ��
 *
 * \retval : AM_TRUE(���������)/ AM_FALSE(���������δ����)
 */
am_static_inline
am_bool_t amhw_hc32f460_hash_status_check (amhw_hc32f460_hash_t *p_hw_hash)
{
    return (p_hw_hash->CR & (1 << 0)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief HASH ��ȡժҪ(�͵�ַ��Ӧ��32λ�Ĵ��������ϢժҪ�ĸ���)
 *
 * \param[in] p_hw_hash : ָ��HASH�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_hash_read (amhw_hc32f460_hash_t *p_hw_hash, uint8_t *p_data)
{
    uint32_t i,j = 0;
    uint32_t temp = 0;
    for (i = 0; i < 8; i++){
        j = i * 4 + 3;
        temp = p_hw_hash->HR[i];

        p_data[j] = (uint8_t)temp;
        p_data[j - 1] = (uint8_t)(temp >> 8);
        p_data[j - 2] = (uint8_t)(temp >> 16);
        p_data[j - 3] = (uint8_t)(temp >> 24);
    }
}

/**
 * \brief HASH д����(�͵�ַ��Ӧ��32λ�Ĵ���������ݵĸ���)
 *
 * \param[in] p_hw_hash : ָ��HASH�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_hash_data_write (amhw_hc32f460_hash_t *p_hw_hash, uint8_t *p_data)
{
    uint32_t temp = 0;

    int i,j = 0;
    for (i = 0; i < 16; i++){
        j = i * 4 + 3;
        temp = (uint32_t)p_data[j];
        temp |= ((uint32_t)p_data[j - 1] << 8);
        temp |= ((uint32_t)p_data[j - 2] << 16);
        temp |= ((uint32_t)p_data[j - 3] << 24);

        p_hw_hash->DR[i] = temp;
    }
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
 * @} amhw_if_hc32f460_hash
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_HASH_H */

/* end of file */
