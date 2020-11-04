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
 * \brief HC32F460 ���� ʵ����ʼ����������
 *
 * ���������豸��I2C��SPI��ADC...����ʵ����ʼ���������ڱ�ͷ�ļ���������ʹ��ʵ��
 * ��ʼ���������������ɻ��һ������ľ����Ȼ��ʹ����صĽӿں�����������в�����
 *
 * \sa am_hc32f460_inst_init.h
 * \internal
 * \par Modification history
 * - 1.00 15-12-11  tee, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_INST_INIT_H
#define __AM_HC32F460_INST_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_adc.h"
#include "am_crc.h"
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
#include "am_can.h"
#include "am_sdio.h"
#include "am_sdcard.h"
#include "am_spi_slv.h"
#include "am_usbd_msc.h"
//#include "am_hwconf_led_gpio.h"
#include "am_hwconf_key_gpio.h"
//#include "am_hwconf_buzzer_pwm.h"
//#include "am_hwconf_debug_uart.h"
#include "am_hwconf_system_tick_softimer.h"
//#include "am_hwconf_lm75.h"
//#include "am_hwconf_microport.h"
//#include "am_hwconf_miniport_zlg72128.h"
//#include "am_hwconf_miniport_595.h"
//#include "am_hwconf_miniport_view.h"
//#include "am_hwconf_miniport_led.h"
//#include "am_hwconf_miniport_key.h"
//#include "am_hwconf_miniport_view_key.h"
//#include "am_event_input_key.h"
//#include "am_event_category_input.h"

#include "am_hc32f460_aes.h"
#include "am_hc32f460_hash.h"
#include "am_hc32f460_trng.h"
#include "am_hc32f460_qspi.h"

/**
 * \addtogroup am_if_hc32f460_inst_init
 * \copydoc am_hc32f460_inst_init.h
 * @{
 */


