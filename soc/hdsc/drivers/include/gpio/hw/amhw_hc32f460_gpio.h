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
 * \brief GPIO Ӳ�������ӿ�
 *
 * 1. GPIO �����ܹ�ͨ���������Ϊ���������
 * 2. ����GPIO ����Ĭ��Ϊ���룬�ڸ�λʱ�жϽ��ܣ�
 * 3. ���żĴ����������ŵ������û���ͬʱ���á�
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

#ifndef __AMHW_HC32F460_GPIO_H
#define __AMHW_HC32F460_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "hc32f460_intctrl.h"
/**
 * \addtogroup amhw_hc32f460_if_gpio
 * \copydoc amhw_hc32f460_gpio.h
 * @{
 */

/**
 * \name GPIO �˿ڱ��
 * @{
 */


/**
 *******************************************************************************
 ** \brief GPIO Port Index enumeration
 ******************************************************************************/
typedef enum en_portx
{
    AMHW_HC32F460_GPIO_PORT_A = 0,                  /**< \brief port group A */
    AMHW_HC32F460_GPIO_PORT_B = 1,                  /**< \brief port group B */
    AMHW_HC32F460_GPIO_PORT_C = 2,                  /**< \brief port group C */
    AMHW_HC32F460_GPIO_PORT_D = 3,                  /**< \brief port group D */
    AMHW_HC32F460_GPIO_PORT_E = 4,                  /**< \brief port group E */
    AMHW_HC32F460_GPIO_PORT_H = 5,                  /**< \brief port group H */
}en_portx_t;

/** @} */
 
/**
 * \name GPIO ���ŵ�ƽ
 * @{
 */
#define AMHW_HC32F460_GPIO_LEVEL_LOW     0        /**< \brief �͵�ƽ */
#define AMHW_HC32F460_GPIO_LEVEL_HIGH    1        /**< \brief �ߵ�ƽ */
/** @} */

/* ʹ�������ṹ�������������Ŀ�ʼ */
#if defined(__CC_ARM)
    #pragma push
    #pragma anon_unions
#elif defined(__ICCARM__)
    #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
    #pragma warning 586
#else
    #warning Not supported compiler t
#endif

/**
 * \brief gpio�����жϴ�����ʽ����
 */
typedef enum amhw_hc32f460_gpio_trig_mode {
    AMHW_HC32F460_PINT_TRIGGER_FALL       = 0x0,   /**< \brief �½��ش���*/
    AMHW_HC32F460_PINT_TRIGGER_RISE       = 0x1,   /**< \brief �����ش���*/
    AMHW_HC32F460_PINT_TRIGGER_BOTH_EDGES = 0x2,   /**< \brief ˫���ش���*/
    AMHW_HC32F460_PINT_TRIGGER_LOW        = 0x3,   /**< \brief �͵�ƽ����*/
} amhw_hc32f460_pin_trig_mode_t;

/**
 * \brief GPIO����������·��Ӧ�ٶ�
 * \note ѡ���ö������GPIO����������·��Ӧ�ٶ�ʱ��GPIO����Ҳȷ��Ϊ�������
 */
typedef enum amhw_hc32f460_gpio_speed_mode {
    AMHW_HC32F460_GPIO_SPEED_LOW  = 0UL,
    AMHW_HC32F460_GPIO_SPEED_MID  = 1UL,
    AMHW_HC32F460_GPIO_SPEED_HIGH = 2UL
}amhw_hc32f460_gpio_speed_mode_t;

/**
 * \brief GPIO����ģʽ
 *
 * \note ������Ϊ���������ʱ�����в�ͬ��ģʽ
 */
typedef enum amhw_hc32f460_gpio_mode {
    
    /** \brief ��GPIO���ŵķ���Ϊ���뷽�����ž������¼���ģʽ */
    AMHW_HC32F460_GPIO_MODE_AIN = 0x00,         /**< \brief ģ������ģʽ     */
    AMHW_HC32F460_GPIO_MODE_IN_FLOATING = 0x01, /**< \brief ��������ģʽ     */
    AMHW_HC32F460_GPIO_MODE_IPD = 0x02,         /**< \brief ��������ģʽ     */
    AMHW_HC32F460_GPIO_MODE_IPU = 0x03,         /**< \brief ��������ģʽ     */

    /** \brief ��GPIO���ŵķ���Ϊ����������ž������¼���ģʽ */
    AMHW_HC32F460_GPIO_MODE_OUT_PP = 0x04,      /**< \brief ͨ���������ģʽ */
    AMHW_HC32F460_GPIO_MODE_OUT_OD = 0x05,      /**< \brief ͨ�ÿ�©���ģʽ */    
    AMHW_HC32F460_GPIO_MODE_AOUT   = 0x06,      /**< \brief ģ�����ģʽ */
    AMHW_HC32F460_GPIO_MODE_AF_PP  = 0x07,      /**< \brief �����������ģʽ */
    AMHW_HC32F460_GPIO_MODE_AF_OD  = 0x08       /**< \brief ���ÿ�©���ģʽ */
} amhw_hc32f460_gpio_mode_t;

/**
 *******************************************************************************
 ** \brief GPIO Function enumeration
 ******************************************************************************/
