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
 * \brief LVD ���������� LVD ��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 20-04-27 zcb, Add callback function parameters
 * - 1.00 19-10-08
 * \endinternal
 */
#ifndef __AM_HC32_LVD_H
#define __AM_HC32_LVD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_hc32_if_lvd
 * \copydoc am_hc32_lvd.h
 * @{
 */
/**
 * \brief LVD�豸��Ϣ�ṹ��
 */
typedef struct am_hc32_lvd_info {

    /** \brief LVD �Ĵ��������ַ */
    uint32_t                     reg_base;

    /** \brief LVD �жϱ�� */
    uint8_t                      inum;

    /** \brief LVD �������� */
    uint32_t                     tri_type;

    /** \brief LVD �����˲�ʱ�� */
    int                          deb_time;

    /** \brief LVD ��ֵ��ѹ */
    int                          vids;

    /** \brief LVD �����Դ */
    int                          src_sel;

    /** \brief LVD �������� */
    int                          tri_act;

    /** \brief LVD ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                       (*pfn_plfm_init)(void);

    /** \brief LVD ƽ̨���ʼ������ */
    void                       (*pfn_plfm_deinit)(void);

}am_hc32_lvd_devinfo_t;

/**
 * \brief LVD�豸ʵ��
 */
typedef struct am_hc32_lvd_dev {

    /** \brief ָ��LVD�豸��Ϣ��ָ�� */
    const am_hc32_lvd_devinfo_t *p_devinfo;

    /** \brief �жϴ����ص���������*/
    am_pfnvoid_t                 pfn_trigger_cb;

    /** \brief �жϴ����ص���������*/
    void                        *p_arg;

} am_hc32_lvd_dev_t;

/** \brief LVD ��׼�������������Ͷ��� */
typedef am_hc32_lvd_dev_t       *am_hc32_lvd_handle_t;

/**
 * \brief LVD ��ʼ��
 *
 * \param[in] p_dev     : LVD �豸ʵ��
 * \param[in] p_devinfo : LVD �豸��Ϣʵ��
 *
 * \retval : ��׼LVD������
 *
 */
am_hc32_lvd_handle_t am_hc32_lvd_init (am_hc32_lvd_dev_t           *p_dev,
                                       const am_hc32_lvd_devinfo_t *p_devinfo);

/**
 * \brief LVD ȥ��ʼ��
 *
 * \param[in] handle : ��׼LVD������
 *
 * \retval : ��
 *
 */
void am_hc32_lvd_deinit (am_hc32_lvd_handle_t     handle);

/**
 * \brief LVD ʹ��
 *
 * \param[in] handle : ��׼LVD������
 *
 * \retval AM_OK     : ʹ�ܳɹ�
 *         AM_ERROR  : ʹ��ʧ��
 *
 */
int am_hc32_lvd_enable (am_hc32_lvd_handle_t      handle);

/**
 * \brief LVD �жϴ�����������
 *
 * \param[in] handle     : ��׼LVD������
 * \param[in] pfn_tri_cb : �û�����Ļص�����
 *
 * \retval AM_OK         : ���ӳɹ�
 * \retval AM_ERROR      : ����ʧ��
 */
int am_hc32_lvd_tri_set (am_hc32_lvd_handle_t     handle,
                         am_pfnvoid_t             pfn_tri_cb,
                         void                    *p_arg);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_LVD_H */

/* end of file */
