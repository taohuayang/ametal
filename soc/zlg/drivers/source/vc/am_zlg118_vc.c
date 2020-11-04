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
 * \brief VC����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "am_zlg118.h"
#include "zlg118_periph_map.h"
#include "am_zlg118_vc.h"
#include "hw/amhw_zlg118_vc.h"


/*VC�жϷ�����*/
void __vc_irq_handler (void *p_cookie)
{
    amhw_zlg118_vc_t *p_hw_vc;
    am_zlg118_vc_dev_t *p_dev = (am_zlg118_vc_dev_t *)p_cookie;
    p_hw_vc = (amhw_zlg118_vc_t *)(p_dev->p_devinfo->vc_reg_base);



    if (amhw_zlg118_vc_int_status_check (p_hw_vc, AMHW_ZLG118_VC0_FLT_INT_FLAG)){

        amhw_zlg118_vc_int_status_clr(p_hw_vc, AMHW_ZLG118_VC0_FLT_INT_FLAG_CLR);

    }else if (amhw_zlg118_vc_int_status_check (
                   p_hw_vc, AMHW_ZLG118_VC1_FLT_INT_FLAG)){

        amhw_zlg118_vc_int_status_clr(p_hw_vc, AMHW_ZLG118_VC1_FLT_INT_FLAG_CLR);

    }else if (amhw_zlg118_vc_int_status_check (
                   p_hw_vc, AMHW_ZLG118_VC2_FLT_INT_FLAG)){

        amhw_zlg118_vc_int_status_clr(p_hw_vc,AMHW_ZLG118_VC2_FLT_INT_FLAG_CLR);

    }else{

        return ;
    }

    p_dev->pfn_trigger_cb(p_dev);
}

/* VCͨ��ʹ�� */
int am_zlg118_vc_chan_enable (am_vc_handle_t vc_handle)
{

    amhw_zlg118_vc_t *p_hw_vc;

    if (vc_handle == NULL){

       return AM_ERROR;
    }

    p_hw_vc = (amhw_zlg118_vc_t *)(vc_handle->p_devinfo->vc_reg_base);

    /*ʹ�ܵ�ѹ�Ƚ���*/
    amhw_zlg118_vc_volt_cmp_enable(p_hw_vc, vc_handle->chan);

    return AM_OK;
}

/* �жϴ����������� */
int am_zlg118_tri_set (am_vc_handle_t vc_handle, void (*pfn_tri_cb) (void *))
{
    if (vc_handle == NULL || pfn_tri_cb == NULL ){

        return AM_ERROR;
    }

    vc_handle->pfn_trigger_cb = pfn_tri_cb;

    return AM_OK;
}

/**
 * \brief VC��ʼ��
 */