///**
// * \brief  timer_pwm ����
// *
// * \param[in] pwm_handle : cap��׼���
// *
// * \param[in] pwm_chan   : cap ͨ��
// */
//void demo_std_timer_pwm_entry (am_pwm_handle_t pwm_handle, int pwm_chan);
//
///**
// * \brief  timer_cap ����
// *
// * \param[in] cap_handle : cap��׼���
// *
// * \param[in] cap_chan   : cap ͨ��
// */
//void demo_std_timer_cap_entry (am_cap_handle_t cap_handle, int cap_chan);
//
///**
// * \brief  uart_polling ����
// *
// * \param[in] handle : uart��׼���
// */
//void demo_std_uart_polling_entry (am_uart_handle_t handle);
//
///**
// * \brief  delay ����
// *
// * \param[in] led_id : led id��
// */
//void demo_std_delay_entry (int led_id);
//
///**
// * \brief  key_digitron ����
// *
// * \param[in] rtc_handle : rtc ��׼���
// */
//void demo_std_rtc_entry (am_rtc_handle_t rtc_handle);
//
///**
// * \brief  key_digitron ����
// *
// * \param[in] id : key id��
// */
//void demo_std_key_digitron_rngbuf_entry (int32_t id);
//
///**
// * \brief  hc595_led ����
// *
// * \param[in] led_id_start : ��ʼled id��
// *
// * \param[in] num          : led����
// */
//void demo_std_led_water_light_entry (int led_id_start, int num);
//
///**
// * \brief  hc595_led ����
// *
// * \param[in] ��
// */
// void demo_std_4key_entry (void);
//
///**
// * \brief  hc595_led ����
// *
// * \param[in] hc595_handle  : ��׼hc595���
// */
// void demo_std_hc595_led_entry (am_hc595_handle_t hc595_handle);
///**
// * \brief  digitron_temp ����
// *
// * \param[in] temp_handle  : ��׼temp_handle���
// *
// * \param[in] id        : id��
// */
//void demo_std_digitron_temp_entry (int32_t id, am_temp_handle_t temp_handle);
///**
// * \brief  key_digitron ����
// *
// * \param[in] id     : id��
// */
//void demo_std_key_digitron_entry (int32_t id);
//
///**
// * \brief  digitron ����
// *
// * \param[in] id     : id��
// */
//void demo_std_digitron_60s_counting_entry (int32_t id);
//
///**
// * \brief  mtd ����
// *
// * \param[in] rtc_handle     : rtc ���
// */
//void demo_std_rtc_entry (am_rtc_handle_t rtc_handle);
//
///**
// * \brief  mtd ����
// *
// * \param[in] mtd_handle     : mtd ���
// *
// * \param[in] test_lenth     : ���Գ���
// */
//void demo_mtd_entry (am_mtd_handle_t mtd_handle, int32_t test_lenth);
//
///**
// * \brief  ftl ����
// *
// * \param[in] ftl_handle     : ftl ���
// *
// * \param[in] test_lenth     : ���Գ���
// */
//void demo_ftl_entry (am_ftl_handle_t ftl_handle, int32_t test_lenth);
//
///**
// * \brief ep24cxx����
// *
// * \param[in] mx25xx_handle    :    mx25xx���
// *
// * \param[in] test_lenth       :   ���Գ���
// */
//void demo_mx25xx_entry (am_mx25xx_handle_t mx25xx_handle,
//                        int32_t test_lenth);
///**
// * \brief ep24cxx����
// *
// * \param[in] ep24cxx_handle    :   ep24cxx���
// *
// * \param[in] test_lenth        :   ���Գ���
// */
//void demo_ep24cxx_entry (am_ep24cxx_handle_t ep24cxx_handle,
//                         int32_t test_lenth);
//
///**
// * \brief timer��ʱ��
// *
// * \param[in] am_timer_handle_t  : timer���
// *
// * \param[in] timing_chan        : ͨ��
// */
//void demo_std_timer_timing_entry (am_timer_handle_t handle,
//                                  int               timing_chan);
//
///**
// * \brief MiniPort-ZLG72128 ʵ����ʼ��
// *
// * \param ��
// *
// * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
// */
//int am_miniport_zlg72128_inst_init (void);
//
///**
// * \brief ʵ����ʼ������
// *
// * \param ��
// *
// * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
// */
//int am_key_gpio_inst_init (void);
//
/**
 * \brief �ж�ʵ����ʼ������ʼ���ж�����
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32f460_nvic_inst_init (void);

/**
 * \brief �ж�ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_hc32f460_nvic_inst_deinit (void);

/**
 * \brief ���Դ���ʵ����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
am_uart_handle_t am_debug_uart_inst_init (void);
/**
 * \brief ADC1 ʵ����ʼ������� ADC ��׼������
 *
 * \param ��
 *
 * \return ADC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_adc_handle_t am_hc32f460_adc1_inst_init (void);

/**
 * \brief ADC1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_zlg118_adc1_inst_init() ������õ� ADC ��׼������
 *
 * \return ��
 */
void am_hc32f460_adc1_inst_deinit (am_adc_handle_t handle);

/**
 * \brief ADC1 ʵ����ʼ������� ADC ��׼������
 *
 * \param ��
 *
 * \return ADC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_adc_handle_t am_hc32f460_adc2_inst_init (void);

/**
 * \brief ADC1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_zlg118_adc1_inst_init() ������õ� ADC ��׼������
 *
 * \return ��
 */
void am_hc32f460_adc2_inst_deinit (am_adc_handle_t handle);

/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32f460_clk_inst_init (void);

