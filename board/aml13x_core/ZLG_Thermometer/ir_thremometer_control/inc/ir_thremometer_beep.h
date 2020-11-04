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
 * \brief ����������
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_BEEP_H_
#define _IR_THREMOMETER_BEEP_H_
/*******************************************************************************
* ˽�ж���
*******************************************************************************/
/**
 * \brief ģʽ��Ϣ
 */
typedef enum _beep_nosie_t {
	BEEP_LONG_NOISE = 0,
	BEEP_SHORT_NOISE,
}beep_nosie_t;
/**
 * \brief ��������ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_beep_init(void);
/**
 * \brief ���ܺ�����ʼ��
 *
 * \param[in] times  ���д���
 * \param[in] nosie  �������ͣ����� BEEP_LONG_NOISE  �̽� BEEP_SHORT_NOISE
 *
 * \return ��
 */
void ir_thremometer_beep_on(uint32_t times, beep_nosie_t nosie);

#endif
/* end of file */
