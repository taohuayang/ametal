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
 * \brief DES ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-07-13  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_DES_H
#define __AM_DES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

#define AM_ENCRY    0x0
#define AM_DECRY    0x1

/**
 * \brief am_tdes
 *
 * \param[in]  mode      : mode = 0:����    mode = 1������
 * \param[in]  p_msg_in  : �������� �������ģ����ܣ������ģ����ܣ�
 * \param[in]  p_key     : 16�ֽ���Կ����
 * \param[out] p_msg_out : ���ģ����ܣ������ģ����ܣ�
 *
 * \return
 */
uint8_t am_tdes (uint8_t  mode,
                 uint8_t *p_msg_in,
                 uint8_t *p_key,
                 uint8_t *p_msg_out);

/**
 * \brief MAC ����
 *
 * \param[in]  p_init_data : ��ʼ������
 * \param[in]  p_mac_key   : 16�ֽ���Կ����
 * \param[in]  data_len    : ���ݳ���
 * \param[in]  p_in_data   : ����
 * \param[out] p_mac_data  : MAC������
 *
 * \return ret
 */
uint8_t am_triple_mac (uint8_t *p_init_data,
                       uint8_t *p_mac_key,
                       uint8_t  data_len,
                       uint8_t *p_in_data,
                       uint8_t *p_mac_data);

/**
 * \brief MAC ����
 *
 * \param[in]  p_init_data : 8�ֽ����飬��ʼ������
 * \param[in]  p_mac_key   : 16�ֽ���Կ����
 * \param[in]  data_len    : ���ݳ���
 * \param[in]  p_in_data   : ����
 * \param[out] p_mac_data  : 8�ֽ����飬MAC������
 *
 * \return ret
 */
uint8_t am_mac (uint8_t *p_init_data,
                uint8_t *p_mac_key,
                uint8_t  data_len,
                uint8_t *p_in_data,
                uint8_t *p_mac_data);

/**
 * \brief ��һ��8�ֽڵ��ַ������е�DES�ӽ��ܼ���
 *
 * \param[in]  mode      : mode=0:���� ��mode=1������
 * \param[in]  p_msg_in  : �������� �������ģ����ܣ������ģ����ܣ�
 * \param[in]  p_key     : 8�ֽ���Կ����
 * \param[out] p_msg_out : ���ģ����ܣ������ģ����ܣ�
 *
 * \return ret
 */
uint8_t am_des (uint8_t  mode,
                uint8_t *p_msg_in,
                uint8_t *p_key,
                uint8_t *p_msg_out);

#ifdef __cplusplus
}
#endif

#endif /* __AM_DES_H */

/* end of file */
