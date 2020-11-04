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
 * \brief ��������������
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_ADC_H_
#define _IR_THREMOMETER_ADC_H_

#include "ir_thremometer.h"
/**
 * \brief ����ADC��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_adc_init(void);
/**
 * \brief ��ȡNTC��ֵ
 *
 * \param[in] ��
 *
 * \return NTC��ֵ
 */
float ir_thremometer_get_ntc_res(void);
/**
 * \brief ��ȡ�������ѹ��
 *
 * \param[in] ��
 *
 * \return ���ѹ��
 */
float ir_thremometer_get_ir_vol(void);
/**
 * \brief ��ȡĿ���¶�
 *
 * \param[in] ��
 *
 * \return Ŀ���¶�
 */
float ir_thremometer_get_obj_temp(void);
/**
 * \brief ��ȡ��ص�ѹ
 *
 * \param[in] ��
 *
 * \return ��ص�ѹ
 */
uint32_t ir_thremometer_get_bat_vol(void);
/**
 * \brief ��ȡУ׼��������
 *
 * \param[in] obj_temp  Ŀ���¶�
 * \param[in] vol_real  ��ʵѹ��
 * \param[in] vol_in_table  VT�����
 *
 * \return У׼ϵ��
 */
void ir_thremometer_calibration_vol(float obj_temp, float* vol_real, float* vol_in_table);
/**
 * \brief ����У׼ϵ��
 *
 * \param[in] k  У׼ϵ��K
 * \param[in] b  У׼ϵ��B
 *
 * \return ��
 */
void ir_thremometer_set_calib_pram(float k, float b);
/**
 * \brief ADC�ο�ԴУ׼
 *
 * \param[in] ��
 *
 * \return ��
  */
void ir_thremometer_adc_calib(void);

#endif

/* end of file */
