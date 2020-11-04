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
 * \brief CPU PLUS����׼����������
 *
 * \internal
 * \par Modification History
 * - 1.00 16-01-06  hetaigang, first implementation.
 * \endinternal
 */
#ifndef __AM_DR_IC_CPU_PLUS_H
#define __AM_DR_IC_CPU_PLUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_uartcmd_cpu_plus.h"
#include "am_uartcmd_ic_iso14443.h"

/**
 * \brief CPU PLUS���豸�ṹ��
 */
typedef struct amdr_ic_cpu_plus_dev {

    /** \brief CPU PLUS������ṹ�� */
    am_ic_cpu_plus_serv_t   serv;

    /** \brief ISO14443������ */
    am_ic_iso14443_handle_t iso14443_handle;

    uint8_t  pcd_vector[16];   /** \brief PCD���ܳ�ʼ������ */
    uint8_t  picc_vector[16];  /** \brief PICC���ܳ�ʼ������ */
    uint8_t  random[16];       /** \brief ����� */

    /** \brief ��������������״���֤�������ɣ�������������ʹ�� */
    uint8_t  ti[4];

    uint8_t  picc_cap2[6];     /** \brief PICC�������� */
    uint8_t  subkey1[16];      /** \brief CMAC��������Կ1 */
    uint8_t  subkey2[16];      /** \brief CMAC��������Կ2 */

    /** \brief  ���ܻỰ��Կ */
    uint8_t  session_key_enc[16];

    /** \brief MAC �Ự��Կ */
    uint8_t  session_key_mac[16];

    am_bool_t   enckey_expand;    /** \brief ������Կ��չ��־ */
    am_bool_t   mackey_expand;    /** \brief MAC��Կ��չ��־ */
    am_bool_t   subkey_expand;    /** \brief CMAC��������Կ��չ��־ */

    uint16_t read_count;       /** \brief �������� */
    uint16_t write_count;      /** \brief д������ */

} amdr_ic_cpu_plus_dev_t;


/**
 * \brief CPU PLUS��������ʼ����
 *
 * \param[in] p_dev : CPU PLUS���豸�ṹ��ָ��
 *
 * \return CPU PLUS��׼������
 */
am_ic_cpu_plus_handle_t amdr_ic_cpu_plus_init (amdr_ic_cpu_plus_dev_t  *p_dev,
                                               am_ic_iso14443_handle_t  iso14443_handle);

/**
 * \brief CPU PLUS�������ʼ����
 *
 * \param[in] p_dev : CPU PLUS���豸�ṹ��ָ��
 *
 * \return ��
 */
void amdr_ic_cpu_plus_deinit (amdr_ic_cpu_plus_dev_t *p_dev);

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_IC_CPU_PLUS_H */

/* end of file */
