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
 * \brief ��Դ����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_POWER_H_
#define _IR_THREMOMETER_POWER_H_
/**
 * \brief ��ԴIO��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_power_init(void);
/**
 * \brief ��Դ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_power_on(void);
/**
 * \brief ��Դ�ر�
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_power_off(void);

#endif
/* end of file */
