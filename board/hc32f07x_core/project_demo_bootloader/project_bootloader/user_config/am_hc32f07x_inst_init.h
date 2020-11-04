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
 * \brief HC32 ���� ʵ����ʼ����������
 *
 * ���������豸��I2C��SPI��ADC...����ʵ����ʼ���������ڱ�ͷ�ļ���������ʹ��ʵ��
 * ��ʼ���������������ɻ��һ������ľ����Ȼ��ʹ����صĽӿں�����������в�����
 *
 * \sa am_hc32f19x_inst_init.h
 * \internal
 * \par Modification history
 * - 1.00 15-12-11  tee, first implementation
 * \endinternal
 */

#ifndef __am_hc32_inst_init_H
#define __am_hc32_inst_init_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_adc.h"
#include "am_crc.h"
#include "am_can.h"	
#include "am_i2c.h"
#include "am_i2c_slv.h"
#include "am_timer.h"
#include "am_cap.h"
#include "am_pwm.h"
#include "am_wdt.h"
#include "am_spi.h"
#include "am_led.h"
#include "am_uart.h"
#include "am_dac.h"
#include "am_rtc.h"
#include "am_ftl.h"
#include "am_temp.h"
#include "am_delay.h"
#include "am_hc595.h"
#include "am_ili9341.h"
#include "am_rx8025t.h"
#include "am_digitron_disp.h"
#include "am_ep24cxx.h"
#include "am_mx25xx.h"
#include "am_mtd.h"
#include "am_rngbuf.h"
#include "am_input.h"
#include "am_usbd_msc.h"

#include "am_hc32_pca.h"
#include "am_hc32f07x_opa.h"
//#include "am_hc32_pcnt.h"
//#include "amhw_hc32_rtc.h"
//#include "am_hc32_pwr.h"
#include "am_hwconf_hc32f07x_led_gpio.h"
//#include "am_hwconf_led_gpio.h"
#include "am_hwconf_key_gpio.h"
#include "am_hwconf_buzzer_pwm.h"
#include "am_hwconf_debug_uart.h"
#include "am_hwconf_system_tick_softimer.h"
//#include "am_hwconf_lm75.h"
//#include "am_hwconf_microport.h"
//#include "am_hwconf_miniport_zlg72128.h"
//#include "am_hwconf_miniport_595.h"
//#include "am_hwconf_miniport_view.h"
//#include "am_hwconf_miniport_led.h"
//#include "am_hwconf_miniport_key.h"
//#include "am_hwconf_miniport_view_key.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"

/**
 * \addtogroup am_if_hc32_inst_init
 * \copydoc am_hc32f07x_inst_init.h
 * @{
 */


/**
 * \brief  timer_pwm ����
 *
 * \param[in] pwm_handle : cap��׼���
 *
 * \param[in] pwm_chan   : cap ͨ��
 */
void demo_std_timer_pwm_entry (am_pwm_handle_t pwm_handle, int pwm_chan);

/**
 * \brief  timer_cap ����
 *
 * \param[in] cap_handle : cap��׼���
 *
 * \param[in] cap_chan   : cap ͨ��
 */
void demo_std_timer_cap_entry (am_cap_handle_t cap_handle, int cap_chan);

/**
 * \brief  uart_polling ����
 *
 * \param[in] handle : uart��׼���
 */
void demo_std_uart_polling_entry (am_uart_handle_t handle);

/**
 * \brief  delay ����
 *
 * \param[in] led_id : led id��
 */
void demo_std_delay_entry (int led_id);

/**
 * \brief  key_digitron ����
 *
 * \param[in] rtc_handle : rtc ��׼���
 */
void demo_std_rtc_entry (am_rtc_handle_t rtc_handle);

/**
 * \brief  key_digitron ����
 *
 * \param[in] id : key id��
 */
void demo_std_key_digitron_rngbuf_entry (int32_t id);

/**
 * \brief  hc595_led ����
 *
 * \param[in] led_id_start : ��ʼled id��
 *
 * \param[in] num          : led����
 */
void demo_std_led_water_light_entry (int led_id_start, int num);

/**
 * \brief  hc595_led ����
 *
 * \param[in] ��
 */
 void demo_std_4key_entry (void);
 
/**
 * \brief  hc595_led ����
 *
 * \param[in] hc595_handle  : ��׼hc595���
 */
