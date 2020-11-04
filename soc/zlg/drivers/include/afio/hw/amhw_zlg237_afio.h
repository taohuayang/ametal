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
 * \brief AFIO hardware operation interface
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-3  zc, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG237_AFIO_H
#define __AMHW_ZLG237_AFIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"

/**
 * \addtogroup amhw_zlg237_if_afio
 * \copydoc amhw_zlg237_afio.h
 * @{
 */

/**
 * \brief GPIO �˿ڼĴ����ṹ��
 */
typedef struct amhw_zlg237_afio {
    __IO  uint32_t evcr;         /**< \brief �¼����ƼĴ��� */
    __IO  uint32_t mapr;         /**< \brief ������ӳ��͵���I/O���üĴ��� */
    __IO  uint32_t exticr[4];    /**< \brief �ⲿ�ж����üĴ��� */
} amhw_zlg237_afio_t;

/**
 * \brief ����ӳ���������
 */
typedef enum {
    AMHW_ZLG237_SPI1_REMAP     = 0,     /**< \brief SPI1 */
    AMHW_ZLG237_I2C1_REMAP,             /**< \brief I2C1 */
    AMHW_ZLG237_UART1_REMAP,            /**< \brief UART1 */
    AMHW_ZLG237_UART2_REMAP,            /**< \brief UART2 */
    AMHW_ZLG237_UART3_REMAP,            /**< \brief UART3 */
    AMHW_ZLG237_TIM1_REMAP     = 6,     /**< \brief TIM1 */
    AMHW_ZLG237_TIM2_REMAP     = 8,     /**< \brief TIM2 */
    AMHW_ZLG237_TIM3_REMAP     = 10,    /**< \brief TIM3 */
    AMHW_ZLG237_CAN_REMAP      = 13,    /**< \brief CAN */
    AMHW_ZLG237_TIM4_REMAP     = 12,    /**< \brief TIM4 */
    AMHW_ZLG237_PD01_REMAP     = 15,    /**< \brief PD01 */
    AMHW_ZLG237_TIM5_CH4_REMAP,    /**< \brief TIM5_CH4 */
    AMHW_ZLG237_ADC1_ETRGINJ_REMAP,    /**< \brief ADC1_ETRGINJ */
    AMHW_ZLG237_ADC1_ETRGREG_REMAP,    /**< \brief ADC1_ETRGREG */
    AMHW_ZLG237_ADC2_ETRGINJ_REMAP,    /**< \brief ADC2_ETRGINJ */
    AMHW_ZLG237_ADC2_ETRGREG_REMAP,    /**< \brief ADC2_ETRGREG */
    AMHW_ZLG237_SWJ_CFG        = 24,                /**< \brief SWJ_CFG */
    AMHW_ZLG237_NO_REMAP,               /**< \brief û����ӳ���� */
}amhw_zlg237_afio_remap_peripheral_t;

/**
 * \name  ��ӳ��λ����
 * @{
 */
/** \brief ����ѡ��  ѡ���������Cortex��EVENTOUT�źŵ����� */
#define AMHW_ZLG237_AFIO_EVCR_PIN_EVENTOUT     (0u)

/** \brief �˿�ѡ��  ѡ���������Cortex��EVENTOUT�źŵĶ˿� */
#define AMHW_ZLG237_AFIO_EVCR_PORT_EVENTOUT     (4u)

/** \brief EVOE �����¼����λ Cortex��EVENTOUT������PORT[2:0] �� PIN[3:0]ѡ����I/O */
#define AMHW_ZLG237_AFIO_EVCR_EVOE     (7u)

/** \brief SPI1��ӳ�� SCK/PB3��MISO/PB4��MOSI/PB5 */
#define AMHW_ZLG237_AFIO_MAPR_SPI1    (0u)

/** \brief I2C1��ӳ�� SCL/PB8��SDA/PB9 */
#define AMHW_ZLG237_AFIO_MAPR_I2C1    (1u)

