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
 * \brief DCU����������DCU��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-27
 * \endinternal
 */
#ifndef __AM_HC32_DCU_H
#define __AM_HC32_DCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"



/**
 * \addtogroup am_hc32f460_if_dcu
 * \copydoc am_hc32f460_dcu.h
 * @{
 */
/**
 * \brief dcu�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f460_dcu_info {

    uint32_t    reg_base;  /**< \brief DCU�Ĵ��������ַ */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
} am_hc32f460_dcu_devinfo_t;

/**
 * \brief DCU�豸ʵ��
 */
typedef struct am_hc32f460_dcu_dev {

    /** \brief ָ��DCU�豸��Ϣ��ָ�� */
    const am_hc32f460_dcu_devinfo_t *p_devinfo;

} am_hc32f460_dcu_dev_t;

/** \brief dcu��׼�������������Ͷ��� */
typedef am_hc32f460_dcu_dev_t *am_dcu_handle_t;

/**
 * \brief DCU ��ʼ��
 *
 * \param[in] p_dev     :DCU�豸��ʼ��ʵ��
 * \param[in] p_devinfo :DCU�豸��Ϣ��ʼ��ʵ��
 *
 * \retval :��
 *
 */
am_aes_handle_t am_hc32f460_dcu_init(am_hc32f460_dcu_dev_t           *p_dev,
                                     const am_hc32f460_dcu_devinfo_t *p_devinfo);

/**
 * \brief DCU ȥʼ��
 *
 * \param[in] handle     :AES��׼�豸������
 *
 * \retval :��
 *
 */
void am_hc32f460_dcu_deinit (am_dcu_handle_t handle);



/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_DCU_H */

/* end of file */
