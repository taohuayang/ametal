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
 * \brief ZLGϵ�������������������̺����������
 * \sa    demo_mm32_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __DEMO_MM32_ENTRIES_H
#define __DEMO_MM32_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"

#include "hw/amhw_mm32_adc.h"
#include "hw/amhw_mm32_exti.h"
#include "hw/amhw_mm32_flash.h"
#include "hw/amhw_mm32_gpio.h"
#include "hw/amhw_mm32_i2c.h"
#include "hw/amhw_mm32_pwr.h"
//#include "hw/amhw_mm32l073_rcc.h"
#include "hw/amhw_mm32_spi.h"
#include "hw/amhw_mm32_dma.h"
#include "hw/amhw_mm32_syscfg.h"
#include "hw/amhw_mm32_tim.h"
#include "hw/amhw_mm32_uart.h"
#include "hw/amhw_mm32_iwdg.h"
#include "hw/amhw_mm32_wwdg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] chan      : ���Ŷ�Ӧ�� ADC ͨ����
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_mm32_hw_adc_int_entry (amhw_mm32_adc_t *p_hw_adc,
                                int             int_num,
                                int             chan,
                                uint32_t        vref_mv);

/**
 * \brief ADC Ӳ���㣨DMA���������
 *
 */
void demo_mm32_hw_adc_dma_entry (amhw_mm32_adc_t *p_hw_adc,
                                int            *p_adc_chan,
                                int             adc_chan_num,
                                uint8_t         dma_chan);

/**
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_clk_id_buf ����ʱ�ӺŵĻ�����
 * \param[in] buf_lenth    ʱ�ӺŻ�������С
 *
 * \return ��
 */
void demo_mm32_hw_clk_entry (am_clk_id_t *p_clk_id_buf, uint8_t buf_lenth);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_mm32_drv_dma_m2m_entry (uint32_t dma_chan);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_mm32_drv_flash_entry (amhw_mm32_flash_t *p_hw_flash, uint8_t sector);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO ����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \return ��
 */
void demo_mm32_hw_gpio_entry (amhw_mm32_gpio_t *p_hw_gpio,
                             int32_t          input_pin,
                             int32_t          output_pin);

/**
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio     ָ�� GPIO ����Ĵ������ָ��
 * \param[in] p_hw_syscfg   ָ�� SYSCFG ����Ĵ������ָ��
 * \param[in] p_hw_exti     ָ�� EXTI ����Ĵ������ָ��
 * \param[in] pin           �ж����ź�
 * \param[in] portsource    �ж����Ŷ˿�
 * \param[in] pinsource     �ж�����Դ
 * \param[in] exti_line_num �ⲿ�ж��ߺ�
 *
 * \return ��
 */
void demo_mm32_hw_gpio_trigger_entry (amhw_mm32_gpio_t         *p_hw_gpio,
                                     amhw_mm32_syscfg_t       *p_hw_syscfg,
                                     amhw_mm32_exti_t         *p_hw_exti,
                                     int32_t                  pin,
                                     uint8_t                  portsource,
                                     uint8_t                  pinsource,
                                     amhw_mm32_exti_line_num_t exti_line_num);

/**
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] clk_rate I2C ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_mm32_hw_i2c_master_poll_entry (amhw_mm32_i2c_t *p_hw_i2c,
                                        uint32_t        clk_rate);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_mm32_hw_i2c_slave_poll_entry (amhw_mm32_i2c_t *p_hw_i2c);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_spi ָ�� SPI ����Ĵ������ָ��
 * \param[in] cs_pin   Ƭѡ���ź�
 * \param[in] clk_rate SPI ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_mm32_hw_spi_master_entry (amhw_mm32_spi_t *p_hw_spi,
                                   int32_t         cs_pin,
                                   uint32_t        clk_rate);

/**
 * \brief ��ʱ���������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] chan     ��ʱ��ͨ��
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] inum     �жϺ�
 *
 * \return ��
 */
void demo_mm32_hw_tim_cap_entry (amhw_mm32_tim_t      *p_hw_tim,
                                amhw_mm32_tim_type_t  type,
                                uint32_t             chan,
                                uint32_t             clk_rate,
                                int32_t              inum);

/**
 * \brief ��ʱ��ͨ���Ƚ�ƥ�����ŷ�ת���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] chan     ��ʱ��ͨ��
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] inum     �жϺ�
 *
 * \return ��
 */
void demo_mm32_hw_tim_cmp_toggle_entry (amhw_mm32_tim_t      *p_hw_tim,
                                       amhw_mm32_tim_type_t  type,
                                       uint32_t             chan,
                                       uint32_t             clk_rate,
                                       uint8_t              inum);

/**
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] chan     ��ʱ��ͨ��
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] inum     �жϺ�
 *
 * \return ��
 */
