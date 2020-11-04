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
 * \brief OPA ��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PB00����ģ���ѹ����ӦOPA�������PA04Ҳ�����PB00��С��ȵ�ѹ��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg118_core_opa_one.c src_zlg118_core_opa_one
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_core_opa_one
 * \copydoc demo_zlg118_core_opa_one.c
 */

/** [src_zlg118_core_opa_one] */
#include "ametal.h"
#include "am_zlg118.h"
#include "am_gpio.h"
#include "zlg118_pin.h"
#include "am_zlg118_opa.h"
#include "demo_zlg_entries.h"

#define OPA_MODE    AM_ZLG118_OPA_GENERAL  /**< \brief OPAͨ��ģʽ*/

/**
 * \brief �������
 */
void demo_zlg118_core_hw_opa_one_entry (void)
{

    AM_DBG_INFO("demo am118_core hw opa one test!\r\n");

    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* PB00 OPA���� */
    am_gpio_pin_cfg (PIOB_0, PIOB_0_AIN);

    demo_zlg118_hw_opa_one_entry(ZLG118_OPA, OPA_MODE);
}

/* end of file */
