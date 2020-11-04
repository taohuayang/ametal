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
 * \snippet demo_zlg118_hw_opa_one.c src_zlg118_hw_opa_one
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_opa_one
 * \copydoc demo_zlg118_hw_opa_one.c
 */

/** [src_zlg118_hw_opa_one] */
#include "ametal.h"
#include "am_zlg118.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_zlg118_opa.h"
#include "hw/amhw_zlg118_opa.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define OPA_CLK      AMHW_ZLG118_OPA_CLK_16    /**< \brief У׼���� */
#define OPA_AZ_WAY   AMHW_ZLG118_OPA_AZ_SW     /**< \brief У׼��ʽ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zlg118_opa_t       *gp_hw_opa   = NULL;  /**< \brief OPA ���� */

/**
 * \brief OPA��ʼ��
 */
void opa_init (uint8_t mode)
{
    if (mode == AM_ZLG118_OPA_GENERAL){
        /* ʹ��opa */
        amhw_zlg118_opa_en (gp_hw_opa);

        /* �Զ�У׼ʹ�� */
        amhw_zlg118_opa_az_en (gp_hw_opa);

        /* �Զ�У׼���������� */
        amhw_zlg118_opa_clk_sel (gp_hw_opa, OPA_CLK);

        /* ѡ��У׼��ʽ */
        amhw_zlg118_opa_az_way_sel (gp_hw_opa, OPA_AZ_WAY);
    }else{
        ;
    }
}

/**
 * \brief �������
 */
void demo_zlg118_hw_opa_one_entry (void *p_hw_opa, uint8_t mode)
{
    gp_hw_opa  = (amhw_zlg118_opa_t *)p_hw_opa;

    /* ʹ��BGR */
    amhw_zlg118_bgr_enable(AM_TRUE);

    /* OPA��ʼ�� */
    opa_init (mode);

    /* ����У׼ */
    amhw_zlg118_az_start (p_hw_opa,AMHW_ZLG118_AZ_SW_START);

    /* ��ʱ 20us*/
    am_udelay(20);

    while (1)
    {
        ;
    }
}

/* end of file */
