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
#include "am_hc32f07x.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_hc32f07x_opa.h"
#include "hw/amhw_hc32f07x_opa.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define OPA_CLK      AMHW_HC32F07X_OPA_CLK_16    /**< \brief У׼���� */
#define OPA_AZ_WAY   AMHW_HC32F07X_OPA_AZ_SW     /**< \brief У׼��ʽ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_hc32f07x_opa_t       *gp_hw_opa   = NULL;  /**< \brief OPA ���� */

/**
 * \brief OPA��ʼ��
 */
void opa_init (uint8_t mode)
{
    if (mode == AM_HC32F07X_OPA0_4_GENERAL){
        /* ʹ��opa */
        amhw_hc32f07x_opa3_en (gp_hw_opa);

        /* �Զ�У׼ʹ�� */
        amhw_hc32f07x_opa3_az_en (gp_hw_opa);

        /* �Զ�У׼���������� */
        amhw_hc32f07x_opa_clk_sel (gp_hw_opa, OPA_CLK);

        /* ѡ��У׼��ʽ */
        amhw_hc32f07x_opa_az_way_sel (gp_hw_opa, OPA_AZ_WAY);
    }else{
        ;
    }
}

/**
 * \brief �������
 */
void demo_hc32f07x_hw_opa_one_entry (void *p_hw_opa, uint8_t mode)
{
    gp_hw_opa  = (amhw_hc32f07x_opa_t *)p_hw_opa;

    /* ʹ��BGR */
    amhw_hc32_bgr_enable(AM_TRUE);

    /* OPA��ʼ�� */
    opa_init (mode);

    /* ����У׼ */
    amhw_hc32f07x_az_start (p_hw_opa,AMHW_HC32F07X_AZ_SW_START);

    /* ��ʱ 20us*/
    am_udelay(20);

    while (1)
    {
        ;
    }
}

/* end of file */
