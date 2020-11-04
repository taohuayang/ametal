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
 * \brief AML166 ���̹���
 * \note  AML166 оƬ�󲿷�������ZLG116��ͬ�����������ZLG116����������
 *        ��˴󲿷�����ĳ�ʼ��������ΪZLG116�弶���������ó�ʼ������
 *
 * - �������裺
 *   1. ȡ��������Ҫʹ�õ����̡�
 *
 * \note
 *    ͬһʱ��ֻ��ʹ��һ�����̡�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-01-17  htf, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_aml166_core_entries.h"
#include "zlg116_pin.h"
#include "am_gpio.h"
/**
 * \brief AMetal Ӧ�ó������
 */
int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");
    /*
     * ����Ϊ����demo����ں�������Ҫ�����ĸ� demo�� ��ȡ����Ӧ���������е�ע��
     *
     * Ĭ�����е���LED��˸ demo��
     *
     * ע�⣺ͬһʱ��ֻ������һ�� demo����ֻ��ʹĳһ�д���ȡ��ע��״̬��
     */

    demo_aml166_core_std_led_entry();
//    demo_aml166_core_std_delay_entry();
//    demo_aml166_core_std_buzzer_entry();
//    demo_aml166_core_hw_clk_entry();
//    demo_aml166_core_drv_dma_m2m_entry();
//    demo_aml166_core_drv_flash_entry();
//    demo_aml166_core_hw_gpio_entry();
//    demo_aml166_core_hw_gpio_trigger_entry();
//    demo_aml166_core_std_gpio_entry();
//    demo_aml166_core_std_gpio_trigger_entry();
//    demo_aml166_core_hw_i2c_master_poll_entry();
//    demo_aml166_core_hw_i2c_slave_poll_entry();
//    demo_aml166_core_std_i2c_lm75_entry();
//    demo_aml166_core_std_i2c_master_async_entry();
//    demo_aml166_core_std_i2c_master_sync_entry();
//    demo_aml166_core_std_i2c_slave_entry();
//    demo_aml166_core_std_i2c_slave_subaddr_entry();
//    demo_aml166_core_std_key_entry();
//    demo_aml166_core_std_softimer_entry();
//    demo_aml166_core_hw_spi_master_entry();
//    demo_aml166_core_std_spi_flash_dma_entry();
//    demo_aml166_core_std_spi_flash_int_entry();
//    demo_aml166_core_std_spi_master_dma_entry();
//    demo_aml166_core_std_spi_master_int_entry();
//    demo_aml166_core_std_spi_slave_dma_entry();
//    demo_aml166_core_hw_tim_cap_entry();
//    demo_aml166_core_hw_tim_pwm_entry();
//    demo_aml166_core_hw_tim_timing_entry();
//    demo_aml166_core_std_tim1_cap_entry();
//    demo_aml166_core_std_tim1_pwm_entry();
//    demo_aml166_core_std_tim1_timing_entry();
//    demo_aml166_core_std_tim2_cap_entry();
//    demo_aml166_core_std_tim2_pwm_entry();
//    demo_aml166_core_std_tim2_timing_entry();
//    demo_aml166_core_std_tim3_cap_entry();
//    demo_aml166_core_std_tim3_pwm_entry();
//    demo_aml166_core_std_tim3_timing_entry();
//    demo_aml166_core_hw_uart_int_entry();
//    demo_aml166_core_hw_uart_polling_entry();
//    demo_aml166_core_hw_uart_rx_dma_entry();
//    demo_aml166_core_hw_uart_tx_dma_entry();
//    demo_aml166_core_std_uart_polling_entry();
//    demo_aml166_core_std_uart_ringbuf_entry();
//    demo_aml166_core_drv_sleepmode_timer_wake_up_entry();
//    demo_aml166_core_drv_sleepmode_wake_up_entry();
//    demo_aml166_core_drv_standbymode_wake_up_entry();
//    demo_aml166_core_drv_stopmode_wake_up_entry();
//    demo_aml166_core_hw_iwdg_entry();
//    demo_aml166_core_hw_wwdg_entry();
//    demo_aml166_core_std_iwdg_entry();
//    demo_aml166_core_std_wwdg_entry();
//    demo_aml166_core_zml166_adc_pt100_measure();
//    demo_aml166_core_zml166_adc_vol_measure();
//    demo_aml166_core_zml166_adc_thermocouple_measure();
//    demo_aml166_core_zml166_adc_vol_para_adjuet();
//    demo_aml166_core_microport_ds1302_entry();
//    demo_aml166_core_microport_eeprom_entry();
//    demo_aml166_core_microport_eeprom_nvram_entry();
//    demo_aml166_core_microport_flash_entry();
//    demo_aml166_core_microport_flash_ftl_entry();
//    demo_aml166_core_microport_flash_mtd_entry();
//    demo_aml166_core_microport_rs485_entry();
//    demo_aml166_core_microport_rtc_entry();
//    demo_aml166_core_microport_rx8025t_entry();
//    demo_aml166_core_microport_usb_entry();
//    demo_aml166_core_miniport_digitron_entry();
//    demo_aml166_core_miniport_hc595_digitron_entry();
//    demo_aml166_core_miniport_hc595_digitron_key_entry();
//    demo_aml166_core_miniport_hc595_digitron_temp_entry();
//    demo_aml166_core_miniport_hc595_led_entry();
//    demo_aml166_core_miniport_key_entry();
//    demo_aml166_core_miniport_key_digitron_entry();
//    demo_aml166_core_miniport_led_entry();
//    demo_aml166_core_miniport_zlg72128_entry();
//    demo_aml166_core_dr_fm175xx_picca_read_id();
//    demo_aml166_core_dr_fm175xx_picca_halt();
//    demo_aml166_core_dr_fm175xx_picca_read_block ();
//    demo_aml166_core_dr_fm175xx_picca_val_operate();
//    demo_aml166_core_dr_fm175xx_picca_write_block();
//    demo_aml166_core_dr_fm175xx_piccb_read_id();
//    demo_aml166_core_dr_fm175xx_picca_lpcd_read_id();
    while (1) {

    }
}
