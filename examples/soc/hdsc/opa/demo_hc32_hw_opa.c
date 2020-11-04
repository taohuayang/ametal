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
 * \snippet demo_hc32_hw_opa_one.c src_hc32_hw_opa_one
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_opa_one
 * \copydoc demo_hc32_hw_opa_one.c
 */

/** [src_hc32_hw_opa_one] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_hc32_opa.h"
#include "hw/amhw_hc32_opa.h"

/** \brief У׼���� */
#define __OPA_CLK        AMHW_HC32_OPA_CLK_16

/** \brief У׼��ʽ */
#define __OPA_AZ_WAY     AMHW_HC32_OPA_AZ_SW

/**
 * \brief OPA��ʼ��
 */
static void __opa_general_purpose_init (amhw_hc32_opa_t *p_hw_opa)
{
    /* ʹ�� OPA */
    amhw_hc32_opa_en(p_hw_opa);

    /* �Զ�У׼ʹ�� */
    amhw_hc32_opa_az_en(p_hw_opa);

    /* �Զ�У׼���������� */
    amhw_hc32_opa_clk_sel(p_hw_opa, __OPA_CLK);

    /* ѡ��У׼��ʽ */
    amhw_hc32_opa_az_way_sel(p_hw_opa, __OPA_AZ_WAY);
}

/**
 * \brief OPA ͨ������Ŵ���ģʽ��ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32_hw_opa_entry (void *p_hw_opa)
{
    /* ʹ��BGR */
    amhw_hc32_bgr_enable(AM_TRUE);

    /* OPA��ʼ�� */
    __opa_general_purpose_init((amhw_hc32_opa_t *)p_hw_opa);

    /* ����У׼ */
    amhw_hc32_az_start (p_hw_opa, AMHW_HC32_AZ_SW_START);

    /* ��ʱ 20us*/
    am_udelay(20);

    while (1) {
        ;
    }
}

/* end of file */
