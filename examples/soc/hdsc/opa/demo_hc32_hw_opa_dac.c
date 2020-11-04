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
 * - �������裺
 *   1. ʾ������ J8 PA4 ��
 *   2. �� ZSL420_EVK USB �ӿ���������ӣ��򿪴�������
 *
 * - ʵ������
 *   1. DAC ������Ҳ� ���� OPA ���� PA4 �����
 *
 * \note
 *   1. �۲촮�������Ϣ��Ҫ�� am_prj_config.h ��ʹ�� AM_CFG_DEBUG_ENABLE
 *
 * \par Դ����
 * \snippet demo_hc32_hw_opa_dac.c src_hc32_hw_opa_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_opa_dac
 * \copydoc demo_hc32_hw_opa_dac.c
 */

/** [src_hc32_hw_opa_dac] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_hc32_opa.h"
#include "hw/amhw_hc32_dac.h"
#include "hw/amhw_hc32_opa.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define OPA_CLK      AMHW_HC32_OPA_CLK_16    /**< \brief У׼���� */
#define OPA_AZ_WAY   AMHW_HC32_OPA_AZ_SW     /**< \brief У׼��ʽ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_hc32_opa_t *gp_hw_opa   = NULL;  /**< \brief OPA ���� */
static amhw_hc32_dac_t *gp_hw_dac   = NULL;  /**< \brief DAC ���� */

/**
 * \brief DAC��ʼ��
 */
static void dac_hw_init(amhw_hc32_dac_t *p_hw_dac,
                        uint32_t           verf)
{

    if (p_hw_dac == NULL){
        return ;
    }

    /* ���òο���ѹԴ */
    amhw_hc32_dac_chan_sref_sel(p_hw_dac, verf);

    /* ʧ�����������*/
    amhw_hc32_dac_chan_output_buf_disable(p_hw_dac);

    /* ����ʹ�� */
    amhw_hc32_dac_chan_trg_enable(p_hw_dac);

    /* ������ʽѡ��  �������*/
    amhw_hc32_dac_chan_trg_sel(p_hw_dac, AMHW_HC32_DAC_CHAN_SOFTWARE_TRG);

    /* ʹ��dacͨ�� */
    amhw_hc32_dac_chan_enable(p_hw_dac);

}

/**
 * \brief OPA��ʼ��
 */
void opa_hw_init (uint8_t mode)
{
    if (mode == AM_HC32_OPA_DAC){

        /* DACʹ��OP3��λ���ӻ���ʹ�� */
        amhw_hc32_opabuf_en (gp_hw_opa);
    }else{
        ;
    }
}

/**
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_hc32_hw_opa_dac_entry (void      *p_hw_opa,
                                 void      *p_hw_dac,
                                 uint8_t    mode,
                                 uint16_t  *p_vol_val,
                                 uint32_t   number)
{
    int i = 0;

    gp_hw_opa = (amhw_hc32_opa_t *)p_hw_opa;
    gp_hw_dac = (amhw_hc32_dac_t *)p_hw_dac;

    /* ʹ��BGR */
    amhw_hc32_bgr_enable(AM_TRUE);

    /* OPA��ʼ�� */
    opa_hw_init (mode);

    /* DAC ��ʼ�� Ĭ�ϲο���ѹ���� �ⲿ�ο���ѹԴ  PB01*/
    dac_hw_init(gp_hw_dac, AMHW_HC32_DAC_CHAN_MASK_EXTER_REF);

    AM_FOREVER {

        /* ������� */
        amhw_hc32_dac_chan_software_trg_enable(gp_hw_dac);

        if (i < number) {
            amhw_hc32_dac_chan_12bit_right_aligned_data(gp_hw_dac,
                                                        p_vol_val[i]);
            i++;
        }else{
            i = 0;
        }
        am_mdelay(1000);
    }
}

/* end of file */