am_vc_handle_t am_zlg118_vc_init (am_zlg118_vc_dev_t           *p_dev,
                                  const am_zlg118_vc_devinfo_t *p_devinfo)
{
    amhw_zlg118_vc_t *p_hw_vc;

    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }

    p_dev->p_devinfo = p_devinfo;
    p_dev->chan      = p_devinfo->vc_chan;

    p_hw_vc = (amhw_zlg118_vc_t *)(p_dev->p_devinfo->vc_reg_base);

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* ʹ��BGR */
    amhw_zlg118_bgr_enable(AM_TRUE);

    /* ���òο���ѹ */
    amhw_zlg118_vc_ref2p5_sel (p_hw_vc, p_dev->p_devinfo->vc_vref);

    /* ѡ�� ���͵�ѹ�����ġ� �˲�ʱ�䡢  ͨ��N��P������ ���ж�����*/
    switch (p_dev->chan){

        case AMHW_ZLG118_VC0 :
                amhw_zlg118_vc0_hys_sel (p_hw_vc, p_dev->p_devinfo->vc_delay);
                amhw_zlg118_vc0_bias_sel (p_hw_vc, p_dev->p_devinfo->vc_bias);
                amhw_zlg118_vc0_flt_time_sel (p_hw_vc,
                                              p_dev->p_devinfo->vc_flt_time);
                amhw_zlg118_vc0_n_sel (p_hw_vc, p_dev->p_devinfo->vc_n_in);
                amhw_zlg118_vc0_p_sel (p_hw_vc, p_dev->p_devinfo->vc_p_in);
                amhw_zlg118_vc0_out_tri_int_sel (p_hw_vc,
                                                 p_dev->p_devinfo->vc_out_int);
            break;

        case AMHW_ZLG118_VC1 :
                amhw_zlg118_vc1_hys_sel (p_hw_vc, p_dev->p_devinfo->vc_delay);
                amhw_zlg118_vc1_bias_sel (p_hw_vc, p_dev->p_devinfo->vc_bias);
                amhw_zlg118_vc1_flt_time_sel (p_hw_vc,
                                              p_dev->p_devinfo->vc_flt_time);
                amhw_zlg118_vc1_n_sel (p_hw_vc, p_dev->p_devinfo->vc_n_in);
                amhw_zlg118_vc1_p_sel (p_hw_vc, p_dev->p_devinfo->vc_p_in);
                amhw_zlg118_vc1_out_tri_int_sel (p_hw_vc,
                                                 p_dev->p_devinfo->vc_out_int);
            break;
        case AMHW_ZLG118_VC2 :
                amhw_zlg118_vc2_hys_sel (p_hw_vc, p_dev->p_devinfo->vc_delay);
                amhw_zlg118_vc2_bias_sel (p_hw_vc, p_dev->p_devinfo->vc_bias);
                amhw_zlg118_vc2_flt_time_sel (p_hw_vc,
                                              p_dev->p_devinfo->vc_flt_time);
                amhw_zlg118_vc2_n_sel (p_hw_vc, p_dev->p_devinfo->vc_n_in);
                amhw_zlg118_vc2_p_sel (p_hw_vc, p_dev->p_devinfo->vc_p_in);
                amhw_zlg118_vc1_out_tri_int_sel (p_hw_vc,
                                                 p_dev->p_devinfo->vc_out_int);
            break;
    }

    /* ������� */
    amhw_zlg118_vc_outcfg_enable (p_hw_vc,
                                  p_dev->p_devinfo->vc_out_cfg,
                                  p_dev->chan);

    if (p_dev->p_devinfo->vc_flt_time != AMHW_ZLG118_DEB_TIME_NO){

        /* �˲�ʹ�� */
        amhw_zlg118_vc_flt_enable (p_hw_vc, p_dev->chan);
    }

    /* ��������ж�ʹ�� */
    amhw_zlg118_vc_int_enable (p_hw_vc, p_dev->chan);

    am_int_connect(p_dev->p_devinfo->vc_inum,
                   __vc_irq_handler,
                   (void *)p_dev);

    am_int_enable (p_dev->p_devinfo->vc_inum);

    return p_dev;

}

/**
 * \brief VCȥ��ʼ��
 */
void am_zlg118_vc_deinit (am_vc_handle_t handle)
{
    am_zlg118_vc_dev_t *p_dev  = (am_zlg118_vc_dev_t *)handle;
    amhw_zlg118_vc_t *p_hw_vc  =
                          (amhw_zlg118_vc_t *)(p_dev->p_devinfo->vc_reg_base);

    if (handle == NULL){

        return ;
    }

    /* �˲����� */
    amhw_zlg118_vc_flt_disable (p_hw_vc, p_dev->chan);

    /*���ܵ�ѹ�Ƚ���*/
    amhw_zlg118_vc_volt_cmp_disable(p_hw_vc, p_dev->chan);

    /* ��������жϽ��� */
    amhw_zlg118_vc_int_disable (p_hw_vc, p_dev->chan);

    am_int_disconnect(p_dev->p_devinfo->vc_inum,
                      __vc_irq_handler,
                      (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}
