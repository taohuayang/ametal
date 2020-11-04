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
 * \brief ISO14443�����׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-01-04  hetaigang, first implementation.
 * \endinternal
 */
#ifndef __AM_DR_IC_ISO14443_H
#define __AM_DR_IC_ISO14443_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uartcmd_ic_iso14443.h"
#include "am_uartcmd_includes.h"

/**
 * \brief tpcl_prot_para T=CLЭ�����
 */
typedef struct tpcl_prot_para {
    uint8_t pcb_num;                /**< \brief �ְ���ʶ */
    uint8_t cid;                    /**< \brief CID */
    uint8_t fsdi;                   /**< \brief PCD  �ܽ��յ����֡ */
    uint8_t fsci;                   /**< \brief PICC �ܽ��յ����֡ */
    uint8_t ta1;                    /**< \brief ��DR��DS */
    uint8_t bit_rate;               /**< \brief λ����(ͬTA1, ��DR��DS) */
    uint8_t fwi;                    /**< \brief ֡�ȴ�ʱ������ */
    uint8_t sfgi;                   /**< \brief ֡����ʱ������ */
    uint8_t tc1;                    /**< \brief ���Ƿ�֧��CID��NAD */
    uint8_t fo;                     /**< \brief ֡ѡ���Ƿ�֧��CID��NAD (ͬTC1) */
} tpcl_prot_para_t;

/**
 * \brief ISO14443�豸�ṹ��
 */
typedef struct amdr_ic_iso14443_dev {

    /** \brief ISO14443����ṹ�� */
    am_ic_iso14443_serv_t serv;

    /** \brief ȫ�ֱ��������ڱ���A�Ϳ�UID */
    uint8_t               uid_back[4];

    /** \brief T=CLͨ��Э����� */
    tpcl_prot_para_t      cur_prot_para;

    /** \brief ����оƬ�����ṹ�� */
    am_fm175xx_dev_t     *p_fm17550s_dev;

} amdr_ic_iso14443_dev_t;

/**
 * \brief ISO14443�������ʼ��
 *
 * \param[in] p_dev : ISO14443�豸�ṹ��ָ��
 *
 * \return ISO14443������
 */
am_ic_iso14443_handle_t amdr_ic_iso14443_init (amdr_ic_iso14443_dev_t *p_dev,
                                               am_fm175xx_dev_t       *p_fm17550s_dev);

/**
 * \brief ISO14443����������ʼ��
 *
 * \param[in] p_dev : ISO14443�豸�ṹ��ָ��
 *
 * \return ��
 */
void amdr_ic_iso14443_deinit (amdr_ic_iso14443_dev_t *p_dev);

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_IC_ISO14443_H */

/* end of file */
