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
 * \brief VC�жϴ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PA07��VCC��GND��ӦPA06����ߵ�ƽ��͵�ƽ����PA07 ��ѹ���� PC00 (��DAC0_out ���2400mv)
 *   �����жϣ����ڴ�ӡ�� "vc trigger interrupt !"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_vc_int.c src_zlg118_hw_vc_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-30  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_hw_vc_int
 * \copydoc demo_zlg118_hw_vc_int.c
 */

/** [src_zlg118_hw_vc_int] */

#include "ametal.h"
#include "am_zlg118.h"
#include "am_int.h"
#include "am_zlg118_vc.h"
#include "hw/amhw_zlg118_vc.h"
#include "hw/amhw_zlg118_dac.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define VC_INUM      INUM_VC0                           /**< \brief VC�жϱ�� */
#define VC_CHAN      AMHW_ZLG118_VC0                    /**< \brief VCͨ�� */
#define VC_VREF      AMHW_ZLG118_VC_REF2P5_VCC          /**< \brief �ο���ѹ  */
#define VC_HYS_VOL   AMHW_ZLG118_VC0_HYS_10_MV          /**< \brief ���͵�ѹ*/
#define VC_BIAS      AMHW_ZLG118_VC0_BIAS_1_2_UA        /**< \brief ����*/
#define VC_DEB_TIME  AMHW_ZLG118_DEB_TIME_28_US         /**< \brief �˲�ʱ��*/
#define VC_P_IN      AMHW_ZLG118_VC0_P_INPUT_PC0        /**< \brief P������*/
#define VC_N_IN      AMHW_ZLG118_VC0_N_INPUT_PA7        /**< \brief N������*/
#define VC_OUT_CFG   AMHW_ZLG118_VC_OUT_CFG_DISABLE     /**< \brief ������� */
#define VC_INT_TYPE  AMHW_ZLG118_VC_OUT_TRI_INT_RISING  /**< \brief �жϴ������� */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zlg118_vc_t       *gp_hw_vc   = NULL;  /**< \brief vc ���� */
static amhw_zlg118_dac_t       *gp_hw_dac  = NULL;  /**< \brief dac ���� */

static void (*gpfn_cb_t) (void *);               /**< \brief vc�жϻص����� */

/*
 * \brief VC��ʼ��
 */
static void vc_init ()
{

    /* ʹ��BGR */
    amhw_zlg118_bgr_enable(AM_TRUE);

    /* ���òο���ѹ */
    amhw_zlg118_vc_ref2p5_sel (gp_hw_vc, VC_VREF);

    /* ѡ�� ���͵�ѹ�����ġ� �˲�ʱ�䡢  ͨ��N��P������ ���ж�����*/
    switch (VC_CHAN){

        case AMHW_ZLG118_VC0 :
                amhw_zlg118_vc0_hys_sel (gp_hw_vc, VC_HYS_VOL);
                amhw_zlg118_vc0_bias_sel (gp_hw_vc, VC_BIAS);
                amhw_zlg118_vc0_flt_time_sel (gp_hw_vc, VC_DEB_TIME);

                amhw_zlg118_vc0_n_sel (gp_hw_vc, VC_N_IN);
                amhw_zlg118_vc0_p_sel (gp_hw_vc, VC_P_IN);

                amhw_zlg118_vc0_out_tri_int_sel (gp_hw_vc,VC_INT_TYPE);
            break;

        case AMHW_ZLG118_VC1 :
                amhw_zlg118_vc1_hys_sel (gp_hw_vc, VC_HYS_VOL);
                amhw_zlg118_vc1_bias_sel (gp_hw_vc, VC_BIAS);
                amhw_zlg118_vc1_flt_time_sel (gp_hw_vc, VC_DEB_TIME);

                amhw_zlg118_vc1_n_sel (gp_hw_vc, VC_N_IN);
                amhw_zlg118_vc1_p_sel (gp_hw_vc, VC_P_IN);

                amhw_zlg118_vc1_out_tri_int_sel (gp_hw_vc, VC_INT_TYPE);
            break;
        case AMHW_ZLG118_VC2 :
                amhw_zlg118_vc2_hys_sel (gp_hw_vc, VC_HYS_VOL);
                amhw_zlg118_vc2_bias_sel (gp_hw_vc, VC_BIAS);
                amhw_zlg118_vc2_flt_time_sel (gp_hw_vc, VC_DEB_TIME);

                amhw_zlg118_vc2_n_sel (gp_hw_vc, VC_N_IN);
                amhw_zlg118_vc2_p_sel (gp_hw_vc, VC_P_IN);

                amhw_zlg118_vc1_out_tri_int_sel (gp_hw_vc, VC_INT_TYPE);
            break;
    }

    /* ������� */
    amhw_zlg118_vc_outcfg_enable (gp_hw_vc,
                                  VC_OUT_CFG,
                                  VC_CHAN);

    if (VC_DEB_TIME != AMHW_ZLG118_DEB_TIME_NO){

        /* �˲�ʹ�� */
        amhw_zlg118_vc_flt_enable (gp_hw_vc, VC_CHAN);
    }

}

