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
 * \brief HC32F460ϵ�������������������̺����������
 * \sa    demo_hc32f460_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __DEMO_HC32F460_ENTRIES_H
#define __DEMO_HC32F460_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"
#include "am_can.h"
#include "hw/amhw_hc32f460_gpio.h"
#include "hw/amhw_hc32f460_adc.h"
#include "hw/amhw_hc32f460_uart.h"
#include "hw/amhw_hc32f460_dma.h"
#include "am_hc32f460_dma.h"
#include "am_hc32f460_qspi.h"
#include "hw/amhw_hc32f460_spi.h"
#include "hw/amhw_hc32f460_wdt.h"
#include "hw/amhw_hc32f460_hash.h"
#include "hw/amhw_hc32f460_trng.h"
#include "hw/amhw_hc32f460_aes.h"
#include "hw/amhw_hc32f460_dcu.h"
#include "hw/amhw_hc32f460_cmp.h"
#include "am_hc32f460_hash.h"
#include "am_hc32f460_trng.h"
#include "am_hc32f460_aes.h"
#include "am_hc32f460_swdt.h"
#include "am_hc32f460_wdt.h"
#include "am_wdt.h"
#include "hw/amhw_hc32f460_adc.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_clk_id_buf   ָ��Ҫ��ӡ��ʱ��ID������
 * \param[in] buf_lenth      ʱ��ID����ĳ���
 *
 * \return ��
 */
void demo_hc32f460_hw_clk_entry (am_clk_id_t  *p_clk_id_buf,
                                 uint8_t       buf_lenth,
                                 char         *p_clk_name,
                                 uint8_t       name_length);

/**
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ��ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] chan       ADCͨ����
 * \param[in] vref_mv    �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_int_entry (void    *p_hw_adc,
                                     int      int_num,
                                     uint8_t  chan,
                                     uint32_t vref_mv);

/**
 * \brief ADC��ͨ��DMA�������̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] p_adc_chan ADCͨ����������
 * \param[in] p_dma_dev  ָ�� DMA�豸��ָ��
 * \param[in] chan_num   ADCͨ����
 * \param[in] vref_mv    �ο���ѹ
 * \param[in] dma_chan   DMAͨ����
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_dma_entry (void                  *p_hw_adc,
                                     amhw_adc_chmux_t      *p_adc_chan,
                                     am_hc32f460_dma_dev_t *p_dma_dev,
                                     int                    chan_num,
                                     uint32_t               vref_mv,
                                     int                    dma_chan);


/**
 * \brief ADC ��ͨ��ת�� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] vref_mv    �ο���ѹ
 * \param[in] p_adc_chan ADCͨ����������
 * \param[in] chan_num   ADCͨ����
 *
 * \return ��
 */
void demo_hc32f460_hw_multichan_adc_entry (void    *p_hw_adc,
                                           int      int_num,
                                           uint32_t vref_mv,
                                           amhw_adc_chmux_t     *p_adc_chan,
                                           uint8_t  chan_num);

/**
 * \brief ADC ��ͨ������ת�� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] vref_mv    �ο���ѹ
 * \param[in] p_adc_chan ADCͨ����������
 * \param[in] chan_num   ADCͨ����
 *
 * \return ��
 */
void demo_hc32f460_hw_multichan_seq_adc_entry (void             *p_hw_adc,
                                               int               int_num,
                                               uint32_t          vref_mv,
                                               amhw_adc_chmux_t *p_adc_chan,
                                               uint8_t           chan_num);

