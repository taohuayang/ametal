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
 
#ifndef __AM_UARTCMD_SERIAL_H
#define __AM_UARTCMD_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uartcmd.h"

#define UARTCMD_SERIAL_SPEED_SET  1 /**< \brief ���ô����豸���� */
#define UARTCMD_SERIAL_SPEED_GET  2 /**< \brief ��ȡ�����豸���� */
#define UARTCMD_SERIAL_ADDR_SET   3 /**< \brief ���ô����豸��ַ */
#define UARTCMD_SERIAL_ADDR_GET   4 /**< \brief ��ȡ�����豸��ַ */

/** \brief ��ǰ�����ṹ�� */
struct uartcmd_serial;

/**
 * \brief �����豸ͨ�ú���
 */
struct uartcmd_serial_funcs {

    /** \brief ʹ�ܸ��豸 */
    int (*pfn_serial_enable)(struct uartcmd_serial *p_serial);

    /** \brief ���ܸ��豸 */
    int (*pfn_serial_disable)(struct uartcmd_serial *p_serial);

    /** \brief �������� */
    int (*pfn_serial_tx_startup)(struct uartcmd_serial *p_serial);

    /** \brief �豸�������� */
    int (*pfn_serial_ioctl)(struct uartcmd_serial *p_serial,
                            int                    request,
                            void                  *p_arg);
                            
    /** \brief �����豸ִ������֡״̬ */
    int (*pfn_serial_status_set) (struct uartcmd_serial *p_serial,
                                  int                    status);

};

/**
 * \brief �����豸�ṹ��
 */
typedef struct uartcmd_serial {
    
    /** \brief �����豸��� */
    void               *p_serial_handle;
    
    /** \brief ����ȷ����ǰ��Ҫʹ�õ��Ǻ��ִ����豸 */
    uint8_t             serial_id;   
    
    uint32_t            rx_count;    /**< \brief ���ռ��� */
    uint32_t            tx_count;    /**< \brief ���ͼ��� */
    
    /** \brief ����ͷ�ڵ� */
    struct am_list_head node;
    
    /** \brief UARTCMD ������ */
    am_uartcmd_handle_t uartcmd_handle;
    
    /** \brief �����豸������Ϣ */
    void               *p_arg;
    
    /** \brief �����豸ͨ�ú��� */
    struct uartcmd_serial_funcs *p_funcs;
    
} uartcmd_serial_t;

/**
 * \brief ע��һ�������豸
 *
 * \param[in] handle   : UARTCMD������
 * \param[in] p_serial : �����豸�ṹ��ָ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_serial_register (am_uartcmd_handle_t handle, uartcmd_serial_t *p_serial);

/**
 * \brief ע��һ�������豸
 *
 * \param[in] handle   : UARTCMD������
 * \param[in] p_serial : �����豸�ṹ��ָ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_serial_unregister (am_uartcmd_handle_t handle, uartcmd_serial_t *p_serial);

/**
 * \brief ���������豸�ķ���
 *        �ú�����UARTCMDģ����ã�����UARTCMD���ͻ�Ӧ֡
 *
 * \param[in] handle : UARTCMD������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_serial_tx_startup (am_uartcmd_handle_t handle);

/**
 * \brief �����豸ͨ�ÿ��ƺ���
 *
 * \param[in] handle  : UARTCMD������
 * \param[in] request : ����ָ��ɾ����豸����
 *                      - UARTCMD_SERIAL_SPEED_SET ���ô����豸����
 *                      - UARTCMD_SERIAL_SPEED_GET ��ȡ�����豸����
 *                      - UARTCMD_SERIAL_ADDR_SET  ���ô����豸��ַ
 *                      - UARTCMD_SERIAL_ADDR_GET  ��ȡ�����豸��ַ
 * \param[in] p_arg   : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_serial_ioctl (am_uartcmd_handle_t handle, int request, void *p_arg);

/**
 * \brief �����豸ִ������֡״̬����
 *
 * \param[in] handle  : UARTCMD������
 * \param[in] stauts  : ״ֵ̬
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_serial_status_set (am_uartcmd_handle_t handle, int status);

#ifdef __cplusplus
}
#endif

#endif /* __AM_UARTCMD_SERIAL_H */

/* end of file */
