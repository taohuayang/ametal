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
 * \brief LVD����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-08
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "am_zlg118.h"
#include "zlg118_periph_map.h"
#include "am_zlg118_lvd.h"
#include "hw/amhw_zlg118_lvd.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/
/**
 * \brief LVD�жϷ�����
 */
void __lvd_irq_handler (void *p_cookie);

/******************************************************************************/
/**
 * \brief LVD�жϷ�����
 */
void __lvd_irq_handler (void *p_cookie)
{
    amhw_zlg118_lvd_t *p_hw_lvd;
    am_zlg118_lvd_dev_t *p_dev = (am_zlg118_lvd_dev_t *)p_cookie;
    p_hw_lvd = (amhw_zlg118_lvd_t *)(p_dev->p_devinfo->reg_base);

    if (amhw_zlg118_int_status_check (p_hw_lvd)){

        /* ����жϱ�־ */
        amhw_zlg118_int_falg_clr (p_hw_lvd);

        /* �û��ص����� */
        p_dev->pfn_trigger_cb(p_dev);
    }
}

/**
 * \brief �жϴ�����������
 */
int am_zlg118_lvd_tri_set (am_lvd_handle_t handle, void (*pfn_tri_cb) (void *))
{
    if (handle == NULL || pfn_tri_cb == NULL ){

        return AM_ERROR;
    }

    handle->pfn_trigger_cb = pfn_tri_cb;

    return AM_OK;
}

/**
 * \brief lvd ʹ��
 */
int am_zlg118_lvd_enable (am_lvd_handle_t handle)
{
    amhw_zlg118_lvd_t *p_hw_lvd;

    if (handle == NULL){

        return AM_ERROR;
    }

    p_hw_lvd = (amhw_zlg118_lvd_t *)handle->p_devinfo->reg_base;

    /* ʹ��LVD */
    amhw_zlg118_lvd_enable (p_hw_lvd);

    return AM_OK;
}

/**
 * \brief lvd ��ʼ��
 */
am_lvd_handle_t  am_zlg118_lvd_init (am_zlg118_lvd_dev_t           *p_dev,
                                     const am_zlg118_lvd_devinfo_t *p_devinfo)
{
    amhw_zlg118_lvd_t *p_hw_lvd;

    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }

    p_dev->p_devinfo = p_devinfo;

    p_hw_lvd = (amhw_zlg118_lvd_t *)(p_dev->p_devinfo->reg_base);

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* cr�Ĵ������� */
    amhw_zlg118_lvd_cr_clr (p_hw_lvd);

    /* ��������ʹ�� */
    amhw_zlg118_lvd_tri_enable (p_hw_lvd, p_dev->p_devinfo->tri_type);

    /* �����˲�ʱ��ѡ�� */
    amhw_zlg118_lvd_deb_time_sel (p_hw_lvd, p_dev->p_devinfo->deb_time);

    /* ʹ�������˲� */
    amhw_zlg118_lvd_deb_time_enable (p_hw_lvd);

    /* ��ֵ��ѹѡ�� */
    amhw_zlg118_lvd_vids_sel (p_hw_lvd, p_dev->p_devinfo->vids);

    /* �����Դѡ�� */
    amhw_zlg118_lvd_src_sel (p_hw_lvd, p_dev->p_devinfo->src_sel);

    /* ������������ */
    amhw_zlg118_lvd_tri_act_sel (p_hw_lvd, p_dev->p_devinfo->tri_act);

    if (p_devinfo->tri_act == ANHW_ZLG118_LVD_TRI_ACT_NVIC_INT){

        /* �ж�״̬��־��� */
        amhw_zlg118_int_falg_clr (p_hw_lvd);

        /* ʹ���ж� */
        amhw_zlg118_lvd_int_enable (p_hw_lvd);

        /* �ж����� */
        am_int_connect(p_dev->p_devinfo->inum,
                       __lvd_irq_handler,
                       (void *)p_dev);
        /* �����ж� */
        am_int_enable (p_dev->p_devinfo->inum);
    }

    return p_dev;
}

/**
 * \brief lvd ȥ��ʼ��
 */
void am_zlg118_lvd_deinit (am_lvd_handle_t handle)
{
    am_zlg118_lvd_dev_t *p_dev  = (am_zlg118_lvd_dev_t *)handle;
    amhw_zlg118_lvd_t *p_hw_lvd =
                          (amhw_zlg118_lvd_t *)(p_dev->p_devinfo->reg_base);

    if (handle == NULL){

        return ;
    }

    /* �˲����� */
    amhw_zlg118_lvd_deb_time_disable (p_hw_lvd);

    if (p_dev->p_devinfo->tri_act == ANHW_ZLG118_LVD_TRI_ACT_NVIC_INT){

        /* �����ж� */
        amhw_zlg118_lvd_int_disable (p_hw_lvd);

        /* �ж����� */
        am_int_disconnect(p_dev->p_devinfo->inum,
                          __lvd_irq_handler,
                          (void *)p_dev);
    }

    /* ����LVD */
    amhw_zlg118_lvd_disable (p_hw_lvd);

    /* ƽ̨ȥ��ʼ�� */
    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
