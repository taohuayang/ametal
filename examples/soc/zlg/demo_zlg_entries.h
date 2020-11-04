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
 * \sa    demo_zlg_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __DEMO_ZLG_ENTRIES_H
#define __DEMO_ZLG_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"
#include "am_can.h"

#include "hw/amhw_zlg_adc.h"
#include "hw/amhw_zlg_exti.h"
#include "hw/amhw_zlg_flash.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zlg_i2c.h"
#include "hw/amhw_zlg_pwr.h"
#include "hw/amhw_zlg_spi.h"
#include "hw/amhw_zlg_dma.h"
#include "hw/amhw_zlg_syscfg.h"
#include "hw/amhw_zlg_tim.h"
#include "hw/amhw_zlg_uart.h"
#include "hw/amhw_zlg_iwdg.h"
#include "hw/amhw_zlg_wwdg.h"
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
void demo_zlg_hw_adc_int_entry (amhw_zlg_adc_t *p_hw_adc,
                                int             int_num,
                                int             chan,
                                uint32_t        vref_mv);

/**
 * \brief ADC Ӳ���㣨DMA������ͨ���������
 *
 */
void demo_zlg_hw_adc_dma_entry (amhw_zlg_adc_t *p_hw_adc,
                                int            *p_adc_chan,
                                int             adc_chan_num,
                                uint8_t         dma_chan);

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] chan      : ���Ŷ�Ӧ�� ADCͨ����
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_zlg118_hw_adc_int_entry (void    *p_hw_adc,
                                   int      int_num,
                                   uint8_t  chan,
                                   uint32_t vref_mv);

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 * \param[in] p_adc_chan: ADCͨ������ָ��
 * \param[in] sqr_num   : ����ͨ������
 * \param[in] jqr_num   : ����ͨ������
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_zlg118_hw_multichan_adc_entry (void    *p_hw_adc,
                                         int      int_num,
                                         uint32_t vref_mv,
                                         int     *p_adc_chan,
                                         uint8_t  sqr_num,
                                         uint8_t  jqr_num);

/**
 * \brief ADC Ӳ���㣨DMA���������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] p_adc_chan: ADCͨ������ָ��
 * \param[in] chan_num  : ADCͨ������
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 * \param[in] dma_chan  : DMAͨ����
 * \param[in] dma_src   : DMA���䴥��Դ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADCģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_zlg118_hw_adc_dma_entry (void    *p_hw_adc,
                                   int     *p_adc_chan,
                                   int      chan_num,
                                   uint32_t vref_mv,
                                   int      dma_chan,
                                   uint8_t  dma_src);

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] chan      : ���Ŷ�Ӧ�� ADCͨ����
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_zsn700_hw_adc_int_entry (void    *p_hw_adc,
                                   int      int_num,
                                   uint8_t  chan,
                                   uint32_t vref_mv);

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 * \param[in] p_adc_chan: ADCͨ������ָ��
 * \param[in] sqr_num   : ����ͨ������
 * \param[in] jqr_num   : ����ͨ������
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_zsn700_hw_multichan_adc_entry (void    *p_hw_adc,
                                         int      int_num,
                                         uint32_t vref_mv,
                                         int     *p_adc_chan,
                                         uint8_t  sqr_num,
                                         uint8_t  jqr_num);

/**
 * \brief ADC Ӳ���㣨DMA���������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] p_adc_chan: ADCͨ������ָ��
 * \param[in] chan_num  : ADCͨ������
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 * \param[in] dma_chan  : DMAͨ����
 * \param[in] dma_src   : DMA���䴥��Դ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADCģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_zsn700_hw_adc_dma_entry (void    *p_hw_adc,
                                   int     *p_adc_chan,
                                   int      chan_num,
                                   uint32_t vref_mv,
                                   int      dma_chan,
                                   uint8_t  dma_src);

/**
 * \brief zlg237 ADC Ӳ���㣨ʹ�����жϣ�����ͨ���������
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
void demo_zlg237_hw_adc_int_entry (void              *p_hw_adc,
                                   int                int_num,
                                   int                chan,
                                   uint32_t           vref_mv);

/**
 * \brief zlg237 DC Ӳ���㣨DMA������ͨ���������
 */
void demo_zlg237_hw_adc_dma_entry (void              *p_hw_adc,
                                   int               *p_adc_chan,
                                   int                adc_chan_num,
                                   uint8_t            dma_chan);


