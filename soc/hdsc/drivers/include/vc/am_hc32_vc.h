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
 * - 1.01 20-04-27 zcb, Add callback function parameters
 * - 1.00 19-09-27
 * \endinternal
 */
#ifndef __AM_HC32_VC_H
#define __AM_HC32_VC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_hc32_vc.h"

/**
 * \addtogroup am_hc32_if_vc
 * \copydoc am_hc32_vc.h
 * @{
 */

/**
 * \brief VC�豸��Ϣ�ṹ��
 */
typedef struct am_hc32_vc_info {

    /** \brief VC �Ĵ��������ַ */
    uint32_t    vc_reg_base;

    /** \brief VC �жϱ�� */
    uint8_t     vc_inum;

    /** \brief VC ͨ�� ѡ��*/
    uint32_t    vc_chan;

    /** \brief VC �ο� ѡ��*/
    uint32_t    vc_vref;

    /** \brief VC ����ʱ�� ѡ��*/
    uint32_t    vc_delay;

    /** \brief VC ���� ѡ��*/
    uint32_t    vc_bias;

    /** \brief VC �˲�ʱ�� ѡ�� �粻ʹ���˲���ΪNULL*/
    uint32_t    vc_flt_time;

    /** \brief VC p������ ѡ��*/
    uint32_t    vc_p_in;

    /** \brief VC n������ ѡ��*/
    uint32_t    vc_n_in;

    /** \brief VC �������*/
    uint32_t    vc_out_cfg;

    /** \brief VC ��������ж�����ѡ��*/
    uint32_t    vc_out_int;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init) (void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit) (void);

}am_hc32_vc_devinfo_t;

/**
 * \brief VC�豸ʵ��
 */
typedef struct am_hc32_vc_dev {

    /** \brief ָ��VC�豸��Ϣ��ָ�� */
    const am_hc32_vc_devinfo_t *p_devinfo;

    /** \brief ��ǰת����ͨ�� */
    uint32_t                    chan;

    /** \brief �жϴ����ص� ���� */
    am_pfnvoid_t                pfn_trigger_cb;

    /** \brief �жϴ����ص� �������� */
    void                       *p_arg;

} am_hc32_vc_dev_t;

/** \brief VC ��׼�������������Ͷ��� */
typedef am_hc32_vc_dev_t *am_hc32_vc_handle_t;

/**
 * \brief VC ��ʼ��
 *
 * \param[in] p_dev     : VC�豸ʵ��
 * \param[in] p_devinfo : VC�豸��Ϣʵ��
 *
 * \retval ��׼VC������
 */
am_hc32_vc_handle_t am_hc32_vc_init (am_hc32_vc_dev_t           *p_dev,
                                     const am_hc32_vc_devinfo_t *p_devinfo);

/**
 * \brief VC ȥ��ʼ��
 *
 * \param[in] handle    : ��׼VC������
 */
void am_hc32_vc_deinit (am_hc32_vc_handle_t        handle);

/**
 * \brief �жϴ�����������
 *
 * \param[in] handle    : ��׼VC������
 * \param[in] pfn_cb    : �û�������жϴ����ص�����
 * \param[in] p_arg     : �û�������жϴ����ص���������
 *
 * \retval AM_ERROR ����ʧ��
 * \retval AM_ERROR ���ӳɹ�
 *
 */
int am_hc32_tri_set (am_hc32_vc_handle_t           handle,
                     am_pfnvoid_t                  pfn_cb,
                     void                         *p_arg);

/**
 * \brief VCͨ��ʹ��
 *
 * \param[in] handle    : ��׼VC������
 *
 * \retval AM_ERROR ʹ��ʧ��
 * \retval AM_ERROR ʹ�ܳɹ�
 */
int am_hc32_vc_chan_enable (am_hc32_vc_handle_t    handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_VC_H */

/* end of file */
