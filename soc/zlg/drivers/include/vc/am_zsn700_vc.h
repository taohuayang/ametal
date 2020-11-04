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
 * \brief VC����������VC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-09
 * \endinternal
 */
#ifndef __AM_ZSN700_VC_H
#define __AM_ZSN700_VC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_zsn700_vc.h"

/**
 * \addtogroup am_zsn700_if_vc
 * \copydoc am_zsn700_vc.h
 * @{
 */

/**
 * \brief VC�豸��Ϣ�ṹ��
 */
typedef struct am_zsn700_vc_info {

    uint32_t    vc_reg_base;  /** \brief vc�Ĵ��������ַ */

    uint8_t     vc_inum;      /**< \brief vc�жϱ�� */

    uint32_t    vc_chan;      /**< \brief vcͨ�� ѡ��*/

    uint32_t    vc_vref;      /**< \brief vc�ο� ѡ��*/

    uint32_t    vc_delay;     /**< \brief vc����ʱ�� ѡ��*/

    uint32_t    vc_bias;      /**< \brief vc���� ѡ��*/

    uint32_t    vc_flt_time;  /**< \brief vc�˲�ʱ�� ѡ�� �粻ʹ���˲���ΪNULL*/

    uint32_t    vc_p_in;      /**< \brief vc p������ ѡ��*/

    uint32_t    vc_n_in;      /**< \brief vc n������ ѡ��*/

    uint32_t    vc_out_cfg;   /**< \brief vc �������*/

    uint32_t    vc_out_int;   /**< \brief vc ��������ж�����ѡ��*/

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

}am_zsn700_vc_devinfo_t;

/**
 * \brief VC�豸ʵ��
 */
typedef struct am_zsn700_vc_dev {

    /** \brief ָ��VC�豸��Ϣ��ָ�� */
    const am_zsn700_vc_devinfo_t *p_devinfo;

    /** \brief ��ǰת����ͨ�� */
    uint32_t                      chan;

    /** \brief �жϴ����ص� ����*/
    void (*pfn_trigger_cb)(void *);

} am_zsn700_vc_dev_t;

/** \brief vc��׼�������������Ͷ��� */
typedef am_zsn700_vc_dev_t *am_vc_handle_t;

/**
 * \brief VC��ʼ��
 *
 * \param[in] p_dev��VC�豸ʵ��
 * \param[in] p_devinfo ��VC�豸��Ϣʵ��
 *
 * \retval ��׼vc������
 */
am_vc_handle_t am_zsn700_vc_init (am_zsn700_vc_dev_t           *p_dev,
                                  const am_zsn700_vc_devinfo_t *p_devinfo);

/**
 * \brief DACȥ��ʼ��
 *
 * \param[in] handle ��׼vc������
 */
void am_zsn700_vc_deinit (am_vc_handle_t handle);

/**
 * \brief �жϴ�����������
 *
 * \param[in] vc_handle : ��׼VC������
 * \param[in] pfn_tri_cb : �û�������жϴ����ص�����
 *
 * \retval AM_ERROR ����ʧ��
 * \retval AM_ERROR ���ӳɹ�
 *
 */
int am_zsn700_tri_set (am_vc_handle_t vc_handle, void (*pfn_tri_cb) (void *));

/**
 * \brief VCͨ��ʹ��
 *
 * \param[in] vc_handle : ��׼VC������
 *
 * \retval AM_ERROR ʹ��ʧ��
 * \retval AM_ERROR ʹ�ܳɹ�
 */
int am_zsn700_vc_chan_enable (am_vc_handle_t vc_handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_VC_H */

/* end of file */
