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
 * \brief ZSN700 ���̹���
 *
 * - ʵ������:
 *   ģ������:LED0��1���Ƶ����˸; demo�������:���demo��ں����ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_softimer.h"
#include "demo_am700_core_entries.h"
#include "am_zsn700_reader.h"
int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");

    /* demo������� */
    demo_zsn700_core_std_led_entry();
//    demo_zsn700_core_std_delay_entry();
//    demo_zsn700_core_std_buzzer_entry();
//    demo_zsn700_reader_picca_halt ();
//    demo_zsn700_reader_picca_lpcd_mode ();
//    demo_zsn700_reader_picca_read_block ();
//    demo_zsn700_reader_picca_val_operate ();
//    demo_zsn700_reader_picca_write_block ();
//    demo_zsn700_reader_piccb_read_id ();
//    demo_zsn700_reader_picca_read_id();
//    demo_zsn700_reader_picca_read_id_8ant();
//    demo_zsn700_reader_ntag_read_id();
//    demo_zsn700_reader_picca_read_cpu_card();
//    demo_zsn700_core_hw_clk_entry();
//    demo_zsn700_core_std_adc_entry();
//    demo_zsn700_core_hw_adc_int_entry();
//    demo_zsn700_core_std_multichan_adc_entry();
//    demo_zsn700_core_hw_multichan_adc_entry();
//    demo_zsn700_core_hw_adc_dma_entry();
//    demo_zsn700_core_std_crc_entry();
//    demo_zsn700_core_drv_dma_m2m_entry();
//    demo_zsn700_core_drv_flash_entry();
//    demo_zsn700_core_hw_gpio_entry();
//    demo_zsn700_core_hw_gpio_trigger_entry();
//    demo_zsn700_core_std_gpio_entry();
//    demo_zsn700_core_std_gpio_trigger_entry();
//    demo_zsn700_core_hw_i2c_master_poll_entry();
//    demo_zsn700_core_hw_i2c_slave_int_entry();
//    demo_zsn700_core_std_i2c_slave_int_entry();
//    demo_zsn700_core_std_i2c_master_async_entry();
//    demo_zsn700_core_std_i2c_master_sync_entry();
//    demo_zsn700_core_std_key_input_event_entry();
//    demo_zsn700_core_drv_rtc_entry();
//    demo_zsn700_core_hw_spi_master_entry();
//    demo_zsn700_core_std_spi_master_dma_entry();
//    demo_zsn700_core_std_spi_master_int_entry();
//    demo_zsn700_core_hw_adtim_swsync_entry();
//    demo_zsn700_core_hw_adtim_port_sw_brake_entry();
//    demo_zsn700_core_hw_adtim_vc_brake_entry();
//    demo_zsn700_core_hw_adtim_trig_adc_sqr_entry();
//    demo_zsn700_core_hw_tim_port_brake_entry();
//    demo_zsn700_core_hw_tim_vc_brake_entry();
//    demo_zsn700_core_hw_tim_trig_adc_sqr_entry();
//    demo_zsn700_core_hw_tim_cap_entry();
//    demo_zsn700_core_hw_tim_cmp_toggle_entry();
//    demo_zsn700_core_hw_tim_pwm_entry();
//    demo_zsn700_core_hw_tim_pwm_dead_entry();
//    demo_zsn700_core_hw_tim_timing_entry();
//    demo_zsn700_core_hw_tim_trig_adc_sqr_entry();
//    demo_zsn700_core_std_tim0_cap_entry();
//    demo_zsn700_core_std_tim1_cap_entry();
//    demo_zsn700_core_std_tim2_cap_entry();
//    demo_zsn700_core_std_tim3_cap_entry();
//    demo_zsn700_core_std_tim4_cap_entry();
//    demo_zsn700_core_std_tim5_cap_entry();
//    demo_zsn700_core_std_tim6_cap_entry();
//    demo_zsn700_core_std_tim0_pwm_entry();
//    demo_zsn700_core_std_tim1_pwm_entry();
//    demo_zsn700_core_std_tim2_pwm_entry();
//    demo_zsn700_core_std_tim3_pwm_entry();
//    demo_zsn700_core_std_tim4_pwm_entry();
//    demo_zsn700_core_std_tim5_pwm_entry();
//    demo_zsn700_core_std_tim6_pwm_entry();
//    demo_zsn700_core_std_tim0_timing_entry();
//    demo_zsn700_core_std_tim1_timing_entry();
//    demo_zsn700_core_std_tim2_timing_entry();
//    demo_zsn700_core_std_tim3_timing_entry();
//    demo_zsn700_core_std_tim4_timing_entry();
//    demo_zsn700_core_std_tim5_timing_entry();
//    demo_zsn700_core_std_tim6_timing_entry();
//    demo_zsn700_core_std_lptim0_timing_entry();
//    demo_zsn700_core_std_lptim1_timing_entry();
//    demo_zsn700_core_std_lptim_timing_gate_entry();
//    demo_zsn700_core_hw_uart_int_entry();
//    demo_zsn700_core_hw_uart_polling_entry();
//    demo_zsn700_core_hw_uart_rx_dma_entry();
//    demo_zsn700_core_hw_uart_tx_dma_entry();
//    demo_zsn700_core_std_uart_polling_entry();
//    demo_zsn700_core_std_uart_ringbuf_entry();
//    demo_zsn700_core_hw_lpuart_int_entry();
//    demo_zsn700_core_hw_lpuart_polling_entry();
//    demo_zsn700_core_hw_lpuart_rx_dma_entry();
//    demo_zsn700_core_hw_lpuart_tx_dma_entry();
//    demo_zsn700_core_std_lpuart_polling_entry();
//    demo_zsn700_core_std_lpuart_ringbuf_entry();
//    demo_zsn700_core_hw_lvd_system_reset_entry ();
//    demo_zsn700_core_hw_lvd_int_entry ();
//    demo_zsn700_core_hw_opa_one_entry ();
//    demo_zsn700_core_hw_opa_dac_entry ();
//    demo_zsn700_core_hw_dac_dma_entry ();
//    demo_zsn700_core_std_dac_entry ();
//    demo_zsn700_core_hw_vc_int_entry();
//    demo_zsn700_core_hw_aes_ency_decy_entry ();
//    demo_zsn700_core_std_dac_entry ();
//    demo_zsn700_core_hw_trng_generate_entry ();
//    demo_zsn700_core_hw_wdt_entry();
//    demo_zsn700_core_std_wdt_entry();
//    demo_zsn700_drv_lpmode_wake_up_entry();
//    demo_zsn700_core_hw_lcd_entry ();
//    demo_zsn700_core_miniport_zlg72128_entry();
//    demo_zsn700_core_miniport_hc595_digitron_entry();
//    demo_zsn700_core_miniport_hc595_led_entry();
//    demo_zsn700_iso7816_entry();
    while (1) {

    }
}

/* end of file */