/**
 * \brief zlg237 ADC Ӳ���㣨ʹ�����жϣ� ע��ͨ���������
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
void demo_zlg237_hw_adc_injected_int_entry (void              *p_hw_adc,
                                            int                int_num,
                                            uint32_t           vref_mv,
                                            int               *p_adc_chan,
                                            int                adc_chan_num);

/**
 * \brief zlg237 ADC Ӳ���㣨ʹ�����жϣ�����ͨ����ע��ͨ���������
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
void demo_zlg237_hw_adc_dma_double_entry (void              *p_hw_adc1,
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
void demo_zlg_hw_clk_entry (am_clk_id_t *p_clk_id_buf, uint8_t buf_lenth);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_zlg_drv_dma_m2m_entry (uint32_t dma_chan);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_zlg118_drv_dma_m2m_entry (uint32_t dma_chan);

/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_zsn700_drv_dma_m2m_entry (uint32_t dma_chan);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_zlg_drv_flash_entry (amhw_zlg_flash_t *p_hw_flash, uint8_t sector);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_zlg118_drv_flash_entry (void *p_hw_flash, uint16_t sector);

/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_zsn700_drv_flash_entry (void *p_hw_flash, uint16_t sector);

/**
 * \brief zlg237 FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_zlg237_drv_flash_entry (void *p_hw_flash, uint8_t sector);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO ����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \return ��
 */