// void demo_std_hc595_led_entry (am_hc595_handle_t hc595_handle);
/**
 * \brief  digitron_temp ����
 *
 * \param[in] temp_handle  : ��׼temp_handle���
 *
 * \param[in] id        : id��
 */
void demo_std_digitron_temp_entry (int32_t id, am_temp_handle_t temp_handle);
/**
 * \brief  key_digitron ����
 *
 * \param[in] id     : id��
 */
void demo_std_key_digitron_entry (int32_t id);
	
/**
 * \brief  digitron ����
 *
 * \param[in] id     : id��
 */
void demo_std_digitron_60s_counting_entry (int32_t id);

/**
 * \brief  mtd ����
 *
 * \param[in] rtc_handle     : rtc ���
 */
void demo_std_rtc_entry (am_rtc_handle_t rtc_handle);

/**
 * \brief timer��ʱ��
 *
 * \param[in] am_timer_handle_t  : timer���
 *
 * \param[in] timing_chan        : ͨ��
 */
void demo_std_timer_timing_entry (am_timer_handle_t handle,
                                  int               timing_chan);

/**
 * \brief ʵ����ʼ������
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_key_gpio_inst_init (void);

/**
 * \brief �ж�ʵ����ʼ������ʼ���ж�����
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32_nvic_inst_init (void);

/**
 * \brief �ж�ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_hc32_nvic_inst_deinit (void);

/**
 * \brief ADC ʵ����ʼ������� ADC ��׼������
 *
 * \param ��
 *
 * \return ADC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_adc_handle_t am_hc32_adc_inst_init (void);

/**
 * \brief ADC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_adc1_inst_init() ������õ� ADC ��׼������
 *
 * \return ��
 */
void am_hc32_adc_inst_deinit (am_adc_handle_t handle);

/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32_clk_inst_init (void);

/**
 * \brief CRC ʵ����ʼ������� CRC ��׼������
 *
 * \param ��
 *
 * \return CRC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_crc_handle_t am_hc32_crc_inst_init (void);

/**
 * \brief CRC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_crc_inst_init() ������õ� CRC ��׼������
 *
 * \return ��
 */
void am_hc32_crc_inst_deinit (am_crc_handle_t handle);

/**
 * \brief DAC ʵ����ʼ������� DAC ��׼������
 *
 * \param ��
 *
 * \return DAC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_dac_handle_t am_hc32_dac0_inst_init (void);

/**
 * \brief DAC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_dac_inst_init() ������õ� DAC ��׼������
 *
 * \return ��
 */
void am_hc32_dac0_inst_deinit (am_dac_handle_t handle);

/**
 * \brief DAC ʵ����ʼ������� DAC ��׼������
 *
 * \param ��
 *
 * \return DAC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_dac_handle_t am_hc32_dac1_inst_init (void);

/**
 * \brief DAC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_dac_inst_init() ������õ� DAC ��׼������
 *
 * \return ��
 */
void am_hc32_dac1_inst_deinit (am_dac_handle_t handle);

/**
 * \brief DMA ʵ����ʼ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32_dma_inst_init (void);

/**
 * \brief DMA ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_hc32_dma_inst_deinit (void);

/**
 * \brief GPIO ʵ����ʼ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32_gpio_inst_init (void);

/**
 * \brief GPIO ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_hc32_gpio_inst_deinit (void);

/**
 * \brief I2C1 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_hc32_i2c1_inst_init (void);

/**
 * \brief I2C1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_i2c1_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_hc32_i2c1_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C2 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_hc32_i2c0_inst_init (void);

/**
 * \brief I2C2 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_i2c2_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_hc32_i2c0_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C1 �ӻ�ʵ����ʼ������� I2C �ӻ���׼������
 *
 * \param ��
 *
 * \return I2C �ӻ���׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_slv_handle_t am_hc32_i2c1_slv_inst_init (void);

/**
 * \brief I2C1 �ӻ�ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_i2c1_slv_inst_init() ����
 *                   ��õ� I2C �ӻ���׼������
 *
 * \return ��
 */
void am_hc32_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle);

/**
 * \brief I2C2 �ӻ�ʵ����ʼ������� I2C �ӻ���׼������
 *
 * \param ��
 *
 * \return I2C �ӻ���׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_slv_handle_t am_hc32_i2c0_slv_inst_init (void);

/**
 * \brief I2C2 �ӻ�ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_i2c2_slv_inst_init() ����
 *                   ��õ� I2C �ӻ���׼������
 *
 * \return ��
 */