typedef enum amhw_hc32f460_gpio_afio
{
    AMHW_HC32F460_AFIO_GPIO       = 0u,               /**< \brief function set to gpio */
    AMHW_HC32F460_AFIO_FCMREF     = 1u,               /**< \brief function set to fcm reference */
    AMHW_HC32F460_AFIO_RTCOUT     = 1u,               /**< \brief function set to rtc output */
    AMHW_HC32F460_AFIO_VCOUT      = 1u,               /**< \brief function set to vc output */
    AMHW_HC32F460_AFIO_ADTRG      = 1u,               /**< \brief function set to adc trigger */
    AMHW_HC32F460_AFIO_MCLKOUT    = 1u,               /**< \brief function set to mclk output */
    AMHW_HC32F460_AFIO_TIM4       = 2u,               /**< \brief function set to timer4 */
    AMHW_HC32F460_AFIO_TIM6       = 3u,               /**< \brief function set to timer6 */
    AMHW_HC32F460_AFIO_TIMA0      = 4u,               /**< \brief function set to timerA */
    AMHW_HC32F460_AFIO_TIMA1      = 5u,               /**< \brief function set to timerA */
    AMHW_HC32F460_AFIO_TIMA2      = 6u,               /**< \brief function set to timerA */
    AMHW_HC32F460_AFIO_EMB        = 6u,               /**< \brief function set to emb */
    AMHW_HC32F460_AFIO_USART_CK   = 7u,               /**< \brief function set to usart clk */
    AMHW_HC32F460_AFIO_SPI_NSS    = 7u,               /**< \brief function set to spi nss */
    AMHW_HC32F460_AFIO_QSPI       = 7u,               /**< \brief function set to qspi */
    AMHW_HC32F460_AFIO_KEY        = 8u,               /**< \brief function set to key */
    AMHW_HC32F460_AFIO_SDIO       = 9u,               /**< \brief function set to sdio */
    AMHW_HC32F460_AFIO_I2S        = 10u,              /**< \brief function set to i2s */
    AMHW_HC32F460_AFIO_USBF       = 10u,              /**< \brief function set to usb full speed */
    AMHW_HC32F460_AFIO_EVNPT      = 14u,              /**< \brief function set to event port */
    AMHW_HC32F460_AFIO_EVENTOUT   = 15u,              /**< \brief function set to event out */
    AMHW_HC32F460_AFIO_USART1_TX  = 32u,              /**< \brief function set to usart tx of ch.1 */
    AMHW_HC32F460_AFIO_USART3_TX  = 32u,              /**< \brief function set to usart tx of ch.3 */
    AMHW_HC32F460_AFIO_USART1_RX  = 33u,              /**< \brief function set to usart rx of ch.1 */
    AMHW_HC32F460_AFIO_USART3_RX  = 33u,              /**< \brief function set to usart rx of ch.3 */
    AMHW_HC32F460_AFIO_USART1_RTS = 34u,              /**< \brief function set to usart rts of ch.1 */
    AMHW_HC32F460_AFIO_USART3_RTS = 34u,              /**< \brief function set to usart rts of ch.3 */
    AMHW_HC32F460_AFIO_USART1_CTS = 35u,              /**< \brief function set to usart cts of ch.1 */
    AMHW_HC32F460_AFIO_USART3_CTS = 35u,              /**< \brief function set to usart cts of ch.3 */
    AMHW_HC32F460_AFIO_USART2_TX  = 36u,              /**< \brief function set to usart tx of ch.2 */
    AMHW_HC32F460_AFIO_USART4_TX  = 36u,              /**< \brief function set to usart tx of ch.4 */
    AMHW_HC32F460_AFIO_USART2_RX  = 37u,              /**< \brief function set to usart rx of ch.2 */
    AMHW_HC32F460_AFIO_USART4_RX  = 37u,              /**< \brief function set to usart rx of ch.4 */
    AMHW_HC32F460_AFIO_USART2_RTS = 38u,              /**< \brief function set to usart rts of ch.2 */
    AMHW_HC32F460_AFIO_USART4_RTS = 38u,              /**< \brief function set to usart rts of ch.4 */
    AMHW_HC32F460_AFIO_USART2_CTS = 39u,              /**< \brief function set to usart cts of ch.2 */
    AMHW_HC32F460_AFIO_USART4_CTS = 39u,              /**< \brief function set to usart cts of ch.4 */
    AMHW_HC32F460_AFIO_SPI1_MOSI  = 40u,              /**< \brief function set to spi mosi of ch.1 */
    AMHW_HC32F460_AFIO_SPI3_MOSI  = 40u,              /**< \brief function set to spi mosi of ch.3 */
    AMHW_HC32F460_AFIO_SPI1_MISO  = 41u,              /**< \brief function set to spi miso of ch.1 */
    AMHW_HC32F460_AFIO_SPI3_MISO  = 41u,              /**< \brief function set to spi miso of ch.3 */
    AMHW_HC32F460_AFIO_SPI1_NSS0  = 42u,              /**< \brief function set to spi nss0 of ch.1 */
    AMHW_HC32F460_AFIO_SPI3_NSS0  = 42u,              /**< \brief function set to spi nss0 of ch.3 */
    AMHW_HC32F460_AFIO_SPI1_SCK   = 43u,              /**< \brief function set to spi sck of ch.1 */
    AMHW_HC32F460_AFIO_SPI3_SCK   = 43u,              /**< \brief function set to spi sck of ch.3 */
    AMHW_HC32F460_AFIO_SPI2_MOSI  = 44u,              /**< \brief function set to spi mosi of ch.2 */
    AMHW_HC32F460_AFIO_SPI4_MOSI  = 44u,              /**< \brief function set to spi mosi of ch.2 */
    AMHW_HC32F460_AFIO_SPI2_MISO  = 45u,              /**< \brief function set to spi miso of ch.4 */
    AMHW_HC32F460_AFIO_SPI4_MISO  = 45u,              /**< \brief function set to spi miso of ch.4 */
    AMHW_HC32F460_AFIO_SPI2_NSS0  = 46u,              /**< \brief function set to spi nss0 of ch.2 */
    AMHW_HC32F460_AFIO_SPI4_NSS0  = 46u,              /**< \brief function set to spi nss0 of ch.4 */
    AMHW_HC32F460_AFIO_SPI2_SCK   = 47u,              /**< \brief function set to spi sck of ch.2 */
    AMHW_HC32F460_AFIO_SPI4_SCK   = 47u,              /**< \brief function set to spi sck of ch.4 */
    AMHW_HC32F460_AFIO_I2C1_SDA   = 48u,              /**< \brief function set to i2c sda of ch.1 */
    AMHW_HC32F460_AFIO_I2C3_SDA   = 48u,              /**< \brief function set to i2c sda of ch.3 */
    AMHW_HC32F460_AFIO_I2C1_SCL   = 49u,              /**< \brief function set to i2c scl of ch.1 */
    AMHW_HC32F460_AFIO_I2C3_SCL   = 49u,              /**< \brief function set to i2c scl of ch.3 */
    AMHW_HC32F460_AFIO_I2C2_SDA   = 50u,              /**< \brief function set to i2c sda of ch.2 */
    AMHW_HC32F460_AFIO_CAN1_TX    = 50u,              /**< \brief function set to can tx of ch.1 */
    AMHW_HC32F460_AFIO_I2C2_SCL   = 51u,              /**< \brief function set to i2c scl of ch.2 */
    AMHW_HC32F460_AFIO_CAN1_RX    = 51u,              /**< \brief function set to can rx of ch.1 */
    AMHW_HC32F460_AFIO_I2S1_SD    = 52u,              /**< \brief function set to i2s sd of ch.1 */
    AMHW_HC32F460_AFIO_I2S3_SD    = 52u,              /**< \brief function set to i2s sd of ch.3 */
    AMHW_HC32F460_AFIO_I2S1_SDIN  = 53u,              /**< \brief function set to i2s sdin of ch.1 */
    AMHW_HC32F460_AFIO_I2S3_SDIN  = 53u,              /**< \brief function set to i2s sdin of ch.3 */
    AMHW_HC32F460_AFIO_I2S1_WS    = 54u,              /**< \brief function set to i2s ws of ch.1 */
    AMHW_HC32F460_AFIO_I2S3_WS    = 54u,              /**< \brief function set to i2s ws of ch.3 */
    AMHW_HC32F460_AFIO_I2S1_CK    = 55u,              /**< \brief function set to i2s ck of ch.1 */
    AMHW_HC32F460_AFIO_I2S3_CK    = 55u,              /**< \brief function set to i2s ck of ch.3 */
    AMHW_HC32F460_AFIO_I2S2_SD    = 56u,              /**< \brief function set to i2s sd of ch.2 */
    AMHW_HC32F460_AFIO_I2S4_SD    = 56u,              /**< \brief function set to i2s sd of ch.4 */
    AMHW_HC32F460_AFIO_I2S2_SDIN  = 57u,              /**< \brief function set to i2s sdin of ch.2 */
    AMHW_HC32F460_AFIO_I2S4_SDIN  = 57u,              /**< \brief function set to i2s sdin of ch.4 */
    AMHW_HC32F460_AFIO_I2S2_WS    = 58u,              /**< \brief function set to i2s ws of ch.2 */
    AMHW_HC32F460_AFIO_I2S4_WS    = 58u,              /**< \brief function set to i2s ws of ch.4 */
    AMHW_HC32F460_AFIO_I2S2_CK    = 59u,              /**< \brief function set to i2s ck of ch.2 */
    AMHW_HC32F460_AFIO_I2S4_CK    = 59u,              /**< \brief function set to i2s ck of ch.4 */
}amhw_hc32f460_gpio_afio_t;

/**
 * \brief GPIOͨ������Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t PIN00                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN01                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN02                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN03                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN04                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN05                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN06                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN07                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN08                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN09                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN10                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN11                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN12                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN13                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN14                     : 1;  /** <brief ����״̬ */
    __IO uint16_t PIN15                     : 1;  /** <brief ����״̬ */
} amhw_hc32f460_port_pidr_field_t;

/**
 * \brief GPIOͨ��������ݼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t POUT00                    : 1;  /** <brief ������� */
    __IO uint16_t POUT01                    : 1;  /** <brief ������� */
    __IO uint16_t POUT02                    : 1;  /** <brief ������� */
    __IO uint16_t POUT03                    : 1;  /** <brief ������� */
    __IO uint16_t POUT04                    : 1;  /** <brief ������� */
    __IO uint16_t POUT05                    : 1;  /** <brief ������� */
    __IO uint16_t POUT06                    : 1;  /** <brief ������� */
    __IO uint16_t POUT07                    : 1;  /** <brief ������� */
    __IO uint16_t POUT08                    : 1;  /** <brief ������� */
    __IO uint16_t POUT09                    : 1;  /** <brief ������� */
    __IO uint16_t POUT10                    : 1;  /** <brief ������� */
    __IO uint16_t POUT11                    : 1;  /** <brief ������� */
    __IO uint16_t POUT12                    : 1;  /** <brief ������� */
    __IO uint16_t POUT13                    : 1;  /** <brief ������� */
    __IO uint16_t POUT14                    : 1;  /** <brief ������� */
    __IO uint16_t POUT15                    : 1;  /** <brief ������� */
} amhw_hc32f460_port_podr_field_t;

/**
 * \brief GPIOͨ�������ɼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t POUTE00                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE01                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE02                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE03                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE04                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE05                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE06                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE07                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE08                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE09                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE10                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE11                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE12                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE13                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE14                   : 1;  /** <brief ������ */
    __IO uint16_t POUTE15                   : 1;  /** <brief ������ */
} amhw_hc32f460_port_poer_field_t;

/**
 * \brief GPIOͨ�������λ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t POS00                     : 1;  /** <brief ����� */
    __IO uint16_t POS01                     : 1;  /** <brief ����� */
    __IO uint16_t POS02                     : 1;  /** <brief ����� */
    __IO uint16_t POS03                     : 1;  /** <brief ����� */
    __IO uint16_t POS04                     : 1;  /** <brief ����� */
    __IO uint16_t POS05                     : 1;  /** <brief ����� */
    __IO uint16_t POS06                     : 1;  /** <brief ����� */
    __IO uint16_t POS07                     : 1;  /** <brief ����� */
    __IO uint16_t POS08                     : 1;  /** <brief ����� */
    __IO uint16_t POS09                     : 1;  /** <brief ����� */
    __IO uint16_t POS10                     : 1;  /** <brief ����� */
    __IO uint16_t POS11                     : 1;  /** <brief ����� */
    __IO uint16_t POS12                     : 1;  /** <brief ����� */
    __IO uint16_t POS13                     : 1;  /** <brief ����� */
    __IO uint16_t POS14                     : 1;  /** <brief ����� */
    __IO uint16_t POS15                     : 1;  /** <brief ����� */
} amhw_hc32f460_port_posr_field_t;

/**
 * \brief GPIOͨ�������λ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t POR00                     : 1;  /** <brief ����� */
    __IO uint16_t POR01                     : 1;  /** <brief ����� */
    __IO uint16_t POR02                     : 1;  /** <brief ����� */
    __IO uint16_t POR03                     : 1;  /** <brief ����� */
    __IO uint16_t POR04                     : 1;  /** <brief ����� */
    __IO uint16_t POR05                     : 1;  /** <brief ����� */
    __IO uint16_t POR06                     : 1;  /** <brief ����� */
    __IO uint16_t POR07                     : 1;  /** <brief ����� */
    __IO uint16_t POR08                     : 1;  /** <brief ����� */
    __IO uint16_t POR09                     : 1;  /** <brief ����� */
    __IO uint16_t POR10                     : 1;  /** <brief ����� */
    __IO uint16_t POR11                     : 1;  /** <brief ����� */
    __IO uint16_t POR12                     : 1;  /** <brief ����� */
    __IO uint16_t POR13                     : 1;  /** <brief ����� */
    __IO uint16_t POR14                     : 1;  /** <brief ����� */
    __IO uint16_t POR15                     : 1;  /** <brief ����� */
} amhw_hc32f460_port_porr_field_t;