/**
 * \brief ADC ����A�¼����� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] chan_num   ADCͨ����
 * \param[in] vref_mv    �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_seq_a_event_trigger_entry (void    *p_hw_adc,
                                                     int      int_num,
                                                     uint8_t  chan,
                                                     uint32_t vref_mv);

/**
 * \brief ADC ����A��B˫�����¼����� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num  �жϱ��
 * \param[in] chan_a   ADC����Aͨ����
 * \param[in] chan_b   ADC����Bͨ����
 * \param[in] vref_mv  �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_seq_a_b_event_trigger_entry (void    *p_hw_adc,
                                                       int      int_num,
                                                       uint8_t  chan_a,
                                                       uint8_t  chan_b,
                                                       uint32_t vref_mv);

/**
 * \brief ��ADC Эͬ���� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc1    ָ�� ADC1����Ĵ������ָ��
 * \param[in] p_hw_adc2    ָ�� ADC2����Ĵ������ָ��
 * \param[in] int_num_adc1 ADC1�жϱ��
 * \param[in] int_num_adc2 ADC2�жϱ��
 * \param[in] chan_adc1    ADC1ͨ����
 * \param[in] chan_adc2    ADC2ͨ����
 * \param[in] vref_mv      �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_sync_entry (void    *p_hw_adc1,
                                      void    *p_hw_adc2,
                                      int      int_num_adc1,
                                      int      int_num_adc2,
                                      uint8_t  chan_adc1,
                                      uint8_t  chan_adc2,
                                      uint32_t vref_mv);

/**
 * \brief ADC PGA ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc  ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num   ADC�жϱ��
 * \param[in] chan      ADCͨ����
 * \param[in] vref_mv   �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_pga_entry (void    *p_hw_adc,
                                     int      int_num,
                                     uint8_t  chan,
                                     uint32_t vref_mv);

/**
 * \brief ADC PGA ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc  ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num   EOC�жϱ��
 * \param[in] chan      SEQCMP�жϱ��
 * \param[in] chan      ADCͨ����
 * \param[in] vref_mv   �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_awd_entry (void    *p_hw_adc,
                                     int      int_num_eoc,
                                     int      int_num_seqcmp,
                                     uint8_t  chan,
                                     uint32_t vref_mv);


/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \return ��
 */
void demo_hc32f460_hw_gpio_entry (void    *p_hw_gpio,
                                  int32_t  input_pin,
                                  int32_t  output_pin);

/**
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio     ָ�� GPIO ����Ĵ������ָ��
 * \param[in] pin           �ж����ź�
 *
 * \return ��
 */
void demo_hc32f460_hw_gpio_trigger_entry (void *p_hw_gpio, int pin);


/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_hc32f460_drv_dma_m2m_entry (am_hc32f460_dma_dev_t *p_dev, uint32_t dma_chan);

/**
 * \brief DMA �ڴ浽�ڴ������������̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_dev    DMA �豸ָ��
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_hc32f460_drv_dma_m2m_chain_entry (am_hc32f460_dma_dev_t *p_dev, uint32_t dma_chan);

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
void demo_hc32f460_hw_uart_int_entry (void             *p_hw_uart,
                                      void (* pfn_init)(void),
                                      int              clk_rate,
                                      unsigned long    uart_base);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hc32f460_hw_uart_polling_entry (void     *p_hw_uart,
                                          uint32_t  clk_rate);


/**
 * \brief UART DMA�������̣�ͨ�� HW ��ӿ�ʵ��
 *

 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hc32f460_hw_uart_tx_dma_entry (void                   *p_hw_uart,
                                         uint32_t                clk_rate,
                                         am_hc32f460_dma_dev_t  *p_dma_dev,
                                         int32_t                 dma_chan);
/**
 * \brief UART DMA�������̣�ͨ�� HW ��ӿ�ʵ��
 *

 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hc32f460_hw_uart_rx_dma_entry (void    *p_hw_uart,
                                         uint32_t clk_rate,
                                         am_hc32f460_dma_dev_t *p_dma_dev,
                                         int32_t  dma_chan);

/**
 * \brief QSPI��д��������
 *
 * \param[in] p_hw_uart ָ�� QSPI�豸��ָ��
 *
 * \return ��
 */
void demo_hc32f460_drv_qspi_entry (am_hc32f460_qspi_dev_t *p_dev);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] cs_pin    Ƭѡ����
 *
 * \return ��
 */
void demo_hc32f460_hw_spi_master_entry (void    *p_hw_spi,
                                        int32_t  cs_pin);

/**
 * \brief WDT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_wdt     ָ�� WDT ����Ĵ������ָ��
 * \param[in] time_out_ms  WDT��ʱʱ��
 * \param[in] feed_time_ms ι�����ʱ��
 * \param[in] clk_rate     wdtʱ��Ƶ��
 *
 * \return ��
 */
void demo_hc32f460_hw_wdt_entry (void     *p_hw_wdt,
                                 uint32_t  time_out_ms,
                                 uint32_t  feed_time_ms,
                                 uint32_t  clk_rate);

/**
 * \brief WDT DRV���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] handle       WDT handler
 * \param[in] p_dev        ָ��WDT�豸��ָ��
 * \param[in] time_out_ms  WDT��ʱʱ��
 * \param[in] feed_time_ms ι�����ʱ��
 *
 * \return ��
 */
void demo_hc32f460_drv_wdt_int_entry (am_wdt_handle_t        handle,
                                      am_hc32f460_wdt_dev_t *p_dev,
                                      uint32_t               time_out_ms,
                                      uint32_t               feed_time_ms);

