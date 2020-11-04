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
 * \brief ֧���豸������ָ��ı�׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-11-27  win, first implementation.
 * \endinternal
 */
#ifndef __AM_DR_READER_CARD_H
#define __AM_DR_READER_CARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_reader_card.h" 
#include "am_uartcmd_includes.h"
#include "am_uartcmd_cd4051.h"
/**
 * \brief ����оƬ�豸�ṹ��
 */
typedef struct amdr_reader_card_dev {
    
    /** \brief ����оƬ����ṹ�� */
    am_reader_card_serv_t  serv;
    
    /** \brief ����оƬ�豸�ṹ��ָ�� */
    am_fm175xx_dev_t      *p_fm17550s_dev;

    /*  \brief оƬ�����豸�ṹ��ָ��*/
    am_antenna_info_t     *p_antenna_info;

} amdr_reader_card_dev_t;

/**
 * \brief ����оƬ�������ʼ������ 
 *
 * \param[in] p_dev : ����оƬ�豸�ṹ��ָ��
 *
 * \retval AM_OK : �ɹ�
 * \retval -AM_EIINVAL : ��������
 */
am_reader_card_handle_t amdr_reader_card_init (amdr_reader_card_dev_t   *p_dev,
                                               am_fm175xx_dev_t         *p_fm17550s_dev,
                                               am_antenna_info_t       *p_cd4051_dev);

/**
 * \brief ����оƬ������ȥ��ʼ������ 
 *
 * \param[in] p_dev : ����оƬ�豸�ṹ��ָ��
 *
 * \retval AM_OK : �ɹ�
 * \retval -AM_EIINVAL : ��������
 */
int amdr_reader_card_deinit (amdr_reader_card_dev_t *p_dev);
    
#ifdef __cplusplus
}
#endif

#endif /* __AMDR_READER_CARD_H */

/* end of file */
