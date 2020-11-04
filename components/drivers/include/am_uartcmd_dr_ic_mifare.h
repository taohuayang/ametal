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
 * \brief Mifare����׼����������
 *
 * \internal
 * \par Modification History
 * - 1.00 16-01-13  hetaigang, first implementation.
 * \endinternal
 */
#ifndef __AM_DR_IC_MIFARE_H
#define __AM_DR_IC_MIFARE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uartcmd_ic_mifare.h"
#include "am_uartcmd_includes.h"

/**
 * \brief Mifare���豸�ṹ��
 */
typedef struct amdr_ic_mifare_dev {

    /** \brief Mifare����׼����ṹ�� */
    am_ic_mifare_serv_t     serv;

    /** \brief ISO14443��׼������ */
    am_ic_iso14443_handle_t iso14443_handle;

    /** \brief ����оƬ�����ṹ�� */
    am_fm175xx_dev_t       *p_fm17550s_dev;
} amdr_ic_mifare_dev_t;

/**
 * \brief Mifare��������ʼ��
 *
 * \param[in] p_dev           : Mifare���豸�ṹ��ָ��
 * \param[in] iso14443_handle : ISO14443��׼������
 *
 * \return Mifare��׼������
 */
am_ic_mifare_handle_t amdr_ic_mifare_init (amdr_ic_mifare_dev_t    *p_dev,
                                           am_ic_iso14443_handle_t  iso14443_handle,
                                           am_fm175xx_dev_t        *p_fm17550s_dev);

/**
 * \brief Mifare���������ʼ��
 * \param[in] p_dev : Mifare���豸�ṹ��ָ��
 * \return ��
 */
void amdr_ic_mifare_deinit (amdr_ic_mifare_dev_t *p_dev);

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_IC_MIFARE_H */

/* end of file */
