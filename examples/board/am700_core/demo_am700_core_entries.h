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
 * \brief ZSN700 �������̺����������
 * \sa demo_am700_core_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_adc_int_entry (void);

/**
 * \brief ADC DMA ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_adc_dma_entry (void);

/**
 * \brief �������
 */
void demo_zsn700_core_hw_multichan_adc_entry (void);

/**
 * \brief ADC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_adc_entry (void);

/**
 * \brief ��ͨ��ADC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_multichan_adc_entry (void);

/**
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_buzzer_entry (void);

/**
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_clk_entry (void);

/**
 * \brief CRC ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_hw_crc_entry (void);

/**
 * \brief CRC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_crc_entry (void);

/**
 * \brief DAC ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_dac_entry (void);

/**
 * \brief DAC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_dac_entry (void);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 */
void demo_zsn700_core_drv_dma_m2m_entry (void);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 */
void demo_zsn700_core_drv_flash_entry (void);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_gpio_entry (void);

/**
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_gpio_trigger_entry (void);

/**
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_gpio_entry (void);

/**
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_gpio_trigger_entry (void);

/**
 * \brief I2C ����������(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_i2c_master_poll_entry (void);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_i2c_slave_int_entry (void);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_i2c_slave_int_entry (void);

/**
 * \brief I2C ������ LM75 ��������ȡ�¶�ֵ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_i2c_lm75_entry (void);

/**
 * \brief I2C �������� EEPROM ���̣�ͨ���첽��׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_i2c_master_async_entry (void);

/**
 * \brief I2C �������� EEPROM ���̣�ͨ��ͬ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_i2c_master_sync_entry (void);

/**
 * \brief ����������ϵͳ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_key_input_event_entry (void);

/**
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_led_entry (void);

/**
 * \brief RTC ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_rtc_sec_int_entry (void);

/**
 * \brief RTC ���̣�ͨ����׼�ӿں��м������㺯��ʵ��
 */
void demo_zsn700_core_drv_rtc_entry (void);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_spi_master_entry (void);

/**
 * \brief SPI ���� DMA ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_spi_master_dma_entry (void);

/**
 * \brief SPI �����жϷ�ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_spi_master_int_entry (void);

/**
 * \brief ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_delay_entry (void);

/**
 * \brief SYSTICK ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_systick_timer_entry (void);

/**
 * \brief ADTIM��ʱ�����ͬ�����̣�ͨ��HW�ӿ�ʵ��
 */
void demo_zsn700_core_hw_adtim_swsync_entry(void);

/**
 * \brief ADTIM��ʱ���˿ڡ����ɲ�����̣�ͨ��HW�ӿ�ʵ��
 */
void demo_zsn700_core_hw_adtim_port_sw_brake_entry (void);

/**
 * \brief ADTIM��ʱ��VCɲ�����̣�ͨ��HW�ӿ�ʵ��
 */
void demo_zsn700_core_hw_adtim_vc_brake_entry (void);

/**
 * \brief ��ʱ�� CAP �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_cap_entry (void);

/**
 * \brief TIM0 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim0_cap_entry (void);

/**
 * \brief TIM1 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim1_cap_entry (void);

/**
 * \brief TIM2 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim2_cap_entry (void);

/**
 * \brief TIM3 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim3_cap_entry (void);

/**
 * \brief ADTIM4��ʱ��cap���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim4_cap_entry(void);

/**
 * \brief ADTIM5��ʱ��cap���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim5_cap_entry(void);

/**
 * \brief ADTIM6��ʱ��cap���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim6_cap_entry(void);

/**
 * \brief TIM ʵ�ֱȽ�ƥ�䷭ת��ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_cmp_toggle_entry (void);

/**
 * \brief ��ʱ�� PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_pwm_entry (void);

/**
 * \brief ��ʱ�� �������Ļ���PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_pwm_dead_entry (void);


/**
 * \brief ͨ�ö�ʱ�� �˿�ɲ�����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_port_brake_entry (void);

/**
 * \brief ͨ�ö�ʱ�� �˿�ɲ�����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_vc_brake_entry (void);

/**
 * \brief TIM0 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim0_pwm_entry (void);

/**
 * \brief TIM1 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim1_pwm_entry (void);

/**
 * \brief TIM2 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim2_pwm_entry (void);

/**
 * \brief TIM3 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim3_pwm_entry (void);

/**
 * \brief ADTIM4��ʱ��pwm���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim4_pwm_entry (void);

/**
 * \brief ADTIM5��ʱ��pwm���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim5_pwm_entry (void);

/**
 * \brief ADTIM6��ʱ��pwm���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim6_pwm_entry (void);

/**
 * \brief ��ʱ�� TIMING ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_timing_entry (void);

/**
 * \brief TIM����ADC�ɼ����̣�ͨ��HW�ӿ�ʵ��
 */
