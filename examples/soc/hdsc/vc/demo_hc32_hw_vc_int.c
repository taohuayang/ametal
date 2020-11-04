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
 * \snippet demo_hc32_hw_vc_int.c src_hc32_hw_vc_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-30  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_vc_int
 * \copydoc demo_hc32_hw_vc_int.c
 */

/** [src_hc32_hw_vc_int] */

#include "ametal.h"
#include "am_hc32.h"
#include "am_int.h"
#include "am_hc32_vc.h"
#include "hw/amhw_hc32_vc.h"
#include "hw/amhw_hc32_dac.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define VC_INUM      INUM_VC0                         /**< \brief VC�жϱ�� */
#define VC_CHAN      AMHW_HC32_VC0                    /**< \brief VCͨ�� */
#define VC_VREF      AMHW_HC32_VC_REF2P5_VCC          /**< \brief �ο���ѹ  */
#define VC_HYS_VOL   AMHW_HC32_VC0_HYS_10_MV          /**< \brief ���͵�ѹ*/
#define VC_BIAS      AMHW_HC32_VC0_BIAS_1_2_UA        /**< \brief ����*/
#define VC_DEB_TIME  AMHW_HC32_DEB_TIME_28_US         /**< \brief �˲�ʱ��*/
#define VC_P_IN      AMHW_HC32_VC0_P_INPUT_PC0        /**< \brief P������*/
#define VC_N_IN      AMHW_HC32_VC0_N_INPUT_PA7        /**< \brief N������*/
#define VC_OUT_CFG   AMHW_HC32_VC_OUT_CFG_DISABLE     /**< \brief ������� */
#define VC_INT_TYPE  AMHW_HC32_VC_OUT_TRI_INT_RISING  /**< \brief �жϴ������� */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_hc32_vc_t   *__gp_hw_vc   = NULL;         /**< \brief vc ���� */
static amhw_hc32_dac_t  *__gp_hw_dac  = NULL;         /**< \brief dac ���� */

static void            (*__gpfn_cb_t) (void *);       /**< \brief vc�жϻص����� */
static void             *__gp_arg;                    /**< \brief vc�жϻص��������� */

/*
 * \brief VC��ʼ��
 */
static void vc_init ()
{

    /* ʹ��BGR */
    amhw_hc32_bgr_enable(AM_TRUE);

    /* ���òο���ѹ */
    amhw_hc32_vc_ref2p5_sel (__gp_hw_vc, VC_VREF);

    /* ѡ�� ���͵�ѹ�����ġ� �˲�ʱ�䡢  ͨ��N��P������ ���ж�����*/
    switch (VC_CHAN){

        case AMHW_HC32_VC0 :
                amhw_hc32_vc0_hys_sel (__gp_hw_vc, VC_HYS_VOL);
                amhw_hc32_vc0_bias_sel (__gp_hw_vc, VC_BIAS);
                amhw_hc32_vc0_flt_time_sel (__gp_hw_vc, VC_DEB_TIME);

                amhw_hc32_vc0_n_sel (__gp_hw_vc, VC_N_IN);
                amhw_hc32_vc0_p_sel (__gp_hw_vc, VC_P_IN);

                amhw_hc32_vc0_out_tri_int_sel (__gp_hw_vc,VC_INT_TYPE);
            break;

        case AMHW_HC32_VC1 :
                amhw_hc32_vc1_hys_sel (__gp_hw_vc, VC_HYS_VOL);
                amhw_hc32_vc1_bias_sel (__gp_hw_vc, VC_BIAS);
                amhw_hc32_vc1_flt_time_sel (__gp_hw_vc, VC_DEB_TIME);

                amhw_hc32_vc1_n_sel (__gp_hw_vc, VC_N_IN);
                amhw_hc32_vc1_p_sel (__gp_hw_vc, VC_P_IN);

                amhw_hc32_vc1_out_tri_int_sel (__gp_hw_vc, VC_INT_TYPE);
            break;
        case AMHW_HC32_VC2 :
                amhw_hc32_vc2_hys_sel (__gp_hw_vc, VC_HYS_VOL);
                amhw_hc32_vc2_bias_sel (__gp_hw_vc, VC_BIAS);
                amhw_hc32_vc2_flt_time_sel (__gp_hw_vc, VC_DEB_TIME);

                amhw_hc32_vc2_n_sel (__gp_hw_vc, VC_N_IN);
                amhw_hc32_vc2_p_sel (__gp_hw_vc, VC_P_IN);

                amhw_hc32_vc1_out_tri_int_sel (__gp_hw_vc, VC_INT_TYPE);
            break;
    }

    /* ������� */
    amhw_hc32_vc_outcfg_enable (__gp_hw_vc,
                                  VC_OUT_CFG,
                                  VC_CHAN);

    if (VC_DEB_TIME != AMHW_HC32_DEB_TIME_NO){

        /* �˲�ʹ�� */
        amhw_hc32_vc_flt_enable (__gp_hw_vc, VC_CHAN);
    }

}

