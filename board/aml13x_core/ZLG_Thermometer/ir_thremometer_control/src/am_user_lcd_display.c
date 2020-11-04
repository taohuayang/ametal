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
 * \brief LCD������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yjx, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "hc32x3x_pin.h"
#include "am_hc32l13x_inst_init.h"
#include "am_user_lcd_display.h"

/* ������ʾ�궨�� */

#define AMHW_USER_BT_LCDRAM                 (0)
#define AMHW_USER_BZ_LCDRAM                 (0)
#define AMHW_USER_0F_LCDRAM                 (0)
#define AMHW_USER_0C_LCDRAM                 (0)
#define AMHW_USER_P1_LCDRAM                 (1)
#define AMHW_USER_BT3_LCDRAM                (2)
#define AMHW_USER_LOG_LCDRAM                (0)
#define AMHW_USER_SUR_LCDRAM                (1)
#define AMHW_USER_KU_LCDRAM                 (2)
#define AMHW_USER_XIAO_LCDRAM               (3)
#define AMHW_USER_BLUE_LCDRAM               (3)
#define AMHW_USER_BODY_LCDRAM               (3)
#define AMHW_USER_BT2_LCDRAM                (3)
#define AMHW_USER_BT1_LCDRAM                (3)

#define AMHW_USER_BT_DISP                   (0x00000008)
#define AMHW_USER_BZ_DISP                   (0x00000004)
#define AMHW_USER_0F_DISP                   (0x00000002)
#define AMHW_USER_0C_DISP                   (0x00000001)
#define AMHW_USER_P1_DISP                   (0x00080000)
#define AMHW_USER_BT3_DISP                  (0x00000008)
#define AMHW_USER_LOG_DISP                  (0x00080000)
#define AMHW_USER_SUR_DISP                  (0x00000800)
#define AMHW_USER_KU_DISP                   (0x00080000)
#define AMHW_USER_XIAO_DISP                 (0x00000800)
#define AMHW_USER_BLUE_DISP                 (0x00080000)
#define AMHW_USER_BODY_DISP                 (0x00040000)
#define AMHW_USER_BT2_DISP                  (0x00020000)
#define AMHW_USER_BT1_DISP                  (0x00010000)

/* ����LCDRAM */
uint32_t __g_lcdram[4] = {0};

/**
 * \brief ��ʾ����
 *
 * \note : LCD��һ���ĸ�������ʾ��Ԫ��LCDÿ��������ʾ�������ֽڵĸ�����λ����
 */
static uint32_t lcd_datacode[] = 
{
    /** \brief ����0~9 */
    0x050f, 0x0006, 0x060b, 0x020f,
    0x0306, 0x030d, 0x070d, 0x0007,
    0x070f, 0x030f,

    0x0000,     /** \brief �հף�����ʾ��       */
    0x0709,     /** \brief ��ĸE                */
    0x0707,     /** \brief ��ĸR                */
    0x0508,     /** \brief ��ĸL                */
    0x060c,     /** \brief ��ĸo                */
    0x0706,     /** \brief ��ĸH                */
};

/* ��ʾ�ض��ַ�λ�ã������ַ��ڶ�����е�λ�� 
 * ���� 0~9 ռ�����ǰ10�����ض�λ�ô� 10 ��ʼ
 */
#define DISP_POS_BLANK          (10)
#define DISP_POS_E              (11)
#define DISP_POS_R              (12)
#define DISP_POS_L              (13)
#define DISP_POS_o              (14)
#define DISP_POS_H              (15)

/**
 * \brief LCD COM-SEG�˿ڳ�ʼ��������Ϣ�ṹ��
 *
 * \note : �û�ʹ��LCD��ʱ����Ҫ�Լ�����һ���ṹ�岢���
 *         ���û��ڿ��ƶ˿�ʱ1��ʾ��0��ʾ�رգ�
 */
static am_hc32_lcd_com_seg_t __g_lcd_com_seg_info =
{
    0x00006fff,     /**< \brief seg0-31�˿� */
    0xf,            /**< \brief seg32-35�˿� */
    0x0,            /**< \brief �ܽŹ���ѡ����CR0.DUTY����*/
    0x10,           /**< \brief seg40-51�˿� */
    0x1,            /**< \brief SEG32~SEG35�˿ڹ���ѡ�� */
    0xf,            /**< \brief COM0-3�˿ڹ���ѡ�� */
};

/**
 * \brief �û� LCD ��ʼ��
 */
