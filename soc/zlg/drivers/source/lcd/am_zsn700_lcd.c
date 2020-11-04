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
 * \brief LCD����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "am_zsn700.h"
#include "zsn700_periph_map.h"
#include "am_zsn700_lcd.h"
#include "am_zsn700_clk.h"
#include "hw/amhw_zsn700_lcd.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/
/**
 * \brief LCD�жϷ�����
 */
void __lcd_irq_handler (void *p_cookie);

/******************************************************************************/
/**
 * \brief LCD�жϷ�����
 */
void __lcd_irq_handler (void *p_cookie)
{
    amhw_zsn700_lcd_t   *p_hw_lcd;
    am_zsn700_lcd_dev_t *p_dev    = (am_zsn700_lcd_dev_t *)p_cookie;
    p_hw_lcd = (amhw_zsn700_lcd_t *)(p_dev->p_devinfo->reg_base);

    if (amhw_zsn700_lcd_int_stu_check (p_hw_lcd)){

        /* �ж�״̬��־��� */
        amhw_zsn700_lcd_int_flag_clr (p_hw_lcd);

        /* �û��ص�����ִ�� */
        p_dev->pfn_trigger_cb(p_dev->p_arg);
    }
}
/******************************************************************************/
/**
 * \brief LCD ����
 */
int am_zsn700_lcd_disp_clr (am_lcd_handle_t handle)
{
    int i = 0;

    amhw_zsn700_lcd_t *p_hw_lcd;

    if (handle == NULL){

        return AM_ERROR;
    }

    p_hw_lcd = (amhw_zsn700_lcd_t *)handle->p_devinfo->reg_base;

    /* ����Դ����� */
    for (i = 0; i < 16; i++){

        amhw_zsn700_lcd_ram_write (p_hw_lcd, 0, i);
    }

    return AM_OK;
}

/**
 * \brief LCD ��������
 */
int am_zsn700_lcd_disp_write (am_lcd_handle_t handle,
                              uint32_t addr,
                              uint32_t data)
{
    amhw_zsn700_lcd_t *p_hw_lcd;

    if (handle == NULL){

        return AM_ERROR;
    }

    p_hw_lcd = (amhw_zsn700_lcd_t *)handle->p_devinfo->reg_base;

    /* д���ݵ��Դ� */
    amhw_zsn700_lcd_ram_write (p_hw_lcd, data, addr);

    return AM_OK;
}

/**
 * \brief LCD DMAģʽ���� ���жϴ�����
 */
