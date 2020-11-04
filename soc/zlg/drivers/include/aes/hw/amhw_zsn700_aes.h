/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
*******************************************************************************/

/**
 * \file
 * \brief AES �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 20-03-10
 * \endinternal
 */

#ifndef __AMHW_ZSN700_AES_H
#define __AMHW_ZSN700_AES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zsn700_if_aes
 * \copydoc amhw_zsn700_aes.h
 * @{
 */

/**
 * \brief AES - �Ĵ�����
 */
typedef struct amhw_zsn700_aes {
    __IO uint32_t  aescr;         /**< \brief  AES ���ƼĴ��� */
         uint32_t  res1[3];       /**< \brief  ���� */
    __IO uint32_t  aesdat[4];     /**< \brief  AES ���ݼĴ��� */
    __IO uint32_t  aeskey[8];     /**< \brief  AES ��Կ�Ĵ��� */
} amhw_zsn700_aes_t;

/**
 * \brief AES ��Կ��������
 */
#define  AMHW_ZSN700_AES_KEY_LEN_128_BIT    (0U)
#define  AMHW_ZSN700_AES_KEY_LEN_192_BIT    (1U)
#define  AMHW_ZSN700_AES_KEY_LEN_256_BIT    (2U)

/**
 * \brief AES ��Կ��������
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 * \param[in] flag     : ��Կ���ȣ��ο��궨�壺AES ��Կ��������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsn700_aes_key_len_sel (amhw_zsn700_aes_t *p_hw_aes, uint32_t flag)
{
    p_hw_aes->aescr = (p_hw_aes->aescr & (~(0x3 << 3))) | (flag << 3);
}

/**
 * \brief AES ��������
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsn700_aes_encrypt (amhw_zsn700_aes_t *p_hw_aes)
{
    p_hw_aes->aescr &= ~(1 << 1);
}

/**
 * \brief AES ��������
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsn700_aes_decrypt (amhw_zsn700_aes_t *p_hw_aes)
{
    p_hw_aes->aescr |= (1 << 1);
}

/**
 * \brief AES ģ����������
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsn700_aes_start (amhw_zsn700_aes_t *p_hw_aes)
{
    p_hw_aes->aescr |= (1 << 0);
}

/**
 * \brief AES ģ��״̬��ѯ
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
int amhw_zsn700_aes_stu_check (amhw_zsn700_aes_t *p_hw_aes)
{
    return (p_hw_aes->aescr & (1 << 0));
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
void amhw_zsn700_aes_data_write (amhw_zsn700_aes_t *p_hw_aes, uint32_t *p_data)
{
    int i = 0;
    for (i = 0; i < 4; i++){
        p_hw_aes->aesdat[i] = (p_hw_aes->aesdat[i] & ~(0xffff)) | p_data[i];
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
void amhw_zsn700_aes_data_read (amhw_zsn700_aes_t *p_hw_aes,
                                uint32_t          *p_data)
{
    int i = 0;

    for (i = 0; i < 4; i++){

        p_data[i] = p_hw_aes->aesdat[i];
    }
}

/**
 * \brief AES ��Կ���
 *
 * \param[in] p_hw_aes : ָ��AES�Ĵ��������ַָ��
 * \param[in] flag     : ��Կ���ȣ��ο��궨�壺AES ��Կ��������
 * \param[in] p_data   : ��Կ���ݣ�ֻ֧��128λ��192λ��256λ��
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
void amhw_zsn700_aes_key_save (amhw_zsn700_aes_t *p_hw_aes,
                               uint32_t           flag,
                               uint32_t          *p_data)
{
    int i = 0;

    switch (flag){

        case AMHW_ZSN700_AES_KEY_LEN_128_BIT:
            for (i = 0; i < 4; i++){
                p_hw_aes->aeskey[i] = (p_hw_aes->aeskey[i] & ~(0xffff)) | p_data[i];
            }
            break;
        case AMHW_ZSN700_AES_KEY_LEN_192_BIT:
            for (i = 0; i < 6; i++){
                p_hw_aes->aeskey[i] = (p_hw_aes->aeskey[i] & ~(0xffff)) | p_data[i];
            }
            break;
        case AMHW_ZSN700_AES_KEY_LEN_256_BIT:
            for (i = 0; i < 8; i++){
                p_hw_aes->aeskey[i] = (p_hw_aes->aeskey[i] & ~(0xffff)) | p_data[i];
            }
            break;
        default :
            ;
    }
}

/**
 * @} amhw_if_zsn700_aes
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZSN700_AES_H */

/* end of file */