/*
 * \brief VC�жϷ�����
 */
static void __vc_irq_handler (void *p_cookie)
{

    if (amhw_hc32_vc_int_status_check (__gp_hw_vc, AMHW_HC32_VC0_FLT_INT_FLAG)){

        amhw_hc32_vc_int_status_clr(__gp_hw_vc,AMHW_HC32_VC0_FLT_INT_FLAG_CLR);
    }else if (amhw_hc32_vc_int_status_check (__gp_hw_vc,
                                               AMHW_HC32_VC1_FLT_INT_FLAG)){

        amhw_hc32_vc_int_status_clr(__gp_hw_vc,AMHW_HC32_VC1_FLT_INT_FLAG_CLR);
    }else if (amhw_hc32_vc_int_status_check (__gp_hw_vc,
                                               AMHW_HC32_VC2_FLT_INT_FLAG)){

        amhw_hc32_vc_int_status_clr(__gp_hw_vc,AMHW_HC32_VC2_FLT_INT_FLAG_CLR);
    }else{

        return ;
    }

    if (__gpfn_cb_t) {
        __gpfn_cb_t(__gp_arg);
    }
}

/**
 * \breif VC�жϴ�������
 *
 */
static void vc_int_tri_cfg ()
{
    if (__gp_hw_vc == NULL){

        return ;
    }

    /* ��������ж�ʹ�� */
    amhw_hc32_vc_int_enable (__gp_hw_vc, VC_CHAN);

    am_int_connect(VC_INUM,
                   __vc_irq_handler,
                   NULL);

    am_int_enable (VC_INUM);
}

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

    /* ʹ��dacͨ�� */
    amhw_hc32_dac_chan_enable(p_hw_dac);

}

/**
 * \brief VC�жϴ������̣�hw�ӿڲ�ʵ��
 */
void demo_hc32_hw_vc_int_entry (void      *p_hw_vc,
                                void     (*pfn_cb_t) (void *),
                                void      *p_arg,
                                void      *p_hw_dac,
                                uint16_t   mv_val)
{
    uint16_t vol_val = 0;

    __gp_hw_vc  = (amhw_hc32_vc_t *)p_hw_vc;
    __gp_hw_dac = (amhw_hc32_dac_t *)p_hw_dac;

    __gpfn_cb_t = pfn_cb_t;
    __gp_arg    = p_arg;

    /* ��ѹֵת��Ϊ������ */
    vol_val = mv_val * 4096 / 3300;

    /* DAC ��ʼ�� Ĭ�ϲο���ѹ���� �ⲿ�ο���ѹԴ  PB01*/
    dac_hw_init(__gp_hw_dac, AMHW_HC32_DAC_CHAN_MASK_EXTER_REF);

    /* ����DAC��ѹֵ ���ݸ�ʽ��12λ�Ҷ��� */
    amhw_hc32_dac_chan_12bit_right_aligned_data(__gp_hw_dac, vol_val);

    /* VC��ʼ�� */
    vc_init ();

    /* VC�����ж�����  */
    vc_int_tri_cfg ();

    /*ʹ�ܵ�ѹ�Ƚ���*/
    amhw_hc32_vc_volt_cmp_enable(p_hw_vc, VC_CHAN);

    while (1)
    {
        ;
    }
}

