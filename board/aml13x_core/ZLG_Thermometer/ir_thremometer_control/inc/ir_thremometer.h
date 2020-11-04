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
 * \brief ����ǹ���ܺ���
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_H_
#define _IR_THREMOMETER_H_

/*******************************************************************************
* ˽�ж���
*******************************************************************************/
/**
 * \brief ģʽ��Ϣ
 */
typedef enum _measure_mode_t {
	MEASURE_BODY_MODE = 0,
	MEASURE_THING_MODE,
} measure_mode_t;
/**
 * \brief ��λ��Ϣ
 */
typedef enum _unit_t {
	UNIT_DAGREE_CELSIUS = 0,
	UNIT_FAHRENHRIT,
} unit_t;
/**
 * \brief ���ܺ�����ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_init(void);
/**
 * \brief ���ܺ���
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_run(void);

#endif
/* end of file */