int am_zsn700_lcd_dma_int_set (am_lcd_handle_t handle,
                               void (*p_lcd_cb) (void *),
                               void *p_arg)
{
    amhw_zsn700_lcd_t *p_hw_lcd;

    if (handle == NULL){

        return AM_ERROR;
    }

    /* �û����� */
    handle->p_arg          = p_arg;

    /* �û��ص��������� */
    handle->pfn_trigger_cb = p_lcd_cb;

    p_hw_lcd = (amhw_zsn700_lcd_t *)handle->p_devinfo->reg_base;

    /* LCD DMAʹ�� */
    amhw_zsn700_lcd_dma_enable (p_hw_lcd);

    /* �ж�״̬��־��� */
    amhw_zsn700_lcd_int_flag_clr (p_hw_lcd);

    /* ʹ��LCD�ж� */
    amhw_zsn700_lcd_int_enable (p_hw_lcd);

    /* �ж����� */
    am_int_connect(handle->p_devinfo->inum,
                   __lcd_irq_handler,
                   handle);
    /* �����ж� */
    am_int_enable (handle->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief LCD ʹ��
 */
int am_zsn700_lcd_enable (am_lcd_handle_t handle, uint8_t lcd_mode)
{
    amhw_zsn700_lcd_t *p_hw_lcd;

    if (handle == NULL){

        return AM_ERROR;
    }

    handle->mode = lcd_mode;

    p_hw_lcd = (amhw_zsn700_lcd_t *)handle->p_devinfo->reg_base;

    /* LCD ģʽѡ�� */
    amhw_zsn700_lcd_mode_sel (p_hw_lcd, lcd_mode);

    /* ʹ��LCD */
    amhw_zsn700_lcd_enable (p_hw_lcd);

    return AM_OK;
}

/**
 * \brief LCD COM SEG �˿�����
 */
int am_zsn700_lcd_com_seg_init (am_lcd_handle_t         handle,
                                am_zsn700_lcd_com_seg_t *p_port)
{
    amhw_zsn700_lcd_t *p_hw_lcd;

    if ((handle == NULL) && (p_port == NULL)){

        return AM_ERROR;
    }

    p_hw_lcd = (amhw_zsn700_lcd_t *)(handle->p_devinfo->reg_base);

    /* ���� SEG0-SEG7 */
    amhw_zsn700_seg0_31_ctr (p_hw_lcd, p_port->seg0_31);

    /* �ر�SEG32-51 Com0-8 */
    amhw_zsn700_seg32_51_com0_8_ctr (p_hw_lcd,
                                     AMHW_ZSN700_LCD_ALL_CLOSE,
                                     0xffffffff);

    /* ����Com0-3 */
    amhw_zsn700_seg32_51_com0_8_ctr (p_hw_lcd,
                                     AMHW_ZSN700_LCD_COM0_3_CTR,
                                     p_port->com0_3);

    /* SEG32-35�˿ڹ���ѡ�� */
    amhw_zsn700_seg32_51_com0_8_ctr (p_hw_lcd,
                                     AMHW_ZSN700_LCD_MUX_CTR,
                                     p_port->mux);

    /* ���ö˿�SEG32-SEG35 */
    amhw_zsn700_seg32_51_com0_8_ctr (p_hw_lcd,
                                     AMHW_ZSN700_LCD_SEG32_35_CTR,
                                     p_port->seg32_35);
    /* ���ö˿�seg40-51 */
    amhw_zsn700_seg32_51_com0_8_ctr (p_hw_lcd,
                                     AMHW_ZSN700_LCD_SEG40_51_CTR,
                                     p_port->seg40_51);

    /* ����SEG36-39 COM4-7 */
    amhw_zsn700_seg32_51_com0_8_ctr (p_hw_lcd,
                                     AMHW_ZSN700_LCD_COMSEG_CTR,
                                     p_port->seg36com7_39com4);

    return AM_OK;

}

/**
 * \brief LCD ��ʼ��
 */
am_lcd_handle_t  am_zsn700_lcd_init (am_zsn700_lcd_dev_t           *p_dev,
                                     const am_zsn700_lcd_devinfo_t *p_devinfo)
{
    amhw_zsn700_lcd_t *p_hw_lcd;

    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }

    p_dev->p_devinfo      = p_devinfo;

    p_dev->pfn_trigger_cb = NULL;
    p_dev->p_arg          = NULL;
    p_dev->mode           = AMHW_ZSN700_LCD_MODE_0;

    p_hw_lcd = (amhw_zsn700_lcd_t *)(p_dev->p_devinfo->reg_base);

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* ʱ��Դѡ�� */
    amhw_zsn700_lcd_clk_rsc_sel (p_hw_lcd, p_dev->p_devinfo->clk_src);

    if(p_devinfo->clk_src == AMHW_ZSN700_LCD_CLK_SRC_XTL) {

        /* �ⲿ������������ѡ�� */
        amhw_zsn700_rcc_xtl_xtal_driver_set(AMHW_ZSN700_XTL_XTAL_DRIVER_DEFAULT);

        /* XTL�����񵴷��ȵĵ��� */
        amhw_zsn700_rcc_xtl_xtal_amplitude_set(
            AMHW_ZSN700_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

        /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
        amhw_zsn700_rcc_xtl_waittime_set(AMHW_ZSN700_XTL_WAITTIME_16384);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_xtl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_xtl_state_get() == AM_FALSE);

    } else if(p_devinfo->clk_src == AMHW_ZSN700_LCD_CLK_SRC_RCL) {

        /* ����RCLʱ��Ƶ��У׼ֵ ��32.768KHz��*/
        amhw_zsn700_rcc_rcl_trim_set(*((uint16_t*)0x00100C22));

        amhw_zsn700_rcc_rcl_waittime_set(AMHW_ZSN700_RCL_WAITTIME_256);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_rcl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_rcl_state_get() == AM_FALSE);
    }

    /* ����LCDʱ�� */
    am_clk_enable (CLK_LCD);

    /* ѡ��ƫ�õ�ѹԴ */
    amhw_zsn700_lcd_bias_rsc_sel (p_hw_lcd, p_devinfo->bias_src);

    /* ����ռ�ձ� */
    amhw_zsn700_lcd_duty_sel (p_hw_lcd, p_devinfo->duty);

    /* ����ƫ�õ�ѹ */
    amhw_zsn700_lcd_bias_sel (p_hw_lcd, p_devinfo->bias);

    /* ��ѹ��ʱ��Ƶ��ѡ�� */
    amhw_zsn700_lcd_cpclk_sel (p_hw_lcd, p_devinfo->cpclk);

    /* ɨ��Ƶ��ѡ�� */
    amhw_zsn700_lcd_cldclk_sel (p_hw_lcd, p_devinfo->scanclk);

    /* �жϽ��� */
    amhw_zsn700_lcd_int_disable (p_hw_lcd);

    /* ����DMA */
    amhw_zsn700_lcd_dma_disable (p_hw_lcd);

    return p_dev;
}

/**
 * \brief LCD ȥ��ʼ��
 */
void am_zsn700_lcd_deinit (am_lcd_handle_t handle)
{
    am_zsn700_lcd_dev_t *p_dev  = (am_zsn700_lcd_dev_t *)handle;
    amhw_zsn700_lcd_t *p_hw_lcd =
                          (amhw_zsn700_lcd_t *)(p_dev->p_devinfo->reg_base);

    if (handle == NULL){

        return ;
    }

    /* ƽ̨ȥ��ʼ�� */
    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

    /* �жϽ��� */
    amhw_zsn700_lcd_int_disable (p_hw_lcd);

    /* �ж����� */
    am_int_disconnect(handle->p_devinfo->inum,
                      __lcd_irq_handler,
                      handle);
    /* �ر��ж� */
    am_int_disable (handle->p_devinfo->inum);
}

/* end of file */