/**
 * \brief GPIOͨ�������ת�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t POT00                     : 1;  /** <brief �����ת */
    __IO uint16_t POT01                     : 1;  /** <brief �����ת */
    __IO uint16_t POT02                     : 1;  /** <brief �����ת */
    __IO uint16_t POT03                     : 1;  /** <brief �����ת */
    __IO uint16_t POT04                     : 1;  /** <brief �����ת */
    __IO uint16_t POT05                     : 1;  /** <brief �����ת */
    __IO uint16_t POT06                     : 1;  /** <brief �����ת */
    __IO uint16_t POT07                     : 1;  /** <brief �����ת */
    __IO uint16_t POT08                     : 1;  /** <brief �����ת */
    __IO uint16_t POT09                     : 1;  /** <brief �����ת */
    __IO uint16_t POT10                     : 1;  /** <brief �����ת */
    __IO uint16_t POT11                     : 1;  /** <brief �����ת */
    __IO uint16_t POT12                     : 1;  /** <brief �����ת */
    __IO uint16_t POT13                     : 1;  /** <brief �����ת */
    __IO uint16_t POT14                     : 1;  /** <brief �����ת */
    __IO uint16_t POT15                     : 1;  /** <brief �����ת */
} amhw_hc32f460_port_potr_field_t;

typedef struct
{
    __IO uint16_t PIN00                     : 1;
    __IO uint16_t PIN01                     : 1;
    __IO uint16_t PIN02                     : 1;
    uint16_t RESERVED3                      :13;
} amhw_hc32f460_port_pidrh_field_t;

typedef struct
{
    __IO uint16_t POUT00                    : 1;
    __IO uint16_t POUT01                    : 1;
    __IO uint16_t POUT02                    : 1;
    uint16_t RESERVED3                      :13;
} amhw_hc32f460_port_podrh_field_t;

typedef struct
{
    __IO uint16_t POUTE00                   : 1;
    __IO uint16_t POUTE01                   : 1;
    __IO uint16_t POUTE02                   : 1;
    uint16_t RESERVED3                      :13;
} AMHW_HC32F460_port_poerh_field_t;

typedef struct
{
    __IO uint16_t POS00                     : 1;
    __IO uint16_t POS01                     : 1;
    __IO uint16_t POS02                     : 1;
    uint16_t RESERVED3                      :13;
} amhw_hc32f460_port_posrh_field_t;

typedef struct
{
    __IO uint16_t POR00                     : 1;
    __IO uint16_t POR01                     : 1;
    __IO uint16_t POR02                     : 1;
    uint16_t RESERVED3                      :13;
} amhw_hc32f460_port_porrh_field_t;

typedef struct
{
    __IO uint16_t POT00                     : 1;
    __IO uint16_t POT01                     : 1;
    __IO uint16_t POT02                     : 1;
    uint16_t RESERVED3                      :13;
} amhw_hc32f460_port_potrh_field_t;

/**
 * \brief GPIO������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t SPFE                      : 5;  /** <brief ���⹦��ѡ�� */
    uint16_t RESERVED5                      :11;  /** <brief ���� */
} amhw_hc32f460_port_pspcr_field_t;

/**
 * \brief GPIO�������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t BFSEL                     : 4;  /** <brief ������ѡ�� */
    uint16_t RESERVED4                      :10;  /** <brief ���� */
    __IO uint16_t RDWT                      : 2;  /** <brief ���˿ڵȴ� */
} amhw_hc32f460_port_pccr_field_t;

/**
 * \brief GPIO������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t PINAE                     : 6;  /** <brief ���볣�� */
    uint16_t RESERVED6                      :10;  /** <brief ���� */
} amhw_hc32f460_port_pinaer_field_t;

/**
 * \brief GPIOд�����Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t WE                        : 1;  /** <brief д��� */
    uint16_t RESERVED1                      : 7;  /** <brief ���� */
    __IO uint16_t WP                        : 8;  /** <brief д������ */
} amhw_hc32f460_port_pwpr_field;

/**
 * \brief GPIOͨ�ÿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t POUT                      : 1;  /** <brief ������� */
    __IO uint16_t POUTE                     : 1;  /** <brief ������ */
    __IO uint16_t NOD                       : 1;  /** <brief NMOS��© */
    uint16_t RESERVED3                      : 1;  /** <brief ���� */
    __IO uint16_t DRV                       : 2;  /** <brief ����ģʽѡ�� */
    __IO uint16_t PUU                       : 1;  /** <brief ������� */
    uint16_t RESERVED7                      : 1;  /** <brief ���� */
    __IO uint16_t PIN                       : 1;  /** <brief ����״̬ */
    __IO uint16_t INVE                      : 1;  /** <brief ������� */
    uint16_t RESERVED10                     : 2;  /** <brief ���� */
    __IO uint16_t INTE                      : 1;  /** <brief �ⲿ�ж���� */
    uint16_t RESERVED13                     : 1;  /** <brief ���� */
    __IO uint16_t LTE                       : 1;  /** <brief ���״̬����*/
    __IO uint16_t DDIS                      : 1;  /** <brief ���ֹ��ܽ�ֹ */
} amhw_hc32f460_port_pcr_field_t;

/**
 * \brief GPIO����ѡ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t FSEL                      : 6;  /** <brief ����ѡ�� */
    uint16_t RESERVED6                      : 2;  /** <brief ���� */
    __IO uint16_t BFE                       : 1;  /** <brief ��������� */
    uint16_t RESERVED9                      : 7;  /** <brief ���� */
} amhw_hc32f460_port_pfsr_field_t;

