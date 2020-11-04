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
 * \brief hk32f103rbt6 ģ�幤��
 *
 * - ʵ������:
 *   ģ������:LED0��1���Ƶ����˸; demo�������:���demo��ں����ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-027  yrh, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "demo_hk32f103rbt6_core_entries.h"
#include "hk32f103rbt6_pin.h"

int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");
    /*
     * ����Ϊ����demo����ں���
     *
     * ��Ҫ�����ĸ�demo����ȡ����Ӧ���������е�ע�ͣ�
     *
     * Ĭ�����е���LED��˸ demo
     *
     * ע�⣺ͬһʱ��ֻ������һ�� demo����ֻ��ʹĳһ�д���ȡ��ע��״̬
     */

    demo_hk32f103rbt6_core_std_led_entry();
//    demo_hk32f103rbt6_core_std_delay_entry();
//    demo_hk32f103rbt6_core_std_adc_entry();
//    demo_hk32f103rbt6_core_hw_adc_int_entry();
//    demo_hk32f103rbt6_core_std_multichan_adc_entry();
//    demo_hk32f103rbt6_core_hw_adc_dma_entry();
//    demo_hk32f103rbt6_core_hw_adc_dma_double_entry();
//    demo_hk32f103rbt6_core_std_buzzer_entry();
//    demo_hk32f103rbt6_core_std_crc_entry();
//    demo_hk32f103rbt6_core_drv_dma_m2m_entry();
//    demo_hk32f103rbt6_core_drv_flash_entry();
//    demo_hk32f103rbt6_core_hw_gpio_entry();
//    demo_hk32f103rbt6_core_hw_gpio_trigger_entry();
//    demo_hk32f103rbt6_core_std_gpio_entry();
//    demo_hk32f103rbt6_core_std_gpio_trigger_entry();
//    demo_hk32f103rbt6_core_hw_i2c_master_poll_entry();
//    demo_hk32f103rbt6_core_hw_i2c_slave_poll_entry();
//    demo_hk32f103rbt6_core_std_i2c_lm75_entry();
//    demo_hk32f103rbt6_core_std_i2c_master_async_entry();
//    demo_hk32f103rbt6_core_std_i2c_master_sync_entry();
//    demo_hk32f103rbt6_core_std_key_input_event_entry();
//    demo_hk32f103rbt6_core_hw_iwdg_entry();
//    demo_hk32f103rbt6_core_std_iwdg_entry();
//    demo_hk32f103rbt6_core_microport_ds1302_entry();
//    demo_hk32f103rbt6_core_microport_eeprom_entry();
//    demo_hk32f103rbt6_core_microport_eeprom_nvram_entry();
//    demo_hk32f103rbt6_core_microport_flash_entry();
//    demo_hk32f103rbt6_core_microport_flash_ftl_entry();
//    demo_hk32f103rbt6_core_microport_flash_mtd_entry();
//    demo_hk32f103rbt6_core_microport_rs485_entry();
//    demo_hk32f103rbt6_core_microport_rtc_entry();
//    demo_hk32f103rbt6_core_microport_rx8025t_entry();
//    demo_hk32f103rbt6_core_miniport_digitron_entry();
//    demo_hk32f103rbt6_core_miniport_hc595_digitron_entry();
//    demo_hk32f103rbt6_core_miniport_hc595_digitron_key_entry();
//    demo_hk32f103rbt6_core_miniport_hc595_digitron_temp_entry();
//    demo_hk32f103rbt6_core_miniport_hc595_led_entry();
//    demo_hk32f103rbt6_core_miniport_key_entry();
//    demo_hk32f103rbt6_core_miniport_key_digitron_entry();
//    demo_hk32f103rbt6_core_miniport_led_entry();
//    demo_hk32f103rbt6_core_miniport_zlg72128_entry();
//    demo_hk32f103rbt6_core_std_rtc_entry();
//    demo_hk32f103rbt6_core_hw_spi_master_entry ();
//    demo_hk32f103rbt6_core_std_spi_master_dma_entry ();
//    demo_hk32f103rbt6_core_std_spi_master_int_entry ();
//    demo_hk32f103rbt6_core_std_spi_master_poll_entry ();
//    demo_hk32f103rbt6_core_std_spi_slaver_dma_entry ();
//    demo_hk32f103rbt6_core_hw_tim_cap_entry();
//    demo_hk32f103rbt6_core_std_tim1_cap_entry();
//    demo_hk32f103rbt6_core_std_tim2_cap_entry();
//    demo_hk32f103rbt6_core_std_tim3_cap_entry();
//    demo_hk32f103rbt6_core_std_tim4_cap_entry();
//    demo_hk32f103rbt6_core_hw_tim_cmp_toggle_entry();
//    demo_hk32f103rbt6_core_hw_tim_pwm_entry();
//    demo_hk32f103rbt6_core_std_tim1_pwm_entry();
//    demo_hk32f103rbt6_core_std_tim2_pwm_entry();
//    demo_hk32f103rbt6_core_std_tim3_pwm_entry();
//    demo_hk32f103rbt6_core_std_tim4_pwm_entry();
//    demo_hk32f103rbt6_core_hw_tim_timing_entry();
//    demo_hk32f103rbt6_core_std_tim1_timing_entry();
//    demo_hk32f103rbt6_core_std_tim2_timing_entry();
//    demo_hk32f103rbt6_core_std_tim3_timing_entry();
//    demo_hk32f103rbt6_core_std_tim4_timing_entry();
//    demo_hk32f103rbt6_core_hw_usart_int_entry();
//    demo_hk32f103rbt6_core_hw_usart_polling_entry();
//    demo_hk32f103rbt6_core_hw_usart_rx_dma_entry();
//    demo_hk32f103rbt6_core_hw_usart_tx_dma_entry();
//    demo_hk32f103rbt6_core_std_usart_polling_entry();
//    demo_hk32f103rbt6_core_std_usart_ringbuf_entry();
//    demo_hk32f103rbt6_core_hw_wwdg_entry();
//    demo_hk32f103rbt6_core_std_wwdg_entry();
//    demo_hk32f103rbt6_core_dr_fm175xx_cpu_card();
//    demo_hk32f103rbt6_core_dr_fm175xx_picca_read_id();
//    demo_hk32f103rbt6_core_dr_fm175xx_picca_halt();
//    demo_hk32f103rbt6_core_dr_fm175xx_picca_read_block ();
//    demo_hk32f103rbt6_core_dr_fm175xx_picca_val_operate();
//    demo_hk32f103rbt6_core_dr_fm175xx_picca_write_block();
//    demo_hk32f103rbt6_core_dr_fm175xx_piccb_read_id();
//    demo_hk32f103rbt6_core_dr_fm175xx_picca_lpcd_read_id();
//    demo_hk32f103rbt6_drv_sleepmode_timer_wake_up_entry();
//    demo_hk32f103rbt6_drv_sleepmode_wake_up_entry();
//    demo_hk32f103rbt6_drv_standbymode_wake_up_entry();
//    demo_hk32f103rbt6_drv_stopmode_wake_up_entry();
//    demo_hk32f103rbt6_core_can_int_entry();
//    demo_hk32f103rbt6_core_can_entry();
//    demo_hk32f103rbt6_core_zsn603_led_test_entry();
//    demo_hk32f103rbt6_core_zsn603_picca_test_entry();
//    demo_hk32f103rbt6_core_zsn603_piccb_test_entry();
//    demo_hk32f103rbt6_core_zsn603_auto_detect_test_entry();
//    demo_hk32f103rbt6_core_sensor_fxos8700cq_entry();
//    demo_hk32f103rbt6_core_sensor_fxos8700cq_int_entry();
    while (1) { 

    }
}

/* end of file */