void demo_zlg_hw_gpio_entry (amhw_zlg_gpio_t *p_hw_gpio,
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
void demo_zlg_hw_gpio_trigger_entry (amhw_zlg_gpio_t         *p_hw_gpio,
                                     amhw_zlg_syscfg_t       *p_hw_syscfg,
                                     amhw_zlg_exti_t         *p_hw_exti,
                                     int32_t                  pin,
                                     uint8_t                  portsource,
                                     uint8_t                  pinsource,
                                     amhw_zlg_exti_line_num_t exti_line_num);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \return ��
 */
void demo_zlg118_hw_gpio_entry (void    *p_hw_gpio,
                                int32_t  input_pin,
                                int32_t  output_pin);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \return ��
 */
void demo_zsn700_hw_gpio_entry (void    *p_hw_gpio,
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
void demo_zlg118_hw_gpio_trigger_entry (void *p_hw_gpio, int32_t pin);

/**
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio     ָ�� GPIO ����Ĵ������ָ��
 * \param[in] pin           �ж����ź�
 *
 * \return ��
 */
void demo_zsn700_hw_gpio_trigger_entry (void *p_hw_gpio, int32_t pin);

/**
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] clk_rate I2C ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zlg_hw_i2c_master_poll_entry (amhw_zlg_i2c_t *p_hw_i2c,
                                        uint32_t        clk_rate);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_zlg_hw_i2c_slave_poll_entry (amhw_zlg_i2c_t *p_hw_i2c);

/**
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] clk_rate I2C ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zlg118_hw_i2c_master_poll_entry (void        *p_hw_i2c,
                                           uint32_t     clk_rate);

/**
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] clk_rate I2C ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zsn700_hw_i2c_master_poll_entry (void        *p_hw_i2c,
                                           uint32_t     clk_rate);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] inum_num I2C�жϺ�
 *
 * \return ��
 */
void demo_zlg118_hw_i2c_slave_int_entry (void  *p_hw_i2c,
                                         int    inum_num);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] inum_num I2C�жϺ�
 *
 * \return ��
 */
void demo_zsn700_hw_i2c_slave_int_entry (void  *p_hw_i2c,
                                         int    inum_num);

/**
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 * \param[in] clk_rate I2C ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zlg237_hw_i2c_master_poll_entry (void           *p_hw_i2c,
                                           uint32_t        clk_rate);

/**
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c ָ�� I2C ����Ĵ������ָ��
 *
 * \return ��
 */
void demo_zlg237_hw_i2c_slave_poll_entry (void *p_hw_i2c);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_spi ָ�� SPI ����Ĵ������ָ��
 * \param[in] cs_pin   Ƭѡ���ź�
 * \param[in] clk_rate SPI ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zlg237_hw_spi_master_entry (void              *p_hw_spi,
                                      int32_t            cs_pin,
                                      uint32_t           clk_rate,
                                      uint32_t           cs_mdelay);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_spi ָ�� SPI ����Ĵ������ָ��
 * \param[in] cs_pin   Ƭѡ���ź�
 * \param[in] clk_rate SPI ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zlg_hw_spi_master_entry (amhw_zlg_spi_t *p_hw_spi,
                                   int32_t         cs_pin,
                                   uint32_t        clk_rate);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_spi ָ�� SPI ����Ĵ������ָ��
 * \param[in] cs_pin   Ƭѡ���ź�
 *
 * \return ��
 */
void demo_zlg118_hw_spi_master_entry (void    *p_hw_spi,
                                      int32_t  cs_pin);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_spi ָ�� SPI ����Ĵ������ָ��
 * \param[in] cs_pin   Ƭѡ���ź�
 *
 * \return ��
 */
void demo_zsn700_hw_spi_master_entry (void    *p_hw_spi,
                                      int32_t  cs_pin);

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
void demo_zlg_hw_tim_cap_entry (amhw_zlg_tim_t      *p_hw_tim,
                                amhw_zlg_tim_type_t  type,
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
void demo_zlg_hw_tim_cmp_toggle_entry (amhw_zlg_tim_t      *p_hw_tim,
                                       amhw_zlg_tim_type_t  type,
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
void demo_zlg_hw_tim_pwm_entry (amhw_zlg_tim_t     *p_hw_tim,
                                amhw_zlg_tim_type_t type,
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
void demo_zlg_hw_tim_pwm_dead_entry (amhw_zlg_tim_t     *p_hw_tim,
                                     amhw_zlg_tim_type_t type,
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
void demo_zlg_hw_tim_timing_entry (amhw_zlg_tim_t     *p_hw_tim,
                                   amhw_zlg_tim_type_t type,
                                   uint32_t            clk_rate,
                                   int32_t             int_num);

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
void demo_zlg118_hw_tim_cap_entry (void     *p_hw_tim,
                                   uint8_t   type,
                                   uint32_t  chan,
                                   uint32_t  clk_rate,
                                   int32_t   inum);

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
void demo_zsn700_hw_tim_cap_entry (void     *p_hw_tim,
                                   uint8_t   type,
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
 * \return ��
 */
void demo_zlg118_hw_tim_cmp_toggle_entry (void    *p_hw_tim,
                                          uint8_t  type,
                                          uint32_t chan,
                                          uint32_t clk_rate,
                                          uint8_t  clk_div,
                                          uint8_t  inum);

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
 * \return ��
 */
void demo_zsn700_hw_tim_cmp_toggle_entry (void    *p_hw_tim,
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
 * \param[in] duty_ns   ����ʱ�䣨us��
 * \param[in] period_ns ����ʱ�䣨us��
 * \param[in] dead_us   ����ʱ�����ã�us��
 *
 * \return ��
 */
void demo_zlg118_hw_tim_pwm_dead_entry (void    *p_hw_tim,
                                        uint8_t  type,
                                        uint8_t  chan_a,
                                        uint8_t  chan_b,
                                        uint32_t duty_us,
                                        uint32_t period_us,
                                        uint16_t dead_us);

/**
 * \brief ��ʱ��ͨ���������Ļ���PWM������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_tim  ָ��ʱ������Ĵ������ָ��
 * \param[in] type      ��ʱ������
 * \param[in] chan_a    ��ʱ������PWMͨ��A
 * \param[in] chan_b    ��ʱ������PWMͨ��B
 * \param[in] duty_ns   ����ʱ�䣨us��
 * \param[in] period_ns ����ʱ�䣨us��
 * \param[in] dead_us   ����ʱ�����ã�us��
 *
 * \return ��
 */
void demo_zsn700_hw_tim_pwm_dead_entry (void    *p_hw_tim,
                                        uint8_t  type,
                                        uint8_t  chan_a,
                                        uint8_t  chan_b,
                                        uint32_t duty_us,
                                        uint32_t period_us,
                                        uint16_t dead_us);

/**
 * \brief �߼���ʱ��������ͬ����ʼ��ͬ��ֹͣ��ͬ���������̣�ͨ�� HW��ӿ�ʵ��
 *
 * \param[in] p_tim_cfg ָ�����ͬ�����ýṹ���ָ�루amhw_zlg118_adtim_sw_sync_t��
 *
 * \return ��
 */
void demo_zlg118_hw_adtim_swsync_entry (void *p_tim_cfg);

/**
 * \brief �߼���ʱ��������ͬ����ʼ��ͬ��ֹͣ��ͬ���������̣�ͨ�� HW��ӿ�ʵ��
 *
 * \param[in] p_tim_cfg ָ�����ͬ�����ýṹ���ָ�루amhw_zlg118_adtim_sw_sync_t��
 *
 * \return ��
 */
void demo_zsn700_hw_adtim_swsync_entry (void *p_tim_cfg);

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
 * \return ��
 */
void demo_zlg118_hw_adtim_port_sw_brake_entry (void          *p_hw_adtim,
                                               uint8_t        chan,
                                               unsigned long  duty_ns,
                                               unsigned long  period_ns,
                                               int            output_pin,
                                               uint8_t        src);

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
 * \return ��
 */
void demo_zsn700_hw_adtim_port_sw_brake_entry (void          *p_hw_adtim,
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
 * \return ��
 */
void demo_zlg118_hw_adtim_vc_brake_entry (void         *p_hw_adtim,
                                          uint8_t       chan,
                                          unsigned long duty_ns,
                                          unsigned long period_ns,
                                          void         *p_hw_vc,
                                          uint8_t       vc0_n,
                                          uint8_t       vc0_p);

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
 * \return ��
 */
void demo_zsn700_hw_adtim_vc_brake_entry (void         *p_hw_adtim,
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
 * \param[in] period_ns   ����ʱ��
 * \param[in] p_hw_adc    ָ��ADC����Ĵ������ָ��
 * \param[in] adc_int_num ADC�жϺ�
 * \param[in] p_adc_chan  ADCͨ���������
 * \param[in] sqr_num     ADC˳��ͨ������
 *
 * \return ��
 */
void demo_zlg118_hw_adtim_trig_adc_sqr_entry (void    *p_hw_adtim,
                                              uint32_t period_ns,
                                              void    *p_hw_adc,
                                              int      adc_int_num,
                                              int     *p_adc_chan,
                                              uint8_t  sqr_num);

/**
 * \brief �߼���ʱ����ʱ����ADCת�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adtim  ָ��ʱ������Ĵ������ָ��
 * \param[in] period_ns   ����ʱ��
 * \param[in] p_hw_adc    ָ��ADC����Ĵ������ָ��
 * \param[in] adc_int_num ADC�жϺ�
 * \param[in] p_adc_chan  ADCͨ���������
 * \param[in] sqr_num     ADC˳��ͨ������
 *
 * \return ��
 */
void demo_zsn700_hw_adtim_trig_adc_sqr_entry (void    *p_hw_adtim,
                                              uint32_t period_ns,
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
 * \return ��
 */
void demo_zlg118_hw_tim_port_brake_entry (void    *p_hw_tim,
                                          uint8_t  type,
                                          uint8_t  chan,
                                          int      inum,
                                          uint32_t duty_ns,
                                          uint32_t period_us);

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
 * \return ��
 */
void demo_zsn700_hw_tim_port_brake_entry (void    *p_hw_tim,
                                          uint8_t  type,
                                          uint8_t  chan,
                                          int      inum,
                                          uint32_t duty_ns,
                                          uint32_t period_us);

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
 * \return ��
 */
void demo_zlg118_hw_tim_vc_brake_entry (void         *p_hw_tim,
                                        uint8_t       chan,
                                        unsigned long duty_ns,
                                        unsigned long period_ns,
                                        void         *p_hw_vc,
                                        uint8_t       vc0_n,
                                        uint8_t       vc0_p);

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
 * \return ��
 */
void demo_zsn700_hw_tim_vc_brake_entry (void         *p_hw_tim,
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
 * \return ��
 */
void demo_zlg118_hw_tim_pwm_entry (void    *p_hw_tim,
                                   uint8_t  type,
                                   uint32_t chan,
                                   uint32_t clk_rate,
                                   uint8_t  clk_div,
                                   int32_t  inum);

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
 * \return ��
 */
void demo_zsn700_hw_tim_pwm_entry (void    *p_hw_tim,
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
 * \param[in] inum     �жϺ�
 *
 * \return ��
 */
void demo_zlg118_hw_tim_timing_entry (void    *p_hw_tim,
                                      uint8_t  type,
                                      uint32_t clk_rate,
                                      int32_t  int_num);

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
void demo_zsn700_hw_tim_timing_entry (void    *p_hw_tim,
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
 * \return ��
 */
void demo_zlg118_hw_tim_trig_adc_sqr_entry (void    *p_hw_tim,
                                            uint8_t  type,
                                            uint8_t  chan,
                                            uint32_t duty_us,
                                            uint32_t period_us,
                                            void    *p_hw_adc,
                                            int      adc_int_num,
                                            int     *p_adc_chan,
                                            uint8_t  sqr_num);

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
 * \return ��
 */
void demo_zsn700_hw_tim_trig_adc_sqr_entry (void    *p_hw_tim,
                                            uint8_t  type,
                                            uint8_t  chan,
                                            uint32_t duty_us,
                                            uint32_t period_us,
                                            void    *p_hw_adc,
                                            int      adc_int_num,
                                            int     *p_adc_chan,
                                            uint8_t  sqr_num);

/**
 * \brief ZLG UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� UART ���ų�ʼ��������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] uart_base UART ����ַ
 * \param[in] inum_uart UART �жϺ�
 *
 * \return ��
 */
void demo_zlg_hw_uart_int_entry (amhw_zlg_uart_t *p_hw_uart,
                                 void (* pfn_init)(void),
                                 uint32_t         clk_rate,
                                 unsigned long    uart_base,
                                 unsigned char    inum_uart);

/**
 * \brief ZLG UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zlg_hw_uart_polling_entry (amhw_zlg_uart_t *p_hw_uart,
                                     uint32_t         clk_rate);

/**
 * \brief ZLG UART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 *
 * \return ��
 */
void demo_zlg_hw_uart_rx_dma_entry (amhw_zlg_uart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan);

/**
 * \brief ZLG UART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 *
 * \return ��
 */
void demo_zlg_hw_uart_tx_dma_entry (amhw_zlg_uart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan);

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
void demo_zlg118_hw_uart_int_entry (void             *p_hw_uart,
                                    void (* pfn_init)(void),
                                    uint32_t         clk_rate,
                                    unsigned long    uart_base,
                                    unsigned char    inum_uart);

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
void demo_zsn700_hw_uart_int_entry (void             *p_hw_uart,
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
void demo_zlg118_hw_uart_polling_entry (void     *p_hw_uart,
                                        uint32_t  clk_rate);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zsn700_hw_uart_polling_entry (void     *p_hw_uart,
                                        uint32_t  clk_rate);

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] dma_chan  DMA ͨ����
 * \param[in] dma_src   DMA ����Դѡ��
 *
 * \return ��
 */
void demo_zlg118_hw_uart_rx_dma_entry (void    *p_hw_uart,
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
 * \return ��
 */
void demo_zsn700_hw_uart_rx_dma_entry (void    *p_hw_uart,
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
 * \return ��
 */
void demo_zlg118_hw_uart_tx_dma_entry (void    *p_hw_uart,
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
 * \return ��
 */
void demo_zsn700_hw_uart_tx_dma_entry (void    *p_hw_uart,
                                       uint32_t clk_rate,
                                       int32_t  dma_chan,
                                       int32_t  dma_src);

/**
 * \brief LPUART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ��LPUART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� LPUART ���ų�ʼ��������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 * \param[in] uart_base LPUART ����ַ
 * \param[in] inum_uart LPUART �жϺ�
 *
 * \return ��
 */
void demo_zlg118_hw_lpuart_int_entry (void             *p_hw_uart,
                                      void (* pfn_init)(void),
                                      uint8_t           sclk_src,
                                      uint32_t          clk_rate,
                                      uint32_t          baudrate,
                                      unsigned long     uart_base,
                                      unsigned char     inum_uart);

/**
 * \brief LPUART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ��LPUART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� LPUART ���ų�ʼ��������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 * \param[in] uart_base LPUART ����ַ
 * \param[in] inum_uart LPUART �жϺ�
 *
 * \return ��
 */
void demo_zsn700_hw_lpuart_int_entry (void             *p_hw_uart,
                                      void (* pfn_init)(void),
                                      uint8_t           sclk_src,
                                      uint32_t          clk_rate,
                                      uint32_t          baudrate,
                                      unsigned long     uart_base,
                                      unsigned char     inum_uart);

/**
 * \brief LPUART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 *
 * \return ��
 */
void demo_zlg118_hw_lpuart_polling_entry (void     *p_hw_uart,
                                          uint8_t   clk_src,
                                          uint32_t  clk_rate,
                                          uint32_t  baudrate);

/**
 * \brief LPUART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 *
 * \return ��
 */
void demo_zsn700_hw_lpuart_polling_entry (void     *p_hw_uart,
                                          uint8_t   clk_src,
                                          uint32_t  clk_rate,
                                          uint32_t  baudrate);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 * \param[in] dma_chan  DMA ͨ����
 * \param[in] dma_src   DMA ����Դѡ��
 *
 * \return ��
 */
void demo_zlg118_hw_lpuart_rx_dma_entry (void    *p_hw_uart,
                                         uint8_t  clk_src,
                                         uint32_t clk_rate,
                                         uint32_t baudrate,
                                         int32_t  dma_chan,
                                         int32_t  dma_src);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 * \param[in] dma_chan  DMA ͨ����
 * \param[in] dma_src   DMA ����Դѡ��
 *
 * \return ��
 */
void demo_zsn700_hw_lpuart_rx_dma_entry (void    *p_hw_uart,
                                         uint8_t  clk_src,
                                         uint32_t clk_rate,
                                         uint32_t baudrate,
                                         int32_t  dma_chan,
                                         int32_t  dma_src);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 * \param[in] dma_chan  DMA ͨ����
 * \param[in] dma_src   DMA ����Դѡ��
 *
 * \return ��
 */
void demo_zlg118_hw_lpuart_tx_dma_entry (void    *p_hw_uart,
                                         uint8_t  clk_src,
                                         uint32_t clk_rate,
                                         uint32_t baudrate,
                                         int32_t  dma_chan,
                                         int32_t  dma_src);

/**
 * \brief LPUART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� LPUART ����Ĵ������ָ��
 * \param[in] sclk_src  LPUART ʱ��Դѡ��
 * \param[in] clk_rate  LPUART ʱ��ԴƵ��
 * \param[in] baudrate  LPUART ������
 * \param[in] dma_chan  DMA ͨ����
 * \param[in] dma_src   DMA ����Դѡ��
 *
 * \return ��
 */
void demo_zsn700_hw_lpuart_tx_dma_entry (void    *p_hw_uart,
                                         uint8_t  clk_src,
                                         uint32_t clk_rate,
                                         uint32_t baudrate,
                                         int32_t  dma_chan,
                                         int32_t  dma_src);

/**
 * \brief ZLG237 USART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� USART ���ų�ʼ��������ָ��
 * \param[in] clk_rate  USART ʱ��ԴƵ��
 * \param[in] uart_base USART ����ַ
 * \param[in] inum_uart USART �жϺ�
 *
 * \return ��
 */
void demo_zlg237_hw_usart_int_entry (void                *p_hw_usart,
                                     void (* pfn_init)(void),
                                     uint32_t             clk_rate,
                                     unsigned long        usart_base,
                                     unsigned char        inum_usart);

/**
 * \brief ZLG237 USART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] clk_rate   USART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_zlg237_hw_usart_polling_entry (void                *p_hw_usart,
                                         uint32_t             clk_rate);

/**
 * \brief ZLG237 USART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] clk_rate   USART ʱ��ԴƵ��
 * \param[in] dma_chan   DMA ͨ����
 *
 * \return ��
 */
void demo_zlg237_hw_usart_rx_dma_entry (void                *p_hw_usart,
                                        uint32_t             clk_rate,
                                        int32_t              dma_chan);

/**
 * \brief ZLG237 USART �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_usart ָ�� USART ����Ĵ������ָ��
 * \param[in] clk_rate   USART ʱ��ԴƵ��
 * \param[in] dma_chan   DMA ͨ����
 *
 * \return ��
 */
void demo_zlg237_hw_usart_tx_dma_entry (void                *p_hw_usart,
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
void demo_zlg116_drv_sleepmode_timer_wake_up_entry (am_timer_handle_t timer_handle,
                                                    uint32_t          timer_clk_rate);

/**
 * \brief ˯��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg116_drv_sleepmode_wake_up_entry (void);

/**
 * \brief ����ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg116_drv_standbymode_wake_up_entry (void);

/**
 * \brief ͣ��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg116_drv_stopmode_wake_up_entry (void);

/**
 * \brief ˯��ģʽ���̣�ʹ�ö�ʱ�����ڻ��ѣ�ͨ��������ӿ�ʵ��
 *
 * \param[in] timer_handle   ��ʱ����׼������
 * \param[in] timer_clk_rate ��ϵͳʱ���л�Ϊ LSI ʱ����ʱ����ʱ��Ƶ��
 *
 * \return ��
 */
void demo_zml165_drv_sleepmode_timer_wake_up_entry (am_timer_handle_t timer_handle,
                                                    uint32_t          timer_clk_rate);

/**
 * \brief ˯��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zml165_drv_sleepmode_wake_up_entry (void);

/**
 * \brief ����ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zml165_drv_standbymode_wake_up_entry (void);

/**
 * \brief ͣ��ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zml165_drv_stopmode_wake_up_entry (void);

/**
 * \brief IWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_iwdg    ָ�� IWDG ����Ĵ������ָ��
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \return ��
 */
void demo_zlg_hw_iwdg_entry (amhw_zlg_iwdg_t *p_hw_iwdg,
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
void demo_zlg_hw_wwdg_entry (amhw_zlg_wwdg_t *p_hw_wwdg,
                             uint32_t         clk_rate,
                             uint32_t         time_out_ms,
                             uint32_t         feed_time_ms);

/**
 * \brief ZSN700 WDT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_wdt     ָ�� WDT ����Ĵ������ָ��
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \return ��
 */
void demo_zlg118_hw_wdt_entry (void     *p_hw_wdt,
                               uint32_t  time_out_ms,
                               uint32_t  feed_time_ms);

/**
 * \brief ZSN700 WDT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_wdt     ָ�� WDT ����Ĵ������ָ��
 * \param[in] time_out_ms  ���Ź���ʱʱ��
 * \param[in] feed_time_ms ι��ʱ��
 *
 * \return ��
 */
void demo_zsn700_hw_wdt_entry (void     *p_hw_wdt,
                               uint32_t  time_out_ms,
                               uint32_t  feed_time_ms);

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
void demo_zml166_adc_vol_measure_entry(void                   *p_handle,
                                       float                  *p_para,
                                       uint8_t                 gpa_index);

/**
 * \brief ZML166 ADC �ȵ�ż��������
 * \param[in] handle      ZML166 ADC ������
 * \param[in] p_para      У׼����
 * \param[in] type        �ȵ�ż����
 * \return ��
 */
void dome_zml166_adc_thermocouple_measure_entry(void     *p_handle,
                                                float    *p_para,
                                                void     *p_ther_handle);

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

/**
 * \brief ZML165 ADC ��ѹ��������
 * \param[in] handle      ZML165 ADC ������
 * \return ��
 */
void demo_zml165_adc_vol_measure_entry(void  *p_handle);

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
void demo_zlg237_can_int_entry (am_can_handle_t     can_handle,
                                am_can_bps_param_t *can_btr_baud,
                                am_can_int_type_t   int_type,
                                am_can_filter_t    *p_filterbuff,
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
void demo_zlg237_can_entry (am_can_handle_t     can_handle,
                            am_can_bps_param_t *can_btr_baud);

/**
 * \brief USB��ӡ������   �����̴���ӡʱ���Լ���ӡ��������ʾ
 * \param[in] handle      USB��ӡ��������
 * \return ��
 */
void demo_usbd_printer_counter_entry (void* p_handle);

/**
 * \brief USB��ӡ������   �����̽���ӡ�����Ϣ
 * \param[in] handle      USB��ӡ��������
 * \return ��
 */
void demo_usbd_printer_entry (void* p_handle);

/**
 * \brief USBģ�⴮������
 * \param[in] handle      USBģ�⴮�ڷ�����
 * \return ��
 */
void demo_usbd_vcom_entry (void* p_handle);

/**
 * \brief USBģ�ⰴ������
 * \param[in] handle      USBģ����̷�����
 * \return ��
 */
void demo_usbd_keyboard_entry (void* p_handle);


/**
 * \brief USBģ��U������
 * \param[in] handle      USBģ����̷�����
 * \return ��
 */
void demo_usbd_msc_entry (void* p_handle);

/**
 * \brief DAC�����ѹ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_dac ָ��DAC�Ĵ���ָ��
 * \param[in] dma_src  DMA����Դ
 * \param[in] dma_chan DMAͨ��
 * \param[in] vol_val  ��ѹֵ
 *
 * \return ��
 */
void demo_zlg118_hw_dac_dma_entry(void     *p_hw_dac,
                                  int32_t  dma_src,
                                  int32_t  dma_chan,
                                  uint16_t *vol_val);

/**
 * \brief DAC�����ѹ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_dac ָ��DAC�Ĵ���ָ��
 * \param[in] dma_src  DMA����Դ
 * \param[in] dma_chan DMAͨ��
 * \param[in] vol_val  ��ѹֵ
 *
 * \return ��
 */
void demo_zsn700_hw_dac_dma_entry(void     *p_hw_dac,
                                  int32_t  dma_src,
                                  int32_t  dma_chan,
                                  uint16_t *vol_val);

/**
 * \brief VC�жϴ������̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_vc   ָ��VC�Ĵ���ָ��
 * \param[in] vc_init_t vc��Ϣ��ʼ���ṹ��
 * \param[in] pfn_cb_t  �жϴ����ص�����
 *
 */
void demo_zlg118_hw_vc_int_entry (void    *p_hw_vc,
                                  void   (*pfn_cb_t) (void *),
                                  void    *p_hw_dac,
                                  uint16_t vol_val);

/**
 * \brief VC�жϴ������̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_vc   ָ��VC�Ĵ���ָ��
 * \param[in] vc_init_t vc��Ϣ��ʼ���ṹ��
 * \param[in] pfn_cb_t  �жϴ����ص�����
 *
 */
void demo_zsn700_hw_vc_int_entry (void    *p_hw_vc,
                                  void   (*pfn_cb_t) (void *),
                                  void    *p_hw_dac,
                                  uint16_t vol_val);

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ���ָ��
 *
 * \return ��
 */
void demo_zlg118_hw_lvd_system_reset_entry (void *p_hw_lvd);

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ���ָ��
 *
 * \return ��
 */
void demo_zsn700_hw_lvd_system_reset_entry (void *p_hw_lvd);

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ���ָ��
 * \param[in] p_lvd_cb : �û��ص�����
 *
 * \return ��
 */
void demo_zlg118_hw_lvd_int_entry (void *p_hw_lvd,
                                   void (*p_lvd_cb)(void *));

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ���ָ��
 * \param[in] p_lvd_cb : �û��ص�����
 *
 * \return ��
 */
void demo_zsn700_hw_lvd_int_entry (void *p_hw_lvd,
                                   void (*p_lvd_cb)(void *));

/**
 * \brief OPA ��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa :ָ��OPA�Ĵ���ָ��
 * \param[in] mode     :OPA����ģʽ
 *
 * \retval :��
 */
void demo_zlg118_hw_opa_one_entry (void *p_hw_opa, uint8_t mode);

/**
 * \brief OPA ��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa :ָ��OPA�Ĵ���ָ��
 * \param[in] mode     :OPA����ģʽ
 *
 * \retval :��
 */
void demo_zsn700_hw_opa_one_entry (void *p_hw_opa, uint8_t mode);

/**
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa :ָ��OPA�Ĵ���ָ��
 * \param[in] p_hw_dac :ָ��DAC�Ĵ���ָ��
 * \param[in] mode     :OPA����ģʽ
 * \param[in] vol_val  :DAC���õ�ѹֵ
 *
 * \retval :��
 */
void demo_zlg118_hw_opa_dac_entry (void     *p_hw_opa,
                                   void     *p_hw_dac,
                                   uint8_t   mode,
                                   uint16_t *vol_val);

/**
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa :ָ��OPA�Ĵ���ָ��
 * \param[in] p_hw_dac :ָ��DAC�Ĵ���ָ��
 * \param[in] mode     :OPA����ģʽ
 * \param[in] vol_val  :DAC���õ�ѹֵ
 *
 * \retval :��
 */
void demo_zsn700_hw_opa_dac_entry (void     *p_hw_opa,
                                   void     *p_hw_dac,
                                   uint8_t   mode,
                                   uint16_t *vol_val);

/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_aes   :ָ��AES�Ĵ���ָ��
 * \param[in] key_len    :��Կ����
 * \param[in] p_aes_data :AES��������
 * \param[in] p_key_data  :AES��Կ
 *
 * \retval :��
 */
void demo_zlg118_hw_aes_ency_decy_entry (void     *p_hw_aes,
                                         uint8_t   key_len,
                                         uint32_t *p_aes_data,
                                         uint32_t *p_key_data);

/**
 * \brief AES ���ܽ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_aes   :ָ��AES�Ĵ���ָ��
 * \param[in] key_len    :��Կ����
 * \param[in] p_aes_data :AES��������
 * \param[in] p_key_data  :AES��Կ
 *
 * \retval :��
 */
void demo_zsn700_hw_aes_ency_decy_entry (void     *p_hw_aes,
                                         uint8_t   key_len,
                                         uint32_t *p_aes_data,
                                         uint32_t *p_key_data);

/**
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_trng   :ָ��TRNG�Ĵ���ָ��
 *
 * \retval :��
 */
void demo_zlg118_hw_trng_generate_entry (void *p_hw_trng);

/**
 * \brief TRNG ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_trng   :ָ��TRNG�Ĵ���ָ��
 *
 * \retval :��
 */
void demo_zsn700_hw_trng_generate_entry (void *p_hw_trng);

/**
 * \brief LCD ��ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_lcd   :ָ��lcd�Ĵ���ָ��
 * \param[in] p_data     :LCD��ʾ����
 *
 * \retval :��
 */
void demo_zlg118_hw_lcd_entry (void                    *p_hw_lcd,
                               uint32_t                *p_data);

/**
 * \brief LCD ��ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_lcd   :ָ��lcd�Ĵ���ָ��
 * \param[in] p_data     :LCD��ʾ����
 *
 * \retval :��
 */
void demo_zsn700_hw_lcd_entry (void                    *p_hw_lcd,
                               uint32_t                *p_data);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_ZLG_ENTRIES_H */

/* end of file */