/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_hc32f460_gpio {
    union
    {
        __IO uint16_t PIDRA;                    /**< \brief ͨ���������ݼĴ���A */
        amhw_hc32f460_port_pidr_field_t PIDRA_f;
    };
    uint8_t RESERVED1[2];                       /**< \brief ���� */
    union
    {
        __IO uint16_t PODRA;                    /**< \brief ͨ��������ݼĴ���A */
        amhw_hc32f460_port_podr_field_t PODRA_f;
    };
    union
    {
        __IO uint16_t POERA;                    /**< \brief ͨ�������ɼĴ���A */
        amhw_hc32f460_port_poer_field_t POERA_f;
    };
    union
    {
        __IO uint16_t POSRA;                    /**< \brief ͨ�������λ�Ĵ���A */
        amhw_hc32f460_port_posr_field_t POSRA_f;
    };
    union
    {
        __IO uint16_t PORRA;                    /**< \brief ͨ�������λ�Ĵ���A */
        amhw_hc32f460_port_porr_field_t PORRA_f;
    };
    union
    {
        __IO uint16_t POTRA;                    /**< \brief ͨ�������ת�Ĵ���A */
        amhw_hc32f460_port_potr_field_t POTRA_f;
    };
    uint8_t RESERVED6[2];                       /**< \brief ���� */
    union
    {
        __IO uint16_t PIDRB;                    /**< \brief ͨ���������ݼĴ���B */
        amhw_hc32f460_port_pidr_field_t PIDRB_f;
    };
    uint8_t RESERVED7[2];                       /**< \brief ���� */
    union
    {
        __IO uint16_t PODRB;                    /**< \brief ͨ��������ݼĴ���B */
        amhw_hc32f460_port_podr_field_t PODRB_f;
    };
    union
    {
        __IO uint16_t POERB;                    /**< \brief ͨ�������ɼĴ���B */
        amhw_hc32f460_port_poer_field_t POERB_f;
    };
    union
    {
        __IO uint16_t POSRB;                    /**< \brief ͨ�������λ�Ĵ���B */
        amhw_hc32f460_port_posr_field_t POSRB_f;
    };
    union
    {
        __IO uint16_t PORRB;                    /**< \brief ͨ�������λ�Ĵ���B */
        amhw_hc32f460_port_porr_field_t PORRB_f;
    };
    union
    {
        __IO uint16_t POTRB;                    /**< \brief ͨ�������ת�Ĵ���B */
        amhw_hc32f460_port_potr_field_t POTRB_f;
    };
    uint8_t RESERVED12[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PIDRC;                    /**< \brief ͨ���������ݼĴ���C */
        amhw_hc32f460_port_pidr_field_t PIDRC_f;
    };
    uint8_t RESERVED13[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PODRC;                    /**< \brief ͨ��������ݼĴ���C */
        amhw_hc32f460_port_podr_field_t PODRC_f;
    };
    union
    {
        __IO uint16_t POERC;                    /**< \brief ͨ�������ɼĴ���C */
        amhw_hc32f460_port_poer_field_t POERC_f;
    };
    union
    {
        __IO uint16_t POSRC;                    /**< \brief ͨ�������λ�Ĵ���C */
        amhw_hc32f460_port_posr_field_t POSRC_f;
    };
    union
    {
        __IO uint16_t PORRC;                    /**< \brief ͨ�������λ�Ĵ���C */
        amhw_hc32f460_port_porr_field_t PORRC_f;
    };
    union
    {
        __IO uint16_t POTRC;                    /**< \brief ͨ�������ת�Ĵ���C */
        amhw_hc32f460_port_potr_field_t POTRC_f;
    };
    uint8_t RESERVED18[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PIDRD;                    /**< \brief ͨ���������ݼĴ���D */
        amhw_hc32f460_port_pidr_field_t PIDRD_f;
    };
    uint8_t RESERVED19[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PODRD;                    /**< \brief ͨ��������ݼĴ���D */
        amhw_hc32f460_port_podr_field_t PODRD_f;
    };
    union
    {
        __IO uint16_t POERD;                    /**< \brief ͨ�������ɼĴ���D */
        amhw_hc32f460_port_poer_field_t POERD_f;
    };
    union
    {
        __IO uint16_t POSRD;                    /**< \brief ͨ�������λ�Ĵ���D */
        amhw_hc32f460_port_posr_field_t POSRD_f;
    };
    union
    {
        __IO uint16_t PORRD;                    /**< \brief ͨ�������λ�Ĵ���D */
        amhw_hc32f460_port_porr_field_t PORRD_f;
    };
    union
    {
        __IO uint16_t POTRD;                    /**< \brief ͨ�������ת�Ĵ���D */
        amhw_hc32f460_port_potr_field_t POTRD_f;
    };
    uint8_t RESERVED24[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PIDRE;                    /**< \brief ͨ���������ݼĴ���E */
        amhw_hc32f460_port_pidr_field_t PIDRE_f;
    };
    uint8_t RESERVED25[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PODRE;                    /**< \brief ͨ��������ݼĴ���E */
        amhw_hc32f460_port_podr_field_t PODRE_f;
    };
    union
    {
        __IO uint16_t POERE;                    /**< \brief ͨ�������ɼĴ���E */
        amhw_hc32f460_port_poer_field_t POERE_f;
    };
    union
    {
        __IO uint16_t POSRE;                    /**< \brief ͨ�������λ�Ĵ���E */
        amhw_hc32f460_port_posr_field_t POSRE_f;
    };
    union
    {
        __IO uint16_t PORRE;                    /**< \brief ͨ�������λ�Ĵ���E */
        amhw_hc32f460_port_porr_field_t PORRE_f;
    };
    union
    {
        __IO uint16_t POTRE;                    /**< \brief ͨ�������ת�Ĵ���E */
        amhw_hc32f460_port_potr_field_t POTRE_f;
    };
    uint8_t RESERVED30[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PIDRH;                    /**< \brief ͨ���������ݼĴ���H */
        amhw_hc32f460_port_pidrh_field_t PIDRH_f;
    };
    uint8_t RESERVED31[2];                      /**< \brief ���� */
    union
    {
        __IO uint16_t PODRH;                    /**< \brief ͨ��������ݼĴ���H */
        amhw_hc32f460_port_podrh_field_t PODRH_f;
    };
    union
    {
        __IO uint16_t POERH;                    /**< \brief ͨ�������ɼĴ���H */
        AMHW_HC32F460_port_poerh_field_t POERH_f;
    };
    union
    {
        __IO uint16_t POSRH;                   /**< \brief ͨ�������λ�Ĵ���H */
        amhw_hc32f460_port_posrh_field_t POSRH_f;
    };
    union
    {
        __IO uint16_t PORRH;                   /**< \brief ͨ�������λ�Ĵ���H */
        amhw_hc32f460_port_porrh_field_t PORRH_f;
    };
    union
    {
        __IO uint16_t POTRH;                   /**< \brief ͨ�������ת�Ĵ���H */
        amhw_hc32f460_port_potrh_field_t POTRH_f;
    };
    uint8_t RESERVED36[918];                   /**< \brief ���� */
    union
    {
        __IO uint16_t PSPCR;                   /**< \brief ������ƼĴ��� */
        amhw_hc32f460_port_pspcr_field_t PSPCR_f;
    };
    uint8_t RESERVED37[2];                     /**< \brief ���� */
    union
    {
        __IO uint16_t PCCR;                    /**< \brief �������ƼĴ��� */
        amhw_hc32f460_port_pccr_field_t PCCR_f;
    };
    union
    {
        __IO uint16_t PINAER;                  /**< \brief ������ƼĴ��� */
        amhw_hc32f460_port_pinaer_field_t PINAER_f;
    };
    union
    {
        __IO uint16_t PWPR;                    /**< \brief д�����Ĵ��� */
        amhw_hc32f460_port_pwpr_field PWPR_f;
    };
    uint8_t RESERVED40[2];                     /**< \brief ���� */
    union
    {
        __IO uint16_t PCRA0;                   /**< \brief ͨ�ÿ��ƼĴ���A0 */
        amhw_hc32f460_port_pcr_field_t PCRA0_f;
    };
    union
    {
        __IO uint16_t PFSRA0;                  /**< \brief ����ѡ��Ĵ��� A0*/
        amhw_hc32f460_port_pfsr_field_t PFSRA0_f;
    };
    union
    {
        __IO uint16_t PCRA1;                   /**< \brief ͨ�ÿ��ƼĴ���A1 */
        amhw_hc32f460_port_pcr_field_t PCRA1_f;
    };
    union
    {
        __IO uint16_t PFSRA1;                  /**< \brief ����ѡ��Ĵ��� A1*/
        amhw_hc32f460_port_pfsr_field_t PFSRA1_f;
    };
    union
    {
        __IO uint16_t PCRA2;                   /**< \brief ͨ�ÿ��ƼĴ���A2 */
        amhw_hc32f460_port_pcr_field_t PCRA2_f;
    };
    union
    {
        __IO uint16_t PFSRA2;                  /**< \brief ����ѡ��Ĵ��� A2*/
        amhw_hc32f460_port_pfsr_field_t PFSRA2_f;
    };
    union
    {
        __IO uint16_t PCRA3;                   /**< \brief ͨ�ÿ��ƼĴ���A3 */
        amhw_hc32f460_port_pcr_field_t PCRA3_f;
    };
    union
    {
        __IO uint16_t PFSRA3;                  /**< \brief ����ѡ��Ĵ��� A3*/
        amhw_hc32f460_port_pfsr_field_t PFSRA3_f;
    };
    union
    {
        __IO uint16_t PCRA4;                   /**< \brief ͨ�ÿ��ƼĴ���A4 */
        amhw_hc32f460_port_pcr_field_t PCRA4_f;
    };
    union
    {
        __IO uint16_t PFSRA4;                  /**< \brief ����ѡ��Ĵ���A4 */
        amhw_hc32f460_port_pfsr_field_t PFSRA4_f;
    };
    union
    {
        __IO uint16_t PCRA5;                   /**< \brief ͨ�ÿ��ƼĴ���A5 */
        amhw_hc32f460_port_pcr_field_t PCRA5_f;
    };
    union
    {
        __IO uint16_t PFSRA5;                  /**< \brief ����ѡ��Ĵ���A5 */
        amhw_hc32f460_port_pfsr_field_t PFSRA5_f;
    };
    union
    {
        __IO uint16_t PCRA6;                   /**< \brief ͨ�ÿ��ƼĴ���A6 */
        amhw_hc32f460_port_pcr_field_t PCRA6_f;
    };
    union
    {
        __IO uint16_t PFSRA6;                  /**< \brief ����ѡ��Ĵ���A6 */
        amhw_hc32f460_port_pfsr_field_t PFSRA6_f;
    };
    union
    {
        __IO uint16_t PCRA7;                   /**< \brief ͨ�ÿ��ƼĴ���A7 */
        amhw_hc32f460_port_pcr_field_t PCRA7_f;
    };
    union
    {
        __IO uint16_t PFSRA7;                  /**< \brief ����ѡ��Ĵ���A7 */
        amhw_hc32f460_port_pfsr_field_t PFSRA7_f;
    };
    union
    {
        __IO uint16_t PCRA8;                   /**< \brief ͨ�ÿ��ƼĴ���A8 */
        amhw_hc32f460_port_pcr_field_t PCRA8_f;
    };
    union
    {
        __IO uint16_t PFSRA8;                  /**< \brief ����ѡ��Ĵ���A8 */
        amhw_hc32f460_port_pfsr_field_t PFSRA8_f;
    };
    union
    {
        __IO uint16_t PCRA9;                   /**< \brief ͨ�ÿ��ƼĴ���A9 */
        amhw_hc32f460_port_pcr_field_t PCRA9_f;
    };
    union
    {
        __IO uint16_t PFSRA9;                  /**< \brief ����ѡ��Ĵ���A9 */
        amhw_hc32f460_port_pfsr_field_t PFSRA9_f;
    };
    union
    {
        __IO uint16_t PCRA10;                  /**< \brief ͨ�ÿ��ƼĴ���A10 */
        amhw_hc32f460_port_pcr_field_t PCRA10_f;
    };
    union
    {
        __IO uint16_t PFSRA10;                 /**< \brief ����ѡ��Ĵ���A10 */
        amhw_hc32f460_port_pfsr_field_t PFSRA10_f;
    };
    union
    {
        __IO uint16_t PCRA11;                  /**< \brief ͨ�ÿ��ƼĴ���A11 */
        amhw_hc32f460_port_pcr_field_t PCRA11_f;
    };
    union
    {
        __IO uint16_t PFSRA11;                 /**< \brief ����ѡ��Ĵ���A11 */
        amhw_hc32f460_port_pfsr_field_t PFSRA11_f;
    };
    union
    {
        __IO uint16_t PCRA12;                  /**< \brief ͨ�ÿ��ƼĴ���A12 */
        amhw_hc32f460_port_pcr_field_t PCRA12_f;
    };
    union
    {
        __IO uint16_t PFSRA12;                 /**< \brief ����ѡ��Ĵ���A12 */
        amhw_hc32f460_port_pfsr_field_t PFSRA12_f;
    };
    union
    {
        __IO uint16_t PCRA13;                  /**< \brief ͨ�ÿ��ƼĴ���A13 */
        amhw_hc32f460_port_pcr_field_t PCRA13_f;
    };
    union
    {
        __IO uint16_t PFSRA13;                 /**< \brief ����ѡ��Ĵ���A13 */
        amhw_hc32f460_port_pfsr_field_t PFSRA13_f;
    };
    union
    {
        __IO uint16_t PCRA14;                  /**< \brief ͨ�ÿ��ƼĴ���A14 */
        amhw_hc32f460_port_pcr_field_t PCRA14_f;
    };
    union
    {
        __IO uint16_t PFSRA14;                 /**< \brief ����ѡ��Ĵ���A14 */
        amhw_hc32f460_port_pfsr_field_t PFSRA14_f;
    };
    union
    {
        __IO uint16_t PCRA15;                  /**< \brief ͨ�ÿ��ƼĴ���A15 */
        amhw_hc32f460_port_pcr_field_t PCRA15_f;
    };
    union
    {
        __IO uint16_t PFSRA15;                 /**< \brief ����ѡ��Ĵ���A15 */
        amhw_hc32f460_port_pfsr_field_t PFSRA15_f;
    };
    union
    {
        __IO uint16_t PCRB0;                   /**< \brief ͨ�ÿ��ƼĴ���B0 */
        amhw_hc32f460_port_pcr_field_t PCRB0_f;
    };
    union
    {
        __IO uint16_t PFSRB0;                  /**< \brief ����ѡ��Ĵ���B0 */
        amhw_hc32f460_port_pfsr_field_t PFSRB0_f;
    };
    union
    {
        __IO uint16_t PCRB1;                   /**< \brief ͨ�ÿ��ƼĴ���B1 */
        amhw_hc32f460_port_pcr_field_t PCRB1_f;
    };
    union
    {
        __IO uint16_t PFSRB1;                  /**< \brief ����ѡ��Ĵ���B1 */
        amhw_hc32f460_port_pfsr_field_t PFSRB1_f;
    };
    union
    {
        __IO uint16_t PCRB2;                   /**< \brief ͨ�ÿ��ƼĴ���B2 */
        amhw_hc32f460_port_pcr_field_t PCRB2_f;
    };
    union
    {
        __IO uint16_t PFSRB2;                  /**< \brief ����ѡ��Ĵ���B2 */
        amhw_hc32f460_port_pfsr_field_t PFSRB2_f;
    };
    union
    {
        __IO uint16_t PCRB3;                   /**< \brief ͨ�ÿ��ƼĴ���B3 */
        amhw_hc32f460_port_pcr_field_t PCRB3_f;
    };
    union
    {
        __IO uint16_t PFSRB3;                  /**< \brief ����ѡ��Ĵ���B3 */
        amhw_hc32f460_port_pfsr_field_t PFSRB3_f;
    };
    union
    {
        __IO uint16_t PCRB4;                   /**< \brief ͨ�ÿ��ƼĴ���B4 */
        amhw_hc32f460_port_pcr_field_t PCRB4_f;
    };
    union
    {
        __IO uint16_t PFSRB4;                  /**< \brief ����ѡ��Ĵ���B4 */
        amhw_hc32f460_port_pfsr_field_t PFSRB4_f;
    };
    union
    {
        __IO uint16_t PCRB5;                   /**< \brief ͨ�ÿ��ƼĴ���B5 */
        amhw_hc32f460_port_pcr_field_t PCRB5_f;
    };
    union
    {
        __IO uint16_t PFSRB5;                  /**< \brief ����ѡ��Ĵ���B5 */
        amhw_hc32f460_port_pfsr_field_t PFSRB5_f;
    };
    union
    {
        __IO uint16_t PCRB6;                   /**< \brief ͨ�ÿ��ƼĴ���B6 */
        amhw_hc32f460_port_pcr_field_t PCRB6_f;
    };
    union
    {
        __IO uint16_t PFSRB6;                  /**< \brief ����ѡ��Ĵ���B6 */
        amhw_hc32f460_port_pfsr_field_t PFSRB6_f;
    };
    union
    {
        __IO uint16_t PCRB7;                   /**< \brief ͨ�ÿ��ƼĴ���B7 */
        amhw_hc32f460_port_pcr_field_t PCRB7_f;
    };
    union
    {
        __IO uint16_t PFSRB7;                  /**< \brief ����ѡ��Ĵ���B7 */
        amhw_hc32f460_port_pfsr_field_t PFSRB7_f;
    };
    union
    {
        __IO uint16_t PCRB8;                   /**< \brief ͨ�ÿ��ƼĴ���B8 */
        amhw_hc32f460_port_pcr_field_t PCRB8_f;
    };
    union
    {
        __IO uint16_t PFSRB8;                  /**< \brief ����ѡ��Ĵ���B8 */
        amhw_hc32f460_port_pfsr_field_t PFSRB8_f;
    };
    union
    {
        __IO uint16_t PCRB9;                   /**< \brief ͨ�ÿ��ƼĴ���B9 */
        amhw_hc32f460_port_pcr_field_t PCRB9_f;
    };
    union
    {
        __IO uint16_t PFSRB9;                  /**< \brief ����ѡ��Ĵ���B9 */
        amhw_hc32f460_port_pfsr_field_t PFSRB9_f;
    };
    union
    {
        __IO uint16_t PCRB10;                  /**< \brief ͨ�ÿ��ƼĴ���B10 */
        amhw_hc32f460_port_pcr_field_t PCRB10_f;
    };
    union
    {
        __IO uint16_t PFSRB10;                 /**< \brief ����ѡ��Ĵ���B10 */
        amhw_hc32f460_port_pfsr_field_t PFSRB10_f;
    };
    union
    {
        __IO uint16_t PCRB11;                  /**< \brief ͨ�ÿ��ƼĴ���B11 */
        amhw_hc32f460_port_pcr_field_t PCRB11_f;
    };
    union
    {
        __IO uint16_t PFSRB11;                 /**< \brief ����ѡ��Ĵ���B11 */
        amhw_hc32f460_port_pfsr_field_t PFSRB11_f;
    };
    union
    {
        __IO uint16_t PCRB12;                  /**< \brief ͨ�ÿ��ƼĴ���B12 */
        amhw_hc32f460_port_pcr_field_t PCRB12_f;
    };
    union
    {
        __IO uint16_t PFSRB12;                 /**< \brief ����ѡ��Ĵ���B12 */
        amhw_hc32f460_port_pfsr_field_t PFSRB12_f;
    };
    union
    {
        __IO uint16_t PCRB13;                  /**< \brief ͨ�ÿ��ƼĴ���B13 */
        amhw_hc32f460_port_pcr_field_t PCRB13_f;
    };
    union
    {
        __IO uint16_t PFSRB13;                 /**< \brief ����ѡ��Ĵ���B13 */
        amhw_hc32f460_port_pfsr_field_t PFSRB13_f;
    };
    union
    {
        __IO uint16_t PCRB14;                  /**< \brief ͨ�ÿ��ƼĴ���B14 */
        amhw_hc32f460_port_pcr_field_t PCRB14_f;
    };
    union
    {
        __IO uint16_t PFSRB14;                 /**< \brief ����ѡ��Ĵ���B14 */
        amhw_hc32f460_port_pfsr_field_t PFSRB14_f;
    };
    union
    {
        __IO uint16_t PCRB15;                  /**< \brief ͨ�ÿ��ƼĴ���B15 */
        amhw_hc32f460_port_pcr_field_t PCRB15_f;
    };
    union
    {
        __IO uint16_t PFSRB15;                 /**< \brief ����ѡ��Ĵ���B15 */
        amhw_hc32f460_port_pfsr_field_t PFSRB15_f;
    };
    union
    {
        __IO uint16_t PCRC0;                   /**< \brief ͨ�ÿ��ƼĴ���C0 */
        amhw_hc32f460_port_pcr_field_t PCRC0_f;
    };
    union
    {
        __IO uint16_t PFSRC0;                  /**< \brief ����ѡ��Ĵ���C0 */
        amhw_hc32f460_port_pfsr_field_t PFSRC0_f;
    };
    union
    {
        __IO uint16_t PCRC1;                   /**< \brief ͨ�ÿ��ƼĴ���C1 */
        amhw_hc32f460_port_pcr_field_t PCRC1_f;
    };
    union
    {
        __IO uint16_t PFSRC1;                  /**< \brief ����ѡ��Ĵ���C1 */
        amhw_hc32f460_port_pfsr_field_t PFSRC1_f;
    };
    union
    {
        __IO uint16_t PCRC2;                   /**< \brief ͨ�ÿ��ƼĴ���C2 */
        amhw_hc32f460_port_pcr_field_t PCRC2_f;
    };
    union
    {
        __IO uint16_t PFSRC2;                  /**< \brief ����ѡ��Ĵ���C2 */
        amhw_hc32f460_port_pfsr_field_t PFSRC2_f;
    };
    union
    {
        __IO uint16_t PCRC3;                   /**< \brief ͨ�ÿ��ƼĴ���C3 */
        amhw_hc32f460_port_pcr_field_t PCRC3_f;
    };
    union
    {
        __IO uint16_t PFSRC3;                  /**< \brief ����ѡ��Ĵ���C3 */
        amhw_hc32f460_port_pfsr_field_t PFSRC3_f;
    };
    union
    {
        __IO uint16_t PCRC4;                   /**< \brief ͨ�ÿ��ƼĴ���C4 */
        amhw_hc32f460_port_pcr_field_t PCRC4_f;
    };
    union
    {
        __IO uint16_t PFSRC4;                  /**< \brief ����ѡ��Ĵ���C4 */
        amhw_hc32f460_port_pfsr_field_t PFSRC4_f;
    };
    union
    {
        __IO uint16_t PCRC5;                   /**< \brief ͨ�ÿ��ƼĴ���C5 */
        amhw_hc32f460_port_pcr_field_t PCRC5_f;
    };
    union
    {
        __IO uint16_t PFSRC5;                  /**< \brief ����ѡ��Ĵ���C5 */
        amhw_hc32f460_port_pfsr_field_t PFSRC5_f;
    };
    union
    {
        __IO uint16_t PCRC6;                   /**< \brief ͨ�ÿ��ƼĴ���C6 */
        amhw_hc32f460_port_pcr_field_t PCRC6_f;
    };
    union
    {
        __IO uint16_t PFSRC6;                  /**< \brief ����ѡ��Ĵ���C6 */
        amhw_hc32f460_port_pfsr_field_t PFSRC6_f;
    };
    union
    {
        __IO uint16_t PCRC7;                   /**< \brief ͨ�ÿ��ƼĴ���C7 */
        amhw_hc32f460_port_pcr_field_t PCRC7_f;
    };
    union
    {
        __IO uint16_t PFSRC7;                  /**< \brief ����ѡ��Ĵ���C7 */
        amhw_hc32f460_port_pfsr_field_t PFSRC7_f;
    };
    union
    {
        __IO uint16_t PCRC8;                   /**< \brief ͨ�ÿ��ƼĴ���C8 */
        amhw_hc32f460_port_pcr_field_t PCRC8_f;
    };
    union
    {
        __IO uint16_t PFSRC8;                  /**< \brief ����ѡ��Ĵ���C8 */
        amhw_hc32f460_port_pfsr_field_t PFSRC8_f;
    };
    union
    {
        __IO uint16_t PCRC9;                   /**< \brief ͨ�ÿ��ƼĴ���C9 */
        amhw_hc32f460_port_pcr_field_t PCRC9_f;
    };
    union
    {
        __IO uint16_t PFSRC9;                  /**< \brief ����ѡ��Ĵ���C9 */
        amhw_hc32f460_port_pfsr_field_t PFSRC9_f;
    };
    union
    {
        __IO uint16_t PCRC10;                  /**< \brief ͨ�ÿ��ƼĴ���C10 */
        amhw_hc32f460_port_pcr_field_t PCRC10_f;
    };
    union
    {
        __IO uint16_t PFSRC10;                 /**< \brief ����ѡ��Ĵ���C10 */
        amhw_hc32f460_port_pfsr_field_t PFSRC10_f;
    };
    union
    {
        __IO uint16_t PCRC11;                  /**< \brief ͨ�ÿ��ƼĴ���C11 */
        amhw_hc32f460_port_pcr_field_t PCRC11_f;
    };
    union
    {
        __IO uint16_t PFSRC11;                 /**< \brief ����ѡ��Ĵ���C11 */
        amhw_hc32f460_port_pfsr_field_t PFSRC11_f;
    };
    union
    {
        __IO uint16_t PCRC12;                  /**< \brief ͨ�ÿ��ƼĴ���C12 */
        amhw_hc32f460_port_pcr_field_t PCRC12_f;
    };
    union
    {
        __IO uint16_t PFSRC12;                 /**< \brief ����ѡ��Ĵ���C12 */
        amhw_hc32f460_port_pfsr_field_t PFSRC12_f;
    };
    union
    {
        __IO uint16_t PCRC13;                  /**< \brief ͨ�ÿ��ƼĴ���C13 */
        amhw_hc32f460_port_pcr_field_t PCRC13_f;
    };
    union
    {
        __IO uint16_t PFSRC13;                 /**< \brief ����ѡ��Ĵ���C13 */
        amhw_hc32f460_port_pfsr_field_t PFSRC13_f;
    };
    union
    {
        __IO uint16_t PCRC14;                  /**< \brief ͨ�ÿ��ƼĴ���C14 */
        amhw_hc32f460_port_pcr_field_t PCRC14_f;
    };
    union
    {
        __IO uint16_t PFSRC14;                 /**< \brief ����ѡ��Ĵ���C14 */
        amhw_hc32f460_port_pfsr_field_t PFSRC14_f;
    };
    union
    {
        __IO uint16_t PCRC15;                  /**< \brief ͨ�ÿ��ƼĴ���C15 */
        amhw_hc32f460_port_pcr_field_t PCRC15_f;
    };
    union
    {
        __IO uint16_t PFSRC15;                 /**< \brief ����ѡ��Ĵ���C15 */
        amhw_hc32f460_port_pfsr_field_t PFSRC15_f;
    };
    union
    {
        __IO uint16_t PCRD0;                   /**< \brief ͨ�ÿ��ƼĴ���D0 */
        amhw_hc32f460_port_pcr_field_t PCRD0_f;
    };
    union
    {
        __IO uint16_t PFSRD0;                  /**< \brief ����ѡ��Ĵ���D0 */
        amhw_hc32f460_port_pfsr_field_t PFSRD0_f;
    };
    union
    {
        __IO uint16_t PCRD1;                   /**< \brief ͨ�ÿ��ƼĴ���D1 */
        amhw_hc32f460_port_pcr_field_t PCRD1_f;
    };
    union
    {
        __IO uint16_t PFSRD1;                  /**< \brief ����ѡ��Ĵ���D1 */
        amhw_hc32f460_port_pfsr_field_t PFSRD1_f;
    };
    union
    {
        __IO uint16_t PCRD2;                   /**< \brief ͨ�ÿ��ƼĴ���D2 */
        amhw_hc32f460_port_pcr_field_t PCRD2_f;
    };
    union
    {
        __IO uint16_t PFSRD2;                 /**< \brief ����ѡ��Ĵ���D2 */
        amhw_hc32f460_port_pfsr_field_t PFSRD2_f;
    };
    union
    {
        __IO uint16_t PCRD3;                  /**< \brief ͨ�ÿ��ƼĴ���D3 */
        amhw_hc32f460_port_pcr_field_t PCRD3_f;
    };
    union
    {
        __IO uint16_t PFSRD3;                 /**< \brief ����ѡ��Ĵ���D3 */
        amhw_hc32f460_port_pfsr_field_t PFSRD3_f;
    };
    union
    {
        __IO uint16_t PCRD4;                  /**< \brief ͨ�ÿ��ƼĴ���D4 */
        amhw_hc32f460_port_pcr_field_t PCRD4_f;
    };
    union
    {
        __IO uint16_t PFSRD4;                 /**< \brief ����ѡ��Ĵ���D4 */
        amhw_hc32f460_port_pfsr_field_t PFSRD4_f;
    };
    union
    {
        __IO uint16_t PCRD5;                  /**< \brief ͨ�ÿ��ƼĴ���D5 */
        amhw_hc32f460_port_pcr_field_t PCRD5_f;
    };
    union
    {
        __IO uint16_t PFSRD5;                 /**< \brief ����ѡ��Ĵ���D5 */
        amhw_hc32f460_port_pfsr_field_t PFSRD5_f;
    };
    union
    {
        __IO uint16_t PCRD6;                  /**< \brief ͨ�ÿ��ƼĴ���D6 */
        amhw_hc32f460_port_pcr_field_t PCRD6_f;
    };
    union
    {
        __IO uint16_t PFSRD6;                 /**< \brief ����ѡ��Ĵ���D6 */
        amhw_hc32f460_port_pfsr_field_t PFSRD6_f;
    };
    union
    {
        __IO uint16_t PCRD7;                  /**< \brief ͨ�ÿ��ƼĴ���D7 */
        amhw_hc32f460_port_pcr_field_t PCRD7_f;
    };
    union
    {
        __IO uint16_t PFSRD7;                 /**< \brief ����ѡ��Ĵ���D7 */
        amhw_hc32f460_port_pfsr_field_t PFSRD7_f;
    };
    union
    {
        __IO uint16_t PCRD8;                  /**< \brief ͨ�ÿ��ƼĴ���D8 */
        amhw_hc32f460_port_pcr_field_t PCRD8_f;
    };
    union
    {
        __IO uint16_t PFSRD8;                 /**< \brief ����ѡ��Ĵ���D8 */
        amhw_hc32f460_port_pfsr_field_t PFSRD8_f;
    };
    union
    {
        __IO uint16_t PCRD9;                  /**< \brief ͨ�ÿ��ƼĴ���D9 */
        amhw_hc32f460_port_pcr_field_t PCRD9_f;
    };
    union
    {
        __IO uint16_t PFSRD9;                 /**< \brief ����ѡ��Ĵ���D9 */
        amhw_hc32f460_port_pfsr_field_t PFSRD9_f;
    };
    union
    {
        __IO uint16_t PCRD10;                 /**< \brief ͨ�ÿ��ƼĴ���D10 */
        amhw_hc32f460_port_pcr_field_t PCRD10_f;
    };
    union
    {
        __IO uint16_t PFSRD10;                /**< \brief ����ѡ��Ĵ���D10 */
        amhw_hc32f460_port_pfsr_field_t PFSRD10_f;
    };
    union
    {
        __IO uint16_t PCRD11;                 /**< \brief ͨ�ÿ��ƼĴ���D11 */
        amhw_hc32f460_port_pcr_field_t PCRD11_f;
    };
    union
    {
        __IO uint16_t PFSRD11;                /**< \brief ����ѡ��Ĵ���D11 */
        amhw_hc32f460_port_pfsr_field_t PFSRD11_f;
    };
    union
    {
        __IO uint16_t PCRD12;                 /**< \brief ͨ�ÿ��ƼĴ���D12 */
        amhw_hc32f460_port_pcr_field_t PCRD12_f;
    };
    union
    {
        __IO uint16_t PFSRD12;                /**< \brief ����ѡ��Ĵ���D12 */
        amhw_hc32f460_port_pfsr_field_t PFSRD12_f;
    };
    union
    {
        __IO uint16_t PCRD13;                 /**< \brief ͨ�ÿ��ƼĴ���D13 */
        amhw_hc32f460_port_pcr_field_t PCRD13_f;
    };
    union
    {
        __IO uint16_t PFSRD13;                /**< \brief ����ѡ��Ĵ���D13 */
        amhw_hc32f460_port_pfsr_field_t PFSRD13_f;
    };
    union
    {
        __IO uint16_t PCRD14;                 /**< \brief ͨ�ÿ��ƼĴ���D14 */
        amhw_hc32f460_port_pcr_field_t PCRD14_f;
    };
    union
    {
        __IO uint16_t PFSRD14;                /**< \brief ����ѡ��Ĵ���D14 */
        amhw_hc32f460_port_pfsr_field_t PFSRD14_f;
    };
    union
    {
        __IO uint16_t PCRD15;                 /**< \brief ͨ�ÿ��ƼĴ���D15 */
        amhw_hc32f460_port_pcr_field_t PCRD15_f;
    };
    union
    {
        __IO uint16_t PFSRD15;                /**< \brief ����ѡ��Ĵ���D15 */
        amhw_hc32f460_port_pfsr_field_t PFSRD15_f;
    };
    union
    {
        __IO uint16_t PCRE0;                  /**< \brief ͨ�ÿ��ƼĴ���E0 */
        amhw_hc32f460_port_pcr_field_t PCRE0_f;
    };
    union
    {
        __IO uint16_t PFSRE0;                 /**< \brief ����ѡ��Ĵ���E0 */
        amhw_hc32f460_port_pfsr_field_t PFSRE0_f;
    };
    union
    {
        __IO uint16_t PCRE1;                  /**< \brief ͨ�ÿ��ƼĴ���E1 */
        amhw_hc32f460_port_pcr_field_t PCRE1_f;
    };
    union
    {
        __IO uint16_t PFSRE1;                 /**< \brief ����ѡ��Ĵ���E1 */
        amhw_hc32f460_port_pfsr_field_t PFSRE1_f;
    };
    union
    {
        __IO uint16_t PCRE2;                  /**< \brief ͨ�ÿ��ƼĴ���E2 */
        amhw_hc32f460_port_pcr_field_t PCRE2_f;
    };
    union
    {
        __IO uint16_t PFSRE2;                 /**< \brief ����ѡ��Ĵ���E2 */
        amhw_hc32f460_port_pfsr_field_t PFSRE2_f;
    };
    union
    {
        __IO uint16_t PCRE3;                  /**< \brief ͨ�ÿ��ƼĴ���E3 */
        amhw_hc32f460_port_pcr_field_t PCRE3_f;
    };
    union
    {
        __IO uint16_t PFSRE3;                 /**< \brief ����ѡ��Ĵ���E3 */
        amhw_hc32f460_port_pfsr_field_t PFSRE3_f;
    };
    union
    {
        __IO uint16_t PCRE4;                  /**< \brief ͨ�ÿ��ƼĴ���E4 */
        amhw_hc32f460_port_pcr_field_t PCRE4_f;
    };
    union
    {
        __IO uint16_t PFSRE4;                  /**< \brief ����ѡ��Ĵ���E4 */
        amhw_hc32f460_port_pfsr_field_t PFSRE4_f;
    };
    union
    {
        __IO uint16_t PCRE5;                   /**< \brief ͨ�ÿ��ƼĴ���E5 */
        amhw_hc32f460_port_pcr_field_t PCRE5_f;
    };
    union
    {
        __IO uint16_t PFSRE5;                  /**< \brief ����ѡ��Ĵ���E5 */
        amhw_hc32f460_port_pfsr_field_t PFSRE5_f;
    };
    union
    {
        __IO uint16_t PCRE6;                   /**< \brief ͨ�ÿ��ƼĴ���E6 */
        amhw_hc32f460_port_pcr_field_t PCRE6_f;
    };
    union
    {
        __IO uint16_t PFSRE6;                  /**< \brief ����ѡ��Ĵ���E6 */
        amhw_hc32f460_port_pfsr_field_t PFSRE6_f;
    };
    union
    {
        __IO uint16_t PCRE7;                   /**< \brief ͨ�ÿ��ƼĴ���E7 */
        amhw_hc32f460_port_pcr_field_t PCRE7_f;
    };
    union
    {
        __IO uint16_t PFSRE7;                  /**< \brief ����ѡ��Ĵ���E7 */
        amhw_hc32f460_port_pfsr_field_t PFSRE7_f;
    };
    union
    {
        __IO uint16_t PCRE8;                   /**< \brief ͨ�ÿ��ƼĴ���E8 */
        amhw_hc32f460_port_pcr_field_t PCRE8_f;
    };
    union
    {
        __IO uint16_t PFSRE8;                  /**< \brief ����ѡ��Ĵ���E8 */
        amhw_hc32f460_port_pfsr_field_t PFSRE8_f;
    };
    union
    {
        __IO uint16_t PCRE9;                   /**< \brief ͨ�ÿ��ƼĴ���E9 */
        amhw_hc32f460_port_pcr_field_t PCRE9_f;
    };
    union
    {
        __IO uint16_t PFSRE9;                  /**< \brief ����ѡ��Ĵ���E9 */
        amhw_hc32f460_port_pfsr_field_t PFSRE9_f;
    };
    union
    {
        __IO uint16_t PCRE10;                  /**< \brief ͨ�ÿ��ƼĴ���E10 */
        amhw_hc32f460_port_pcr_field_t PCRE10_f;
    };
    union
    {
        __IO uint16_t PFSRE10;                 /**< \brief ����ѡ��Ĵ���E10 */
        amhw_hc32f460_port_pfsr_field_t PFSRE10_f;
    };
    union
    {
        __IO uint16_t PCRE11;                  /**< \brief ͨ�ÿ��ƼĴ���E11 */
        amhw_hc32f460_port_pcr_field_t PCRE11_f;
    };
    union
    {
        __IO uint16_t PFSRE11;                 /**< \brief ����ѡ��Ĵ���E11 */
        amhw_hc32f460_port_pfsr_field_t PFSRE11_f;
    };
    union
    {
        __IO uint16_t PCRE12;                  /**< \brief ͨ�ÿ��ƼĴ���E12 */
        amhw_hc32f460_port_pcr_field_t PCRE12_f;
    };
    union
    {
        __IO uint16_t PFSRE12;                 /**< \brief ����ѡ��Ĵ���E12 */
        amhw_hc32f460_port_pfsr_field_t PFSRE12_f;
    };
    union
    {
        __IO uint16_t PCRE13;                  /**< \brief ͨ�ÿ��ƼĴ���E13 */
        amhw_hc32f460_port_pcr_field_t PCRE13_f;
    };
    union
    {
        __IO uint16_t PFSRE13;                 /**< \brief ����ѡ��Ĵ���E13 */
        amhw_hc32f460_port_pfsr_field_t PFSRE13_f;
    };
    union
    {
        __IO uint16_t PCRE14;                  /**< \brief ͨ�ÿ��ƼĴ���E14 */
        amhw_hc32f460_port_pcr_field_t PCRE14_f;
    };
    union
    {
        __IO uint16_t PFSRE14;                 /**< \brief ����ѡ��Ĵ���E14 */
        amhw_hc32f460_port_pfsr_field_t PFSRE14_f;
    };
    union
    {
        __IO uint16_t PCRE15;                  /**< \brief ͨ�ÿ��ƼĴ���E15 */
        amhw_hc32f460_port_pcr_field_t PCRE15_f;
    };
    union
    {
        __IO uint16_t PFSRE15;                 /**< \brief ����ѡ��Ĵ���E15 */
        amhw_hc32f460_port_pfsr_field_t PFSRE15_f;
    };
    union
    {
        __IO uint16_t PCRH0;                   /**< \brief ͨ�ÿ��ƼĴ���H0 */
        amhw_hc32f460_port_pcr_field_t PCRH0_f;
    };
    union
    {
        __IO uint16_t PFSRH0;                  /**< \brief ����ѡ��Ĵ���H0 */
        amhw_hc32f460_port_pfsr_field_t PFSRH0_f;
    };
    union
    {
        __IO uint16_t PCRH1;                   /**< \brief ͨ�ÿ��ƼĴ���H1 */
        amhw_hc32f460_port_pcr_field_t PCRH1_f;
    };
    union
    {
        __IO uint16_t PFSRH1;                  /**< \brief ����ѡ��Ĵ���H1 */
        amhw_hc32f460_port_pfsr_field_t PFSRH1_f;
    };
    union
    {
        __IO uint16_t PCRH2;                   /**< \brief ͨ�ÿ��ƼĴ���H2 */
        amhw_hc32f460_port_pcr_field_t PCRH2_f;
    };
    union
    {
        __IO uint16_t PFSRH2;                  /**< \brief ����ѡ��Ĵ���H2 */
        amhw_hc32f460_port_pfsr_field_t PFSRH2_f;
    };
} amhw_hc32f460_gpio_t;

