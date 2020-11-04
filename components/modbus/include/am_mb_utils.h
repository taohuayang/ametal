/*******************************************************************************
*                                 AWORKS
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief modbus ���ù���ͷ�ļ�.
 *
 * \internal
 * \par modification history
 * - 1.03 2-17-03-29  mkr, transplant from aworks
 * - 1.02 2015-05-18  cod, fix code style and comments, a little improve.
 * - 1.01 2013-03-29  liuweiyun, fix code style and comments, a little improve.
 * - 1.00 2012-05-03  ygy, first implementation
 * \endinternal
 */

#ifndef __AM_MB_UTILS_H /* { */
#define __AM_MB_UTILS_H

/**
 * \addtogroup grp_am_if_mb_utils
 * \copydoc am_mb_utils.h
 * @{
 */

#include "am_mb_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief �ú�����ȡ������һ���ֽڵ�λ
 *
 * @note  �ú�����߿ɶ�8λ����
 *
 *
 * @param p_bytebuf �ֽ����ݵĻ�����
 *
 * @param bit_offset ��ȡλ��ƫ����
 *
 * @param nbits ��ȡλ������С��8λ
 *
 * \par example
 * \code
 * uint8_t bits_buf[2] = {0, 0};
 * uint8_t value;
 *
 * // Extract the bits 3 - 10.
 * value = am_mb_bits_get(bits_buf, 3, 8);
 * \endcode
 *
 * @retval ָ����ȡ��λ��ֵ
 */
uint8_t am_mb_bits_get (const uint8_t *p_bytebuf, int bit_offset, int nbits);

/**
 * \brief �ú���������ĳ��λ��һ���ֽڵĻ�����
 *
 * @note �ú���һ�β�����߿�����8bit������������Ϊ2���ֽڡ�
 *
 * @param p_bytebuf д�뻺����������Ϊ2���ֽڣ���ֹƫ��λ����������д��
 *
 * @param bit_offset ƫ��λ��
 *
 * @param nbits ����λ��
 *
 * @param values ����λ����ֵ����ֵ�����λΪbit_offset���õ�λֵ
 *
 * \par example:
 * \code
 * uint8_t bits_buf[2] = {0, 0};
 *
 * // Set bit 4 to 1 (set 1 bit starting at bit offset 4 to value 1)
 * am_mb_bits_set(bits_buf, 4, 1, 1);
 *
 * // Set bit 7 to 1 and bit 8 to 0.
 * am_mb_bits_set(bits_buf, 7, 2, 0x01);
 *
 * // Set bits 8 - 11 to 0x05 and bits 12 - 15 to 0x0A;
 * am_mb_bits_set(bits_buf, 8, 8, 0x5A);
 * \endcode
 *
 * @return ��
 */
void am_mb_bits_set (uint8_t *p_bytebuf,
					 int 	  bit_offset,
					 int      nbits,
					 uint8_t  value);

/**
 * \brief ��ȡbitsֵ��������
 *
 * @note  �ú����������ڴ��ص�
 *
 * @param[in,out] p_bytesbuf ���ݻ�����
 * @param[in] 	  p_bitsbuf  д��λֵ�Ļ�����
 * @param[in]     bit_offset ƫ��λ��
 * @param[in]     nbits      д��λ��
 */
void am_mb_bits_cp_to_buf (uint8_t       *p_bytesbuf,
                           const uint8_t *p_bitsbuf,
                           int            bit_offset,
                           int            nbits);

/**
 * \brief �ӻ���������bits��ֵ
 *
 * @note  �ú����������ڴ��ص�
 *
 * @param[in,out] p_bitsbuf	  �������ݻ�����
 * @param[in] 	  p_bytesbuf λֵ�����������λֵ
 * @param[in]     bit_offset ƫ��λ��
 * @param[in]     nbits      ����λ��
 *
 */
void am_mb_bits_set_from_buf (uint8_t       *p_bitsbuf,
                              const uint8_t *p_bytesbuf,
                              int            bit_offset,
                              int            nbits);
/**
 * @brief ����16bits�Ĵ�������
 *
 * @note  Modbus PDU���ģʽ����ת��ΪĬ��С��ģʽ������
 *
 * @param p_dst[out]   :  ���������
 * @param p_src[in]    :  �������ݻ�����
 * @param num_reg[in]  :  ���ƵļĴ�������2�ı���
 */
void am_mb_regcpy (void *p_dst, const void *p_src, uint16_t num_reg);

#ifdef __cplusplus
}
#endif

/* @} grp_am_if_mb_utils */

#endif /* } __AM_MB_UTILS_H */

/* end of file */
