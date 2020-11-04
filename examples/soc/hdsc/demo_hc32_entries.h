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
 * \brief HC32ϵ�������������������̺����������
 * \sa    demo_hc32_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __DEMO_HC32_ENTRIES_H
#define __DEMO_HC32_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"
#include "am_can.h"

#include "hw/amhw_hc32_adc.h"
#include "hw/amhw_hc32_flash.h"
#include "hw/amhw_hc32_gpio.h"
#include "hw/amhw_hc32_i2c.h"
#include "hw/amhw_hc32_spi.h"
#include "hw/amhw_hc32_dma.h"
#include "hw/amhw_hc32_tim.h"
#include "hw/amhw_hc32_uart.h"
#include "hw/amhw_hc32_wdt.h"
#include "hw/amhw_hc32_lvd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] chan      : ���Ŷ�Ӧ�� ADCͨ����
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 *
 * \note  һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 *        ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \retval ��
 */
void demo_hc32_hw_adc_int_entry (void    *p_hw_adc,
                                 int      int_num,
                                 uint8_t  chan,
                                 uint32_t vref_mv);

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc   : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num    : �жϺ�
 * \param[in] vref_mv    : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 * \param[in] p_adc_chan : ADCͨ������ָ��
 * \param[in] sqr_num    : ����ͨ������
 * \param[in] jqr_num    : ����ͨ������
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 *       ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \retval ��
 */
void demo_hc32_hw_multichan_adc_entry (void    *p_hw_adc,
                                       int      int_num,
                                       uint32_t vref_mv,
                                       int     *p_adc_chan,
                                       uint8_t  sqr_num,
                                       uint8_t  jqr_num);

/**
 * \brief ADC Ӳ���㣨DMA���������
 *
 * \param[in] p_hw_adc   : ָ�� ADC ����Ĵ������ָ��
 * \param[in] p_adc_chan : ADCͨ������ָ��
 * \param[in] chan_num   : ADCͨ������
 * \param[in] vref_mv    : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 * \param[in] dma_chan   : DMAͨ����
 * \param[in] dma_src    : DMA���䴥��Դ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADCģ����Ӧ��ʱ�ӣ�
 *       ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \retval ��
 */
void demo_hc32_hw_adc_dma_entry (void    *p_hw_adc,
                                 int     *p_adc_chan,
                                 int      chan_num,
                                 uint32_t vref_mv,
                                 int      dma_chan,
                                 uint8_t  dma_src);

/**
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_clk_id_buf ����ʱ�ӺŵĻ�����
 * \param[in] buf_lenth    ʱ�ӺŻ�������С
 *
 * \retval ��
 */
void demo_hc32_hw_clk_entry (am_clk_id_t *p_clk_id_buf, uint8_t buf_lenth);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan  DMA ͨ����
 *
 * \retval ��
 */
void demo_hc32_drv_dma_m2m_entry (uint32_t dma_chan);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 * \param[in] sector     ʹ�� FLASH ������
 *
 * \retval ��
 */
void demo_hc32_drv_flash_entry (void *p_hw_flash, uint16_t sector);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \retval ��
 */
void demo_hc32_hw_gpio_entry (void    *p_hw_gpio,
                              int32_t  input_pin,
                              int32_t  output_pin);

/**
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio     ָ�� GPIO ����Ĵ������ָ��
 * \param[in] pin           �ж����ź�
 *
 * \retval ��
 */
void demo_hc32_hw_gpio_trigger_entry (void *p_hw_gpio, int32_t pin);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_spi ָ�� SPI ����Ĵ������ָ��
 * \param[in] cs_pin   Ƭѡ���ź�
 *
 * \retval ��
 */
void demo_hc32_hw_spi_master_entry (void    *p_hw_spi,
                                    int32_t  cs_pin);

/**
 * \brief ��ʱ���������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] chan     ��ʱ��ͨ��
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] inum     �жϺ�
 *
 * \retval ��
 */
void demo_hc32_hw_tim_cap_entry (void     *p_hw_tim,
                                 uint32_t  chan,
                                 uint32_t  clk_rate,
                                 int32_t   inum);

/**
 * \brief ��ʱ��ͨ���Ƚ�ƥ�����ŷ�ת���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] chan     ��ʱ��ͨ��
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] clk_div  ��ʱ��ʱ��Դ��Ƶϵ��
 * \param[in] inum     �жϺ�
 *
 * \retval ��
 */
