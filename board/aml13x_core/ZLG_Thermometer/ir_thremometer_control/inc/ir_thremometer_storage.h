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
 * \brief �洢����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_STORAGE_H_
#define _IR_THREMOMETER_STORAGE_H_

#include "ir_thremometer.h"

typedef struct _record_t{
	uint8_t id;
	float temp;
}record_t;
/**
 * \brief �洢��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_storage_init(void);
/**
 * \brief �洢�¶ȡ�ģʽ��λ��Ϣ
 *
 * \param[in] temp Ŀ�굥λ
 * \param[in] mode ģʽ
 * \param[in] unit ��λ
 *
 * \return ��
 */
int ir_thremometer_storage_temp(float temp, measure_mode_t mode, unit_t unit);
/**
 * \brief �洢У׼ֵ
 *
 * \param[in] data У׼ϵ��
 *
 * \return ��
 */
int ir_thremometer_storage_k(float data);
/**
 * \brief �洢У׼ֵ
 *
 * \param[in] data У׼ϵ��
 *
 * \return ��
 */
int ir_thremometer_storage_b(float data);
/**
 * \brief ��ȡ�洢�¶ȡ�ģʽ��λ��Ϣ
 *
 * \param[in] temp Ŀ�굥λ
 * \param[in] mode ģʽ
 * \param[in] unit ��λ
 *
 * \return ��
 */
void ir_thremometer_storage_load_record(record_t* p_record, measure_mode_t* p_mode, unit_t* p_unit);
/**
 * \brief У׼������ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_calib_init(void);
/**
 * \brief У׼�������
 *
 * \param[in] ��
 *
 * \return У����
 */
int ir_thremometer_storage_check_k_b(void);
/**
 * \brief ����У׼ֵ
 *
 * \param[in] ��
 *
 * \return ���ý��
 */
int ir_thremometer_storage_set_k_b_flag(void);
/**
 * \brief ��� �洢����ֵID
 *
 * \param[in] ��
 *
 * \return �����
 */
am_bool_t ir_thremometer_storage_check_in_record(uint8_t id);
/**
 * \brief �洢�¶ȡ�ģʽ��λ��Ϣ
 *
 * \param[in] start_addr ��ַ
 * \param[in] p_buf �洢����
 * \param[in] len ����
 *
 * \return ��
 */
int ir_thremometer_storage_write(int start_addr, uint8_t *p_buf, int len);
/**
 * \brief ��ȡ�洢�¶ȡ�ģʽ��λ��Ϣ
 *
 * \param[in] start_addr ��ַ
 * \param[in] p_buf �洢����
 * \param[in] len ����
 *
 * \return ��
 */
int ir_thremometer_storage_reead(int start_addr, uint8_t *p_buf, int len);

#endif
/* end of file */
