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
 * \brief trng����������trng��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-26
 * \endinternal
 */
#ifndef __AM_HC32F460_trng_H
#define __AM_HC32F460_trng_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_hc32f460_if_trng
 * \copydoc am_hc32f460_trng.h
 * @{
 */

/**
 * \brief ��������ɻ���
 */
#define  AM_HC32F460_TRNG_LOAD_NEW_INIT_VALUE      1     /**< \brief ���������ǰ�����ݼĴ����������������װ���µĳ�ʼֵ */
#define  AM_HC32F460_TRNG_NOT_LOAD_NEW_INIT_VALUE  0     /**< \brief ���������ǰ�����ݼĴ������������������װ���µĳ�ʼֵ */

/**
 * \brief TRNG�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f460_trng_info {

    uint32_t    reg_base;  /**< \brief trng�Ĵ��������ַ */

    uint8_t     rng_cnt;   /**< \brief trng��λ���� */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

}am_hc32f460_trng_devinfo_t;

/**
 * \brief TRNG�豸ʵ��
 */
typedef struct am_hc32f460_trng_dev {

    /** \brief ָ��trng�豸��Ϣ��ָ�� */
    const am_hc32f460_trng_devinfo_t *p_devinfo;

} am_hc32f460_trng_dev_t;

/** \brief TRNG��׼�������������Ͷ��� */
typedef am_hc32f460_trng_dev_t *am_trng_handle_t;

/**
 * \brief trng ��ʼ��
 *
 * \param[in] p_dev     : trng �豸ʵ��
 * \param[in] p_devinfo : trng �豸��Ϣʵ��
 *
 * \retval : ��׼TRNG������
 *
 */
am_trng_handle_t am_hc32f460_trng_init (am_hc32f460_trng_dev_t           *p_dev,
                                        const am_hc32f460_trng_devinfo_t *p_devinfo);

/**
 * \brief TRNG ȥ��ʼ��
 *
 * \param[in] handle : ��׼TRNG������
 *
 * \retval : ��
 *
 */
void am_hc32f460_trng_deinit (am_trng_handle_t handle);

/**
 * \brief ���������
 *
 * \param[in] handle   : TRNG ��׼������
 * \param[in] env_flag : ������������� ���ϵ���������ϵ������
 * \param[in] p_data   : 64λ�����������
 *
 * \retval : AM_ERROR �������������
 *           AM_OK    ����������ɹ�
 */
int am_hc32f460_trng_generate (am_trng_handle_t handle,
                               uint8_t          env_flag,
                               uint32_t        *p_data);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_TRNG_H */

/* end of file */
