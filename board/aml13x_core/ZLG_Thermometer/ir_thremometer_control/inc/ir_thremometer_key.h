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
#ifndef _IR_THREMOMETER_KEY_H_
#define _IR_THREMOMETER_KEY_H_
/**
 * \brief �����¼�
 */
typedef enum _key_press_t {
	KEY_1_SHORT_PRESSED = 0,
	KEY_2_SHORT_PRESSED,
	KEY_3_SHORT_PRESSED,
	KEY_4_SHORT_PRESSED,
	KEY_1_LONG_PRESSED,
	KEY_2_LONG_PRESSED,
	KEY_3_LONG_PRESSED,
	KEY_4_LONG_PRESSED,
	KEY_1_LONG_PRESSED_10S,
	KEY_PRESSING,
	KEY_RELEASE,
} key_press_t;
/**
 * \brief ������ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_key_init(void);
/**
 * \brief �����¼���ȡ
 *
 * \param[in] ��
 *
 * \return �����¼�
 */
key_press_t ir_thremometer_get_key(void);
/**
 * \brief �����ͷ�
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_release_key(void);
/**
 * \brief ���ð�����ֵ
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_set_default_key(void);

#endif
/* end of file */
