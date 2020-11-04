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
 * \brief hc32f460 �������̺����������
 * \sa demo_amhc32f460_all_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 20-01-16  cds, first implementation
 * \endinternal
 */


/**
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_adc_int_entry (void);

/**
 * \brief ADC DMA ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_adc_dma_entry (void);

/**
 * \brief ADC ��ͨ��ת�����̣� ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_multichan_adc_entry (void);

/**
 * \brief ADC ��ͨ������ɨ�����̣� ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_multichan_seq_adc_entry (void);

/**
 * \brief ADC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_adc_entry (void);

/**
 * \brief ��ͨ��ADC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_multichan_adc_entry (void);

/**
 * \brief ADC ����A�¼��������̣�ͨ��HW�ӿ�ʵ��
 */
void demo_hc32f460_core_hw_adc_seq_a_event_trigger_entry(void);

/**
 * \brief ADC ����A��B˫�����¼��������̣�ͨ��HW�ӿ�ʵ��
 */
void demo_hc32f460_core_hw_adc_seq_a_b_event_trigger_entry(void);

/**
 * \brief ADC �ɱ������Ŵ���PGA���� ͨ��HW�ӿ�ʵ��
 */
void demo_hc32f460_core_hw_adc_pga_entry(void);

/**
 * \brief ADC ģ�⿴�Ź�AWD���� ͨ��HW�ӿ�ʵ��
 */
void demo_hc32f460_core_hw_adc_awd_entry(void);

/**
 * \brief ��ADC Эͬ�������� ͨ��HW�ӿ�ʵ��
 */
void demo_hc32f460_core_hw_adc_sync_entry(void);

/**
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_buzzer_entry (void);

/**
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_clk_entry (void);

/**
 * \brief CRC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_crc_entry (void);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 */
void demo_hc32f460_core_drv_dma_m2m_entry (void);

/**
 * \brief DMA �ڴ浽�ڴ������������̣�ͨ��������ӿ�ʵ��
 */
void demo_hc32f460_core_drv_dma_m2m_chain_entry(void);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 */
void demo_hc32f460_core_drv_flash_entry (void);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_gpio_entry (void);

/**
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_gpio_trigger_entry (void);

/**
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_gpio_entry (void);

/**
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_gpio_trigger_entry (void);

/**
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_led_entry (void);

/**
 * \brief RTC ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_rtc_sec_int_entry (void);

/**
 * \brief RTC ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_rtc_entry (void);

/**
 * \brief QSPI ���̣�ͨ��������ӿ�ʵ��
 */
void demo_hc32f460_core_drv_qspi_entry (void);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_spi_master_entry (void);

/**
 * \brief SPI ���� DMA ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_spi_master_dma_entry (void);

/**
 * \brief SPI �����жϷ�ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_spi_master_int_entry (void);

/**
 * \brief SPI ������ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_spi_master_poll_entry (void);

/**
 * \brief SPI �ӻ�DMA��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_spi_slaver_dma_entry (void);

/**
 * \brief UART �ж����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_uart_int_entry (void);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_hw_uart_polling_entry (void);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_uart_rx_dma_entry (void);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_uart_tx_dma_entry (void);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_uart_polling_entry (void);

/**
 * \brief UART ���λ��������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_uart_ringbuf_entry (void);

/**
 * \brief WWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_wdt_entry (void);
/**
 * \brief WWDG �ж����̣�ͨ�� ���� ��ӿ�ʵ��
 */
void demo_hc32f460_core_drv_wdt_int_entry (void);

/**
 * \brief WWDG ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_wdt_entry (void);

/**
 * \brief gpio ���̣� ͨ����׼�ӿ�ʵ��
 */
void demo_std_gpio_entry (int input_pin, int output_pin);

