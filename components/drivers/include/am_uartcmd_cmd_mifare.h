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
 * - 1.00 15-11-30  win, first implementation.
 * \endinternal
 */
#ifndef __AM_UARTCMD_CMD_MIFARE_H
#define __AM_UARTCMD_CMD_MIFARE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uartcmd_cmd.h"
#include "am_uartcmd_cmd_define.h"

#include "am_uartcmd_ic_mifare.h"
#include "am_uartcmd_ic_iso14443.h"
#include "am_uartcmd_cpu_plus.h"
#include "am_reader_card.h"

typedef struct uartcmd_cmd_mifare_var {

    /** \brief ��Ƭ���� */
    uint8_t card_type;

    /** \brief CPU PLUS��׼������ */
    am_ic_cpu_plus_handle_t cpu_plus_handle;

    /** \brief Mifare��׼������ */
    am_ic_mifare_handle_t   mifare_handle;

    /** \brief ISO14443��׼������ */
    am_ic_iso14443_handle_t iso14443_handle;

    /** \brief ����оƬ������ */
    am_reader_card_handle_t reader_card_handle;

    /** \brief �����Զ���� */
    uartcmd_auto_detest_info_t auto_detest;

    /** \brief �Զ�������ݴ�ŵĻ�������ַ */
    uint8_t  auto_buf[260];

    /** \brief ��ʱ������ */
    uint8_t  auto_tmp_buf[260];

    /** \brief ��ʱ���������� */
    uint32_t auto_tmp_count;

    /** \brief �Զ�������ݵĳ��ȣ�ǰ���������ݴ��� */
    uint32_t auto_nbytes;

    /** \brief �Զ��쿨����Ĳ��ֲ��� */
    struct am_uartcmd_frame auto_frame;

} uartcmd_cmd_mifare_var_t;

/**
 * \brief Mifare �������ʼ��
 *
 * \param[in] handle             : UARTCMD������
 * \param[in] p_cmd              : �豸����������ṹ��ָ��
 * \param[in] p_var              : Mifare��������ṹ��ָ��
 * \param[in] mifare_handle      : Mifare������
 * \param[in] iso14443_handle    : ISO14443������
 * \param[in] cpu_plus_handle    : CPU PLUS��������
 * \param[in] reader_card_handle : ������������
 * \param[in] cmd_class          : ��������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_cmd_mifare_init (am_uartcmd_handle_t       handle,
                             uartcmd_cmd_t            *p_cmd,
                             uartcmd_cmd_mifare_var_t *p_var,
                             am_ic_mifare_handle_t     mifare_handle,
                             am_ic_iso14443_handle_t   iso14443_handle,
                             am_ic_cpu_plus_handle_t   cpu_plus_handle,
                             am_reader_card_handle_t   reader_card_handle,
                             uint8_t                   cmd_class);

/**
 * \brief Mifare ������ȥ����ʼ��
 *
 * \param[in] handle : UARTCMD������
 * \param[in] p_cmd  : �豸����������ṹ��ָ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
void uartcmd_cmd_mifare_deinit (am_uartcmd_handle_t handle, uartcmd_cmd_t *p_cmd);

/**
 * \brief �Զ����ģʽ
 */
int uartcmd_cmd_mifare_auto_detest (am_uartcmd_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_CMD_MIFARE_H */
