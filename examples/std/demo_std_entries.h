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
 * \brief STD�������̺����������
 * \sa    demo_std_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  sdy, first implementation
 * \endinternal
 */

#ifndef __DEMO_STD_ENTRIES_H
#define __DEMO_STD_ENTRIES_H

#include "am_cap.h"
#include "am_crc.h"
#include "am_i2c.h"
#include "am_i2c_slv.h"
#include "am_pwm.h"
#include "am_wdt.h"
#include "am_spi.h"
#include "am_spi_slv.h"
#include "am_adc.h"
#include "am_can.h"
#include "am_uart.h"
#include "am_temp.h"
#include "am_timer.h"
#include "am_rtc.h"
#include "am_pcf85063.h"
#include "am_hc595.h"
#include "am_sensor.h"
#include "am_sdcard.h"
#include "am_dac.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ADC���̣����ò�ѯ��ʽ��ȡADCת�������ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle ADC ��׼������
 * \param[in] chan   ADC ͨ����
 *
 * \return ��
 */
void demo_std_adc_entry (am_adc_handle_t handle, int chan);

/**
 * \brief ADC�ڲ��¶ȴ��������̣����ò�ѯ��ʽ��ȡADCת�������ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle ADC ��׼������
 * \param[in] chan   ADC ͨ����
 *
 * \return ��
 */
void demo_std_adc_its_entry (am_adc_handle_t handle, int chan);

/**
 * \brief �������
 */
void demo_std_multichan_adc_entry (am_adc_handle_t handle,
                                   int            *p_chan,
                                   int             chan_num);

/**
 * \brief ADC ���ð��ӵ���������(NTC)��������¶����̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle    ADC ��׼������
 * \param[in] chan      ADC ͨ���ţ���ͨ����Ӧ�������������� NTC �ˣ�
 * \param[in] res_fixed �̶���ѹ����ֵ����λ��ŷķ���������Ӳ����·���
 *
 * \return ��
 */
void demo_std_adc_ntc_entry (am_adc_handle_t handle,
                             int             chan,
                             uint32_t        res_fixed);

/**
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_std_buzzer_entry (void);

/**
 * \brief ��ʱ��ʵ�ֲ����ܣ�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] cap_handle ���벶���׼������
 * \param[in] pwm_handle PWM ��׼������
 * \param[in] cap_chan   ��ʱ������ͨ����һ��Ĭ��ʹ�ò���ͨ�� 0��
 * \param[in] pwm_chan   ��ʱ�����ͨ����һ��Ĭ��ʹ�� PWM ͨ�� 0��
 *
 * \return ��
 */
void demo_std_timer_cap_entry (am_cap_handle_t cap_handle, int cap_chan);

/**
 * \brief CRC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] crc_handle CRC ��׼������
 *
 * \return ��
 */
void demo_std_crc_entry (am_crc_handle_t crc_handle);

/**
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] input_pin  GPIO �ܽű�� (# PIO*_0)
 * \param[in] output_pin GPIO �ܽű�� (# PIO*_0)
 *
 * \return ��
 */
void demo_std_gpio_entry (int input_pin, int output_pin);

/**
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] pin GPIO �ܽű�� (# PIO*_0)
 *
 * \return ��
 */
void demo_std_gpio_trigger_entry (int pin);

/**
 * \brief I2C ������ȡ�¶ȴ����� LM75 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle �¶ȱ�׼������
 *
 * \return ��
 */
void demo_std_i2c_lm75_entry (am_temp_handle_t handle);

/**
 * \brief I2C �������� EEPROM �豸���̣�ͨ���첽��׼�ӿ�ʵ��
 *
 * \param[in] handle      I2C ��׼������
 * \param[in] eeprom_addr EEPROM ��ַ
 * \param[in] test_len    �����ֽ���
 *
 * \return ��
 */
void demo_std_i2c_master_async_entry (am_i2c_handle_t handle,
                                      uint32_t        eeprom_addr,
                                      uint32_t        test_len);

/**
 * \brief I2C �������� EEPROM �豸���̣�ͨ��ͬ����׼�ӿ�ʵ��
 *
 * \param[in] handle      I2C ��׼������
 * \param[in] eeprom_addr EEPROM ��ַ
 * \param[in] test_len    �����ֽ���
 *
 * \return ��
 */