am_static_inline
void amhw_hc32f460_port_unlock(amhw_hc32f460_gpio_t *p_hw_gpio)
{
    p_hw_gpio->PWPR = 0xA501u;
}

am_static_inline
void amhw_hc32f460_port_lock(amhw_hc32f460_gpio_t *p_hw_gpio)
{
    p_hw_gpio->PWPR = 0xA500u;
}


am_static_inline
int amhw_hc32f460_gpio_pin_dir_get (amhw_hc32f460_gpio_t *p_hw_gpio, int pin);

am_static_inline
void __pin_calc (int pin, en_portx_t *p_port, uint8_t *p_pin_pos)
{
    if ((NULL != p_port) && (NULL != p_pin_pos))
    {
        *p_port    = (en_portx_t)(pin >> 4); 
        *p_pin_pos = (pin & 0x0F);
    }
}

/**
 * \brief ����GPIO����Ϊ���ֶ˿�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_digital_set (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->DDIS  = 0u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ����GPIO����Ϊģ��˿�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_analog_set (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->DDIS  = 1u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ��ȡ��ǰ�˿����ֶ˿�/ģ��˿�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : ���ֶ˿�
 * \retval 1 : ģ��˿�
 */
am_static_inline
int amhw_hc32f460_gpio_pin_analog_digital_get (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    uint8_t value = 0;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    value = PCRx->DDIS;  
    amhw_hc32f460_port_lock(p_hw_gpio);
    return value;
}

