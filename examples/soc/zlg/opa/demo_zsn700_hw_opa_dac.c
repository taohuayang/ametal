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
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
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
 * \snippet demo_zsn700_hw_opa_dac.c src_zsn700_hw_opa_dac
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-10  YRZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_opa_dac
 * \copydoc demo_zsn700_hw_opa_dac.c
 */

/** [src_zsn700_hw_opa_dac] */
#include "ametal.h"
#include "am_zsn700.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_zsn700_opa.h"
#include "hw/amhw_zsn700_dac.h"
#include "hw/amhw_zsn700_opa.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define OPA_CLK      AMHW_ZSN700_OPA_CLK_16    /**< \brief У׼���� */
#define OPA_AZ_WAY   AMHW_ZSN700_OPA_AZ_SW     /**< \brief У׼��ʽ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zsn700_opa_t *gp_hw_opa   = NULL;  /**< \brief OPA ���� */
static amhw_zsn700_dac_t *gp_hw_dac   = NULL;  /**< \brief DAC ���� */

/**
 * \brief DAC��ʼ��
 */
static void dac_hw_init(amhw_zsn700_dac_t *p_hw_dac,
                        uint32_t           verf)
{

    if (p_hw_dac == NULL){
        return ;
    }

    /* ���òο���ѹԴ */
    amhw_zsn700_dac_chan_sref_sel(p_hw_dac, verf);

    /* ʧ�����������*/
    amhw_zsn700_dac_chan_output_buf_disable(p_hw_dac);

    /* ����ʹ�� */
    amhw_zsn700_dac_chan_trg_enable(p_hw_dac);

    /* ������ʽѡ��  �������*/
    amhw_zsn700_dac_chan_trg_sel(p_hw_dac, AMHW_ZSN700_DAC_CHAN_SOFTWARE_TRG);

    /* ʹ��dacͨ�� */
    amhw_zsn700_dac_chan_enable(p_hw_dac);

}

/**
 * \brief OPA��ʼ��
 */
void opa_hw_init (uint8_t mode)
{
    if (mode == AM_ZSN700_OPA_DAC){

        /* DACʹ��OP3��λ���ӻ���ʹ�� */
        amhw_zsn700_opabuf_en (gp_hw_opa);
    }else{
        ;
    }
}

/**
 * \brief �������
 */
void demo_zsn700_hw_opa_dac_entry (void     *p_hw_opa,
                                   void     *p_hw_dac,
                                   uint8_t   mode,
                                   uint16_t *vol_val)
{
    int i = 0;

    gp_hw_opa = (amhw_zsn700_opa_t *)p_hw_opa;
    gp_hw_dac = (amhw_zsn700_dac_t *)p_hw_dac;

    /* ʹ��BGR */
    amhw_zsn700_bgr_enable(AM_TRUE);

    /* OPA��ʼ�� */
    opa_hw_init (mode);

    /* DAC ��ʼ�� Ĭ�ϲο���ѹ���� �ⲿ�ο���ѹԴ  PB01*/
    dac_hw_init(gp_hw_dac, AMHW_ZSN700_DAC_CHAN_MASK_EXTER_REF);

    AM_FOREVER {

        /* ������� */
        amhw_zsn700_dac_chan_software_trg_enable(gp_hw_dac);

        if (i < 128)
        {
            amhw_zsn700_dac_chan_12bit_right_aligned_data (gp_hw_dac,
                                                           vol_val[i]);
            i++;
        }else{
            i = 0;
        }

        am_mdelay(1000);
    }
}

/* end of file */
