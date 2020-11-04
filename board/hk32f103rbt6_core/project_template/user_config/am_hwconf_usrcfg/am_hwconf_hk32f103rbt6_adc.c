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
 * \brief HK32F103RBT6 ADC �û������ļ�
 * \sa am_hwconf_hk32f103rbt6_adc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "am_hk32f103rbt6.h"
#include "amhw_hk32f103rbt6_rcc.h"
#include "hk32f103rbt6_inum.h"
#include "hk32f103rbt6_periph_map.h"
#include "am_gpio.h"
#include "am_hk32f103rbt6_adc.h"
#include "amhw_hk32f103rbt6_adc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hk32f103rbt6_adc
 * \copydoc am_hwconf_hk32f103rbt6_adc.c
 * @{
 */



/** \brief ADCƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_adc1_init (void)
{
    /* ADC1��ADC2����ͨ����ʵ���ϲ���ͬʱ����ADC12,��������ģʽʹ��*/
    /* �˴�����ADC1�ɼ�ͨ��*/
    am_gpio_pin_cfg(PIOA_0, PIOA_0_ADC12_IN0 | PIOA_0_AIN);     /* ADC12ͨ��0 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_ADC12_IN1 | PIOA_1_AIN);     /* ADC12ͨ��1 */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_ADC12_IN2 | PIOA_2_AIN);     /* ADC12ͨ��2 */
    am_gpio_pin_cfg(PIOA_3, PIOA_3_ADC12_IN3 | PIOA_3_AIN);     /* ADC12ͨ��3 */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_ADC12_IN4 | PIOA_4_AIN);     /* ADC12ͨ��4 */
    am_gpio_pin_cfg(PIOA_5, PIOA_5_ADC12_IN5 | PIOA_5_AIN);     /* ADC12ͨ��5 */
    am_gpio_pin_cfg(PIOA_6, PIOA_6_ADC12_IN6 | PIOA_6_AIN);     /* ADC12ͨ��6 */
    am_gpio_pin_cfg(PIOA_7, PIOA_7_ADC12_IN7 | PIOA_7_AIN);     /* ADC12ͨ��7 */

    /* ʹ��ADC1ʱ��*/
    am_clk_enable(CLK_ADC1);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_adc1_deinit (void)
{
    /* ʧ��ADC1ʱ��*/
    am_clk_disable (CLK_ADC1);
}

/** \brief �豸��Ϣ */
static const am_hk32f103rbt6_adc_devinfo_t __g_adc1_devinfo = {

    HK32F103RBT6_ADC1_BASE,                    /**< \brief ADC */
    INUM_ADC1_2,                         /**< \brief ADC���жϱ�� */
    CLK_ADC1,                            /**< \brief ADCʱ�Ӻ� */

    3300,                                /**< \brief �ο���ѹ */

    0,                                   /**< \brief ADC1ͨ��16�ڲ��¶ȴ���������ʹ��
                                          *          1�������� 0���ر�
                                          *          ��ADC1��Ч
                                          */

    AMHW_HK32F103RBT6_ADC_DATA_VALID_12BIT,    /**< \brief ת�����ȣ�hk32f103rbt6����ֻ��Ϊ12λ */

    __hk32f103rbt6_plfm_adc1_init,             /**< \brief ADC1��ƽ̨��ʼ�� */
    __hk32f103rbt6_plfm_adc1_deinit,           /**< \brief ADC1��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_hk32f103rbt6_adc_dev_t  __g_adc1_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_hk32f103rbt6_adc1_inst_init (void)
{
    return am_hk32f103rbt6_adc_init(&__g_adc1_dev, &__g_adc1_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_hk32f103rbt6_adc1_inst_deinit (am_adc_handle_t handle)
{
    am_hk32f103rbt6_adc_deinit(handle);
}

/** \brief ADC2ƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_adc2_init (void)
{
    /* ADC1��ADC2����ͨ����ʵ���ϲ���ͬʱ����ADC12,��������ģʽʹ��*/
    /* �˴�����ADC2�ɼ�ͨ��*/
    am_gpio_pin_cfg(PIOB_0, PIOB_0_ADC12_IN8  | PIOB_0_AIN);/* ADC12ͨ��8 */
    am_gpio_pin_cfg(PIOB_1, PIOB_1_ADC12_IN9  | PIOB_1_AIN);/* ADC12ͨ��9 */
    am_gpio_pin_cfg(PIOC_0, PIOC_0_ADC12_IN10 | PIOC_0_AIN);/* ADC12ͨ��10 */
    am_gpio_pin_cfg(PIOC_1, PIOC_1_ADC12_IN11 | PIOC_1_AIN);/* ADC12ͨ��11 */
    am_gpio_pin_cfg(PIOC_2, PIOC_2_ADC12_IN12 | PIOC_2_AIN);/* ADC12ͨ��12 */
    am_gpio_pin_cfg(PIOC_3, PIOC_3_ADC12_IN13 | PIOC_3_AIN);/* ADC12ͨ��13 */
    am_gpio_pin_cfg(PIOC_4, PIOC_4_ADC12_IN14 | PIOC_4_AIN);/* ADC12ͨ��14 */
    am_gpio_pin_cfg(PIOC_5, PIOC_5_ADC12_IN15 | PIOC_5_AIN);/* ADC12ͨ��15 */

    /* ʹ��ADC2ʱ��*/
    am_clk_enable(CLK_ADC2);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __hk32f103rbt6_plfm_adc2_deinit (void)
{
    /* ʧ��ADC2ʱ��*/
    am_clk_disable (CLK_ADC2);
}

/** \brief ADC�豸��Ϣ */
static const am_hk32f103rbt6_adc_devinfo_t __g_adc2_devinfo = {

    HK32F103RBT6_ADC2_BASE,                 /**< \brief ADC */
    INUM_ADC1_2,                      /**< \brief ADC���жϱ�� */
    CLK_ADC2,                         /**< \brief ADCʱ�Ӻ� */

    3300,                             /**< \brief �ο���ѹ */

    0,                                /**< \brief ADC1ͨ��16�ڲ��¶ȴ���������ʹ��
                                       *          1�������� 0���ر�
                                       *          ��ADC1��Ч
                                       */

    AMHW_HK32F103RBT6_ADC_DATA_VALID_12BIT, /**< \brief ת�����ȣ�hk32f103rbt6����ֻ��Ϊ12λ */

    __hk32f103rbt6_plfm_adc2_init,          /**< \brief ADC2��ƽ̨��ʼ�� */
    __hk32f103rbt6_plfm_adc2_deinit,        /**< \brief ADC2��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_hk32f103rbt6_adc_dev_t  __g_adc2_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_hk32f103rbt6_adc2_inst_init (void)
{
    return am_hk32f103rbt6_adc_init(&__g_adc2_dev, &__g_adc2_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_hk32f103rbt6_adc2_inst_deinit (am_adc_handle_t handle)
{
    am_hk32f103rbt6_adc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
