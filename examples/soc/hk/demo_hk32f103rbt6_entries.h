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
 * \brief HK32F103ϵ�������������������̺����������
 * \sa    demo_hk32f103rbt6_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __DEMO_HK32F103RBT6_ENTRIES_H
#define __DEMO_HK32F103RBT6_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"
#include "am_can.h"
#include "hw/amhw_hk32f103rbt6_adc.h"
#include "hw/amhw_hk32f103rbt6_exti.h"
#include "hw/amhw_hk32f103rbt6_flash.h"
#include "hw/amhw_hk32f103rbt6_gpio.h"
#include "hw/amhw_hk32f103rbt6_i2c.h"
#include "hw/amhw_hk32f103rbt6_pwr.h"
#include "hw/amhw_hk32f103rbt6_spi.h"
#include "hw/amhw_hk32f103rbt6_dma.h"
#include "hw/amhw_hk32f103rbt6_syscfg.h"
#include "hw/amhw_hk32f103rbt6_tim.h"
#include "hw/amhw_hk32f103rbt6_usart.h"
#include "hw/amhw_hk32f103rbt6_iwdg.h"
#include "hw/amhw_hk32f103rbt6_wwdg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ�����ͨ���������
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
void demo_hk32f103rbt6_hw_adc_int_entry (amhw_hk32f103rbt6_adc_t *p_hw_adc,
                                int             int_num,
                                int             chan,
                                uint32_t        vref_mv);

/**
 * \brief ADC Ӳ���㣨DMA������ͨ���������
 *
 */
void demo_hk32f103rbt6_hw_adc_dma_entry (amhw_hk32f103rbt6_adc_t *p_hw_adc,
                                int            *p_adc_chan,
                                int             adc_chan_num,
                                uint8_t         dma_chan);