/**
 * \brief SWDT DRV���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] handle       SWDT handler
 * \param[in] p_dev        ָ��SWDT�豸��ָ��
 * \param[in] feed_time_ms ι�����ʱ��
 *
 * \return ��
 */
void demo_hc32f460_drv_swdt_int_entry (am_wdt_handle_t         handle,
                                       am_hc32f460_swdt_dev_t *p_dev,
                                       uint32_t                feed_time_ms);


/**
 * \brief MPU ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_mpu     MPU�Ĵ����ṹ��ָ��
 *
 * \return ��
 */
void demo_hc32f460_hw_mpu_entry (void *p_hw_mpu);

/**
 * \brief HASH ��ϢժҪ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_hash     ָ�� HASH ����Ĵ������ָ��
 * \param[in] data_len      ԭʼ���ݳ��ȣ��ֽڣ�
 * \param[in] p_hash_data   ָ����ԭʼ���ݵ�BUFFER��ָ��
 * \param[in] p_hash_digest ָ������ϢժҪ��BUFFER��ָ��
 *
 * \return ��
 */
void demo_hc32f460_hw_hash_entry(void     *p_hw_hash,
                                 uint32_t  data_len,
                                 uint8_t  *p_hash_data,
                                 uint8_t  *p_hash_digest);

/**
 * \brief HASH ��ϢժҪ�������̣�ͨ�� ���� ��ӿ�ʵ��
 *
 * \param[in] p_hw_trng ָ�� HASH�����handle
 *
 * \return ��
 */
void demo_hc32f460_drv_hash_generate_entry (am_hash_handle_t handle);

/**
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_trng ָ�� TRNG ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_hc32f460_hw_trng_generate_entry (void *p_hw_trng);

/**
 * \brief TRNG ������������̣�ͨ�� DRV ��ӿ�ʵ��
 *
 * \param[in] p_hw_trng ָ�� TRNG�����handle
 *
 * \return ��
 */
void demo_hc32f460_drv_trng_generate_entry (am_trng_handle_t handle);

/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart  ָ�� AES ����Ĵ������ָ��
 * \param[in] p_aes_data ָ�� Ҫ���ܵ�����
 * \param[in] p_key_data ָ�� ��Կ
 *
 * \return ��
 */
void demo_hc32f460_hw_aes_ency_decy_entry (void     *p_hw_aes,
                                           uint32_t *p_aes_data,
                                           uint32_t *p_key_data);

/**
 * \brief AES ���ܽ������̣�ͨ�� DRV ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart  ָ�� AES �����handle
 * \param[in] p_aes_data ָ�� Ҫ���ܵ�����
 * \param[in] p_key_data ָ�� ��Կ
 *
 * \return ��
 */
void demo_hc32f460_drv_aes_ency_decy_entry (am_aes_handle_t  handle,
                                            uint32_t        *p_aes_data,
                                            uint32_t        *p_key_data);

/**
 * \brief DCU ���ݼ��㵥Ԫ���̣�ͨ�� Ӳ�� ��ӿ�ʵ��
 *
 * \param[in] p_hw_dcu ָ�� DCU ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_hc32f460_hw_dcu_entry (void *p_hw_dcu);

/**
 * \brief FLASH��д���̣�ͨ�� DRV ��ӿ�ʵ��
 *
 * \param[in] p_hw_dcu ָ�� EFM ����Ĵ������ָ��
 * \param[in] sector   �������
 *
 * \return ��
 */
void demo_hc32f460_drv_flash_entry (void *p_hw_flash, uint16_t sector);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_hw_i2c_slave_poll_entry (void     *p_hw_i2c_addr,
                                            uint32_t  clk_id,
                                            int       slave_speed,
                                            int       slave_addr);

/**
 * \brief I2C ������ѯ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_hw_i2c_master_poll_entry (void     *p_hw_i2c_addr,
                                             uint32_t  clk_id,
                                             int       master_speed,
                                             int       master_addr);

/**
 * \brief USBģ��U�����̣�ͨ��driver��Ľӿ�ʵ��
 */
void demo_usbd_msc_entry (void* p_handle);

/**
 * \brief USBģ��������̣�ͨ��driver��Ľӿ�ʵ��
 */
void demo_usbd_mouse_entry (void* p_handle);

/**
 * \brief CMP���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32f460_hw_cmp_entry (amhw_hc32f460_cmp_t *p_hw_cmp);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_HC32F460_ENTRIES_H */

/* end of file */