am_lcd_handle_t am_user_lcd_disp_init (void)
{
    am_lcd_handle_t handle = am_hc32_lcd_inst_init();

    /* LCD COM SEG �˿����� */
    am_hc32_lcd_com_seg_init(handle, &__g_lcd_com_seg_info);

    /* LCD ѡ����ʾģʽ0����ʹ�� */
    am_hc32_lcd_enable(handle, AM_HC32_LCD_MODE_0);

    return handle;
}

/**
 * \brief �û� LCD ����
 */
int am_user_lcd_disp_clr (am_lcd_handle_t handle)
{
    int i = 0;

    amhw_hc32_lcd_t *p_hw_lcd;

    if (handle == NULL){

        return AM_ERROR;
    }

    p_hw_lcd = (amhw_hc32_lcd_t *)handle->p_devinfo->reg_base;

    /* ����Դ����� */
    for (i = 0; i < 4; i++){

        amhw_hc32_lcd_ram_write (p_hw_lcd, 0x0, i);
    }

    return AM_OK;
}

/****************(�������º����൱��һ��ȫ����������ʾdata)*******************/

/**
 * \brief �û� LCD д������
 */
int am_user_lcd_disp_float (am_lcd_handle_t handle,
                            float           data)
{
    amhw_hc32_lcd_t *p_hw_lcd;

    if (handle == NULL){
        return AM_ERROR;
    }

    p_hw_lcd = (amhw_hc32_lcd_t *)handle->p_devinfo->reg_base;

    uint8_t         i = 0;
    int             data_ten_times = 0;
    uint32_t        data_bit[4] = {0};
    uint32_t        data_div = 0;

    data_ten_times = (int)(data * 10);  /* �� data �Ŵ� 10 ����ȡ�� */
    data_div = data_ten_times;

    /* �����¶ȷ�Χ��32.9 ~ 42.0�������ڷ�Χ�ڣ��������ʾ ERR */
    if ( data_ten_times > 9999 ) {

//        data_bit[0] = DISP_POS_R;         //R
//        data_bit[1] = DISP_POS_R;         //R
//        data_bit[2] = DISP_POS_E;         //E
//        data_bit[3] = DISP_POS_BLANK;     //�հף�����ʾ

    } else {
        /* ��data��Ϊ0ʱ�������λ��dataΪ0ʱ����while */
        while (data_div != 0) {
            *(data_bit + i) = data_div % 10;
            i++;
            data_div /= 10;
        }

        /*  
            �˶����ã�����λΪ0ʱ����ʾ���� data = 0 ʱ��ֻ��ʾ��λ��0��
        ����
            ��λ����ȫ��ʾ                                  1357    ��ʾ 1357
            ��λ�������λ0����ʾ                           103     ��ʾ x103
            ��λ�������λ�ʹθ�λ��0����ʾ                 78      ��ʾ xx78
            һλ�����������λ��0����ʾ��ֻ��ʾ���λ       5       ��ʾ xxx5
                    ��������Ϊ0ʱ����ʾxxx0��
        */
        for (i = 3; i > 1; i--) {        /* �����λ���ε�λ�ж� */
            if (data_bit[i] != 0) {
                break;
            } else {
                data_bit[i] = DISP_POS_BLANK;
            }
        }
    }

    __g_lcdram[0] = ( (lcd_datacode[data_bit[0]] & 0xff ) << 24);

    __g_lcdram[1] = ( (lcd_datacode[data_bit[1]] & 0xff ) << 24)    |
                    ( (lcd_datacode[data_bit[0]] & 0xff00 ) << 8);

    __g_lcdram[2] = ( (lcd_datacode[data_bit[1]] & 0xff00 ) >> 8)    |
                    ( (lcd_datacode[data_bit[2]]) << 8 )            |
                    ( (lcd_datacode[data_bit[3]] & 0xff ) << 24);

    __g_lcdram[3] = ( (lcd_datacode[data_bit[3]] & 0xff00 ) << 8);

    __g_lcdram[AMHW_USER_P1_LCDRAM] |= AMHW_USER_P1_DISP;

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }

    return AM_OK;
}

/**
 * \brief �û� LCD ��ʾ��ر���
 */