/**
 * \brief hk32f103rbt6 ADC Ӳ���㣨ʹ�����жϣ� ע��ͨ���������
 *
 * \param[in] p_hw_adc     : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num      : �жϺ�
 * \param[in] vref_mv      : �ο���ѹ��mv��
 * \param[in] p_adc_chan   : ָ��ADCͨ�������ָ��
 * \param[in] adc_chan_num : ADCͨ������
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_adc_injected_int_entry (void              *p_hw_adc,
                                            int                int_num,
                                            uint32_t           vref_mv,
                                            int               *p_adc_chan,
                                            int                adc_chan_num);

/**
 * \brief hk32f103rbt6 ADC Ӳ���㣨ʹ�����жϣ�����ͨ����ע��ͨ���������
 *
 * \param[in] p_hw_adc     : ָ�� ADC1����Ĵ������ָ��
 * \param[in] p_adc_chan   : ָ��ADC1ͨ�������ָ��
 * \param[in] adc_chan_num : ADC1ͨ������
 * \param[in] dma_chan     : DMAͨ��
 * \param[in] p_hw_adc     : ָ�� ADC2����Ĵ������ָ��
 * \param[in] p_adc_chan   : ָ��ADC2ͨ�������ָ��
 * \param[in] adc_chan_num : ADC2ͨ������
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_adc_dma_double_entry (void              *p_hw_adc1,
                                          int               *p_adc1_chan,
                                          int                adc1_chan_num,
                                          uint8_t            dma_chan,
                                          void              *p_hw_adc2,
                                          int               *p_adc2_chan,
                                          int                adc2_chan_num);

/**
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_clk_id_buf ����ʱ�ӺŵĻ�����
 * \param[in] buf_lenth    ʱ�ӺŻ�������С
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_clk_entry (am_clk_id_t *p_clk_id_buf, uint8_t buf_lenth);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_hk32f103rbt6_drv_dma_m2m_entry (uint32_t dma_chan);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_drv_flash_entry (amhw_hk32f103rbt6_flash_t *p_hw_flash, uint8_t sector);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO ����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_gpio_entry (amhw_hk32f103rbt6_gpio_t *p_hw_gpio,
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
void demo_hk32f103rbt6_hw_gpio_trigger_entry (amhw_hk32f103rbt6_gpio_t         *p_hw_gpio,
                                     amhw_hk32f103rbt6_syscfg_t       *p_hw_syscfg,
                                     amhw_hk32f103rbt6_exti_t         *p_hw_exti,
                                     int32_t                  pin,
                                     uint8_t                  portsource,
                                     uint8_t                  pinsource,
                                     amhw_hk32f103rbt6_exti_line_num_t exti_line_num);

/**
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] clk_rate I2C ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_i2c_master_poll_entry (amhw_hk32f103rbt6_i2c_t *p_hw_i2c,
                                        uint32_t        clk_rate);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_i2c_slave_poll_entry (amhw_hk32f103rbt6_i2c_t *p_hw_i2c);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_spi ָ�� SPI ����Ĵ������ָ��
 * \param[in] cs_pin   Ƭѡ���ź�
 * \param[in] clk_rate SPI ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_spi_master_entry (amhw_hk32f103rbt6_spi_t *p_hw_spi,
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
void demo_hk32f103rbt6_hw_tim_cap_entry (amhw_hk32f103rbt6_tim_t      *p_hw_tim,
                                amhw_hk32f103rbt6_tim_type_t  type,
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
void demo_hk32f103rbt6_hw_tim_cmp_toggle_entry (amhw_hk32f103rbt6_tim_t      *p_hw_tim,
                                       amhw_hk32f103rbt6_tim_type_t  type,
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
void demo_hk32f103rbt6_hw_tim_pwm_entry (amhw_hk32f103rbt6_tim_t     *p_hw_tim,
                                amhw_hk32f103rbt6_tim_type_t type,
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
void demo_hk32f103rbt6_hw_tim_pwm_dead_entry (amhw_hk32f103rbt6_tim_t     *p_hw_tim,
                                     amhw_hk32f103rbt6_tim_type_t type,
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
void demo_hk32f103rbt6_hw_tim_timing_entry (amhw_hk32f103rbt6_tim_t     *p_hw_tim,
                                   amhw_hk32f103rbt6_tim_type_t type,
                                   uint32_t            clk_rate,
                                   int32_t             int_num);

/**
 * \brief HK32F103 UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� UART ���ų�ʼ��������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] uart_base UART ����ַ
 * \param[in] inum_uart UART �жϺ�
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_uart_int_entry (amhw_hk32f103rbt6_usart_t *p_hw_uart,
                                 void (* pfn_init)(void),
                                 uint32_t         clk_rate,
                                 unsigned long    uart_base,
                                 unsigned char    inum_uart);

/**
 * \brief HK32F103 UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_uart_polling_entry (amhw_hk32f103rbt6_usart_t *p_hw_uart,
                                     uint32_t         clk_rate);

/**
 * \brief HK32F103 UART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_uart_rx_dma_entry (amhw_hk32f103rbt6_usart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan);

/**
 * \brief HK32F103 UART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_uart_tx_dma_entry (amhw_hk32f103rbt6_usart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan);

/**
 * \brief HK32F103RBT6 USART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� USART ���ų�ʼ��������ָ��
 * \param[in] clk_rate  USART ʱ��ԴƵ��
 * \param[in] uart_base USART ����ַ
 * \param[in] inum_uart USART �жϺ�
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_usart_int_entry (void                *p_hw_usart,
                                     void (* pfn_init)(void),
                                     uint32_t             clk_rate,
                                     unsigned long        usart_base,
                                     unsigned char        inum_usart);

/**
 * \brief HK32F103RBT6 USART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] clk_rate   USART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_usart_polling_entry (void                *p_hw_usart,
                                         uint32_t             clk_rate);

/**
 * \brief HK32F103RBT6 USART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] clk_rate   USART ʱ��ԴƵ��
 * \param[in] dma_chan   DMA ͨ����
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_usart_rx_dma_entry (void                *p_hw_usart,
                                        uint32_t             clk_rate,
                                        int32_t              dma_chan);

/**
 * \brief HK32F103RBT6 USART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] clk_rate   USART ʱ��ԴƵ��
 * \param[in] dma_chan   DMA ͨ����
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_usart_tx_dma_entry (void                *p_hw_usart,
                                        uint32_t             clk_rate,
                                        int32_t              dma_chan);

/**
 * \brief ˯��ģʽ���̣�ʹ�ö�ʱ�����ڻ��ѣ�ͨ��������ӿ�ʵ��
 *
 * \param[in] timer_handle   ��ʱ����׼������
 * \param[in] timer_clk_rate ��ϵͳʱ���л�Ϊ LSI ʱ����ʱ����ʱ��Ƶ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_drv_sleepmode_timer_wake_up_entry (am_timer_handle_t timer_handle,
                                                    uint32_t          timer_clk_rate);

/**
 * \brief ˯��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_drv_sleepmode_wake_up_entry (void);

/**
 * \brief ����ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_drv_standbymode_wake_up_entry (void);

/**
 * \brief ͣ��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_drv_stopmode_wake_up_entry (void);

/**
 * \brief IWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_iwdg    ָ�� IWDG ����Ĵ������ָ��
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \return ��
 */
void demo_hk32f103rbt6_hw_iwdg_entry (amhw_hk32f103rbt6_iwdg_t *p_hw_iwdg,
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
void demo_hk32f103rbt6_hw_wwdg_entry (amhw_hk32f103rbt6_wwdg_t *p_hw_wwdg,
                             uint32_t         clk_rate,
                             uint32_t         time_out_ms,
                             uint32_t         feed_time_ms);

/**
 * \brief CAN �ж��������
 *
 * \param[in] am_can_handle_t     can������
 * \param[in] am_can_bps_param_t  ָ�����ʲ����ṹ���ָ��
 * \param[in] am_can_int_type_t   �ж�ʹ������
 * \param[in] uint8_t             ָ�����table��ָ��
 * \param[in] size_t              ����table�ĳ���
 * \return ��
 */
void demo_hk32f103rbt6_can_int_entry (am_can_handle_t     can_handle,
                                am_can_bps_param_t *can_btr_baud,
                                am_can_int_type_t   int_type,
                                uint8_t            *p_filterbuff,
                                size_t              lenth);
/**
 * \brief �������
 */

/**
 * \brief CAN �������
 *
 * \param[in] am_can_handle_t     can������
 * \param[in] am_can_bps_param_t  ָ�����ʲ����ṹ���ָ��
 * \param[in] am_can_int_type_t   �ж�ʹ������
 *
 * \return ��
 */
void demo_hk32f103rbt6_can_entry (am_can_handle_t     can_handle,
                            am_can_bps_param_t *can_btr_baud);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_HK32F103RBT6_ENTRIES_H */

/* end of file */
