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
 * \brief AES �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 20-05-22
 * \endinternal
 */

#ifndef __AMHW_HC32F460_AES_H
#define __AMHW_HC32F460_AES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_hc32f460_if_aes
 * \copydoc amhw_hc32f460_aes.h
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
 * \brief AES - �Ĵ�����
 */

/**
 * \brief AES���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t START                     : 1;  /** <brief ���� */
    __IO uint32_t MODE                      : 1;  /** <brief ����ѡ�� */
    uint32_t RESERVED2                      :30;  /** <brief ���� */
} stc_aes_cr_field_t;

typedef struct amhw_hc32f460_aes {
    union
    {
        __IO uint32_t CR;       /** <brief AES���ƼĴ��� */
        stc_aes_cr_field_t CR_f;
    };
    uint8_t RESERVED1[12];      /** <brief ���� */
    __IO uint32_t DR[4];        /** <brief AES���ݼĴ��� */
    __IO uint32_t KR[4];        /** <brief AES��Կ�Ĵ��� */
} amhw_hc32f460_aes_t;



/**
 * \brief AES ��������
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_aes_encrypt (amhw_hc32f460_aes_t *p_hw_aes)
{
    p_hw_aes->CR &= ~(1 << 1);
}

/**
 * \brief AES ��������
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_aes_decrypt (amhw_hc32f460_aes_t *p_hw_aes)
{
    p_hw_aes->CR |= (1 << 1);
}

/**
 * \brief AES ģ����������
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_aes_start (amhw_hc32f460_aes_t *p_hw_aes)
{
    p_hw_aes->CR |= (1 << 0);
}

/**
 * \brief AES ģ��״̬��ѯ
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
int amhw_hc32f460_aes_stu_check (amhw_hc32f460_aes_t *p_hw_aes)
{
    return (p_hw_aes->CR & (1 << 0));
}

/**
 * \brief AES ���ġ��������ݴ��
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \note1 :���ݼĴ������ĸ� 32λ�ļĴ������ 128λ���ݣ�������ģ������ǰ�����Ҫ�� λ���ݣ�
 *         ������ģ������ǰ�����Ҫ�� ���� �����Ļ�����Ҫ���⣬����������ɺ��ż��� ������
 *         ����Ҫ���⣬����������ɺ��ż��� �����Ļ�����Ҫ���⣬����������ɺ��ż��� ��
 *         ���Ļ�����Ҫ���⣬����������ɺ��ż��ܺ�����Ļ��߽��ܺ�����ġ�
 *
 * \note2 : ���ڱ��Ĵ�����д��ֻ����ģ��û �д�������״̬ʱ,����Ӳ�����Զ����Ըò�����
 *          ���ڱ��Ĵ����Ķ�ȡֻ����ģ��û�д�����״̬ʱ ���ܽ��У�����Ա��Ĵ����Ķ�ȡ���õ�ȫ 0��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_aes_data_write (amhw_hc32f460_aes_t *p_hw_aes, uint32_t *p_data)
{
    int i = 0;
    for (i = 0; i < 4; i++){
        p_hw_aes->DR[i] = p_data[i];
    }
}

/**
 * \brief AES ���ġ��������ݶ�ȡ
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \note1 :���ݼĴ������ĸ� 32λ�ļĴ������ 128λ���ݣ�������ģ������ǰ�����Ҫ�� λ���ݣ�
 *         ������ģ������ǰ�����Ҫ�� ���� �����Ļ�����Ҫ���⣬����������ɺ��ż��� ������
 *         ����Ҫ���⣬����������ɺ��ż��� �����Ļ�����Ҫ���⣬����������ɺ��ż��� ��
 *         ���Ļ�����Ҫ���⣬����������ɺ��ż��ܺ�����Ļ��߽��ܺ�����ġ�
 *
 * \note2 : ���ڱ��Ĵ�����д��ֻ����ģ��û �д�������״̬ʱ,����Ӳ�����Զ����Ըò�����
 *          ���ڱ��Ĵ����Ķ�ȡֻ����ģ��û�д�����״̬ʱ ���ܽ��У�����Ա��Ĵ����Ķ�ȡ���õ�ȫ 0��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_aes_data_read (amhw_hc32f460_aes_t *p_hw_aes,
                                  uint32_t          *p_data)
{
    int i = 0;

    for (i = 0; i < 4; i++){

        p_data[i] = p_hw_aes->DR[i];
    }
}

/**
 * \brief AES ��Կ���
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 * \param[in] flag     : ��Կ���ȣ��ο��궨�壺AES ��Կ��������
 * \param[in] p_data   : ��Կ���ݣ�ֻ֧��128λ��
 *
 * \note1 :���ݼĴ������ĸ� 32λ�ļĴ������ 128λ���ݣ�������ģ������ǰ�����Ҫ�� λ���ݣ�
 *         ������ģ������ǰ�����Ҫ�� ���� �����Ļ�����Ҫ���⣬����������ɺ��ż��� ������
 *         ����Ҫ���⣬����������ɺ��ż��� �����Ļ�����Ҫ���⣬����������ɺ��ż��� ��
 *         ���Ļ�����Ҫ���⣬����������ɺ��ż��ܺ�����Ļ��߽��ܺ�����ġ�
 *
 * \note2 : ���ڱ��Ĵ�����д��ֻ����ģ��û �д�������״̬ʱ,����Ӳ�����Զ����Ըò�����
 *          ���ڱ��Ĵ����Ķ�ȡֻ����ģ��û�д�����״̬ʱ ���ܽ��У�����Ա��Ĵ����Ķ�ȡ���õ�ȫ 0��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_aes_key_save (amhw_hc32f460_aes_t *p_hw_aes,
                                 uint32_t            *p_data)
{
    int i = 0;

    for (i = 0; i < 4; i++){
        p_hw_aes->KR[i] = p_data[i];
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
 * @} amhw_if_hc32f460_aes
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_AES_H */

/* end of file */