/**
 * \brief adtim61 capʵ����ʼ��
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_adtim61_cap_inst_init (void);

/**
 * \brief adtim61 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_adtim61_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_adtim61_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief adtim62 capʵ����ʼ��
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_adtim62_cap_inst_init (void);

/**
 * \brief adtim62 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_adtim62_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_adtim62_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief adtim63 capʵ����ʼ��
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_adtim63_cap_inst_init (void);

/**
 * \brief adtim61 CAP ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_adtim63_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_adtim63_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief adtim6 pwm ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_adtim61_pwm_inst_init (void);

/**
 * \brief adtim6 pwm ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_adtim61_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_adtim61_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief adtim6 pwm ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_adtim62_pwm_inst_init (void);

/**
 * \brief adtim6 pwm ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_adtim62_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_adtim62_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief adtim6 pwm ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_adtim63_pwm_inst_init (void);

/**
 * \brief adtim6 pwm ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_adtim63_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_adtim63_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief ��ʱ��ADTIM6 Timingʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim61_timing_inst_init (void);

/**
 * \brief ADTIM6 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim61_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim61_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��ADTIM6 Timingʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim62_timing_inst_init (void);

/**
 * \brief ADTIM6 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim62_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim62_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��ADTIM6 Timingʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim63_timing_inst_init (void);

/**
 * \brief ADTIM6 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim63_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim63_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief AES ʵ����ʼ������� aes ��׼������
 *
 * \param ��
 *
 * \return aes ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_aes_handle_t am_hc32f460_aes_inst_init (void);

/**
 * \brief AES ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_aes_inst_init() ����
 *                   ��õ� aes ��׼������
 *
 * \return ��
 */
void am_hc32f460_aes_inst_deinit (am_aes_handle_t handle);

/**
 * \brief CAN ʵ����ʼ������� can ��׼������
 *
 * \param ��
 *
 * \return can ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_can_handle_t am_hc32f460_can_inst_init (void);

/**
 * \brief CAN ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_can_inst_init() ����
 *                   ��õ�can ��׼������
 *
 * \return ��
 */
void am_hc32f460_can_inst_deinit (am_can_handle_t handle);

/**
 * \brief DMA ʵ����ʼ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32f460_dma1_inst_init (void);

/**
 * \brief DMA ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_hc32f460_dma1_inst_deinit (void);

/**
 * \brief DMA ʵ����ʼ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32f460_dma2_inst_init (void);

/**
 * \brief DMA ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_hc32f460_dma2_inst_deinit (void);

/**
 * \brief GPIO ʵ����ʼ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32f460_gpio_inst_init (void);

/**
 * \brief GPIO ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_hc32f460_gpio_inst_deinit (void);

/**
 * \brief HASH ʵ����ʼ��
 *
 * \param ��
 *
 * \return HASH ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_hash_handle_t am_hc32f460_hash_inst_init (void);

/**
 * \brief HASH ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_hash_inst_init() ������õ� HASH ��׼������
 *
 * \return ��
 */
void am_hc32f460_hash_inst_deinit (am_hash_handle_t handle);


/**
 * \brief I2C1 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_hc32f460_i2c1_inst_init (void);

/**
 * \brief I2C1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_i2c1_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_hc32f460_i2c_inst1_deinit (am_i2c_handle_t handle);


/**
 * \brief I2C2 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_hc32f460_i2c2_inst_init (void);

/**
 * \brief I2C2 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_i2c2_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_hc32f460_i2c_inst2_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C1�ӻ� ʵ����ʼ�������I2C��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_slv_handle_t  am_hc32f460_i2c1_slv_inst_init (void);

/**
 * \brief I2C1�ӻ� ʵ����ʼ�������I2C��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
void am_hc32f460_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle);

/**
 * \brief led gpio ʵ����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_i2c2_inst_init() ������õ� I2C ��׼������
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_hc32f460_led_gpio_inst_init (void);

/**
 * \brief QSPI ʵ����ʼ������� qspi ��׼������
 *
 * \param ��
 *
 * \return QSPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_qspi_handle_t am_hc32f460_qspi_inst_init(void);

/**
 * \brief QSPI ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_qspi_inst_init() ������õ� QSPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_qspi_inst_deinit(am_qspi_handle_t handle);

/**
 * \brief RTC ʵ����ʼ������� RTC ��׼������
 *
 * \param ��
 *
 * \return RTC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_hc32f460_rtc_inst_init (void);

/**
 * \brief RTC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_rtc_inst_init() ������õ� RTC ��׼������
 *
 * \return ��
 */
void am_hc32f460_rtc_inst_deinit (am_rtc_handle_t handle);

/**
 * \brief SDCARD1 ʵ����ʼ������� SDCARD ��׼������
 *
 * \param ��
 *
 * \return SDCARD ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_sdcard_handle_t am_sdcard1_inst_init (void);

/**
 * \brief SDIOC ʵ����ʼ������� SDIOC ��׼������
 *
 * \param ��
 *
 * \return SDIOC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_sdio_handle_t am_hc32f460_sdioc1_inst_init (void);

/**
 * \brief SDIOC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_sdioc1_inst_init() ������õ� SDIOC ��׼������
 *
 * \return ��
 */
