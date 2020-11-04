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
 * \brief �������
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_BACKLIGHT_H_
#define _IR_THREMOMETER_BACKLIGHT_H_
/*******************************************************************************
* ˽�ж���
*******************************************************************************/
/**
 * \brief ģʽ��Ϣ
 */
typedef enum _backlight_mode_t {
	BACKLIGNT_RED = 0,
	BACKLIGNT_GREEN,
	BACKLIGNT_ORANGE,
} backlight_mode_t;
/**
 * \brief ����Ƴ�ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_backlight_init(void);
/**
 * \brief ��������
 *
 * \param[in] mode �����ģʽ  ��ͬģʽ��
 *
 * \return ��
 */
void ir_thremometer_backlight_on(backlight_mode_t mode);
/**
 * \brief �رձ����
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_backlight_off(void);


#endif
/* end of file */
