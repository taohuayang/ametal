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
 * - 1.00 15-11-27  win, first implementation.
 * \endinternal
 */
#ifndef __AM_UARTCMD_CMD_DEV_CTRL_H
#define __AM_UARTCMD_CMD_DEV_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_reader_card.h"
#include "am_uartcmd_cmd.h"
#include "am_uartcmd_cmd_define.h"

/** \brief ����IAP����ָ������ */
typedef int (*pfn_iap_funcs_t)(uint32_t dst_addr,
                               uint32_t src_addr,
                               uint32_t nbytes);
/**
 * \brief �豸������ָ�����FLASH����
 *        �������������û�����
 */
struct uartcmd_cmd_dev_ctrl_funcs {

    /**
     * \brief ���ڴ��е�����д��FLASH��
     *        ����ֵΪAM_OK��ʾ�ɹ�������ֵ��ʾʧ��
     */
    pfn_iap_funcs_t pfn_iap_copy;

    /**
     * \brief �Ƚ��ڴ��е����ݺ�FLASH�е�����
     *        ����ֵΪAM_OK��ʾ�ɹ�������ֵ��ʾʧ��
     */
    pfn_iap_funcs_t pfn_iap_compare;
};

/**
 * \brief �����豸����������ṹ�����
 * 
 * \param[in] p_cmd       : �豸����������ṹ��ָ��
 * \param[in] p_funcs     : �豸������ָ�����FLASH�����ṹ��ָ��
 * \param[in] cd_handle   : ������������
 * \param[in] pfn_copy    : IAP��������ָ��
 * \param[in] pfn_compare : IAP�ȽϺ���ָ��
 * \param[in] cmd_classs  : ��������
 * 
 * \retval AM_OK : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int uartcmd_cmd_dev_ctrl_mkdev (uartcmd_cmd_t                     *p_cmd,
                                struct uartcmd_cmd_dev_ctrl_funcs *p_funcs,
                                am_reader_card_handle_t            cd_handle,
                                pfn_iap_funcs_t                    pfn_copy,
                                pfn_iap_funcs_t                    pfn_compare,
                                uint8_t                            cmd_class)
{
    if (p_cmd       == NULL ||
        p_funcs     == NULL ||
        pfn_copy    == NULL ||
        pfn_compare == NULL) {
        return -AM_EINVAL;
    }

    p_funcs->pfn_iap_copy    = pfn_copy;
    p_funcs->pfn_iap_compare = pfn_compare;
    p_cmd->p_arg             = (void *)p_funcs;
    p_cmd->cmd_class         = cmd_class;
    p_cmd->p_iso_handle      = (void *)cd_handle;

    return AM_OK;
}

/**
 * \brief �ֽ��ۼӺͼ��� 
 * 
 * \param[in] p_buf  : ��Ҫ�����ۼӺ͵Ļ�����
 * \param[in] nbytes : �������ֽ���
 *
 * \return �ۼӺ�
 */
uint32_t uartcmd_cmd_byte_sum_get (const void *p_buf, uint32_t nbytes);

/**
 * \brief �豸�����������ʼ��
 *
 * \param[in] handle : UARTCMD������
 * \param[in] p_cmd  : �豸����������ṹ��ָ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int uartcmd_cmd_dev_ctrl_init (am_uartcmd_handle_t  handle,
                               uartcmd_cmd_t       *p_cmd);

/**
 * \brief �豸����������ȥ����ʼ��
 *
 * \param[in] handle : UARTCMD������
 * \param[in] p_cmd  : �豸����������ṹ��ָ��
 *
 * \return ��
 */
void uartcmd_cmd_dev_ctrl_deinit (am_uartcmd_handle_t handle, uartcmd_cmd_t *p_cmd);

#ifdef __cplusplus
}
#endif


#endif /* __UARTCMD_CMD_DEV_CTRL_H */

/* end of file */
