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
 * \brief  bsdiff/bspatch ����㷨
 *
 * \internal
 * \par Modification History
 * - 1.00 2020-09-10 , yrh, first implementation.
 * \endinternal
 */
#ifndef __AM_BSDIFF_H
#define __AM_BSDIFF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_am_bsdiff
 * @copydoc am_bsdiff.h
 * @{
 */

/**
 * \brief �����������Ϣ
 *
 */
typedef struct {
    uint8_t *p_diff;    /**< \brief ������� */
    int      offset;    /**< \brief �Ѿ���ȡ�Ĳ�����ݵ�ƫ�� */
}bsdiff_stream_info_t;

/**
 * \brief ��������
 *
 * \param[in]  p_old_data    : ������
 * \param[in]  old_data_size : �����ݴ�С
 * \param[in]  p_diff_data   : �������
 * \param[out] p_new_buff    : ��Ž��ֺ�������ݵĻ�����
 * \param[in]  new_data_size : �����ݵ�ʵ�ʴ�С��������ָ�����p_new_buffָ��Ĵ�С��
 *
 * \return  0  ���ɹ�;
 *          -1 ��ʧ�ܣ�
 */
int am_bspatch(const uint8_t *p_old_data,
               int32_t        old_data_size,
               uint8_t       *p_diff_data,
               uint8_t       *p_new_buff,
               int32_t        new_data_size);
/**
 * \brief ����������
 *
 * \param[in]  p_old_data    : ������
 * \param[in]  old_data_size : �����ݴ�С
 * \param[in]  p_new_data    : ������
 * \param[in]  new_data_size : �����ݴ�С
 * \param[out] p_diff_buf    : ��Ų������
 *
 * \return  > 0  ��������ݵĴ�С��p_diff_bufʵ�ʴ�ŵ���Ч���ݣ�;
 *          =< 0 ��ʧ�ܣ�
 */
int am_bsdiff(const uint8_t *p_old_data,
              int32_t        old_data_size,
              const uint8_t *p_new_data,
              int32_t        new_data_size,
              uint8_t       *p_diff_buf);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_BSDIFF_H */

/* end of file */
