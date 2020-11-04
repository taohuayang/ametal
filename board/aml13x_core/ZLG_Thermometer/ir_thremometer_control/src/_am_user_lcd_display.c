/**
 * \file
 * \brief LCD������ʵ��
 *
 */

#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "hc32x3x_pin.h"
#include "am_hc32l13x_inst_init.h"
#include "am_user_lcd_display.h"

/* ������ʾ�궨�� */
#define AMHW_USER_BT_DISP         (0x00000008)//0
#define AMHW_USER_BZ_DISP         (0x00000004)//0
#define AMHW_USER_0F_DISP         (0x00000002)//0
#define AMHW_USER_0C_DISP         (0x00000001)//0
#define AMHW_USER_P1_DISP         (0x00080000)//1
#define AMHW_USER_BT3_DISP        (0x00000008)//2
#define AMHW_USER_LOG_DISP        (0x00080000)//0
#define AMHW_USER_SUR_DISP        (0x00000800)//1
#define AMHW_USER_KU_DISP         (0x00080000)//2
#define AMHW_USER_XIAO_DISP       (0x00000800)//3
#define AMHW_USER_BLUE_DISP       (0x00080000)//3
#define AMHW_USER_BODY_DISP       (0x00040000)//3
#define AMHW_USER_BT2_DISP        (0x00020000)//3
#define AMHW_USER_BT1_DISP        (0x00010000)//3

/* ����LCDRAM */
uint32_t __g_lcdram[4] = {0};

/**
 * \brief ��ʾ����
 *
 * \note : LCD��һ���ĸ�������ʾ��Ԫ��LCDÿ��������ʾ�������ֽڵĸ�����λ����,
 *         ����0-9 �����룺
 *                      0-------0x0a0f
 *                      1-------0x0006
 *                      2-------0x060d
 *                      3-------0x040f
 *                      4-------0x0c06
 *                      5-------0x0c0b
 *                      6-------0x0e0b
 *                      7-------0x000e
 *                      8-------0x0e0f
 *                      9-------0x0c0f
 *                      .-------0x0100
 *                      x-------0x0000 (x ��ʾ����ʾ)
 *
 */
static uint32_t lcd_datacode[14] = {
    0x050F, 0x0006, 0x060B, 0x020F,
    0x0306, 0x030D, 0x070D, 0x0007,
    0x070F, 0x030F, 0x0008, 0x0000,
    0x0709, 0x0707
};

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
        
        data_bit[0] = 11;
        data_bit[1] = 13;
        data_bit[2] = 13;
        data_bit[3] = 12;

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
                data_bit[i] = 11;
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

    __g_lcdram[1] |= 0x00080000;

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }

    return AM_OK;
}

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
        
        __g_lcdram[0] = ( __g_lcdram[0] & 0xfffff80f ) |
                        ( (lcd_datacode[data_bit[0]]) << 8 );
        
        __g_lcdram[1] = ( __g_lcdram[1] & 0xffffff80 ) |
                        ( (lcd_datacode[data_bit[1]]) );
        
    }

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }
    
    return AM_OK;
}

/**
 * \brief �û� LCD ��ʾ����
 */
int am_user_lcd_disp_err(am_lcd_handle_t    handle)
{
    amhw_hc32_lcd_t *p_hw_lcd;

    if (handle == NULL){
        return AM_ERROR;
    }

    p_hw_lcd = (amhw_hc32_lcd_t *)handle->p_devinfo->reg_base;

    uint8_t         i = 0;    
    uint32_t        data_bit[4] = {0};
    
    data_bit[0] = 13;
    data_bit[1] = 13;
    data_bit[2] = 12;
    data_bit[3] = 11;

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
        __g_lcdram[0] |= AMHW_USER_BT_DISP;
    }

    if (flags & AM_USER_BZ_DISP) {
        __g_lcdram[0] |= AMHW_USER_BZ_DISP;
    }

    if (flags & AM_USER_0F_DISP) {
        __g_lcdram[0] |= AMHW_USER_0F_DISP;
    }

    if (flags & AM_USER_0C_DISP) {
        __g_lcdram[0] |= AMHW_USER_0C_DISP;
    }

    if (flags & AM_USER_P1_DISP) {
        __g_lcdram[1] |= AMHW_USER_P1_DISP;
    }

    if (flags & AM_USER_BT3_DISP) {
        __g_lcdram[2] |= AMHW_USER_BT3_DISP;
    }

    if (flags & AM_USER_LOG_DISP) {
        __g_lcdram[0] |= AMHW_USER_LOG_DISP;
    }

    if (flags & AM_USER_SUR_DISP) {
        __g_lcdram[1] |= AMHW_USER_SUR_DISP;
    }

    if (flags & AM_USER_KU_DISP) {
        __g_lcdram[2] |= AMHW_USER_KU_DISP;
    }

    if (flags & AM_USER_XIAO_DISP) {
        __g_lcdram[3] |= AMHW_USER_XIAO_DISP;
    }

    if (flags & AM_USER_BLUE_DISP) {
        __g_lcdram[3] |= AMHW_USER_BLUE_DISP;
    }

    if (flags & AM_USER_BODY_DISP) {
        __g_lcdram[3] |= AMHW_USER_BODY_DISP;
    }

    if (flags & AM_USER_BT2_DISP) {
        __g_lcdram[3] |= AMHW_USER_BT2_DISP;
    }

    if (flags & AM_USER_BT1_DISP) {
        __g_lcdram[3] |= AMHW_USER_BT1_DISP;
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
        __g_lcdram[0] &= (~AMHW_USER_BT_DISP);
    }

    if (flags & AM_USER_BZ_DISP) {
        __g_lcdram[0] &= (~AMHW_USER_BZ_DISP);
    }

    if (flags & AM_USER_0F_DISP) {
        __g_lcdram[0] &= (~AMHW_USER_0F_DISP);
    }

    if (flags & AM_USER_0C_DISP) {
        __g_lcdram[0] &= (~AMHW_USER_0C_DISP);
    }

    if (flags & AM_USER_P1_DISP) {
        __g_lcdram[1] &= (~AMHW_USER_P1_DISP);
    }

    if (flags & AM_USER_BT3_DISP) {
        __g_lcdram[2] &= (~AMHW_USER_BT3_DISP);
    }

    if (flags & AM_USER_LOG_DISP) {
        __g_lcdram[0] &= (~AMHW_USER_LOG_DISP);
    }

    if (flags & AM_USER_SUR_DISP) {
        __g_lcdram[1] &= (~AMHW_USER_SUR_DISP);
    }

    if (flags & AM_USER_KU_DISP) {
        __g_lcdram[2] &= (~AMHW_USER_KU_DISP);
    }

    if (flags & AM_USER_XIAO_DISP) {
        __g_lcdram[3] &= (~AMHW_USER_XIAO_DISP);
    }

    if (flags & AM_USER_BLUE_DISP) {
        __g_lcdram[3] &= (~AMHW_USER_BLUE_DISP);
    }

    if (flags & AM_USER_BODY_DISP) {
        __g_lcdram[3] &= (~AMHW_USER_BODY_DISP);
    }

    if (flags & AM_USER_BT2_DISP) {
        __g_lcdram[3] &= (~AMHW_USER_BT2_DISP);
    }

    if (flags & AM_USER_BT1_DISP) {
        __g_lcdram[3] &= (~AMHW_USER_BT1_DISP);
    }

    for (i = 0; i < 4; i++) {
        amhw_hc32_lcd_ram_write (p_hw_lcd, __g_lcdram[i], i);
    }

    return AM_OK;
}

/* end of file */

