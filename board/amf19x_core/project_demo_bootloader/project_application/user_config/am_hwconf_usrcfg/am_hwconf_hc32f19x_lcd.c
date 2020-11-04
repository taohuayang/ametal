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
 * \brief ZLG LCD �û������ļ�
 * \sa am_hwconf_hc32_lcd.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "am_hc32_lcd.h"
#include "hw/amhw_hc32_lcd.h"
#include "hc32_pin.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_lcd
 * \copydoc am_hwconf_hc32_lcd.c
 * @{
 */

/**
 * \brief LCD ƽ̨��ʼ��
 */
void __hc32_plfm_lcd_init (void)
{
    /* ��ʼ��LCD�ⲿGPIO���� */
    am_gpio_pin_cfg(PIOA_9,  PIOA_9_AIN);  /**< \brief COM0 */
    am_gpio_pin_cfg(PIOA_10, PIOA_10_AIN); /**< \brief COM1 */
    am_gpio_pin_cfg(PIOA_11, PIOA_11_AIN); /**< \brief COM2 */
    am_gpio_pin_cfg(PIOA_12, PIOA_12_AIN); /**< \brief COM3 */

    am_gpio_pin_cfg(PIOA_8,  PIOA_8_AIN);  /**< \brief SEG0 */
    am_gpio_pin_cfg(PIOC_9,  PIOC_9_AIN);  /**< \brief SEG1 */
    am_gpio_pin_cfg(PIOC_8,  PIOC_8_AIN);  /**< \brief SEG2 */
    am_gpio_pin_cfg(PIOC_7,  PIOC_7_AIN);  /**< \brief SEG3 */
    am_gpio_pin_cfg(PIOC_6,  PIOC_6_AIN);  /**< \brief SEG4 */
    am_gpio_pin_cfg(PIOB_15, PIOB_15_AIN); /**< \brief SEG5 */
    am_gpio_pin_cfg(PIOB_14, PIOB_14_AIN); /**< \brief SEG6 */
    am_gpio_pin_cfg(PIOB_13, PIOB_13_AIN); /**< \brief SEG7 */
    am_gpio_pin_cfg(PIOB_3,  PIOB_3_AIN);  /**< \brief VLCDH */
    am_gpio_pin_cfg(PIOB_4,  PIOB_4_AIN);  /**< \brief VLCD3 */
    am_gpio_pin_cfg(PIOB_5,  PIOB_5_AIN);  /**< \brief VLCD2 */
    am_gpio_pin_cfg(PIOB_6,  PIOB_6_AIN);  /**< \brief VLCD1 */

}

/**
 * \brief LCD ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_lcd_deinit (void)
{
    /* �ر�LCDʱ�� */
    am_clk_disable(CLK_LCD);
}

/** \brief LCD �豸��Ϣ */
static const am_hc32_lcd_devinfo_t __g_lcd_devinfo =
{
    /**< \brief ָ��LCD�Ĵ������ָ�� */
    HC32_LCD_BASE,

    /**< \brief LCD�жϱ�� */
    INUM_LCD,

    /**
     * \brief LCDƫ��Դ
     *
     * \note : ��ֵ�ο�amhw_hc32_lcd.h�к궨��:Bias��ѹ��Դѡ������
     */
    AMHW_HC32_LCD_BIAS_CAP_DIV,

    /**
     * \brief LCDռ�ձ�
     *
     * \note : ��ֵ�ο�amhw_hc32_lcd.h��ö�ٶ��壺LCD duty����
     *
     */
    AMHW_HC32_DUTY_1_4,

    /**
     * \brief LCDƫ�õ�ѹ
     *
     * \note : ��ֵ�ο�amhw_hc32_lcd.h�к궨�壺ƫ�õ�ѹ��������
     */
    AMHW_HC32_BIAS_1_3,

    /**
     * \brief LCD��ѹ��ʱ��Ƶ��
     *
     * \note : ��ֵ�ο�amhw_hc32_lcd.h�к궨�壺��ѹ��ʱ��Ƶ��ѡ������
     */
    AMHW_HC32_CPCLK_2K_HZ,

    /**
     * \brief LCDɨ��Ƶ��
     *
     * \note : ��ֵ�ο�amhw_hc32_lcd.h�к궨�壺LCDɨ��Ƶ��ѡ������
     */
    AMHW_HC32_LCDCLK_128_HZ,

    /**
     * \brief ʱ��Դ    ��XTL RCL��
     *
     */
    AMHW_HC32_LCD_CLK_SRC_RCL,

    /**< \brief LCDƽ̨��ʼ������ */
    __hc32_plfm_lcd_init,

    /**< \brief LCDƽ̨���ʼ������  */
    __hc32_plfm_lcd_deinit,
};

/** \brief LCD�豸ʵ�� */
static am_hc32_lcd_dev_t __g_lcd_dev;

/** \brief lcd ʵ����ʼ�������LCD��׼������ */
am_lcd_handle_t am_hc32_lcd_inst_init (void)
{
    return am_hc32_lcd_init(&__g_lcd_dev, &__g_lcd_devinfo);
}

/** \brief LCD ʵ�����ʼ�� */
void am_hc32_lcd_inst_deinit (am_lcd_handle_t handle)
{
    am_hc32_lcd_deinit(handle);
}

/**
 * @}
 */

/* end of file */