void demo_std_i2c_master_sync_entry (am_i2c_handle_t handle,
                                     uint32_t        eeprom_addr,
                                     uint32_t        test_len);

/**
 * \brief I2C �ӻ�ģ�� TMP100 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle I2C ��׼������
 *
 * \return ��
 */
void demo_std_i2c_slave_subaddr_entry (am_i2c_slv_handle_t handle);

/**
 * \brief I2C �ӻ����̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle   I2C ��׼������
 * \param[in] dev_addr �ӻ���ַ
 *
 * \return ��
 */
void demo_std_i2c_slave_entry (am_i2c_slv_handle_t handle, uint16_t dev_addr);
 
/**
 * \brief �������̣�4��������
 * \param[in] led_id LED ���
 * \return ��
 */
void demo_std_4key_entry (void);

/**
 * \brief ��������
 * \return ��
 */
void demo_std_key_entry (void);

/**
 * \brief �������̣�ʹ���������ʾ��ǰ���µİ����������¼��ڰ����ص�����������
 * \param[in] id  ����ܱ��
 * \return ��
 */
void demo_std_key_digitron_entry (int32_t id);

/**
 * \brief �������̣�ʹ���������ʾ��ǰ���µİ����������¼����浽���λ������У�
 * \param[in] id  ����ܱ��
 * \return ��
 */
void demo_std_key_digitron_rngbuf_entry (int32_t id);

/**
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 * \param[in] led_id LED ���
 * \return ��
 */
void demo_std_led_entry (int led_id);

/**
 * \brief LED ��ˮ������
 *
 * \param[in] led_id_start  ���LED����ʼ���
 * \param[in] num           ������ˮ�����̵� LED ��Ŀ
 *
 * \return ��
 */
void demo_std_led_water_light_entry (int led_id_start, int num);

/**
 * \brief ��ʱ�� PWM ������ܣ�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] pwm_handle   PWM ��׼������
 * \param[in] pwm_chan     ͨ����
 *
 * \return ��
 */
void demo_std_timer_pwm_entry (am_pwm_handle_t pwm_handle, int pwm_chan);

/**
 * \brief �����ʱ�����̣�ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_std_softimer_entry (void);

/**
 * \brief SPI ��д FLASH(MX25L3206E) ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] spi_handle  SPI ��׼������
 * \param[in] cs_pin      Ƭѡ���ź�
 * \param[in] test_addr   ���Ե�ַ
 * \param[in] test_length �����ֽ���
 *
 * \return ��
 */
void demo_std_spi_flash_entry (am_spi_handle_t spi_handle,
                               int             cs_pin,
                               uint32_t        test_addr,
                               uint32_t        test_length);

/**
 * \brief SPI ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] spi_handle SPI ��׼������
 * \param[in] cs_pin     Ƭѡ���ź�
 *
 * \return ��
 */
void demo_std_spi_master_entry (am_spi_handle_t spi_handle,
                                int             cs_pin);

/**
 * \brief SPI �ӻ����̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] spi_handle SPI ��׼������
 * \param[in] cs_pin     Ƭѡ���ź�
 *
 * \return ��
 */
void demo_std_spi_slave_entry (am_spi_slv_handle_t handle);

/**
 * \brief ��ʱ��׼�ӿ����̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] led_id LED ���
 *
 * \return ��
 */
void demo_std_delay_entry (int led_id);

/**
 * \brief Systick ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle ��ʱ����׼������
 * \param[in] led_id LED ���
 *
 * \return ��
 */
void demo_std_systick_timer_entry (am_timer_handle_t handle, int led_id);

/**
 * \brief ��ʱ��ʵ�ֱ�׼��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle      ��ʱ����׼������
 * \param[in] timing_chan ��ʱ��ͨ����
 *
 * \return ��
 */
void demo_std_timer_timing_entry (am_timer_handle_t handle,
                                  int               timing_chan);

/**
 * \brief UART ��ѯ��ʽ�½��շ����������̣�ͨ����׼�ӿ�ʵ��
 * \param[in] handle UART ��׼������
 * \return ��
 */
void demo_std_uart_polling_entry (am_uart_handle_t handle);

/**
 * \brief UART ���λ�������ʽ�½��շ����������̣�ͨ����׼�ӿ�ʵ��
 * \param[in] uart_handle UART ��׼������
 * \return ��
 */
void demo_std_uart_ringbuf_entry (am_uart_handle_t uart_handle);