/** \brief UART1��ӳ�� TX/PB6��RX/PB7 */
#define AMHW_ZLG237_AFIO_MAPR_UART1   (2u)

/** \brief UART2��ӳ��
 *  CTS/PD3��RTS/PD4��
 *  TX/PD5��RX/PD6��
 *  CK/PD7
 */
#define AMHW_ZLG237_AFIO_MAPR_UART2   (3u)

/** \brief UART3��ӳ�� */
#define AMHW_ZLG237_AFIO_MAPR_UART3   (4u)

typedef enum {

    /** \brief TX/PB10,RX/PB11,CK/PB12,CST/PB13,RTS/PB14 */
    AMHW_ZLG237_AFIO_UART3_REMAP_NO  = 0,
    /** \brief TX/PC10,RX/PC11,CK/PC12,CST/PB13,RTS/PB14 */
    AMHW_ZLG237_AFIO_UART3_REMAP_PART1,
    /** \brief TX/PD8,RX/PD9,CK/PD10,CST/PD11,RTS/PD12 */
    AMHW_ZLG237_AFIO_UART3_REMAP_ALL = 3,
}amhw_zlg237_afio_uart3_remap_mode_t;

/** \brief
 * TIM1������ӳ��
 * ETR/PA12��
 * CH1/PA8��CH2/PA9��CH3/PA10��CH4/PA11��
 * BAKIN/PA6��
 * CH1N/PA7��CH2N/PB0��CH3N/PB1
 */
#define AMHW_ZLG237_AFIO_MAPR_TIM1    (6u)

typedef enum {

    /** \brief ETR/PA12��CH1/PA8��CH2/PA9��CH3/PA10��
     * CH4/PA11��BKIN/PB12��CH1N/PB13��CH2N/PB14��CH3N/PB15 */
    AMHW_ZLG237_AFIO_TIM1_REMAP_NO  = 0,
    /** \brief ETR/PA12��CH1/PA8��CH2/PA9��CH3/PA10��
     * CH4/PA11��BKIN/PA6��CH1N/PA7��CH2N/PB0��CH3N/PB1 */
    AMHW_ZLG237_AFIO_TIM1_REMAP_PART1,
    /** \brief ETR/PE7��CH1/PE9��CH2/PE11��CH3/PE13��
     * CH4/PE14��BKIN/PE15��CH1N/PE8��CH2N/PE10��CH3N/PE12 */
    AMHW_ZLG237_AFIO_TIM1_REMAP_ALL = 3,
}amhw_zlg237_afio_tim1_remap_mode_t;




/** \brief TIM2��ӳ�� */
#define AMHW_ZLG237_AFIO_MAPR_TIM2    (8u)

typedef enum {

    /** \brief CH1/ETR/PA0��CH2/PA1��CH3/PA2��CH4/PA3 */
    AMHW_ZLG237_AFIO_TIM2_REMAP_NO = 0,
    /** \brief CH1/ETR/PA15��CH2/PB3��CH3/PA2��CH4/PA3 */
    AMHW_ZLG237_AFIO_TIM2_REMAP_PART1,
    /** \brief CH1/ETR/PA0��CH2/PA1��CH3/PB10��CH4/PB11 */
    AMHW_ZLG237_AFIO_TIM2_REMAP_PART2,
    /** \brief CH1/ETR/PA15��CH2/PB3��CH3/PB10��CH4/PB11 */
    AMHW_ZLG237_AFIO_TIM2_REMAP_ALL
}amhw_zlg237_afio_tim2_remap_mode_t;

/** \brief TIM3��ӳ�� */
#define AMHW_ZLG237_AFIO_MAPR_TIM3    (10u)

