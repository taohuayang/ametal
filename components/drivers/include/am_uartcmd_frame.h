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
 * \brief 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-11-12  win, first implementation.
 * \endinternal
 */
 
#ifndef __AM_UARTCMD_FRAME_H
#define __AM_UARTCMD_FRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_list.h"
#include "am_uartcmd.h"

/**
 * \brief ֡����ͨ�ú���
 */
struct uartcmd_frame_funcs {
    
    /** \brief ֡��⺯�� */
    int (*pfn_frame_check)(const void *p_buf, uint32_t nbytes);
    
    /** \brief ֡������ */
    int (*pfn_frame_execute)(am_uartcmd_handle_t  handle,
                             void                *p_buf,
                             uint32_t             nbytes);
    
    /** \brief ��ȡ֡�е�������Ϣ�ĳ��Ⱥ�֡�� */
    int (*pfn_frame_info_get)(const void *p_buf,
                              uint32_t   *p_frame_len,
                              uint32_t   *p_info_len);

};

/**
 * \brief ͨ��֡����
 */
typedef struct uartcmd_frame {
    
    /** \brief ֡����ͨ�ú��� */
    struct uartcmd_frame_funcs *p_funcs;
    
    /** \brief ֡���� */
    uint8_t                frame_type;
    
    /** \brief ������ */
    struct am_list_head    node;

} uartcmd_frame_t;

/**
 * \brief ע��һ���µ�֡����
 * 
 * \param[in] handle  : UARTCMD������
 * \param[in] p_frame : ����֡�ṹ��ָ��
 * 
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_frame_class_register (am_uartcmd_handle_t  handle,
                                  uartcmd_frame_t     *p_frame);

/**
 * \brief ע��һ���µ�֡����
 *
 * \param[in] handle  : UARTCMD������
 * \param[in] p_frame : ����֡�ṹ��ָ��
 * 
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_frame_class_unregister (am_uartcmd_handle_t  handle,
                                    uartcmd_frame_t     *p_frame);

/**
 * \brief ֡������
 *
 * \param[in] handle : UARTCMD������
 * 
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_frame_execute (am_uartcmd_handle_t handle);

/**
 * \brief ������һ��֡����������Զ����ģʽ��
 *
 * \param[in] handle : UARTCMD������
 * 
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_frame_last_execute (am_uartcmd_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_FRAME_H */

/* end of file */
