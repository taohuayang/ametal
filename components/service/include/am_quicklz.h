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
 * \brief  QuickLZ ѹ����ѹ�㷨
 *
 * \internal
 * \par Modification History
 * - 1.00 2020-09-10 , yrh, first implementation.
 * \endinternal
 */
#ifndef __AM_QUICKLZ_H
#define __AM_QUICKLZ_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_am_quicklz
 * @copydoc am_quicklz.h
 * @{
 */
#include "ametal.h"

/**
 * \brief ����ѹ��
 *
 * \param[in]  p_src    : Դ���ݵ�ַ
 * \param[in]  p_dst    : ѹ�������ݴ洢��ʼ��ַ�����С����Ϊ��src_size + 400���ֽ�
 * \param[in]  src_size : ��Ҫѹ�������ݴ�С
 *
 * \return > 0 : ѹ��������ݵ��ֽ���
 *         = 0 : ѹ��ʧ��
 */
size_t am_quicklz_compress(const void *p_src, char *p_dst, size_t src_size);

/**
 * \brief ���ݽ�ѹ��
 *
 * \param[in] p_src ��ָ���ѹ�����ݵĴ����ַ
 * \param[in] p_dst ��ָ���ѹ��������ݴ����ַ����ѹ��������������p_dst �������㹻��Ŀռ�
 *
 * \return > 0 : ��ѹ�������ݵ��ֽ���
 *         = 0 : ��ѹʧ��
 */
size_t am_quicklz_decompress(const char *p_src,
                             void       *p_dst);

/**
 * \brief ��ȡ��ǰѹ�����Ĵ�С
 *
 * \param[in] p_src ��ָ���Ѿ�ѹ��������ݵ���ʼ��ַ
 *
 * \return ѹ���������ݴ�С
 */
size_t am_quicklz_size_compressed(const char *p_src);

/**
 * \brief ��ȡѹ������ѹ������ݴ�С��Ҳ��ѹ��֮ǰ�����ݴ�С��
 *
 * \param[in] p_src ��ָ���Ѿ�ѹ��������ݵ���ʼ��ַ
 *
 * \return ��ѹ���Ժ�����ݴ�С
 */
size_t am_quicklz_size_decompressed(const char *p_src);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_QUICKLZ_H */

/* end of file */