void am_hc32f460_sdioc1_inst_deinit (am_sdio_handle_t handle);

/**
 * \brief SDIOC ʵ����ʼ������� SDIOC ��׼������
 *
 * \param ��
 *
 * \return SDIOC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_sdio_handle_t am_hc32f460_sdioc2_inst_init (void);

/**
 * \brief SDIOC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_sdioc2_inst_init() ������õ� SDIOC ��׼������
 *
 * \return ��
 */
void am_hc32f460_sdioc2_inst_deinit (am_sdio_handle_t handle);

/**
 * \brief SPI1 DMA ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi1_dma_inst_init (void);

/**
 * \brief SPI1 DMA ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi1_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi1_dma_inst_deinit (am_spi_handle_t handle);


/**
 * \brief SPI2 DMA ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi2_dma_inst_init (void);

/**
 * \brief SPI2 DMA ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi2_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi2_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI3 DMA ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi3_dma_inst_init (void);

/**
 * \brief SPI3 DMA ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi3_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi3_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI4 DMA ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi4_dma_inst_init (void);

/**
 * \brief SPI4 DMA ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi4_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi4_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 INT ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi1_int_inst_init (void);

/**
 * \brief SPI1 INT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi1_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hcc32f460_spi1_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI2 INT ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi2_int_inst_init (void);

/**
 * \brief SPI2 INT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi2_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hcc32f460_spi2_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI3 INT ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi3_int_inst_init (void);

/**
 * \brief SPI3 INT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi3_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hcc32f460_spi3_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI4 INT ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi4_int_inst_init (void);

/**
 * \brief SPI4 INT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi4_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hcc32f460_spi4_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 POLL ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi1_poll_inst_init (void);

/**
 * \brief SPI1 POLL ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi1_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi1_poll_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI2 POLL ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi2_poll_inst_init (void);

/**
 * \brief SPI2 POLL ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi2_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi2_poll_inst_deinit (am_spi_handle_t handle);


/**
 * \brief SPI3 POLL ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi3_poll_inst_init (void);

/**
 * \brief SPI3 POLL ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi3_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi3_poll_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI4 POLL ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_hc32f460_spi4_poll_inst_init (void);

/**
 * \brief SPI4 POLL ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi4_int_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi4_poll_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 SLV ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_slv_handle_t am_hc32f460_spi1_slv_dma_inst_init (void);

/**
 * \brief SPI1 SLV ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi1_slv_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi1_slv_dma_inst_deinit (am_spi_slv_handle_t handle);


/**
 * \brief SPI2 SLV ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_slv_handle_t am_hc32f460_spi2_slv_dma_inst_init (void);

/**
 * \brief SPI2 SLV ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi2_slv_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi2_slv_dma_inst_deinit (am_spi_slv_handle_t handle);

/**
 * \brief SPI3 SLV ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_slv_handle_t am_hc32f460_spi3_slv_dma_inst_init (void);

/**
 * \brief SPI3 SLV ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi3_slv_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi3_slv_dma_inst_deinit (am_spi_slv_handle_t handle);

/**
 * \brief SPI4 SLV ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_slv_handle_t am_hc32f460_spi4_slv_dma_inst_init (void);

/**
 * \brief SPI4 SLV ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_spi4_slv_dma_inst_init() ����
 *                   ��õ� SPI ��׼������
 *
 * \return ��
 */
void am_hc32f460_spi4_slv_dma_inst_deinit (am_spi_slv_handle_t handle);

/**
 * \brief SWDT ʵ����ʼ������� SWDT ��׼������
 *
 * \param ��
 *
 * \return SWDT ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_wdt_handle_t am_hc32f460_swdt_inst_init (void);

/**
 * \brief SWDT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_swdt_inst_init() ����
 *                   ��õ� SWDT ��׼������
 *
 * \return ��
 */
void am_hc32f460_swdt_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief SYSTICK ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_systick_inst_init (void);

