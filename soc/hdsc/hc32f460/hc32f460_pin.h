/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (cUL) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief HC32F460 GPIO �������ò�������
 *
 * \note: �������Ź��ܵ�ʱ��һ��Ҫͬʱ�������ŵ�ģʽ����������ģʽ������ģʽ��
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-21  zcb, first implementation
 * \endinternal
 */

#ifndef __HC32F460_PIN_H
#define __HC32F460_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../drivers/include/gpio/am_hc32f460_gpio_util.h"

 /**
 * \addtogroup hc32f460_if_pin
 * \copydoc hc32f460_pin.h
 * @{
 */

/**
 * \name HC32F460 GPIO ���ű��
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
#define PIOA_11         11        /**< \brief PIOA_11 ���ź� */
#define PIOA_12         12        /**< \brief PIOA_13 ���ź� */
#define PIOA_13         13        /**< \brief PIOA_13 ���ź� */
#define PIOA_14         14        /**< \brief PIOA_14 ���ź� */
#define PIOA_15         15        /**< \brief PIOA_15 ���ź� */

#define PIOB            16        /**< \brief �˿�B������ʼ�� */
#define PIOB_0          16        /**< \brief PIOB_0 ���ź� */
#define PIOB_1          17        /**< \brief PIOB_1 ���ź� */
#define PIOB_2          18        /**< \brief PIOB_2 ���ź� */
#define PIOB_3          19        /**< \brief PIOB_3 ���ź� */
#define PIOB_4          20        /**< \brief PIOB_4 ���ź� */
#define PIOB_5          21        /**< \brief PIOB_5 ���ź� */
#define PIOB_6          22        /**< \brief PIOB_6 ���ź� */
#define PIOB_7          23        /**< \brief PIOB_7 ���ź� */
#define PIOB_8          24        /**< \brief PIOB_8 ���ź� */
#define PIOB_9          25        /**< \brief PIOB_9 ���ź� */
#define PIOB_10         26        /**< \brief PIOB_10���ź� */
#define PIOB_11         27        /**< \brief PIOB_11���ź� */
#define PIOB_12         28        /**< \brief PIOB_12���ź� */
#define PIOB_13         29        /**< \brief PIOB_13���ź� */
#define PIOB_14         30        /**< \brief PIOB_14���ź� */
#define PIOB_15         31        /**< \brief PIOB_15���ź� */

#define PIOC            32        /**< \brief �˿�C������ʼ�� */
#define PIOC_0          32        /**< \brief PIOC_0 ���ź� */
#define PIOC_1          33        /**< \brief PIOC_1 ���ź� */
#define PIOC_2          34        /**< \brief PIOC_2 ���ź� */
#define PIOC_3          35        /**< \brief PIOC_3 ���ź� */
#define PIOC_4          36        /**< \brief PIOC_4 ���ź� */
#define PIOC_5          37        /**< \brief PIOC_5 ���ź� */
#define PIOC_6          38        /**< \brief PIOC_6 ���ź� */
#define PIOC_7          39        /**< \brief PIOC_7 ���ź� */
#define PIOC_8          40        /**< \brief PIOC_8 ���ź� */
#define PIOC_9          41        /**< \brief PIOC_9 ���ź� */
#define PIOC_10         42        /**< \brief PIOC_10���ź� */
#define PIOC_11         43        /**< \brief PIOC_11���ź� */
#define PIOC_12         44        /**< \brief PIOC_12���ź� */
#define PIOC_13         45        /**< \brief PIOC_13���ź� */
#define PIOC_14         46        /**< \brief PIOC_14���ź� */
#define PIOC_15         47        /**< \brief PIOC_15���ź� */

#define PIOD            48        /**< \brief �˿�D������ʼ�� */
#define PIOD_0          48        /**< \brief PIOD_0 ���ź� */
#define PIOD_1          49        /**< \brief PIOD_1 ���ź� */
#define PIOD_2          50        /**< \brief PIOD_2 ���ź� */
#define PIOD_3          51        /**< \brief PIOD_3 ���ź� */
#define PIOD_4          52        /**< \brief PIOD_4 ���ź� */
#define PIOD_5          53        /**< \brief PIOD_5 ���ź� */
#define PIOD_6          54        /**< \brief PIOD_6 ���ź� */
#define PIOD_7          55        /**< \brief PIOD_7 ���ź� */
#define PIOD_8          56        /**< \brief PIOD_8 ���ź� */
#define PIOD_9          57        /**< \brief PIOD_9 ���ź� */
#define PIOD_10         58        /**< \brief PIOD_10���ź� */
#define PIOD_11         59        /**< \brief PIOD_11���ź� */
#define PIOD_12         60        /**< \brief PIOD_12���ź� */
#define PIOD_13         61        /**< \brief PIOD_13���ź� */
#define PIOD_14         62        /**< \brief PIOD_14���ź� */
#define PIOD_15         63        /**< \brief PIOD_15���ź� */

#define PIOE            64        /**< \brief �˿�E������ʼ�� */
#define PIOE_0          64        /**< \brief PIOE_0 ���ź� */
#define PIOE_1          65        /**< \brief PIOE_1 ���ź� */
#define PIOE_2          66        /**< \brief PIOE_2 ���ź� */
#define PIOE_3          67        /**< \brief PIOE_3 ���ź� */
#define PIOE_4          68        /**< \brief PIOE_4 ���ź� */
#define PIOE_5          69        /**< \brief PIOE_5 ���ź� */
#define PIOE_6          70        /**< \brief PIOE_6 ���ź� */
#define PIOE_7          71        /**< \brief PIOE_7 ���ź� */
#define PIOE_8          72        /**< \brief PIOE_8 ���ź� */
#define PIOE_9          73        /**< \brief PIOE_9 ���ź� */
#define PIOE_10         74        /**< \brief PIOE_10���ź� */
#define PIOE_11         75        /**< \brief PIOE_11���ź� */
#define PIOE_12         76        /**< \brief PIOE_12���ź� */
#define PIOE_13         77        /**< \brief PIOE_13���ź� */
#define PIOE_14         78        /**< \brief PIOE_14���ź� */
#define PIOE_15         79        /**< \brief PIOE_15���ź� */

#define PIOH            80        /**< \brief �˿�H������ʼ�� */
#define PIOH_0          80        /**< \brief PIOH_0 ���ź� */
#define PIOH_1          81        /**< \brief PIOH_1 ���ź� */
#define PIOH_2          82        /**< \brief PIOH_2 ���ź� */
/**
 * \brief ������ĿΪ83
 */
#define PIN_NUM         83


/**
 * \brief ֧��ͬʱ������������ж�����16
 */
#define PIN_INT_MAX     16


/******************************************************************************/

/**
 * \name PIO���Ÿ���ʱ����ģʽ(ͨ��)
 * @{
 */
#define GPIO_AFIO(x)   AM_HC32F460_GPIO_FUNC_CODE(x)
/**
 * @}
 */


/**
 * \name PIO���Ÿ���ʱ����ģʽ(ͨ��)
 * @{
 */
#define GPIO_MODE(x)   AM_HC32F460_GPIO_MODE_CODE(x)
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F460_PIN_H */

/* end of file */
