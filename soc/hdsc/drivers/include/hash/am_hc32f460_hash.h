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
 * \brief HASH����������HASH��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-22
 * \endinternal
 */
#ifndef __AM_HC32F460_HASH_H
#define __AM_HC32F460_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"



/**
 * \addtogroup am_hc32f460_if_hash
 * \copydoc am_hc32f460_hash.h
 * @{
 */
/**
 * \brief aes�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f460_hash_info {

    uint32_t    reg_base;  /**< \brief HASH�Ĵ��������ַ */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
}am_hc32f460_hash_devinfo_t;

/**
 * \brief HASH�豸ʵ��
 */
typedef struct am_hc32f460_hash_dev {

    /** \brief ָ��HASH�豸��Ϣ��ָ�� */
    const am_hc32f460_hash_devinfo_t *p_devinfo;

} am_hc32f460_hash_dev_t;

/** \brief hash��׼�������������Ͷ��� */
typedef am_hc32f460_hash_dev_t *am_hash_handle_t;

/**
 * \brief HASH ��ʼ��
 *
 * \param[in] p_dev     :HASH�豸��ʼ��ʵ��
 * \param[in] p_devinfo :HASH�豸��Ϣ��ʼ��ʵ��
 *
 * \retval :��
 *
 */
am_hash_handle_t am_hc32f460_hash_init(am_hc32f460_hash_dev_t           *p_dev,
                                       const am_hc32f460_hash_devinfo_t *p_devinfo);

/**
 * \brief HASH ȥʼ��
 *
 * \param[in] handle     :HASH��׼�豸������
 *
 * \retval :��
 *
 */
void am_hc32f460_hash_deinit (am_hash_handle_t handle);

/**
 * \brief hash ����
 *
 * \param[in] : handle ��׼HASH������
 * \param[in] : p_hash_data ԭʼ��Ϣ
 * \param[in] : data_length ԭʼ��Ϣ����
 * \param[in] : p_hash_digest ��ż�������ϢժҪ�Ļ�����
 *
 * \retval : AM_ERROR ��������ɹ�
 *           AM_ERROR ��������ʧ��
 */
uint32_t am_hc32f460_hash_compute (am_hash_handle_t handle,
                                   uint8_t         *p_hash_data,
                                   uint32_t         data_length,
                                   uint8_t         *p_hash_digest);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_HASH_H */

/* end of file */
