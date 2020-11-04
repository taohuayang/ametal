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
 * \brief HC32 PIO �������ò�������
 *
 * \note: �������Ź��ܵ�ʱ��һ��Ҫͬʱ�������ŵ�ģʽ����������ģʽ������ģʽ��
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-06  zp, first implementation
 * \endinternal
 */

#ifndef __HC32_PIN_H
#define __HC32_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_hc32_gpio_util.h"

#ifdef PIN_OUTSET
    #include "hc32_pin_outset.h"
#endif
 /**
 * \addtogroup hc32_if_pin
 * \copydoc hc32_pin.h
 * @{
 */

/**
 * \name HC32 PIO ���ű��
 * \anchor grp_gpio_pin_number
 * @{
 */

#define PIOA            0         /**< \brief �˿�A������ʼ�� */
#define PIOA_0          0         /**< \brief PIOA_0 ���ź� */
#define PIOA_1          1         /**< \brief PIOA_1 ���ź� */
#define PIOA_2          2         /**< \brief PIOA_2 ���ź� */
#define PIOA_3          3         /**< \brief PIOA_3 ���ź� */
#define PIOA_4          4         /**< \brief PIOA_4 ���ź� */
#define PIOA_5          5         /**< \brief PIOA_5 ���ź� */
#define PIOA_6          6         /**< \brief PIOA_6 ���ź� */
#define PIOA_7          7         /**< \brief PIOA_7 ���ź� */
#define PIOA_8          8         /**< \brief PIOA_8 ���ź� */
#define PIOA_9          9         /**< \brief PIOA_9 ���ź� */
#define PIOA_10         10        /**< \brief PIOA_10 ���ź� */
#define PIOA_13         13        /**< \brief PIOA_13 ���ź� */
#define PIOA_14         14        /**< \brief PIOA_14 ���ź� */
#define PIOA_15         15        /**< \brief PIOA_15 ���ź� */

#define PIOB            16        /**< \brief �˿�B������ʼ�� */
#define PIOB_0          16        /**< \brief PIOB_8 ���ź� */
#define PIOB_1          17        /**< \brief PIOB_1 ���ź� */
#define PIOB_2          18        /**< \brief PIOB_2 ���ź� */
#define PIOB_3          19        /**< \brief PIOB_3 ���ź� */
#define PIOB_4          20        /**< \brief PIOB_4 ���ź� */
#define PIOB_5          21        /**< \brief PIOB_5 ���ź� */
#define PIOB_6          22        /**< \brief PIOB_3 ���ź� */
#define PIOB_7          23        /**< \brief PIOB_4 ���ź� */
#define PIOB_8          24        /**< \brief PIOB_5 ���ź� */
#define PIOB_9          25        /**< \brief PIOB_5 ���ź� */
#define PIOB_10         26        /**< \brief PIOB_10���ź� */
#define PIOB_11         27        /**< \brief PIOB_11���ź� */
#define PIOB_12         28        /**< \brief PIOB_12���ź� */
#define PIOB_13         29        /**< \brief PIOB_13���ź� */
#define PIOB_14         30        /**< \brief PIOB_14���ź� */
#define PIOB_15         31        /**< \brief PIOB_15���ź� */

#define PIOC            32        /**< \brief �˿�C������ʼ�� */
#define PIOC_0          32        /**< \brief PIOC_13���ź� */
#define PIOC_1          33        /**< \brief PIOC_13���ź� */
#define PIOC_2          34        /**< \brief PIOC_13���ź� */
#define PIOC_3          35        /**< \brief PIOC_13���ź� */
#define PIOC_4          36        /**< \brief PIOC_13���ź� */
#define PIOC_5          37        /**< \brief PIOC_13���ź� */
#define PIOC_6          38        /**< \brief PIOC_13���ź� */
#define PIOC_7          39        /**< \brief PIOC_13���ź� */
#define PIOC_8          40        /**< \brief PIOC_13���ź� */
#define PIOC_9          41        /**< \brief PIOC_13���ź� */
#define PIOC_10         42        /**< \brief PIOC_13���ź� */
#define PIOC_11         43        /**< \brief PIOC_13���ź� */
#define PIOC_12         44        /**< \brief PIOC_13���ź� */
#define PIOC_13         45        /**< \brief PIOC_13���ź� */
#define PIOC_14         46        /**< \brief PIOC_14���ź� */
#define PIOC_15         47        /**< \brief PIOC_15���ź� */

#define PIOD            48        /**< \brief �˿�D������ʼ�� */
#define PIOD_0          48        /**< \brief PIOD_0  ���ź� */
#define PIOD_1          49        /**< \brief PIOD_1  ���ź� */
#define PIOD_2          50        /**< \brief PIOD_2  ���ź� */
#define PIOD_3          51        /**< \brief PIOD_3  ���ź� */
#define PIOD_4          52        /**< \brief PIOD_4  ���ź� */
#define PIOD_5          53        /**< \brief PIOD_5  ���ź� */
#define PIOD_6          54        /**< \brief PIOD_6  ���ź� */
#define PIOD_7          55        /**< \brief PIOD_7  ���ź� */
#define PIOD_8          56        /**< \brief PIOD_8  ���ź� */
#define PIOD_9          57        /**< \brief PIOD_9  ���ź� */
#define PIOD_10         58        /**< \brief PIOD_10 ���ź� */
#define PIOD_11         59        /**< \brief PIOD_11 ���ź� */
#define PIOD_12         60        /**< \brief PIOD_12 ���ź� */
#define PIOD_13         61        /**< \brief PIOD_13 ���ź� */
#define PIOD_14         62        /**< \brief PIOD_14 ���ź� */
#define PIOD_15         63        /**< \brief PIOD_15 ���ź� */