void am_hc32_i2c0_slv_inst_deinit (am_i2c_slv_handle_t handle);

/**
 * \brief RTC ʵ����ʼ������� RTC ��׼������
 *
 * \param ��
 *
 * \return RTC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_hc32_rtc_inst_init (void);

/**
 * \brief RTC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_rtc_inst_init() ������õ� RTC ��׼������
 *
 * \return ��
 */
void am_hc32_rtc_inst_deinit (am_rtc_handle_t handle);

/**
 * \brief SPI0 DMA ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32_spi0_dma_inst_init (void);

/**
 * \brief SPI2 DMA ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_spi0_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32_spi0_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 DMA ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32_spi1_dma_inst_init (void);

/**
 * \brief SPI1 DMA ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_spi1_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32_spi1_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI0 INT ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32_spi0_int_inst_init (void);

/**
 * \brief SPI0 INT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_spi0_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32_spi0_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 INT ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32_spi1_int_inst_init (void);

/**
 * \brief SPI1 INT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_spi1_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32_spi1_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI0 poll ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32_spi0_poll_inst_init (void);

/**
 * \brief SPI2 poll ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_spi0_poll_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32_spi0_poll_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 poll ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32_spi1_poll_inst_init (void);

/**
 * \brief SPI1 poll ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_spi1_poll_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32_spi1_poll_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SYSTICK ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_systick_inst_init (void);

/**
 * \brief SYSTICK ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_systick_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32_systick_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM0 CAP ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32_tim0_cap_inst_init (void);

/**
 * \brief TIM0 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim3_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim0_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM1 CAP ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32_tim1_cap_inst_init (void);

/**
 * \brief TIM1 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim1_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim1_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM2 CAP ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32_tim2_cap_inst_init (void);

/**
 * \brief TIM2 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim2_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim2_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM3 CAP ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32_tim3_cap_inst_init (void);

/**
 * \brief TIM3 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim3_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim3_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM0 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32_tim0_pwm_inst_init (void);

/**
 * \brief TIM0 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim1_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32_tim0_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM1 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32_tim1_pwm_inst_init (void);

/**
 * \brief TIM1 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim1_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32_tim1_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM2 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32_tim2_pwm_inst_init (void);

/**
 * \brief TIM2 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim2_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32_tim2_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM3 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32_tim3_pwm_inst_init (void);

/**
 * \brief TIM3 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim3_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32_tim3_pwm_inst_deinit (am_pwm_handle_t handle);


/**
 * \brief TIM0 TIMING ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_tim0_timing_inst_init (void);

/**
 * \brief TIM0 TIMING ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim0_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32_tim0_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM1 TIMING ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_tim1_timing_inst_init (void);

/**
 * \brief TIM1 TIMING ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim1_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32_tim1_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM2 TIMING ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_tim2_timing_inst_init (void);

/**
 * \brief TIM2 TIMING ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim2_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32_tim2_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM3 TIMING ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_tim3_timing_inst_init (void);

/**
 * \brief TIM3 TIMING ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim3_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32_tim3_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief LPTIM0 TIMING ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_lptim0_timing_inst_init (void);

/**
 * \brief LPTIM0 TIMING ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_lptim0_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32_lptim0_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief LPTIM1 TIMING ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_lptim1_timing_inst_init (void);

/**
 * \brief LPTIM1 TIMING ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_lptim1_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32_lptim1_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ADTIM4 CAP ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32_tim4_cap_inst_init (void);

/**
 * \brief ADTIM4 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim4_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim4_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief ADTIM5 CAP ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32_tim5_cap_inst_init (void);

/**
 * \brief ADTIM5 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim5_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim5_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief ADTIM6 CAP ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32_tim6_cap_inst_init (void);

/**
 * \brief ADTIM6 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim6_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim6_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief ADTIM4 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32_tim4_pwm_inst_init (void);

/**
 * \brief ADTIM4 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim4_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32_tim4_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief ADTIM5 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32_tim5_pwm_inst_init (void);

/**
 * \brief ADTIM5 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim5_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32_tim5_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief ADTIM6 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32_tim6_pwm_inst_init (void);

/**
 * \brief ADTIM6 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim6_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32_tim6_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief ADTIM4 timing ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_tim4_timing_inst_init (void);

/**
 * \brief ADTIM4 timing ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim4_timing_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim4_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ADTIM5 timing ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_tim5_timing_inst_init (void);

/**
 * \brief ADTIM5 timing ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim5_timing_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim5_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ADTIM6 timing ʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32_tim6_timing_inst_init (void);

/**
 * \brief ADTIM6 timing ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_tim6_timing_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32_tim6_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief UART0 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32_uart0_inst_init (void);

/**
 * \brief UART0 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_uart1_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32_uart0_inst_deinit (am_uart_handle_t handle);

/**
 * \brief UART1 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32_uart1_inst_init (void);

/**
 * \brief UART1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_uart1_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32_uart1_inst_deinit (am_uart_handle_t handle);

/**
 * \brief UART2 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32_uart2_inst_init (void);

/**
 * \brief UART2 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_uart2_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32_uart2_inst_deinit (am_uart_handle_t handle);

/**
 * \brief UART3 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32_uart3_inst_init (void);

/**
 * \brief UART3 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_uart3_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32_uart3_inst_deinit (am_uart_handle_t handle);

/**
 * \brief LPUART0 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32_lpuart0_inst_init (void);

/**
 * \brief LPUART0 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_lpuart0_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32_lpuart0_inst_deinit (am_uart_handle_t handle);

/**
 * \brief LPUART1 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32_lpuart1_inst_init (void);

/**
 * \brief LPUART1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_lpuart1_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32_lpuart1_inst_deinit (am_uart_handle_t handle);

/**
 * \brief WDT ʵ����ʼ������� WDT ��׼������
 *
 * \param ��
 *
 * \return WDT ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_wdt_handle_t am_hc32_wdt_inst_init (void);

/**
 * \brief WDT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32_wdt_inst_init() ������õ� WDT ��׼������
 *
 * \return ��
 */
