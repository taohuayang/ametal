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
 * \brief OPA��ͬģʽ�����������ϵ���̣�ͨ�� std ��ӿ�ʵ��
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
 * \snippet demo_hc32l13x_core_std_opa.c src_hc32l13x_core_std_opa
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-17  ly, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_hc32.h"
#include "am_gpio.h"
#include "hc32x3x_pin.h"
#include "am_hc32x3x_opa.h"
#include "am_hc32f03x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hc32_entries.h"
/**
 * \brief OPAͨ��
 */
#define OPA_CH    AM_HC32_OPA_CH1

/**
 * \brief �������
 */
void demo_hc32f03x_core_std_opa_entry (void)
{
    AM_DBG_INFO("demo aml13x_core std opa  test!\r\n");

    /* �ײ��ļ���Ҫ���� ģʽ������Ȳ���*/
    demo_hc32x3x_drv_opa_entry(am_hc32_opa1_inst_init(), OPA_CH);
}