void demo_hc32_hw_tim_cmp_toggle_entry (void    *p_hw_tim,
                                        uint8_t  type,
                                        uint32_t chan,
                                        uint32_t clk_rate,
                                        uint8_t  clk_div,
                                        uint8_t  inum);

/**
 * \brief ��ʱ��ͨ���������Ļ���PWM������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim  ָ��ʱ������Ĵ������ָ��
 * \param[in] type      ��ʱ������
 * \param[in] chan_a    ��ʱ������PWMͨ��A
 * \param[in] chan_b    ��ʱ������PWMͨ��B
 * \param[in] duty_us   ����ʱ�䣨us��
 * \param[in] period_us ����ʱ�䣨us��
 * \param[in] dead_us   ����ʱ�����ã�us��
 *
 * \retval ��
 */
void demo_hc32_hw_tim_pwm_dead_entry (void    *p_hw_tim,
                                      uint8_t  type,
                                      uint8_t  chan_a,
                                      uint8_t  chan_b,
                                      uint32_t duty_us,
                                      uint32_t period_us,
                                      uint16_t dead_us);

/**
 * \brief �߼���ʱ��������ͬ����ʼ��ͬ��ֹͣ��ͬ���������̣�ͨ�� HW��ӿ�ʵ��
 *
 * \param[in] p_tim_cfg ָ�����ͬ�����ýṹ���ָ�루amhw_hc32_adtim_sw_sync_t��
 *
 * \retval ��
 */
void demo_hc32_hw_adtim_swsync_entry (void *p_tim_cfg);

/**
 * \brief �߼���ʱ���˿ڡ����ɲ�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adtim ָ��ʱ������Ĵ������ָ��
 * \param[in] chan       ��ʱ��ͨ��
 * \param[in] duty_ns    ����ʱ��
 * \param[in] period_ns  ����ʱ��
 * \param[in] output_pin �������
 * \param[in] src        ADT�˿ڴ������� - ����Դѡ��
 *
 * \retval ��
 */
void demo_hc32_hw_adtim_port_sw_brake_entry (void          *p_hw_adtim,
                                             uint8_t        chan,
                                             unsigned long  duty_ns,
                                             unsigned long  period_ns,
                                             int            output_pin,
                                             uint8_t        src);

/**
 * \brief �߼���ʱ��VCɲ�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adtim ָ��ʱ������Ĵ������ָ��
 * \param[in] chan       ��ʱ��ͨ��
 * \param[in] duty_ns    ����ʱ��
 * \param[in] period_ns  ����ʱ��
 * \param[in] p_hw_vc    ָ��VC����Ĵ������ָ��
 * \param[in] vc0_n      VC0 ��ѹ�Ƚ��� ��-��������ѡ��
 * \param[in] vc0_p      VC0 ��ѹ�Ƚ��� ��+��������ѡ��
 *
 * \retval ��
 */
void demo_hc32_hw_adtim_vc_brake_entry (void         *p_hw_adtim,
                                        uint8_t       chan,
                                        unsigned long duty_ns,
                                        unsigned long period_ns,
                                        void         *p_hw_vc,
                                        uint8_t       vc0_n,
                                        uint8_t       vc0_p);

/**
 * \brief �߼���ʱ����ʱ����ADCת�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adtim  ָ��ʱ������Ĵ������ָ��
 * \param[in] period_us   ����ʱ��
 * \param[in] p_hw_adc    ָ��ADC����Ĵ������ָ��
 * \param[in] adc_int_num ADC�жϺ�
 * \param[in] p_adc_chan  ADCͨ���������
 * \param[in] sqr_num     ADC˳��ͨ������
 *
 * \retval ��
 */
void demo_hc32_hw_adtim_trig_adc_sqr_entry (void    *p_hw_adtim,
                                            uint32_t period_us,
                                            void    *p_hw_adc,
                                            int      adc_int_num,
                                            int     *p_adc_chan,
                                            uint8_t  sqr_num);

/**
 * \brief ͨ�ö�ʱ���˿�ɲ�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim   ָ��ʱ������Ĵ������ָ��
 * \param[in] type       ��ʱ������
 * \param[in] chan       ��ʱ��ͨ��
 * \param[in] inum       ��ʱ���жϺ�
 * \param[in] duty_ns    ����ʱ��
 * \param[in] period_ns  ����ʱ��
 *
 * \retval ��
 */