#define PIOE            64        /**< \brief �˿�E������ʼ�� */
#define PIOE_0          64        /**< \brief PIOE_0  ���ź� */
#define PIOE_1          65        /**< \brief PIOE_1  ���ź� */
#define PIOE_2          66        /**< \brief PIOE_2  ���ź� */
#define PIOE_3          67        /**< \brief PIOE_3  ���ź� */
#define PIOE_4          68        /**< \brief PIOE_4  ���ź� */
#define PIOE_5          69        /**< \brief PIOE_5  ���ź� */
#define PIOE_6          70        /**< \brief PIOE_6  ���ź� */
#define PIOE_7          71        /**< \brief PIOE_7  ���ź� */
#define PIOE_8          70        /**< \brief PIOE_8  ���ź� */
#define PIOE_9          73        /**< \brief PIOE_9  ���ź� */
#define PIOE_10         74        /**< \brief PIOE_10 ���ź� */
#define PIOE_11         75        /**< \brief PIOE_11 ���ź� */
#define PIOE_12         76        /**< \brief PIOE_12 ���ź� */
#define PIOE_13         77        /**< \brief PIOE_13 ���ź� */
#define PIOE_14         78        /**< \brief PIOE_14 ���ź� */
#define PIOE_15         79        /**< \brief PIOE_15 ���ź� */

#define PIOF            80       /**< \brief �˿�F������ʼ�� */
#define PIOF_0          80       /**< \brief PIOF_0   ���ź� */
#define PIOF_1          81       /**< \brief PIOF_1   ���ź� */
#define PIOF_2          82       /**< \brief PIOF_2   ���ź� */
#define PIOF_3          83       /**< \brief PIOF_3   ���ź� */
//#define PIOF_4          84       /**< \brief PIOF_4   ���ź� */
//#define PIOF_5          85       /**< \brief PIOF_5   ���ź� */
#define PIOF_6          86       /**< \brief PIOF_6   ���ź� */
//#define PIOF_7          87       /**< \brief PIOF_7   ���ź� */

/* ��PIOF_8�������ڼĴ�������Ȼռ���˼Ĵ���λ�ã��ر�ע�ⲻҪ�������ű�� */

#define PIOF_9          89       /**< \brief PIOF_9   ���ź� */
#define PIOF_10         90       /**< \brief PIOF_10  ���ź� */
#define PIOF_11         91       /**< \brief PIOF_11  ���ź� */

/**
 * \brief ������ĿΪ96
 */
#define PIN_NUM         92

/**
 * \brief ֧��ͬʱ������������ж�����92
 */
#define PIN_INT_MAX     92

/** @} */

/**
 * \name HC32 ���Ŷ���,����������SWCK��SWIO֮�⣬�������Ÿ�λʱ��Ĭ��ΪGPIO����(��������)
 * @{
 */

/******************************************************************************/


/**
 * \name PIO���Ÿ���ʱ����ģʽ(ͨ��)
 * @{
 */
