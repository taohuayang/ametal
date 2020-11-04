#ifndef __AM_USER_LCD_DISPLAY_H
#define __AM_USER_LCD_DISPLAY_H

#include "am_common.h"
#include "am_hc32_lcd.h"

#define AM_USER_BT_DISP         (0x0001)        /* ��������    */
#define AM_USER_BZ_DISP         (0x0002)        /* ������        */
#define AM_USER_0F_DISP         (0x0004)        /* ���϶ȵ�λ    */
#define AM_USER_0C_DISP         (0x0008)        /* ���϶ȵ�λ    */
#define AM_USER_P1_DISP         (0x0010)        /* С����        */
#define AM_USER_BT3_DISP        (0x0020)        /* ������        */
#define AM_USER_LOG_DISP        (0x0040)        /* ����          */
#define AM_USER_SUR_DISP        (0x0080)        /* �����¶�      */
#define AM_USER_KU_DISP         (0x0100)        /* ����          */
#define AM_USER_XIAO_DISP       (0x0200)        /* Ц��          */
#define AM_USER_BLUE_DISP       (0x0400)        /* ����          */
#define AM_USER_BODY_DISP       (0x0800)        /* ����          */
#define AM_USER_BT2_DISP        (0x1000)        /* ������        */
#define AM_USER_BT1_DISP        (0x2000)        /* ������        */

/**
 * \brief �û� LCD ��ʼ��
 */
am_lcd_handle_t am_user_lcd_disp_init (void);

/**
 * \brief �û� LCD ����
 */
int am_user_lcd_disp_clr (am_lcd_handle_t handle);

/**
 * \brief �û� LCD д������ (���ô˺����൱��һ��ȫ����������ʾdata),������
 */
int am_user_lcd_disp_float (am_lcd_handle_t handle,
                            float           data);

/**
 * \brief �û� LCD ��ʾ����,������
 */
int am_user_lcd_disp_err(am_lcd_handle_t    handle);


/**
 * \brief �û� LCD д��������ȡ����
 */
int am_user_lcd_disp_mem(am_lcd_handle_t    handle,
                         uint32_t           data);

/* ���º���flags����Ϊ  AM_USER_BT_DISP */
/**
 * \brief �û� LCD ������ʾʹ��
 */
int am_user_lcd_disp_flag_enable(am_lcd_handle_t    handle,
                                 uint32_t           flags);

/**
 * \brief �û� LCD ������ʾ����
 */
int am_user_lcd_disp_flag_disable(am_lcd_handle_t    handle,
                                  uint32_t           flags);

#endif