int am_user_lcd_disp_alarm(am_lcd_handle_t              handle,
                           am_user_lcd_disp_alarm_t     alarm_type)
{
    amhw_hc32_lcd_t *p_hw_lcd;

    if (handle == NULL){
        return AM_ERROR;
    }

    p_hw_lcd = (amhw_hc32_lcd_t *)handle->p_devinfo->reg_base;

    uint8_t         i = 0;    
    uint32_t        data_bit[4] = {0};

    if (alarm_type == AM_USER_DISP_ERR) {

        data_bit[0] = DISP_POS_R;       /*  ��ĸR           */
        data_bit[1] = DISP_POS_R;       /*  ��ĸR           */
        data_bit[2] = DISP_POS_E;       /*  ��ĸE           */
        data_bit[3] = DISP_POS_BLANK;   /*  �հף�����ʾ    */

    } else if (alarm_type == AM_USER_DISP_LO) {

        data_bit[0] = DISP_POS_BLANK;   /* �հף�����ʾ��   */
        data_bit[1] = DISP_POS_o;       /* ��ĸo            */
        data_bit[2] = DISP_POS_L;       /* ��ĸL            */
        data_bit[3] = DISP_POS_BLANK;   /* �հף�����ʾ��   */

    } else if (alarm_type == AM_USER_DISP_HO) {

        data_bit[0] = DISP_POS_BLANK;   /* �հף�����ʾ��   */
        data_bit[1] = DISP_POS_o;       /* ��ĸo            */
        data_bit[2] = DISP_POS_H;       /* ��ĸH            */
        data_bit[3] = DISP_POS_BLANK;   /* �հף�����ʾ��   */
    } else {

    }

    __g_lcdram[0] = ( (lcd_datacode[data_bit[0]] & 0xff ) << 24);

    __g_lcdram[1] = ( (lcd_datacode[data_bit[1]] & 0xff ) << 24)    |
                    ( (lcd_datacode[data_bit[0]] & 0xff00 ) << 8);

    __g_lcdram[2] = ( (lcd_datacode[data_bit[1]] & 0xff00 ) >> 8)    |
                    ( (lcd_datacode[data_bit[2]]) << 8 )            |
                    ( (lcd_datacode[data_bit[3]] & 0xff ) << 24);

    __g_lcdram[3] = ( (lcd_datacode[data_bit[3]] & 0xff00 ) << 8);

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }

    return AM_OK;
}

/*****************************************************************************/

/**
 * \brief �û� LCD д��������ȡ����
 */
int am_user_lcd_disp_mem(am_lcd_handle_t    handle,
                         uint32_t           data)
{
    amhw_hc32_lcd_t *p_hw_lcd;

    if (handle == NULL){
        return AM_ERROR;
    }

    p_hw_lcd = (amhw_hc32_lcd_t *)handle->p_devinfo->reg_base;

    uint8_t         i = 0;
    uint32_t        data_bit[2] = {0};
    uint32_t        data_div = data;

    if (data > 99) {
        
    } else {
        /* ��data��Ϊ0ʱ�������λ��dataΪ0ʱ����while */
        while (data_div != 0) {
            *(data_bit + i) = data_div % 10;
            i++;
            data_div /= 10;
        }

        __g_lcdram[0] = ( __g_lcdram[0] & 0xfff8f0ff ) |
                        ( (lcd_datacode[data_bit[0]]) << 8 );
        
        __g_lcdram[1] = ( __g_lcdram[1] & 0xfffff8f0 ) |
                        ( (lcd_datacode[data_bit[1]]) );

    }

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }

    return AM_OK;
}

/**
 * \brief �û� LCD ������ʾʹ��
 */