/**
 * \brief UART RS485����
 * \param[in] uart_handle UART ��׼������
 * \return ��
 */
void demo_std_uart_rs485_entry (am_uart_handle_t uart_handle);

/**
 * \brief WDT ��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param[in] handle       WDT ��׼������
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \return ��
 */
void demo_std_wdt_entry (am_wdt_handle_t handle,
                         uint32_t        time_out_ms,
                         uint32_t        feed_time_ms);
                         
/**
 * \brief �������ʾ60���ʱ����
 * \param[in] id ����ܱ��
 * \return ��
 */          
void demo_std_digitron_60s_counting_entry (int32_t id);

/**
 * \brief �����ʵʱ��ʾ�¶�����
 *
 * \param[in] id          ����ܱ��
 * \param[in] temp_handle �¶ȴ�������׼������
 *
 * \return ��
 */
void demo_std_digitron_temp_entry (int32_t id, am_temp_handle_t temp_handle);
 
/**
 * \brief HC595 ������̣�Ϊ���ڹ۲����󣬽��齫HC595��8��������ӵ�LED��
 * \param[in] hc595_handle  HC595 ��׼������
 * \return ��
 */
void demo_std_hc595_led_entry (am_hc595_handle_t hc595_handle);

/**
 * \brief RTC����
 * \param[in] rtc_handle  RTC�豸��׼������
 * \return ��
 */
void demo_std_rtc_entry (am_rtc_handle_t rtc_handle);

/**
 * \brief HMI����
 * \param[in] pcf85063_handle  PCF85063�豸��׼������
 * \return ��
 */
void demo_std_hmi_int_entry (am_pcf85063_handle_t pcf85063_handle);

/**
 * \brief NVRAM ��������
 *
 * ����ʹ�õĴ洢������ __g_nvram_segs[] �б��ж��壨am_nvram_cfg.c �ļ��У�
 *
 * \param[in] p_nvram_name  �洢����
 * \param[in] nvram_unit    �洢�ε�Ԫ��
 * \param[in] test_lenth    ���Զ�д���ݵĳ���
 *
 * \return ��
 */
void demo_std_nvram_entry (char *p_nvram_name, int32_t nvram_unit, int32_t test_lenth);

/**
 * \brief can ��������
 *
 * \param[in] can_handle    can ��׼������
 * \param[in] can_btr_baud  �����ʲ���
 *
 * \return ��
 */
void demo_std_can_entry (am_can_handle_t can_handle, am_can_bps_param_t  *can_btr_baud);


/**
 * \brief ��ʪ�ȴ�����HTS221���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_hts221_int_entry (am_sensor_handle_t handle);

/**
 * \brief ��ʪ�ȴ�����HTS221���̣�ͨ����ѯ��ʽʵ��
 *
 * \return ��
 */
void demo_std_hts221_entry (am_sensor_handle_t handle);

/**
 * \brief ѹ���¶ȴ�����BMP280���̣�ͨ����ѯ��ʽʵ��
 *
 * \return ��
 */
void demo_std_bmp280_entry (am_sensor_handle_t handle);

/**
 * \brief ѹ����ʪ�ȴ�����BME280���̣�ͨ����ѯ��ʽʵ��
 *
 * \return ��
 */
void demo_std_bme280_entry (am_sensor_handle_t handle);

/**
 * \brief ѹ���¶ȴ�����LPS22HB���̣�ͨ����ѯ��ʽʵ��
 *
 * \return ��
 */
void demo_std_lps22hb_entry (am_sensor_handle_t handle);

/**
 * \brief ѹ���¶ȴ�����LPS22HB���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_lps22hb_int_entry (am_sensor_handle_t handle);

/**
 * \brief ���������Ǵ�����BMG160���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_bmg160_entry (am_sensor_handle_t handle);

/**
 * \brief ����Ŵ�����MMC5883MA���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_mmc5883ma_entry (am_sensor_handle_t handle);

/**
 * \brief ���ᴫ����FXOS8700CQ���̣�ͨ����ѯ��ʽʵ��
 *
 * \return ��
 */
void demo_std_fxos8700cq_entry (am_sensor_handle_t handle);