void demo_mm32_hw_tim_pwm_entry (amhw_mm32_tim_t     *p_hw_tim,
                                amhw_mm32_tim_type_t type,
                                uint32_t            chan,
                                uint32_t            clk_rate,
                                int32_t             inum);

/**
 * \brief ��ʱ��������ʱ��Ļ��� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] chan     ��ʱ��ͨ��
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_mm32_hw_tim_pwm_dead_entry (amhw_mm32_tim_t     *p_hw_tim,
                                     amhw_mm32_tim_type_t type,
                                     uint32_t            chan,
                                     uint32_t            clk_rate);

/**
 * \brief ��ʱ����ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] inum     �жϺ�
 *
 * \return ��
 */
void demo_mm32_hw_tim_timing_entry (amhw_mm32_tim_t     *p_hw_tim,
                                   amhw_mm32_tim_type_t type,
                                   uint32_t            clk_rate,
                                   int32_t             int_num);

/**
 * \brief UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� UART ���ų�ʼ��������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] uart_base UART ����ַ
 * \param[in] inum_uart UART �жϺ�
 *
 * \return ��
 */
void demo_mm32_hw_uart_int_entry (amhw_mm32_uart_t *p_hw_uart,
                                 void (* pfn_init)(void),
                                 uint32_t         clk_rate,
                                 unsigned long    uart_base,
                                 unsigned char    inum_uart);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_mm32_hw_uart_polling_entry (amhw_mm32_uart_t *p_hw_uart,
                                     uint32_t         clk_rate);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 *
 * \return ��
 */
void demo_mm32_hw_uart_rx_dma_entry (amhw_mm32_uart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 *
 * \return ��
 */
void demo_mm32_hw_uart_tx_dma_entry (amhw_mm32_uart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan);
                                    
/**
 * \brief ˯��ģʽ���̣�ʹ�ö�ʱ�����ڻ��ѣ�ͨ��������ӿ�ʵ��
 *
 * \param[in] timer_handle   ��ʱ����׼������
 * \param[in] timer_clk_rate ��ϵͳʱ���л�Ϊ LSI ʱ����ʱ����ʱ��Ƶ��
 *
 * \return ��
 */
void demo_mm32l073_drv_sleepmode_timer_wake_up_entry (am_timer_handle_t timer_handle,
                                                    uint32_t          timer_clk_rate);

/**
 * \brief ˯��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_mm32l073_drv_sleepmode_wake_up_entry (void);

/**
 * \brief ����ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_mm32l073_drv_standbymode_wake_up_entry (void);

/**
 * \brief ͣ��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_mm32l073_drv_stopmode_wake_up_entry (void);

/**
 * \brief IWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_iwdg    ָ�� IWDG ����Ĵ������ָ��
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \return ��
 */
void demo_mm32_hw_iwdg_entry (amhw_mm32_iwdg_t *p_hw_iwdg,
                             uint32_t         time_out_ms,
                             uint32_t         feed_time_ms);

/**
 * \brief WWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_wwdg    ָ�� WWDG ����Ĵ������ָ��
 * \param[in] clk_rate     WWDG ʱ��ԴƵ��
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \return ��
 */
void demo_mm32_hw_wwdg_entry (amhw_mm32_wwdg_t *p_hw_wwdg,
                             uint32_t         clk_rate,
                             uint32_t         time_out_ms,
                             uint32_t         feed_time_ms);


/**
 * \brief ZML166 ADC pt100��������
 * \param[in] handle      ZML166 ADC ������
 * \param[in] p_para      PT100����У׼����
 * \return ��
 */
void demo_zml166_adc_pt100_measure_entry(void                   *p_handle,
                                         float                  *p_para);


/**
 * \brief ZML166 ADC �����̶���ѹ����
 * \param[in] handle      ZML166 ADC ������
 * \param[in] p_para      flash ��ѹУ׼����
 * \param[in] gpa_index   ZML166 ADC���汶������
 * \return ��
 */
void dome_zml166_adc_vol_measure_entry(void                   *p_handle,
                                       float                  *p_para,
                                       uint8_t                 gpa_index);

/**
 * \brief ZML166 ADC �ȵ�ż��������
 * \param[in] handle      ZML166 ADC ������
 * \param[in] p_para      У׼����
 * \param[in] type        �ȵ�ż����
 * \return ��
 */
void dome_zml166_adc_thermocouple_measure_entry(void              *p_handle,
                                                float             *p_para,
                                                uint8_t            type);

/**
 * \brief ZML166 ADC ��ѹУ׼����
 * \param[in] handle      ZML166 ADC ������
 * \param[in] uart_handle ���ھ��
 * \param[out] p_para      У׼�������
 * \return ��
 */
void demo_zml166_adc_vol_para_adjuet_entry(void                   *p_handle,
                                           am_uart_handle_t        uart_handle,
                                           float                  *p_para);
#ifdef __cplusplus
}
#endif

#endif /* __DEMO_MM32_ENTRIES_H */

/* end of file */