void demo_zsn700_core_hw_tim_trig_adc_sqr_entry (void);

/**
 * \brief TIM0 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim0_timing_entry (void);

/**
 * \brief TIM1 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim1_timing_entry (void);

/**
 * \brief TIM2 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim2_timing_entry (void);

/**
 * \brief TIM3 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim3_timing_entry (void);

/**
 * \brief ADTIM4��ʱ��timing���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim4_timing_entry (void);

/**
 * \brief ADTIM5��ʱ��timing���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim5_timing_entry (void);

/**
 * \brief ADTIM6��ʱ��timing���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_tim6_timing_entry (void);

/**
 * \brief LPTIM0��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_lptim0_timing_entry (void);

/**
 * \brief LPTIM1��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_lptim1_timing_entry (void);

/**
 * \brief LPTIM1��ʱ����LPTIM2��ʱ��TIMING���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_lptim_timing_gate_entry (void);

/**
 * \brief ADTIM����ADC�ɼ����̣�ͨ��HW�ӿ�ʵ��
 */
void demo_zsn700_core_hw_adtim_trig_adc_sqr_entry (void);

/**
 * \brief U_ID ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_uid_entry (void);

/**
 * \brief UART �ж����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_uart_int_entry (void);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_hw_uart_polling_entry (void);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_uart_rx_dma_entry (void);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_uart_tx_dma_entry (void);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_uart_polling_entry (void);

/**
 * \brief UART ���λ��������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_uart_ringbuf_entry (void);

/**
 * \brief LPUART �ж����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_lpuart_int_entry (void);

/**
 * \brief LPUART ��ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_hw_lpuart_polling_entry (void);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_lpuart_rx_dma_entry (void);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_lpuart_tx_dma_entry (void);

/**
 * \brief LPUART ��ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_lpuart_polling_entry (void);

/**
 * \brief LPUART ���λ��������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_lpuart_ringbuf_entry (void);

/**
 * \brief �͹���ģʽ��˯�ߡ����˯�ߣ����̣�ͨ��������ӿ�ʵ��
 */
void demo_zsn700_drv_lpmode_wake_up_entry (void);

/**
 * \brief WWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_wdt_entry (void);

/**
 * \brief WWDG ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_std_wdt_entry (void);

/**
 * \brief MicroPort DS1302 ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_microport_ds1302_entry (void);

/**
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_microport_eeprom_entry (void);

/**
 * \brief MicroPort EEPROM ���̣�ͨ�� NVRAM �ӿ�ʵ��
 */
void demo_zsn700_core_microport_eeprom_nvram_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_microport_flash_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ�� MTD �ӿ�ʵ��
 */
void demo_zsn700_core_microport_flash_mtd_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ�� FTL �ӿ�ʵ��
 */
void demo_zsn700_core_microport_flash_ftl_entry (void);

/**
 * \brief MicroPort RS485 ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_microport_rs485_entry (void);

/**
 * \brief MicroPort RTC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_microport_rtc_entry (void);

/**
 * \brief MicroPort RX8025T ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_microport_rx8025t_entry (void);

/**
 * \brief MicroPort USB ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_zsn700_core_microport_usb_entry (void);

/**
 * \brief MiniPort-VIEW ����
 */
void demo_zsn700_core_miniport_digitron_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-VIEW ����
 */
void demo_zsn700_core_miniport_hc595_digitron_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-KEY ����
 */
void demo_zsn700_core_miniport_hc595_digitron_key_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-VIEW + LM75 ����
 */
void demo_zsn700_core_miniport_hc595_digitron_temp_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-LED ����
 */
void demo_zsn700_core_miniport_hc595_led_entry (void);

/**
 * \brief MiniPort-KEY
 */
void demo_zsn700_core_miniport_key_entry (void);

/**
 * \brief MiniPort-KEY + MiniPort-DIGITORN��ʾ����
 */
