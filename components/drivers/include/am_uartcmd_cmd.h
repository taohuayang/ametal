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
 
#ifndef __AM_UARTCMD_CMD_H
#define __AM_UARTCMD_CMD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_list.h"
#include "am_uartcmd.h"

struct uartcmd_cmd_info;

/**
 * \brief �������ͽṹ�� 
 */
typedef struct uartcmd_cmd {
    
    /** \brief �������� */
    uint8_t cmd_class;
    
    /** \brief ����ִ�к��� */
    int (*pfn_cmd_execute)(am_uartcmd_handle_t      handle,
                           struct uartcmd_cmd_info *p_cmd_info);
    
    /** \brief ISOЭ���׼��� */
    void     *p_iso_handle; 
    
    /** \brief ������ */
    struct am_list_head node;
    
    /** \brief ָ��ֻ֧�ֵ�һ����ľ�� */
    void     *p_other_handle;

    /** \brief ������չ������Ϣ */
    void     *p_arg;

} uartcmd_cmd_t;

/**
 * \brief ������Ϣ�ṹ��
 */
typedef struct uartcmd_cmd_info {
    uartcmd_cmd_t *p_cmd;       /**< \brief ��������������������� */
    uint32_t       cmd_code;    /**< \brief ������� */
    uint8_t        slot_index;  /**< \brief ���������� */
    uint8_t       *p_rx_buf;    /**< \brief �������֡������Ϣ�Ļ����� */
    uint32_t       rx_nbytes;   /**< \brief ������Ϣ���ֽ��� */
    uint8_t       *p_tx_buf;    /**< \brief ��Ż�Ӧ֡������Ϣ�Ļ����� */
    uint32_t      *p_tx_nbytes; /**< \brief ������Ϣ���ֽ��� */
} uartcmd_cmd_info_t;

/**
 * \brief ע��һ���µ���������
 *
 * \param[in] handle : UARTCMD������
 * \param[in] p_cmd  : �������ͽṹ��ָ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_cmd_class_register (am_uartcmd_handle_t handle, uartcmd_cmd_t *p_cmd);

/**
 * \brief ע��һ���µ���������
 *
 * \param[in] handle : UARTCMD������
 * \param[in] p_cmd  : �������ͽṹ��ָ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_cmd_class_unregister (am_uartcmd_handle_t handle, uartcmd_cmd_t *p_cmd);

/**
 * \brief ����ִ�к���
 *
 * \param[in] handle      : UARTCMD������
 * \param[in] cmd_class   : �������
 * \param[in] cmd_code    : �������
 * \param[in] slot_index  : �������� 
 * \param[in] p_rx_buf    : �������ݻ�����
 * \param[in] rx_nbytes   : �������ݵ��ֽ���
 * \param[in] p_tx_buf    : ��ŷ�����Ϣ�Ļ�����
 * \param[in] p_tx_nbytes : ������Ϣ���ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ������Ϣ
 */
int uartcmd_cmd_execute (am_uartcmd_handle_t  handle,
                         uint32_t             cmd_class,
                         uint32_t             cmd_code,
                         uint8_t              slot_index,
                         uint8_t             *p_rx_buf,
                         uint32_t             rx_nbytes,
                         uint8_t             *p_tx_buf,
                         uint32_t            *p_tx_nbytes);

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_CMD_H */

/* end of file */
