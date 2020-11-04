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
 * \brief HC32F460 ADC �û������ļ�
 * \sa am_hwconf_hc32f460_adc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-21  cds, first implementation
 * \endinternal
 */

#include "am_hc32f460.h"
#include "hw/amhw_hc32f460_rcc.h"
#include "am_gpio.h"
#include "am_hc32f460_adc.h"
#include "hw/amhw_hc32f460_adc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_adc
 * \copydoc am_hwconf_hc32f460_adc.c
 * @{
 */

/*******************************************************************************/
/** \brief ADC1ƽ̨��ʼ�� */
static void __hc32f460_plfm_adc1_init (void)
{
    /* ʹ��ADC1ʱ��*/
    am_clk_enable(CLK_ADC1);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __hc32f460_plfm_adc1_deinit (void)
{
    /* ʧ��ADC1ʱ��*/
    am_clk_disable (CLK_ADC1);
}

/**
 *  \brief  ADC������������Ϣ�б�
 *
 *  \note ÿ����Ա����ÿ��ADCͨ����Ӧ��ͨ�����ͼ���������
 *
 */
am_hc32f460_adc_ioinfo_t __g_adc1_ioinfo_list[] = {
    {0,  AMHW_HC32F460_ADC_CH_MUX_ADC1_IN0 ,       PIOA_0 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN0 },
    {1,  AMHW_HC32F460_ADC_CH_MUX_ADC1_IN1 ,       PIOA_1 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN1 },
    {2,  AMHW_HC32F460_ADC_CH_MUX_ADC1_IN2 ,       PIOA_2 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN2 },
    {3,  AMHW_HC32F460_ADC_CH_MUX_ADC1_IN3 ,       PIOA_3 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN3 },
    {4,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN4 ,      PIOA_4 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN4 },
    {5,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN5 ,      PIOA_5 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN5 },
    {6,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN6 ,      PIOA_6 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN6 },
    {7,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN7 ,      PIOA_7 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN7 },
    {8,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN8 ,      PIOB_0 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN8 },
    {9,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN9 ,      PIOB_1 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN9 },
    {10, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN10,      PIOC_0 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN10 },
    {11, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN11,      PIOC_1 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC12_IN11 },
    {12, AMHW_HC32F460_ADC_CH_MUX_ADC1_IN12,       PIOC_2 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN12 },
    {13, AMHW_HC32F460_ADC_CH_MUX_ADC1_IN13,       PIOC_3 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN13 },
    {14, AMHW_HC32F460_ADC_CH_MUX_ADC1_IN14,       PIOC_4 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN14 },
    {15, AMHW_HC32F460_ADC_CH_MUX_ADC1_IN15,       PIOC_5 , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) , GPIO_MODE(AMHW_HC32F460_GPIO_MODE_IPU), AMHW_HC32F460_ADC_CH_MUX_ADC1_IN15 },
    {16, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN_ANALOG,      0 ,                           0 ,                          0 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN_ANALOG},
};

/** \brief �豸��Ϣ */
static const am_hc32f460_adc_devinfo_t __g_adc1_devinfo = {
    HC32F460_ADC1_BASE,                 /**< \brief ADC */
    INUM_ADC1,                          /**< \brief ADC���жϱ�� */
    CLK_ADC1,                           /**< \brief ADCʱ�Ӻ� */
    1,
    3300,                               /**< \brief �ο���ѹ(mv)*/

    AMHW_HC32F460_ADC_RESOLUTION_12BIT, /**< \brief ת�����ȣ�12λ/10λ/8λ */
    &__g_adc1_ioinfo_list[0],           /**< \brief ������Ϣ�б� */
    __hc32f460_plfm_adc1_init,          /**< \brief ADC1��ƽ̨��ʼ�� */
    __hc32f460_plfm_adc1_deinit,        /**< \brief ADC1��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
am_hc32f460_adc_dev_t  __g_adc1_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_hc32f460_adc1_inst_init (void)
{
    return am_hc32f460_adc_init(&__g_adc1_dev, &__g_adc1_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_hc32f460_adc1_inst_deinit (am_adc_handle_t handle)
{
    am_hc32f460_adc_deinit(handle);
}




/** \brief ADC2ƽ̨��ʼ�� */
static void __hc32f460_plfm_adc2_init (void)
{
    /* ʹ��ADC2ʱ��*/
    am_clk_enable(CLK_ADC2);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __hc32f460_plfm_adc2_deinit (void)
{
    /* ʧ��ADC2ʱ��*/
    am_clk_disable (CLK_ADC2);
}

/**
 *  \brief  ADC������������Ϣ�б�
 *
 *  \note ÿ����Ա����ÿ��ADCͨ����Ӧ��ͨ�����ͼ���������
 *
 */
am_hc32f460_adc_ioinfo_t __g_adc2_ioinfo_list[] = {
    {0,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN4 ,     PIOA_4 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN4 },
    {1,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN5 ,     PIOA_5 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN5 },
    {2,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN6 ,     PIOA_6 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN6 },
    {3,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN7 ,     PIOA_7 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN7 },
    {4,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN8 ,     PIOB_0 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN8 },
    {5,  AMHW_HC32F460_ADC_CH_MUX_ADC12_IN9 ,     PIOB_1 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN9 },
    {6, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN10,      PIOC_0 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN10 },
    {7, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN11,      PIOC_1 , AMHW_HC32F460_GPIO_MODE_AIN , AMHW_HC32F460_GPIO_MODE_IPU, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN11 },
    {8, AMHW_HC32F460_ADC_CH_MUX_ADC12_IN_ANALOG,      0 ,                           0 ,                          0 , AMHW_HC32F460_ADC_CH_MUX_ADC12_IN_ANALOG},
};

/** \brief �豸��Ϣ */
static const am_hc32f460_adc_devinfo_t __g_adc2_devinfo = {
    HC32F460_ADC2_BASE,                 /**< \brief ADC */
    INUM_ADC2,                          /**< \brief ADC���жϱ�� */
    CLK_ADC2,                           /**< \brief ADCʱ�Ӻ� */
    2,
    3300,                               /**< \brief �ο���ѹ(mv)*/
    AMHW_HC32F460_ADC_RESOLUTION_12BIT, /**< \brief ת�����ȣ�12λ/10λ/8λ */
    &__g_adc2_ioinfo_list[0],           /**< \brief ������Ϣ�б� */
    __hc32f460_plfm_adc2_init,          /**< \brief ADC1��ƽ̨��ʼ�� */
    __hc32f460_plfm_adc2_deinit,        /**< \brief ADC1��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
am_hc32f460_adc_dev_t  __g_adc2_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_hc32f460_adc2_inst_init (void)
{
    return am_hc32f460_adc_init(&__g_adc2_dev, &__g_adc2_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_hc32f460_adc2_inst_deinit (am_adc_handle_t handle)
{
    am_hc32f460_adc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