void demo_zsn700_core_miniport_key_digitron_entry (void);

/**
 * \brief MiniPort-LED ����
 */
void demo_zsn700_core_miniport_led_entry (void);

/**
 * \brief MiniPort-ZLG72128��ʾ����
 */
void demo_zsn700_core_miniport_zlg72128_entry (void);

/**
 * \brief gpio ����
 */
void demo_std_gpio_entry (int input_pin, int output_pin);

/**
 * \brief ��CPU������
 */
void demo_zsn700_core_dr_fm175xx_cpu_card (void);
/**
 * \brief A�࿨�������ͺͿ�������
 */
void demo_zsn700_core_dr_fm175xx_picca_read_id(void);

/**
 * \brief A�࿨�����߿�����
 */
void demo_zsn700_core_dr_fm175xx_picca_halt (void);

/**
 * \brief A�࿨��������
 */
void demo_zsn700_core_dr_fm175xx_picca_read_block (void);

/**
 * \brief A�࿨ֵ��������
 */
void demo_zsn700_core_dr_fm175xx_picca_val_operate(void);

/**
 * \brief A�࿨д������
 */
void demo_zsn700_core_dr_fm175xx_picca_write_block(void);

/**
 * \brief B�࿨����������
 */
void demo_zsn700_core_dr_fm175xx_piccb_read_id(void);
/**
 * \brief FM175XX LCPDģʽ A�࿨�������ͺͿ�������
 */
void demo_zsn700_core_dr_fm175xx_picca_lpcd_read_id(void);

/**
 * \brief ����KinetisFlashTool��λ����bootloader ����
 */
void demo_zsn700_core_kft_bootloader_entry (void);

/**
 * \brief ����KinetisFlashTool��λ����bootloader�Ĳ���Ӧ������
 */
void demo_zsn700_core_kft_application_entry (void);

/**

 * \brief ˫��bootloader�Ĳ���Ӧ�ó�������
 */

void demo_zsn700_core_double_application_entry (void);

/**

 * \brief ����bootloader�Ĳ���Ӧ�ó�������
 */

void demo_zsn700_core_single_application_entry (void);

/**
 * \brief ���ڴ������ֵĵ���bootloader����
 */
void demo_zsn700_core_single_bootloader_uart_entry (void);

/**
 * \brief ���ڴ������ֵ�˫��bootloader����
 */
void demo_zsn700_core_double_bootloader_uart_entry(void);

/**
 * \brief VC�жϴ������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_vc_int_entry (void);

/**
 * \brief LVDϵͳ��λ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_lvd_system_reset_entry (void);

/**
 * \brief LVD �ж����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_lvd_int_entry (void);

/**
 * \brief OPA��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_opa_one_entry (void);

/**
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_opa_dac_entry (void);

/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_aes_ency_decy_entry (void);

/**
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_trng_generate_entry (void);

/**
 * \brief LCD��ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsn700_core_hw_lcd_entry (void);

/**
 * \brief ZSN700 ��������A�࿨����
 */
void demo_zsn700_reader_picca_read_id (void);

/**
 * \brief A�࿨�������ͺͿ�������(8����)
 */
void demo_zsn700_reader_picca_read_id_8ant (void);

/**
 * \brief NTAG���������ͺͿ�������
 */
void demo_zsn700_reader_ntag_read_id (void);

/**
 * \brief ZSN700 ��������A���������
 */
void demo_zsn700_reader_picca_halt (void);

/**
 * \brief ZSN700 ��������A��LPCDģʽ����
 */
void demo_zsn700_reader_picca_lpcd_mode (void);

/**
 * \brief ZSN700 ��������A�������������
 */
void demo_zsn700_reader_picca_read_block (void);

/**
 * \brief CPU���������ͺͿ�������
 */
void demo_zsn700_reader_picca_read_cpu_card (void);

/**
 * \brief A�࿨ֵ��������
 */
void demo_zsn700_reader_picca_val_operate (void);

/**
 * \brief A�࿨д������
 */
void demo_zsn700_reader_picca_write_block (void);

/**
 * \brief B�࿨��������
 */
void demo_zsn700_reader_piccb_read_id (void);

/**
 * \brief ISO7816 �Ӵ�ʽ������
 */
void demo_zsn700_iso7816_entry (void);