/**
 * \brief ���ᴫ����FXOS8700CQ���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_fxos8700cq_int_entry (am_sensor_handle_t handle);

/**
 * \brief ��ѹ�¶ȴ�����MPL3115A2���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_mpl3115a2_entry (am_sensor_handle_t handle);

/**
 * \brief ��ѹ�¶ȴ�����MPL3115A2���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_mpl3115a2_int_entry (am_sensor_handle_t handle);

/**
 * \brief ����������MAG3110���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_mag3110_entry (am_sensor_handle_t handle);

/**
 * \brief ����������MAG3110���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_mag3110_int_entry (am_sensor_handle_t handle);

/**
 * \brief ������/��ɫ���ӽ������� TMD3702VC���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tmd3702vc_entry (am_sensor_handle_t handle);

/**
 * \brief ������/��ɫ���ӽ������� TMD3702VC���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tmd3702vc_int_entry (am_sensor_handle_t handle);

/**
 * \brief �����⴫���� TSL2540���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tsl2540_entry (am_sensor_handle_t handle);

/**
 * \brief �����⴫���� TSL2540���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tsl2540_int_entry (am_sensor_handle_t handle);

/**
 * \brief ������/��ɫ������ TCS3430���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tcs3430_entry (am_sensor_handle_t handle);

/**
 * \brief ������/��ɫ������ TCS3430���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tcs3430_int_entry (am_sensor_handle_t handle);

/**
 * \brief �ӽ������� TMD2635���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tmd2635_entry (am_sensor_handle_t handle);

/**
 * \brief �ӽ������� TMD2635���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tmd2635_int_entry (am_sensor_handle_t handle);

/**
 * \brief �����⡢�ӽ������� TMD2750���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tmd2750_entry (am_sensor_handle_t handle);

/**
 * \brief �����⡢�ӽ������� TMD2750���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tmd2750_int_entry (am_sensor_handle_t handle);

/**
 * \brief �¶ȴ����� AS621x ���̣�ͨ���Ƚ�ģʽʵ��
 *
 * \return ��
 */
void demo_std_as621x_comparator_mode_entry (am_sensor_handle_t handle);

/**
 * \brief �¶ȴ����� AS621x ���̣�ͨ���ж�ģʽʵ��
 *
 * \return ��
 */
void demo_std_as621x_interrupt_mode_entry (am_sensor_handle_t handle);

/**
 * \brief ������/��ɫ���ӽ�/���ƴ����� TMG49037���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tmg49037_entry (am_sensor_handle_t handle);

/**
 * \brief ������/��ɫ���ӽ�/���ƴ����� TMG49037���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tmg49037_int_entry (am_sensor_handle_t handle);

/**
 * \brief ���״����� AS7341���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_as7341_entry (am_sensor_handle_t handle);

/**
 * \brief ���״����� AS7341���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_as7341_int_entry (am_sensor_handle_t handle);

/**
 * \brief �߹��״����� AS7421���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_as7421_entry (am_sensor_handle_t handle);

/**
 * \brief �߹��״����� AS7421���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_as7421_int_entry (am_sensor_handle_t handle);

/**
 * \brief ���״����� AS7262���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_as7262_entry (am_sensor_handle_t handle);

/**
 * \brief ���״����� AS7262���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_as7262_int_entry (am_sensor_handle_t handle);

/**
 * \brief �Ƕȴ����� AS5600���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_as5600_entry (am_sensor_handle_t handle);

/**
 * \brief TOF������ TMF8801���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tmf8801_entry (am_sensor_handle_t handle);

/**
 * \brief TOF������ TMF8801���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tmf8801_int_entry (am_sensor_handle_t handle);

/**
 * \brief �����⴫���� TSL2560���̣�ͨ����ѯģʽʵ��
 *
 * \return ��
 */
void demo_std_tsl2560_entry (am_sensor_handle_t handle);

/**
 * \brief �����⴫���� TSL2560���̣�ͨ������ģʽʵ��
 *
 * \return ��
 */
void demo_std_tsl2560_int_entry (am_sensor_handle_t handle);

/**
 * \brief SD Card��д����
 *
 * \return ��
 */
//void demo_std_sdcard_entry (am_sdcard_handle_t handle);

/**
 * \brief DAC�����ѹ����׼�ӿڲ�ʵ��
 * \return ��
 */
void demo_std_dac_entry (am_dac_handle_t dac0_handle,
                         uint8_t         channel,
                         uint32_t        mv_out);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_STD_ENTRIES_H */

/* end of file */
