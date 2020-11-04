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
 * \snippet demo_zsn700_hw_opa_one.c src_zsn700_hw_opa_one
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-10  YRZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_opa_one
 * \copydoc demo_zsn700_hw_opa_one.c
 */

/** [src_zsn700_hw_opa_one] */
#include "ametal.h"
#include "am_zsn700.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_zsn700_opa.h"
#include "hw/amhw_zsn700_opa.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define OPA_CLK      AMHW_ZSN700_OPA_CLK_16    /**< \brief У׼���� */
#define OPA_AZ_WAY   AMHW_ZSN700_OPA_AZ_SW     /**< \brief У׼��ʽ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zsn700_opa_t       *gp_hw_opa   = NULL;  /**< \brief OPA ���� */

/**
 * \brief OPA��ʼ��
 */
void opa_init (uint8_t mode)
{
    if (mode == AM_ZSN700_OPA_GENERAL){
        /* ʹ��opa */
        amhw_zsn700_opa_en (gp_hw_opa);

        /* �Զ�У׼ʹ�� */
        amhw_zsn700_opa_az_en (gp_hw_opa);

        /* �Զ�У׼���������� */
        amhw_zsn700_opa_clk_sel (gp_hw_opa, OPA_CLK);

        /* ѡ��У׼��ʽ */
        amhw_zsn700_opa_az_way_sel (gp_hw_opa, OPA_AZ_WAY);
    }else{
        ;
    }
}

/**
 * \brief �������
 */
void demo_zsn700_hw_opa_one_entry (void *p_hw_opa, uint8_t mode)
{
    gp_hw_opa  = (amhw_zsn700_opa_t *)p_hw_opa;

    /* ʹ��BGR */
    amhw_zsn700_bgr_enable(AM_TRUE);

    /* OPA��ʼ�� */
    opa_init (mode);

    /* ����У׼ */
    amhw_zsn700_az_start (p_hw_opa,AMHW_ZSN700_AZ_SW_START);

    /* ��ʱ 20us*/
    am_udelay(20);

    while (1)
    {
        ;
    }
}

/* end of file */