typedef enum {

    /** \brief CH1/PA6��CH2/PA7��CH3/PB0��CH4/PB1 */
    AMHW_ZLG237_AFIO_TIM3_REMAP_NO = 0,
    /** \brief CH1/PB4��CH2/PB5��CH3/PB0��CH4/PB1 */
    AMHW_ZLG237_AFIO_TIM3_REMAP_PART = 2,
    /** \brief CH1/PC6��CH2/PC7��CH3/PC8��CH4/PC9 */
    AMHW_ZLG237_AFIO_TIM3_REMAP_ALL
}amhw_zlg237_afio_tim3_remap_mode_t;

/** \brief TIM4��ȫ��ӳ��
 * CH1/PD12��CH2/PD13��CH3/PD14��CH4/PD15
 */
#define AMHW_ZLG237_AFIO_MAPR_TIM4    (12u)

/** \brief CAN��ӳ�� */
#define AMHW_ZLG237_AFIO_MAPR_CAN     (13u)

typedef enum {
    AMHW_ZLG237_AFIO_CAN_RX_PA11_TX_PA12 = 0,
    AMHW_ZLG237_AFIO_CAN_RX_PB8_TX_PB9   = 2,
    AMHW_ZLG237_AFIO_CAN_RX_PD0_TX_PD1   = 3,
}amhw_zlg237_afio_can_remap_mode_t;

/** \brief PD01��ӳ�� PD0ӳ��OSC_IN��PD1ӳ��OSC_OUT */
#define AMHW_ZLG237_AFIO_MAPR_PD01    (15u)

/** \brief TIM5ͨ��4 �ڲ���ӳ��
 * 0 TIM5_CH4/PA3
 * 1 TIM5_CH4/LSI�ڲ�����
 */
#define AMHW_ZLG237_AFIO_MAPR_TIM5_CH4    (16u)

/** \brief ADC1 ע��ת���ⲿ������ӳ��
 * 0 ADC1ע��ת��������EXTI15����
 * 1 ADC1ע��ת���ⲿ������TIM8_CH4����
 */
#define AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGINJ    (17u)

/** \brief ADC1 ����ת���ⲿ������ӳ��
 * 0 ADC1����ת��������EXTI11����
 * 1 ADC1����ת���ⲿ������TIM8_TRGO����
 */
#define AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGREG    (18u)

/** \brief ADC2 ע��ת���ⲿ������ӳ��
 * 0 ADC2ע��ת��������EXTI15����
 * 1 ADC2ע��ת���ⲿ������TIM8_CH4����
 */
#define AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGINJ    (19u)

/** \brief ADC1 ����ת���ⲿ������ӳ��
 * 0 ADC1����ת��������EXTI11����
 * 1 ADC1����ת���ⲿ������TIM8_TRGO����
 */
#define AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGREG    (20u)


/** \brief ������JTAG���� */
#define AMHW_ZLG237_AFIO_SWJ_CFG      (24u)

typedef enum {
    /**
     * \brief ��ȫSWJ��JTAG-DP + SW-DP������λ״̬
     *
     * PIOA13:I/0������   PIOA14:I/0������   PIOA15:I/0������
     * PIOB3 :I/0������   PIOB4 :I/0������
     */
    AMHW_ZLG237_AFIO_SWJ_CFG_0 = 0,

    /**
     * \brief ��ȫSWJ��JTAG-DP + SW-DP����û��JNTRST
     *
     * PIOA13:I/0������   PIOA14:I/0������   PIOA15:I/0������
     * PIOB3 :I/0������   PIOB4 :I/0����
     */
    AMHW_ZLG237_AFIO_SWJ_CFG_1,

    /**
     * \brief �ر�JTAG-DP������SW-DP
     *
     * PIOA13:I/0������   PIOA14:I/0������   PIOA15:I/0����
     * PIOB3 :I/0����   PIOB4 :I/0����
     */
    AMHW_ZLG237_AFIO_SWJ_CFG_2,

    /**
     * \brief �ر�JTAG-DP���ر�SW-DP
     *
     * PIOA13:I/0����   PIOA14:I/0����   PIOA15:I/0����
     * PIOB3 :I/0����   PIOB4 :I/0����
     */
    AMHW_ZLG237_AFIO_SWJ_CFG_4 = 4,
}amhw_zlg237_afio_swj_cfg_mode_t;