/**
 * \brief SYSTICK ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_systick_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32f460_systick_inst_deinit (am_timer_handle_t handle);


/**
 * \brief ��ʱ��TIM0 Timingʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim01_timing_inst_init (void);

/**
 * \brief ��ʱ��TIM0 Timing ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim01_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim01_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��TIM0 Timingʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim02_timing_inst_init (void);

/**
 * \brief ��ʱ��TIM0 Timing ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim02_timing_inst_init() ����
 *                   ��õ� TIMER ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim02_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief tim41 pwm ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_tim41_pwm_inst_init (void);

/**
 * \brief tim41 pwm ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim41_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim41_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief tim42 pwm ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_tim42_pwm_inst_init (void);

/**
 * \brief tim41 pwm ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim42_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim42_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief tim43 pwm ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_tim43_pwm_inst_init (void);

/**
 * \brief tim43 pwm ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim43_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim43_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief ��ʱ��TIM4 Timing ʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim41_timing_inst_init (void);

/**
 * \brief TIM4 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim41_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim41_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��TIM4 Timing ʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim42_timing_inst_init (void);

/**
 * \brief TIM4 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim42_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim42_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��TIM4 Timing ʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_tim43_timing_inst_init (void);

/**
 * \brief TIM4 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_tim43_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_tim43_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief timea1 capʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_timea1_cap_inst_init (void);

/**
 * \brief timea1 capʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea1_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea1_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief timea2 capʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_timea2_cap_inst_init (void);

/**
 * \brief timea2 capʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea2_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea2_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief timea3 capʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_timea3_cap_inst_init (void);

/**
 * \brief timea3 capʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea3_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea3_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief timea4 capʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_timea4_cap_inst_init (void);

/**
 * \brief timea4 capʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea4_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea4_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief timea5 capʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_timea5_cap_inst_init (void);

/**
 * \brief timea5 capʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea5_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea5_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief timea6 capʵ����ʼ������� CAP ��׼������
 *
 * \param ��
 *
 * \return CAP ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_cap_handle_t am_hc32f460_timea6_cap_inst_init (void);

/**
 * \brief timea6 capʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea6_cap_inst_init() ����
 *                   ��õ� CAP ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea6_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief tima1 pwmʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_timea1_pwm_inst_init (void);

/**
 * \brief tima1 pwmʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea1_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea1_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief tima2 pwmʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_timea2_pwm_inst_init (void);

/**
 * \brief tima2 pwmʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea2_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea2_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief tima3 pwmʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_timea3_pwm_inst_init (void);

/**
 * \brief tima3 pwmʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea3_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea3_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief tima4 pwmʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_timea4_pwm_inst_init (void);

/**
 * \brief tima4 pwmʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea4_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea4_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief tima5 pwmʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_timea5_pwm_inst_init (void);

/**
 * \brief tima5 pwmʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea5_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea5_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief tima6 pwmʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_hc32f460_timea6_pwm_inst_init (void);

/**
 * \brief tima6 pwmʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea6_pwm_inst_init() ����
 *                   ��õ� PWM ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea6_pwm_inst_deinit (am_pwm_handle_t handle);


/**
 * \brief ��ʱ��tima1 Timingʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_timea1_timing_inst_init (void);

/**
 * \brief tima1 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea1_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea1_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��tima2 Timingʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_timea2_timing_inst_init (void);

/**
 * \brief tima2 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea2_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea2_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��tima3 Timingʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_timea3_timing_inst_init (void);

/**
 * \brief tima3 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea3_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea3_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��tima4 Timingʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_timea4_timing_inst_init (void);

/**
 * \brief tima4 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea4_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea4_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��tima5 Timingʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_timea5_timing_inst_init (void);

/**
 * \brief tima5 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea5_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea5_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ��ʱ��tima6 Timingʵ����ʼ������� Timer ��׼������
 *
 * \param ��
 *
 * \return Timer ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_hc32f460_timea6_timing_inst_init (void);

/**
 * \brief tima6 Timingʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_timea6_timing_inst_init() ����
 *                   ��õ� Timer ��׼������
 *
 * \return ��
 */