void demo_hc32_hw_tim_port_brake_entry (void    *p_hw_tim,
                                        uint8_t  type,
                                        uint8_t  chan,
                                        int      inum,
                                        uint32_t duty_ns,
                                        uint32_t period_ns);

/**
 * \brief ͨ�ö�ʱ��VCɲ�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adtim ָ��ʱ������Ĵ������ָ��
 * \param[in] chan       ��ʱ��ͨ��
 * \param[in] duty_ns    ����ʱ��
 * \param[in] period_ns  ����ʱ��
 * \param[in] p_hw_vc    ָ��VC����Ĵ������ָ��
 * \param[in] vc0_n      VC0 ��ѹ�Ƚ��� ��-��������ѡ��
 * \param[in] vc0_p      VC0 ��ѹ�Ƚ��� ��+��������ѡ��
 *
 * \retval ��
 */
void demo_hc32_hw_tim_vc_brake_entry (void         *p_hw_tim,
                                      uint8_t       chan,
                                      unsigned long duty_ns,
                                      unsigned long period_ns,
                                      void         *p_hw_vc,
                                      uint8_t       vc0_n,
                                      uint8_t       vc0_p);

/**
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] chan     ��ʱ��ͨ��
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] clk_div  ��ʱ��ʱ��Դ��Ƶϵ��
 * \param[in] inum     �жϺ�
 *
 * \retval ��
 */
void demo_hc32_hw_tim_pwm_entry (void    *p_hw_tim,
                                 uint8_t  type,
                                 uint32_t chan,
                                 uint32_t clk_rate,
                                 uint8_t  clk_div,
                                 int32_t  inum);

/**
 * \brief ��ʱ����ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim ָ��ʱ������Ĵ������ָ��
 * \param[in] type     ��ʱ������
 * \param[in] clk_rate ��ʱ��ʱ��ԴƵ��
 * \param[in] int_num  �жϺ�
 *
 * \retval ��
 */
void demo_hc32_hw_tim_timing_entry (void    *p_hw_tim,
                                    uint8_t  type,
                                    uint32_t clk_rate,
                                    int32_t  int_num);

/**
 * \brief ͨ�ö�ʱ����ʱ����ADCת�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim    ָ��ʱ������Ĵ������ָ��
 * \param[in] type        ��ʱ������
 * \param[in] chan        ��ʱ��ͨ��
 * \param[in] duty_us     ����ʱ��
 * \param[in] period_us   ����ʱ��
 * \param[in] p_hw_adc    ָ��ADC����Ĵ������ָ��
 * \param[in] adc_int_num ADC�жϺ�
 * \param[in] p_adc_chan  ADCͨ���������
 * \param[in] sqr_num     ADC˳��ͨ������
 *
 * \retval ��
 */
void demo_hc32_hw_tim_trig_adc_sqr_entry (void    *p_hw_tim,
                                          uint8_t  type,
                                          uint8_t  chan,
                                          uint32_t duty_us,
                                          uint32_t period_us,
                                          void    *p_hw_adc,
                                          int      adc_int_num,
                                          int     *p_adc_chan,
                                          uint8_t  sqr_num);

/**
 * \brief UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� UART ���ų�ʼ��������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] uart_base UART ����ַ
 * \param[in] inum_uart UART �жϺ�
 *
 * \retval ��
 */
void demo_hc32_hw_uart_int_entry (void             *p_hw_uart,
                                  void            (*pfn_init) (void),
                                  uint32_t          clk_rate,
                                  unsigned long     uart_base,
                                  unsigned char     inum_uart);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \retval ��
 */
void demo_hc32_hw_uart_polling_entry (void     *p_hw_uart,
                                      uint32_t  clk_rate);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 * \param[in] dma_src   DMA ����Դѡ��
 *
 * \retval ��
 */
void demo_hc32_hw_uart_rx_dma_entry (void    *p_hw_uart,
                                     uint32_t clk_rate,
                                     int32_t  dma_chan,
                                     int32_t  dma_src);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 * \param[in] dma_src   DMA ����Դѡ��
 *
 * \retval ��
 */
