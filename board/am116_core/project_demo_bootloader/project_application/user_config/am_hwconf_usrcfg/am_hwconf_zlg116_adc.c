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
 * \brief ZLG116 ADC �û������ļ�
 * \sa am_hwconf_zlg116_adc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  ari, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_zlg116.h"
#include "am_gpio.h"
#include "am_zlg_adc.h"
#include "hw/amhw_zlg_adc.h"
#include "hw/amhw_zlg116_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_adc
 * \copydoc am_hwconf_zlg116_adc.c
 * @{
 */

/** \brief ADCƽ̨��ʼ�� */
static void __zlg_plfm_adc_init (void)
{
    am_gpio_pin_cfg(PIOA_1, PIOA_1_ADC_IN1 | PIOA_1_AIN);
    am_gpio_pin_cfg(PIOB_0, PIOB_0_ADC_IN8 | PIOB_0_AIN);
    am_clk_enable(CLK_ADC1);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __zlg_plfm_adc_deinit (void)
{
    am_gpio_pin_cfg(PIOA_1, PIOA_1_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_0, PIOB_0_INPUT_FLOAT);
    am_clk_disable (CLK_ADC1);
}

/** \brief ADC�豸��Ϣ */
static const am_zlg_adc_devinfo_t __g_adc_devinfo = {

    ZLG116_ADC_BASE,                  /**< \brief ADC */
    INUM_ADC_COMP,                    /**< \brief ADC���жϱ�� */
    CLK_ADC1,                         /**< \brief ADCʱ�Ӻ� */

    3300,                             /**< \brief �ο���ѹ */
    AMHW_ZLG_ADC_DATA_VALID_12BIT, /**< \brief ת������ */

    __zlg_plfm_adc_init,              /**< \brief ADC��ƽ̨��ʼ�� */
    __zlg_plfm_adc_deinit,            /**< \brief ADC��ƽ̨ȥ��ʼ�� */

};

static am_zlg_adc_dev_t  __g_adc_dev;   /**< \brief ����ADC �豸 */

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_zlg116_adc_inst_init (void)
{
    return am_zlg_adc_init(&__g_adc_dev, &__g_adc_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_zlg116_adc_inst_deinit (am_adc_handle_t handle)
{
    am_zlg_adc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