/**
 * \brief TIM01 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim01_timing_entry(void);

/**
 * \brief TIM02 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim02_timing_entry(void);

/**
 * \brief TIMA1 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea1_timing_entry (void);

/**
 * \brief TIMA2 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea2_timing_entry (void);

/**
 * \brief TIMA3 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea3_timing_entry (void);

/**
 * \brief TIMA4 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea4_timing_entry (void);

/**
 * \brief TIMA5 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea5_timing_entry (void);

/**
 * \brief TIMA6 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea6_timing_entry (void);

/**
 * \brief TIM41 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim41_timing_entry (void);

/**
 * \brief TIM42 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim42_timing_entry (void);

/**
 * \brief TIM43 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim43_timing_entry (void);

/**
 * \brief TIM61 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim61_timing_entry (void);

/**
 * \brief TIM62 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim62_timing_entry (void);

/**
 * \brief TIM63 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim63_timing_entry (void);

/**
 * \brief TIMERA1 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea1_pwm_entry(void);

/**
 * \brief TIMERA2 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea2_pwm_entry(void);

/**
 * \brief TIMERA3 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea3_pwm_entry(void);

/**
 * \brief TIMERA4 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea4_pwm_entry(void);

/**
 * \brief TIMERA5 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea5_pwm_entry(void);

/**
 * \brief TIMERA6 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea6_pwm_entry(void);

/**
 * \brief TIM41 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim41_pwm_entry(void);

/**
 * \brief TIM42 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim42_pwm_entry(void);

/**
 * \brief TIM43 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_tim43_pwm_entry(void);

/**
 * \brief ADTIMER61 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_adtim61_pwm_entry(void);

/**
 * \brief ADTIMER62 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_adtim62_pwm_entry(void);

/**
 * \brief ADTIMER63 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_adtim63_pwm_entry(void);

/**
 * \brief TIMA1 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea1_cap_entry(void);

/**
 * \brief TIMA2 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea2_cap_entry(void);

/**
 * \brief TIMA3 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea3_cap_entry(void);

/**
 * \brief TIMA4 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea4_cap_entry(void);

/**
 * \brief TIMA5 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea5_cap_entry(void);

/**
 * \brief TIMA6 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_timea6_cap_entry(void);

/**
 * \brief ADTIMER61 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_adtim61_cap_entry(void);

/**
 * \brief ADTIMER62 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_adtim62_cap_entry(void);

/**
 * \brief ADTIMER63 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_adtim63_cap_entry(void);

/**
 * \brief I2C �������� EEPROM ���̣�ͨ��ͬ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_i2c_master_sync_entry (void);

/**
 * \brief I2C �������� EEPROM ���̣�ͨ���첽��׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_i2c_master_async_entry (void);

/**
 * \brief I2C ������ѯ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_i2c_master_poll_entry (void);

/**
 * \brief I2C �ӻ���ѯ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_i2c_slave_poll_entry (void);

/**
 * \brief RTC ���̣�ͨ����׼�ӿں��м������㺯��ʵ��
 */
void demo_hc32f460_core_std_rtc_entry (void);

/**
 * \brief CAN ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_can_entry (void);
/**
 * \brief USB msc���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_usbd_msc_entry (void);
/**
 * \brief USB mouse���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_usbd_mouse_entry (void);

/**
 * \brief USB hid custom���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_usbd_hid_custom_entry (void);

/**
 * \brief SD������д���̣�ͨ����׼��ӿ�ʵ��
 */
void demo_hc32f460_core_std_sdcard_entry (void);

/**
 * \brief ר�ÿ��Ź� �ж����̣�ͨ�� ���� ��ӿ�ʵ��
 */
void demo_hc32f460_core_drv_swdt_int_entry (void);

/**
 * \brief MPU �ڴ汣�����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_mpu_entry (void);

/**
 * \brief HASH ��ϢժҪ�������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_hash_entry (void);

/**
 * \brief HASH ��ϢժҪ�������̣�ͨ�� DRV ��ӿ�ʵ��
 */
void demo_hc32f460_core_drv_hash_entry(void);

/**
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_trng_generate_entry (void);

/**
 * \brief TRNG ������������̣�ͨ�� DRV ��ӿ�ʵ��
 */
void demo_hc32f460_core_drv_trng_entry(void);

/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_core_hw_aes_ency_decy_entry (void);

/**
 * \brief AES ���ܽ������̣�ͨ�� DRV ��ӿ�ʵ��
 */
void demo_hc32f460_core_drv_aes_entry (void);

/**
 * \brief DCU ���ݼ������̣�ͨ��HW�ӿ�ʵ��
 */
void demo_hc32f460_core_hw_dcu_entry (void);

/**
 * \brief KEY���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_hc32f460_core_std_key_input_event_entry (void);