void demo_hc32_hw_uart_tx_dma_entry (void    *p_hw_uart,
                                     uint32_t clk_rate,
                                     int32_t  dma_chan,
                                     int32_t  dma_src);

/**
 * \brief LPUART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_lpuart   ָ��LPUART ����Ĵ������ָ��
 * \param[in] pfn_init      ָ�� LPUART ���ų�ʼ��������ָ��
 * \param[in] sclk_src      LPUART ʱ��Դѡ��
 * \param[in] clk_rate      LPUART ʱ��ԴƵ��
 * \param[in] baudrate      LPUART ������
 * \param[in] inum_lpuart   LPUART �жϺ�
 *
 * \retval ��
 */
void demo_hc32_hw_lpuart_int_entry (void             *p_hw_lpuart,
                                    void            (*pfn_init) (void),
                                    uint8_t           sclk_src,
                                    uint32_t          clk_rate,
                                    uint32_t          baudrate,
                                    unsigned char     inum_lpuart);

/**
 * \brief LPUART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_lpuart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] clk_src     LPUART ʱ��Դѡ��
 * \param[in] clk_rate    LPUART ʱ��ԴƵ��
 * \param[in] baudrate    LPUART ������
 *
 * \retval ��
 */
void demo_hc32_hw_lpuart_polling_entry (void     *p_hw_lpuart,
                                        uint8_t   clk_src,
                                        uint32_t  clk_rate,
                                        uint32_t  baudrate);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_lpuart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] clk_src     LPUART ʱ��Դѡ��
 * \param[in] clk_rate    LPUART ʱ��ԴƵ��
 * \param[in] baudrate    LPUART ������
 * \param[in] dma_chan    DMA ͨ����
 * \param[in] dma_src     DMA ����Դѡ��
 *
 * \retval ��
 */
void demo_hc32_hw_lpuart_rx_dma_entry (void    *p_hw_lpuart,
                                       uint8_t  clk_src,
                                       uint32_t clk_rate,
                                       uint32_t baudrate,
                                       int32_t  dma_chan,
                                       int32_t  dma_src);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_lpuart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] clk_src     LPUART ʱ��Դѡ��
 * \param[in] clk_rate    LPUART ʱ��ԴƵ��
 * \param[in] baudrate    LPUART ������
 * \param[in] dma_chan    DMA ͨ����
 * \param[in] dma_src     DMA ����Դѡ��
 *
 * \retval ��
 */
void demo_hc32_hw_lpuart_tx_dma_entry (void    *p_hw_lpuart,
                                       uint8_t  clk_src,
                                       uint32_t clk_rate,
                                       uint32_t baudrate,
                                       int32_t  dma_chan,
                                       int32_t  dma_src);

/**
 * \brief HC32 I2C �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c     ָ�� I2C ����Ĵ������ָ��
 * \param[in] clk_rate     I2c����Ƶ��
 *
 * \return ��
 */
void demo_hc32_hw_i2c_master_poll_entry (void      *p_hw_i2c,
                                         uint32_t   clk_rate);

/**
 * \brief HC32 I2C �ӻ����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c     ָ�� I2C ����Ĵ������ָ��
 * \param[in] inum_num     I2c�жϺ�
 *
 * \return ��
 */
void demo_hc32_hw_i2c_slave_int_entry (void    *p_hw_i2c,
                                       int      inum_num);

/**
 * \brief HC32 WDT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_wdt     ָ�� WDT ����Ĵ������ָ��
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \retval ��
 */
void demo_hc32_hw_wdt_entry (void     *p_hw_wdt,
                             uint32_t  time_out_ms,
                             uint32_t  feed_time_ms);

/**
 * \brief DAC�����ѹ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_dac  ָ��DAC�Ĵ���ָ��
 * \param[in] dma_src   DMA����Դ
 * \param[in] dma_chan  DMAͨ��
 * \param[in] p_vol_val ��ѹֵ
 *
 * \retval ��
 */
void demo_hc32_hw_dac_dma_entry(void     *p_hw_dac,
                                int32_t   dma_src,
                                int32_t   dma_chan,
                                uint16_t *p_vol_val);

/**
 * \brief VC�жϴ������̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_vc   ָ��VC�Ĵ���ָ��
 * \param[in] pfn_cb_t  �жϴ����ص�����
 * \param[in] p_arg     �жϴ����ص���������
 * \param[in] p_hw_dac  ָ��ADC�Ĵ���ָ��
 * \param[in] mv_val    DAC �����ѹ
 *
 */