/*
 * \brief VC�жϷ�����
 */
static void __vc_irq_handler (void *p_cookie)
{

    if (amhw_zlg118_vc_int_status_check (gp_hw_vc, AMHW_ZLG118_VC0_FLT_INT_FLAG)){

        amhw_zlg118_vc_int_status_clr(gp_hw_vc,AMHW_ZLG118_VC0_FLT_INT_FLAG_CLR);
    }else if (amhw_zlg118_vc_int_status_check (gp_hw_vc,
                                               AMHW_ZLG118_VC1_FLT_INT_FLAG)){

        amhw_zlg118_vc_int_status_clr(gp_hw_vc,AMHW_ZLG118_VC1_FLT_INT_FLAG_CLR);
    }else if (amhw_zlg118_vc_int_status_check (gp_hw_vc,
                                               AMHW_ZLG118_VC2_FLT_INT_FLAG)){

        amhw_zlg118_vc_int_status_clr(gp_hw_vc,AMHW_ZLG118_VC2_FLT_INT_FLAG_CLR);
    }else{

        return ;
    }

    gpfn_cb_t(NULL);
}

/**
 * \breif VC�жϴ�������
 *
 */
static void vc_int_tri_cfg ()
{
    if (gp_hw_vc == NULL){

        return ;
    }

    /* ��������ж�ʹ�� */
    amhw_zlg118_vc_int_enable (gp_hw_vc, VC_CHAN);

    am_int_connect(VC_INUM,
                   __vc_irq_handler,
                   NULL);

    am_int_enable (VC_INUM);
}

/**
 * \brief DAC��ʼ��
 */
static void dac_hw_init(amhw_zlg118_dac_t *p_hw_dac,
                        uint32_t           verf)
{

    if (p_hw_dac == NULL){
        return ;
    }

    /* ���òο���ѹԴ */
    amhw_zlg118_dac_chan_sref_sel(p_hw_dac, verf);

    /* ʧ�����������*/
    amhw_zlg118_dac_chan_output_buf_disable(p_hw_dac);

    /* ����ʹ�� */
    amhw_zlg118_dac_chan_trg_enable(p_hw_dac);

    /* ʹ��dacͨ�� */
    amhw_zlg118_dac_chan_enable(p_hw_dac);

}

/**
 * \brief �������
 */
void demo_zlg118_hw_vc_int_entry (void    *p_hw_vc,
                                  void   (*pfn_cb_t) (void *),
                                  void    *p_hw_dac,
                                  uint16_t mv_val)
{
    uint16_t vol_val = 0;

    gp_hw_vc  = (amhw_zlg118_vc_t *)p_hw_vc;
    gp_hw_dac = (amhw_zlg118_dac_t *)p_hw_dac;

    gpfn_cb_t = pfn_cb_t;

    /* ��ѹֵת��Ϊ������ */
    vol_val = mv_val * 4096 / 3300;

    /* DAC ��ʼ�� Ĭ�ϲο���ѹ���� �ⲿ�ο���ѹԴ  PB01*/
    dac_hw_init(gp_hw_dac, AMHW_ZLG118_DAC_CHAN_MASK_EXTER_REF);

    /* ����DAC��ѹֵ ���ݸ�ʽ��12λ�Ҷ��� */
    amhw_zlg118_dac_chan_12bit_right_aligned_data(gp_hw_dac, vol_val);

    /* VC��ʼ�� */
    vc_init ();

    /* VC�����ж�����  */
    vc_int_tri_cfg ();

    /*ʹ�ܵ�ѹ�Ƚ���*/
    amhw_zlg118_vc_volt_cmp_enable(p_hw_vc, VC_CHAN);

    while (1)
    {
        ;
    }
}