/**
 * \brief ����GPIO����Ϊ���״̬���� ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_lte_enable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->LTE= 1u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ����GPIO����Ϊ���״̬���� ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_lte_disable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->LTE= 0u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief �ⲿ�ж�ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_ext_int_enable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->INTE  = 1u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief �ⲿ�ж�ʹ�����üĴ���    ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_ext_int_disable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->INTE  = 0u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

am_static_inline
int amhw_hc32f460_gpio_pin_get (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    amhw_hc32f460_port_pcr_field_t *PCRx;

    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                                    en_portx * 0x40ul + pin_pos * 0x04ul); 
    amhw_hc32f460_port_lock(p_hw_gpio);

    /* ��Ϊ�������ʱ����ȡ���ŵ�״̬����ͨ����ȡODR�Ĵ�����ֵ��ʵ�� */
    if (amhw_hc32f460_gpio_pin_dir_get(p_hw_gpio, pin) != 0) {
        return ((PCRx->POUT != 0) ? 1 : 0);
    } else {
        return ((PCRx->PIN != 0) ? 1 : 0);
    }
}

/**
 * \brief ����ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_pu_enable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->PUU  = 1u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ����ʹ�����üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_pu_disable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->PUU  = 0u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief �����������üĴ���  
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_driver_capability  (amhw_hc32f460_gpio_t           *p_hw_gpio, 
                                                amhw_hc32f460_gpio_speed_mode_t speed_mode,
                                                int                             pin
)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    __pin_calc(pin, &en_portx, &pin_pos);
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                                en_portx * 0x40ul + pin_pos * 0x04ul); 
    PCRx->DRV = speed_mode;
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ����GPIO���ŷ���Ϊ���
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] speed_mode : ����Ϊ����ʱ����������·��Ӧ�ٶ�ģʽ��
 *                         ֵΪ amhw_hc32f460_gpio_speed_mode_t ���ö������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_dir_output (amhw_hc32f460_gpio_t           *p_hw_gpio,
                                   int                        pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    __pin_calc(pin, &en_portx, &pin_pos);
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                                en_portx * 0x40ul + pin_pos * 0x04ul); 
    PCRx->POUTE = 1;                                                
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_dir_input (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    /* �������ŷ���Ϊ������λ��, ���øĽӿڲ���Ӱ������λ�� */
    amhw_hc32f460_port_pcr_field_t *PCRx;
    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    __pin_calc(pin, &en_portx, &pin_pos);
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                            en_portx * 0x40ul + pin_pos * 0x04ul);                                                
    PCRx->POUTE = 0;
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ��ȡGPIO���������������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \retval  0  : ����
 * \retval  1  : ���
 */
