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
 * \brief AES����������AES��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-22
 * \endinternal
 */
#ifndef __AM_HC32_AES_H
#define __AM_HC32_AES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"



/**
 * \addtogroup am_hc32f460_if_aes
 * \copydoc am_hc32f460_aes.h
 * @{
 */
/**
 * \brief aes�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f460_aes_info {

    uint32_t    reg_base;  /**< \brief AES�Ĵ��������ַ */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
}am_hc32f460_aes_devinfo_t;

/**
 * \brief AES�豸ʵ��
 */
typedef struct am_hc32f460_aes_dev {

    /** \brief ָ��AES�豸��Ϣ��ָ�� */
    const am_hc32f460_aes_devinfo_t *p_devinfo;

} am_hc32f460_aes_dev_t;

/** \brief aes��׼�������������Ͷ��� */
typedef am_hc32f460_aes_dev_t *am_aes_handle_t;

/**
 * \brief AES ��ʼ��
 *
 * \param[in] p_dev     :AES�豸��ʼ��ʵ��
 * \param[in] p_devinfo :AES�豸��Ϣ��ʼ��ʵ��
 *
 * \retval :��
 *
 */
am_aes_handle_t am_hc32f460_aes_init(am_hc32f460_aes_dev_t           *p_dev,
                                     const am_hc32f460_aes_devinfo_t *p_devinfo);

/**
 * \brief AES ȥʼ��
 *
 * \param[in] handle     :AES��׼�豸������
 *
 * \retval :��
 *
 */
void am_hc32f460_aes_deinit (am_aes_handle_t handle);

/**
 * \brief AES ����
 *
 * \param[in] : handle ��׼AES������
 * \param[in] : p_aes_data ��������
 * \param[in] : p_key_data ��Կ
 * \param[in] : p_ency_data �������ݻ�����
 *
 * \retval : AM_ERROR ��������ɹ�
 *           AM_ERROR ��������ʧ��
 */
uint32_t am_hc32f460_aes_encrypt (am_aes_handle_t handle,
                                  uint32_t       *p_aes_data,
                                  uint32_t       *p_key_data,
                                  uint32_t       *p_ency_data);

/**
 * \brief AES ����
 *
 * \param[in] : handle ��׼AES������
 * \param[in] : p_ency_data ��������
 * \param[in] : p_key_data ��Կ
 * \param[in] : p_decy_data �������ݻ�����
 *
 * \retval : AM_OK �����������
 *           AM_ERROR ��������ʧ��
 */
uint32_t am_hc32f460_aes_decrypt (am_aes_handle_t handle,
                                  uint32_t       *p_aes_data,
                                  uint32_t       *p_key_data,
                                  uint32_t       *p_decy_data);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_AES_H */

/* end of file */
