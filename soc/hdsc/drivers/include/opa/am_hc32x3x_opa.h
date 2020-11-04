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
 * \brief OPA����������OPA��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-13
 * \endinternal
 */
#ifndef __AM_HC32_OPA_H
#define __AM_HC32_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

#define  AM_HC32_OPA_CH1   (1U)
#define  AM_HC32_OPA_CH2   (2U)
#define  AM_HC32_OPA_CH3   (3U)

/**
 * \brief OPA����ģʽѡ��
 */
#define AM_HC32_OPA_MODE_UNITY_GAIN         (1U)    /**< \biref ��λ����ģʽ */
#define AM_HC32_OPA_MODE_FORWARD_IN         (2U)    /**< \biref ��������ģʽ */
#define AM_HC32_OPA_MODE_OPPOSITE           (3U)    /**< \biref ��������ģʽ */
#define AM_HC32_OPA_MODE_TWO_DIFF           (4U)    /**< \biref ������˷�ģʽ */
#define AM_HC32_OPA_MODE_UNIVERSAL          (5U)    /**< \biref ͨ��ģʽ */
#define AM_HC32_OPA_MODE_CAS_OPPO           (6U)    /**< \biref ��������ģʽ */
#define AM_HC32_OPA_MODE_CAS_FORWARD        (7U)    /**< \biref ��������ģʽ */


/**
 * \addtogroup am_hc32_if_opa
 * \copydoc am_hc32_opa.h
 * @{
 */
/**
 * \brief OPA�豸��Ϣ�ṹ��
 */
typedef struct am_hc32_opa_info {

    uint32_t    reg_base;  /**< \brief OPA�Ĵ��������ַ */

    uint8_t     opa_mode;  /**< \brief OPAģʽ */

    uint8_t     gain;      /**< \brief OPA����  */

    uint8_t     po;        /**< \brief IO�˿����ڲ����ӿ��� */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
}am_hc32_opa_devinfo_t;

/**
 * \brief OPA�豸ʵ��
 */
typedef struct am_hc32_opa_dev {

    /** \brief ָ��OPA�豸��Ϣ��ָ�� */
    const am_hc32_opa_devinfo_t *p_devinfo;

} am_hc32_opa_dev_t;

/** \brief opa��׼�������������Ͷ��� */
typedef am_hc32_opa_dev_t *am_opa_handle_t;

/**
 * \brief OPA ��ʼ��
 *
 * \param[in] p_dev     :OPA�豸��ʼ��ʵ��
 * \param[in] p_devinfo :OPA�豸��Ϣ��ʼ��ʵ��
 *
 * \retval :OPA��׼���
 *
 */
am_opa_handle_t am_hc32_opa_init(am_hc32_opa_dev_t           *p_dev,
                                 const am_hc32_opa_devinfo_t *p_devinfo);

/**
 * \brief OPA ȥʼ��
 *
 * \param[in] handle     :OPA��׼�豸������
 *
 * \retval :��
 *
 */
void am_hc32_opa_deinit (am_opa_handle_t handle);

/**
 * \brief OPA ʹ��
 *
 * \param[in] handle     :OPA��׼�豸������
 *
 * \retval :AM_OK     ʹ�ܳɹ�;
 *          -AM_ENXIO ���豸;
 */
error_t am_hc32_opa_enable (am_opa_handle_t handle);

/**
 * \brief OPA ģʽѡ��
 *
 * \param[in] handle     :OPA��׼�豸������
 * \param[in] ch         :OPAͨ��
 * \param[in] mode       :OPAģʽ
 *
 * \retval :AM_OK      ģʽ���óɹ�;
 *          -AM_ENXIO  ���豸;
 *          -AM_EINVAL ��Ч������
 */
error_t am_hc32_opa_mode_set (am_hc32_opa_dev_t  *p_dev,
                              uint8_t             ch);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_OPA_H */

/* end of file */