am_static_inline
int amhw_hc32f460_gpio_pin_dir_get (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    
    __pin_calc(pin, &en_portx, &pin_pos);    
   
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                                en_portx * 0x40ul + pin_pos * 0x04ul);                                                
    amhw_hc32f460_port_lock(p_hw_gpio);

    return ((PCRx->POUTE != 0) ? 1 : 0);
}


/**
 * \brief ��©������üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_od_enable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->NOD  = 1u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}


/**
 * \brief ��©������üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_od_disable (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    amhw_hc32f460_port_pcr_field_t *PCRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    amhw_hc32f460_port_unlock(p_hw_gpio);
    PCRx = (amhw_hc32f460_port_pcr_field_t *)((uint32_t)(&(p_hw_gpio->PCRA0)) +      \
                                      en_portx * 0x40ul + pin_pos * 0x04ul);
    PCRx->NOD  = 0u;  
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ����GPIO��������ߵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��.
 *
 * \note �ù��������������ŵ�ʱ��Ϊʹ���������貢ʧ����������
 */
am_static_inline
void amhw_hc32f460_gpio_pin_out_high (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    uint32_t *POSRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t   pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);

    POSRx = (uint32_t *)((uint32_t)(&(p_hw_gpio->POSRA)) + 0x10 * en_portx);
    *POSRx |= (1 << pin_pos) & 0x0000FFFFul;
}

