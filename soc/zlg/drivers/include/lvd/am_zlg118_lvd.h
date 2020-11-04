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
 * \brief LVD����������LVD��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-08
 * \endinternal
 */
#ifndef __AM_ZLG118_LVD_H
#define __AM_ZLG118_LVD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_zlg118_if_lvd
 * \copydoc am_zlg118_lvd.h
 * @{
 */
/**
 * \brief LVD�豸��Ϣ�ṹ��
 */
typedef struct am_zlg118_lvd_info {

    uint32_t    reg_base;  /**< \brief lvd�Ĵ��������ַ */

    uint8_t     inum;      /**< \brief lvd�жϱ�� */

    uint32_t    tri_type;  /**< \brief lvd�������� */

    int         deb_time;  /**< \brief lvd�����˲�ʱ�� */

    int         vids;      /**< \brief lvd��ֵ��ѹ */

    int         src_sel;   /**< \brief lvd�����Դ */

    int         tri_act;   /**< \brief lvd�������� */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

}am_zlg118_lvd_devinfo_t;

/**
 * \brief LVD�豸ʵ��
 */
typedef struct am_zlg118_lvd_dev {

    /** \brief ָ��LVD�豸��Ϣ��ָ�� */
    const am_zlg118_lvd_devinfo_t *p_devinfo;

    /** \brief �жϴ����ص� ����*/
    void (*pfn_trigger_cb)(void *);

} am_zlg118_lvd_dev_t;

/** \brief lvd��׼�������������Ͷ��� */
typedef am_zlg118_lvd_dev_t *am_lvd_handle_t;

/**
 * \brief lvd ��ʼ��
 *
 * \param[in] p_dev     : LVD �豸ʵ��
 * \param[in] p_devinfo : LVD �豸��Ϣʵ��
 *
 * \retval : ��׼LVD������
 *
 */
am_lvd_handle_t  am_zlg118_lvd_init (am_zlg118_lvd_dev_t           *p_dev,
                                     const am_zlg118_lvd_devinfo_t *p_devinfo);

/**
 * \brief lvd ȥ��ʼ��
 *
 * \param[in] handle : ��׼LVD������
 *
 * \retval : ��
 *
 */
void am_zlg118_lvd_deinit (am_lvd_handle_t handle);

/**
 * \brief lvd ʹ��
 *
 * \param[in] handle : ��׼LVD������
 *
 * \retval AM_OK    : ʹ�ܳɹ�
 *         AM_ERROR : ʹ��ʧ��
 *
 */
int am_zlg118_lvd_enable (am_lvd_handle_t handle);

/**
 * \brief �жϴ�����������
 *
 * \param[in] handle     : ��׼LVD������
 * \param[in] pfn_tri_cb : �û�����Ļص�����
 *
 * \retval AM_ERROR ����ʧ��
 * \retval AM_OK    ���ӳɹ�
 */
int am_zlg118_lvd_tri_set (am_lvd_handle_t handle,
                           void (*pfn_tri_cb) (void *));

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_LVD_H */

/* end of file */