void am_hc32_wdt_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief PCA ʵ����ʼ��
 */
am_hc32_pca_handle_t am_hc32_pca_inst_init (void);

/**
 * \brief PCA ʵ�����ʼ��
 */
void am_hc32_pca_inst_deinit (am_hc32_pca_handle_t handle);

/**
 * \brief OPA ʵ����ʼ�������OPA ������
 *
 * \param ��
 *
 * \return OPA ����������Ϊ NULL��������ʼ��ʧ��
 */
am_opa_handle_t am_hc32_opa0_inst_init (void);

/**
 * \brief OPA ʵ����ʼ�������OPA ������
 *
 * \param ��
 *
 * \return OPA ����������Ϊ NULL��������ʼ��ʧ��
 */
am_opa_handle_t am_hc32_opa1_inst_init (void);

/**
 * \brief OPA ʵ����ʼ�������OPA ������
 *
 * \param ��
 *
 * \return OPA ����������Ϊ NULL��������ʼ��ʧ��
 */
am_opa_handle_t am_hc32_opa2_inst_init (void);

/**
 * \brief OPA ʵ����ʼ�������OPA ������
 *
 * \param ��
 *
 * \return OPA ����������Ϊ NULL��������ʼ��ʧ��
 */
am_opa_handle_t am_hc32_opa3_inst_init (void);

/**
 * \brief OPA ʵ����ʼ�������OPA ������
 *
 * \param ��
 *
 * \return OPA ����������Ϊ NULL��������ʼ��ʧ��
 */
am_opa_handle_t am_hc32_opa4_inst_init (void);

/**
 * \brief CAN ʵ����ʼ�������CAN ������
 *
 * \param ��
 *
 * \return CAN ������
 */
am_can_handle_t am_hc32f07x_can_inst_init (void);

/**
 * \brief CAN ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f072_can_inst_init() ������õ�CAN ������
 *
 * \return ��
 */
void am_hc32f07x_can_inst_deinit (am_can_handle_t handle);

/**
 * \brief USB ʵ����ʼ�������USB ������
 *
 * \param ��
 *
 * \return USB ������
 */
am_usbd_dev_t am_hc32f07x_usbd_mouse_inst_init (void);

/**
 * \brief USB ʵ�����ʼ��
 *
 *
 * \return ��
 */
void am_hc32f07x_usbd_mouse_inst_deinit (void);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __am_hc32_inst_init_H */

/* end of file */
