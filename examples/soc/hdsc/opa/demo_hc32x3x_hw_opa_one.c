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
 * - 1.00 20-03-16  ly, first implementation
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
#include "am_hc32x3x_opa.h"
#include "hw/amhw_hc32x3x_opa.h"

/**
 * \brief �������
 */
void demo_hc32x3x_hw_opa_entry (void *p_hw_opa, uint8_t mode, uint8_t ch)
{

    /* ʹ��BGR */
    amhw_hc32_bgr_enable(AM_TRUE);

    /* ģʽ���� */
    switch (mode){
        case AM_HC32_OPA_MODE_UNITY_GAIN:
            amhw_hc32_opa_unity_gain_mode(p_hw_opa, ch);
            amhw_hc32_opa_po_ctrl (p_hw_opa, ch, AWHW_HC32_OPA_PO_EN);
            break;
        case AM_HC32_OPA_MODE_FORWARD_IN:
            amhw_hc32_opa_forwar_in_mode(p_hw_opa,
                                         ch,
                                         AMHW_HC32_OPA_NONGAIN_2);
            amhw_hc32_opa_po_ctrl (p_hw_opa, ch, AWHW_HC32_OPA_PO_EN);
            break;
        case AM_HC32_OPA_MODE_UNIVERSAL:
            amhw_hc32_uinversal_mode (p_hw_opa,
                                      ch);
            amhw_hc32_opa_po_ctrl (p_hw_opa, ch, AWHW_HC32_OPA_PO_EN);
            break;
        default:
            break;
    }

    /* ʹ��OPA */
    amhw_hc32_opa_en(p_hw_opa);

    while(1){
        ;
    }
}

/* end of file */
