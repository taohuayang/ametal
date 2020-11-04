/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief LCD �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 19-10-14
 * \endinternal
 */

#ifndef __AMHW_ZLG118_LCD_H
#define __AMHW_ZLG118_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zlg118_if_lcd
 * \copydoc amhw_zlg118_lcd.h
 * @{
 */

/**
 * \brief LCD - �Ĵ�����
 */
typedef struct amhw_zlg118_lcd {
    __IO uint32_t lcdcr0;        /**< \brief LCD���üĴ���0 */
    __IO uint32_t lcdcr1;        /**< \brief LCD���üĴ���1 */
    __IO uint32_t lcdintclr;     /**< \brief LCD�ж�����Ĵ��� */
    __IO uint32_t lcdpoen0;      /**< \brief LCD������üĴ���0 */
    __IO uint32_t lcdpoen1;      /**< \brief LCD������üĴ���1 */
         uint32_t res[11];       /**< \brief ���� */
    __IO uint32_t lcdram0_f[16]; /**< \brief LCD RAM0~f */
} amhw_zlg118_lcd_t;

/**
 * \brief LCD�Աȶ�����,contrastֵһ��16���ȼ���
 */
typedef enum amhw_zlg118_lcd_ctr_val {
    AHHW_ZLG118_CTR_1 = 0,
    AHHW_ZLG118_CTR_2,
    AHHW_ZLG118_CTR_3,
    AHHW_ZLG118_CTR_4,
    AHHW_ZLG118_CTR_5,
    AHHW_ZLG118_CTR_6,
    AHHW_ZLG118_CTR_7,
    AHHW_ZLG118_CTR_8,
    AHHW_ZLG118_CTR_9,
    AHHW_ZLG118_CTR_10,
    AHHW_ZLG118_CTR_11,
    AHHW_ZLG118_CTR_12,
    AHHW_ZLG118_CTR_13,
    AHHW_ZLG118_CTR_14,
    AHHW_ZLG118_CTR_15,
    AHHW_ZLG118_CTR_16
}amhw_zlg118_lcd_ctr_val_t;

/**
 * \brief LCD�Աȶȵ���
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : contrastֵ���ο�ö�ٶ��壺LCD�Աȶ�����
 *
 * \note : ����Bias��ѹ��Դѡ���ڲ������ѹʱ��Ч
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lcd_ctr_set (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr0 = (p_hw_lcd->lcdcr0 & (~(0xf << 12))) | (flag << 12);
}

/**
 * \brief Bias��ѹ��Դѡ������
 */
#define AMHW_ZLG118_LCD_BIAS_EXT_RES  (0U)   /**< \brief �ⲿ����ģʽ����Ҫ�ⲿ��·��� */
#define AMHW_ZLG118_LCD_BIAS_CAP_DIV  (1U)   /**< \brief ���ݷ�ѹģʽ����Ҫ�ⲿ��·���*/

/**< \brief �ڲ������ѹ���й���ģʽ*/
#define AMHW_ZLG118_LCD_BIAS_INT_RES_DIV_POWER_MID   (2U)
/**< \brief �ڲ������ѹ��С����ģʽ*/
#define AMHW_ZLG118_LCD_BIAS_INT_RES_DIV_POWER_LOW   (4U)
/**< \brief �ڲ������ѹ���󹦺�ģʽ*/
#define AMHW_ZLG118_LCD_BIAS_INT_RES_DIV_POWER_HIGH  (6U)

/**
 * \brief Bias��ѹ��Դѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ƫ�õ�ѹ���ο�ö�궨�壺Bias��ѹ��Դѡ������
 *
 */
am_static_inline
void amhw_zlg118_lcd_bias_rsc_sel (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr0 = (p_hw_lcd->lcdcr0 & (~(0x7 << 9))) | (flag << 9);
}

/**
 * \brief LCD duty����
 */
typedef enum amhw_zlg118_lcd_duty {
    AMHW_ZLG118_DUTY_STATIC = 0,
    AMHW_ZLG118_DUTY_1_2,
    AMHW_ZLG118_DUTY_1_3,
    AMHW_ZLG118_DUTY_1_4,
    AMHW_ZLG118_DUTY_1_6 = 5,
    AMHW_ZLG118_DUTY_1_8 = 7,
}amhw_zlg118_lcd_duty_t;

/**
 * \brief LCD duty����
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ƫ�õ�ѹ���ο�ö�ٶ��壺LCD duty����
 *
 * \retval : ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_duty_sel (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr0 = (p_hw_lcd->lcdcr0 & (~(0x7 << 6))) | (flag << 6);
}

/**
 * \biref ƫ�õ�ѹ��������
 */
#define AMHW_ZLG118_BIAS_1_3  (0U)  /**< \brief 1/3 bias */
#define AMHW_ZLG118_BIAS_1_2  (1U)  /**< \brief 1/2 bias */

/**
 * \brief LCD duty����
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ƫ�õ�ѹ���ο��궨�壺ƫ�õ�ѹ��������
 *
 * \retval : ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_bias_sel (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr0 |= (p_hw_lcd->lcdcr0 & ~(0x1 << 5)) | (flag << 5);
}

/**
 * \biref ��ѹ��ʱ��Ƶ��ѡ������
 */
#define AMHW_ZLG118_CPCLK_2K_HZ  (0U)  /**< \brief 2k Hz */
#define AMHW_ZLG118_CPCLK_4K_HZ  (1U)  /**< \brief 4k Hz */
#define AMHW_ZLG118_CPCLK_8K_HZ  (2U)  /**< \brief 8k Hz */
#define AMHW_ZLG118_CPCLK_16K_HZ (3U)  /**< \brief 16k Hz */

/**
 * \brief ��ѹ��ʱ��Ƶ��ѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ƫ�õ�ѹ���ο��궨�壺��ѹ��ʱ��Ƶ��ѡ��
 *
 * \retval : ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_cpclk_sel (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr0 = (p_hw_lcd->lcdcr0 & (~(0x3 << 3))) | (flag << 3);
}

/**
 * \biref LCDɨ��Ƶ��ѡ������
 */
#define AMHW_ZLG118_LCDCLK_64_HZ   (0U)  /**< \brief 64 Hz */
#define AMHW_ZLG118_LCDCLK_128_HZ  (1U)  /**< \brief 128 Hz */
#define AMHW_ZLG118_LCDCLK_256_HZ  (2U)  /**< \brief 256 Hz */
#define AMHW_ZLG118_LCDCLK_512_HZ  (3U)  /**< \brief 512 Hz */

/**
 * \brief LCDɨ��Ƶ��ѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ƫ�õ�ѹ���ο��궨�壺LCDɨ��Ƶ��ѡ��
 *
 * \note : LCD֡Ƶ�� = LCDɨ��Ƶ�ʡ�Duty
 *
 * \retval : ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_cldclk_sel (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr0 = (p_hw_lcd->lcdcr0 & (~(0x3 << 1))) | (flag << 1);
}

/**
 * \brief LCDʹ��
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 * \retval : ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_enable (amhw_zlg118_lcd_t *p_hw_lcd)
{
    p_hw_lcd->lcdcr0 |= (1 << 0);
}

/**
 * \brief LCD����
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 * \retval : ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_disable (amhw_zlg118_lcd_t *p_hw_lcd)
{
    p_hw_lcd->lcdcr0 &= ~(1 << 0);
}

/**
 * \brief LCD�ж�״̬��ȡ
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 * \retval : 1 �ж�  0 ���ж�
 *
 */
am_static_inline
int amhw_zlg118_lcd_int_stu_check (amhw_zlg118_lcd_t *p_hw_lcd)
{
    return (p_hw_lcd->lcdcr0 >> 11);
}

/**
 * \brief �ж�ʹ��
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_int_enable (amhw_zlg118_lcd_t *p_hw_lcd)
{
    p_hw_lcd->lcdcr1 |= (1 << 9);
}

/**
 * \brief �жϽ���
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_int_disable (amhw_zlg118_lcd_t *p_hw_lcd)
{
    p_hw_lcd->lcdcr1 &= ~(1 << 9);
}

/**
 * \brief �жϱ�־���
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_int_flag_clr (amhw_zlg118_lcd_t *p_hw_lcd)
{
    p_hw_lcd->lcdintclr &= ~(1 << 10);
}

/**
 * \brief DMAӲ������ʹ��
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_dma_enable (amhw_zlg118_lcd_t *p_hw_lcd)
{
    p_hw_lcd->lcdcr1 |= (1 << 10);
}

/**
 * \brief DMAӲ����������
 *
 * \param[in] p_hw_lcd: ָ��LCD�Ĵ������ָ��
 *
 */
am_static_inline
void amhw_zlg118_lcd_dma_disable (amhw_zlg118_lcd_t *p_hw_lcd)
{
    p_hw_lcd->lcdcr1 &= ~(1 << 10);
}

/**
 * \brief LCD RAM��ʾģʽѡ������
 */
#define AMHW_ZLG118_LCD_MODE_0  (0U)
#define AMHW_ZLG118_LCD_MODE_1  (1U)

/**
 * \brief LCD RAM��ʾģʽѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ģʽ���ο��궨�壺LCD RAM��ʾģʽѡ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lcd_mode_sel (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr1 = (p_hw_lcd->lcdcr1 & ~(1 << 8)) | (flag << 8);
}

/**
 * \brief LCDʱ��Դѡ������
 */
#define AMHW_ZLG118_LCD_CLK_SRC_XTL  (1U)
#define AMHW_ZLG118_LCD_CLK_SRC_RCL  (0U)

/**
 * \brief LCDʱ��Դѡ��ѡ��
 *
 * \param[in] p_hw_lcd  : ָ��LCD�Ĵ������ָ��
 * \param[in] flag      : ʱ��Դ���ο��궨�壺LCDʱ��Դѡ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lcd_clk_rsc_sel (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->lcdcr1 = (p_hw_lcd->lcdcr1 & ~(1 << 7)) | (flag << 7);
}

/**
 * \brief ����Ƶ����LCD�жϼ������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] val      : Blinkcntֵ
 *
 * \note : ע��LCD��˸Ƶ��Ϊ = LCD֡Ƶ�� / (BlinkCnt+1)
 *            LCD�жϼ��= (BlinkCnt+1)*(1/LCD ֡Ƶ��)
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_blink_cnt_set (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t val)
{
    p_hw_lcd->lcdcr1 = (p_hw_lcd->lcdcr1 & (~(0x3f))) | (val << 0);
}

/**
 * \brief Seg0_31�������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ��Ҫ���ƿ�����رյ�Segλ
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_seg0_31_ctr (amhw_zlg118_lcd_t *p_hw_lcd, uint32_t flag)
{

    p_hw_lcd->lcdpoen0 &= ~flag;
}

/**
 * \brief Seg32_51_Com0_8��������
 */
#define AMHW_ZLG118_LCD_SEG32_35_CTR  0    /**< \brief seg32-35 */
#define AMHW_ZLG118_LCD_COM0_3_CTR    1    /**< \brief COM0-3 */
#define AMHW_ZLG118_LCD_COMSEG_CTR    2    /**< \brief COM4-7 seg36-39 */
#define AMHW_ZLG118_LCD_MUX_CTR       3    /**< \brief SEG32~SEG35�˿ڹ���ѡ�� */
#define AMHW_ZLG118_LCD_SEG40_51_CTR  4    /**< \brief seg40-51 */
#define AMHW_ZLG118_LCD_ALL_CLOSE     5    /**< \brief ���п�������ر�*/

/**
 * \brief Seg32_51_Com0_8�������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : Seg32_51_Com0_8������
 * \param[in] data     : �����������(��ͬ�������ݸ�ʽ��ͬ�����磺AMHW_ZLG118_LCD_MUX_CTR����
 *                       data = 1��AMHW_ZLG118_LCD_COM0_3_CTRȫ���رգ�data = 0x0)
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_seg32_51_com0_8_ctr(amhw_zlg118_lcd_t *p_hw_lcd,
                                     uint32_t           flag,
                                     uint32_t           data)
{



    switch (flag){

        case AMHW_ZLG118_LCD_ALL_CLOSE:
            p_hw_lcd->lcdpoen1 = (p_hw_lcd->lcdpoen1 | 0xffffffff) & data;
            break;
        case AMHW_ZLG118_LCD_SEG40_51_CTR :
            p_hw_lcd->lcdpoen1 = (p_hw_lcd->lcdpoen1) & (~(data << 8));
            break;
        case AMHW_ZLG118_LCD_MUX_CTR :
            if (data == 0){
                p_hw_lcd->lcdpoen1 &= ~(1 << 12);
            }else{
                p_hw_lcd->lcdpoen1 |=  (1 << 12);
            }
            break;
        case AMHW_ZLG118_LCD_COMSEG_CTR :
            p_hw_lcd->lcdpoen1 = (p_hw_lcd->lcdpoen1)  & (~(data << 4));
            break;
        case AMHW_ZLG118_LCD_COM0_3_CTR :
            p_hw_lcd->lcdpoen1 =
                         (p_hw_lcd->lcdpoen1 ) & (~(data << 21));
            break;
        case AMHW_ZLG118_LCD_SEG32_35_CTR :
            p_hw_lcd->lcdpoen1 =
                         (p_hw_lcd->lcdpoen1) & ~data;
            break;
        default : return ;
    }
}

/**
 * \brief LCD-RAM_0_f �������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] data     : ramд������
 * \param[in] addr     : ��ַ����
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lcd_ram_write (amhw_zlg118_lcd_t *p_hw_lcd ,
                                uint32_t           data,
                                uint8_t            addr)
{
    p_hw_lcd->lcdram0_f[addr] =
                           (p_hw_lcd->lcdram0_f[addr] & (~(0xffffffff))) | data;
}


/**
 * @} amhw_if_zlg118_lcd
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_lcd_H */

/* end of file */