int am_user_lcd_disp_flag_enable(am_lcd_handle_t    handle,
                                 uint32_t           flags)
{
    
    amhw_hc32_lcd_t *p_hw_lcd;

    if (handle == NULL){
        return AM_ERROR;
    }

    p_hw_lcd = (amhw_hc32_lcd_t *)handle->p_devinfo->reg_base;

    uint8_t         i = 0;

    if (flags & AM_USER_BT_DISP) {
        __g_lcdram[AMHW_USER_BT_LCDRAM] |= AMHW_USER_BT_DISP;
    }

    if (flags & AM_USER_BZ_DISP) {
        __g_lcdram[AMHW_USER_BZ_LCDRAM] |= AMHW_USER_BZ_DISP;
    }

    if (flags & AM_USER_0F_DISP) {
        __g_lcdram[AMHW_USER_0F_LCDRAM] |= AMHW_USER_0F_DISP;
    }

    if (flags & AM_USER_0C_DISP) {
        __g_lcdram[AMHW_USER_0C_LCDRAM] |= AMHW_USER_0C_DISP;
    }

    if (flags & AM_USER_P1_DISP) {
        __g_lcdram[AMHW_USER_P1_LCDRAM] |= AMHW_USER_P1_DISP;
    }

    if (flags & AM_USER_BT3_DISP) {
        __g_lcdram[AMHW_USER_BT3_LCDRAM] |= AMHW_USER_BT3_DISP;
    }

    if (flags & AM_USER_LOG_DISP) {
        __g_lcdram[AMHW_USER_LOG_LCDRAM] |= AMHW_USER_LOG_DISP;
    }

    if (flags & AM_USER_SUR_DISP) {
        __g_lcdram[AMHW_USER_SUR_LCDRAM] |= AMHW_USER_SUR_DISP;
    }

    if (flags & AM_USER_KU_DISP) {
        __g_lcdram[AMHW_USER_KU_LCDRAM] |= AMHW_USER_KU_DISP;
    }

    if (flags & AM_USER_XIAO_DISP) {
        __g_lcdram[AMHW_USER_XIAO_LCDRAM] |= AMHW_USER_XIAO_DISP;
    }

    if (flags & AM_USER_BLUE_DISP) {
        __g_lcdram[AMHW_USER_BLUE_LCDRAM] |= AMHW_USER_BLUE_DISP;
    }

    if (flags & AM_USER_BODY_DISP) {
        __g_lcdram[AMHW_USER_BODY_LCDRAM] |= AMHW_USER_BODY_DISP;
    }

    if (flags & AM_USER_BT2_DISP) {
        __g_lcdram[AMHW_USER_BT2_LCDRAM] |= AMHW_USER_BT2_DISP;
    }

    if (flags & AM_USER_BT1_DISP) {
        __g_lcdram[AMHW_USER_BT1_LCDRAM] |= AMHW_USER_BT1_DISP;
    }

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }

    return AM_OK;
}

/**
 * \brief �û� LCD ������ʾ����
 */
int am_user_lcd_disp_flag_disable(am_lcd_handle_t    handle,
                                  uint32_t           flags)
{
    
    amhw_hc32_lcd_t *p_hw_lcd;

    if (handle == NULL){
        return AM_ERROR;
    }

    p_hw_lcd = (amhw_hc32_lcd_t *)handle->p_devinfo->reg_base;

    uint8_t         i = 0;

    if (flags & AM_USER_BT_DISP) {
        __g_lcdram[AMHW_USER_BT_LCDRAM] &= (~AMHW_USER_BT_DISP);
    }

    if (flags & AM_USER_BZ_DISP) {
        __g_lcdram[AMHW_USER_BZ_LCDRAM] &= (~AMHW_USER_BZ_DISP);
    }

    if (flags & AM_USER_0F_DISP) {
        __g_lcdram[AMHW_USER_0F_LCDRAM] &= (~AMHW_USER_0F_DISP);
    }

    if (flags & AM_USER_0C_DISP) {
        __g_lcdram[AMHW_USER_0C_LCDRAM] &= (~AMHW_USER_0C_DISP);
    }

    if (flags & AM_USER_P1_DISP) {
        __g_lcdram[AMHW_USER_P1_LCDRAM] &= (~AMHW_USER_P1_DISP);
    }

    if (flags & AM_USER_BT3_DISP) {
        __g_lcdram[AMHW_USER_BT3_LCDRAM] &= (~AMHW_USER_BT3_DISP);
    }

    if (flags & AM_USER_LOG_DISP) {
        __g_lcdram[AMHW_USER_LOG_LCDRAM] &= (~AMHW_USER_LOG_DISP);
    }

    if (flags & AM_USER_SUR_DISP) {
        __g_lcdram[AMHW_USER_SUR_LCDRAM] &= (~AMHW_USER_SUR_DISP);
    }

    if (flags & AM_USER_KU_DISP) {
        __g_lcdram[AMHW_USER_KU_LCDRAM] &= (~AMHW_USER_KU_DISP);
    }

    if (flags & AM_USER_XIAO_DISP) {
        __g_lcdram[AMHW_USER_XIAO_LCDRAM] &= (~AMHW_USER_XIAO_DISP);
    }

    if (flags & AM_USER_BLUE_DISP) {
        __g_lcdram[AMHW_USER_BLUE_LCDRAM] &= (~AMHW_USER_BLUE_DISP);
    }

    if (flags & AM_USER_BODY_DISP) {
        __g_lcdram[AMHW_USER_BODY_LCDRAM] &= (~AMHW_USER_BODY_DISP);
    }

    if (flags & AM_USER_BT2_DISP) {
        __g_lcdram[AMHW_USER_BT2_LCDRAM] &= (~AMHW_USER_BT2_DISP);
    }

    if (flags & AM_USER_BT1_DISP) {
        __g_lcdram[AMHW_USER_BT1_LCDRAM] &= (~AMHW_USER_BT1_DISP);
    }

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }

    return AM_OK;
}

/* end of file */

