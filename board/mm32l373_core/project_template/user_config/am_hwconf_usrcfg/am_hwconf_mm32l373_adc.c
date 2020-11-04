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
 * \brief MM32L373 ADC �û������ļ�
 * \sa am_hwconf_mm32l373_adc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "mm32l373_periph_map.h"
#include "am_mm32l373.h"
#include "mm32l373_inum.h"
#include "am_gpio.h"
#include "am_mm32_adc.h"
#include "amhw_mm32_adc.h"
#include "amhw_mm32l373_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_mm32l373_adc
 * \copydoc am_hwconf_mm32l373_adc.c
 * @{
 */



/** \brief ADCƽ̨��ʼ�� */
static void __mm32_plfm_adc1_init (void)
{
    am_gpio_pin_cfg(PIOA_0, PIOA_0_ADC1_IN0 | PIOA_0_AIN);     /* ADC1ͨ��0 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_ADC1_IN1 | PIOA_1_AIN);     /* ADC1ͨ��1 */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_ADC1_IN2 | PIOA_2_AIN);     /* ADC1ͨ��2 */
    am_gpio_pin_cfg(PIOA_3, PIOA_3_ADC1_IN3 | PIOA_3_AIN);     /* ADC1ͨ��3 */
//    am_gpio_pin_cfg(PIOA_4, PIOA_4_ADC1_IN4 | PIOA_4_AIN);     /* ADC1ͨ��4 */
//    am_gpio_pin_cfg(PIOA_5, PIOA_5_ADC1_IN5 | PIOA_5_AIN);     /* ADC1ͨ��5 */
//    am_gpio_pin_cfg(PIOA_6, PIOA_6_ADC1_IN6 | PIOA_6_AIN);     /* ADC1ͨ��6 ���¶ȴ�����ͨ��*/
//    am_gpio_pin_cfg(PIOA_7, PIOA_7_ADC1_IN7 | PIOA_7_AIN);     /* ADC1ͨ��7 ����ѹ������ͨ��*/

    am_clk_enable(CLK_ADC1);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __mm32_plfm_adc1_deinit (void)
{
    am_clk_disable (CLK_ADC1);
}

/** \brief �豸��Ϣ */
static const am_mm32_adc_devinfo_t __g_adc1_devinfo = {

    MM32L373_ADC1_BASE,                 /**< \brief ADC */
    INUM_ADC1_2,                      /**< \brief ADC���жϱ�� */
    CLK_ADC1,                         /**< \brief ADCʱ�Ӻ� */

    3300,                             /**< \brief �ο���ѹ */
    AMHW_MM32_ADC_DATA_VALID_12BIT, /**< \brief ת������ */

    __mm32_plfm_adc1_init,             /**< \brief ADC1��ƽ̨��ʼ�� */
    __mm32_plfm_adc1_deinit,           /**< \brief ADC1��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_mm32_adc_dev_t  __g_adc1_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_mm32l373_adc1_inst_init (void)
{
    return am_mm32_adc_init(&__g_adc1_dev, &__g_adc1_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_mm32l373_adc1_inst_deinit (am_adc_handle_t handle)
{
    am_mm32_adc_deinit(handle);
}

/** \brief ADC2ƽ̨��ʼ�� */
static void __mm32_plfm_adc2_init (void)
{
    am_gpio_pin_cfg(PIOB_0, PIOB_0_AIN);
    am_clk_enable(CLK_ADC2);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __mm32_plfm_adc2_deinit (void)
{
    am_gpio_pin_cfg(PIOB_0, PIOB_0_INPUT_FLOAT);
    am_clk_disable (CLK_ADC2);
}

/** \brief ADC�豸��Ϣ */
static const am_mm32_adc_devinfo_t __g_adc2_devinfo = {

    MM32L373_ADC2_BASE,                 /**< \brief ADC */
    INUM_ADC1_2,                      /**< \brief ADC���жϱ�� */
    CLK_ADC2,                         /**< \brief ADCʱ�Ӻ� */

    3300,                             /**< \brief �ο���ѹ */
    AMHW_MM32_ADC_DATA_VALID_12BIT, /**< \brief ת������ */

    __mm32_plfm_adc2_init,             /**< \brief ADC2��ƽ̨��ʼ�� */
    __mm32_plfm_adc2_deinit,           /**< \brief ADC2��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_mm32_adc_dev_t  __g_adc2_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_mm32l373_adc2_inst_init (void)
{
    return am_mm32_adc_init(&__g_adc2_dev, &__g_adc2_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_mm32l373_adc2_inst_deinit (am_adc_handle_t handle)
{
    am_mm32_adc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
