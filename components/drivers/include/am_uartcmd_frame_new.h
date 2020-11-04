/*******************************************************************************
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
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

#ifndef __AM_UARTCMD_FRAME_NEW_H
#define __AM_UARTCMD_FRAME_NEW_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uartcmd_frame.h"

/**
 * \brief ��֡��ʼ������
 *
 * \param[in] handle  : UARTCMD������
 * \param[in] p_frame : ͨ��֡���ͽṹ��
 * \param[in] type    : ֡������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_frame_new_init (am_uartcmd_handle_t  handle,
                            uartcmd_frame_t     *p_frame,
                            uint8_t              type);

/**
 * \brief ��֡ȥ��ʼ������
 *
 * \param[in] handle  : UARTCMD������
 * \param[in] p_frame : ͨ��֡���ͽṹ��
 * \param[in] type    : ֡������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_frame_new_deinit (am_uartcmd_handle_t  handle,
                              uartcmd_frame_t     *p_frame);

/**
 * \brief ��֡У��ͼ���
 *
 * \param[in] p_buf : ���֡�Ļ�����
 * \param[in] len   : �ӵ�ַ�ֽڿ�ʼ����Ϣ������ֽڣ�������У����ֽڣ�
 *
 * \return У���
 */
uint32_t uartcmd_frame_new_sum_cacl (const uint8_t *p_buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __AM_UARTCMD_FRAME_OLD_H */

/* end of file */