#define PIO_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIO_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIO_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIO_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIO_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIO_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIO_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_0���Ÿ��ù���
 * @{
 */
#define PIOA_0_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_0_UART1_CTS      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_0_LPUART1_TXD    AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_0_TIM0_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_0_VC0_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_0_TIM1_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_0_TIM3_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_0_TIM0_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_0���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_0_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_0_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_0_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_0_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_0_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_0_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_0_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_1���Ÿ��ù���
 * @{
 */
#define PIOA_1_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_1_UART1_RTS      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_1_LPUART1_RXD    AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_1_TIM0_CHB       AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_1_TIM1_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_1_TIM1_CHB       AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_1_HCLK_OUT       AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_1_SPI1_MOSI      AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_1���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_1_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_1_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_1_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_1_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_1_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_1_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_1_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_2���Ÿ��ù���
 * @{
 */
#define PIOA_2_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_2_UART1_TXD      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_2_TIM0_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_2_VC1_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_2_TIM1_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_2_TIM2_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_2_PCLK_OUT       AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_2_SPI1_MISO      AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_2_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_2_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_2_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_2_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_2_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_2_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_2_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_3���Ÿ��ù���
 * @{
 */
#define PIOA_3_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_3_UART1_RXD      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_3_TIM0_GATE      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_3_TIM1_CHB       AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_3_TIM2_CHB       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_3_SPI1_CS        AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_3_TIM3_CH1A      AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_3_TIM5_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_3���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_3_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_3_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_3_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_3_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_3_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_3_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_3_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_4���Ÿ��ù���
 * @{
 */
#define PIOA_4_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_4_SPI0_CS        AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_4_UART1_TXD      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_4_PCA_CH4        AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_4_TIM2_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_4_TIM5_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_4_LVD_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_4_TIM3_CH2B      AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_4���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_4_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_4_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_4_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_4_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_4_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_4_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_4_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_5���Ÿ��ù���
 * @{
 */
#define PIOA_5_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_5_SPI0_SCK       AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_5_TIM0_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_5_PCA_ECI        AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_5_TIM0_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_5_TIM5_CHB       AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_5_XTL_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_5_XTH_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_5���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_5_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_5_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_5_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_5_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_5_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_5_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_5_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_6���Ÿ��ù���
 * @{
 */
#define PIOA_6_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_6_SPI0_MISO      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_6_PCA_CH0        AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_6_TIM3_BK        AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_6_TIM1_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_6_VC0_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_6_TIM3_GATE      AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_6_LPUART0_CTS    AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_6���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_6_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_6_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_6_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_6_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_6_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_6_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_6_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_7���Ÿ��ù���
 * @{
 */
#define PIOA_7_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_7_SPI0_MOSI      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_7_PCA_CH1        AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_7_HCLK_OUT       AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_7_TIM3_CH0B      AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_7_TIM2_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_7_VC1_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_7_TIM4_CHB       AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_7���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_7_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_7_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_7_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_7_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_7_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_7_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_7_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_8���Ÿ��ù���
 * @{
 */
#define PIOA_8_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_8_UART0_TXD      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_8_TIM3_CH0A      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_8_CRS_SYNC       AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_8_CAN_STBY       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_8_TIM1_GATE      AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_8_TIM4_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_8_TIM3_BK        AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_8���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_8_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_8_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_8_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_8_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_8_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_8_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_8_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_9���Ÿ��ù���
 * @{
 */
#define PIOA_9_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_9_UART0_TXD      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_9_TIM3_CH1A      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_9_TIM0_BK        AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_9_I2C0_SCL       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_9_HCLK_OUT       AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_9_TIM5_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_9���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_9_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_9_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_9_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_9_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_9_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_9_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_9_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_10���Ÿ��ù���
 * @{
 */
#define PIOA_10_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_10_UART0_RXD      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_10_TIM3_CH2A      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_10_TIM2_BK        AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_10_I2C0_SDA       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_10_TIM2_GATE      AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_10_PCLK_OUT       AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_10_TIM6_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_10���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_10_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_10_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_10_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_10_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_10_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_10_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_10_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

///**
// * \name PIOA_11���Ÿ��ù���
// * @{
// */
//#define PIOA_11_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
//#define PIOA_11_UART0_CTS      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
//#define PIOA_11_TIM3_GATE      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
//#define PIOA_11_I2C1_SCL       AM_HC32_GPIO_REMAP_CODE(0x01, 3)
//#define PIOA_11_VC0_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 5)
//#define PIOA_11_SPI0_MISO      AM_HC32_GPIO_REMAP_CODE(0x01, 6)
//#define PIOA_11_TIM4_CHB       AM_HC32_GPIO_REMAP_CODE(0x01, 7)

///** @} */

///**
// * \name PIOA_11���Ÿ���ʱ����ģʽ
// * @{
// */
//#define PIOA_11_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
//#define PIOA_11_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
//#define PIOA_11_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
//#define PIOA_11_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
//#define PIOA_11_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
//#define PIOA_11_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
//#define PIOA_11_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
///** @} */

/**
 * \name PIOA_12���Ÿ��ù���
 * @{
 */
#define PIOA_12_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_12_UART0_RTS      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_12_TIM3_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_12_I2C1_SDA       AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_12_VC1_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_12_SPI0_MOSI      AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_12_PCNT_S0        AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_12���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_12_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_12_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_12_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_12_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_12_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_12_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_12_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_13���Ÿ��ù���
 * @{
 */
#define PIOA_13_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_13_IR_OUT         AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_13_UART0_RXD      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_13_LVD_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_13_TIM3_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_13_VC2_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_13���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_13_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_13_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_13_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_13_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_13_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_13_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_13_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_14���Ÿ��ù���
 * @{
 */
#define PIOA_14_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_14_UART1_TXD      AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_14_UART0_TXD      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_14_TIM3_CH2A      AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_14_LVD_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_14_RCH_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_14_RCL_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 6)
#define PIOA_14_PLL_OUT        AM_HC32_GPIO_REMAP_CODE(0x01, 7)

/** @} */

/**
 * \name PIOA_14���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_14_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_14_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_14_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_14_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_14_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_14_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_14_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOA_15���Ÿ��ù���
 * @{
 */
#define PIOA_15_GPIO           AM_HC32_GPIO_REMAP_CODE(0x01, 0)
#define PIOA_15_SPI0_CS        AM_HC32_GPIO_REMAP_CODE(0x01, 1)
#define PIOA_15_UART1_RXD      AM_HC32_GPIO_REMAP_CODE(0x01, 2)
#define PIOA_15_LPUART1_RTS    AM_HC32_GPIO_REMAP_CODE(0x01, 3)
#define PIOA_15_TIM0_ETR       AM_HC32_GPIO_REMAP_CODE(0x01, 4)
#define PIOA_15_TIM0_CHA       AM_HC32_GPIO_REMAP_CODE(0x01, 5)
#define PIOA_15_TIM3_CH1A      AM_HC32_GPIO_REMAP_CODE(0x01, 6)

/** @} */

/**
 * \name PIOA_15���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_15_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOA_15_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOA_15_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOA_15_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_15_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOA_15_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOA_15_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_0���Ÿ��ù���
 * @{
 */
#define PIOB_0_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_0_PCA_CH2        AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_0_TIM3_CH1B      AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_0_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_0_TIM5_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_0_RCH_OUT        AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_0_RCL_OUT        AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_0_PLL_OUT        AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_0���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_0_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_0_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_0_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_0_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_0_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_0_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_0_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_1���Ÿ��ù���
 * @{
 */
#define PIOB_1_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_1_PCA_CH3        AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_1_PCLK_OUT       AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_1_TIM3_CH2B      AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_1_TIM6_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_1_LPUART0_RTS    AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_1_VC2_OUT        AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_1_TCLK_OUT       AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_1���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_1_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_1_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_1_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_1_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_1_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_1_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_1_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_2���Ÿ��ù���
 * @{
 */
#define PIOB_2_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_2_PCA_ECI        AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_2_LPUART1_TXD    AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_2_TIM4_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_2_TIM1_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_2_TIM0_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_2_TIM2_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_2���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_2_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_2_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_2_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_2_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_2_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_2_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_2_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_3���Ÿ��ù���
 * @{
 */
#define PIOB_3_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_3_SPI0_SCK       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_3_TIM0_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_3_TIM1_GATE      AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_3_TIM3_CH0A      AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_3_XTL_OUT        AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_3_XTH_OUT        AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_3���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_3_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_3_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_3_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_3_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_3_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_3_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_3_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_4���Ÿ��ù���
 * @{
 */
#define PIOB_4_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_4_SPI0_MISO      AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_4_PCA_CH0        AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_4_TIM2_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_4_UART0_CTS      AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_4_TIM2_GATE      AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_4_TIM3_CH0B      AM_HC32_GPIO_REMAP_CODE(0x02, 6)

/** @} */

/**
 * \name PIOB_4���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_4_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_4_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_4_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_4_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_4_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_4_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_4_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_5���Ÿ��ù���
 * @{
 */
#define PIOB_5_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_5_SPI0_MOSI      AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_5_TIM1_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_5_PCA_CH1        AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_5_UART0_RTS      AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_5���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_5_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_5_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_5_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_5_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_5_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_5_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_5_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_6���Ÿ��ù���
 * @{
 */
#define PIOB_6_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_6_I2C0_SCL       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_6_UART0_TXD      AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_6_TIM1_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_6_TIM0_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_6_TIM3_CH0A      AM_HC32_GPIO_REMAP_CODE(0x02, 6)

/** @} */

/**
 * \name PIOB_6���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_6_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_6_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_6_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_6_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_6_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_6_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_6_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_7���Ÿ��ù���
 * @{
 */
#define PIOB_7_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_7_I2C0_SDA       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_7_UART0_RXD      AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_7_TIM2_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_7_LPUART1_CTS    AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_7_TIM0_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_7_LPTIM0_TOGN    AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_7_PCNT_S1        AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_7���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_7_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_7_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_7_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_7_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_7_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_7_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_7_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_8���Ÿ��ù���
 * @{
 */
#define PIOB_8_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_8_I2C0_SCL       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_8_TIM1_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_8_CAN_RX         AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_8_TIM2_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_8_TIM0_GATE      AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_8_TIM3_CH2A      AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_8_UART0_TXD      AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_8���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_8_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_8_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_8_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_8_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_8_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_8_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_8_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_9���Ÿ��ù���
 * @{
 */
#define PIOB_9_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_9_I2C0_SDA       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_9_IR_OUT         AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_9_SPI1_CS        AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_9_TIM2_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_9_CAN_TX         AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_9_TIM2_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_9_UART0_RXD      AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_9���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_9_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_9_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_9_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_9_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_9_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_9_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_9_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_10���Ÿ��ù���
 * @{
 */
#define PIOB_10_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_10_I2C1_SCL       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_10_SPI1_SCK       AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_10_TIM1_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_10_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_10_TIM3_CH1A      AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_10_LPUART1_RTS    AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_10_UART1_RTS      AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_10���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_10_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_10_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_10_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_10_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_10_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_10_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_10_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_11���Ÿ��ù���
 * @{
 */
#define PIOB_11_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_11_I2C1_SDA       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_11_TIM1_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_11_LPUART0_RXD    AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_11_TIM2_GATE      AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_11_TIM6_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_11_LPUART1_CTS    AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_11_UART1_CTS      AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_11���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_11_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_11_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_11_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_11_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_11_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_11_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_11_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_12���Ÿ��ù���
 * @{
 */
#define PIOB_12_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_12_SPI1_CS        AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_12_TIM3_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_12_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_12_TIM0_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_12_LPUART0_RTS    AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_12_TIM6_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_12���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_12_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_12_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_12_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_12_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_12_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_12_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_12_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_13���Ÿ��ù���
 * @{
 */
#define PIOB_13_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_13_SPI1_SCK       AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_13_I2C1_SCL       AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_13_TIM3_CH0B      AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_13_LPUART0_CTS    AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_13_TIM1_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 5)
#define PIOB_13_TIM1_GATE      AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_13_TIM6_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_13���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_13_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_13_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_13_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_13_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_13_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_13_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_13_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_14���Ÿ��ù���
 * @{
 */
#define PIOB_14_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_14_SPI1_MISO      AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_14_I2C1_SDA       AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_14_TIM3_CH1B      AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_14_TIM0_CHA       AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_14_LPUART0_RTS    AM_HC32_GPIO_REMAP_CODE(0x02, 6)
#define PIOB_14_TIM1_BK        AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_14���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_14_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_14_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_14_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_14_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_14_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_14_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_14_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOB_15���Ÿ��ù���
 * @{
 */
#define PIOB_15_GPIO           AM_HC32_GPIO_REMAP_CODE(0x02, 0)
#define PIOB_15_SPI1_MOSI      AM_HC32_GPIO_REMAP_CODE(0x02, 1)
#define PIOB_15_TIM3_CH2B      AM_HC32_GPIO_REMAP_CODE(0x02, 2)
#define PIOB_15_TIM0_CHB       AM_HC32_GPIO_REMAP_CODE(0x02, 3)
#define PIOB_15_TIM0_GATE      AM_HC32_GPIO_REMAP_CODE(0x02, 4)
#define PIOB_15_LPUART1_RXD    AM_HC32_GPIO_REMAP_CODE(0x02, 7)

/** @} */

/**
 * \name PIOB_15���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOB_15_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOB_15_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOB_15_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOB_15_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_15_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOB_15_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOB_15_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_0���Ÿ��ù���
 * @{
 */
#define PIOC_0_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_0_UART1_CTS      AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_0_UART2_RTS      AM_HC32_GPIO_REMAP_CODE(0x03, 4)
#define PIOC_0_I2S0_MCK       AM_HC32_GPIO_REMAP_CODE(0x03, 5)

/** @} */

/**
 * \name PIOC_0���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_0_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_0_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_0_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_0_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_0_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_0_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_0_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_1���Ÿ��ù���
 * @{
 */
#define PIOC_1_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_1_TIM5_CHB       AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_1_UART1_RTS      AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_1_I2S0_SD        AM_HC32_GPIO_REMAP_CODE(0x03, 5)
#define PIOC_1_UART2_CTS      AM_HC32_GPIO_REMAP_CODE(0x03, 6)

/** @} */

/**
 * \name PIOC_1���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_1_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_1_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_1_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_1_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_1_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_1_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_1_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_2���Ÿ��ù���
 * @{
 */
#define PIOC_2_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_2_SPI1_MISO      AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_2_UART2_RXD      AM_HC32_GPIO_REMAP_CODE(0x03, 4)

/** @} */

/**
 * \name PIOC_2���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_2_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_2_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_2_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_2_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_2_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_2_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_2_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_3���Ÿ��ù���
 * @{
 */
#define PIOC_3_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_3_SPI1_MOSI      AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_3_UART2_TXD      AM_HC32_GPIO_REMAP_CODE(0x03, 5)

/** @} */

/**
 * \name PIOC_3���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_3_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_3_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_3_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_3_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_3_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_3_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_3_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_4���Ÿ��ù���
 * @{
 */
#define PIOC_4_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_4_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_4_TIM2_ETR       AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_4_IR_OUT         AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_4_VC2_OUT        AM_HC32_GPIO_REMAP_CODE(0x03, 4)
#define PIOC_4_I2S0_WS        AM_HC32_GPIO_REMAP_CODE(0x03, 5)

/** @} */

/**
 * \name PIOC_4���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_4_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_4_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_4_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_4_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_4_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_4_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_4_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_5���Ÿ��ù���
 * @{
 */
#define PIOC_5_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_5_LPUART0_RXD    AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_5_TIM6_CHB       AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_5_PCA_CH4        AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_5_I2S0_SDIN      AM_HC32_GPIO_REMAP_CODE(0x03, 5)

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_5_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_5_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_5_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_5_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_5_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_5_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_5_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_6���Ÿ��ù���
 * @{
 */
#define PIOC_6_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_6_PCA_CH0        AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_6_TIM4_CHA       AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_6_TIM2_CHA       AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_6_I2S1_SCK       AM_HC32_GPIO_REMAP_CODE(0x03, 5)
#define PIOC_6_UART3_RXD      AM_HC32_GPIO_REMAP_CODE(0x03, 6)

/** @} */

/**
 * \name PIOC_6���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_6_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_6_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_6_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_6_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_6_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_6_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_6_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_7���Ÿ��ù���
 * @{
 */
#define PIOC_7_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_7_PCA_CH1        AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_7_TIM5_CHA       AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_7_TIM2_CHB       AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_7_I2S1_MCK       AM_HC32_GPIO_REMAP_CODE(0x03, 5)
#define PIOC_7_UART3_TXD      AM_HC32_GPIO_REMAP_CODE(0x03, 6)

/** @} */

/**
 * \name PIOC_7���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_7_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_7_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_7_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_7_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_7_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_7_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_7_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_8���Ÿ��ù���
 * @{
 */
#define PIOC_8_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_8_PCA_CH2        AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_8_TIM6_CHA       AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_8_TIM2_ETR       AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_8_I2S1_SD        AM_HC32_GPIO_REMAP_CODE(0x03, 5)
#define PIOC_8_UART3_CTS      AM_HC32_GPIO_REMAP_CODE(0x03, 6)

/** @} */

/**
 * \name PIOC_8���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_8_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_8_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_8_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_8_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_8_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_8_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_8_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_9���Ÿ��ù���
 * @{
 */
#define PIOC_9_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_9_PCA_CH3        AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_9_TIM4_CHB       AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_9_TIM1_ETR       AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_9_I2S1_WS        AM_HC32_GPIO_REMAP_CODE(0x03, 5)
#define PIOC_9_UART3_RTS      AM_HC32_GPIO_REMAP_CODE(0x03, 6)

/** @} */

/**
 * \name PIOC_9���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_9_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_9_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_9_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_9_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_9_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_9_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_9_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_10���Ÿ��ù���
 * @{
 */
#define PIOC_10_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_10_LPUART1_TXD    AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_10_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_10_PCA_CH2        AM_HC32_GPIO_REMAP_CODE(0x03, 3)

/** @} */

/**
 * \name PIOC_10���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_10_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_10_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_10_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_10_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_10_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_10_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_10_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_11���Ÿ��ù���
 * @{
 */
#define PIOC_11_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_11_LPUART1_RXD    AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_11_LPUART0_RXD    AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_11_PCA_CH3        AM_HC32_GPIO_REMAP_CODE(0x03, 3)

/** @} */

/**
 * \name PIOC_11���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_11_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_11_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_11_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_11_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_11_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_11_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_11_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_12���Ÿ��ù���
 * @{
 */
#define PIOC_12_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_12_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x03, 1)
#define PIOC_12_LPUART1_TXD    AM_HC32_GPIO_REMAP_CODE(0x03, 2)
#define PIOC_12_PCA_CH4        AM_HC32_GPIO_REMAP_CODE(0x03, 3)

/** @} */

/**
 * \name PIOC_12���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_12_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_12_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_12_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_12_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_12_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_12_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_12_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_13���Ÿ��ù���
 * @{
 */
#define PIOC_13_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)
#define PIOC_13_TIM3_CH1B      AM_HC32_GPIO_REMAP_CODE(0x03, 3)
#define PIOC_13_I2S0_SCK       AM_HC32_GPIO_REMAP_CODE(0x03, 5)

/** @} */

/**
 * \name PIOC_13���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_13_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_13_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_13_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_13_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_13_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_13_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_13_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_14���Ÿ��ù���
 * @{
 */
#define PIOC_14_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)

/** @} */

/**
 * \name PIOC_14���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_14_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_14_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_14_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_14_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_14_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_14_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_14_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOC_15���Ÿ��ù���
 * @{
 */
#define PIOC_15_GPIO           AM_HC32_GPIO_REMAP_CODE(0x03, 0)

/** @} */

/**
 * \name PIOC_15���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOC_15_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOC_15_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOC_15_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOC_15_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_15_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOC_15_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOC_15_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */
/**
 * \name PIOD_0���Ÿ��ù���
 * @{
 */
#define PIOD_0_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_0_CAN_RX         AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_0_SPI1_CS        AM_HC32_GPIO_REMAP_CODE(0x04, 2)
/** @} */

/**
 * \name PIOD_0���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_0_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_0_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_0_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_0_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_0_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_0_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_0_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_1���Ÿ��ù���
 * @{
 */
#define PIOD_1_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_1_CAN_TX         AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_1_SPI1_SCK       AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_1���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_1_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_1_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_1_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_1_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_1_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_1_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_1_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_2���Ÿ��ù���
 * @{
 */
#define PIOD_2_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_2_PCA_ECI        AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_2_LPUART0_RTS    AM_HC32_GPIO_REMAP_CODE(0x04, 2)
#define PIOD_2_TIM1_ETR       AM_HC32_GPIO_REMAP_CODE(0x04, 3)

/** @} */

/**
 * \name PIOD_2���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_2_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_2_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_2_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_2_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_2_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_2_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_2_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */
#define PIOD_3_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_3_UART1_CTS      AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_3_SPI1_MISO      AM_HC32_GPIO_REMAP_CODE(0x04, 2)
#define PIOD_3_I2S1_SCK       AM_HC32_GPIO_REMAP_CODE(0x04, 4)

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_3_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_3_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_3_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_3_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_3_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_3_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_3_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_4���Ÿ��ù���
 * @{
 */
#define PIOD_4_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_4_UART1_RTS      AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_4_SPI1_MOSI      AM_HC32_GPIO_REMAP_CODE(0x04, 2)
#define PIOD_4_I2S1_MCK       AM_HC32_GPIO_REMAP_CODE(0x04, 4)

/** @} */

/**
 * \name PIOD_4���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_4_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_4_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_4_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_4_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_4_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_4_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_4_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_5���Ÿ��ù���
 * @{
 */
#define PIOD_5_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_5_UART1_TXD      AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_5_CAN_STBY       AM_HC32_GPIO_REMAP_CODE(0x04, 3)
#define PIOD_5_I2S1_SD        AM_HC32_GPIO_REMAP_CODE(0x04, 4)

/** @} */

/**
 * \name PIOD_5���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_5_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_5_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_5_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_5_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_5_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_5_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_5_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_6���Ÿ��ù���
 * @{
 */
#define PIOD_6_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_6_UART1_RXD      AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_6_I2S1_WS        AM_HC32_GPIO_REMAP_CODE(0x04, 4)

/** @} */

/**
 * \name PIOD_6���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_6_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_6_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_6_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_6_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_6_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_6_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_6_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_7���Ÿ��ù���
 * @{
 */
#define PIOD_7_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_7_UART1_TXD      AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_7_I2S1_SDIN      AM_HC32_GPIO_REMAP_CODE(0x04, 4)

/** @} */

/**
 * \name PIOD_7���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_7_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_7_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_7_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_7_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_7_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_7_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_7_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_8���Ÿ��ù���
 * @{
 */
#define PIOD_8_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_8_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_8_I2S0_SCK       AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_8���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_8_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_8_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_8_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_8_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_8_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_8_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_8_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_9���Ÿ��ù���
 * @{
 */
#define PIOD_9_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_9_LPUART0_RXD    AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_9_I2S0_MCK        AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_9���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_9_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_9_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_9_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_9_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_9_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_9_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_9_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_10���Ÿ��ù���
 * @{
 */
#define PIOD_10_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_10_LPUART0_TXD    AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_10_I2S0_SD        AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_10���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_10_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_10_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_10_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_10_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_10_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_10_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_10_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_11���Ÿ��ù���
 * @{
 */
#define PIOD_11_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_11_LPUART0_CTS    AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_11_I2S0_WS        AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_11���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_11_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_11_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_11_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_11_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_11_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_11_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_11_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_12���Ÿ��ù���
 * @{
 */
#define PIOD_12_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_12_LPUART0_RTS    AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_12_UART2_RTS      AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_12���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_12_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_12_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_12_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_12_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_12_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_12_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_12_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_13���Ÿ��ù���
 * @{
 */
#define PIOD_13_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_13_UART2_RXD      AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_13_I2S0_SDIN      AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_13���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_13_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_13_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_13_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_13_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_13_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_13_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_13_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_14���Ÿ��ù���
 * @{
 */
#define PIOD_14_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_14_UART2_TXD      AM_HC32_GPIO_REMAP_CODE(0x04, 1)

/** @} */

/**
 * \name PIOD_14���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_14_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_14_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_14_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_14_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_14_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_14_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_14_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOD_15���Ÿ��ù���
 * @{
 */
#define PIOD_15_GPIO           AM_HC32_GPIO_REMAP_CODE(0x04, 0)
#define PIOD_15_CRS_SYNC       AM_HC32_GPIO_REMAP_CODE(0x04, 1)
#define PIOD_15_UART2_CTS      AM_HC32_GPIO_REMAP_CODE(0x04, 2)

/** @} */

/**
 * \name PIOD_15���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOD_15_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOD_15_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOD_15_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOD_15_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_15_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOD_15_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOD_15_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */
#define PIOE_0_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_0_TIM1_CHA       AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_0_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_0_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_0_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_0_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_0_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_0_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_0_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_1���Ÿ��ù���
 * @{
 */
#define PIOE_1_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_1_TIM2_CHA       AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_1���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_1_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_1_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_1_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_1_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_1_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_1_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_1_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_2���Ÿ��ù���
 * @{
 */
#define PIOE_2_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_2_PCA_ECI        AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_2���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_2_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_2_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_2_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_2_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_2_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_2_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_2_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_3���Ÿ��ù���
 * @{
 */
#define PIOE_3_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_3_PCA_CH0        AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_3���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_3_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_3_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_3_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_3_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_3_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_3_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_3_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_4���Ÿ��ù���
 * @{
 */
#define PIOE_4_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_4_PCA_CH1        AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_4���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_4_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_4_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_4_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_4_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_4_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_4_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_4_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_5���Ÿ��ù���
 * @{
 */
#define PIOE_5_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_5_PCA_CH2        AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_5���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_5_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_5_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_5_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_5_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_5_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_5_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_5_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */
/**
 * \name PIOE_6���Ÿ��ù���
 * @{
 */
#define PIOE_6_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_6_PCA_CH3        AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_6���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_6_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_6_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_6_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_6_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_6_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_6_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_6_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */
/**
 * \name PIOE_7���Ÿ��ù���
 * @{
 */
#define PIOE_7_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_7_TIM3_ETR       AM_HC32_GPIO_REMAP_CODE(0x05, 1)
/** @} */

/**
 * \name PIOE_7���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_7_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_7_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_7_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_7_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_7_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_7_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_7_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_8���Ÿ��ù���
 * @{
 */
#define PIOE_8_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_8_TIM3_CH0B      AM_HC32_GPIO_REMAP_CODE(0x05, 1)
/** @} */

/**
 * \name PIOE_8���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_8_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_8_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_8_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_8_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_8_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_8_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_8_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_9���Ÿ��ù���
 * @{
 */
#define PIOE_9_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_9_TIM3_CH0A      AM_HC32_GPIO_REMAP_CODE(0x05, 1)
/** @} */

/**
 * \name PIOE_9���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_9_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_9_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_9_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_9_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_9_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_9_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_9_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_10���Ÿ��ù���
 * @{
 */
#define PIOE_10_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_10_TIM3_CH1B      AM_HC32_GPIO_REMAP_CODE(0x05, 1)

/** @} */

/**
 * \name PIOE_10���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_10_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_10_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_10_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_10_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_10_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_10_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_10_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */
/**
 * \name PIOE_11���Ÿ��ù���
 * @{
 */
#define PIOE_11_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_11_TIM3_CH1A      AM_HC32_GPIO_REMAP_CODE(0x05, 1)
/** @} */

/**
 * \name PIOE_11���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_11_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_11_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_11_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_11_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_11_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_11_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_11_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_12���Ÿ��ù���
 * @{
 */
#define PIOE_12_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_12_TIM3_CH2B      AM_HC32_GPIO_REMAP_CODE(0x05, 1)
#define PIOE_12_SPI0_CS        AM_HC32_GPIO_REMAP_CODE(0x05, 2)
#define PIOE_12_UART3_CTS      AM_HC32_GPIO_REMAP_CODE(0x05, 3)

/** @} */

/**
 * \name PIOE_12���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_12_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_12_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_12_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_12_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_12_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_12_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_12_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_13���Ÿ��ù���
 * @{
 */
#define PIOE_13_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_13_TIM3_CH2A      AM_HC32_GPIO_REMAP_CODE(0x05, 1)
#define PIOE_13_SPI0_SCK       AM_HC32_GPIO_REMAP_CODE(0x05, 2)
#define PIOE_13_UART3_RTS      AM_HC32_GPIO_REMAP_CODE(0x05, 3)

/** @} */

/**
 * \name PIOE_13���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_13_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_13_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_13_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_13_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_13_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_13_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_13_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_14���Ÿ��ù���
 * @{
 */
#define PIOE_14_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_14_TIM3_CH0B      AM_HC32_GPIO_REMAP_CODE(0x05, 1)
#define PIOE_14_SPI0_MISO      AM_HC32_GPIO_REMAP_CODE(0x05, 2)
#define PIOE_14_UART3_RXD      AM_HC32_GPIO_REMAP_CODE(0x05, 3)

/** @} */

/**
 * \name PIOE_14���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_14_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_14_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_14_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_14_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_14_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_14_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_14_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOE_15���Ÿ��ù���
 * @{
 */
#define PIOE_15_GPIO           AM_HC32_GPIO_REMAP_CODE(0x05, 0)
#define PIOE_15_TIM3_BK        AM_HC32_GPIO_REMAP_CODE(0x05, 1)
#define PIOE_15_SPI0_MOSI      AM_HC32_GPIO_REMAP_CODE(0x05, 2)
#define PIOE_15_UART3_TXD      AM_HC32_GPIO_REMAP_CODE(0x05, 3)

/** @} */

/**
 * \name PIOE_15���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOE_15_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOE_15_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOE_15_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOE_15_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_15_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOE_15_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOE_15_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_0���Ÿ��ù���
 * @{
 */
#define PIOF_0_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)
#define PIOF_0_I2C0_SDA       AM_HC32_GPIO_REMAP_CODE(0x06, 1)
#define PIOF_0_CRS_SYNC       AM_HC32_GPIO_REMAP_CODE(0x06, 2)
#define PIOF_0_UART1_TXD      AM_HC32_GPIO_REMAP_CODE(0x06, 3)

/** @} */

/**
 * \name PIOF_0���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_0_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_0_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_0_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_0_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_0_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_0_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_0_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_1���Ÿ��ù���
 * @{
 */
#define PIOF_1_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)
#define PIOF_1_I2C0_SCL       AM_HC32_GPIO_REMAP_CODE(0x06, 1)
#define PIOF_1_TIM4_CHB       AM_HC32_GPIO_REMAP_CODE(0x06, 2)
#define PIOF_1_UART1_RXD      AM_HC32_GPIO_REMAP_CODE(0x06, 3)

/** @} */

/**
 * \name PIOF_1���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_1_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_1_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_1_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_1_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_1_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_1_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_1_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_2���Ÿ��ù���
 * @{
 */
#define PIOF_2_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)

/** @} */

/**
 * \name PIOF_2���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_2_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_2_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_2_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_2_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_2_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_2_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_2_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_3���Ÿ��ù���
 * @{
 */
#define PIOF_3_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)

/** @} */

/**
 * \name PIOF_3���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_3_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_3_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_3_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_3_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_3_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_3_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_3_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_4���Ÿ��ù���
 * @{
 */
#define PIOF_4_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)

/** @} */

/**
 * \name PIOF_4���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_4_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_4_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_4_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_4_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_4_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_4_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_4_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_5���Ÿ��ù���
 * @{
 */
#define PIOF_5_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)

/** @} */

/**
 * \name PIOF_5���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_5_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_5_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_5_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_5_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_5_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_5_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_5_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_6���Ÿ��ù���
 * @{
 */
#define PIOF_6_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)
#define PIOF_6_I2C1_SCL       AM_HC32_GPIO_REMAP_CODE(0x06, 1)
#define PIOF_6_LPUART1_CTS    AM_HC32_GPIO_REMAP_CODE(0x06, 2)
#define PIOF_6_UART0_CTS      AM_HC32_GPIO_REMAP_CODE(0x06, 3)

/** @} */

/**
 * \name PIOF_6���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_6_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_6_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_6_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_6_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_6_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_6_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_6_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_7���Ÿ��ù���
 * @{
 */
#define PIOF_7_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)
#define PIOF_7_I2C1_SDA       AM_HC32_GPIO_REMAP_CODE(0x06, 1)
#define PIOF_7_LPUART1_RTS    AM_HC32_GPIO_REMAP_CODE(0x06, 2)
#define PIOF_7_UART0_RTS      AM_HC32_GPIO_REMAP_CODE(0x06, 3)

/** @} */

/**
 * \name PIOF_7���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_7_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_7_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_7_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_7_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_7_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_7_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_7_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_9���Ÿ��ù���
 * @{
 */
#define PIOF_9_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)
#define PIOF_9_TIM0_CHA       AM_HC32_GPIO_REMAP_CODE(0x06, 1)

/** @} */

/**
 * \name PIOF_9���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_9_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_9_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_9_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_9_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_9_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_9_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_9_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_10���Ÿ��ù���
 * @{
 */
#define PIOF_10_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)
#define PIOF_10_TIM0_CHB       AM_HC32_GPIO_REMAP_CODE(0x06, 1)

/** @} */

/**
 * \name PIOF_10���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_10_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_10_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_10_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_10_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_10_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_10_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_10_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/**
 * \name PIOF_11���Ÿ��ù���
 * @{
 */
#define PIOF_11_GPIO           AM_HC32_GPIO_REMAP_CODE(0x06, 0)

/** @} */

/**
 * \name PIOF_11���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOF_11_INPUT_PU       AM_HC32_GPIO_MODE_CODE(0x0)   /**< \brief ��������ģʽ (Ĭ��) */
#define PIOF_11_INPUT_PD       AM_HC32_GPIO_MODE_CODE(0x1)   /**< \brief ��������ģʽ */
#define PIOF_11_AIN            AM_HC32_GPIO_MODE_CODE(0x2)   /**< \brief ģ������ģʽ */
#define PIOF_11_INPUT_FLOAT    AM_HC32_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOF_11_OUT_PP         AM_HC32_GPIO_MODE_CODE(0x4)   /**< \brief �������ģʽ */
#define PIOF_11_OUT_OD         AM_HC32_GPIO_MODE_CODE(0x5)   /**< \brief ��©���ģʽ */
#define PIOF_11_AOUT           AM_HC32_GPIO_MODE_CODE(0x6)   /**< \brief ģ�����ģʽ */
/** @} */

/******************************************************************************/

/**
 * @}
 */

/**
 * @}if_hc32_pin
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_PIN_H */

/* end of file */