void demo_hc32_hw_vc_int_entry (void      *p_hw_vc,
                                void     (*pfn_cb_t) (void *),
                                void      *p_arg,
                                void      *p_hw_dac,
                                uint16_t   mv_val);

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ���ָ��
 * \param[in] lvd_vids : LVD ��ֵ��ѹ��amhw_hc32_lvd_vids_t
 * \param[in] lvd_src  : LVD �����Դѡ�񣬺궨�� AMHW_HC32_LVD_SRC_
 *
 * \retval ��
 */
void demo_hc32_hw_lvd_system_reset_entry (amhw_hc32_lvd_t     *p_hw_base,
                                          amhw_hc32_lvd_vids_t lvd_vids,
                                          uint32_t             lvd_src);

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_lvd   : ָ��LVD�Ĵ���ָ��
 * \param[in] lvd_vids   : LVD ��ֵ��ѹ��amhw_hc32_lvd_vids_t
 * \param[in] lvd_src    : LVD �����Դѡ�񣬺궨�� AMHW_HC32_LVD_SRC_
 * \param[in] pfn_lvd_cb : �û��ص�����
 * \param[in] p_arg      : �û��ص���������
 *
 * \retval ��
 */
void demo_hc32_hw_lvd_int_entry (amhw_hc32_lvd_t      *p_hw_base,
                                 amhw_hc32_lvd_vids_t  lvd_vids,
                                 uint32_t              lvd_src,
                                 am_pfnvoid_t          pfn_lvd_cb,
                                 void                 *p_arg);

/**
 * \brief OPA ͨ������Ŵ���ģʽ��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa :ָ��OPA�Ĵ���ָ��
 *
 * \retval ��
 */
void demo_hc32_hw_opa_entry (void *p_hw_opa);

/**
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa  : ָ��OPA�Ĵ���ָ��
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ���ָ��
 * \param[in] mode      : OPA����ģʽ
 * \param[in] p_vol_val : DAC���õ�ѹֵ����
 * \param[in] number    : DAC���õ�ѹֵ���鳤��
 *
 * \retval ��
 */
void demo_hc32_hw_opa_dac_entry (void      *p_hw_opa,
                                 void      *p_hw_dac,
                                 uint8_t    mode,
                                 uint16_t  *p_vol_val,
                                 uint32_t   number);

/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_aes    : ָ��AES�Ĵ���ָ��
 * \param[in] key_len     : ��Կ����
 * \param[in] p_aes_data  : AES��������
 * \param[in] p_key_data  : AES��Կ
 *
 * \retval ��
 */
void demo_hc32_hw_aes_ency_decy_entry (void     *p_hw_aes,
                                       uint8_t   key_len,
                                       uint32_t *p_aes_data,
                                       uint32_t *p_key_data);

/**
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_trng   : ָ��TRNG�Ĵ���ָ��
 *
 * \retval ��
 */
void demo_hc32_hw_trng_generate_entry (void *p_hw_trng);

/**
 * \brief LCD ��ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_lcd   : ָ��lcd�Ĵ���ָ��
 * \param[in] p_data     : LCD��ʾ����
 *
 * \retval ��
 */
void demo_hc32_hw_lcd_entry (void *p_hw_lcd, uint32_t *p_data);


/******************************************************************************/

/**
 * \brief hc32x3x OPA���̣�ͨ���첽��׼�ӿ�ʵ��
 *
 * \param[in] handle      OPA ��׼������
 * \param[in] ch          OPAͨ��
 *
 * \return ��
 */
void demo_hc32x3x_drv_opa_entry (void *p_handle, uint8_t ch);

/**
 * \brief hc32x3x OPA ��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa :ָ��OPA�Ĵ���ָ��
 * \param[in] mode     :OPA����ģʽ
 * \param[in] ch       :OPAͨ��
 *
 * \retval :��
 */
void demo_hc32x3x_hw_opa_entry (void *p_hw_opa, uint8_t mode, uint8_t ch);

/**
 * \brief RTC ʵʱʱ�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_rtc    : ָ��RTC�Ĵ���ָ��
 *
 * \retval ��
 */
void demo_hc32_hw_rtc_entry (void *p_hw_rtc);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_HC32_ENTRIES_H */

/* end of file */
