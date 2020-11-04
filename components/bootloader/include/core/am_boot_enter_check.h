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
 * \brief �����������жϼ���׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-5-23  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_BOOT_ENTER_CHECK_H
#define __AM_BOOT_ENTER_CHECK_H

#include "am_common.h"

/**
 * \brief bootloader ���������жϼ�����������ṹ��
 */
struct am_boot_enter_check_drv_funcs {

    /** \brief ���������жϼ�� */
    am_bool_t (*pfn_startup_check) (void *p_drv);

    /** \brief ���³�ʼ�����������жϼ�� */
    void      (*pfn_reinit)(void *p_drv);
};

/**
 * \brief ���������жϼ���׼����ṹ��
 */
typedef struct am_boot_enter_check_serv {
    /**< \brief �豸���������ṹ��ָ�� */
    const struct am_boot_enter_check_drv_funcs *p_funcs;

    /**< \brief �豸����������һ������ */
    void                                       *p_drv;
} am_boot_enter_check_serv_t;

/** \brief ���������жϼ���׼�������������Ͷ��� */
typedef am_boot_enter_check_serv_t  *am_boot_enter_check_handle_t;

/**
 * \brief  ���������жϼ��
 *
 * \retval AM_TRUE  �����������
 * \retval AM_FALSE �������������
 */
am_static_inline
am_bool_t am_boot_enter_check(am_boot_enter_check_handle_t handle)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_startup_check) {
        return handle->p_funcs->pfn_startup_check(handle->p_drv);
    }
    return AM_FALSE;
}

/**
 * \brief ���³�ʼ�� ���������жϼ��
 *
 *
 */
am_static_inline
void am_boot_enter_check_reinit(am_boot_enter_check_handle_t handle)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_reinit) {
        handle->p_funcs->pfn_reinit(handle->p_drv);
    }
}

#endif /* __AM_BOOT_ENTER_CHECK_H */