void am_hc32f460_timea6_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TRNG ʵ����ʼ������� TRNG ��׼������
 *
 * \param ��
 *
 * \return TRNG ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_trng_handle_t am_hc32f460_trng_inst_init (void);

/**
 * \brief TRNG ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_trng_inst_init() ������õ� TRNG ��׼������
 *
 * \return ��
 */
void am_hc32f460_trng_inst_deinit (am_trng_handle_t handle);

/**
 * \brief WDT ʵ����ʼ������� WDT ��׼������
 *
 * \param ��
 *
 * \return WDT ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_wdt_handle_t am_hc32f460_wdt_inst_init (void);

/**
 * \brief WDT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_wdt_inst_init() ������õ� WDT ��׼������
 *
 * \return ��
 */
void am_hc32f460_wdt_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief ϵͳ�δ�ʵ����ʼ��(��ʹ�������ʱ��)
 *
 * \param[in] ��
 *
 * \return ��ʱ����׼����������
 */
am_timer_handle_t am_system_tick_inst_init (void);

/**
 * \brief ϵͳ�δ�ʵ����ʼ��(ʹ�������ʱ��)
 *
 * \param[in] ��
 *
 * \return ��ʱ����׼����������
 */
am_timer_handle_t am_system_tick_softimer_inst_init (void);


/**
 * \brief CRC ʵ����ʼ������� CRC ��׼������
 *
 * \param ��
 *
 * \return CRC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_crc_handle_t am_hc32f460_crc_inst_init (void);

/**
 * \brief CRC ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_crc_inst_init() ������õ� CRC ��׼������
 *
 * \return ��
 */
void am_hc32f460_crc_inst_deinit (am_crc_handle_t handle);
//

/**
 * \brief UART1 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32f460_uart1_inst_init (void);

/**
 * \brief UART1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_uart1_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32f460_uart1_inst_deinit (am_uart_handle_t handle);

/**
 * \brief UART2 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32f460_uart2_inst_init (void);

/**
 * \brief UART2 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_uart2_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32f460_uart2_inst_deinit (am_uart_handle_t handle);

/**
 * \brief UART3 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32f460_uart3_inst_init (void);

/**
 * \brief UART3 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_uart3_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32f460_uart3_inst_deinit (am_uart_handle_t handle);
/**
 * \brief UART4 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_hc32f460_uart4_inst_init (void);

/**
 * \brief UART4 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_uart4_inst_init() ������õ� UART ��׼������
 *
 * \return ��
 */
void am_hc32f460_uart4_inst_deinit (am_uart_handle_t handle);

/**
 * \brief usb_mscʵ����ʼ�������usb_msc��׼������
 *
 * \param ��
 *
 * \return usb_msc ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_usbd_msc_handle am_hc32f460_usb_msc_inst_init (void);

/**
 * \brief usb_msc���ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_usb_msc_inst_init() ������õ� usb_msc ��׼������
 *
 * \return ��
 */
void am_hc32f460_usb_msc_inst_deinit (void);

/**
 * \brief usb_mouseʵ����ʼ�������usb_mouse��׼������
 *
 * \param ��
 *
 * \return usb_mouse ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_usbd_dev_t am_hc32f460_usb_mouse_inst_init (void);

/**
 * \brief usb_mouse���ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_usb_mouse_inst_init() ������õ� usb_msc ��׼������
 *
 * \return ��
 */
void am_hc32f460_usb_mouse_inst_deinit (void);


/**
 * \brief usb hid customʵ����ʼ�������usb hid custom��׼������
 *
 * \param ��
 *
 * \return usb hid custom ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_usbd_dev_t am_hc32f460_usb_hid_custom_inst_init (void);

/**
 * \brief usb hid custom���ʼ��
 *
 * \param[in] handle ͨ�� am_hc32f460_usb__hid_custom_inst_init() ������õ� usb_msc ��׼������
 *
 * \return ��
 */
void am_hc32f460_usb_hid_custom_inst_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_HC32F460_INST_INIT_H */

/* end of file */
