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
 * \brief LCD ��������ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   ��LCD����ѭ����ʾ����"0000~9999"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32_hw_lcd.c src_hc32_hw_lcd
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_lcd
 * \copydoc demo_hc32_hw_lcd.c
 */

/** [src_hc32_hw_lcd] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_hc32_lcd.h"
#include "hw/amhw_hc32_lcd.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define LCD_CLK_SRC   AMHW_HC32_LCD_CLK_SRC_RCL   /**< \brief ʱ��Դ */
#define LCD_BIAS_SRC  AMHW_HC32_LCD_BIAS_CAP_DIV  /**< \brief ƫ�õ�ѹԴ */
#define LCD_DUTY      AMHW_HC32_DUTY_1_4          /**< \brief ռ�ձ� */
#define LCD_BIAS      AMHW_HC32_BIAS_1_3          /**< \brief ƫ�õ�ѹ */
#define LCD_CPCLK     AMHW_HC32_CPCLK_2K_HZ       /**< \brief ��ѹ��Ƶ�� */
#define LCD_SCAN_CLK  AMHW_HC32_LCDCLK_128_HZ     /**< \brief ɨ��Ƶ�� */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_hc32_lcd_t       *gp_hw_lcd   = NULL;  /**< \brief lcd ���� */

/**
 * \brief LCD�������˿ڳ�ʼ��
 */
static void lcd_port_init ()
{
    /* ���� SEG0-SEG7 */
    amhw_hc32_seg0_31_ctr (gp_hw_lcd, 0x000000ff);

    /* �ر�SEG32-51 Com0-8 */
    amhw_hc32_seg32_51_com0_8_ctr (gp_hw_lcd,
                                     AMHW_HC32_LCD_ALL_CLOSE,
                                     0xffffffff);

    /* ����Com0-3 */
    amhw_hc32_seg32_51_com0_8_ctr (gp_hw_lcd,
                                     AMHW_HC32_LCD_COM0_3_CTR,
                                     0xf);

    /* SEG32-35�˿ڹ���ѡ�� */
    amhw_hc32_seg32_51_com0_8_ctr (gp_hw_lcd,
                                     AMHW_HC32_LCD_MUX_CTR,
                                     0x1);

    /* ���ö˿�SEG32-SEG35 */
    amhw_hc32_seg32_51_com0_8_ctr (gp_hw_lcd,
                                     AMHW_HC32_LCD_SEG32_35_CTR,
                                     0xf);
    /* ���ö˿�seg40-51 */
    amhw_hc32_seg32_51_com0_8_ctr (gp_hw_lcd,
                                     AMHW_HC32_LCD_SEG40_51_CTR,
                                     0x10);

    /* ����SEG36-39 COM4-7 */
    amhw_hc32_seg32_51_com0_8_ctr (gp_hw_lcd,
                                     AMHW_HC32_LCD_COMSEG_CTR,
                                     0x0);
                                     
#ifdef HC32L136
    /* ���ö˿�COM0-3 */
    amhw_hc32_seg32_51_com0_8_ctr (gp_hw_lcd,
                                   AMHW_HC32_LCD_SEG40_51_CTR,
                                   0x1f);
#endif
}

/**
 * \brief LCD��������ʼ��
 */
static void lcd_init ()
{
	int peri = 0;

    /* ʱ��Դѡ�� */
    amhw_hc32_lcd_clk_rsc_sel (gp_hw_lcd, LCD_CLK_SRC);

    /* ����RCLʱ��Ƶ��У׼ֵ ��32.768KHz��*/
    amhw_hc32_rcc_rcl_trim_set(*((uint16_t*)0x00100C22));

    amhw_hc32_rcc_rcl_waittime_set(AMHW_HC32_RCL_WAITTIME_256);

    amhw_hc32_rcc_set_start(0x5A5A);
    amhw_hc32_rcc_set_start(0xA5A5);

    amhw_hc32_rcc_rcl_enable();

    /* �ȴ��ȶ�*/
    while(amhw_hc32_rcc_rcl_state_get() == AM_FALSE);

    /* ����LCDʱ�� */
    peri = CLK_LCD & 0xff;

    amhw_hc32_rcc_peripheral_enable((amhw_hc32_peripheral)peri);

    /* ѡ��ƫ�õ�ѹԴ */
    amhw_hc32_lcd_bias_rsc_sel (gp_hw_lcd, LCD_BIAS_SRC);

    /* ����ռ�ձ� */
    amhw_hc32_lcd_duty_sel (gp_hw_lcd, LCD_DUTY);

    /* ����ƫ�õ�ѹ */
    amhw_hc32_lcd_bias_sel (gp_hw_lcd, LCD_BIAS);

    /* ��ѹ��ʱ��Ƶ��ѡ�� */
    amhw_hc32_lcd_cpclk_sel (gp_hw_lcd, LCD_CPCLK);

    /* ɨ��Ƶ��ѡ�� */
    amhw_hc32_lcd_cldclk_sel (gp_hw_lcd, LCD_SCAN_CLK);

    /* �жϽ��� */
    amhw_hc32_lcd_int_disable (gp_hw_lcd);

    /* ����DMA */
    amhw_hc32_lcd_dma_disable (gp_hw_lcd);
}

/**
 * \brief LCD ��ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32_hw_lcd_entry (void *p_hw_lcd, uint32_t *p_data)
{
    int i = 0;

    gp_hw_lcd  = (amhw_hc32_lcd_t *)p_hw_lcd;

    /* LCD��������ʼ�� */
    lcd_init ();

    /* LCD�������˿ڳ�ʼ�� */
    lcd_port_init ();
    
    /* LCD ģʽѡ�� */
    amhw_hc32_lcd_mode_sel (gp_hw_lcd, AMHW_HC32_LCD_MODE_0);

    /* ʹ��LCD */
    amhw_hc32_lcd_enable (gp_hw_lcd);

    /* ����Դ����� */
    for (i = 0; i < 2; i++){

        amhw_hc32_lcd_ram_write (gp_hw_lcd, 0, i);
    }

    while (1)
    {
        for (i = 0; i < 12; i++){

            /* д���ݵ��Դ� */
            amhw_hc32_lcd_ram_write (gp_hw_lcd, p_data[i], 0);
            /* д���ݵ��Դ� */
            amhw_hc32_lcd_ram_write (gp_hw_lcd, p_data[i], 1);

            am_mdelay (1000);
        }

        i = 0;
    }
}

/* end of file */