/** @} */


/**
 * \brief eventout evcr�¼������������
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] pin
 * \param[in] stats  0 1 ʹ��״̬
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_evcr_mode_set (amhw_zlg237_afio_t              *p_hw_afio,
                                     int                              pin,
                                     int                              stats)
{
    p_hw_afio->evcr |= (pin >> 4) << AMHW_ZLG237_AFIO_EVCR_PORT_EVENTOUT;
    p_hw_afio->evcr |= (pin & 0xf) << AMHW_ZLG237_AFIO_EVCR_PIN_EVENTOUT;
    p_hw_afio->evcr |= stats << AMHW_ZLG237_AFIO_EVCR_EVOE;
}


/**
 * \brief SPI1������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_spi1_pin_remap_enable (amhw_zlg237_afio_t *p_hw_afio)
{
    p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_SPI1;
}

/**
 * \brief SPI1������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_spi1_pin_remap_disable (amhw_zlg237_afio_t *p_hw_afio)
{
    p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_SPI1);
}

/**
 * \brief I2C1������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_i2c1_pin_remap_enable (amhw_zlg237_afio_t *p_hw_afio)
{
    p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_I2C1;
}

/**
 * \brief I2C1������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_i2c1_pin_remap_disable (amhw_zlg237_afio_t *p_hw_afio)
{
    p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_I2C1);
}

/**
 * \brief UART������ӳ��ʹ��
 *
 * \notes : ��ʵ�ô���3ʱ mode Ϊ 0
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] num       ���ںţ�1,2,3
 * \param[in] mode      amhw_zlg237_afio_uart3_remap_mode_t
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_uart_pin_remap_enable (amhw_zlg237_afio_t *p_hw_afio,
                                             int                 num)
{

    if (num == 1) {
        p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_UART1;
    } else if (num == 2) {
        p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_UART2;
    }
}

/**
 * \brief UART������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] num       ���ںţ�1,2,3
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_uart_pin_remap_disable (amhw_zlg237_afio_t *p_hw_afio,
                                              int num)
{
    if (num == 1) {
        p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_UART1);
    } else if (num == 2) {
        p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_UART2);
    }
}

/**
 * \brief uart3������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg237_afio_uart3_remap_mode_tö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_uart3_remap_mode_set (amhw_zlg237_afio_t *p_hw_afio,
                                           amhw_zlg237_afio_uart3_remap_mode_t mode)
{
     p_hw_afio->mapr &= ~(0x3<< AMHW_ZLG237_AFIO_MAPR_UART3);
     p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG237_AFIO_MAPR_UART3;

}

/**
 * \brief TIM1������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg237_afio_tim1_remap_modeö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_tim1_remap_mode_set (amhw_zlg237_afio_t *p_hw_afio,
                                           amhw_zlg237_afio_tim1_remap_mode_t mode)
{
    p_hw_afio->mapr &= ~(0x3<< AMHW_ZLG237_AFIO_MAPR_TIM1);
    p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG237_AFIO_MAPR_TIM1;

}

/**
 * \brief TIM2������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg237_afio_tim2_remap_modeö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_tim2_remap_mode_set (amhw_zlg237_afio_t *p_hw_afio,
                                           amhw_zlg237_afio_tim2_remap_mode_t mode)
{
    p_hw_afio->mapr &= ~(0x3 << AMHW_ZLG237_AFIO_MAPR_TIM2);
    p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG237_AFIO_MAPR_TIM2;
}

/**
 * \brief TIM3������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg237_afio_tim3_remap_modeö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_tim3_remap_mode_set (amhw_zlg237_afio_t *p_hw_afio,
                                           amhw_zlg237_afio_tim3_remap_mode_t mode)
{
    p_hw_afio->mapr &= ~(0x3 << AMHW_ZLG237_AFIO_MAPR_TIM3);
    p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG237_AFIO_MAPR_TIM3;
}

/**
 * \brief TIM4������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_tim4_pin_remap_enable (amhw_zlg237_afio_t *p_hw_afio)
{
      p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_TIM4;
}

/**
 * \brief TIM4������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_tim4_pin_remap_disable (amhw_zlg237_afio_t *p_hw_afio)
{
      p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_TIM4);
}

/**
 * \brief CAN������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg237_afio_can_remap_modeö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_can_remap_mode_set (amhw_zlg237_afio_t *p_hw_afio,
                                          amhw_zlg237_afio_can_remap_mode_t mode)
{
    p_hw_afio->mapr &= ~(0x3 << AMHW_ZLG237_AFIO_MAPR_CAN);
    p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG237_AFIO_MAPR_CAN;
}

/**
 * \brief PD01������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_pd01_pin_remap_enable (amhw_zlg237_afio_t *p_hw_afio)
{
    p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_PD01;
}

/**
 * \brief PD01������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_pd01_pin_remap_disable (amhw_zlg237_afio_t *p_hw_afio)
{
    p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_PD01);
}

/**
 * \brief TIM5CH4������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_tim5_ch4_pin_remap_enable (amhw_zlg237_afio_t *p_hw_afio)
{
      p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_TIM5_CH4;
}

/**
 * \brief TIM5CH4������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_tim5_ch4_pin_remap_disable (amhw_zlg237_afio_t *p_hw_afio)
{
      p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_TIM5_CH4);
}

/**
 * \brief ADC��ӳ��ģʽ����ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[mode] AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGINJ
 *              AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGREG
 *              AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGINJ
 *              AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGREG
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_adc_pin_remap_enable (amhw_zlg237_afio_t *p_hw_afio,
                                            int                 mode)
{
      switch (mode) {

      case AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGINJ:
          p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGINJ;
          break;

      case AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGREG:
          p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGREG;
          break;

      case AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGINJ:
          p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGINJ;
          break;

      case AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGREG:
          p_hw_afio->mapr |= 1 << AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGREG;
          break;

      default:
          break;
      }
}

/**
 * \brief ADC��ӳ��ģʽ���ý���
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[mode] AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGINJ
 *              AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGREG
 *              AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGINJ
 *              AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGREG
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_adc_pin_remap_disable (amhw_zlg237_afio_t *p_hw_afio,
                                             int                 mode)
{
      switch (mode) {

      case AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGINJ:
          p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGINJ);
          break;

      case AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGREG:
          p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_ADC1_ETRGREG);
          break;

      case AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGINJ:
          p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGINJ);
          break;

      case AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGREG:
          p_hw_afio->mapr &= ~(1 << AMHW_ZLG237_AFIO_MAPR_ADC2_ETRGREG);
          break;

      default:
          break;
      }
}


/**
 * \brief SWJ_CFG��ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg237_afio_swj_cfg_mode_tö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_swj_cfg_remap_mode_set (amhw_zlg237_afio_t *p_hw_afio,
                                              amhw_zlg237_afio_swj_cfg_mode_t mode)
{
    uint32_t flags = p_hw_afio->mapr;

    flags &= ~(0x7 << AMHW_ZLG237_AFIO_SWJ_CFG);
    flags |= (mode & 0x7) << AMHW_ZLG237_AFIO_SWJ_CFG;

    p_hw_afio->mapr |= flags;
}

/**
 * \brief �ⲿ�жϺ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg237_afio_t �ṹ��ָ��
 * \param[in] pin       ���ź�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_afio_exti_pin_set (amhw_zlg237_afio_t *p_hw_afio, int pin)
{
    p_hw_afio->exticr[(pin >> 2) & 0x3] |=
                                     ((pin >> 4) & 0x3) << ((pin & 0x3) << 2);
}

/**
 * @} amhw_zlg237_if_afio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG237_AFIO_H */

/* end of file */
