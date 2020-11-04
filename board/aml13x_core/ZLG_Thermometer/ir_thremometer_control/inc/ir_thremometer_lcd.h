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
 * \brief LCD��ʾ����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_LCD_H_
#define _IR_THREMOMETER_LCD_H_

typedef struct _display_t{
	uint32_t disp_flag;
	float num;
	uint8_t id;
	am_bool_t flash;
	am_bool_t update;
}display_t;
/**
 * \brief LCD��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_lcd_init(void);
/**
 * \brief LCD��ʾ
 *
 * \param[in] ��ʾ��Ϣ
 *
 * \return ��
 */
void ir_thremometer_lcd_display(display_t *p_display);
/**
 * \brief LCD��ʾ�¶�ֵ
 *
 * \param[in] num  �¶�ֵ
 *
 * \return ��
 */
void ir_thremometer_lcd_display_float(float num);
/**
 * \brief LCDȫ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_lcd_display_all(void);
/**
 * \brief LCD����
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_lcd_clear(void);

#endif
/* end of file */
