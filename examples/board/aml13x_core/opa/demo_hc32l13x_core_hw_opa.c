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
 * \brief OPA��ͬģʽ�����������ϵ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *    OPA_UintMode_Test
 *    ��ʱͨ��ʾ�����۲�PC06��PC07�źţ�PC07����ź���PC06�ź�ͨ�ŷ�ֵ��һ�µġ�
 *    OPA_ForWardMode_Test
 *    ��ʱͨ��ʾ�����۲�PC06��PC07�źţ�PC07����ź���PC06�ź�ͨ�ŷ�ֵ����������
 *    OPA_GpMode_Test
 *    PC06����VCOR1.5V��PB15��PC07�ӵ���22K��PB15�ӵ���10K�Եأ�
 *    ��ʱͨ��ʾ�����۲�PC06��PC07�źţ�PC07����ź���PC06�ź�ͨ�ŷ�ֵ����������
 *
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32l13x_core_opa_one.c src_hc32l13x_core_opa_one
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l13x_core_opa_one
 * \copydoc demo_hc32l13x_core_opa_one.c
 */

/** [src_hc32l13x_core_opa_one] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "hc32x3x_pin.h"
#include "am_hc32x3x_opa.h"
#include "demo_hc32_entries.h"

/**
 * \brief OPAͨ��
 */
#define OPA_CH    AM_HC32_OPA_CH1

/**
 * \brief OPAģʽ
 */
#define OPA_MODE    AM_HC32_OPA_MODE_UNITY_GAIN  /**< \brief OPA��λ����ģʽ*/
//#define OPA_MODE    AM_HC32_OPA_MODE_FORWARD_IN  /**< \biref ��������ģʽ */
//#define OPA_MODE    AM_HC32_OPA_MODE_UNIVERSAL   /**< \biref ͨ��ģʽ */


/**
 * \brief �������
 */
void demo_hc32l13x_core_hw_opa_entry (void)
{

    AM_DBG_INFO("demo aml13x_core hw opa one test!\r\n");

    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* OPA1 P N OUT�� */
    am_gpio_pin_cfg (PIOC_6,  PIOC_6_AIN);
    am_gpio_pin_cfg (PIOB_15, PIOB_15_AIN);
    am_gpio_pin_cfg (PIOC_7,  PIOC_7_AOUT);

    //    /* OPA2 P N OUT�� */
    //    am_gpio_pin_cfg (PIOB_13, PIOB_13_AIN);
    //    am_gpio_pin_cfg (PIOB_12, PIOB_12_AIN);
    //    am_gpio_pin_cfg (PIOB_14, PIOB_14_AOUT);
    //
    //    /* OPA3 P N OUT�� */
    //    am_gpio_pin_cfg (PIOB_10, PIOB_10_AIN);
    //    am_gpio_pin_cfg (PIOB_2,  PIOB_2_AIN);
    //    am_gpio_pin_cfg (PIOB_11, PIOB_11_AOUT);

    demo_hc32x3x_hw_opa_entry(HC32_OPA, OPA_MODE, OPA_CH);
}

/* end of file */
