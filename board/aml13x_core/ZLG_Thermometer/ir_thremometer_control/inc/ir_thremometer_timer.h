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
 * \brief ��ʱ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */
#ifndef _IR_THREMOMETER_TIMER_H_
#define _IR_THREMOMETER_TIMER_H_

#define TIMER_MS 10
#define POWER_OFF_TIMEOUT 1000
#define LCD_FLASH_TIMEOUT 100
/**
 * \brief ��ʱ����ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_timer_init(void);
/**
 * \brief �򿪶�ʱ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_timer_start(void);
/**
 * \brief �رն�ʱ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_timer_stop(void);
/**
 * \brief �������ֵ
 *
 * \param[in] ��
 *
 * \return ��
 */
void ir_thremometer_timer_clear_cnt(void);
/**
 * \brief ��ȡ����ֵ
 *
 * \param[in] ��
 *
 * \return ��
 */
uint32_t ir_thremometer_timer_get_cnt(void);
/**
 * \brief ����ʱ���ʱ
 *
 * \param[in] ��
 *
 * \return ��
 */
am_bool_t ir_thremometer_time_to_powe_off(void);

#endif
/* end of file */
