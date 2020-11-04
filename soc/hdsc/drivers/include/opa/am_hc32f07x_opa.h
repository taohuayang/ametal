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
 * - 1.00 19-10-08
 * \endinternal
 */
#ifndef __AM_HC32_OPA_H
#define __AM_HC32_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \brief OPA����ģʽѡ��
 */
#define AM_HC32F07X_OPA0_4_GENERAL  0 /**< \brief ͨ��ģʽ */
#define AM_HC32F07X_OPA3_4_DAC      1 /**< \brief DAC����ģʽ */

/**
 * \addtogroup am_hc32f07x_if_opa
 * \copydoc am_hc32f07x_opa.h
 * @{
 */
	
/**
 * \brief OPA��Ӧͨ����Ϣ
 */
typedef struct {
    uint8_t chan_sel;                          /**< \brief ��Ӧ��OPA��� */
    uint32_t gpio;                         /**< \brief ��Ӧ��GPIO�ܽź� */
    uint32_t func;                         /**< \brief ��Ӧ��GPIO�������� */
    uint32_t dfunc;                        /**< \brief ��Ӧ��GPIO����Ĭ������ */
} am_hc32_opa_ioinfo_t;	
	
/**
 * \brief OPA�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f07x_opa_info {

    uint32_t    reg_base;  /**< \brief OPA�Ĵ��������ַ */
	
	  uint8_t     chan;

    uint8_t     clk_sel;   /**< \brief OPA�Զ�У׼����*/

    uint8_t     az_way;    /**< \brief OPAУ׼��ʽ */

    uint8_t     opa_mode;  /**< \brief OPA����ģʽ */
	
    am_hc32_opa_ioinfo_t  *p_ioinfo;
    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
}am_hc32f07x_opa_devinfo_t;

/**
 * \brief LVD�豸ʵ��
 */
typedef struct am_hc32f07x_opa_dev {

    /** \brief ָ��OPA�豸��Ϣ��ָ�� */
    const am_hc32f07x_opa_devinfo_t *p_devinfo;

} am_hc32f07x_opa_dev_t;

/** \brief opa��׼�������������Ͷ��� */
typedef am_hc32f07x_opa_dev_t *am_opa_handle_t;

/**
 * \brief OPA ��ʼ��
 *
 * \param[in] p_dev     :OPA�豸��ʼ��ʵ��
 * \param[in] p_devinfo :OPA�豸��Ϣ��ʼ��ʵ��
 *
 * \retval :��
 *
 */
am_opa_handle_t am_hc32f07x_opa_init(am_hc32f07x_opa_dev_t           *p_dev,
                                   const am_hc32f07x_opa_devinfo_t *p_devinfo);

/**
 * \brief OPA ȥʼ��
 *
 * \param[in] handle     :OPA��׼�豸������
 *
 * \retval :��
 *
 */
void am_hc32f07x_opa_deinit (am_opa_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_OPA_H */

/* end of file */