/**
 * \brief ����GPIO��������͵�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note �ù��������������ŵ�ʱ��Ϊʧ���������貢ʹ����������
 */
am_static_inline
void amhw_hc32f460_gpio_pin_out_low (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    uint32_t *PORRx;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t   pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);

    PORRx = (uint32_t *)((uint32_t)(&(p_hw_gpio->PORRA)) + 0x10 * en_portx);
    *PORRx |= (1 << pin_pos) & 0x0000FFFFul;
}

/**
 * \brief ��תGPIO������ŵĵ�ƽ״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note �ù��������������ŵ�ʱ��Ϊ��������/��������
 */
am_static_inline
void amhw_hc32f460_gpio_pin_toggle (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    uint32_t *POTRx;    
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t   pin_pos = 0u;
    __pin_calc(pin, &en_portx, &pin_pos);
    
    POTRx = (uint32_t *)((uint32_t)(&(p_hw_gpio->POTRA)) + 0x10 * en_portx);
    *POTRx |= (1 << pin_pos) & 0x0000FFFFul;
}

/**
 * \brief ���Ÿ��ù�����ӳ������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] gpio_af   : ���Ÿ��ù��ܱ�ţ�ֵΪ AMHW_GPIO_AF_* ��һ��� (# AMHW_GPIO_AF_0)
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_afr_set (amhw_hc32f460_gpio_t *p_hw_gpio, int gpio_af, int pin)
{
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t   pin_pos = 0u;
    amhw_hc32f460_gpio_afio_t enFuncSel;
    amhw_hc32f460_port_pfsr_field_t *PFSRx;

    __pin_calc(pin, &en_portx, &pin_pos);

    enFuncSel = (amhw_hc32f460_gpio_afio_t)gpio_af;

    amhw_hc32f460_port_unlock(p_hw_gpio);
    PFSRx = (amhw_hc32f460_port_pfsr_field_t *)((uint32_t)(&(p_hw_gpio->PFSRA0)) \
        + 0x40ul * en_portx + 0x4ul * pin_pos);

    /* main function setting */
    PFSRx->FSEL = enFuncSel & 0x0000003f;
    amhw_hc32f460_port_lock(p_hw_gpio);
}

/**
 * \brief ��ȡ��ǰ���Ÿ��ù�����AF
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ���� AMHW_GPIO_AF_* ��һ���ֵ (# AMHW_GPIO_AF_0)
 */
am_static_inline
uint32_t amhw_hc32f460_gpio_pin_afr_get (amhw_hc32f460_gpio_t *p_hw_gpio, int pin)
{
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;
    uint8_t   pin_pos = 0u;
    amhw_hc32f460_gpio_afio_t enFuncSel;
    amhw_hc32f460_port_pfsr_field_t *PFSRx;

    __pin_calc(pin, &en_portx, &pin_pos);

    amhw_hc32f460_port_unlock(p_hw_gpio);
    PFSRx = (amhw_hc32f460_port_pfsr_field_t *)((uint32_t)(&(p_hw_gpio->PFSRA0)) \
            + 0x40ul * en_portx + 0x4ul * pin_pos);

    /* main function setting */
    enFuncSel = (amhw_hc32f460_gpio_afio_t)((PFSRx->FSEL) & 0x0000003f);
    amhw_hc32f460_port_lock(p_hw_gpio);
    return enFuncSel;

}

/**
 * \brief ����GPIO���ŵ�ģʽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] gpio_mode : ���ŵ�ģʽ��ֵΪ AMHW_HC32F460_gpiomode_t ���ö������
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_gpio_pin_mode_set (amhw_hc32f460_gpio_t       *p_hw_gpio,
                                 amhw_hc32f460_gpio_mode_t   gpio_mode,
                                 int                    pin)
{
    if (AMHW_HC32F460_GPIO_MODE_AIN == gpio_mode ) 
    {
        amhw_hc32f460_gpio_pin_analog_set(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_dir_input(p_hw_gpio, pin);
    }
    else if (AMHW_HC32F460_GPIO_MODE_IN_FLOATING == gpio_mode ) 
    {
        amhw_hc32f460_gpio_pin_digital_set(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_dir_input(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_pu_disable(p_hw_gpio, pin);
    }
    else if (AMHW_HC32F460_GPIO_MODE_IPD == gpio_mode ) 
    {
        
    }
    else if (AMHW_HC32F460_GPIO_MODE_IPU == gpio_mode ) 
    {
        amhw_hc32f460_gpio_pin_digital_set(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_dir_input(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_pu_enable(p_hw_gpio, pin);

    }
    else if (AMHW_HC32F460_GPIO_MODE_OUT_PP == gpio_mode ) 
    {
        amhw_hc32f460_gpio_pin_digital_set(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_dir_output(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_od_disable(p_hw_gpio, pin);
    }
    else if (AMHW_HC32F460_GPIO_MODE_OUT_OD == gpio_mode ) 
    {
        amhw_hc32f460_gpio_pin_digital_set(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_dir_output(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_od_enable(p_hw_gpio, pin);
    }
    else if (AMHW_HC32F460_GPIO_MODE_AOUT == gpio_mode ) 
    {
        amhw_hc32f460_gpio_pin_analog_set(p_hw_gpio, pin);
        amhw_hc32f460_gpio_pin_dir_output(p_hw_gpio, pin);        
    }     
    else if (AMHW_HC32F460_GPIO_MODE_AF_PP == gpio_mode ) 
    {
        
    } 
    else if (AMHW_HC32F460_GPIO_MODE_AF_OD == gpio_mode ) 
    {
        
    }                                              
}


/**
 * @}
 */

/* ʹ�������ṹ�������������Ľ��� */
#if defined(__CC_ARM)
    #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
    #pragma warning restore
#else
    #warning Not supported compiler t
#endif

/**
 * @} AMHW_HC32F460_if_zlg_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_GPIO_H */

/* end of file */
